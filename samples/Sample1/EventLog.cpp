/*=============================================================================
 * This is a part of the yLib Software Development Kit.
 * Copyright (C) 1998-2000 YEAsoft Inc.
 * All rights reserved.
 *=============================================================================
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation. In addition, you may also charge for any
 * application using yLib, and are under no obligation to supply source
 * code. You must accredit YEAsoft Inc. in the "About Box", or banner
 * of your application. 
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should also have received a copy of the GNU General Public License
 * with this software, also indicating additional rights you have when using
 * yLib.
 *=============================================================================
 * FILENAME		:	EventLog.cpp
 * PURPOSE		:	yLib application sample (Event Logging Parts)
 * SCOPE		:	yLib SDK
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:07:23  leo
 * Initial revision
 *
 *============================================================================*/

#include "StdAfc.h"
#include "Sample1.h"

/*=============================================================================
 * IMPLEMENTATION
 *============================================================================*/
void Sample1::EvtInstall ()
{
	_tprintf (_T("This example shows the installation of an application as\n"));
	_tprintf (_T("an Event Source:\n"));
	_tprintf (_T("\n"));

	YPathString	ysApp;
	ysApp.Format (_T("%s\\%s"), GetImagePath (), GetImageName ());

	if ( YEventLogSource::Install (GetAppName (), ysApp, 2) ) {
		_tprintf (_T("Application successfully installed within the event log\n\n"));
	}
	else {
		_tprintf (_T("Error while installing the application within the event log\n\n"));
	}
}

void Sample1::EvtRemove ()
{
	_tprintf (_T("This example shows the removal of an application installed as\n"));
	_tprintf (_T("an Event Source:\n"));
	_tprintf (_T("\n"));
	if ( YEventLogSource::Uninstall (GetAppName ()) ) {
		_tprintf (_T("Application successfully removed from the event log\n\n"));
	}
	else {
		_tprintf (_T("Error while removing the application from the event log\n\n"));
	}
}

void Sample1::EvtTest1 (YCmdLineParam *cliPar)
{
	_tprintf (_T("This example post a simple event into the event log:\n"));
	_tprintf (_T("\n"));

	YEventLogSource	evt;

	if ( cliPar->GetCount () ) {
		_tprintf (_T("Message will be set with userid '%s'\n"), cliPar->GetAt (ZERO));
		if ( !evt.SetOriginatorSID (cliPar->GetAt (ZERO)) ) {
			_tprintf (_T("Error geeting the SID for user '%s'\n"), cliPar->GetAt (ZERO));
		}
	}
	if ( evt.Register (GetAppName ()) ) {
		if ( evt.Error (CAT_NO_PARAMS, MSG_TEST1, NULL) ) {
			_tprintf (_T("Test Message 1 successfully written!\n"));
		}
		else {
			_tprintf (_T("Could not write Test Message 1!\n"));
		}
	}
	else {
		_tprintf (_T("Could not register with the event log\n"));
	}
}

void Sample1::EvtTest2 (YCmdLineParam *cliPar)
{
	_tprintf (_T("This example post an event with one parameter into the event log:\n"));
	_tprintf (_T("\n"));

	YEventLogSource	evt;

	if ( cliPar->GetCount () ) {
		_tprintf (_T("Message will be set with userid '%s'\n"), cliPar->GetAt (ZERO));
		if ( !evt.SetOriginatorSID (cliPar->GetAt (ZERO)) ) {
			_tprintf (_T("Error geeting the SID for user '%s'\n"), cliPar->GetAt (ZERO));
		}
	}
	if ( evt.Register (GetAppName ()) ) {
		if ( evt.Warning (CAT_PARAMS, MSG_TEST2, _T("PARM1"), NULL) ) {
			_tprintf (_T("Test Message 2 successfully written!\n"));
		}
		else {
			_tprintf (_T("Could not write Test Message 2!\n"));
		}
	}
	else {
		_tprintf (_T("Could not register with the event log\n"));
	}
}

void Sample1::EvtTest3 (YCmdLineParam *cliPar)
{
	_tprintf (_T("This example post an event with one parameter into the event log\n"));
	_tprintf (_T("and demonstrates fixed parameters for event log messages\n"));
	_tprintf (_T("\n"));

	LPCTSTR			lpInserts[2];
	YEventLogSource	evt;

	lpInserts[0] = _T("Insert 1");
	lpInserts[1] = _T("Insert 2");

	evt.SetInserts (2, lpInserts);

	if ( cliPar->GetCount () ) {
		_tprintf (_T("Message will be set with userid '%s'\n"), cliPar->GetAt (ZERO));
		if ( !evt.SetOriginatorSID (cliPar->GetAt (ZERO)) ) {
			_tprintf (_T("Error geeting the SID for user '%s'\n"), cliPar->GetAt (ZERO));
		}
	}
	if ( evt.Register (GetAppName ()) ) {
		if ( evt.Info (CAT_PARAMS, MSG_TEST3, _T("PARM1"), NULL) ) {
			_tprintf (_T("Test Message 3 successfully written!\n"));
		}
		else {
			_tprintf (_T("Could not write Test Message 3!\n"));
		}
	}
	else {
		_tprintf (_T("Could not register with the event log\n"));
	}
}

