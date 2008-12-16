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

#ifndef FR_WORKERTHREAD_H
#define FR_WORKERTHREAD_H
//-----------------------------------------------------------------------------
#include <wx/thread.h>

#include <list>
#include <memory>

#include <boost/shared_ptr.hpp>
//-----------------------------------------------------------------------------
BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_EVENT_TYPE(EVT_JobCompleted, -1)
END_DECLARE_EVENT_TYPES()
//-----------------------------------------------------------------------------
template<class ThreadJob>
class ThreadJobManager
{
public:
    virtual bool getNextJob(ThreadJob& job) = 0;
    virtual void putCompletedJob(ThreadJob job) = 0;
};
//-----------------------------------------------------------------------------
template<class ThreadJob>
class WorkerThread: public wxThread
{
private:
    ThreadJobManager<ThreadJob>& jobManagerM;
protected:
    virtual wxThread::ExitCode Entry()
    {
        for (;;)
        {
            ThreadJob job;
            if (!jobManagerM.getNextJob(job))
                break;
            if (job.get())
            {
                try
                {
                    job->execute(this);
                }
                catch (...)
                {
                    // we swallow all exceptions silently, jobs must
                    // catch and handle them internally
                }
                jobManagerM.putCompletedJob(job);
            }
        }
        return 0;
    };
public:
    WorkerThread(ThreadJobManager<ThreadJob>& manager)
       : wxThread(wxTHREAD_JOINABLE), jobManagerM(manager)
    {
        if (Create() != wxTHREAD_NO_ERROR)
            wxLogError(wxT("WorkerThread::Create() failed"));
        if (Run() != wxTHREAD_NO_ERROR)
            wxLogError(wxT("WorkerThread::Run() failed"));
    };
};
//-----------------------------------------------------------------------------
template<class ThreadJob>
class WorkerThreadEngine: public wxEvtHandler,
    protected ThreadJobManager<ThreadJob>
{
private:
    wxMutex mutexM;
    wxCondition conditionM;
    bool shutdownRequestM;

    std::auto_ptr<WorkerThread<ThreadJob> > threadM;

    typedef std::list<ThreadJob> ThreadJobList;
    ThreadJobList pendingJobsM;
    ThreadJob executedJobM;
    ThreadJobList processedJobsM;

    bool blockNotificationsM;
    void OnJobCompleted(wxCommandEvent&)
    {
        for (;;)
        {
            ThreadJob job;
            {
                wxMutexLocker lock(mutexM);
                if (processedJobsM.empty())
                {
                    blockNotificationsM = false;
                    return;
                }
                job = processedJobsM.front();
                processedJobsM.pop_front();
            }
            try
            {
                job->processResults();
            }
            catch(...)
            {
                wxMutexLocker lock(mutexM);
                blockNotificationsM = false;
                throw;
            }
        }
    };

    // called by thread to get next job to execute
    // will block if pendingJobsM is empty, until new job is queued or
    // thread shutdown is requested
    bool getNextJob(ThreadJob& job)
    {
        job.reset();
        for (;;)
        {
            // test for shutdown request, and get the next queued job
            wxMutexLocker lock(mutexM);
            if (shutdownRequestM)
                return false;
            if (!pendingJobsM.empty())
            {
                executedJobM = job = pendingJobsM.front();
                pendingJobsM.pop_front();
                return true;
            }
            // no queued job, wait for the condition to be signaled
            conditionM.Wait();
        }
    };
    // called by thread to signal completion of executed job
    void putCompletedJob(ThreadJob job)
    {
        wxMutexLocker lock(mutexM);

        wxASSERT(executedJobM == job);
        executedJobM.reset();
        processedJobsM.push_back(job);
        // don't send notification event when previous has not been processed,
        // or when thread shutdown is in progress
        if (!blockNotificationsM && !shutdownRequestM)
        {
            blockNotificationsM = true;
        
            wxCommandEvent ev;
            ev.SetEventType(EVT_JobCompleted);
            AddPendingEvent(ev);
        }
    };
    // called by engine to wake thread up and cause it to exit
    void shutdownThread()
    {
        wxMutexLocker lock(mutexM);
        shutdownRequestM = true;
        if (executedJobM.get() && executedJobM->canCancelExecution())
            executedJobM->cancelExecution();
        conditionM.Signal();
    };

    // used by QueueJob() to create thread or wake it up if sleeping
    inline void wakeupThread()
    {
        if (0 == threadM.get())
            threadM.reset(createWorkerThread());
        conditionM.Signal();
    };

protected:
    virtual WorkerThread<ThreadJob>* createWorkerThread() = 0
    {
        // needs to be overridden, but implement it all the same...
        return 0;
    };

    bool queueJob(ThreadJob job)
    {
        wxMutexLocker lock(mutexM);
        if (shutdownRequestM || !job.get())
            return false;
        pendingJobsM.push_back(job);
        wakeupThread();
        return true;
    };

    bool queueJobs(ThreadJobList jobs)
    {
        wxMutexLocker lock(mutexM);
        if (shutdownRequestM)
            return false;
        unsigned added = 0;
        for (typename ThreadJobList::iterator it = jobs.begin();
            it != jobs.end(); ++it)
        {
            ThreadJob job = *it;
            if (job.get())
            {
                pendingJobsM.push_back(job);
                ++added;
            }
        }
        if (!added)
            return false;
        wakeupThread();
        return true;
    };

public:
    WorkerThreadEngine()
        : wxEvtHandler(), mutexM(), conditionM(mutexM),
            shutdownRequestM(false), threadM(0), blockNotificationsM(false)
    {
        Connect(EVT_JobCompleted,
            wxCommandEventHandler(WorkerThreadEngine::OnJobCompleted));
    };

    virtual ~WorkerThreadEngine()
    {
        Disconnect(EVT_JobCompleted,
            wxCommandEventHandler(WorkerThreadEngine::OnJobCompleted));
        if (threadM.get())
        {
            // make sure that even a sleeping thread is properly shut down
            shutdownThread();
            threadM->Wait();
            threadM.reset();
        }
    };
};
//-----------------------------------------------------------------------------
#endif // FR_WORKERTHREAD_H
