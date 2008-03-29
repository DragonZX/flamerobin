# Microsoft Developer Studio Project File - Name="flamerobin_flamerobin" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=flamerobin - Win32 Debug Dynamic
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "flamerobin_flamerobin.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "flamerobin_flamerobin.mak" CFG="flamerobin - Win32 Debug Dynamic"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "flamerobin - Win32 DLL Unicode Release Static" (based on "Win32 (x86) Application")
!MESSAGE "flamerobin - Win32 DLL Unicode Release Dynamic" (based on "Win32 (x86) Application")
!MESSAGE "flamerobin - Win32 DLL Unicode Debug Static" (based on "Win32 (x86) Application")
!MESSAGE "flamerobin - Win32 DLL Unicode Debug Dynamic" (based on "Win32 (x86) Application")
!MESSAGE "flamerobin - Win32 DLL Release Static" (based on "Win32 (x86) Application")
!MESSAGE "flamerobin - Win32 DLL Release Dynamic" (based on "Win32 (x86) Application")
!MESSAGE "flamerobin - Win32 DLL Debug Static" (based on "Win32 (x86) Application")
!MESSAGE "flamerobin - Win32 DLL Debug Dynamic" (based on "Win32 (x86) Application")
!MESSAGE "flamerobin - Win32 Unicode Release Static" (based on "Win32 (x86) Application")
!MESSAGE "flamerobin - Win32 Unicode Release Dynamic" (based on "Win32 (x86) Application")
!MESSAGE "flamerobin - Win32 Unicode Debug Static" (based on "Win32 (x86) Application")
!MESSAGE "flamerobin - Win32 Unicode Debug Dynamic" (based on "Win32 (x86) Application")
!MESSAGE "flamerobin - Win32 Release Static" (based on "Win32 (x86) Application")
!MESSAGE "flamerobin - Win32 Release Dynamic" (based on "Win32 (x86) Application")
!MESSAGE "flamerobin - Win32 Debug Static" (based on "Win32 (x86) Application")
!MESSAGE "flamerobin - Win32 Debug Dynamic" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "flamerobin - Win32 DLL Unicode Release Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vcus"
# PROP BASE Intermediate_Dir "vcus\flamerobin"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vcus"
# PROP Intermediate_Dir "vcus\flamerobin"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MT /Fdvcus\flamerobin.pdb /O1 /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_dll\mswu" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcus\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_UNICODE" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD CPP /nologo /FD /MT /Fdvcus\flamerobin.pdb /O1 /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_dll\mswu" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcus\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_UNICODE" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_UNICODE" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_UNICODE" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_UNICODE" /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_dll\mswu" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
# ADD RSC /l 0x409 /d "_UNICODE" /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_dll\mswu" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw28u_stc.lib wxmsw28u_html.lib wxmsw28u_adv.lib wxmsw28u_core.lib wxbase28u_xml.lib wxbase28u.lib wxregexu.lib wxexpat.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcus\ibpp.lib /nologo /machine:i386 /out:"vcus\flamerobin.exe" /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_dll" /subsystem:windows
# ADD LINK32 wxmsw28u_stc.lib wxmsw28u_html.lib wxmsw28u_adv.lib wxmsw28u_core.lib wxbase28u_xml.lib wxbase28u.lib wxregexu.lib wxexpat.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcus\ibpp.lib /nologo /machine:i386 /out:"vcus\flamerobin.exe" /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_dll" /subsystem:windows

!ELSEIF  "$(CFG)" == "flamerobin - Win32 DLL Unicode Release Dynamic"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vcu"
# PROP BASE Intermediate_Dir "vcu\flamerobin"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vcu"
# PROP Intermediate_Dir "vcu\flamerobin"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdvcu\flamerobin.pdb /O1 /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_dll\mswu" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcu\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_UNICODE" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD CPP /nologo /FD /MD /Fdvcu\flamerobin.pdb /O1 /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_dll\mswu" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcu\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_UNICODE" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_UNICODE" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_UNICODE" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_UNICODE" /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_dll\mswu" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
# ADD RSC /l 0x409 /d "_UNICODE" /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_dll\mswu" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw28u_stc.lib wxmsw28u_html.lib wxmsw28u_adv.lib wxmsw28u_core.lib wxbase28u_xml.lib wxbase28u.lib wxregexu.lib wxexpat.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcu\ibpp.lib /nologo /machine:i386 /out:"vcu\flamerobin.exe" /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_dll" /subsystem:windows
# ADD LINK32 wxmsw28u_stc.lib wxmsw28u_html.lib wxmsw28u_adv.lib wxmsw28u_core.lib wxbase28u_xml.lib wxbase28u.lib wxregexu.lib wxexpat.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcu\ibpp.lib /nologo /machine:i386 /out:"vcu\flamerobin.exe" /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_dll" /subsystem:windows

