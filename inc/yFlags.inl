/*=============================================================================
 * This is a part of the yLib Software Development Kit.
 * Copyright (C) 1998-1999 YEAsoft Inc.
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
 * FILENAME		:	yFlags.inl
 * PURPOSE		:	Inline members of the flags class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yFlags.h
 *============================================================================*/

// @mfunc Constructs a <c YFlags> object
// @parm DWORD | defaultState = 0 | Default initialisation of the bitfield
// @xref <c YFlags>, <j Needful Things>
YLB_INLINE YFlags::YFlags (DWORD defaultState)
{
	_state = defaultState;
}

// @mfunc Set the internal state mask
// @parm DWORD | flag | The new mask of bits
// @xref <mf YFlags::Get>, <c YFlags>
YLB_INLINE DWORD YFlags::Set(DWORD flag)
{
	_state = flag;
	return _state;
}

// @mfunc Retrieve  the internal state mask
// @rdesc The current mask of bits
// @xref <mf YFlags::Set>, <c YFlags>
YLB_INLINE DWORD YFlags::Get(void) const
{
	return _state;
}

// @mfunc Set the bits of a flag mask in the internal state mask
// @rdesc The modified state mask
// @xref <mf YFlags::ClearFlags>, <mf YFlags::ChangeFlags>, <c YFlags>
YLB_INLINE DWORD YFlags::SetFlags(DWORD flag)
{
	_state |= flag;
	return _state;
}

// @mfunc Clear the bits of a flag mask in the internal state mask
// @parm DWORD | flag = ~(DWORD)0 | Flag mask to clear
// @rdesc The modified state mask
// @xref <mf YFlags::SetFlags>, <mf YFlags::ChangeFlags>, <c YFlags>
YLB_INLINE DWORD YFlags::ClearFlags(DWORD flag)
{	
	_state &= ~flag;
	return _state;
}

// @mfunc Set or clear the bits of a flag mask in the internal state mask
// @parm DWORD | flag | Flag mask to set or clear
// @parm BOOL | setState | If <TRUE> the bits in <p flag> will be set
//		otherwise they will be cleared
// @rdesc The modified state mask
// @xref <mf YFlags::SetFlags>, <mf YFlags::ClearFlags>, <c YFlags>
YLB_INLINE DWORD YFlags::ChangeFlags(DWORD flag, BOOL setState)
{
	return (setState ? SetFlags(flag) : ClearFlags(flag));
}

// @mfunc Test the bits of a flag mask against the internal state mask
// @parm DWORD | flag | Flag mask to test
// @parm FLG_TEST_MODE | mode = FLG_AND | Testing mode (see <t FLG_TEST_MODE>)
// @rdesc <TRUE> if all bits of the flag mask are set in the internal
//		state mask if <e FLG_TEST_MODE.FLG_AND> was set, <TRUE> if any
//		of the bits is set in the internal state mask if <e FLG_TEST_MODE.FLG_OR>
//		was set.
// @xref <mf YFlags::TestSetFlags>, <mf YFlags::TestClearFlags>, <c YFlags>
YLB_INLINE BOOL YFlags::TestFlags(DWORD flag, FLG_TEST_MODE mode) const
{
	DWORD x = _state & flag;
	BOOL result;
	switch ( mode ) {
	case FLG_AND:
		result =  (x == flag);
		break;
	case FLG_OR:
		result =  (x != 0);
		break;
	case FLG_XOR:
		if ( x == 0 ) {
			result = FALSE;
		}
		else if ( x == 1 ) {
			result = TRUE;
		}
		else {	
			div_t dresult;
			dresult.quot = x;
			do {
				dresult = div(dresult.quot,2);
			} while (dresult.rem == 0);
			result = (dresult.quot == 0);
		}
		break;
	default:
		result = FALSE;
		break;
	}
	return result;
}

