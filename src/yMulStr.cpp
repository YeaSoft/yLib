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
 * FILENAME		:	yMulStr.cpp
 * PURPOSE		:	Implementation of the multiple string class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

#include "StdInc.hpp"

/*=============================================================================
 * @doc YLIB | yMulStr.h
 *============================================================================*/

/*=============================================================================
 * MULTISTRING CLASS IMPLEMENTATION
 *============================================================================*/
BOOL YMultiString::Alloc (UINT cbSize, BOOL bEmpty)
{
	if ( cbSize < 2) {
		Free ();
		return TRUE;
	}

	LPTSTR	lpPtr, lpOld	= m_pszString;
	UINT	cbOld			= m_cbSize;

	if ( !(lpPtr = (LPTSTR) malloc (sizeof (TCHAR) * cbSize)) ) {
		return FALSE;
	}
	m_cbSize	= cbSize;
	m_pszString	= lpPtr;

	if ( lpOld ) {
		memcpy (m_pszString, lpOld, min(m_cbSize - 2,cbOld - 2) * sizeof (TCHAR));
		m_pszString[m_cbSize - 2] = 0;
		m_pszString[m_cbSize - 1] = 0;
		free (lpOld);
	}
	else if ( bEmpty ) {
		m_pszString[0] = m_pszString[1] = 0;
	}
	return TRUE;
}

void YMultiString::Free ()
{
	if ( m_pszString ) {
		free (m_pszString);
	}
	m_pszString	= NULL;
	m_cbSize	= 0;
}

#ifndef YLB_ENABLE_INLINE
#include <yMulStr.inl>
#endif

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////