/*=============================================================================
 * This is a part of the yLib Software Development Kit.
 * Copyright (C) 1998-2002 YEAsoft Int'l.
 * All rights reserved.
 *=============================================================================
 * Copyright (c) 1998-2002 YEAsoft Int'l (Leo Moll, Andrea Pennelli).
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
 * FILENAME		:	_ntStubs.cpp
 * PURPOSE		:	Wrappers for native NT functions (Win9x support)
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.2  2002/06/03 15:20:30  leopoldo
 * Fixed UniCode Stuff
 *
 * Revision 1.1  2002/06/03 11:38:26  leopoldo
 * Initial revision
 *
 *============================================================================*/
#include "StdInc.hpp"

#ifdef _DEBUG
#undef HERE
static char HERE[] = __FILE__;
#endif //_DEBUG

/*=============================================================================
 * CONDITIONAL COMPILATION
 *============================================================================*/
#ifndef YLB_NATIVE_NT_LINKING

/*=============================================================================
 * CONFIGURATION
 *============================================================================*/
#pragma warning(disable:4074)
#pragma init_seg(compiler)

/*=============================================================================
 * THE STUB LOADER
 *============================================================================*/
class STUB_LOADER
{
public:
	STUB_LOADER					();
	~STUB_LOADER				();

private:
	void						CommonConstructor		();
	bool						LoadLibrary				();
	void						FreeLibrary				();

public:
	static HINSTANCE			m_hAdvAPI;
	static HINSTANCE			m_hKernel;

	static LPFN_ENCFILA			m_lpfnEncryptFileA;
	static LPFN_ENCFILW			m_lpfnEncryptFileW;
	static LPFN_DECFILA			m_lpfnDecryptFileA;
	static LPFN_DECFILW			m_lpfnDecryptFileW;

	static LPFN_CSCA			m_lpfnChangeServiceConfigA;
	static LPFN_CSCW			m_lpfnChangeServiceConfigW;
	static LPFN_CSC2A			m_lpfnChangeServiceConfig2A;
	static LPFN_CSC2W			m_lpfnChangeServiceConfig2W;
	static LPFN_CSH				m_lpfnCloseServiceHandle;
	static LPFN_CS				m_lpfnControlService;
	static LPFN_CSA				m_lpfnCreateServiceA;
	static LPFN_CSW				m_lpfnCreateServiceW;
	static LPFN_DS				m_lpfnDeleteService;
	static LPFN_EDSA			m_lpfnEnumDependentServicesA;
	static LPFN_EDSW			m_lpfnEnumDependentServicesW;
	static LPFN_ESSA			m_lpfnEnumServicesStatusA;
	static LPFN_ESSW			m_lpfnEnumServicesStatusW;
	static LPFN_GSKNA			m_lpfnGetServiceKeyNameA;
	static LPFN_GSKNW			m_lpfnGetServiceKeyNameW;
	static LPFN_GSDNA			m_lpfnGetServiceDisplayNameA;
	static LPFN_GSDNW			m_lpfnGetServiceDisplayNameW;
	static LPFN_LSD				m_lpfnLockServiceDatabase;
	static LPFN_NBCS			m_lpfnNotifyBootConfigStatus;
	static LPFN_OSCMA			m_lpfnOpenSCManagerA;
	static LPFN_OSCMW			m_lpfnOpenSCManagerW;
	static LPFN_OSA				m_lpfnOpenServiceA;
	static LPFN_OSW				m_lpfnOpenServiceW;
	static LPFN_QSCA			m_lpfnQueryServiceConfigA;
	static LPFN_QSCW			m_lpfnQueryServiceConfigW;
	static LPFN_QSC2A			m_lpfnQueryServiceConfig2A;
	static LPFN_QSC2W			m_lpfnQueryServiceConfig2W;
	static LPFN_QSLSA			m_lpfnQueryServiceLockStatusA;
	static LPFN_QSLSW			m_lpfnQueryServiceLockStatusW;
	static LPFN_QSOS			m_lpfnQueryServiceObjectSecurity;
	static LPFN_QSS				m_lpfnQueryServiceStatus;
	static LPFN_RSCHA			m_lpfnRegisterServiceCtrlHandlerA;
	static LPFN_RSCHW			m_lpfnRegisterServiceCtrlHandlerW;
	static LPFN_SSOS			m_lpfnSetServiceObjectSecurity;
	static LPFN_SSS				m_lpfnSetServiceStatus;
	static LPFN_SSCDA			m_lpfnStartServiceCtrlDispatcherA;
	static LPFN_SSCDW			m_lpfnStartServiceCtrlDispatcherW;
	static LPFN_SSA				m_lpfnStartServiceA;
	static LPFN_SSW				m_lpfnStartServiceW;
	static LPFN_USD				m_lpfnUnlockServiceDatabase;
};

