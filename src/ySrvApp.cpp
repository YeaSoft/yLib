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
 * FILENAME		:	ySrvApp.cpp
 * PURPOSE		:	Implementation of the system service classes
 * SCOPE		:	yAfc
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

#include "StdAfc.hpp"

/*============================================================================*
 * @doc YLIB | yService.h
 *============================================================================*/

#ifdef _DEBUG
#undef HERE
static char HERE[] = __FILE__;
#endif //_DEBUG

/*============================================================================*
 * SERVICE RUNTIME FUNCTION PROTOTYPES AND HANDLER TABLE
 *============================================================================*/
extern "C" static VOID WINAPI	_ylb_service_main		(DWORD dwArgc, LPTSTR *lpszArgv);
extern "C" static VOID WINAPI	_ylb_service_ctr0		(DWORD dwCtrlCode);
extern "C" static VOID WINAPI	_ylb_service_ctr1		(DWORD dwCtrlCode);
extern "C" static VOID WINAPI	_ylb_service_ctr2		(DWORD dwCtrlCode);
extern "C" static VOID WINAPI	_ylb_service_ctr3		(DWORD dwCtrlCode);
extern "C" static VOID WINAPI	_ylb_service_ctr4		(DWORD dwCtrlCode);
extern "C" static VOID WINAPI	_ylb_service_ctr5		(DWORD dwCtrlCode);
extern "C" static VOID WINAPI	_ylb_service_ctr6		(DWORD dwCtrlCode);
extern "C" static VOID WINAPI	_ylb_service_ctr7		(DWORD dwCtrlCode);

LPHANDLER_FUNCTION _ytab_service_ctrl[] = {
	_ylb_service_ctr0,
	_ylb_service_ctr1,
	_ylb_service_ctr2,
	_ylb_service_ctr3,
	_ylb_service_ctr4,
	_ylb_service_ctr5,
	_ylb_service_ctr6,
	_ylb_service_ctr7
};

#if (YLB_MAX_SERVICES > 8)
#error Maximum number of services reached!
#endif

/*============================================================================*
 * THE SERVICE COMMANDLINE PARSER
 *============================================================================*/
YServiceCmdLineParser::YServiceCmdLineParser (BOOL bAutoParse)
{
	if ( bAutoParse ) {
		Parse ();
	}
}

BOOL YServiceCmdLineParser::OnProcessOption (BOOL &bTerminate, LPCTSTR &pszOptString, YCmdLineOption &cliOpt)
{
	switch ( cliOpt.GetOption () ) {
	case _T('i'):
		SetOptionFlags (SCL_OPT_INTERACTIVE);
		cliOpt.ResetAdditionalArgs ();
		++pszOptString;
		return TRUE;
	case _T('a'):
		SetOptionFlags (SCL_OPT_START_AUTO);
		cliOpt.ResetAdditionalArgs ();
		++pszOptString;
		return TRUE;
	case _T('d'):
		SetOptionFlags (SCL_OPT_START_DISABLE);
		cliOpt.ResetAdditionalArgs ();
		++pszOptString;
		return TRUE;
	case _T('u'):
		SetOptionFlags (SCL_OPT_USER_NAME);
		cliOpt.SetMeaning (SCL_OPT_USER_NAME);
		if ( cliOpt.GetParamCount () > 1 )  {
			cliOpt.SetParamCount (1);
		}
		++pszOptString;
		return TRUE;
	case _T('p'):
		SetOptionFlags (SCL_OPT_USER_PWD);
		cliOpt.SetMeaning (SCL_OPT_USER_PWD);
		if ( cliOpt.GetParamCount () > 1 )  {
			cliOpt.SetParamCount (1);
		}
		++pszOptString;
		return TRUE;
	}
	return FALSE;
}

BOOL YServiceCmdLineParser::OnProcessParam (BOOL &bTerminate, YCmdLineParam &cliPar)
{
	typedef struct {
		LPCTSTR	pszCmd;
		DWORD	appCmd;
	} CMDMATRIX;

	CMDMATRIX	cmCmds[] = {
		{ _T("help"),		SCL_CMD_WANTSHELP },
		{ _T("install"),	SCL_CMD_INSTALL },
		{ _T("remove"),		SCL_CMD_REMOVE },
		{ _T("start"),		SCL_CMD_START },
		{ _T("stop"),		SCL_CMD_STOP },
		{ _T("pause"),		SCL_CMD_PAUSE },
		{ _T("resume"),		SCL_CMD_RESUME },
		{ _T("simulate"),	SCL_CMD_SIMULATE }
	};

	DWORD dwCmd = SCL_CMD_UNKNOWN;
	for ( DWORD dw = 0; dw < _countof (cmCmds); dw++ ) {
		if ( !_tcsicmp (cmCmds[dw].pszCmd, cliPar.GetParam ()) ) {
			dwCmd = cmCmds[dw].appCmd;
			break;
		} 
	}
	cliPar.SetMeaning (dwCmd);

	switch ( dwCmd ) {
	case SCL_CMD_WANTSHELP:
	case SCL_CMD_UNKNOWN:
		// take none
		cliPar.ResetAdditionalArgs ();
		break;
	case SCL_CMD_START:
	case SCL_CMD_SIMULATE:
		// take them all!
		break;
	case SCL_CMD_INSTALL:
	case SCL_CMD_REMOVE:
	case SCL_CMD_STOP:
	case SCL_CMD_PAUSE:
	case SCL_CMD_RESUME:
		if ( YlbGetSrv ()->IsShareService () ) {
			// take one
			if ( cliPar.m_argc ) {
				cliPar.m_argc = 1;
			}
		}
		else {
			// take none
			cliPar.ResetAdditionalArgs ();
		}
		break;
	}

	SetCommandFlags (dwCmd);
	return dwCmd != SCL_CMD_UNKNOWN;
}

