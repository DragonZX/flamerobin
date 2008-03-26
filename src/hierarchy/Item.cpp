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

#include <map>
#include <utility>

#include "hierarchy/Item.h"
#include "hierarchy/ItemVisitor.h"
//-----------------------------------------------------------------------------
typedef std::map<Item::Handle, Item*> ItemHandleMap;
typedef std::pair <Item::Handle, Item*> ItemHandlePair;

static Item::Handle nextItemHandle = 0;
static ItemHandleMap itemHandles;
//-----------------------------------------------------------------------------
// Item class
Item::Item()
{
    // starts with handle 1, will not be recycled until wrap-around
    handleM = ++nextItemHandle;
    itemHandles.insert(ItemHandlePair(handleM, this));
}
//-----------------------------------------------------------------------------
Item::~Item()
{
    itemHandles.erase(handleM);
}
//-----------------------------------------------------------------------------
/*static*/
bool Item::findFromHandle(Handle handle, Item** item)
{
    wxASSERT(wxIsMainThread());
    ItemHandleMap::iterator it = itemHandles.find(handle);
    if (it == itemHandles.end())
    {
        *item = 0;
        return false;
    }
    *item = it->second;
    return true;
}
//-----------------------------------------------------------------------------
/*static*/
Item* Item::getFromHandle(Handle handle)
{
    wxASSERT(wxIsMainThread());
    ItemHandleMap::iterator it = itemHandles.find(handle);
    return (it != itemHandles.end()) ? it->second : 0;
}
//-----------------------------------------------------------------------------
PSharedItem Item::getParent() const
{
    return parentM.lock();
}
//-----------------------------------------------------------------------------
void Item::setParent(PSharedItem parent)
{
    PSharedItem oldParent = parentM.lock();
    if (parent != oldParent)
    {
        if (oldParent)
            oldParent->removeChild(shared_from_this());
        parentM = parent;
        if (parent)
        {
            setLockCount(parent->getLockCount());
            parent->addChild(shared_from_this());
        }
    }
}
//-----------------------------------------------------------------------------
Database* Item::getDatabase()
{
    PSharedItem parent = getParent();
    if (parent)
        return parent->getDatabase();
    return 0;
}
//-----------------------------------------------------------------------------
bool Item::hasChildren() const
{
    return getChildrenCount() > 0;
}
//-----------------------------------------------------------------------------
unsigned Item::getChildrenCount() const
{
    return 0;
}
//-----------------------------------------------------------------------------
PSharedItem Item::getChild(unsigned /*index*/) const
{
    // we can only arrive here when the index is invalid, or the class
    // has overridden getChildrenCount() but not getChild()
    wxFAIL_MSG(wxT("Item::getChild()"));
    return PSharedItem();
}
//-----------------------------------------------------------------------------
bool Item::hasChildrenLoaded() const
{
    return true;
}
//-----------------------------------------------------------------------------
void Item::loadChildren()
{
}
//-----------------------------------------------------------------------------
const wxString Item::getName() const
{
    return wxEmptyString;
}
//-----------------------------------------------------------------------------
Item::Handle Item::getHandle() const
{
    return handleM;
}
//-----------------------------------------------------------------------------
const wxString Item::getTypeName() const
{
    return wxEmptyString;
}
//-----------------------------------------------------------------------------
const wxString Item::getItemPath() const
{
    wxString result = getTypeName() + wxT("_") + getPathId();
    if (PSharedItem parent = parentM.lock())
    {
        wxString parentItemPath = parent->getItemPath();
        if (!parentItemPath.empty())
            result = parentItemPath + wxT("/") + result;
    }
    return result;
}
//-----------------------------------------------------------------------------
const wxString Item::getPathId() const
{
    return getId();
}
//-----------------------------------------------------------------------------
const wxString Item::getId() const
{
    return getName();
}
//-----------------------------------------------------------------------------
void Item::refreshData()
{
}
//-----------------------------------------------------------------------------
void Item::accept(ItemVisitor* visitor)
{
    wxASSERT(visitor);
    if (visitor)
        visitor->visit(*this);
}
//-----------------------------------------------------------------------------
// Policy classes
const wxString ItemNameIsString::getNameImpl() const
{
    return nameM;
}
//-----------------------------------------------------------------------------
void ItemNameIsString::setNameImpl(const wxString& name)
{
    nameM = name;
}
//-----------------------------------------------------------------------------
void ItemNameIsIdentifier::setIdentifier(const Identifier& identifier)
{
    identifierM = identifier;
}
//-----------------------------------------------------------------------------
const wxString ItemNameIsIdentifier::getNameImpl() const
{
    return identifierM.get();
}
//-----------------------------------------------------------------------------
bool ItemNameIsIdentifier::isSystem()
{
    return false;
}
//-----------------------------------------------------------------------------
unsigned ItemHasNoChildren::getChildrenCountImpl() const
{
    return 0;
}
//-----------------------------------------------------------------------------
PSharedItem ItemHasNoChildren::getChildImpl(unsigned /*index*/) const
{
    return PSharedItem();
}
//-----------------------------------------------------------------------------
PSharedItem ItemHasNoChildren::getChildImpl(const wxString& /*name*/) const
{
    return PSharedItem();
}
//-----------------------------------------------------------------------------
bool ItemHasNoChildren::hasChildrenLoadedImpl() const
{
    return true;
}
//-----------------------------------------------------------------------------
bool ItemHasNoChildren::addChildImpl(PSharedItem child)
{
    wxFAIL_MSG(wxT("ItemHasNoChildren::addChildImpl()"));
    return false;
}
//-----------------------------------------------------------------------------
bool ItemHasNoChildren::removeChildImpl(PSharedItem child)
{
    wxFAIL_MSG(wxT("ItemHasNoChildren::removeChildImpl()"));
    return false;
}
//-----------------------------------------------------------------------------
void ItemHasNoChildren::lockChildrenImpl()
{
}
//-----------------------------------------------------------------------------
void ItemHasNoChildren::unlockChildrenImpl()
{
}
//-----------------------------------------------------------------------------
ItemHasChildren::ItemHasChildren()
{
    childrenLoadedM = true;
}
//-----------------------------------------------------------------------------
unsigned ItemHasChildren::getChildrenCountImpl() const
{
    return childrenM.size();
}
//-----------------------------------------------------------------------------
PSharedItem ItemHasChildren::getChildImpl(unsigned index) const
{
    // if index is invalid this will return an empty shared_ptr<> in release
    wxCHECK_MSG(index < childrenM.size(), PSharedItem(),
        wxT("ItemHasChildren::getChildImpl()"));
    return childrenM[index];
}
//-----------------------------------------------------------------------------
PSharedItem ItemHasChildren::getChildImpl(const wxString& name) const
{
    for (std::vector<PSharedItem>::const_iterator it = childrenM.begin();
        it != childrenM.end(); ++it)
    {
        if ((*it)->getName().Cmp(name) == 0)
            return *it;
    }
    return PSharedItem();
}
//-----------------------------------------------------------------------------
bool ItemHasChildren::hasChildrenLoadedImpl() const
{
    return childrenLoadedM;
}
//-----------------------------------------------------------------------------
void ItemHasChildren::setChildrenLoaded(bool value)
{
    childrenLoadedM = value;
}
//-----------------------------------------------------------------------------
bool ItemHasChildren::clearChildren()
{
    if (!childrenM.size())
        return false;
    childrenM.clear();
    return true;
}
//-----------------------------------------------------------------------------
bool ItemHasChildren::addChildImpl(PSharedItem child)
{
    std::vector<PSharedItem>::iterator it = std::find(childrenM.begin(),
        childrenM.end(), child);
    wxCHECK_MSG(it == childrenM.end(), false,
        wxT("ItemHasChildren::addChildImpl()"));
    childrenM.push_back(child);
    return true;
}
//-----------------------------------------------------------------------------
bool ItemHasChildren::removeChildImpl(PSharedItem child)
{
    std::vector<PSharedItem>::iterator it = std::find(childrenM.begin(),
        childrenM.end(), child);
    wxCHECK_MSG(it != childrenM.end(), false,
        wxT("ItemHasChildren::removeChildImpl()"));
    childrenM.erase(it);
    return true;
}
//-----------------------------------------------------------------------------
void ItemHasChildren::lockChildrenImpl()
{
    std::vector<PSharedItem>::iterator it;
    for (it = childrenM.begin(); it != childrenM.end(); ++it)
        (*it)->lockSubject();
}
//-----------------------------------------------------------------------------
void ItemHasChildren::unlockChildrenImpl()
{
    std::vector<PSharedItem>::iterator it;
    for (it = childrenM.begin(); it != childrenM.end(); ++it)
        (*it)->unlockSubject();
}
//-----------------------------------------------------------------------------
