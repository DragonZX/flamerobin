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
//-----------------------------------------------------------------------------
#include "DatabaseConfig.h"
#include "metadata/database.h"
//-----------------------------------------------------------------------------
DatabaseConfig::DatabaseConfig(const Database *d)
    :Config(), databaseM(d)
{
    // we need to copy these settings, since they may have been modified
    // by env variables or command line params
    setHomePath(config().getHomePath());
    setUserHomePath(config().getUserHomePath());
}
//-----------------------------------------------------------------------------
wxString DatabaseConfig::addPathToKey(const wxString key) const
{
    if (databaseM)
        return wxT("DATABASE_") + databaseM->getId() + Config::pathSeparator + key;
    else
        return wxT("");
}
//-----------------------------------------------------------------------------
bool DatabaseConfig::keyExists(const wxString& key) const
{
    return config().keyExists(addPathToKey(key));
}
//-----------------------------------------------------------------------------
bool DatabaseConfig::getValue(wxString key, wxString& value)
{
    return config().getValue(addPathToKey(key), value);
}
//-----------------------------------------------------------------------------
bool DatabaseConfig::setValue(wxString key, wxString value)
{
    return config().setValue(addPathToKey(key), value);
}
//-----------------------------------------------------------------------------