void YServiceCmdLineParser::ShowUsage (DWORDLONG dwCmd)
{
	ASSERTY(YlbGetSrv ());

	YSrvApp	*pApp	= YlbGetSrv ();
	BOOL	bSingle	= pApp->IsOwnService ();

	switch ( dwCmd ) {
	case SCL_CMD_INSTALL:
		_tprintf (_T("USAGE: %s install%s [-i] [-d] [-a] %s\n\n"), pApp->GetImageName (), (bSingle) ? (_T("")) : (_T(" <svcName>")), (bSingle) ? (_T("[-u <username> -p <password>]")) : (_T("")));
		if ( bSingle ) {
			_tprintf (_T("       This command installs the %s.\n"), pApp->GetAppDescription ());
		}
		else {
			_tprintf (_T("       This command installs one of the services contained\n"));
			_tprintf (_T("       in the the %s.\n"), pApp->GetAppDescription ());
		}
		_tprintf (_T("       The following options are available:\n"));
		_tprintf (_T("       -i  Allow the service to interact with the desktop.\n"));
		_tprintf (_T("           This option cannot be used in conjunction with -u.\n"));
		_tprintf (_T("       -d  Install as a disabled service.\n"));
		_tprintf (_T("           This option cannot be used in conjunction with -a.\n"));
		_tprintf (_T("       -a  Install as an automatic starting service.\n"));
		_tprintf (_T("           This option cannot be used in conjunction with -d.\n"));
		if ( bSingle ) {
			_tprintf (_T("       -u <username>  Specify the account under which the service\n"));
			_tprintf (_T("                      will run. Cannot be used in conjunction with -i\n"));
			_tprintf (_T("       -p <password>  Specify the password for the account under which\n"));
			_tprintf (_T("                      the service will run. Must be used in conjunction\n"));
			_tprintf (_T("                      with -u\n"));
		}
		else {
			ShowServices ();
		}
		break;
	case SCL_CMD_REMOVE:
		_tprintf (_T("USAGE: %s remove%s\n\n"), pApp->GetImageName (), (bSingle) ? (_T("")) : (_T(" <svcName>")));
		if ( bSingle ) {
			_tprintf (_T("       This command uninstalls an installed %s.\n"), pApp->GetAppDescription ());
		}
		else {
			_tprintf (_T("       This command uninstalls one of the services contained\n"));
			_tprintf (_T("       in the the %s.\n"), pApp->GetAppDescription ());
			ShowServices ();
		}
		break;
	case SCL_CMD_START:
		_tprintf (_T("USAGE: %s start%s [<parm1> ...]\n\n"), pApp->GetImageName (), (bSingle) ? (_T("")) : (_T(" <svcName>")));
		if ( bSingle ) {
			_tprintf (_T("       This command starts the %s.\n"), YlbGetApp ()->GetAppDescription ());
		}
		else {
			_tprintf (_T("       This command starts one of the services contained\n"));
			_tprintf (_T("       in the the %s.\n"), pApp->GetAppDescription ());
			ShowServices ();
		}
		break;
	case SCL_CMD_STOP:
		_tprintf (_T("USAGE: %s stop%s\n\n"), pApp->GetImageName (), (bSingle) ? (_T("")) : (_T(" <svcName>")));
		if ( bSingle ) {
			_tprintf (_T("       This command stops the execution of a running %s.\n"), pApp->GetAppDescription ());
		}
		else {
			_tprintf (_T("       This command stops one of the services contained\n"));
			_tprintf (_T("       in the the %s.\n"), pApp->GetAppDescription ());
			ShowServices ();
		}
		break;
	case SCL_CMD_PAUSE:
		_tprintf (_T("USAGE: %s pause%s\n\n"), pApp->GetImageName (), (bSingle) ? (_T("")) : (_T(" <svcName>")));
		if ( bSingle ) {
			_tprintf (_T("       This command pauses the execution of a running %s.\n"), pApp->GetAppDescription ());
		}
		else {
			_tprintf (_T("       This command pauses one of the services contained\n"));
			_tprintf (_T("       in the the %s.\n"), pApp->GetAppDescription ());
			ShowServices ();
		}
		break;
	case SCL_CMD_RESUME:
		_tprintf (_T("USAGE: %s resume%s\n\n"), pApp->GetImageName (), (bSingle) ? (_T("")) : (_T(" <svcName>")));
		if ( bSingle ) {
			_tprintf (_T("       This command resumes the execution of a paused %s.\n"), pApp->GetAppDescription ());
		}
		else {
			_tprintf (_T("       This command resumes one of the services contained\n"));
			_tprintf (_T("       in the the %s.\n"), pApp->GetAppDescription ());
			ShowServices ();
		}
		break;
	case SCL_CMD_SIMULATE:
		_tprintf (_T("USAGE: %s simulate%s [<parm1> ...]\n\n"), pApp->GetImageName (), (bSingle) ? (_T("")) : (_T(" <svcName>")));
		if ( bSingle ) {
			_tprintf (_T("       This command starts the %s as an application.\n"), pApp->GetAppDescription ());
		}
		else {
			_tprintf (_T("       This command start one of the services contained\n"));
			_tprintf (_T("       in the the %s as an application.\n"), pApp->GetAppDescription ());
			ShowServices ();
		}
		break;
	default:
		_tprintf (_T("USAGE: %s <cmd> [options]\n\n"), pApp->GetImageName ());
		_tprintf (_T("       where <cmd> can be:\n"));
		_tprintf (_T("       install          Installs the %s\n"), pApp->GetAppDescription ());
		_tprintf (_T("       remove           Uninstalls the %s\n"), pApp->GetAppDescription ());
		_tprintf (_T("       start            Starts the %s\n"), pApp->GetAppDescription ());
		_tprintf (_T("       stop             Stops the %s\n"), pApp->GetAppDescription ());
		_tprintf (_T("       pause            Pauses the %s\n"), pApp->GetAppDescription ());
		_tprintf (_T("       resume           Resumes the %s\n"), pApp->GetAppDescription ());
		_tprintf (_T("       simulate         Starts the %s as an application\n"), pApp->GetAppDescription ());
		if ( !bSingle ) {
			ShowServices ();
		}
		break;
	}
}

void YServiceCmdLineParser::ShowServices ()
{
	ASSERTY(YlbGetSrv ());
	YSrvApp *pApp = YlbGetSrv ();

	_tprintf (_T("\nThe shared %s contains the following services:\n\n"), pApp->GetAppDescription ());
	for ( UINT nCnt = 1; nCnt <= pApp->GetServiceCount (); nCnt++ ) {
		YServiceLogic *pSL = pApp->GetService (nCnt);
		if ( pSL ) {
			_tprintf (_T("       %-16.16s  %s\n"), pSL->GetAppName (), pSL->GetAppDescription ());
		}
	}
}

BOOL YServiceCmdLineParser::OnFinalCheck ()
{
	if ( !GetCommands () ) {
		// standard service execution
		return TRUE;
	}
	if ( TestCommandFlags (SCL_CMD_WANTSHELP) ) {
		return TRUE;
	}
	if ( TestCommandFlags (SCL_CMD_UNKNOWN) ) {
		// unknown command specified
		ShowIntro ();
		_tprintf (_T("ERROR: unknown command specified\n\n"));
		ShowUsage (GetCommands () & SCL_CMD_MASK);
		ShowExtro ();
		return FALSE;
	}
	if ( TestOptionFlags (SCL_OPT_UNKNOWN) ) {
		// unknown command specified
		ShowIntro ();
		_tprintf (_T("ERROR: unknown option specified\n\n"));
		ShowUsage (GetCommands () & SCL_CMD_MASK);
		ShowExtro ();
		return FALSE;
	}

	// only one command permitted
	if ( TestCommandFlags (SCL_CMD_INSTALL|SCL_CMD_REMOVE|SCL_CMD_START|SCL_CMD_STOP|SCL_CMD_PAUSE|SCL_CMD_RESUME|SCL_CMD_SIMULATE, FLG_OR) ) {
		if ( !TestCommandFlags (SCL_CMD_INSTALL|SCL_CMD_REMOVE|SCL_CMD_START|SCL_CMD_STOP|SCL_CMD_PAUSE|SCL_CMD_RESUME|SCL_CMD_SIMULATE, FLG_XOR) ) {
			ShowIntro ();
			_tprintf (_T("ERROR: more than one command specified\n\n"));
			ShowUsage (GetCommands () & SCL_CMD_MASK);
			ShowExtro ();
			return FALSE;
		}
	}

	// only one start mode permitted
	if ( TestOptionFlags (SCL_OPT_START_DISABLE) && TestOptionFlags (SCL_OPT_START_AUTO) ) {
		ShowIntro ();
		_tprintf (_T("ERROR: start mode -a and -d are mutually exclusive\n\n"));
		ShowUsage (GetCommands () & SCL_CMD_MASK);
		ShowExtro ();
		return FALSE;
	}

	if ( !TestCommandFlags (SCL_CMD_INSTALL) ) {
		// user can only be specified with install
		if ( TestOptionFlags (SCL_OPT_USER_NAME|SCL_OPT_USER_PWD, FLG_OR) ) {
			ShowIntro ();
			_tprintf (_T("ERROR: the service user/password can only be specified during installation\n\n"));
			ShowUsage (GetCommands () & SCL_CMD_MASK);
			ShowExtro ();
			return FALSE;
		}
	}

	if ( TestOptionFlags (SCL_OPT_USER_PWD) ) {
		if ( !FindOptionByMeaning (SCL_OPT_USER_PWD)->GetParamCount () ) {
			ShowIntro ();
			_tprintf (_T("ERROR: no password was specified with -p\n\n"));
			ShowUsage (GetCommands () & SCL_CMD_MASK);
			ShowExtro ();
			return FALSE;
		}
		if ( !TestOptionFlags (SCL_OPT_USER_NAME) ) {
			ShowIntro ();
			_tprintf (_T("ERROR: a password cannot be specified without a user\n\n"));
			ShowUsage (GetCommands () & SCL_CMD_MASK);
			ShowExtro ();
			return FALSE;
		}
	}

	if ( TestOptionFlags (SCL_OPT_USER_NAME) ) {
		if ( !FindOptionByMeaning (SCL_OPT_USER_NAME)->GetParamCount () ) {
			ShowIntro ();
			_tprintf (_T("ERROR: no user was specified with -u\n\n"));
			ShowUsage (GetCommands () & SCL_CMD_MASK);
			ShowExtro ();
			return FALSE;
		}
	}

	return TRUE;
}

