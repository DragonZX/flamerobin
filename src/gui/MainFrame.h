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
#include <wx/aui/aui.h>

#include "gui/BaseFrame.h"
#include "gui/controls/DBHTreeControl.h"

#include "commands/ItemCommands.h"
//-----------------------------------------------------------------------------
class MainFrame : public BaseFrame, ItemCommandsGUIAccessor
{
public:
    // the treeRootItem parameter could be used to open secondary instances
    // of MainFrame for working with only a part of the hierarchy (like a
    // single database)
    MainFrame(wxWindow* parent, int id, PSharedItem treeRootItem);
    ~MainFrame();

    bool openUnregisteredDatabase(const wxString& dbpath);

public:
    // ItemCommandsGUIAccessor
    virtual wxAuiNotebook* getNotebookForViews();
    virtual wxFrame* getParentForViews();
protected:
    virtual void doReadConfigSettings(const wxString& prefix);
    virtual void doWriteConfigSettings(const wxString& prefix) const;
    virtual const wxString getName() const;
    virtual const wxRect getDefaultRect() const;
private:
    wxAuiManager auiManagerM;
    wxAuiToolBar* auiToolbarM;
    DBHTreeControl* treeRegisteredDatabasesM;
    DBHTreeControl* treeUnregisteredDatabasesM;
    wxAuiNotebook* auiNotebookM;

    PSharedItemCommands selectedItemCommandsM;
    void setSelectedItem(PSharedItem selectedItem);
    Database* getSelectedDatabase();
    bool isMainFrameM;

    void connectEventHandlers();
    void createControls();
    void createMenu();
    void createToolbars();
    void layoutControls();
    void updateStatusBar();

    void openHtmlFileView(const wxString& caption, const wxString& filename);
    void openUrlExternal(const wxString& url);

private:
    // event handler methods
    void OnFileExit(wxCommandEvent& event);

    // View menu
    void OnViewPane(wxCommandEvent& event);
    void OnViewStatusBar(wxCommandEvent& event);
    void OnUpdateViewStatusBar(wxUpdateUIEvent& event);
    void OnViewToolBar(wxCommandEvent& event);
    void OnUpdateViewToolBar(wxUpdateUIEvent& event);

    // Help menu
    void OnHelpAbout(wxCommandEvent& event);
    void OnHelpLicense(wxCommandEvent& event);
    void OnHelpManual(wxCommandEvent& event);
    void OnHelpReleaseNotes(wxCommandEvent& event);
    void OnHelpUrlBugReport(wxCommandEvent& event);
    void OnHelpUrlFeatureRequest(wxCommandEvent& event);
    void OnHelpUrlHomePage(wxCommandEvent& event);
    void OnHelpUrlProjectPage(wxCommandEvent& event);

    void OnMenuOpenInNewFrame(wxCommandEvent& event);
    void OnTreeSelectionChanged(wxTreeEvent& event);

    void OnUpdateUIEnable(wxUpdateUIEvent& event);

    DECLARE_EVENT_TABLE()
};
//-----------------------------------------------------------------------------
#endif // FR_MAINFRAME_H
