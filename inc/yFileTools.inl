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
 * FILENAME		:	yFileTools.inl
 * PURPOSE		:	Pseudo classes for file utility functions
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.2  2000/08/23 10:02:52  leo
 * Improved file/dir detection methods
 * Updated license
 *
 * Revision 1.1  2000/05/26  14:03:07  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yFileTools.h
 *============================================================================*/
// @mfunc Appends a backslash
// @parm LPTSTR | lpPath | A null-terminated string that contains the
//			path to be checked and eventually modified
// @comm Appends a backslash to a pathname if not already present.
// @xref <mf YFileNameHandler::StripBSL>, <c YFileNameHandler>
YLB_INLINE void YFileNameHandler::AppendBSL (LPTSTR lpPath)
{
	if ( lpPath[_tcslen (lpPath) - 1] != _T('\\') ) {
		_tcscat (lpPath, _T("\\"));
	}
}

// @mfunc Strips a backslash
// @parm LPTSTR | lpPath | A null-terminated string that contains the
//			path to be checked and eventually modified
// @comm Strips the backslash from a pathname if already present.
// @xref <mf YFileNameHandler::AppendBSL>, <c YFileNameHandler>
YLB_INLINE void YFileNameHandler::StripBSL (LPTSTR lpPath)
{
	if ( lpPath[_tcslen (lpPath) - 1] == _T('\\') ) {
		lpPath[_tcslen (lpPath) - 1] = 0;
	}
}

YLB_INLINE BOOL YFileNameHandler::IsAbsolutePath (LPCTSTR lpTestPath)
{
	
	return (_istalpha (lpTestPath[0]) && (lpTestPath[1] == _T(':'))) || ((lpTestPath[0] == _T('\\')) && (lpTestPath[1] == _T('\\')));
}