/*==================================================================================*
 * SERVICE RUNTIME FUNCTION IMPLEMENTATION
 *==================================================================================*/
extern "C" static VOID WINAPI _ylb_service_main (DWORD dwArgc, LPTSTR *lpszArgv)
{
	_proc.m_cli = YCommandLineInfo (dwArgc, lpszArgv);

#ifdef _DEBUG
	_CrtSetReportHook (_ylb_report_hook);
#endif

	ASSERTY(YlbGetSrv ());

	// find the requested service logic
	UINT nIndex			= YlbGetSrv ()->FindService (lpszArgv[0]);
	YServiceLogic *pSL	= YlbGetSrv ()->GetService (nIndex);
	ASSERTY(pSL);

	YCommandLineInfo sCLI (dwArgc, lpszArgv);

	if ( pSL->InitInstance (&sCLI) ) {
		pSL->ServiceMain (nIndex, &sCLI, TRUE);
		pSL->ExitInstance (TRUE);
	}
	else {
		pSL->ExitInstance (FALSE);
	}
}

extern "C" static VOID WINAPI _ylb_service_ctr0	 (DWORD dwCtrlCode)
{
	ASSERTY(YlbGetSrv ());
	((YSrvApp *) _proc.m_pApp)->GetService(1)->ServiceControl (dwCtrlCode);
}

extern "C" static VOID WINAPI _ylb_service_ctr1	 (DWORD dwCtrlCode)
{
	ASSERTY(YlbGetSrv ());
	((YSrvApp *) _proc.m_pApp)->GetService(2)->ServiceControl (dwCtrlCode);
}

extern "C" static VOID WINAPI _ylb_service_ctr2	 (DWORD dwCtrlCode)
{
	ASSERTY(YlbGetSrv ());
	((YSrvApp *) _proc.m_pApp)->GetService(3)->ServiceControl (dwCtrlCode);
}

extern "C" static VOID WINAPI _ylb_service_ctr3	 (DWORD dwCtrlCode)
{
	ASSERTY(YlbGetSrv ());
	((YSrvApp *) _proc.m_pApp)->GetService(4)->ServiceControl (dwCtrlCode);
}

extern "C" static VOID WINAPI _ylb_service_ctr4	 (DWORD dwCtrlCode)
{
	ASSERTY(YlbGetSrv ());
	((YSrvApp *) _proc.m_pApp)->GetService(5)->ServiceControl (dwCtrlCode);
}

extern "C" static VOID WINAPI _ylb_service_ctr5	 (DWORD dwCtrlCode)
{
	ASSERTY(YlbGetSrv ());
	((YSrvApp *) _proc.m_pApp)->GetService(6)->ServiceControl (dwCtrlCode);
}

extern "C" static VOID WINAPI _ylb_service_ctr6	 (DWORD dwCtrlCode)
{
	ASSERTY(YlbGetSrv ());
	((YSrvApp *) _proc.m_pApp)->GetService(7)->ServiceControl (dwCtrlCode);
}

extern "C" static VOID WINAPI _ylb_service_ctr7	 (DWORD dwCtrlCode)
{
	ASSERTY(YlbGetSrv ());
	((YSrvApp *) _proc.m_pApp)->GetService(8)->ServiceControl (dwCtrlCode);
}


/*============================================================================*
 * THE SERVICE LOGIC CLASS
 *============================================================================*/
//
// management overridables
//

void YServiceLogic::OnInstallError (DWORD dwError, LPCTSTR pszCompName, LPCTSTR pszImagePath)
{
	_tprintf (_T("FAILURE: The %s service cannot be installed.\n"), GetAppDescription ());
	_tprintf (_T("         CreateService Error %u:\n"), dwError);
	_tprintf (_T("         %s\n"), GetSysErrorString (dwError));
}

BOOL YServiceLogic::OnStartUI (DWORD dwState, DWORD dwWin32ExitCode, DWORD dwSeconds)
{
	if ( (dwState == SERVICE_STOPPED) ) {
		if ( dwWin32ExitCode != NOERROR ) {
			_tprintf (_T("\nFAILURE: The %s service stopped\n         with error %u.\n\n"), GetAppDescription (), dwWin32ExitCode);
			return TRUE;
		}
		else if ( !dwSeconds ) {
			_tprintf (_T("Starting"));
			return TRUE;
		}
	}
	else if ( dwState == SERVICE_RUNNING ) {
		_tprintf (_T("\nOK: The %s service was successfully started\n"), GetAppDescription ());
		return TRUE;
	}

	_tprintf (_T("."));
	return dwSeconds < 60;
}

void YServiceLogic::OnStartError (DWORD dwError, LPCTSTR pszCompName, LPCTSTR pszImagePath)
{
	_tprintf (_T("\nFAILURE: The %s service cannot be started.\n"), GetAppDescription ());
	_tprintf (_T("         StartService Error %u:\n"), dwError);
	_tprintf (_T("         %s"), GetSysErrorString (dwError));
}

BOOL YServiceLogic::OnStopUI (DWORD dwState, DWORD dwWin32ExitCode, DWORD dwSeconds)
{
	if ( (dwState != SERVICE_STOPPED) ) {
		if ( !dwSeconds ) {
			_tprintf (_T("Stopping"));
			return TRUE;
		}
		else {
			_tprintf (_T("."));
			return dwSeconds < 60;
		}
	}
	_tprintf (_T("\nOK: The %s service was successfully stopped\n"), GetAppDescription ());
	return TRUE;
}

void YServiceLogic::OnStopError (DWORD dwError, LPCTSTR pszCompName, LPCTSTR pszImagePath)
{
	_tprintf (_T("\nFAILURE: The %s service cannot be stopped.\n"), GetAppDescription ());
	_tprintf (_T("         ControlService Error %u:\n"), dwError);
	_tprintf (_T("         %s"), GetSysErrorString (dwError));
}

BOOL YServiceLogic::OnPauseUI (DWORD dwState, DWORD dwWin32ExitCode, DWORD dwSeconds)
{
	if ( (dwState == SERVICE_RUNNING) ) {
		if ( !dwSeconds ) {
			_tprintf (_T("Pausing"));
			return TRUE;
		}
		else {
			_tprintf (_T("."));
			return dwSeconds < 60;
		}
	}
	_tprintf (_T("\nOK: The %s service was successfully paused\n"), GetAppDescription ());
	return TRUE;
}

void YServiceLogic::OnPauseError (DWORD dwError, LPCTSTR pszCompName, LPCTSTR pszImagePath)
{
	_tprintf (_T("\nFAILURE: The %s service cannot be paused.\n"), GetAppDescription ());
	_tprintf (_T("         ControlService Error %u:\n"), dwError);
	_tprintf (_T("         %s"), GetSysErrorString (dwError));
}

