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
 * FILENAME		:	MailSlots.cpp
 * PURPOSE		:	yLib application sample (Mailslot Samples)
 * SCOPE		:	yLib SDK
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

#include "StdAfc.h"
#include "Sample1.h"

/*=============================================================================
 * CLIENT IMPLEMENTATION
 *============================================================================*/
void Sample1::RunMSClient (YCmdLineParam *cliPar)
{
	_tprintf (_T("This example shows sending of messages via a mailslot:\n"));
	_tprintf (_T("\n"));

	YClientMailslot		ms;
	LPCTSTR				lpComputerName = (cliPar->GetParamCount ()) ? (cliPar->GetAt(ZERO)) : (NULL);

	if ( !ms.Create (_T("TestSlot"), lpComputerName) ) {
		_tprintf (_T("ERROR: Cannot open the mailslot\n"));
		return;
	}

	if ( cliPar->GetParamCount () > 1 ) {
		for ( UINT i = 1; i < cliPar->GetParamCount (); i++ ) {
			LPCTSTR	pszStr = cliPar->GetAt (i);

			if ( !ms.Write (pszStr, _tcslen (pszStr) + 1) ) {
				_tprintf (_T("ERROR: Cannot write on the mailslot\n"));
				return;
			}

		}
	}
	else {
		LPCTSTR	pszStr = _T("Test String");

		if ( !ms.Write (pszStr, _tcslen (pszStr) + 1) ) {
			_tprintf (_T("ERROR: Cannot write on the mailslot\n"));
			return;
		}

	}

	_tprintf (_T("Write finished.\n\n"));
}

/*=============================================================================
 * SERVER IMPLEMENTATION
 *============================================================================*/
class CMyMailslotServer : public YMailslotServer
{
public:
	CMyMailslotServer			();

public:
	// overridables
	virtual void				OnTimer					();
	virtual void				OnReceive				(LPVOID lpData, UINT cbData);
	virtual void				OnFatalError			(DWORD dwError);
};

CMyMailslotServer::CMyMailslotServer () : YMailslotServer (_T("TestSlot"), 15000, 0, 16)
{
}

void CMyMailslotServer::OnTimer ()
{
	_tprintf (_T("Timer event\n"));
}

void CMyMailslotServer::OnReceive (LPVOID lpData, UINT cbData)
{
	_tprintf (_T("Received: '%s'\n"), lpData);
}

void CMyMailslotServer::OnFatalError (DWORD dwError)
{
	_tprintf (_T("Fatal error %lu\n"), dwError);
}

void Sample1::RunMSServer (YCmdLineParam *cliPar)
{
	_tprintf (_T("This example shows a named mailslot server thread:\n"));

	DWORD dwWait = 30;

	if ( cliPar->GetParamCount () ) {
		if ( _ttoi (cliPar->GetAt(ZERO)) > 5 ) {
			dwWait = _ttoi (cliPar->GetAt(ZERO));
		}
	}

	_tprintf (_T("Server will remain active for %lu seconds...\n"), dwWait);
	_tprintf (_T("\n"));

	CMyMailslotServer	ms;

	if ( !ms.Create () ) {
		_tprintf (_T("Error %i creating the mailslot server\n"), ms.GetLastError ());
		return;
	}

	if ( ms.Wait (dwWait * 1000) == WAIT_TIMEOUT ) {
		ms.Terminate (10000, 0);
	}

	_tprintf (_T("Mailslot Server terminated.\n"));
}
