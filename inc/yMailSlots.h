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
 * FILENAME		:	yMailSlots.h
 * PURPOSE		:	Declaration of the mailslot classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
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