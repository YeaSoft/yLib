# Microsoft Developer Studio Project File - Name="yAfc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=yAfc - Win32 Dynamic Debug CRT Unicode
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "yAfc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "yAfc.mak" CFG="yAfc - Win32 Dynamic Debug CRT Unicode"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "yAfc - Win32 Static Release CRT" (based on "Win32 (x86) Static Library")
!MESSAGE "yAfc - Win32 Static Debug CRT" (based on "Win32 (x86) Static Library")
!MESSAGE "yAfc - Win32 Dynamic Debug CRT" (based on "Win32 (x86) Static Library")
!MESSAGE "yAfc - Win32 Dynamic Release CRT" (based on "Win32 (x86) Static Library")
!MESSAGE "yAfc - Win32 Static Debug CRT Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE "yAfc - Win32 Static Release CRT Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE "yAfc - Win32 Dynamic Debug CRT Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE "yAfc - Win32 Dynamic Release CRT Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "yAfc"
# PROP Scc_LocalPath ".."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "yAfc - Win32 Static Release CRT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Static Release CRT"
# PROP BASE Intermediate_Dir "Static Release CRT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "RelStlA2"
# PROP Intermediate_Dir "RelStlA2"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /G5 /MT /W3 /GX /Zd /O1 /I "..\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /YX"StdAfc.hpp" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\nYFCswr.lib"

!ELSEIF  "$(CFG)" == "yAfc - Win32 Static Debug CRT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Static Debug CRT"
# PROP BASE Intermediate_Dir "Static Debug CRT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DbgStlA2"
# PROP Intermediate_Dir "DbgStlA2"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /G5 /MTd /W3 /GX /Z7 /Od /I "..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /FR /YX"StdAfc.hpp" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\nYFCswd.lib"

!ELSEIF  "$(CFG)" == "yAfc - Win32 Dynamic Debug CRT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "yAfc___Win32_Dynamic_Debug_CRT"
# PROP BASE Intermediate_Dir "yAfc___Win32_Dynamic_Debug_CRT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DbgDllA2"
# PROP Intermediate_Dir "DbgDllA2"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MTd /W3 /GX /Z7 /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX"StdAfc.hpp" /FD /GZ /c
# ADD CPP /nologo /G5 /MDd /W3 /GX /Z7 /Od /I "..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /FR /YX"StdAfc.hpp" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\yAfcSD.lib"
# ADD LIB32 /nologo /out:"..\lib\nYFCdwd.lib"

!ELSEIF  "$(CFG)" == "yAfc - Win32 Dynamic Release CRT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "yAfc___Win32_Dynamic_Release_CRT"
# PROP BASE Intermediate_Dir "yAfc___Win32_Dynamic_Release_CRT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "RelDllA2"
# PROP Intermediate_Dir "RelDllA2"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MT /W3 /GX /Zd /O1 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX"StdAfc.hpp" /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GX /Zd /O1 /I "..\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /YX"StdAfc.hpp" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\yAfcSR.lib"
# ADD LIB32 /nologo /out:"..\lib\nYFCdwr.lib"

!ELSEIF  "$(CFG)" == "yAfc - Win32 Static Debug CRT Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "yAfc___Win32_Static_Debug_CRT_Unicode"
# PROP BASE Intermediate_Dir "yAfc___Win32_Static_Debug_CRT_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DbgStlU2"
# PROP Intermediate_Dir "DbgStlU2"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MTd /W3 /GX /Z7 /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX"StdAfc.hpp" /FD /GZ /c
# ADD CPP /nologo /G5 /MTd /W3 /GX /Z7 /Od /I "..\inc" /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /FR /YX"StdAfc.hpp" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\yAfcSD.lib"
# ADD LIB32 /nologo /out:"..\lib\uYFCswd.lib"

