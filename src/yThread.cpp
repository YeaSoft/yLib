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
 * FILENAME		:	YWorkerThread.cpp
 * PURPOSE		:	Implementation of the thread class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:05:12  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | YWorkerThread.h
 *============================================================================*/

#include "StdInc.hpp"

const DWORD		FLG_THRD_DIRTY				= 0x20000000;
const DWORD		FLG_THRD_RUNOUT				= 0x40000000;
const DWORD		FLG_THRD_FINISHED			= 0x80000000;

YWorkerThread::YWorkerThread (LPCTSTR pszName /* = _T("<noname>") */)
{
	pCommonConstructor ();
	_tcsncpy (m_szThreadName, pszName, YLB_MAX_THREADNAME - 1);
	m_szThreadName[YLB_MAX_THREADNAME - 1] = 0;
}

YWorkerThread::~YWorkerThread ()
{
	Terminate (10000, 0);
	pCommonConstructor ();
}

BOOL YWorkerThread::Create (BOOL bSuspended /* = FALSE */, UINT uStackSize /* = 0 */, LPSECURITY_ATTRIBUTES lpThreadAttributes /* = NULL */)
{
	YSingleGuard	sg(&m_csControl, TRUE);

	if ( m_flags.TestClearFlags (FLG_THRD_FINISHED) ) {
		// close the handle from a previous run...
		Close ();
	}

	if ( IsValid () ) {
		SetLastError (ERROR_ALREADY_EXISTS);
		return FALSE;
	}

	pCommonConstructor ();

	if ( !PreCreateThread (bSuspended, uStackSize, lpThreadAttributes) ) {
		return FALSE;
	}

	m_hHandle = (HANDLE) _beginthreadex (
		(void *) lpThreadAttributes,
		uStackSize,
		_yLibThread,
		(void *) this,
		CREATE_SUSPENDED,
		&m_uThreadID
	);
	if ( m_hHandle == (HANDLE) -1 ) {
		// error!
		pCommonConstructor ();
		SetLastSysError ();
		return FALSE;
	}
	m_dwSuspendCount = 1;
	return (bSuspended) ? (TRUE) : (Resume ());
}

BOOL YWorkerThread::Terminate (DWORD dwTimeout, DWORD dwExitCode)
{
	m_csControl.Enter ();
	if ( !IsValid ()  ) {
		// error
		SetLastError (ERROR_INVALID_HANDLE);
		m_csControl.Leave ();
		return FALSE;
	}
	if ( IsThis () ) {
		// called within the thread...
		m_dwExitCode	= dwExitCode;
		OnExitThread (FALSE);
		ClearFlags (FLG_THRD_DIRTY);
		Close ();
		m_uThreadID		= 0;
		m_flags.Set (0);
		m_csControl.Leave ();
		_endthreadex (m_dwExitCode); 
		// unreachable code
		return TRUE;
	}
	else {
		// called from outside
		if ( !IsRunning () ) {
			// suspended. try to run out
			m_flags.SetFlags (FLG_THRD_RUNOUT);
			while ( ::ResumeThread (GetHandle ()) != ((DWORD) -1) ) {
				--m_dwSuspendCount;
			}
		}
		m_csControl.Leave ();
		OnQueryThreadTermination ();
		switch ( Wait (dwTimeout) ) {
		case WAIT_OBJECT_0:	// thread terminated!
			return TRUE;
		case WAIT_TIMEOUT:	// thread already running
			if ( OnHardThreadTermination () ) {
				// hard kill requested!
				m_dwExitCode = (DWORD) dwExitCode;
				TerminateThread (GetHandle (), m_dwExitCode);
				Close ();
				if ( m_flags.TestFlags (FLG_THRD_DIRTY) ) {
					// The critical section CAN be corrupted here.
					// Let's try to repair it...
					m_csControl.Recreate ();
				}
				return TRUE;
			}
			return FALSE;
		default:
			// handle problably not valid...
			SetLastError (ERROR_INVALID_HANDLE);
			return FALSE;
		}
	}
}

BOOL YWorkerThread::Suspend ()
{
	YSingleGuard	sg(&m_csControl, TRUE);

	if ( IsThis () ) {
		SetLastError (ERROR_ALREADY_EXISTS);
		return FALSE;
	}
	if ( !IsValid () ) {
		SetLastError (ERROR_INVALID_HANDLE);
		return FALSE;
	}
	DWORD dwRet;
	if ( (dwRet = ::SuspendThread (GetHandle ())) == (DWORD) -1 ) {
		SetLastSysError ();
		return FALSE;
	}
	else {
		m_dwSuspendCount	= dwRet + 1;
		SetLastError (NOERROR);
		return TRUE;
	}
}

BOOL YWorkerThread::Resume ()
{
	YSingleGuard	sg(&m_csControl, TRUE);

	if ( IsThis () ) {
		SetLastError (ERROR_ALREADY_EXISTS);
		return FALSE;
	}
	if ( !IsValid () ) {
		SetLastError (ERROR_INVALID_HANDLE);
		return FALSE;
	}
	DWORD dwRet;
	if ( (dwRet = ::ResumeThread (GetHandle ())) == (DWORD) -1 ) {
		SetLastSysError ();
		return FALSE;
	}
	else {
		m_dwSuspendCount	= (dwRet) ? (dwRet - 1) : (0);
		SetLastError (NOERROR);
		return TRUE;
	}
}

void YWorkerThread::pCommonConstructor ()
{
	SetLastError (NOERROR);

	m_flags.Set (0);
	m_hHandle			= INVALID_HANDLE_VALUE;
	m_uThreadID			= 0;
	m_dwSuspendCount	= 0;
	m_dwExitCode		= 0;
}

extern "C" static unsigned __stdcall _yLibThread (void *pParam)
{
	YWorkerThread *pThread = (YWorkerThread *) pParam;

	pThread->m_csControl.Enter ();
	if ( pThread->TestFlags (FLG_THRD_RUNOUT) ) {
		pThread->m_csControl.Leave ();
		return 0;
	}
	pThread->m_dwExitCode = 0;
	pThread->SetFlags (FLG_THRD_DIRTY);
	pThread->m_csControl.Leave ();
	if ( pThread && pThread->OnInitThread () ) {
		pThread->m_dwExitCode = (UINT) pThread->OnRunThread ();
		pThread->OnExitThread (TRUE);
	}
	pThread->m_csControl.Enter ();
	pThread->ClearFlags (FLG_THRD_DIRTY);
	pThread->m_flags.SetFlags (FLG_THRD_FINISHED);
	pThread->m_csControl.Leave ();
	return pThread->m_dwExitCode;
}

#ifndef YLB_ENABLE_INLINE
#include "YThread.inl"
#endif


/// RCS STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EOF
////////