// @mfunc Tests and resets one or more bits in the internal state mask
// @parm DWORD | flag | The flag mask to test and reset
// @comm Test the bits of a flag mask against the internal state mask.
//		Clear the bits set in the flag mask in the internal state mask
//		If the flag mask more than one bit set the return value is the
//		logical <b>AND<n> operation of all the single bit state tests.
// @rdesc <TRUE> if all bits of flag mask are set in the internal state mask
// @xref <mf YFlags::TestSetFlags>, <mf YFlags::TestFlags>, <c YFlags>
YLB_INLINE BOOL YFlags::TestClearFlags(DWORD flag)
{
	BOOL result = ((_state & flag) == flag);
	ClearFlags(flag);
	return result;
}

// @mfunc Tests and sets one or more bits in the internal state mask
// @parm DWORD | flag | The flag mask to test and set
// @comm Test the bits of a flag mask against the internal state mask.
//		Set the bits set in the flag mask in the internal state mask.
//		If the flag mask more than one bit set the return value is the
//		logical <b>AND<n> operation of all the single bit state tests.
// @rdesc <TRUE> if all bits of flag mask are set in the internal state mask
// @xref <mf YFlags::TestClearFlags>, <mf YFlags::TestFlags>, <c YFlags>
YLB_INLINE BOOL YFlags::TestSetFlags(DWORD flag)
{
	BOOL result = ((_state & flag) == flag);
	SetFlags(flag);
	return result;
}

// @mfunc Compare two bit fields
// @parm YFlags& | other | The state mask to compare with
// @rdesc <TRUE> if all bits of <p other> are equal in the internal
//		state mask
// @xref <mf YFlags::CompareFlags>, <mf YFlags::operator!=>, <c YFlags>
YLB_INLINE BOOL YFlags::operator==(YFlags& other) const
{
	return (_state == other.Get());
}

// @mfunc Compare two bit fields
// @parm YFlags& | other | The state mask to compare with
// @rdesc <TRUE> if any bits of <p other> are different in the internal
//		state mask
// @xref <mf YFlags::operator==>, <mf YFlags::CompareFlags>, <c YFlags>
YLB_INLINE BOOL YFlags::operator!=(YFlags& other) const
{
	return (_state != other.Get());
}

// @mfunc Compare two bit fields
// @parm DWORD | flags | The state mask to compare with
// @rdesc <TRUE> if all bits of <p flags> are equal in the internal
//		state mask
// @xref <mf YFlags::CompareFlags>, <mf YFlags::operator!=>, <c YFlags>
YLB_INLINE BOOL YFlags::operator==(DWORD flags) const
{
	return (_state == flags);
}

// @mfunc Compare two bit fields
// @parm DWORD | flags | The state mask to compare with
// @rdesc <TRUE> if any bits of <p flags> are different in the internal
//		state mask
// @xref <mf YFlags::operator==>, <mf YFlags::CompareFlags>, <c YFlags>
YLB_INLINE BOOL YFlags::operator!=(DWORD flags) const
{
	return (_state != flags);
}

YLB_INLINE YFlags::operator DWORD() const
{
	return _state;
}

// @mfunc Compare two bit fields masked by flag
// @parm DWORD | mask | The mask for the comparison
// @parm YFlags& | other | The state mask to compare with
// @rdesc <TRUE> if all bits of <p other> masked by <p mask> are equal in
//		the internal state mask
// @xref <mf YFlags::operator==>, <mf YFlags::operator!=>, <c YFlags>
YLB_INLINE BOOL YFlags::CompareFlags(DWORD mask, YFlags& other) const
{
	return (_state & mask) == (other.Get() & mask);
}

// @mfunc Compare two bit fields masked by flag
// @parm DWORD | mask | The mask for the comparison
// @parm DWORD | flags | The state mask to compare with
// @rdesc <TRUE> if all bits of <p flags> masked by <p mask> are equal in
//		the internal state mask
// @xref <mf YFlags::operator==>, <mf YFlags::operator!=>, <c YFlags>
YLB_INLINE BOOL YFlags::CompareFlags(DWORD mask, DWORD flags) const
{
	return (_state & mask) == (mask & flags);
}







