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
 * FILENAME		:	yMailSlots.cpp
 * PURPOSE		:	Implementation of the mailslot classes
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
 * MAILSLOT BASE CLASS
 *============================================================================*/
void YMailslot::Attach (HANDLE hMailSlot)
{
	if ( hMailSlot != m_hHandle ) {
		Close ();
	}
	m_hHandle = hMailSlot;
}

/*=============================================================================
 * SERVER MAILSLOT
 *============================================================================*/
BOOL YServerMailslot::Create (LPCTSTR pszName, DWORD dwMaxMessageSize, DWORD dwReadTimeout, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
	HANDLE hMailslot = ::CreateMailslot (
		pszName,
		dwMaxMessageSize,
		dwReadTimeout,
		lpSecurityAttributes
	);
	if ( hMailslot != INVALID_HANDLE_VALUE ) {
		Close ();
		m_hHandle = hMailslot;
		return TRUE;
	}
	return FALSE;
}

/*=============================================================================
 * CLIENT MAILSLOT
 *============================================================================*/
BOOL YClientMailslot::Create (LPCTSTR pszMailslotName, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
	if ( !IsValidMailslotName (pszMailslotName) ) {
		::SetLastError (ERROR_BAD_NET_NAME);
		return FALSE;
	}
	HANDLE	hMailslot = ::CreateFile (
		pszMailslotName,
		GENERIC_WRITE,
		FILE_SHARE_READ,
		lpSecurityAttributes,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if ( hMailslot != INVALID_HANDLE_VALUE ) {
		Close ();
		m_hHandle = hMailslot;
		return TRUE;
	}
	return FALSE;
}

BOOL YClientMailslot::Create (LPCTSTR pszName, LPCTSTR pszComputer, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
	TCHAR	szMailslotName[MAX_PATH];

	_stprintf (szMailslotName, _T("\\\\%s\\mailslot\\%s"), (pszComputer && *pszComputer) ? (pszComputer) : (_T(".")), pszName);

	HANDLE	hMailslot = ::CreateFile (
		szMailslotName,
		GENERIC_WRITE,
		FILE_SHARE_READ,
		lpSecurityAttributes,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if ( hMailslot != INVALID_HANDLE_VALUE ) {
		Close ();
		m_hHandle = hMailslot;
		return TRUE;
	}
	return FALSE;
}

BOOL YClientMailslot::IsValidMailslotName (LPCTSTR lpFileName)
{
	if ( (lpFileName[0] != '\\') || (lpFileName[1] != '\\') ) {
		// must start with two backslashes
		return FALSE;
	}
	if ( lpFileName[2] == '.' ) {
		// if local mailslot must be followed by "\\mailslot\\" and something other
		return (_tcsnicmp (lpFileName + 3, _T("\\mailslot\\"), 10) == 0) && lpFileName[13];
	}

	LPTSTR lpPtr = _tcschr (lpFileName + 2, _T('\\'));
	if ( !lpPtr || (lpPtr == (lpFileName + 2)) ) {
		// invalid
		return FALSE;
	}
	return (_tcsnicmp (lpPtr, _T("\\mailslot\\"), 10) == 0) && lpPtr[10];
}


#ifndef YLB_ENABLE_INLINE
#include <yMailSlots.inl>
#endif

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////