BOOL YServiceLogic::OnContinueUI (DWORD dwState, DWORD dwWin32ExitCode, DWORD dwSeconds)
{
	if ( (dwState == SERVICE_PAUSED) ) {
		if ( !dwSeconds ) {
			_tprintf (_T("Resuming"));
			return TRUE;
		}
		else {
			_tprintf (_T("."));
			return dwSeconds < 60;
		}
	}
	_tprintf (_T("\nOK: The %s service was successfully resumed\n"), GetAppDescription ());
	return TRUE;
}

void YServiceLogic::OnContinueError (DWORD dwError, LPCTSTR pszCompName, LPCTSTR pszImagePath)
{
	_tprintf (_T("\nFAILURE: The %s service cannot be resumed.\n"), GetAppDescription ());
	_tprintf (_T("         ControlService Error %u:\n"), dwError);
	_tprintf (_T("         %s"), GetSysErrorString (dwError));
}

BOOL YServiceLogic::OnRemove (BOOL bStopped)
{
	if ( !bStopped ) {
		_tprintf (_T("FAILURE: The %s service cannot\n"));
		_tprintf (_T("         be removed because it's currently running.\n"), GetAppDescription ());
		return FALSE;
	}
	_tprintf (_T("Removing %s...\n"), GetAppDescription ());
	return TRUE;
}

void YServiceLogic::OnRemoveError (DWORD dwError, LPCTSTR pszCompName, LPCTSTR pszImagePath)
{
	_tprintf (_T("FAILURE: The %s service cannot be remove.\n"), GetAppDescription ());
	_tprintf (_T("         System Error %u:\n"), dwError);
	_tprintf (_T("         %s\n"), GetSysErrorString (dwError));
}

void YServiceLogic::AfterRemoveService (LPCTSTR pszCompName, LPCTSTR pszImagePath, BOOL bBadInstalled)
{
	if ( !bBadInstalled ) {
		_tprintf (_T("OK: The %s service was successfully removed\n"), GetAppDescription ());
	}
}

//
// very advanced overridables (the whole service logic)
//

void YServiceLogic::ServiceMain (UINT nIndex, YCommandLineInfo *cli, BOOL bRunAsService)
{
	// let's go!
	InitServiceEnvironment ();

	// open the event log
	m_evLog.Register (GetAppName ());

	// startup the service
	try {
		if ( bRunAsService ) {
			//register the service control handler
			if ( !(m_sshStatusHandle = m_theSvc->RegisterControlHandler (nIndex)) ) {
				throw YException (::GetLastError ());
			}
		}

		// report that we are starting up
		if ( !SetNewState (SERVICE_START_PENDING) ) {
			throw YException (::GetLastError ());
		}

		// report a small delay
		ReportOperationDelay (2000);

		// determine if we are running interactively
		YServiceControlManager	scm;
		if ( scm.Open () ) {
			LPQUERY_SERVICE_CONFIG lpQSC = scm.AllocQueryConfig (GetAppName ());
			if ( lpQSC ) {
				m_bInteractive = (lpQSC->dwServiceType & SERVICE_INTERACTIVE_PROCESS) != 0;
				scm.FreeQueryConfig (lpQSC);
			}
			scm.Close ();
		}

		// prepare the termination event
		if ( !m_evTerm.Create () ) {
			throw YException (::GetLastError ());
		}

		// prepare the service environment
		if ( !OnServiceStart (cli) ) {
			throw YException (ERROR_SERVICE_SPECIFIC_ERROR);
		}

		// report that we are running
		if ( !SetNewState (SERVICE_RUNNING) ) {
			throw YException (::GetLastError ());
		}

		// wait for termination
		ServiceWait (bRunAsService);

		// report that we are stopping
		if ( !SetNewState (SERVICE_STOP_PENDING) ) {
			throw YException (::GetLastError ());
		}

		// discard the termination event
		m_evTerm.Close ();

		// perform cleanup
		OnServiceEnd (m_bShutDown, TRUE);

		// OK! That was it
		SetNewState (SERVICE_STOPPED);

	}
	catch ( YException e ) {
		m_evTerm.Close ();
		OnServiceError (e.GetLastError (), m_dwServiceError);
		OnServiceEnd (m_bShutDown, FALSE);
		if ( !m_sshStatusHandle ) {
			if ( m_theSvc->IsOwnService () ) {
				// hack - returning from service_main seems not to work if
				// the service status has not been set to SERVICE_STOPPED
				ExitInstance (TRUE);
				exit (0);
			}
		}
		SetNewState (SERVICE_STOPPED, e.GetLastError (), m_dwServiceError);
	}
	m_evLog.Deregister ();
}

void YServiceLogic::ServiceControl (DWORD dwCtrlCode)
{
	switch ( dwCtrlCode ) {
	case SERVICE_CONTROL_PAUSE:
		if ( m_dwState == SERVICE_RUNNING ) {
			SetNewState (SERVICE_PAUSE_PENDING);
			if ( OnServicePause () ) {
				SetNewState (SERVICE_PAUSED);
			}
			else {
				SetNewState (SERVICE_RUNNING, ERROR_SERVICE_SPECIFIC_ERROR, m_dwServiceError);
			}
			return;
		}
		break;
	case SERVICE_CONTROL_CONTINUE:
		if ( m_dwState == SERVICE_PAUSED ) {
			SetNewState (SERVICE_CONTINUE_PENDING);
			if ( OnServiceContinue () ) {
				SetNewState (SERVICE_RUNNING);
			}
			else {
				SetNewState (SERVICE_PAUSED, ERROR_SERVICE_SPECIFIC_ERROR, m_dwServiceError);
			}
			return;
		}
	case SERVICE_CONTROL_SHUTDOWN:
		m_bShutDown = TRUE;
		// intended
	case SERVICE_CONTROL_STOP:
		// request to stop the service
		SetNewState (SERVICE_STOP_PENDING, NOERROR, 0, 5000);
		StopService ();
		return;
#if(_WIN32_WINNT >= 0x0500)
	case SERVICE_CONTROL_PARAMCHANGE:
		if ( !OnServiceParamChange () ) {
			ReportStatusToSCM (ERROR_SERVICE_SPECIFIC_ERROR, m_dwServiceError, 0);
			return;
		}
		break;
	case SERVICE_CONTROL_NETBINDCHANGE:
		if ( !OnServiceNetBindChange () ) {
			ReportStatusToSCM (ERROR_SERVICE_SPECIFIC_ERROR, m_dwServiceError, 0);
			return;
		}
		break;
#endif
	case SERVICE_CONTROL_INTERROGATE:
		break;
	default:
		if ( (dwCtrlCode >= 128) && (dwCtrlCode < 256) ) {
			if ( !OnUserControl (dwCtrlCode) ) {
				ReportStatusToSCM (ERROR_SERVICE_SPECIFIC_ERROR, m_dwServiceError, 0);
				return;
			}
		}
		break;
	}
	ReportStatusToSCM (NOERROR, 0, 0);
}

void YServiceLogic::ServiceWait (BOOL bRunAsService)
{
	if ( bRunAsService ) {
		m_evTerm.Wait ();
		return;
	}

	// simulation loop
	TCHAR	szKeys[16];
	ShowSimulationMenu (szKeys);

	while ( m_evTerm.Wait (500) != WAIT_OBJECT_0 ) {
		if ( _kbhit () ) {
			TCHAR key = tolower (_getch ());
			if ( _tcschr (szKeys, key) ) {
				switch ( key ) {
				case _T('s'):
					_tprintf (_T("s\n"));
					ServiceControl (SERVICE_CONTROL_STOP);
					ShowSimulationMenu (szKeys);
					break;
				case _T('w'):
					_tprintf (_T("w\n"));
					ServiceControl (SERVICE_CONTROL_SHUTDOWN);
					ShowSimulationMenu (szKeys);
					break;
				case _T('p'):
					_tprintf (_T("p\n"));
					ServiceControl (SERVICE_CONTROL_PAUSE);
					ShowSimulationMenu (szKeys);
					break;
				case _T('c'):
					_tprintf (_T("c\n"));
					ServiceControl (SERVICE_CONTROL_CONTINUE);
					ShowSimulationMenu (szKeys);
					break;
#if(_WIN32_WINNT >= 0x0500)
				case _T('r'):
					_tprintf (_T("r\n"));
					ServiceControl (SERVICE_CONTROL_PARAMCHANGE);
					ShowSimulationMenu (szKeys);
					break;
#endif
				default:
					MessageBeep (0);
					break;
				}
			}
		}
	}
}