// @mfunc Constructs a <c YWideFlags> object
// @parm DWORDLONG | defaultState = 0 | Default initialisation of the bitfield
// @xref <c YWideFlags>, <j Needful Things>
YLB_INLINE YWideFlags::YWideFlags (DWORDLONG defaultState)
{
	_state = defaultState;
}

// @mfunc Set the internal state mask
// @parm DWORDLONG | flag | The new mask of bits
// @xref <mf YWideFlags::Get>, <c YWideFlags>
YLB_INLINE DWORDLONG YWideFlags::Set(DWORDLONG flag)
{
	_state = flag;
	return _state;
}

// @mfunc Retrieve  the internal state mask
// @rdesc The current mask of bits
// @xref <mf YWideFlags::Set>, <c YWideFlags>
YLB_INLINE DWORDLONG YWideFlags::Get(void) const
{
	return _state;
}

// @mfunc Set the bits of a flag mask in the internal state mask
// @rdesc The modified state mask
// @xref <mf YWideFlags::ClearFlags>, <mf YWideFlags::ChangeFlags>, <c YWideFlags>
YLB_INLINE DWORDLONG YWideFlags::SetFlags(DWORDLONG flag)
{
	_state |= flag;
	return _state;
}

// @mfunc Clear the bits of a flag mask in the internal state mask
// @parm DWORDLONG | flag = ~(DWORDLONG)0 | Flag mask to clear
// @rdesc The modified state mask
// @xref <mf YWideFlags::SetFlags>, <mf YWideFlags::ChangeFlags>, <c YWideFlags>
YLB_INLINE DWORDLONG YWideFlags::ClearFlags(DWORDLONG flag)
{	
	_state &= ~flag;
	return _state;
}

// @mfunc Set or clear the bits of a flag mask in the internal state mask
// @parm DWORDLONG | flag | Flag mask to set or clear
// @parm BOOL | setState | If <TRUE> the bits in <p flag> will be set
//		otherwise they will be cleared
// @rdesc The modified state mask
// @xref <mf YWideFlags::SetFlags>, <mf YWideFlags::ClearFlags>, <c YWideFlags>
YLB_INLINE DWORDLONG YWideFlags::ChangeFlags(DWORDLONG flag, BOOL setState)
{
	return (setState ? SetFlags(flag) : ClearFlags(flag));
}

// @mfunc Test the bits of a flag mask against the internal state mask
// @parm DWORDLONG | flag | Flag mask to test
// @parm FLG_TEST_MODE | mode = FLG_AND | Testing mode (see <t FLG_TEST_MODE>)
// @rdesc <TRUE> if all bits of the flag mask are set in the internal
//		state mask if <e FLG_TEST_MODE.FLG_AND> was set, <TRUE> if any
//		of the bits is set in the internal state mask if <e FLG_TEST_MODE.FLG_OR>
//		was set.
// @xref <mf YWideFlags::TestSetFlags>, <mf YWideFlags::TestClearFlags>, <c YWideFlags>
YLB_INLINE BOOL YWideFlags::TestFlags(DWORDLONG flag, FLG_TEST_MODE mode) const
{
	DWORDLONG x = _state & flag;
	BOOL result;
	switch ( mode ) {
	case FLG_AND:
		result =  (x == flag);
		break;
	case FLG_OR:
		result =  (x != 0);
		break;
	case FLG_XOR:
		if ( x == 0 ) {
			result = FALSE;
		}
		else if ( x == 1 ) {
			result = TRUE;
		}
		else {	
			DWORDLONG	quot;
			DWORDLONG	rem;
			quot = x;
			do {
				rem = (quot & ((DWORDLONG)1));
				quot >>= 1;
			} while ( !rem );
			result = (quot == 0);
		}
		break;
	default:
		result = FALSE;
		break;
	}
	return result;
}

// @mfunc Tests and resets one or more bits in the internal state mask
// @parm DWORDLONG | flag | The flag mask to test and reset
// @comm Test the bits of a flag mask against the internal state mask.
//		Clear the bits set in the flag mask in the internal state mask
//		If the flag mask more than one bit set the return value is the
//		logical <b>AND<n> operation of all the single bit state tests.
// @rdesc <TRUE> if all bits of flag mask are set in the internal state mask
// @xref <mf YWideFlags::TestSetFlags>, <mf YWideFlags::TestFlags>, <c YWideFlags>
YLB_INLINE BOOL YWideFlags::TestClearFlags(DWORDLONG flag)
{
	BOOL result = ((_state & flag) == flag);
	ClearFlags(flag);
	return result;
}

