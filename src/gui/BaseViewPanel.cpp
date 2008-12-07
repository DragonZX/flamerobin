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

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWindows headers
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <wx/aui/aui.h>

#include <algorithm>
#include <list>

#include "gui/BaseViewPanel.h"
//-----------------------------------------------------------------------------
typedef std::list<BaseViewPanel*> BaseViewPanelList;

BaseViewPanelList viewPanels;
//-----------------------------------------------------------------------------
BaseViewPanel::BaseViewPanel(wxWindow* parent, wxWindowID id,
        const wxPoint& pos, const wxSize& size, long style,
        const wxString& name)
    : wxPanel()
{
    Hide();
    Create(parent, id, pos, size, style, name);
    viewPanels.push_back(this);
}
//-----------------------------------------------------------------------------
BaseViewPanel::~BaseViewPanel()
{
    BaseViewPanelList::iterator it = std::find(viewPanels.begin(),
        viewPanels.end(), this);
    if (it != viewPanels.end())
        viewPanels.erase(it);
}
//-----------------------------------------------------------------------------
wxString BaseViewPanel::getId() const
{
    return idM;
}
//-----------------------------------------------------------------------------
void BaseViewPanel::setId(const wxString& id)
{
    idM = id;
}
//-----------------------------------------------------------------------------
/*static*/
bool BaseViewPanel::activateViewPanel(const wxString& id)
{
    if (BaseViewPanel* panel = findViewPanel(id))
    {
        wxWindow* tlw = wxGetTopLevelParent(panel);
        wxCHECK_MSG(tlw, false, wxT("view panel has no top level parent"));

        wxWindow* parent = panel->GetParent();
        while (parent && parent != tlw)
        {
            if (wxAuiNotebook* nb = wxDynamicCast(parent, wxAuiNotebook))
            {
                int page = nb->GetPageIndex(panel);
                if (page != wxNOT_FOUND && page != nb->GetSelection())
                    nb->SetSelection(page);
            }
            parent = parent->GetParent();
        }
        tlw->Raise();
        return true;
    }
    return false;
}
//-----------------------------------------------------------------------------
/*static*/
BaseViewPanel* BaseViewPanel::findViewPanel(const wxString& id)
{
    for (BaseViewPanelList::iterator it = viewPanels.begin();
        it != viewPanels.end(); ++it)
    {
        wxASSERT((*it) != 0);
        if (id == (*it)->getId())
            return *it;
    }
    return 0;
}
//-----------------------------------------------------------------------------