!ELSEIF  "$(CFG)" == "flamerobin - Win32 DLL Unicode Debug Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vcusd"
# PROP BASE Intermediate_Dir "vcusd\flamerobin"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vcusd"
# PROP Intermediate_Dir "vcusd\flamerobin"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MTd /Zi /Gm /GZ /Fdvcusd\flamerobin.pdb /Od /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_dll\mswud" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcusd\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_DEBUG" /D "_UNICODE" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD CPP /nologo /FD /MTd /Zi /Gm /GZ /Fdvcusd\flamerobin.pdb /Od /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_dll\mswud" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcusd\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_DEBUG" /D "_UNICODE" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "_UNICODE" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "_UNICODE" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_UNICODE" /d "__WXDEBUG__" /d "_DEBUG" /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_dll\mswud" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
# ADD RSC /l 0x409 /d "_DEBUG" /d "_UNICODE" /d "__WXDEBUG__" /d "_DEBUG" /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_dll\mswud" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw28ud_stc.lib wxmsw28ud_html.lib wxmsw28ud_adv.lib wxmsw28ud_core.lib wxbase28ud_xml.lib wxbase28ud.lib wxregexud.lib wxexpatd.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcusd\ibpp.lib /nologo /machine:i386 /out:"vcusd\flamerobin.exe" /debug /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_dll" /subsystem:windows
# ADD LINK32 wxmsw28ud_stc.lib wxmsw28ud_html.lib wxmsw28ud_adv.lib wxmsw28ud_core.lib wxbase28ud_xml.lib wxbase28ud.lib wxregexud.lib wxexpatd.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcusd\ibpp.lib /nologo /machine:i386 /out:"vcusd\flamerobin.exe" /debug /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_dll" /subsystem:windows

!ELSEIF  "$(CFG)" == "flamerobin - Win32 DLL Unicode Debug Dynamic"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vcud"
# PROP BASE Intermediate_Dir "vcud\flamerobin"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vcud"
# PROP Intermediate_Dir "vcud\flamerobin"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdvcud\flamerobin.pdb /Od /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_dll\mswud" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcud\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_DEBUG" /D "_UNICODE" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdvcud\flamerobin.pdb /Od /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_dll\mswud" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcud\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_DEBUG" /D "_UNICODE" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "_UNICODE" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "_UNICODE" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_UNICODE" /d "__WXDEBUG__" /d "_DEBUG" /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_dll\mswud" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
# ADD RSC /l 0x409 /d "_DEBUG" /d "_UNICODE" /d "__WXDEBUG__" /d "_DEBUG" /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_dll\mswud" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw28ud_stc.lib wxmsw28ud_html.lib wxmsw28ud_adv.lib wxmsw28ud_core.lib wxbase28ud_xml.lib wxbase28ud.lib wxregexud.lib wxexpatd.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcud\ibpp.lib /nologo /machine:i386 /out:"vcud\flamerobin.exe" /debug /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_dll" /subsystem:windows
# ADD LINK32 wxmsw28ud_stc.lib wxmsw28ud_html.lib wxmsw28ud_adv.lib wxmsw28ud_core.lib wxbase28ud_xml.lib wxbase28ud.lib wxregexud.lib wxexpatd.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcud\ibpp.lib /nologo /machine:i386 /out:"vcud\flamerobin.exe" /debug /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_dll" /subsystem:windows

