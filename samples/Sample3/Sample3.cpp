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
 * FILENAME		:	Sample3.cpp
 * PURPOSE		:	yLib multiple service sample
 * SCOPE		:	yLib SDK
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

#include "StdAfc.h"
#include "Sample3.h"

/*=============================================================================
 * INSTANTIATE
 *============================================================================*/
CMultiService theSvc;

void CMultiParser::ShowIntro ()
{
	// show credits
	_tprintf (_T("\nThis is %s v%i.%i, the %s\n"), theSvc.GetAppName (), theSvc.GetMajorVersion (), theSvc.GetMinorVersion (), theSvc.GetAppDescription ());
	_tprintf (_T("(c) 2000 YEAsoft Int'l. All rights reserved.\n\n"));
}

void CMultiParser::ShowExtro ()
{
	_tprintf (_T("\n"));
}

/*=============================================================================
 * OUR SAMPLE SERVICE APPLICATION
 *============================================================================*/
CMultiService::CMultiService () : YSrvApp (IDS_APP_TITLE), m_slEarner1(IDS_SVC_EARNER1, 0), m_slEarner2(IDS_SVC_EARNER2, 1)
{
	AddService (&m_slEarner1);
	AddService (&m_slEarner2);
	AddService (&m_slReporter);
}

BOOL CMultiService::InitInstance (YCommandLineInfo *cli)
{
	// performs autoparsing
	CMultiParser	cliParser;
	return !ProcessShellCommand (cliParser);
}

void CMultiService::Allocate ()
{
	m_con.Allocate ();
	m_con.SetConsoleTitle (GetAppDescription ());
}

/*=============================================================================
 * OUR SAMPLE SERVICE
 *============================================================================*/
BOOL CEarnerService::InitInstance (YCommandLineInfo *cli)
{
	// prepare the event log
	// we specify the service short name as default
	// parameter %1 for all messages
	m_lpInserts[0] = GetAppName ();
	m_evLog.SetDefaultCategory (CAT_SERVICE);
	m_evLog.SetInserts (1, m_lpInserts);
	return TRUE;
}

BOOL CEarnerService::PreInstallService (LPCTSTR pszCompName, LPCTSTR pszImagePath, LPSVCCREATESTRUCT lpSCS)
{
	if ( !YServiceLogic::PreInstallService (pszCompName, pszImagePath, lpSCS) ) {
		return FALSE;
	}

	// we have also categories in our event logging system
	lpSCS->cbNumCategories	= 2;
	lpSCS->ysCatMessageFile	= pszImagePath;
	// always run interactive
	lpSCS->bInteractive		= TRUE;
	return TRUE;
}

void CEarnerService::OnInstallError (DWORD dwError, LPCTSTR pszCompName, LPCTSTR pszImagePath)
{
	YServiceLogic::OnInstallError (dwError, pszCompName, pszImagePath);
	YString16 ysErrNum; ysErrNum.Assign (dwError);
	m_evLog.ErrorEx (CAT_MANAGEMENT, MSG_INSTALL_ERROR, ysErrNum, NULL);
}

void CEarnerService::OnInstall ()
{
	YServiceLogic::OnInstall ();
	m_evLog.InfoEx (CAT_MANAGEMENT, MSG_INSTALLED, NULL);
}

void CEarnerService::AfterRemoveService (LPCTSTR pszCompName, LPCTSTR pszImagePath, BOOL bBadInstalled)
{
	YServiceLogic::AfterRemoveService (pszCompName, pszImagePath, bBadInstalled);
	if ( !bBadInstalled ) {
		m_evLog.InfoEx (CAT_MANAGEMENT, MSG_REMOVED, NULL);
	}
}

BOOL CEarnerService::OnServiceStart (YCommandLineInfo *cli)
{
	ReportOperationDelay (2000);

	// give him his identity
	m_eaThread.SetName (GetAppName ());
	m_eaThread.SetAccount (m_nAccount);

	// Create the Earner Object
	if ( !m_eaThread.Create (TRUE) ) {
		m_evLog.Error (MSG_INITERROR, NULL);
		return FALSE;
	}

	// allocate the console....
	theSvc.Allocate ();

	// activate the earner
	m_eaThread.Resume ();

	// message in the event log
	m_evLog.Info (MSG_STARTED, NULL);

	return TRUE;
}

BOOL CEarnerService::OnServicePause ()
{
	m_eaThread.Pause ();
	// message in the event log
	m_evLog.Info (MSG_PAUSED, NULL);
	return TRUE;
}

BOOL CEarnerService::OnServiceContinue ()
{
	m_eaThread.Continue ();
	// message in the event log
	m_evLog.Info (MSG_CONTINUED, NULL);
	return TRUE;
}

