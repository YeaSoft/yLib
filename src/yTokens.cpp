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
 * FILENAME		:	yTokens.cpp
 * PURPOSE		:	Implementation of the token helper classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
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