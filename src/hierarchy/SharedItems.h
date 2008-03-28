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
typedef boost::shared_ptr<Item> PSharedItem;

class TreeFolder;
typedef boost::shared_ptr<TreeFolder> PSharedTreeFolder;
class TreeRoot;
typedef boost::shared_ptr<TreeRoot> PSharedTreeRoot;

class Database;
typedef boost::shared_ptr<Database> PSharedDatabase;

class Table;
typedef boost::shared_ptr<Table> PSharedTable;
class TableCollection;
typedef boost::shared_ptr<TableCollection> PSharedTableCollection;
class SystemTableCollection;
typedef boost::shared_ptr<SystemTableCollection> PSharedSystemTableCollection;
class Trigger;
typedef boost::shared_ptr<Trigger> PSharedTrigger;
class TriggerCollection;
typedef boost::shared_ptr<TriggerCollection> PSharedTriggerCollection;
class View;
typedef boost::shared_ptr<View> PSharedView;
class ViewCollection;
typedef boost::shared_ptr<ViewCollection> PSharedViewCollection;
//-----------------------------------------------------------------------------
#endif // FR_SHAREDITEMS_H
