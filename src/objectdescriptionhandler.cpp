/*
  Copyright (c) 2004-2011 The FlameRobin Development Team

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
//-----------------------------------------------------------------------------
#include "gui/MultilineEnterDialog.h"
#include "metadata/database.h"
#include "metadata/metadataitem.h"
#include "urihandler.h"

class ObjectDescriptionHandler: public URIHandler
{
public:
    ObjectDescriptionHandler() {};
    bool handleURI(URI& uri);
private:
    // singleton; registers itself on creation.
    static const ObjectDescriptionHandler handlerInstance;
};
//-----------------------------------------------------------------------------
const ObjectDescriptionHandler ObjectDescriptionHandler::handlerInstance;
//-----------------------------------------------------------------------------
bool ObjectDescriptionHandler::handleURI(URI& uri)
{
    if (uri.action != wxT("edit_description"))
        return false;

    MetadataItem* m = (MetadataItem*)getObject(uri);
    wxWindow* w = getWindow(uri);
    if (!m || !w)
        return true;

    wxString desc = m->getDescription();
    if (GetMultilineTextFromUser(w, wxString::Format(_("Description of %s"),
        uri.getParam(wxT("object_name")).c_str()), desc))
    {
        wxBusyCursor wait;
        m->setDescription(desc);
        // FIXME: This can be removed when MetadataItem::setDescriptionM()
        //        is fixed to call it without recursion.
        m->notifyObservers();
    }
    return true;
}
//-----------------------------------------------------------------------------

