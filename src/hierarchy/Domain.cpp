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

#include "hierarchy/Domain.h"
#include "hierarchy/ItemVisitor.h"
//-----------------------------------------------------------------------------
// Domain class
Domain::Domain(const Identifier& identifier)
{
    setIdentifier(identifier);
}
//-----------------------------------------------------------------------------
const wxString Domain::getTypeName() const
{
    return wxT("DOMAIN");
}
//-----------------------------------------------------------------------------
bool Domain::isSystem()
{
    wxString prefix(getName().Mid(0, 4).MakeUpper());
    return (prefix == wxT("RDB$"));
}
//-----------------------------------------------------------------------------
void Domain::accept(ItemVisitor* visitor)
{
    wxASSERT(visitor);
    if (visitor)
        visitor->visit(*this);
}
//-----------------------------------------------------------------------------
// DomainCollection class
PSharedItem DomainCollection::createCollectionItem(const Identifier& identifier)
{
    PSharedItem domain(new Domain(identifier));
    domain->setParent(shared_from_this());
    return domain;
}
//-----------------------------------------------------------------------------
void DomainCollection::loadChildren()
{
    Database* db = getDatabase();
    wxCHECK_RET(db,
        wxT("DomainCollection::loadChildren() called without parent database"));
    DatabaseConnection* dbc = db->getMetadataConnection();
    if (dbc)
    {
        setLoadChildrenState(lcsLoading);
        std::string sql("select f.RDB$FIELD_NAME from RDB$FIELDS f"
            " left outer join RDB$TYPES t on f.RDB$FIELD_TYPE = t.RDB$TYPE"
            " where t.RDB$FIELD_NAME = 'RDB$FIELD_TYPE' order by 1");
        dbc->loadCollection(getHandle(), sql);
        return;
    }

    // loading is not possible, so clear children and show empty collection
    SubjectLocker lock(this);
    clearChildren();
    setLoadChildrenState(lcsLoaded);
}
//-----------------------------------------------------------------------------
void DomainCollection::accept(ItemVisitor* visitor)
{
    wxASSERT(visitor);
    if (visitor)
        visitor->visit(*this);
}
//-----------------------------------------------------------------------------
