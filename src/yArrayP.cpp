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
 * FILENAME		:	yArrayP.cpp
 * PURPOSE		:	Implementation of the generic pointer array
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

#include "StdInc.hpp"

/*=============================================================================
 * @doc YLIB | yArray.h
 *============================================================================*/
YPtrArray::YPtrArray (int nAllocationGranularity /* = -1 */)
{
	m_pData						= NULL;
	m_nSize						= 0;
	m_nAllocatedSize			= 0;
	m_nAllocationGranularity	= (nAllocationGranularity >= 0) ? (nAllocationGranularity) : (1);
}

void YPtrArray::RemoveAll ()
{
	if ( m_pData ) {
		free (m_pData);
	}
	m_pData				= NULL;
	m_nSize				= 0;
	m_nAllocatedSize	= 0;
}

int YPtrArray::Find (LPVOID pElement) const
{
	for ( int i = 0; i < m_nSize; i++ ) {
		if ( m_pData[i] == pElement ) {
			return i;
		}
	}
	return -1;
}

BOOL YPtrArray::SetAt (int nIndex, LPVOID newElement)
{
	if ( (nIndex >= 0) && (nIndex < m_nSize) ) {
		m_pData[nIndex] = newElement;
		return TRUE;
	}
	return FALSE;
}

BOOL YPtrArray::SetAtGrow (int nIndex, LPVOID newElement)
{
	if ( (nIndex < 0) || ((nIndex >= m_nSize) && !SetSize (nIndex + 1)) ) {
		return FALSE;
	}
	m_pData[nIndex] = newElement;
	return TRUE;
}

int YPtrArray::Append (const YPtrArray & src)
{
	int nOldSize = m_nSize;
	if ( ((m_nSize + src.m_nSize) > m_nAllocatedSize) && !SetAllocatedSize (m_nSize + src.m_nSize) ) {
		return -1;
	}
	memcpy (m_pData + m_nSize, src.m_pData, src.m_nSize * sizeof (LPVOID));
	m_nSize += src.m_nSize;
	return nOldSize;
}

BOOL YPtrArray::Copy (const YPtrArray & src)
{
	if ( (src.m_nSize > m_nAllocatedSize) && !SetAllocatedSize (src.m_nSize) ) {
		return FALSE;
	}
	memcpy (m_pData, src.m_pData, src.m_nSize * sizeof (LPVOID));
	m_nSize = src.m_nSize;
	return TRUE;
}

BOOL YPtrArray::InsertAt (int nIndex, const YPtrArray & src)
{
	// compute new size
	int nNewSize = (nIndex < m_nSize) ? (m_nSize + src.m_nSize) : (nIndex + src.m_nSize);
	// in case resize....
	if ( (nNewSize > m_nAllocatedSize) && !SetAllocatedSize (nNewSize) ) {
		return FALSE;
	}
	if ( nIndex < m_nSize ) {
		// shift up the remaining stuff
		memmove (m_pData + nIndex + src.m_nSize, m_pData + nIndex, (m_nSize - nIndex) * sizeof (LPVOID));
	}
	else if ( nIndex > m_nSize ) {
		// initialize newly created but unused elements
		memset (m_pData + m_nSize, 0, (nIndex - m_nSize) * sizeof (LPVOID));
	}
	// copy the stuff
	memcpy (m_pData + nIndex, src.m_pData, src.m_nSize * sizeof (LPVOID));
	m_nSize = nNewSize;
	return TRUE;
}

BOOL YPtrArray::InsertAt (int nIndex, LPVOID newElement, int nCount /* = 1 */)
{
	// compute new size
	int nNewSize = (nIndex < m_nSize) ? (m_nSize + nCount) : (nIndex + nCount);
	// in case resize....
	if ( (nNewSize > m_nAllocatedSize) && !SetAllocatedSize (nNewSize) ) {
		return FALSE;
	}
	if ( nIndex < m_nSize ) {
		// shift up the remaining stuff
		memmove (m_pData + nIndex + nCount, m_pData + nIndex, (m_nSize - nIndex) * sizeof (LPVOID));
	}
	else if ( nIndex > m_nSize ) {
		// initialize newly created but unused elements
		memset (m_pData + m_nSize, 0, (nIndex - m_nSize) * sizeof (LPVOID));
	}
	// set values
	for ( LPVOID * lpPtr = m_pData + nIndex; nCount; lpPtr++, nCount-- ) {
		*lpPtr = newElement;
	}
	m_nSize = nNewSize;
	return TRUE;
}