!ELSEIF  "$(CFG)" == "flamerobin - Win32 DLL Release Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vcs"
# PROP BASE Intermediate_Dir "vcs\flamerobin"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vcs"
# PROP Intermediate_Dir "vcs\flamerobin"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MT /Fdvcs\flamerobin.pdb /O1 /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_dll\msw" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcs\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD CPP /nologo /FD /MT /Fdvcs\flamerobin.pdb /O1 /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_dll\msw" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcs\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_dll\msw" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
# ADD RSC /l 0x409 /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_dll\msw" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw28_stc.lib wxmsw28_html.lib wxmsw28_adv.lib wxmsw28_core.lib wxbase28_xml.lib wxbase28.lib wxregex.lib wxexpat.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcs\ibpp.lib /nologo /machine:i386 /out:"vcs\flamerobin.exe" /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_dll" /subsystem:windows
# ADD LINK32 wxmsw28_stc.lib wxmsw28_html.lib wxmsw28_adv.lib wxmsw28_core.lib wxbase28_xml.lib wxbase28.lib wxregex.lib wxexpat.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcs\ibpp.lib /nologo /machine:i386 /out:"vcs\flamerobin.exe" /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_dll" /subsystem:windows

!ELSEIF  "$(CFG)" == "flamerobin - Win32 DLL Release Dynamic"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vc"
# PROP BASE Intermediate_Dir "vc\flamerobin"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vc"
# PROP Intermediate_Dir "vc\flamerobin"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdvc\flamerobin.pdb /O1 /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_dll\msw" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vc\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD CPP /nologo /FD /MD /Fdvc\flamerobin.pdb /O1 /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_dll\msw" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vc\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_dll\msw" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
# ADD RSC /l 0x409 /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_dll\msw" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw28_stc.lib wxmsw28_html.lib wxmsw28_adv.lib wxmsw28_core.lib wxbase28_xml.lib wxbase28.lib wxregex.lib wxexpat.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vc\ibpp.lib /nologo /machine:i386 /out:"vc\flamerobin.exe" /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_dll" /subsystem:windows
# ADD LINK32 wxmsw28_stc.lib wxmsw28_html.lib wxmsw28_adv.lib wxmsw28_core.lib wxbase28_xml.lib wxbase28.lib wxregex.lib wxexpat.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vc\ibpp.lib /nologo /machine:i386 /out:"vc\flamerobin.exe" /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_dll" /subsystem:windows

!ELSEIF  "$(CFG)" == "flamerobin - Win32 DLL Debug Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vcsd"
# PROP BASE Intermediate_Dir "vcsd\flamerobin"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vcsd"
# PROP Intermediate_Dir "vcsd\flamerobin"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MTd /Zi /Gm /GZ /Fdvcsd\flamerobin.pdb /Od /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_dll\mswd" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcsd\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_DEBUG" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD CPP /nologo /FD /MTd /Zi /Gm /GZ /Fdvcsd\flamerobin.pdb /Od /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_dll\mswd" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcsd\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_DEBUG" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "__WXDEBUG__" /d "_DEBUG" /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_dll\mswd" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
# ADD RSC /l 0x409 /d "_DEBUG" /d "__WXDEBUG__" /d "_DEBUG" /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_dll\mswd" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw28d_stc.lib wxmsw28d_html.lib wxmsw28d_adv.lib wxmsw28d_core.lib wxbase28d_xml.lib wxbase28d.lib wxregexd.lib wxexpatd.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcsd\ibpp.lib /nologo /machine:i386 /out:"vcsd\flamerobin.exe" /debug /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_dll" /subsystem:windows
# ADD LINK32 wxmsw28d_stc.lib wxmsw28d_html.lib wxmsw28d_adv.lib wxmsw28d_core.lib wxbase28d_xml.lib wxbase28d.lib wxregexd.lib wxexpatd.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcsd\ibpp.lib /nologo /machine:i386 /out:"vcsd\flamerobin.exe" /debug /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_dll" /subsystem:windows

