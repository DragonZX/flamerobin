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

#ifndef FR_DATABASECONNECTION_H
#define FR_DATABASECONNECTION_H
//-----------------------------------------------------------------------------
#include <wx/string.h>

#include <string>
#include <vector>

#include <ibpp.h>

#include "engine/WorkerThread.h"
#include "hierarchy/Database.h"
//-----------------------------------------------------------------------------
class DatabaseConnectionThreadJob;
typedef boost::shared_ptr<DatabaseConnectionThreadJob> SharedDBCThreadJob;
//-----------------------------------------------------------------------------
class DatabaseConnectionThread: public WorkerThread<SharedDBCThreadJob>
{
private:
    IBPP::Database databaseM;
public:
    DatabaseConnectionThread(ThreadJobManager<SharedDBCThreadJob>& manager);
    IBPP::Database& getDatabase(); 
    void setDatabase(IBPP::Database& database);
};
//-----------------------------------------------------------------------------
class DatabaseConnectionThreadJob
{
private:
    SharedDatabase databaseM;
protected:
    std::string exceptionWhatM;
    bool systemErrorM;
    bool hasError();

    SharedDatabase getDatabase();
    // This is called in the context of the background thread.
    // Override this method and implement "workload" there.
    // Make sure that all exceptions are handled and information is stored
    // for the processResults() method.
    // All interaction with the GUI has to be delayed to processResults().
    virtual void executeJob(DatabaseConnectionThread* thread) = 0;
    void reportError(const wxString& primaryMsg);
public:
    DatabaseConnectionThreadJob(SharedDatabase database);

    // Override these methods to implement interuptible jobs.
    virtual bool canCancelExecution();
    virtual void cancelExecution();
    // This is called in the context of the background thread.
    // Exception handling and type-casting of thread parameter to class 
    // DatabaseConnectionThread* is taken care of.
    // Override executeJob() to implement actual background processing.
    virtual void execute(WorkerThread<SharedDBCThreadJob>* thread);
    // This is called in the context of the main (GUI) thread.
    // Override this method and handle results of execute() call.
    virtual void processResults() = 0;
};
//-----------------------------------------------------------------------------
class DatabaseConnection: public WorkerThreadEngine<SharedDBCThreadJob>
{
private:
    boost::weak_ptr<Database> databaseM;
//    Database& databaseM;
    DatabaseConnection(Database& database);
    friend class Database;
protected:
    virtual WorkerThread<SharedDBCThreadJob>* createWorkerThread();
public:
    void connect();
    void disconnect();

    void executeJob(SharedDBCThreadJob job);

    void loadCollection(Item::Handle itemHandle, const std::string& sql);
    void loadCollection(Item::Handle itemHandle, const std::string& sql,
        const std::vector<std::string>& params);
};
//-----------------------------------------------------------------------------
#endif // FR_DATABASECONNECTION_H
