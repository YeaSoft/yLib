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
 * FILENAME		:	yFileTools.h
 * PURPOSE		:	Pseudo classes for file utility functions
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.2  2000/08/23 10:02:47  leo
 * Improved file/dir detection methods
 * Updated license
 *
 * Revision 1.1  2000/05/26  14:03:06  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yFileTools.h
 *============================================================================*/
#ifndef __yFileTools_h__
#define __yFileTools_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yLibBase_h__
#include <yLibBase.h>
#endif
#ifndef __yCrc32_h__
#include <yCrc32.h>
#endif

/*=============================================================================
 * HELPER CLASSES
 *============================================================================*/
// @class	Filename handler tools pseudoclass
// @comm	This pseudoclass provides functions that permit to handle
//			file and directory names.
//
class YFileNameHandler
{
public:
	// @cmember Appends a backslash to a pathname if not already present
	static void				AppendBSL					(LPTSTR lpPath);
	// @cmember Strips the backslash from a pathname if already present
	static void				StripBSL					(LPTSTR lpPath);
	// @cmember Splits a pathname in it's components
	static BOOL				SplitPath					(LPCTSTR lpString, LPTSTR lpPath, LPTSTR lpName);
	// @cmember Splits a pathname in it's components
	static BOOL				SplitPath					(LPCTSTR lpString, LPTSTR lpPath, LPTSTR lpName, LPTSTR lpExt);
	// @cmember Splits a filename in it's components
	static BOOL				SplitName					(LPCTSTR lpString, LPTSTR lpName, LPTSTR lpExt);
	// @cmember Compares two strings using wildcards
	static BOOL				WildCompareString			(LPCTSTR lpS1, LPCTSTR lpS2, BOOL bCaseSensitive = FALSE);
	// @cmember Compares a filename with a mask using wildcards
	static BOOL				WildCompare					(LPCTSTR lpMask, LPCTSTR lpName);
	// @cmember Checks if a path is absolute or not
	static BOOL				IsAbsolutePath				(LPCTSTR lpTestPath);
	// @cmember Builds a full path based on a master path
	static LPCTSTR			IntegratePath				(LPCTSTR lpMaster, LPCTSTR lpAdd, LPTSTR lpBuffer);
};
//
// @xref
//		<j Tools Pseudoclasses>

#ifndef FILE_ATTRIBUTE_INVALID
#define FILE_ATTRIBUTE_INVALID			0xffffffff
#endif

