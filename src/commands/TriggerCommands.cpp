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

#include "hierarchy/Relation.h"
#include "hierarchy/Trigger.h"
//-----------------------------------------------------------------------------
// TriggerCommands class
class TriggerCommands : public ItemCommands
{
private:
    Trigger* triggerM;
public:
    TriggerCommands(PSharedItem item);
};
//-----------------------------------------------------------------------------
TriggerCommands::TriggerCommands(PSharedItem item)
    : ItemCommands(item), triggerM(0)
{
    triggerM = dynamic_cast<Trigger*>(item.get());
    wxASSERT(triggerM);
}
//-----------------------------------------------------------------------------
// TriggerCollectionCommands class
class TriggerCollectionCommands : public ItemCommands
{
private:
    TriggerCollection* triggersM;
    bool canCreateNewM;

    void OnCreateNew(wxCommandEvent& event);
    void OnRefresh(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
protected:
    virtual bool hasChildItems();
public:
    TriggerCollectionCommands(PSharedItem item);

    virtual void addCommandsTo(wxMenu* menu, bool isContextMenu);
};
//-----------------------------------------------------------------------------
TriggerCollectionCommands::TriggerCollectionCommands(PSharedItem item)
    : ItemCommands(item), triggersM(0), canCreateNewM(false)
{
    triggersM = dynamic_cast<TriggerCollection*>(item.get());
    wxASSERT(triggersM);

    Relation* relation = triggersM->getRelation();
    canCreateNewM = relation && !relation->isSystem();
}
//-----------------------------------------------------------------------------
void TriggerCollectionCommands::addCommandsTo(wxMenu* menu,
    bool /*isContextMenu*/)
{
    wxCHECK_RET(menu,
        wxT("TriggerCollectionCommands::addCommandsTo() called without menu"));
    wxCHECK_RET(triggersM,
        wxT("TriggerCollectionCommands::addCommandsTo() called without collection"));

    if (canCreateNewM)
    {
        menu->Append(CmdObject_Create, _("&Create new trigger..."));
        menu->AppendSeparator();
    }
    menu->Append(CmdObject_Refresh, _("&Refresh"));
}
//-----------------------------------------------------------------------------
bool TriggerCollectionCommands::hasChildItems()
{
    return triggersM != 0 && triggersM->hasChildren();
}
//-----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(TriggerCollectionCommands, ItemCommands)
    EVT_MENU(CmdObject_Create, TriggerCollectionCommands::OnCreateNew)
    EVT_UPDATE_UI(CmdObject_Create, ItemCommands::CommandIsEnabled)
    EVT_MENU(CmdObject_Refresh, TriggerCollectionCommands::OnRefresh)
    EVT_UPDATE_UI(CmdObject_Refresh, ItemCommands::CommandIsEnabled)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
void TriggerCollectionCommands::OnCreateNew(wxCommandEvent& /*event*/)
{
// TODO: implement TriggerCollectionCommands::OnCreateNew()
}
//-----------------------------------------------------------------------------
void TriggerCollectionCommands::OnRefresh(wxCommandEvent& /*event*/)
{
    wxCHECK_RET(triggersM,
        wxT("TriggerCollectionCommands::OnRefresh() called without collection"));

    triggersM->refreshData();
}
//-----------------------------------------------------------------------------
static const ItemCommandsFactoryImpl<Trigger, TriggerCommands> itemFactory;
static const ItemCommandsFactoryImpl<TriggerCollection,
    TriggerCollectionCommands> collectionFactory;
//-----------------------------------------------------------------------------
