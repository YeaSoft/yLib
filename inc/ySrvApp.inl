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
 * FILENAME		:	ySrvApp.inl
 * PURPOSE		:	Inline members of the system service classes
 * SCOPE		:	yAfc
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/
/*=============================================================================
 * @doc YLIB | ySrvApp.h
 *============================================================================*/


/*============================================================================*
 * THE SERVICE COMMANDLINE PARSER
 *============================================================================*/
YLB_INLINE void YServiceCmdLineParser::ShowIntro ()
{
}

YLB_INLINE void YServiceCmdLineParser::ShowExtro ()
{
}


/*============================================================================*
 * THE SERVICE LOGIC CLASS
 *============================================================================*/
YLB_INLINE YServiceLogic::YServiceLogic (LPCTSTR pszSvcName, LPCTSTR pszSvcDesc) : YBaseApp (pszSvcName, pszSvcDesc)
{
	InitServiceEnvironment ();
}

YLB_INLINE YServiceLogic::YServiceLogic (UINT nSvcNameID) : YBaseApp (nSvcNameID)
{
	InitServiceEnvironment ();
}

//
// attributes
//

YLB_INLINE YSrvApp * YServiceLogic::GetSrv () const
{
	return m_theSvc;
}

YLB_INLINE YEventLogSource * YServiceLogic::GetEventLog ()
{
	return &m_evLog;
}

YLB_INLINE BOOL YServiceLogic::IsInteractive () const
{
	ASSERTY(m_theSvc);
	return m_bInteractive;
}

YLB_INLINE BOOL YServiceLogic::IsShareService () const
{
	ASSERTY(m_theSvc);
	return m_theSvc->IsShareService ();
}

YLB_INLINE BOOL YServiceLogic::IsOwnService () const
{
	ASSERTY(m_theSvc);
	return m_theSvc->IsOwnService ();
}

//
// operations
//

YLB_INLINE void YServiceLogic::StopService ()
{
	m_evTerm.SetEvent ();
}

YLB_INLINE void YServiceLogic::ReportOperationDelay (DWORD dwDelay)
{
	ReportStatusToSCM (NOERROR, 0, dwDelay);
}

//
// management overridables
//

YLB_INLINE BOOL YServiceLogic::PreInstallService (LPCTSTR pszCompName, LPCTSTR pszImagePath, LPSVCCREATESTRUCT lpSCS)
{
	_tprintf (_T("Installing %s...\n"), GetAppDescription ());
	return TRUE;
}

YLB_INLINE void YServiceLogic::OnInstall ()
{
	_tprintf (_T("OK: The %s service was successfully registered\n"), GetAppDescription ());
}

//
// runtime overridables
//

YLB_INLINE BOOL YServiceLogic::OnServiceStart (YCommandLineInfo *cli)
{
	return TRUE;
}

YLB_INLINE BOOL YServiceLogic::OnServicePause ()
{
	return TRUE;
}

YLB_INLINE BOOL YServiceLogic::OnServiceContinue ()
{
	return TRUE;
}

YLB_INLINE BOOL YServiceLogic::OnUserControl (DWORD dwCtrlCode)
{
	return TRUE;
}

#if(_WIN32_WINNT >= 0x0500)
YLB_INLINE void YServiceLogic::OnServiceParamChange ()
{
}

YLB_INLINE void YServiceLogic::OnServiceNetBindChange ()
{
}

#endif

YLB_INLINE void YServiceLogic::OnServiceError (DWORD dwWin32Error, DWORD dwServiceError)
{
}

YLB_INLINE void YServiceLogic::OnServiceEnd (BOOL bSystemShudown, BOOL bRegularExit)
{
}

//
// advanced overridables
//

YLB_INLINE void YServiceLogic::OnReportStatus (DWORD dwState, DWORD &dwControlsAccepted)
{
}

//
// implementation
//

YLB_INLINE BOOL YServiceLogic::SetNewState (DWORD dwState, DWORD dwWin32Error, DWORD dwServiceError, DWORD dwWaitHint)
{
	m_dwState = dwState;
	return ReportStatusToSCM (dwWin32Error, dwServiceError, dwWaitHint);
}


/*============================================================================*
 * THE SYSTEM SERVICE CLASS
 *============================================================================*/
YLB_INLINE YSrvApp::~YSrvApp ()
{
}

//
// attributes
//

YLB_INLINE YServiceLogic * YSrvApp::GetService (UINT nIndex) const
{
	return (nIndex && (nIndex <= YLB_MAX_SERVICES)) ? (m_slServices[nIndex - 1]) : (NULL);
}

YLB_INLINE UINT YSrvApp::GetServiceCount () const
{
	return m_nServices;
}

YLB_INLINE BOOL YSrvApp::IsShareService () const
{
	return m_nServices > 1;
}

YLB_INLINE BOOL YSrvApp::IsOwnService () const
{
	return m_nServices == 1;
}


//
// EoF
////////