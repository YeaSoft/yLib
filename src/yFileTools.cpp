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
 * FILENAME		:	yFileTools.cpp
 * PURPOSE		:	Pseudo classes for file utility functions
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.2  2000/08/23 10:02:42  leo
 * Improved file/dir detection methods
 * Updated license
 *
 * Revision 1.1  2000/05/26  14:04:58  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yFileTools.h
 *============================================================================*/
#include "StdInc.hpp"
#include <winioctl.h>

/*=============================================================================
 * INTERNAL MAKROS
 *============================================================================*/
// This unusual construction is necessary because otherwise this library does not
// work inside a DLL... MicroDoom...
#undef isalpha
#define isalpha(a)			((((a) & 0xdf) >= _T('A')) && (((a) & 0xdf) <= _T('Z')))

#define isabspath(sz)		( (isalpha(sz[0]) && (sz[1] == _T(':')) && (sz[2] == _T('\\')) ) || ( (sz[0] == _T('\\')) && (sz[1] == _T('\\')) ))
#define isrootpath(sz)		( (isabspath(sz) && (_tcschr (sz + 2, _T('\\'))) && (*(_tcschr (sz + 2, _T('\\'))) == 0)) || ((sz[0] == _T('\\')) && (sz[1] == 0)) )
#define pathhasdrive(sz)	( (isalpha(sz[0]) && (sz[1] == _T(':')) ) || ((sz[0] == _T('\\')) && (sz[1] == _T('\\'))))

/*=============================================================================
 * INTERNAL STATICS
 *============================================================================*/
static BOOL						sfMakeTree				(LPCTSTR pszDirName);
static BOOL						sfSetCompressState		(LPCTSTR pszDirName, BOOL bDir, BOOL bCompress);
static BOOL						sfCompressTree			(LPCTSTR pszDirName, BOOL bCompress, BOOL bRecurse);

/*=============================================================================
 * FILE NAME HANDLER
 *============================================================================*/
BOOL YFileNameHandler::SplitPath (LPCTSTR lpString, LPTSTR lpPath, LPTSTR lpName)
{
	LPCTSTR lpPtr = _tcsrchr (lpString, _T('\\'));
	if ( lpPtr ) {
		if ( lpPath ) {
			_tcsncpy (lpPath, lpString, lpPtr - lpString + 1);
			lpPath[lpPtr - lpString + 1] = 0;
		}
		if ( lpName ) {
			_tcscpy (lpName, lpPtr + 1);
		}
		return TRUE;
	}
	else {
		if ( lpPath ) {
			*lpPath = 0;
		}
		if ( lpName ) {
			_tcscpy (lpName, lpString);
		}
		return FALSE;
	}
}

// @mfunc Splits a pathname in all its components
// @syntax <b>BOOL SplitPath (LPCTSTR<n> lpString<b>, LPTSTR<n> lpPath<b>, LPTSTR<n> lpName<b>);<n>
// @syntax <b>BOOL SplitPath (LPCTSTR<n> lpString<b>, LPTSTR<n> lpPath<b>, LPTSTR<n> lpName<b>, LPTSTR<n> lpExt<b>);<n>
// @parm LPCTSTR | lpString | Pathname string to split
// @parm LPTSTR | lpPath | Buffer that will receive the path component
//			if detected. Can be <NULL>.
// @parm LPTSTR | lpName | Buffer that will receive the filename component
//			if detected. Can also be <NULL>.
// @parm LPTSTR | lpExt | Buffer that will receive the extension component
//			of a filename if detected. Can also be <NULL>.
// @rdesc <TRUE> if the supplied string contains a filename with path information,
//			<FALSE> if no path information could be detected.
// @comm This function tries to split the supplied string in a filename, an extension
//			and a path component by reverse searching for a backslash and a period.
//			There is no guarantee that the returned results correspond to a real
//			filename  and it's path component. If the suppplied string contains only
//			a directory name, the last directory will be interpreted as the
//			filename. The retuned path component (if any) will contain a
//			terminating backslash. The first version of this function will return in
//			<p lpName> a complete filename (with extension).
// @xref <mf YFileNameHandler::SplitName>, <c YFileNameHandler>
BOOL YFileNameHandler::SplitPath (LPCTSTR lpString, LPTSTR lpPath, LPTSTR lpName, LPTSTR lpExt)
{
	LPCTSTR lpPtr1 = _tcsrchr (lpString, _T('\\'));
	if ( lpPtr1 ) {
		if ( lpPath ) {
			_tcsncpy (lpPath, lpString, lpPtr1 - lpString + 1);
			lpPath[lpPtr1 - lpString + 1] = 0;
		}
		++lpPtr1;
	}
	else {
		if ( lpPath ) {
			*lpPath = 0;
		}
		lpPtr1 = lpString;
	}
	LPCTSTR lpPtr2 = _tcsrchr (lpPtr1, _T('.'));
	if ( lpPtr2 ) {
		if ( lpName ) {
			_tcsncpy (lpName, lpPtr1, lpPtr2 - lpPtr1);
			lpName[lpPtr2 - lpPtr1] = 0;
		}
		if ( lpExt ) {
			_tcscpy (lpExt, lpPtr2 + 1);
		}
	}
	else {
		if ( lpName ) {
			_tcscpy (lpName, lpPtr1);
		}
		if ( lpExt ) {
			*lpExt = 0;
		}
	}
	return lpPtr1 != lpString;
}

