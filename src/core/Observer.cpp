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
//-----------------------------------------------------------------------------
#include <algorithm>

#include "core/Observer.h"
#include "core/Subject.h"
//-----------------------------------------------------------------------------
Observer::Observer()
{
}
//-----------------------------------------------------------------------------
Observer::~Observer()
{
    while (!subjectsM.empty())
    {
        // remove the last added subject first, by detaching from it
        Subject* subject = subjectsM.back();
        subject->detachObserver(this);
        // it must have been removed by a call to removeSubject()
        wxASSERT(subjectsM.end() == std::find(subjectsM.begin(),
            subjectsM.end(), subject));
    }
}
//-----------------------------------------------------------------------------
void Observer::addSubject(Subject* subject)
{
    wxCHECK_RET(subject, wxT("subject is 0 in Observer::addSubject()"));
    SubjectIterator it = std::find(subjectsM.begin(), subjectsM.end(),
        subject);
    wxCHECK_RET(it == subjectsM.end(),
        wxT("Subject already registered with this Observer"));
    subjectsM.push_back(subject);
    subjectAdded(subject);
}
//-----------------------------------------------------------------------------
void Observer::removeSubject(Subject* subject)
{
    wxCHECK_RET(subject, wxT("subject is 0 in Observer::removeSubject()"));
    SubjectIterator it = std::find(subjectsM.begin(), subjectsM.end(),
        subject);
    wxCHECK_RET(it != subjectsM.end(),
        wxT("Subject not registered with this Observer"));
    subjectsM.erase(it);
    subjectRemoved(subject);
}
//-----------------------------------------------------------------------------
void Observer::subjectAdded(Subject* /*subject*/)
{
}
//-----------------------------------------------------------------------------
void Observer::subjectRemoved(Subject* /*subject*/)
{
}
//-----------------------------------------------------------------------------