int YPtrArray::RemoveAt (int nIndex, int nCount /* = 1 */)
{
	if ( (nIndex < 0) || (nIndex >= m_nSize) ) {
		// bad param
		return -1;
	}
	else if ( nCount == 0 ) {
		// nothing to do
		return m_nSize;
	}
	// compute the real remove count
	if ( (nIndex + nCount) > m_nSize ) {
		nCount = m_nSize - nIndex;
	}
	else if ( (nIndex + nCount) < m_nSize ) {
		// we must shift
		memmove (m_pData + nIndex, m_pData + nIndex + nCount, (m_nSize - (nIndex + nCount)) * sizeof (LPVOID));
	}
	m_nSize -= nCount;
	return m_nSize;
}

BOOL YPtrArray::Remove (LPVOID pElement)
{
	int nIndex = Find (pElement);
	if ( nIndex != -1 ) {
		return RemoveAt (nIndex);
	}
	return FALSE;
}

BOOL YPtrArray::SetSize (int nNewSize, int nAllocationGranularity /* = -1 */)
{
	// reset granularity
	if ( nAllocationGranularity >= 0 ) {
		m_nAllocationGranularity = nAllocationGranularity;
	}

	if ( nNewSize < 0 ) {
		// crap
		return FALSE;
	}
	else if ( nNewSize == 0 ) {
		// clear
		RemoveAll ();
		return TRUE;
	}
	else if ( nNewSize == m_nSize ) {
		// no change
		return TRUE;
	}
	else if ( nNewSize > m_nAllocatedSize ) {
		// determine how much to grow the array.
		// if no granularity is specified, we grow dynamically:
		// 1/8 of the array size, but not less than 4 elements
		// and not more than 1024 elements.
		int nAddElements	= (m_nAllocationGranularity > 0) ? (m_nAllocationGranularity) : (min (max (m_nSize / 8, 4), 1024));
		int nNewAllocated	= m_nAllocatedSize + nAddElements;
		if ( nNewAllocated < nNewSize ) {
			// let's allocate exactly what the user wants.
			nNewAllocated = nNewSize;
		}
		if ( nNewAllocated < m_nAllocatedSize ) {
			// roll over...
			return FALSE;
		}
		if ( !SetAllocatedSize (nNewAllocated) ) {
			return FALSE;
		}
	}

	if ( nNewSize > m_nSize ) {
		// initialize the added elements
		memset (m_pData + m_nSize, 0, (nNewSize - m_nSize) * sizeof (LPVOID));
	}
	m_nSize = nNewSize;
	return TRUE;
}

BOOL YPtrArray::SetAllocatedSize (int nNewSize)
{
	if ( nNewSize <= 0 ) {
		RemoveAll ();
	}
	else if ( m_nAllocatedSize != nNewSize ) {
		if ( nNewSize > (SIZE_T_MAX/sizeof (LPVOID)) ) {
			// allocation too big (would exceed memory boundaries)
			return FALSE;
		}
		LPVOID *pData = NULL;
		int nByteSize = nNewSize * sizeof (LPVOID);
		if ( (pData = (LPVOID *) malloc (nByteSize)) == NULL ) {
			return FALSE;
		}
		memcpy (pData, m_pData, min (m_nSize, nNewSize) * sizeof (LPVOID));
		free (m_pData);
		m_pData				= pData;
		m_nSize				= min (m_nSize, nNewSize);
		m_nAllocatedSize	= nNewSize;
	}
	return TRUE;
}

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////