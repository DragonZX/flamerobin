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
#include "hierarchy/Generator.h"
//-----------------------------------------------------------------------------
// GeneratorCommands class
class GeneratorCommands : public ItemCommands
{
private:
    Generator* generatorM;

    void OnShowInfo(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
public:
    GeneratorCommands(PSharedItem item);

    virtual void addCommandsTo(wxMenu* menu, bool isContextMenu);
};
//-----------------------------------------------------------------------------
GeneratorCommands::GeneratorCommands(PSharedItem item)
    : ItemCommands(item), generatorM(0)
{
    generatorM = dynamic_cast<Generator*>(item.get());
    wxASSERT(generatorM);
}
//-----------------------------------------------------------------------------
void GeneratorCommands::addCommandsTo(wxMenu* menu, bool /*isContextMenu*/)
{
    wxCHECK_RET(menu,
        wxT("GeneratorCommands::addCommandsTo() called without menu"));
    wxCHECK_RET(generatorM,
        wxT("GeneratorCommands::addCommandsTo() called without generator"));

    menu->Append(CmdObject_ShowInfo, _("&Show value"));
}
//-----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(GeneratorCommands, ItemCommands)
    EVT_MENU(CmdObject_ShowInfo, GeneratorCommands::OnShowInfo)
    EVT_UPDATE_UI(CmdObject_ShowInfo, ItemCommands::CommandIsEnabled)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
void GeneratorCommands::OnShowInfo(wxCommandEvent& /*event*/)
{
    wxCHECK_RET(generatorM,
        wxT("GeneratorCommands::OnShowInfo() called without generator"));

    generatorM->loadValue();
}
//-----------------------------------------------------------------------------
// GeneratorCollectionCommands class
class GeneratorCollectionCommands : public ItemCommands
{
private:
    GeneratorCollection* generatorsM;

    void OnCreateNew(wxCommandEvent& event);
    void OnRefresh(wxCommandEvent& event);
    void OnShowInfo(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
protected:
    virtual bool hasChildItems();
public:
    GeneratorCollectionCommands(PSharedItem item);

    virtual void addCommandsTo(wxMenu* menu, bool isContextMenu);
};
//-----------------------------------------------------------------------------
GeneratorCollectionCommands::GeneratorCollectionCommands(PSharedItem item)
    : ItemCommands(item), generatorsM(0)
{
    generatorsM = dynamic_cast<GeneratorCollection*>(item.get());
    wxASSERT(generatorsM);
}
//-----------------------------------------------------------------------------
void GeneratorCollectionCommands::addCommandsTo(wxMenu* menu,
    bool /*isContextMenu*/)
{
    wxCHECK_RET(menu,
        wxT("GeneratorCollectionCommands::addCommandsTo() called without menu"));
    wxCHECK_RET(generatorsM,
        wxT("GeneratorCollectionCommands::addCommandsTo() called without collection"));

    menu->Append(CmdObject_Create, _("&Create new generator..."));
    menu->AppendSeparator();
    menu->Append(CmdObject_ShowInfo, _("&Show all generator values"));
    menu->AppendSeparator();
    menu->Append(CmdObject_Refresh, _("&Refresh"));
}
//-----------------------------------------------------------------------------
bool GeneratorCollectionCommands::hasChildItems()
{
    return generatorsM != 0 && generatorsM->hasChildren();
}
//-----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(GeneratorCollectionCommands, ItemCommands)
    EVT_MENU(CmdObject_Create, GeneratorCollectionCommands::OnCreateNew)
    EVT_UPDATE_UI(CmdObject_Create, ItemCommands::CommandIsEnabled)
    EVT_MENU(CmdObject_ShowInfo, GeneratorCollectionCommands::OnShowInfo)
    EVT_UPDATE_UI(CmdObject_ShowInfo, ItemCommands::CommandIsEnabledIfHasChildItems)
    EVT_MENU(CmdObject_Refresh, GeneratorCollectionCommands::OnRefresh)
    EVT_UPDATE_UI(CmdObject_Refresh, ItemCommands::CommandIsEnabled)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
void GeneratorCollectionCommands::OnCreateNew(wxCommandEvent& /*event*/)
{
// TODO: implement GeneratorCollectionCommands::OnCreateNew()
}
//-----------------------------------------------------------------------------
void GeneratorCollectionCommands::OnRefresh(wxCommandEvent& /*event*/)
{
    wxCHECK_RET(generatorsM,
        wxT("GeneratorCollectionCommands::OnRefresh() called without collection"));

    generatorsM->refreshData();
}
//-----------------------------------------------------------------------------
void GeneratorCollectionCommands::OnShowInfo(wxCommandEvent& /*event*/)
{
    wxCHECK_RET(generatorsM,
        wxT("GeneratorCollectionCommands::OnShowInfo() called without collection"));

    generatorsM->loadValues();
}
//-----------------------------------------------------------------------------
static const ItemCommandsFactoryImpl<Generator,
    GeneratorCommands> itemFactory;
static const ItemCommandsFactoryImpl<GeneratorCollection,
    GeneratorCollectionCommands> collectionFactory;
//-----------------------------------------------------------------------------
