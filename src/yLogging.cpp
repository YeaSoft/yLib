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
 * FILENAME		:	yLogging.cpp
 * PURPOSE		:	Implementation of the logging classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
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
		SetFlags (LOG_F_FATAL | LOG_F_ERROR | LOG_F_WARNING | LOG_F_INFO);
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
	TCHAR	cFlag;

	if ( !TestFlags (logFlag) ) {
		return TRUE;
	}
	switch ( logFlag ) {
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
	}

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


	_vsntprintf (
		szLogString + 24,
		_countof (szLogString) - 24,
		lpszFormat,
		va
	);
	szLogString[_countof (szLogString) - 1] = 0;
	DWORD dwRet;
	if ( !m_bOpenOnDemand || (m_bOpenOnDemand && ReOpen (FALSE)) ) {
		if ( !IsOpen () ) {
			return FALSE;
		}
		WriteFile (m_hFile, szLogString, _tcslen (szLogString), &dwRet, NULL);
#ifdef _DEBUG
		OutputDebugString (szLogString);
		OutputDebugString (_T("\r\n"));
#endif
		WriteFile (m_hFile, _T("\r\n"), 2 * sizeof (TCHAR), &dwRet, NULL);
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