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
#include "hierarchy/Exception.h"
//-----------------------------------------------------------------------------
// ExceptionCommands class
class ExceptionCommands : public ItemCommands
{
private:
    Exception* exceptionM;
public:
    ExceptionCommands(SharedItem item);
};
//-----------------------------------------------------------------------------
ExceptionCommands::ExceptionCommands(SharedItem item)
    : ItemCommands(item), exceptionM(0)
{
    exceptionM = dynamic_cast<Exception*>(item.get());
    wxASSERT(exceptionM);
}
//-----------------------------------------------------------------------------
// ExceptionCollectionCommands class
class ExceptionCollectionCommands : public ItemCommands
{
private:
    ExceptionCollection* exceptionsM;

    void OnCreateNew(wxCommandEvent& event);
    void OnRefresh(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
protected:
    virtual bool hasChildItems();
public:
    ExceptionCollectionCommands(SharedItem item);

    virtual void addCommandsTo(wxMenu* menu, bool isContextMenu);
};
//-----------------------------------------------------------------------------
ExceptionCollectionCommands::ExceptionCollectionCommands(SharedItem item)
    : ItemCommands(item), exceptionsM(0)
{
    exceptionsM = dynamic_cast<ExceptionCollection*>(item.get());
    wxASSERT(exceptionsM);
}
//-----------------------------------------------------------------------------
void ExceptionCollectionCommands::addCommandsTo(wxMenu* menu,
    bool /*isContextMenu*/)
{
    wxCHECK_RET(menu,
        wxT("ExceptionCollectionCommands::addCommandsTo() called without menu"));
    wxCHECK_RET(exceptionsM,
        wxT("ExceptionCollectionCommands::addCommandsTo() called without collection"));

    menu->Append(CmdObject_Create, _("&Create new exception..."));
    menu->AppendSeparator();
    menu->Append(CmdObject_Refresh, _("&Refresh"));
}
//-----------------------------------------------------------------------------
bool ExceptionCollectionCommands::hasChildItems()
{
    return exceptionsM != 0 && exceptionsM->hasChildren();
}
//-----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(ExceptionCollectionCommands, ItemCommands)
    EVT_MENU(CmdObject_Create, ExceptionCollectionCommands::OnCreateNew)
    EVT_UPDATE_UI(CmdObject_Create, ItemCommands::CommandIsEnabled)
    EVT_MENU(CmdObject_Refresh, ExceptionCollectionCommands::OnRefresh)
    EVT_UPDATE_UI(CmdObject_Refresh, ItemCommands::CommandIsEnabled)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
void ExceptionCollectionCommands::OnCreateNew(wxCommandEvent& /*event*/)
{
// TODO: implement ExceptionCollectionCommands::OnCreateNew()
}
//-----------------------------------------------------------------------------
void ExceptionCollectionCommands::OnRefresh(wxCommandEvent& /*event*/)
{
    wxCHECK_RET(exceptionsM,
        wxT("ExceptionCollectionCommands::OnRefresh() called without collection"));

    exceptionsM->refreshData();
}
//-----------------------------------------------------------------------------
static const ItemCommandsFactoryImpl<Exception, ExceptionCommands> itemFactory;
static const ItemCommandsFactoryImpl<ExceptionCollection,
    ExceptionCollectionCommands> collectionFactory;
//-----------------------------------------------------------------------------