/*=============================================================================
 * STUB INSTANTIATION
 *============================================================================*/
static STUB_LOADER				_stub;

HINSTANCE			STUB_LOADER::m_hAdvAPI;
HINSTANCE			STUB_LOADER::m_hKernel;

LPFN_ENCFILA		STUB_LOADER::m_lpfnEncryptFileA;
LPFN_ENCFILW		STUB_LOADER::m_lpfnEncryptFileW;
LPFN_DECFILA		STUB_LOADER::m_lpfnDecryptFileA;
LPFN_DECFILW		STUB_LOADER::m_lpfnDecryptFileW;

LPFN_CSCA			STUB_LOADER::m_lpfnChangeServiceConfigA;
LPFN_CSCW			STUB_LOADER::m_lpfnChangeServiceConfigW;
LPFN_CSC2A			STUB_LOADER::m_lpfnChangeServiceConfig2A;
LPFN_CSC2W			STUB_LOADER::m_lpfnChangeServiceConfig2W;
LPFN_CSH			STUB_LOADER::m_lpfnCloseServiceHandle;
LPFN_CS				STUB_LOADER::m_lpfnControlService;
LPFN_CSA			STUB_LOADER::m_lpfnCreateServiceA;
LPFN_CSW			STUB_LOADER::m_lpfnCreateServiceW;
LPFN_DS				STUB_LOADER::m_lpfnDeleteService;
LPFN_EDSA			STUB_LOADER::m_lpfnEnumDependentServicesA;
LPFN_EDSW			STUB_LOADER::m_lpfnEnumDependentServicesW;
LPFN_ESSA			STUB_LOADER::m_lpfnEnumServicesStatusA;
LPFN_ESSW			STUB_LOADER::m_lpfnEnumServicesStatusW;
LPFN_GSKNA			STUB_LOADER::m_lpfnGetServiceKeyNameA;
LPFN_GSKNW			STUB_LOADER::m_lpfnGetServiceKeyNameW;
LPFN_GSDNA			STUB_LOADER::m_lpfnGetServiceDisplayNameA;
LPFN_GSDNW			STUB_LOADER::m_lpfnGetServiceDisplayNameW;
LPFN_LSD			STUB_LOADER::m_lpfnLockServiceDatabase;
LPFN_NBCS			STUB_LOADER::m_lpfnNotifyBootConfigStatus;
LPFN_OSCMA			STUB_LOADER::m_lpfnOpenSCManagerA;
LPFN_OSCMW			STUB_LOADER::m_lpfnOpenSCManagerW;
LPFN_OSA			STUB_LOADER::m_lpfnOpenServiceA;
LPFN_OSW			STUB_LOADER::m_lpfnOpenServiceW;
LPFN_QSCA			STUB_LOADER::m_lpfnQueryServiceConfigA;
LPFN_QSCW			STUB_LOADER::m_lpfnQueryServiceConfigW;
LPFN_QSC2A			STUB_LOADER::m_lpfnQueryServiceConfig2A;
LPFN_QSC2W			STUB_LOADER::m_lpfnQueryServiceConfig2W;
LPFN_QSLSA			STUB_LOADER::m_lpfnQueryServiceLockStatusA;
LPFN_QSLSW			STUB_LOADER::m_lpfnQueryServiceLockStatusW;
LPFN_QSOS			STUB_LOADER::m_lpfnQueryServiceObjectSecurity;
LPFN_QSS			STUB_LOADER::m_lpfnQueryServiceStatus;
LPFN_RSCHA			STUB_LOADER::m_lpfnRegisterServiceCtrlHandlerA;
LPFN_RSCHW			STUB_LOADER::m_lpfnRegisterServiceCtrlHandlerW;
LPFN_SSOS			STUB_LOADER::m_lpfnSetServiceObjectSecurity;
LPFN_SSS			STUB_LOADER::m_lpfnSetServiceStatus;
LPFN_SSCDA			STUB_LOADER::m_lpfnStartServiceCtrlDispatcherA;
LPFN_SSCDW			STUB_LOADER::m_lpfnStartServiceCtrlDispatcherW;
LPFN_SSA			STUB_LOADER::m_lpfnStartServiceA;
LPFN_SSW			STUB_LOADER::m_lpfnStartServiceW;
LPFN_USD			STUB_LOADER::m_lpfnUnlockServiceDatabase;

/*=============================================================================
 * STUB IMPLEMENTATION
 *============================================================================*/
