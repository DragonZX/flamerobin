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

#include <wx/cmdline.h>
#include <wx/utils.h>

#include <exception>

#include <ibpp.h>

#include "Application.h"
#include "config/Config.h"
#include "core/ArtProvider.h"
#include "core/FRError.h"
#include "core/StringUtils.h"
#include "gui/MainFrame.h"
#include "hierarchy/Item.h"
#include "hierarchy/TreeRoot.h"
//-----------------------------------------------------------------------------
IMPLEMENT_APP(Application)
//-----------------------------------------------------------------------------
void parachute()
{
    if (wxYES == ::wxMessageBox(_("A fatal error has occured. If you know how to reproduce the problem,\nplease submit the bug report at:\nhttp://sourceforge.net/tracker/?group_id=124340&atid=699234\n\nThe program can try to keep running so that you can save your data.\nDo you wish to try?\n"),
        _("Fatal Application Error"), wxYES_NO | wxICON_ERROR))
    {
        int result = ::wxGetApp().OnRun();
        exit(result);
    }
    exit(1);
}
//-----------------------------------------------------------------------------
bool Application::OnExceptionInMainLoop()
{
    return true;
}
//-----------------------------------------------------------------------------
void Application::OnFatalException()
{
    parachute();
}
//-----------------------------------------------------------------------------
int Application::OnExit()
{
    PSharedTreeRoot root = TreeRoot::get();
    // make sure that all background threads are freed, otherwise shutdown
    // will not always work properly on Linux
    if (root)
        root->clearChildren();
    return wxApp::OnExit();
}
//-----------------------------------------------------------------------------
bool Application::OnInit()
{
#if wxUSE_ON_FATAL_EXCEPTION
    ::wxHandleFatalExceptions();
#endif

    std::set_terminate(parachute);
    checkEnvironment();
    parseCommandLine();

#if wxCHECK_VERSION(2, 8, 0)
    wxArtProvider::Push(new ArtProvider);
#else
    wxArtProvider::PushProvider(new ArtProvider);
#endif
    wxImage::AddHandler(new wxPNGHandler);

    // first frame shows complete DBH, starting with global root node
    PSharedTreeRoot root = TreeRoot::get();
    MainFrame* mf = new MainFrame(0, wxID_ANY, root);

    if (!root->loadHierarchy())
        root->createDefaultHierarchy();

    SetTopWindow(mf);
    mf->Show();

    openDatabasesFromParams(mf);
    return true;
}
//-----------------------------------------------------------------------------
void Application::HandleEvent(wxEvtHandler* handler, wxEventFunction func,
    wxEvent& event) const
{
    try
    {
        wxAppConsole::HandleEvent(handler, func, event);
    }
    catch (const std::exception& e)
    {
        wxMessageBox(std2wx(e.what()), _("Unhandled Error in FlameRobin"),
            wxOK | wxICON_ERROR, wxGetTopLevelParent(wxGetActiveWindow()));
    }
}
//-----------------------------------------------------------------------------
void Application::checkEnvironment()
{
    wxString envVar;
    if (wxGetEnv(wxT("FR_HOME"), &envVar))
        config().setHomePath(translatePathMacros(envVar));
    if (wxGetEnv(wxT("FR_USER_HOME"), &envVar))
        config().setUserHomePath(translatePathMacros(envVar));
}
//-----------------------------------------------------------------------------
void Application::parseCommandLine()
{
    wxCmdLineParser parser(wxGetApp().argc, wxGetApp().argv);
    parser.AddOption(wxT("h"), wxT("home"), _("Set FlameRobin's home path"));
    parser.AddOption(wxT("uh"), wxT("user-home"),
        _("Set FlameRobin's user home path"));
    // open databases given as command line parameters
    parser.AddParam(_("File name of database to open"), wxCMD_LINE_VAL_STRING,
        wxCMD_LINE_PARAM_OPTIONAL | wxCMD_LINE_PARAM_MULTIPLE);

    if (parser.Parse() == 0)
    {
        wxString paramValue;
        if (parser.Found(wxT("home"), &paramValue))
            config().setHomePath(translatePathMacros(paramValue));

        if (parser.Found(wxT("user-home"), &paramValue))
            config().setUserHomePath(translatePathMacros(paramValue));

        for (size_t i = 0; i < parser.GetParamCount(); i++)
            cmdlineParamsM.Add(parser.GetParam(i));
    }
}
//-----------------------------------------------------------------------------
const wxString Application::translatePathMacros(const wxString path) const
{
    if (path == wxT("$app"))
        return config().getLocalDataDir();
    else if (path == wxT("$user"))
        return config().getUserLocalDataDir();
    else
        return path;
}
//-----------------------------------------------------------------------------
const wxString Application::getConfigurableObjectId() const
{
    return wxT("");
}
//-----------------------------------------------------------------------------
void Application::openDatabasesFromParams(MainFrame* frFrame)
{
    if (cmdlineParamsM.GetCount())
    {
        for (size_t i = 0; i < cmdlineParamsM.GetCount(); i++)
            frFrame->openUnregisteredDatabase(cmdlineParamsM[i]);
        cmdlineParamsM.Clear();
    }
}
//-----------------------------------------------------------------------------
