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
 * FILENAME		:	yMailSlots.inl
 * PURPOSE		:	Inline members of the mailslot classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yMailSlots.h
 *============================================================================*/

/*=============================================================================
 * MAILSLOT BASE CLASS
 *============================================================================*/
YLB_INLINE YMailslot::YMailslot ()
{
}

YLB_INLINE BOOL YMailslot::Unlock ()
{
	return TRUE;
}

YLB_INLINE BOOL YMailslot::Unlock (LONG lCount, LPLONG lpPrevCount)
{
	return TRUE;
}

/*=============================================================================
 * SERVER MAILSLOT
 *============================================================================*/
YLB_INLINE YServerMailslot::YServerMailslot ()
{
	SetFlags (FLG_DAT_SERVERMS);
}

YLB_INLINE BOOL YServerMailslot::GetMailslotInfo (LPDWORD lpMaxMessageSize, LPDWORD lpNextSize, LPDWORD lpMessageCount, LPDWORD lpReadTimeout) const
{
	return ::GetMailslotInfo (m_hHandle, lpMaxMessageSize, lpNextSize, lpMessageCount, lpReadTimeout);
}

YLB_INLINE BOOL YServerMailslot::SetMailslotInfo (DWORD dwReadTimeout) const
{
	return ::SetMailslotInfo (m_hHandle, dwReadTimeout);
}

/*=============================================================================
 * CLIENT MAILSLOT
 *============================================================================*/
YLB_INLINE YClientMailslot::YClientMailslot ()
{
	SetFlags (FLG_DAT_CLIENTMS);
}


//
// EoF
////////