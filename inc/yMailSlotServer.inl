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
 * FILENAME		:	yMailSlotServer.inl
 * PURPOSE		:	Inline members of the mailslot server class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:03:20  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yMailSlotServer.h
 *============================================================================*/
YLB_INLINE YMailslotServer::~YMailslotServer ()
{
	Deallocate ();
}

YLB_INLINE LPCTSTR YMailslotServer::GetMailslotName () const
{
	return m_szMailslotName;
}

YLB_INLINE BOOL YMailslotServer::SetMailslotName (LPCTSTR pszMailslotName)
{
	if ( IsValid () ) {
		return FALSE;
	}
	_tcsncpy (m_szMailslotName, pszMailslotName, _countof (m_szMailslotName));
	return *m_szMailslotName != 0;
}

YLB_INLINE UINT YMailslotServer::GetTimer () const
{
	return m_nTimer;
}

YLB_INLINE void YMailslotServer::SetTimer (UINT nTimer)
{
	m_nTimer = (nTimer) ? (nTimer) : (INFINITE);
}

YLB_INLINE DWORD YMailslotServer::GetMaxMessageSize () const
{
	return m_dwMaxMessageSize;
}

YLB_INLINE BOOL YMailslotServer::SetMaxMessageSize (DWORD dwMaxMessageSize)
{
	if ( IsValid () ) {
		return FALSE;
	}
	m_dwMaxMessageSize = dwMaxMessageSize;
	return TRUE;
}

YLB_INLINE DWORD YMailslotServer::GetReadTimeout () const
{
	return m_dwReadTimeout;
}

YLB_INLINE BOOL YMailslotServer::SetReadTimeout (DWORD dwReadTimeout)
{
	if ( IsValid () ) {
		return FALSE;
	}
	m_dwReadTimeout = dwReadTimeout;
	return TRUE;
}

YLB_INLINE UINT YMailslotServer::GetReadBufferSize () const
{
	return m_cbReadBufferSize;
}

YLB_INLINE BOOL YMailslotServer::SetReadBufferSize (UINT cbReadBufferSize)
{
	if ( IsValid () ) {
		return FALSE;
	}
	m_cbReadBufferSize = cbReadBufferSize;
	return m_cbReadBufferSize != 0;
}

YLB_INLINE LPSECURITY_ATTRIBUTES YMailslotServer::GetSecurityAttributes () const
{
	return m_lpSecurityAttributes;
}

YLB_INLINE BOOL YMailslotServer::SetSecurityAttributes (LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
	if ( IsValid () ) {
		return FALSE;
	}
	m_lpSecurityAttributes = lpSecurityAttributes;
	return TRUE;
}

YLB_INLINE BOOL YMailslotServer::Unlock ()
{
	return TRUE;
}

YLB_INLINE void YMailslotServer::OnQueryThreadTermination ()
{
	 m_evTerm.SetEvent ();
}

YLB_INLINE void YMailslotServer::OnExitThread (BOOL bRegularExit)
{
	Deallocate ();
}

YLB_INLINE void YMailslotServer::OnTimer ()
{
}

YLB_INLINE void YMailslotServer::OnReceive (LPVOID lpData, UINT cbData)
{
}

YLB_INLINE void YMailslotServer::OnFatalError (DWORD dwError)
{
}

//
// EoF
////////