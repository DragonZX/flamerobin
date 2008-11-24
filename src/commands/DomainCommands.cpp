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
#include "hierarchy/Domain.h"
//-----------------------------------------------------------------------------
// DomainCommands class
class DomainCommands : public ItemCommands
{
private:
    Domain* domainM;
public:
    DomainCommands(PSharedItem item);
};
//-----------------------------------------------------------------------------
DomainCommands::DomainCommands(PSharedItem item)
    : ItemCommands(item), domainM(0)
{
    domainM = dynamic_cast<Domain*>(item.get());
    wxASSERT(domainM);
}
//-----------------------------------------------------------------------------
// DomainCollectionCommands class
class DomainCollectionCommands : public ItemCommands
{
private:
    DomainCollection* domainsM;

    void OnCreateNew(wxCommandEvent& event);
    void OnRefresh(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
protected:
    virtual bool hasChildItems();
public:
    DomainCollectionCommands(PSharedItem item);

    virtual void addCommandsTo(wxMenu* menu, bool isContextMenu);
};
//-----------------------------------------------------------------------------
DomainCollectionCommands::DomainCollectionCommands(PSharedItem item)
    : ItemCommands(item), domainsM(0)
{
    domainsM = dynamic_cast<DomainCollection*>(item.get());
    wxASSERT(domainsM);
}
//-----------------------------------------------------------------------------
void DomainCollectionCommands::addCommandsTo(wxMenu* menu,
    bool /*isContextMenu*/)
{
    wxCHECK_RET(menu,
        wxT("DomainCollectionCommands::addCommandsTo() called without menu"));
    wxCHECK_RET(domainsM,
        wxT("DomainCollectionCommands::addCommandsTo() called without collection"));

    menu->Append(CmdObject_Create, _("&Create new domain..."));
    menu->AppendSeparator();
    menu->Append(CmdObject_Refresh, _("&Refresh"));
}
//-----------------------------------------------------------------------------
bool DomainCollectionCommands::hasChildItems()
{
    return domainsM != 0 && domainsM->hasChildren();
}
//-----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(DomainCollectionCommands, ItemCommands)
    EVT_MENU(CmdObject_Create, DomainCollectionCommands::OnCreateNew)
    EVT_UPDATE_UI(CmdObject_Create, ItemCommands::CommandIsEnabled)
    EVT_MENU(CmdObject_Refresh, DomainCollectionCommands::OnRefresh)
    EVT_UPDATE_UI(CmdObject_Refresh, ItemCommands::CommandIsEnabled)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
void DomainCollectionCommands::OnCreateNew(wxCommandEvent& /*event*/)
{
// TODO: implement DomainCollectionCommands::OnCreateNew()
}
//-----------------------------------------------------------------------------
void DomainCollectionCommands::OnRefresh(wxCommandEvent& /*event*/)
{
    wxCHECK_RET(domainsM,
        wxT("DomainCollectionCommands::OnRefresh() called without collection"));

    domainsM->refreshData();
}
//-----------------------------------------------------------------------------
static const ItemCommandsFactoryImpl<Domain, DomainCommands> itemFactory;
static const ItemCommandsFactoryImpl<DomainCollection,
    DomainCollectionCommands> collectionFactory;
//-----------------------------------------------------------------------------