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
 * FILENAME		:	yFlags.h
 * PURPOSE		:	Declaration of the flags class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.2  2000/09/04 11:59:53  leopoldo
 * Updated license to zlib/libpng
 *
 * Revision 1.1  2000/05/26 14:03:09  leo
 * Initial revision
 *
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
//! Flag testing mode
/*!	This enumeration type is used to define the the testing mode for flags
	@see YFlags
 */
typedef enum {
	FLG_AND,			//!	Tests for all flags
	FLG_OR,				//!	Tests for any flag
	FLG_XOR				//! Tests that only one of the specified flags is set
} FLG_TEST_MODE;

//!	Flag storage class
/*!	This class implements the storage and method handling for 32 bit
	wide bitfields.
 */
class YFlags
{
public:
	//! Constructs a YFlags object
	YFlags				(DWORD defaultState = 0);

	//!  Sets the bitfield
	DWORD				Set				(DWORD flag);
	//!  Gets the bitfield
	DWORD				Get				(void) const;
	//!  Sets one or more bits in the bitfield
	DWORD				SetFlags		(DWORD flag);
	//!  Clears one or more bits in the bitfield
	DWORD				ClearFlags		(DWORD flag = ~(DWORD)0);
	//!  Masks one or more bits in the bitfield
	DWORD				MaskFlags		(DWORD flag);
	//!  Modifies one or more bits in the bitfield
	DWORD				ChangeFlags		(DWORD flag, BOOL setState);
	//!  Tests for one or more bits in the bitfield
	BOOL				TestFlags		(DWORD flag, FLG_TEST_MODE mode = FLG_AND) const;

	//!  Tests and resets one or more bits in the bitfield
	BOOL				TestClearFlags	(DWORD flag);
	//!  Tests and sets one or more bits in the bitfield
	BOOL				TestSetFlags	(DWORD flag);
	
	//!  Compares two bitfields
	BOOL				operator==		(YFlags&) const;
	//!  Compares two bitfields
	BOOL				operator==		(DWORD flags) const;
	//!  Compares two bitfields
	BOOL				operator!=		(YFlags&) const;
	//!  Compares two bitfields
	BOOL				operator!=		(DWORD flags) const;
	//!  Casting operator
	operator			DWORD			() const;


	//!  Compares two bitfields
	BOOL				CompareFlags	(DWORD mask, DWORD flags) const;
	//!  Compares two bitfields
	BOOL				CompareFlags	(DWORD mask, YFlags& other) const;

private:
	DWORD				_state;
};

//!	Flag storage class
/*!	This class implements the storage and method handling for 64 bit
	wide bitfields.
 */
class YWideFlags
{
public:
	//!  Constructs a YWideFlags object
	YWideFlags			(DWORDLONG defaultState = 0);

	//!  Sets the bitfield
	DWORDLONG			Set				(DWORDLONG flag);
	//!  Gets the bitfield
	DWORDLONG			Get				(void) const;
	//!  Sets one or more bits in the bitfield
	DWORDLONG			SetFlags		(DWORDLONG flag);
	//!  Clears one or more bits in the bitfield
	DWORDLONG			ClearFlags		(DWORDLONG flag = ~(DWORDLONG)0);
	//!  Masks one or more bits in the bitfield
	DWORDLONG			MaskFlags		(DWORDLONG flag);
	//!  Modifies one or more bits in the bitfield
	DWORDLONG			ChangeFlags		(DWORDLONG flag, BOOL setState);
	//!  Tests for one or more bits in the bitfield
	BOOL				TestFlags		(DWORDLONG flag, FLG_TEST_MODE mode = FLG_AND) const;

	//!  Tests and resets one or more bits in the bitfield
	BOOL				TestClearFlags	(DWORDLONG flag);
	//!  Tests and sets one or more bits in the bitfield
	BOOL				TestSetFlags	(DWORDLONG flag);
	
	//!  Compares two bitfields
	BOOL				operator==		(YWideFlags&) const;
	//!  Compares two bitfields
	BOOL				operator==		(DWORDLONG flags) const;
	//!  Compares two bitfields
	BOOL				operator!=		(YWideFlags&) const;
	//!  Compares two bitfields
	BOOL				operator!=		(DWORDLONG flags) const;
	//!  Casting operator
	operator			DWORDLONG			() const;


	//!  Compares two bitfields
	BOOL				CompareFlags	(DWORDLONG mask, DWORDLONG flags) const;
	//!  Compares two bitfields
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
