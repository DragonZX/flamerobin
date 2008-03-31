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
class Column;
class ColumnCollection;
class Database;
class Domain;
class DomainCollection;
class SystemDomainCollection;
class Exception;
class ExceptionCollection;
class Function;
class FunctionCollection;
class Generator;
class GeneratorCollection;
class Item;
class Procedure;
class ProcedureCollection;
class SystemTableCollection;
class Table;
class TableCollection;
class TreeFolder;
class Trigger;
class TriggerCollection;
class View;
class ViewCollection;
//-----------------------------------------------------------------------------
class ItemVisitor : public Visitor
{
public:
    virtual void visit(Item& item);

    virtual void visit(Column& column);
    virtual void visit(ColumnCollection& columns);
    virtual void visit(Database& database);
    virtual void visit(Domain& domain);
    virtual void visit(DomainCollection& domains);
    virtual void visit(SystemDomainCollection& domains);
    virtual void visit(Exception& exception);
    virtual void visit(ExceptionCollection& exceptions);
    virtual void visit(Function& function);
    virtual void visit(FunctionCollection& functions);
    virtual void visit(Generator& generator);
    virtual void visit(GeneratorCollection& generators);
    virtual void visit(Procedure& procedure);
    virtual void visit(ProcedureCollection& procedures);
    virtual void visit(SystemTableCollection& tables);
    virtual void visit(Table& table);
    virtual void visit(TableCollection& tables);
    virtual void visit(TreeFolder& folder);
    virtual void visit(Trigger& trigger);
    virtual void visit(TriggerCollection& triggers);
    virtual void visit(View& view);
    virtual void visit(ViewCollection& views);
protected:
    virtual void defaultAction(Item* item);
};
//-----------------------------------------------------------------------------
#endif // FR_ITEMVISITOR_H
