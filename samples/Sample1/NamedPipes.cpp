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
 * FILENAME		:	NamedPipes.cpp
 * PURPOSE		:	yLib application sample (Named Pipes Samples)
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
void Sample1::RunNPClient (YCmdLineParam *cliPar)
{
	_tprintf (_T("This example shows sending of transactions via a named pipe:\n"));
	_tprintf (_T("\n"));

	YClientNamedPipe	np;
	LPCTSTR				lpComputerName = (cliPar->GetParamCount ()) ? (cliPar->GetAt(ZERO)) : (NULL);

	if ( !np.Create (_T("TestPipe"), lpComputerName) ) {
		_tprintf (_T("Cannot open the named pipe\n"));
		return;
	}

	if ( !np.SetPipeMode (PIPE_READMODE_MESSAGE) ) {
		_tprintf (_T("Cannot set the named pipe mode\n"));
		return;
	}

	TCHAR	szResult[32];

	if ( cliPar->GetParamCount () > 1 ) {
		for ( UINT i = 1; i < cliPar->GetParamCount (); i++ ) {
			LPCTSTR	pszStr = cliPar->GetAt (i);
			DWORD	dwRead;
			if ( !np.Transact (pszStr, _tcslen (pszStr) + 1, szResult, _countof (szResult), &dwRead) ) {
				_tprintf (_T("Cannot transact the named pipe\n"));
				return;
			}
		}
	}
	else {
		LPCTSTR	pszStr = _T("Test String");
		DWORD	dwRead;
		if ( !np.Transact (pszStr, _tcslen (pszStr) + 1, szResult, _countof (szResult), &dwRead) ) {
			_tprintf (_T("Cannot transact the named pipe\n"));
			return;
		}
	}

	_tprintf (_T("The server returned %s"), szResult);
}

/*=============================================================================
 * SERVER IMPLEMENTATION
 *============================================================================*/
class CMyInstance : public YPipeInstance
{
	DECLARE_DYNAMIC_CREATABLE	(CMyInstance);

public:
	CMyInstance					() { }

public:
	// overridables
	virtual BOOL				InitInstance			(UINT nInstanceNumber);
	virtual void				ExitInstance			();
	virtual void				OnConnect				();
	virtual void				OnTransact				(LPVOID lpData, UINT cbData);
	virtual void				OnError					();
	virtual void				OnDisconnect			();
	virtual void				OnTerminate				();

public:
	UINT						m_nInstanceNumber;
};

class CMyPipeServer : public YPipeServer
{
public:
	CMyPipeServer				();

public:
	// overridables
	virtual void				OnProxy					(UINT nProxyNumber);
};

CMyPipeServer::CMyPipeServer () : YPipeServer (RUNTIME_INFO(CMyInstance), _T("TestPipe"), 10, 1)
{
}

void CMyPipeServer::OnProxy (UINT nProxyNumber)
{
	_tprintf (_T("CMyPipeServer::OnProxy (%i)\n"), nProxyNumber);
}


IMPLEMENT_DYNAMIC_CREATABLE(CMyInstance,YPipeInstance);

BOOL CMyInstance::InitInstance (UINT nInstanceNumber)
{
	_tprintf (_T("[%i] CMyInstance::InitInstance\n"), nInstanceNumber);
	m_nInstanceNumber = nInstanceNumber;
	return TRUE;
}

void CMyInstance::ExitInstance ()
{
	_tprintf (_T("[%i] CMyInstance::ExitInstance\n"), m_nInstanceNumber);
}

void CMyInstance::OnConnect ()
{
	_tprintf (_T("[%i] CMyInstance::OnConnect\n"), m_nInstanceNumber);
}

void CMyInstance::OnTransact (LPVOID lpData, UINT cbData)
{
	_tprintf (_T("[%i] CMyInstance::OnTransact: '%s'\n"), m_nInstanceNumber, lpData);
	LPCTSTR pszResponse = _T("OK");
	WriteResponse (pszResponse, _tcslen (pszResponse) + 1);
}

void CMyInstance::OnError ()
{
	_tprintf (_T("[%i] CMyInstance::OnError\n"), m_nInstanceNumber);
}

void CMyInstance::OnDisconnect ()
{
	_tprintf (_T("[%i] CMyInstance::OnDisconnect\n"), m_nInstanceNumber);
}

void CMyInstance::OnTerminate ()
{
	_tprintf (_T("[%i] CMyInstance::OnTerminate\n"), m_nInstanceNumber);
}

void Sample1::RunNPServer (YCmdLineParam *cliPar)
{
	_tprintf (_T("This example shows a named pipe server thread:\n"));

	DWORD dwWait = 30;

	if ( cliPar->GetParamCount () ) {
		if ( _ttoi (cliPar->GetAt(ZERO)) > 5 ) {
			dwWait = _ttoi (cliPar->GetAt(ZERO));
		}
	}

	_tprintf (_T("Server will remain active for %lu seconds...\n"), dwWait);
	_tprintf (_T("\n"));

	CMyPipeServer	ps;

	if ( !ps.Create () ) {
		_tprintf (_T("Error %i creating the pipe server\n"), ps.GetLastError ());
		return;
	}

	do {
		if ( ps.Wait (1000) == WAIT_TIMEOUT ) {
			ps.TriggerProxy (0);
		}
		else {
			// pipe server has spontaneously exited
			_tprintf (_T("Pipe Server terminated itself.\n"));
			return;
		}
	} while ( dwWait-- );

	ps.Terminate (10000, 0);

	_tprintf (_T("Pipe Server terminated.\n"));
}

