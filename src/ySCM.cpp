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
 * FILENAME		:	ySCM.cpp
 * PURPOSE		:	The service control manager class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.5  2001/05/25 15:13:35  leopoldo
 * Fixed access rights
 *
 * Revision 1.4  2001/05/25 14:28:32  leopoldo
 * Improved YServiceControlManager::StatusGet
 *
 * Revision 1.3  2001/05/25 12:04:15  leopoldo
 * Fixed a pointer error in YServiceControlManager::EnumServices
 *
 * Revision 1.2  2000/09/04 12:07:43  leopoldo
 * Updated license to zlib/libpng
 *
 * Revision 1.1  2000/05/26 14:05:08  leo
 * Initial revision
 *
 *============================================================================*/

#include "StdInc.hpp"

/*=============================================================================
 * @doc YLIB | ySCM.h
 *============================================================================*/
BOOL YServiceControlManager::Open (DWORD dwDesiredAccess /* = GENERIC_READ | GENERIC_EXECUTE */, LPCTSTR lpMachineName /* = NULL */, LPCTSTR lpDatabaseName /* = SERVICES_ACTIVE_DATABASE */)
{
	if ( m_hSCM ) {
		return TRUE;
	}
	m_hSCM = OpenSCManager (lpMachineName, lpDatabaseName, dwDesiredAccess);
	return m_hSCM != NULL;
}

void YServiceControlManager::Close ()
{
	if ( m_hSCM ) {
		Unlock ();
		CloseServiceHandle (m_hSCM);
		m_hSCM = NULL;
	}
}

BOOL YServiceControlManager::Lock ()
{
	if ( !m_hSCM ) {
		// not inited
		::SetLastError (ERROR_INVALID_HANDLE);
		return NULL;
	}
	if ( m_hLock ) {
		// already locked
		return TRUE;
	}
	return (m_hLock = ::LockServiceDatabase (m_hSCM)) != NULL;
}

BOOL YServiceControlManager::Unlock ()
{
	if ( !m_hSCM ) {
		// not inited
		::SetLastError (ERROR_INVALID_HANDLE);
		return NULL;
	}
	if ( !m_hLock ) {
		// not locked
		return TRUE;
	}
	if ( ::UnlockServiceDatabase (m_hLock) ) {
		m_hLock = NULL;
		return TRUE;
	}
	return FALSE;
}

BOOL YServiceControlManager::Attach (SC_HANDLE hSCM)
{
	if ( m_hSCM != hSCM ) {
		Unlock ();
		Close ();
	}

	m_hSCM = hSCM;
	return TRUE;
}

SC_HANDLE YServiceControlManager::Detach ()
{
	SC_HANDLE hReturn = m_hSCM;
	Unlock ();
	m_hSCM = NULL;
	return hReturn;
}


LPQUERY_SERVICE_LOCK_STATUS	YServiceControlManager::AllocQueryLockStatus () const
{
	if ( !m_hSCM ) {
		// not inited
		::SetLastError (ERROR_INVALID_HANDLE);
		return NULL;
	}

	DWORD						dwBytesNeeded, dwSize;
	LPQUERY_SERVICE_LOCK_STATUS	lpLockStatus;

	if ( ::QueryServiceLockStatus (m_hSCM, NULL, 0, &dwBytesNeeded) ) {
		// SNH:
		return NULL;
	}
	if ( ::GetLastError() != ERROR_INSUFFICIENT_BUFFER ) {
		// SNH: Mistus!
		return NULL;
	}
	if ( !(lpLockStatus = (LPQUERY_SERVICE_LOCK_STATUS) malloc (dwBytesNeeded)) ) {
		// No mem or corrupted heap
		return NULL;
	}

	if ( !::QueryServiceLockStatus(m_hSCM, lpLockStatus, dwBytesNeeded, &dwSize) ) {
		// strange strange
		free (lpLockStatus);
		return NULL;
	}

	return lpLockStatus;
}

