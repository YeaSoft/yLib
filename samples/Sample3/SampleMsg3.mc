;/*=============================================================================
; * This is a part of the yLib Software Development Kit.
; * Copyright (C) 1998-2000 YEAsoft Inc.
; * All rights reserved.
; *=============================================================================
; * This program is free software; you can redistribute it and/or modify
; * it under the terms of the GNU General Public License as published by
; * the Free Software Foundation. In addition, you may also charge for any
; * application using yLib, and are under no obligation to supply source
; * code. You must accredit YEAsoft Inc. in the "About Box", or banner
; * of your application. 
; *
; * This program is distributed in the hope that it will be useful,
; * but WITHOUT ANY WARRANTY; without even the implied warranty of
; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; * GNU General Public License for more details.
; *
; * You should also have received a copy of the GNU General Public License
; * with this software, also indicating additional rights you have when using
; * yLib.
; *=============================================================================
; * FILENAME	:	SampleMsg3.mc
; * PURPOSE		:	yLib service sample
; * SCOPE		:	yLib SDK
; * HISTORY		: =============================================================
; * 
; * $Log$
; *============================================================================*/

;/*
;-------------------------------------------------------------------------
; HEADER SECTION
;
; The header section defines names and language identifiers for use
; by the message definitions later in this file. The MessageIdTypedef,
; SeverityNames, FacilityNames, and LanguageNames keywords are
; optional and not required.
;
;
MessageIdTypedef=DWORD
;
; The MessageIdTypedef keyword gives a typedef name that is used in a
; type cast for each message code in the generated include file. Each
; message code appears in the include file with the format: #define
; name ((type) 0xnnnnnnnn) The default value for type is empty, and no
; type cast is generated. It is the programmer's responsibility to
; specify a typedef statement in the application source code to define
; the type. The type used in the typedef must be large enough to
; accomodate the entire 32-bit message code.
;
;
SeverityNames=(Success=0x0:STATUS_SEVERITY_SUCCESS
               Informational=0x1:STATUS_SEVERITY_INFORMATIONAL
               Warning=0x2:STATUS_SEVERITY_WARNING
               Error=0x3:STATUS_SEVERITY_ERROR
              )
;
; The SeverityNames keyword defines the set of names that are allowed
; as the value of the Severity keyword in the message definition. The
; set is delimited by left and right parentheses. Associated with each
; severity name is a number that, when shifted left by 30, gives the
; bit pattern to logical-OR with the Facility value and MessageId
; value to form the full 32-bit message code. The default value of
; this keyword is:
;
; SeverityNames=(
;   Success=0x0
;   Informational=0x1
;   Warning=0x2
;   Error=0x3
;   )
;
; Severity values occupy the high two bits of a 32-bit message code.
; Any severity value that does not fit in two bits is an error. The
; severity codes can be given symbolic names by following each value
; with :name
;
;
FacilityNames=(System=0x0:FACILITY_SYSTEM
               Runtime=0x2:FACILITY_RUNTIME
               Stubs=0x3:FACILITY_STUBS
               Io=0x4:FACILITY_IO_ERROR_CODE
              )
;
; The FacilityNames keyword defines the set of names that are allowed
; as the value of the Facility keyword in the message definition. The
; set is delimited by left and right parentheses. Associated with each
; facility name is a number that, when shift it left by 16 bits, gives
; the bit pattern to logical-OR with the Severity value and MessageId
; value to form the full 32-bit message code. The default value of
; this keyword is:
;
; FacilityNames=(
;   System=0x0FF
;   Application=0xFFF
;   )
;
; Facility codes occupy the low order 12 bits of the high order
; 16-bits of a 32-bit message code. Any facility code that does not
; fit in 12 bits is an error. This allows for 4,096 facility codes.
; The first 256 codes are reserved for use by the system software. The
; facility codes can be given symbolic names by following each value
; with :name
;
;
; The LanguageNames keyword defines the set of names that are allowed
; as the value of the Language keyword in the message definition. The
; set is delimited by left and right parentheses. Associated with each
; language name is a number and a file name that are used to name the
; generated resource file that contains the messages for that
; language. The number corresponds to the language identifier to use
; in the resource table. The number is separated from the file name
; with a colon. The initial value of LanguageNames is:
;
; LanguageNames=(English=1:MSG00001)
LanguageNames=(
				German=7:MSG00007
				Italian=16:MSG00010
				)
;
; Any new names in the source file which don't override the built-in
; names are added to the list of valid languages. This allows an
; application to support private languages with descriptive names.
;
;
;-------------------------------------------------------------------------
; MESSAGE DEFINITION SECTION
;
; Following the header section is the body of the Message Compiler
; source file. The body consists of zero or more message definitions.
; Each message definition begins with one or more of the following
; statements:
;
; MessageId = [number|+number]
; Severity = severity_name
; Facility = facility_name
; SymbolicName = name
;
; The MessageId statement marks the beginning of the message
; definition. A MessageID statement is required for each message,
; although the value is optional. If no value is specified, the value
; used is the previous value for the facility plus one. If the value
; is specified as +number then the value used is the previous value
; for the facility, plus the number after the plus sign. Otherwise, if
; a numeric value is given, that value is used. Any MessageId value
; that does not fit in 16 bits is an error.
;
; The Severity and Facility statements are optional. These statements
; specify additional bits to OR into the final 32-bit message code. If
; not specified they default to the value last specified for a message
; definition. The initial values prior to processing the first message
; definition are:
;
; Severity=Success
; Facility=Application
;
; The value associated with Severity and Facility must match one of
; the names given in the FacilityNames and SeverityNames statements in
; the header section. The SymbolicName statement allows you to
; associate a C/C++ symbolic constant with the final 32-bit message
; code.
; */

