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

#include <list>
#include <map>
#include <vector>
#include <boost/any.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/weak_ptr.hpp>

#include "core/Subject.h"
#include "hierarchy/SharedItems.h"
#include "sql/Identifier.h"
//-----------------------------------------------------------------------------
class ItemVisitor;
class Relation;
//-----------------------------------------------------------------------------
typedef std::vector<boost::any> VectorOfAny;
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

    SharedItem getParent() const;
    void setParent(SharedItem parent);

    virtual Database* getDatabase();
    virtual Relation* getRelation();

    // access to child items (Composite pattern)
    virtual bool containsChild(SharedItem item) const = 0;
    virtual bool hasChildren() const;
    virtual unsigned getChildrenCount() const = 0;
    virtual SharedItem getChild(unsigned index) const = 0;

    enum LoadChildrenState { lcsNotLoaded, lcsLoading, lcsLoaded };
    virtual LoadChildrenState getLoadChildrenState() const = 0;
    virtual void setLoadChildrenState(Item::LoadChildrenState state) = 0;
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

    virtual bool addChild(SharedItem child) = 0;
    virtual bool removeChild(SharedItem child) = 0;
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
    bool addChild(SharedItem child)
    {
        if (!ItemHasChildrenPolicy::addChildImpl(child))
            return false;
        notifyObservers();
        return true;
    }
    bool removeChild(SharedItem child)
    {
        if (!ItemHasChildrenPolicy::removeChildImpl(child))
            return false;
        notifyObservers();
        return true;
    }
    void setLoadChildrenState(Item::LoadChildrenState state)
    {
        if (ItemHasChildrenPolicy::getLoadChildrenStateImpl() != state)
        {
            ItemHasChildrenPolicy::setLoadChildrenStateImpl(state);
            notifyObservers();
        }
    };
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

    virtual bool containsChild(SharedItem child) const
        { return ItemHasChildrenPolicy::containsChildImpl(child); };

    virtual unsigned getChildrenCount() const
        { return ItemHasChildrenPolicy::getChildrenCountImpl(); };

    virtual SharedItem getChild(unsigned index) const
        { return ItemHasChildrenPolicy::getChildImpl(index); };

    virtual SharedItem getChild(const wxString& name) const
        { return ItemHasChildrenPolicy::getChildImpl(name); };

    virtual LoadChildrenState getLoadChildrenState() const
        { return ItemHasChildrenPolicy::getLoadChildrenStateImpl(); };

    virtual const wxString getName() const
        { return ItemHasIdentifierPolicy::getNameImpl(); };

    virtual void refreshData()
    {
        setLoadChildrenState(Item::lcsNotLoaded);
    }
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
    const Identifier& getIdentifier();
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
    bool containsChildImpl(SharedItem child) const;
    unsigned getChildrenCountImpl() const;
    SharedItem getChildImpl(unsigned index) const;
    SharedItem getChildImpl(const wxString& name) const;
    Item::LoadChildrenState getLoadChildrenStateImpl() const;
    void setLoadChildrenStateImpl(Item::LoadChildrenState state);

    bool addChildImpl(SharedItem child);
    bool removeChildImpl(SharedItem child);

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

    bool containsChildImpl(SharedItem child) const;
    unsigned getChildrenCountImpl() const;
    SharedItem getChildImpl(unsigned index) const;
    SharedItem getChildImpl(const wxString& name) const;
    Item::LoadChildrenState getLoadChildrenStateImpl() const;
    void setLoadChildrenStateImpl(Item::LoadChildrenState state);

    bool addChildImpl(SharedItem child);
    bool removeChildImpl(SharedItem child);

    void lockChildrenImpl();
    void unlockChildrenImpl();
private:
    std::vector<SharedItem> childrenM;
    Item::LoadChildrenState loadChildrenStateM;
};
//-----------------------------------------------------------------------------
// a base class for folders, databases and servers
typedef ItemTemplate<ItemHasChildren, ItemNameIsString> ItemWithChildrenBase;
// a base class for metadata objects without children
typedef ItemTemplate<ItemHasNoChildren, ItemNameIsIdentifier> MetadataItemBase;
// a base class for metadata objects with children
typedef ItemTemplate<ItemHasChildren, ItemNameIsIdentifier> MetadataItemWithChildrenBase;
//-----------------------------------------------------------------------------
class MetadataItemCollection: public ItemWithChildrenBase
{
public:
    typedef struct IdentifierAndData {
        Identifier identifier;
        VectorOfAny data;
    };
protected:
    virtual SharedItem createCollectionItem(const Identifier& identifier) = 0;
    virtual void setCollectionItemData(SharedItem item,
        const VectorOfAny& data);
    void setLoadedWithoutChildren();
public:
    void setChildrenIdentifiers(const std::list<Identifier>& identifiers);
    void setChildrenIdentifiersData(
        const std::list<IdentifierAndData>& identAndData);
};
//-----------------------------------------------------------------------------
#endif // FR_ITEM_H
