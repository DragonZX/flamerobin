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

#include "hierarchy/ItemVisitor.h"
#include "hierarchy/Table.h"
//-----------------------------------------------------------------------------
Table::Table(const Identifier& identifier)
    : Relation()
{
    setIdentifier(identifier);
}
//-----------------------------------------------------------------------------
const wxString Table::getTypeName() const
{
    return wxT("TABLE");
}
//-----------------------------------------------------------------------------
bool Table::isSystem()
{
    wxString prefix(getName().Mid(0, 4).MakeUpper());
    return (prefix == wxT("RDB$") || prefix == wxT("MON$"));
}
//-----------------------------------------------------------------------------
void Table::accept(ItemVisitor* visitor)
{
    wxASSERT(visitor);
    if (visitor)
        visitor->visit(*this);
}
//-----------------------------------------------------------------------------
// SystemTableCollection class
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
        std::string sql("select r.RDB$RELATION_NAME from RDB$RELATIONS r"
            " where r.RDB$SYSTEM_FLAG = 1 and r.RDB$VIEW_SOURCE is null"
            " order by 1");
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
        std::string sql("select r.RDB$RELATION_NAME from RDB$RELATIONS r"
            " where (r.RDB$SYSTEM_FLAG = 0 or RDB$SYSTEM_FLAG is null)"
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
