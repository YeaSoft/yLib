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
 * FILENAME		:	ySync.inl
 * PURPOSE		:	Inline members of the synchronisation classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | ySync.h
 *============================================================================*/
YLB_INLINE YSemaphore::YSemaphore ()
{
	SetFlags (FLG_SYN_SEMAPHORE);
}

YLB_INLINE BOOL YSemaphore::Unlock ()
{
	return Unlock (1, NULL);
}

YLB_INLINE YMutex::YMutex ()
{
	SetFlags (FLG_SYN_MUTEX);
}

YLB_INLINE BOOL YMutex::Unlock ()
{
	ASSERTY(IsValid());
	return ::ReleaseMutex (m_hHandle);
}

YLB_INLINE YEvent::YEvent ()
{
	SetFlags (FLG_SYN_EVENT);
}

YLB_INLINE BOOL YEvent::SetEvent () const
{
	ASSERTY(IsValid());
	return ::SetEvent (m_hHandle);
}

YLB_INLINE BOOL YEvent::PulseEvent () const
{
	ASSERTY(IsValid());
	return ::PulseEvent (m_hHandle);
}

YLB_INLINE BOOL YEvent::ResetEvent () const
{
	ASSERTY(IsValid());
	return ::ResetEvent (m_hHandle);
}

YLB_INLINE BOOL YEvent::Unlock ()
{
	if ( m_bManualReset ) {
		return ResetEvent ();
	}
	return TRUE;
}

YLB_INLINE YCriticalSection::YCriticalSection ()
{
	::InitializeCriticalSection (&m_sect);
}

YLB_INLINE YCriticalSection::~YCriticalSection ()
{
	::DeleteCriticalSection (&m_sect);
}

YLB_INLINE YCriticalSection::operator CRITICAL_SECTION * ()
{
	return (CRITICAL_SECTION *) &m_sect;
}

YLB_INLINE void YCriticalSection::Recreate ()
{
	::DeleteCriticalSection (&m_sect);
	::InitializeCriticalSection (&m_sect);
}

YLB_INLINE void YCriticalSection::Enter ()
{
	::EnterCriticalSection (&m_sect);
}

YLB_INLINE void YCriticalSection::Leave ()
{
	::LeaveCriticalSection (&m_sect);
}

#if (_WIN32_WINNT >= 0x0400)
YLB_INLINE BOOL YCriticalSection::TryEnter ()
{
	return ::TryEnterCriticalSection (&m_sect);
}
#endif

YLB_INLINE BOOL YCriticalSection::Lock ()
{
	::EnterCriticalSection (&m_sect);
	return TRUE;
}

YLB_INLINE BOOL YCriticalSection::Lock (DWORD /* dwTimeout */)
{
	return Lock ();
}

YLB_INLINE BOOL YCriticalSection::Unlock ()
{
	::LeaveCriticalSection (&m_sect);
	return TRUE;
}

YLB_INLINE YSingleGuard::~YSingleGuard ()
{
	Unlock ();
}

YLB_INLINE BOOL YSingleGuard::IsLocked ()
{
	return m_bAcquired;
}

YLB_INLINE YMultiGuard::YMultiGuard ()
{
	CleanObjects ();
}

YLB_INLINE YMultiGuard::~YMultiGuard ()
{
	Unlock ();
}

YLB_INLINE BOOL YMultiGuard::AddObject (YSyncHandle &shObject)
{
	return AddObject (&shObject);
}

YLB_INLINE void YMultiGuard::CleanObjects ()
{
	m_dwCount = 0;
}

YLB_INLINE DWORD YMultiGuard::Wait (DWORD dwTimeOut /* = INFINITE */, BOOL bWaitForAll /* = TRUE */)
{
	return Lock (dwTimeOut, bWaitForAll);
}

YLB_INLINE BOOL YMultiGuard::IsLocked (DWORD dwObject)
{
	ASSERTY((dwObject >= 0) && (dwObject < m_dwCount));
	return m_bObjects[dwObject];
}

//
// EoF
////////