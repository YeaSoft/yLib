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
 * FILENAME		:	yPipes.cpp
 * PURPOSE		:	Implementation of the data pipe classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
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

	LPTSTR lpPtr = _tcschr (lpFileName + 2, _T('\\'));
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
#pragma comment( exestr, "$Id$" )

//
// EoF
////////