// @mfunc Splits a filename in its components
// @parm LPCTSTR | lpString | Pathname string to split
// @parm LPTSTR | lpName | Buffer that will receive the path and name component
//			of a filename. Can be <NULL>.
// @parm LPTSTR | lpExt | Buffer that will receive the extension component
//			of a filename if detected. Can also be <NULL>.
// @rdesc <TRUE> if the supplied string contains a filename with an extension,
//			<FALSE> if no extension could be detected.
// @comm This function tries to split the supplied string in a filename and
//			an extension component by reverse searching for a period.
// @xref <mf YFileNameHandler::SplitPath>, <c YFileNameHandler>
BOOL YFileNameHandler::SplitName (LPCTSTR lpString, LPTSTR lpName, LPTSTR lpExt)
{
	LPTSTR lpPtr = _tcsrchr (lpString, _T('.'));
	if ( lpPtr ) {
		if ( lpName ) {
			_tcsncpy (lpName, lpString, lpPtr - lpString);
			lpName[lpPtr - lpString] = 0;
		}
		if ( lpExt ) {
			_tcscpy (lpExt, lpPtr + 1);
		}
		return TRUE;
	}
	else {
		if ( lpName ) {
			_tcscpy (lpName, lpString);
		}
		if ( lpExt ) {
			*lpExt = 0;
		}
		return FALSE;
	}
}

BOOL YFileNameHandler::WildCompareString (LPCTSTR lpS1, LPCTSTR lpS2, BOOL bCaseSensitive /* = FALSE */)
{
	unsigned int	i, s1len;
	TCHAR			c1, c2;
	s1len = _tcslen (lpS1);

	if ( bCaseSensitive ) {
		for ( i = 0; i < s1len; i++ ) {
			if ( (lpS1[i] == _T('*')) || (lpS2[i] == _T('*')) )
				return TRUE;
			if ( !((lpS1[i]==_T('?')) || (lpS2[i]==_T('?'))) ) {
				c1 = lpS1[i]; c2 = lpS2[i];
				if ( c1 != c2 ) return FALSE;
			}
			if ( lpS2[i] == 0 ) return FALSE;
		}
	}
	else {
		for ( i = 0; i < s1len; i++ ) {
			if ( (lpS1[i] == _T('*')) || (lpS2[i] == _T('*')) )
				return TRUE;
			if ( !((lpS1[i]==_T('?')) || (lpS2[i]==_T('?'))) ) {
				c1 = lpS1[i]; c2 = lpS2[i];
				if ( (c1 >= _T('a')) && (c1 <= _T('z')) ) c1 += _T('A') - _T('a');
				if ( (c2 >= _T('a')) && (c2 <= _T('z')) ) c2 += _T('A') - _T('a');
				if ( c1 != c2 ) return FALSE;
			}
			if ( lpS2[i] == 0 ) return FALSE;
		}
	}
	if ( lpS2[i] == 0 )		return TRUE;
	if ( lpS2[i] == _T('*') )	return TRUE;
	return FALSE;
}

BOOL YFileNameHandler::WildCompare (LPCTSTR lpMask, LPCTSTR lpName)
{
	TCHAR	szMask[512];
	TCHAR	szName[512];
	LPTSTR	lpMDot, lpFDot;

	_tcscpy (szMask, lpMask);
	lpMDot = _tcschr (szMask, '.');
	if ( lpMDot ) {
		*lpMDot = 0; ++lpMDot;
		_tcscpy (szName, lpName);
		lpFDot = _tcschr (szName, '.');
		if ( lpFDot ) {
			*lpFDot = 0; ++lpFDot;
			return WildCompareString (lpName, lpMask) && WildCompareString (lpFDot, lpMDot);
		}
		else
			return WildCompareString (lpName, lpMask) && WildCompareString (_T(""), lpMDot);
	}
	else {
		// simple wildcard (mask has no dot)
		return WildCompareString (lpName, lpMask);
	}
}

