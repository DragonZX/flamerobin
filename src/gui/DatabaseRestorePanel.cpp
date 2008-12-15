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
#include <wx/filename.h>

#include <memory>

#include "gui/DatabaseRestorePanel.h"
#include "gui/controls/DndTextControls.h"
#include "gui/controls/LogTextControl.h"
#include "gui/StyleGuide.h"
#include "hierarchy/Database.h"
//-----------------------------------------------------------------------------
/*static*/
DatabaseRestorePanel* DatabaseRestorePanel::createViewPanel(const wxString& id,
    SharedDatabase database, ItemCommandsGUIAccessor* accessor)
{
    wxCHECK_MSG(database, 0,
        wxT("DatabaseRestorePanel::createViewPanel() called without database"));
    wxCHECK_MSG(accessor, 0,
        wxT("DatabaseRestorePanel::createViewPanel() called without GUI accessor"));

// TODO: create panel in frame instead of notebook depending on user preference
    wxAuiNotebook* notebook = accessor->getNotebookForViews();
    wxCHECK_MSG(notebook, 0,
        wxT("GUI accessor in DatabaseRestorePanel::createViewPanel() has no notebook"));

    DatabaseRestorePanel* panel = new DatabaseRestorePanel(notebook, database);
    panel->setId(id);

    wxString caption(wxString::Format(_("Restore Database \"%s\""),
        database->getName().c_str()));
    notebook->AddPage(panel, caption, true);
    notebook->Update();
    return panel;
}
//-----------------------------------------------------------------------------
/*static*/
wxString DatabaseRestorePanel::getIdFromDatabase(const Database* database)
{
    wxCHECK_MSG(database != 0, wxT(""),
        wxT("DatabaseRestorePanel::getIdFromDatabase() called without database"));
    return wxT("DatabaseRestore/") + database->getItemPath();
}
//-----------------------------------------------------------------------------
DatabaseRestorePanel::DatabaseRestorePanel(wxWindow* parent,
        SharedDatabase database)
    : BaseViewPanel(parent), databaseM(database)
{
    restoreIsActiveM = false;

    createControls();
    layoutControls();
    updateControls();
}
//-----------------------------------------------------------------------------
void DatabaseRestorePanel::createControls()
{
    labelFileNameM = new wxStaticText(this, wxID_ANY, _("Backup &file:"));
    textFileNameM = new FileTextControl(this, ID_FileName, wxEmptyString);
    buttonChooseFileNameM = new wxButton(this, ID_FileNameButton,
        _("&Choose..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);

    checkReplaceDatabaseM = new wxCheckBox(this, wxID_ANY,
        _("Replace e&xisting database"));
    checkDontRestoreShadowsM = new wxCheckBox(this, wxID_ANY,
        _("Don't restore &shadow files"));
    checkCommitPerTableM = new wxCheckBox(this, wxID_ANY,
        _("Commit per &table"));
    checkDeactivateIndicesM = new wxCheckBox(this, wxID_ANY,
        _("Deacti&vate indices"));
    checkIgnoreValidityM = new wxCheckBox(this, wxID_ANY,
        _("&Ignore validity constraints"));
    checkUseAllSpaceM = new wxCheckBox(this, wxID_ANY,
        _("&Use all space"));

    labelPageSizeM = new wxStaticText(this, wxID_ANY, _("&Page size:"));
    choicePageSizeM = new wxChoice(this, wxID_ANY, wxDefaultPosition,
        wxDefaultSize, Database::getAvailablePageSizes());
    checkCompleteLogM = new wxCheckBox(this, ID_CompleteLog,
        _("Sho&w complete log"));

    buttonStartM = new wxButton(this, ID_StartRestore, _("Start &restore"));
    buttonCancelM = new wxButton(this, ID_CancelRestore, _("Cancel r&estore"));

    textLogM = new LogTextControl(this, wxID_ANY);
}
//-----------------------------------------------------------------------------
void DatabaseRestorePanel::layoutControls()
{
/* TODO
    std::list<wxWindow*> controls;
    controls.push_back(label_filename);
    controls.push_back(label_pagesize);
    adjustControlsMinWidth(controls);
    controls.clear();
*/

    int wh = textFileNameM->GetMinHeight();
    buttonChooseFileNameM->SetSize(wh, wh);

    // file name selection
    std::auto_ptr<wxBoxSizer> sizerFilename(new wxBoxSizer(wxHORIZONTAL));
    sizerFilename->Add(labelFileNameM, 0, wxALIGN_CENTER_VERTICAL);
    sizerFilename->Add(styleguide().getControlLabelMargin(), 0);
    sizerFilename->Add(textFileNameM, 1, wxALIGN_CENTER_VERTICAL);
    sizerFilename->Add(styleguide().getBrowseButtonMargin(), 0);
    sizerFilename->Add(buttonChooseFileNameM, 0, wxALIGN_CENTER_VERTICAL);
    // checkboxes for restore options
    std::auto_ptr<wxGridSizer> sizerChecks(new wxGridSizer(2, 2,
        styleguide().getCheckboxSpacing(),
        styleguide().getUnrelatedControlMargin(wxHORIZONTAL)));
    sizerChecks->Add(checkReplaceDatabaseM, 0, wxEXPAND);
    sizerChecks->Add(checkDeactivateIndicesM, 0, wxEXPAND);
    sizerChecks->Add(checkDontRestoreShadowsM, 0, wxEXPAND);
    sizerChecks->Add(checkIgnoreValidityM, 0, wxEXPAND);
    sizerChecks->Add(checkCommitPerTableM, 0, wxEXPAND);
    sizerChecks->Add(checkUseAllSpaceM, 0, wxEXPAND);
    // page size selection
    std::auto_ptr<wxBoxSizer> sizerPageSize(new wxBoxSizer(wxHORIZONTAL));
    sizerPageSize->Add(labelPageSizeM, 0, wxALIGN_CENTER_VERTICAL);
    sizerPageSize->Add(styleguide().getControlLabelMargin(), 0);
    sizerPageSize->Add(choicePageSizeM, 0, wxALIGN_CENTER_VERTICAL);
    // log display and action buttons
    std::auto_ptr<wxBoxSizer> sizerButtons(new wxBoxSizer(wxHORIZONTAL));
    sizerButtons->Add(checkCompleteLogM, 0, wxALIGN_CENTER_VERTICAL);
    sizerButtons->AddStretchSpacer(1);
    sizerButtons->Add(buttonStartM);
    sizerButtons->AddSpacer(
        styleguide().getBetweenButtonsMargin(wxHORIZONTAL));
    sizerButtons->Add(buttonCancelM);

    // stack the sizers vertically with proper spacing
    std::auto_ptr<wxBoxSizer> sizerVert1(new wxBoxSizer(wxVERTICAL));
    sizerVert1->AddSpacer(styleguide().getFrameMargin(wxTOP));
    sizerVert1->Add(sizerFilename.release(), 0, wxEXPAND);
    sizerVert1->AddSpacer(styleguide().getRelatedControlMargin(wxVERTICAL));
    sizerVert1->Add(sizerChecks.release());
    sizerVert1->AddSpacer(styleguide().getRelatedControlMargin(wxVERTICAL));
    sizerVert1->Add(sizerPageSize.release());
    sizerVert1->AddSpacer(styleguide().getUnrelatedControlMargin(wxVERTICAL));
    sizerVert1->Add(sizerButtons.release(), 0, wxEXPAND);
    // add horizontal spacing to vertical sizer
    std::auto_ptr<wxBoxSizer> sizerHorz1(new wxBoxSizer(wxHORIZONTAL));
    sizerHorz1->AddSpacer(styleguide().getFrameMargin(wxLEFT));
    sizerHorz1->Add(sizerVert1.release(), 1, wxEXPAND);
    sizerHorz1->AddSpacer(styleguide().getFrameMargin(wxRIGHT));

    std::auto_ptr<wxBoxSizer> sizerMain(new wxBoxSizer(wxVERTICAL));
    sizerMain->Add(sizerHorz1.release(), 0, wxEXPAND);
    sizerMain->AddSpacer(styleguide().getRelatedControlMargin(wxVERTICAL));
    // show at least 3 lines of text in the log control
    textLogM->SetMinSize(wxSize(wxDefaultCoord,
        3 * textFileNameM->GetSize().GetHeight()));
    sizerMain->Add(textLogM, 1, wxEXPAND);

    SetSizerAndFit(sizerMain.release());
}
//-----------------------------------------------------------------------------
void DatabaseRestorePanel::updateControls()
{
// TODO
}
//-----------------------------------------------------------------------------
// event handling
BEGIN_EVENT_TABLE(DatabaseRestorePanel, BaseViewPanel)
    EVT_BUTTON(DatabaseRestorePanel::ID_CancelRestore, DatabaseRestorePanel::OnCancelButtonClick)
    EVT_BUTTON(DatabaseRestorePanel::ID_FileNameButton, DatabaseRestorePanel::OnFileNameButtonClick)
    EVT_BUTTON(DatabaseRestorePanel::ID_StartRestore, DatabaseRestorePanel::OnStartButtonClick)
    EVT_CHECKBOX(DatabaseRestorePanel::ID_CompleteLog, DatabaseRestorePanel::OnCompleteLogChange)

    EVT_IDLE(DatabaseRestorePanel::OnIdle)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
void DatabaseRestorePanel::OnCancelButtonClick(wxCommandEvent& /*event*/)
{
    restoreIsActiveM = false;
// TODO
}
//-----------------------------------------------------------------------------
void DatabaseRestorePanel::OnCompleteLogChange(wxCommandEvent& /*event*/)
{
// TODO
}
//-----------------------------------------------------------------------------
void DatabaseRestorePanel::OnFileNameButtonClick(wxCommandEvent& /*event*/)
{
    wxFileName oldName(textFileNameM->GetValue());
    wxString filename = ::wxFileSelector(_("Select Backup File"),
        oldName.GetPath(), oldName.GetFullName(), wxT("*.fbk"),
        _("Backup file (*.fbk, *.gbk)|*.fbk;*.gbk|All files (*.*)|*.*"),
        wxFD_OPEN, wxGetTopLevelParent(this));
    if (!filename.empty())
        textFileNameM->SetValue(filename);
}
//-----------------------------------------------------------------------------
void DatabaseRestorePanel::OnStartButtonClick(wxCommandEvent& /*event*/)
{
    buttonStartM->Enable(false);
    restoreIsActiveM = true;
// TODO
}
//-----------------------------------------------------------------------------
void DatabaseRestorePanel::OnIdle(wxIdleEvent& event)
{
    bool settingsOK = textFileNameM->GetValue() != wxEmptyString
        && choicePageSizeM->GetSelection() != wxNOT_FOUND;
    buttonStartM->Enable(settingsOK && !restoreIsActiveM
        && databaseM != 0 && databaseM->canRestoreFromBackup());
    buttonCancelM->Enable(restoreIsActiveM);
    // don't disable default handling...
    event.Skip();
}
//-----------------------------------------------------------------------------
