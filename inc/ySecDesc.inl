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
 * FILENAME		:	ySecDesc.inl
 * PURPOSE		:	Inline members of the security descriptor classes
 * CREDITS		:	Based on work of Peter Kenyon
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:03:30  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | ySecDesc.h
 *============================================================================*/

/*=============================================================================
 * YSecurityAttributes Implementation
 *============================================================================*/
YLB_INLINE YSecurityAttributes::YSecurityAttributes ()
{
	lpSecurityDescriptor	= NULL;
	bInheritHandle			= FALSE;
	nLength					= sizeof (SECURITY_ATTRIBUTES);
}

YLB_INLINE YSecurityAttributes::YSecurityAttributes (PSECURITY_DESCRIPTOR pSD, BOOL bCanInheritHandle /* = FALSE */)
{
	lpSecurityDescriptor	= (LPVOID) pSD;
	bInheritHandle			= bCanInheritHandle;
	nLength					= sizeof (SECURITY_ATTRIBUTES);
}

YLB_INLINE BOOL YSecurityAttributes::GetInheritance () const
{
	return bInheritHandle;
}

YLB_INLINE void YSecurityAttributes::SetInheritance (BOOL bInherit)
{
	bInheritHandle = bInherit;
}

YLB_INLINE PSECURITY_DESCRIPTOR YSecurityAttributes::GetSecurityDescriptor	() const
{
	return lpSecurityDescriptor;
}

YLB_INLINE void YSecurityAttributes::SetSecurityDescriptor	(PSECURITY_DESCRIPTOR pSD)
{
	lpSecurityDescriptor = pSD;
}

YLB_INLINE YSecurityAttributes::operator LPSECURITY_ATTRIBUTES()
{
	return this;
}

/*=============================================================================
 * YSid Implementation
 *============================================================================*/
YLB_INLINE YSid::YSid ()
{
	pCommonConstructor ();
}

YLB_INLINE YSid::~YSid ()
{
	FreeSid ();
}

// Creates a SID with no members
YLB_INLINE BOOL YSid::CreateNullSid ()
{
	SID_IDENTIFIER_AUTHORITY sidAuth = SECURITY_NULL_SID_AUTHORITY;
	return AllocateAndInitializeSid (
		&sidAuth,
		1,
        SECURITY_NULL_RID,
        0, 0, 0, 0, 0, 0, 0
	);
}

// Creates a SID representing all users everywhere.
YLB_INLINE BOOL YSid::CreateEveryoneSid ()
{
	SID_IDENTIFIER_AUTHORITY sidAuth = SECURITY_WORLD_SID_AUTHORITY;
	return AllocateAndInitializeSid (
		&sidAuth,
		1,
        SECURITY_WORLD_RID,
        0, 0, 0, 0, 0, 0, 0
	);
}

// Creates a SID representing the user who created an object
YLB_INLINE BOOL YSid::CreateCreatorOwnerSid ()
{
	SID_IDENTIFIER_AUTHORITY sidAuth = SECURITY_CREATOR_SID_AUTHORITY;
	return AllocateAndInitializeSid (
		&sidAuth,
		1,
        SECURITY_CREATOR_OWNER_RID,
        0, 0, 0, 0, 0, 0, 0
	);
}

// Creates a SID representing the group the user who who created an 
// object belongs to.
YLB_INLINE BOOL YSid::CreateCreatorGroupSid ()
{
	SID_IDENTIFIER_AUTHORITY sidAuth = SECURITY_CREATOR_SID_AUTHORITY;
	return AllocateAndInitializeSid (
		&sidAuth,
		1,
        SECURITY_CREATOR_GROUP_RID,
        0, 0, 0, 0, 0, 0, 0
	);
}

// This SID represents any user physically logged into the current workstation.
// Can be used to grant access to logged-on users as opposed to users
// accessing data across the network.
YLB_INLINE BOOL YSid::CreateInteractiveUserSid ()
{
	SID_IDENTIFIER_AUTHORITY sidAuth = SECURITY_NT_AUTHORITY;
	return AllocateAndInitializeSid (
		&sidAuth,
		1,
        SECURITY_INTERACTIVE_RID,
        0, 0, 0, 0, 0, 0, 0
	);
}

// Creates a SID representing all users on the local machine
YLB_INLINE BOOL YSid::CreateLocalUserSid ()
{
	SID_IDENTIFIER_AUTHORITY sidAuth = SECURITY_NT_AUTHORITY;
	return AllocateAndInitializeSid (
		&sidAuth,
		2,
        SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_USERS,
        0, 0, 0, 0, 0, 0
	);
}

// Creates a SID representing anybody who is a member of the built-in
// Administrators group on the local computer.
YLB_INLINE BOOL YSid::CreateLocalAdminSid ()
{
	SID_IDENTIFIER_AUTHORITY sidAuth = SECURITY_NT_AUTHORITY;
	return AllocateAndInitializeSid (
		&sidAuth,
		2,
        SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0
	);
}

