/*=============================================================================
 * This is a part of the yLib Software Development Kit.
 * Copyright (C) 1998-2001 YEAsoft Int'l.
 * All rights reserved.
 *=============================================================================
 * Copyright (c) 1998-2001 YEAsoft Int'l (Leo Moll, Andrea Pennelli).
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
 * Revision 1.7  2001/05/22 16:57:59  leopoldo
 * Added more methods to YDynamicBuffer
 *
 * Revision 1.6  2001/05/21 18:53:05  leopoldo
 * Added more methods to YDynamicBuffer
 *
 * Revision 1.5  2001/05/06 18:31:00  leopoldo
 * Improved YBuffer
 * Added new class YDynamicBuffer
 *
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
BOOL YBuffer::Attach (LPVOID lpBuffer, int cbSize)
{
	ASSERTY((!lpBuffer && !cbSize) || (lpBuffer && cbSize >= 0));
	if ( cbSize < 0 ) {
		return FALSE;
	}
	if ( lpBuffer != m_lpPtr ) {
		Free ();
	}
	m_lpPtr		= (LPBYTE) lpBuffer;
	m_cbSize	= cbSize;
	return TRUE;
}

LPVOID YBuffer::Detach (LPINT lpcbSize)
{
	if ( lpcbSize ) {
		*lpcbSize = m_cbSize;
	}
	LPVOID lpRet = m_lpPtr;
	m_lpPtr		= NULL;
	m_cbSize	= 0;
	return lpRet;
}

BOOL YBuffer::Alloc (int cbSize, BOOL fZeroInit)
{
	if ( cbSize < 0 ) {
		return FALSE;
	}
	LPBYTE lpData = (LPBYTE) malloc (cbSize);
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

BOOL YBuffer::Realloc (int cbSize, BOOL fAllocCopyFree, BOOL fNoCopy)
{
	if ( cbSize < 0 ) {
		return FALSE;
	}
	LPBYTE lpData;

	if ( !m_lpPtr || fAllocCopyFree || !cbSize ) {
		if ( !(lpData = (LPBYTE) malloc (cbSize)) ) {
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
		if ( !(lpData = (LPBYTE) realloc (m_lpPtr, cbSize)) ) {
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

	LPBYTE lpData = (LPBYTE) malloc (srcBuffer.m_cbSize);
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
LPVOID YDynamicBuffer::Detach (LPINT lpcbContentSize /* = NULL */, LPINT lpcbSize /* = NULL */)
{
	if ( lpcbContentSize ) {
		*lpcbContentSize = m_cbContentSize;
	}
	m_cbContentSize = 0;
	return YBuffer::Detach (lpcbSize);
}

BOOL YDynamicBuffer::Alloc (int cbSize, BOOL fZeroInit)
{
	if ( YBuffer::Alloc (cbSize, fZeroInit) ) {
		m_cbContentSize = 0;
		return TRUE;
	}
	return FALSE;
}