!ELSEIF  "$(CFG)" == "yAfc - Win32 Static Release CRT Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "yAfc___Win32_Static_Release_CRT_Unicode"
# PROP BASE Intermediate_Dir "yAfc___Win32_Static_Release_CRT_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "RelStlU2"
# PROP Intermediate_Dir "RelStlU2"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MT /W3 /GX /Zd /O1 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX"StdAfc.hpp" /FD /c
# ADD CPP /nologo /G5 /MT /W3 /GX /Zd /O1 /I "..\inc" /D "NDEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /YX"StdAfc.hpp" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\yAfcSR.lib"
# ADD LIB32 /nologo /out:"..\lib\uYFCswr.lib"

!ELSEIF  "$(CFG)" == "yAfc - Win32 Dynamic Debug CRT Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "yAfc___Win32_Dynamic_Debug_CRT_Unicode"
# PROP BASE Intermediate_Dir "yAfc___Win32_Dynamic_Debug_CRT_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DbgDllU2"
# PROP Intermediate_Dir "DbgDllU2"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MDd /W3 /GX /Z7 /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX"StdAfc.hpp" /FD /GZ /c
# ADD CPP /nologo /G5 /MDd /W3 /GX /Z7 /Od /I "..\inc" /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /FR /YX"StdAfc.hpp" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\yAfcSD.lib"
# ADD LIB32 /nologo /out:"..\lib\uYFCdwd.lib"

!ELSEIF  "$(CFG)" == "yAfc - Win32 Dynamic Release CRT Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "yAfc___Win32_Dynamic_Release_CRT_Unicode"
# PROP BASE Intermediate_Dir "yAfc___Win32_Dynamic_Release_CRT_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "RelDllU2"
# PROP Intermediate_Dir "RelDllU2"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MD /W3 /GX /Zd /O1 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX"StdAfc.hpp" /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GX /Zd /O1 /I "..\inc" /D "NDEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /YX"StdAfc.hpp" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\yAfcSR.lib"
# ADD LIB32 /nologo /out:"..\lib\uYFCdwr.lib"

!ENDIF 

# Begin Target

# Name "yAfc - Win32 Static Release CRT"
# Name "yAfc - Win32 Static Debug CRT"
# Name "yAfc - Win32 Dynamic Debug CRT"
# Name "yAfc - Win32 Dynamic Release CRT"
# Name "yAfc - Win32 Static Debug CRT Unicode"
# Name "yAfc - Win32 Static Release CRT Unicode"
# Name "yAfc - Win32 Dynamic Debug CRT Unicode"
# Name "yAfc - Win32 Dynamic Release CRT Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\_tmainfn.cpp
# End Source File
# Begin Source File

SOURCE=.\yAfc.cpp
# End Source File
# Begin Source File

SOURCE=.\yBaseApp.cpp
# End Source File
# Begin Source File

SOURCE=.\yConApp.cpp
# End Source File
# Begin Source File

SOURCE=.\ySrvApp.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm"
# Begin Group "Internal"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\internal.h
# End Source File
# Begin Source File

SOURCE=.\StdAfc.hpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\inc\yAfc.h
# End Source File
# Begin Source File

SOURCE=..\inc\yAfcBase.h
# End Source File
# Begin Source File

SOURCE=..\inc\yBaseApp.h
# End Source File
# Begin Source File

SOURCE=..\inc\yConApp.h
# End Source File
# Begin Source File

SOURCE=..\inc\ySrvApp.h
# End Source File
# End Group
# Begin Group "Inline Files"

# PROP Default_Filter "inl"
# Begin Source File

SOURCE=..\inc\yAfcBase.inl
# End Source File
# Begin Source File

SOURCE=..\inc\yBaseApp.inl
# End Source File
# Begin Source File

SOURCE=..\inc\yConApp.inl
# End Source File
# Begin Source File

SOURCE=..\inc\ySrvApp.inl
# End Source File
# End Group
# Begin Group "yLib Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\inc\yArgParser.h
# End Source File
# Begin Source File

SOURCE=..\inc\yArray.h
# End Source File
# Begin Source File

SOURCE=..\inc\yBuffer.h
# End Source File
# Begin Source File

SOURCE=..\inc\yConsole.h
# End Source File
# Begin Source File

SOURCE=..\inc\yCrc32.h
# End Source File
# Begin Source File

SOURCE=..\inc\yEventSource.h
# End Source File
# Begin Source File

