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
 * FILENAME		:	yEventSource.cpp
 * PURPOSE		:	Implementation of the Eventlog source class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.2  2000/09/04 12:07:43  leopoldo
 * Updated license to zlib/libpng
 *
 * Revision 1.1  2000/05/26 14:04:56  leo
 * Initial revision
 *
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
	DWORD		dwCount;

	// initialize with inserts
	if ( m_dwNumInserts && m_lplpInserts ) {
		memcpy (lpStrArr, m_lplpInserts, m_dwNumInserts * sizeof (LPCTSTR));
	}
	for ( dwCount = m_dwNumInserts; ((lpStrArr[dwCount] = va_arg (va, LPCTSTR)) != NULL) && (dwCount < (256 - m_dwNumInserts)); dwCount++ ) {
		/*TUNIX*/
	}
	return ReportEvent (wType, wCategory, dwEventID, m_pSID, (WORD) dwCount, lpStrArr);
}

BOOL YEventLogSource::ReportVa (WORD wType, DWORD dwEventID, va_list va) const
{
	LPCTSTR		lpStrArr[256];
	DWORD		dwCount;

	// initialize with inserts
	if ( m_dwNumInserts && m_lplpInserts ) {
		memcpy (lpStrArr, m_lplpInserts, m_dwNumInserts * sizeof (LPCTSTR));
	}
	for ( dwCount = m_dwNumInserts; ((lpStrArr[dwCount] = va_arg (va, LPCTSTR)) != NULL) && (dwCount < (256 - m_dwNumInserts)); dwCount++ ) {
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
//LPCTSTR lpComment = _T("$Id$");

//
// EoF
////////