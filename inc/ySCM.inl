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
 * FILENAME		:	ySCM.inl
 * PURPOSE		:	The service control manager class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | ySCM.h
 *============================================================================*/

/*=============================================================================
 * SERVICE CONTROL MANAGER CLASS IMPLEMENTATION
 *============================================================================*/
YLB_INLINE YServiceControlManager::YServiceControlManager ()
{
	m_hSCM	= NULL;
	m_hLock	= NULL;
}

YLB_INLINE YServiceControlManager::~YServiceControlManager ()
{
	Unlock ();
	Close ();
}

YLB_INLINE YServiceControlManager::operator SC_HANDLE() const
{
	return m_hSCM;
}

YLB_INLINE void YServiceControlManager::FreeQueryLockStatus (LPQUERY_SERVICE_LOCK_STATUS &lpSLS) const
{
	if ( lpSLS ) {
		free (lpSLS);
		lpSLS = NULL;
	}
}


YLB_INLINE BOOL YServiceControlManager::IsRunning (LPCTSTR pszServiceName) const
{
	return StatusGet (pszServiceName)  != SERVICE_STOPPED;
}

YLB_INLINE void YServiceControlManager::FreeQueryConfig (LPQUERY_SERVICE_CONFIG &lpSc) const
{
	if ( lpSc ) {
		free (lpSc);
		lpSc = NULL;
	}
}

YLB_INLINE BOOL YServiceControlManager::OpenService (YService &svc, LPCTSTR pszServiceName, DWORD dwDesiredAccess) const
{
	svc.Attach (m_hSCM, NULL);
	return svc.Open (
		pszServiceName,
		dwDesiredAccess
	);
}

YLB_INLINE BOOL YServiceControlManager::CreateService (
	YService	&svc,
	LPCTSTR		lpServiceName,
	LPCTSTR		lpDisplayName,
	DWORD		dwDesiredAccess,
	DWORD		dwServiceType,
	DWORD		dwStartType,
	DWORD		dwErrorControl,
	LPCTSTR		lpBinaryPathName,
	LPCTSTR		lpLoadOrderGroup,
	LPDWORD		lpdwTagId,
	LPCTSTR		lpDependencies,
	LPCTSTR		lpServiceStartName,
	LPCTSTR		lpPassword
)
{
	svc.Attach (m_hSCM, NULL);

	return svc.Create (
		lpServiceName,
		lpDisplayName,
		dwDesiredAccess,
		dwServiceType,
		dwStartType,
		dwErrorControl,
		lpBinaryPathName,
		lpLoadOrderGroup,
		lpdwTagId,
		lpDependencies,
		lpServiceStartName,
		lpPassword
	);
}

/*=============================================================================
 * SERVICE CLASS IMPLEMENTATION
 *============================================================================*/
YLB_INLINE YService::YService (SC_HANDLE hSCM, SC_HANDLE hService)
{
	m_hSCM		= hSCM;
	m_hService	= hService;
}

YLB_INLINE YService::~YService ()
{
	Close ();
}

YLB_INLINE void YService::Close ()
{
	if ( m_hService ) {
		::CloseServiceHandle (m_hService);
		m_hService = NULL;
	}
}

YLB_INLINE BOOL YService::IsOpen () const
{
	return m_hService != NULL;
}

YLB_INLINE BOOL YService::QueryStatus (LPSERVICE_STATUS lpServiceStatus)
{
	return ::QueryServiceStatus (m_hService, lpServiceStatus);
}

YLB_INLINE DWORD YService::QueryStatus ()
{
	SERVICE_STATUS	ssStatus;
	return (QueryStatus (&ssStatus)) ? (ssStatus.dwCurrentState) : (SERVICE_UNKNOWN);
}

YLB_INLINE BOOL YService::Start (DWORD dwNumServiceArgs, LPCTSTR *lpServiceArgVectors) const
{
	return ::StartService (m_hService, dwNumServiceArgs, lpServiceArgVectors);
}

YLB_INLINE BOOL YService::Stop (LPSERVICE_STATUS lpServiceStatus) const
{
	return Control (SERVICE_CONTROL_STOP, lpServiceStatus);
}

YLB_INLINE BOOL YService::Pause (LPSERVICE_STATUS lpServiceStatus) const
{
	return Control (SERVICE_CONTROL_PAUSE, lpServiceStatus);
}

YLB_INLINE BOOL YService::Continue (LPSERVICE_STATUS lpServiceStatus) const
{
	return Control (SERVICE_CONTROL_CONTINUE, lpServiceStatus);
}

