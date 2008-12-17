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

#include <exception>
#include <string>

#include "core/StringUtils.h"
#include "engine/DatabaseConnection.h"
#include "sql/Identifier.h"
//-----------------------------------------------------------------------------
DatabaseConnectionThread::DatabaseConnectionThread(
        ThreadJobManager<SharedDBCThreadJob>& manager)
    : WorkerThread<SharedDBCThreadJob>(manager) 
{
};
//-----------------------------------------------------------------------------
IBPP::Database& DatabaseConnectionThread::getDatabase()
{
    // all access to IBPP objects has to happen in this thread
    wxASSERT(!wxIsMainThread());
    return databaseM;
}; 
//-----------------------------------------------------------------------------
void DatabaseConnectionThread::setDatabase(IBPP::Database& database)
{
    // all access to IBPP objects has to happen in this thread
    wxASSERT(!wxIsMainThread());
    databaseM = database;
};
//-----------------------------------------------------------------------------
// DatabaseConnectionThreadJob base class
DatabaseConnectionThreadJob::DatabaseConnectionThreadJob(
        SharedDatabase database)
    : databaseM(database), exceptionWhatM(), systemErrorM(false)
{
}
//-----------------------------------------------------------------------------
SharedDatabase DatabaseConnectionThreadJob::getDatabase()
{
    // all access to database has to happen in main thread
    wxASSERT(wxIsMainThread());
    return databaseM.lock();
}
//-----------------------------------------------------------------------------
bool DatabaseConnectionThreadJob::hasError()
{
    return systemErrorM || !exceptionWhatM.empty();
}
//-----------------------------------------------------------------------------
void DatabaseConnectionThreadJob::tryCancelExecution()
{
}
//-----------------------------------------------------------------------------
void DatabaseConnectionThreadJob::execute(
    WorkerThread<SharedDBCThreadJob>* thread)
{
    try
    {
        DatabaseConnectionThread* dct =
            dynamic_cast<DatabaseConnectionThread*>(thread);
        wxASSERT(dct);
        if (dct)
            executeJob(dct);
    }
    catch (std::exception& e)
    {
        exceptionWhatM = e.what();
    }
    catch (...)
    {
        systemErrorM = true;
    }
}
//-----------------------------------------------------------------------------
void DatabaseConnectionThreadJob::reportError(const wxString& primaryMsg)
{
    wxASSERT(wxIsMainThread());

    wxString msg(primaryMsg);
    if (!exceptionWhatM.empty())
    {
        SharedDatabase db = getDatabase();
        wxMBConv* conv = (db) ? db->getCharsetConverter() : wxConvCurrent;

        msg += wxT("\n\n");
        msg += std2wx(exceptionWhatM, conv);
    }
// TODO: show errors in a non-modal frame
    wxMessageBox(msg);
}
//-----------------------------------------------------------------------------
// DatabaseConnectJob class
class DatabaseConnectJob: public DatabaseConnectionThreadJob
{
private:
    std::string charsetM;
    std::string connectionStringM;
    std::string passwordM;
    std::string roleNameM;
    std::string userNameM;

