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
 * FILENAME		:	internal.h
 * PURPOSE		:	Internal common stuff
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.3  2001/05/16 17:15:53  leopoldo
 * Added support for reattachment of RTL output handles
 *
 * Revision 1.2  2000/08/23 10:01:41  leo
 * Added inlined format function
 * Updated license
 *
 * Revision 1.1  2000/05/26  14:04:48  leo
 * Initial revision
 *
 *============================================================================*/

#ifndef _ylib_internal_
#define _ylib_internal_

/*=============================================================================
 * INTERNAL EXCEPTION CLASS
 *============================================================================*/
class YException : public YErrableObject
{
public:
	// construction
	YException					(DWORD dwError) : YErrableObject (dwError) { }
};

/*=============================================================================
 * FORWARD CLASS DECLARATIONS
 *============================================================================*/
class YConApp;

/*=============================================================================
 * PROCESS ENVIRONMENT
 *============================================================================*/
class PROC_ENV
{
public:
	PROC_ENV					();
	~PROC_ENV					();

public:
	YConApp						*m_pApp;
	YCommandLineInfo			m_cli;
	YFlags						m_flg;

	HANDLE						m_hProcessHandle;
	HANDLE						m_hThreadHandle;
	HINSTANCE					m_hInstance;
	HINSTANCE					m_hResHandle;
	HANDLE						m_hStdIn;
	HANDLE						m_hStdOut;
	HANDLE						m_hStdErr;
	int							m_iStdOut;
	int							m_iStdErr;
	FILE *						m_fpStdOut;
	FILE *						m_fpStdErr;
};

#define FLG_APP_YCONAPP			0x00000001
#define FLG_APP_YSERVICE		0x00000002
#define FLG_APP_USER			0x00010000

extern PROC_ENV					_proc;

/*=============================================================================
 * LIBRARY ENVIRONMENT DATA
 *============================================================================*/
class YAUX_DATA
{
public:
	// other system information
	UINT						nWinVer;        // Major.Minor version numbers
	BOOL						bWin95;         // TRUE if Windows 95 (not NT)
	BOOL						bWin4;          // TRUE if Windows 4.0
	BOOL						bNotWin4;       // TRUE if not Windows 4.0

public:
// Implementation
	YAUX_DATA					();
	~YAUX_DATA					();
};

/*=============================================================================
 * INSTANTIATION
 *============================================================================*/
extern YAUX_DATA				ylbData;

/*=============================================================================
 * CONVERSION HELPERS
 *============================================================================*/
int YLB_CDECL					_ywcstombsz				(char* mbstr, const wchar_t* wcstr, size_t count);
int YLB_CDECL					_ymbstowcsz				(wchar_t* wcstr, const char* mbstr, size_t count);

/*=============================================================================
 * DEBUGGING REPORT HOOK
 *============================================================================*/
#ifdef _DEBUG
extern "C" int					_ylb_report_hook		(int reportType, char *userMessage, int *retVal);
#endif

/*=============================================================================
 * CONSOLE HANDLER
 *============================================================================*/
extern "C" BOOL WINAPI			_ylb_console_handler	(DWORD dwCtrlType);

/*=============================================================================
 * INLINED HELPERS
 *============================================================================*/
inline void						_ylb_formatv			(LPTSTR pszBuffer, UINT cbSize, LPCTSTR pszFormat, va_list argList)
{
	if ( _vsntprintf (pszBuffer, cbSize - 1, pszFormat, argList) < 0 ) {
		pszBuffer[cbSize - 1] = 0;
	}
}

#ifndef YLB_NATIVE_NT_LINKING