YLB_INLINE BOOL YFileManager::IsFile (LPCTSTR lpFile, ...)
{
	va_list			va;

	va_start (va, lpFile);
	BOOL bRet = YFileManager::IsFileVa (lpFile, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YFileManager::IsFile (FILETIME *lpFileTime, LPDWORD lpFileAttr, LPDWORD lpFileSizeHi, LPDWORD lpFileSizeLo, LPTSTR lpFileName, LPCTSTR lpFile, ...)
{
	va_list			va;

	va_start (va, lpFile);
	BOOL bRet = YFileManager::IsFileVa (lpFileTime, lpFileAttr, lpFileSizeHi, lpFileSizeLo, lpFileName, lpFile, va);
	va_end (va);
	return bRet;
}

YLB_INLINE UINT YFileManager::CountFiles (LPCTSTR lpFile, ...)
{
	va_list			va;

	va_start (va, lpFile);
	UINT uRet = YFileManager::CountFilesVa (lpFile, va);
	va_end (va);
	return uRet;
}

YLB_INLINE UINT YFileManager::CountFiles (FILETIME *lpFileTime, LPDWORD lpFileAttr, LPDWORD lpFileSizeHi, LPDWORD lpFileSizeLo, LPTSTR lpFileName, LPCTSTR lpFile, ...)
{
	va_list			va;

	va_start (va, lpFile);
	UINT uRet = YFileManager::CountFilesVa (lpFileTime, lpFileAttr, lpFileSizeHi, lpFileSizeLo, lpFileName, lpFile, va);
	va_end (va);
	return uRet;
}

YLB_INLINE BOOL YFileManager::IsDir (LPCTSTR lpDir, ...)
{
	va_list			va;

	va_start (va, lpDir);
	BOOL bRet = YFileManager::IsDirVa (lpDir, va);
	va_end (va);
	return bRet;
}

YLB_INLINE UINT YFileManager::CountDirs (LPCTSTR lpFile, ...)
{
	va_list			va;

	va_start (va, lpFile);
	UINT uRet = YFileManager::CountDirsVa (lpFile, va);
	va_end (va);
	return uRet;
}

YLB_INLINE BOOL YFileManager::IsDirEmpty (LPCTSTR lpDir, ...)
{
	va_list			va;

	va_start (va, lpDir);
	BOOL bRet = YFileManager::IsDirEmptyVa (lpDir, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YFileManager::IsDirWritable (LPCTSTR lpDir, ...)
{
	va_list			va;

	va_start (va, lpDir);
	BOOL bRet = YFileManager::IsDirWritableVa (lpDir, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YFileManager::IsDirCompressed (LPCTSTR lpDir, ...)
{
	va_list			va;

	va_start (va, lpDir);
	BOOL bRet = YFileManager::IsDirCompressedVa (lpDir, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YFileManager::CreateDirectoryTree (LPCTSTR lpDir, ...)
{
	va_list			va;

	va_start (va, lpDir);
	BOOL bRet = YFileManager::CreateDirectoryTreeVa (lpDir, va);
	va_end (va);
	return bRet;
}

YLB_INLINE UINT YFileManager::DeleteFiles (LPCTSTR lpFile, ...)
{
	va_list			va;

	va_start (va, lpFile);
	UINT uRet = YFileManager::DeleteFilesVa (FALSE, lpFile, va);
	va_end (va);
	return uRet;
}

YLB_INLINE UINT YFileManager::DeleteFiles (BOOL bHardKill, LPCTSTR lpFile, ...)
{
	va_list			va;

	va_start (va, lpFile);
	UINT uRet = YFileManager::DeleteFilesVa (bHardKill, lpFile, va);
	va_end (va);
	return uRet;
}

YLB_INLINE BOOL YFileManager::RemoveDir (LPCTSTR lpDir, ...)
{
	va_list			va;

	va_start (va, lpDir);
	BOOL bRet = YFileManager::RemoveDirVa (lpDir, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YFileManager::KillDir (LPCTSTR lpDir, ...)
{
	va_list			va;

	va_start (va, lpDir);
	BOOL bRet = YFileManager::KillDirVa (FALSE, lpDir, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YFileManager::KillDir (BOOL bHardKill, LPCTSTR lpDir, ...)
{
	va_list			va;

	va_start (va, lpDir);
	BOOL bRet = YFileManager::KillDirVa (bHardKill, lpDir, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YFileManager::CompressDir (LPCTSTR lpDir, ...)
{
	va_list			va;

	va_start (va, lpDir);
	BOOL bRet = YFileManager::CompressDirVa (lpDir, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YFileManager::UncompressDir (LPCTSTR lpDir, ...)
{
	va_list			va;

	va_start (va, lpDir);
	BOOL bRet = YFileManager::UncompressDirVa (lpDir, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YFileManager::CompressDirTree (LPCTSTR lpDir, ...)
{
	va_list			va;

	va_start (va, lpDir);
	BOOL bRet = YFileManager::CompressDirTreeVa (lpDir, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YFileManager::UncompressDirTree (LPCTSTR lpDir, ...)
{
	va_list			va;

	va_start (va, lpDir);
	BOOL bRet = YFileManager::UncompressDirTreeVa (lpDir, va);
	va_end (va);
	return bRet;
}

YLB_INLINE DWORD YFileManager::GetFilesSizes (LPCTSTR lpFile, ...)
{
	va_list			va;

	va_start (va, lpFile);
	BOOL bRet = YFileManager::GetFilesSizesVa (NULL, lpFile, va);
	va_end (va);
	return bRet;
}

YLB_INLINE DWORD YFileManager::GetFilesSizes (LPDWORD lpdwRetHi, LPCTSTR lpFile, ...)
{
	va_list			va;

	va_start (va, lpFile);
	BOOL bRet = YFileManager::GetFilesSizesVa (lpdwRetHi, lpFile, va);
	va_end (va);
	return bRet;
}

YLB_INLINE DWORD YFileManager::GetFilesSizesVa (LPCTSTR lpFile, va_list vaFile)
{
	return YFileManager::GetFilesSizesVa (NULL, lpFile, vaFile);
}

YLB_INLINE BOOL YFileManager::IsReadOnly (LPCTSTR lpFile, ...)
{
	va_list			va;

	va_start (va, lpFile);
	BOOL bRet = YFileManager::IsReadOnlyVa (lpFile, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YFileManager::SetReadOnly (LPCTSTR lpFile, ...)
{
	va_list			va;

	va_start (va, lpFile);
	BOOL bRet = YFileManager::SetReadOnlyVa (lpFile, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YFileManager::SetReadWrite (LPCTSTR lpFile, ...)
{
	va_list			va;

	va_start (va, lpFile);
	BOOL bRet = YFileManager::SetReadWriteVa (lpFile, va);
	va_end (va);
	return bRet;
}

YLB_INLINE DWORD YFileManager::GetFileSize (LPCTSTR lpFile, ...)
{
	va_list			va;
	DWORD			dwSize;

	va_start (va, lpFile);
	BOOL bRet = YFileManager::IsFileVa (NULL, NULL, NULL, &dwSize, NULL, lpFile, va);
	va_end (va);
	return (bRet) ? (dwSize) : (0);
}

YLB_INLINE DWORD YFileManager::GetFileSizeVa (LPCTSTR lpFile, va_list vaFile)
{
	DWORD			dwSize;

	return (
		YFileManager::IsFileVa (
			NULL, 
			NULL, 
			NULL, 
			&dwSize, 
			NULL, 
			lpFile, 
			vaFile
		)
	) ? (dwSize) : (0);
}

YLB_INLINE BOOL YFileManager::GetFileTime (FILETIME *lpFileTime, LPCTSTR lpFile, ...)
{
	va_list			va;

	va_start (va, lpFile);
	BOOL bRet = YFileManager::IsFileVa (lpFileTime, NULL, NULL, NULL, NULL, lpFile, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YFileManager::GetFileTimeVa (FILETIME *lpFileTime, LPCTSTR lpFile, va_list vaFile)
{
	return YFileManager::IsFileVa (
			lpFileTime, 
			NULL, 
			NULL, 
			NULL, 
			NULL, 
			lpFile, 
			vaFile
	);
}

YLB_INLINE BOOL YFileManager::SetFileTime (const FILETIME *lpFileTime, LPCTSTR lpFile, ...)
{
	va_list			va;

	va_start (va, lpFile);
	BOOL bRet = YFileManager::SetFileTimeVa (lpFileTime, lpFile, va);
	va_end (va);
	return bRet;
}

YLB_INLINE DWORD YFileManager::GetFileCRC (LPCTSTR lpFile, ...)
{
	YCrc32	crc;
	va_list	va;
	TCHAR	szPathName[MAX_PATH];

	va_start (va, lpFile);
	_vstprintf (szPathName, lpFile, va);
	va_end (va);
	return crc.GetFileCrc (szPathName);
}

YLB_INLINE DWORD YFileManager::GetFileCRCVa (LPCTSTR lpFile, va_list vaFile)
{
	YCrc32	crc;
	TCHAR	szPathName[MAX_PATH];

	_vstprintf (szPathName, lpFile, vaFile);
	return crc.GetFileCrc (szPathName);
}

YLB_INLINE BOOL YFileManager::Touch (LPCTSTR lpFile, ...)
{
	va_list	va;

	va_start (va, lpFile);
	BOOL bRet = YFileManager::TouchVa (lpFile, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YFileManager::AddFileAttributes (DWORD dwAttrMask, LPCTSTR lpFile, ...)
{
	va_list			va;

	va_start (va, lpFile);
	BOOL bRet = YFileManager::AddFileAttributesVa (dwAttrMask, lpFile, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YFileManager::ClearFileAttributes (DWORD dwAttrMask, LPCTSTR lpFile, ...)
{
	va_list			va;

	va_start (va, lpFile);
	BOOL bRet = YFileManager::ClearFileAttributesVa (dwAttrMask, lpFile, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YFileManager::CompressFile (LPCTSTR lpFile, ...)
{
	va_list	va;

	va_start (va, lpFile);
	BOOL bRet = YFileManager::CompressFileVa (lpFile, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YFileManager::UncompressFile (LPCTSTR lpFile, ...)
{
	va_list	va;

	va_start (va, lpFile);
	BOOL bRet = YFileManager::UncompressFileVa (lpFile, va);
	va_end (va);
	return bRet;
}

/*=============================================================================
 * THE DIRECTORY ENUMERATOR
 *============================================================================*/
YLB_INLINE YDirEnumerator::YDirEnumerator ()
{
	m_hFind		= INVALID_HANDLE_VALUE;
	memset (&m_wfd, 0, sizeof (m_wfd));
	*m_szPathComponent = *m_szFullName = 0;
}

YLB_INLINE YDirEnumerator::~YDirEnumerator ()
{
	End ();
}

YLB_INLINE void YDirEnumerator::Start (LPCTSTR pszPattern, ...)
{
	va_list	va;

	va_start (va, pszPattern);
	StartVa (pszPattern, va);
	va_end (va);
}

YLB_INLINE void YDirEnumerator::End ()
{
	if ( m_hFind != INVALID_HANDLE_VALUE ) {
		FindClose (m_hFind);
		m_hFind = INVALID_HANDLE_VALUE;
		memset (&m_wfd, 0, sizeof (m_wfd));
		*m_szPathComponent = *m_szFullName = 0;
	}
}

YLB_INLINE LPCTSTR YDirEnumerator::GetName () const
{
	return m_wfd.cFileName;
}

YLB_INLINE LPCTSTR YDirEnumerator::GetPath () const
{
	return m_szPathComponent;
}

YLB_INLINE LPCTSTR YDirEnumerator::GetFullName () const
{
	return m_szFullName;
}

YLB_INLINE LPCTSTR YDirEnumerator::GetAlternateName () const
{
	return m_wfd.cAlternateFileName;
}

YLB_INLINE DWORD YDirEnumerator::GetSize (LPDWORD pdwFileSizeHigh) const
{
	if ( pdwFileSizeHigh ) {
		*pdwFileSizeHigh = m_wfd.nFileSizeHigh;
	}
	return m_wfd.nFileSizeLow;
}

YLB_INLINE DWORD YDirEnumerator::GetAttributes () const
{
	return m_wfd.dwFileAttributes;
}

YLB_INLINE void YDirEnumerator::GetCreationTime (LPFILETIME pftTime) const
{
	if ( pftTime ) {
		pftTime->dwHighDateTime	= m_wfd.ftCreationTime.dwHighDateTime;
		pftTime->dwLowDateTime	= m_wfd.ftCreationTime.dwLowDateTime;
	}
}

YLB_INLINE void YDirEnumerator::GetModificationTime (LPFILETIME pftTime) const
{
	if ( pftTime ) {
		pftTime->dwHighDateTime	= m_wfd.ftLastWriteTime.dwHighDateTime;
		pftTime->dwLowDateTime	= m_wfd.ftLastWriteTime.dwLowDateTime;
	}
}

YLB_INLINE void YDirEnumerator::GetAccessTime (LPFILETIME pftTime) const
{
	if ( pftTime ) {
		pftTime->dwHighDateTime	= m_wfd.ftLastAccessTime.dwHighDateTime;
		pftTime->dwLowDateTime	= m_wfd.ftLastAccessTime.dwLowDateTime;
	}
}

YLB_INLINE BOOL YDirEnumerator::IsDir () const
{
	return (m_wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
}

YLB_INLINE BOOL YDirEnumerator::IsFile () const
{
	return (m_wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
}

YLB_INLINE BOOL YDirEnumerator::IsDotDir () const
{
	if ( m_wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) {
		if ( m_wfd.cFileName[0] == _T('.') ) {
			switch ( m_wfd.cFileName[1] ) {
			case 0:
				return TRUE;
			case _T('.'):
				return m_wfd.cFileName[2] == 0;
			}
		}
	}
	return FALSE;
}

YLB_INLINE BOOL YDirEnumerator::IsNoDotDir () const
{
	if ( m_wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) {
		if ( m_wfd.cFileName[0] == _T('.') ) {
			switch ( m_wfd.cFileName[1] ) {
			case 0:
				return FALSE;
			case _T('.'):
				return m_wfd.cFileName[2] != 0;
			}
		}
		return TRUE;
	}
	return FALSE;
}
