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
#include <boost/shared_ptr.hpp>

#include "config/Config.h"

#include "commands/ItemCommands.h"

#include "core/ArtProvider.h"
#include "core/CommandIds.h"

#include "gui/controls/DBHTreeControl.h"

#include "hierarchy/Column.h"
#include "hierarchy/Database.h"
#include "hierarchy/Domain.h"
#include "hierarchy/Exception.h"
#include "hierarchy/Function.h"
#include "hierarchy/Generator.h"
#include "hierarchy/ItemVisitor.h"
#include "hierarchy/Procedure.h"
#include "hierarchy/Table.h"
#include "hierarchy/TreeFolder.h"
#include "hierarchy/TreeRoot.h"
#include "hierarchy/Trigger.h"
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
};
//-----------------------------------------------------------------------------
DBHTreeImageList::DBHTreeImageList()
    : wxImageList(16, 16)
{
    addImage(wxART_FOLDER);
    addImage(ART_Object);
    addImage(ART_Columns);
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
    {
        bmp = wxArtProvider::GetBitmap(wxART_MISSING_IMAGE, wxART_OTHER,
           wxSize(16, 16));
    }
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
// DBHTreeConfigCache: class to cache config data for tree control behaviour
class DBHTreeConfigCache: public ConfigCache
{
private:
    bool allowDragM;
    bool hideDisconnectedDatabasesM;
    bool showColumnsM;
protected:
    virtual void loadFromConfig();
public:
    DBHTreeConfigCache();
    
    static DBHTreeConfigCache& get();

    bool allowDnD();
    bool getHideDisconnectedDatabases();
    bool getShowColumns();
};
//----------------------------------------------------------------------------
DBHTreeConfigCache::DBHTreeConfigCache()
    : ConfigCache(config())
{
}
//-----------------------------------------------------------------------------
DBHTreeConfigCache& DBHTreeConfigCache::get()
{
    static DBHTreeConfigCache dndc;
    return dndc;
}
//-----------------------------------------------------------------------------
void DBHTreeConfigCache::loadFromConfig()
{
    allowDragM = config().get(wxT("allowDragAndDrop"), false);
    hideDisconnectedDatabasesM = config().get(wxT("HideDisconnectedDatabases"),
        false);
    showColumnsM = config().get(wxT("ShowColumnsInTree"), true);
}
//----------------------------------------------------------------------------
bool DBHTreeConfigCache::allowDnD()
{
    ensureCacheValid();
    return allowDragM;
}
//-----------------------------------------------------------------------------
bool DBHTreeConfigCache::getHideDisconnectedDatabases()
{
    ensureCacheValid();
    return hideDisconnectedDatabasesM;
}
//-----------------------------------------------------------------------------
bool DBHTreeConfigCache::getShowColumns()
{
    ensureCacheValid();
    return showColumnsM;
}
//-----------------------------------------------------------------------------
// DBHItemTreeNodeProperties class
class DBHItemTreeNodeProperties : public ItemVisitor
{
public:
    DBHItemTreeNodeProperties(DBHTreeControl& tree);

    bool getSortChildren() { return sortChildrenM; };
    bool hasNotLoadedChildren() { return childrenNotLoadedM; };
    bool isVisible() { return visibleM; };
    void updateTreeItem(const wxTreeItemId id);

    virtual void visit(Column& column);
    virtual void visit(ColumnCollection& columns);
    virtual void visit(Database& database);
    virtual void visit(Domain& domain);
    virtual void visit(DomainCollection& domains);
    virtual void visit(Exception& exception);
    virtual void visit(ExceptionCollection& exceptions);
    virtual void visit(Function& function);
    virtual void visit(FunctionCollection& functions);
    virtual void visit(Generator& generator);
    virtual void visit(GeneratorCollection& generators);
    virtual void visit(Item& item) { visitItem(&item); };
    virtual void visit(Procedure& procedure);
    virtual void visit(ProcedureCollection& procedures);
    virtual void visit(SystemTableCollection& tables);
    virtual void visit(Table& table);
    virtual void visit(TableCollection& tables);
    virtual void visit(TreeFolder& folder);
    virtual void visit(Trigger& trigger);
    virtual void visit(TriggerCollection& triggers);
    virtual void visit(View& view);
    virtual void visit(ViewCollection& views);
private:
    DBHTreeControl& treeM;

    bool visibleM;
    bool captionIsBoldM;
    wxString captionM;
    int imageIndexM;
    bool childrenNotLoadedM;
    bool sortChildrenM;

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
    Item::LoadChildrenState state = item->getLoadChildrenState();
    captionIsBoldM = n > 0;
    captionM = caption;
    if (state == Item::lcsLoading)
        captionM = captionM + wxT(" ") + _("(expanding...)");
    else if (n > 0)
        captionM = caption + wxString::Format(wxT(" (%u)"), n);
    imageIndexM = imageIndex;
    childrenNotLoadedM = (state == Item::lcsNotLoaded);
}
//-----------------------------------------------------------------------------
void DBHItemTreeNodeProperties::visitItem(Item* item)
{
    wxASSERT(item);
    Item::LoadChildrenState state = item->getLoadChildrenState();
    visibleM = true;
    captionIsBoldM = item->hasChildren();
    if (state == Item::lcsLoading)
        captionM = captionM + wxT(" ") + _("(expanding...)");
    else
        captionM = item->getName();
    imageIndexM = -1;
    childrenNotLoadedM = (state == Item::lcsNotLoaded);
}
//-----------------------------------------------------------------------------
void DBHItemTreeNodeProperties::reset()
{
    visibleM = false;
    captionIsBoldM = false;
    captionM.clear();
    imageIndexM = -1;
    childrenNotLoadedM = true;
    sortChildrenM = false;
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
void DBHItemTreeNodeProperties::visit(Column& column)
{
    visitItem(&column);
    captionM = captionM + wxT(" ") + column.getDatatypeAsString();
    if (!column.isNullable())
// TODO: use "not null" or "NOT NULL" depending on user setting for keywords
        captionM = captionM + wxT(" not null");
    imageIndexM = DBHTreeImageList::get().getImageIndex(ART_Column);
}
//-----------------------------------------------------------------------------
void DBHItemTreeNodeProperties::visit(ColumnCollection& columns)
{
    int img = DBHTreeImageList::get().getImageIndex(ART_Columns);
    visitCollection(&columns, _("Columns"), img);
}
//-----------------------------------------------------------------------------
void DBHItemTreeNodeProperties::visit(Database& database)
{
    // hide disconnected databases
    visibleM = database.isConnected()
        || !DBHTreeConfigCache::get().getHideDisconnectedDatabases();
    if (!visibleM)
        return;

    captionIsBoldM = database.isConnected();
    captionM = database.getName();
    if (database.getConnectionState() == Database::csConnecting)
        captionM = captionM + wxT(" ") + _("(connecting...)");
    if (database.getConnectionState() == Database::csDisconnecting)
        captionM = captionM + wxT(" ") + _("(disconnecting...)");
    wxArtID id = (database.isConnected() ?
        ART_DatabaseConnected : ART_DatabaseDisconnected);
    imageIndexM = DBHTreeImageList::get().getImageIndex(id);
    childrenNotLoadedM = false;
    sortChildrenM = true;
}
//-----------------------------------------------------------------------------
void DBHItemTreeNodeProperties::visit(Domain& domain)
{
    if (!domain.isSystem())
    {
        visitItem(&domain);
        imageIndexM = DBHTreeImageList::get().getImageIndex(ART_Domain);
    }
}
//-----------------------------------------------------------------------------
void DBHItemTreeNodeProperties::visit(DomainCollection& domains)
{
    int img = DBHTreeImageList::get().getImageIndex(ART_Domains);
    visitCollection(&domains, _("Domains"), img);
}
//-----------------------------------------------------------------------------
void DBHItemTreeNodeProperties::visit(Exception& exception)
{
    visitItem(&exception);
    imageIndexM = DBHTreeImageList::get().getImageIndex(ART_Exception);
}
//-----------------------------------------------------------------------------
void DBHItemTreeNodeProperties::visit(ExceptionCollection& exceptions)
{
    int img = DBHTreeImageList::get().getImageIndex(ART_Exceptions);
    visitCollection(&exceptions, _("Exceptions"), img);
}
//-----------------------------------------------------------------------------
void DBHItemTreeNodeProperties::visit(Function& function)
{
    visitItem(&function);
    imageIndexM = DBHTreeImageList::get().getImageIndex(ART_Function);
}
//-----------------------------------------------------------------------------
void DBHItemTreeNodeProperties::visit(FunctionCollection& functions)
{
    int img = DBHTreeImageList::get().getImageIndex(ART_Functions);
    visitCollection(&functions, _("Functions"), img);
}
//-----------------------------------------------------------------------------
void DBHItemTreeNodeProperties::visit(Generator& generator)
{
    visitItem(&generator);
    imageIndexM = DBHTreeImageList::get().getImageIndex(ART_Generator);
}
//-----------------------------------------------------------------------------
void DBHItemTreeNodeProperties::visit(GeneratorCollection& generators)
{
    int img = DBHTreeImageList::get().getImageIndex(ART_Generators);
    visitCollection(&generators, _("Generators"), img);
}
//-----------------------------------------------------------------------------
void DBHItemTreeNodeProperties::visit(Procedure& procedure)
{
    visitItem(&procedure);
    imageIndexM = DBHTreeImageList::get().getImageIndex(ART_Procedure);
}
//-----------------------------------------------------------------------------
void DBHItemTreeNodeProperties::visit(ProcedureCollection& procedures)
{
    int img = DBHTreeImageList::get().getImageIndex(ART_Procedures);
    visitCollection(&procedures, _("Procedures"), img);
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
    sortChildrenM = true;
}
//-----------------------------------------------------------------------------
void DBHItemTreeNodeProperties::visit(Trigger& trigger)
{
    visitItem(&trigger);
    imageIndexM = DBHTreeImageList::get().getImageIndex(ART_Trigger);
}
//-----------------------------------------------------------------------------
void DBHItemTreeNodeProperties::visit(TriggerCollection& triggers)
{
    int img = DBHTreeImageList::get().getImageIndex(ART_Triggers);
    if (triggers.getRelation() != 0)
        visitCollection(&triggers, _("Triggers"), img);
    else
        visitCollection(&triggers, _("Database Triggers"), img);
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

    Item* getItem();
    PSharedItem getSharedItem();
    void setSharedItem(PSharedItem item);
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
    return itemM && (itemM->getLoadChildrenState() == Item::lcsLoaded);
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
Item* DBHTreeNode::getItem()
{
    return itemM.get();
}
//-----------------------------------------------------------------------------
PSharedItem DBHTreeNode::getSharedItem()
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
void DBHTreeNode::setSharedItem(PSharedItem item)
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

    wxBusyCursor wait;

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
    if (nodeProps.hasNotLoadedChildren())
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
            nodeData->setSharedItem(childItem);
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

    if (nodeProps.getSortChildren())
        treeM.SortChildren(id);

    // show the [+] marker when there are (or could be) children
    Item::LoadChildrenState state = itemM->getLoadChildrenState();
    treeM.SetItemHasChildren(id,
        itemM->hasChildren() || (state == Item::lcsNotLoaded));
    // expand tree node after background data loading
    if (getExpandOnUpdate() && state == Item::lcsLoaded)
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
    nodeData->setSharedItem(rootItem);
}
//-----------------------------------------------------------------------------
PSharedItem DBHTreeControl::getItemFromId(wxTreeItemId id)
{
    if (id.IsOk())
    {
        DBHTreeNode* childNodeData = DBHTreeNode::getFromTreeData(
            GetItemData(id));
        if (childNodeData)
            return childNodeData->getSharedItem();
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
    // select item under the mouse first, since right-click doesn't change
    // the selection under GTK
    // NOTE: removing the SelectItem() call for wxMSW does not work either,
    // because commands will be enabled for the selected, not for the
    // highlighted item :-(
    if (!useSelected)
    {
        const int checkFlags = wxTREE_HITTEST_ONITEMBUTTON
#ifdef __WXMSW__
            | wxTREE_HITTEST_ONITEMINDENT | wxTREE_HITTEST_ONITEMRIGHT
#endif
            | wxTREE_HITTEST_ONITEMICON | wxTREE_HITTEST_ONITEMLABEL;
        int hitFlags;
        id = HitTest(pos, hitFlags);
        if (id.IsOk() && (hitFlags & checkFlags))
            SelectItem(id);
    }

    PSharedItem item;
    if (id.IsOk())
    {
        DBHTreeNode* nodeData = DBHTreeNode::getFromTreeData(GetItemData(id));
        if (nodeData)
            item = nodeData->getSharedItem();
    }
    if (!item)
        return;
    // make sure the ItemCommands object will be properly freed
    boost::shared_ptr<ItemCommands> commands(
        ItemCommands::createItemCommands(item));
    if (commands)
    {
        // compute the menu coordinates if the event does not contain them
        if (useSelected)
        {
            wxRect rc;
            GetBoundingRect(id, rc, true);
            pos = wxPoint(rc.GetLeft(), rc.GetTop() + rc.GetHeight() / 2);
        }
        wxMenu menu;
        commands->addCommandsTo(&menu, true);
        PopupMenu(&menu, pos);
    }
}
//-----------------------------------------------------------------------------
void DBHTreeControl::OnTreeItemActivated(wxTreeEvent& /*event*/)
{
    wxCommandEvent ev(wxEVT_COMMAND_MENU_SELECTED, CmdObject_DefaultAction);
    AddPendingEvent(ev);
}
//-----------------------------------------------------------------------------
void DBHTreeControl::OnTreeItemExpanding(wxTreeEvent& event)
{
    wxTreeItemId id(event.GetItem());
    DBHTreeNode* nodeData = DBHTreeNode::getFromTreeData(GetItemData(id));
    if (nodeData)
    {
        PSharedItem item = nodeData->getSharedItem();
        // there maybe child nodes that have not been created yet
        if (item && !nodeData->hasLoadedChildren())
        {
            nodeData->setExpandOnUpdate(true);
            item->loadChildren();
        }
    }
}
//-----------------------------------------------------------------------------
