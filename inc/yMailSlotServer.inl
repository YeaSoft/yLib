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
 * FILENAME		:	yMailSlotServer.inl
 * PURPOSE		:	Inline members of the mailslot server class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
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