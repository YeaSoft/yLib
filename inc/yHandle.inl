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
 * FILENAME		:	yHandle.inl
 * PURPOSE		:	Inline members of the generic handle class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:03:12  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yHandle.h
 *============================================================================*/

/*=============================================================================
 * THE BASE HANDLE
 *============================================================================*/
YLB_INLINE YBaseHandle::YBaseHandle (HANDLE hHandle, DWORD dwType)
{
	m_hHandle = hHandle;
	Set (dwType);
}


YLB_INLINE YTransSemaphore::YTransSemaphore (HANDLE hHandle) : YBaseHandle (hHandle, FLG_SYN_SEMAPHORE)
{
}

YLB_INLINE YTransMutex::YTransMutex (HANDLE hHandle) : YBaseHandle (hHandle, FLG_SYN_MUTEX)
{
}

YLB_INLINE YTransEvent::YTransEvent (HANDLE hHandle) : YBaseHandle (hHandle, FLG_SYN_EVENT)
{
}

YLB_INLINE YTransThread::YTransThread (HANDLE hHandle) : YBaseHandle (hHandle, FLG_PRC_THREAD)
{
}

YLB_INLINE YTransProcess::YTransProcess (HANDLE hHandle) : YBaseHandle (hHandle, FLG_PRC_PROCESS)
{
}

YLB_INLINE YTransClientNamedPipe::YTransClientNamedPipe (HANDLE hHandle) : YBaseHandle (hHandle, FLG_DAT_CLIENTNP)
{
}

YLB_INLINE YTransServerNamedPipe::YTransServerNamedPipe (HANDLE hHandle) : YBaseHandle (hHandle, FLG_DAT_SERVERNP)
{
}

YLB_INLINE YTransClientMailslot::YTransClientMailslot (HANDLE hHandle) : YBaseHandle (hHandle, FLG_DAT_CLIENTMS)
{
}

YLB_INLINE YTransServerMailslot::YTransServerMailslot (HANDLE hHandle) : YBaseHandle (hHandle, FLG_DAT_SERVERMS)
{
}

YLB_INLINE YHandle::YHandle ()
{
}

YLB_INLINE YHandle::~YHandle ()
{
	Close ();
}

YLB_INLINE HANDLE YHandle::Duplicate (HANDLE hTargetProcessHandle, BOOL bInheritHandle, DWORD dwDesiredAccess, DWORD dwOptions) const
{
	return Duplicate (::GetCurrentProcess (), hTargetProcessHandle, bInheritHandle, dwDesiredAccess, dwOptions);
}

YLB_INLINE HANDLE YHandle::Duplicate (BOOL bInheritHandle, DWORD dwDesiredAccess, DWORD dwOptions) const
{
	return Duplicate (::GetCurrentProcess (), ::GetCurrentProcess (), bInheritHandle, dwDesiredAccess, dwOptions);
}

YLB_INLINE YHandle::operator HANDLE() const
{
	return m_hHandle;
}

YLB_INLINE HANDLE YHandle::GetHandle () const
{
	return m_hHandle;
}

YLB_INLINE BOOL YHandle::GetInformation (LPDWORD lpdwFlags) const
{
	return ::GetHandleInformation (m_hHandle, lpdwFlags);
}

YLB_INLINE BOOL YHandle::SetInformation (DWORD dwMask, DWORD dwFlags) const
{
	return ::SetHandleInformation (m_hHandle, dwMask, dwFlags);
}

YLB_INLINE BOOL YHandle::IsCriticalSection () const
{
	return TestFlags (FLG_SYN_CRITICALSECT);
}

YLB_INLINE BOOL YHandle::IsEvent () const
{
	return TestFlags (FLG_SYN_EVENT);
}

YLB_INLINE BOOL YHandle::IsSemaphore () const
{
	return TestFlags (FLG_SYN_SEMAPHORE);
}

YLB_INLINE BOOL YHandle::IsMutex () const
{
	return TestFlags (FLG_SYN_MUTEX);
}

YLB_INLINE BOOL YHandle::IsThread () const
{
	return TestFlags (FLG_PRC_THREAD);
}

YLB_INLINE BOOL YHandle::IsProcess () const
{
	return TestFlags (FLG_PRC_PROCESS);
}

YLB_INLINE BOOL YHandle::IsClientNamedPipe () const
{
	return TestFlags (FLG_DAT_CLIENTNP);
}

YLB_INLINE BOOL YHandle::IsServerNamedPipe () const
{
	return TestFlags (FLG_DAT_SERVERNP);
}

YLB_INLINE BOOL YHandle::IsClientMailslot () const
{
	return TestFlags (FLG_DAT_CLIENTMS);
}

YLB_INLINE BOOL YHandle::IsServerMailslot () const
{
	return TestFlags (FLG_DAT_SERVERMS);
}

YLB_INLINE BOOL YHandle::IsValid () const
{
	return m_hHandle != INVALID_HANDLE_VALUE;
}

YLB_INLINE BOOL YHandle::IsWaitable() const
{
	return TestFlags (MSK_WAITABLE, FLG_OR);
}

