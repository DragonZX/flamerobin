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

#include "core/StringUtils.h"

#include "engine/DatabaseConnection.h"

#include "hierarchy/Column.h"
#include "hierarchy/ItemVisitor.h"
#include "hierarchy/Relation.h"
//-----------------------------------------------------------------------------
// Column class
Column::Column(const Identifier& identifier)
{
    setIdentifier(identifier);
}
//-----------------------------------------------------------------------------
const wxString Column::getTypeName() const
{
    return wxT("COLUMN");
}
//-----------------------------------------------------------------------------
void Column::accept(ItemVisitor* visitor)
{
    wxASSERT(visitor);
    if (visitor)
        visitor->visit(*this);
}
//-----------------------------------------------------------------------------
// ColumnCollection class
PSharedItem ColumnCollection::createCollectionItem(const Identifier& identifier)
{
    PSharedItem column(new Column(identifier));
    column->setParent(shared_from_this());
    return column;
}
//-----------------------------------------------------------------------------
void ColumnCollection::loadChildren()
{
    Database* db = getDatabase();
    wxCHECK_RET(db,
        wxT("ColumnCollection::loadChildren() called without parent database"));
    DatabaseConnection* dbc = db->getMetadataConnection();
    if (dbc)
    {
        setLoadChildrenState(lcsLoading);
        std::string sql("select rf.RDB$FIELD_NAME, rf.RDB$NULL_FLAG,"
            " rf.RDB$FIELD_SOURCE, c.RDB$COLLATION_NAME,"
            " f.RDB$COMPUTED_SOURCE, rf.RDB$DEFAULT_SOURCE"
            " from RDB$FIELDS f"
            " join RDB$RELATION_FIELDS rf"
            "     on f.RDB$FIELD_NAME = rf.RDB$FIELD_SOURCE"
            " left outer join RDB$COLLATIONS c"
            "     on c.RDB$COLLATION_ID = rf.RDB$COLLATION_ID"
            "     and c.RDB$CHARACTER_SET_ID = f.RDB$CHARACTER_SET_ID"
            " where rf.RDB$RELATION_NAME = ?"
            " order by rf.RDB$FIELD_POSITION");
        std::vector<std::string> params;
        if (Relation* relation = getRelation())
            params.push_back(wx2std(relation->getName()));
// TODO: loadCollection() needs to read and set all fields, not only identifiers...
        dbc->loadCollection(getHandle(), sql, params);
        return;
    }

    // loading is not possible, so clear children and show empty collection
    SubjectLocker lock(this);
    clearChildren();
    setLoadChildrenState(lcsLoaded);
    notifyObservers();
}
//-----------------------------------------------------------------------------
void ColumnCollection::accept(ItemVisitor* visitor)
{
    wxASSERT(visitor);
    if (visitor)
        visitor->visit(*this);
}
//-----------------------------------------------------------------------------
