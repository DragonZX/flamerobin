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

#ifndef FR_TREEROOT_H
#define FR_TREEROOT_H
//-----------------------------------------------------------------------------
#include <wx/wx.h>
#include <wx/xml/xml.h>

#include "hierarchy/SharedItems.h"
#include "hierarchy/TreeFolder.h"
//-----------------------------------------------------------------------------
class TreeRoot : public TreeFolder
{
public:
    TreeRoot();

    static SharedTreeRoot get();

    void createDefaultHierarchy();
    bool loadHierarchy();
    bool saveHierarchy();

    void disconnectAllDatabases();

    // increments the Id generator and returns the value
    const unsigned getNextId();
private:
    wxString fileNameM;
    wxString getFileName();
    bool needsSaveM;

    unsigned nextIdM;

    bool parseDatabase(SharedItem parent, wxXmlNode* xmln,
        const wxString& serverHostnamePort, bool importOldSettings);
    bool parseFolder(SharedItem parent, wxXmlNode* xmln);
    bool parseServer(SharedItem parent, wxXmlNode* xmln);
};
//-----------------------------------------------------------------------------
#endif // FR_TREEROOT_H