    bool connectedM;
    std::string serverVersionM;
protected:
    virtual void executeJob(DatabaseConnectionThread* thread);
public:
    DatabaseConnectJob(SharedDatabase database);
    virtual void processResults();
};
//-----------------------------------------------------------------------------
DatabaseConnectJob::DatabaseConnectJob(SharedDatabase database)
    : DatabaseConnectionThreadJob(database), connectedM(false)
{
    wxASSERT(wxIsMainThread());
    wxASSERT(database);

    wxMBConv* conv = database->getCharsetConverter();
    const DatabaseCredentials& dbc = database->getCredentials();
    charsetM = wx2std(dbc.getCharset(), conv);
    connectionStringM = wx2std(database->getConnectionString(), conv);
    passwordM = wx2std(dbc.getRawPassword(), conv);
    roleNameM = wx2std(dbc.getRole(), conv);
    userNameM = wx2std(dbc.getUsername(), conv);
}
//-----------------------------------------------------------------------------
void DatabaseConnectJob::executeJob(DatabaseConnectionThread* thread)
{
    wxASSERT(thread);
    // first reset previous database
    IBPP::Database db;
    thread->setDatabase(db);
    db = IBPP::DatabaseFactory("", connectionStringM, userNameM, passwordM,
        roleNameM, charsetM, "");
    db->Connect();
    // set new database if connection successful
    thread->setDatabase(db);
    connectedM = true;

    serverVersionM = "";
    std::string serverName(connectionStringM);
    size_t colon = serverName.find_first_of(":");
    if (colon != std::string::npos)
    {
        serverName.resize(colon);
        IBPP::Service svc = IBPP::ServiceFactory(serverName, userNameM,
            passwordM);
        svc->Connect();
        svc->GetVersion(serverVersionM);
    }
}
//-----------------------------------------------------------------------------
void DatabaseConnectJob::processResults()
{
    wxASSERT(wxIsMainThread());

    SharedDatabase db = getDatabase();
    if (!db)
        return;

    if (connectedM)
    {
        db->setConnectionState(Database::csConnected);
        db->setServerVersion(std2wx(serverVersionM,
            db->getCharsetConverter()));
    }
    else
    {
        db->setConnectionState(Database::csConnectionFailed);
        wxString primaryMsg(wxString::Format(_("An error occurred while connecting to the database \"%s\"!"),
            db->getName().c_str()));
        reportError(primaryMsg);
    }
}
//-----------------------------------------------------------------------------
// DatabaseDisconnectJob class
class DatabaseDisconnectJob: public DatabaseConnectionThreadJob
{
private:
    bool disconnectedM;
protected:
    virtual void executeJob(DatabaseConnectionThread* thread);
public:
    DatabaseDisconnectJob(SharedDatabase database);
    virtual void processResults();
};
//-----------------------------------------------------------------------------
DatabaseDisconnectJob::DatabaseDisconnectJob(SharedDatabase database)
    : DatabaseConnectionThreadJob(database), disconnectedM(false)
{
    wxASSERT(wxIsMainThread());
}
//-----------------------------------------------------------------------------
void DatabaseDisconnectJob::executeJob(DatabaseConnectionThread* thread)
{
    wxASSERT(thread);
    IBPP::Database db = thread->getDatabase();
    if (db != 0 && db->Connected())
    {
        db->Disconnect();
        db.clear();
        thread->setDatabase(db);
        disconnectedM = true;
    }
}
//-----------------------------------------------------------------------------
void DatabaseDisconnectJob::processResults()
{
    wxASSERT(wxIsMainThread());

    SharedDatabase db = getDatabase();
    if (!db)
        return;

    if (disconnectedM)
        db->setConnectionState(Database::csDisconnected);
    else
    {
        wxString primaryMsg(wxString::Format(_("An error occurred while disconnecting from the database \"%s\"!"),
            db->getName().c_str()));
        reportError(primaryMsg);
    }
}
//-----------------------------------------------------------------------------
// FetchIdentifiersJob class
class FetchIdentifiersJob: public DatabaseConnectionThreadJob
{
private:
    Item::Handle itemHandleM;
    std::string statementM;
    std::vector<std::string> paramsM;
    std::list<std::string> identifiersM;
    std::list<VectorOfAny> dataM;