void CEarnerService::OnServiceError (DWORD dwWin32Error, DWORD dwServiceError)
{
	YString16	ysWin32, ysService;
	ysWin32.Assign (dwWin32Error);
	ysService.Assign (dwServiceError);
	// message in the event log
	m_evLog.Error (MSG_SERVICE_ERROR, (LPCTSTR) ysWin32, (LPCTSTR) ysService, NULL);
}

void CEarnerService::OnServiceEnd (BOOL bSystemShudown, BOOL bRegularExit)
{
	if ( !bSystemShudown ) {
		// simulate lengthy shutdown

		// tell the SCM that we will take long
		ReportOperationDelay (6000);

		// take long... ;-)
		Sleep (3000);
	}
	m_eaThread.Terminate (2000, 0);
	// message in the event log
	m_evLog.Info (MSG_STOPPED, NULL);
}

/*=============================================================================
 * OUR SAMPLE SERVICE 2
 *============================================================================*/
BOOL CReporterService::InitInstance (YCommandLineInfo *cli)
{
	// prepare the event log
	// we specify the service short name as default
	// parameter %1 for all messages
	m_lpInserts[0] = GetAppName ();
	m_evLog.SetDefaultCategory (CAT_SERVICE);
	m_evLog.SetInserts (1, m_lpInserts);
	return TRUE;
}

BOOL CReporterService::PreInstallService (LPCTSTR pszCompName, LPCTSTR pszImagePath, LPSVCCREATESTRUCT lpSCS)
{
	if ( !YServiceLogic::PreInstallService (pszCompName, pszImagePath, lpSCS) ) {
		return FALSE;
	}

	// we have also categories in our event logging system
	lpSCS->cbNumCategories	= 2;
	lpSCS->ysCatMessageFile	= pszImagePath;
	// always run interactive
	lpSCS->bInteractive		= TRUE;
	return TRUE;
}

void CReporterService::OnInstallError (DWORD dwError, LPCTSTR pszCompName, LPCTSTR pszImagePath)
{
	YServiceLogic::OnInstallError (dwError, pszCompName, pszImagePath);
	YString16 ysErrNum; ysErrNum.Assign (dwError);
	m_evLog.ErrorEx (CAT_MANAGEMENT, MSG_INSTALL_ERROR, ysErrNum, NULL);
}

void CReporterService::OnInstall ()
{
	YServiceLogic::OnInstall ();
	m_evLog.InfoEx (CAT_MANAGEMENT, MSG_INSTALLED, NULL);
}

void CReporterService::AfterRemoveService (LPCTSTR pszCompName, LPCTSTR pszImagePath, BOOL bBadInstalled)
{
	YServiceLogic::AfterRemoveService (pszCompName, pszImagePath, bBadInstalled);
	if ( !bBadInstalled ) {
		m_evLog.InfoEx (CAT_MANAGEMENT, MSG_REMOVED, NULL);
	}
}

BOOL CReporterService::OnServiceStart (YCommandLineInfo *cli)
{
	ReportOperationDelay (2000);

	// Create the Earner Object
	if ( !m_rpThread.Create (TRUE) ) {
		m_evLog.Error (MSG_INITERROR, NULL);
		return FALSE;
	}

	// allocate the console....
	theSvc.Allocate ();

	// activate the earner
	m_rpThread.Resume ();

	// message in the event log
	m_evLog.Info (MSG_STARTED, NULL);

	return TRUE;
}

BOOL CReporterService::OnServicePause ()
{
	m_rpThread.Pause ();
	// message in the event log
	m_evLog.Info (MSG_PAUSED, NULL);
	return TRUE;
}

BOOL CReporterService::OnServiceContinue ()
{
	m_rpThread.Continue ();
	// message in the event log
	m_evLog.Info (MSG_CONTINUED, NULL);
	return TRUE;
}

void CReporterService::OnServiceError (DWORD dwWin32Error, DWORD dwServiceError)
{
	YString16	ysWin32, ysService;
	ysWin32.Assign (dwWin32Error);
	ysService.Assign (dwServiceError);
	// message in the event log
	m_evLog.Error (MSG_SERVICE_ERROR, (LPCTSTR) ysWin32, (LPCTSTR) ysService, NULL);
}

void CReporterService::OnServiceEnd (BOOL bSystemShudown, BOOL bRegularExit)
{
	if ( !bSystemShudown ) {
		// simulate lengthy shutdown

		// tell the SCM that we will take long
		ReportOperationDelay (5000);

		// take long... ;-)
		Sleep (3000);
	}
	m_rpThread.Terminate (2000, 0);
	// message in the event log
	m_evLog.Info (MSG_STOPPED, NULL);
}