MessageIdTypedef=WORD

MessageId=0x1
SymbolicName=CAT_MANAGEMENT
Language=English
Management
.
Language=German
Verwaltung
.
Language=Italian
Gestione
.

MessageId=
SymbolicName=CAT_SERVICE
Language=English
Service
.
Language=German
Dienst
.
Language=Italian
Servizio
.

MessageIdTypedef=DWORD

MessageId=0x100
Severity=Success
Facility=Runtime
SymbolicName=MSG_INSTALLED
Language=English
%1 service successfully installed
.
Language=German
%1 Dienst erfolgreich installiert
.
Language=Italian
Servizio %1 installato senza errori
.

MessageId=
Severity=Error
SymbolicName=MSG_INSTALL_ERROR
Language=English
Could not install %1 service (error: %2)
.
Language=German
Der %1 Dienst konnte nicht installiert werden (Fehler: %2)
.
Language=Italian
Non è stato possibile installare il servizio %1 (Errore: %2)
.

MessageId=
Severity=Success
SymbolicName=MSG_REMOVED
Language=English
%1 service successfully removed
.
Language=German
%1 Dienst erfolgreich deinstalliert
.
Language=Italian
Servizio %1 deinstallato senza errori
.

MessageId=
Severity=Informational
SymbolicName=MSG_STARTED
Language=English
%1 service successfully started
.
Language=German
%1 Dienst erfolgreich gestartet
.
Language=Italian
Servizio %1 avviato senza errori
.

MessageId=
Severity=Informational
SymbolicName=MSG_STOPPED
Language=English
%1 service stopped
.
Language=German
%1 Dienst gestoppt
.
Language=Italian
Servizio %1 terminato
.

MessageId=
Severity=Informational
SymbolicName=MSG_PAUSED
Language=English
%1 service temporarily paused
.
Language=German
%1 Dienst zeitweise in Ruhezustand
.
Language=Italian
Servizio %1 sospeso monetaneamente
.

MessageId=
Severity=Informational
SymbolicName=MSG_CONTINUED
Language=English
%1 service resumed
.
Language=German
%1 Dienst wieder aktiv
.
Language=Italian
Servizio %1 nuovamente disponibile
.

MessageId=
Severity=Error
SymbolicName=MSG_INITERROR
Language=English
%1 service cannot be initialized
.
Language=German
%1 Dienst konnte nicht korrekt initialisieren
.
Language=Italian
Non è stato possibile inizializzare corretamente il Servizio %1
.

MessageId=
Severity=Error
SymbolicName=MSG_SERVICE_ERROR
Language=English
%1 service produced the following error: (WIN32: %2, Service Specific: %3)
.
Language=German
Im %1 Dienst ist der folgende Fehler aufgetreten: (WIN32: %2, Dienst-Spezifisch: %3)
.
Language=Italian
Nel Servizio %1 è accaduto il seguente errore:  (WIN32: %2, Errore-Servizio: %3)
.

MessageId=
SymbolicName=MSG_FATAL_ERROR
Language=English
%1 service produced the following fatal error: %2
The service execution will be terminated.
.
Language=German
Im %1 Dienst ist der folgender fataler Fehler aufgetreten: %2
Der Dienst wird abgebrochen.
.
Language=Italian
Nel Servizio %1 è accaduto il seguente errore fatale: %2
Il servizio viene terminato.
.

