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
 * FILENAME		:	yArrayI.cpp
 * PURPOSE		:	Implementation of the generic integer cardinal array
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.2  2001/05/10 10:26:27  leopoldo
 * Fixed array bugs and harmonized YPtrArray
 *
 * Revision 1.1  2001/05/06 18:32:16  leopoldo
 * Initial revision
 *
 *============================================================================*/

#include "StdInc.hpp"

/*=============================================================================
 * @doc YLIB | yArray.h
 *============================================================================*/
YIntArray::YIntArray (int nAllocationGranularity /* = -1 */) : YBaseArray (nAllocationGranularity)
{
	m_pData	= NULL;
}

void YIntArray::RemoveAll ()
{
	if ( m_pData ) {
		free (m_pData);
	}
	m_pData				= NULL;
	m_nSize				= 0;
	m_nAllocatedSize	= 0;
}

int YIntArray::Find (int theElement) const
{
	for ( int i = 0; i < m_nSize; i++ ) {
		if ( m_pData[i] == theElement ) {
			return i;
		}
	}
	return -1;
}

BOOL YIntArray::SetAt (int nIndex, int newElement)
{
	if ( (nIndex >= 0) && (nIndex < m_nSize) ) {
		m_pData[nIndex] = newElement;
		return TRUE;
	}
	return FALSE;
}

BOOL YIntArray::SetAtGrow (int nIndex, int newElement)
{
	if ( (nIndex < 0) || ((nIndex >= m_nSize) && !SetSize (nIndex + 1)) ) {
		return FALSE;
	}
	m_pData[nIndex] = newElement;
	return TRUE;
}

int YIntArray::Append (const YIntArray & src)
{
	int nOldSize = m_nSize;
	if ( ((m_nSize + src.m_nSize) > m_nAllocatedSize) && !SetAllocatedSize (m_nSize + src.m_nSize) ) {
		return -1;
	}
	memcpy (m_pData + m_nSize, src.m_pData, src.m_nSize * sizeof (int));
	m_nSize += src.m_nSize;
	return nOldSize;
}

BOOL YIntArray::Copy (const YIntArray & src)
{
	if ( (src.m_nSize > m_nAllocatedSize) && !SetAllocatedSize (src.m_nSize) ) {
		return FALSE;
	}
	memcpy (m_pData, src.m_pData, src.m_nSize * sizeof (int));
	m_nSize = src.m_nSize;
	return TRUE;
}

BOOL YIntArray::InsertAt (int nIndex, const YIntArray & src)
{
	// compute new size
	int nNewSize = (nIndex < m_nSize) ? (m_nSize + src.m_nSize) : (nIndex + src.m_nSize);
	// in case resize....
	if ( (nNewSize > m_nAllocatedSize) && !SetAllocatedSize (nNewSize) ) {
		return FALSE;
	}
	if ( nIndex < m_nSize ) {
		// shift up the remaining stuff
		memmove (m_pData + nIndex + src.m_nSize, m_pData + nIndex, (m_nSize - nIndex) * sizeof (int));
	}
	else if ( nIndex > m_nSize ) {
		// initialize newly created but unused elements
		memset (m_pData + m_nSize, 0, (nIndex - m_nSize) * sizeof (int));
	}
	// copy the stuff
	memcpy (m_pData + nIndex, src.m_pData, src.m_nSize * sizeof (int));
	m_nSize = nNewSize;
	return TRUE;
}

BOOL YIntArray::InsertAt (int nIndex, int newElement, int nCount /* = 1 */)
{
	// compute new size
	int nNewSize = (nIndex < m_nSize) ? (m_nSize + nCount) : (nIndex + nCount);
	// in case resize....
	if ( (nNewSize > m_nAllocatedSize) && !SetAllocatedSize (nNewSize) ) {
		return FALSE;
	}
	if ( nIndex < m_nSize ) {
		// shift up the remaining stuff
		memmove (m_pData + nIndex + nCount, m_pData + nIndex, (m_nSize - nIndex) * sizeof (int));
	}
	else if ( nIndex > m_nSize ) {
		// initialize newly created but unused elements
		memset (m_pData + m_nSize, 0, (nIndex - m_nSize) * sizeof (int));
	}
	// set values
	for ( int * lpPtr = m_pData + nIndex; nCount; lpPtr++, nCount-- ) {
		*lpPtr = newElement;
	}
	m_nSize = nNewSize;
	return TRUE;
}

int YIntArray::RemoveAt (int nIndex, int nCount /* = 1 */)
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
		memmove (m_pData + nIndex, m_pData + nIndex + nCount, (m_nSize - (nIndex + nCount)) * sizeof (int));
	}
	m_nSize -= nCount;
	return m_nSize;
}

BOOL YIntArray::Remove (int theElement)
{
	int nIndex = Find (theElement);
	if ( nIndex != -1 ) {
		return RemoveAt (nIndex) != -1;
	}
	return FALSE;
}

BOOL YIntArray::SetSize (int nNewSize, int nAllocationGranularity /* = -1 */)
{
	int nNewAllocated = SizeHeuristic (nNewSize, nAllocationGranularity);

	switch ( nNewAllocated ) {
	case SZHEU_CLEAR:
		RemoveAll ();
		// intended fallthrough
	case SZHEU_DONOTHING:
		return TRUE;

	case SZHEU_NEGATIVE:
	case SZHEU_OVERFLOW:
		return FALSE;

	default:
		if ( !SetAllocatedSize (nNewAllocated) ) {
			return FALSE;
		}
		// intended fallthrough
	case SZHEU_BIGGER:
		// initialize the added elements
		memset (m_pData + m_nSize, 0, (nNewSize - m_nSize) * sizeof (int));
		// intended fallthrough
	case SZHEU_SMALLER:
		m_nSize = nNewSize;
		return TRUE;
	}
}

BOOL YIntArray::SetAllocatedSize (int nNewSize)
{
	if ( nNewSize <= 0 ) {
		RemoveAll ();
	}
	else if ( m_nAllocatedSize != nNewSize ) {
		if ( nNewSize > (SIZE_T_MAX/sizeof (int)) ) {
			// allocation too big (would exceed memory boundaries)
			return FALSE;
		}
		int *pData = NULL;
		int nByteSize = nNewSize * sizeof (int);
		if ( (pData = (int *) malloc (nByteSize)) == NULL ) {
			return FALSE;
		}
		memcpy (pData, m_pData, min (m_nSize, nNewSize) * sizeof (int));
		free (m_pData);
		m_pData				= pData;
		m_nSize				= min (m_nSize, nNewSize);
		m_nAllocatedSize	= nNewSize;
	}
	return TRUE;
}

/// IDENTITY STUFF ///
//LPCTSTR lpComment = _T("$Id$");

//
// EoF
////////