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

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "commands/ItemCommands.h"
#include "core/CommandIds.h"
#include "hierarchy/Database.h"
#include "hierarchy/TreeFolder.h"
#include "hierarchy/TreeRoot.h"
//-----------------------------------------------------------------------------
// TreeFolderCommands class
class TreeFolderCommands : public ItemCommands
{
private:
    TreeFolder* folderM;

    void OnCreateDatabase(wxCommandEvent& event);
    void OnCreateDatabaseRestoreBackup(wxCommandEvent& event);
    void OnRegisterDatabase(wxCommandEvent& event);
    void OnUpdateUIEnable(wxUpdateUIEvent& event);
    void OnConnectAllDatabases(wxCommandEvent& event);
    void OnUpdateConnectAllDatabases(wxUpdateUIEvent& event);
    void OnDisconnectAllDatabases(wxCommandEvent& event);
    void OnUpdateDisconnectAllDatabases(wxUpdateUIEvent& event);

    DECLARE_EVENT_TABLE()
public:
    TreeFolderCommands(PSharedItem item);

    virtual void addCommandsTo(wxMenu* menu, bool isContextMenu);
};
//-----------------------------------------------------------------------------
TreeFolderCommands::TreeFolderCommands(PSharedItem item)
    : ItemCommands(item), folderM(0)
{
    folderM = dynamic_cast<TreeFolder*>(item.get());
    wxASSERT(folderM);
}
//-----------------------------------------------------------------------------
void TreeFolderCommands::addCommandsTo(wxMenu* menu, bool isContextMenu)
{
    wxCHECK_RET(menu,
        wxT("TreeFolderCommands::addCommandsTo() called without menu"));
    wxCHECK_RET(folderM,
        wxT("TreeFolderCommands::addCommandsTo() called without folder"));
    wxASSERT(isContextMenu);

    menu->Append(CmdDatabase_Create, _("Create &new database..."));
    menu->Append(CmdDatabase_RestoreIntoNew,
        _("Restore bac&kup into new database..."));
    menu->Append(CmdDatabase_Register, _("&Register existing database..."));
    menu->AppendSeparator();
    menu->Append(CmdFolder_ConnectAllDatabases, _("&Connect all databases"));
    menu->Append(CmdFolder_DisconnectAllDatabases,
        _("&Disconnect all databases"));
/*
    menu->AppendSeparator();
    menu->Append(CmdView_OpenInNewFrame, _("&Open in new frame"));
*/
}
//-----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(TreeFolderCommands, ItemCommands)
    EVT_MENU(CmdDatabase_Create, TreeFolderCommands::OnCreateDatabase)
    EVT_UPDATE_UI(CmdDatabase_Create, ItemCommands::CommandIsEnabled)
    EVT_MENU(CmdDatabase_RestoreIntoNew, TreeFolderCommands::OnCreateDatabaseRestoreBackup)
    EVT_UPDATE_UI(CmdDatabase_RestoreIntoNew, ItemCommands::CommandIsEnabled)
    EVT_MENU(CmdDatabase_Register, TreeFolderCommands::OnRegisterDatabase)
    EVT_UPDATE_UI(CmdDatabase_Register, ItemCommands::CommandIsEnabled)
    EVT_MENU(CmdFolder_ConnectAllDatabases, TreeFolderCommands::OnConnectAllDatabases)
    EVT_UPDATE_UI(CmdFolder_ConnectAllDatabases, TreeFolderCommands::OnUpdateConnectAllDatabases)
    EVT_MENU(CmdFolder_DisconnectAllDatabases, TreeFolderCommands::OnDisconnectAllDatabases)
    EVT_UPDATE_UI(CmdFolder_DisconnectAllDatabases, TreeFolderCommands::OnUpdateDisconnectAllDatabases)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
void TreeFolderCommands::OnCreateDatabase(wxCommandEvent& event)
{
// TODO: implement TreeFolderCommands::OnCreateDatabase()
}
//-----------------------------------------------------------------------------
void TreeFolderCommands::OnCreateDatabaseRestoreBackup(wxCommandEvent& event)
{
// TODO: implement TreeFolderCommands::OnCreateDatabaseRestoreBackup()
}
//-----------------------------------------------------------------------------
void TreeFolderCommands::OnRegisterDatabase(wxCommandEvent& event)
{
// TODO: implement TreeFolderCommands::OnRegisterDatabase()
}
//-----------------------------------------------------------------------------
void TreeFolderCommands::OnConnectAllDatabases(wxCommandEvent& /*event*/)
{
    for (unsigned i = 0; i < folderM->getChildrenCount(); ++i)
    {
        PSharedItem item = folderM->getChild(i);
        Database* database = dynamic_cast<Database*>(item.get());
        if (database && database->isDisconnected())
            database->connect();
    }
}
//-----------------------------------------------------------------------------
void TreeFolderCommands::OnUpdateConnectAllDatabases(wxUpdateUIEvent& event)
{
    for (unsigned i = 0; i < folderM->getChildrenCount(); ++i)
    {
        PSharedItem item = folderM->getChild(i);
        Database* database = dynamic_cast<Database*>(item.get());
        if (database && database->isDisconnected())
        {
            event.Enable(true);
            return;
        }
    }
    event.Enable(false);
}
//-----------------------------------------------------------------------------
void TreeFolderCommands::OnDisconnectAllDatabases(wxCommandEvent& /*event*/)
{
    for (unsigned i = 0; i < folderM->getChildrenCount(); ++i)
    {
        PSharedItem item = folderM->getChild(i);
        Database* database = dynamic_cast<Database*>(item.get());
        if (database && database->isConnected())
            database->disconnect();
    }
}
//-----------------------------------------------------------------------------
void TreeFolderCommands::OnUpdateDisconnectAllDatabases(wxUpdateUIEvent& event)
{
    for (unsigned i = 0; i < folderM->getChildrenCount(); ++i)
    {
        PSharedItem item = folderM->getChild(i);
        Database* database = dynamic_cast<Database*>(item.get());
        if (database && database->isConnected())
        {
            event.Enable(true);
            return;
        }
    }
    event.Enable(false);
}
//-----------------------------------------------------------------------------
static const ItemCommandsFactoryImpl<TreeFolder, TreeFolderCommands> factory1;
static const ItemCommandsFactoryImpl<TreeRoot, TreeFolderCommands> factory2;
//-----------------------------------------------------------------------------
