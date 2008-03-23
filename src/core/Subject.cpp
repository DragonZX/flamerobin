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

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWindows headers
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <algorithm>

#include "core/Observer.h"
#include "core/Subject.h"
//-----------------------------------------------------------------------------
Subject::Subject()
    : lockCountM(0), needsNotifyObserversM(false)
{
}
//-----------------------------------------------------------------------------
Subject::~Subject()
{
    detachAllObservers();
}
//-----------------------------------------------------------------------------
void Subject::attachObserver(Observer* observer)
{
    wxCHECK_RET(observer, wxT("observer is 0 in Subject::attachObserver()"));
    ObserverIterator it = std::find(observersM.begin(), observersM.end(),
        observer);
    wxCHECK_RET(it == observersM.end(),
        wxT("Observer already registered for this Subject"));

    observer->addSubject(this);
    observersM.push_back(observer);
    observer->update();
}
//-----------------------------------------------------------------------------
void Subject::detachObserver(Observer* observer)
{
    wxCHECK_RET(observer, wxT("observer is 0 in Subject::detachObserver()"));
    ObserverIterator it = std::find(observersM.begin(), observersM.end(),
        observer);
    wxCHECK_RET(it != observersM.end(),
        wxT("Observer not registered for this Subject"));
    observer->removeSubject(this);
    observersM.erase(it);
}
//-----------------------------------------------------------------------------
void Subject::detachAllObservers()
{
    for (ObserverIterator it = observersM.begin(); it != observersM.end(); ++it)
        (*it)->removeSubject(this);
    observersM.clear();
}
//-----------------------------------------------------------------------------
void Subject::notifyObservers()
{
    if (isLocked())
    {
        needsNotifyObserversM = true;
        return;
    }
    // make sure there are no reentrancy problems
    ++lockCountM;
    for (ObserverIterator it = observersM.begin(); it != observersM.end(); ++it)
        (*it)->update();
    --lockCountM;
    needsNotifyObserversM = false;
}
//-----------------------------------------------------------------------------
void Subject::lockSubject()
{
    ++lockCountM;
    if (lockCountM == 1)
        doFirstLock();
}
//-----------------------------------------------------------------------------
void Subject::unlockSubject()
{
    if (isLocked())
    {
        if (lockCountM)
            --lockCountM;
        if (!isLocked())
        {
            doLastUnlock();
            if (needsNotifyObserversM)
                notifyObservers();
        }
    }
}
//-----------------------------------------------------------------------------
unsigned Subject::getLockCount()
{
    return lockCountM;
}
//-----------------------------------------------------------------------------
void Subject::setLockCount(unsigned lockCount)
{
    lockCountM = lockCount;
}
//-----------------------------------------------------------------------------
void Subject::doFirstLock()
{
}
//-----------------------------------------------------------------------------
void Subject::doLastUnlock()
{
}
//-----------------------------------------------------------------------------
bool Subject::isLocked()
{
    return lockCountM > 0;
}
//-----------------------------------------------------------------------------
SubjectLocker::SubjectLocker(Subject* subject)
{
    subjectM = 0;
    setSubject(subject);
}
//-----------------------------------------------------------------------------
SubjectLocker::~SubjectLocker()
{
    setSubject(0);
}
//-----------------------------------------------------------------------------
Subject* SubjectLocker::getSubject()
{
    return subjectM;
}
//-----------------------------------------------------------------------------
void SubjectLocker::setSubject(Subject* subject)
{
    if (subject != subjectM)
    {
        if (subjectM)
            subjectM->unlockSubject();
        subjectM = subject;
        if (subjectM)
            subjectM->lockSubject();
    }
}
//-----------------------------------------------------------------------------
