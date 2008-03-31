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

#ifndef FR_COLUMN_H
#define FR_COLUMN_H
//-----------------------------------------------------------------------------
#include "hierarchy/Item.h"

class ColumnCollection;
class Domain;
//-----------------------------------------------------------------------------
class Column : public MetadataItemBase
{
private:
    bool notNullM;
    Identifier domainNameM;
    wxString collationNameM;
    wxString computedSourceM;
    wxString defaultSourceM;
    bool defaultSourceIsNullM;

    void setData(bool notNull, const wxString& fieldSource,
        const wxString& collationName, const wxString& computedSource,
        const wxString& defaultSource, bool defaultSourceIsNull);
public:
    friend class ColumnCollection;

    Column(const Identifier& identifier);

    virtual const wxString getTypeName() const;

    wxString getDatatypeAsString();
    Domain* getDomain();
    bool isNullable();

    virtual void accept(ItemVisitor* visitor);
};
//-----------------------------------------------------------------------------
class ColumnCollection: public MetadataItemCollection
{
protected:
    virtual PSharedItem createCollectionItem(const Identifier& identifier);
    virtual void setCollectionItemData(PSharedItem item,
        const VectorOfAny& data);
public:
    virtual void loadChildren();
    virtual void accept(ItemVisitor* visitor);
};
//-----------------------------------------------------------------------------
#endif // FR_COLUMN_H
