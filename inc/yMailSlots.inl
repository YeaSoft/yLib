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
 * FILENAME		:	yMailSlots.inl
 * PURPOSE		:	Inline members of the mailslot classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:03:18  leo
 * Initial revision
 *
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