STUB_LOADER::STUB_LOADER ()
{
	CommonConstructor ();
	LoadLibrary ();
}

STUB_LOADER::~STUB_LOADER ()
{
	FreeLibrary ();
}

void STUB_LOADER::CommonConstructor ()
{
	m_hAdvAPI							= NULL;
	m_hKernel							= NULL;

	m_lpfnEncryptFileA					= NULL;
	m_lpfnEncryptFileW					= NULL;
	m_lpfnDecryptFileA					= NULL;
	m_lpfnDecryptFileW					= NULL;

	m_lpfnChangeServiceConfigA			= NULL;
	m_lpfnChangeServiceConfigW			= NULL;
	m_lpfnChangeServiceConfig2A			= NULL;
	m_lpfnChangeServiceConfig2W			= NULL;
	m_lpfnCloseServiceHandle			= NULL;
	m_lpfnControlService				= NULL;
	m_lpfnCreateServiceA				= NULL;	
	m_lpfnCreateServiceW				= NULL;
	m_lpfnDeleteService					= NULL;
	m_lpfnEnumDependentServicesA		= NULL;
	m_lpfnEnumDependentServicesW		= NULL;
	m_lpfnEnumServicesStatusA			= NULL;
	m_lpfnEnumServicesStatusW			= NULL;
	m_lpfnGetServiceKeyNameA			= NULL;
	m_lpfnGetServiceKeyNameW			= NULL;
	m_lpfnGetServiceDisplayNameA		= NULL;
	m_lpfnGetServiceDisplayNameW		= NULL;
	m_lpfnLockServiceDatabase			= NULL;
	m_lpfnNotifyBootConfigStatus		= NULL;
	m_lpfnOpenSCManagerA				= NULL;
	m_lpfnOpenSCManagerW				= NULL;
	m_lpfnOpenServiceA					= NULL;
	m_lpfnOpenServiceW					= NULL;
	m_lpfnQueryServiceConfigA			= NULL;
	m_lpfnQueryServiceConfigW			= NULL;
	m_lpfnQueryServiceConfig2A			= NULL;
	m_lpfnQueryServiceConfig2W			= NULL;
	m_lpfnQueryServiceLockStatusA		= NULL;
	m_lpfnQueryServiceLockStatusW		= NULL;
	m_lpfnQueryServiceObjectSecurity	= NULL;
	m_lpfnQueryServiceStatus			= NULL;
	m_lpfnRegisterServiceCtrlHandlerA	= NULL;
	m_lpfnRegisterServiceCtrlHandlerW	= NULL;
	m_lpfnSetServiceObjectSecurity		= NULL;
	m_lpfnSetServiceStatus				= NULL;
	m_lpfnStartServiceCtrlDispatcherA	= NULL;
	m_lpfnStartServiceCtrlDispatcherW	= NULL;
	m_lpfnStartServiceA					= NULL;
	m_lpfnStartServiceW					= NULL;
	m_lpfnUnlockServiceDatabase			= NULL;
}

