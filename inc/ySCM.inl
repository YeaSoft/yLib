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
 * FILENAME		:	ySCM.inl
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
 * Revision 1.1  2000/05/26 14:03:28  leo
 * Initial revision
 *
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

YLB_INLINE DWORD YServiceControlManager::StatusGet (LPCTSTR pszServiceName) const
{
	SERVICE_STATUS	srvStatus;
	StatusGet (pszServiceName, &srvStatus);
	return srvStatus.dwCurrentState;
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

YLB_INLINE void YService::FreeQueryConfig (LPQUERY_SERVICE_CONFIG &lpSc) const
{
	if ( lpSc ) {
		free (lpSc);
		lpSc = NULL;
	}
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

