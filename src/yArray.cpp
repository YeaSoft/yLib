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
 * FILENAME		:	yArray.cpp
 * PURPOSE		:	Implementation of the generic array classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.2  2001/04/19 17:30:04  leopoldo
 * Added new template YTypedAllocatedPtrArray
 *
 * Revision 1.1  2001/04/12 18:47:47  leopoldo
 * Initial revision
 *
 *============================================================================*/

#include "StdInc.hpp"

/*=============================================================================
 * @doc YLIB | yArray.h
 *============================================================================*/
YBaseArray::YBaseArray(int nAllocationGranularity /* = -1 */)
{
	m_nSize						= 0;
	m_nAllocatedSize			= 0;
	m_nAllocationGranularity	= (nAllocationGranularity >= 0) ? (nAllocationGranularity) : (0);
}

YBaseArray::YBaseArray (const YBaseArray &src)
{
	m_nSize						= 0;
	m_nAllocatedSize			= 0;
	m_nAllocationGranularity	= src.m_nAllocationGranularity;
}

int YBaseArray::SizeHeuristic (int nNewSize, int nAllocationGranularity)
{
	// reset granularity
	if ( nAllocationGranularity >= 0 ) {
		m_nAllocationGranularity = nAllocationGranularity;
	}

	if ( nNewSize < 0 ) {
		// crap
		return SZHEU_NEGATIVE;
	}
	else if ( nNewSize == 0 ) {
		// clear
		return SZHEU_CLEAR;
	}
	else if ( nNewSize == m_nSize ) {
		// no change
		return SZHEU_DONOTHING;
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
			return SZHEU_OVERFLOW;
		}
		return nNewAllocated;
	}

	if ( nNewSize > m_nSize ) {
		// initialize the added elements
		return SZHEU_BIGGER;
	}
	return SZHEU_SMALLER;
}

#ifndef YLB_ENABLE_INLINE
#include <yArray.inl>
#endif

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////