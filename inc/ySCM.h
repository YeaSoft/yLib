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
 * FILENAME		:	ySCM.hpp
 * PURPOSE		:	The service control manager class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
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
	BOOL						Open					(LPCTSTR pszServiceName, DWORD dwDesiredAccess = GENERIC_EXECUTE);
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
