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
 * FILENAME		:	yBuffer.inl
 * PURPOSE		:	Inline members of the generic buffer class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yBuffer.h
 *============================================================================*/
YLB_INLINE YBuffer::YBuffer ()
{
	m_cbSize	= 0;
	m_lpPtr		= NULL;
}

YLB_INLINE YBuffer::~YBuffer ()
{
	Free ();
}

YLB_INLINE UINT YBuffer::GetSize () const
{
	return m_cbSize;
}

YLB_INLINE LPVOID YBuffer::GetBuffer () const
{
	return m_lpPtr;
}

YLB_INLINE YBuffer::operator LPVOID () const
{
	return m_lpPtr;
}

YLB_INLINE void YBuffer::Clear (int iFill)
{
	if ( m_lpPtr ) {
		memset (m_lpPtr, iFill, m_cbSize);
	}
}

//
// EoF
////////
