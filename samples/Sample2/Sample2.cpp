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
 * FILENAME		:	Sample2.cpp
 * PURPOSE		:	yLib service sample
 * SCOPE		:	yLib SDK
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:07:40  leo
 * Initial revision
 *
 *============================================================================*/

#include "StdAfc.h"
#include "Sample2.h"

/*=============================================================================
 * INSTANTIATE
 *============================================================================*/
CBeeperApp theSvc;

void CBeeperParser::ShowIntro ()
{
	// show credits
	_tprintf (_T("\nThis is %s v%i.%i, the %s\n"), theSvc.GetAppName (), theSvc.GetMajorVersion (), theSvc.GetMinorVersion (), theSvc.GetAppDescription ());
	_tprintf (_T("(c) 2000 YEAsoft Int'l. All rights reserved.\n\n"));
}

void CBeeperParser::ShowExtro ()
{
	_tprintf (_T("\n"));
}

/*=============================================================================
 * OUR SAMPLE SERVICE APPLICATION
 *============================================================================*/
CBeeperApp::CBeeperApp () : YSrvApp (IDS_APP_TITLE)
{
	AddService (&m_slBeeper);
}

BOOL CBeeperApp::InitInstance (YCommandLineInfo *cli)
{
	// performs autoparsing
	CBeeperParser	cliParser;

	if ( !ProcessShellCommand (cliParser) ) {
		// no interactive command specified.
		if ( ::YlbIsAttachedToConsole () ) {
			// not started by SCM
			cliParser.ShowIntro ();
			cliParser.ShowUsage (cliParser.GetCommands () & SCL_CMD_MASK);
			cliParser.ShowExtro ();
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

/*=============================================================================
 * OUR SAMPLE SERVICE
 *============================================================================*/
BOOL CBeeperService::InitInstance (YCommandLineInfo *cli)
{
	// prepare the event log
	// we specify the service short name as default
	// parameter %1 for all messages
	m_lpInserts[0] = GetAppName ();
	m_evLog.SetDefaultCategory (CAT_SERVICE);
	m_evLog.SetInserts (1, m_lpInserts);
	return TRUE;
}

BOOL CBeeperService::PreInstallService (LPCTSTR pszCompName, LPCTSTR pszImagePath, LPSVCCREATESTRUCT lpSCS)
{
	if ( !YServiceLogic::PreInstallService (pszCompName, pszImagePath, lpSCS) ) {
		return FALSE;
	}

	// we have also categories in our event logging system
	lpSCS->cbNumCategories	= 2;
	lpSCS->ysCatMessageFile	= pszImagePath;
	return TRUE;
}

void CBeeperService::OnInstallError (DWORD dwError, LPCTSTR pszCompName, LPCTSTR pszImagePath)
{
	YServiceLogic::OnInstallError (dwError, pszCompName, pszImagePath);
	YString16 ysErrNum; ysErrNum.Assign (dwError);
	m_evLog.ErrorEx (CAT_MANAGEMENT, MSG_INSTALL_ERROR, ysErrNum, NULL);
}

void CBeeperService::OnInstall ()
{
	YServiceLogic::OnInstall ();
	m_evLog.InfoEx (CAT_MANAGEMENT, MSG_INSTALLED, NULL);
}

void CBeeperService::AfterRemoveService (LPCTSTR pszCompName, LPCTSTR pszImagePath, BOOL bBadInstalled)
{
	YServiceLogic::AfterRemoveService (pszCompName, pszImagePath, bBadInstalled);
	if ( !bBadInstalled ) {
		m_evLog.InfoEx (CAT_MANAGEMENT, MSG_REMOVED, NULL);
	}
}

BOOL CBeeperService::OnServiceStart (YCommandLineInfo *cli)
{
	// Create the Beeper Object
	if ( !m_bpThread.Create (TRUE) ) {
		m_evLog.Error (MSG_INITERROR, NULL);
		return FALSE;
	}

	// simulate lengthy initialisation

	// in case allocate the console....
	if ( IsInteractive () ) {
		m_con.Allocate ();
		m_con.SetConsoleTitle (GetAppDescription ());
	}

	// tell the SCM that we will take long
	ReportOperationDelay (50000);

	// take long... ;-)
	Sleep (3000);

	// activate the beeper
	m_bpThread.Resume ();

	// message in the event log
	m_evLog.Info (MSG_STARTED, NULL);

	return TRUE;
}

BOOL CBeeperService::OnServicePause ()
{
	m_bpThread.Pause ();
	// message in the event log
	m_evLog.Info (MSG_PAUSED, NULL);
	return TRUE;
}

BOOL CBeeperService::OnServiceContinue ()
{
	m_bpThread.Continue ();
	// message in the event log
	m_evLog.Info (MSG_CONTINUED, NULL);
	return TRUE;
}

void CBeeperService::OnServiceError (DWORD dwWin32Error, DWORD dwServiceError)
{
	YString16	ysWin32, ysService;
	ysWin32.Assign (dwWin32Error);
	ysService.Assign (dwServiceError);
	// message in the event log
	m_evLog.Error (MSG_SERVICE_ERROR, (LPCTSTR) ysWin32, (LPCTSTR) ysService, NULL);
}

void CBeeperService::OnServiceEnd (BOOL bSystemShudown, BOOL bRegularExit)
{
	if ( !bSystemShudown ) {
		// simulate lengthy shutdown

		// tell the SCM that we will take long
		ReportOperationDelay (6000);

		// take long... ;-)
		Sleep (3000);
	}
	m_bpThread.Terminate (2000, 0);
	// message in the event log
	m_evLog.Info (MSG_STOPPED, NULL);
}

