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
 * FILENAME		:	yHandle.h
 * PURPOSE		:	Declaration of the generic handle class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:03:11  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yHandle.h
 *============================================================================*/
#ifndef __yHandle_h__
#define __yHandle_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yFlags_h__
#include <yFlags.h>
#endif

/*=============================================================================
 * FORWARD CLASS DECLARATIONS
 *============================================================================*/
class YBaseHandle;
	class YHandle;
		class YSimpleDataHandle;
			class YBaseFile;
		class YSyncHandle;
			class YSemaphore;
			class YMutex;
			class YEvent;
			class YThread;
			class YProcess;
			class YDataHandle;
				class YFile;
				class YClientNamedPipe;
				class YServerNamedPipe;
				class YClientMailslot;
				class YServerMailslot;
	class YTransSemaphore;
	class YTransMutex;
	class YTransEvent;
	class YTransThread;
	class YTransProcess;
	class YTransClientNamedPipe;
	class YTransServerNamedPipe;
	class YTransClientMailslot;
	class YTransServerMailslot;

/*=============================================================================
 * CLASS DECLARATIONS
 *============================================================================*/
class YBaseHandle : protected YFlags
{
protected:
	// flags
	static DWORD				FLG_SYN_CRITICALSECT;
	static DWORD				FLG_SYN_EVENT;
	static DWORD				FLG_SYN_SEMAPHORE;
	static DWORD				FLG_SYN_MUTEX;
	static DWORD				FLG_PRC_THREAD;
	static DWORD				FLG_PRC_PROCESS;
	static DWORD				FLG_DAT_FILE;
	static DWORD				FLG_DAT_CLIENTNP;
	static DWORD				FLG_DAT_SERVERNP;
	static DWORD				FLG_DAT_CLIENTMS;
	static DWORD				FLG_DAT_SERVERMS;
	// masks
	static DWORD				MSK_SYNC;
	static DWORD				MSK_PROCESS;
	static DWORD				MSK_DATA;
	static DWORD				MSK_TYPES;
	static DWORD				MSK_WAITABLE;

public:
	// construction
	YBaseHandle					(HANDLE hHandle = INVALID_HANDLE_VALUE, DWORD dwType = 0);

protected:
	// implementation
	HANDLE						m_hHandle;
};

// transport classes
class YTransSemaphore : protected YBaseHandle
{
public:
	// construction
	YTransSemaphore				(HANDLE hHandle);
};

class YTransMutex : protected YBaseHandle
{
public:
	// construction
	YTransMutex					(HANDLE hHandle);
};

class YTransEvent : protected YBaseHandle
{
public:
	// construction
	YTransEvent					(HANDLE hHandle);
};

class YTransThread : protected YBaseHandle
{
public:
	// construction
	YTransThread				(HANDLE hHandle);
};

class YTransProcess : protected YBaseHandle
{
public:
	// construction
	YTransProcess				(HANDLE hHandle);
};

class YTransClientNamedPipe : protected YBaseHandle
{
public:
	// construction
	YTransClientNamedPipe		(HANDLE hHandle);
};

class YTransServerNamedPipe : protected YBaseHandle
{
public:
	// construction
	YTransServerNamedPipe		(HANDLE hHandle);
};

class YTransClientMailslot : protected YBaseHandle
{
public:
	// construction
	YTransClientMailslot		(HANDLE hHandle);
};

class YTransServerMailslot : protected YBaseHandle
{
public:
	// construction
	YTransServerMailslot		(HANDLE hHandle);
};

