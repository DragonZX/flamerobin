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

#include <wx/aui/aui.h>

#include "gui/DatabaseBackupPanel.h"
#include "hierarchy/Database.h"
//-----------------------------------------------------------------------------
DatabaseBackupPanel::DatabaseBackupPanel(wxWindow* parent,
        SharedDatabase database)
    : BaseViewPanel(parent), databaseM(database)
{
    new wxStaticText(this, wxID_ANY, wxT("ToDo: all controls need to go here..."));
}
//-----------------------------------------------------------------------------
/*static*/
DatabaseBackupPanel* DatabaseBackupPanel::createViewPanel(const wxString& id,
    SharedDatabase database, ItemCommandsGUIAccessor* accessor)
{
    wxCHECK_MSG(database, 0,
        wxT("DatabaseBackupPanel::createViewPanel() called without database"));
    wxCHECK_MSG(accessor, 0,
        wxT("DatabaseBackupPanel::createViewPanel() called without GUI accessor"));

// TODO: create panel in frame instead of notebook depending on user preference
    wxAuiNotebook* notebook = accessor->getNotebookForViews();
    wxCHECK_MSG(notebook, 0,
        wxT("GUI accessor in DatabaseBackupPanel::createViewPanel() has no notebook"));

    DatabaseBackupPanel* panel = new DatabaseBackupPanel(notebook, database);
    panel->setId(id);

    wxString caption(wxString::Format(_("Backup Database \"%s\""),
        database->getName().c_str()));
    notebook->AddPage(panel, caption, true);
    notebook->Update();
    return panel;
}
//-----------------------------------------------------------------------------
/*static*/
wxString DatabaseBackupPanel::getIdFromDatabase(const Database* database)
{
    wxCHECK_MSG(database != 0, wxT(""),
        wxT("DatabaseBackupPanel::getIdFromDatabase() called without database"));
    return wxT("DatabaseBackup/") + database->getItemPath();
}
//-----------------------------------------------------------------------------
