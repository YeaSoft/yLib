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
 * FILENAME		:	yEventSource.cpp
 * PURPOSE		:	Implementation of the Eventlog source class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

#include "StdInc.hpp"

/*=============================================================================
 * @doc YLIB | yEventSource.h
 *============================================================================*/
static LPCTSTR pszEventApp		= _T("SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application\\");
static LPCTSTR pszEventSrc		= _T("EventMessageFile");
static LPCTSTR pszEventTypes	= _T("TypesSupported");
static LPCTSTR pszEventSources	= _T("Sources");
static LPCTSTR pszCatSrc		= _T("CategoryMessageFile");
static LPCTSTR pszCatCount		= _T("CategoryCount");

static BOOL		sfInstall	(HKEY hStartKey, LPCTSTR lpSourceName, LPCTSTR lpEventMessageFile, UINT cbCategoryCount, LPCTSTR lpCategoryMessageFile, DWORD dwTypesSupported);
static BOOL		sfUninstall	(HKEY hStartKey, LPCTSTR lpSourceName);

/*=============================================================================
 * IMPLEMENTATION
 *============================================================================*/
BOOL YEventLogSource::Register (LPCTSTR lpSourceName, LPCTSTR lpUNCServerName /* = NULL */)
{
	Deregister ();
	if ( !(m_hEventSource = ::RegisterEventSource (lpUNCServerName, lpSourceName)) ) {
		return FALSE;
	}
	return TRUE;
}

BOOL YEventLogSource::Deregister ()
{
	if ( m_hEventSource != NULL ) {
		if ( !::DeregisterEventSource (m_hEventSource) ) {
			return FALSE;
		}
		m_hEventSource = NULL;
	}
	return TRUE;
}

BOOL YEventLogSource::Install (LPCTSTR lpSourceName, LPCTSTR lpEventMessageFile, UINT cbCategoryCount /* = 0 */, LPCTSTR lpCategoryMessageFile /* = NULL */, DWORD dwTypesSupported /* = EVENTLOG_ALL_STD */)
{
	return sfInstall (HKEY_LOCAL_MACHINE, lpSourceName, lpEventMessageFile, cbCategoryCount, lpCategoryMessageFile, dwTypesSupported);
}

BOOL YEventLogSource::Install (LPCTSTR lpComputerName, LPCTSTR lpSourceName, LPCTSTR lpEventMessageFile, UINT cbCategoryCount /* = 0 */, LPCTSTR lpCategoryMessageFile /* = NULL */, DWORD dwTypesSupported /* = EVENTLOG_ALL_STD */)
{
	ASSERTY(lpSourceName);
	ASSERTY(lpEventMessageFile);

	YRegistry regRemote(HKEY_LOCAL_MACHINE);
	if ( lpComputerName && *lpComputerName && !regRemote.Connect (lpComputerName) ) {
		return FALSE;
	}
	return sfInstall (regRemote, lpSourceName, lpEventMessageFile, cbCategoryCount, lpCategoryMessageFile, dwTypesSupported);
}

BOOL YEventLogSource::Uninstall (LPCTSTR lpSourceName, LPCTSTR lpComputerName)
{
	ASSERTY(lpSourceName);

	if ( lpComputerName && *lpComputerName ) {
		YRegistry regRemote;
		if ( !regRemote.Connect (lpComputerName) ) {
			return FALSE;
		}
		return sfUninstall (regRemote, lpSourceName);
	}
	return sfUninstall (HKEY_LOCAL_MACHINE, lpSourceName);
}

BOOL YEventLogSource::SetOriginatorSID (LPCTSTR lpszUserName /* = NULL */)
{
	DWORD			dwUserNameSize = UNLEN + 1;
	TCHAR			szUserName[UNLEN + 1];
	DWORD			dwDomainNameSize = UNLEN + 1;
	TCHAR			szDomainName[UNLEN + 1];
	SID_NAME_USE	accountType; 
	DWORD			dwSidSize = 0;
	PSID			lpSid = NULL;

	if ( !lpszUserName ) {
		::GetUserName (szUserName, &dwUserNameSize);
		lpszUserName = szUserName;
	}

	if ( !::LookupAccountName (NULL, lpszUserName, NULL, &dwSidSize, szDomainName, &dwDomainNameSize, &accountType) ) {
		if ( !(lpSid = (PSID) malloc (dwSidSize)) ) {
			// crushed heap!
			return FALSE;
		}
		if ( ::LookupAccountName (NULL, lpszUserName, lpSid , &dwSidSize, szDomainName, &dwDomainNameSize, &accountType) ) {
			if ( m_pSID && m_bSidAllocated ) {
				free (m_pSID);
			}
			m_bSidAllocated	= TRUE;
			m_pSID			= lpSid;
			return TRUE;
		}
		free (lpSid);
	}
	return FALSE;
}

