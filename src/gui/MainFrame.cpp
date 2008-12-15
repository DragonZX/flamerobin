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

#include "config/Config.h"

#include "core/ArtProvider.h"
#include "core/CommandIds.h"

#include "gui/AboutBox.h"
#include "gui/HtmlViewPanel.h"
#include "gui/MainFrame.h"
#include "gui/controls/DBHTreeControl.h"

#include "hierarchy/Database.h"
#include "hierarchy/TreeFolder.h"
#include "hierarchy/TreeRoot.h"
//-----------------------------------------------------------------------------
// MainFrame class
MainFrame::MainFrame(wxWindow* parent, int id, SharedItem treeRootItem)
    : BaseFrame(parent, id, _("FlameRobin Database Admin [Multithreaded]")),
        auiManagerM(), auiToolbarM(0), treeRegisteredDatabasesM(0),
        treeUnregisteredDatabasesM(0), auiNotebookM(0),
        selectedItemCommandsM()
{
    isMainFrameM = TreeRoot::get() == treeRootItem;

    auiManagerM.SetManagedWindow(this);
    SetIcon(wxArtProvider::GetIcon(ART_FlameRobin, wxART_FRAME_ICON));

    createMenu();
    createControls();
    layoutControls();

    connectEventHandlers();

    treeRegisteredDatabasesM->createRootNode(treeRootItem);
    if (!isMainFrameM)
    {
        wxString rootName(treeRootItem->getName());
        if (!rootName.empty())
            SetTitle(GetTitle() + wxT(" - ") + rootName);
    }
    updateStatusBar();

//    treeUnregisteredDatabasesM->createRootNode(SharedItem());
}
//-----------------------------------------------------------------------------
MainFrame::~MainFrame()
{
    auiManagerM.UnInit();

    setSelectedItem(SharedItem());
}
//-----------------------------------------------------------------------------
void MainFrame::connectEventHandlers()
{
    // tree view handlers
    Connect(treeRegisteredDatabasesM->GetId(), wxEVT_COMMAND_TREE_SEL_CHANGED,
        wxTreeEventHandler(MainFrame::OnTreeSelectionChanged));
}
//-----------------------------------------------------------------------------
void MainFrame::createControls()
{
    createToolbars();

    treeRegisteredDatabasesM = new DBHTreeControl(this, wxID_ANY);
    treeUnregisteredDatabasesM = new DBHTreeControl(this, wxID_ANY);

    int nbStyle = wxAUI_NB_DEFAULT_STYLE | wxAUI_NB_TAB_EXTERNAL_MOVE
        | wxAUI_NB_WINDOWLIST_BUTTON | wxNO_BORDER;
    auiNotebookM = new wxAuiNotebook(this, wxID_ANY, wxDefaultPosition,
        wxDefaultSize, nbStyle);

    CreateStatusBar();
    updateStatusBar();
}
//-----------------------------------------------------------------------------
void MainFrame::createMenu()
{
    std::auto_ptr<wxMenuBar> bar(new wxMenuBar);
    // File menu
    std::auto_ptr<wxMenu> menu(new wxMenu);
    menu->Append(wxID_NEW, _("&New\tCtrl+N"));
    menu->Append(wxID_OPEN, _("&Open...\tCtrl+O"));
    menu->Append(wxID_SAVE, _("&Save\tCtrl+S"));
    menu->Append(wxID_SAVEAS, _("&Save As...\tCtrl+S"));
    menu->AppendSeparator();
    menu->Append(wxID_EXIT, _("E&xit"));
    bar->Append(menu.release(), _("&File"));
    // Edit menu
    menu.reset(new wxMenu);
    menu->Append(wxID_UNDO, _("&Undo\tCtrl+Z"));
    menu->Append(wxID_REDO, _("&Redo\tCtrl+Y"));
    menu->AppendSeparator();
    menu->Append(wxID_CUT, _("Cu&t\tCtrl+X"));
    menu->Append(wxID_COPY, _("&Copy\tCtrl+C"));
    menu->Append(wxID_PASTE, _("&Paste\tCtrl+V"));
    menu->Append(wxID_DELETE, _("&Delete\tDel"));
    menu->AppendSeparator();
    menu->Append(wxID_SELECTALL, _("Select &All\tCtrl+A"));
    bar->Append(menu.release(), _("&Edit"));
    // View menu
    menu.reset(new wxMenu);
/* FIXME: this does not work, for whatever reason... find out later!
    std::auto_ptr<wxMenu> subMenu(new wxMenu);
    subMenu->AppendCheckItem(CmdView_ToolBarStandard, _("&Standard"));
    menu->Append(CmdView_ToolBarSubMenu, _("&Tool Bars"), subMenu.release());
*/
    menu->AppendCheckItem(CmdView_ToolBarStandard, _("&Tool Bar"));

    menu->AppendSeparator();
    menu->Append(CmdView_RegisteredDatabases, _("&Registered Databases"));
    menu->Append(CmdView_UnregisteredDatabases, _("&Unregistered Databases"));
    menu->AppendSeparator();
    menu->AppendCheckItem(CmdView_StatusBar, _("&Status Bar"));
    bar->Append(menu.release(), _("&View"));
    // Database menu
    menu.reset(new wxMenu);
    // use a dummy database and matching commands object to populate
    // the database menu
    SharedDatabase db(new Database);
    SharedItemCommands dbCmds = ItemCommands::createItemCommands(db);
    dbCmds->addCommandsTo(menu.get(), false);
    dbCmds.reset();
    db.reset();
    bar->Append(menu.release(), _("&Database"));
    // Object menu
    menu.reset(new wxMenu);

    bar->Append(menu.release(), _("&Object"));
    // Statement menu
    menu.reset(new wxMenu);

    bar->Append(menu.release(), _("&Statement"));
    // Window menu
    menu.reset(new wxMenu);

    bar->Append(menu.release(), _("&Window"));
    // Help menu
    menu.reset(new wxMenu);
    menu->Append(CmdHelp_Manual, _("&User Manual"));
    menu->Append(CmdHelp_RelNotes, _("&Release Notes"));
    menu->Append(CmdHelp_License, _("&License"));
    menu->AppendSeparator();
    menu->Append(CmdURL_HomePage, _("FlameRobin &Home Page"));
    menu->Append(CmdURL_ProjectPage, _("SourceForge &Project Page"));
    menu->Append(CmdURL_FeatureRequest, _("SourceForge &Feature Requests"));
    menu->Append(CmdURL_BugReport, _("SourceForge &Bug Reports"));
    menu->AppendSeparator();
    menu->Append(wxID_ABOUT, _("&About FlameRobin"));
    bar->Append(menu.release(), _("&Help"));
    // menu bar
    SetMenuBar(bar.release());
}
//-----------------------------------------------------------------------------
void MainFrame::createToolbars()
{
    auiToolbarM = new wxAuiToolBar(this);
    wxSize btnSize(16, 15);
    auiToolbarM->SetToolBitmapSize(btnSize);

    auiToolbarM->AddTool(wxID_CUT, _("Open File"),
        wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_OTHER, btnSize));
    auiToolbarM->AddTool(wxID_CUT, _("Save File"),
        wxArtProvider::GetBitmap(wxART_FILE_SAVE, wxART_OTHER, btnSize));
    auiToolbarM->AddTool(wxID_CUT, _("Save File As"),
        wxArtProvider::GetBitmap(wxART_FILE_SAVE_AS, wxART_OTHER, btnSize));
    auiToolbarM->AddSeparator();
    auiToolbarM->AddTool(wxID_CUT, _("Cut"),
        wxArtProvider::GetBitmap(wxART_CUT, wxART_OTHER, btnSize));
    auiToolbarM->AddTool(wxID_CUT, _("Copy"),
        wxArtProvider::GetBitmap(wxART_COPY, wxART_OTHER, btnSize));
    auiToolbarM->AddTool(wxID_CUT, _("Paste"),
        wxArtProvider::GetBitmap(wxART_PASTE, wxART_OTHER, btnSize));
    auiToolbarM->AddSeparator();
    auiToolbarM->AddTool(wxID_CUT, _("Undo"),
        wxArtProvider::GetBitmap(wxART_UNDO, wxART_OTHER, btnSize));
    auiToolbarM->AddTool(wxID_CUT, _("Redo"),
        wxArtProvider::GetBitmap(wxART_REDO, wxART_OTHER, btnSize));
