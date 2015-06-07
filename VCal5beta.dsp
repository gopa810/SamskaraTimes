# Microsoft Developer Studio Project File - Name="VCal5beta" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=VCal5beta - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCal5beta.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCal5beta.mak" CFG="VCal5beta - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VCal5beta - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "VCal5beta - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "VCal5beta - Win32 Release Beta" (based on "Win32 (x86) Application")
!MESSAGE "VCal5beta - Win32 Release Bhanu Swami" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VCal5beta - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "C:\Program Files\HTML Help Workshop\include\\" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"../gcal-release/" /Fp"../gcal-release/VCal5beta.pch" /Yu"stdafx.h" /Fo"../gcal-release/" /Fd"../gcal-release/" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41b /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x41b /fo"../gcal-release/gcal.res" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../gcal-release/gcal.bsc"
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 Htmlhelp.lib /nologo /subsystem:windows /machine:I386 /out:"../gcal-release/gcal.exe" /libpath:"C:\Program Files\HTML Help Workshop\lib\\"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "VCal5beta - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "C:\Program Files\HTML Help Workshop\include\\" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"../gcal-debug/" /Fp"../gcal-debug/VCal5beta.pch" /Yu"stdafx.h" /Fo"../gcal-debug/" /Fd"../gcal-debug/" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41b /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x41b /fo"../gcal-debug/gcal.res" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../gcal-debug/gcal.bsc"
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Htmlhelp.lib /nologo /subsystem:windows /pdb:"../gcal-debug/gcal.pdb" /debug /machine:I386 /out:"../gcal-debug/gcal.exe" /pdbtype:sept /libpath:"C:\Program Files\HTML Help Workshop\lib\\"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "VCal5beta - Win32 Release Beta"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "VCal5beta___Win32_Release_Beta"
# PROP BASE Intermediate_Dir "VCal5beta___Win32_Release_Beta"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "VCal5beta___Win32_Release_Beta"
# PROP Intermediate_Dir "VCal5beta___Win32_Release_Beta"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "GCAL_BETA" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41b /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x41b /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"Release/gcal.exe"
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"Release/gcal-beta1.exe"

!ELSEIF  "$(CFG)" == "VCal5beta - Win32 Release Bhanu Swami"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "VCal5beta___Win32_Release_Bhanu_Swami"
# PROP BASE Intermediate_Dir "VCal5beta___Win32_Release_Bhanu_Swami"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "VCal5beta___Win32_Release_Bhanu_Swami"
# PROP Intermediate_Dir "VCal5beta___Win32_Release_Bhanu_Swami"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "BHANU_SWAMI_" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41b /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x41b /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"Release/gcal.exe"
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"Release Bhanu Swami/gcal.exe"

!ENDIF 

# Begin Target

# Name "VCal5beta - Win32 Release"
# Name "VCal5beta - Win32 Debug"
# Name "VCal5beta - Win32 Release Beta"
# Name "VCal5beta - Win32 Release Bhanu Swami"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\astro_html.cpp
# End Source File
# Begin Source File

SOURCE=.\avc.cpp
# End Source File
# Begin Source File

SOURCE=.\CommandLineVCal.cpp
# End Source File
# Begin Source File

SOURCE=.\ConditionsView.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\DayFindBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAskLimitation.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCalcProgress.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCustomEventDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEditCustomEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEditLocation.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEditString.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEventsGaubdTM.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEventsGetText.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEventsTypeOfEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGetDate.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGetEndDate.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGetEventSpec.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGetLocation.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGetLocationEx.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMasaListing.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgObservedEvents.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRenameCountry.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSelectLangOutput.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSetAyanamsaType.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSetPrintStyle.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSpecCommand.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgStringManager.cpp
# End Source File
# Begin Source File

SOURCE=.\DNewCountry.cpp
# End Source File
# Begin Source File

SOURCE=.\DPageAstro.cpp
# End Source File
# Begin Source File

