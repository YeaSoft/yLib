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
 * Revision 1.6  2002/08/20 18:51:47  leopoldo
 * Moved pseudofunctions support from yLibBase.h
 *
 * Revision 1.5  2001/05/25 16:31:53  leopoldo
 * Added configuration management methods
 *
 * Revision 1.4  2001/05/25 14:50:07  leopoldo
 * Changed access mode to YService::Open
 *
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
 * NT API PSEUDOFUNCTIONS REMAPPER
 *============================================================================*/
#ifndef YLB_NATIVE_NT_LINKING

#define ChangeServiceConfigA			YlbChangeServiceConfigA
#define ChangeServiceConfigW			YlbChangeServiceConfigW
#define ChangeServiceConfig2A			YlbChangeServiceConfig2A
#define ChangeServiceConfig2W			YlbChangeServiceConfig2W
#define CloseServiceHandle				YlbCloseServiceHandle
#define ControlService					YlbControlService
#define CreateServiceA					YlbCreateServiceA
#define CreateServiceW					YlbCreateServiceW
#define DeleteService					YlbDeleteService
#define EnumDependentServicesA			YlbEnumDependentServicesA
#define EnumDependentServicesW			YlbEnumDependentServicesW
#define EnumServicesStatusA				YlbEnumServicesStatusA
#define EnumServicesStatusW				YlbEnumServicesStatusW
#define GetServiceKeyNameA				YlbGetServiceKeyNameA
#define GetServiceKeyNameW				YlbGetServiceKeyNameW
#define GetServiceDisplayNameA			YlbGetServiceDisplayNameA
#define GetServiceDisplayNameW			YlbGetServiceDisplayNameW
#define LockServiceDatabase				YlbLockServiceDatabase
#define NotifyBootConfigStatus			YlbNotifyBootConfigStatus
#define OpenSCManagerA					YlbOpenSCManagerA
#define OpenSCManagerW					YlbOpenSCManagerW
#define OpenServiceA					YlbOpenServiceA
#define OpenServiceW					YlbOpenServiceW
#define QueryServiceConfigA				YlbQueryServiceConfigA
#define QueryServiceConfigW				YlbQueryServiceConfigW
#define QueryServiceConfig2A			YlbQueryServiceConfig2A
#define QueryServiceConfig2W			YlbQueryServiceConfig2W
#define QueryServiceLockStatusA			YlbQueryServiceLockStatusA
#define QueryServiceLockStatusW			YlbQueryServiceLockStatusW
#define QueryServiceObjectSecurity		YlbQueryServiceObjectSecurity
#define QueryServiceStatus				YlbQueryServiceStatus
#define RegisterServiceCtrlHandlerA		YlbRegisterServiceCtrlHandlerA
#define RegisterServiceCtrlHandlerW		YlbRegisterServiceCtrlHandlerW
#define SetServiceObjectSecurity		YlbSetServiceObjectSecurity
#define SetServiceStatus				YlbSetServiceStatus
#define StartServiceCtrlDispatcherA		YlbStartServiceCtrlDispatcherA
#define StartServiceCtrlDispatcherW		YlbStartServiceCtrlDispatcherW
#define StartServiceA					YlbStartServiceA
#define StartServiceW					YlbStartServiceW
#define UnlockServiceDatabase			YlbUnlockServiceDatabase

#endif //YLB_NATIVE_NT_LINKING

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
	LPQUERY_SERVICE_CONFIG		AllocQueryConfig		() const;
	void						FreeQueryConfig			(LPQUERY_SERVICE_CONFIG &lpSc) const;

	BOOL						SetInteractive			(BOOL bInteractive) const;
	BOOL						SetStartMode			(DWORD dwStartType) const;
	BOOL						SetErrorControl			(DWORD dwErrorControl) const;
	BOOL						SetLoadOrderGroup		(LPCTSTR lpGroup = NULL, LPDWORD lpdwTagId = NULL) const;
	BOOL						SetDependencies			(LPCTSTR lpDependencies = _T("\0")) const;
	BOOL						SetStartUser			(LPCTSTR lpUserName = _T("\0"), LPCTSTR lpPassword = NULL) const;
	BOOL						SetDisplayName			(LPCTSTR lpDisplayName) const;


private:
	SC_HANDLE					m_hSCM;
	SC_HANDLE					m_hService;
};

/*=============================================================================
 * NT API PSEUDOFUNCTIONS
 *============================================================================*/
#ifndef YLB_NATIVE_NT_LINKING