    volatile bool cancelM;
protected:
    virtual void executeJob(DatabaseConnectionThread* thread);
public:
    FetchIdentifiersJob(SharedDatabase database, Item::Handle itemHandle,
        const std::string& statement);
    FetchIdentifiersJob(SharedDatabase database, Item::Handle itemHandle,
        const std::string& statement, const std::vector<std::string>& params);
    virtual void processResults();
    virtual void tryCancelExecution();
};
//-----------------------------------------------------------------------------
FetchIdentifiersJob::FetchIdentifiersJob(SharedDatabase database,
        Item::Handle itemHandle, const std::string& statement)
    : DatabaseConnectionThreadJob(database), itemHandleM(itemHandle),
        statementM(statement), cancelM(false)
{
    wxASSERT(wxIsMainThread());
}
//-----------------------------------------------------------------------------
FetchIdentifiersJob::FetchIdentifiersJob(SharedDatabase database,
        Item::Handle itemHandle, const std::string& statement,
        const std::vector<std::string>& params)
    : DatabaseConnectionThreadJob(database), itemHandleM(itemHandle),
        statementM(statement), paramsM(params), cancelM(false)
{
    wxASSERT(wxIsMainThread());
}
//-----------------------------------------------------------------------------
void FetchIdentifiersJob::executeJob(DatabaseConnectionThread* thread)
{
    wxASSERT(thread);
    IBPP::Database db = thread->getDatabase();
    if (db != 0 && db->Connected())
    {
        IBPP::Transaction tr = IBPP::TransactionFactory(db, IBPP::amRead);
        tr->Start();
        IBPP::Statement st = IBPP::StatementFactory(db, tr, statementM);
        if (paramsM.size())
        {
            for (unsigned i = 1; i <= paramsM.size(); ++i)
                st->Set(i, paramsM[i - 1]);
        }
        st->Execute();
        int columns = st->Columns();
        while (!cancelM && st->Fetch())
        {
            std::string name;
            // do as little as possible here
            // trailing spaces are removed when Identifier is created
            if (!st->Get(1, name))
            {
                identifiersM.push_back(name);

                if (columns > 1)
                {
                    VectorOfAny data;
                    data.reserve(2 * (columns - 1));
                    for (int i = 2; i <= columns; ++i)
                    {
                        // initialize with defaults for NULL in column
                        bool isNull;
                        int n = 0;
                        std::string s;

                        switch (st->ColumnType(i))
                        {
                            case IBPP::sdSmallint:
                            case IBPP::sdInteger:
                                isNull = st->Get(i, n);
                                data.push_back(isNull);
                                data.push_back(n);
                                break;
                            // TODO: handle more data types
                            default:
                                isNull = st->Get(i, s);
                                data.push_back(isNull);
                                data.push_back(s);
                                break;
                        }
                    }
                    dataM.push_back(data);
                }
            }
        }
    }
}
//-----------------------------------------------------------------------------
void FetchIdentifiersJob::processResults()
{
    wxASSERT(wxIsMainThread());

    if (cancelM)
        return;

    if (hasError())
    {
        reportError(_("An error occurred while fetching the list of identifiers!"));
        return;
    }

    Item* item = Item::getFromHandle(itemHandleM);
    MetadataItemCollection* collection =
        dynamic_cast<MetadataItemCollection*>(item);
    wxASSERT(collection);
    if (collection)
    {
        SharedDatabase db = getDatabase();
        wxMBConv* conv = (db) ? db->getCharsetConverter() : wxConvCurrent;

        if (dataM.size() && dataM.size() == identifiersM.size())
        {
            // build a list of IdentifierAndData structs from the std::strings
            // and vector<boost::any> objects
            // the Identifier constructor will strip trailing spaces
            std::list<MetadataItemCollection::IdentifierAndData> identAndData;
            std::list<VectorOfAny>::iterator itData = dataM.begin();
            for (std::list<std::string>::iterator it = identifiersM.begin();
                it != identifiersM.end(); ++it)
            {
                MetadataItemCollection::IdentifierAndData iaa;
                iaa.identifier.setText(std2wx(*it, conv));
                iaa.data = *itData;
                identAndData.push_back(iaa);
                ++itData;
            }
            collection->setChildrenIdentifiersData(identAndData);
        }
        else
        {
            // build a list of Identifier objects from the strings
            // the Identifier constructor will strip trailing spaces
            std::list<Identifier> identifiers;
            for (std::list<std::string>::iterator it = identifiersM.begin();
                it != identifiersM.end(); ++it)
            {
                Identifier id(std2wx(*it, conv));
                identifiers.push_back(id);
            }
            collection->setChildrenIdentifiers(identifiers);
        }
    }
}
//-----------------------------------------------------------------------------
void FetchIdentifiersJob::tryCancelExecution()
{
    cancelM = true;
}
//-----------------------------------------------------------------------------
// DatabaseConnection class
DatabaseConnection::DatabaseConnection(Database& database)
    : WorkerThreadEngine<SharedDBCThreadJob>()
{
    databaseM = database.asShared();
}
//-----------------------------------------------------------------------------
WorkerThread<SharedDBCThreadJob>* DatabaseConnection::createWorkerThread()
{
    return new DatabaseConnectionThread(*this);
}
//-----------------------------------------------------------------------------
void DatabaseConnection::connect()
{
    SharedDatabase db = databaseM.lock();
    if (db)
        queueJob(SharedDBCThreadJob(new DatabaseConnectJob(db)));
}
//-----------------------------------------------------------------------------
void DatabaseConnection::disconnect()
{
    SharedDatabase db = databaseM.lock();
    if (db)
        queueJob(SharedDBCThreadJob(new DatabaseDisconnectJob(db)));
}
//-----------------------------------------------------------------------------
void DatabaseConnection::executeJob(SharedDBCThreadJob job)
{
    wxCHECK_RET(job.get(),
        wxT("job is 0 in DatabaseConnection::executeJob(()"));
    queueJob(job);
}
//-----------------------------------------------------------------------------
void DatabaseConnection::loadCollection(Item::Handle itemHandle,
    const std::string& sql)
{
    SharedDatabase db = databaseM.lock();
    if (db)
    {
        queueJob(SharedDBCThreadJob(
            new FetchIdentifiersJob(db, itemHandle, sql)));
    }
}
//-----------------------------------------------------------------------------
void DatabaseConnection::loadCollection(Item::Handle itemHandle,
    const std::string& sql, const std::vector<std::string>& params)
{
    SharedDatabase db = databaseM.lock();
    if (db)
    {
        queueJob(SharedDBCThreadJob(
            new FetchIdentifiersJob(db, itemHandle, sql, params)));
    }
}
//-----------------------------------------------------------------------------
