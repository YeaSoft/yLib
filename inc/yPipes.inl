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
 * FILENAME		:	yPipes.inl
 * PURPOSE		:	Inline members of the data pipe classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yPipes.h
 *============================================================================*/

/*=============================================================================
 * PIPE BASE CLASS
 *============================================================================*/
YLB_INLINE YPipe::YPipe ()
{
}

YLB_INLINE BOOL YPipe::Unlock ()
{
	return TRUE;
}

YLB_INLINE BOOL YPipe::Unlock (LONG lCount, LPLONG lpPrevCount)
{
	return TRUE;
}

/*=============================================================================
 * NAMED PIPE BASE CLASS
 *============================================================================*/
YLB_INLINE YNamedPipe::YNamedPipe ()
{
}

YLB_INLINE BOOL YNamedPipe::SetPipeMode (DWORD dwMode) const
{
	return SetHandleState (&dwMode);
}

YLB_INLINE BOOL YNamedPipe::SetPipeCollectionParams	(DWORD dwMaxCollectionCount, DWORD dwCollectDataTimeout) const
{
	return SetHandleState (NULL, &dwMaxCollectionCount, &dwCollectDataTimeout);
}

/*=============================================================================
 * SERVER NAMED PIPE
 *============================================================================*/
YLB_INLINE YServerNamedPipe::YServerNamedPipe ()
{
	SetFlags (FLG_DAT_SERVERNP);
}

YLB_INLINE BOOL YServerNamedPipe::Connect (LPOVERLAPPED lpOverlapped /* = NULL */) const
{
	ASSERTY(IsValid());
	return ::ConnectNamedPipe (m_hHandle, lpOverlapped);
}

YLB_INLINE BOOL YServerNamedPipe::Disconnect () const
{
	ASSERTY(IsValid());
	return ::DisconnectNamedPipe (m_hHandle);
}

YLB_INLINE BOOL YServerNamedPipe::Unlock ()
{
	return TRUE;
}

/*=============================================================================
 * CLIENT NAMED PIPE
 *============================================================================*/
YLB_INLINE YClientNamedPipe::YClientNamedPipe ()
{
	SetFlags (FLG_DAT_CLIENTNP);
}

YLB_INLINE BOOL YClientNamedPipe::Call (LPCTSTR pszPipeName, LPVOID lpInBuffer, DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesRead, DWORD nTimeOut)
{
	if ( !IsValidPipeName (pszPipeName) ) {
		return FALSE;
	}
	return ::CallNamedPipe (pszPipeName, lpInBuffer, nInBufferSize, lpOutBuffer, nOutBufferSize, lpBytesRead, nTimeOut);
}

YLB_INLINE BOOL YClientNamedPipe::Call (LPCTSTR pszName, LPCTSTR pszComputer, LPVOID lpInBuffer, DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesRead, DWORD nTimeOut)
{
	TCHAR	szPipeName[MAX_PATH];
	_stprintf (szPipeName, _T("\\\\%s\\pipe\\%s"), (pszComputer && *pszComputer) ? (pszComputer) : (_T(".")), pszName);
	return ::CallNamedPipe (szPipeName, lpInBuffer, nInBufferSize, lpOutBuffer, nOutBufferSize, lpBytesRead, nTimeOut);
}

YLB_INLINE BOOL YClientNamedPipe::WaitNamedPipe (LPCTSTR pszPipeName, DWORD nTimeOut)
{
	if ( !IsValidPipeName (pszPipeName) ) {
		return FALSE;
	}
	return ::WaitNamedPipe (pszPipeName, nTimeOut);
}

YLB_INLINE BOOL YClientNamedPipe::WaitNamedPipe (LPCTSTR pszName, LPCTSTR pszComputer, DWORD nTimeOut)
{
	TCHAR	szPipeName[MAX_PATH];
	_stprintf (szPipeName, _T("\\\\%s\\pipe\\%s"), (pszComputer && *pszComputer) ? (pszComputer) : (_T(".")), pszName);
	return ::WaitNamedPipe (szPipeName, nTimeOut);
}

YLB_INLINE BOOL YClientNamedPipe::Transact (LPCVOID lpInBuffer, DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesRead, LPOVERLAPPED lpOverlapped) const
{
	if ( !IsValid () ) {
		return FALSE;
	}
	return ::TransactNamedPipe (m_hHandle, (LPVOID) lpInBuffer, nInBufferSize, lpOutBuffer, nOutBufferSize, lpBytesRead, lpOverlapped);
}

//
// EoF
////////