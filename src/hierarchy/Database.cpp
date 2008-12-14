/*
  Copyright (c) 2004-2008 The FlameRobin Development Team

  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files (the
  "Software"), to deal in the Software without restriction, including
  without limitation the rights to use, copy, modify, merge, publish,
  distribute, sublicense, and/or sell copies of the Software, and to
  permit persons to whom the Software is furnished to do so, subject to
  the following conditions:

  The above copyright notice and this permission notice shall be included
  in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


  $Id$

*/

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <wx/regex.h>

#include "core/StringUtils.h"

#include "engine/DatabaseConnection.h"
#include "engine/ServiceConnection.h"

#include "hierarchy/Database.h"
#include "hierarchy/Domain.h"
#include "hierarchy/Exception.h"
#include "hierarchy/Function.h"
#include "hierarchy/Generator.h"
#include "hierarchy/ItemVisitor.h"
#include "hierarchy/Procedure.h"
#include "hierarchy/Table.h"
#include "hierarchy/TreeRoot.h"
#include "hierarchy/Trigger.h"
#include "hierarchy/View.h"
//-----------------------------------------------------------------------------
// ServerVersion class
void ServerVersion::initialize(const wxString& versionString)
{
    if (versionStringM != versionString)
    {
        versionStringM = versionString;
        versionNumbersM.clear();

        if (!versionString.empty())
        {
            const wxString FirebirdVersionString = wxT("(.*)") // WI, LI, ...
                wxT("-V([0-9]+)\\.([0-9]+)\\.([0-9]+)\\.([0-9]+)") // x.y.z.b
                wxT("[ \t]*(.*)");                             // Firebird x.y
            wxRegEx re(FirebirdVersionString);
            if (re.IsValid() && re.Matches(versionString))
            {
                wxString match = re.GetMatch(versionString, 1);
                for (unsigned i = 2; i <= 5; ++i)
                {
                    match = re.GetMatch(versionString, i);
                    unsigned long ver;
                    if (match.ToULong(&ver))
                        versionNumbersM.push_back(ver);
                }
            }
        }
    }
}
//-----------------------------------------------------------------------------
void ServerVersion::reset()
{
    versionStringM.clear();
    versionNumbersM.clear();
}
//-----------------------------------------------------------------------------
bool ServerVersion::versionIsAtLeast(unsigned major, unsigned minor,
    unsigned release, unsigned build) const
{
    if (versionNumbersM.size() != 4)
        return false;
    if (versionNumbersM[0] != major)
        return versionNumbersM[0] > major;
    if (versionNumbersM[1] != minor)
        return versionNumbersM[1] > minor;
    if (versionNumbersM[2] != release)
        return versionNumbersM[2] > release;
    return versionNumbersM[3] >= build;
}
//-----------------------------------------------------------------------------
// DatabaseCredentials class
DatabaseCredentials::DatabaseCredentials()
{
    askForPasswordM = true;
}
//-----------------------------------------------------------------------------
wxString DatabaseCredentials::getCharset() const
{
    return charsetM;
}
//-----------------------------------------------------------------------------
wxString DatabaseCredentials::getUsername() const
{
    return usernameM;
}
//-----------------------------------------------------------------------------
wxString DatabaseCredentials::getRawPassword() const
{
    return passwordM;
}
//-----------------------------------------------------------------------------
wxString DatabaseCredentials::getRole() const
{
    return roleM;
}
//-----------------------------------------------------------------------------
bool DatabaseCredentials::getAskForPassword() const
{
    return askForPasswordM;
}
//-----------------------------------------------------------------------------
void DatabaseCredentials::setCharset(const wxString& charset)
{
    charsetM = charset;
}
//-----------------------------------------------------------------------------
void DatabaseCredentials::setUsername(const wxString& username)
{
    usernameM = username;
}
//-----------------------------------------------------------------------------
void DatabaseCredentials::setRawPassword(const wxString& password)
{
    passwordM = password;
}
//-----------------------------------------------------------------------------
void DatabaseCredentials::setAskForPassword(bool askForPassword)
{
    askForPasswordM = askForPassword;
}
//-----------------------------------------------------------------------------
void DatabaseCredentials::setRole(const wxString& role)
{
    roleM = role;
}
//-----------------------------------------------------------------------------
bool DatabaseCredentials::operator!= (const DatabaseCredentials& rhs) const
{
    return (rhs.charsetM != charsetM) || (rhs.usernameM != usernameM)
        || (rhs.passwordM != passwordM) || (rhs.roleM != roleM);
}
//-----------------------------------------------------------------------------
// Database class
Database::Database()
    : ItemWithChildrenBase(), idM(0), encryptedPasswordM(false),
        connectionStateM(csDisconnected)
{
    // children are all static collections of metadata objects
    setLoadChildrenState(lcsLoaded);
}
//-----------------------------------------------------------------------------
Database::~Database()
{
    metadataConnectionM.reset();
    setConnectionState(csDisconnected);

    detachAllObservers();
    resetTemporaryCredentials();
}
//-----------------------------------------------------------------------------
Database* Database::getDatabase()
{
    return this;
}
//-----------------------------------------------------------------------------
bool Database::hasChildren()
{
    return isConnected() && ItemWithChildrenBase::hasChildren();
}
//-----------------------------------------------------------------------------
const wxString Database::getTypeName() const
{
    return wxT("DATABASE");
}
//-----------------------------------------------------------------------------
const wxString Database::getId() const
{
    if (idM == 0)
        idM = TreeRoot::get()->getNextId();
    return wxString::Format(wxT("%d"), idM);
}
//-----------------------------------------------------------------------------
void Database::setName(const wxString& name)
{
    if (getName() != name)
    {
        setNameImpl(name);
        notifyObservers();
    }
}
//-----------------------------------------------------------------------------
void Database::setDatabaseId(unsigned id) const
{
    idM = id;
}
//-----------------------------------------------------------------------------
void Database::refreshData()
{
// TODO
}
//-----------------------------------------------------------------------------
const wxString& Database::getConnectionString() const
{
    return connectionStringM;
}
//-----------------------------------------------------------------------------
void Database::setConnectionString(const wxString& connectionstring)
{
    wxCHECK_RET(!isConnected(), 
        wxT("Database::setConnectionString() called while connected"));
    if (connectionStringM != connectionstring)
    {
        connectionStringM = connectionstring;
        notifyObservers();
    }
}
//-----------------------------------------------------------------------------
void Database::setConnectionString(const wxString& hostNamePort, 
    const wxString& path)
{
    setConnectionString(hostNamePort + wxT(":") + path);
}
//-----------------------------------------------------------------------------
const DatabaseCredentials& Database::getCredentials() const
{
    if (tempCredentialsM)
        return *tempCredentialsM;
    return credentialsM;
}
//-----------------------------------------------------------------------------
void Database::setCredentials(DatabaseCredentials dbc)
{
    wxCHECK_RET(!isConnected(), 
        wxT("Database::setCredentials() called while connected"));
    if (credentialsM != dbc)
    {
        credentialsM = dbc;
        notifyObservers();
    }
}
//-----------------------------------------------------------------------------
void Database::setTemporaryCredentials(const DatabaseCredentials& dbc)
{
    wxCHECK_RET(!isConnected(), 
        wxT("Database::setTemporaryCredentials() called while connected"));
    // if no existing or different temporary credentials, then create new
    if (!tempCredentialsM || *tempCredentialsM != dbc)
    {
        tempCredentialsM.reset(new DatabaseCredentials(dbc));
        notifyObservers();
    }
}
//-----------------------------------------------------------------------------
void Database::resetTemporaryCredentials()
{
    wxCHECK_RET(!isConnected(), 
        wxT("Database::resetTemporaryCredentials() called while connected"));
    if (tempCredentialsM)
    {
        tempCredentialsM.reset();
        notifyObservers();
    }
}
//-----------------------------------------------------------------------------
void Database::setStoreEncryptedPassword(bool encrypted)
{
    encryptedPasswordM = encrypted;
}
//-----------------------------------------------------------------------------
DatabaseConnection* Database::getMetadataConnection()
{
    return metadataConnectionM.get();
}
//-----------------------------------------------------------------------------
void Database::accept(ItemVisitor* visitor)
{
    wxASSERT(visitor);
    if (visitor)
        visitor->visit(*this);
}
//-----------------------------------------------------------------------------
bool Database::canConnect() const
{
    return connectionStateM == csDisconnected
        || connectionStateM == csConnectionFailed
        || connectionStateM == csRestoreFailed;
}
//-----------------------------------------------------------------------------
void Database::connect()
{
    if (canConnect())
    {
        // setConnectionState() checks for valid metadataConnectionM...
        if (!metadataConnectionM)
            metadataConnectionM.reset(new DatabaseConnection(*this));
        setConnectionState(csConnecting);
        metadataConnectionM->connect();
    }
}
//-----------------------------------------------------------------------------
void Database::disconnect()
{
    if (isConnected() && metadataConnectionM)
    {
        setConnectionState(csDisconnecting);
        metadataConnectionM->disconnect();
    }
}
//-----------------------------------------------------------------------------
bool Database::isConnected() const
{
    return (connectionStateM == csConnected && metadataConnectionM != 0);
}
//-----------------------------------------------------------------------------
Database::ConnectionState Database::getConnectionState() const
{
    return connectionStateM;
}
//-----------------------------------------------------------------------------
void Database::setConnectionState(ConnectionState state)
{
    wxASSERT(metadataConnectionM != 0 || state == csDisconnected);
    if (connectionStateM != state)
    {
        SubjectLocker lock(this);

        connectionStateM = state;
        if (connectionStateM == csDisconnected)
        {
            deleteCollections();
            serverVersionM.reset();
        }
        else if (connectionStateM == csConnected)
        {
            createCollections();
            refreshData();
        }
        notifyObservers();
    }
}
//-----------------------------------------------------------------------------
bool Database::canRestoreFromBackup() const
{
    return connectionStateM == csDisconnected
        || connectionStateM == csConnectionFailed
        || connectionStateM == csRestoreFailed;
}
//-----------------------------------------------------------------------------
void Database::setServerVersion(const wxString& versionString)
{
    serverVersionM.initialize(versionString);
}
//-----------------------------------------------------------------------------
void Database::createCollections()
{
    PSharedItem me(shared_from_this());
    // create shared pointers to collections
    // setParent() will add these to the list of child items
    // create (and load) them in order of importance, because captions
    // may be different in other languages and need to be reordered anyway
    tablesM = PSharedTableCollection(new TableCollection());
    tablesM->setParent(me);
    tablesM->loadChildren();

    viewsM = PSharedViewCollection(new ViewCollection());
    viewsM->setParent(me);
    viewsM->loadChildren();

    proceduresM = PSharedProcedureCollection(new ProcedureCollection());
    proceduresM->setParent(me);
    proceduresM->loadChildren();

    if (serverVersionM.supportsDatabaseTriggers())
    {
        triggersM = PSharedTriggerCollection(new TriggerCollection());
        triggersM->setParent(me);
        triggersM->loadChildren();
    }

    functionsM = PSharedFunctionCollection(new FunctionCollection());
    functionsM->setParent(me);
    functionsM->loadChildren();

    generatorsM = PSharedGeneratorCollection(new GeneratorCollection());
    generatorsM->setParent(me);
    generatorsM->loadChildren();

    domainsM = PSharedDomainCollection(new DomainCollection());
    domainsM->setParent(me);
    domainsM->loadChildren();

    exceptionsM = PSharedExceptionCollection(new ExceptionCollection());
    exceptionsM->setParent(me);
    exceptionsM->loadChildren();

    systemTablesM = PSharedSystemTableCollection(new SystemTableCollection());
    systemTablesM->setParent(me);
    systemTablesM->loadChildren();

    systemDomainsM = PSharedSystemDomainCollection(new SystemDomainCollection());
    systemDomainsM->setParent(me);
    systemDomainsM->loadChildren();
}
//-----------------------------------------------------------------------------
void Database::deleteCollections()
{
    clearChildren();
    // reset all shared pointers to collections
    domainsM.reset();
    exceptionsM.reset();
    functionsM.reset();
    generatorsM.reset();
    proceduresM.reset();
    systemDomainsM.reset();
    systemTablesM.reset();
    tablesM.reset();
    triggersM.reset();
    viewsM.reset();
}
//-----------------------------------------------------------------------------
Domain* Database::getDomain(const Identifier& identifier)
{
    Domain* domain = 0;
    if (domainsM && 0 != (domain = domainsM->getDomain(identifier)))
        return domain;
    if (systemDomainsM)
        domain = systemDomainsM->getDomain(identifier);
    return domain;
}
//-----------------------------------------------------------------------------
/*static*/
wxArrayString Database::getAvailablePageSizes()
{
    wxArrayString sizes;
    sizes.reserve(6);
    sizes.push_back(_("Default"));
    sizes.push_back(wxT("1024"));
    sizes.push_back(wxT("2048"));
    sizes.push_back(wxT("4096"));
    sizes.push_back(wxT("8192"));
    sizes.push_back(wxT("16384"));
    return sizes;
}
//-----------------------------------------------------------------------------
