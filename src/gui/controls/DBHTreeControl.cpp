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

#include <wx/dnd.h>
#include <wx/imaglist.h>

#include <algorithm>
#include <map>
#include <vector>

#include "core/ArtProvider.h"
#include "core/CommandIds.h"

#include "gui/controls/DBHTreeControl.h"
#include "gui/controls/DBHTreeControlContextMenuCreator.h"

#include "hierarchy/Database.h"
#include "hierarchy/ItemVisitor.h"
#include "hierarchy/Table.h"
#include "hierarchy/TreeFolder.h"
#include "hierarchy/TreeRoot.h"
#include "hierarchy/View.h"
//-----------------------------------------------------------------------------
// DBHTreeImageList class
class DBHTreeImageList: public wxImageList
{
private:
    std::map<wxArtID, int> artIdIndicesM;
    void addImage(const wxArtID& art);
public:
    DBHTreeImageList();

    static DBHTreeImageList& get();
    int getImageIndex(const wxArtID& id);
//    int getImageIndex(NodeType type);
};
//-----------------------------------------------------------------------------
DBHTreeImageList::DBHTreeImageList()
    : wxImageList(16, 16)
{
    addImage(wxART_FOLDER);
    addImage(ART_Object);
    addImage(ART_Column);
    addImage(ART_Computed);
    addImage(ART_DatabaseConnected);
    addImage(ART_DatabaseDisconnected);
    addImage(ART_Domain);
    addImage(ART_Domains);
    addImage(ART_Exception);
    addImage(ART_Exceptions);
    addImage(ART_ForeignKey);
    addImage(ART_Function);
    addImage(ART_Functions);
    addImage(ART_Generator);
    addImage(ART_Generators);
    addImage(ART_ParameterInput);
    addImage(ART_ParameterOutput);
    addImage(ART_PrimaryAndForeignKey);
    addImage(ART_PrimaryKey);
    addImage(ART_Procedure);
    addImage(ART_Procedures);
    addImage(ART_Role);
    addImage(ART_Roles);
    addImage(ART_Root);
    addImage(ART_Server);
    addImage(ART_SystemTable);
    addImage(ART_SystemTables);
    addImage(ART_Table);
    addImage(ART_Tables);
    addImage(ART_Trigger);
    addImage(ART_Triggers);
    addImage(ART_View);
    addImage(ART_Views);
}
//-----------------------------------------------------------------------------
/*static*/ DBHTreeImageList& DBHTreeImageList::get()
{
    static DBHTreeImageList til;
    return til;
}
//-----------------------------------------------------------------------------
void DBHTreeImageList::addImage(const wxArtID& art)
{
    wxBitmap bmp(wxArtProvider::GetBitmap(art, wxART_OTHER, wxSize(16, 16)));
    if (!bmp.Ok())
        return;
    wxIcon icon;
    icon.CopyFromBitmap(bmp);
    artIdIndicesM[art] = Add(icon);
}
//-----------------------------------------------------------------------------
int DBHTreeImageList::getImageIndex(const wxArtID& id)
{
    std::map<wxArtID, int>::const_iterator it = artIdIndicesM.find(id);
    if (it != artIdIndicesM.end())
        return (*it).second;
    return -1;
}
//-----------------------------------------------------------------------------
// DBHItemTreeNodeProperties class
class DBHItemTreeNodeProperties : public ItemVisitor
{
public:
    DBHItemTreeNodeProperties(DBHTreeControl& tree);

    bool hasLoadedChildren() { return childrenLoadedM; };
    bool isVisible() { return visibleM; };
    void updateTreeItem(const wxTreeItemId id);

    virtual void visit(Database& database);
    virtual void visit(Item& item) { visitItem(&item); };
    virtual void visit(SystemTableCollection& tables);
    virtual void visit(Table& table);
    virtual void visit(TableCollection& tables);
    virtual void visit(TreeFolder& folder);
    virtual void visit(View& view);
    virtual void visit(ViewCollection& views);
private:
    DBHTreeControl& treeM;

    bool visibleM;
    bool captionIsBoldM;
    wxString captionM;
    int imageIndexM;
    bool childrenLoadedM;

