#
# yLib Helpfile AUTODUCK makefile
#

PROJ		= yLib
PTITLE		= yLib SDK Help
INTDIR		= Help
TARGETDIR	= ..\hlp
AD			= ..\..\tools\AutoDuck\AutoDuck.exe
#ADLOG		= /l$(INTDIR)\$(PROJ).LOG /N
ADLOG		= /rh /n /l$(INTDIR)\$(PROJ).LOG /c$(INTDIR)\$(PROJ).LOG
ADHLP		= /rh /C$(INTDIR)\$(PROJ).LOG /O$(INTDIR)\$(PROJ).RTF /d "title=$(PTITLE) Help File"
ADDOC		= /rd /O$(TARGETDIR)\$(PROJ).DOC
ADTAB		= 8
HC			= hcrtf.exe
SRC			= ..\inc\*.h* ..\inc\*.inl ..\src\*.c* ..\src\*.h*

# Help and Doc targets

hlp : $(TARGETDIR)\$(PROJ).hlp

doc : $(TARGETDIR)\$(PROJ).doc

clean: cleanad

cleanad:
	if exist $(INTDIR)\*.rtf del $(INTDIR)\*.rtf
	if exist $(INTDIR)\*.hpj del $(INTDIR)\*.hpj
	if exist $(INTDIR)\*.log del $(INTDIR)\*.log
	if exist $(TARGETDIR)\$(PROJ).doc del $(TARGETDIR)\$(PROJ).doc
	if exist $(TARGETDIR)\$(PROJ).hlp del $(TARGETDIR)\$(PROJ).hlp

# Generate a Help file

$(TARGETDIR)\$(PROJ).hlp : $(INTDIR)\$(PROJ).rtf
	$(HC) /a /x /o$(INTDIR)\$(PROJ).hlp $(INTDIR)\$(PROJ).hpj
	move $(INTDIR)\$(PROJ).hlp $(TARGETDIR)\$(PROJ).hlp
#	ren $(TARGETDIR)\$(PROJ).hlp $(TARGETDIR)\$(PROJ).hlp

# Generate a print documentation file

$(TARGETDIR)\$(PROJ).doc : $(SRC)
	if not exist $(INTDIR)\. md $(INTDIR)
	if not exist $(TARGETDIR)\. md $(TARGETDIR)
	$(AD) $(ADDOC) /t$(ADTAB) $(SRC)

# Generate a topic log file

$(INTDIR)\$(PROJ).log : $(SRC)
	if not exist $(INTDIR)\. md $(INTDIR)
	if not exist $(TARGETDIR)\. md $(TARGETDIR)
	echo A>$(INTDIR)\$(PROJ).log
	echo A>$(INTDIR)\$(PROJ).log
	$(AD) $(ADLOG) $(SRC)

# Generate a help source file

$(INTDIR)\$(PROJ).rtf : $(INTDIR)\$(PROJ).log $(SRC)
	if not exist $(INTDIR)\. md $(INTDIR)
	if not exist $(TARGETDIR)\. md $(TARGETDIR)
	$(AD) $(ADHLP) /t$(ADTAB) $(SRC)

