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
 * FILENAME		:	yLogging.cpp
 * PURPOSE		:	Implementation of the logging classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.3  2000/09/04 12:07:43  leopoldo
 * Updated license to zlib/libpng
 *
 * Revision 1.2  2000/07/06 11:22:45  leo
 * Added flag LOG_F_TEXT to write text without time stamp
 *
 * Revision 1.1  2000/05/26  14:05:03  leo
 * Initial revision
 *
 *============================================================================*/

#include "StdInc.hpp"


BOOL YLogFileHandler::Open (LPCTSTR pszName, BOOL bTruncate /*= TRUE*/)
{

	_tcsncpy (m_szFileName, pszName, _countof (m_szFileName) - 1);
	m_szFileName[_countof (m_szFileName) - 1] = 0;

	return ReOpen (bTruncate);
}

BOOL YLogFileHandler::ReOpen (BOOL bTruncate)
{
	if ( m_hFile != INVALID_HANDLE_VALUE ) {
		return TRUE;
	}
	if ( !*m_szFileName ) {
		return FALSE;
	}

	m_hFile = CreateFile (
		m_szFileName,
		GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		(bTruncate) ? (CREATE_ALWAYS) : (OPEN_ALWAYS),
		FILE_FLAG_SEQUENTIAL_SCAN,
		NULL
	);
	if ( m_hFile == INVALID_HANDLE_VALUE ) {
		return FALSE;
	}
	SetFilePointer (m_hFile, 0, NULL, FILE_END);
	return TRUE;
}

void YLogFileHandler::SetVerbosityLevel (int iLevel /* = 0 */)
{
	Set (0);
	switch ( iLevel ) {
	case 3:
		SetFlags (LOG_F_XDBG3 | LOG_F_XDBG4);
	case 2:
		SetFlags (LOG_F_XDBG1 | LOG_F_XDBG2);
	case 1:
		SetFlags (LOG_F_DEBUG);
	case 0:
	default:
		SetFlags (LOG_F_FATAL | LOG_F_ERROR | LOG_F_WARNING | LOG_F_INFO | LOG_F_TEXT);
		break;
	}
}

void YLogFileHandler::SetOpenMode (BOOL bOpenOnDemand /* = FALSE */)
{
	if ( bOpenOnDemand && !m_bOpenOnDemand ) {
		// activate open on demand...
		Close ();		// close the file if opened
	}
	else if ( !bOpenOnDemand && m_bOpenOnDemand ) {
		// deactivate open on demand...
		ReOpen (FALSE);	// open the file in case
	}
	m_bOpenOnDemand = bOpenOnDemand;
}

BOOL YLogFileHandler::OutVa (LOG_FLAG logFlag, LPCTSTR lpszFormat, va_list va)
{
	TCHAR	szLogString[1024];
	TCHAR	szErrBuffer[768];
	TCHAR	cFlag;
	int		iLen;
	int		iErrLen;

	if ( !TestFlags (logFlag) ) {
		return TRUE;
	}
	switch ( logFlag & LOG_M_FLAGS ) {
	case LOG_F_FATAL:
		cFlag = _T('F');
		break;
	case LOG_F_ERROR:
		cFlag = _T('E');
		break;
	case LOG_F_WARNING:
		cFlag = _T('W');
		break;
	case LOG_F_INFO:
		cFlag = _T('I');
		break;
	case LOG_F_DEBUG:
		cFlag = _T('D');
		break;
	case LOG_F_XDBG1:
		cFlag = _T('1');
		break;
	case LOG_F_XDBG2:
		cFlag = _T('2');
		break;
	case LOG_F_XDBG3:
		cFlag = _T('3');
		break;
	case LOG_F_XDBG4:
		cFlag = _T('4');
		break;
	default:
		cFlag = _T(' ');
		break;
	}

	if ( (logFlag & LOG_M_FLAGS) == LOG_F_TEXT ) {
		iLen = _vsntprintf (szLogString, _countof (szLogString), lpszFormat, va);
	}
	else {
		SYSTEMTIME	st;
		GetLocalTime (&st);
		_stprintf (
			szLogString,
			_T("%04.04d%02.02d%02.02d %02d:%02d:%02d:%03d %c "),
			(int) st.wYear,
			(int) st.wMonth,
			(int) st.wDay,
			(int) st.wHour,
			(int) st.wMinute,
			(int) st.wSecond,
			(int) st.wMilliseconds,
			cFlag
		);


		iLen = _vsntprintf (
			szLogString + 24,
			_countof (szLogString) - 26,
			lpszFormat,
			va
		);
	}
	if ( iLen < 0 ) {
		iLen = _countof (szLogString) - 3;
		szLogString[iLen] = 0;
	}
	else {
		iLen += 24;
	}

	if ( logFlag & LOG_F_ERRSTR ) {
		iErrLen = FormatMessage	( 
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_MAX_WIDTH_MASK,
			NULL,
			GetLastError (),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			szErrBuffer,
			sizeof (szErrBuffer),
			NULL 
		);
		if ( iErrLen && ((iLen + iErrLen + 5) < _countof (szLogString)) ) {
			// error string is small enougth to fit into one line
			_tcscat (szLogString, _T(" ("));	// 2
			_tcscat (szLogString, szErrBuffer);	// iErrLen
			_tcscat (szLogString, _T(")\r\n"));	// 3
			iLen += iErrLen + 5;
			iErrLen = 0;	// OK: Don't append
		}
	}
	else {
		szLogString[iLen + 0] = _T('\r');
		szLogString[iLen + 1] = _T('\n');
		szLogString[iLen + 2] = 0;
		iLen += 2;
	}

	WriteToFile (szLogString, iLen);

	// we have a long error string to send...
	if ( (logFlag & LOG_F_ERRSTR) && iErrLen ) {
		iLen = _sntprintf (
			szLogString + 24,
			_countof (szLogString) - 24,
			_T("NT Error: %s\r\n"),
			szErrBuffer
		);
		if ( iLen < 0 ) {
			iLen = _countof (szLogString) - 1;
			szLogString[iLen] = 0;
		}
		else {
			iLen += 24;
		}
		WriteToFile (szLogString, iLen);
	}
	return TRUE;
}

BOOL YLogFileHandler::WriteToFile (LPCTSTR pszStr, int iLen /* = -1 */)
{
	if ( iLen < 0 ) {
		iLen = _tcslen (pszStr);
	}

	DWORD dwRet;
	if ( !m_bOpenOnDemand || (m_bOpenOnDemand && ReOpen (FALSE)) ) {
		if ( !IsOpen () ) {
			return FALSE;
		}
		WriteFile (m_hFile, pszStr, iLen * sizeof (TCHAR), &dwRet, NULL);
#ifdef _DEBUG
		OutputDebugString (pszStr);
#endif
		if ( m_bOpenOnDemand ) {
			Close ();
		}
	}
	return TRUE;
}

#ifndef YLB_ENABLE_INLINE
#include <yLogging.inl>
#endif

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////