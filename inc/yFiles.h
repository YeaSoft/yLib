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
 * FILENAME		:	yFiles.h
 * PURPOSE		:	Declaration of the generic file classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
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
		modeRead		= 0x00000000,
		modeWrite		= 0x00000001,
		modeReadWrite	= 0x00000002,
		shareExclusive	= 0x00000000,
		shareDenyWrite	= 0x00000004,
		shareDenyRead	= 0x00000008,
		shareDenyNone	= 0x00000010,
		modeNoInherit	= 0x00000020,
		modeCreate		= 0x00000040,
		modeNoTruncate	= 0x00000080,
		typeText		= 0x00000100,
		typeBinary		= 0x00000200
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

public:
	// operations
	virtual HANDLE				Detach					();
	virtual BOOL				Open					(LPCTSTR pszFileName, UINT nOpenFlags);
	virtual BOOL				Close					();

	virtual BOOL				Read					(LPVOID lpBuffer, DWORD nNumberOfBytesToRead);
	virtual BOOL				Read					(LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead);
	virtual BOOL				Write					(LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite);
	virtual BOOL				Write					(LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten);

	virtual BOOL				WriteString				(LPCTSTR pszString);
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