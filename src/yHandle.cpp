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
 * FILENAME		:	yHandle.cpp
 * PURPOSE		:	Implementation of the generic handle class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:05:01  leo
 * Initial revision
 *
 *============================================================================*/

#include "StdInc.hpp"

/*=============================================================================
 * THE BASE HANDLE
 *============================================================================*/
// flags
DWORD YBaseHandle::FLG_SYN_CRITICALSECT	= 0x00000001;
DWORD YBaseHandle::FLG_SYN_EVENT		= 0x00000002;
DWORD YBaseHandle::FLG_SYN_SEMAPHORE	= 0x00000004;
DWORD YBaseHandle::FLG_SYN_MUTEX		= 0x00000008;
DWORD YBaseHandle::FLG_PRC_THREAD		= 0x00000010;
DWORD YBaseHandle::FLG_PRC_PROCESS		= 0x00000020;
DWORD YBaseHandle::FLG_DAT_FILE			= 0x00000040;
DWORD YBaseHandle::FLG_DAT_CLIENTNP		= 0x00000080;
DWORD YBaseHandle::FLG_DAT_SERVERNP		= 0x00000100;
DWORD YBaseHandle::FLG_DAT_CLIENTMS		= 0x00000200;
DWORD YBaseHandle::FLG_DAT_SERVERMS		= 0x00000400;
// masks
DWORD YBaseHandle::MSK_SYNC				= 0x0000000f;
DWORD YBaseHandle::MSK_PROCESS			= 0x00000030;
DWORD YBaseHandle::MSK_DATA				= 0x000007c0;
DWORD YBaseHandle::MSK_TYPES			= 0x000007ff;
DWORD YBaseHandle::MSK_WAITABLE			= 0x000007fe;

HANDLE YHandle::Duplicate (HANDLE hSourceProcessHandle, HANDLE hTargetProcessHandle, BOOL bInheritHandle, DWORD dwDesiredAccess, DWORD dwOptions) const
{
	HANDLE	hReturn;

	if ( ::DuplicateHandle (hSourceProcessHandle, m_hHandle, hTargetProcessHandle, &hReturn, dwDesiredAccess, bInheritHandle, dwOptions) ) {
		return hReturn;
	}
	return INVALID_HANDLE_VALUE;
}

BOOL YHandle::Close ()
{
	if ( IsValid () ) {
		BOOL bRet = ::CloseHandle (m_hHandle);
		m_hHandle = INVALID_HANDLE_VALUE;
		return bRet;
	}
	return TRUE;
}

#ifndef YLB_ENABLE_INLINE
#include <yHandle.inl>
#endif

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////