BOOL YDynamicBuffer::Realloc (int cbSize, BOOL fAllocCopyFree, BOOL fNoCopy)
{
	if ( cbSize < 0 ) {
		return FALSE;
	}

	LPBYTE lpData;

	if ( !m_lpPtr || fAllocCopyFree || !cbSize ) {
		if ( !(lpData = (LPBYTE) malloc (cbSize)) ) {
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
		if ( !(lpData = (LPBYTE) realloc (m_lpPtr, cbSize)) ) {
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

	LPBYTE lpData = (LPBYTE) malloc (srcBuffer.m_cbSize);
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

BOOL YDynamicBuffer::IncreaseSize (int cbIncrease)
{
	if ( cbIncrease < 1 ) {
		return TRUE;
	}
	int cbNewSize = m_cbSize;
	if ( m_nAllocationIncrease > 0 ) {
		cbNewSize += (((cbIncrease / m_nAllocationIncrease) + 1) * m_nAllocationIncrease);
	}
	else {
		// determine how much to grow the buffer.
		// if no increase is specified, we grow dynamically:
		// 1/8 of the buffer size, but not less than 2 times
		// the requested size and not more than 256 times.
		cbNewSize += min (max (m_cbSize / 8, 2 * cbIncrease), 256 * cbIncrease);
	}
	LPBYTE lpData = (LPBYTE) realloc (m_lpPtr, cbNewSize);
	if ( !lpData ) {
		return FALSE;
	}
	m_lpPtr		= lpData;
	m_cbSize	= cbNewSize;
	return TRUE;
}

BOOL YDynamicBuffer::PushData (LPCVOID lpData, int cbSize)
{
	// avoid useless calculations
	if ( cbSize < 1 ) {
		return FALSE;
	}

	if ( (m_cbContentSize + cbSize) > m_cbSize ) {
		if ( !IncreaseSize (cbSize) ) {
			return FALSE;
		}
	}
	memcpy (m_lpPtr + m_cbContentSize, lpData, cbSize);
	m_cbContentSize += cbSize;
	return TRUE;
}

BOOL YDynamicBuffer::InsertData (int nOffset, LPCVOID lpData, int cbSize)
{
	// avoid useless calculations
	if ( (cbSize < 1) || (nOffset < 0) ) {
		return FALSE;
	}

	int nIncrease = 0;

	// determine how much we need to increase the size
	if ( nOffset >= m_cbContentSize ) {
		if ( (nOffset + cbSize) > m_cbSize ) {
			nIncrease = (nOffset + cbSize) - m_cbSize;
		}
	}
	else {
		if ( (m_cbContentSize + cbSize) > m_cbSize ) {
			nIncrease = cbSize;
		}
	}

	// if needed try to increase the size
	if ( nIncrease && !IncreaseSize (nIncrease) ) {
		return FALSE;
	}


	// check if we have to move existing stuff
	if ( nOffset < m_cbContentSize ) {
		// move up our stuff
		memmove (m_lpPtr + nOffset + cbSize, m_lpPtr + nOffset, min (cbSize,m_cbContentSize - nOffset));
		m_cbContentSize = m_cbContentSize + cbSize;
	}
	else {
		m_cbContentSize = nOffset + cbSize;
	}

	// push the data
	memcpy (m_lpPtr + nOffset, lpData, cbSize);
	return TRUE;
}

BOOL YDynamicBuffer::ExtractData (int nOffset, LPVOID lpData, int cbSize, LPINT pNumberOfBytesRead /* = NULL */)
{
	int nExtract;
	if ( !pNumberOfBytesRead ) {
		pNumberOfBytesRead = &nExtract;
	}
	*pNumberOfBytesRead = 0;

	// avoid useless calculations
	if ( (cbSize < 1) || (nOffset < 0) ) {
		return FALSE;
	}

	// test if offset out of range
	if ( nOffset >= m_cbContentSize ) {
		return FALSE;
	}

	// determine how much must be extracted
	*pNumberOfBytesRead = min (cbSize, m_cbContentSize - nOffset);

	// get it!
	memcpy (lpData, m_lpPtr + nOffset, *pNumberOfBytesRead);

	// check if we have to move existing stuff
	if ( (nOffset + *pNumberOfBytesRead) < m_cbContentSize ) {
		// shift the rest back
		memmove (m_lpPtr + nOffset, m_lpPtr + nOffset + *pNumberOfBytesRead, m_cbContentSize - (nOffset + *pNumberOfBytesRead));
	}

	m_cbContentSize -= *pNumberOfBytesRead;

	return TRUE;
}

BOOL YDynamicBuffer::PopData (LPVOID lpData, int cbSize, LPINT pNumberOfBytesRead /* = NULL */)
{
	int nExtract;
	if ( !pNumberOfBytesRead ) {
		pNumberOfBytesRead = &nExtract;
	}
	*pNumberOfBytesRead = 0;

	// avoid useless calculations
	if ( !cbSize ) {
		return FALSE;
	}

	// determine how much must be extracted
	*pNumberOfBytesRead = min (cbSize, m_cbContentSize);

	// get it!
	memcpy (lpData, m_lpPtr, *pNumberOfBytesRead);

	// check if we have to move existing stuff
	if ( *pNumberOfBytesRead < m_cbContentSize ) {
		// shift the rest back
		memmove (m_lpPtr, m_lpPtr + *pNumberOfBytesRead, m_cbContentSize - *pNumberOfBytesRead);
	}

	m_cbContentSize -= *pNumberOfBytesRead;

	return TRUE;
}

BOOL YDynamicBuffer::ExtractString (int nOffset, LPSTR pszData, int cbSize)
{
	if ( !pszData || (nOffset < 0) || ((m_cbContentSize - nOffset) < 1) || (cbSize < 2) ) {
		if ( pszData && (cbSize > 0) ) {
			*pszData = 0;
		}
		return FALSE;
	}

	// determine how many chars to read (cbSize must be > 0)
	cbSize = min (m_cbContentSize - nOffset, cbSize - 1);

	// copy the stuff
	for ( LPSTR lpPtr = (LPSTR) (m_lpPtr + nOffset); *lpPtr && cbSize; lpPtr++, cbSize-- ) {
		*pszData = *lpPtr;
	}
	// zero terminate
	*pszData = 0;

	if ( !*lpPtr ) {
		// zero termination has thrown us out
		++lpPtr;
	}

	// determine how much stuff we have extracted
	int nExtracted = lpPtr - (LPSTR) (m_lpPtr + nOffset);

	if ( nExtracted ) {
		// shift the rest back
		memmove (m_lpPtr + nOffset, lpPtr, m_cbContentSize - (nOffset + nExtracted));
		// redimension
		m_cbContentSize -= nExtracted;
	}

	return TRUE;
}

BOOL YDynamicBuffer::ExtractString (int nOffset, LPWSTR pszData, int cbSize)
{
	if ( !pszData || (nOffset < 0) || ((m_cbContentSize - nOffset) < sizeof(WCHAR)) || (cbSize < 2) ) {
		if ( pszData && cbSize ) {
			*pszData = 0;
		}
		return FALSE;
	}

	// determine how many chars to read (cbSize must be > 0)
	cbSize = min ((int) ((m_cbContentSize - nOffset) / sizeof(WCHAR)), (cbSize - 1));

	// copy the stuff
	for ( LPWSTR lpPtr = (LPWSTR) (m_lpPtr + nOffset); *lpPtr && cbSize; lpPtr++, cbSize-- ) {
		*pszData = *lpPtr;
	}
	// zero terminate
	*pszData = 0;

	if ( !*lpPtr ) {
		// zero termination has thrown us out
		++lpPtr;
	}

	// determine how much stuff we have extracted
	UINT nExtracted = (LPBYTE) lpPtr - (m_lpPtr + nOffset);

	if ( nExtracted ) {
		// shift the rest back
		memmove (m_lpPtr + nOffset, lpPtr, m_cbContentSize - (nOffset + nExtracted));
		// redimension
		m_cbContentSize -= nExtracted;
	}

	return TRUE;
}

BOOL YDynamicBuffer::SetContentSize (int cbContentSize)
{
	if ( (cbContentSize > m_cbSize) && !IncreaseSize (m_nAllocationIncrease + cbContentSize - m_cbSize) ) {
		return FALSE;
	}
	m_cbContentSize = cbContentSize;
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