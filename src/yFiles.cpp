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
 * FILENAME		:	yFiles.cpp
 * PURPOSE		:	Implementation of the generic file classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.5  2001/05/06 18:29:59  leopoldo
 * Improved YStdioFile::ReadString
 *
 * Revision 1.4  2001/01/17 17:58:49  leopoldo
 * YStdioFile::WriteString now works with a variable parameter list
 *
 * Revision 1.3  2000/08/24 16:52:45  leo
 * Fixed the close method and added autoclose to the destructor
 *
 * Revision 1.2  2000/08/23  11:55:42  leo
 * Added more file open modes
 * Updated license
 *
 * Revision 1.1  2000/05/26  14:04:57  leo
 * Initial revision
 *
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

	// map caching mode
	DWORD	dwCacheMode = 0;
	switch ( nOpenFlags & (YFile::cacheDefault|YFile::cacheNoBuffering|YFile::cacheWriteThrough|YFile::cacheSequentialOptimized|YFile::cacheRandomOptimized) ) {
	default:
		// invalid caching mode?
		ASSERTY(FALSE);
	case YFile::cacheDefault:
		dwCacheMode = 0;
		break;
	case YFile::cacheNoBuffering:
		dwCacheMode = FILE_FLAG_NO_BUFFERING;
		break;
	case YFile::cacheWriteThrough:
		dwCacheMode = FILE_FLAG_WRITE_THROUGH;
		break;
	case YFile::cacheSequentialOptimized:
		dwCacheMode = FILE_FLAG_SEQUENTIAL_SCAN;
		break;
	case YFile::cacheRandomOptimized:
		dwCacheMode = FILE_FLAG_RANDOM_ACCESS;
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

	// map other mode flags
	DWORD dwOtherModes = 0;
	if ( nOpenFlags & YFile::modeDeleteOnClose ) {
		dwOtherModes |= FILE_FLAG_DELETE_ON_CLOSE;
	}
	if ( nOpenFlags & YFile::modeBackup ) {
		dwOtherModes |= FILE_FLAG_BACKUP_SEMANTICS;
	}
	if ( nOpenFlags & YFile::modePosix ) {
		dwOtherModes |= FILE_FLAG_POSIX_SEMANTICS;
	}

	// attempt file creation
	return ::CreateFile (
		pszFileName,
		dwAccess,
		dwShareMode,
		&ysa,
		dwCreateFlag,
		FILE_ATTRIBUTE_NORMAL | dwCacheMode | dwOtherModes,
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
	BOOL bRet = TRUE;

	if ( m_pStream ) {
		bRet = fclose (m_pStream) == 0;
	}
	m_pStream	= NULL;
	m_hHandle	= NULL;
	return bRet;
}

BOOL YStdioFile::Read (LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead)
{
	if ( !IsValid () ) {
		return FALSE;
	}
	size_t tRead = fread (lpBuffer, 1, nNumberOfBytesToRead, m_pStream);
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
	size_t tWrite = fwrite (lpBuffer, 1, nNumberOfBytesToWrite, m_pStream);
	if ( lpNumberOfBytesWritten ) {
		*lpNumberOfBytesWritten = tWrite;
	}
	return (tWrite == *lpNumberOfBytesWritten);
}

BOOL YStdioFile::WriteStringVa (LPCTSTR pszString, va_list va)
{
	ASSERTY(pszString);
	if ( !IsValid () ) {
		return FALSE;
	}
	return _vftprintf (m_pStream, pszString, va);
}

LPTSTR YStdioFile::ReadString (LPTSTR pszString, UINT nMax, BOOL bAutoTruncate /* = TRUE */)
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
	if ( bAutoTruncate ) {
		LPTSTR lpEnd = _tcspbrk (pszString, _T("\r\n"));
		if ( lpEnd ) {
			*lpEnd = 0;
		}
	}
	return lpszResult;
}

BOOL YStdioFile::ReadString (YFixedString& rString, BOOL bAutoTruncate /* = TRUE */)
{
	rString.Empty ();
	if ( !ReadString (rString.GetBuffer (), rString.GetBufferSize (), bAutoTruncate) ) {
		return FALSE;
	}
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