bool STUB_LOADER::LoadLibrary ()
{
	if ( m_hAdvAPI && m_hKernel) {
		return true;
	}

	if ( !m_hKernel && (m_hKernel = ::LoadLibrary (_T("KERNEL32.DLL"))) != NULL ) {
		m_lpfnEncryptFileA					= (LPFN_ENCFILA) ::GetProcAddress (m_hKernel, "EncryptFileA");
		m_lpfnEncryptFileW					= (LPFN_ENCFILW) ::GetProcAddress (m_hKernel, "EncryptFileW");
		m_lpfnDecryptFileA					= (LPFN_DECFILA) ::GetProcAddress (m_hKernel, "DecryptFileA");
		m_lpfnDecryptFileW					= (LPFN_DECFILW) ::GetProcAddress (m_hKernel, "DecryptFileW");
	}

	if ( !m_hAdvAPI && (m_hAdvAPI = ::LoadLibrary (_T("ADVAPI32.DLL"))) != NULL ) {
		m_lpfnChangeServiceConfigA			= (LPFN_CSCA) ::GetProcAddress (m_hAdvAPI, "ChangeServiceConfigA");
		m_lpfnChangeServiceConfigW			= (LPFN_CSCW) ::GetProcAddress (m_hAdvAPI, "ChangeServiceConfigW");
		m_lpfnChangeServiceConfig2A			= (LPFN_CSC2A) ::GetProcAddress (m_hAdvAPI, "ChangeServiceConfig2A");
		m_lpfnChangeServiceConfig2W			= (LPFN_CSC2W) ::GetProcAddress (m_hAdvAPI, "ChangeServiceConfig2W");
		m_lpfnCloseServiceHandle			= (LPFN_CSH) ::GetProcAddress (m_hAdvAPI, "CloseServiceHandle");
		m_lpfnControlService				= (LPFN_CS) ::GetProcAddress (m_hAdvAPI, "ControlService");
		m_lpfnCreateServiceA				= (LPFN_CSA) ::GetProcAddress (m_hAdvAPI, "CreateServiceA");
		m_lpfnCreateServiceW				= (LPFN_CSW) ::GetProcAddress (m_hAdvAPI, "CreateServiceW");
		m_lpfnDeleteService					= (LPFN_DS) ::GetProcAddress (m_hAdvAPI, "DeleteService");
		m_lpfnEnumDependentServicesA		= (LPFN_EDSA) ::GetProcAddress (m_hAdvAPI, "EnumDependentServicesA");
		m_lpfnEnumDependentServicesW		= (LPFN_EDSW) ::GetProcAddress (m_hAdvAPI, "EnumDependentServicesW");
		m_lpfnEnumServicesStatusA			= (LPFN_ESSA) ::GetProcAddress (m_hAdvAPI, "EnumServicesStatusA");
		m_lpfnEnumServicesStatusW			= (LPFN_ESSW) ::GetProcAddress (m_hAdvAPI, "EnumServicesStatusW");
		m_lpfnGetServiceKeyNameA			= (LPFN_GSKNA) ::GetProcAddress (m_hAdvAPI, "GetServiceKeyNameA");
		m_lpfnGetServiceKeyNameW			= (LPFN_GSKNW) ::GetProcAddress (m_hAdvAPI, "GetServiceKeyNameW");
		m_lpfnGetServiceDisplayNameA		= (LPFN_GSDNA) ::GetProcAddress (m_hAdvAPI, "GetServiceDisplayNameA");
		m_lpfnGetServiceDisplayNameW		= (LPFN_GSDNW) ::GetProcAddress (m_hAdvAPI, "GetServiceDisplayNameW");
		m_lpfnLockServiceDatabase			= (LPFN_LSD) ::GetProcAddress (m_hAdvAPI, "LockServiceDatabase");
		m_lpfnNotifyBootConfigStatus		= (LPFN_NBCS) ::GetProcAddress (m_hAdvAPI, "NotifyBootConfigStatus");
		m_lpfnOpenSCManagerA				= (LPFN_OSCMA) ::GetProcAddress (m_hAdvAPI, "OpenSCManagerA");
		m_lpfnOpenSCManagerW				= (LPFN_OSCMW) ::GetProcAddress (m_hAdvAPI, "OpenSCManagerW");
		m_lpfnOpenServiceA					= (LPFN_OSA) ::GetProcAddress (m_hAdvAPI, "OpenServiceA");
		m_lpfnOpenServiceW					= (LPFN_OSW) ::GetProcAddress (m_hAdvAPI, "OpenServiceW");
		m_lpfnQueryServiceConfigA			= (LPFN_QSCA) ::GetProcAddress (m_hAdvAPI, "QueryServiceConfigA");
		m_lpfnQueryServiceConfigW			= (LPFN_QSCW) ::GetProcAddress (m_hAdvAPI, "QueryServiceConfigW");
		m_lpfnQueryServiceConfig2A			= (LPFN_QSC2A) ::GetProcAddress (m_hAdvAPI, "QueryServiceConfig2A");
		m_lpfnQueryServiceConfig2W			= (LPFN_QSC2W) ::GetProcAddress (m_hAdvAPI, "QueryServiceConfig2W");
		m_lpfnQueryServiceLockStatusA		= (LPFN_QSLSA) ::GetProcAddress (m_hAdvAPI, "QueryServiceLockStatusA");
		m_lpfnQueryServiceLockStatusW		= (LPFN_QSLSW) ::GetProcAddress (m_hAdvAPI, "QueryServiceLockStatusW");
		m_lpfnQueryServiceObjectSecurity	= (LPFN_QSOS) ::GetProcAddress (m_hAdvAPI, "QueryServiceObjectSecurity");
		m_lpfnQueryServiceStatus			= (LPFN_QSS) ::GetProcAddress (m_hAdvAPI, "QueryServiceStatus");
		m_lpfnRegisterServiceCtrlHandlerA	= (LPFN_RSCHA) ::GetProcAddress (m_hAdvAPI, "RegisterServiceCtrlHandlerA");
		m_lpfnRegisterServiceCtrlHandlerW	= (LPFN_RSCHW) ::GetProcAddress (m_hAdvAPI, "RegisterServiceCtrlHandlerW");
		m_lpfnSetServiceObjectSecurity		= (LPFN_SSOS) ::GetProcAddress (m_hAdvAPI, "SetServiceObjectSecurity");
		m_lpfnSetServiceStatus				= (LPFN_SSS) ::GetProcAddress (m_hAdvAPI, "SetServiceStatus");
		m_lpfnStartServiceCtrlDispatcherA	= (LPFN_SSCDA) ::GetProcAddress (m_hAdvAPI, "StartServiceCtrlDispatcherA");
		m_lpfnStartServiceCtrlDispatcherW	= (LPFN_SSCDW) ::GetProcAddress (m_hAdvAPI, "StartServiceCtrlDispatcherW");
		m_lpfnStartServiceA					= (LPFN_SSA) ::GetProcAddress (m_hAdvAPI, "StartServiceA");
		m_lpfnStartServiceW					= (LPFN_SSW) ::GetProcAddress (m_hAdvAPI, "StartServiceW");
		m_lpfnUnlockServiceDatabase			= (LPFN_USD) ::GetProcAddress (m_hAdvAPI, "UnlockServiceDatabase");
	}
	return true;
}