BOOL YEventLogSource::ReportVa (WORD wType, WORD wCategory, DWORD dwEventID, va_list va) const
{
	LPCTSTR		lpStrArr[256];

	// initialize with inserts
	if ( m_dwNumInserts && m_lplpInserts ) {
		memcpy (lpStrArr, m_lplpInserts, m_dwNumInserts * sizeof (LPCTSTR));
	}
	for ( DWORD dwCount = m_dwNumInserts; ((lpStrArr[dwCount] = va_arg (va, LPCTSTR)) != NULL) && (dwCount < (256 - m_dwNumInserts)); dwCount++ ) {
		/*TUNIX*/
	}
	return ReportEvent (wType, wCategory, dwEventID, m_pSID, (WORD) dwCount, lpStrArr);
}

BOOL YEventLogSource::ReportVa (WORD wType, DWORD dwEventID, va_list va) const
{
	LPCTSTR		lpStrArr[256];

	// initialize with inserts
	if ( m_dwNumInserts && m_lplpInserts ) {
		memcpy (lpStrArr, m_lplpInserts, m_dwNumInserts * sizeof (LPCTSTR));
	}
	for ( DWORD dwCount = m_dwNumInserts; ((lpStrArr[dwCount] = va_arg (va, LPCTSTR)) != NULL) && (dwCount < (256 - m_dwNumInserts)); dwCount++ ) {
		/*TUNIX*/
	}
	return ReportEvent (wType, m_wCategory, dwEventID, m_pSID, (WORD) dwCount, lpStrArr);
}

static BOOL sfInstall (HKEY hStartKey, LPCTSTR lpSourceName, LPCTSTR lpEventMessageFile, UINT cbCategoryCount, LPCTSTR lpCategoryMessageFile, DWORD dwTypesSupported)
{
	ASSERTY(lpSourceName);
	ASSERTY(lpEventMessageFile);

	YRegistry	regApp(hStartKey);

	if ( !regApp.Open (pszEventApp, KEY_WRITE | KEY_READ) ) {
		return FALSE;
	}


	try {
		YRegistry regSrc (regApp.GetHandle ());

		if ( !regSrc.Create (lpSourceName, _T(""), KEY_WRITE | KEY_READ) ) {
			throw YException (::GetLastError ());
		}

		if ( !regSrc.ExpandableStringSet (pszEventSrc, lpEventMessageFile) ) {
			throw YException (::GetLastError ());
		}
		if ( !regSrc.NumberSet (pszEventTypes, dwTypesSupported) ) {
			throw YException (::GetLastError ());
		}

		if ( cbCategoryCount ) {
			if ( !regSrc.ExpandableStringSet (pszCatSrc, (lpCategoryMessageFile && *lpCategoryMessageFile) ? (lpCategoryMessageFile) : (lpEventMessageFile)) ) {
				throw YException (::GetLastError ());
			}
			if ( !regSrc.NumberSet (pszCatCount, cbCategoryCount) ) {
				throw YException (::GetLastError ());
			}
		}
	}
	catch ( YException e ) {
		e.GetLastError ();
		regApp.SectionDelete (lpSourceName);
		return FALSE;
	}

	regApp.MultiStringAdd (pszEventSources, lpSourceName);

	return TRUE;
}

static BOOL sfUninstall (HKEY hStartKey, LPCTSTR lpSourceName)
{
	ASSERTY(lpSourceName);

	YRegistry	regApp(hStartKey);

	if ( !regApp.Open (pszEventApp, KEY_WRITE | KEY_READ) ) {
		return FALSE;
	}
	if ( !regApp.SectionDelete (lpSourceName) ) {
		return FALSE;
	}

	regApp.MultiStringRemove (pszEventSources, lpSourceName);

	return TRUE;
}

#ifndef YLB_ENABLE_INLINE
#include <yEventSource.inl>
#endif

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////