//
// implementation
//
void YServiceLogic::InitServiceEnvironment ()
{
	m_sshStatusHandle		= NULL;
	m_dwState				= SERVICE_STOPPED;
	m_dwCheckPoint			= 0;
	m_dwServiceError		= 0;
	m_bShutDown				= FALSE;
	m_dwControlsAccepted	= 0;
	m_bInteractive			= 0;
}

BOOL YServiceLogic::ReportStatusToSCM (DWORD dwWin32Error, DWORD dwServiceError, DWORD dwWaitHint)
{
	SERVICE_STATUS	ssStatus;

	ssStatus.dwServiceType				= SERVICE_WIN32_OWN_PROCESS;
	ssStatus.dwCurrentState				= m_dwState;
	ssStatus.dwWin32ExitCode			= dwWin32Error;
	ssStatus.dwServiceSpecificExitCode	= dwServiceError;

	switch ( m_dwState ) {
	case SERVICE_STOPPED:
		// terminal state
		ssStatus.dwControlsAccepted = 0;
		ssStatus.dwCheckPoint		= 0;
		ssStatus.dwWaitHint			= 0;
		m_dwCheckPoint				= 0;
		break;
	case SERVICE_RUNNING:
	case SERVICE_PAUSED:
		// terminal state
		ssStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_PAUSE_CONTINUE;
		ssStatus.dwCheckPoint		= 0;
		ssStatus.dwWaitHint			= 0;
		m_dwCheckPoint				= 0;
		break;
	case SERVICE_START_PENDING:
	case SERVICE_STOP_PENDING:
	case SERVICE_PAUSE_PENDING:
	case SERVICE_CONTINUE_PENDING:
		// pending states
		ssStatus.dwControlsAccepted	= 0;
		ssStatus.dwCheckPoint		= ++m_dwCheckPoint;
		ssStatus.dwWaitHint			= dwWaitHint;
		break;
	}

	OnReportStatus (m_dwState, ssStatus.dwControlsAccepted);
	m_dwControlsAccepted = ssStatus.dwControlsAccepted;

	if ( m_sshStatusHandle ) {
		return SetServiceStatus (m_sshStatusHandle, &ssStatus);
	}
	else {
		// simulation
		_tprintf (_T("Service state is now "));
		switch ( m_dwState ) {
		case SERVICE_STOPPED:
			_tprintf (_T("STOPPED\n"));
			break;
		case SERVICE_RUNNING:
			_tprintf (_T("RUNNING\n"));
			break;
		case SERVICE_PAUSED:
			_tprintf (_T("PAUSED\n"));
			break;
		case SERVICE_START_PENDING:
			_tprintf (_T("START PENDING\n"));
			break;
		case SERVICE_STOP_PENDING:
			_tprintf (_T("STOP PENDING\n"));
			break;
		case SERVICE_PAUSE_PENDING:
			_tprintf (_T("PAUSE PENDING\n"));
			break;
		case SERVICE_CONTINUE_PENDING:
			_tprintf (_T("CONTINUE PENDING\n"));
			break;
		default:
			_tprintf (_T("UNDEFINED\n"));
			break;
		}
	}
	return TRUE;
}

void YServiceLogic::ShowSimulationMenu (LPTSTR lpszKeys)
{
	TCHAR	szAdd[] = _T(", ");
	LPCTSTR lpAdd = _T("");
	_tprintf (_T("Fake Control ["));
	if ( m_dwControlsAccepted & SERVICE_ACCEPT_STOP ) {
		_tprintf (_T("(S)top"));
		*lpszKeys++ = _T('s');
		lpAdd = szAdd;
	}
	if ( m_dwControlsAccepted & SERVICE_ACCEPT_SHUTDOWN ) {
		_tprintf (_T("%sShutdo(w)n"), lpAdd);
		*lpszKeys++ = _T('w');
		lpAdd = szAdd;
	}
#if(_WIN32_WINNT >= 0x0500)
	if ( m_dwControlsAccepted & SERVICE_ACCEPT_PARAMCHANGE ) {
		_tprintf (_T("%spa(r)am Change"), lpAdd);
		*lpszKeys++ = _T('r');
		lpAdd = szAdd;
	}
#endif
	if ( (m_dwControlsAccepted & SERVICE_ACCEPT_PAUSE_CONTINUE) && (m_dwState == SERVICE_PAUSED) ) {
		_tprintf (_T("%s(C)ontinue"), lpAdd);
		*lpszKeys++ = _T('c');
		lpAdd = szAdd;
	}
	if ( (m_dwControlsAccepted & SERVICE_ACCEPT_PAUSE_CONTINUE) && (m_dwState == SERVICE_RUNNING) ) {
		_tprintf (_T("%s(P)ause"), lpAdd);
		*lpszKeys++ = _T('p');
		lpAdd = szAdd;
	}
	*lpszKeys = 0;
	_tprintf (_T("]: "));
}

BOOL YServiceLogic::ComputeActionPaths (YComputerName &ysCompName, YPathString &ysBinPath)
{
	ASSERTY(GetSrv ());

	YUNC unc(_T("%s\\%s"), GetSrv ()->GetImagePath (), GetSrv ()->GetImageName ());

	if ( unc.IsUNC () && unc.IsLocal () ) {
		// local operations only possible from physical path
		return FALSE;
	}
	if ( unc.IsRemote () ) {
		if ( !unc.IsAdministrative () ) {
			// if remote UNC, it must be administrative because we
			// will refer to the service on the remote machine and
			// we cannot determine the physical location on that
			// machine.
			ysBinPath = unc;
			return FALSE;
		}
		ysBinPath = unc.BuildLocalName ();
	}
	else {
		ysBinPath.Format (_T("%s\\%s"), GetSrv ()->GetImagePath (), GetSrv ()->GetImageName ());
	}
	ysCompName = unc;
	return TRUE;
}

