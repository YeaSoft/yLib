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
 * FILENAME		:	yFiles.cpp
 * PURPOSE		:	Implementation of the generic file classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

#include "StdInc.hpp"
#include <fcntl.h>
#include <io.h>

/*=============================================================================
 * @doc YLIB | yFiles.h
 *============================================================================*/
HANDLE YBaseFile::OpenHelper (LPCTSTR pszFileName, UINT nOpenFlags)
{
	ASSERTY(pszFileName);
	ASSERTY(YlbIsValidString(pszFileName));

	// map read/write mode
	DWORD	dwAccess = 0;
	switch ( nOpenFlags & (YFile::modeRead|YFile::modeWrite|YFile::modeReadWrite) ) {
	case YFile::modeRead:
		dwAccess = GENERIC_READ;
		break;
	case YFile::modeWrite:
		dwAccess = GENERIC_WRITE;
		break;
	case YFile::modeReadWrite:
		dwAccess = GENERIC_READ | GENERIC_WRITE;
		break;
	default:
		// invalid share mode
		ASSERTY(FALSE);
	}

	// map share mode
	DWORD	dwShareMode = 0;
	switch ( nOpenFlags & (YFile::shareExclusive|YFile::shareDenyWrite|YFile::shareDenyRead|YFile::shareDenyNone) ) {
	default:
		// invalid share mode?
		ASSERTY(FALSE);
	case YFile::shareExclusive:
		dwShareMode = 0;
		break;
	case YFile::shareDenyWrite:
		dwShareMode = FILE_SHARE_READ;
		break;
	case YFile::shareDenyRead:
		dwShareMode = FILE_SHARE_WRITE;
		break;
	case YFile::shareDenyNone:
		dwShareMode = FILE_SHARE_WRITE | FILE_SHARE_READ;
		break;
	}

	// map modeNoInherit flag
	YSecurityAttributes	ysa;
	ysa.SetInheritance ((nOpenFlags & YFile::modeNoInherit) == 0);

	// map creation flags
	DWORD	dwCreateFlag;
	if ( nOpenFlags & YFile::modeCreate ) {
		if ( nOpenFlags & YFile::modeNoTruncate ) {
			dwCreateFlag = OPEN_ALWAYS;
		}
		else {
			dwCreateFlag = CREATE_ALWAYS;
		}
	}
	else {
		dwCreateFlag = OPEN_EXISTING;
	}

	// attempt file creation
	return ::CreateFile (
		pszFileName,
		dwAccess,
		dwShareMode,
		&ysa,
		dwCreateFlag,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
}

DWORD YBaseFile::GetPosition (LPDWORD lpdwPosHigh) const
{
	ASSERTY(IsValid());
	if ( lpdwPosHigh ) {
		*lpdwPosHigh = 0;
	}
	return ::SetFilePointer (m_hHandle, 0, (LPLONG) lpdwPosHigh, FILE_CURRENT);
}

/*=============================================================================
 * THE GENERIC FILE CLASS
 *============================================================================*/
void YFile::Attach (HANDLE hFile)
{
	if ( hFile != m_hHandle ) {
		Close ();
	}
	m_hHandle = hFile;
}

BOOL YFile::Open (LPCTSTR pszFileName, UINT nOpenFlags)
{
	ASSERTY((nOpenFlags & typeText) == 0);
	// YFile objects are always binary and CreateFile does not need flag
	nOpenFlags &= ~(UINT) typeBinary;

	HANDLE hFile = OpenHelper (pszFileName, nOpenFlags);
	if ( hFile == INVALID_HANDLE_VALUE ) {
		return FALSE;
	}
	Close ();
	m_hHandle = hFile;
	return TRUE;
}

BOOL YFile::Create (
	LPCTSTR					lpFileName,
	DWORD					dwDesiredAccess,
	DWORD					dwShareMode,
	LPSECURITY_ATTRIBUTES	lpSecurityAttributes,
	DWORD					dwCreationDisposition,
	DWORD					dwFlagsAndAttributes,
	HANDLE					hTemplateFile
)
{
	HANDLE hFile = ::CreateFile (
		lpFileName,
		dwDesiredAccess,
		dwShareMode,
		lpSecurityAttributes,
		dwCreationDisposition,
		dwFlagsAndAttributes,
		hTemplateFile
	);
	if ( hFile == INVALID_HANDLE_VALUE ) {
		return FALSE;
	}
	Close ();
	m_hHandle = hFile;
	return TRUE;
}

BOOL YFile::SetLength (DWORD dwSize, DWORD dwSizeHigh)
{
	ASSERTY(IsValid());
	DWORD dwPosLow, dwPosHigh;
	dwPosLow = GetPosition (&dwPosHigh);

	Seek (dwSize, (LPLONG) ((dwSizeHigh) ? (&dwSizeHigh) : (NULL)));
	BOOL bRet = ::SetEndOfFile (m_hHandle);
	Seek (dwPosLow, dwPosHigh);
	return bRet;
}

/*=============================================================================
 * THE STREAM FILE CLASS
 *============================================================================*/
BOOL YStdioFile::Open (LPCTSTR pszFileName, UINT nOpenFlags)
{
	HANDLE hFile = OpenHelper (pszFileName, nOpenFlags);
	if ( hFile == INVALID_HANDLE_VALUE ) {
		return FALSE;
	}

	TCHAR	szMode[4];
	int		nMode = 0;

	// determine read/write mode depending on CFile mode
	if ( nOpenFlags & YFile::modeCreate ) {
		if ( nOpenFlags & YFile::modeNoTruncate ) {
			szMode[nMode++] = _T('a');
		}
		else {
			szMode[nMode++] = _T('w');
		}
	}
	else if ( nOpenFlags & YFile::modeWrite ) {
		szMode[nMode++] = _T('a');
	}
	else {
		szMode[nMode++] = _T('r');
	}

	// add '+' if necessary (when read/write modes mismatched)
	if ( (szMode[0] == _T('r')) && (nOpenFlags & YFile::modeReadWrite) || (szMode[0] != _T('r')) && !(nOpenFlags & YFile::modeWrite) ) {
		// current szMode mismatched, need to add '+' to fix
		szMode[nMode++] = _T('+');
	}

	// will be inverted if not necessary
	int nFlags = _O_RDONLY|_O_TEXT;
	if ( nOpenFlags & (YFile::modeWrite|YFile::modeReadWrite) ) {
		nFlags ^= _O_RDONLY;
	}

	if ( nOpenFlags & YFile::typeBinary ) {
		szMode[nMode++] = _T('b'), nFlags ^= _O_TEXT;
	}
	else {
		szMode[nMode++] = _T('t');
	}
	szMode[nMode++] = '\0';

	// open a C-runtime low-level file handle
	int		nHandle		= _open_osfhandle ((long) hFile, nFlags);
	FILE	*pStream	= NULL;

	// open a C-runtime stream from that handle
	if ( nHandle != -1 ) {
		pStream = _tfdopen (nHandle, szMode);
	}

	if ( !pStream ) {
		::CloseHandle (hFile);
		return FALSE;
	}
	Close ();
	m_hHandle	= hFile;
	m_pStream	= pStream;
	return TRUE;
}

BOOL YStdioFile::Close ()
{
	if ( YBaseFile::Close () ) {
		m_pStream = NULL;
		return TRUE;
	}
	return FALSE;
}

BOOL YStdioFile::Read (LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead)
{
	if ( !IsValid () ) {
		return FALSE;
	}
	size_t tRead = fread (lpBuffer, nNumberOfBytesToRead, 1, m_pStream);
	if ( lpNumberOfBytesRead ) {
		*lpNumberOfBytesRead = tRead;
	}
	if ( tRead != nNumberOfBytesToRead ) {
		return !ferror (m_pStream);
	}
	return TRUE;
}

BOOL YStdioFile::Write (LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten)
{
	if ( !IsValid () ) {
		return FALSE;
	}
	size_t tWrite = fwrite (lpBuffer, nNumberOfBytesToWrite, 1, m_pStream);
	if ( lpNumberOfBytesWritten ) {
		*lpNumberOfBytesWritten = tWrite;
	}
	return (tWrite == *lpNumberOfBytesWritten);
}

BOOL YStdioFile::WriteString (LPCTSTR pszString)
{
	ASSERTY(pszString);
	if ( !IsValid () ) {
		return FALSE;
	}

	return _fputts (pszString, m_pStream) != _TEOF;
}

LPTSTR YStdioFile::ReadString (LPTSTR pszString, UINT nMax)
{
	ASSERTY(pszString != NULL);
	ASSERTY(YlbIsValidAddress(pszString, nMax));

	if ( !IsValid () ) {
		return FALSE;
	}

	LPTSTR lpszResult = _fgetts (pszString, nMax, m_pStream);
	if ( (lpszResult == NULL) && !feof (m_pStream) ) {
		clearerr (m_pStream);
		return NULL;
	}
	return lpszResult;
}

BOOL YStdioFile::ReadString (YFixedString& rString)
{
	rString.Empty ();
	if ( !ReadString (rString.GetBuffer (), rString.GetBufferSize ()) ) {
		rString.Terminate (_T('\r'));
		return FALSE;
	}
	rString.Terminate (_T('\r'));
	return TRUE;
}

DWORD YStdioFile::Seek (LONG lDistanceToMove, DWORD dwMoveMethod)
{
	if ( !IsValid () ) {
		return INVALID_SET_FILE_POINTER;
	}

	int iMove = SEEK_SET;

	switch ( dwMoveMethod ) {
	case FILE_BEGIN:
		iMove = SEEK_SET;
		break;
	case FILE_END:
		iMove = SEEK_END;
		break;
	case FILE_CURRENT:
		iMove = SEEK_CUR;
		break;
	default:
		ASSERTY(FALSE);
		return INVALID_SET_FILE_POINTER;
	}

	if ( fseek (m_pStream, lDistanceToMove, iMove) != 0 ) {
		return INVALID_SET_FILE_POINTER;
	}
	return (DWORD) ftell (m_pStream);
}

DWORD YStdioFile::Seek (LONG lDistanceToMove, LPLONG lpDistanceToMoveHigh, DWORD dwMoveMethod)
{
	if ( lpDistanceToMoveHigh && *lpDistanceToMoveHigh ) {
		// not supported
		ASSERTY(FALSE);
		return INVALID_SET_FILE_POINTER;
	}
	return Seek (lDistanceToMove, dwMoveMethod);
}

DWORD YStdioFile::GetLength (LPDWORD lpdwSizeHigh) const
{
	if ( !IsValid () ) {
		return 0;
	}

	if ( lpdwSizeHigh ) {
		*lpdwSizeHigh = 0;
	}

	LONG lOldPos = ftell (m_pStream);
	if ( lOldPos != -1 ) {
		fseek (m_pStream, 0, SEEK_END);
		LONG lSize = ftell (m_pStream);
		fseek (m_pStream, lOldPos, SEEK_SET);
		return (DWORD) lSize;
	}
	return INVALID_SET_FILE_POINTER;
}

DWORD YStdioFile::GetPosition (LPDWORD lpdwPosHigh) const
{
	if ( !IsValid () ) {
		return INVALID_SET_FILE_POINTER;
	}

	if ( lpdwPosHigh ) {
		*lpdwPosHigh = 0;
	}
	return (DWORD) ftell (m_pStream);
}


#ifndef YLB_ENABLE_INLINE
#include <yFiles.inl>
#endif

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////