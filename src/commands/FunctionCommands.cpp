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
#include "hierarchy/Function.h"
//-----------------------------------------------------------------------------
// FunctionCommands class
class FunctionCommands : public ItemCommands
{
private:
    Function* functionM;
public:
    FunctionCommands(SharedItem item);
};
//-----------------------------------------------------------------------------
FunctionCommands::FunctionCommands(SharedItem item)
    : ItemCommands(item), functionM(0)
{
    functionM = dynamic_cast<Function*>(item.get());
    wxASSERT(functionM);
}
//-----------------------------------------------------------------------------
// FunctionCollectionCommands class
class FunctionCollectionCommands : public ItemCommands
{
private:
    FunctionCollection* functionsM;

    void OnCreateNew(wxCommandEvent& event);
    void OnRefresh(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
protected:
    virtual bool hasChildItems();
public:
    FunctionCollectionCommands(SharedItem item);

    virtual void addCommandsTo(wxMenu* menu, bool isContextMenu);
};
//-----------------------------------------------------------------------------
FunctionCollectionCommands::FunctionCollectionCommands(SharedItem item)
    : ItemCommands(item), functionsM(0)
{
    functionsM = dynamic_cast<FunctionCollection*>(item.get());
    wxASSERT(functionsM);
}
//-----------------------------------------------------------------------------
void FunctionCollectionCommands::addCommandsTo(wxMenu* menu,
    bool /*isContextMenu*/)
{
    wxCHECK_RET(menu,
        wxT("FunctionCollectionCommands::addCommandsTo() called without menu"));
    wxCHECK_RET(functionsM,
        wxT("FunctionCollectionCommands::addCommandsTo() called without collection"));

    menu->Append(CmdObject_Create, _("&Declare new function..."));
    menu->AppendSeparator();
    menu->Append(CmdObject_Refresh, _("&Refresh"));
}
//-----------------------------------------------------------------------------
bool FunctionCollectionCommands::hasChildItems()
{
    return functionsM != 0 && functionsM->hasChildren();
}
//-----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(FunctionCollectionCommands, ItemCommands)
    EVT_MENU(CmdObject_Create, FunctionCollectionCommands::OnCreateNew)
    EVT_UPDATE_UI(CmdObject_Create, ItemCommands::CommandIsEnabled)
    EVT_MENU(CmdObject_Refresh, FunctionCollectionCommands::OnRefresh)
    EVT_UPDATE_UI(CmdObject_Refresh, ItemCommands::CommandIsEnabled)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
void FunctionCollectionCommands::OnCreateNew(wxCommandEvent& /*event*/)
{
// TODO: implement FunctionCollectionCommands::OnCreateNew()
}
//-----------------------------------------------------------------------------
void FunctionCollectionCommands::OnRefresh(wxCommandEvent& /*event*/)
{
    wxCHECK_RET(functionsM,
        wxT("FunctionCollectionCommands::OnRefresh() called without collection"));

    functionsM->refreshData();
}
//-----------------------------------------------------------------------------
static const ItemCommandsFactoryImpl<Function, FunctionCommands> itemFactory;
static const ItemCommandsFactoryImpl<FunctionCollection,
    FunctionCollectionCommands> collectionFactory;
//-----------------------------------------------------------------------------
