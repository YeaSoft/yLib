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
 * FILENAME		:	yTokens.cpp
 * PURPOSE		:	Implementation of the token helper classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:05:13  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yTokens.h
 *============================================================================*/
#include "StdInc.hpp"

#ifdef _DEBUG
#undef HERE
static char HERE[] = __FILE__;
#endif //_DEBUG

/*=============================================================================
 * IMPLEMENTATION
 *============================================================================*/
LPCTSTR YTokenizer::GetNextToken (TCHAR cToken, LPTSTR pszBuffer, UINT cbSize)
{
	ASSERTY(!pszBuffer || (cbSize > 0));

	if ( !m_pszStart ) {
		*pszBuffer = 0;
		return NULL;
	}

	LPTSTR lpPtr;

	if ( m_bWordMode ) {
		// find start
		while ( *m_pszStart && (*m_pszStart == cToken) ) {
			++m_pszStart;
		}
		if ( !*m_pszStart ) {
			// EoS
			*pszBuffer = 0;
			return NULL;
		}
	}

	if ( !(lpPtr = _tcschr (m_pszStart, cToken)) ) {
		_tcsncpy (pszBuffer, m_pszStart, cbSize - 1);
		pszBuffer[cbSize - 1] = 0;
		m_pszStart = NULL;
		return pszBuffer;
	}
	_tcsncpy (pszBuffer, m_pszStart, min(lpPtr-m_pszStart,(int)cbSize - 1));
	pszBuffer[min(lpPtr-m_pszStart,(int)cbSize - 1)] = 0;
	m_pszStart = lpPtr + 1;
	return pszBuffer;
}

LPCTSTR YTokenizer::GetNextToken (LPCTSTR lpszSeparators, LPTSTR pszBuffer, UINT cbSize)
{
	ASSERTY(!pszBuffer || (cbSize > 0));

	if ( !m_pszStart ) {
		*pszBuffer = 0;
		return NULL;
	}

	if ( !*m_pszStart ) {
		*pszBuffer = 0;
		m_pszStart = NULL;
		return (m_bWordMode) ? (NULL) : (pszBuffer);
	}

	size_t	tSize;

	if ( m_bWordMode ) {
		while ( !(tSize = _tcscspn (m_pszStart, lpszSeparators)) ) {
			if ( !*m_pszStart ) {
				// EoS
				*pszBuffer = 0;
				m_pszStart = NULL;
				return NULL;
			}
			++m_pszStart;
		}
	}
	else {
		if ( !(tSize = _tcscspn (m_pszStart, lpszSeparators)) ) {
			*pszBuffer = 0;
			++m_pszStart;
			return pszBuffer;
		}
	}
	_tcsncpy (pszBuffer, m_pszStart, min(tSize,cbSize - 1));
	pszBuffer[min(tSize,cbSize - 1)] = 0;
	m_pszStart = (m_pszStart[tSize]) ? (m_pszStart + tSize + 1) : (NULL);
	return pszBuffer;
}

#ifndef YLB_ENABLE_INLINE
#include <yTokens.inl>
#endif

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////