BOOL YServiceControlManager::IsService (LPCTSTR pszServiceName) const
{
	if ( !m_hSCM ) {
		::SetLastError (ERROR_INVALID_HANDLE);
		return FALSE;
	}
	SC_HANDLE schService = ::OpenService (
		m_hSCM,
		pszServiceName,
		GENERIC_READ
	);
	if ( !schService ) {
		return FALSE;
	}
	CloseServiceHandle (schService);
	return TRUE;
}

BOOL YServiceControlManager::StatusGet (LPCTSTR pszServiceName, LPSERVICE_STATUS lpServiceStatus) const
{
	lpServiceStatus->dwCurrentState = SERVICE_STOPPED;

	if ( !m_hSCM ) {
		::SetLastError (ERROR_INVALID_HANDLE);
		return FALSE;
	}
	SC_HANDLE schService = ::OpenService (
		m_hSCM,
		pszServiceName,
		GENERIC_READ
	);
	if ( !schService ) {
		return FALSE;
	}

	BOOL bRet;

	if ( !(bRet = QueryServiceStatus (schService, lpServiceStatus)) ) {
		lpServiceStatus->dwCurrentState = SERVICE_STOPPED;
	}
	CloseServiceHandle (schService);
	return bRet;
}

BOOL  YServiceControlManager::Start (LPCTSTR pszServiceName) const
{
	if ( !m_hSCM ) {
		::SetLastError (ERROR_INVALID_HANDLE);
		return FALSE;
	}
	SC_HANDLE schService = ::OpenService (
		m_hSCM,
		pszServiceName,
		GENERIC_READ|GENERIC_EXECUTE
	);
	if ( !schService ) {
		return FALSE;
	}
	SERVICE_STATUS	srvStatus;
	if ( !QueryServiceStatus (schService, &srvStatus) ) {
		CloseServiceHandle (schService);
		return FALSE;
	}
	if ( srvStatus.dwCurrentState != SERVICE_STOPPED ) {
		CloseServiceHandle (schService);
		return FALSE;
	}
	BOOL bRet = StartService (schService, 0, NULL);
	CloseServiceHandle (schService);
	return bRet;
}

BOOL  YServiceControlManager::Stop (LPCTSTR pszServiceName) const
{
	if ( !m_hSCM ) {
		::SetLastError (ERROR_INVALID_HANDLE);
		return FALSE;
	}
	SC_HANDLE schService = ::OpenService (
		m_hSCM,
		pszServiceName,
		GENERIC_READ|GENERIC_EXECUTE
	);
	if ( !schService ) {
		return FALSE;
	}
	SERVICE_STATUS	srvStatus;
	if ( !QueryServiceStatus (schService, &srvStatus) ) {
		CloseServiceHandle (schService);
		return FALSE;
	}
	if ( !(srvStatus.dwControlsAccepted & SERVICE_ACCEPT_STOP) ) {
		CloseServiceHandle (schService);
		return FALSE;
	}
	BOOL bRet = ControlService (schService, SERVICE_CONTROL_STOP, &srvStatus);
	CloseServiceHandle (schService);
	return bRet;
}

BOOL  YServiceControlManager::Pause (LPCTSTR pszServiceName) const
{
	if ( !m_hSCM ) {
		::SetLastError (ERROR_INVALID_HANDLE);
		return FALSE;
	}
	SC_HANDLE schService = ::OpenService (
		m_hSCM,
		pszServiceName,
		GENERIC_READ|GENERIC_EXECUTE
	);
	if ( !schService ) {
		return FALSE;
	}
	SERVICE_STATUS	srvStatus;
	if ( !QueryServiceStatus (schService, &srvStatus) ) {
		CloseServiceHandle (schService);
		return FALSE;
	}
	if ( !(srvStatus.dwControlsAccepted & SERVICE_ACCEPT_PAUSE_CONTINUE) ) {
		CloseServiceHandle (schService);
		return FALSE;
	}
	BOOL bRet = ControlService (schService, SERVICE_CONTROL_PAUSE, &srvStatus);
	CloseServiceHandle (schService);
	return bRet;
}

