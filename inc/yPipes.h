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
 * FILENAME		:	yPipes.h
 * PURPOSE		:	Declaration of the data pipe classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:03:21  leo
 * Initial revision
 *
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