// @class	Filesystem related file handling pseudoclasses
// @comm	This pseudoclass provides functions that permit to manage
//			with files and directories.
//
class YFileManager
{
public:
	// @cmember Checks a file for existance
	static BOOL				IsFile					(LPCTSTR lpFile, ...);
	// @cmember Checks a file for existance
	static BOOL				IsFileVa				(LPCTSTR lpFile, va_list vaFile);
	// @cmember Checks a file for existance and retuns some related data
	static BOOL				IsFile					(FILETIME *lpFileTime, LPDWORD lpFileAttr, LPDWORD lpFileSizeHi, LPDWORD lpFileSizeLo, LPTSTR lpFileName, LPCTSTR lpFile, ...);
	// @cmember Checks a file for existance and retuns some related data
	static BOOL				IsFileVa				(FILETIME *lpFileTime, LPDWORD lpFileAttr, LPDWORD lpFileSizeHi, LPDWORD lpFileSizeLo, LPTSTR lpFileName, LPCTSTR lpFile, va_list vaFile);
	// @cmember Counts the files that match a filename pattern
	static UINT				CountFiles				(LPCTSTR lpFile, ...);
	// @cmember Counts the files that match a filename pattern
	static UINT				CountFilesVa			(LPCTSTR lpFile, va_list vaFile);
	// @cmember Counts the files that match a filename pattern and retuns some data about the first file
	static UINT				CountFiles				(FILETIME *lpFileTime, LPDWORD lpFileAttr, LPDWORD lpFileSizeHi, LPDWORD lpFileSizeLo, LPTSTR lpFileName, LPCTSTR lpFile, ...);
	// @cmember Counts the files that match a filename pattern and retuns some data about the first file
	static UINT				CountFilesVa			(FILETIME *lpFileTime, LPDWORD lpFileAttr, LPDWORD lpFileSizeHi, LPDWORD lpFileSizeLo, LPTSTR lpFileName, LPCTSTR lpFile, va_list vaFile);
	// @cmember Checks a directory for existance
	static BOOL				IsDir					(LPCTSTR lpDir, ...);
	// @cmember Checks a directory for existance
	static BOOL				IsDirVa					(LPCTSTR lpDir, va_list vaDir);
	// @cmember Counts the directories that match a name pattern
	static UINT				CountDirs				(LPCTSTR lpFile, ...);
	// @cmember Counts the directories that match a name pattern
	static UINT				CountDirsVa				(LPCTSTR lpFile, va_list vaFile);
	// @cmember Checks if a directory is empty
	static BOOL				IsDirEmpty				(LPCTSTR lpDir, ...);
	// @cmember Checks if a directory is empty
	static BOOL				IsDirEmptyVa			(LPCTSTR lpDir, va_list vaDir);
	// @cmember Checks if a directory is writable
	static BOOL				IsDirWritable			(LPCTSTR lpDir, ...);
	// @cmember Checks if a directory is writable
	static BOOL				IsDirWritableVa			(LPCTSTR lpDir, va_list vaDir);
	// @cmember Checks if a directory is writable
	static BOOL				IsDirCompressed			(LPCTSTR lpDir, ...);
	// @cmember Checks if a directory is writable
	static BOOL				IsDirCompressedVa		(LPCTSTR lpDir, va_list vaDir);
	// @cmember Creates a directory or a directory tree
	static BOOL				CreateDirectoryTree		(LPCTSTR lpDir, ...);
	// @cmember Creates a directory or a directory tree
	static BOOL				CreateDirectoryTreeVa	(LPCTSTR lpDir, va_list vaDir);
	// @cmember Creates a directory or a directory tree under an existing directory
	static BOOL				CreatePartialDirectoryTree	(LPCTSTR lpBase, LPCTSTR lpDir);
	// @cmember Deletes one or more files
	static UINT				DeleteFiles				(LPCTSTR lpFile, ...);
	// @cmember Deletes one or more files
	static UINT				DeleteFiles				(BOOL bHardKill, LPCTSTR lpFile, ...);
	// @cmember Deletes one or more files
	static UINT				DeleteFilesVa			(BOOL bHardKill, LPCTSTR lpFile, va_list vaFile);
	// @cmember Removes a directory
	static BOOL				RemoveDir				(LPCTSTR lpDir, ...);
	// @cmember Removes a directory
	static BOOL				RemoveDirVa				(LPCTSTR lpDir, va_list vaDir);
	// @cmember Removes a directory and all contained files
	static BOOL				KillDir					(LPCTSTR lpDir, ...);
	// @cmember Removes a directory and all contained files
	static BOOL				KillDir					(BOOL bHardKill, LPCTSTR lpDir, ...);
	// @cmember Removes a directory and all contained files
	static BOOL				KillDirVa				(BOOL bHardKill, LPCTSTR lpDir, va_list vaDir);
	// @cmember Compresses a directory and all contained files
	static BOOL				CompressDir				(LPCTSTR lpDir, ...);
	// @cmember Compresses a directory and all contained files
	static BOOL				CompressDirVa			(LPCTSTR lpDir, va_list vaDir);
	// @cmember Uncompresses a directory and all contained files
	static BOOL				UncompressDir			(LPCTSTR lpDir, ...);
	// @cmember Uncompresses a directory and all contained files
	static BOOL				UncompressDirVa			(LPCTSTR lpDir, va_list vaDir);
	// @cmember Compresses recursively a directory tree and all contained files
	static BOOL				CompressDirTree			(LPCTSTR lpDir, ...);
	// @cmember Compresses recursively a directory tree and all contained files
	static BOOL				CompressDirTreeVa		(LPCTSTR lpDir, va_list vaDir);
	// @cmember Uncompresses recursively a directory tree and all contained files
	static BOOL				UncompressDirTree		(LPCTSTR lpDir, ...);
	// @cmember Uncompresses recursively a directory tree and all contained files
	static BOOL				UncompressDirTreeVa		(LPCTSTR lpDir, va_list vaDir);

