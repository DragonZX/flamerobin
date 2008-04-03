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

#ifndef FR_MAINFRAME_H
#define FR_MAINFRAME_H
//-----------------------------------------------------------------------------
#include <wx/wx.h>

#include "gui/BaseFrame.h"
#include "gui/controls/DBHTreeControl.h"
#include "hierarchy/SharedItems.h"

class ItemCommands;
//-----------------------------------------------------------------------------
class MainFrame : public BaseFrame
{
public:
    // the treeRootItem parameter could be used to open secondary instances
    // of MainFrame for working with only a part of the hierarchy (like a
    // single database)
    MainFrame(wxWindow* parent, int id, PSharedItem treeRootItem);
    ~MainFrame();

    bool openUnregisteredDatabase(const wxString& dbpath);

protected:
    virtual const wxString getName() const;
    virtual const wxRect getDefaultRect() const;
private:
    wxPanel* parentPanelM;
    DBHTreeControl* dbhTreeM;

    ItemCommands* selectedItemCommandsM;
    void setSelectedItem(PSharedItem selectedItem);
    Database* getSelectedDatabase();
    bool isMainFrameM;

    void connectEventHandlers();
    void createControls();
    void createMenu();
    void layoutControls();
    void setProperties();
    void updateStatusBar();

private:
    // event handler methods
    void OnMenuOpenInNewFrame(wxCommandEvent& event);
    void OnTreeSelectionChanged(wxTreeEvent& event);

    void OnUpdateUIEnable(wxUpdateUIEvent& event);

    DECLARE_EVENT_TABLE()
};
//-----------------------------------------------------------------------------
#endif // FR_MAINFRAME_H