extern "C" {


BOOL YLBAPI YlbChangeServiceConfigA (
	SC_HANDLE	hService,
	DWORD		dwServiceType,
	DWORD		dwStartType,
	DWORD		dwErrorControl,
	LPCSTR		lpBinaryPathName,
	LPCSTR		lpLoadOrderGroup,
	LPDWORD		lpdwTagId,
	LPCSTR		lpDependencies,
	LPCSTR		lpServiceStartName,
	LPCSTR		lpPassword,
	LPCSTR		lpDisplayName
);

BOOL YLBAPI YlbChangeServiceConfigW (
	SC_HANDLE	hService,
	DWORD		dwServiceType,
	DWORD		dwStartType,
	DWORD		dwErrorControl,
	LPCWSTR		lpBinaryPathName,
	LPCWSTR		lpLoadOrderGroup,
	LPDWORD		lpdwTagId,
	LPCWSTR		lpDependencies,
	LPCWSTR		lpServiceStartName,
	LPCWSTR		lpPassword,
	LPCWSTR		lpDisplayName
);

BOOL YLBAPI YlbChangeServiceConfig2A (
	SC_HANDLE	hService,
	DWORD		dwInfoLevel,
	LPVOID		lpInfo
);

BOOL YLBAPI YlbChangeServiceConfig2W (
	SC_HANDLE	hService,
	DWORD		dwInfoLevel,
	LPVOID		lpInfo
);

BOOL YLBAPI YlbCloseServiceHandle (
	SC_HANDLE	hSCObject
);

BOOL YLBAPI YlbControlService (
	SC_HANDLE			hService,
	DWORD				dwControl,
	LPSERVICE_STATUS	lpServiceStatus
);

SC_HANDLE YLBAPI YlbCreateServiceA (
	SC_HANDLE	hSCManager,
	LPCSTR		lpServiceName,
	LPCSTR		lpDisplayName,
	DWORD		dwDesiredAccess,
	DWORD		dwServiceType,
	DWORD		dwStartType,
	DWORD		dwErrorControl,
	LPCSTR		lpBinaryPathName,
	LPCSTR		lpLoadOrderGroup,
	LPDWORD		lpdwTagId,
	LPCSTR		lpDependencies,
	LPCSTR		lpServiceStartName,
	LPCSTR		lpPassword
);

SC_HANDLE YLBAPI YlbCreateServiceW (
	SC_HANDLE	hSCManager,
	LPCWSTR		lpServiceName,
	LPCWSTR		lpDisplayName,
	DWORD		dwDesiredAccess,
	DWORD		dwServiceType,
	DWORD		dwStartType,
	DWORD		dwErrorControl,
	LPCWSTR		lpBinaryPathName,
	LPCWSTR		lpLoadOrderGroup,
	LPDWORD		lpdwTagId,
	LPCWSTR		lpDependencies,
	LPCWSTR		lpServiceStartName,
	LPCWSTR		lpPassword
);

BOOL YLBAPI YlbDeleteService (
	SC_HANDLE	hService
);

BOOL YLBAPI YlbEnumDependentServicesA (
	SC_HANDLE				hService,
	DWORD					dwServiceState,
	LPENUM_SERVICE_STATUSA	lpServices,
	DWORD					cbBufSize,
	LPDWORD					pcbBytesNeeded,
	LPDWORD					lpServicesReturned
);

BOOL YLBAPI YlbEnumDependentServicesW (
	SC_HANDLE				hService,
	DWORD					dwServiceState,
	LPENUM_SERVICE_STATUSW	lpServices,
	DWORD					cbBufSize,
	LPDWORD					pcbBytesNeeded,
	LPDWORD					lpServicesReturned
);

BOOL YLBAPI YlbEnumServicesStatusA (
	SC_HANDLE				hSCManager,
	DWORD					dwServiceType,
	DWORD					dwServiceState,
	LPENUM_SERVICE_STATUSA	lpServices,
	DWORD					cbBufSize,
	LPDWORD					pcbBytesNeeded,
	LPDWORD					lpServicesReturned,
	LPDWORD					lpResumeHandle
);

BOOL YLBAPI YlbEnumServicesStatusW (
	SC_HANDLE				hSCManager,
	DWORD					dwServiceType,
	DWORD					dwServiceState,
	LPENUM_SERVICE_STATUSW	lpServices,
	DWORD					cbBufSize,
	LPDWORD					pcbBytesNeeded,
	LPDWORD					lpServicesReturned,
	LPDWORD					lpResumeHandle
);

BOOL YLBAPI YlbGetServiceKeyNameA (
	SC_HANDLE	hSCManager,
	LPCSTR		lpDisplayName,
	LPSTR		lpServiceName,
	LPDWORD		lpcchBuffer
);

BOOL YLBAPI YlbGetServiceKeyNameW (
	SC_HANDLE	hSCManager,
	LPCWSTR		lpDisplayName,
	LPWSTR		lpServiceName,
	LPDWORD		lpcchBuffer
);

BOOL YLBAPI YlbGetServiceDisplayNameA (
	SC_HANDLE	hSCManager,
	LPCSTR		lpServiceName,
	LPSTR		lpDisplayName,
	LPDWORD		lpcchBuffer
);

BOOL YLBAPI YlbGetServiceDisplayNameW (
	SC_HANDLE	hSCManager,
	LPCWSTR		lpServiceName,
	LPWSTR		lpDisplayName,
	LPDWORD		lpcchBuffer
);

SC_LOCK YLBAPI YlbLockServiceDatabase (
	SC_HANDLE	hSCManager
);

BOOL YLBAPI YlbNotifyBootConfigStatus (
	BOOL	BootAcceptable
);

SC_HANDLE YLBAPI YlbOpenSCManagerA (
	LPCSTR	lpMachineName,
	LPCSTR	lpDatabaseName,
	DWORD	dwDesiredAccess
);

SC_HANDLE YLBAPI YlbOpenSCManagerW (
	LPCWSTR	lpMachineName,
	LPCWSTR	lpDatabaseName,
	DWORD	dwDesiredAccess
);

SC_HANDLE YLBAPI YlbOpenServiceA (
	SC_HANDLE	hSCManager,
	LPCSTR		lpServiceName,
	DWORD		dwDesiredAccess
);

SC_HANDLE YLBAPI YlbOpenServiceW (
	SC_HANDLE	hSCManager,
	LPCWSTR		lpServiceName,
	DWORD		dwDesiredAccess
);

BOOL YLBAPI YlbQueryServiceConfigA (
	SC_HANDLE				hService,
	LPQUERY_SERVICE_CONFIGA	lpServiceConfig,
	DWORD					cbBufSize,
	LPDWORD					pcbBytesNeeded
);

BOOL YLBAPI YlbQueryServiceConfigW (
	SC_HANDLE				hService,
	LPQUERY_SERVICE_CONFIGW	lpServiceConfig,
	DWORD					cbBufSize,
	LPDWORD					pcbBytesNeeded
);

BOOL YLBAPI YlbQueryServiceConfig2A (
	SC_HANDLE	hService,
	DWORD		dwInfoLevel,
	LPBYTE		lpBuffer,
	DWORD		cbBufSize,
	LPDWORD		pcbBytesNeeded
);

BOOL YLBAPI YlbQueryServiceConfig2W (
	SC_HANDLE	hService,
	DWORD		dwInfoLevel,
	LPBYTE		lpBuffer,
	DWORD		cbBufSize,
	LPDWORD		pcbBytesNeeded
);

BOOL YLBAPI YlbQueryServiceLockStatusA (
	SC_HANDLE						hSCManager,
	LPQUERY_SERVICE_LOCK_STATUSA	lpLockStatus,
	DWORD							cbBufSize,
	LPDWORD							pcbBytesNeeded
);

BOOL YLBAPI YlbQueryServiceLockStatusW (
	SC_HANDLE						hSCManager,
	LPQUERY_SERVICE_LOCK_STATUSW	lpLockStatus,
	DWORD							cbBufSize,
	LPDWORD							pcbBytesNeeded
);

BOOL YLBAPI YlbQueryServiceObjectSecurity (
	SC_HANDLE				hService,
	SECURITY_INFORMATION	dwSecurityInformation,
	PSECURITY_DESCRIPTOR	lpSecurityDescriptor,
	DWORD					cbBufSize,
	LPDWORD					pcbBytesNeeded
);

BOOL YLBAPI YlbQueryServiceStatus (
	SC_HANDLE			hService,
	LPSERVICE_STATUS	lpServiceStatus
);

SERVICE_STATUS_HANDLE YLBAPI YlbRegisterServiceCtrlHandlerA (
	LPCSTR				lpServiceName,
	LPHANDLER_FUNCTION	lpHandlerProc
);

SERVICE_STATUS_HANDLE YLBAPI YlbRegisterServiceCtrlHandlerW (
	LPCWSTR				lpServiceName,
	LPHANDLER_FUNCTION	lpHandlerProc
);

BOOL YLBAPI YlbSetServiceObjectSecurity (
	SC_HANDLE				hService,
	SECURITY_INFORMATION	dwSecurityInformation,
	PSECURITY_DESCRIPTOR	lpSecurityDescriptor
);

BOOL YLBAPI YlbSetServiceStatus (
	SERVICE_STATUS_HANDLE	hServiceStatus,
	LPSERVICE_STATUS		lpServiceStatus
);

BOOL YLBAPI YlbStartServiceCtrlDispatcherA (
	CONST SERVICE_TABLE_ENTRYA *	lpServiceStartTable
);

BOOL YLBAPI YlbStartServiceCtrlDispatcherW (
	CONST SERVICE_TABLE_ENTRYW *	lpServiceStartTable
);

BOOL YLBAPI YlbStartServiceA (
	SC_HANDLE	hService,
	DWORD		dwNumServiceArgs,
	LPCSTR *	lpServiceArgVectors
);

BOOL YLBAPI YlbStartServiceW (
	SC_HANDLE	hService,
	DWORD		dwNumServiceArgs,
	LPCWSTR *	lpServiceArgVectors
);

BOOL YLBAPI YlbUnlockServiceDatabase (
	SC_LOCK	ScLock
);

} //extern "C"

#endif //YLB_NATIVE_NT_LINKING

#ifdef YLB_ENABLE_INLINE
#include <ySCM.inl>
#endif

#endif //__ySCM_h__

//
// EoF
////////
