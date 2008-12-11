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

#ifndef FR_COMMANDIDS_H
#define FR_COMMANDIDS_H

enum CmdIds {
  CmdIdFirst = 100,

  CmdView_ToolBarFirst = CmdIdFirst,
  CmdView_ToolBarStandard = CmdView_ToolBarFirst,
  // add IDs for other toolbars here
  CmdView_ToolBarLast, CmdView_StatusBar,
  CmdView_RegisteredDatabases, CmdView_UnregisteredDatabases,
  CmdView_OpenInNewFrame,

  CmdHelp_Manual = 140,
  CmdHelp_RelNotes, CmdHelp_License,

  CmdURL_HomePage = 150,
  CmdURL_ProjectPage, CmdURL_FeatureRequest, CmdURL_BugReport,

  CmdFolder_Create = 160,
  CmdFolder_ConnectAllDatabases, CmdFolder_DisconnectAllDatabases,

  CmdDatabase_Register = 200,
  CmdDatabase_Properties, CmdDatabase_RegistrationInfo, CmdDatabase_Unregister,
  CmdDatabase_Preferences,
  CmdDatabase_Connect, CmdDatabase_ConnectAs, CmdDatabase_Reconnect,
  CmdDatabase_Disconnect,
  CmdDatabase_Create, CmdDatabase_Backup, CmdDatabase_Restore,
  CmdDatabase_RestoreIntoNew,
  CmdDatabase_Drop, CmdDatabase_MonitorEvents,
  CmdDatabase_ExecuteStatement, CmdDatabase_ExecuteProcedure,
  CmdDatabase_InsertInto, CmdDatabase_SelectAll, CmdDatabase_SelectColumns,
  CmdDatabase_ShowGeneratorValue, CmdDatabase_ShowAllGeneratorValues,
  CmdDatabase_SetGeneratorValue,
  CmdDatabase_AddTableColumn, CmdDatabase_CreateTableTrigger,

  CmdObject_New = 300,
  CmdObject_Create, CmdObject_Alter, CmdObject_Properties, CmdObject_Drop,
  CmdObject_CreateDomain, CmdObject_CreateException, CmdObject_CreateFunction,
  CmdObject_CreateGenerator, CmdObject_CreateProcedure, CmdObject_CreateRole,
  CmdObject_CreateTable, CmdObject_CreateTrigger, CmdObject_CreateView,
  CmdObject_ShowInfo, CmdObject_Refresh,
  CmdObject_DefaultAction,

  CmdIdLast
};
//-----------------------------------------------------------------------------
#endif // FR_COMMANDIDS_H