// @mfunc Tests and sets one or more bits in the internal state mask
// @parm DWORDLONG | flag | The flag mask to test and set
// @comm Test the bits of a flag mask against the internal state mask.
//		Set the bits set in the flag mask in the internal state mask.
//		If the flag mask more than one bit set the return value is the
//		logical <b>AND<n> operation of all the single bit state tests.
// @rdesc <TRUE> if all bits of flag mask are set in the internal state mask
// @xref <mf YWideFlags::TestClearFlags>, <mf YWideFlags::TestFlags>, <c YWideFlags>
YLB_INLINE BOOL YWideFlags::TestSetFlags(DWORDLONG flag)
{
	BOOL result = ((_state & flag) == flag);
	SetFlags(flag);
	return result;
}

// @mfunc Compare two bit fields
// @parm YWideFlags& | other | The state mask to compare with
// @rdesc <TRUE> if all bits of <p other> are equal in the internal
//		state mask
// @xref <mf YWideFlags::CompareFlags>, <mf YWideFlags::operator!=>, <c YWideFlags>
YLB_INLINE BOOL YWideFlags::operator==(YWideFlags& other) const
{
	return (_state == other.Get());
}

// @mfunc Compare two bit fields
// @parm YWideFlags& | other | The state mask to compare with
// @rdesc <TRUE> if any bits of <p other> are different in the internal
//		state mask
// @xref <mf YWideFlags::operator==>, <mf YWideFlags::CompareFlags>, <c YWideFlags>
YLB_INLINE BOOL YWideFlags::operator!=(YWideFlags& other) const
{
	return (_state != other.Get());
}

// @mfunc Compare two bit fields
// @parm DWORDLONG | flags | The state mask to compare with
// @rdesc <TRUE> if all bits of <p flags> are equal in the internal
//		state mask
// @xref <mf YWideFlags::CompareFlags>, <mf YWideFlags::operator!=>, <c YWideFlags>
YLB_INLINE BOOL YWideFlags::operator==(DWORDLONG flags) const
{
	return (_state == flags);
}

// @mfunc Compare two bit fields
// @parm DWORDLONG | flags | The state mask to compare with
// @rdesc <TRUE> if any bits of <p flags> are different in the internal
//		state mask
// @xref <mf YWideFlags::operator==>, <mf YWideFlags::CompareFlags>, <c YWideFlags>
YLB_INLINE BOOL YWideFlags::operator!=(DWORDLONG flags) const
{
	return (_state != flags);
}

YLB_INLINE YWideFlags::operator DWORDLONG() const
{
	return _state;
}

// @mfunc Compare two bit fields masked by flag
// @parm DWORDLONG | mask | The mask for the comparison
// @parm YWideFlags& | other | The state mask to compare with
// @rdesc <TRUE> if all bits of <p other> masked by <p mask> are equal in
//		the internal state mask
// @xref <mf YWideFlags::operator==>, <mf YWideFlags::operator!=>, <c YWideFlags>
YLB_INLINE BOOL YWideFlags::CompareFlags(DWORDLONG mask, YWideFlags& other) const
{
	return (_state & mask) == (other.Get() & mask);
}

// @mfunc Compare two bit fields masked by flag
// @parm DWORDLONG | mask | The mask for the comparison
// @parm DWORDLONG | flags | The state mask to compare with
// @rdesc <TRUE> if all bits of <p flags> masked by <p mask> are equal in
//		the internal state mask
// @xref <mf YWideFlags::operator==>, <mf YWideFlags::operator!=>, <c YWideFlags>
YLB_INLINE BOOL YWideFlags::CompareFlags(DWORDLONG mask, DWORDLONG flags) const
{
	return (_state & mask) == (mask & flags);
}

