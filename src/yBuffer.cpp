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
 * FILENAME		:	yBuffer.cpp
 * PURPOSE		:	Implementation of the generic buffer class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

#include "StdInc.hpp"

/*=============================================================================
 * @doc YLIB | yBuffer.h
 *============================================================================*/

/*=============================================================================
 * IMPLEMENTATION
 *============================================================================*/
void YBuffer::Attach (LPVOID lpBuffer, UINT cbSize)
{
	ASSERTY((!lpBuffer && !cbSize) || (lpBuffer && cbSize));
	if ( lpBuffer != m_lpPtr ) {
		Free ();
	}
	m_lpPtr		= lpBuffer;
	m_cbSize	= cbSize;
}

LPVOID YBuffer::Detach (LPUINT lpcbSize)
{
	if ( lpcbSize ) {
		*lpcbSize = m_cbSize;
	}
	LPVOID lpRet = m_lpPtr;
	m_lpPtr		= NULL;
	m_cbSize	= 0;
	return lpRet;
}

BOOL YBuffer::Alloc (UINT cbSize, BOOL fZeroInit)
{
	LPVOID	lpData = malloc (cbSize);
	if ( !lpData ) {
		return FALSE;
	}
	Free ();
	m_lpPtr		= lpData;
	m_cbSize	= cbSize;
	if ( fZeroInit ) {
		Clear ();
	}
	return TRUE;
}

BOOL YBuffer::Realloc (UINT cbSize, BOOL fAllocCopyFree, BOOL fNoCopy)
{
	LPVOID	lpData;

	if ( !m_lpPtr || fAllocCopyFree || !cbSize ) {
		if ( !(lpData = malloc (cbSize)) ) {
			return FALSE;
		}
		if ( m_lpPtr && !fNoCopy ) {
			memcpy (lpData, m_lpPtr, min (cbSize, m_cbSize));
		}
		Free ();
		m_lpPtr		= lpData;
		m_cbSize	= cbSize;
		return TRUE;
	}
	else {
		if ( !(lpData = realloc (m_lpPtr, cbSize)) ) {
			return FALSE;
		}
		Free ();
		m_lpPtr		= lpData;
		m_cbSize	= cbSize;
		return TRUE;
	}
}

void YBuffer::Free ()
{
	if ( m_lpPtr ) {
		free (m_lpPtr);
		m_lpPtr = NULL;
	}
	m_cbSize = 0;
}

#ifndef YLB_ENABLE_INLINE
#include <yBuffer.inl>
#endif

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////