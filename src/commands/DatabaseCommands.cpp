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
//-----------------------------------------------------------------------------
// DatabaseCommands class
class DatabaseCommands : public ItemCommands
{
private:
    Database* databaseM;

    void OnConnectDatabase(wxCommandEvent& event);
    void OnDisconnectDatabase(wxCommandEvent& event);
    void DatabaseCanConnect(wxUpdateUIEvent& event);
    void DatabaseIsConnected(wxUpdateUIEvent& event);

    DECLARE_EVENT_TABLE()
public:
    DatabaseCommands(PSharedItem item);

    virtual void addCommandsTo(wxMenu* menu, bool isContextMenu);
};
//-----------------------------------------------------------------------------
DatabaseCommands::DatabaseCommands(PSharedItem item)
    : ItemCommands(item), databaseM(0)
{
    databaseM = dynamic_cast<Database*>(item.get());
    wxASSERT(databaseM);
}
//-----------------------------------------------------------------------------
void DatabaseCommands::addCommandsTo(wxMenu* menu, bool isContextMenu)
{
    wxCHECK_RET(menu,
        wxT("DatabaseCommands::addCommandsTo() called without menu"));
    wxCHECK_RET(databaseM,
        wxT("DatabaseCommands::addCommandsTo() called without database"));
    // do not show any popup menu for database nodes that are being connected
    // or disconnected right now
    bool connected = databaseM->isConnected();
    bool canConnect = databaseM->canConnect();
    if (isContextMenu && !connected && !canConnect)
        return;

    bool addSep = false;
    if (!isContextMenu || canConnect)
    {
        menu->Append(CmdDatabase_Connect, _("&Connect"));
        menu->Append(CmdDatabase_ConnectAs, _("Connect &as..."));
        addSep = true;
    }
    if (!isContextMenu || connected)
    {
        menu->Append(CmdDatabase_Disconnect, _("&Disconnect"));
        menu->Append(CmdDatabase_Reconnect, _("Reconnec&t"));
        addSep = true;
    }

    if (addSep)
        menu->AppendSeparator();
    menu->Append(CmdDatabase_ExecuteStatement, _("&Execute SQL statements"));
    if (isContextMenu)
    {
        menu->AppendSeparator();
        menu->Append(CmdView_OpenInNewFrame, _("&Open in new frame"));
    }
}
//-----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(DatabaseCommands, ItemCommands)
    EVT_MENU(CmdObject_DefaultAction, DatabaseCommands::OnConnectDatabase)
    EVT_MENU(CmdDatabase_Connect, DatabaseCommands::OnConnectDatabase)
    EVT_UPDATE_UI(CmdDatabase_Connect, DatabaseCommands::DatabaseCanConnect)
    EVT_MENU(CmdDatabase_ConnectAs, DatabaseCommands::OnConnectDatabase)
    EVT_UPDATE_UI(CmdDatabase_ConnectAs, DatabaseCommands::DatabaseCanConnect)
    EVT_MENU(CmdDatabase_Disconnect, DatabaseCommands::OnDisconnectDatabase)
    EVT_UPDATE_UI(CmdDatabase_Disconnect, DatabaseCommands::DatabaseIsConnected)
    EVT_UPDATE_UI(CmdView_OpenInNewFrame, ItemCommands::CommandIsEnabled)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
void DatabaseCommands::OnConnectDatabase(wxCommandEvent& event)
{
    if (databaseM && databaseM->canConnect())
    {
        if (event.GetId() == CmdDatabase_ConnectAs)
        {
// TODO: prepare temporary connection credentials for "Connect as..."
        }
        databaseM->connect();
    }
}
//-----------------------------------------------------------------------------
void DatabaseCommands::OnDisconnectDatabase(wxCommandEvent& /*event*/)
{
    if (databaseM && databaseM->isConnected())
        databaseM->disconnect();
}
//-----------------------------------------------------------------------------
void DatabaseCommands::DatabaseCanConnect(wxUpdateUIEvent& event)
{
    event.Enable(databaseM && databaseM->canConnect());
}
//-----------------------------------------------------------------------------
void DatabaseCommands::DatabaseIsConnected(wxUpdateUIEvent& event)
{
    event.Enable(databaseM && databaseM->isConnected());
}
//-----------------------------------------------------------------------------
static const ItemCommandsFactoryImpl<Database, DatabaseCommands> factory;
//-----------------------------------------------------------------------------