BOOL  YServiceControlManager::Resume (LPCTSTR pszServiceName) const
{
	if ( !m_hSCM ) {
		::SetLastError (ERROR_INVALID_HANDLE);
		return FALSE;
	}
	SC_HANDLE schService = ::OpenService (
		m_hSCM,
		pszServiceName,
		GENERIC_READ|GENERIC_EXECUTE
	);
	if ( !schService ) {
		return FALSE;
	}
	SERVICE_STATUS	srvStatus;
	if ( !QueryServiceStatus (schService, &srvStatus) ) {
		CloseServiceHandle (schService);
		return FALSE;
	}
	if ( !(srvStatus.dwControlsAccepted & SERVICE_ACCEPT_PAUSE_CONTINUE) ) {
		CloseServiceHandle (schService);
		return FALSE;
	}
	BOOL bRet = ControlService (schService, SERVICE_CONTROL_CONTINUE, &srvStatus);
	CloseServiceHandle (schService);
	return bRet;
}

LPQUERY_SERVICE_CONFIG YServiceControlManager::AllocQueryConfig (LPCTSTR pszServiceName) const
{
	if ( !m_hSCM ) {
		// not inited
		::SetLastError (ERROR_INVALID_HANDLE);
		return NULL;
	}

	YService srv (m_hSCM);

	if ( !srv.Open (pszServiceName, SERVICE_QUERY_CONFIG) ) {
		return NULL;
	}
	return srv.AllocQueryConfig ();
}

BOOL YServiceControlManager::EnumServices (ENUM_SERVICES_PROC lpEnumServicesFunc, DWORD dwUserData /* = 0 */, DWORD dwServiceType /* = SERVICE_WIN32 */, DWORD dwServiceState /* = SERVICE_STATE_ALL */) const
{
	if ( !m_hSCM ) {
		// not inited
		::SetLastError (ERROR_INVALID_HANDLE);
		return NULL;
	}

	DWORD					dwBytesNeeded, dwServices, dwSize, dwResumeHandle = 0;
	LPENUM_SERVICE_STATUS	lpESS;

	BOOL bSuccess = ::EnumServicesStatus (m_hSCM, dwServiceType, dwServiceState, NULL, 0, &dwBytesNeeded, &dwServices, &dwResumeHandle);
	if ( !bSuccess && (::GetLastError() == ERROR_MORE_DATA) ) {
		if ( !(lpESS = (LPENUM_SERVICE_STATUS) malloc (dwBytesNeeded)) ) {
			// no mem or heap corrupted
			return FALSE;
		}
		bSuccess = ::EnumServicesStatus (
			m_hSCM,
			dwServiceType,
			dwServiceState,
			lpESS,
			dwBytesNeeded,
			&dwSize,
			&dwServices,
			&dwResumeHandle
		);
		if ( bSuccess ) {
			BOOL bContinue = TRUE;
			for ( DWORD dw = 0; (dw < dwServices) && bContinue; dw++ ) {
				bContinue = lpEnumServicesFunc (dwUserData, lpESS[dw]);
			}
		}
		free (lpESS);
	}

	return bSuccess;
}


/*=============================================================================
 * SERVICE CLASS IMPLEMENTATION
 *============================================================================*/
BOOL YService::Attach (SC_HANDLE hService)
{
	if ( !m_hSCM ) {
		return FALSE;
	}
	if ( m_hService != hService ) {
		Close ();
	}
	m_hService = hService;
	return TRUE;
}

BOOL YService::Attach (SC_HANDLE hSCM, SC_HANDLE hService)
{
	if ( !hSCM ) {
		return FALSE;
	}
	m_hSCM = hSCM;
	return Attach (hService);
}

SC_HANDLE YService::Detach (SC_HANDLE *phSCM)
{
	SC_HANDLE hReturn = m_hService;
	if ( phSCM ) {
		*phSCM = m_hSCM;
	}
	m_hService = NULL;
	return hReturn;
}