SOURCE=.\DPageAstroVedic.cpp
# End Source File
# Begin Source File

SOURCE=.\DPageFest.cpp
# End Source File
# Begin Source File

SOURCE=.\DPageGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\EditClipboarded.cpp
# End Source File
# Begin Source File

SOURCE=.\EventsHtmlView.cpp
# End Source File
# Begin Source File

SOURCE=.\FrameBase.cpp
# End Source File
# Begin Source File

SOURCE=.\FrameEvents.cpp
# End Source File
# Begin Source File

SOURCE=.\FrameFind.cpp
# End Source File
# Begin Source File

SOURCE=.\FrameLocs.cpp
# End Source File
# Begin Source File

SOURCE=.\FrameMain.cpp
# End Source File
# Begin Source File

SOURCE=.\FrameServer.cpp
# End Source File
# Begin Source File

SOURCE=.\gcal_evx.cpp
# End Source File
# Begin Source File

SOURCE=.\globvar.cpp
# End Source File
# Begin Source File

SOURCE=.\gmath.cpp
# End Source File
# Begin Source File

SOURCE=.\init_tips.cpp
# End Source File
# Begin Source File

SOURCE=.\level_0.cpp
# End Source File
# Begin Source File

SOURCE=.\level_1_moon.cpp
# End Source File
# Begin Source File

SOURCE=.\level_1_sun.cpp
# End Source File
# Begin Source File

SOURCE=.\level_2_conj.cpp
# End Source File
# Begin Source File

SOURCE=.\level_2_tithi.cpp
# End Source File
# Begin Source File

SOURCE=.\level_3.cpp
# End Source File
# Begin Source File

SOURCE=.\level_4_vcin.cpp
# End Source File
# Begin Source File

SOURCE=.\level_5.cpp
# End Source File
# Begin Source File

SOURCE=.\level_5_days.cpp
# End Source File
# Begin Source File

SOURCE=.\level_6.cpp
# End Source File
# Begin Source File

SOURCE=.\ListBoxClipboarded.cpp
# End Source File
# Begin Source File

SOURCE=.\Location.cpp
# End Source File
# Begin Source File

SOURCE=.\LocsTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\MyWebView.cpp
# End Source File
# Begin Source File

SOURCE=.\outcities.cpp
# End Source File
# Begin Source File

SOURCE=.\RichEditResults.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticHeader1.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticHeader3.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\strings.cpp
# End Source File
# Begin Source File

SOURCE=.\TCountry.cpp
# End Source File
# Begin Source File

SOURCE=.\TextEditWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\TFile.cpp
# End Source File
# Begin Source File

SOURCE=.\TFileRichList.cpp
# End Source File
# Begin Source File

SOURCE=.\TipDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TithiCalc.cpp
# End Source File
# Begin Source File

SOURCE=.\TResultEvents.cpp
# End Source File
# Begin Source File

SOURCE=.\TResultMasaList.cpp
# End Source File
# Begin Source File

SOURCE=.\TString.cpp
# End Source File
# Begin Source File

SOURCE=.\TStringStorage.cpp
# End Source File
# Begin Source File

SOURCE=.\TTimeZone.cpp
# End Source File
# Begin Source File

SOURCE=.\VCal5beta.cpp
# End Source File
# Begin Source File

SOURCE=.\VCal5beta.rc
# End Source File
# Begin Source File

SOURCE=.\vedic_ui.cpp
# End Source File
# Begin Source File

SOURCE=.\write_f.cpp
# End Source File
# Begin Source File

SOURCE=.\XmlFile.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\avc.h
# End Source File
# Begin Source File

SOURCE=.\CommandLineVCal.h
# End Source File
# Begin Source File

SOURCE=.\ConditionsView.h
# End Source File
# Begin Source File

SOURCE=.\CustomEvent.h
# End Source File
# Begin Source File

SOURCE=.\DayFindBuffer.h
# End Source File
# Begin Source File

