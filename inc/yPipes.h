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
 * FILENAME		:	yPipes.h
 * PURPOSE		:	Declaration of the data pipe classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yPipes.h
 *============================================================================*/
#ifndef __yPipes_h__
#define __yPipes_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yHandles_h__
#include <yHandle.h>
#endif

/*=============================================================================
 * FORWARD CLASS DECLARATIONS
 *============================================================================*/
class YPipe;
	class YServerNamedPipe;
	class YClientNamedPipe;

/*=============================================================================
 * CLASS DECLARATIONS
 *============================================================================*/
class YPipe : public YDataHandle
{
private:
	// kill these construction methods & operators
	YPipe						(const YPipe &);
	YPipe						&operator=				(const YPipe &);

public:
	// construction
	YPipe						();

public:
	// operations
	virtual BOOL				Unlock					();
	virtual BOOL				Unlock					(LONG lCount, LPLONG lpPrevCount = NULL);
	BOOL						PeekPipe				(
														LPVOID lpBuffer,
														DWORD nBufferSize,
														LPDWORD lpBytesRead,
														LPDWORD lpTotalBytesAvail = NULL,
														LPDWORD lpBytesLeftThisMessage = NULL
														) const;

public:
	// attributes
	BOOL						GetPipeInfo				(
														LPDWORD lpFlags = NULL,
														LPDWORD lpOutBufferSize = NULL,
														LPDWORD lpInBufferSize = NULL,
														LPDWORD lpMaxInstances = NULL
														) const;
};

class YNamedPipe : public YPipe
{
private:
	// kill these construction methods & operators
	YNamedPipe					(const YNamedPipe &);
	YNamedPipe					&operator=				(const YNamedPipe &);

public:
	// construction
	YNamedPipe					();

public:
	// operations
	void						Attach					(HANDLE hNamedPipe);

public:
	// attributes
	BOOL						GetHandleState			(
														LPDWORD lpState = NULL,
														LPDWORD lpCurInstances = NULL,
														LPDWORD lpMaxCollectionCount = NULL,
														LPDWORD lpCollectDataTimeout = NULL,
														LPTSTR lpUserName = NULL,
														DWORD nMaxUserNameSize = 0
														) const;
	BOOL						SetHandleState			(
														LPDWORD lpMode,
														LPDWORD lpMaxCollectionCount = NULL,
														LPDWORD lpCollectDataTimeout = NULL
														) const;
	BOOL						SetPipeMode				(DWORD dwMode) const;
	BOOL						SetPipeCollectionParams	(DWORD dwMaxCollectionCount, DWORD dwCollectDataTimeout) const;
};

class YServerNamedPipe : public YNamedPipe
{
private:
	// kill these construction methods & operators
	YServerNamedPipe			(const YServerNamedPipe &);
	YServerNamedPipe			&operator=				(const YServerNamedPipe &);

public:
	// construction
	YServerNamedPipe			();

public:
	// operations
	BOOL						Create					(LPCTSTR lpName, DWORD dwOpenMode, DWORD dwPipeMode, DWORD nMaxInstances, DWORD nOutBufferSize, DWORD nInBufferSize, DWORD nDefaultTimeOut, LPSECURITY_ATTRIBUTES lpSecurityAttributes = NULL);
	BOOL						Connect					(LPOVERLAPPED lpOverlapped = NULL) const;
	BOOL						Disconnect				() const;

public:
	// overridables
	virtual BOOL				Unlock					();
};

class YClientNamedPipe : public YNamedPipe
{
private:
	// kill these construction methods & operators
	YClientNamedPipe			(const YClientNamedPipe &);
	YClientNamedPipe			&operator=				(const YClientNamedPipe &);

public:
	// construction
	YClientNamedPipe			();

public:
	// operations
	BOOL						Create					(
														LPCTSTR pszPipeName,
														DWORD dwDesiredAccess = GENERIC_READ|GENERIC_WRITE,
														LPSECURITY_ATTRIBUTES lpSecurityAttributes = NULL,
														DWORD dwFlagsAndAttributes = 0
														);
	BOOL						Create					(
														LPCTSTR pszName,
														LPCTSTR pszComputer,
														DWORD dwDesiredAccess = GENERIC_READ|GENERIC_WRITE,
														LPSECURITY_ATTRIBUTES lpSecurityAttributes = NULL,
														DWORD dwFlagsAndAttributes = 0
														);
	static BOOL					Call					(
														LPCTSTR pszPipeName,
														LPVOID lpInBuffer,
														DWORD nInBufferSize,
														LPVOID lpOutBuffer,
														DWORD nOutBufferSize,
														LPDWORD lpBytesRead,
														DWORD nTimeOut = NMPWAIT_USE_DEFAULT_WAIT
														);
	static BOOL					Call					(
														LPCTSTR pszName,
														LPCTSTR pszComputer,
														LPVOID lpInBuffer,
														DWORD nInBufferSize,
														LPVOID lpOutBuffer,
														DWORD nOutBufferSize,
														LPDWORD lpBytesRead,
														DWORD nTimeOut = NMPWAIT_USE_DEFAULT_WAIT
														);
	static BOOL					WaitNamedPipe			(LPCTSTR pszPipeName, DWORD nTimeOut = NMPWAIT_USE_DEFAULT_WAIT);
	static BOOL					WaitNamedPipe			(LPCTSTR pszName, LPCTSTR pszComputer, DWORD nTimeOut = NMPWAIT_USE_DEFAULT_WAIT);

	BOOL						Transact				(
														LPCVOID lpInBuffer,
														DWORD nInBufferSize,
														LPVOID lpOutBuffer,
														DWORD nOutBufferSize,
														LPDWORD lpBytesRead,
														LPOVERLAPPED lpOverlapped = NULL
														) const;

public:
	// attributes
	static BOOL					IsValidPipeName			(LPCTSTR lpFileName);
};

#ifdef YLB_ENABLE_INLINE
#include <yPipes.inl>
#endif

#endif //__yPipes_h__
//
// EoF
////////