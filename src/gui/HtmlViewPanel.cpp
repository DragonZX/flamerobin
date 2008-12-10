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
#include <wx/html/htmlwin.h>

#include <memory>

#include "gui/HtmlViewPanel.h"
//-----------------------------------------------------------------------------
HtmlViewPanel::HtmlViewPanel(wxWindow* parent, wxWindowID id)
    : BaseViewPanel(parent, id)
{
    htmlWindowM = new wxHtmlWindow(this);
    wxString htmlSource(wxT("<html><body>"));
    htmlSource += _("Please wait while the page is being loaded...");
    htmlSource += wxT("</body></html>");
    htmlWindowM->SetPage(htmlSource);

    std::auto_ptr<wxBoxSizer> sizer(new wxBoxSizer(wxHORIZONTAL));
    sizer->Add(htmlWindowM, 1, wxEXPAND);
    SetSizerAndFit(sizer.release());
}
//-----------------------------------------------------------------------------
bool HtmlViewPanel::loadFromFile(const wxFileName& filename)
{
    fileNameM.Clear();
    bool success = htmlWindowM->LoadFile(filename);
    if (success)
        fileNameM = filename;
    return success;
}
//-----------------------------------------------------------------------------
/*static*/
HtmlViewPanel* HtmlViewPanel::createViewInFrame(const wxString& id,
    wxWindow* parent, const wxString& caption)
{
    // use two step creation for minimal flicker
    wxFrame* frame = new wxFrame();
    frame->Hide();
    frame->Create(parent, wxID_ANY, caption);

    HtmlViewPanel* panel = new HtmlViewPanel(frame);
    panel->setId(id);
    panel->Show();

    frame->Show();
    frame->Update();
    return panel;
}
//-----------------------------------------------------------------------------
/*static*/
HtmlViewPanel* HtmlViewPanel::createViewInNotebook(const wxString& id,
    wxAuiNotebook* notebook, const wxString& caption)
{
    wxCHECK_MSG(notebook, 0,
        wxT("HtmlViewPanel::createViewInNotebook called without notebook"));

    HtmlViewPanel* panel = new HtmlViewPanel(notebook);
    panel->setId(id);
    notebook->AddPage(panel, caption, true);
    notebook->Update();
    return panel;
}
//-----------------------------------------------------------------------------
/*static*/
wxString HtmlViewPanel::getIdFromFileName(const wxString& filename)
{
    return wxT("HtmlView/File/") + filename;
}
//-----------------------------------------------------------------------------