BOOL YServiceLogic::PerformInstallation (UINT nIndex, YServiceCmdLineParser &cliParser)
{
	YServiceControlManager	scm;
	SVCCREATESTRUCT			scs;
	YComputerName			ysCompName;
	YPathString				ysBinImage;
	YCmdLineOption			*pOption;

	scs.bInteractive	= cliParser.TestOptionFlags (SCL_OPT_INTERACTIVE);
	scs.cbNumCategories	= 0;
	if ( cliParser.TestOptionFlags (SCL_OPT_START_AUTO) ) {
		scs.svcStartType	= svcStartAutomatic;
	}
	else if ( cliParser.TestOptionFlags (SCL_OPT_START_DISABLE) ) {
		scs.svcStartType	= svcStartDisabled;
	}
	else {
		scs.svcStartType	= svcStartManual;
	}
	if ( cliParser.TestOptionFlags (SCL_OPT_USER_NAME) && (pOption = cliParser.FindOptionByMeaning (SCL_OPT_USER_NAME)) ) {
		if ( scs.ysAccount.Alloc (_tcslen (pOption->GetParam ()) + 1) ) {
			scs.ysAccount = pOption->GetParam ();
		}
	}
	if ( cliParser.TestOptionFlags (SCL_OPT_USER_PWD) && (pOption = cliParser.FindOptionByMeaning (SCL_OPT_USER_PWD)) ) {
		if ( scs.ysPassword.Alloc (_tcslen (pOption->GetParam ()) + 1) ) {
			scs.ysPassword = pOption->GetParam ();
		}
	}

	if ( !ComputeActionPaths (ysCompName, ysBinImage) ) {
		// invalid network path combination
		YlbGetSrv ()->SetReturnCode (ERROR_BAD_NETPATH);
		// open the event log
		m_evLog.Register (GetAppName (), ysCompName.GetNullForEmptyString ());
		OnInstallError (ERROR_BAD_NETPATH, ysCompName.GetNullForEmptyString (), ysBinImage);
		return FALSE;
	}
	try {
		// open the event log
		m_evLog.Register (GetAppName (), ysCompName.GetNullForEmptyString ());

		// make sure that we exit with error in case
		YlbGetSrv ()->SetReturnCode (-1);

		if ( !PreInstallService (ysCompName.GetNullForEmptyString (), ysBinImage, &scs) ) {
			// the user do not want...
			return FALSE;
		}
		YlbGetSrv ()->SetReturnCode (0);

		// install as an event source
		if ( !m_evLog.Install (ysCompName.GetNullForEmptyString (), GetAppName (), ysBinImage, scs.cbNumCategories, scs.ysCatMessageFile.GetNullForEmptyString ()) ) {
			throw YException (::GetLastError ());
		}

		// open the service control manager
		if ( !scm.Open (SC_MANAGER_ALL_ACCESS, ysCompName.GetNullForEmptyString ()) ) {
			throw YException (::GetLastError ());
		}

		// quote the path in case it contains blanks
		YPathString ysSrvName = (ysBinImage.Find (_T(" ")) == -1) ? (ysBinImage) : (_T("\"") + ysBinImage + _T("\""));

		YService srv;

		scm.CreateService (
			srv,
			GetAppName (),
			GetAppDescription (),
			SERVICE_ALL_ACCESS,
			((YlbGetSrv ()->IsOwnService ()) ? (SERVICE_WIN32_OWN_PROCESS) : (SERVICE_WIN32_SHARE_PROCESS)) |
			(scs.bInteractive ? (SERVICE_INTERACTIVE_PROCESS) : (0)),
			scs.svcStartType,
			SERVICE_ERROR_NORMAL,
			ysSrvName,
			scs.ysGroup.GetNullForEmptyString (),
			NULL,
			scs.ymsDependencies.GetNullForEmptyString (),
			scs.ysAccount.GetNullForEmptyString (),
			scs.ysPassword.GetNullForEmptyString ()
		);

		if ( !srv.IsOpen () ) {
			throw YException (::GetLastError ());
		}
		OnInstall ();
		YlbGetSrv ()->SetReturnCode (0);
	}
	catch ( YException e ) {
		YlbGetSrv ()->SetReturnCode (e.GetLastError ());
		OnInstallError (e.GetLastError (), ysCompName.GetNullForEmptyString (), ysBinImage);
		AfterRemoveService (ysCompName.GetNullForEmptyString (), ysBinImage, TRUE);
		m_evLog.Uninstall (GetAppName (), ysCompName.GetNullForEmptyString ());
		return FALSE;
	}
	return TRUE;
}

BOOL YServiceLogic::PerformDeinstallation (UINT nIndex, YServiceCmdLineParser &cliParser)
{
	YComputerName			ysCompName;
	YServiceControlManager	scm;
	YPathString				ysBinImage;

	if ( !ComputeActionPaths (ysCompName, ysBinImage) ) {
		// invalid network path combination
		YlbGetSrv ()->SetReturnCode (ERROR_BAD_NETPATH);
		// open the event log
		m_evLog.Register (GetAppName (), ysCompName.GetNullForEmptyString ());
		OnRemoveError (ERROR_BAD_NETPATH, ysCompName.GetNullForEmptyString (), ysBinImage);
		return FALSE;
	}

	// open the event log
	m_evLog.Register (GetAppName (), ysCompName.GetNullForEmptyString ());

	try {
		if ( !scm.Open (SC_MANAGER_ALL_ACCESS, ysCompName.GetNullForEmptyString ()) ) {
			throw YException (::GetLastError ());
		}

		YService srv;

		if ( !scm.OpenService (srv, GetAppName (), SERVICE_ALL_ACCESS) ) {
			throw YException (::GetLastError ());
		}

		if ( !OnRemove (srv.QueryStatus () == SERVICE_STOPPED) ) {
			return FALSE;
		}

		if ( !srv.Delete (FALSE) ) {
			throw YException (::GetLastError ());
		}
		AfterRemoveService (ysCompName.GetNullForEmptyString (), ysBinImage, FALSE);
		m_evLog.Uninstall (GetAppName (), ysCompName.GetNullForEmptyString ());
	}
	catch ( YException e ) {
		YlbGetSrv ()->SetReturnCode (e.GetLastError ());
		OnRemoveError (e.GetLastError (), ysCompName.GetNullForEmptyString (), ysBinImage);
		return FALSE;
	}
	return TRUE;
}

BOOL YServiceLogic::PerformStart (UINT nIndex, YServiceCmdLineParser &cliParser)
{
	YComputerName			ysCompName;
	YServiceControlManager	scm;
	YPathString				ysBinImage;

	YCmdLineParam *pParam = cliParser.FindParamByMeaning (SCL_CMD_START);
	ASSERTY(pParam);

	DWORD	dwArgC = _proc.m_cli.GetParamCount () - pParam->GetCliIndex ();
	LPCTSTR	*lpArgV = (dwArgC) ? ((LPCTSTR *) _proc.m_cli.m_argv + pParam->GetCliIndex () - 1) : (NULL);
	if ( lpArgV ) {
		lpArgV[0] = GetAppName ();
	}

	if ( !ComputeActionPaths (ysCompName, ysBinImage) ) {
		// invalid network path combination
		YlbGetSrv ()->SetReturnCode (ERROR_BAD_NETPATH);
		OnStartError (ERROR_BAD_NETPATH, ysCompName.GetNullForEmptyString (), ysBinImage);
		return FALSE;
	}

	try {
		if ( !scm.Open (SC_MANAGER_ALL_ACCESS, ysCompName.GetNullForEmptyString ()) ) {
			throw YException (::GetLastError ());
		}

		YService srv;

		if ( !scm.OpenService (srv, GetAppName (), SERVICE_ALL_ACCESS) ) {
			throw YException (::GetLastError ());
		}

		switch ( srv.QueryStatus () ) {
		case SERVICE_STOPPED:
			// OK!
			break;
		case SERVICE_UNKNOWN:
			throw YException (::GetLastError ());
		default:
			throw YException (ERROR_SERVICE_ALREADY_RUNNING);
		}

		OnStartUI (SERVICE_STOPPED);

		if ( !srv.Start (dwArgC, lpArgV) ) {
			throw YException (::GetLastError ());
		}

		BOOL			bPending = FALSE;
		DWORD			dwSeconds	= 0;
		SERVICE_STATUS	ssStatus;

		do {
			if ( !srv.QueryStatus (&ssStatus) ) {
				throw YException (::GetLastError ());
			}
			switch ( ssStatus.dwCurrentState ) {
			case SERVICE_START_PENDING:
				bPending = TRUE;
				// intended
			default:
				if ( !OnStartUI (ssStatus.dwCurrentState, NOERROR, ++dwSeconds) ) {
					throw YException (ERROR_SERVICE_REQUEST_TIMEOUT);
				}
				break;
			case SERVICE_RUNNING:
				OnStartUI (SERVICE_RUNNING);
				return TRUE;
			case SERVICE_STOPPED:
				if ( bPending ) {
					OnStartUI (SERVICE_STOPPED, ssStatus.dwWin32ExitCode, ++dwSeconds);
					return FALSE;
				}
				else {
					OnStartUI (SERVICE_STOPPED, NOERROR, ++dwSeconds);
				}
				break;
			}
			Sleep (1000);
		} while (TRUE);
	}
	catch ( YException e ) {
		YlbGetSrv ()->SetReturnCode (e.GetLastError ());
		OnStartError (e.GetLastError (), ysCompName.GetNullForEmptyString (), ysBinImage);
		return FALSE;
	}
	return TRUE;
}

