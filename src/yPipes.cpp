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
 * FILENAME		:	yPipes.cpp
 * PURPOSE		:	Implementation of the data pipe classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.2  2000/09/04 12:07:43  leopoldo
 * Updated license to zlib/libpng
 *
 * Revision 1.1  2000/05/26 14:05:06  leo
 * Initial revision
 *
 *============================================================================*/

#include "StdInc.hpp"

/*=============================================================================
 * @doc YLIB | yMailSlots.h
 *============================================================================*/

/*=============================================================================
 * PIPE BASE CLASS
 *============================================================================*/
BOOL YPipe::GetPipeInfo (LPDWORD lpFlags, LPDWORD lpOutBufferSize, LPDWORD lpInBufferSize, LPDWORD lpMaxInstances) const
{
	if ( !IsValid () ) {
		::SetLastError (ERROR_INVALID_HANDLE);
		return FALSE;
	}
	return ::GetNamedPipeInfo (m_hHandle, lpFlags, lpOutBufferSize, lpInBufferSize, lpMaxInstances);
}

BOOL YPipe::PeekPipe (LPVOID lpBuffer, DWORD nBufferSize, LPDWORD lpBytesRead, LPDWORD lpTotalBytesAvail, LPDWORD lpBytesLeftThisMessage) const
{
	if ( !IsValid () ) {
		::SetLastError (ERROR_INVALID_HANDLE);
		return FALSE;
	}
	return ::PeekNamedPipe (m_hHandle, lpBuffer, nBufferSize, lpBytesRead, lpTotalBytesAvail, lpBytesLeftThisMessage);
}

/*=============================================================================
 * NAMED PIPE BASE CLASS
 *============================================================================*/
void YNamedPipe::Attach (HANDLE hNamedPipe)
{
	if ( hNamedPipe != m_hHandle ) {
		Close ();
	}
	m_hHandle = hNamedPipe;
}

BOOL YNamedPipe::GetHandleState (LPDWORD lpState, LPDWORD lpCurInstances, LPDWORD lpMaxCollectionCount, LPDWORD lpCollectDataTimeout, LPTSTR lpUserName, DWORD nMaxUserNameSize) const
{
	if ( !IsValid () ) {
		::SetLastError (ERROR_INVALID_HANDLE);
		return FALSE;
	}
	return ::GetNamedPipeHandleState (m_hHandle, lpState, lpCurInstances, lpMaxCollectionCount, lpCollectDataTimeout, lpUserName, nMaxUserNameSize);
}

BOOL YNamedPipe::SetHandleState (LPDWORD lpMode, LPDWORD lpMaxCollectionCount, LPDWORD lpCollectDataTimeout) const
{
	if ( !IsValid () ) {
		::SetLastError (ERROR_INVALID_HANDLE);
		return FALSE;
	}
	return ::SetNamedPipeHandleState (m_hHandle, lpMode, lpMaxCollectionCount, lpCollectDataTimeout);
}

/*=============================================================================
 * SERVER NAMED PIPE
 *============================================================================*/
BOOL YServerNamedPipe::Create (LPCTSTR lpName, DWORD dwOpenMode, DWORD dwPipeMode, DWORD nMaxInstances, DWORD nOutBufferSize, DWORD nInBufferSize, DWORD nDefaultTimeOut, LPSECURITY_ATTRIBUTES lpSecurityAttributes /* = NULL */)
{
	HANDLE hPipe = CreateNamedPipe (
		lpName,
		dwOpenMode,
		dwPipeMode,
		nMaxInstances,
		nOutBufferSize,
		nInBufferSize,
		nDefaultTimeOut,
		lpSecurityAttributes
	);
	if ( hPipe != INVALID_HANDLE_VALUE ) {
		Close ();
		m_hHandle = hPipe;
		return TRUE;
	}
	return FALSE;
}

/*=============================================================================
 * CLIENT NAMED PIPE
 *============================================================================*/
BOOL YClientNamedPipe::Create (LPCTSTR pszPipeName, DWORD dwDesiredAccess, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwFlagsAndAttributes)
{
	if ( !IsValidPipeName (pszPipeName) ) {
		::SetLastError (ERROR_BAD_NET_NAME);
		return FALSE;
	}
	HANDLE	hPipe = ::CreateFile (
		pszPipeName,
		dwDesiredAccess,
		0,
		lpSecurityAttributes,
		OPEN_EXISTING,
		dwFlagsAndAttributes,
		NULL
	);
	if ( hPipe != INVALID_HANDLE_VALUE ) {
		Close ();
		m_hHandle = hPipe;
		return TRUE;
	}
	return FALSE;
}

BOOL YClientNamedPipe::Create (LPCTSTR pszName, LPCTSTR pszComputer, DWORD dwDesiredAccess, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwFlagsAndAttributes)
{
	TCHAR	szPipeName[MAX_PATH];

	_stprintf (szPipeName, _T("\\\\%s\\pipe\\%s"), (pszComputer && *pszComputer) ? (pszComputer) : (_T(".")), pszName);

	HANDLE	hPipe = ::CreateFile (
		szPipeName,
		dwDesiredAccess,
		0,
		lpSecurityAttributes,
		OPEN_EXISTING,
		dwFlagsAndAttributes,
		NULL
	);
	if ( hPipe != INVALID_HANDLE_VALUE ) {
		Close ();
		m_hHandle = hPipe;
		return TRUE;
	}
	return FALSE;
}

BOOL YClientNamedPipe::IsValidPipeName (LPCTSTR lpFileName)
{
	if ( (lpFileName[0] != '\\') || (lpFileName[1] != '\\') ) {
		// must start with two backslashes
		return FALSE;
	}
	if ( lpFileName[2] == '.' ) {
		// if local pipe must be followed by "\\pipe\\" and something other
		return (_tcsnicmp (lpFileName + 3, _T("\\pipe\\"), 6) == 0) && lpFileName[9];
	}

	LPCTSTR lpPtr = _tcschr (lpFileName + 2, _T('\\'));
	if ( !lpPtr || (lpPtr == (lpFileName + 2)) ) {
		// invalid
		return FALSE;
	}
	return (_tcsnicmp (lpPtr, _T("\\pipe\\"), 6) == 0) && lpPtr[6];
}


#ifndef YLB_ENABLE_INLINE
#include <yPipes.inl>
#endif

/// IDENTITY STUFF ///
//LPCTSTR lpComment = _T("$Id$");

//
// EoF
////////