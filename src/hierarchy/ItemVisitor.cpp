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

#include "hierarchy/Database.h"
#include "hierarchy/Function.h"
#include "hierarchy/Generator.h"
#include "hierarchy/Item.h"
#include "hierarchy/ItemVisitor.h"
#include "hierarchy/Procedure.h"
#include "hierarchy/Table.h"
#include "hierarchy/TreeFolder.h"
#include "hierarchy/Trigger.h"
#include "hierarchy/View.h"
//-----------------------------------------------------------------------------
void ItemVisitor::visit(Item& item)
{
    defaultAction(&item);
}
//-----------------------------------------------------------------------------
void ItemVisitor::visit(Database& database)
{
    defaultAction(&database);
}
//-----------------------------------------------------------------------------
void ItemVisitor::visit(Function& function)
{
    defaultAction(&function);
}
//-----------------------------------------------------------------------------
void ItemVisitor::visit(FunctionCollection& functions)
{
    defaultAction(&functions);
}
//-----------------------------------------------------------------------------
void ItemVisitor::visit(Generator& generator)
{
    defaultAction(&generator);
}
//-----------------------------------------------------------------------------
void ItemVisitor::visit(GeneratorCollection& generators)
{
    defaultAction(&generators);
}
//-----------------------------------------------------------------------------
void ItemVisitor::visit(Procedure& procedure)
{
    defaultAction(&procedure);
}
//-----------------------------------------------------------------------------
void ItemVisitor::visit(ProcedureCollection& procedures)
{
    defaultAction(&procedures);
}
//-----------------------------------------------------------------------------
void ItemVisitor::visit(SystemTableCollection& tables)
{
    defaultAction(&tables);
}
//-----------------------------------------------------------------------------
void ItemVisitor::visit(Table& table)
{
    defaultAction(&table);
}
//-----------------------------------------------------------------------------
void ItemVisitor::visit(TableCollection& tables)
{
    defaultAction(&tables);
}
//-----------------------------------------------------------------------------
void ItemVisitor::visit(TreeFolder& folder)
{
    defaultAction(&folder);
}
//-----------------------------------------------------------------------------
void ItemVisitor::visit(Trigger& trigger)
{
    defaultAction(&trigger);
}
//-----------------------------------------------------------------------------
void ItemVisitor::visit(TriggerCollection& triggers)
{
    defaultAction(&triggers);
}
//-----------------------------------------------------------------------------
void ItemVisitor::visit(View& view)
{
    defaultAction(&view);
}
//-----------------------------------------------------------------------------
void ItemVisitor::visit(ViewCollection& views)
{
    defaultAction(&views);
}
//-----------------------------------------------------------------------------
void ItemVisitor::defaultAction(Item*)
{
}
//-----------------------------------------------------------------------------
