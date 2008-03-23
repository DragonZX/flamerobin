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

#include "engine/DatabaseConnection.h"
#include "hierarchy/Database.h"
#include "hierarchy/DatabaseCollections.h"
#include "hierarchy/ItemVisitor.h"
#include "hierarchy/Table.h"
#include "hierarchy/View.h"
//-----------------------------------------------------------------------------
// MetadataItemCollection base class
void MetadataItemCollection::setChildrenIdentifiers(
    const std::list<Identifier>& identifiers)
{
    bool changed = identifiers.size() != getChildrenCount();
    std::vector<PSharedItem> children;

    SubjectLocker lock(this);
    for (std::list<Identifier>::const_iterator it = identifiers.begin();
        it != identifiers.end(); ++it)
    {
        const Identifier& id = *it;
        PSharedItem child = getChild(id.get());
        if (!child)
        {
            child = createCollectionItem(id);
            changed = true;
        }
        children.push_back(child);
    }
    if (changed)
    {
// TODO: remove children that are no longer in identifiers
    };
    setChildrenLoaded(true);
    notifyObservers();
}
//-----------------------------------------------------------------------------
// SystemTableCollection class
SystemTableCollection::SystemTableCollection()
{
    // load children on-demand
    setChildrenLoaded(false);
}
//-----------------------------------------------------------------------------
PSharedItem SystemTableCollection::createCollectionItem(
    const Identifier& identifier)
{
    PSharedItem table(new Table(identifier));
    table->setParent(shared_from_this());
    return table;
}
//-----------------------------------------------------------------------------
bool SystemTableCollection::isSystem()
{
    return true;
}
//-----------------------------------------------------------------------------
void SystemTableCollection::loadChildren()
{
    Database* db = getDatabase();
    wxCHECK_RET(db,
        wxT("SystemTableCollection::loadChildren() called without parent database"));
    DatabaseConnection* dbc = db->getMetadataConnection();
    if (dbc)
    {
        std::string sql("select r.rdb$relation_name from rdb$relations r "
            " where (r.RDB$SYSTEM_FLAG = 1) "
            " and r.RDB$VIEW_SOURCE is null order by 1");
        dbc->loadCollection(getHandle(), sql);
        return;
    }

    // loading is not possible, so clear children and show empty collection
    SubjectLocker lock(this);
    clearChildren();
    setChildrenLoaded(true);
    notifyObservers();
}
//-----------------------------------------------------------------------------
void SystemTableCollection::accept(ItemVisitor* visitor)
{
    wxASSERT(visitor);
    if (visitor)
        visitor->visit(*this);
}
//-----------------------------------------------------------------------------
// TableCollection class
TableCollection::TableCollection()
{
    // load children on-demand
    setChildrenLoaded(false);
}
//-----------------------------------------------------------------------------
PSharedItem TableCollection::createCollectionItem(const Identifier& identifier)
{
    PSharedItem table(new Table(identifier));
    table->setParent(shared_from_this());
    return table;
}
//-----------------------------------------------------------------------------
void TableCollection::loadChildren()
{
    Database* db = getDatabase();
    wxCHECK_RET(db,
        wxT("TableCollection::loadChildren() called without parent database"));
    DatabaseConnection* dbc = db->getMetadataConnection();
    if (dbc)
    {
        std::string sql("select r.rdb$relation_name from rdb$relations r "
            " where (r.RDB$SYSTEM_FLAG = 0 or r.RDB$SYSTEM_FLAG is null) "
            " and r.RDB$VIEW_SOURCE is null order by 1");
        dbc->loadCollection(getHandle(), sql);
        return;
    }

    // loading is not possible, so clear children and show empty collection
    SubjectLocker lock(this);
    clearChildren();
    setChildrenLoaded(true);
    notifyObservers();
}
//-----------------------------------------------------------------------------
void TableCollection::accept(ItemVisitor* visitor)
{
    wxASSERT(visitor);
    if (visitor)
        visitor->visit(*this);
}
//-----------------------------------------------------------------------------
// ViewCollection class
ViewCollection::ViewCollection()
{
    // load children on-demand
    setChildrenLoaded(false);
}
//-----------------------------------------------------------------------------
PSharedItem ViewCollection::createCollectionItem(const Identifier& identifier)
{
    PSharedItem view(new View(identifier));
    view->setParent(shared_from_this());
    return view;
}
//-----------------------------------------------------------------------------
void ViewCollection::loadChildren()
{
    Database* db = getDatabase();
    wxCHECK_RET(db,
        wxT("ViewCollection::loadChildren() called without parent database"));
    DatabaseConnection* dbc = db->getMetadataConnection();
    if (dbc)
    {
        std::string sql("select r.rdb$relation_name from rdb$relations r "
            " where (r.RDB$SYSTEM_FLAG = 0 or r.RDB$SYSTEM_FLAG is null) "
            " and r.RDB$VIEW_SOURCE is not null order by 1");
        dbc->loadCollection(getHandle(), sql);
        return;
    }

    // loading is not possible, so clear children and show empty collection
    SubjectLocker lock(this);
    clearChildren();
    setChildrenLoaded(true);
    notifyObservers();
}
//-----------------------------------------------------------------------------
void ViewCollection::accept(ItemVisitor* visitor)
{
    wxASSERT(visitor);
    if (visitor)
        visitor->visit(*this);
}
//-----------------------------------------------------------------------------
