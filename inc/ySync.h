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
 * FILENAME		:	ySync.h
 * PURPOSE		:	Declaration of the synchronisation classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:03:34  leo
 * Initial revision
 *
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