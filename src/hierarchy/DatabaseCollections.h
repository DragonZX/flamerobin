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

#ifndef FR_DATABASECOLLECTIONS_H
#define FR_DATABASECOLLECTIONS_H
//-----------------------------------------------------------------------------
#include "hierarchy/Item.h"
#include "hierarchy/SharedItems.h"
//-----------------------------------------------------------------------------
class MetadataItemCollection: public ItemWithChildrenBase
{
protected:
    virtual PSharedItem createCollectionItem(const Identifier& identifier) = 0;
public:
    void setChildrenIdentifiers(const std::list<Identifier>& identifiers);
};
//-----------------------------------------------------------------------------
class SystemTableCollection: public MetadataItemCollection
{
protected:
    virtual PSharedItem createCollectionItem(const Identifier& identifier);
public:
    SystemTableCollection();

    virtual void loadChildren();
    virtual void accept(ItemVisitor* visitor);
};
//-----------------------------------------------------------------------------
class TableCollection: public MetadataItemCollection
{
protected:
    virtual PSharedItem createCollectionItem(const Identifier& identifier);
public:
    TableCollection();

    virtual void loadChildren();
    virtual void accept(ItemVisitor* visitor);
};
//-----------------------------------------------------------------------------
#endif // FR_DATABASECOLLECTIONS_H
