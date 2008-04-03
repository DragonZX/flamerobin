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

#include "hierarchy/Database.h"
#include "hierarchy/Table.h"
//-----------------------------------------------------------------------------
/*static*/
ItemCommands::TypeInfoFactoryMap& ItemCommands::getFactories()
{
    static ItemCommands::TypeInfoFactoryMap factories;
    return factories;
}
//-----------------------------------------------------------------------------
/*static*/
bool ItemCommands::registerFactory(const std::type_info& info,
    ItemCommandsFactory* factory)
{
    if (!factory)
        return false;
    TypeInfoFactoryMap& factories(getFactories());
    if (factories.find((void*)&info) != factories.end())
        return false;
    factories.insert(TypeInfoFactoryPair((void*)&info, factory));
    return true;
}
//-----------------------------------------------------------------------------
/*static*/
bool ItemCommands::unregisterFactory(const std::type_info& info,
    ItemCommandsFactory* factory)
{
    if (!factory)
        return false;
    TypeInfoFactoryMap& factories(getFactories());
    if (factories.find((void*)&info) == factories.end())
        return false;
    factories.erase((void*)&info);
    return true;
}
//-----------------------------------------------------------------------------
/*static*/
ItemCommands* ItemCommands::createItemCommands(PSharedItem item)
{
    if (!item)
        return 0;
    const std::type_info& info = typeid(*item.get());
    TypeInfoFactoryMap& factories(getFactories());

    TypeInfoFactoryMap::iterator it = factories.find((void*)&info);
    if (it != factories.end())
        return ((*it).second)->createItemCommands(item);
    return 0;
}
//-----------------------------------------------------------------------------
ItemCommands::ItemCommands(PSharedItem item)
    : wxEvtHandler(), itemM(item)
{
}
//-----------------------------------------------------------------------------
void ItemCommands::addCommandsTo(wxMenu* /*menu*/, bool /*isContextMenu*/)
{
}
//-----------------------------------------------------------------------------
PSharedItem ItemCommands::getItem()
{
    return itemM;
}
//-----------------------------------------------------------------------------
void ItemCommands::CommandIsDisabled(wxUpdateUIEvent& event)
{
    event.Enable(false);
}
//-----------------------------------------------------------------------------
void ItemCommands::CommandIsEnabled(wxUpdateUIEvent& event)
{
    event.Enable(true);
}
//-----------------------------------------------------------------------------
