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

#ifndef FR_ITEMVISITOR_H
#define FR_ITEMVISITOR_H
//-----------------------------------------------------------------------------
#include "core/Visitor.h"
//-----------------------------------------------------------------------------
class Database;
class Item;
class SystemTableCollection;
class Table;
class TableCollection;
class TreeFolder;
class View;
class ViewCollection;
//-----------------------------------------------------------------------------
class ItemVisitor : public Visitor
{
public:
    virtual void visit(Item& item);

    virtual void visit(Database& database);
    virtual void visit(SystemTableCollection& tables);
    virtual void visit(Table& table);
    virtual void visit(TableCollection& tables);
    virtual void visit(TreeFolder& folder);
    virtual void visit(View& view);
    virtual void visit(ViewCollection& views);
protected:
    virtual void defaultAction(Item* item);
};
//-----------------------------------------------------------------------------
#endif // FR_ITEMVISITOR_H
