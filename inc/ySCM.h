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
 * FILENAME		:	ySCM.hpp
 * PURPOSE		:	The service control manager class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.3  2001/05/25 14:28:21  leopoldo
 * Improved YServiceControlManager::StatusGet
 *
 * Revision 1.2  2000/09/04 11:59:53  leopoldo
 * Updated license to zlib/libpng
 *
 * Revision 1.1  2000/05/26 14:03:27  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | ySCM.h
 *============================================================================*/
#ifndef __ySCM_h__
#define __ySCM_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yLibBase_h__
#include <yLibBase.h>
#endif

/*=============================================================================
 * FORWARD CLASS DECLARATIONS
 *============================================================================*/
class YServiceControlManager;
class YService;

/*=============================================================================
 * TYPE DEFINITIONS
 *============================================================================*/
typedef BOOL (CALLBACK* ENUM_SERVICES_PROC) (
	DWORD					dwData,
	ENUM_SERVICE_STATUS&	Service
);

/*=============================================================================
 * SERVICE CONTROL MANAGER CLASS DEFINITION
 *============================================================================*/
class YServiceControlManager
{
private:
	// kill these construction methods & operators
	YServiceControlManager		(const YServiceControlManager &);
	YServiceControlManager		&operator=				(const YServiceControlManager &);

public:
	// construction/destruction
	YServiceControlManager		();
	~YServiceControlManager		();

public:
	// operations on SCM
	BOOL						Open					(DWORD dwDesiredAccess = GENERIC_READ | GENERIC_EXECUTE, LPCTSTR lpMachineName = NULL, LPCTSTR lpDatabaseName = SERVICES_ACTIVE_DATABASE);
	void						Close					();
	BOOL						Lock					();
	BOOL						Unlock					();

	BOOL						Attach					(SC_HANDLE hSCM);
	SC_HANDLE					Detach					();

public:
	// attributes of SCM
	operator					SC_HANDLE				() const;

	LPQUERY_SERVICE_LOCK_STATUS	AllocQueryLockStatus	() const;
	void						FreeQueryLockStatus		(LPQUERY_SERVICE_LOCK_STATUS &lpSLS) const;


public:
	// attributes of services
	BOOL						IsService				(LPCTSTR pszServiceName) const;
	BOOL						StatusGet				(LPCTSTR pszServiceName, LPSERVICE_STATUS lpServiceStatus) const;
	DWORD						StatusGet				(LPCTSTR pszServiceName) const;
	BOOL						IsRunning				(LPCTSTR pszServiceName) const;
	LPQUERY_SERVICE_CONFIG		AllocQueryConfig		(LPCTSTR pszServiceName) const;
	void						FreeQueryConfig			(LPQUERY_SERVICE_CONFIG &lpSc) const;
	BOOL						EnumServices			(ENUM_SERVICES_PROC lpEnumServicesFunc, DWORD dwUserData = 0, DWORD dwServiceType = SERVICE_WIN32, DWORD dwServiceState = SERVICE_STATE_ALL) const;


public:
	// operations on services
	BOOL						Start					(LPCTSTR pszServiceName) const;
	BOOL						Stop					(LPCTSTR pszServiceName) const;
	BOOL						Pause					(LPCTSTR pszServiceName) const;
	BOOL						Resume					(LPCTSTR pszServiceName) const;

	BOOL						OpenService				(YService &svc, LPCTSTR pszServiceName, DWORD dwDesiredAccess = GENERIC_EXECUTE) const;
	BOOL						CreateService			(
														YService	&svc,
														LPCTSTR		lpServiceName,
														LPCTSTR		lpDisplayName,
														DWORD		dwDesiredAccess,
														DWORD		dwServiceType,
														DWORD		dwStartType,
														DWORD		dwErrorControl,
														LPCTSTR		lpBinaryPathName,
														LPCTSTR		lpLoadOrderGroup = NULL,
														LPDWORD		lpdwTagId = NULL,
														LPCTSTR		lpDependencies = NULL,
														LPCTSTR		lpServiceStartName = NULL,
														LPCTSTR		lpPassword = NULL
														);

private:
	SC_HANDLE					m_hSCM;
	SC_LOCK						m_hLock;
};

/*=============================================================================
 * RELATED MAKROS
 *============================================================================*/
#define SERVICE_UNKNOWN			0xffffffff

/*=============================================================================
 * SERVICE CLASS DEFINITION
 *============================================================================*/
class YService
{
public:
	// construction/destruction
	YService					(SC_HANDLE hSCM = NULL, SC_HANDLE hService = NULL);
	~YService					();

public:
	// attributes
	BOOL						IsOpen					() const;

public:
	// operations
	BOOL						Attach					(SC_HANDLE hService);
	BOOL						Attach					(SC_HANDLE hSCM, SC_HANDLE hService);
	SC_HANDLE					Detach					(SC_HANDLE *phSCM = NULL);

	BOOL						Create					(
														LPCTSTR	lpServiceName,
														LPCTSTR	lpDisplayName,
														DWORD	dwDesiredAccess,
														DWORD	dwServiceType,
														DWORD	dwStartType,
														DWORD	dwErrorControl,
														LPCTSTR	lpBinaryPathName,
														LPCTSTR	lpLoadOrderGroup = NULL,
														LPDWORD	lpdwTagId = NULL,
														LPCTSTR	lpDependencies = NULL,
														LPCTSTR	lpServiceStartName = NULL,
														LPCTSTR	lpPassword = NULL
														);
	BOOL						Open					(LPCTSTR pszServiceName, DWORD dwDesiredAccess = GENERIC_READ|GENERIC_EXECUTE);
	void						Close					();
	BOOL						Delete					(BOOL bAutoClose = TRUE);
	BOOL						Start					(DWORD dwNumServiceArgs = 0, LPCTSTR *lpServiceArgVectors = NULL) const;
	BOOL						Stop					(LPSERVICE_STATUS lpServiceStatus = NULL) const;
	BOOL						Pause					(LPSERVICE_STATUS lpServiceStatus = NULL) const;
	BOOL						Continue				(LPSERVICE_STATUS lpServiceStatus = NULL) const;
	BOOL						Control					(DWORD dwControl, LPSERVICE_STATUS lpServiceStatus = NULL) const;
	BOOL						QueryStatus				(LPSERVICE_STATUS lpServiceStatus);
	DWORD						QueryStatus				();


private:
	SC_HANDLE					m_hSCM;
	SC_HANDLE					m_hService;
};

#ifdef YLB_ENABLE_INLINE
#include <ySCM.inl>
#endif

#endif //__ySCM_h__

//
// EoF
////////