!ELSEIF  "$(CFG)" == "flamerobin - Win32 DLL Debug Dynamic"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vcd"
# PROP BASE Intermediate_Dir "vcd\flamerobin"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vcd"
# PROP Intermediate_Dir "vcd\flamerobin"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdvcd\flamerobin.pdb /Od /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_dll\mswd" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcd\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_DEBUG" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdvcd\flamerobin.pdb /Od /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_dll\mswd" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcd\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_DEBUG" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "__WXDEBUG__" /d "_DEBUG" /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_dll\mswd" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
# ADD RSC /l 0x409 /d "_DEBUG" /d "__WXDEBUG__" /d "_DEBUG" /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_dll\mswd" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw28d_stc.lib wxmsw28d_html.lib wxmsw28d_adv.lib wxmsw28d_core.lib wxbase28d_xml.lib wxbase28d.lib wxregexd.lib wxexpatd.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcd\ibpp.lib /nologo /machine:i386 /out:"vcd\flamerobin.exe" /debug /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_dll" /subsystem:windows
# ADD LINK32 wxmsw28d_stc.lib wxmsw28d_html.lib wxmsw28d_adv.lib wxmsw28d_core.lib wxbase28d_xml.lib wxbase28d.lib wxregexd.lib wxexpatd.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcd\ibpp.lib /nologo /machine:i386 /out:"vcd\flamerobin.exe" /debug /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_dll" /subsystem:windows

!ELSEIF  "$(CFG)" == "flamerobin - Win32 Unicode Release Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vcus"
# PROP BASE Intermediate_Dir "vcus\flamerobin"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vcus"
# PROP Intermediate_Dir "vcus\flamerobin"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MT /Fdvcus\flamerobin.pdb /O1 /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_lib\mswu" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcus\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_UNICODE" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD CPP /nologo /FD /MT /Fdvcus\flamerobin.pdb /O1 /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_lib\mswu" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcus\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_UNICODE" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_UNICODE" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_UNICODE" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_UNICODE" /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_lib\mswu" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
# ADD RSC /l 0x409 /d "_UNICODE" /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_lib\mswu" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw28u_stc.lib wxmsw28u_html.lib wxmsw28u_adv.lib wxmsw28u_core.lib wxbase28u_xml.lib wxbase28u.lib wxregexu.lib wxexpat.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcus\ibpp.lib /nologo /machine:i386 /out:"vcus\flamerobin.exe" /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_lib" /subsystem:windows
# ADD LINK32 wxmsw28u_stc.lib wxmsw28u_html.lib wxmsw28u_adv.lib wxmsw28u_core.lib wxbase28u_xml.lib wxbase28u.lib wxregexu.lib wxexpat.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcus\ibpp.lib /nologo /machine:i386 /out:"vcus\flamerobin.exe" /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_lib" /subsystem:windows

!ELSEIF  "$(CFG)" == "flamerobin - Win32 Unicode Release Dynamic"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vcu"
# PROP BASE Intermediate_Dir "vcu\flamerobin"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vcu"
# PROP Intermediate_Dir "vcu\flamerobin"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdvcu\flamerobin.pdb /O1 /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_lib\mswu" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcu\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_UNICODE" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD CPP /nologo /FD /MD /Fdvcu\flamerobin.pdb /O1 /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_lib\mswu" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcu\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_UNICODE" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_UNICODE" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_UNICODE" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_UNICODE" /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_lib\mswu" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
# ADD RSC /l 0x409 /d "_UNICODE" /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_lib\mswu" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw28u_stc.lib wxmsw28u_html.lib wxmsw28u_adv.lib wxmsw28u_core.lib wxbase28u_xml.lib wxbase28u.lib wxregexu.lib wxexpat.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcu\ibpp.lib /nologo /machine:i386 /out:"vcu\flamerobin.exe" /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_lib" /subsystem:windows
# ADD LINK32 wxmsw28u_stc.lib wxmsw28u_html.lib wxmsw28u_adv.lib wxmsw28u_core.lib wxbase28u_xml.lib wxbase28u.lib wxregexu.lib wxexpat.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcu\ibpp.lib /nologo /machine:i386 /out:"vcu\flamerobin.exe" /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_lib" /subsystem:windows

