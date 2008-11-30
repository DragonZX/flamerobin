# Microsoft Developer Studio Project File - Name="flamerobin_ibpp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ibpp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "flamerobin_ibpp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "flamerobin_ibpp.mak" CFG="ibpp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ibpp - Win32 DLL Unicode Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ibpp - Win32 DLL Unicode Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ibpp - Win32 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ibpp - Win32 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ibpp - Win32 Unicode Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ibpp - Win32 Unicode Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ibpp - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ibpp - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ibpp - Win32 DLL Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vcu"
# PROP BASE Intermediate_Dir "vcu\ibpp"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vcu"
# PROP Intermediate_Dir "vcu\ibpp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdvcu\ibpp.pdb /O1 /GR /EHsc /W4 /Yu"_ibpp.h" /Fp"vcu\ibpp.pch" /I ".\src\ibpp" /D "WIN32" /D "_LIB" /D "IBPP_WINDOWS" /c
# ADD CPP /nologo /FD /MD /Fdvcu\ibpp.pdb /O1 /GR /EHsc /W4 /Yu"_ibpp.h" /Fp"vcu\ibpp.pch" /I ".\src\ibpp" /D "WIN32" /D "_LIB" /D "IBPP_WINDOWS" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"vcu\ibpp.lib"
# ADD LIB32 /nologo /out:"vcu\ibpp.lib"

!ELSEIF  "$(CFG)" == "ibpp - Win32 DLL Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vcud"
# PROP BASE Intermediate_Dir "vcud\ibpp"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vcud"
# PROP Intermediate_Dir "vcud\ibpp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Fdvcud\ibpp.pdb /Od /Gm /GR /EHsc /W4 /Yu"_ibpp.h" /Fp"vcud\ibpp.pch" /I ".\src\ibpp" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "IBPP_WINDOWS" /c
# ADD CPP /nologo /FD /MDd /Zi /Fdvcud\ibpp.pdb /Od /Gm /GR /EHsc /W4 /Yu"_ibpp.h" /Fp"vcud\ibpp.pch" /I ".\src\ibpp" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "IBPP_WINDOWS" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"vcud\ibpp.lib"
# ADD LIB32 /nologo /out:"vcud\ibpp.lib"

!ELSEIF  "$(CFG)" == "ibpp - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vc"
# PROP BASE Intermediate_Dir "vc\ibpp"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vc"
# PROP Intermediate_Dir "vc\ibpp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdvc\ibpp.pdb /O1 /GR /EHsc /W4 /Yu"_ibpp.h" /Fp"vc\ibpp.pch" /I ".\src\ibpp" /D "WIN32" /D "_LIB" /D "IBPP_WINDOWS" /c
# ADD CPP /nologo /FD /MD /Fdvc\ibpp.pdb /O1 /GR /EHsc /W4 /Yu"_ibpp.h" /Fp"vc\ibpp.pch" /I ".\src\ibpp" /D "WIN32" /D "_LIB" /D "IBPP_WINDOWS" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"vc\ibpp.lib"
# ADD LIB32 /nologo /out:"vc\ibpp.lib"

!ELSEIF  "$(CFG)" == "ibpp - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vcd"
# PROP BASE Intermediate_Dir "vcd\ibpp"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vcd"
# PROP Intermediate_Dir "vcd\ibpp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Fdvcd\ibpp.pdb /Od /Gm /GR /EHsc /W4 /Yu"_ibpp.h" /Fp"vcd\ibpp.pch" /I ".\src\ibpp" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "IBPP_WINDOWS" /c
# ADD CPP /nologo /FD /MDd /Zi /Fdvcd\ibpp.pdb /Od /Gm /GR /EHsc /W4 /Yu"_ibpp.h" /Fp"vcd\ibpp.pch" /I ".\src\ibpp" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "IBPP_WINDOWS" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"vcd\ibpp.lib"
# ADD LIB32 /nologo /out:"vcd\ibpp.lib"

!ELSEIF  "$(CFG)" == "ibpp - Win32 Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vcu"
# PROP BASE Intermediate_Dir "vcu\ibpp"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vcu"
# PROP Intermediate_Dir "vcu\ibpp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdvcu\ibpp.pdb /O1 /GR /EHsc /W4 /Yu"_ibpp.h" /Fp"vcu\ibpp.pch" /I ".\src\ibpp" /D "WIN32" /D "_LIB" /D "IBPP_WINDOWS" /c
# ADD CPP /nologo /FD /MD /Fdvcu\ibpp.pdb /O1 /GR /EHsc /W4 /Yu"_ibpp.h" /Fp"vcu\ibpp.pch" /I ".\src\ibpp" /D "WIN32" /D "_LIB" /D "IBPP_WINDOWS" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"vcu\ibpp.lib"
# ADD LIB32 /nologo /out:"vcu\ibpp.lib"

