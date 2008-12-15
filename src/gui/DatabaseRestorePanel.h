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

//-----------------------------------------------------------------------------
#ifndef FR_DATABASERESTOREPANEL_H
#define FR_DATABASERESTOREPANEL_H

#include "commands/ItemCommands.h"
#include "gui/BaseViewPanel.h"
#include "hierarchy/SharedItems.h"

class FileTextControl;
class LogTextControl;

class ServiceConnection;
//-----------------------------------------------------------------------------
class DatabaseRestorePanel: public BaseViewPanel
{
private:
    SharedDatabase databaseM;
    boost::shared_ptr<ServiceConnection> serviceConnectionM;

    wxStaticText* labelFileNameM;
    FileTextControl* textFileNameM;
    wxButton* buttonChooseFileNameM;
    wxCheckBox* checkReplaceDatabaseM;
    wxCheckBox* checkDontRestoreShadowsM;
    wxCheckBox* checkCommitPerTableM;
    wxCheckBox* checkDeactivateIndicesM;
    wxCheckBox* checkIgnoreValidityM;
    wxCheckBox* checkUseAllSpaceM;
    wxStaticText* labelPageSizeM;
    wxChoice* choicePageSizeM;
    wxCheckBox* checkCompleteLogM;
    wxButton* buttonStartM;
    wxButton* buttonCancelM;
    LogTextControl* textLogM;

    bool restoreIsActiveM;

    void createControls();
    void layoutControls();
    void updateControls();
public:
    DatabaseRestorePanel(wxWindow* parent, SharedDatabase database);

    static DatabaseRestorePanel* createViewPanel(const wxString& id,
        SharedDatabase database, ItemCommandsGUIAccessor* accessor);
    static wxString getIdFromDatabase(const Database* database);
private:
    // event handling
    enum { ID_FileName = 2000, ID_FileNameButton, 
        ID_CompleteLog, ID_StartRestore, ID_CancelRestore };

    void OnCancelButtonClick(wxCommandEvent& event);
    void OnCompleteLogChange(wxCommandEvent& event);
    void OnFileNameButtonClick(wxCommandEvent& event);
    void OnStartButtonClick(wxCommandEvent& event);

    void OnIdle(wxIdleEvent& event);

    DECLARE_EVENT_TABLE()
};
//-----------------------------------------------------------------------------
#endif // FR_DATABASERESTOREPANEL_H