BOOL YServiceLogic::PerformStop (UINT nIndex, YServiceCmdLineParser &cliParser)
{
	YComputerName			ysCompName;
	YServiceControlManager	scm;
	YPathString				ysBinImage;

	if ( !ComputeActionPaths (ysCompName, ysBinImage) ) {
		// invalid network path combination
		YlbGetSrv ()->SetReturnCode (ERROR_BAD_NETPATH);
		OnStopError (ERROR_BAD_NETPATH, ysCompName.GetNullForEmptyString (), ysBinImage);
		return FALSE;
	}

	try {
		if ( !scm.Open (SC_MANAGER_ALL_ACCESS, ysCompName.GetNullForEmptyString ()) ) {
			throw YException (::GetLastError ());
		}

		YService srv;

		if ( !scm.OpenService (srv, GetAppName (), SERVICE_ALL_ACCESS) ) {
			throw YException (::GetLastError ());
		}

		switch ( srv.QueryStatus () ) {
		case SERVICE_RUNNING:
		case SERVICE_PAUSED:
			// OK!
			break;
		case SERVICE_UNKNOWN:
			throw YException (::GetLastError ());
		case SERVICE_STOPPED:
			throw YException (ERROR_SERVICE_NOT_ACTIVE);
		default:
			// let's take a try...
			break;
		}

		OnStopUI (SERVICE_RUNNING);

		DWORD			dwSeconds	= 0;
		SERVICE_STATUS	ssStatus;

		if ( !srv.Stop () ) {
			throw YException (::GetLastError ());
		}

		do {
			if ( !srv.QueryStatus (&ssStatus) ) {
				throw YException (::GetLastError ());
			}
			if ( ssStatus.dwCurrentState == SERVICE_STOPPED ) {
				OnStopUI (SERVICE_STOPPED, ssStatus.dwWin32ExitCode, ++dwSeconds);
				return TRUE;
			}
			else {
				if ( !OnStopUI (ssStatus.dwCurrentState, NOERROR, ++dwSeconds) ) {
					throw YException (ERROR_SERVICE_REQUEST_TIMEOUT);
				}
			}
			Sleep (1000);
		} while (TRUE);
	}
	catch ( YException e ) {
		YlbGetSrv ()->SetReturnCode (e.GetLastError ());
		OnStopError (e.GetLastError (), ysCompName.GetNullForEmptyString (), ysBinImage);
		return FALSE;
	}
	return TRUE;
}

BOOL YServiceLogic::PerformPause (UINT nIndex, YServiceCmdLineParser &cliParser)
{
	YComputerName			ysCompName;
	YServiceControlManager	scm;
	YPathString				ysBinImage;

	if ( !ComputeActionPaths (ysCompName, ysBinImage) ) {
		// invalid network path combination
		YlbGetSrv ()->SetReturnCode (ERROR_BAD_NETPATH);
		OnPauseError (ERROR_BAD_NETPATH, ysCompName.GetNullForEmptyString (), ysBinImage);
		return FALSE;
	}

	try {
		if ( !scm.Open (SC_MANAGER_ALL_ACCESS, ysCompName.GetNullForEmptyString ()) ) {
			throw YException (::GetLastError ());
		}

		YService srv;

		if ( !scm.OpenService (srv, GetAppName (), SERVICE_ALL_ACCESS) ) {
			throw YException (::GetLastError ());
		}

		switch ( srv.QueryStatus () ) {
		case SERVICE_RUNNING:
			// OK!
			break;
		case SERVICE_UNKNOWN:
			throw YException (::GetLastError ());
		default:
			throw YException (ERROR_SERVICE_NOT_ACTIVE);
		}

		OnPauseUI (SERVICE_RUNNING);

		DWORD			dwSeconds	= 0;
		SERVICE_STATUS	ssStatus;

		if ( !srv.Pause () ) {
			throw YException (::GetLastError ());
		}

		do {
			if ( !srv.QueryStatus (&ssStatus) ) {
				throw YException (::GetLastError ());
			}
			switch ( ssStatus.dwCurrentState ) {
			case SERVICE_PAUSED:
				OnPauseUI (SERVICE_PAUSED);
				return TRUE;
			case SERVICE_STOPPED:
				OnPauseUI (SERVICE_STOPPED, ssStatus.dwWin32ExitCode, ++dwSeconds);
				return FALSE;
			default:
				if ( !OnPauseUI (ssStatus.dwCurrentState, NOERROR, ++dwSeconds) ) {
					throw YException (ERROR_SERVICE_REQUEST_TIMEOUT);
				}
			}
			Sleep (1000);
		} while (TRUE);
	}
	catch ( YException e ) {
		YlbGetSrv ()->SetReturnCode (e.GetLastError ());
		OnPauseError (e.GetLastError (), ysCompName.GetNullForEmptyString (), ysBinImage);
		return FALSE;
	}
	return TRUE;
}

BOOL YServiceLogic::PerformResume (UINT nIndex, YServiceCmdLineParser &cliParser)
{
	YComputerName			ysCompName;
	YServiceControlManager	scm;
	YPathString				ysBinImage;

	if ( !ComputeActionPaths (ysCompName, ysBinImage) ) {
		// invalid network path combination
		YlbGetSrv ()->SetReturnCode (ERROR_BAD_NETPATH);
		OnContinueError (ERROR_BAD_NETPATH, ysCompName.GetNullForEmptyString (), ysBinImage);
		return FALSE;
	}

	try {
		if ( !scm.Open (SC_MANAGER_ALL_ACCESS, ysCompName.GetNullForEmptyString ()) ) {
			throw YException (::GetLastError ());
		}

		YService srv;

		if ( !scm.OpenService (srv, GetAppName (), SERVICE_ALL_ACCESS) ) {
			throw YException (::GetLastError ());
		}

		switch ( srv.QueryStatus () ) {
		case SERVICE_PAUSED:
			// OK!
			break;
		case SERVICE_UNKNOWN:
			throw YException (::GetLastError ());
		default:
			throw YException (ERROR_SERVICE_NOT_ACTIVE);
		}

		OnContinueUI (SERVICE_PAUSED);

		DWORD			dwSeconds	= 0;
		SERVICE_STATUS	ssStatus;

		if ( !srv.Continue () ) {
			throw YException (::GetLastError ());
		}

		do {
			if ( !srv.QueryStatus (&ssStatus) ) {
				throw YException (::GetLastError ());
			}
			switch ( ssStatus.dwCurrentState ) {
			case SERVICE_RUNNING:
				OnContinueUI (SERVICE_RUNNING);
				return TRUE;
			case SERVICE_STOPPED:
				OnContinueUI (SERVICE_STOPPED, ssStatus.dwWin32ExitCode, ++dwSeconds);
				return FALSE;
			default:
				if ( !OnPauseUI (ssStatus.dwCurrentState, NOERROR, ++dwSeconds) ) {
					throw YException (ERROR_SERVICE_REQUEST_TIMEOUT);
				}
			}
			Sleep (1000);
		} while (TRUE);
	}
	catch ( YException e ) {
		YlbGetSrv ()->SetReturnCode (e.GetLastError ());
		OnContinueError (e.GetLastError (), ysCompName.GetNullForEmptyString (), ysBinImage);
		return FALSE;
	}
	return TRUE;
}

