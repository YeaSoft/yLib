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
 * FILENAME		:	yConsole.cpp
 * PURPOSE		:	Implementation of the NT console class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.2  2000/09/04 12:07:43  leopoldo
 * Updated license to zlib/libpng
 *
 * Revision 1.1  2000/05/26 14:04:54  leo
 * Initial revision
 *
 *============================================================================*/

#include "StdInc.hpp"

/*=============================================================================
 * @doc YLIB | yConsole.h
 *============================================================================*/

/*=============================================================================
 * IMPLEMENTATION
 *============================================================================*/
BOOL YConsole::Allocate (BOOL bReattachRTL /* = TRUE */)
{
	if ( IsAllocated () ) {
		return TRUE;
	}
	if ( ::AllocConsole () ) {
		if ( IsAllocated () && bReattachRTL ) {
			::YlbReattachRTL ();
		}
		return IsAllocated ();
	}
	return FALSE;
}

BOOL YConsole::Free ()
{
	if ( IsAllocated () ) {
		if ( ::FreeConsole () ) {
			return !IsAllocated ();
		}
		return FALSE;
	}
	return TRUE;
}

BOOL YConsole::Err (BOOL fAppendLF, LPCTSTR pszString, int cbLength /* = -1 */) const
{
	return Out (_proc.m_hStdErr, fAppendLF, pszString, cbLength);
}

BOOL YConsole::ErrVa (BOOL fAppendLF, LPCTSTR pszFormat, va_list va) const
{
	return OutVa (_proc.m_hStdErr, fAppendLF, pszFormat, va);
}

BOOL YConsole::Out (BOOL fAppendLF, LPCTSTR pszString, int cbLength /* = -1 */) const
{
	return Out (_proc.m_hStdOut, fAppendLF, pszString, cbLength);
}

BOOL YConsole::OutVa (BOOL fAppendLF, LPCTSTR pszFormat, va_list va) const
{
	return OutVa (_proc.m_hStdOut, fAppendLF, pszFormat, va);
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
	if ( _proc.m_hStdOut && lpsz ) {
		DWORD dwWritten;
		WriteConsoleA (_proc.m_hStdOut, lpsz, _mbclen ((const unsigned char *) lpsz), &dwWritten, NULL);
	}
	return *this;
}

#else

YConsole & YConsole::operator<< (LPCWSTR lpsz)
{
	if ( _proc.m_hStdOut && lpsz ) {
		DWORD dwWritten;
		WriteConsoleW (_proc.m_hStdOut, lpsz, wcslen (lpsz), &dwWritten, NULL);
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