	// @cmember Determines the sum of the sizes of one or more files
	static DWORD			GetFilesSizes			(LPCTSTR lpFile, ...);
	// @cmember Determines the sum of the sizes of one or more files
	static DWORD			GetFilesSizes			(LPDWORD lpdwRetHi, LPCTSTR lpFile, ...);
	// @cmember Determines the sum of the sizes of one or more files
	static DWORD			GetFilesSizesVa			(LPCTSTR lpFile, va_list vaFile);
	// @cmember Determines the sum of the sizes of one or more files
	static DWORD			GetFilesSizesVa			(LPDWORD lpdwRetHi, LPCTSTR lpFile, va_list vaFile);
	// @cmember Checks if a file has the read/only attribute set
	static BOOL				IsReadOnly				(LPCTSTR lpFile, ...);
	// @cmember Checks if a file has the read/only attribute set
	static BOOL				IsReadOnlyVa			(LPCTSTR lpFile, va_list vaFile);
	// @cmember Sets the read only attribute of a file
	static BOOL				SetReadOnly				(LPCTSTR lpFile, ...);
	// @cmember Sets the read only attribute of a file
	static BOOL				SetReadOnlyVa			(LPCTSTR lpFile, va_list vaFile);
	// @cmember Clears the read only attribute of a file
	static BOOL				SetReadWrite			(LPCTSTR lpFile, ...);
	// @cmember Clears the read only attribute of a file
	static BOOL				SetReadWriteVa			(LPCTSTR lpFile, va_list vaFile);
	// @cmember Computes the CRC of the contents of a file
	static DWORD			GetFileCRC				(LPCTSTR lpFile, ...);
	// @cmember Computes the CRC of the contents of a file
	static DWORD			GetFileCRCVa			(LPCTSTR lpFile, va_list vaFile);
	// @cmember Gets the size on bytes of a file
	static DWORD			GetFileSize				(LPCTSTR lpFile, ...);
	// @cmember Gets the size on bytes of a file
	static DWORD			GetFileSizeVa			(LPCTSTR lpFile, va_list vaFile);
	// @cmember Gets the last file modification time
	static BOOL				GetFileTime				(FILETIME *lpFileTime, LPCTSTR lpFile, ...);
	// @cmember Gets the last file modification time
	static BOOL				GetFileTimeVa			(FILETIME *lpFileTime, LPCTSTR lpFile, va_list vaFile);
	// @cmember Sets the last file modification time
	static BOOL				SetFileTime				(const FILETIME *lpFileTime, LPCTSTR lpFile, ...);
	// @cmember Sets the last file modification time
	static BOOL				SetFileTimeVa			(const FILETIME *lpFileTime, LPCTSTR lpFile, va_list vaFile);
	// @cmember Sets the last file modification time to now
	static BOOL				Touch					(LPCTSTR lpFile, ...);
	// @cmember Sets the last file modification time to now
	static BOOL				TouchVa					(LPCTSTR lpFile, va_list vaFile);
	// @cmember Adds a set of file attributes to a file
	static BOOL				AddFileAttributes		(DWORD dwAttrMask, LPCTSTR lpFile, ...);
	// @cmember Adds a set of file attributes to a file
	static BOOL				AddFileAttributesVa		(DWORD dwAttrMask, LPCTSTR lpFile, va_list vaFile);
	// @cmember Clears a set of file attributes from a file
	static BOOL				ClearFileAttributes		(DWORD dwAttrMask, LPCTSTR lpFile, ...);
	// @cmember Clears a set of file attributes from a file
	static BOOL				ClearFileAttributesVa	(DWORD dwAttrMask, LPCTSTR lpFile, va_list vaFile);
	// @cmember Compresses a file
	static BOOL				CompressFile			(LPCTSTR lpFile, ...);
	// @cmember Compresses a file
	static BOOL				CompressFileVa			(LPCTSTR lpFile, va_list vaFile);
	// @cmember Uncompresses a file
	static BOOL				UncompressFile			(LPCTSTR lpFile, ...);
	// @cmember Uncompresses a file
	static BOOL				UncompressFileVa		(LPCTSTR lpFile, va_list vaFile);
};
//
// @xref
//		<j Tools Pseudoclasses>

class YDirEnumerator
{
public:
	YDirEnumerator			();
	~YDirEnumerator			();

public:
	void					Start					(LPCTSTR pszPattern, ...);
	void					StartVa					(LPCTSTR pszPattern, va_list vaPattern);
	void					End						();
	BOOL					GetNext					();

public:
	LPCTSTR					GetName					() const;
	LPCTSTR					GetPath					() const;
	LPCTSTR					GetFullName				() const;
	LPCTSTR					GetAlternateName		() const;
	DWORD					GetSize					(LPDWORD pdwFileSizeHigh = NULL) const;
	DWORD					GetAttributes			() const;
	void					GetCreationTime			(LPFILETIME pftTime) const;
	void					GetModificationTime		(LPFILETIME pftTime) const;
	void					GetAccessTime			(LPFILETIME pftTime) const;

	BOOL					IsDir					() const;
	BOOL					IsFile					() const;
	BOOL					IsDotDir				() const;
	BOOL					IsNoDotDir				() const;

protected:
	HANDLE					m_hFind;
	WIN32_FIND_DATA			m_wfd;
	TCHAR					m_szPathComponent[MAX_PATH];
	TCHAR					m_szFullName[MAX_PATH];
};

#ifdef YLB_ENABLE_INLINE
#include <yFileTools.inl>
#endif

#endif //__yFileTools_h__

//
// EoF
////////
