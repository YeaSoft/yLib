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
 * FILENAME		:	yPipes.inl
 * PURPOSE		:	Inline members of the data pipe classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:03:22  leo
 * Initial revision
 *
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