LPCTSTR YFileNameHandler::IntegratePath (LPCTSTR lpMaster, LPCTSTR lpAdd, LPTSTR lpBuffer)
{
	if ( IsAbsolutePath (lpAdd) ) {
		_tcscpy (lpBuffer, lpAdd);
	}
	else {
		_tcscpy (lpBuffer, lpMaster);
		AppendBSL (lpBuffer);
		_tcscat (lpBuffer, (*lpAdd == _T('\\')) ? (lpAdd + 1) : (lpAdd));
	}
	return lpBuffer;
}

/*=============================================================================
 * FILE MANAGER
 *============================================================================*/

// file / directory management methods
BOOL YFileManager::IsFileVa (LPCTSTR lpFile, va_list vaFile)
{
	TCHAR	szPathName[MAX_PATH];
	DWORD	dwAttributes;

	_ylb_formatv (szPathName, _countof (szPathName), lpFile, vaFile);
	dwAttributes = ::GetFileAttributes (szPathName);
	return (dwAttributes != FILE_ATTRIBUTE_INVALID) && ((dwAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0);
}

BOOL YFileManager::IsFileVa (FILETIME *lpFileTime, LPDWORD lpFileAttr, LPDWORD lpFileSizeHi, LPDWORD lpFileSizeLo, LPTSTR lpFileName, LPCTSTR lpFile, va_list vaFile)
{
	TCHAR			szPathName[MAX_PATH];
	WIN32_FIND_DATA	wfd;

	_ylb_formatv (szPathName, _countof (szPathName), lpFile, vaFile);
	wfd.dwFileAttributes = ::GetFileAttributes (szPathName);

	if (  (wfd.dwFileAttributes == FILE_ATTRIBUTE_INVALID) || (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
		// file not exists or directory
		return FALSE;
	}

	HANDLE	hFind = ::FindFirstFile (szPathName, &wfd);
	if ( hFind == INVALID_HANDLE_VALUE ) {
		// SNH
		return FALSE;
	}
	::FindClose (hFind);

	if ( (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0 ) {
		if ( lpFileName ) _tcscpy (lpFileName, wfd.cFileName);
		if ( lpFileTime ) memcpy (lpFileTime, &wfd.ftLastWriteTime, sizeof (FILETIME));
		if ( lpFileAttr ) *lpFileAttr = wfd.dwFileAttributes;
		if ( lpFileSizeHi ) *lpFileSizeHi = wfd.nFileSizeHigh;
		if ( lpFileSizeLo ) *lpFileSizeLo = wfd.nFileSizeLow;
		return TRUE;
	}
	return FALSE;
}

UINT YFileManager::CountFilesVa (LPCTSTR lpFile, va_list vaFile)
{
	TCHAR			szPathName[MAX_PATH];
	WIN32_FIND_DATA	wfd;
	UINT			nCount = 0;

	_ylb_formatv (szPathName, _countof (szPathName), lpFile, vaFile);

	HANDLE	hFind = ::FindFirstFile (szPathName, &wfd);
	if ( hFind == INVALID_HANDLE_VALUE ) {
		return 0;
	}

	do {
		if ( (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0 ) {
			++nCount;
		}
	} while ( ::FindNextFile (hFind, &wfd) );
	::FindClose (hFind);

	return nCount;
}

UINT YFileManager::CountFilesVa (FILETIME *lpFileTime, LPDWORD lpFileAttr, LPDWORD lpFileSizeHi, LPDWORD lpFileSizeLo, LPTSTR lpFileName, LPCTSTR lpFile, va_list vaFile)
{
	TCHAR			szPathName[MAX_PATH];
	WIN32_FIND_DATA	wfd;
	UINT			nCount = 0;

	_ylb_formatv (szPathName, _countof (szPathName), lpFile, vaFile);

	HANDLE	hFind = ::FindFirstFile (szPathName, &wfd);
	if ( hFind == INVALID_HANDLE_VALUE ) {
		return 0;
	}

	do {
		if ( (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0 ) {
			if ( !nCount ) {
				// first file found
				if ( lpFileName )	_tcscpy (lpFileName, wfd.cFileName);
				if ( lpFileTime )	memcpy (lpFileTime, &wfd.ftLastWriteTime, sizeof (FILETIME));
				if ( lpFileAttr )	*lpFileAttr = wfd.dwFileAttributes;
				if ( lpFileSizeHi )	*lpFileSizeHi = wfd.nFileSizeHigh;
				if ( lpFileSizeLo )	*lpFileSizeLo = wfd.nFileSizeLow;
			}
			++nCount;
		}
	} while ( ::FindNextFile (hFind, &wfd) );
	::FindClose (hFind);

	return nCount;
}

BOOL YFileManager::IsDirVa (LPCTSTR lpFile, va_list vaFile)
{
	TCHAR	szPathName[MAX_PATH];
	DWORD	dwAttributes;

	_ylb_formatv (szPathName, _countof (szPathName), lpFile, vaFile);
	dwAttributes = ::GetFileAttributes (szPathName);
	return (dwAttributes != FILE_ATTRIBUTE_INVALID) && ((dwAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0);
}

#if (0)
BOOL YFileManager::IsDirVa (LPCTSTR lpDir, va_list vaDir)
{
	TCHAR			szPathName[MAX_PATH];

	_ylb_formatv (szPathName, _countof (szPathName), lpDir, vaDir);
	YFileNameHandler::StripBSL (szPathName);

	HANDLE hDirectory = ::CreateFile (
		szPathName,
		GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS,
		NULL
	);
	if ( hDirectory == INVALID_HANDLE_VALUE ) {
		return FALSE;
	}
	::CloseHandle (hDirectory);
	return TRUE;


//	WIN32_FIND_DATA	wfd;
//	_tcscat (szBuffer, _T("\\*.*"));

//	HANDLE	hFind = ::FindFirstFile (szBuffer, &wfd);
//	if ( hFind == INVALID_HANDLE_VALUE ) {
//		return FALSE;
//	}
//	::FindClose (hFind);
//	return TRUE;
}
#endif

// 
// This does not enumerate shares or computers
//
UINT YFileManager::CountDirsVa (LPCTSTR lpFile, va_list vaFile)
{
	TCHAR			szPathName[MAX_PATH];
	WIN32_FIND_DATA	wfd;
	UINT			nCount = 0;

	_ylb_formatv (szPathName, _countof (szPathName), lpFile, vaFile);
	YFileNameHandler::StripBSL (szPathName);

	HANDLE	hFind = ::FindFirstFile (szPathName, &wfd);
	if ( hFind == INVALID_HANDLE_VALUE ) {
		return 0;
	}

	do {
		if ( wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) {
			++nCount;
		}
	} while ( ::FindNextFile (hFind, &wfd) );
	::FindClose (hFind);

	return nCount;
}

BOOL YFileManager::IsDirWritableVa (LPCTSTR lpDir, va_list vaDir)
{
	TCHAR			szPathName[MAX_PATH];

	_ylb_formatv (szPathName, _countof (szPathName) - 13, lpDir, vaDir);
	YFileNameHandler::StripBSL (szPathName);
	_tcscat (szPathName, _T("\\~dirtst~.tmp"));
	HANDLE	hFile = ::CreateFile (
		szPathName,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if ( hFile == INVALID_HANDLE_VALUE ) {
		return FALSE;
	}
	::CloseHandle (hFile);
	::DeleteFile (szPathName);
	return TRUE;
}

BOOL YFileManager::IsDirCompressedVa (LPCTSTR lpDir, va_list vaDir)
{
	TCHAR		szPathName[MAX_PATH];
	HANDLE		hDir;
	USHORT		uCompressFlag;
	DWORD		dwRet;
	BOOL		bRet;

	_ylb_formatv (szPathName, _countof (szPathName), lpDir, vaDir);

	dwRet = ::GetFileAttributes (szPathName);
	if ( (dwRet == FILE_ATTRIBUTE_INVALID) || ((dwRet & FILE_ATTRIBUTE_DIRECTORY) == 0) ) {
		return FALSE;
	}

	hDir = CreateFile (
		szPathName,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS,
		NULL
	);
	if ( hDir == INVALID_HANDLE_VALUE ) {
		// SNH
		return FALSE;
	}

	if ( DeviceIoControl (hDir, FSCTL_GET_COMPRESSION, NULL, 0, &uCompressFlag, sizeof (USHORT), &dwRet, NULL) ) {
		bRet = (uCompressFlag != COMPRESSION_FORMAT_NONE);
	}
	else {
		bRet = FALSE;
	}

	CloseHandle (hDir);
	return bRet;
}

BOOL YFileManager::IsDirEmptyVa (LPCTSTR lpDir, va_list vaDir)
{
	WIN32_FIND_DATA	wfd;
	TCHAR			szBuffer[MAX_PATH];

	_ylb_formatv (szBuffer, _countof (szBuffer), lpDir, vaDir);
	YFileNameHandler::StripBSL (szBuffer);
	_tcscat (szBuffer, _T("\\*.*"));

	HANDLE	hFind = ::FindFirstFile (szBuffer, &wfd);
	if ( hFind == INVALID_HANDLE_VALUE ) {
		// directory does not exist
		return TRUE;
	}

	BOOL bEmpty = TRUE;
	do {
		if ( _tcscmp (wfd.cFileName, _T(".")) && _tcscmp (wfd.cFileName, _T("..")) ) {
			// something different as . or ..
			bEmpty = FALSE;
			break;
		}
	} while ( ::FindNextFile (hFind, &wfd) );


	::FindClose (hFind);
	return bEmpty;
}

BOOL YFileManager::CreateDirectoryTreeVa (LPCTSTR lpDir, va_list vaDir)
{
	if ( IsDirVa (lpDir, vaDir) ) {
		return TRUE;
	}

	TCHAR			szBuffer[MAX_PATH];

	_ylb_formatv (szBuffer, _countof (szBuffer), lpDir, vaDir);
	YFileNameHandler::StripBSL (szBuffer);

	return sfMakeTree (szBuffer);
}

BOOL YFileManager::CreatePartialDirectoryTree (LPCTSTR lpBase, LPCTSTR lpDir)
{
	DWORD	dwRet;
	TCHAR	szPath[MAX_PATH];

	_stprintf (szPath, _T("%s\\%s"), lpBase, lpDir);
	if ( (dwRet = ::GetFileAttributes (szPath)) != FILE_ATTRIBUTE_INVALID ) {
		// file or subdir exists
		// return TRUE if subdir, FALSE if file
		return (dwRet & FILE_ATTRIBUTE_DIRECTORY) != 0;
	}

	if ( _tcsrchr (lpDir, _T('\\')) ) {
		_tcscpy (szPath, lpDir);
		LPTSTR lpPtr = _tcsrchr (szPath, _T('\\'));
		*lpPtr = 0;
		if ( !CreatePartialDirectoryTree (lpBase, szPath) ) {
			return FALSE;
		}
		_stprintf (szPath, _T("%s\\%s"), lpBase, lpDir);
	}
	return ::CreateDirectory (szPath, NULL);
}

UINT YFileManager::DeleteFilesVa (BOOL bHardKill, LPCTSTR lpFile, va_list vaFile)
{
	TCHAR			szFileName[MAX_PATH];
	TCHAR			szPath[MAX_PATH * 2];
	HANDLE			hFind;
	WIN32_FIND_DATA	wfd;
	UINT			nCount = 0;

	_ylb_formatv (szFileName, _countof (szFileName), lpFile, vaFile);

	_tcscpy (szPath, szFileName);
	LPTSTR lpPtr = _tcsrchr (szPath, _T('\\'));
	if ( !lpPtr ) {
		return 0;
	}
	*lpPtr = 0;

	hFind = ::FindFirstFile (szFileName, &wfd);
	if ( hFind == INVALID_HANDLE_VALUE ) {
		return 0;
	}
	do {
		_stprintf (szFileName, _T("%s\\%s"), szPath, wfd.cFileName);
		DWORD dwAttr = ::GetFileAttributes (szFileName);
		if ( bHardKill ) {
			::SetFileAttributes (szFileName, dwAttr & ~(FILE_ATTRIBUTE_READONLY|FILE_ATTRIBUTE_SYSTEM));
		}
		if ( ::DeleteFile (szFileName) ) {
			++nCount;
		}
		else if ( bHardKill ) {
			::SetFileAttributes (szFileName, dwAttr);
		}
	} while ( ::FindNextFile (hFind, &wfd) );
	::FindClose (hFind);
	return nCount;
}

BOOL YFileManager::RemoveDirVa (LPCTSTR lpDir, va_list vaDir)
{
	TCHAR			szBuffer[MAX_PATH];

	_ylb_formatv (szBuffer, _countof (szBuffer), lpDir, vaDir);
	YFileNameHandler::StripBSL (szBuffer);
	return ::RemoveDirectory (szBuffer);
}

BOOL YFileManager::KillDirVa (BOOL bHardKill, LPCTSTR lpDir, va_list vaDir)
{
	TCHAR			szBuffer[MAX_PATH];

	_ylb_formatv (szBuffer, _countof (szBuffer) - 4, lpDir, vaDir);
	YFileNameHandler::StripBSL (szBuffer);
	_tcscat (szBuffer, _T("\\*.*"));
	DeleteFiles (bHardKill, szBuffer);
	_ylb_formatv (szBuffer, _countof (szBuffer), lpDir, vaDir);
	YFileNameHandler::StripBSL (szBuffer);

	DWORD dwAttr = ::GetFileAttributes (szBuffer);
	if ( bHardKill ) {
		::SetFileAttributes (szBuffer, dwAttr & ~(FILE_ATTRIBUTE_READONLY|FILE_ATTRIBUTE_SYSTEM));
	}
	BOOL bRet = ::RemoveDirectory (szBuffer);
	if ( !bRet & bHardKill ) {
		::SetFileAttributes (szBuffer, dwAttr);
	}
	return bRet;
}

BOOL YFileManager::CompressDirVa (LPCTSTR lpDir, va_list vaDir)
{
	TCHAR			szBuffer[MAX_PATH];

	_ylb_formatv (szBuffer, _countof (szBuffer), lpDir, vaDir);
	return sfCompressTree (szBuffer, TRUE, FALSE);
}

BOOL YFileManager::UncompressDirVa (LPCTSTR lpDir, va_list vaDir)
{
	TCHAR			szBuffer[MAX_PATH];

	_ylb_formatv (szBuffer, _countof (szBuffer), lpDir, vaDir);
	return sfCompressTree (szBuffer, FALSE, FALSE);
}

BOOL YFileManager::CompressDirTreeVa (LPCTSTR lpDir, va_list vaDir)
{
	TCHAR			szBuffer[MAX_PATH];

	_ylb_formatv (szBuffer, _countof (szBuffer), lpDir, vaDir);
	return sfCompressTree (szBuffer, TRUE, TRUE);
}

BOOL YFileManager::UncompressDirTreeVa (LPCTSTR lpDir, va_list vaDir)
{
	TCHAR			szBuffer[MAX_PATH];

	_ylb_formatv (szBuffer, _countof (szBuffer), lpDir, vaDir);
	return sfCompressTree (szBuffer, FALSE, TRUE);
}

DWORD YFileManager::GetFilesSizesVa (LPDWORD lpdwRetHi, LPCTSTR lpFile, va_list vaFile)
{
	TCHAR			szPathName[MAX_PATH];
	WIN32_FIND_DATA	wfd;

	_ylb_formatv (szPathName, _countof (szPathName), lpFile, vaFile);

	HANDLE	hFind = FindFirstFile (szPathName, &wfd);
	if ( hFind == INVALID_HANDLE_VALUE ) {
		if ( lpdwRetHi ) {
			*lpdwRetHi = 0;
		}
		return 0;
	}
	if ( lpdwRetHi ) {
		ULONG64 dwRet = 0;
		do {
			if ( (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0 ) {
				dwRet += ((ULONG64)(((DWORD)(wfd.nFileSizeLow)) | ((ULONG64)((DWORD)(wfd.nFileSizeHigh))) << 32));
			}
		} while ( FindNextFile (hFind, &wfd) );
		FindClose (hFind);
		*lpdwRetHi = (DWORD) (dwRet >> 32);
		return (DWORD) (dwRet & 0x00000000ffffffffUI64);

	}
	else {
		DWORD dwRet = 0;
		do {
			if ( (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0 ) {
				dwRet += wfd.nFileSizeLow;
			}
		} while ( FindNextFile (hFind, &wfd) );
		FindClose (hFind);
		return dwRet;
	}
}

BOOL YFileManager::IsReadOnlyVa (LPCTSTR lpFile, va_list vaFile)
{
	TCHAR			szPathName[MAX_PATH];
	DWORD			dwAttr;

	_ylb_formatv (szPathName, _countof (szPathName), lpFile, vaFile);
	if ( (dwAttr = ::GetFileAttributes (szPathName)) == FILE_ATTRIBUTE_INVALID ) {
		return FALSE;
	}
	else {
		return (dwAttr & FILE_ATTRIBUTE_READONLY) != 0;
	}
}

BOOL YFileManager::SetReadOnlyVa (LPCTSTR lpFile, va_list vaFile)
{
	TCHAR	szPathName[MAX_PATH];

	_ylb_formatv (szPathName, _countof (szPathName), lpFile, vaFile);

	DWORD dwAttr = ::GetFileAttributes (szPathName);
	if ( dwAttr == FILE_ATTRIBUTE_INVALID ) {
		return FALSE;
	}
	dwAttr |= FILE_ATTRIBUTE_READONLY;
	return ::SetFileAttributes (szPathName, dwAttr);
}

BOOL YFileManager::SetReadWriteVa (LPCTSTR lpFile, va_list vaFile)
{
	TCHAR	szPathName[MAX_PATH];

	_ylb_formatv (szPathName, _countof (szPathName), lpFile, vaFile);

	DWORD dwAttr = ::GetFileAttributes (szPathName);
	if ( dwAttr == FILE_ATTRIBUTE_INVALID ) {
		return FALSE;
	}
	dwAttr &= ~((DWORD) FILE_ATTRIBUTE_READONLY);
	return ::SetFileAttributes (szPathName, dwAttr);
}

BOOL YFileManager::SetFileTimeVa (const FILETIME *lpFileTime, LPCTSTR lpFile, va_list vaFile)
{
	TCHAR	szPathName[MAX_PATH];
	HANDLE	hFile;

	_ylb_formatv (szPathName, _countof (szPathName), lpFile, vaFile);

	hFile = CreateFile (
		szPathName,
		GENERIC_WRITE,
		0,
        NULL,
		OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if ( hFile == INVALID_HANDLE_VALUE ) {
		return FALSE;
	}
	BOOL bRet = ::SetFileTime (hFile, NULL, NULL, lpFileTime);
	CloseHandle (hFile);
	return bRet;
}

BOOL YFileManager::TouchVa (LPCTSTR lpFile, va_list vaFile)
{
	SYSTEMTIME	st;
	FILETIME	ft;

	GetLocalTime (&st);
	SystemTimeToFileTime (&st, &ft);
	return SetFileTimeVa (&ft, lpFile, vaFile);
}

BOOL YFileManager::AddFileAttributesVa (DWORD dwAttrMask, LPCTSTR lpFile, va_list vaFile)
{
	TCHAR	szPathName[MAX_PATH];

	_ylb_formatv (szPathName, _countof (szPathName), lpFile, vaFile);

	DWORD dwAttr = ::GetFileAttributes (szPathName);
	if ( dwAttr == (DWORD) -1 ) {
		return FALSE;
	}
	dwAttr |= dwAttrMask;
	return SetFileAttributes (szPathName, dwAttr);
}

BOOL YFileManager::ClearFileAttributesVa (DWORD dwAttrMask, LPCTSTR lpFile, va_list vaFile)
{
	TCHAR	szPathName[MAX_PATH];

	_ylb_formatv (szPathName, _countof (szPathName), lpFile, vaFile);

	DWORD dwAttr = ::GetFileAttributes (szPathName);
	if ( dwAttr == (DWORD) -1 ) {
		return FALSE;
	}
	dwAttr &= ~((DWORD) dwAttrMask);
	return ::SetFileAttributes (szPathName, dwAttr);
}

BOOL YFileManager::CompressFileVa (LPCTSTR lpFile, va_list vaFile)
{
	TCHAR	szPathName[MAX_PATH];

	_ylb_formatv (szPathName, _countof (szPathName), lpFile, vaFile);
	return sfSetCompressState (szPathName, FALSE, TRUE);
}

BOOL YFileManager::UncompressFileVa (LPCTSTR lpFile, va_list vaFile)
{
	TCHAR	szPathName[MAX_PATH];

	_ylb_formatv (szPathName, _countof (szPathName), lpFile, vaFile);
	return sfSetCompressState (szPathName, FALSE, FALSE);
}

/*=============================================================================
 * THE DIRECTORY ENUMERATOR
 *============================================================================*/
void YDirEnumerator::StartVa (LPCTSTR pszPattern, va_list vaPattern)
{
	End ();
	_ylb_formatv (m_szPathComponent, _countof (m_szPathComponent), pszPattern, vaPattern);
}

BOOL YDirEnumerator::GetNext ()
{
	if ( m_hFind == INVALID_HANDLE_VALUE ) {
		if ( !*m_szPathComponent ) {
			// not inited!
			return FALSE;
		}
		if ( (m_hFind = ::FindFirstFile (m_szPathComponent, &m_wfd)) == INVALID_HANDLE_VALUE ) {
			// nothing found!
			return FALSE;
		}
		LPTSTR lpPtr = _tcsrchr (m_szPathComponent, _T('\\'));
		if ( lpPtr ) {
			++lpPtr;
			*lpPtr = 0;
		}
		else {
			*m_szPathComponent = 0;
		}
		_stprintf (m_szFullName, _T("%s%s"), m_szPathComponent, m_wfd.cFileName);
		return TRUE;
	}
	else {
		if ( ::FindNextFile (m_hFind, &m_wfd) ) {
			_stprintf (m_szFullName, _T("%s%s"), m_szPathComponent, m_wfd.cFileName);
			return TRUE;
		}
		else {
			*m_szFullName = 0;
			memset (&m_wfd, 0, sizeof (m_wfd));
			return FALSE;
		}
	}
}


/*=============================================================================
 * INTERNAL STATICS IMPLEMENTATION
 *============================================================================*/
static BOOL sfMakeTree (LPCTSTR pszDirName)
{
	LPTSTR		lpPtr;
	DWORD		dwRet;
	
	if ( (dwRet = ::GetFileAttributes (pszDirName)) != FILE_ATTRIBUTE_INVALID ) {
		// file or subdir exists
		// return TRUE if subdir, FALSE if file
		return (dwRet & FILE_ATTRIBUTE_DIRECTORY) != 0;
	}

	// dir does not exist
	if ( (lpPtr = _tcsrchr (pszDirName, _T('\\'))) != 0 ) {
		// get parent dir
		*lpPtr = 0;
		if ( (pszDirName[0]) && ((pszDirName[1] != ':') || (pszDirName[2])) ) {
			// not root of current drive
			// not root of absolute drive
			if ( !sfMakeTree (pszDirName) ) {
				// parent dir does not exist
				// and is not creatable, so fail
				return FALSE;
			}
		}
		*lpPtr = _T('\\');
	}

	return ::CreateDirectory (pszDirName, NULL);
}

static BOOL sfSetCompressState (LPCTSTR pszDirName, BOOL bDir, BOOL bCompress)
{
	HANDLE	hDir;
	USHORT	uCompressFlag;
	DWORD	dwRet;
	BOOL	bRet;
	
	hDir = CreateFile (
		pszDirName,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		(bDir) ? (FILE_FLAG_BACKUP_SEMANTICS) : (0),
		NULL
	);
	if ( hDir == INVALID_HANDLE_VALUE ) {
		return FALSE;
	}

	if ( DeviceIoControl (hDir, FSCTL_GET_COMPRESSION, NULL, 0, &uCompressFlag, sizeof (USHORT), &dwRet, NULL) ) {
		if ( bCompress && (uCompressFlag == COMPRESSION_FORMAT_NONE) ) {
			uCompressFlag = COMPRESSION_FORMAT_DEFAULT;
			bRet = DeviceIoControl (hDir, FSCTL_SET_COMPRESSION, &uCompressFlag, sizeof (USHORT), NULL, 0, &dwRet, NULL);
		}
		else if ( !bCompress && (uCompressFlag != COMPRESSION_FORMAT_NONE) ) {
			uCompressFlag = COMPRESSION_FORMAT_NONE;
			bRet = DeviceIoControl (hDir, FSCTL_SET_COMPRESSION, &uCompressFlag, sizeof (USHORT), NULL, 0, &dwRet, NULL);
		}
		else {
			bRet = TRUE;
		}
	}
	else {
		bRet = FALSE;
	}

	CloseHandle (hDir);
	return bRet;
}

static BOOL sfCompressTree (LPCTSTR pszDirName, BOOL bCompress, BOOL bRecurse)
{
	HANDLE			hFind;
	WIN32_FIND_DATA	wFD;
	BOOL			bRet;
	TCHAR			szBuffer[MAX_PATH];

	_tcscpy (szBuffer, pszDirName);
	YFileNameHandler::StripBSL (szBuffer);

	// set the compress flag on the directory
	bRet = sfSetCompressState (szBuffer, TRUE, bCompress);

	_tcscat (szBuffer, _T("\\*.*"));
	
	if ( (hFind = FindFirstFile (szBuffer, &wFD)) == INVALID_HANDLE_VALUE ) {
		return bRet;
	}

	do {
		if ( wFD.cFileName[0] != _T('.') ) {
			_tcscpy (_tcsrchr (szBuffer, _T('\\')) + 1, wFD.cFileName);
			if ( (wFD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && bRecurse ) {
				if ( !sfCompressTree (szBuffer, bCompress, TRUE) ) {
					FindClose (hFind);
					return FALSE;
				}
			}
			else {
				bRet |= sfSetCompressState (szBuffer, FALSE, bCompress);
			}
		}
	}
	while (FindNextFile (hFind, &wFD));
	FindClose (hFind);
	return bRet;
}

#ifndef YLB_ENABLE_INLINE
#include <yFileTools.inl>
#endif

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////