!ELSEIF  "$(CFG)" == "flamerobin - Win32 Unicode Debug Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vcusd"
# PROP BASE Intermediate_Dir "vcusd\flamerobin"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vcusd"
# PROP Intermediate_Dir "vcusd\flamerobin"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MTd /Zi /Gm /GZ /Fdvcusd\flamerobin.pdb /Od /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_lib\mswud" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcusd\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_DEBUG" /D "_UNICODE" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD CPP /nologo /FD /MTd /Zi /Gm /GZ /Fdvcusd\flamerobin.pdb /Od /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_lib\mswud" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcusd\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_DEBUG" /D "_UNICODE" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "_UNICODE" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "_UNICODE" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_UNICODE" /d "__WXDEBUG__" /d "_DEBUG" /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_lib\mswud" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
# ADD RSC /l 0x409 /d "_DEBUG" /d "_UNICODE" /d "__WXDEBUG__" /d "_DEBUG" /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_lib\mswud" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw28ud_stc.lib wxmsw28ud_html.lib wxmsw28ud_adv.lib wxmsw28ud_core.lib wxbase28ud_xml.lib wxbase28ud.lib wxregexud.lib wxexpatd.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcusd\ibpp.lib /nologo /machine:i386 /out:"vcusd\flamerobin.exe" /debug /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_lib" /subsystem:windows
# ADD LINK32 wxmsw28ud_stc.lib wxmsw28ud_html.lib wxmsw28ud_adv.lib wxmsw28ud_core.lib wxbase28ud_xml.lib wxbase28ud.lib wxregexud.lib wxexpatd.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcusd\ibpp.lib /nologo /machine:i386 /out:"vcusd\flamerobin.exe" /debug /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_lib" /subsystem:windows

!ELSEIF  "$(CFG)" == "flamerobin - Win32 Unicode Debug Dynamic"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vcud"
# PROP BASE Intermediate_Dir "vcud\flamerobin"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vcud"
# PROP Intermediate_Dir "vcud\flamerobin"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdvcud\flamerobin.pdb /Od /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_lib\mswud" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcud\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_DEBUG" /D "_UNICODE" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdvcud\flamerobin.pdb /Od /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_lib\mswud" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcud\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_DEBUG" /D "_UNICODE" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "_UNICODE" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "_UNICODE" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_UNICODE" /d "__WXDEBUG__" /d "_DEBUG" /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_lib\mswud" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
# ADD RSC /l 0x409 /d "_DEBUG" /d "_UNICODE" /d "__WXDEBUG__" /d "_DEBUG" /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_lib\mswud" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw28ud_stc.lib wxmsw28ud_html.lib wxmsw28ud_adv.lib wxmsw28ud_core.lib wxbase28ud_xml.lib wxbase28ud.lib wxregexud.lib wxexpatd.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcud\ibpp.lib /nologo /machine:i386 /out:"vcud\flamerobin.exe" /debug /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_lib" /subsystem:windows
# ADD LINK32 wxmsw28ud_stc.lib wxmsw28ud_html.lib wxmsw28ud_adv.lib wxmsw28ud_core.lib wxbase28ud_xml.lib wxbase28ud.lib wxregexud.lib wxexpatd.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcud\ibpp.lib /nologo /machine:i386 /out:"vcud\flamerobin.exe" /debug /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_lib" /subsystem:windows

!ELSEIF  "$(CFG)" == "flamerobin - Win32 Release Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vcs"
# PROP BASE Intermediate_Dir "vcs\flamerobin"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vcs"
# PROP Intermediate_Dir "vcs\flamerobin"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MT /Fdvcs\flamerobin.pdb /O1 /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_lib\msw" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcs\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD CPP /nologo /FD /MT /Fdvcs\flamerobin.pdb /O1 /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_lib\msw" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcs\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_lib\msw" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
# ADD RSC /l 0x409 /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_lib\msw" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw28_stc.lib wxmsw28_html.lib wxmsw28_adv.lib wxmsw28_core.lib wxbase28_xml.lib wxbase28.lib wxregex.lib wxexpat.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcs\ibpp.lib /nologo /machine:i386 /out:"vcs\flamerobin.exe" /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_lib" /subsystem:windows
# ADD LINK32 wxmsw28_stc.lib wxmsw28_html.lib wxmsw28_adv.lib wxmsw28_core.lib wxbase28_xml.lib wxbase28.lib wxregex.lib wxexpat.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcs\ibpp.lib /nologo /machine:i386 /out:"vcs\flamerobin.exe" /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_lib" /subsystem:windows