!ELSEIF  "$(CFG)" == "ibpp - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vcud"
# PROP BASE Intermediate_Dir "vcud\ibpp"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vcud"
# PROP Intermediate_Dir "vcud\ibpp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Fdvcud\ibpp.pdb /Od /Gm /GR /EHsc /W4 /Yu"_ibpp.h" /Fp"vcud\ibpp.pch" /I ".\src\ibpp" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "IBPP_WINDOWS" /c
# ADD CPP /nologo /FD /MDd /Zi /Fdvcud\ibpp.pdb /Od /Gm /GR /EHsc /W4 /Yu"_ibpp.h" /Fp"vcud\ibpp.pch" /I ".\src\ibpp" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "IBPP_WINDOWS" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"vcud\ibpp.lib"
# ADD LIB32 /nologo /out:"vcud\ibpp.lib"

!ELSEIF  "$(CFG)" == "ibpp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vc"
# PROP BASE Intermediate_Dir "vc\ibpp"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vc"
# PROP Intermediate_Dir "vc\ibpp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdvc\ibpp.pdb /O1 /GR /EHsc /W4 /Yu"_ibpp.h" /Fp"vc\ibpp.pch" /I ".\src\ibpp" /D "WIN32" /D "_LIB" /D "IBPP_WINDOWS" /c
# ADD CPP /nologo /FD /MD /Fdvc\ibpp.pdb /O1 /GR /EHsc /W4 /Yu"_ibpp.h" /Fp"vc\ibpp.pch" /I ".\src\ibpp" /D "WIN32" /D "_LIB" /D "IBPP_WINDOWS" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"vc\ibpp.lib"
# ADD LIB32 /nologo /out:"vc\ibpp.lib"

!ELSEIF  "$(CFG)" == "ibpp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vcd"
# PROP BASE Intermediate_Dir "vcd\ibpp"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vcd"
# PROP Intermediate_Dir "vcd\ibpp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Fdvcd\ibpp.pdb /Od /Gm /GR /EHsc /W4 /Yu"_ibpp.h" /Fp"vcd\ibpp.pch" /I ".\src\ibpp" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "IBPP_WINDOWS" /c
# ADD CPP /nologo /FD /MDd /Zi /Fdvcd\ibpp.pdb /Od /Gm /GR /EHsc /W4 /Yu"_ibpp.h" /Fp"vcd\ibpp.pch" /I ".\src\ibpp" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "IBPP_WINDOWS" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"vcd\ibpp.lib"
# ADD LIB32 /nologo /out:"vcd\ibpp.lib"

!ENDIF

# Begin Target

# Name "ibpp - Win32 DLL Unicode Release"
# Name "ibpp - Win32 DLL Unicode Debug"
# Name "ibpp - Win32 DLL Release"
# Name "ibpp - Win32 DLL Debug"
# Name "ibpp - Win32 Unicode Release"
# Name "ibpp - Win32 Unicode Debug"
# Name "ibpp - Win32 Release"
# Name "ibpp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\ibpp\_dpb.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ibpp\_ibpp.cpp
# ADD BASE CPP /Yc"_ibpp.h"
# ADD CPP /Yc"_ibpp.h"
# End Source File
# Begin Source File

SOURCE=.\src\ibpp\_ibs.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ibpp\_rb.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ibpp\_spb.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ibpp\_tpb.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ibpp\array.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ibpp\blob.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ibpp\database.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ibpp\date.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ibpp\dbkey.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ibpp\events.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ibpp\exception.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ibpp\row.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ibpp\service.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ibpp\statement.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ibpp\time.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ibpp\transaction.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ibpp\user.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\ibpp\_ibpp.h
# End Source File
# Begin Source File

SOURCE=.\src\ibpp\ibase.h
# End Source File
# Begin Source File

SOURCE=.\src\ibpp\iberror.h
# End Source File
# Begin Source File

SOURCE=.\src\ibpp\ibpp.h
# End Source File
# End Group
# End Target
# End Project