SOURCE=.\DlgAskLimitation.h
# End Source File
# Begin Source File

SOURCE=.\DlgCalcProgress.h
# End Source File
# Begin Source File

SOURCE=.\DlgCustomEventDialog.h
# End Source File
# Begin Source File

SOURCE=.\DlgEditCustomEvent.h
# End Source File
# Begin Source File

SOURCE=.\DlgEditLocation.h
# End Source File
# Begin Source File

SOURCE=.\DlgEditString.h
# End Source File
# Begin Source File

SOURCE=.\DlgEventsGaubdTM.h
# End Source File
# Begin Source File

SOURCE=.\DlgEventsGetText.h
# End Source File
# Begin Source File

SOURCE=.\DlgEventsTypeOfEvent.h
# End Source File
# Begin Source File

SOURCE=.\DlgGetDate.h
# End Source File
# Begin Source File

SOURCE=.\DlgGetEndDate.h
# End Source File
# Begin Source File

SOURCE=.\DlgGetEventSpec.h
# End Source File
# Begin Source File

SOURCE=.\DlgGetLocation.h
# End Source File
# Begin Source File

SOURCE=.\DlgGetLocationEx.h
# End Source File
# Begin Source File

SOURCE=.\DlgMasaListing.h
# End Source File
# Begin Source File

SOURCE=.\DlgObservedEvents.h
# End Source File
# Begin Source File

SOURCE=.\DlgRenameCountry.h
# End Source File
# Begin Source File

SOURCE=.\DlgSelectLangOutput.h
# End Source File
# Begin Source File

SOURCE=.\DlgSetAyanamsaType.h
# End Source File
# Begin Source File

SOURCE=.\DlgSetPrintStyle.h
# End Source File
# Begin Source File

SOURCE=.\DlgSpecCommand.h
# End Source File
# Begin Source File

SOURCE=.\DlgStringManager.h
# End Source File
# Begin Source File

SOURCE=.\DNewCountry.h
# End Source File
# Begin Source File

SOURCE=.\DPageAstro.h
# End Source File
# Begin Source File

SOURCE=.\DPageAstroVedic.h
# End Source File
# Begin Source File

SOURCE=.\DPageFest.h
# End Source File
# Begin Source File

SOURCE=.\DPageGeneral.h
# End Source File
# Begin Source File

SOURCE=.\EditClipboarded.h
# End Source File
# Begin Source File

SOURCE=.\EventsHtmlView.h
# End Source File
# Begin Source File

SOURCE=.\FrameBase.h
# End Source File
# Begin Source File

SOURCE=.\FrameEvents.h
# End Source File
# Begin Source File

SOURCE=.\FrameFind.h
# End Source File
# Begin Source File

SOURCE=.\FrameLocs.h
# End Source File
# Begin Source File

SOURCE=.\FrameMain.h
# End Source File
# Begin Source File

SOURCE=.\FrameServer.h
# End Source File
# Begin Source File

SOURCE=.\gcal_evx.h
# End Source File
# Begin Source File

SOURCE=.\gmath.h
# End Source File
# Begin Source File

SOURCE=.\LangFileInfo.h
# End Source File
# Begin Source File

SOURCE=.\level_0.h
# End Source File
# Begin Source File

SOURCE=.\level_1.h
# End Source File
# Begin Source File

SOURCE=.\level_2.h
# End Source File
# Begin Source File

SOURCE=.\level_3.h
# End Source File
# Begin Source File

SOURCE=.\level_4.h
# End Source File
# Begin Source File

SOURCE=.\level_5.h
# End Source File
# Begin Source File

SOURCE=.\level_5_days.h
# End Source File
# Begin Source File

SOURCE=.\level_6.h
# End Source File
# Begin Source File

SOURCE=.\ListBoxClipboarded.h
# End Source File
# Begin Source File

SOURCE=.\Location.h
# End Source File
# Begin Source File

SOURCE=.\LocationRef.h
# End Source File
# Begin Source File

