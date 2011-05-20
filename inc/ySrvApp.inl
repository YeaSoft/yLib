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
 * FILENAME		:	ySrvApp.inl
 * PURPOSE		:	Inline members of the system service classes
 * SCOPE		:	yAfc
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.4  2001/04/26 08:54:41  leopoldo
 * Added support for renamable services
 *
 * Revision 1.3  2001/04/12 18:50:16  leopoldo
 * Added YSrvApp::OnCrtDebugReport implementation which excludes
 * interactive operations
 *
 * Revision 1.2  2000/09/04 11:59:53  leopoldo
 * Updated license to zlib/libpng
 *
 * Revision 1.1  2000/05/26 14:03:33  leo
 * Initial revision
 *
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

YLB_INLINE void YServiceCmdLineParser::ShowServices ()
{
	ASSERTY(YlbGetSrv ());
	ShowServices (YlbGetSrv (), YlbGetSrv ()->IsOwnService ());
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
YLB_INLINE BOOL YServiceLogic::OnServiceParamChange ()
{
	return TRUE;
}

YLB_INLINE BOOL YServiceLogic::OnServiceNetBindChange ()
{
	return TRUE;
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

#ifdef _DEBUG

YLB_INLINE BOOL YSrvApp::OnCrtDebugReport (int reportType, LPCSTR pszMessage, int *iRetValue)
{
	if ( reportType == _CRT_ASSERT ) {
		// do not show dialog box.
		YlbDebugBreak ();
		return TRUE;
	}
	return FALSE;
}

#endif

//
// EoF
////////