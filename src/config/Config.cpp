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
#include "wx/fileconf.h"
#include "wx/filename.h"

#include <fstream>
#include <sstream>

#include "config/Config.h"
#ifdef HAVE_FRCONFIG_H
    #include "frconfig.h"
#endif
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
const wxString Config::pathSeparator = wxT("/");
//-----------------------------------------------------------------------------
Config& config()
{
    static Config c;
    return c;
}
//-----------------------------------------------------------------------------
Config::Config()
    : homePathM(wxT("")), userHomePathM(wxT("")), configM(0), needsFlushM(false)
{
#ifdef FR_CONFIG_USE_PRIVATE_STDPATHS
    standardPathsM.SetInstallPrefix(wxT(FR_INSTALL_PREFIX));
#endif
}
//-----------------------------------------------------------------------------
Config::~Config()
{
    delete configM;
}
//-----------------------------------------------------------------------------
wxFileConfig* Config::getConfig() const
{
    if (!configM)
    {
        wxFileName configFileName = getConfigFileName();
        if (!wxDirExists(configFileName.GetPath()))
            wxMkdir(configFileName.GetPath());
        configM = new wxFileConfig(wxT(""), wxT(""),
            configFileName.GetFullPath(), wxT(""), wxCONFIG_USE_LOCAL_FILE);
        configM->SetExpandEnvVars(false);
    }
    return configM;
}
//-----------------------------------------------------------------------------
void Config::lockedChanged(bool locked)
{
    // delay getConfig()->Flush() until object is completely unlocked again
    if (!locked && needsFlushM)
    {
        needsFlushM = false;
        getConfig()->Flush();
    }
}
//-----------------------------------------------------------------------------
//! return true if value exists, false if not
bool Config::keyExists(const wxString& key) const
{
    return getConfig()->HasEntry(key);
}
//-----------------------------------------------------------------------------
//! return true if value exists, false if not
bool Config::getValue(wxString key, wxString& value)
{
    // if complete key is found, then return (recursion exit condition).
    wxString configValue;
    if (getConfig()->Read(key, &configValue))
    {
        value = configValue;
        return true;
    }
    // does key contain a separator? If not, then the key is not found and
    // we're done.
    wxString::size_type separatorPos = key.rfind(pathSeparator);
    if (separatorPos == wxString::npos)
        return false;
    else
    {
        // split key into keyPart and pathPart; remove last component of
        // pathPart and recurse.
        wxString keyPart = key.substr(separatorPos + 1, key.length());
        wxString pathPart = key.substr(0, separatorPos);
        wxString::size_type separatorPosInPath = pathPart.rfind(pathSeparator);
        if (separatorPosInPath == wxString::npos)
            return getValue(keyPart, value);
        else
            return getValue(pathPart.substr(0, separatorPosInPath) +
                pathSeparator + keyPart, value);
    }
}
//-----------------------------------------------------------------------------
bool Config::getValue(wxString key, int& value)
{
    wxString s;
    if (!getValue(key, s))
        return false;

    // This variable is only needed because the compiler considers
    // int* and long* incompatible. It may be ditched if a better solution
    // is found.
    long longValue;
    if (!s.ToLong(&longValue))
        return false;

    value = longValue;
    return true;
}
//-----------------------------------------------------------------------------
bool Config::getValue(wxString key, double& value)
{
    wxString s;
    if (!getValue(key, s))
        return false;

    if (!s.ToDouble(&value))
        return false;

    return true;
}
//-----------------------------------------------------------------------------
bool Config::getValue(wxString key, bool& value)
{
    wxString s;
    if (!getValue(key, s))
        return false;

    value = (s == wxT("1"));
    return true;
}
//-----------------------------------------------------------------------------
bool Config::getValue(wxString key, StorageGranularity& value)
{
    int intValue = 0;
    bool ret = getValue(key, intValue);
    if (ret)
        value = StorageGranularity(intValue);
    return ret;
}
//-----------------------------------------------------------------------------
bool Config::getValue(wxString key, vector<wxString>& value)
{
    wxString s;
    if (!getValue(key, s))
        return false;

    value.clear();
    wxString item;
    size_t pos = 0, sep = s.find(',');
    while (sep != wxString::npos)
    {
        item = s.substr(pos, sep - pos);
        if (!item.empty())
            value.push_back(item);
        sep = s.find(',', pos = sep + 1);
    }
    if (!(item = s.substr(pos)).empty())
        value.push_back(item);
    return true;
}
//-----------------------------------------------------------------------------
//! return true if value existed, false if not
bool Config::setValue(wxString key, wxString value)
{
    bool result = getConfig()->Write(key, value);
    if (!isLocked())
        getConfig()->Flush();
    else
        needsFlushM = true;
    notifyObservers();
    return result;
}
//-----------------------------------------------------------------------------
bool Config::setValue(wxString key, int value)
{
    wxString s;
    s << value;
    return setValue(key, s);
}
//-----------------------------------------------------------------------------
bool Config::setValue(wxString key, double value)
{
    wxString s;
    s << value;
    return setValue(key, s);
}
//-----------------------------------------------------------------------------
bool Config::setValue(wxString key, bool value)
{
    if (value)
        return setValue(key, wxString(wxT("1")));
    else
        return setValue(key, wxString(wxT("0")));
}
//-----------------------------------------------------------------------------
bool Config::setValue(wxString key, StorageGranularity value)
{
    return setValue(key, int(value));
}
//-----------------------------------------------------------------------------
bool Config::setValue(wxString key, vector<wxString> value)
{
    wxString s;
    for (vector<wxString>::iterator it = value.begin(); it != value.end(); it++)
    {
        if (it != value.begin())
            s += wxT(",");
        // this is just a parachute, if this should ever be triggered we
        // will need to quote and unquote this wxString or all in value
        wxASSERT((*it).find(',') == wxString::npos);
        s += *it;
    }
    return setValue(key, s);
}
//-----------------------------------------------------------------------------
wxString Config::getHomePath() const
{
    if (!homePathM.empty())
        return homePathM + wxT("/");
    else
        return getDataDir() + wxT("/");
}
//-----------------------------------------------------------------------------
wxString Config::getHtmlTemplatesPath() const
{
    return getHomePath() + wxT("html-templates/");
}
//-----------------------------------------------------------------------------
wxString Config::getDocsPath() const
{
    return getHomePath() + wxT("docs/");
}
//-----------------------------------------------------------------------------
wxString Config::getConfDefsPath() const
{
    return getHomePath() + wxT("conf-defs/");
}
//-----------------------------------------------------------------------------
wxString Config::getImagesPath() const
{
    return getHomePath() + wxT("images/");
}
//-----------------------------------------------------------------------------
wxString Config::getUserHomePath() const
{
    if (!userHomePathM.empty())
        return userHomePathM + wxT("/");
    else
        return getUserLocalDataDir() + wxT("/");
}
//-----------------------------------------------------------------------------
wxString Config::getDBHFileName() const
{
    return getUserHomePath() + wxT("fr_databases.conf");
}
//-----------------------------------------------------------------------------
wxString Config::getConfigFileName() const
{
    return getUserHomePath() + wxT("fr_settings.conf");
}
//-----------------------------------------------------------------------------
wxString Config::getDataDir() const
{
#ifdef FR_CONFIG_USE_PRIVATE_STDPATHS
    return standardPathsM.GetDataDir();
#else
    return wxStandardPaths::Get().GetDataDir();
#endif
}
//-----------------------------------------------------------------------------
wxString Config::getLocalDataDir() const
{
#ifdef FR_CONFIG_USE_PRIVATE_STDPATHS
    return standardPathsM.GetLocalDataDir();
#else
    return wxStandardPaths::Get().GetLocalDataDir();
#endif
}
//-----------------------------------------------------------------------------
wxString Config::getUserLocalDataDir() const
{
#ifdef FR_CONFIG_USE_PRIVATE_STDPATHS
    return standardPathsM.GetUserLocalDataDir();
#else
    return wxStandardPaths::Get().GetUserLocalDataDir();
#endif
}
//-----------------------------------------------------------------------------
void Config::setHomePath(const wxString& homePath)
{
    homePathM = homePath;
}
//-----------------------------------------------------------------------------
void Config::setUserHomePath(const wxString& userHomePath)
{
    userHomePathM = userHomePath;
}
//-----------------------------------------------------------------------------
// class ConfigCache
ConfigCache::ConfigCache(Config& config)
    : Observer(), cacheValidM(false)
{
    config.attachObserver(this);
}
//-----------------------------------------------------------------------------
void ConfigCache::ensureCacheValid()
{
    if (!cacheValidM)
    {
        loadFromConfig();
        cacheValidM = true;
    }
}
//-----------------------------------------------------------------------------
void ConfigCache::loadFromConfig()
{
}
//-----------------------------------------------------------------------------
void ConfigCache::update()
{
    // next call to ensureCacheValid() will reload the cached information
    cacheValidM = false;
}
//-----------------------------------------------------------------------------
