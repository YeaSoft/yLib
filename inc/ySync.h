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
 * FILENAME		:	ySync.h
 * PURPOSE		:	Declaration of the synchronisation classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | ySync.h
 *============================================================================*/
#ifndef __ySync_h__
#define __ySync_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yLibBase_h__
#include <yLibBase.h>
#endif
#ifndef __yHandle_h__
#include <yHandle.h>
#endif

/*=============================================================================
 * SYNCHRONISATION OBJECT DECLARATIONS
 *============================================================================*/
class YSemaphore : public YSyncHandle
{
private:
	// kill these construction methods & operators
	YSemaphore					(const YSemaphore &);
	YSemaphore					&operator=				(const YSemaphore &);

public:
	// construction
	YSemaphore					();

public:
	// operations
	void						Attach					(HANDLE hSemaphore);
	BOOL						Create					(LONG lInitialCount = 1, LONG lMaxCount = 1, LPCTSTR lpszName = NULL, LPSECURITY_ATTRIBUTES lpsaAttributes = NULL);
	virtual BOOL				Unlock					();
	virtual BOOL				Unlock					(LONG lCount, LPLONG lpPrevCount = NULL);
};

class YMutex : public YSyncHandle
{
private:
	// kill these construction methods & operators
	YMutex						(const YMutex &);
	YMutex						&operator=				(const YMutex &);

public:
	// construction
	YMutex						();

public:
	// operations
	void						Attach					(HANDLE hMutex);
	BOOL						Create					(BOOL bInitiallyOwn = FALSE, LPCTSTR lpszName = NULL, LPSECURITY_ATTRIBUTES lpsaAttribute = NULL);
	virtual BOOL				Unlock					();
};

class YEvent : public YSyncHandle
{
private:
	// kill these construction methods & operators
	YEvent						(const YEvent &);
	YEvent						&operator=				(const YEvent &);

public:
	// construction
	YEvent						();

public:
	// operations
	BOOL						Create					(BOOL bManualReset = FALSE, BOOL bInitiallyOwn = FALSE, LPCTSTR lpszName = NULL, LPSECURITY_ATTRIBUTES lpsaAttribute = NULL);
	BOOL						SetEvent				() const;
	BOOL						PulseEvent				() const;
	BOOL						ResetEvent				() const;
	BOOL						Unlock					();

protected:
	// implementation
	BOOL						m_bManualReset;
};

class YCriticalSection : public YSyncHandle
{
private:
	// kill these construction methods & operators
	YCriticalSection			(const YCriticalSection &);
	YCriticalSection			&operator=				(const YCriticalSection &);

public:
	// construction/destruction
	YCriticalSection			();
	~YCriticalSection			();

public:
	// operations
	void						Recreate				();
	void						Enter					();
	void						Leave					();
#if (_WIN32_WINNT >= 0x0400)
	BOOL						TryEnter				();
#endif
	BOOL						Lock					();
	BOOL						Lock					(DWORD dwTimeout);
	BOOL						Unlock					();

public:
	// attributes
	operator					CRITICAL_SECTION*		();

protected:
	// implementation
	CRITICAL_SECTION			m_sect;
};

/*=============================================================================
 * SYNCHRONISATION GUARD DECLARATIONS
 *============================================================================*/
class YSingleGuard
{
private:
	// kill these construction methods & operators
	YSingleGuard				(const YSingleGuard &);
	YSingleGuard				&operator=				(const YSingleGuard &);

public:
	// construction/destruction
	YSingleGuard				(YSyncHandle* pObject, BOOL bInitialLock = FALSE);
	~YSingleGuard				();

public:
	// operations
	BOOL						Lock					(DWORD dwTimeOut = INFINITE);
	BOOL						Unlock					();
	BOOL						Unlock					(LONG lCount, LPLONG lPrevCount = NULL);

public:
	// attributes
	BOOL						IsLocked				();

protected:
	// implementation
	YSyncHandle *				m_pHandle;
	BOOL						m_bAcquired;
};

class YMultiGuard
{
private:
	// kill these construction methods & operators
	YMultiGuard					(const YMultiGuard &);
	YMultiGuard					&operator=				(const YMultiGuard &);

public:
	// construction/destruction
	YMultiGuard					();
	YMultiGuard					(YSyncHandle* ppObjects[], DWORD dwCount, BOOL bInitialLock = FALSE);
	~YMultiGuard				();

public:
	// operations
	BOOL						AddObject				(YSyncHandle *pObject);
	BOOL						AddObject				(YSyncHandle &shObject);
	void						CleanObjects			();
	DWORD						Wait					(DWORD dwTimeOut = INFINITE, BOOL bWaitForAll = FALSE);
	DWORD						WaitEx					(DWORD dwTimeOut = INFINITE, BOOL bWaitForAll = FALSE, BOOL bAlertable = TRUE);
	DWORD						Lock					(DWORD dwTimeOut = INFINITE, BOOL bWaitForAll = TRUE);
	BOOL						Unlock					();
	BOOL						Unlock					(LONG lCount, LPLONG lPrevCount = NULL);

public:
	// attributes
	BOOL						IsLocked				(DWORD dwItem);

protected:
	// implementation
	YSyncHandle *				m_pObjects[MAXIMUM_WAIT_OBJECTS];
	HANDLE						m_hObjects[MAXIMUM_WAIT_OBJECTS];
	BOOL						m_bObjects[MAXIMUM_WAIT_OBJECTS];
	DWORD						m_dwCount;
};


#ifdef YLB_ENABLE_INLINE
#include <ySync.inl>
#endif

#endif //__ySync_h__
//
// EoF
////////