    void visitCollection(Item* item, const wxString& caption, int imageIndex);
    void visitItem(Item* item);
    void reset();
};
//-----------------------------------------------------------------------------
DBHItemTreeNodeProperties::DBHItemTreeNodeProperties(DBHTreeControl& tree)
    : treeM(tree)
{
    reset();
}
//-----------------------------------------------------------------------------
void DBHItemTreeNodeProperties::visitCollection(Item* item,
    const wxString& caption, int imageIndex)
{
    wxASSERT(item);
    visibleM = true;
    unsigned n = item->getChildrenCount();
    captionIsBoldM = n > 0;
    captionM = (n) ? caption + wxString::Format(wxT(" (%u)"), n) : caption;
    imageIndexM = imageIndex;
    childrenLoadedM = item->hasChildrenLoaded();
}
//-----------------------------------------------------------------------------
void DBHItemTreeNodeProperties::visitItem(Item* item)
{
    wxASSERT(item);
    visibleM = true;
    captionIsBoldM = item->hasChildren();
    captionM = item->getName();
    imageIndexM = -1;
    childrenLoadedM = item->hasChildrenLoaded();
}
//-----------------------------------------------------------------------------
void DBHItemTreeNodeProperties::reset()
{
    visibleM = false;
    captionIsBoldM = false;
    captionM.clear();
    imageIndexM = -1;
    childrenLoadedM = false;
}
//-----------------------------------------------------------------------------
void DBHItemTreeNodeProperties::updateTreeItem(wxTreeItemId id)
{
    // update tree node caption without flicker
    if (treeM.GetItemText(id) != captionM)
        treeM.SetItemText(id, captionM);
    if (treeM.IsBold(id) != captionIsBoldM)
        treeM.SetItemBold(id, captionIsBoldM);

    // update tree node image index without flicker
    if (treeM.GetItemImage(id) != imageIndexM)
        treeM.SetItemImage(id, imageIndexM);
}
//-----------------------------------------------------------------------------
void DBHItemTreeNodeProperties::visit(Database& database)
{
    visibleM = true;
    captionIsBoldM = database.isConnected();
    captionM = database.getName();
    if (database.getConnectionState() == Database::csConnecting)
        captionM += wxT(" (connecting...)");
    if (database.getConnectionState() == Database::csDisconnecting)
        captionM += wxT(" (disconnecting...)");
    wxArtID id = (database.isConnected() ?
        ART_DatabaseConnected : ART_DatabaseDisconnected);
    imageIndexM = DBHTreeImageList::get().getImageIndex(id);
    childrenLoadedM = true;
}
//-----------------------------------------------------------------------------
void DBHItemTreeNodeProperties::visit(SystemTableCollection& tables)
{
    int img = DBHTreeImageList::get().getImageIndex(ART_SystemTables);
    visitCollection(&tables, _("System Tables"), img);
}
//-----------------------------------------------------------------------------
void DBHItemTreeNodeProperties::visit(Table& table)
{
    visitItem(&table);
    imageIndexM = DBHTreeImageList::get().getImageIndex(
        table.isSystem() ? ART_SystemTable : ART_Table);
}
//-----------------------------------------------------------------------------
void DBHItemTreeNodeProperties::visit(TableCollection& tables)
{
    int img = DBHTreeImageList::get().getImageIndex(ART_Tables);
    visitCollection(&tables, _("Tables"), img);
}
//-----------------------------------------------------------------------------
void DBHItemTreeNodeProperties::visit(TreeFolder& folder)
{
    visitItem(&folder);
    // even empty folder nodes should have a bold caption
    captionIsBoldM = true;
    imageIndexM = DBHTreeImageList::get().getImageIndex(wxART_FOLDER);
}
//-----------------------------------------------------------------------------
void DBHItemTreeNodeProperties::visit(View& view)
{
    visitItem(&view);
    imageIndexM = DBHTreeImageList::get().getImageIndex(ART_View);
}
//-----------------------------------------------------------------------------
void DBHItemTreeNodeProperties::visit(ViewCollection& views)
{
    int img = DBHTreeImageList::get().getImageIndex(ART_Views);
    visitCollection(&views, _("Views"), img);
}
//-----------------------------------------------------------------------------
// DBHTreeNode class
class DBHTreeNode : public wxTreeItemData, public Observer
{
public:
    DBHTreeNode(DBHTreeControl& tree);

    static inline DBHTreeNode* getFromTreeData(wxTreeItemData* data);

    bool hasLoadedChildren();
    bool getExpandOnUpdate();
    void setExpandOnUpdate(bool expand);

