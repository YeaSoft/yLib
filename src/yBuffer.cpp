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
 * FILENAME		:	yBuffer.cpp
 * PURPOSE		:	Implementation of the generic buffer class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.4  2001/04/11 17:03:15  leopoldo
 * Fixed arroneous free in YBuffer::Realloc
 *
 * Revision 1.3  2000/10/25 09:18:59  leopoldo
 * Added assignment operations
 *
 * Revision 1.2  2000/09/04 12:07:43  leopoldo
 * Updated license to zlib/libpng
 *
 * Revision 1.1  2000/05/26 14:04:53  leo
 * Initial revision
 *
 *============================================================================*/

#include "StdInc.hpp"

/*=============================================================================
 * @doc YLIB | yBuffer.h
 *============================================================================*/

/*=============================================================================
 * SIMPLE BUFFER IMPLEMENTATION
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

BOOL YBuffer::Copy (const YBuffer &srcBuffer, BOOL bDontReallocIfFits)
{
	if ( bDontReallocIfFits && (srcBuffer.m_cbSize <= m_cbSize) ) {
		// avoid risk of failed allocation and avoid fragmentation
		memcpy (m_lpPtr, srcBuffer.m_lpPtr, srcBuffer.m_cbSize);
		return TRUE;
	}

	LPVOID lpData = malloc (srcBuffer.m_cbSize);
	if ( !lpData ) {
		// fail without destroying previous content
		return FALSE;
	}
	memcpy (lpData, srcBuffer.m_lpPtr, srcBuffer.m_cbSize);

	// free previous
	Free ();
	// reassign
	m_lpPtr		= lpData;
	m_cbSize	= srcBuffer.m_cbSize;

	return TRUE;
}

/*=============================================================================
 * DYNAMIC BUFFER IMPLEMENTATION
 *============================================================================*/
LPVOID YDynamicBuffer::Detach (LPUINT lpcbContentSize /* = NULL */, LPUINT lpcbSize /* = NULL */)
{
	if ( lpcbContentSize ) {
		*lpcbContentSize = m_cbContentSize;
	}
	m_cbContentSize = 0;
	return YBuffer::Detach (lpcbSize);
}

BOOL YDynamicBuffer::Alloc (UINT cbSize, BOOL fZeroInit)
{
	if ( YBuffer::Alloc (cbSize, fZeroInit) ) {
		m_cbContentSize = 0;
		return TRUE;
	}
	return FALSE;
}

BOOL YDynamicBuffer::Realloc (UINT cbSize, BOOL fAllocCopyFree, BOOL fNoCopy)
{
	LPVOID	lpData;

	if ( !m_lpPtr || fAllocCopyFree || !cbSize ) {
		if ( !(lpData = malloc (cbSize)) ) {
			return FALSE;
		}
		if ( m_lpPtr && !fNoCopy ) {
			memcpy (lpData, m_lpPtr, min (cbSize, m_cbContentSize));
		}
		Free ();
		m_lpPtr			= lpData;
		m_cbSize		= cbSize;
		m_cbContentSize	= min (cbSize, m_cbContentSize);
		return TRUE;
	}
	else {
		if ( !(lpData = realloc (m_lpPtr, cbSize)) ) {
			return FALSE;
		}
		m_lpPtr			= lpData;
		m_cbSize		= cbSize;
		m_cbContentSize	= min (cbSize, m_cbContentSize);
		return TRUE;
	}
}

BOOL YDynamicBuffer::Copy (const YDynamicBuffer &srcBuffer, BOOL bDontReallocIfFits)
{
	if ( bDontReallocIfFits && (srcBuffer.m_cbContentSize <= m_cbSize) ) {
		// avoid risk of failed allocation and avoid fragmentation
		memcpy (m_lpPtr, srcBuffer.m_lpPtr, srcBuffer.m_cbContentSize);
		m_cbContentSize			= srcBuffer.m_cbContentSize;
		m_nAllocationIncrease	= srcBuffer.m_nAllocationIncrease;
		return TRUE;
	}

	LPVOID lpData = malloc (srcBuffer.m_cbSize);
	if ( !lpData ) {
		// fail without destroying previous content
		return FALSE;
	}
	memcpy (lpData, srcBuffer.m_lpPtr, srcBuffer.m_cbContentSize);

	// free previous
	Free ();
	// reassign
	m_lpPtr					= lpData;
	m_cbSize				= srcBuffer.m_cbSize;
	m_cbContentSize			= srcBuffer.m_cbContentSize;
	m_nAllocationIncrease	= srcBuffer.m_nAllocationIncrease;

	return TRUE;
}

BOOL YDynamicBuffer::IncreaseSize (UINT cbIncrease)
{
	if ( !cbIncrease ) {
		return TRUE;
	}
	UINT cbNewSize = m_cbSize;
	if ( m_nAllocationIncrease ) {
		cbNewSize += (((cbIncrease / m_nAllocationIncrease) + 1) * m_nAllocationIncrease);
	}
	else {
		// determine how much to grow the buffer.
		// if no increase is specified, we grow dynamically:
		// 1/8 of the buffer size, but not less than 2 times
		// the requested size and not more than 256 times.
		cbNewSize += min (max (m_cbSize / 8, 2 * cbIncrease), 256 * cbIncrease);
	}
	LPVOID lpData = realloc (m_lpPtr, cbNewSize);
	if ( !lpData ) {
		return FALSE;
	}
	m_lpPtr		= lpData;
	m_cbSize	= cbNewSize;
	return TRUE;
}

BOOL YDynamicBuffer::PushData (LPCVOID lpData, UINT cbSize)
{
	if ( (m_cbContentSize + cbSize) > m_cbSize ) {
		if ( !IncreaseSize (cbSize) ) {
			return FALSE;
		}
	}
	memcpy (GetByteBufferPtr (m_cbContentSize), lpData, cbSize);
	m_cbContentSize += cbSize;
	return TRUE;
}

#ifndef YLB_ENABLE_INLINE
#include <yBuffer.inl>
#endif

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////