// Creates a SID representing the built-in Guests group.
YLB_INLINE BOOL YSid::CreateLocalGuestSid ()
{
	SID_IDENTIFIER_AUTHORITY sidAuth = SECURITY_NT_AUTHORITY;
	return AllocateAndInitializeSid (
		&sidAuth,
		2,
        SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_GUESTS,
        0, 0, 0, 0, 0, 0
	);
}

// A Power User is a user who "expects to treat a system as if it 	
// were their personal computer rather than as a workstation for 
// multiple users" - Platform SDK
YLB_INLINE BOOL YSid::CreateLocalPowerUserSid ()
{
	SID_IDENTIFIER_AUTHORITY sidAuth = SECURITY_NT_AUTHORITY;
	return AllocateAndInitializeSid (
		&sidAuth,
		2,
        SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_POWER_USERS,
        0, 0, 0, 0, 0, 0
	);
}

YLB_INLINE BOOL YSid::AllocateAndInitializeSid (
	PSID_IDENTIFIER_AUTHORITY	pIA,
	BYTE						nSACount,
	DWORD						nSA0,
	DWORD						nSA1,
	DWORD						nSA2,
	DWORD						nSA3,
	DWORD						nSA4,
	DWORD						nSA5,
	DWORD						nSA6,
	DWORD						nSA7
)
{
	FreeSid ();

	if ( ::AllocateAndInitializeSid (pIA, nSACount, nSA0, nSA1, nSA2, nSA3, nSA4, nSA5, nSA6, nSA7, &m_pSid) ) {
		m_bSystemAllocated = TRUE;
		return TRUE;
	}
	else {
		return FALSE;
	}
}

YLB_INLINE DWORD YSid::GetLengthSid () const
{
	if ( IsValid () ) {
		return ::GetLengthSid (m_pSid);
	}
	return 0;
}

YLB_INLINE PDWORD YSid::GetSidSubAuthority (DWORD dwSubAuthority) const
{
	if ( IsValid () ) {
		return ::GetSidSubAuthority (m_pSid, dwSubAuthority);
	}
	return NULL;
}

YLB_INLINE PUCHAR YSid::GetSidSubAuthorityCount	() const
{
	if ( IsValid () ) {
		return ::GetSidSubAuthorityCount (m_pSid);
	}
	return NULL;
}

YLB_INLINE BOOL YSid::IsValid () const
{
	return m_pSid && ::IsValidSid (m_pSid);
}

YLB_INLINE YSid::operator PSID ()
{
	return m_pSid;
}

YLB_INLINE BOOL YSid::operator==(YSid sid)
{
	return ::EqualSid (sid.m_pSid, m_pSid);
}

YLB_INLINE void YSid::pCommonConstructor ()
{
	m_pSid				= NULL;
	m_bSystemAllocated	= FALSE;
}


/*=============================================================================
 * YSecurityDescriptor Implementation
 *============================================================================*/
YLB_INLINE YSecurityDescriptor::YSecurityDescriptor (PSECURITY_DESCRIPTOR pSD /* = NULL */)
{
	m_pSD = pSD;
}

YLB_INLINE YSecurityDescriptor::~YSecurityDescriptor ()
{
	Free ();
}

YLB_INLINE PSID YSecurityDescriptor::Detach ()
{
	PSECURITY_DESCRIPTOR pSD = m_pSD;
	Free ();
	return pSD;
}

YLB_INLINE BOOL YSecurityDescriptor::IsValid () const
{
	return ::IsValidSecurityDescriptor (m_pSD);
}

YLB_INLINE BOOL YSecurityDescriptor::SetGroup (PSID pGroup, BOOL bGroupDefaulted) const
{
	return ::SetSecurityDescriptorGroup (m_pSD, pGroup, bGroupDefaulted);
}

YLB_INLINE BOOL YSecurityDescriptor::SetOwner (PSID pOwner, BOOL bOwnerDefaulted) const
{
	return ::SetSecurityDescriptorOwner (m_pSD, pOwner, bOwnerDefaulted);
}

YLB_INLINE BOOL YSecurityDescriptor::SetSacl (BOOL bSaclPresent, PACL pSacl, BOOL bSaclDefaulted) const
{
	return ::SetSecurityDescriptorSacl (m_pSD, bSaclPresent, pSacl, bSaclDefaulted);
}

YLB_INLINE BOOL YSecurityDescriptor::SetDacl (BOOL bDaclPresent, PACL pDacl, BOOL bDaclDefaulted) const
{
	return ::SetSecurityDescriptorDacl (m_pSD, bDaclPresent, pDacl, bDaclDefaulted);
}

YLB_INLINE BOOL YSecurityDescriptor::GetGroup (PSID* pGroup, LPBOOL lpGroupDefaulted) const
{
	return ::GetSecurityDescriptorGroup (m_pSD, pGroup, lpGroupDefaulted);
}