    PSharedItem getItem();
    void setItem(PSharedItem item);
    virtual void update();
private:
    DBHTreeControl& treeM;
    PSharedItem itemM;
    bool expandOnUpdateM;
    wxTreeItemId findChildIdForItem(PSharedItem item);
};
//-----------------------------------------------------------------------------
DBHTreeNode::DBHTreeNode(DBHTreeControl& tree)
    : treeM(tree), expandOnUpdateM(false)
{
}
//-----------------------------------------------------------------------------
/*static*/
DBHTreeNode* DBHTreeNode::getFromTreeData(wxTreeItemData* data)
{
    return (data) ? dynamic_cast<DBHTreeNode*>(data) : 0;
}
//-----------------------------------------------------------------------------
bool DBHTreeNode::hasLoadedChildren()
{
    return itemM && itemM->hasChildrenLoaded();
}
//-----------------------------------------------------------------------------
bool DBHTreeNode::getExpandOnUpdate()
{
    return expandOnUpdateM;
}
//-----------------------------------------------------------------------------
void DBHTreeNode::setExpandOnUpdate(bool expand)
{
    expandOnUpdateM = expand;
}
//-----------------------------------------------------------------------------
PSharedItem DBHTreeNode::getItem()
{
    return itemM;
}
//-----------------------------------------------------------------------------
wxTreeItemId DBHTreeNode::findChildIdForItem(PSharedItem item)
{
    wxTreeItemIdValue cookie;
    wxTreeItemId id = GetId();
    wxTreeItemId childId = treeM.GetFirstChild(id, cookie);
    while (childId.IsOk())
    {
        PSharedItem childItem = treeM.getItemFromId(childId);
        if (childItem == item)
            return childId;
        childId = treeM.GetNextChild(id, cookie);
    }
    return wxTreeItemId();
}
//-----------------------------------------------------------------------------
void DBHTreeNode::setItem(PSharedItem item)
{
    if (itemM != item)
    {
        if (itemM)
            itemM->detachObserver(this);
        itemM = item;
        if (itemM)
            itemM->attachObserver(this);
    }
}
//-----------------------------------------------------------------------------
void DBHTreeNode::update()
{
    wxTreeItemId id = GetId();
    if (!id.IsOk())
        return;
    wxCHECK_RET(itemM, wxT("Item is 0 in DBHTreeNode::update()"));

    DBHItemTreeNodeProperties nodeProps(treeM);
    itemM->accept(&nodeProps);
    // remove the node and its children if it's not visible in the tree
    if (!nodeProps.isVisible())
    {
        treeM.Delete(id);
        return;
    }
    nodeProps.updateTreeItem(id);

    // show [+] if node is collapsed but could have children
    // for implementation see also EVT_TREE_ITEM_EXPANDING event handler
    if (!nodeProps.hasLoadedChildren())
    {
        treeM.Collapse(id);
        treeM.SetItemHasChildren(id);
        return;
    }

    // add missing and update existing child nodes
    wxTreeItemId prevChildId;
    for (unsigned i = 0; i < itemM->getChildrenCount(); ++i)
    {
        PSharedItem childItem = itemM->getChild(i);
        if (!childItem)
            continue;

        DBHItemTreeNodeProperties childProps(treeM);
        childItem->accept(&childProps);

        // skip children that are not visible in the tree
        if (!childProps.isVisible())
            continue;

        wxTreeItemId childItemId = findChildIdForItem(childItem);
        if (!childItemId.IsOk())
        {
            DBHTreeNode* nodeData = new DBHTreeNode(treeM);
            if (prevChildId.IsOk())
                prevChildId = treeM.InsertItem(id, prevChildId, wxEmptyString);
            else
                prevChildId = treeM.PrependItem(id, wxEmptyString);
            treeM.SetItemData(prevChildId, nodeData);
            // this will call update()
            nodeData->setItem(childItem);
        }
        else
        {
            prevChildId = childItemId;
            childProps.updateTreeItem(childItemId);
        }
    }

    // remove all child nodes if item has no children at all
    if (itemM->getChildrenCount() == 0 && treeM.GetChildrenCount(id, false))
        treeM.CollapseAndReset(id);

    // remove any child nodes that have no corresponding item
    if (itemM->getChildrenCount())
    {
        // TODO: find orphaned child nodes and delete them
    }

    // show the [+] marker when there are (or could be) children
    treeM.SetItemHasChildren(id,
        itemM->hasChildren() || !itemM->hasChildrenLoaded());

    // expand tree node after background data loading
    if (getExpandOnUpdate())
    {
        if (itemM->getChildrenCount())
            treeM.Expand(id);
        setExpandOnUpdate(false);
    }
}
//-----------------------------------------------------------------------------
// DBHTreeControl class
const long DBHTCStyle = wxTR_DEFAULT_STYLE
#if defined __WXGTK20__ || defined __WXMAC__
    | wxTR_NO_LINES
#endif
    | wxTR_HIDE_ROOT | wxTR_HAS_BUTTONS;

