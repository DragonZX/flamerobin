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

#ifndef FR_ITEMCOMMANDS_H
#define FR_ITEMCOMMANDS_H
//-----------------------------------------------------------------------------
#include <wx/event.h>

#include <map>

#include "hierarchy/SharedItems.h"
//-----------------------------------------------------------------------------
class ItemCommands;

class ItemCommandsFactory
{
protected:
    virtual ~ItemCommandsFactory() {};
public:
    virtual ItemCommands* createItemCommands(PSharedItem item) = 0;
};
//-----------------------------------------------------------------------------
template<class T, class TC>
class ItemCommandsFactoryImpl : public ItemCommandsFactory
{
public:
public:
    ItemCommandsFactoryImpl() : ItemCommandsFactory()
    {
        ItemCommands::registerFactory(typeid(T), this);
    };
    virtual ~ItemCommandsFactoryImpl()
    {
        ItemCommands::unregisterFactory(typeid(T), this);
    };
    virtual ItemCommands* createItemCommands(PSharedItem item)
    {
        return new TC(item);
    };
};
//-----------------------------------------------------------------------------
class ItemCommands : public wxEvtHandler
{
private:
    typedef std::map<void*, ItemCommandsFactory*> TypeInfoFactoryMap;
    typedef TypeInfoFactoryMap::value_type TypeInfoFactoryPair;
    static TypeInfoFactoryMap& getFactories();

    PSharedItem itemM;
protected:
    ItemCommands(PSharedItem item);

public:
    static bool registerFactory(const type_info& info,
        ItemCommandsFactory* factory);
    static bool unregisterFactory(const type_info& info,
        ItemCommandsFactory* factory);
    static ItemCommands* createItemCommands(PSharedItem item);

    PSharedItem getItem();
};
//-----------------------------------------------------------------------------
#endif // FR_ITEMCOMMANDS_H
