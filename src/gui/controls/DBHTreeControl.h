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

#ifndef FR_DBHTREECONTROL_H
#define FR_DBHTREECONTROL_H
//-----------------------------------------------------------------------------
#include <wx/wx.h>
#include <wx/treectrl.h>

#include "core/Observer.h"
#include "hierarchy/SharedItems.h"
//-----------------------------------------------------------------------------
class DBHTreeControl : public wxTreeCtrl
{
public:
    DBHTreeControl(wxWindow* parent, wxWindowID id);

    void createRootNode(SharedItem rootItem);
    SharedItem getItemFromId(wxTreeItemId id);
private:
    wxTreeItemId hiddenRootNodeM;
private:
    void OnBeginDrag(wxTreeEvent& event);
    void OnContextMenu(wxContextMenuEvent& event);
    void OnTreeItemActivated(wxTreeEvent& event);
    void OnTreeItemExpanding(wxTreeEvent& event);
};
//-----------------------------------------------------------------------------
#endif // FR_DBHTREECONTROL_H
