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
#include "engine/ServiceConnection.h"
//-----------------------------------------------------------------------------
ServiceConnectionThread::ServiceConnectionThread(
        ThreadJobManager<SharedSCThreadJob>& manager)
    : WorkerThread<SharedSCThreadJob>(manager) 
{
};
//-----------------------------------------------------------------------------
IBPP::Service& ServiceConnectionThread::getService()
{
    // all access to IBPP objects has to happen in this thread
    wxASSERT(!wxIsMainThread());
    return serviceM;
}; 
//-----------------------------------------------------------------------------
void ServiceConnectionThread::setService(IBPP::Service& service)
{
    // all access to IBPP objects has to happen in this thread
    wxASSERT(!wxIsMainThread());
    serviceM = service;
};
//-----------------------------------------------------------------------------
// ServiceConnectionThreadJob base class
ServiceConnectionThreadJob::ServiceConnectionThreadJob(Database& database)
    : databaseM(database), exceptionWhatM(), systemErrorM(false)
{
}
//-----------------------------------------------------------------------------
Database& ServiceConnectionThreadJob::getDatabase()
{
    // all access to database has to happen in main thread
    wxASSERT(wxIsMainThread());
    return databaseM;
}
//-----------------------------------------------------------------------------
bool ServiceConnectionThreadJob::hasError()
{
    return systemErrorM || !exceptionWhatM.empty();
}
//-----------------------------------------------------------------------------
bool ServiceConnectionThreadJob::canCancelExecution()
{
    return false;
}
//-----------------------------------------------------------------------------
void ServiceConnectionThreadJob::cancelExecution()
{
}
//-----------------------------------------------------------------------------
void ServiceConnectionThreadJob::execute(
    WorkerThread<SharedSCThreadJob>* thread)
{
    try
    {
        ServiceConnectionThread* sct =
            dynamic_cast<ServiceConnectionThread*>(thread);
        wxASSERT(sct);
        if (sct)
            executeJob(sct);
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
void ServiceConnectionThreadJob::reportError(const wxString& primaryMsg)
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
// ServiceConnection class
ServiceConnection::ServiceConnection(Database& database)
    : WorkerThreadEngine<SharedSCThreadJob>(), databaseM(database)
{
}
//-----------------------------------------------------------------------------
WorkerThread<SharedSCThreadJob>* ServiceConnection::createWorkerThread()
{
    return new ServiceConnectionThread(*this);
}
//-----------------------------------------------------------------------------