YLB_INLINE BOOL YSecurityDescriptor::GetOwner (PSID* pOwner, LPBOOL lpOwnerDefaulted) const
{
	return ::GetSecurityDescriptorGroup (m_pSD, pOwner, lpOwnerDefaulted);
}

YLB_INLINE BOOL YSecurityDescriptor::GetSacl (LPBOOL lpbSaclPresent, PACL* pSacl, LPBOOL lpbSaclDefaulted) const
{
	return ::GetSecurityDescriptorSacl (m_pSD, lpbSaclPresent, pSacl, lpbSaclDefaulted);
}

YLB_INLINE BOOL YSecurityDescriptor::GetDacl (LPBOOL lpbDaclPresent, PACL* pDacl, LPBOOL lpbDaclDefaulted) const
{
	return ::GetSecurityDescriptorSacl (m_pSD, lpbDaclPresent, pDacl, lpbDaclDefaulted);
}

YLB_INLINE YSecurityDescriptor::operator PSECURITY_DESCRIPTOR ()
{
	return m_pSD;
}

/*=============================================================================
 * YAcl Implementation Implementation
 *============================================================================*/
YLB_INLINE YAcl::YAcl()
{
	m_pACL = NULL;
}

YLB_INLINE YAcl::~YAcl()
{
	Free ();
}

YLB_INLINE BOOL YAcl::IsValid () const
{
	return ::IsValidAcl (m_pACL);
}

YLB_INLINE YAcl::operator PACL ()
{
	return m_pACL;
}

YLB_INLINE PACL YAcl::Detach ()
{
	PACL pAcl = m_pACL;
	m_pACL = NULL;
	return pAcl;
}

YLB_INLINE void YAcl::Free ()
{
	if ( m_pACL ) {
		::LocalFree (m_pACL);
		m_pACL = NULL;
	}
}

YLB_INLINE BOOL YAcl::AddAce (DWORD dwStartingAceIndex, LPVOID pAceList, DWORD nAceListLength)
{
	return ::AddAce (m_pACL, ACL_REVISION, dwStartingAceIndex, pAceList, nAceListLength);
}

YLB_INLINE BOOL YAcl::AddAccessAllowedAce (DWORD dwAccessMask, PSID pSID)
{
	return ::AddAccessAllowedAce (m_pACL, ACL_REVISION, dwAccessMask, pSID);
}

YLB_INLINE BOOL YAcl::AddAccessDeniedAce (DWORD dwAccessMask, PSID pSID)
{
	return ::AddAccessDeniedAce (m_pACL, ACL_REVISION, dwAccessMask, pSID);
}

YLB_INLINE BOOL YAcl::AddAuditAccessAce (DWORD dwAccessMask, PSID pSid, BOOL bAuditSuccess, BOOL bAuditFailure)
{
	return ::AddAuditAccessAce (m_pACL, ACL_REVISION, dwAccessMask, pSid, bAuditSuccess, bAuditFailure);
}

YLB_INLINE BOOL YAcl::DeleteAce (DWORD dwAceIndex)
{
	return ::DeleteAce (m_pACL, dwAceIndex);
}

YLB_INLINE BOOL YAcl::FindFirstFreeAce (LPVOID * pAce)
{
	return ::FindFirstFreeAce (m_pACL, pAce);
}

YLB_INLINE BOOL YAcl::GetAce (DWORD dwAceIndex, LPVOID* pAce)
{
	return ::GetAce (m_pACL, dwAceIndex, pAce);
}

/*=============================================================================
 * YExplicitAccess Implementation
 *============================================================================*/
YLB_INLINE YExplicitAccess::YExplicitAccess ()
{
}

YLB_INLINE YExplicitAccess::YExplicitAccess (DWORD dwAccessPermissions, ACCESS_MODE am, DWORD dwInheritance, TRUSTEE trAppliesTo)
{
	grfAccessPermissions	= dwAccessPermissions;
	grfAccessMode			= am;
	grfInheritance			= dwInheritance;
	Trustee					= trAppliesTo;
}

/*=============================================================================
 * YTrustee Implementation
 *============================================================================*/
YLB_INLINE YTrustee::YTrustee ()
{ 
	pMultipleTrustee			= NULL; 
	MultipleTrusteeOperation	= NO_MULTIPLE_TRUSTEE; 
}

YLB_INLINE YTrustee::YTrustee (TRUSTEE_TYPE type, LPCTSTR pszTrustee)
{
	pMultipleTrustee			= NULL; 
	MultipleTrusteeOperation	= NO_MULTIPLE_TRUSTEE; 
	TrusteeForm					= TRUSTEE_IS_NAME;
	ptstrName					= (LPTSTR) pszTrustee;
}

YLB_INLINE YTrustee::YTrustee (TRUSTEE_TYPE type, PSID pSid)
{
	pMultipleTrustee			= NULL; 
	MultipleTrusteeOperation	= NO_MULTIPLE_TRUSTEE; 
	TrusteeForm					= TRUSTEE_IS_SID;
	ptstrName					= (LPTSTR) pSid;
}

//
// EoF
////////