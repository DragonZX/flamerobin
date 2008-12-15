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

#ifndef FR_SHAREDITEMS_H
#define FR_SHAREDITEMS_H
//-----------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
//-----------------------------------------------------------------------------
class Item;
typedef boost::shared_ptr<Item> SharedItem;

class TreeFolder;
typedef boost::shared_ptr<TreeFolder> SharedTreeFolder;
class TreeRoot;
typedef boost::shared_ptr<TreeRoot> SharedTreeRoot;

class Database;
typedef boost::shared_ptr<Database> SharedDatabase;

class Column;
typedef boost::shared_ptr<Column> SharedColumn;
class ColumnCollection;
typedef boost::shared_ptr<ColumnCollection> SharedColumnCollection;
class Domain;
typedef boost::shared_ptr<Domain> SharedDomain;
class DomainCollection;
typedef boost::shared_ptr<DomainCollection> SharedDomainCollection;
class SystemDomainCollection;
typedef boost::shared_ptr<SystemDomainCollection> SharedSystemDomainCollection;
class Exception;
typedef boost::shared_ptr<Exception> SharedException;
class ExceptionCollection;
typedef boost::shared_ptr<ExceptionCollection> SharedExceptionCollection;
class Function;
typedef boost::shared_ptr<Function> SharedFunction;
class FunctionCollection;
typedef boost::shared_ptr<FunctionCollection> SharedFunctionCollection;
class Generator;
typedef boost::shared_ptr<Generator> SharedGenerator;
class GeneratorCollection;
typedef boost::shared_ptr<GeneratorCollection> SharedGeneratorCollection;
class Procedure;
typedef boost::shared_ptr<Procedure> SharedProcedure;
class ProcedureCollection;
typedef boost::shared_ptr<ProcedureCollection> SharedProcedureCollection;
class Table;
typedef boost::shared_ptr<Table> SharedTable;
class TableCollection;
typedef boost::shared_ptr<TableCollection> SharedTableCollection;
class SystemTableCollection;
typedef boost::shared_ptr<SystemTableCollection> SharedSystemTableCollection;
class Trigger;
typedef boost::shared_ptr<Trigger> SharedTrigger;
class TriggerCollection;
typedef boost::shared_ptr<TriggerCollection> SharedTriggerCollection;
class View;
typedef boost::shared_ptr<View> SharedView;
class ViewCollection;
typedef boost::shared_ptr<ViewCollection> SharedViewCollection;
//-----------------------------------------------------------------------------
#endif // FR_SHAREDITEMS_H