SOURCE=..\inc\yFileObjects.h
# End Source File
# Begin Source File

SOURCE=..\inc\yFiles.h
# End Source File
# Begin Source File

SOURCE=..\inc\yFileTools.h
# End Source File
# Begin Source File

SOURCE=..\inc\yFixStr.h
# End Source File
# Begin Source File

SOURCE=..\inc\yFlags.h
# End Source File
# Begin Source File

SOURCE=..\inc\yHandle.h
# End Source File
# Begin Source File

SOURCE=..\inc\yLib.h
# End Source File
# Begin Source File

SOURCE=..\inc\yLibBase.h
# End Source File
# Begin Source File

SOURCE=..\inc\yLogging.h
# End Source File
# Begin Source File

SOURCE=..\inc\yMailSlots.h
# End Source File
# Begin Source File

SOURCE=..\inc\yMailSlotServer.h
# End Source File
# Begin Source File

SOURCE=..\inc\yMulStr.h
# End Source File
# Begin Source File

SOURCE=..\inc\yPipes.h
# End Source File
# Begin Source File

SOURCE=..\inc\yPipeServer.h
# End Source File
# Begin Source File

SOURCE=..\inc\yRegistry.h
# End Source File
# Begin Source File

SOURCE=..\inc\ySCM.h
# End Source File
# Begin Source File

SOURCE=..\inc\ySecDesc.h
# End Source File
# Begin Source File

SOURCE=..\inc\ySync.h
# End Source File
# Begin Source File

SOURCE=..\inc\yThread.h
# End Source File
# Begin Source File

SOURCE=..\inc\yTokens.h
# End Source File
# Begin Source File

SOURCE=..\inc\yUNC.h
# End Source File
# Begin Source File

SOURCE=..\inc\yVersInfo.h
# End Source File
# End Group
# Begin Group "yLib Inline Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\inc\yArgParser.inl
# End Source File
# Begin Source File

SOURCE=..\inc\yArray.inl
# End Source File
# Begin Source File

SOURCE=..\inc\yBuffer.inl
# End Source File
# Begin Source File

SOURCE=..\inc\yConsole.inl
# End Source File
# Begin Source File

SOURCE=..\inc\yCrc32.inl
# End Source File
# Begin Source File

SOURCE=..\inc\yEventSource.inl
# End Source File
# Begin Source File

SOURCE=..\inc\yFileObjects.inl
# End Source File
# Begin Source File

SOURCE=..\inc\yFiles.inl
# End Source File
# Begin Source File

SOURCE=..\inc\yFileTools.inl
# End Source File
# Begin Source File

SOURCE=..\inc\yFixStr.inl
# End Source File
# Begin Source File

SOURCE=..\inc\yFlags.inl
# End Source File
# Begin Source File

SOURCE=..\inc\yHandle.inl
# End Source File
# Begin Source File

SOURCE=..\inc\yLibBase.inl
# End Source File
# Begin Source File

SOURCE=..\inc\yLogging.inl
# End Source File
# Begin Source File

SOURCE=..\inc\yMailSlots.inl
# End Source File
# Begin Source File

SOURCE=..\inc\yMailSlotServer.inl
# End Source File
# Begin Source File

SOURCE=..\inc\yMulStr.inl
# End Source File
# Begin Source File

SOURCE=..\inc\yPipes.inl
# End Source File
# Begin Source File

SOURCE=..\inc\yPipeServer.inl
# End Source File
# Begin Source File

SOURCE=..\inc\yRegistry.inl
# End Source File
# Begin Source File

SOURCE=..\inc\ySCM.inl
# End Source File
# Begin Source File

SOURCE=..\inc\ySecDesc.inl
# End Source File
# Begin Source File

SOURCE=..\inc\ySync.inl
# End Source File
# Begin Source File

SOURCE=..\inc\yThread.inl
# End Source File
# Begin Source File

SOURCE=..\inc\yTokens.inl
# End Source File
# Begin Source File

SOURCE=..\inc\yUNC.inl
# End Source File
# Begin Source File

SOURCE=..\inc\yVersInfo.inl
# End Source File
# End Group
# End Target
# End Project
