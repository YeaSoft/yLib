/*=============================================================================
 * This is a part of the yLib Software Development Kit.
 * Copyright (C) 1998-2000 YEAsoft Int'l.
 * All rights reserved.
 *=============================================================================
 * Copyright (c) 1998-2000 YEAsoft Int'l (Leo Moll, Andrea Pennelli).
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the
 * use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in
 *    a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *=============================================================================
 * FILENAME		:	yMailSlotServer.cpp
 * PURPOSE		:	Implementation of the mailslot server class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:05:05  leo
 * Initial revision
 *
 *============================================================================*/

#include "StdInc.hpp"

/*=============================================================================
 * @doc YLIB | yMailSlotServer.h
 *============================================================================*/

/*=============================================================================
 * MAILSLOT SERVER CLASS
 *============================================================================*/
YMailslotServer::YMailslotServer (
	LPCTSTR					pszMailslotName,
	UINT					nTimer,
	DWORD					dwMaxMessageSize,
	UINT					cbReadBuffer,
	DWORD					dwReadTimeout,
	LPSECURITY_ATTRIBUTES	lpSecurityAttributes,
	LPCTSTR					pszName
) : YWorkerThread (pszName)
{
	SetLastError (ERROR_SUCCESS);
	SetMailslotName (pszMailslotName);
	SetTimer (nTimer);
	SetMaxMessageSize (dwMaxMessageSize);
	SetReadTimeout (dwReadTimeout);
	SetReadBufferSize (cbReadBuffer);
	SetSecurityAttributes (lpSecurityAttributes);
}

BOOL YMailslotServer::OnIncreaseBuffer ()
{
	if ( m_lpReadBuffer.Realloc (m_cbReadBufferSize * 2, TRUE, TRUE) ) {
		m_cbReadBufferSize *= 2;
		return TRUE;
	}
	return FALSE;
}

BOOL YMailslotServer::Allocate ()
{
	try {
		if ( !m_sd.Create () ) {
			throw YException (ERROR_NOT_ENOUGH_MEMORY);
		}
		if ( !m_sd.SetDacl (TRUE, NULL, FALSE) ) {
			throw YException (::GetLastError ());
		}
		m_sa.SetSecurityDescriptor (m_sd);

		// allocate the read buffer
		if ( !(m_lpReadBuffer.Alloc (m_cbReadBufferSize)) ) {
			throw YException (ERROR_NOT_ENOUGH_MEMORY);
		}

		// create the termination event
		if ( !m_evTerm.Create (TRUE) ) {
			throw YException (::GetLastError ());
		}

		// create the read event
		if ( !m_evRead.Create (TRUE) ) {
			throw YException (::GetLastError ());
		}

		// create the mailslot
		TCHAR	szName[MAX_PATH];

		_tcscpy (szName, _T("\\\\.\\mailslot\\"));
		_tcscat (szName, GetMailslotName ());
		if ( !m_ms.Create (szName, GetMaxMessageSize (), GetReadTimeout (), GetSecurityAttributes ()) ) {
			throw YException (::GetLastError ());
		}

	}
	catch ( YException e ) {
		SetLastError (e.GetLastError ());
		Deallocate ();
		return FALSE;
	}

	return TRUE;
}

void YMailslotServer::Deallocate ()
{
	m_ms.Close ();
	m_evRead.Close ();
	m_evTerm.Close ();
	m_lpReadBuffer.Free ();
}

BOOL YMailslotServer::PreCreateThread (BOOL &bSuspended, UINT &uStackSize, LPSECURITY_ATTRIBUTES &lpThreadAttributes)
{
	// plausibility checks
	if ( !*m_szMailslotName ) {
		SetLastError (ERROR_INVALID_PARAMETER);
		return FALSE;
	}

	if ( m_cbReadBufferSize < 16 ) {
		SetLastError (ERROR_INVALID_PARAMETER);
		return FALSE;
	}

	Deallocate ();

	// prepare internal data
	return Allocate ();
}

UINT YMailslotServer::OnRunThread ()
{
	YMultiGuard		mg;
	OVERLAPPED		ov;
	BOOL			fIOPending;

	memset (&ov, 0, sizeof (ov));

	mg.AddObject (m_evTerm);
	mg.AddObject (m_evRead);
	ov.hEvent = m_evRead;

	while ( TRUE ) {
		if ( m_ms.Read (m_lpReadBuffer, m_cbReadBufferSize, &ov) ) {
			// message completely received. loop on!
			OnReceive (m_lpReadBuffer, m_ms.GetBytesRead ());
			continue;
		}

		// read returned false....
		switch ( ::GetLastError () ) {
		case ERROR_INSUFFICIENT_BUFFER:
			// increase buffer size
			if ( !OnIncreaseBuffer () ) {
				OnFatalError (ERROR_NOT_ENOUGH_MEMORY);
				return 0;
			}
			continue;
		case NOERROR:
			// SNH: Strange....
			continue;
		case ERROR_IO_PENDING:
			// OK. Let's go to the waiter loop
			fIOPending = TRUE;
			break;
		default:
			// the mailslot seems to be broken! terminate.
			OnFatalError (::GetLastError ());
			return 0;
		}


		// wait loop
		while ( fIOPending ) {
			DWORD cbBytes;
			switch ( mg.Wait (GetTimer ()) ) {
			case WAIT_TIMEOUT:
				OnTimer ();
				break;
			case WAIT_OBJECT_0:
				// termination requested
				return 0;
			case WAIT_OBJECT_0 + 1:
				// data received
				if ( !m_ms.GetOverlappedResult (&ov, &cbBytes, FALSE) ) {
					switch ( ::GetLastError () ) {
					case ERROR_INSUFFICIENT_BUFFER:
						// increase buffer size
						if ( !OnIncreaseBuffer () ) {
							OnFatalError (ERROR_NOT_ENOUGH_MEMORY);
							return 0;
						}
						fIOPending = FALSE;
						continue;
					case ERROR_IO_PENDING:
						// SNH: IO still pending. wait.
						continue;
					case NOERROR:
						// SNH:
						fIOPending = FALSE;
						continue;
					default:
						// the mailslot seems to be broken! terminate.
						OnFatalError (::GetLastError ());
						return 0;
					}
				}
				OnReceive (m_lpReadBuffer, cbBytes);
				fIOPending = FALSE;
				break;
			default:
				// sumething terribly wrong. terminate.
				OnFatalError (::GetLastError ());
				return 0;
			}
		}
	};

	return 0;
}

#ifndef YLB_ENABLE_INLINE
#include <yMailSlotServer.inl>
#endif

/// RCS STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////