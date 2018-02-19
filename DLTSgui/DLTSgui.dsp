# Microsoft Developer Studio Project File - Name="DLTSgui" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DLTSgui - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DLTSgui.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DLTSgui.mak" CFG="DLTSgui - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DLTSgui - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DLTSgui - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DLTSgui - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 nidaq32.lib gpib-32.obj /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "DLTSgui - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 nidaq32.lib gpib-32.obj /nologo /subsystem:windows /map /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "DLTSgui - Win32 Release"
# Name "DLTSgui - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Boonton7200.cpp
# End Source File
# Begin Source File

SOURCE=.\BoontonRange.cpp
# End Source File
# Begin Source File

SOURCE=.\BufferedFileWriter.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ComHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\Console.cpp
# End Source File
# Begin Source File

SOURCE=.\DAQDevice.cpp
# End Source File
# Begin Source File

SOURCE=.\DataArray.cpp
# End Source File
# Begin Source File

SOURCE=.\DataArrayList.cpp
# End Source File
# Begin Source File

SOURCE=.\DataElement.cpp
# End Source File
# Begin Source File

SOURCE=.\DataHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\DLTSdevice.cpp
# End Source File
# Begin Source File

SOURCE=.\DLTSgui.cpp
# End Source File
# Begin Source File

SOURCE=.\DLTSgui.rc
# End Source File
# Begin Source File

SOURCE=.\DLTSguiDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\DLTSguiView.cpp
# End Source File
# Begin Source File

SOURCE=.\FileWriter.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\HardwareException.cpp
# End Source File
# Begin Source File

SOURCE=.\ListFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SIZECBAR.CPP
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StringTokenizer.cpp
# End Source File
# Begin Source File

SOURCE=.\TempController.cpp
# End Source File
# Begin Source File

SOURCE=.\VoltageOutDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\WorkspaceWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\Writer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Boonton7200.h
# End Source File
# Begin Source File

SOURCE=.\BoontonRange.h
# End Source File
# Begin Source File

SOURCE=.\BufferedFileWriter.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\ComHandler.h
# End Source File
# Begin Source File

SOURCE=.\Console.h
# End Source File
# Begin Source File

SOURCE=.\DAQDevice.h
# End Source File
# Begin Source File

SOURCE=.\DataArray.h
# End Source File
# Begin Source File

SOURCE=.\DataArrayList.h
# End Source File
# Begin Source File

SOURCE=.\DataElement.h
# End Source File
# Begin Source File

SOURCE=.\DataHandler.h
# End Source File
# Begin Source File

SOURCE=.\DltsConstants.h
# End Source File
# Begin Source File

SOURCE=.\DLTSdevice.h
# End Source File
# Begin Source File

SOURCE=.\DLTSgui.h
# End Source File
# Begin Source File

SOURCE=.\DLTSguiDoc.h
# End Source File
# Begin Source File

SOURCE=.\DLTSguiView.h
# End Source File
# Begin Source File

SOURCE=.\FileWriter.h
# End Source File
# Begin Source File

SOURCE=.\GraphProperties.h
# End Source File
# Begin Source File

SOURCE=.\HardwareException.h
# End Source File
# Begin Source File

SOURCE=.\ListFrame.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\PropertyDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\sizecbar.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StringTokenizer.h
# End Source File
# Begin Source File

SOURCE=.\TempController.h
# End Source File
# Begin Source File

SOURCE=.\VoltageOutDialog.h
# End Source File
# Begin Source File

SOURCE=.\WorkspaceWnd.h
# End Source File
# Begin Source File

SOURCE=.\Writer.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\C_t_messGUI.ico
# End Source File
# Begin Source File

SOURCE=.\res\dlts.ico
# End Source File
# Begin Source File

SOURCE=.\res\DLTSgui.ico
# End Source File
# Begin Source File

SOURCE=.\res\DLTSgui.rc2
# End Source File
# Begin Source File

SOURCE=.\res\DLTSguiDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\term.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\DLTSgui.reg
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