DBHTreeControl::DBHTreeControl(wxWindow* parent, wxWindowID id)
    : wxTreeCtrl(parent, id, wxDefaultPosition, wxDefaultSize, DBHTCStyle)
{
    hiddenRootNodeM = AddRoot(wxT("hidden"));
    SetImageList(&DBHTreeImageList::get());

    // this looks much better than event tables...
    Connect(wxEVT_COMMAND_TREE_BEGIN_DRAG,
        wxTreeEventHandler(DBHTreeControl::OnBeginDrag));
    Connect(wxEVT_CONTEXT_MENU,
        wxContextMenuEventHandler(DBHTreeControl::OnContextMenu));
    Connect(wxEVT_COMMAND_TREE_ITEM_ACTIVATED,
        wxTreeEventHandler(DBHTreeControl::OnTreeItemActivated));
    Connect(wxEVT_COMMAND_TREE_ITEM_EXPANDING,
        wxTreeEventHandler(DBHTreeControl::OnTreeItemExpanding));
}
//-----------------------------------------------------------------------------
void DBHTreeControl::createRootNode(PSharedItem rootItem)
{
    wxCHECK_RET(rootItem,
        wxT("rootItem is 0 in DBHTreeControl::createRootNode()"));

    DBHTreeNode* nodeData = new DBHTreeNode(*this);
    wxTreeItemId id = AppendItem(hiddenRootNodeM, wxEmptyString, -1, -1,
        nodeData);
    nodeData->setItem(rootItem);
}
//-----------------------------------------------------------------------------
PSharedItem DBHTreeControl::getItemFromId(wxTreeItemId id)
{
    if (id.IsOk())
    {
        DBHTreeNode* childNodeData = DBHTreeNode::getFromTreeData(
            GetItemData(id));
        if (childNodeData)
            return childNodeData->getItem();
    }
    return PSharedItem();
}
//-----------------------------------------------------------------------------
// event handlers
void DBHTreeControl::OnBeginDrag(wxTreeEvent& event)
{
    wxTreeItemId id = event.GetItem();
    PSharedItem dragItem = getItemFromId(id);
    if (!dragItem)
    {
        event.Skip();
        return;
    }
    // necessary for MSW, when different node is selected
    SelectItem(id);

    wxString test(dragItem->getItemPath());
    wxTextDataObject textData(test);
    wxDropSource source(textData, this);
    source.DoDragDrop(wxDrag_AllowMove);
}
//-----------------------------------------------------------------------------
void DBHTreeControl::OnContextMenu(wxContextMenuEvent& event)
{
    wxPoint pos(event.GetPosition());
    // for MSW: the menu key will show the popup of the selected item
    bool useSelected = (pos == wxDefaultPosition);
    if (pos != wxDefaultPosition)
        pos = ScreenToClient(pos);

    wxTreeItemId id(GetSelection());
    // if event is initiated by mouse click, then get item under mouse
    // instead of currently selected or focused item
    // this way pressing ESC will revert to the old selection
    if (!useSelected)
    {
        int hitFlags;
        id = HitTest(pos, hitFlags);
    }

    Item* item = 0;
    if (id.IsOk())
    {
        DBHTreeNode* nodeData = DBHTreeNode::getFromTreeData(GetItemData(id));
        if (nodeData)
            item = nodeData->getItem().get();
    }

    // compute the menu coordinates if the event does not contain them
    if (useSelected && item)
    {
        wxRect rc;
        GetBoundingRect(id, rc, true);
        pos = wxPoint(rc.GetLeft(), rc.GetTop() + rc.GetHeight() / 2);
    }

    wxMenu menu;
    DBHTreeControlContextMenuCreator cmc(menu);
    if (item)
        item->accept(&cmc);
    else
        TreeRoot::get()->accept(&cmc);
    PopupMenu(&menu, pos);
}
//-----------------------------------------------------------------------------
void DBHTreeControl::OnTreeItemActivated(wxTreeEvent& event)
{
    wxCommandEvent ev(wxEVT_COMMAND_MENU_SELECTED, CmdObject_DefaultAction);
    AddPendingEvent(ev);

    // TODO: remove this, it's only for testing...
    wxTreeItemId id(event.GetItem());
    DBHTreeNode* nodeData = DBHTreeNode::getFromTreeData(GetItemData(id));
    Database* database = 0;
    if (nodeData)
        database = dynamic_cast<Database*>(nodeData->getItem().get());

    if (database)
    {
        if (database->isDisconnected())
            database->connect();
        else
            database->disconnect();
    }
}
//-----------------------------------------------------------------------------
void DBHTreeControl::OnTreeItemExpanding(wxTreeEvent& event)
{
    wxTreeItemId id(event.GetItem());
    DBHTreeNode* nodeData = DBHTreeNode::getFromTreeData(GetItemData(id));
    if (nodeData)
    {
        PSharedItem item = nodeData->getItem();
        // there maybe child nodes that have not been created yet
        if (item && !nodeData->hasLoadedChildren())
        {
            SetItemText(id, GetItemText(id) + _(" (expanding...)"));
            SetItemHasChildren(id, false);
            nodeData->setExpandOnUpdate(true);
            item->loadChildren();
        }
    }
}
//-----------------------------------------------------------------------------
