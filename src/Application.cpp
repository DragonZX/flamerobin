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
#include "core/CommandIds.h"
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

    wxArtProvider::Push(new ArtProvider);
    wxImage::AddHandler(new wxPNGHandler);

    localeM.Init();
    localeM.AddCatalog(wxT("wx"));
    localeM.AddCatalog(wxT("flamerobin"));

    // IBPP initialization is not thread-safe on Windows, therefore we have to
    // force loading of client library and get API entry points in GUI thread
    IBPP::GDSVersion();

    // disable all (context) menu commands that are not enabled by a proper
    // wxCommandUpdateUI handler - necessary for wxMac, where commands in the
    // mein menu need to be disabled if they are not applicable to the
    // currently active control/frame
    Connect(wxEVT_UPDATE_UI,
        wxUpdateUIEventHandler(Application::OnUpdateUIDisable));

    // first frame shows complete DBH, starting with global root node
    PSharedTreeRoot root = TreeRoot::get();
    if (!root->loadHierarchy())
        root->createDefaultHierarchy();

    MainFrame* mf = new MainFrame(0, wxID_ANY, root);
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
void Application::OnUpdateUIDisable(wxUpdateUIEvent& event)
{
    int evtId = event.GetId();
    // disable standard commands that have not been enabled yet
    if (evtId >= wxID_LOWEST && evtId <= wxID_HIGHEST)
    {
        const int stdCmds[] = {
            wxID_OPEN, wxID_CLOSE, wxID_NEW, wxID_SAVE, wxID_SAVEAS,
            wxID_REVERT, wxID_EXIT, wxID_UNDO, wxID_REDO, wxID_HELP,
            wxID_PRINT, wxID_PRINT_SETUP, wxID_PAGE_SETUP, wxID_PREVIEW,
            wxID_ABOUT, wxID_HELP_CONTENTS, wxID_HELP_INDEX, wxID_HELP_SEARCH,
            wxID_HELP_COMMANDS, wxID_HELP_PROCEDURES, wxID_HELP_CONTEXT,
            wxID_CLOSE_ALL, wxID_PREFERENCES,

            wxID_EDIT, wxID_CUT, wxID_COPY, wxID_PASTE, wxID_CLEAR, wxID_FIND,
            wxID_DUPLICATE, wxID_SELECTALL, wxID_DELETE, wxID_REPLACE,
            wxID_REPLACE_ALL, wxID_PROPERTIES,

            wxID_VIEW_DETAILS, wxID_VIEW_LARGEICONS, wxID_VIEW_SMALLICONS,
            wxID_VIEW_LIST, wxID_VIEW_SORTDATE, wxID_VIEW_SORTNAME,
            wxID_VIEW_SORTSIZE, wxID_VIEW_SORTTYPE,

            wxID_FILE, wxID_FILE1, wxID_FILE2, wxID_FILE3, wxID_FILE4,
            wxID_FILE5, wxID_FILE6, wxID_FILE7, wxID_FILE8, wxID_FILE9,

            wxID_FORWARD, wxID_BACKWARD, wxID_MORE, wxID_SETUP, wxID_RESET,
            wxID_ADD, wxID_REMOVE,

            wxID_UP, wxID_DOWN, wxID_HOME, wxID_REFRESH, wxID_STOP, wxID_INDEX,
        };

        for (int i = 0; i < sizeof(stdCmds) / sizeof(int); ++i)
        {
            if (stdCmds[i] == evtId)
            {
                event.Enable(false);
                return;
            }
        }
    }
    // disable FlameRobin commands that have not been enabled yet,
    // enable everything else
    event.Enable(evtId < CmdIdFirst || evtId > CmdIdLast);
}
//-----------------------------------------------------------------------------
