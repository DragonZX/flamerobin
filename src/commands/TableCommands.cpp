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
#include "hierarchy/Table.h"
//-----------------------------------------------------------------------------
// TableCommands class
class TableCommands : public ItemCommands
{
private:
    Table* tableM;
public:
    TableCommands(SharedItem item);
};
//-----------------------------------------------------------------------------
TableCommands::TableCommands(SharedItem item)
    : ItemCommands(item), tableM(0)
{
    tableM = dynamic_cast<Table*>(item.get());
    wxASSERT(tableM);
}
//-----------------------------------------------------------------------------
// SystemTableCollectionCommands class
class SystemTableCollectionCommands : public ItemCommands
{
private:
    SystemTableCollection* tablesM;

    void OnRefresh(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
public:
    SystemTableCollectionCommands(SharedItem item);

    virtual void addCommandsTo(wxMenu* menu, bool isContextMenu);
};
//-----------------------------------------------------------------------------
SystemTableCollectionCommands::SystemTableCollectionCommands(SharedItem item)
    : ItemCommands(item), tablesM(0)
{
    tablesM = dynamic_cast<SystemTableCollection*>(item.get());
    wxASSERT(tablesM);
}
//-----------------------------------------------------------------------------
void SystemTableCollectionCommands::addCommandsTo(wxMenu* menu,
    bool /*isContextMenu*/)
{
    wxCHECK_RET(menu,
        wxT("SystemTableCollectionCommands::addCommandsTo() called without menu"));
    wxCHECK_RET(tablesM,
        wxT("SystemTableCollectionCommands::addCommandsTo() called without collection"));

    menu->Append(CmdObject_Refresh, _("&Refresh"));
}
//-----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(SystemTableCollectionCommands, ItemCommands)
    EVT_MENU(CmdObject_Refresh, SystemTableCollectionCommands::OnRefresh)
    EVT_UPDATE_UI(CmdObject_Refresh, ItemCommands::CommandIsEnabled)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
void SystemTableCollectionCommands::OnRefresh(wxCommandEvent& /*event*/)
{
    wxCHECK_RET(tablesM,
        wxT("SystemTableCollectionCommands::OnRefresh() called without collection"));

    tablesM->refreshData();
}
//-----------------------------------------------------------------------------
// TableCollectionCommands class
class TableCollectionCommands : public ItemCommands
{
private:
    TableCollection* tablesM;

    void OnCreateNew(wxCommandEvent& event);
    void OnRefresh(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
protected:
    virtual bool hasChildItems();
public:
    TableCollectionCommands(SharedItem item);

    virtual void addCommandsTo(wxMenu* menu, bool isContextMenu);
};
//-----------------------------------------------------------------------------
TableCollectionCommands::TableCollectionCommands(SharedItem item)
    : ItemCommands(item), tablesM(0)
{
    tablesM = dynamic_cast<TableCollection*>(item.get());
    wxASSERT(tablesM);
}
//-----------------------------------------------------------------------------
void TableCollectionCommands::addCommandsTo(wxMenu* menu,
    bool /*isContextMenu*/)
{
    wxCHECK_RET(menu,
        wxT("TableCollectionCommands::addCommandsTo() called without menu"));
    wxCHECK_RET(tablesM,
        wxT("TableCollectionCommands::addCommandsTo() called without collection"));

    menu->Append(CmdObject_Create, _("&Create new table..."));
    menu->AppendSeparator();
    menu->Append(CmdObject_Refresh, _("&Refresh"));
}
//-----------------------------------------------------------------------------
bool TableCollectionCommands::hasChildItems()
{
    return tablesM != 0 && tablesM->hasChildren();
}
//-----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(TableCollectionCommands, ItemCommands)
    EVT_MENU(CmdObject_Create, TableCollectionCommands::OnCreateNew)
    EVT_UPDATE_UI(CmdObject_Create, ItemCommands::CommandIsEnabled)
    EVT_MENU(CmdObject_Refresh, TableCollectionCommands::OnRefresh)
    EVT_UPDATE_UI(CmdObject_Refresh, ItemCommands::CommandIsEnabled)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
void TableCollectionCommands::OnCreateNew(wxCommandEvent& /*event*/)
{
// TODO: implement TableCollectionCommands::OnCreateNew()
}
//-----------------------------------------------------------------------------
void TableCollectionCommands::OnRefresh(wxCommandEvent& /*event*/)
{
    wxCHECK_RET(tablesM,
        wxT("TableCollectionCommands::OnRefresh() called without collection"));

    tablesM->refreshData();
}
//-----------------------------------------------------------------------------
static const ItemCommandsFactoryImpl<Table, TableCommands> factory;
static const ItemCommandsFactoryImpl<SystemTableCollection,
    SystemTableCollectionCommands> collectionFactory1;
static const ItemCommandsFactoryImpl<TableCollection,
    TableCollectionCommands> collectionFactory2;
//-----------------------------------------------------------------------------