!ELSEIF  "$(CFG)" == "flamerobin - Win32 Release Dynamic"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vc"
# PROP BASE Intermediate_Dir "vc\flamerobin"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vc"
# PROP Intermediate_Dir "vc\flamerobin"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdvc\flamerobin.pdb /O1 /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_lib\msw" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vc\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD CPP /nologo /FD /MD /Fdvc\flamerobin.pdb /O1 /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_lib\msw" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vc\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_lib\msw" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
# ADD RSC /l 0x409 /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_lib\msw" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw28_stc.lib wxmsw28_html.lib wxmsw28_adv.lib wxmsw28_core.lib wxbase28_xml.lib wxbase28.lib wxregex.lib wxexpat.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vc\ibpp.lib /nologo /machine:i386 /out:"vc\flamerobin.exe" /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_lib" /subsystem:windows
# ADD LINK32 wxmsw28_stc.lib wxmsw28_html.lib wxmsw28_adv.lib wxmsw28_core.lib wxbase28_xml.lib wxbase28.lib wxregex.lib wxexpat.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vc\ibpp.lib /nologo /machine:i386 /out:"vc\flamerobin.exe" /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_lib" /subsystem:windows

!ELSEIF  "$(CFG)" == "flamerobin - Win32 Debug Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vcsd"
# PROP BASE Intermediate_Dir "vcsd\flamerobin"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vcsd"
# PROP Intermediate_Dir "vcsd\flamerobin"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MTd /Zi /Gm /GZ /Fdvcsd\flamerobin.pdb /Od /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_lib\mswd" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcsd\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_DEBUG" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD CPP /nologo /FD /MTd /Zi /Gm /GZ /Fdvcsd\flamerobin.pdb /Od /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_lib\mswd" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcsd\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_DEBUG" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "__WXDEBUG__" /d "_DEBUG" /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_lib\mswd" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
# ADD RSC /l 0x409 /d "_DEBUG" /d "__WXDEBUG__" /d "_DEBUG" /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_lib\mswd" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw28d_stc.lib wxmsw28d_html.lib wxmsw28d_adv.lib wxmsw28d_core.lib wxbase28d_xml.lib wxbase28d.lib wxregexd.lib wxexpatd.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcsd\ibpp.lib /nologo /machine:i386 /out:"vcsd\flamerobin.exe" /debug /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_lib" /subsystem:windows
# ADD LINK32 wxmsw28d_stc.lib wxmsw28d_html.lib wxmsw28d_adv.lib wxmsw28d_core.lib wxbase28d_xml.lib wxbase28d.lib wxregexd.lib wxexpatd.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcsd\ibpp.lib /nologo /machine:i386 /out:"vcsd\flamerobin.exe" /debug /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_lib" /subsystem:windows

!ELSEIF  "$(CFG)" == "flamerobin - Win32 Debug Dynamic"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vcd"
# PROP BASE Intermediate_Dir "vcd\flamerobin"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vcd"
# PROP Intermediate_Dir "vcd\flamerobin"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdvcd\flamerobin.pdb /Od /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_lib\mswd" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcd\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_DEBUG" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdvcd\flamerobin.pdb /Od /GR /EHsc /W4 /I "$(WXDIR)\lib\vc_lib\mswd" /I "$(WXDIR)\contrib\include" /I "$(WXDIR)\include" /Yu"wx/wxprec.h" /Fp"vcd\flamerobin.pch" /I "$(BOOST_ROOT)" /I ".\src" /I ".\src\ibpp" /I ".\res" /D "WIN32" /D "_DEBUG" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXDEBUG__" /D "_DEBUG" /D "_WINDOWS" /D "__WINDOWS__" /D WINVER=0x400 /D "WIN32" /D "__WIN32__" /D "__WIN95__" /D "STRICT" /D "__WXMSW__" /D wxUSE_GUI=1 /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "IBPP_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "__WXDEBUG__" /d "_DEBUG" /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_lib\mswd" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
# ADD RSC /l 0x409 /d "_DEBUG" /d "__WXDEBUG__" /d "_DEBUG" /d "_WINDOWS" /d "__WINDOWS__" /d WINVER=0x400 /d "WIN32" /d "__WIN32__" /d "__WIN95__" /d "STRICT" /d "__WXMSW__" /d wxUSE_GUI=1 /d "WIN32_LEAN_AND_MEAN" /i "$(WXDIR)\lib\vc_lib\mswd" /i "$(WXDIR)\contrib\include" /i "$(WXDIR)\include" /d "_WINDOWS" /d "IBPP_WINDOWS" /i "$(BOOST_ROOT)" /i ".\src" /i ".\src\ibpp" /i .\res
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw28d_stc.lib wxmsw28d_html.lib wxmsw28d_adv.lib wxmsw28d_core.lib wxbase28d_xml.lib wxbase28d.lib wxregexd.lib wxexpatd.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcd\ibpp.lib /nologo /machine:i386 /out:"vcd\flamerobin.exe" /debug /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_lib" /subsystem:windows
# ADD LINK32 wxmsw28d_stc.lib wxmsw28d_html.lib wxmsw28d_adv.lib wxmsw28d_core.lib wxbase28d_xml.lib wxbase28d.lib wxregexd.lib wxexpatd.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib rpcrt4.lib wsock32.lib vcd\ibpp.lib /nologo /machine:i386 /out:"vcd\flamerobin.exe" /debug /nologo /subsystem:windows /machine:I386 /libpath:"$(WXDIR)\lib\vc_lib" /subsystem:windows

