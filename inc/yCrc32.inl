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
 * FILENAME		:	yCrc32.inl
 * PURPOSE		:	Inline members of the CRC Calculation Class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yCrc32.h
 *============================================================================*/

// @mfunc Constructs a <c YCrc32> object
// @xref <c YCrc32>
YLB_INLINE YCrc32::YCrc32 ()
{
	m_dwCrc = 0;
}

// @mfunc Updates the CRC using the supplied memory buffer
// @parm LPVOID | lpBuffer | Pointer to the buffer containing the data
//		to be used for the CRC computation
// @parm DWORD | cbSize | Length in bytes of the supplied buffer
// @comm Call this member function to update the internal CRC value
//		with the contents of the supplied memory buffer
// @xref <mf YCrc32::GetCrc>, <mf YCrc32::ResetCrc>, <c YCrc32>
YLB_INLINE void YCrc32::UpdateCrc (LPVOID lpBuffer, DWORD cbSize)
{
	m_dwCrc = UpdateCrc ((LPSTR) lpBuffer, cbSize, m_dwCrc);
}

// @mfunc Returns the computed CRC value
// @rdesc The computed CRC values after one or more calls to
//		<mf YCrc32::UpdateCrc>
// @comm Call this member function to get the computed CRC value
//		after one or more calls to the member function <mf YCrc32::UpdateCrc>.
//		If you wish to start a new CRC computation, you can reset the
//		internal CRC system by calling <mf YCrc32::ResetCrc>
// @xref <mf YCrc32::UpdateCrc>, <mf YCrc32::ResetCrc>, <c YCrc32>
YLB_INLINE DWORD YCrc32::GetCrc ()
{
	return m_dwCrc;
}

// @mfunc Resets the internal CRC value for a new computation
// @comm Use this function to reset the internal values of the CRC
//		computation system if you want to perform a new CRC
//		computation.
// @xref <mf YCrc32::UpdateCrc>, <mf YCrc32::GetCrc>, <c YCrc32>
YLB_INLINE void YCrc32::ResetCrc ()
{
	m_dwCrc = 0;
}

//
// EoF
////////