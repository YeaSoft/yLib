# Microsoft Developer Studio Project File - Name="Sample1" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Sample1 - Win32 Static Debug CRT Unicode
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Sample1.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Sample1.mak" CFG="Sample1 - Win32 Static Debug CRT Unicode"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Sample1 - Win32 Static Release CRT" (based on "Win32 (x86) Console Application")
!MESSAGE "Sample1 - Win32 Static Debug CRT" (based on "Win32 (x86) Console Application")
!MESSAGE "Sample1 - Win32 Static Debug CRT Unicode" (based on "Win32 (x86) Console Application")
!MESSAGE "Sample1 - Win32 Static Release CRT Unicode" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "Sample1"
# PROP Scc_LocalPath "..\.."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Sample1 - Win32 Static Release CRT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Sample1___Win32_Static_Release_CRT"
# PROP BASE Intermediate_Dir "Sample1___Win32_Static_Release_CRT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "RelStlA"
# PROP Intermediate_Dir "RelStlA"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MT /W3 /GX /O2 /I "..\..\inc" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX"yAfc.h" /FD /c
# ADD CPP /nologo /G5 /MT /W3 /GX /O2 /I "..\..\inc" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX"StdAfc.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /libpath:"..\..\lib"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"../../bin/RelStlA/Sample1.exe" /libpath:"..\..\lib"

!ELSEIF  "$(CFG)" == "Sample1 - Win32 Static Debug CRT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Sample1___Win32_Static_Debug_CRT"
# PROP BASE Intermediate_Dir "Sample1___Win32_Static_Debug_CRT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DbgStlA"
# PROP Intermediate_Dir "DbgStlA"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MTd /W3 /Gm /GX /Zi /Od /I "..\..\inc" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX"yAfc.h" /FD /GZ /c
# ADD CPP /nologo /G5 /MTd /W3 /GX /Zi /Od /I "..\..\inc" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX"StdAfc.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"..\..\lib"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"../../bin/DbgStlA/Sample1.exe" /pdbtype:sept /libpath:"..\..\lib"
# SUBTRACT LINK32 /verbose

!ELSEIF  "$(CFG)" == "Sample1 - Win32 Static Debug CRT Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Sample1___Win32_Static_Debug_CRT_Unicode"
# PROP BASE Intermediate_Dir "Sample1___Win32_Static_Debug_CRT_Unicode"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DbgStlU"
# PROP Intermediate_Dir "DbgStlU"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MTd /W3 /Gm /GX /Zi /Od /I "..\..\inc" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX"yAfc.h" /FD /GZ /c
# ADD CPP /nologo /G5 /MTd /W3 /GX /Zi /Od /I "..\..\inc" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_UNICODE" /YX"StdAfc.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"..\..\lib"
# SUBTRACT BASE LINK32 /verbose
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"wmainCRTStartup" /subsystem:console /map /debug /machine:I386 /out:"../../bin/DbgStlU/Sample1.exe" /pdbtype:sept /libpath:"..\..\lib"
# SUBTRACT LINK32 /verbose

!ELSEIF  "$(CFG)" == "Sample1 - Win32 Static Release CRT Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Sample1___Win32_Static_Release_CRT_Unicode"
# PROP BASE Intermediate_Dir "Sample1___Win32_Static_Release_CRT_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "RelStlU"
# PROP Intermediate_Dir "RelStlU"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MT /W3 /GX /O2 /I "..\..\inc" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX"yAfc.h" /FD /c
# ADD CPP /nologo /G5 /MT /W3 /GX /O2 /I "..\..\inc" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_UNICODE" /YX"StdAfc.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /libpath:"..\..\lib"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"wmainCRTStartup" /subsystem:console /machine:I386 /out:"../../bin/RelStlU/Sample1.exe" /libpath:"..\..\lib"

!ENDIF 

# Begin Target

# Name "Sample1 - Win32 Static Release CRT"
# Name "Sample1 - Win32 Static Debug CRT"
# Name "Sample1 - Win32 Static Debug CRT Unicode"
# Name "Sample1 - Win32 Static Release CRT Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\EventLog.cpp
# End Source File
# Begin Source File

SOURCE=.\MailSlots.cpp
# End Source File
# Begin Source File

SOURCE=.\NamedPipes.cpp
# End Source File
# Begin Source File

SOURCE=.\Registry.cpp
# End Source File
# Begin Source File

SOURCE=.\Sample1.cpp
# End Source File
# Begin Source File

SOURCE=.\Sample1.rc
# End Source File
# Begin Source File

SOURCE=.\SampleMsg1.mc

!IF  "$(CFG)" == "Sample1 - Win32 Static Release CRT"

# Begin Custom Build
ProjDir=.
InputPath=.\SampleMsg1.mc

BuildCmds= \
	mc SampleMsg1.mc

"$(ProjDir)\SampleMsg1.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\SampleMsg1.rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\MSG00001.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\MSG00007.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\MSG00010.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Sample1 - Win32 Static Debug CRT"

# Begin Custom Build
ProjDir=.
InputPath=.\SampleMsg1.mc
InputName=SampleMsg1

BuildCmds= \
	mc $(InputName)

"$(ProjDir)\SampleMsg1.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\SampleMsg1.rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\MSG00001.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\MSG00007.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\MSG00010.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Sample1 - Win32 Static Debug CRT Unicode"

# Begin Custom Build
ProjDir=.
InputPath=.\SampleMsg1.mc

BuildCmds= \
	mc SampleMsg1.mc

"$(ProjDir)\SampleMsg1.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\SampleMsg1.rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\MSG00001.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\MSG00007.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\MSG00010.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Sample1 - Win32 Static Release CRT Unicode"

# Begin Custom Build
ProjDir=.
InputPath=.\SampleMsg1.mc

BuildCmds= \
	mc SampleMsg1.mc

"$(ProjDir)\SampleMsg1.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\SampleMsg1.rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\MSG00001.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\MSG00007.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\MSG00010.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Threads.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Sample1.h
# End Source File
# Begin Source File

SOURCE=.\SampleRes1.h
# End Source File
# Begin Source File

SOURCE=.\StdAfc.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\MSG00001.bin
# End Source File
# Begin Source File

SOURCE=.\MSG00007.bin
# End Source File
# Begin Source File

SOURCE=.\MSG00010.bin
# End Source File
# Begin Source File

SOURCE=.\SampleMsg1.rc

!IF  "$(CFG)" == "Sample1 - Win32 Static Release CRT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Sample1 - Win32 Static Debug CRT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Sample1 - Win32 Static Debug CRT Unicode"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Sample1 - Win32 Static Release CRT Unicode"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "yLib Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\inc\yAfc.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\yAfcBase.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\yArray.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\yBaseApp.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\yBuffer.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\yConApp.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\yConsole.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\yCrc32.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\yEventSource.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\yFileObjects.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\yFiles.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\yFileTools.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\yFixStr.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\yFlags.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\yHandle.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\yLib.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\yLibBase.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\yLogging.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\yMailSlots.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\yMailSlotServer.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\yPipes.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\yPipeServer.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\yRegistry.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\ySCM.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\ySecDesc.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\ySrvApp.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\ySync.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\yThread.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\yTokens.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\yUNC.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\yVersInfo.h
# End Source File
# End Group
# End Target
# End Project