/*
YLB_INLINE YEvent * YHandle::GetEvent () const
{
	return (IsEvent ()) ? ((YEvent *) this) : (NULL);
}

YLB_INLINE YSemaphore * YHandle::GetSemaphore () const
{
	return (IsSemaphore ()) ? ((YSemaphore *) this) : (NULL);
}

YLB_INLINE YMutex * YHandle::GetMutex () const
{
	return (IsMutex ()) ? ((YMutex *) this) : (NULL);
}

YLB_INLINE YThread * YHandle::GetThread () const
{
	return (IsThread ()) ? ((YThread *) this) : (NULL);
}

YLB_INLINE YClientNamedPipe * YHandle::GetClientNamedPipe () const
{
	return (IsClientNamedPipe ()) ? ((YClientNamedPipe *) this) : (NULL);
}

YLB_INLINE YServerNamedPipe * YHandle::GetServerNamedPipe () const
{
	return (IsServerNamedPipe ()) ? ((YServerNamedPipe *) this) : (NULL);
}

YLB_INLINE YClientMailslot * YHandle::GetClientMailslot () const
{
	return (IsClientMailslot ()) ? ((YClientMailslot *) this) : (NULL);
}

YLB_INLINE YServerMailslot * YHandle::GetServerMailslot () const
{
	return (IsServerMailslot ()) ? ((YServerMailslot *) this) : (NULL);
}

*/

YLB_INLINE HANDLE YHandle::Detach ()
{
	HANDLE hReturn = m_hHandle;
	m_hHandle = INVALID_HANDLE_VALUE;
	return hReturn;
}

/*=============================================================================
 * SYNCHRONISABLE HANDLES
 *============================================================================*/
YLB_INLINE YSyncHandle::YSyncHandle ()
{
}

YLB_INLINE BOOL YSyncHandle::Lock (DWORD dwTimeout /* = INFINITE */)
{
	ASSERTY(IsValid() && IsWaitable());
	return (::WaitForSingleObject (m_hHandle, dwTimeout) == WAIT_OBJECT_0);
}

YLB_INLINE DWORD YSyncHandle::Wait (DWORD dwTimeout /* = INFINITE */)
{
	ASSERTY(IsValid() && IsWaitable());
	return ::WaitForSingleObject (m_hHandle, dwTimeout);
}

YLB_INLINE DWORD YSyncHandle::WaitEx (DWORD dwTimeout /* = INFINITE */, BOOL bAlertable /* = TRUE */)
{
	ASSERTY(IsValid() && IsWaitable());
	return ::WaitForSingleObjectEx (m_hHandle, dwTimeout, bAlertable);
}

YLB_INLINE BOOL YSyncHandle::Unlock (LONG lCount, LPLONG lpPrevCount /* = NULL */)
{
	return TRUE;
}

/*=============================================================================
 * NON SYNCHRONISABLE DATA DEVICE HANDLES
 *============================================================================*/
YLB_INLINE YSimpleDataHandle::YSimpleDataHandle ()
{
	m_dwBytesRead = m_dwBytesWritten = 0;
}

YLB_INLINE BOOL YSimpleDataHandle::Read (LPVOID lpBuffer, DWORD nNumberOfBytesToRead)
{
	return Read (lpBuffer, nNumberOfBytesToRead, &m_dwBytesRead);
}

YLB_INLINE BOOL YSimpleDataHandle::Read (LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead)
{
	ASSERTY(IsValid());
	return ::ReadFile (m_hHandle, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, NULL);
}

YLB_INLINE BOOL YSimpleDataHandle::Write (LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite)
{
	return Write (lpBuffer, nNumberOfBytesToWrite, &m_dwBytesWritten);
}

YLB_INLINE BOOL YSimpleDataHandle::Write (LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten)
{
	ASSERTY(IsValid());
	return ::WriteFile (m_hHandle, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, NULL);
}

YLB_INLINE DWORD YSimpleDataHandle::GetBytesRead () const
{
	return m_dwBytesRead;
}

YLB_INLINE DWORD YSimpleDataHandle::GetBytesWritten () const
{
	return m_dwBytesWritten;
}

/*=============================================================================
 * SYNCHRONISABLE DATA DEVICE HANDLES
 *============================================================================*/
YLB_INLINE YDataHandle::YDataHandle ()
{
}

YLB_INLINE BOOL YDataHandle::Read (LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped /* = NULL */)
{
	ASSERTY(IsValid());
	return ::ReadFile (m_hHandle, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
}

YLB_INLINE BOOL YDataHandle::Read (LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPOVERLAPPED lpOverlapped /* = NULL */)
{
	return Read (lpBuffer, nNumberOfBytesToRead, &m_dwBytesRead, lpOverlapped);
}

YLB_INLINE BOOL YDataHandle::Write (LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped /* = NULL */)
{
	ASSERTY(IsValid());
	return ::WriteFile (m_hHandle, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
}

YLB_INLINE BOOL YDataHandle::Write (LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPOVERLAPPED lpOverlapped /* = NULL */)
{
	return Write (lpBuffer, nNumberOfBytesToWrite, &m_dwBytesWritten, lpOverlapped);
}

YLB_INLINE BOOL YDataHandle::ReadEx (LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPOVERLAPPED lpOverlapped, LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	ASSERTY(IsValid());
	return ::ReadFileEx (m_hHandle, lpBuffer, nNumberOfBytesToRead, lpOverlapped, lpCompletionRoutine);
}

YLB_INLINE BOOL YDataHandle::WriteEx (LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPOVERLAPPED lpOverlapped, LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	ASSERTY(IsValid());
	return ::WriteFileEx (m_hHandle, lpBuffer, nNumberOfBytesToWrite, lpOverlapped, lpCompletionRoutine);
}

YLB_INLINE BOOL YDataHandle::GetOverlappedResult (LPOVERLAPPED lpOverlapped, LPDWORD lpNumberOfBytesTransferred, BOOL bWait) const
{
	ASSERTY(IsValid());
	return ::GetOverlappedResult (m_hHandle, lpOverlapped, lpNumberOfBytesTransferred, bWait);
}

//
// EoF
////////