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
 * FILENAME		:	ySecDesc.h
 * PURPOSE		:	Declaration of the security descriptor classes
 * CREDITS		:	Based on work of Peter Kenyon
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:03:29  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | ySecDesc.h
 *============================================================================*/
#ifndef __ySecDesc_h__
#define __ySecDesc_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yLibBase_h__
#include <yLibBase.h>
#endif

/*=============================================================================
 * FORWARD CLASS DECLARATIONS
 *============================================================================*/
class YSecurityAttributes;
class YSid;
class YSecurityDescriptor;
class YAcl;
class YExplicitAccess;
class YTrustee;

/*=============================================================================
 * CLASS DECLARATIONS
 *============================================================================*/
class YSecurityAttributes : public SECURITY_ATTRIBUTES
{
public:
	// construction
	YSecurityAttributes			();
	YSecurityAttributes			(PSECURITY_DESCRIPTOR pSD, BOOL bCanInheritHandle = FALSE);

public:
	// attributes
	BOOL						GetInheritance			() const;
	void						SetInheritance			(BOOL bInherit);
	PSECURITY_DESCRIPTOR		GetSecurityDescriptor	() const;
	void						SetSecurityDescriptor	(PSECURITY_DESCRIPTOR pSD);
	operator					LPSECURITY_ATTRIBUTES	();
};

class YSid
{
public:
	// additional types
	enum WELLKNOWN_SID_TYPE {
		WST_NULL				= 0,
		WST_EVERYONE,
		WST_CREATOROWNER,
		WST_CREATORGROUP,
		WST_INTERACTIVE,
		WST_LOCALUSERS,
		WST_LOCALADMINS,
		WST_LOCALGUESTS,
		WST_LOCALPOWERUSERS
	};

public:
	// construction/destruction
	YSid						();
	YSid						(WELLKNOWN_SID_TYPE type);
	virtual ~YSid				();

public:
	// operations
	BOOL						Attach					(PSID pSid, BOOL bSystemAllocated /* = FALSE */);
	PSID						Detach					(LPBOOL pbSystemAllocated = NULL);
	BOOL						AllocateSid				(DWORD dwSize);
	void						FreeSid					();

	BOOL						CreateNullSid			();
	BOOL						CreateEveryoneSid		();
	BOOL						CreateCreatorOwnerSid	();
	BOOL						CreateCreatorGroupSid	();
	BOOL						CreateInteractiveUserSid();
	BOOL						CreateLocalUserSid		();
	BOOL						CreateLocalAdminSid		();
	BOOL						CreateLocalGuestSid		();
	BOOL						CreateLocalPowerUserSid	();
	
	BOOL						LookupAccountName		(LPCTSTR lpAccountName, LPCTSTR lpSystemName = NULL, LPTSTR lpReferencedDomainName = NULL, DWORD cbReferencedDomainName = 0, PSID_NAME_USE peUse = NULL);
	BOOL						AllocateAndInitializeSid(PSID_IDENTIFIER_AUTHORITY pIdentifierAuthority, BYTE nSubAuthorityCount, DWORD nSubAuthority0, DWORD nSubAuthority1, DWORD nSubAuthority2, DWORD nSubAuthority3, DWORD nSubAuthority4, DWORD nSubAuthority5, DWORD nSubAuthority6, DWORD nSubAuthority7);

public:
	// attributes
	DWORD						GetLengthSid			() const;
	PDWORD						GetSidSubAuthority		(DWORD dwSubAuthority) const;
	PUCHAR						GetSidSubAuthorityCount	() const;
	BOOL						IsValid					() const;

	operator					PSID					();
	BOOL						operator==				(YSid sid);
	
protected:
	// implementation
	void						pCommonConstructor		();

protected:
	// implementation
	BOOL						m_bSystemAllocated;
	PSID						m_pSid;
};

class YSecurityDescriptor  
{
public:
	// creation/destruction
	YSecurityDescriptor			(PSECURITY_DESCRIPTOR pSD = NULL);
	virtual ~YSecurityDescriptor();

public:
	// operations
	BOOL						Attach					(PSECURITY_DESCRIPTOR pSD);
	PSECURITY_DESCRIPTOR		Detach					();
	BOOL						Create					();
	void						Free					();

public:
	// attributes
	BOOL						IsValid					() const;
	BOOL						SetGroup				(PSID pGroup, BOOL bGroupDefaulted) const;
	BOOL						SetOwner				(PSID pOwner, BOOL bOwnerDefaulted) const;
	BOOL						SetSacl					(BOOL bSaclPresent, PACL pSacl, BOOL bSaclDefaulted) const;
	BOOL						SetDacl					(BOOL bDaclPresent, PACL pDacl, BOOL bDaclDefaulted) const;
	BOOL						GetGroup				(PSID* pGroup, LPBOOL lpGroupDefaulted) const;
	BOOL						GetOwner				(PSID* pOwner, LPBOOL lpOwnerDefaulted) const;
	BOOL						GetSacl					(LPBOOL lpbSaclPresent, PACL* pSacl, LPBOOL lpbSaclDefaulted) const;
	BOOL						GetDacl					(LPBOOL lpbDaclPresent, PACL* pDacl, LPBOOL lpbDaclDefaulted) const;

	operator					PSECURITY_DESCRIPTOR	();

protected:
	// implementation
	PSECURITY_DESCRIPTOR		m_pSD;
};

class YAcl  
{
public:
	// creation/destruction
	YAcl						();
	virtual ~YAcl				();

public:
	// attributes
	BOOL						IsValid					() const;
	operator					PACL					();

public:
	// operations
	void						Attach					(PACL pAcl);
	PACL						Detach					();
	BOOL						Initialize				(DWORD nAclLength);
	void						Free					();

	DWORD						SetEntriesInAcl			(ULONG cCountOfExplicitEntries, PEXPLICIT_ACCESS pListOfExplicitEntries);

	BOOL						AddAce					(DWORD dwStartingAceIndex, LPVOID pAceList, DWORD nAceListLength);
	BOOL						AddAccessAllowedAce		(DWORD dwAccessMask, PSID pSID);
	BOOL						AddAccessDeniedAce		(DWORD dwAccessMask, PSID pSID);
	BOOL						AddAuditAccessAce		(DWORD dwAccessMask, PSID pSid, BOOL bAuditSuccess, BOOL bAuditFailure);
	BOOL						DeleteAce				(DWORD dwAceIndex);
	BOOL						FindFirstFreeAce		(LPVOID * pAce);
	BOOL						GetAce					(DWORD dwAceIndex, LPVOID* pAce);

protected:
	// implementation
	PACL						m_pACL;
};

class YExplicitAccess : public EXPLICIT_ACCESS
{
public:
	// creation/destruction
	YExplicitAccess				();
	YExplicitAccess				(DWORD dwAccessPermissions, ACCESS_MODE am, DWORD dwInheritance, TRUSTEE trAppliesTo);
};

class YTrustee : public TRUSTEE
{
public:
	// creation/destruction
	YTrustee					();
	YTrustee					(TRUSTEE_TYPE type, LPCTSTR pszTrustee);
	YTrustee					(TRUSTEE_TYPE type, PSID pSid);
};

#ifdef YLB_ENABLE_INLINE
#include <ySecDesc.inl>
#endif

#endif //__yHandle_h__
//
// EoF
////////