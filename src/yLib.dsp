# Microsoft Developer Studio Project File - Name="yLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=yLib - Win32 Dynamic Debug CRT Unicode
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "yLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "yLib.mak" CFG="yLib - Win32 Dynamic Debug CRT Unicode"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "yLib - Win32 Static Debug CRT" (based on "Win32 (x86) Static Library")
!MESSAGE "yLib - Win32 Dynamic Debug CRT" (based on "Win32 (x86) Static Library")
!MESSAGE "yLib - Win32 Static Release CRT" (based on "Win32 (x86) Static Library")
!MESSAGE "yLib - Win32 Dynamic Release CRT" (based on "Win32 (x86) Static Library")
!MESSAGE "yLib - Win32 Static Debug CRT Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE "yLib - Win32 Dynamic Debug CRT Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE "yLib - Win32 Static Release CRT Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE "yLib - Win32 Dynamic Release CRT Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "yLib - Win32 Static Debug CRT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "yLib___Win32_Static_Debug_CRT"
# PROP BASE Intermediate_Dir "yLib___Win32_Static_Debug_CRT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DbgStlA1"
# PROP Intermediate_Dir "DbgStlA1"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MTd /W3 /GX /Z7 /Od /I "\src\sdk\yLib\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX"StdInc.hpp" /FD /c
# ADD CPP /nologo /G5 /MTd /W3 /GX /Z7 /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX"StdInc.hpp" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"\src\sdk\yLib\lib\yLibD.lib"
# ADD LIB32 /nologo /out:"..\lib\nYLBswd.lib"

!ELSEIF  "$(CFG)" == "yLib - Win32 Dynamic Debug CRT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "yLib___Win32_Dynamic_Debug_CRT"
# PROP BASE Intermediate_Dir "yLib___Win32_Dynamic_Debug_CRT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DbgDllA1"
# PROP Intermediate_Dir "DbgDllA1"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MTd /W3 /GX /Z7 /Od /I "\src\sdk\yLib\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX"StdInc.hpp" /FD /c
# ADD CPP /nologo /G5 /MDd /W3 /GX /Z7 /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX"StdInc.hpp" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"\src\sdk\yLib\lib\yLibD.lib"
# ADD LIB32 /nologo /out:"..\lib\nYLBdwd.lib"

!ELSEIF  "$(CFG)" == "yLib - Win32 Static Release CRT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "yLib___Win32_Static_Release_CRT"
# PROP BASE Intermediate_Dir "yLib___Win32_Static_Release_CRT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "RelStlA1"
# PROP Intermediate_Dir "RelStlA1"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MT /W3 /GX /O1 /I "\src\sdk\yLib\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX"StdInc.hpp" /FD /c
# ADD CPP /nologo /G5 /MT /W3 /GX /Zd /O1 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX"StdInc.hpp" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"\src\sdk\yLib\lib\yLibR.lib"
# ADD LIB32 /nologo /out:"..\lib\nYLBswr.lib"

!ELSEIF  "$(CFG)" == "yLib - Win32 Dynamic Release CRT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "yLib___Win32_Dynamic_Release_CRT"
# PROP BASE Intermediate_Dir "yLib___Win32_Dynamic_Release_CRT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "RelDllA1"
# PROP Intermediate_Dir "RelDllA1"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MT /W3 /GX /O1 /I "\src\sdk\yLib\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX"StdInc.hpp" /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GX /O1 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX"StdInc.hpp" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"\src\sdk\yLib\lib\yLibR.lib"
# ADD LIB32 /nologo /out:"..\lib\nYLBdwr.lib"

!ELSEIF  "$(CFG)" == "yLib - Win32 Static Debug CRT Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "yLib___Win32_Static_Debug_CRT_Unicode"
# PROP BASE Intermediate_Dir "yLib___Win32_Static_Debug_CRT_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DbgStlU1"
# PROP Intermediate_Dir "DbgStlU1"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MTd /W3 /GX /Z7 /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX"StdInc.hpp" /FD /c
# ADD CPP /nologo /G5 /MTd /W3 /GX /Z7 /Od /I "..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /FR /YX"StdInc.hpp" /FD /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\yLibSD.lib"
# ADD LIB32 /nologo /out:"..\lib\uYLBswd.lib"

!ELSEIF  "$(CFG)" == "yLib - Win32 Dynamic Debug CRT Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "yLib___Win32_Dynamic_Debug_CRT_Unicode"
# PROP BASE Intermediate_Dir "yLib___Win32_Dynamic_Debug_CRT_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DbgDllU1"
# PROP Intermediate_Dir "DbgDllU1"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MDd /W3 /GX /Z7 /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX"StdInc.hpp" /FD /c
# ADD CPP /nologo /G5 /MDd /W3 /GX /Z7 /Od /I "..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /FR /YX"StdInc.hpp" /FD /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\yLibDD.lib"
# ADD LIB32 /nologo /out:"..\lib\uYLBdwd.lib"

!ELSEIF  "$(CFG)" == "yLib - Win32 Static Release CRT Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "yLib___Win32_Static_Release_CRT_Unicode"
# PROP BASE Intermediate_Dir "yLib___Win32_Static_Release_CRT_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "RelStlU1"
# PROP Intermediate_Dir "RelStlU1"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MT /W3 /GX /Zd /O1 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX"StdInc.hpp" /FD /c
# ADD CPP /nologo /G5 /MT /W3 /GX /Zd /O1 /I "..\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /YX"StdInc.hpp" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\yLibSR.lib"
# ADD LIB32 /nologo /out:"..\lib\uYLBswr.lib"

