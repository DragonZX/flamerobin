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

#include "core/ArtProvider.h"

#include "gui/MainFrame.h"
#include "gui/controls/DBHTreeControl.h"

#include "hierarchy/Database.h"
#include "hierarchy/TreeFolder.h"
#include "hierarchy/TreeRoot.h"
//-----------------------------------------------------------------------------
// MainFrame class
MainFrame::MainFrame(wxWindow* parent, int id, PSharedItem treeRootItem)
    : BaseFrame(parent, id, _("FlameRobin Database Admin")),
        selectedItemCommandsM(0)
{
    createMenu();
    createControls();
    layoutControls();
    setProperties();
    connectEventHandlers();

    dbhTreeM->createRootNode(treeRootItem);
}
//-----------------------------------------------------------------------------
MainFrame::~MainFrame()
{
    setSelectedItem(PSharedItem());
}
//-----------------------------------------------------------------------------
void MainFrame::setSelectedItem(PSharedItem selectedItem)
{
    if (selectedItemM != selectedItem)
    {
        // delete event handler for previously selected item
        if (selectedItemCommandsM)
        {
            wxEvtHandler* handler = PopEventHandler();
            wxASSERT(handler == selectedItemCommandsM);
            delete selectedItemCommandsM;
            selectedItemCommandsM = 0;
        }
        selectedItemM = selectedItem;
        // create and push event handler for newly selected item
        if (selectedItem)
        {

/* TODO: create real ItemCommands instance from selectedItem
*/
            selectedItemCommandsM = new ItemCommands;

            if (selectedItemCommandsM)
                PushEventHandler(selectedItemCommandsM);
        }
        updateStatusBar();
    }
}
//-----------------------------------------------------------------------------
void MainFrame::connectEventHandlers()
{
    // global menu item handlers
    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(MainFrame::OnMenuExitApp));

    // tree view handlers
    Connect(dbhTreeM->GetId(), wxEVT_COMMAND_TREE_SEL_CHANGED,
        wxTreeEventHandler(MainFrame::OnTreeSelectionChanged));
}
//-----------------------------------------------------------------------------
void MainFrame::createControls()
{
    parentPanelM = new wxPanel(this);
    dbhTreeM = new DBHTreeControl(parentPanelM, wxID_ANY);

    CreateStatusBar();
    updateStatusBar();
}
//-----------------------------------------------------------------------------
void MainFrame::createMenu()
{
}
//-----------------------------------------------------------------------------
void MainFrame::layoutControls()
{
    wxSizer* sizerAll = new wxBoxSizer(wxVERTICAL);
    sizerAll->Add(dbhTreeM, 1, wxEXPAND);

    parentPanelM->SetSizer(sizerAll);
    sizerAll->Fit(this);
    sizerAll->SetSizeHints(this);
}
//-----------------------------------------------------------------------------
void MainFrame::setProperties()
{
    SetIcon(wxArtProvider::GetIcon(ART_FlameRobin, wxART_FRAME_ICON));
}
//-----------------------------------------------------------------------------
void MainFrame::updateStatusBar()
{
    wxStatusBar* sbar = GetStatusBar();
    if (sbar)
    {
        Database* database = (selectedItemM) ? selectedItemM->getDatabase() : 0;
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
    return wxT("MainFrame");
}
//-----------------------------------------------------------------------------
bool MainFrame::openUnregisteredDatabase(const wxString& /*dbpath*/)
{
    return false;
}
//-----------------------------------------------------------------------------
// event handler methods
void MainFrame::OnMenuExitApp(wxCommandEvent& /*event*/)
{
    Close();
}
//-----------------------------------------------------------------------------
void MainFrame::OnTreeSelectionChanged(wxTreeEvent& event)
{
    setSelectedItem(dbhTreeM->getItemFromId(event.GetItem()));
}
//-----------------------------------------------------------------------------
