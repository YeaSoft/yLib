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
 * FILENAME		:	yConsole.cpp
 * PURPOSE		:	Implementation of the NT console class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

#include "StdInc.hpp"

/*=============================================================================
 * @doc YLIB | yConsole.h
 *============================================================================*/

/*=============================================================================
 * IMPLEMENTATION
 *============================================================================*/
BOOL YConsole::Allocate ()
{
	if ( IsAllocated () ) {
		if ( !AreHandlesValid () ) {
			return LoadHandles ();
		}
		return TRUE;
	}
	if ( ::AllocConsole () ) {
		return LoadHandles ();
	}
	ClearHandles ();
	return FALSE;
}

BOOL YConsole::Free ()
{
	if ( IsAllocated () ) {
		if ( FreeConsole () ) {
			ClearHandles ();
			return TRUE;
		}
		return FALSE;
	}
	ClearHandles ();
	return TRUE;
}

BOOL YConsole::Out (HANDLE hHandle, BOOL fAppendLF, LPCTSTR pszString, int cbLength) const
{
	if ( !hHandle ) {
		return FALSE;
	}
	if ( cbLength == -1 ) {
		cbLength = (pszString) ? (_tcslen (pszString)) : (0);
	}
	DWORD	dwWritten;
	BOOL	bRet = (cbLength && pszString) ? (::WriteConsole (hHandle, pszString, cbLength, &dwWritten, NULL)) : (TRUE);
	if ( fAppendLF ) {
		bRet = bRet && ::WriteConsole (hHandle, _T("\n"), 1, &dwWritten, NULL);
	}
	return bRet;
}

BOOL YConsole::OutVa (HANDLE hHandle, BOOL fAppendLF, LPCTSTR pszFormat, va_list va) const
{
	if ( !hHandle ) {
		return FALSE;
	}

	TCHAR	szBuffer[4096];

	int iLength = _vsntprintf (szBuffer, _countof (szBuffer), pszFormat, va);
	if ( iLength < 0 ) {
		szBuffer[_countof (szBuffer) - 1] = 0;
		iLength = _countof (szBuffer) - 1;
	}
	return Out (hHandle, fAppendLF, szBuffer, iLength);
}

#ifdef _UNICODE

#include <mbstring.h>

YConsole & YConsole::operator<< (LPCSTR lpsz)
{
	if ( m_hStdOut && lpsz ) {
		DWORD dwWritten;
		WriteConsoleA (m_hStdOut, lpsz, _mbclen ((const unsigned char *) lpsz), &dwWritten, NULL);
	}
	return *this;
}

#else

YConsole & YConsole::operator<< (LPCWSTR lpsz)
{
	if ( m_hStdOut && lpsz ) {
		DWORD dwWritten;
		WriteConsoleW (m_hStdOut, lpsz, wcslen (lpsz), &dwWritten, NULL);
	}
	return *this;
}

#endif

#ifndef YLB_ENABLE_INLINE
#include <yConsole.inl>
#endif

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////