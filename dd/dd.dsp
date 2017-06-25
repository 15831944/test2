# Microsoft Developer Studio Project File - Name="dd" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=dd - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dd.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dd.mak" CFG="dd - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dd - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "dd - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dd - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "dd - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../Inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"../Inc"

!ENDIF 

# Begin Target

# Name "dd - Win32 Release"
# Name "dd - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\dd.cpp
# End Source File
# Begin Source File

SOURCE=.\dd.rc
# End Source File
# Begin Source File

SOURCE=.\ddDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\Inc\control\dialogheader.cpp
# ADD CPP /I "..\..\dd"
# End Source File
# Begin Source File

SOURCE=.\Page\Page.cpp
# End Source File
# Begin Source File

SOURCE=.\Page\Page1.cpp
# End Source File
# Begin Source File

SOURCE=.\Page\Page2.cpp
# End Source File
# Begin Source File

SOURCE=.\Page\Page3.cpp
# End Source File
# Begin Source File

SOURCE=.\PubClass.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\dd.h
# End Source File
# Begin Source File

SOURCE=.\ddDlg.h
# End Source File
# Begin Source File

SOURCE=..\Inc\control\dialogheader.h
# End Source File
# Begin Source File

SOURCE=.\Page\Page.h
# End Source File
# Begin Source File

SOURCE=.\Page\Page1.h
# End Source File
# Begin Source File

SOURCE=.\Page\Page2.h
# End Source File
# Begin Source File

SOURCE=.\Page\Page3.h
# End Source File
# Begin Source File

SOURCE=.\PubClass.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\background.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bk.bmp
# End Source File
# Begin Source File

SOURCE=.\res\dd.ico
# End Source File
# Begin Source File

SOURCE=.\res\dd.rc2
# End Source File
# Begin Source File

SOURCE=.\res\header.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pig.bmp
# End Source File
# Begin Source File

SOURCE=.\res\search1.ico
# End Source File
# Begin Source File

SOURCE=".\res\±¨¾¯µÆ-1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\±¨¾¯µÆ-2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\±¨¾¯µÆ-3.bmp"
# End Source File
# End Group
# Begin Group "Dialog"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Wnd\BasicWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\Wnd\BasicWnd.h
# End Source File
# Begin Source File

SOURCE=.\Wnd\dlgcalendarctrl.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Wnd\dlgcalendarctrl.h
# End Source File
# Begin Source File

SOURCE=.\Wnd\DlgSpy.cpp
# End Source File
# Begin Source File

SOURCE=.\Wnd\DlgSpy.h
# End Source File
# Begin Source File

SOURCE=.\Wnd\SubFrom.cpp
# End Source File
# Begin Source File

SOURCE=.\Wnd\SubFrom.h
# End Source File
# End Group
# Begin Group "Inc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Inc\base\Character.cpp
# End Source File
# Begin Source File

SOURCE=..\Inc\base\Character.h
# End Source File
# Begin Source File

SOURCE=..\Inc\base\CommonFun.cpp
# End Source File
# Begin Source File

SOURCE=..\Inc\base\CommonFun.h
# End Source File
# Begin Source File

SOURCE=..\Inc\base\Console.cpp
# End Source File
# Begin Source File

SOURCE=..\Inc\base\Console.h
# End Source File
# Begin Source File

SOURCE=..\Inc\base\Directory.cpp
# End Source File
# Begin Source File

SOURCE=..\Inc\base\Directory.h
# End Source File
# Begin Source File

SOURCE=..\Inc\base\Driver.cpp
# End Source File
# Begin Source File

SOURCE=..\Inc\base\Driver.h
# End Source File
# Begin Source File

SOURCE=..\Inc\base\Global.h
# End Source File
# Begin Source File

SOURCE=..\Inc\base\IniFile.cpp
# End Source File
# Begin Source File

SOURCE=..\Inc\base\IniFile.h
# End Source File
# Begin Source File

SOURCE=..\Inc\base\MemDC.h
# End Source File
# Begin Source File

SOURCE=..\Inc\base\PEFile.cpp
# End Source File
# Begin Source File

SOURCE=..\Inc\base\PEFile.h
# End Source File
# Begin Source File

SOURCE=..\Inc\base\Picture.cpp
# End Source File
# Begin Source File

SOURCE=..\Inc\base\Picture.h
# End Source File
# Begin Source File

SOURCE=..\Inc\base\SystemUtility.cpp
# End Source File
# Begin Source File

SOURCE=..\Inc\base\SystemUtility.h
# End Source File
# Begin Source File

SOURCE=..\Inc\control\Track.cpp
# End Source File
# Begin Source File

SOURCE=..\Inc\control\Track.h
# End Source File
# Begin Source File

SOURCE=..\Inc\base\Wave.cpp
# End Source File
# Begin Source File

SOURCE=..\Inc\base\Wave.h
# End Source File
# End Group
# Begin Group "Control"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Wnd\CalendarCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Wnd\CalendarCtrl.h
# End Source File
# Begin Source File

SOURCE=..\Inc\control\CustomEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\Inc\control\CustomEdit.h
# End Source File
# Begin Source File

SOURCE=.\Wnd\TipWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\Wnd\TipWnd.h
# End Source File
# Begin Source File

SOURCE=..\Inc\control\XPButton.cpp
# End Source File
# Begin Source File

SOURCE=..\Inc\control\XPButton.h
# End Source File
# Begin Source File

SOURCE=..\Inc\control\xSkinButton.cpp
# End Source File
# Begin Source File

SOURCE=..\Inc\control\xSkinButton.h
# End Source File
# End Group
# Begin Group "XML"

# PROP Default_Filter ""
# Begin Group "tinyXML"

# PROP Default_Filter ""
# End Group
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
