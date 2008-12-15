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

#include "hierarchy/Column.h"
#include "hierarchy/Table.h"
//-----------------------------------------------------------------------------
// ColumnCommands class
class ColumnCommands : public ItemCommands
{
private:
    Column* columnM;
public:
    ColumnCommands(SharedItem item);
};
//-----------------------------------------------------------------------------
ColumnCommands::ColumnCommands(SharedItem item)
    : ItemCommands(item), columnM(0)
{
    columnM = dynamic_cast<Column*>(item.get());
    wxASSERT(columnM);
}
//-----------------------------------------------------------------------------
// ColumnCollectionCommands class
class ColumnCollectionCommands : public ItemCommands
{
private:
    ColumnCollection* columnsM;
    bool canCreateNewM;

    void OnCreateNew(wxCommandEvent& event);
    void OnRefresh(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
protected:
    virtual bool hasChildItems();
public:
    ColumnCollectionCommands(SharedItem item);

    virtual void addCommandsTo(wxMenu* menu, bool isContextMenu);
};
//-----------------------------------------------------------------------------
ColumnCollectionCommands::ColumnCollectionCommands(SharedItem item)
    : ItemCommands(item), columnsM(0), canCreateNewM(false)
{
    columnsM = dynamic_cast<ColumnCollection*>(item.get());
    wxASSERT(columnsM);

    Table* table = dynamic_cast<Table*>(columnsM->getRelation());
    canCreateNewM = table && !table->isSystem();
}
//-----------------------------------------------------------------------------
void ColumnCollectionCommands::addCommandsTo(wxMenu* menu,
    bool /*isContextMenu*/)
{
    wxCHECK_RET(menu,
        wxT("ColumnCollectionCommands::addCommandsTo() called without menu"));
    wxCHECK_RET(columnsM,
        wxT("ColumnCollectionCommands::addCommandsTo() called without collection"));

    if (canCreateNewM)
    {
        menu->Append(CmdObject_Create, _("&Create new column..."));
        menu->AppendSeparator();
    }
    menu->Append(CmdObject_Refresh, _("&Refresh"));
}
//-----------------------------------------------------------------------------
bool ColumnCollectionCommands::hasChildItems()
{
    return columnsM != 0 && columnsM->hasChildren();
}
//-----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(ColumnCollectionCommands, ItemCommands)
    EVT_MENU(CmdObject_Create, ColumnCollectionCommands::OnCreateNew)
    EVT_UPDATE_UI(CmdObject_Create, ItemCommands::CommandIsEnabled)
    EVT_MENU(CmdObject_Refresh, ColumnCollectionCommands::OnRefresh)
    EVT_UPDATE_UI(CmdObject_Refresh, ItemCommands::CommandIsEnabled)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
void ColumnCollectionCommands::OnCreateNew(wxCommandEvent& /*event*/)
{
// TODO: implement ColumnCollectionCommands::OnCreateNew()
}
//-----------------------------------------------------------------------------
void ColumnCollectionCommands::OnRefresh(wxCommandEvent& /*event*/)
{
    wxCHECK_RET(columnsM,
        wxT("ColumnCollectionCommands::OnRefresh() called without collection"));

    columnsM->refreshData();
}
//-----------------------------------------------------------------------------
static const ItemCommandsFactoryImpl<Column, ColumnCommands> itemFactory;
static const ItemCommandsFactoryImpl<ColumnCollection,
    ColumnCollectionCommands> collectionFactory;
//-----------------------------------------------------------------------------
