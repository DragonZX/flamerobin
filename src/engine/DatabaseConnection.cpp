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
class DatabaseConnectionThread: public WorkerThread<SharedDBCThreadJob>
{
private:
    IBPP::Database databaseM;
    IBPP::Transaction transactionM;
public:
    DatabaseConnectionThread(ThreadJobManager<SharedDBCThreadJob>& manager);
    IBPP::Database& getDatabase(); 
    IBPP::Transaction& getTransaction();
    void setDatabase(IBPP::Database& database);
};
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
IBPP::Transaction& DatabaseConnectionThread::getTransaction()
{
    // all access to IBPP objects has to happen in this thread
    wxASSERT(!wxIsMainThread());
    return transactionM;
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
DatabaseConnectionThreadJob::DatabaseConnectionThreadJob(Database& database)
    : databaseM(database), exceptionWhatM(), systemErrorM(false)
{
}
//-----------------------------------------------------------------------------
Database& DatabaseConnectionThreadJob::getDatabase()
{
    // all access to database has to happen in main thread
    wxASSERT(wxIsMainThread());
    return databaseM;
}
//-----------------------------------------------------------------------------
bool DatabaseConnectionThreadJob::canCancelExecution()
{
    return false;
}
//-----------------------------------------------------------------------------
void DatabaseConnectionThreadJob::cancelExecution()
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
        msg += wxT("\n\n");
        msg += std2wx(exceptionWhatM);
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
protected:
    virtual void executeJob(DatabaseConnectionThread* thread);
public:
    DatabaseConnectJob(Database& database);
    virtual void processResults();
};
//-----------------------------------------------------------------------------
DatabaseConnectJob::DatabaseConnectJob(Database& database)
    : DatabaseConnectionThreadJob(database), connectedM(false)
{
    wxASSERT(wxIsMainThread());

    DatabaseCredentials dbc(database.getCredentials());
    charsetM = wx2std(dbc.getCharset());
    connectionStringM = wx2std(getDatabase().getConnectionString());
    passwordM = wx2std(dbc.getRawPassword());
    roleNameM = wx2std(dbc.getRole());
    userNameM = wx2std(dbc.getUsername());
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
}
//-----------------------------------------------------------------------------
void DatabaseConnectJob::processResults()
{
    wxASSERT(wxIsMainThread());

    if (connectedM)
        getDatabase().setConnectionState(Database::csConnected);
    else
    {
        getDatabase().setConnectionState(Database::csDisconnected);
        reportError(_("An error occurred while connecting to the database!"));
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
    DatabaseDisconnectJob(Database& database);
    virtual void processResults();
};
//-----------------------------------------------------------------------------
DatabaseDisconnectJob::DatabaseDisconnectJob(Database& database)
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

    if (disconnectedM)
        getDatabase().setConnectionState(Database::csDisconnected);
    else
        reportError(_("An error occurred while disconnecting from the database!"));
}
//-----------------------------------------------------------------------------
// FetchIdentifiersJob class
class FetchIdentifiersJob: public DatabaseConnectionThreadJob
{
private:
    Item::Handle itemHandleM;
    std::string statementM;
    std::list<std::string> identifiersM;
protected:
    virtual void executeJob(DatabaseConnectionThread* thread);
public:
    FetchIdentifiersJob(Database& database, Item::Handle itemHandle,
        const std::string& statement);
    virtual void processResults();
};
//-----------------------------------------------------------------------------
FetchIdentifiersJob::FetchIdentifiersJob(Database& database,
        Item::Handle itemHandle, const std::string& statement)
    : DatabaseConnectionThreadJob(database), itemHandleM(itemHandle),
        statementM(statement)
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
        st->Execute();
        while (st->Fetch())
        {
            std::string name;
            // do as little as possible here - trailing spaces are not removed
            if (!st->Get(1, name))
                identifiersM.push_back(name);
        }
    }
}
//-----------------------------------------------------------------------------
void FetchIdentifiersJob::processResults()
{
    Item* item = Item::getFromHandle(itemHandleM);
    if (item)
    {
        // build a list of Identifier objects from the strings
        // the Identifier constructor will strip trailing spaces
        std::list<Identifier> identifiers;
        for (std::list<std::string>::iterator it = identifiersM.begin();
            it != identifiersM.end(); ++it)
        {
            Identifier id(std2wx(*it));
            identifiers.push_back(id);
        }
        MetadataItemCollection* collection =
            dynamic_cast<MetadataItemCollection*>(item);
        wxASSERT(collection);
        if (collection)
            collection->setChildrenIdentifiers(identifiers);
    }
}
//-----------------------------------------------------------------------------
// DatabaseConnection class
DatabaseConnection::DatabaseConnection(Database& database)
    : WorkerThreadEngine<SharedDBCThreadJob>(), databaseM(database)
{
}
//-----------------------------------------------------------------------------
WorkerThread<SharedDBCThreadJob>* DatabaseConnection::createWorkerThread()
{
    return new DatabaseConnectionThread(*this);
}
//-----------------------------------------------------------------------------
void DatabaseConnection::connect()
{
    queueJob(SharedDBCThreadJob(new DatabaseConnectJob(databaseM)));
}
//-----------------------------------------------------------------------------
void DatabaseConnection::disconnect()
{
    queueJob(SharedDBCThreadJob(new DatabaseDisconnectJob(databaseM)));
}
//-----------------------------------------------------------------------------
void DatabaseConnection::loadCollection(Item::Handle itemHandle,
    const std::string& sql)
{
    queueJob(SharedDBCThreadJob(
        new FetchIdentifiersJob(databaseM, itemHandle, sql)));
}
//-----------------------------------------------------------------------------
