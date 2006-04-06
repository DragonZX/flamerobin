/*
  The contents of this file are subject to the Initial Developer's Public
  License Version 1.0 (the "License"); you may not use this file except in
  compliance with the License. You may obtain a copy of the License here:
  http://www.flamerobin.org/license.html.

  Software distributed under the License is distributed on an "AS IS"
  basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the
  License for the specific language governing rights and limitations under
  the License.

  The Original Code is FlameRobin (TM).

  The Initial Developer of the Original Code is Milan Babuskov.

  Portions created by the original developer
  are Copyright (C) 2005 Milan Babuskov.

  All Rights Reserved.

  $Id$

  Contributor(s): Michael Hieke
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
