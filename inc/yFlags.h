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
 * FILENAME		:	yFlags.h
 * PURPOSE		:	Declaration of the flags class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yFlags.h
 *============================================================================*/
#ifndef __yFlags_h__
#define __yFlags_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yLibBase_h__
#include <yLibBase.h>
#endif

/*=============================================================================
 * TYPES
 *============================================================================*/
typedef enum {			// @enum FLG_TEST_MODE | Flag testing mode
	FLG_AND,			// @emem Tests for all flags
	FLG_OR,				// @emem Tests for any flag
	FLG_XOR				// @emem ????
} FLG_TEST_MODE;

// @class Flag storage class
// @comm This class implements the storage and method handling for 32 bit
//		wide bitfields.
class YFlags
{
public:
	// @cmember Constructs a YFlags object
	YFlags				(DWORD defaultState = 0);

	// @cmember Sets the bitfield
	DWORD				Set				(DWORD flag);
	// @cmember Gets the bitfield
	DWORD				Get				(void) const;
	// @cmember Sets one or more bits in the bitfield
	DWORD				SetFlags		(DWORD flag);
	// @cmember Clears one or more bits in the bitfield
	DWORD				ClearFlags		(DWORD flag = ~(DWORD)0);
	// @cmember Modifies one or more bits in the bitfield
	DWORD				ChangeFlags		(DWORD flag, BOOL setState);
	// @cmember Tests for one or more bits in the bitfield
	BOOL				TestFlags		(DWORD flag, FLG_TEST_MODE mode = FLG_AND) const;

	// @cmember Tests and resets one or more bits in the bitfield
	BOOL				TestClearFlags	(DWORD flag);
	// @cmember Tests and sets one or more bits in the bitfield
	BOOL				TestSetFlags	(DWORD flag);
	
	// @cmember Compares two bitfields
	BOOL				operator==		(YFlags&) const;
	// @cmember Compares two bitfields
	BOOL				operator==		(DWORD flags) const;
	// @cmember Compares two bitfields
	BOOL				operator!=		(YFlags&) const;
	// @cmember Compares two bitfields
	BOOL				operator!=		(DWORD flags) const;
	// @cmember Casting operator
	operator			DWORD			() const;


	// @cmember Compares two bitfields
	BOOL				CompareFlags	(DWORD mask, DWORD flags) const;
	// @cmember Compares two bitfields
	BOOL				CompareFlags	(DWORD mask, YFlags& other) const;

private:
	DWORD				_state;
};

// @class Flag storage class
// @comm This class implements the storage and method handling for 32 bit
//		wide bitfields.
class YWideFlags
{
public:
	// @cmember Constructs a YWideFlags object
	YWideFlags			(DWORDLONG defaultState = 0);

	// @cmember Sets the bitfield
	DWORDLONG			Set				(DWORDLONG flag);
	// @cmember Gets the bitfield
	DWORDLONG			Get				(void) const;
	// @cmember Sets one or more bits in the bitfield
	DWORDLONG			SetFlags		(DWORDLONG flag);
	// @cmember Clears one or more bits in the bitfield
	DWORDLONG			ClearFlags		(DWORDLONG flag = ~(DWORDLONG)0);
	// @cmember Modifies one or more bits in the bitfield
	DWORDLONG			ChangeFlags		(DWORDLONG flag, BOOL setState);
	// @cmember Tests for one or more bits in the bitfield
	BOOL				TestFlags		(DWORDLONG flag, FLG_TEST_MODE mode = FLG_AND) const;

	// @cmember Tests and resets one or more bits in the bitfield
	BOOL				TestClearFlags	(DWORDLONG flag);
	// @cmember Tests and sets one or more bits in the bitfield
	BOOL				TestSetFlags	(DWORDLONG flag);
	
	// @cmember Compares two bitfields
	BOOL				operator==		(YWideFlags&) const;
	// @cmember Compares two bitfields
	BOOL				operator==		(DWORDLONG flags) const;
	// @cmember Compares two bitfields
	BOOL				operator!=		(YWideFlags&) const;
	// @cmember Compares two bitfields
	BOOL				operator!=		(DWORDLONG flags) const;
	// @cmember Casting operator
	operator			DWORDLONG			() const;


	// @cmember Compares two bitfields
	BOOL				CompareFlags	(DWORDLONG mask, DWORDLONG flags) const;
	// @cmember Compares two bitfields
	BOOL				CompareFlags	(DWORDLONG mask, YWideFlags& other) const;

private:
	DWORDLONG			_state;
};
//
// @xref <j Needful Things>

#ifdef YLB_ENABLE_INLINE
#include <yFlags.inl>
#endif

#endif //__yFlags_h__

//
// EoF
////////
