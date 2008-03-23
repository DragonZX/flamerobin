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

#ifndef FR_ITEM_H
#define FR_ITEM_H
//-----------------------------------------------------------------------------
#include <wx/wx.h>

#include <vector>
#include <boost/enable_shared_from_this.hpp>
#include <boost/weak_ptr.hpp>

#include "core/Subject.h"
#include "hierarchy/SharedItems.h"
#include "sql/Identifier.h"
//-----------------------------------------------------------------------------
class ItemVisitor;
//-----------------------------------------------------------------------------
// Item class is the base class for the hierarchy
// Since we have hierarchy items which are not metadata items (folders,
// service manager nodes, even databases) we limit the public interface to the
// absolutely necessary stuff for describing the tree structure and for
// visualizing the items in a tree control
class Item : public Subject, public boost::enable_shared_from_this<Item>
{
public:
    typedef unsigned Handle;
    static bool findFromHandle(Handle handle, Item** item);
    static Item* getFromHandle(Handle handle);
public:
    ~Item();

    PSharedItem getParent() const;
    void setParent(PSharedItem parent);

    virtual Database* getDatabase();

    // access to child items (Composite pattern)
    virtual bool hasChildren() const;
    virtual unsigned getChildrenCount() const = 0;
    virtual PSharedItem getChild(unsigned index) const = 0;
    virtual bool hasChildrenLoaded() const = 0;
    virtual void loadChildren();

    // returns the name of the item
    virtual const wxString getName() const = 0;

    // returns a unique handle for safe runtime references to the item
    Handle getHandle() const;
    // returns the name of the data type (like TABLE)
    virtual const wxString getTypeName() const;
    // returns the item path, used to store settings in config() and
    // to locate items in the DBH tree.
    virtual const wxString getItemPath() const;
    // returns the id wxString of the item that contributes to the path.
    // The predefined implementation just returns getId().
    virtual const wxString getPathId() const;
    // returns the id of the item (to be saved in config files, etc.).
    // The predefined implementation just returns getName().
    virtual const wxString getId() const;

    // reloads (meta-)data from database
    virtual void refreshData();

    // GoF Visitor pattern: Item is a Visitable
    virtual void accept(ItemVisitor* visitor);
protected:
    Item();

    virtual bool addChild(PSharedItem child) = 0;
    virtual bool removeChild(PSharedItem child) = 0;
private:
    Handle handleM;
    boost::weak_ptr<Item> parentM;
};
//-----------------------------------------------------------------------------
template <
    class ItemHasChildrenPolicy,
    class ItemHasIdentifierPolicy
>
class ItemTemplate : public Item,
    // policy classes
    public ItemHasChildrenPolicy, public ItemHasIdentifierPolicy
{
protected:
    bool addChild(PSharedItem child)
    {
        if (!ItemHasChildrenPolicy::addChildImpl(child))
            return false;
        notifyObservers();
        return true;
    }
    bool removeChild(PSharedItem child)
    {
        if (!ItemHasChildrenPolicy::removeChildImpl(child))
            return false;
        notifyObservers();
        return true;
    }
public:
    virtual void lockSubject()
    {
        Subject::lockSubject();
        ItemHasChildrenPolicy::lockChildrenImpl();
    };
    virtual void unlockSubject()
    {
        Subject::unlockSubject();
        // important: unlock children *after* the parent, because above line
        // could change the list of children
        ItemHasChildrenPolicy::unlockChildrenImpl();
    };

    virtual unsigned getChildrenCount() const
    {
        return ItemHasChildrenPolicy::getChildrenCountImpl();
    };
    virtual PSharedItem getChild(unsigned index) const
    {
        return ItemHasChildrenPolicy::getChildImpl(index);
    };
    virtual PSharedItem getChild(const wxString& name) const
    {
        return ItemHasChildrenPolicy::getChildImpl(name);
    };
    virtual bool hasChildrenLoaded() const
    {
        return ItemHasChildrenPolicy::hasChildrenLoadedImpl();
    };

    virtual const wxString getName() const
        { return ItemHasIdentifierPolicy::getNameImpl(); };
};
//-----------------------------------------------------------------------------
// Policy classes for item name
class ItemNameIsString
{
protected:
    const wxString getNameImpl() const;
    void setNameImpl(const wxString& name);
private:
    wxString nameM;
};
//-----------------------------------------------------------------------------
class ItemNameIsIdentifier
{
public:
    virtual bool isSystem();
protected:
    const wxString getNameImpl() const;
    void setIdentifier(const Identifier& identifier);
private:
    Identifier identifierM;
};
//-----------------------------------------------------------------------------
// Policy classes for item children
class ItemHasNoChildren
{
protected:
    unsigned getChildrenCountImpl() const;
    PSharedItem getChildImpl(unsigned index) const;
    PSharedItem getChildImpl(const wxString& name) const;
    bool hasChildrenLoadedImpl() const;

    bool addChildImpl(PSharedItem child);
    bool removeChildImpl(PSharedItem child);

    void lockChildrenImpl();
    void unlockChildrenImpl();
};
//-----------------------------------------------------------------------------
class ItemHasChildren
{
public:
    bool clearChildren();
protected:
    ItemHasChildren();

    unsigned getChildrenCountImpl() const;
    PSharedItem getChildImpl(unsigned index) const;
    PSharedItem getChildImpl(const wxString& name) const;
    bool hasChildrenLoadedImpl() const;
    void setChildrenLoaded(bool value);

    bool addChildImpl(PSharedItem child);
    bool removeChildImpl(PSharedItem child);

    void lockChildrenImpl();
    void unlockChildrenImpl();
private:
    std::vector<PSharedItem> childrenM;
    bool childrenLoadedM;
};
//-----------------------------------------------------------------------------
// a base class for folders, databases and servers
typedef ItemTemplate<ItemHasChildren, ItemNameIsString> ItemWithChildrenBase;
// a base class for metadata objects without children
typedef ItemTemplate<ItemHasNoChildren, ItemNameIsIdentifier> MetadataItemBase;
// a base class for metadata objects with children
typedef ItemTemplate<ItemHasChildren, ItemNameIsIdentifier> MetadataItemWithChildrenBase;
//-----------------------------------------------------------------------------
#endif // FR_ITEM_H
