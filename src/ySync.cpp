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
 * FILENAME		:	ySync.cpp
 * PURPOSE		:	Implementation of the synchronisation classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

#include "StdInc.hpp"

void YSemaphore::Attach (HANDLE hSemaphore)
{
	if ( hSemaphore != m_hHandle ) {
		Close ();
	}
	m_hHandle = hSemaphore;
}

BOOL YSemaphore::Create (LONG lInitialCount, LONG lMaxCount, LPCTSTR lpszName, LPSECURITY_ATTRIBUTES lpsaAttributes)
{
	ASSERTY(lMaxCount > 0);
	ASSERTY(lInitialCount <= lMaxCount);

	HANDLE hSemaphore = ::CreateSemaphore (
		lpsaAttributes,
		lInitialCount,
		lMaxCount,
		lpszName
	);
	if ( hSemaphore ) {
		Close ();
		m_hHandle = hSemaphore;
		return TRUE;
	}
	return FALSE;
}

BOOL YSemaphore::Unlock (LONG lCount, LPLONG lpPrevCount /* = NULL */)
{
	if ( !IsValid () ) {
		return FALSE;
	}
	return ::ReleaseSemaphore (m_hHandle, lCount, lpPrevCount);
}

BOOL YMutex::Create (BOOL bInitiallyOwn, LPCTSTR lpszName, LPSECURITY_ATTRIBUTES lpsaAttribute /* = NULL */)
{
	HANDLE hMutex = ::CreateMutex (
		lpsaAttribute,
		bInitiallyOwn,
		lpszName
	);
	if ( hMutex ) {
		Close ();
		m_hHandle = hMutex;
		return TRUE;
	}
	return FALSE;
}

BOOL YEvent::Create (BOOL bManualReset /* = FALSE */, BOOL bInitiallyOwn /* = FALSE */, LPCTSTR lpszName /* = NULL */, LPSECURITY_ATTRIBUTES lpsaAttribute /* = NULL */)
{
	HANDLE hEvent = ::CreateEvent (
		lpsaAttribute,
		bManualReset,
		bInitiallyOwn,
		lpszName
	);
	if ( hEvent ) {
		Close ();
		m_hHandle		= hEvent;
		m_bManualReset	= bManualReset;
		return TRUE;
	}
	return FALSE;
}

/*=============================================================================
 * SYNCHRONISATION GUARD IMPLEMENTATIONS
 *============================================================================*/
YSingleGuard::YSingleGuard (YSyncHandle* pHandle, BOOL bInitialLock)
{
	ASSERTY(pHandle != NULL);

	m_pHandle	= pHandle;
	m_bAcquired	= FALSE;

	if ( bInitialLock ) {
		Lock ();
	}
}

BOOL YSingleGuard::Lock (DWORD dwTimeOut /* = INFINITE */)
{
	ASSERTY(m_pHandle != NULL);
	ASSERTY(!m_bAcquired);

	m_bAcquired = m_pHandle->Lock (dwTimeOut);
	return m_bAcquired;
}

BOOL YSingleGuard::Unlock ()
{
	ASSERTY(m_pHandle != NULL);
	if ( m_bAcquired ) {
		m_bAcquired = !m_pHandle->Unlock ();
	}
	return !m_bAcquired;
}

BOOL YSingleGuard::Unlock (LONG lCount, LPLONG lpPrevCount /* = NULL */)
{
	ASSERTY(m_pHandle != NULL);
	if ( m_bAcquired ) {
		m_bAcquired = !m_pHandle->Unlock (lCount, lpPrevCount);
	}
	return !m_bAcquired;
}

YMultiGuard::YMultiGuard (YSyncHandle* ppObjects[], DWORD dwCount, BOOL bInitialLock /* = FALSE */)
{
	m_dwCount = 0;

	for ( DWORD dw = 0; dw < dwCount; dw++ ) {
		AddObject (ppObjects[dw]);
	}
	if ( bInitialLock ) {
		Lock ();
	}
}

BOOL YMultiGuard::AddObject (YSyncHandle *pHandle)
{
	ASSERTY(pHandle != NULL);
	ASSERTY(pHandle->IsValid());
	if ( m_dwCount >= MAXIMUM_WAIT_OBJECTS ) {
		// array full. cannot add any more
		return FALSE;
	}
	if ( !pHandle->IsWaitable () ) {
		// 
		return FALSE;
	}
	m_pObjects[m_dwCount]	= pHandle;
	m_hObjects[m_dwCount]	= pHandle->GetHandle ();
	m_bObjects[m_dwCount]	= FALSE;
	++m_dwCount;
	return TRUE;
}

DWORD YMultiGuard::WaitEx (DWORD dwTimeOut /* = INFINITE */, BOOL bWaitForAll /* = TRUE */, BOOL bAlertable /* = TRUE */)
{
	DWORD dwResult = ::WaitForMultipleObjectsEx (m_dwCount, m_hObjects, bWaitForAll, dwTimeOut, bAlertable);
	if ( (dwResult >= WAIT_OBJECT_0) && (dwResult < (WAIT_OBJECT_0 + m_dwCount)) ) {
		if ( bWaitForAll ) {
			for ( DWORD dw = 0; dw < m_dwCount; dw++ ) {
				m_bObjects[dw] = TRUE;
			}
		}
		else {
			ASSERTY((dwResult - WAIT_OBJECT_0) >= 0);
			m_bObjects[dwResult - WAIT_OBJECT_0] = TRUE;
		}
	}
	return dwResult;
}

DWORD YMultiGuard::Lock (DWORD dwTimeOut /* = INFINITE */, BOOL bWaitForAll /* = TRUE */)
{
	DWORD dwResult = ::WaitForMultipleObjects (m_dwCount, m_hObjects, bWaitForAll, dwTimeOut);
	if ( (dwResult >= WAIT_OBJECT_0) && (dwResult < (WAIT_OBJECT_0 + m_dwCount)) ) {
		if ( bWaitForAll ) {
			for ( DWORD dw = 0; dw < m_dwCount; dw++ ) {
				m_bObjects[dw] = TRUE;
			}
		}
		else {
			ASSERTY((dwResult - WAIT_OBJECT_0) >= 0);
			m_bObjects[dwResult - WAIT_OBJECT_0] = TRUE;
		}
	}
	return dwResult;
}

BOOL YMultiGuard::Unlock ()
{
	for ( DWORD dw = 0; dw < m_dwCount; dw++ ) {
		if ( m_bObjects[dw] ) {
			m_bObjects[dw] = !m_pObjects[dw]->Unlock ();
		}
	}
	return TRUE;
}

BOOL YMultiGuard::Unlock (LONG lCount, LPLONG lpPrevCount /* =NULL */)
{
	BOOL bGotOne = FALSE;
	for ( DWORD dw = 0; dw < m_dwCount; dw++ ) {
		if ( m_bObjects[dw] && m_pObjects[dw]->IsSemaphore () ) {
			bGotOne = TRUE;
			m_bObjects[dw] = !m_pObjects[dw]->Unlock (lCount, lpPrevCount);
		}
	}

	return bGotOne;
}


#ifndef YLB_ENABLE_INLINE
#include <ySync.inl>
#endif

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////