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

#ifndef FR_DATABASE_H
#define FR_DATABASE_H
//-----------------------------------------------------------------------------
#include <ibpp.h>

#include "hierarchy/Item.h"

class DatabaseConnection;
//-----------------------------------------------------------------------------
// ServerVersion helper class
class ServerVersion
{
private:
    wxString versionStringM;
    std::vector<unsigned> versionNumbersM;
    inline bool versionIsAtLeast(unsigned major, unsigned minor = 0,
        unsigned release = 0, unsigned build = 0) const;
public:
    void initialize(const wxString& versionString);
    void reset();

    bool supportsDatabaseTriggers() const { return versionIsAtLeast(2, 1); };
};
//-----------------------------------------------------------------------------
// DatabaseCredentials helper class
class DatabaseCredentials
{
private:
    wxString charsetM;
    wxString usernameM;
    wxString passwordM;
    wxString roleM;
public:
    DatabaseCredentials();

    wxString getCharset() const;
    wxString getUsername() const;
    wxString getRawPassword() const;
    wxString getRole() const;
    void setCharset(const wxString& charset);
    void setUsername(const wxString& username);
    void setRawPassword(const wxString& password);
    void setRole(const wxString& role);
    bool operator!= (DatabaseCredentials& rhs);
};
//-----------------------------------------------------------------------------
// Database class
class Database : public ItemWithChildrenBase
{
public:
    Database();
    ~Database();

    virtual Database* getDatabase();
    virtual bool hasChildren();

    virtual const wxString getTypeName() const;
    virtual const wxString getId() const;
    void setName(const wxString& name);
    void setDatabaseId(unsigned id) const;

    virtual void refreshData();

    const wxString& getConnectionString() const;
    void setConnectionString(const wxString& connectionstring);
    void setConnectionString(const wxString& hostNamePort,
        const wxString& path);

    const DatabaseCredentials& getCredentials() const;
    void setCredentials(DatabaseCredentials dbc);
    void setTemporaryCredentials(DatabaseCredentials dbc);
    void resetTemporaryCredentials();
    void setStoreEncryptedPassword(bool encrypted);

    enum ConnectionState {
        csConnecting, csConnected, csDisconnecting, csDisconnected };

    void connect();
    void disconnect();
    bool isConnected() const;
    bool isDisconnected() const;
    ConnectionState getConnectionState() const;
    void setConnectionState(ConnectionState state);

    void setServerVersion(const wxString& versionString);

    DatabaseConnection* getMetadataConnection();

    virtual void accept(ItemVisitor* visitor);
private:
    mutable unsigned idM;
    DatabaseCredentials credentialsM;
    DatabaseCredentials* tempCredentialsM;
    bool encryptedPasswordM;

    wxString connectionStringM;

    ConnectionState connectionStateM;
    DatabaseConnection* metadataConnectionM;
    ServerVersion serverVersionM;

    PSharedGeneratorCollection generatorsM;
    PSharedSystemTableCollection systemTablesM;
    PSharedTriggerCollection triggersM;
    PSharedTableCollection tablesM;
    PSharedViewCollection viewsM;

    void createCollections();
    void deleteCollections();
};
//-----------------------------------------------------------------------------
#endif // FR_DATABASE_H
