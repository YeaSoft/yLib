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
 * FILENAME		:	yUNC.cpp
 * PURPOSE		:	Declaration of the UNC Class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:05:14  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yUNC.h
 *============================================================================*/
#include "StdInc.hpp"

YUNC::YUNC (LPCTSTR lpszFileName, ...)
{
	va_list			va;

	CommonConstructor ();

	va_start (va, lpszFileName);
	_vstprintf (m_szFileName, lpszFileName, va);
	va_end (va);
	Analyze ();
}

YUNC::YUNC (const YUNC &uncSrc)
{
	CommonConstructor ();

	_tcscpy (m_szFileName, uncSrc.m_szFileName);
}

void YUNC::SetName (LPCTSTR lpszFileName, ...)
{
	va_list			va;

	va_start (va, lpszFileName);
	_vstprintf (m_szFileName, lpszFileName, va);
	va_end (va);
	Analyze ();
}

void YUNC::CommonConstructor ()
{
	m_szFileName[0]		= 0;
	m_pszComputerPart	= NULL;
	m_pszSharePart		= NULL;
	m_pszPathPart		= NULL;
	m_nComputerLength	= 0;
	m_nShareLength		= 0;
	m_nPathLength		= 0;
}

void YUNC::Analyze ()
{
	m_pszComputerPart	= NULL;
	m_pszSharePart		= NULL;
	m_nComputerLength	= 0;
	m_nShareLength		= 0;
	m_nPathLength		= 0;

	if ( (m_szFileName[0] != _T('\\')) || (m_szFileName[1] != _T('\\')) ) {
		m_pszPathPart		= m_szFileName;
		m_nPathLength		= _tcslen (m_szFileName);
		return;
	}
	m_pszComputerPart = m_szFileName + 2;
	if ( (m_pszSharePart = _tcschr (m_pszComputerPart, _T('\\'))) != NULL ) {
		m_nComputerLength = m_pszSharePart - m_pszComputerPart;
		++m_pszSharePart;
		if ( (m_pszPathPart = _tcschr (m_pszSharePart, _T('\\'))) != NULL ) {
			m_nShareLength = m_pszPathPart - m_pszSharePart;
			++m_pszPathPart;
			m_nPathLength = _tcslen (m_pszPathPart);
		}
	}
	else {
		m_pszPathPart = NULL;
		m_nComputerLength	= _tcslen (m_pszComputerPart);
	}
}

LPCTSTR YUNC::GetComputerPart (LPTSTR pszBuffer, UINT cbBuffer)
{
	if ( !m_nComputerLength ) {
		return NULL;
	}

	if ( !pszBuffer ) {
		pszBuffer	= m_szBuffer;
		cbBuffer	= MAX_PATH;
	}

	cbBuffer = min(cbBuffer - 1, m_nComputerLength);
	_tcsncpy (pszBuffer, m_pszComputerPart, cbBuffer);
	pszBuffer[cbBuffer - 1] = 0;
	return pszBuffer;
}

LPCTSTR YUNC::GetSharePart (LPTSTR pszBuffer, UINT cbBuffer)
{
	if ( !m_nShareLength ) {
		return NULL;
	}

	if ( !pszBuffer ) {
		pszBuffer	= m_szBuffer;
		cbBuffer	= MAX_PATH;
	}
	
	cbBuffer = min(cbBuffer - 1, m_nShareLength);
	_tcsncpy (pszBuffer, m_pszSharePart, cbBuffer);
	pszBuffer[cbBuffer - 1] = 0;
	return pszBuffer;
}

LPCTSTR YUNC::GetPathPart (LPTSTR pszBuffer, UINT cbBuffer)
{
	if ( !m_nPathLength ) {
		return NULL;
	}

	if ( !pszBuffer ) {
		pszBuffer	= m_szBuffer;
		cbBuffer	= MAX_PATH;
	}

	cbBuffer = min(cbBuffer - 1, m_nPathLength);
	_tcsncpy (pszBuffer, m_pszPathPart, cbBuffer);
	pszBuffer[cbBuffer - 1] = 0;
	return pszBuffer;
}

LPCTSTR YUNC::BuildLocalName (LPTSTR pszBuffer, UINT cbBuffer)
{
	if ( !IsAdministrative () ) {
		return NULL;
	}
	if ( !pszBuffer ) {
		pszBuffer	= m_szBuffer;
		cbBuffer	= MAX_PATH;
	}
	int iLen = _sntprintf (pszBuffer, cbBuffer - 1, _T("%c:\\%s"), *m_pszSharePart, m_pszPathPart);
	if ( iLen < 0 ) {
		pszBuffer[cbBuffer - 1] = 0;
	}
	else {
		pszBuffer[iLen] = 0;
	}
	return pszBuffer;
}


#ifndef YLB_ENABLE_INLINE
#include <yUNC.inl>
#endif

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////