!ENDIF

# Begin Target

# Name "flamerobin - Win32 DLL Unicode Release Static"
# Name "flamerobin - Win32 DLL Unicode Release Dynamic"
# Name "flamerobin - Win32 DLL Unicode Debug Static"
# Name "flamerobin - Win32 DLL Unicode Debug Dynamic"
# Name "flamerobin - Win32 DLL Release Static"
# Name "flamerobin - Win32 DLL Release Dynamic"
# Name "flamerobin - Win32 DLL Debug Static"
# Name "flamerobin - Win32 DLL Debug Dynamic"
# Name "flamerobin - Win32 Unicode Release Static"
# Name "flamerobin - Win32 Unicode Release Dynamic"
# Name "flamerobin - Win32 Unicode Debug Static"
# Name "flamerobin - Win32 Unicode Debug Dynamic"
# Name "flamerobin - Win32 Release Static"
# Name "flamerobin - Win32 Release Dynamic"
# Name "flamerobin - Win32 Debug Static"
# Name "flamerobin - Win32 Debug Dynamic"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Application.cpp
# End Source File
# Begin Source File

SOURCE=.\src\core\ArtProvider.cpp
# End Source File
# Begin Source File

SOURCE=.\src\gui\BaseFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\src\hierarchy\Column.cpp
# End Source File
# Begin Source File

SOURCE=.\src\config\Config.cpp
# End Source File
# Begin Source File

SOURCE=.\src\gui\controls\DBHTreeControl.cpp
# End Source File
# Begin Source File

SOURCE=.\src\gui\controls\DBHTreeControlContextMenuCreator.cpp
# End Source File
# Begin Source File

SOURCE=.\src\hierarchy\Database.cpp
# End Source File
# Begin Source File

SOURCE=.\src\commands\DatabaseCommands.cpp
# End Source File
# Begin Source File

SOURCE=.\src\engine\DatabaseConnection.cpp
# End Source File
# Begin Source File

SOURCE=.\src\core\FRError.cpp
# End Source File
# Begin Source File

SOURCE=.\src\gui\FrameManager.cpp
# End Source File
# Begin Source File

SOURCE=.\src\hierarchy\Function.cpp
# End Source File
# Begin Source File

SOURCE=.\src\commands\FunctionCommands.cpp
# End Source File
# Begin Source File

SOURCE=.\src\hierarchy\Generator.cpp
# End Source File
# Begin Source File

SOURCE=.\src\commands\GeneratorCommands.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sql\Identifier.cpp
# End Source File
# Begin Source File

SOURCE=.\src\hierarchy\Item.cpp
# End Source File
# Begin Source File

SOURCE=.\src\commands\ItemCommands.cpp
# End Source File
# Begin Source File

SOURCE=.\src\hierarchy\ItemVisitor.cpp
# End Source File
# Begin Source File

SOURCE=.\src\gui\MainFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\src\core\Observer.cpp
# End Source File
# Begin Source File

SOURCE=.\src\PCH.cpp
# ADD BASE CPP /Yc"wx/wxprec.h"
# ADD CPP /Yc"wx/wxprec.h"
# End Source File
# Begin Source File

SOURCE=.\src\hierarchy\Procedure.cpp
# End Source File
# Begin Source File

SOURCE=.\src\commands\ProcedureCommands.cpp
# End Source File
# Begin Source File

SOURCE=.\src\hierarchy\Relation.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sql\SqlTokenizer.cpp
# End Source File
# Begin Source File