SOURCE=.\LocsTabCtrl.h
# End Source File
# Begin Source File

SOURCE=.\MyWebView.h
# End Source File
# Begin Source File

SOURCE=.\platform.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RichEditResults.h
# End Source File
# Begin Source File

SOURCE=.\showset.h
# End Source File
# Begin Source File

SOURCE=.\StaticHeader1.h
# End Source File
# Begin Source File

SOURCE=.\StaticHeader3.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\strings.h
# End Source File
# Begin Source File

SOURCE=.\TCountry.h
# End Source File
# Begin Source File

SOURCE=.\TextEditWnd.h
# End Source File
# Begin Source File

SOURCE=.\TFile.h
# End Source File
# Begin Source File

SOURCE=.\TFileRichList.h
# End Source File
# Begin Source File

SOURCE=.\TipDlg.h
# End Source File
# Begin Source File

SOURCE=.\TithiCalc.h
# End Source File
# Begin Source File

SOURCE=.\TLocation.h
# End Source File
# Begin Source File

SOURCE=.\TResultApp.h
# End Source File
# Begin Source File

SOURCE=.\TResultEvent.h
# End Source File
# Begin Source File

SOURCE=.\TResultMasaList.h
# End Source File
# Begin Source File

SOURCE=.\TString.h
# End Source File
# Begin Source File

SOURCE=.\TStringStorage.h
# End Source File
# Begin Source File

SOURCE=.\TTimeZone.h
# End Source File
# Begin Source File

SOURCE=.\VCal5beta.h
# End Source File
# Begin Source File

SOURCE=.\vedic_ui.h
# End Source File
# Begin Source File

SOURCE=.\write_f.h
# End Source File
# Begin Source File

SOURCE=.\write_s.h
# End Source File
# Begin Source File

SOURCE=.\XmlFile.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\litebulb.bmp
# End Source File
# Begin Source File

SOURCE=".\doc-specs\textual.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\VCal5beta.ico
# End Source File
# Begin Source File

SOURCE=.\res\VCal5beta.rc2
# End Source File
# Begin Source File

SOURCE=".\doc-specs\wall.bmp"
# End Source File
# End Group
# Begin Source File

SOURCE=.\dst.xml
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section VCal5beta : {72ADFD54-2C39-11D0-9903-00A0C91BC942}
# 	1:17:CG_IDS_DIDYOUKNOW:111
# 	1:22:CG_IDS_TIPOFTHEDAYMENU:110
# 	1:18:CG_IDS_TIPOFTHEDAY:109
# 	1:22:CG_IDS_TIPOFTHEDAYHELP:114
# 	1:19:CG_IDP_FILE_CORRUPT:113
# 	1:7:IDD_TIP:108
# 	1:13:IDB_LIGHTBULB:107
# 	1:18:CG_IDS_FILE_ABSENT:112
# 	2:17:CG_IDS_DIDYOUKNOW:CG_IDS_DIDYOUKNOW
# 	2:7:CTipDlg:CTipDlg
# 	2:22:CG_IDS_TIPOFTHEDAYMENU:CG_IDS_TIPOFTHEDAYMENU
# 	2:18:CG_IDS_TIPOFTHEDAY:CG_IDS_TIPOFTHEDAY
# 	2:12:CTIP_Written:OK
# 	2:22:CG_IDS_TIPOFTHEDAYHELP:CG_IDS_TIPOFTHEDAYHELP
# 	2:2:BH:
# 	2:19:CG_IDP_FILE_CORRUPT:CG_IDP_FILE_CORRUPT
# 	2:7:IDD_TIP:IDD_TIP
# 	2:8:TipDlg.h:TipDlg.h
# 	2:13:IDB_LIGHTBULB:IDB_LIGHTBULB
# 	2:18:CG_IDS_FILE_ABSENT:CG_IDS_FILE_ABSENT
# 	2:10:TipDlg.cpp:TipDlg.cpp
# End Section
