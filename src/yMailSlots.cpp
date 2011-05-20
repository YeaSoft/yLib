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
 * FILENAME		:	yMailSlots.cpp
 * PURPOSE		:	Implementation of the mailslot classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.2  2000/09/04 12:07:43  leopoldo
 * Updated license to zlib/libpng
 *
 * Revision 1.1  2000/05/26 14:05:04  leo
 * Initial revision
 *
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

	LPCTSTR lpPtr = _tcschr (lpFileName + 2, _T('\\'));
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
//LPCTSTR lpComment = _T("$Id$");

//
// EoF
////////