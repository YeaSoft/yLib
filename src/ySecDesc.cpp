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
 * FILENAME		:	ySecDesc.cpp
 * PURPOSE		:	Implementation of the security descriptor classes
 * CREDITS		:	Based on work of Peter Kenyon
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:05:09  leo
 * Initial revision
 *
 *============================================================================*/

#include "StdInc.hpp"

/*=============================================================================
 * @doc YLIB | ySecDesc.h
 *============================================================================*/
YSid::YSid (WELLKNOWN_SID_TYPE type)
{
	pCommonConstructor ();

	switch( type ) {
	default:
	case WST_NULL:
		CreateNullSid ();
		break;
	case WST_EVERYONE:
		CreateEveryoneSid ();
		break;
	case WST_CREATOROWNER:
		CreateCreatorOwnerSid ();
		break;
	case WST_CREATORGROUP:
		CreateCreatorGroupSid ();
		break;
	case WST_INTERACTIVE:
		CreateInteractiveUserSid ();
		break;
	case WST_LOCALUSERS:
		CreateLocalUserSid ();
		break;
	case WST_LOCALADMINS:
		CreateLocalAdminSid ();
		break;
	case WST_LOCALGUESTS:
		CreateLocalGuestSid ();
		break;
	case WST_LOCALPOWERUSERS:
		CreateLocalPowerUserSid ();
		break;
	}
}

BOOL YSid::Attach (PSID pSid, BOOL bSystemAllocated /* = FALSE */)
{
	if ( (m_pSid != pSid) && ::IsValidSid (pSid) ) {
		FreeSid ();
		m_pSid				= pSid;
		m_bSystemAllocated	= bSystemAllocated;
		return TRUE;
	}
	return FALSE;
}

PSID YSid::Detach (LPBOOL pbSystemAllocated /* = NULL */)
{
	PSID	pSid = m_pSid;
	if ( pbSystemAllocated ) {
		*pbSystemAllocated = m_bSystemAllocated;
	}
	pCommonConstructor ();
	return pSid;
}

BOOL YSid::AllocateSid (DWORD dwSize)
{
	FreeSid ();

	if ( !(m_pSid = (PSID) calloc (dwSize, 1)) ) {
		return FALSE;
	}
	return TRUE;	
}

void YSid::FreeSid ()
{
	if( m_pSid ) {
		if ( m_bSystemAllocated ) {
			::FreeSid (m_pSid);
		}
		else {
			delete m_pSid;
		}
	}
	pCommonConstructor ();
}

BOOL YSid::LookupAccountName (LPCTSTR lpAccountName, LPCTSTR lpSystemName /* = NULL */, LPTSTR lpReferencedDomainName /* = NULL */, DWORD cbReferencedDomainName /* = 0 */, PSID_NAME_USE peUse /* = NULL */)
{
	DWORD			dwDomainNameSize = UNLEN + 1;
	TCHAR			szDomainName[UNLEN + 1];
	SID_NAME_USE	accountType; 
	DWORD			dwSidSize = 0;
	PSID			lpSid = NULL;

	if ( !::LookupAccountName (lpSystemName, lpAccountName, NULL, &dwSidSize, szDomainName, &dwDomainNameSize, &accountType) ) {
		if ( !(lpSid = (PSID) malloc (dwSidSize)) ) {
			// crushed heap!
			return FALSE;
		}
		if ( ::LookupAccountName (lpSystemName, lpAccountName, lpSid , &dwSidSize, szDomainName, &dwDomainNameSize, &accountType) ) {
			FreeSid ();
			m_pSid = lpSid;
			if ( lpReferencedDomainName ) {
				_tcsncpy (lpReferencedDomainName, szDomainName, cbReferencedDomainName - 1);
				lpReferencedDomainName[cbReferencedDomainName - 1] = 0;
			}
			if ( peUse ) {
				*peUse = accountType;
			}
			return TRUE;
		}
		free (lpSid);
	}
	return FALSE;
}

BOOL YSecurityDescriptor::Attach (PSECURITY_DESCRIPTOR pSD)
{
	if ( (m_pSD != pSD) && ::IsValidSecurityDescriptor (pSD) ) {
		Free ();
		m_pSD	= pSD;
		return TRUE;
	}
	return FALSE;
}

BOOL YSecurityDescriptor::Create ()
{
	PSECURITY_DESCRIPTOR pSD = ::LocalAlloc (LMEM_FIXED, SECURITY_DESCRIPTOR_MIN_LENGTH);
	if ( !pSD ) {
		return FALSE;
	}
	if ( !::InitializeSecurityDescriptor (pSD, SECURITY_DESCRIPTOR_REVISION) ) {
		::LocalFree (pSD);
		return FALSE;
	}
	Free ();
	m_pSD = pSD;
	return TRUE;
}

void YSecurityDescriptor::Free ()
{
	if ( m_pSD ) {
		::LocalFree (m_pSD);
		m_pSD = NULL;
	}
}


/*=============================================================================
 * YAcl Implementation
 *============================================================================*/
void YAcl::Attach (PACL pAcl)
{
	if ( m_pACL != pAcl ) {
		Free ();
		m_pACL = pAcl;
	}
}

BOOL YAcl::Initialize (DWORD nAclLength)
{
	PACL	pAcl = (PACL) ::LocalAlloc (LMEM_FIXED, nAclLength);
	if ( !pAcl ) {
		return FALSE;
	}
	if ( ::InitializeAcl (pAcl, nAclLength, ACL_REVISION) ) {
		Free ();
		m_pACL = pAcl;
		return TRUE;
	}
	::LocalFree (pAcl);
	return FALSE;
}

DWORD YAcl::SetEntriesInAcl (ULONG cCountOfExplicitEntries, PEXPLICIT_ACCESS pListOfExplicitEntries)
{
	if ( !IsValid () ) {
		return ERROR_INVALID_DATA;
	}

	PACL	paclNew;
	DWORD	dwRes = ::SetEntriesInAcl (
		cCountOfExplicitEntries,
		pListOfExplicitEntries,
		m_pACL,
		&paclNew
	);

	if( dwRes == ERROR_SUCCESS ) {
		Free ();
		m_pACL = paclNew;
	}

	return dwRes;
}

/*=============================================================================
 * YExplicitAccess Implementation
 *============================================================================*/

#ifndef YLB_ENABLE_INLINE
#include "ySecDesc.inl"
#endif


/// RCS STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EOF
////////