void STUB_LOADER::FreeLibrary ()
{
	if ( m_hAdvAPI ) {
		::FreeLibrary (m_hAdvAPI);
	}
	if ( m_hKernel ) {
		::FreeLibrary (m_hKernel);
	}
	CommonConstructor ();
}


/*=============================================================================
 * NT API PSEUDOFUNCTIONS
 *============================================================================*/
BOOL YLBAPI YlbEncryptFileA (
	LPCSTR		lpFileName
)
{
	if ( !_stub.m_lpfnEncryptFileA ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnEncryptFileA (lpFileName);
}

BOOL YLBAPI YlbEncryptFileW (
	LPCWSTR		lpFileName
)
{
	if ( !_stub.m_lpfnEncryptFileW ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnEncryptFileW (lpFileName);
}

BOOL YLBAPI YlbDecryptFileA (
	LPCSTR		lpFileName,
	DWORD		dwReserved
)
{
	if ( !_stub.m_lpfnDecryptFileA ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnDecryptFileA (lpFileName, dwReserved);
}

BOOL YLBAPI YlbDecryptFileW (
	LPCWSTR		lpFileName,
	DWORD		dwReserved
)
{
	if ( !_stub.m_lpfnDecryptFileW ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnDecryptFileW (lpFileName, dwReserved);
}

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
)
{
	if ( !_stub.m_lpfnChangeServiceConfigA ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnChangeServiceConfigA (hService, dwServiceType, dwStartType, dwErrorControl, lpBinaryPathName, lpLoadOrderGroup, lpdwTagId, lpDependencies, lpServiceStartName, lpPassword, lpDisplayName);
}

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
)
{
	if ( !_stub.m_lpfnChangeServiceConfigW ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnChangeServiceConfigW (hService, dwServiceType, dwStartType, dwErrorControl, lpBinaryPathName, lpLoadOrderGroup, lpdwTagId, lpDependencies, lpServiceStartName, lpPassword, lpDisplayName);
}

BOOL YLBAPI YlbChangeServiceConfig2A (
	SC_HANDLE	hService,
	DWORD		dwInfoLevel,
	LPVOID		lpInfo
)
{
	if ( !_stub.m_lpfnChangeServiceConfig2A ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnChangeServiceConfig2A (hService, dwInfoLevel, lpInfo);
}

BOOL YLBAPI YlbChangeServiceConfig2W (
	SC_HANDLE	hService,
	DWORD		dwInfoLevel,
	LPVOID		lpInfo
)
{
	if ( !_stub.m_lpfnChangeServiceConfig2W ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnChangeServiceConfig2W (hService, dwInfoLevel, lpInfo);
}

BOOL YLBAPI YlbCloseServiceHandle (
	SC_HANDLE	hSCObject
)
{
	if ( !_stub.m_lpfnCloseServiceHandle ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnCloseServiceHandle (hSCObject);
}

BOOL YLBAPI YlbControlService (
	SC_HANDLE			hService,
	DWORD				dwControl,
	LPSERVICE_STATUS	lpServiceStatus
)
{
	if ( !_stub.m_lpfnControlService ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnControlService (hService, dwControl, lpServiceStatus);
}

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
)
{
	if ( !_stub.m_lpfnCreateServiceA ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return NULL;
	}
	return _stub.m_lpfnCreateServiceA (hSCManager, lpServiceName, lpDisplayName, dwDesiredAccess, dwServiceType, dwStartType, dwErrorControl, lpBinaryPathName, lpLoadOrderGroup, lpdwTagId, lpDependencies, lpServiceStartName, lpPassword);
}

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
)
{
	if ( !_stub.m_lpfnCreateServiceW ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return NULL;
	}
	return _stub.m_lpfnCreateServiceW (hSCManager, lpServiceName, lpDisplayName, dwDesiredAccess, dwServiceType, dwStartType, dwErrorControl, lpBinaryPathName, lpLoadOrderGroup, lpdwTagId, lpDependencies, lpServiceStartName, lpPassword);
}

BOOL YLBAPI YlbDeleteService (
	SC_HANDLE	hService
)
{
	if ( !_stub.m_lpfnDeleteService ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnDeleteService (hService);
}

BOOL YLBAPI YlbEnumDependentServicesA (
	SC_HANDLE				hService,
	DWORD					dwServiceState,
	LPENUM_SERVICE_STATUSA	lpServices,
	DWORD					cbBufSize,
	LPDWORD					pcbBytesNeeded,
	LPDWORD					lpServicesReturned
)
{
	if ( !_stub.m_lpfnEnumDependentServicesA ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnEnumDependentServicesA (hService, dwServiceState, lpServices, cbBufSize, pcbBytesNeeded, lpServicesReturned);
}

BOOL YLBAPI YlbEnumDependentServicesW (
	SC_HANDLE				hService,
	DWORD					dwServiceState,
	LPENUM_SERVICE_STATUSW	lpServices,
	DWORD					cbBufSize,
	LPDWORD					pcbBytesNeeded,
	LPDWORD					lpServicesReturned
)
{
	if ( !_stub.m_lpfnEnumDependentServicesW ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnEnumDependentServicesW (hService, dwServiceState, lpServices, cbBufSize, pcbBytesNeeded, lpServicesReturned);
}

BOOL YLBAPI YlbEnumServicesStatusA (
	SC_HANDLE				hSCManager,
	DWORD					dwServiceType,
	DWORD					dwServiceState,
	LPENUM_SERVICE_STATUSA	lpServices,
	DWORD					cbBufSize,
	LPDWORD					pcbBytesNeeded,
	LPDWORD					lpServicesReturned,
	LPDWORD					lpResumeHandle
)
{
	if ( !_stub.m_lpfnEnumServicesStatusA ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnEnumServicesStatusA (hSCManager, dwServiceType, dwServiceState, lpServices, cbBufSize, pcbBytesNeeded, lpServicesReturned, lpResumeHandle);
}

BOOL YLBAPI YlbEnumServicesStatusW (
	SC_HANDLE				hSCManager,
	DWORD					dwServiceType,
	DWORD					dwServiceState,
	LPENUM_SERVICE_STATUSW	lpServices,
	DWORD					cbBufSize,
	LPDWORD					pcbBytesNeeded,
	LPDWORD					lpServicesReturned,
	LPDWORD					lpResumeHandle
)
{
	if ( !_stub.m_lpfnEnumServicesStatusW ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnEnumServicesStatusW (hSCManager, dwServiceType, dwServiceState, lpServices, cbBufSize, pcbBytesNeeded, lpServicesReturned, lpResumeHandle);

}

BOOL YLBAPI YlbGetServiceKeyNameA (
	SC_HANDLE	hSCManager,
	LPCSTR		lpDisplayName,
	LPSTR		lpServiceName,
	LPDWORD		lpcchBuffer
)
{
	if ( !_stub.m_lpfnGetServiceKeyNameA ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnGetServiceKeyNameA (hSCManager, lpDisplayName, lpServiceName, lpcchBuffer);
}

BOOL YLBAPI YlbGetServiceKeyNameW (
	SC_HANDLE	hSCManager,
	LPCWSTR		lpDisplayName,
	LPWSTR		lpServiceName,
	LPDWORD		lpcchBuffer
)
{
	if ( !_stub.m_lpfnGetServiceKeyNameW ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnGetServiceKeyNameW (hSCManager, lpDisplayName, lpServiceName, lpcchBuffer);
}

BOOL YLBAPI YlbGetServiceDisplayNameA (
	SC_HANDLE	hSCManager,
	LPCSTR		lpServiceName,
	LPSTR		lpDisplayName,
	LPDWORD		lpcchBuffer
)
{
	if ( !_stub.m_lpfnGetServiceDisplayNameA ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnGetServiceDisplayNameA (hSCManager, lpServiceName, lpDisplayName, lpcchBuffer);
}

BOOL YLBAPI YlbGetServiceDisplayNameW (
	SC_HANDLE	hSCManager,
	LPCWSTR		lpServiceName,
	LPWSTR		lpDisplayName,
	LPDWORD		lpcchBuffer
)
{
	if ( !_stub.m_lpfnGetServiceDisplayNameW ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnGetServiceDisplayNameW (hSCManager, lpServiceName, lpDisplayName, lpcchBuffer);
}

SC_LOCK YLBAPI YlbLockServiceDatabase (
	SC_HANDLE	hSCManager
)
{
	if ( !_stub.m_lpfnLockServiceDatabase ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return NULL;
	}
	return _stub.m_lpfnLockServiceDatabase (hSCManager);
}

BOOL YLBAPI YlbNotifyBootConfigStatus (
	BOOL	BootAcceptable
)
{
	if ( !_stub.m_lpfnNotifyBootConfigStatus ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnNotifyBootConfigStatus (BootAcceptable);
}

SC_HANDLE YLBAPI YlbOpenSCManagerA (
	LPCSTR	lpMachineName,
	LPCSTR	lpDatabaseName,
	DWORD	dwDesiredAccess
)
{
	if ( !_stub.m_lpfnOpenSCManagerA ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return NULL;
	}
	return _stub.m_lpfnOpenSCManagerA (lpMachineName, lpDatabaseName, dwDesiredAccess);
}

SC_HANDLE YLBAPI YlbOpenSCManagerW (
	LPCWSTR	lpMachineName,
	LPCWSTR	lpDatabaseName,
	DWORD	dwDesiredAccess
)
{
	if ( !_stub.m_lpfnOpenSCManagerW ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return NULL;
	}
	return _stub.m_lpfnOpenSCManagerW (lpMachineName, lpDatabaseName, dwDesiredAccess);
}

SC_HANDLE YLBAPI YlbOpenServiceA (
	SC_HANDLE	hSCManager,
	LPCSTR		lpServiceName,
	DWORD		dwDesiredAccess
)
{
	if ( !_stub.m_lpfnOpenServiceA ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return NULL;
	}
	return _stub.m_lpfnOpenServiceA (hSCManager, lpServiceName, dwDesiredAccess);
}

SC_HANDLE YLBAPI YlbOpenServiceW (
	SC_HANDLE	hSCManager,
	LPCWSTR		lpServiceName,
	DWORD		dwDesiredAccess
)
{
	if ( !_stub.m_lpfnOpenServiceW ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return NULL;
	}
	return _stub.m_lpfnOpenServiceW (hSCManager, lpServiceName, dwDesiredAccess);
}

BOOL YLBAPI YlbQueryServiceConfigA (
	SC_HANDLE				hService,
	LPQUERY_SERVICE_CONFIGA	lpServiceConfig,
	DWORD					cbBufSize,
	LPDWORD					pcbBytesNeeded
)
{
	if ( !_stub.m_lpfnQueryServiceConfigA ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnQueryServiceConfigA (hService, lpServiceConfig, cbBufSize, pcbBytesNeeded);
}

BOOL YLBAPI YlbQueryServiceConfigW (
	SC_HANDLE				hService,
	LPQUERY_SERVICE_CONFIGW	lpServiceConfig,
	DWORD					cbBufSize,
	LPDWORD					pcbBytesNeeded
)
{
	if ( !_stub.m_lpfnQueryServiceConfigW ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnQueryServiceConfigW (hService, lpServiceConfig, cbBufSize, pcbBytesNeeded);
}

BOOL YLBAPI YlbQueryServiceConfig2A (
	SC_HANDLE	hService,
	DWORD		dwInfoLevel,
	LPBYTE		lpBuffer,
	DWORD		cbBufSize,
	LPDWORD		pcbBytesNeeded
)
{
	if ( !_stub.m_lpfnQueryServiceConfig2A ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnQueryServiceConfig2A (hService, dwInfoLevel, lpBuffer, cbBufSize, pcbBytesNeeded);
}

BOOL YLBAPI YlbQueryServiceConfig2W (
	SC_HANDLE	hService,
	DWORD		dwInfoLevel,
	LPBYTE		lpBuffer,
	DWORD		cbBufSize,
	LPDWORD		pcbBytesNeeded
)
{
	if ( !_stub.m_lpfnQueryServiceConfig2W ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnQueryServiceConfig2W (hService, dwInfoLevel, lpBuffer, cbBufSize, pcbBytesNeeded);
}

BOOL YLBAPI YlbQueryServiceLockStatusA (
	SC_HANDLE						hSCManager,
	LPQUERY_SERVICE_LOCK_STATUSA	lpLockStatus,
	DWORD							cbBufSize,
	LPDWORD							pcbBytesNeeded
)
{
	if ( !_stub.m_lpfnQueryServiceLockStatusA ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnQueryServiceLockStatusA (hSCManager, lpLockStatus, cbBufSize, pcbBytesNeeded);
}

BOOL YLBAPI YlbQueryServiceLockStatusW (
	SC_HANDLE						hSCManager,
	LPQUERY_SERVICE_LOCK_STATUSW	lpLockStatus,
	DWORD							cbBufSize,
	LPDWORD							pcbBytesNeeded
)
{
	if ( !_stub.m_lpfnQueryServiceLockStatusW ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnQueryServiceLockStatusW (hSCManager, lpLockStatus, cbBufSize, pcbBytesNeeded);
}

BOOL YLBAPI YlbQueryServiceObjectSecurity (
	SC_HANDLE				hService,
	SECURITY_INFORMATION	dwSecurityInformation,
	PSECURITY_DESCRIPTOR	lpSecurityDescriptor,
	DWORD					cbBufSize,
	LPDWORD					pcbBytesNeeded
)
{
	if ( !_stub.m_lpfnQueryServiceObjectSecurity ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnQueryServiceObjectSecurity (hService, dwSecurityInformation, lpSecurityDescriptor, cbBufSize, pcbBytesNeeded);
}

BOOL YLBAPI YlbQueryServiceStatus (
	SC_HANDLE			hService,
	LPSERVICE_STATUS	lpServiceStatus
)
{
	if ( !_stub.m_lpfnQueryServiceStatus ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnQueryServiceStatus (hService, lpServiceStatus);
}

SERVICE_STATUS_HANDLE YLBAPI YlbRegisterServiceCtrlHandlerA (
	LPCSTR				lpServiceName,
	LPHANDLER_FUNCTION	lpHandlerProc
)
{
	if ( !_stub.m_lpfnRegisterServiceCtrlHandlerA ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnRegisterServiceCtrlHandlerA (lpServiceName, lpHandlerProc);
}

SERVICE_STATUS_HANDLE YLBAPI YlbRegisterServiceCtrlHandlerW (
	LPCWSTR				lpServiceName,
	LPHANDLER_FUNCTION	lpHandlerProc
)
{
	if ( !_stub.m_lpfnRegisterServiceCtrlHandlerW ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnRegisterServiceCtrlHandlerW (lpServiceName, lpHandlerProc);
}

BOOL YLBAPI YlbSetServiceObjectSecurity (
	SC_HANDLE				hService,
	SECURITY_INFORMATION	dwSecurityInformation,
	PSECURITY_DESCRIPTOR	lpSecurityDescriptor
)
{
	if ( !_stub.m_lpfnSetServiceObjectSecurity ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnSetServiceObjectSecurity (hService, dwSecurityInformation, lpSecurityDescriptor);
}

BOOL YLBAPI YlbSetServiceStatus (
	SERVICE_STATUS_HANDLE	hServiceStatus,
	LPSERVICE_STATUS		lpServiceStatus
)
{
	if ( !_stub.m_lpfnSetServiceStatus ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnSetServiceStatus (hServiceStatus, lpServiceStatus);
}

BOOL YLBAPI YlbStartServiceCtrlDispatcherA (
	CONST SERVICE_TABLE_ENTRYA *	lpServiceStartTable
)
{
	if ( !_stub.m_lpfnStartServiceCtrlDispatcherA ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnStartServiceCtrlDispatcherA (lpServiceStartTable);
}

BOOL YLBAPI YlbStartServiceCtrlDispatcherW (
	CONST SERVICE_TABLE_ENTRYW *	lpServiceStartTable
)
{
	if ( !_stub.m_lpfnStartServiceCtrlDispatcherW ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnStartServiceCtrlDispatcherW (lpServiceStartTable);
}

BOOL YLBAPI YlbStartServiceA (
	SC_HANDLE	hService,
	DWORD		dwNumServiceArgs,
	LPCSTR *	lpServiceArgVectors
)
{
	if ( !_stub.m_lpfnStartServiceA ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnStartServiceA (hService, dwNumServiceArgs, lpServiceArgVectors);
}

BOOL YLBAPI YlbStartServiceW (
	SC_HANDLE	hService,
	DWORD		dwNumServiceArgs,
	LPCWSTR *	lpServiceArgVectors
)
{
	if ( !_stub.m_lpfnStartServiceW ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnStartServiceW (hService, dwNumServiceArgs, lpServiceArgVectors);
}

BOOL YLBAPI YlbUnlockServiceDatabase (
	SC_LOCK	ScLock
)
{
	if ( !_stub.m_lpfnUnlockServiceDatabase ) {
		::SetLastError (ERROR_INVALID_FUNCTION);
		return FALSE;
	}
	return _stub.m_lpfnUnlockServiceDatabase (ScLock);
}

#endif //YLB_NATIVE_NT_LINKING

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////