typedef BOOL  (WINAPI * LPFN_CSCA) (
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

typedef BOOL (WINAPI * LPFN_CSCW) (
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

typedef BOOL (WINAPI * LPFN_CSC2A) (
	SC_HANDLE	hService,
	DWORD		dwInfoLevel,
	LPVOID		lpInfo
);

typedef BOOL (WINAPI * LPFN_CSC2W) (
	SC_HANDLE	hService,
	DWORD		dwInfoLevel,
	LPVOID		lpInfo
);

typedef BOOL (WINAPI * LPFN_CSH) (
	SC_HANDLE	hSCObject
);

typedef BOOL (WINAPI * LPFN_CS) (
	SC_HANDLE			hService,
	DWORD				dwControl,
	LPSERVICE_STATUS	lpServiceStatus
);

typedef SC_HANDLE (WINAPI * LPFN_CSA) (
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

typedef SC_HANDLE (WINAPI * LPFN_CSW) (
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

typedef BOOL (WINAPI * LPFN_DS) (
	SC_HANDLE	hService
);

typedef BOOL (WINAPI * LPFN_EDSA) (
	SC_HANDLE				hService,
	DWORD					dwServiceState,
	LPENUM_SERVICE_STATUSA	lpServices,
	DWORD					cbBufSize,
	LPDWORD					pcbBytesNeeded,
	LPDWORD					lpServicesReturned
);


typedef BOOL (WINAPI * LPFN_EDSW) (
	SC_HANDLE				hService,
	DWORD					dwServiceState,
	LPENUM_SERVICE_STATUSW	lpServices,
	DWORD					cbBufSize,
	LPDWORD					pcbBytesNeeded,
	LPDWORD					lpServicesReturned
);

typedef BOOL (WINAPI * LPFN_ESSA) (
	SC_HANDLE				hSCManager,
	DWORD					dwServiceType,
	DWORD					dwServiceState,
	LPENUM_SERVICE_STATUSA	lpServices,
	DWORD					cbBufSize,
	LPDWORD					pcbBytesNeeded,
	LPDWORD					lpServicesReturned,
	LPDWORD					lpResumeHandle
);

typedef BOOL (WINAPI * LPFN_ESSW) (
	SC_HANDLE				hSCManager,
	DWORD					dwServiceType,
	DWORD					dwServiceState,
	LPENUM_SERVICE_STATUSW	lpServices,
	DWORD					cbBufSize,
	LPDWORD					pcbBytesNeeded,
	LPDWORD					lpServicesReturned,
	LPDWORD					lpResumeHandle
);

typedef BOOL (WINAPI * LPFN_GSKNA) (
	SC_HANDLE	hSCManager,
	LPCSTR		lpDisplayName,
	LPSTR		lpServiceName,
	LPDWORD		lpcchBuffer
);

typedef BOOL (WINAPI * LPFN_GSKNW) (
	SC_HANDLE	hSCManager,
	LPCWSTR		lpDisplayName,
	LPWSTR		lpServiceName,
	LPDWORD		lpcchBuffer
);

typedef BOOL (WINAPI * LPFN_GSDNA) (
	SC_HANDLE	hSCManager,
	LPCSTR		lpServiceName,
	LPSTR		lpDisplayName,
	LPDWORD		lpcchBuffer
);

typedef BOOL (WINAPI * LPFN_GSDNW) (
	SC_HANDLE	hSCManager,
	LPCWSTR		lpServiceName,
	LPWSTR		lpDisplayName,
	LPDWORD		lpcchBuffer
);

typedef SC_LOCK (WINAPI * LPFN_LSD) (
	SC_HANDLE	hSCManager
);

typedef BOOL (WINAPI * LPFN_NBCS) (
	BOOL	BootAcceptable
);

typedef SC_HANDLE (WINAPI * LPFN_OSCMA) (
	LPCSTR	lpMachineName,
	LPCSTR	lpDatabaseName,
	DWORD	dwDesiredAccess
);

typedef SC_HANDLE (WINAPI * LPFN_OSCMW) (
	LPCWSTR	lpMachineName,
	LPCWSTR	lpDatabaseName,
	DWORD	dwDesiredAccess
);

typedef SC_HANDLE (WINAPI * LPFN_OSA) (
	SC_HANDLE	hSCManager,
	LPCSTR		lpServiceName,
	DWORD		dwDesiredAccess
);

typedef SC_HANDLE (WINAPI * LPFN_OSW) (
	SC_HANDLE	hSCManager,
	LPCWSTR		lpServiceName,
	DWORD		dwDesiredAccess
);

typedef BOOL (WINAPI * LPFN_QSCA) (
	SC_HANDLE				hService,
	LPQUERY_SERVICE_CONFIGA	lpServiceConfig,
	DWORD					cbBufSize,
	LPDWORD					pcbBytesNeeded
);

typedef BOOL (WINAPI * LPFN_QSCW) (
	SC_HANDLE				hService,
	LPQUERY_SERVICE_CONFIGW	lpServiceConfig,
	DWORD					cbBufSize,
	LPDWORD					pcbBytesNeeded
);


typedef BOOL (WINAPI *LPFN_QSC2A) (
	SC_HANDLE	hService,
	DWORD		dwInfoLevel,
	LPBYTE		lpBuffer,
	DWORD		cbBufSize,
	LPDWORD		pcbBytesNeeded
);

typedef BOOL (WINAPI * LPFN_QSC2W) (
	SC_HANDLE	hService,
	DWORD		dwInfoLevel,
	LPBYTE		lpBuffer,
	DWORD		cbBufSize,
	LPDWORD		pcbBytesNeeded
);

typedef BOOL (WINAPI * LPFN_QSLSA) (
	SC_HANDLE						hSCManager,
	LPQUERY_SERVICE_LOCK_STATUSA	lpLockStatus,
	DWORD							cbBufSize,
	LPDWORD							pcbBytesNeeded
);

typedef BOOL (WINAPI * LPFN_QSLSW) (
	SC_HANDLE						hSCManager,
	LPQUERY_SERVICE_LOCK_STATUSW	lpLockStatus,
	DWORD							cbBufSize,
	LPDWORD							pcbBytesNeeded
);

typedef BOOL (WINAPI * LPFN_QSOS) (
	SC_HANDLE				hService,
	SECURITY_INFORMATION	dwSecurityInformation,
	PSECURITY_DESCRIPTOR	lpSecurityDescriptor,
	DWORD					cbBufSize,
	LPDWORD					pcbBytesNeeded
);

typedef BOOL (WINAPI * LPFN_QSS) (
	SC_HANDLE			hService,
	LPSERVICE_STATUS	lpServiceStatus
);

typedef SERVICE_STATUS_HANDLE (WINAPI * LPFN_RSCHA) (
	LPCSTR				lpServiceName,
	LPHANDLER_FUNCTION	lpHandlerProc
);

typedef SERVICE_STATUS_HANDLE (WINAPI * LPFN_RSCHW) (
	LPCWSTR				lpServiceName,
	LPHANDLER_FUNCTION	lpHandlerProc
);

typedef BOOL (WINAPI * LPFN_SSOS) (
	SC_HANDLE				hService,
	SECURITY_INFORMATION	dwSecurityInformation,
	PSECURITY_DESCRIPTOR	lpSecurityDescriptor
);

typedef BOOL (WINAPI * LPFN_SSS) (
	SERVICE_STATUS_HANDLE	hServiceStatus,
	LPSERVICE_STATUS		lpServiceStatus
);

typedef BOOL (WINAPI * LPFN_SSCDA) (
	CONST SERVICE_TABLE_ENTRYA *	lpServiceStartTable
);

typedef BOOL (WINAPI * LPFN_SSCDW) (
	CONST SERVICE_TABLE_ENTRYW *	lpServiceStartTable
);

typedef BOOL (WINAPI * LPFN_SSA) (
	SC_HANDLE	hService,
	DWORD		dwNumServiceArgs,
	LPCSTR *	lpServiceArgVectors
);

typedef BOOL (WINAPI * LPFN_SSW) (
	SC_HANDLE	hService,
	DWORD		dwNumServiceArgs,
	LPCWSTR *	lpServiceArgVectors
);

typedef BOOL (WINAPI * LPFN_USD) (
	SC_LOCK	ScLock
);

#endif //YLB_NATIVE_NT_LINKING

#endif //_ylib_internal_
//
// EoF
////////