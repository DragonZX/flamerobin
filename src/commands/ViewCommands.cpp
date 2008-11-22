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
#include "hierarchy/View.h"
//-----------------------------------------------------------------------------
// ViewCommands class
class ViewCommands : public ItemCommands
{
private:
    View* viewM;
public:
    ViewCommands(PSharedItem item);
};
//-----------------------------------------------------------------------------
ViewCommands::ViewCommands(PSharedItem item)
    : ItemCommands(item), viewM(0)
{
    viewM = dynamic_cast<View*>(item.get());
    wxASSERT(viewM);
}
//-----------------------------------------------------------------------------
// ViewCollectionCommands class
class ViewCollectionCommands : public ItemCommands
{
private:
    ViewCollection* viewsM;

    void OnCreateNew(wxCommandEvent& event);
    void OnRefresh(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
protected:
    virtual bool hasChildItems();
public:
    ViewCollectionCommands(PSharedItem item);

    virtual void addCommandsTo(wxMenu* menu, bool isContextMenu);
};
//-----------------------------------------------------------------------------
ViewCollectionCommands::ViewCollectionCommands(PSharedItem item)
    : ItemCommands(item), viewsM(0)
{
    viewsM = dynamic_cast<ViewCollection*>(item.get());
    wxASSERT(viewsM);
}
//-----------------------------------------------------------------------------
void ViewCollectionCommands::addCommandsTo(wxMenu* menu,
    bool /*isContextMenu*/)
{
    wxCHECK_RET(menu,
        wxT("ViewCollectionCommands::addCommandsTo() called without menu"));
    wxCHECK_RET(viewsM,
        wxT("ViewCollectionCommands::addCommandsTo() called without collection"));

    menu->Append(CmdObject_Create, _("&Create new view..."));
    menu->AppendSeparator();
    menu->Append(CmdObject_Refresh, _("&Refresh"));
}
//-----------------------------------------------------------------------------
bool ViewCollectionCommands::hasChildItems()
{
    return viewsM != 0 && viewsM->hasChildren();
}
//-----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(ViewCollectionCommands, ItemCommands)
    EVT_MENU(CmdObject_Create, ViewCollectionCommands::OnCreateNew)
    EVT_UPDATE_UI(CmdObject_Create, ItemCommands::CommandIsEnabled)
    EVT_MENU(CmdObject_Refresh, ViewCollectionCommands::OnRefresh)
    EVT_UPDATE_UI(CmdObject_Refresh, ItemCommands::CommandIsEnabled)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
void ViewCollectionCommands::OnCreateNew(wxCommandEvent& /*event*/)
{
// TODO: implement ViewCollectionCommands::OnCreateNew()
}
//-----------------------------------------------------------------------------
void ViewCollectionCommands::OnRefresh(wxCommandEvent& /*event*/)
{
    wxCHECK_RET(viewsM,
        wxT("ViewCollectionCommands::OnRefresh() called without collection"));

    viewsM->refreshData();
}
//-----------------------------------------------------------------------------
static const ItemCommandsFactoryImpl<View, ViewCommands> itemFactory;
static const ItemCommandsFactoryImpl<ViewCollection,
    ViewCollectionCommands> collectionFactory;
//-----------------------------------------------------------------------------
