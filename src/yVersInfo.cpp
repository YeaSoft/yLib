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
 * FILENAME		:	yVersInfo.cpp
 * PURPOSE		:	Implementation of the version information handler class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yVersInfo.h
 *============================================================================*/
#include "StdInc.hpp"

TCHAR YVersInfo::m_szComments[]			= _T("Comments");
TCHAR YVersInfo::m_szInternalName[]		= _T("InternalName");
TCHAR YVersInfo::m_szProductName[]		= _T("ProductName");
TCHAR YVersInfo::m_szCompanyName[]		= _T("CompanyName");
TCHAR YVersInfo::m_szLegalCopyright[]	= _T("LegalCopyright");
TCHAR YVersInfo::m_szProductVersion[]	= _T("ProductVersion");
TCHAR YVersInfo::m_szFileDescription[]	= _T("FileDescription");
TCHAR YVersInfo::m_szLegalTrademarks[]	= _T("LegalTrademarks");
TCHAR YVersInfo::m_szPrivateBuild[]		= _T("PrivateBuild");
TCHAR YVersInfo::m_szFileVersion[]		= _T("FileVersion");
TCHAR YVersInfo::m_szOriginalFilename[]	= _T("OriginalFilename");
TCHAR YVersInfo::m_szSpecialBuild[]		= _T("SpecialBuild");

YVersInfo::YVersInfo (const YVersInfo &cvi)
{
	CommonConstructor ();

	if ( cvi.m_pVerInfo ) {
		m_pVerInfo = malloc (cvi.m_dwVerInfoSize);
		if ( m_pVerInfo ) {
			memcpy ((void *) m_pVerInfo, cvi.m_pVerInfo, cvi.m_dwVerInfoSize);
			m_dwVerInfoSize = cvi.m_dwVerInfoSize;
			m_dwLastError	= cvi.m_dwLastError;
			m_pvsFixedInfo	= cvi.m_pvsFixedInfo;
		}
	}
	if ( *cvi.m_szFileName ) {
		_tcscpy (m_szFileName, cvi.m_szFileName);
	}
}

YVersInfo::YVersInfo (LPCTSTR lpszFileName, ...)
{
	va_list			va;

	CommonConstructor ();

	va_start (va, lpszFileName);
	_vstprintf (m_szFileName, lpszFileName, va);
	va_end (va);
}

void YVersInfo::SetName (LPCTSTR lpszFileName, ...)
{
	va_list			va;

	UnloadInfo ();

	va_start (va, lpszFileName);
	_vstprintf (m_szFileName, lpszFileName, va);
	va_end (va);
}

void YVersInfo::CommonConstructor (DWORD dwErr /* = NOERROR */)
{
	m_pVerInfo		= NULL;
	m_dwVerInfoSize	= 0;
	m_dwLastError	= dwErr;
	m_pvsFixedInfo	= NULL;
	m_lpTranslate	= NULL;
	m_dwNumLang		= 0;
	if ( dwErr != NOERROR ) {
		m_szFileName[0]	= 0;
	}
}

BOOL YVersInfo::LoadInfo ()
{
	if ( m_pVerInfo ) {
		return TRUE;
	}
	DWORD	dwDummy;
	UINT	uDummy;

	m_dwVerInfoSize = GetFileVersionInfoSize ((LPTSTR) m_szFileName, &dwDummy);
	if ( !m_dwVerInfoSize ) {
		CommonConstructor (GetLastError ());
		return FALSE;
	}
	m_pVerInfo = malloc (m_dwVerInfoSize);
	if ( !m_pVerInfo ) {
		CommonConstructor (ERROR_NOT_ENOUGH_MEMORY);
		return FALSE;
	}

	if ( !GetFileVersionInfo ((LPTSTR) m_szFileName, 0, m_dwVerInfoSize, m_pVerInfo) ) {
		free (m_pVerInfo);
		CommonConstructor (GetLastError ());
		return FALSE;
	}
	if ( !VerQueryValue (m_pVerInfo, TEXT("\\"), (LPVOID *) &m_pvsFixedInfo, &uDummy) ) {
		m_pvsFixedInfo = NULL;
	}
	if ( uDummy < sizeof (VS_FIXEDFILEINFO) ) {
		m_pvsFixedInfo = NULL;
	}
	return TRUE;
}

void YVersInfo::UnloadInfo ()
{
	if ( m_pVerInfo ) {
		free ((void *) m_pVerInfo);
		m_pVerInfo = NULL;
	}
	m_dwVerInfoSize	= 0;
	m_dwLastError	= NOERROR;
	m_pvsFixedInfo	= NULL;
	m_lpTranslate	= NULL;
	m_dwNumLang		= 0;
}

BOOL YVersInfo::GetFirstLanguage (LPWORD pwLangCode, LPWORD pwCodePage)
{
	LoadInfo ();
	if ( !m_pVerInfo ) {
		return FALSE;
	}

	UINT	cbSize;

	if ( !::VerQueryValue (m_pVerInfo, TEXT("\\VarFileInfo\\Translation"), (LPVOID *) &m_lpTranslate, &cbSize) ) {
		m_lpTranslate	= NULL;
		m_dwNumLang		= 0;
	}
	m_dwNumLang = cbSize / sizeof(LANGANDCODEPAGE);
	return GetNextLanguage (pwLangCode, pwCodePage);
}

BOOL YVersInfo::GetNextLanguage (LPWORD pwLangCode, LPWORD pwCodePage)
{
	if ( m_lpTranslate && m_dwNumLang ) {
		--m_dwNumLang;
		if ( pwLangCode ) {
			*pwLangCode = m_lpTranslate->wLanguage;
		}
		if ( pwCodePage ) {
			*pwCodePage = m_lpTranslate->wCodePage;
		}
		++m_lpTranslate;
		return TRUE;
	}
	return FALSE;
}

LPCTSTR  YVersInfo::QueryValue (WORD wLangCode, WORD wCodePage, LPCTSTR pszName)
{
	LoadInfo ();
	if ( !m_pVerInfo ) {
		return FALSE;
	}

	YString256	ysQuery;
	LPCTSTR		lpReturn;
	UINT		cbSize;

	ysQuery.Format (_T("\\StringFileInfo\\%04x%04x\\FileDescription"), wLangCode, wCodePage);


	if ( !::VerQueryValue (m_pVerInfo, ysQuery.GetBuffer (), (LPVOID *) &lpReturn, &cbSize) ) {
		return NULL;
	}
	return lpReturn;
}

LPCTSTR  YVersInfo::QueryValue (LPCTSTR pszName)
{
	WORD wLanguage, wCodePage;
	for ( BOOL bFound = GetFirstLanguage (&wLanguage, &wCodePage); bFound; bFound = GetNextLanguage (&wLanguage, &wCodePage) ) {
		LPCTSTR lpPtr = QueryValue (wLanguage, wCodePage, pszName);
		if ( lpPtr && *lpPtr ) {
			return lpPtr;
		}
	}
	return NULL;
}

#ifndef YLB_ENABLE_INLINE
#include <yVersInfo.inl>
#endif

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////