SOURCE=.\src\core\StringUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\src\gui\StyleGuide.cpp
# End Source File
# Begin Source File

SOURCE=.\src\gui\msw\StyleGuideMSW.cpp
# End Source File
# Begin Source File

SOURCE=.\src\core\Subject.cpp
# End Source File
# Begin Source File

SOURCE=.\src\hierarchy\Table.cpp
# End Source File
# Begin Source File

SOURCE=.\src\commands\TableCommands.cpp
# End Source File
# Begin Source File

SOURCE=.\src\hierarchy\TreeFolder.cpp
# End Source File
# Begin Source File

SOURCE=.\src\hierarchy\TreeRoot.cpp
# End Source File
# Begin Source File

SOURCE=.\src\hierarchy\Trigger.cpp
# End Source File
# Begin Source File

SOURCE=.\src\commands\TriggerCommands.cpp
# End Source File
# Begin Source File

SOURCE=.\src\hierarchy\View.cpp
# End Source File
# Begin Source File

SOURCE=.\src\engine\WorkerThread.cpp
# End Source File
# Begin Source File

SOURCE=.\res\flamerobin.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Application.h
# End Source File
# Begin Source File

SOURCE=.\src\core\ArtProvider.h
# End Source File
# Begin Source File

SOURCE=.\src\gui\BaseFrame.h
# End Source File
# Begin Source File

SOURCE=.\src\hierarchy\Column.h
# End Source File
# Begin Source File

SOURCE=.\src\core\CommandIds.h
# End Source File
# Begin Source File

SOURCE=.\src\config\Config.h
# End Source File
# Begin Source File

SOURCE=.\src\gui\controls\DBHTreeControl.h
# End Source File
# Begin Source File

SOURCE=.\src\gui\controls\DBHTreeControlContextMenuCreator.h
# End Source File
# Begin Source File

SOURCE=.\src\hierarchy\Database.h
# End Source File
# Begin Source File

SOURCE=.\src\engine\DatabaseConnection.h
# End Source File
# Begin Source File

SOURCE=.\src\core\FRError.h
# End Source File
# Begin Source File

SOURCE=.\src\gui\FrameManager.h
# End Source File
# Begin Source File

SOURCE=.\src\hierarchy\Function.h
# End Source File
# Begin Source File

SOURCE=.\src\hierarchy\Generator.h
# End Source File
# Begin Source File

SOURCE=.\src\sql\Identifier.h
# End Source File
# Begin Source File

SOURCE=.\src\hierarchy\Item.h
# End Source File
# Begin Source File

SOURCE=.\src\commands\ItemCommands.h
# End Source File
# Begin Source File

SOURCE=.\src\hierarchy\ItemVisitor.h
# End Source File
# Begin Source File

SOURCE=.\src\gui\MainFrame.h
# End Source File
# Begin Source File

SOURCE=.\src\core\Observer.h
# End Source File
# Begin Source File

SOURCE=.\src\hierarchy\Procedure.h
# End Source File
# Begin Source File

SOURCE=.\src\hierarchy\Relation.h
# End Source File
# Begin Source File

SOURCE=.\src\hierarchy\SharedItems.h
# End Source File
# Begin Source File

SOURCE=.\src\sql\SqlTokenizer.h
# End Source File
# Begin Source File

SOURCE=.\src\core\StringUtils.h
# End Source File
# Begin Source File

SOURCE=.\src\gui\StyleGuide.h
# End Source File
# Begin Source File

SOURCE=.\src\core\Subject.h
# End Source File
# Begin Source File

SOURCE=.\src\hierarchy\Table.h
# End Source File
# Begin Source File

SOURCE=.\src\hierarchy\TreeFolder.h
# End Source File
# Begin Source File

SOURCE=.\src\hierarchy\TreeRoot.h
# End Source File
# Begin Source File

SOURCE=.\src\hierarchy\Trigger.h
# End Source File
# Begin Source File

SOURCE=.\src\Version.h
# End Source File
# Begin Source File

SOURCE=.\src\hierarchy\View.h
# End Source File
# Begin Source File

SOURCE=.\src\core\Visitor.h
# End Source File
# Begin Source File

SOURCE=.\src\engine\WorkerThread.h
# End Source File
# End Group
# End Target
# End Project