//    auiToolbarM->Add
    auiToolbarM->Realize();
}
//-----------------------------------------------------------------------------
void MainFrame::layoutControls()
{
    // setup default AUI layout
    auiManagerM.AddPane(auiToolbarM, wxAuiPaneInfo().
        Name(wxT("ToolbarMain")).Caption(wxT("Standard Toolbar")).
        ToolbarPane().Top().
        LeftDockable(false).RightDockable(false));
    auiManagerM.AddPane(treeRegisteredDatabasesM, wxAuiPaneInfo().
        Name(wxT("TreeRegisteredDB")).Caption(wxT("Registered Databases")).
        BestSize(300, 500).FloatingSize(300, 500).
        Left().CloseButton(true).MaximizeButton(true));
    auiManagerM.AddPane(treeUnregisteredDatabasesM, wxAuiPaneInfo().
        Name(wxT("TreeUnregisteredDB")).Caption(wxT("Unregistered Databases")).
        BestSize(300, 500).FloatingSize(300, 500).
        Left().CloseButton(true).MaximizeButton(true).Hide());
    auiManagerM.AddPane(auiNotebookM, wxAuiPaneInfo().
        Name(wxT("ContentNotebook")).CenterPane().PaneBorder(false));
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
void MainFrame::doReadConfigSettings(const wxString& prefix)
{
    // load saved AUI layout
    wxString key = prefix + Config::pathSeparator + wxT("AUIPerspective");
    wxString layout;
    if (config().getValue(key, layout) && !layout.empty())
        auiManagerM.LoadPerspective(layout);
}
//-----------------------------------------------------------------------------
void MainFrame::doWriteConfigSettings(const wxString& prefix) const
{
    // save current AUI layout
    config().setValue(prefix + Config::pathSeparator + wxT("AUIPerspective"),
        const_cast<MainFrame*>(this)->auiManagerM.SavePerspective());
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
    SharedItem selectedItem;
    if (selectedItemCommandsM)
        selectedItem = selectedItemCommandsM->getItem();
    return (selectedItem) ? selectedItem->getDatabase() : 0;
}
//-----------------------------------------------------------------------------
void MainFrame::setSelectedItem(SharedItem selectedItem)
{
    SharedItem lastSelectedItem;
    if (selectedItemCommandsM)
        lastSelectedItem = selectedItemCommandsM->getItem();
    if (lastSelectedItem != selectedItem)
    {
        // delete event handler for previously selected item
        if (selectedItemCommandsM)
        {
            wxASSERT(this == selectedItemCommandsM->getGUIAccessor());
            selectedItemCommandsM->setGUIAccessor(0);

            wxEvtHandler* handler = PopEventHandler();
            wxASSERT(handler == selectedItemCommandsM.get());
            selectedItemCommandsM = SharedItemCommands();
        }
        // create and push event handler for newly selected item
        if (selectedItem)
        {
            selectedItemCommandsM =
                ItemCommands::createItemCommands(selectedItem);
            if (selectedItemCommandsM != 0)
            {
                selectedItemCommandsM->setGUIAccessor(this);
                PushEventHandler(selectedItemCommandsM.get());
            }
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
void MainFrame::openHtmlFileView(const wxString& caption,
    const wxString& filename)
{
    wxString id(HtmlViewPanel::getIdFromFileName(filename));
    if (BaseViewPanel::activateViewPanel(id))
        return;

    wxFileName fullname(config().getDocsPath(), filename);
    if (fullname.FileExists())
    {
#if 0
        HtmlViewPanel* panel = HtmlViewPanel::createViewInFrame(id, this,
            caption);
#else
        HtmlViewPanel* panel = HtmlViewPanel::createViewInNotebook(id,
            auiNotebookM, caption);
#endif
        // the html view shows "please wait while the page is being loaded..."
        panel->loadFromFile(fullname);
    }
}
//-----------------------------------------------------------------------------
void MainFrame::openUrlExternal(const wxString& url)
{
    if (!wxLaunchDefaultBrowser(url))
        wxLogError(_T("Failed to open URL \"%s\""), url.c_str());
}
//-----------------------------------------------------------------------------
// ItemCommandsGUIAccessor
wxAuiNotebook* MainFrame::getNotebookForViews()
{
    return auiNotebookM;
}
//-----------------------------------------------------------------------------
wxFrame* MainFrame::getParentForViews()
{
    return this;
}
//-----------------------------------------------------------------------------
// static event table
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    // File menu
    EVT_MENU(wxID_EXIT, MainFrame::OnFileExit)
    EVT_UPDATE_UI(wxID_EXIT, MainFrame::OnUpdateUIEnable)

    // View menu
    EVT_MENU_RANGE(CmdView_RegisteredDatabases, CmdView_UnregisteredDatabases, MainFrame::OnViewPane)
    EVT_UPDATE_UI_RANGE(CmdView_RegisteredDatabases, CmdView_UnregisteredDatabases, MainFrame::OnUpdateUIEnable)
    EVT_MENU(CmdView_StatusBar, MainFrame::OnViewStatusBar)
    EVT_UPDATE_UI(CmdView_StatusBar, MainFrame::OnUpdateViewStatusBar)
    EVT_MENU_RANGE(CmdView_ToolBarFirst, CmdView_ToolBarLast, MainFrame::OnViewToolBar)
    EVT_UPDATE_UI_RANGE(CmdView_ToolBarFirst, CmdView_ToolBarLast, MainFrame::OnUpdateViewToolBar)

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
// event handler methods: File menu
void MainFrame::OnFileExit(wxCommandEvent& /*event*/)
{
    Close();
}
//-----------------------------------------------------------------------------
// View menu
void MainFrame::OnViewPane(wxCommandEvent& event)
{
    wxWindow* pane = 0;
    if (event.GetId() == CmdView_RegisteredDatabases)
        pane = treeRegisteredDatabasesM;
    else if (event.GetId() == CmdView_UnregisteredDatabases)
        pane = treeUnregisteredDatabasesM;

    wxAuiPaneInfo& info = auiManagerM.GetPane(pane);
    if (info.IsOk())
    {
        info.Show();
        auiManagerM.Update();
        pane->SetFocus();
    }
}
//-----------------------------------------------------------------------------
void MainFrame::OnViewStatusBar(wxCommandEvent& /*event*/)
{
    if (wxStatusBar* sbar = GetStatusBar())
    {
        sbar->Show(!sbar->IsShown());
        SendSizeEvent();
    }
}
//-----------------------------------------------------------------------------
void MainFrame::OnUpdateViewStatusBar(wxUpdateUIEvent& event)
{
    wxStatusBar* sbar = GetStatusBar();
    event.Enable(sbar != 0);
    event.Check(sbar && sbar->IsShown());
}
//-----------------------------------------------------------------------------
void MainFrame::OnViewToolBar(wxCommandEvent& event)
{
    wxWindow* tbar = 0;
    if (event.GetId() == CmdView_ToolBarStandard)
        tbar = auiToolbarM;

    wxAuiPaneInfo& info = auiManagerM.GetPane(tbar);
    if (info.IsOk())
    {
        info.Show(!info.IsShown());
        auiManagerM.Update();
    }
}
//-----------------------------------------------------------------------------
void MainFrame::OnUpdateViewToolBar(wxUpdateUIEvent& event)
{
    wxWindow* tbar = 0;
    if (event.GetId() == CmdView_ToolBarStandard)
        tbar = auiToolbarM;

    wxAuiPaneInfo& info = auiManagerM.GetPane(tbar);
    event.Enable(info.IsOk());
    event.Check(info.IsOk() && info.IsShown());
}
//-----------------------------------------------------------------------------
// Help menu
void MainFrame::OnHelpAbout(wxCommandEvent& /*event*/)
{
    showAboutBox(this);
}
//-----------------------------------------------------------------------------
void MainFrame::OnHelpLicense(wxCommandEvent& /*event*/)
{
    openHtmlFileView(_("License"), wxT("fr_license.html"));
}
//-----------------------------------------------------------------------------
void MainFrame::OnHelpManual(wxCommandEvent& /*event*/)
{
    openHtmlFileView(_("User Manual"), wxT("fr_manual.html"));
}
//-----------------------------------------------------------------------------
void MainFrame::OnHelpReleaseNotes(wxCommandEvent& /*event*/)
{
    openHtmlFileView(_("Release Notes"), wxT("fr_whatsnew.html"));
}
//-----------------------------------------------------------------------------
void MainFrame::OnHelpUrlBugReport(wxCommandEvent& /*event*/)
{
    openUrlExternal(
        wxT("http://sourceforge.net/tracker/?atid=699234&group_id=124340"));
}
//-----------------------------------------------------------------------------
void MainFrame::OnHelpUrlFeatureRequest(wxCommandEvent& /*event*/)
{
    openUrlExternal(
        wxT("http://sourceforge.net/tracker/?atid=699237&group_id=124340"));
}
//-----------------------------------------------------------------------------
void MainFrame::OnHelpUrlHomePage(wxCommandEvent& /*event*/)
{
    openUrlExternal(wxT("http://www.flamerobin.org"));
}
//-----------------------------------------------------------------------------
void MainFrame::OnHelpUrlProjectPage(wxCommandEvent& /*event*/)
{
    openUrlExternal(wxT("http://sourceforge.net/projects/flamerobin"));
}
//-----------------------------------------------------------------------------
void MainFrame::OnMenuOpenInNewFrame(wxCommandEvent& /*event*/)
{
    SharedItem selectedItem;
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
    setSelectedItem(treeRegisteredDatabasesM->getItemFromId(event.GetItem()));
}
//-----------------------------------------------------------------------------
