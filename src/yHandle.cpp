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
 * FILENAME		:	yHandle.cpp
 * PURPOSE		:	Implementation of the generic handle class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
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