BOOL YServiceLogic::PerformSimulation (UINT nIndex, YServiceCmdLineParser &cliParser)
{
	YCmdLineParam *pParam = cliParser.FindParamByMeaning (SCL_CMD_SIMULATE);
	ASSERTY(pParam);

	YCommandLineInfo cli (_proc.m_cli.GetParamCount () - pParam->GetCliIndex (), _proc.m_cli.m_argv + pParam->GetCliIndex () - 1);
	cli.m_argv[0] = (LPTSTR) GetAppName ();

	ServiceMain (nIndex, &cli, FALSE);

	return TRUE;
}


/*============================================================================*
 * THE SYSTEM SERVICE CLASS
 *============================================================================*/
YSrvApp::YSrvApp (LPCTSTR pszAppName, LPCTSTR pszAppDesc, WORD wMajor, WORD wMinor, WORD wStepping, WORD wBuild)
	: YConApp (pszAppName, pszAppDesc, wMajor, wMinor, wStepping, wBuild)
{
	CommonConstructor ();
}

YSrvApp::YSrvApp (UINT nAppNameID) : YConApp (nAppNameID)
{
	CommonConstructor ();
}

YSrvApp::YSrvApp (YServiceLogic &sl, LPCTSTR pszAppName, LPCTSTR pszAppDesc, WORD wMajor, WORD wMinor, WORD wStepping, WORD wBuild)
	: YConApp (pszAppName, pszAppDesc, wMajor, wMinor, wStepping, wBuild)
{
	CommonConstructor ();
	AddService (&sl);
}

YSrvApp::YSrvApp (YServiceLogic &sl, UINT nAppNameID) : YConApp (nAppNameID)
{
	CommonConstructor ();
	AddService (&sl);
}

//
// operations
//

BOOL YSrvApp::AddService (YServiceLogic *psl)
{
	if ( m_nServices < YLB_MAX_SERVICES ) {
		m_slServices[m_nServices]					= psl;
		psl->m_theSvc = this;
		++m_nServices;
		return TRUE;
	}
	return FALSE;
}

UINT YSrvApp::FindService (LPCTSTR pszName) const
{
	if ( pszName && *pszName ) {
		for ( UINT nCnt = 0; nCnt < YLB_MAX_SERVICES; nCnt++ ) {
			if ( m_slServices[nCnt] && !_tcsicmp (pszName, m_slServices[nCnt]->GetAppName ()) ) {
				return nCnt + 1;
			}
		}
	}
	return 0;
}

BOOL YSrvApp::ProcessShellCommand (YServiceCmdLineParser &cliParser)
{
	if ( !cliParser.GetParserResult () ) {
		// we had an error and we had already shown it
		return TRUE;
	}
	if ( cliParser.TestCommandFlags (SCL_CMD_WANTSHELP) ) {
		cliParser.ShowIntro ();
		cliParser.ShowUsage (cliParser.GetCommands () & SCL_CMD_MASK);
		cliParser.ShowExtro ();
		return TRUE;
	}

	DWORDLONG dwCmd = cliParser.GetCommands () & SCL_CMD_MASK_KNOWN;
	if ( !dwCmd ) {
		// no known commands. nothing to do.
		return FALSE;
	}

	UINT			nIndex = GetRequestedService (cliParser, dwCmd);
	YServiceLogic *	pSL = GetService (nIndex);
	if ( !pSL ) {
		// bad. we are done.
		return TRUE;
	}

	// got it!
	cliParser.ShowIntro ();

	if ( !pSL->InitInstance (GetCommandLineInfo ()) ) {
		// he does not want. he is responsible for showing an appropriate error...
		pSL->ExitInstance (FALSE);
		cliParser.ShowExtro ();
		return TRUE;
	}

	switch ( dwCmd ) {
	case SCL_CMD_INSTALL:
		pSL->PerformInstallation (nIndex, cliParser);
		cliParser.ShowExtro ();
		return TRUE;
	case SCL_CMD_REMOVE:
		pSL->PerformDeinstallation (nIndex, cliParser);
		cliParser.ShowExtro ();
		return TRUE;
	case SCL_CMD_START:
		pSL->PerformStart (nIndex, cliParser);
		cliParser.ShowExtro ();
		return TRUE;
	case SCL_CMD_STOP:
		pSL->PerformStop (nIndex, cliParser);
		cliParser.ShowExtro ();
		return TRUE;
	case SCL_CMD_PAUSE:
		pSL->PerformPause (nIndex, cliParser);
		cliParser.ShowExtro ();
		return TRUE;
	case SCL_CMD_RESUME:
		pSL->PerformResume (nIndex, cliParser);
		cliParser.ShowExtro ();
		return TRUE;
	case SCL_CMD_SIMULATE:
		pSL->PerformSimulation (nIndex, cliParser);
		cliParser.ShowExtro ();
		return TRUE;
	}

	// mhhh unknown command. the derived implementation has to implement it
	// or throw an error message. intro has already been shown...
	return FALSE;
}

//
// very advanced overridables (the whole service logic)
//

void YSrvApp::Run ()
{
	SERVICE_TABLE_ENTRY	dispatchTable[YLB_MAX_SERVICES + 1];

	for ( UINT nCnt = 0; nCnt < m_nServices; nCnt++ ) {
		dispatchTable[nCnt].lpServiceName = (LPTSTR) m_slServices[nCnt]->GetAppName ();
		dispatchTable[nCnt].lpServiceProc = _ylb_service_main;
	}
	dispatchTable[nCnt].lpServiceName = NULL;
	dispatchTable[nCnt].lpServiceProc = NULL;

	StartServiceCtrlDispatcher (dispatchTable);
}

//
// implementation
//

void YSrvApp::CommonConstructor ()
{
	_proc.m_flg.ClearFlags (FLG_APP_YCONAPP);
	_proc.m_flg.SetFlags (FLG_APP_YSERVICE);
	m_nServices	= 0;
	memset (m_slServices, 0, sizeof (m_slServices));
}

SERVICE_STATUS_HANDLE  YSrvApp::RegisterControlHandler (UINT nIndex)
{
	if ( GetService (nIndex) ) {
		return ::RegisterServiceCtrlHandler (
			GetService (nIndex)->GetAppName (),
			_ytab_service_ctrl[nIndex - 1]
		);
	}
	return NULL;
}

UINT YSrvApp::GetRequestedService (YServiceCmdLineParser &cliParser, DWORDLONG dwCmd)
{
	ASSERTY(GetServiceCount ());
	if ( !GetServiceCount () ) {
		return 0;
	}
	if ( IsOwnService () ) {
		return 1;
	}

	// find out command
	YCmdLineParam *pParm = cliParser.FindParamByMeaning (dwCmd);
	if ( !pParm ) {
		cliParser.ShowIntro ();
		_tprintf (_T("ERROR: internal error.\n\n"));
		cliParser.ShowExtro ();
		return 0;
	}

	if ( !pParm->GetParamCount () ) {
		cliParser.ShowIntro ();
		_tprintf (_T("ERROR: no service name specified\n\n"));
		cliParser.ShowUsage (cliParser.GetCommands () & SCL_CMD_MASK);
		cliParser.ShowExtro ();
		return 0;
	}
	UINT nIndex = FindService (pParm->GetAt (ZERO));
	if ( !nIndex ) {
		cliParser.ShowIntro ();
		_tprintf (_T("ERROR: unknown service name specified\n\n"));
		cliParser.ShowUsage (cliParser.GetCommands () & SCL_CMD_MASK);
		cliParser.ShowExtro ();
	}
	return nIndex;
}


#ifndef YLB_ENABLE_INLINE
#include <ySrvApp.inl>
#endif

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////