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
 * FILENAME		:	ySync.inl
 * PURPOSE		:	Inline members of the synchronisation classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:03:35  leo
 * Initial revision
 *
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