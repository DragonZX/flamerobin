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

#ifndef FR_OBSERVER_H
#define FR_OBSERVER_H
//-----------------------------------------------------------------------------
#include <list>

class Subject;
//-----------------------------------------------------------------------------
class Observer
{
    // do not allow any other object to alter the list of Subjects
    // this is important, because only Subject::attachObserver() and
    // Subject::detachObserver() correctly maintain the synchronicity of
    // Observer::subjectsM and Subject::observersM
    friend class Subject;
private:
    // pointers to all observed objects
    std::list<Subject*> subjectsM;
    typedef std::list<Subject*>::iterator SubjectIterator;

    void addSubject(Subject* subject);
    void removeSubject(Subject* subject);
protected:
    // make these protected, as instances of this class are bogus...
    Observer();
    virtual ~Observer();

    virtual void subjectAdded(Subject* subject);
    // BE CAREFUL: if function gets called when subject is destroyed
    //             its derived-class destructor has already been called !
    virtual void subjectRemoved(Subject* subject);
public:
    virtual void update() = 0;
};
//-----------------------------------------------------------------------------
#endif // FR_OBSERVER_H
