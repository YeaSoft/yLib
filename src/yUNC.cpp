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
 * FILENAME		:	yUNC.cpp
 * PURPOSE		:	Declaration of the UNC Class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
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