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
 * FILENAME		:	yFiles.h
 * PURPOSE		:	Declaration of the generic file classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.4  2000/08/24 17:15:46  leo
 * Added missing destructor to YStdioFile
 *
 * Revision 1.3  2000/08/23  11:55:49  leo
 * Added more file open modes
 * Updated license
 *
 * Revision 1.2  2000/05/30  10:58:08  leo
 * Removed unused methods from YStdioFile
 *
 * Revision 1.1  2000/05/26  14:03:04  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yFiles.h
 *============================================================================*/
#ifndef __yFiles_h__
#define __yFiles_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yHandle_h__
#include <yHandle.h>
#endif
#ifndef __yFixStr_h__
#include <yFixStr.h>
#endif

#ifndef INVALID_SET_FILE_POINTER
#define INVALID_SET_FILE_POINTER	((DWORD) -1)
#endif

/*=============================================================================
 * THE BASE FILE CLASS
 *============================================================================*/
class YBaseFile : virtual public YSimpleDataHandle
{
private:
	// kill these construction methods & operators
	YBaseFile					(const YBaseFile &);
	YBaseFile					&operator=				(const YBaseFile &);

public:
	// construction
	YBaseFile					();

public:
	// operations
	virtual BOOL				Open					(LPCTSTR pszFileName, UINT nOpenFlags) = 0;
	virtual BOOL				Flush					();
	virtual DWORD				Seek					(LONG lDistanceToMove, DWORD dwMoveMethod = FILE_BEGIN);
	virtual DWORD				Seek					(LONG lDistanceToMove, LPLONG lpDistanceToMoveHigh, DWORD dwMoveMethod = FILE_BEGIN);
	virtual BOOL				SeekToBegin				();
	virtual BOOL				SeekToEnd				();

public:
	// attributes
	virtual DWORD				GetLength				(LPDWORD lpdwSizeHigh = NULL) const;
	virtual DWORD				GetPosition				(LPDWORD lpdwPosHigh = NULL) const;

protected:
	// implementation
	HANDLE						OpenHelper				(LPCTSTR pszFileName, UINT nOpenFlags);
};

class YFile : virtual public YBaseFile, virtual public YDataHandle
{
public:
	enum YOpenFlags {
		modeRead					= 0x00000000,
		modeWrite					= 0x00000001,
		modeReadWrite				= 0x00000002,
		shareExclusive				= 0x00000000,
		shareDenyWrite				= 0x00000004,
		shareDenyRead				= 0x00000008,
		shareDenyNone				= 0x00000010,
		modeNoInherit				= 0x00000020,
		modeCreate					= 0x00000040,
		modeNoTruncate				= 0x00000080,
		typeText					= 0x00000100,
		typeBinary					= 0x00000200,
		cacheDefault				= 0x00000000,
		cacheNoBuffering			= 0x00010000,
		cacheWriteThrough			= 0x00020000,
		cacheSequentialOptimized	= 0x00040000,
		cacheRandomOptimized		= 0x00080000,
		modeDeleteOnClose			= 0x00100000,
		modeBackup					= 0x00200000,
		modePosix					= 0x00400000
	};

private:
	// kill these construction methods & operators
	YFile						(const YFile &);
	YFile						&operator=				(const YFile &);

public:
	// construction
	YFile						();

public:
	// operations
	void						Attach					(HANDLE hFile);
	virtual BOOL				Open					(LPCTSTR pszFileName, UINT nOpenFlags);
	virtual BOOL				Create					(
															LPCTSTR					lpFileName,
															DWORD					dwDesiredAccess = GENERIC_READ | GENERIC_WRITE,
															DWORD					dwShareMode = 0,
															LPSECURITY_ATTRIBUTES	lpSecurityAttributes = NULL,
															DWORD					dwCreationDisposition = OPEN_ALWAYS,
															DWORD					dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL,
															HANDLE					hTemplateFile = NULL
														);
	virtual BOOL				LockRange				(DWORD dwPos, DWORD dwCount);
	virtual BOOL				UnlockRange				(DWORD dwPos, DWORD dwCount);

	virtual BOOL				Unlock					();
	virtual BOOL				Unlock					(LONG lCount, LPLONG lpPrevCount = NULL);

public:
	// attributes
	virtual BOOL				SetLength				(DWORD dwSize, DWORD dwSizeHigh = 0);
	virtual BOOL				GetStatus				(LPBY_HANDLE_FILE_INFORMATION pbhFI) const;
};

class YStdioFile : virtual public YBaseFile
{
private:
	// kill these construction methods & operators
	YStdioFile					(const YStdioFile &);
	YStdioFile					&operator=				(const YBaseFile &);

public:
	// construction
	YStdioFile					();
	~YStdioFile					();

public:
	// operations
	virtual HANDLE				Detach					();
	virtual BOOL				Open					(LPCTSTR pszFileName, UINT nOpenFlags);
	virtual BOOL				Close					();

	virtual BOOL				Read					(LPVOID lpBuffer, DWORD nNumberOfBytesToRead);
	virtual BOOL				Read					(LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead);
	virtual BOOL				Write					(LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite);
	virtual BOOL				Write					(LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten);

	virtual BOOL				WriteString				(LPCTSTR pszString, ...);
	virtual BOOL				WriteStringVa			(LPCTSTR pszString, va_list va);
	virtual LPTSTR				ReadString				(LPTSTR pszString, UINT nMax);
	virtual BOOL				ReadString				(YFixedString& rString);

	virtual BOOL				Flush					();
	virtual DWORD				Seek					(LONG lDistanceToMove, DWORD dwMoveMethod = FILE_BEGIN);
	virtual DWORD				Seek					(LONG lDistanceToMove, LPLONG lpDistanceToMoveHigh, DWORD dwMoveMethod = FILE_BEGIN);

public:
	// attributes
	virtual BOOL				IsValid					() const;
	virtual DWORD				GetLength				(LPDWORD lpdwSizeHigh = NULL) const;
	virtual DWORD				GetPosition				(LPDWORD lpdwPosHigh = NULL) const;

protected:
	// implementation
	FILE *						m_pStream;
};

#ifdef YLB_ENABLE_INLINE
#include <yFiles.inl>
#endif

#endif //__yFiles_h__
//
// EoF
////////