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

#include <wx/filename.h>
#include <wx/wfstream.h>

#include "config/Config.h"
#include "core/Subject.h"
#include "hierarchy/Database.h"
#include "hierarchy/TreeRoot.h"
//-----------------------------------------------------------------------------
static const wxString getXmlNodeContent(wxXmlNode* node,
    const wxString& defaultValue)
{
    for (wxXmlNode* n = node->GetChildren(); (n); n = n->GetNext())
    {
        if (n->GetType() == wxXML_TEXT_NODE)
            return n->GetContent();
        if (n->GetType() == wxXML_CDATA_SECTION_NODE)
            return n->GetContent();
    }
    return defaultValue;
}
//-----------------------------------------------------------------------------
// TreeRoot class
TreeRoot::TreeRoot()
	: TreeFolder(), needsSaveM(false), nextIdM(0)
{
    setName(_("Firebird Databases"));
}
//-----------------------------------------------------------------------------
/*static*/ 
SharedTreeRoot TreeRoot::get()
{
    static SharedTreeRoot sharedRoot(new TreeRoot());
    return sharedRoot;
}
//-----------------------------------------------------------------------------
void TreeRoot::createDefaultHierarchy()
{
    SharedTreeFolder child = SharedTreeFolder(new TreeFolder);
    child->setName(_("Localhost"));
    child->setParent(shared_from_this());
}
//-----------------------------------------------------------------------------
wxString TreeRoot::getFileName()
{
    if (fileNameM.empty())
        fileNameM = config().getDBHFileName();
    return fileNameM;
}
//-----------------------------------------------------------------------------
const unsigned TreeRoot::getNextId()
{
    return ++nextIdM;
}
//-----------------------------------------------------------------------------
bool TreeRoot::loadHierarchy()
{
    wxXmlDocument doc;
    // if the DBH file (fr_hierarchy.conf) does not exist, try to migrate the
    // old DBH file (fr_databases.conf), promoting server nodes to folders in
    // the process
    bool imported = false;
    wxFileName fileName(getFileName());
    if (!fileName.FileExists())
    {
        fileName.SetName(wxT("fr_databases"));
        imported = true;
    }
    if (fileName.FileExists())
    {
        wxFileInputStream stream(fileName.GetFullPath());
        if (stream.Ok())
            doc.Load(stream);
    }
    if (!doc.IsOk())
        return false;

    wxXmlNode* xmlr = doc.GetRoot();
    if (xmlr->GetName() != wxT("root"))
        return false;

    SharedItem me(shared_from_this());

    SubjectLocker lock(this);
    for (wxXmlNode* xmln = doc.GetRoot()->GetChildren(); (xmln);
        xmln = xmln->GetNext())
    {
        if (xmln->GetType() != wxXML_ELEMENT_NODE)
            continue;
        if (xmln->GetName() == wxT("database"))
            parseDatabase(me, xmln, wxEmptyString, imported);
        else if (xmln->GetName() == wxT("folder"))
            parseFolder(me, xmln);
        else if (xmln->GetName() == wxT("server"))
            parseServer(me, xmln);
        else if (xmln->GetName() == wxT("name"))
        {
            wxString value(getXmlNodeContent(xmln, wxEmptyString));
            if (!value.empty())
                setName(value);
        }
        else if (xmln->GetName() == wxT("nextId"))
        {
            wxString value(getXmlNodeContent(xmln, wxEmptyString));
            unsigned long id;
            // nextIdM may have been written already (from database id)
            if (!value.IsEmpty() && value.ToULong(&id) && id > nextIdM)
                nextIdM = id;
        }
    }
    needsSaveM = false;
    return true;
}
//-----------------------------------------------------------------------------
bool TreeRoot::parseDatabase(SharedItem parent, wxXmlNode* xmln,
    const wxString& serverHostnamePort, bool importOldSettings)
{
    wxASSERT(xmln);

    SharedDatabase database(new Database);
    SubjectLocker lock(database.get());
    database->setParent(parent);

    DatabaseCredentials dbc;
    if (importOldSettings)
        dbc.setAskForPassword(true);

    for (xmln = xmln->GetChildren(); (xmln); xmln = xmln->GetNext())
    {
        if (xmln->GetType() != wxXML_ELEMENT_NODE)
            continue;

        wxString value(getXmlNodeContent(xmln, wxEmptyString));
        if (xmln->GetName() == wxT("name"))
            database->setName(value);
        else if (xmln->GetName() == wxT("path"))
            database->setConnectionString(serverHostnamePort, value);
        else if (xmln->GetName() == wxT("connectionstring"))
            database->setConnectionString(value);
        else if (xmln->GetName() == wxT("charset"))
            dbc.setCharset(value);
        else if (xmln->GetName() == wxT("username"))
            dbc.setUsername(value);
        else if (xmln->GetName() == wxT("password"))
        {
            dbc.setRawPassword(value);
            if (importOldSettings && value != wxEmptyString)
                dbc.setAskForPassword(false);
        }
        else if (xmln->GetName() == wxT("askforpassword"))
            dbc.setAskForPassword(value == wxT("1"));
        else if (xmln->GetName() == wxT("encrypted"))
            database->setStoreEncryptedPassword(value == wxT("1"));
        else if (xmln->GetName() == wxT("role"))
            dbc.setRole(value);
        else if (xmln->GetName() == wxT("id"))
        {
            unsigned long id;
            if (value.ToULong(&id))
            {
                database->setDatabaseId(id);
                // force nextIdM to be higher than ids of existing databases
                if (nextIdM <= id)
                    nextIdM = id + 1;
            }
        }
    }
    database->setCredentials(dbc);
    return true;
}
//-----------------------------------------------------------------------------
bool TreeRoot::parseFolder(SharedItem parent, wxXmlNode* xmln)
{
    wxASSERT(xmln);

    SharedTreeFolder folder(new TreeFolder);
    SubjectLocker lock(folder.get());
    folder->setParent(parent);

    for (xmln = xmln->GetChildren(); (xmln); xmln = xmln->GetNext())
    {
        if (xmln->GetType() != wxXML_ELEMENT_NODE)
            continue;

        wxString value(getXmlNodeContent(xmln, wxEmptyString));
        if (xmln->GetName() == wxT("folder"))
            parseFolder(folder, xmln);
        else if (xmln->GetName() == wxT("name"))
            folder->setName(value);
        else if (xmln->GetName() == wxT("database"))
        {
            // folder is part of new hierarchy file format
            if (!parseDatabase(folder, xmln, wxEmptyString, false))
                return false;
        }
    }
    return true;
}
//-----------------------------------------------------------------------------
bool TreeRoot::parseServer(SharedItem parent, wxXmlNode* xmln)
{
    wxASSERT(xmln);

    SharedTreeFolder folder(new TreeFolder);
    SubjectLocker lock(folder.get());
    folder->setParent(parent);

    wxString srvHostPort;

    for (xmln = xmln->GetChildren(); (xmln); xmln = xmln->GetNext())
    {
        if (xmln->GetType() != wxXML_ELEMENT_NODE)
            continue;

        wxString value(getXmlNodeContent(xmln, wxEmptyString));
        if (xmln->GetName() == wxT("name"))
        {
            folder->setName(wxString::Format(_("Databases on %s"),
                value.c_str()));
        }
        else if (xmln->GetName() == wxT("host"))
        {
            if (!srvHostPort.empty())
                srvHostPort.insert(0, value + wxT(":"));
            else
                srvHostPort = value;
        }
        else if (xmln->GetName() == wxT("port"))
        {
            if (!srvHostPort.empty())
                srvHostPort += wxT(":") + value;
            else
                srvHostPort = value;
        }
        else if (xmln->GetName() == wxT("database"))
        {
            // server is part of old hierarchy file format
            if (!parseDatabase(folder, xmln, srvHostPort, true))
                return false;
        }
    }
    // backward compatibility with FR < 0.3.0
    if (folder->getName().empty())
        folder->setName(srvHostPort);
    return true;
}
//-----------------------------------------------------------------------------
bool TreeRoot::saveHierarchy()
{
// TODO: implement TreeRoot::saveHierarchy()
    return false;
}
//-----------------------------------------------------------------------------