// real handle classes classes
class YHandle : protected YBaseHandle
{
private:
	// kill these construction methods & operators
	YHandle						(const YHandle &);
	YHandle						&operator=				(const YHandle &);

public:
	// construction/destruction
	YHandle						();
	~YHandle					();

public:
	// operations
	virtual HANDLE				Detach					();
	virtual BOOL				Close					();
	HANDLE						Duplicate				(HANDLE hSourceProcessHandle, HANDLE hTargetProcessHandle, BOOL bInheritHandle = FALSE, DWORD dwDesiredAccess = 0, DWORD dwOptions = DUPLICATE_SAME_ACCESS) const;
	HANDLE						Duplicate				(HANDLE hTargetProcessHandle, BOOL bInheritHandle = FALSE, DWORD dwDesiredAccess = 0, DWORD dwOptions = DUPLICATE_SAME_ACCESS) const;
	HANDLE						Duplicate				(BOOL bInheritHandle = FALSE, DWORD dwDesiredAccess = 0, DWORD dwOptions = DUPLICATE_SAME_ACCESS) const;

public:
	// attributes
	operator					HANDLE					() const;
	HANDLE						GetHandle				() const;
	BOOL						GetInformation			(LPDWORD lpdwFlags) const;
	BOOL						SetInformation			(DWORD dwMask, DWORD dwFlags) const;

	BOOL						IsCriticalSection		() const;
	BOOL						IsEvent					() const;
	BOOL						IsSemaphore				() const;
	BOOL						IsMutex					() const;
	BOOL						IsThread				() const;
	BOOL						IsProcess				() const;
	BOOL						IsClientNamedPipe		() const;
	BOOL						IsServerNamedPipe		() const;
	BOOL						IsClientMailslot		() const;
	BOOL						IsServerMailslot		() const;

	virtual BOOL				IsValid					() const;
	BOOL						IsWaitable				() const;
};

class YSyncHandle : virtual public YHandle
{
private:
	// kill these construction methods & operators
	YSyncHandle					(const YSyncHandle &);
	YSyncHandle					&operator=				(const YSyncHandle &);

protected:
	// construction
	YSyncHandle					();

public:
	// operations
	virtual BOOL				Lock					(DWORD dwTimeout = INFINITE);
	virtual DWORD				Wait					(DWORD dwTimeout = INFINITE);
	virtual DWORD				WaitEx					(DWORD dwTimeout = INFINITE, BOOL bAlertable = TRUE);
	virtual BOOL				Unlock					() = 0;
	virtual BOOL				Unlock					(LONG lCount, LPLONG lpPrevCount = NULL);
};

class YSimpleDataHandle : virtual public YHandle
{
private:
	// kill these construction methods & operators
	YSimpleDataHandle			(const YSimpleDataHandle &);
	YSimpleDataHandle			&operator=				(const YSimpleDataHandle &);

protected:
	// construction
	YSimpleDataHandle			();

public:
	// operations
	virtual BOOL				Read					(LPVOID lpBuffer, DWORD nNumberOfBytesToRead);
	virtual BOOL				Read					(LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead);
	virtual BOOL				Write					(LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite);
	virtual BOOL				Write					(LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten);

public:
	// attributes
	DWORD						GetBytesRead			() const;
	DWORD						GetBytesWritten			() const;

protected:
	// implementation
	DWORD						m_dwBytesRead;
	DWORD						m_dwBytesWritten;
};

class YDataHandle : virtual public YSyncHandle, virtual public YSimpleDataHandle
{
private:
	// kill these construction methods & operators
	YDataHandle					(const YDataHandle &);
	YDataHandle					&operator=				(const YDataHandle &);

protected:
	// construction
	YDataHandle					();

public:
	// operations
	using						YSimpleDataHandle::Read;
	using						YSimpleDataHandle::Write;

	virtual BOOL				Read					(LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
	virtual BOOL				Read					(LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPOVERLAPPED lpOverlapped);
	virtual BOOL				Write					(LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);
	virtual BOOL				Write					(LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPOVERLAPPED lpOverlapped);
	virtual BOOL				ReadEx					(LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPOVERLAPPED lpOverlapped, LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
	virtual BOOL				WriteEx					(LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPOVERLAPPED lpOverlapped, LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);

public:
	// attributes
	BOOL						GetOverlappedResult		(LPOVERLAPPED lpOverlapped, LPDWORD lpNumberOfBytesTransferred, BOOL bWait) const;
};

#ifdef YLB_ENABLE_INLINE
#include <yHandle.inl>
#endif

#endif //__yHandle_h__
//
// EoF
////////