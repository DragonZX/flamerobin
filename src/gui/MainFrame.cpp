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

#include <wx/html/htmlwin.h>

#include <memory>

#include "commands/ItemCommands.h"

#include "config/Config.h"

#include "core/ArtProvider.h"
#include "core/CommandIds.h"

#include "gui/AboutBox.h"
#include "gui/MainFrame.h"
#include "gui/controls/DBHTreeControl.h"

#include "hierarchy/Database.h"
#include "hierarchy/TreeFolder.h"
#include "hierarchy/TreeRoot.h"
//-----------------------------------------------------------------------------
// MainFrame class
MainFrame::MainFrame(wxWindow* parent, int id, PSharedItem treeRootItem)
    : BaseFrame(parent, id, _("FlameRobin Database Admin [Multithreaded]")),
        selectedItemCommandsM(0)
{
    isMainFrameM = TreeRoot::get() == treeRootItem;

    auiManagerM.SetManagedWindow(this);
    SetIcon(wxArtProvider::GetIcon(ART_FlameRobin, wxART_FRAME_ICON));

    createMenu();
    createControls();
    layoutControls();

    connectEventHandlers();

    dbhTreeM->createRootNode(treeRootItem);
    if (!isMainFrameM)
    {
        wxString rootName(treeRootItem->getName());
        if (!rootName.empty())
            SetTitle(GetTitle() + wxT(" - ") + rootName);
    }
}
//-----------------------------------------------------------------------------
MainFrame::~MainFrame()
{
    // save current AUI layout
    wxString key = getStorageName() + Config::pathSeparator
        + wxT("AUIPerspective");
    wxString layout(auiManagerM.SavePerspective());
    config().setValue(key, layout);

    auiManagerM.UnInit();

    setSelectedItem(PSharedItem());
}
//-----------------------------------------------------------------------------
void MainFrame::connectEventHandlers()
{
    // tree view handlers
    Connect(dbhTreeM->GetId(), wxEVT_COMMAND_TREE_SEL_CHANGED,
        wxTreeEventHandler(MainFrame::OnTreeSelectionChanged));
}
//-----------------------------------------------------------------------------
void MainFrame::createControls()
{
    dbhTreeM = new DBHTreeControl(this, wxID_ANY);
    auiNotebookM = new wxAuiNotebook(this, wxID_ANY, wxDefaultPosition,
        wxDefaultSize,
        wxAUI_NB_DEFAULT_STYLE | wxAUI_NB_TAB_EXTERNAL_MOVE | wxNO_BORDER);

    CreateStatusBar();
    updateStatusBar();
}
//-----------------------------------------------------------------------------
void MainFrame::createMenu()
{
    std::auto_ptr<wxMenuBar> bar(new wxMenuBar);
    // File menu
    std::auto_ptr<wxMenu> menu(new wxMenu);
    menu->Append(wxID_EXIT, _("E&xit"));
    bar->Append(menu.release(), _("&File"));
    // Help menu
    menu.reset(new wxMenu);
    menu->Append(CmdHelp_Manual, _("&User manual"));
    menu->Append(CmdHelp_RelNotes, _("&What's new"));
    menu->Append(CmdHelp_License, _("&License"));
    menu->AppendSeparator();
    menu->Append(CmdURL_HomePage, _("FlameRobin &home page"));
    menu->Append(CmdURL_ProjectPage, _("SourceForge &project page"));
    menu->Append(CmdURL_FeatureRequest, _("SourceForge &feature requests"));
    menu->Append(CmdURL_BugReport, _("SourceForge &bug reports"));
    menu->AppendSeparator();
    menu->Append(wxID_ABOUT, _("&About FlameRobin"));
    bar->Append(menu.release(), _("&Help"));
    // menu bar
    SetMenuBar(bar.release());
}
//-----------------------------------------------------------------------------
void MainFrame::layoutControls()
{
    // setup default AUI layout
    auiManagerM.AddPane(dbhTreeM, wxAuiPaneInfo().
        Name(wxT("DBHTree")).Caption(wxT("Registered Databases")).
        BestSize(300, 500).FloatingSize(300, 500).
        Left().CloseButton(false).MaximizeButton(true));
    auiManagerM.AddPane(auiNotebookM, wxAuiPaneInfo().
        Name(wxT("ContentNotebook")).CenterPane().PaneBorder(false));

    // load saved AUI layout
/*
    wxString key = getStorageName() + Config::pathSeparator
        + wxT("AUIPerspective");
    wxString layout;
    if (config().getValue(key, layout) && !layout.empty())
        auiManagerM.LoadPerspective(layout);
*/

    auiManagerM.Update();
}
//-----------------------------------------------------------------------------
void MainFrame::updateStatusBar()
{
    wxStatusBar* sbar = GetStatusBar();
    if (sbar)
    {
        Database* database = getSelectedDatabase();
        if (database)
        {
            DatabaseCredentials dbc(database->getCredentials());
            wxString s = dbc.getUsername() + wxT("@")
                + database->getConnectionString()
                + wxT(" (") + dbc.getCharset() + wxT(")");
            sbar->SetStatusText(s);
        }
        else
            sbar->SetStatusText(_("[No database selected]"));
    }
}
//-----------------------------------------------------------------------------
const wxRect MainFrame::getDefaultRect() const
{
    return wxRect(wxDefaultCoord, wxDefaultCoord, 260, 400);
}
//-----------------------------------------------------------------------------
const wxString MainFrame::getName() const
{
    return wxT("MainFrameAUI");
}
//-----------------------------------------------------------------------------
Database* MainFrame::getSelectedDatabase()
{
    PSharedItem selectedItem;
    if (selectedItemCommandsM)
        selectedItem = selectedItemCommandsM->getItem();
    return (selectedItem) ? selectedItem->getDatabase() : 0;
}
//-----------------------------------------------------------------------------
void MainFrame::setSelectedItem(PSharedItem selectedItem)
{
    PSharedItem lastSelectedItem;
    if (selectedItemCommandsM)
        lastSelectedItem = selectedItemCommandsM->getItem();
    if (lastSelectedItem != selectedItem)
    {
        // delete event handler for previously selected item
        if (selectedItemCommandsM)
        {
            wxEvtHandler* handler = PopEventHandler();
            wxASSERT(handler == selectedItemCommandsM);
            delete selectedItemCommandsM;
            selectedItemCommandsM = 0;
        }
        // create and push event handler for newly selected item
        if (selectedItem)
        {
            selectedItemCommandsM =
                ItemCommands::createItemCommands(selectedItem);
            if (selectedItemCommandsM)
                PushEventHandler(selectedItemCommandsM);
        }
        updateStatusBar();
    }
}
//-----------------------------------------------------------------------------
bool MainFrame::openUnregisteredDatabase(const wxString& /*dbpath*/)
{
    return false;
}
//-----------------------------------------------------------------------------
void MainFrame::openHtmlFileIntern(const wxString& caption,
    const wxString& filename)
{
// TODO: implement MainFrame::openHtmlFileIntern()
}
//-----------------------------------------------------------------------------
void MainFrame::openUrlExtern(const wxString& url)
{
    if (!wxLaunchDefaultBrowser(url))
        wxLogError(_T("Failed to open URL \"%s\""), url.c_str());
}
//-----------------------------------------------------------------------------
// static event table
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    // File menu
    EVT_MENU(wxID_EXIT, MainFrame::OnFileExit)
    EVT_UPDATE_UI(wxID_EXIT, MainFrame::OnUpdateUIEnable)

    // Help menu
    EVT_MENU(CmdHelp_Manual, MainFrame::OnHelpManual)
    EVT_MENU(CmdHelp_RelNotes, MainFrame::OnHelpReleaseNotes)
    EVT_MENU(CmdHelp_License, MainFrame::OnHelpLicense)
    EVT_UPDATE_UI_RANGE(CmdHelp_Manual, CmdHelp_License, MainFrame::OnUpdateUIEnable)
    EVT_MENU(CmdURL_HomePage, MainFrame::OnHelpUrlHomePage)
    EVT_MENU(CmdURL_ProjectPage, MainFrame::OnHelpUrlProjectPage)
    EVT_MENU(CmdURL_FeatureRequest, MainFrame::OnHelpUrlFeatureRequest)
    EVT_MENU(CmdURL_BugReport, MainFrame::OnHelpUrlBugReport)
    EVT_UPDATE_UI_RANGE(CmdURL_HomePage, CmdURL_BugReport, MainFrame::OnUpdateUIEnable)
    EVT_MENU(wxID_ABOUT, MainFrame::OnHelpAbout)
    EVT_UPDATE_UI(wxID_ABOUT, MainFrame::OnUpdateUIEnable)

    EVT_MENU(CmdView_OpenInNewFrame, MainFrame::OnMenuOpenInNewFrame)
    EVT_UPDATE_UI(CmdView_OpenInNewFrame, MainFrame::OnUpdateUIEnable)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
