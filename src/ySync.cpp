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
 * FILENAME		:	ySync.cpp
 * PURPOSE		:	Implementation of the synchronisation classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.2  2000/09/04 12:07:43  leopoldo
 * Updated license to zlib/libpng
 *
 * Revision 1.1  2000/05/26 14:05:11  leo
 * Initial revision
 *
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
//LPCTSTR lpComment = _T("$Id$");

//
// EoF
////////