BOOL YService::Create (
	LPCTSTR	lpServiceName,
	LPCTSTR	lpDisplayName,
	DWORD	dwDesiredAccess,
	DWORD	dwServiceType,
	DWORD	dwStartType,
	DWORD	dwErrorControl,
	LPCTSTR	lpBinaryPathName,
	LPCTSTR	lpLoadOrderGroup,
	LPDWORD	lpdwTagId,
	LPCTSTR	lpDependencies,
	LPCTSTR	lpServiceStartName,
	LPCTSTR	lpPassword
)
{
	if ( !m_hSCM ) {
		::SetLastError (ERROR_INVALID_HANDLE);
		return FALSE;
	}
	SC_HANDLE hService = ::CreateService (
		m_hSCM,
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
	if ( hService ) {
		Close ();
		m_hService = hService;
		return TRUE;
	}
	return FALSE;
}

BOOL YService::Open (LPCTSTR pszServiceName, DWORD dwDesiredAccess)
{
	if ( !m_hSCM ) {
		::SetLastError (ERROR_INVALID_HANDLE);
		return FALSE;
	}
	SC_HANDLE hService = ::OpenService (
		m_hSCM,
		pszServiceName,
		dwDesiredAccess
	);
	if ( hService ) {
		Close ();
		m_hService = hService;
		return TRUE;
	}
	::SetLastError (ERROR_INVALID_HANDLE);
	return FALSE;
}

BOOL YService::Delete (BOOL bAutoClose)
{
	if ( m_hService ) {
		if ( ::DeleteService (m_hService) ) {
			if ( bAutoClose ) {
				Close ();
			}
			return TRUE;
		}
	}
	::SetLastError (ERROR_INVALID_HANDLE);
	return FALSE;
}


BOOL YService::Control (DWORD dwControl, LPSERVICE_STATUS lpServiceStatus) const
{
	SERVICE_STATUS	ssStatus;
	if ( !lpServiceStatus ) {
		lpServiceStatus = &ssStatus;
	}
	return ::ControlService (m_hService, dwControl, lpServiceStatus);
}

LPQUERY_SERVICE_CONFIG YService::AllocQueryConfig () const
{
	if ( !m_hService ) {
		// not inited
		::SetLastError (ERROR_INVALID_HANDLE);
		return NULL;
	}

	DWORD					dwBytesNeeded, dwSize;
	LPQUERY_SERVICE_CONFIG	lpSc;

	if ( ::QueryServiceConfig (m_hService, NULL, 0, &dwBytesNeeded) ) {
		// SNH:
		return NULL;
	}
	if ( ::GetLastError() != ERROR_INSUFFICIENT_BUFFER ) {
		// SNH: Mistus!
		return NULL;
	}
	if ( !(lpSc = (LPQUERY_SERVICE_CONFIG) malloc (dwBytesNeeded)) ) {
		// No mem or corrupted heap
		return NULL;
	}

	if ( !::QueryServiceConfig (m_hService, lpSc, dwBytesNeeded, &dwSize) ) {
		// strange strange
		free (lpSc);
		return NULL;
	}

	return lpSc;
}

BOOL YService::SetInteractive (BOOL bInteractive) const
{
	LPQUERY_SERVICE_CONFIG pConfig = AllocQueryConfig ();
	if ( !pConfig ) {
		return FALSE;
	}

	YFlags dw(pConfig->dwServiceType);
	dw.ChangeFlags (SERVICE_INTERACTIVE_PROCESS, bInteractive);
	if ( dw == pConfig->dwServiceType ) {
		// no change
		return TRUE;
	}
	pConfig->dwServiceType = dw;

	BOOL bRet = ChangeServiceConfig (
		m_hService,
		pConfig->dwServiceType,
		SERVICE_NO_CHANGE,
		SERVICE_NO_CHANGE,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		pConfig->lpDisplayName
	);
	FreeQueryConfig (pConfig);
	return bRet;
}

BOOL YService::SetStartMode (DWORD dwStartType) const
{
	LPQUERY_SERVICE_CONFIG pConfig = AllocQueryConfig ();
	if ( !pConfig ) {
		return FALSE;
	}
	
	switch ( dwStartType ) {
	case SERVICE_AUTO_START:
	case SERVICE_BOOT_START:
	case SERVICE_DEMAND_START:
	case SERVICE_DISABLED:
	case SERVICE_SYSTEM_START:
		break;
	default:
		::SetLastError (ERROR_INVALID_PARAMETER);
		return FALSE;
	}

	BOOL bRet = ChangeServiceConfig (
		m_hService,
		SERVICE_NO_CHANGE,
		dwStartType,
		SERVICE_NO_CHANGE,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		pConfig->lpDisplayName
	);
	FreeQueryConfig (pConfig);
	return bRet;
}

BOOL YService::SetErrorControl (DWORD dwErrorControl) const
{
	LPQUERY_SERVICE_CONFIG pConfig = AllocQueryConfig ();
	if ( !pConfig ) {
		return FALSE;
	}
	
	switch ( dwErrorControl ) {
	case SERVICE_ERROR_IGNORE:
	case SERVICE_ERROR_NORMAL:
	case SERVICE_ERROR_SEVERE:
	case SERVICE_ERROR_CRITICAL:
		break;
	default:
		::SetLastError (ERROR_INVALID_PARAMETER);
		return FALSE;
	}

	BOOL bRet = ChangeServiceConfig (
		m_hService,
		SERVICE_NO_CHANGE,
		SERVICE_NO_CHANGE,
		dwErrorControl,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		pConfig->lpDisplayName
	);
	FreeQueryConfig (pConfig);
	return bRet;
}

BOOL YService::SetLoadOrderGroup (LPCTSTR lpGroup /* = NULL */, LPDWORD lpdwTagId /* = NULL */) const
{
	LPQUERY_SERVICE_CONFIG pConfig = AllocQueryConfig ();
	if ( !pConfig ) {
		return FALSE;
	}
	
	BOOL bRet = ChangeServiceConfig (
		m_hService,
		SERVICE_NO_CHANGE,
		SERVICE_NO_CHANGE,
		SERVICE_NO_CHANGE,
		NULL,
		lpGroup,
		lpdwTagId,
		NULL,
		NULL,
		NULL,
		pConfig->lpDisplayName
	);
	FreeQueryConfig (pConfig);
	return bRet;
}

BOOL YService::SetDependencies (LPCTSTR lpDependencies /* = _T("\0") */) const
{
	LPQUERY_SERVICE_CONFIG pConfig = AllocQueryConfig ();
	if ( !pConfig ) {
		return FALSE;
	}
	
	BOOL bRet = ChangeServiceConfig (
		m_hService,
		SERVICE_NO_CHANGE,
		SERVICE_NO_CHANGE,
		SERVICE_NO_CHANGE,
		NULL,
		NULL,
		NULL,
		lpDependencies,
		NULL,
		NULL,
		pConfig->lpDisplayName
	);
	FreeQueryConfig (pConfig);
	return bRet;
}

BOOL YService::SetStartUser (LPCTSTR lpUserName /* = _T("\0") */, LPCTSTR lpPassword /* = NULL */) const
{
	LPQUERY_SERVICE_CONFIG pConfig = AllocQueryConfig ();
	if ( !pConfig ) {
		return FALSE;
	}
	
	BOOL bRet = ChangeServiceConfig (
		m_hService,
		SERVICE_NO_CHANGE,
		SERVICE_NO_CHANGE,
		SERVICE_NO_CHANGE,
		NULL,
		NULL,
		NULL,
		NULL,
		lpUserName,
		lpPassword,
		pConfig->lpDisplayName
	);
	FreeQueryConfig (pConfig);
	return bRet;
}

BOOL YService::SetDisplayName (LPCTSTR lpDisplayName) const
{
	LPQUERY_SERVICE_CONFIG pConfig = AllocQueryConfig ();
	if ( !pConfig ) {
		return FALSE;
	}
	
	BOOL bRet = ChangeServiceConfig (
		m_hService,
		SERVICE_NO_CHANGE,
		SERVICE_NO_CHANGE,
		SERVICE_NO_CHANGE,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		lpDisplayName
	);
	FreeQueryConfig (pConfig);
	return bRet;
}

#ifndef YLB_ENABLE_INLINE
#include <ySCM.inl>
#endif

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////