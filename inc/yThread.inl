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
 * FILENAME		:	yThread.inl
 * PURPOSE		:	Inline members of the thread class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yThread.h
 *============================================================================*/
// @mfunc	Constructs a <c YThread> object
// @xref	<c YThread>, <j System Handles>
YLB_INLINE YThread::YThread ()
{
	SetFlags (FLG_PRC_THREAD);
}

// @mfunc	Attaches a thread handle
// @parm	DWORD | flag | The new mask of bits
// @comm	Use this member function to attach a thread handle to the
//			<c YThread> object. If the <c YThread> has already a handle
//			attached, this will be closed.
// @xref	<mf YHandle::Detach>, <c YThread>
YLB_INLINE void YThread::Attach (HANDLE hThread)
{
	if ( hThread != m_hHandle ) {
		Close ();
	}
	m_hHandle = hThread;
}

// @mfunc	Retrieves the termination status of the thread.
// @parm	LPDWORD | lpdwExitCode | Pointer to a variable to receive the thread termination status.
// @rdesc	<TRUE> if the method succeeds, <FALSE> if not.
// @comm	If the specified thread has not terminated, the termination
//			status returned is <b>STILL_ACTIVE<n>. If the thread has
//			terminated, the termination status returned may be one of
//			the following:
//			<nl>The exit value specified in the ExitThread or TerminateThread function.
//			<nl>The return value from the thread function.
//			<nl>The exit value of the thread's process.
// @xref	<c YThread>
YLB_INLINE BOOL YThread::GetExitCode (LPDWORD lpdwExitCode) const
{
	ASSERTY(lpdwExitCode);
	if ( !IsValid () ) {
		return FALSE;
	}
	return ::GetExitCodeThread (m_hHandle, lpdwExitCode);
}

YLB_INLINE int YThread::GetPriority () const
{
	if ( !IsValid () ) {
		return -1;
	}
	return ::GetThreadPriority (m_hHandle);
}

YLB_INLINE BOOL YThread::SetPriority (int nPriority) const
{
	if ( !IsValid () ) {
		return -1;
	}
	return ::SetThreadPriority (m_hHandle, nPriority);
}

YLB_INLINE BOOL YThread::GetPriorityBoost (LPBOOL pbDisablePriorityBoost) const
{
	ASSERTY(pbDisablePriorityBoost);
	if ( !IsValid () ) {
		return FALSE;
	}
	return ::GetThreadPriorityBoost (m_hHandle, pbDisablePriorityBoost);
}

YLB_INLINE BOOL YThread::SetPriorityBoost (BOOL bDisablePriorityBoost) const
{
	if ( !IsValid () ) {
		return FALSE;
	}
	return ::SetThreadPriorityBoost (m_hHandle, bDisablePriorityBoost);
}

YLB_INLINE BOOL YThread::GetTimes (LPFILETIME lpCreationTime, LPFILETIME lpExitTime, LPFILETIME lpKernelTime, LPFILETIME lpUserTime) const
{
	ASSERTY(lpCreationTime);
	ASSERTY(lpExitTime);
	ASSERTY(lpKernelTime);
	ASSERTY(lpUserTime);
	if ( !IsValid () ) {
		return FALSE;
	}
	return ::GetThreadTimes (m_hHandle, lpCreationTime, lpExitTime, lpKernelTime, lpUserTime);
}

#if(_WIN32_WINNT >= 0x0500)

YLB_INLINE BOOL YThread::Open (DWORD dwThreadId, DWORD dwDesiredAccess /* = THREAD_ALL_ACCESS */, BOOL bInheritHandle /* = FALSE */)
{
	if ( !IsValid () ) {
		return FALSE;
	}
	HANDLE hThread = OpenThread (dwDesiredAccess, bInheritHandle, dwThreadId);
	if ( hThread ) {
		Close ();
		m_hHandle = hThread;
		return TRUE;
	}
	return FALSE;
}

#endif

YLB_INLINE DWORD YThread::Suspend () const
{
	if ( !IsValid () ) {
		return (DWORD) -1;
	}
	return ::SuspendThread (m_hHandle);
}

YLB_INLINE DWORD YThread::Resume () const
{
	if ( !IsValid () ) {
		return (DWORD) -1;
	}
	return ::ResumeThread (m_hHandle);
}

YLB_INLINE DWORD YThread::SetAffinityMask (DWORD dwThreadAffinityMask) const
{
	if ( !IsValid () ) {
		return 0;
	}
	return ::SetThreadAffinityMask (m_hHandle, dwThreadAffinityMask);
}

#if(_WIN32_WINNT >= 0x0400)

YLB_INLINE DWORD YThread::SetIdealProcessor (DWORD dwIdealProcessor /* = MAXIMUM_PROCESSORS */) const
{
	if ( !IsValid () ) {
		return (DWORD) -1;
	}
	return ::SetThreadIdealProcessor (m_hHandle, dwIdealProcessor);
}

#endif

YLB_INLINE BOOL YThread::Terminate (DWORD dwExitCode) const
{
	if ( !IsValid () ) {
		return (DWORD) -1;
	}
	return ::TerminateThread (m_hHandle, dwExitCode);
}


YLB_INLINE BOOL YThread::Unlock ()
{
	return TRUE;
}

YLB_INLINE BOOL YThread::Unlock (LONG lCount, LPLONG lpPrevCount /* = NULL */)
{
	return TRUE;
}

YLB_INLINE BOOL YWorkerThread::Open (DWORD dwThreadId, DWORD dwDesiredAccess /* = THREAD_ALL_ACCESS */, BOOL bInheritHandle /* = FALSE */)
{
	// NEVER EVER USE OPEN on a worker thread
	ASSERTY(FALSE);
	return FALSE;
}

YLB_INLINE BOOL YWorkerThread::Terminate (DWORD dwExitCode) const
{
	// NEVER EVER USE Terminate on a worker thread
	ASSERTY(FALSE);
	return FALSE;
}

YLB_INLINE BOOL YWorkerThread::PreCreateThread (BOOL &bSuspended, UINT &uStackSize, LPSECURITY_ATTRIBUTES &lpThreadAttributes)
{
	return TRUE;
}

YLB_INLINE BOOL YWorkerThread::OnInitThread ()
{
	return TRUE;
}

YLB_INLINE UINT YWorkerThread::OnRunThread ()
{
	return 0;
}

YLB_INLINE void YWorkerThread::OnExitThread (BOOL bRegularExit)
{
}

YLB_INLINE void YWorkerThread::OnQueryThreadTermination ()
{
}

YLB_INLINE BOOL YWorkerThread::OnHardThreadTermination ()
{
	return TRUE;
}

YLB_INLINE DWORD YWorkerThread::GetSuspendCount ()
{
	return m_dwSuspendCount;
}

YLB_INLINE BOOL YWorkerThread::IsRunning ()
{
	return m_dwSuspendCount == 0;
}

YLB_INLINE BOOL YWorkerThread::IsThis ()
{
	return m_uThreadID == ::GetCurrentThreadId ();
}

YLB_INLINE LPCTSTR YWorkerThread::GetName ()
{
	return m_szThreadName;
}

//
// EoF
////////