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
 * FILENAME		:	yPipeServer.inl
 * PURPOSE		:	Inline members of the pipe server classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:03:24  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yPipeServer.h
 *============================================================================*/

/*=============================================================================
 * PIPE SERVER INSTANCE CLASSES
 *============================================================================*/
YLB_INLINE YPipeBaseInstance::YPipeBaseInstance ()
{
	m_pPipeServer;
}

YLB_INLINE YPipeBaseInstance::~YPipeBaseInstance ()
{
}

YLB_INLINE YPipeServer * YPipeBaseInstance::GetPipeServer () const
{
	return m_pPipeServer;
}

YLB_INLINE BOOL YPipeBaseInstance::InitInstance (UINT nInstanceNumber)
{
	return TRUE;
}

YLB_INLINE void YPipeBaseInstance::ExitInstance ()
{
}

YLB_INLINE void YPipeBaseInstance::OnConnect ()
{
}

YLB_INLINE void YPipeBaseInstance::OnTransact (LPVOID lpData, UINT cbData)
{
}

YLB_INLINE void YPipeBaseInstance::OnError ()
{
}

YLB_INLINE void YPipeBaseInstance::OnDisconnect ()
{
}

YLB_INLINE void YPipeBaseInstance::OnTerminate ()
{
}

YLB_INLINE YPipeInstance::YPipeInstance ()
{
}

YLB_INLINE YPipeInstance::~YPipeInstance ()
{
}

YLB_INLINE YAsyncPipeInstance::YAsyncPipeInstance ()
{
}

YLB_INLINE YAsyncPipeInstance::~YAsyncPipeInstance ()
{
}

/*=============================================================================
 * PIPE SERVER CLASS
 *============================================================================*/
YLB_INLINE YPipeServer::~YPipeServer ()
{
	Deallocate ();
}

YLB_INLINE LPCTSTR YPipeServer::GetPipeName () const
{
	return m_szPipeName;
}

YLB_INLINE BOOL YPipeServer::SetPipeName (LPCTSTR pszPipeName)
{
	if ( IsValid () ) {
		return FALSE;
	}
	_tcsncpy (m_szPipeName, pszPipeName, _countof (m_szPipeName));
	return *m_szPipeName != 0;
}

YLB_INLINE YRuntimeInfo * YPipeServer::GetInstanceInfo () const
{
	return m_pInstanceInfo;
}

YLB_INLINE BOOL YPipeServer::SetInstanceInfo (YRuntimeInfo *pInstance)
{
	if ( IsValid () ) {
		return FALSE;
	}
	m_pInstanceInfo = pInstance;
	return m_pInstanceInfo != NULL;
}

YLB_INLINE UINT YPipeServer::GetMaxInstances () const
{
	return m_nMaxInstances;
}

YLB_INLINE BOOL YPipeServer::SetMaxInstances (UINT nMaxInstances)
{
	if ( IsValid () ) {
		return FALSE;
	}
	m_nMaxInstances = nMaxInstances;
	return (m_nMaxInstances + m_nMaxProxies + 1) <= MAXIMUM_WAIT_OBJECTS;
}

YLB_INLINE UINT YPipeServer::GetMaxProxies () const
{
	return m_nMaxProxies;
}

YLB_INLINE BOOL YPipeServer::SetMaxProxies (UINT nMaxProxies)
{
	if ( IsValid () ) {
		return FALSE;
	}
	m_nMaxProxies = nMaxProxies;
	return (m_nMaxInstances + m_nMaxProxies + 1) <= MAXIMUM_WAIT_OBJECTS;
}

YLB_INLINE UINT YPipeServer::GetTimer () const
{
	return m_nTimer;
}

YLB_INLINE void YPipeServer::SetTimer (UINT nTimer)
{
	m_nTimer = (nTimer) ? (nTimer) : (INFINITE);
}

YLB_INLINE UINT YPipeServer::GetPipeTimeout () const
{
	return m_nPipeTimeout;
}

YLB_INLINE void YPipeServer::SetPipeTimeout (UINT nPipeTimeout)
{
	m_nPipeTimeout = nPipeTimeout;
}

YLB_INLINE UINT YPipeServer::GetReadBufferSize () const
{
	return m_cbReadBufferSize;
}

YLB_INLINE BOOL YPipeServer::SetReadBufferSize (UINT cbReadBufferSize)
{
	if ( IsValid () ) {
		return FALSE;
	}
	m_cbReadBufferSize = cbReadBufferSize;
	return m_cbReadBufferSize >= 16;
}

YLB_INLINE UINT YPipeServer::GetWriteBufferSize () const
{
	return m_cbWriteBufferSize;
}

YLB_INLINE BOOL YPipeServer::SetWriteBufferSize (UINT cbWriteBufferSize)
{
	if ( IsValid () ) {
		return FALSE;
	}
	m_cbWriteBufferSize = cbWriteBufferSize;
	return m_cbWriteBufferSize > 16;
}

YLB_INLINE LPSECURITY_ATTRIBUTES YPipeServer::GetSecurityAttributes () const
{
	return m_lpSecurityAttributes;
}

YLB_INLINE BOOL YPipeServer::SetSecurityAttributes (LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
	if ( IsValid () ) {
		return FALSE;
	}
	m_lpSecurityAttributes = lpSecurityAttributes;
	return TRUE;
}

YLB_INLINE BOOL YPipeServer::Unlock ()
{
	return TRUE;
}

YLB_INLINE void YPipeServer::OnTimer ()
{
}

YLB_INLINE void YPipeServer::OnProxy (UINT nProxyNumber)
{
}

YLB_INLINE void YPipeServer::OnQueryThreadTermination ()
{
	 m_evTerm.SetEvent ();
}

YLB_INLINE void YPipeServer::OnExitThread (BOOL bRegularExit)
{
	Deallocate ();
}

//
// EoF
////////