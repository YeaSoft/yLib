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
 * FILENAME		:	yMailSlots.h
 * PURPOSE		:	Declaration of the mailslot classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:03:17  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yMailSlots.h
 *============================================================================*/
#ifndef __yMailSlots_h__
#define __yMailSlots_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yHandle_h__
#include <yHandle.h>
#endif

/*=============================================================================
 * FORWARD CLASS DECLARATIONS
 *============================================================================*/
class YMailslot;
	class YServerMailslot;
	class YClientMailslot;

/*=============================================================================
 * CLASS DECLARATIONS
 *============================================================================*/
class YMailslot : public YDataHandle
{
private:
	// kill these construction methods & operators
	YMailslot					(const YMailslot &);
	YMailslot					&operator=				(const YMailslot &);

public:
	// construction
	YMailslot					();

public:
	// operations
	virtual BOOL				Unlock					();
	virtual BOOL				Unlock					(LONG lCount, LPLONG lpPrevCount = NULL);

	void						Attach					(HANDLE hMailSlot);
};

class YServerMailslot : public YMailslot
{
private:
	// kill these construction methods & operators
	YServerMailslot				(const YServerMailslot &);
	YServerMailslot				&operator=				(const YServerMailslot &);

public:
	// construction
	YServerMailslot				();

public:
	// operations
	BOOL						Create					(
														LPCTSTR pszName,
														DWORD dwMaxMessageSize = 0,
														DWORD dwReadTimeout = MAILSLOT_WAIT_FOREVER,
														LPSECURITY_ATTRIBUTES lpSecurityAttributes = NULL
														);
public:
	// attributes
	BOOL						GetMailslotInfo			(
														LPDWORD lpMaxMessageSize = NULL,
														LPDWORD lpNextSize = NULL,
														LPDWORD lpMessageCount = NULL,
														LPDWORD lpReadTimeout = NULL
														) const;
	BOOL						SetMailslotInfo			(DWORD dwReadTimeout) const;
};

class YClientMailslot : public YMailslot
{
private:
	// kill these construction methods & operators
	YClientMailslot				(const YClientMailslot &);
	YClientMailslot				&operator=				(const YClientMailslot &);

public:
	// construction
	YClientMailslot				();

public:
	// operations
	BOOL						Create					(LPCTSTR pszMailslotName, LPSECURITY_ATTRIBUTES lpSecurityAttributes = NULL);
	BOOL						Create					(LPCTSTR pszName, LPCTSTR pszComputer, LPSECURITY_ATTRIBUTES lpSecurityAttributes = NULL);

public:
	// attributes
	static BOOL					IsValidMailslotName		(LPCTSTR lpFileName);
};

#ifdef YLB_ENABLE_INLINE
#include <yMailSlots.inl>
#endif

#endif //__yMailSlots_h__
//
// EoF
////////