// event handler methods
void MainFrame::OnFileExit(wxCommandEvent& /*event*/)
{
    Close();
}
//-----------------------------------------------------------------------------
void MainFrame::OnHelpAbout(wxCommandEvent& /*event*/)
{
    showAboutBox(this);
}
//-----------------------------------------------------------------------------
void MainFrame::OnHelpLicense(wxCommandEvent& /*event*/)
{
    openHtmlFileIntern(_("License"), wxT("fr_license.html"));
}
//-----------------------------------------------------------------------------
void MainFrame::OnHelpManual(wxCommandEvent& /*event*/)
{
    openHtmlFileIntern(_("Manual"), wxT("fr_manual.html"));
}
//-----------------------------------------------------------------------------
void MainFrame::OnHelpReleaseNotes(wxCommandEvent& /*event*/)
{
    openHtmlFileIntern(_("Release notes"), wxT("fr_whatsnew.html"));
}
//-----------------------------------------------------------------------------
void MainFrame::OnHelpUrlBugReport(wxCommandEvent& /*event*/)
{
    openUrlExtern(
        wxT("http://sourceforge.net/tracker/?atid=699234&group_id=124340"));
}
//-----------------------------------------------------------------------------
void MainFrame::OnHelpUrlFeatureRequest(wxCommandEvent& /*event*/)
{
    openUrlExtern(
        wxT("http://sourceforge.net/tracker/?atid=699237&group_id=124340"));
}
//-----------------------------------------------------------------------------
void MainFrame::OnHelpUrlHomePage(wxCommandEvent& /*event*/)
{
    openUrlExtern(wxT("http://www.flamerobin.org"));
}
//-----------------------------------------------------------------------------
void MainFrame::OnHelpUrlProjectPage(wxCommandEvent& /*event*/)
{
    openUrlExtern(wxT("http://sourceforge.net/projects/flamerobin"));
}
//-----------------------------------------------------------------------------
void MainFrame::OnMenuOpenInNewFrame(wxCommandEvent& /*event*/)
{
    PSharedItem selectedItem;
    if (selectedItemCommandsM)
        selectedItem = selectedItemCommandsM->getItem();
    if (selectedItem)
    {
        MainFrame* mf = new MainFrame(0, wxID_ANY, selectedItem);
        mf->Show();
    }
}
//-----------------------------------------------------------------------------
void MainFrame::OnUpdateUIEnable(wxUpdateUIEvent& event)
{
    event.Enable(true);
}
//-----------------------------------------------------------------------------
void MainFrame::OnTreeSelectionChanged(wxTreeEvent& event)
{
    setSelectedItem(dbhTreeM->getItemFromId(event.GetItem()));
}
//-----------------------------------------------------------------------------