!ELSEIF  "$(CFG)" == "yLib - Win32 Dynamic Release CRT Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "yLib___Win32_Dynamic_Release_CRT_Unicode"
# PROP BASE Intermediate_Dir "yLib___Win32_Dynamic_Release_CRT_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "RelDllU1"
# PROP Intermediate_Dir "RelDllU1"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MD /W3 /GX /O1 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX"StdInc.hpp" /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GX /O1 /I "..\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /YX"StdInc.hpp" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\yLibDR.lib"
# ADD LIB32 /nologo /out:"..\lib\uYLBdwr.lib"

!ENDIF 

# Begin Target

# Name "yLib - Win32 Static Debug CRT"
# Name "yLib - Win32 Dynamic Debug CRT"
# Name "yLib - Win32 Static Release CRT"
# Name "yLib - Win32 Dynamic Release CRT"
# Name "yLib - Win32 Static Debug CRT Unicode"
# Name "yLib - Win32 Dynamic Debug CRT Unicode"
# Name "yLib - Win32 Static Release CRT Unicode"
# Name "yLib - Win32 Dynamic Release CRT Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\_yState.cpp
# End Source File
# Begin Source File

SOURCE=.\yBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\yConsole.cpp
# End Source File
# Begin Source File

SOURCE=.\yCrc32.cpp
# End Source File
# Begin Source File

SOURCE=.\yEventSource.cpp
# End Source File
# Begin Source File

SOURCE=.\yFileObjects.cpp
# End Source File
# Begin Source File

SOURCE=.\yFiles.cpp
# End Source File
# Begin Source File

SOURCE=.\yFileTools.cpp
# End Source File
# Begin Source File

SOURCE=.\yFixStr.cpp
# End Source File
# Begin Source File

SOURCE=.\yFlags.cpp
# End Source File
# Begin Source File

SOURCE=.\yHandle.cpp
# End Source File
# Begin Source File

SOURCE=.\yLib.cpp
# End Source File
# Begin Source File

SOURCE=..\hlp\yLibHlp.mk

!IF  "$(CFG)" == "yLib - Win32 Static Debug CRT"

# Begin Custom Build - Making Help File
InputPath=..\hlp\yLibHlp.mk

"..\hlp\yLib.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake /nologo /s /f ..\hlp\yLibHlp.mk

# End Custom Build

!ELSEIF  "$(CFG)" == "yLib - Win32 Dynamic Debug CRT"

# Begin Custom Build - Making Help File
InputPath=..\hlp\yLibHlp.mk

"..\hlp\yLib.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake /nologo /s /f ..\hlp\yLibHlp.mk

# End Custom Build

!ELSEIF  "$(CFG)" == "yLib - Win32 Static Release CRT"

# Begin Custom Build - Making Help File
InputPath=..\hlp\yLibHlp.mk

"..\hlp\yLib.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake /nologo /s /f ..\hlp\yLibHlp.mk

# End Custom Build

!ELSEIF  "$(CFG)" == "yLib - Win32 Dynamic Release CRT"

# Begin Custom Build - Making Help File
InputPath=..\hlp\yLibHlp.mk

"..\hlp\yLib.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake /nologo /s /f ..\hlp\yLibHlp.mk

# End Custom Build

!ELSEIF  "$(CFG)" == "yLib - Win32 Static Debug CRT Unicode"

# Begin Custom Build - Making Help File
InputPath=..\hlp\yLibHlp.mk

"..\hlp\yLib.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake /nologo /s /f ..\hlp\yLibHlp.mk

# End Custom Build

!ELSEIF  "$(CFG)" == "yLib - Win32 Dynamic Debug CRT Unicode"

# Begin Custom Build - Making Help File
InputPath=..\hlp\yLibHlp.mk

"..\hlp\yLib.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake /nologo /s /f ..\hlp\yLibHlp.mk

# End Custom Build

!ELSEIF  "$(CFG)" == "yLib - Win32 Static Release CRT Unicode"

# Begin Custom Build - Making Help File
InputPath=..\hlp\yLibHlp.mk

"..\hlp\yLib.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake /nologo /s /f ..\hlp\yLibHlp.mk

# End Custom Build

!ELSEIF  "$(CFG)" == "yLib - Win32 Dynamic Release CRT Unicode"

# Begin Custom Build - Making Help File
InputPath=..\hlp\yLibHlp.mk

"..\hlp\yLib.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake /nologo /s /f ..\hlp\yLibHlp.mk

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\yLogging.cpp
# End Source File
# Begin Source File

SOURCE=.\yMailSlots.cpp
# End Source File
# Begin Source File

SOURCE=.\yMailSlotServer.cpp
# End Source File
# Begin Source File

SOURCE=.\yPipes.cpp
# End Source File
# Begin Source File

SOURCE=.\yPipeServer.cpp
# End Source File
# Begin Source File

SOURCE=.\yRegistry.cpp
# End Source File
# Begin Source File

SOURCE=.\ySCM.cpp
# End Source File
# Begin Source File

SOURCE=.\ySecDesc.cpp
# End Source File
# Begin Source File

SOURCE=.\ySync.cpp
# End Source File
# Begin Source File

SOURCE=.\yThread.cpp
# End Source File
# Begin Source File

SOURCE=.\yTokens.cpp
# End Source File
# Begin Source File

SOURCE=.\yUNC.cpp
# End Source File
# Begin Source File

SOURCE=.\yVersInfo.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;fi;fd"
# Begin Group "Internal"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\docFile.h
# End Source File
# Begin Source File

SOURCE=.\internal.h
# End Source File
# Begin Source File

SOURCE=.\StdInc.hpp
# End Source File
# End Group
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
# Begin Group "Inline Files"

# PROP Default_Filter "inl"
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
