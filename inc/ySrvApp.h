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
 * FILENAME		:	ySrvApp.h
 * PURPOSE		:	Declaration of the system service classes
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
 * Revision 1.1  2000/05/26 14:03:32  leo
 * Initial revision
 *
 *============================================================================*/
/*=============================================================================
 * @doc YLIB | ySrvApp.h
 *============================================================================*/
#ifndef __ySrvApp_h__
#define __ySrvApp_h__


/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yConApp_h__
#include <yConApp.h>
#endif
#ifndef __yEventSource_h__
#include <yEventSource.h>
#endif
#ifndef __ySync_h__
#include <ySync.h>
#endif

/*=============================================================================
 * FORWARD CLASS DECLARATIONS
 *============================================================================*/
//class YCmdLineParser;
	class YServiceCmdLineParser;
//class YBaseApp;
	class YSrvApp;
	class YServiceLogic;

/*=============================================================================
 * DEFAULT SERVICE COMMANDLINE PARSER
 *============================================================================*/
// supported commands
#define SCL_CMD_UNKNOWN			0x00000001
#define SCL_CMD_WANTSHELP		0x00000002

#define SCL_CMD_INSTALL			0x00000004
#define SCL_CMD_REMOVE			0x00000008
#define SCL_CMD_START			0x00000010
#define SCL_CMD_STOP			0x00000020
#define SCL_CMD_PAUSE			0x00000040
#define SCL_CMD_RESUME			0x00000080
#define SCL_CMD_SIMULATE		0x00000100
#define SCL_CMD_USER			0x00000200

#define SCL_CMD_MASK			0xfffffffc
#define SCL_CMD_MASK_KNOWN		0x000003fc

// supported options
#define SCL_OPT_UNKNOWN			0x00000001

#define SCL_OPT_INTERACTIVE		0x00000002
#define SCL_OPT_START_AUTO		0x00000004
#define SCL_OPT_START_DISABLE	0x00000008
#define SCL_OPT_USER_NAME		0x00000010
#define SCL_OPT_USER_PWD		0x00000020
#define SCL_OPT_USER			0x00000040

#define SCL_OPT_MASK			0xfffffffe

class YServiceCmdLineParser : public YCmdLineParser
{
public:
	// construction
	YServiceCmdLineParser		(BOOL bAutoParse = TRUE, BOOL bCanBeRenamed = FALSE);

public:
	// attributes
	BOOL						CanBeRenamed			() const { return m_bCanBeRenamed; }

public:
	// overridables
	virtual void				ShowFullUsage			(DWORDLONG dwCmd, LPCTSTR pszError, ...);
	virtual void				ShowFullUsageVa			(DWORDLONG dwCmd, LPCTSTR pszError, va_list va);
	virtual void				ShowIntro				();
	virtual void				ShowUsage				(DWORDLONG dwCmd);
	virtual void				ShowExtro				();
	virtual void				ShowServices			();

protected:
	// usage helpers
	virtual void				ShowCommands			(YSrvApp *pApp, BOOL bSingle);
	virtual void				ShowServices			(YSrvApp *pApp, BOOL bSingle);
	virtual void				ShowInstallCommand		(YSrvApp *pApp, BOOL bSingle);
	virtual void				ShowInstallExplanation	(YSrvApp *pApp, BOOL bSingle);
	virtual void				ShowInstallOptions		(YSrvApp *pApp, BOOL bSingle);
	virtual void				ShowRemoveCommand		(YSrvApp *pApp, BOOL bSingle);
	virtual void				ShowRemoveExplanation	(YSrvApp *pApp, BOOL bSingle);
	virtual void				ShowRemoveOptions		(YSrvApp *pApp, BOOL bSingle);
	virtual void				ShowStartCommand		(YSrvApp *pApp, BOOL bSingle);
	virtual void				ShowStartExplanation	(YSrvApp *pApp, BOOL bSingle);
	virtual void				ShowStartOptions		(YSrvApp *pApp, BOOL bSingle);
	virtual void				ShowStopCommand			(YSrvApp *pApp, BOOL bSingle);
	virtual void				ShowStopExplanation		(YSrvApp *pApp, BOOL bSingle);
	virtual void				ShowStopOptions			(YSrvApp *pApp, BOOL bSingle);
	virtual void				ShowPauseCommand		(YSrvApp *pApp, BOOL bSingle);
	virtual void				ShowPauseExplanation	(YSrvApp *pApp, BOOL bSingle);
	virtual void				ShowPauseOptions		(YSrvApp *pApp, BOOL bSingle);
	virtual void				ShowResumeCommand		(YSrvApp *pApp, BOOL bSingle);
	virtual void				ShowResumeExplanation	(YSrvApp *pApp, BOOL bSingle);
	virtual void				ShowResumeOptions		(YSrvApp *pApp, BOOL bSingle);
	virtual void				ShowSimulateCommand		(YSrvApp *pApp, BOOL bSingle);
	virtual void				ShowSimulateExplanation	(YSrvApp *pApp, BOOL bSingle);
	virtual void				ShowSimulateOptions		(YSrvApp *pApp, BOOL bSingle);

public:
	// implemented overridables
	virtual BOOL				OnProcessOption			(BOOL &bTerminate, LPCTSTR &pszOptString, YCmdLineOption &cliOpt);
	virtual BOOL				OnProcessParam			(BOOL &bTerminate, YCmdLineParam &cliPar);
	virtual BOOL				OnFinalCheck			();

protected:
	BOOL						m_bCanBeRenamed;
};

/*============================================================================*
 * THE SERVICE LOGIC CLASS
 *============================================================================*/
class YServiceLogic : public YBaseApp
{
protected:
	typedef enum {
		svcStartDisabled	= SERVICE_DISABLED,
		svcStartManual		= SERVICE_DEMAND_START,
		svcStartAutomatic	= SERVICE_AUTO_START
	} SVCSTARTTYPE;

	typedef struct _tagSVCCREATESTRUCT {
		BOOL			bInteractive;
		SVCSTARTTYPE	svcStartType;
		YString32		ysGroup;
		YMultiString	ymsDependencies;
		YHeapString		ysAccount;
		YHeapString		ysPassword;
		YHeapString		ysDescription;
		UINT			cbNumCategories;
		YPathString		ysCatMessageFile;
	} SVCCREATESTRUCT, *LPSVCCREATESTRUCT;

private:
	// kill these construction methods & operators
	YServiceLogic				(const YServiceLogic &);
	YServiceLogic				&operator=				(const YServiceLogic &);

public:
	// construction/destruction
	YServiceLogic				(LPCTSTR pszSvcName, LPCTSTR pszSvcDesc = NULL);
	YServiceLogic				(UINT nSvcNameID);

public:
	// attributes
	YSrvApp *					GetSrv					() const;
	YEventLogSource *			GetEventLog				();
	BOOL						IsInteractive			() const;
	BOOL						IsShareService			() const;
	BOOL						IsOwnService			() const;

public:
	// operations
	void						StopService				();
	void						ReportOperationDelay	(DWORD dwDelay);

public:
	// management overridables
	virtual BOOL				PreInstallService		(LPCTSTR pszCompName, LPCTSTR pszImagePath, LPSVCCREATESTRUCT lpSCS);
	virtual void				OnInstallError			(DWORD dwError, LPCTSTR pszCompName, LPCTSTR pszImagePath);
	virtual void				OnInstall				();
	virtual BOOL				OnStartUI				(DWORD dwState, DWORD dwWin32ExitCode = NOERROR, DWORD dwSeconds = 0);
	virtual void				OnStartError			(DWORD dwError, LPCTSTR pszCompName, LPCTSTR pszImagePath);
	virtual BOOL				OnStopUI				(DWORD dwState, DWORD dwWin32ExitCode = NOERROR, DWORD dwSeconds = 0);
	virtual void				OnStopError				(DWORD dwError, LPCTSTR pszCompName, LPCTSTR pszImagePath);
	virtual BOOL				OnPauseUI				(DWORD dwState, DWORD dwWin32ExitCode = NOERROR, DWORD dwSeconds = 0);
	virtual void				OnPauseError			(DWORD dwError, LPCTSTR pszCompName, LPCTSTR pszImagePath);
	virtual BOOL				OnContinueUI			(DWORD dwState, DWORD dwWin32ExitCode = NOERROR, DWORD dwSeconds = 0);
	virtual void				OnContinueError			(DWORD dwError, LPCTSTR pszCompName, LPCTSTR pszImagePath);
	virtual BOOL				OnRemove				(BOOL bStopped);
	virtual void				OnRemoveError			(DWORD dwError, LPCTSTR pszCompName, LPCTSTR pszImagePath);
	virtual void				AfterRemoveService		(LPCTSTR pszCompName, LPCTSTR pszImagePath, BOOL bBadInstalled);

	// runtime overridables
	virtual BOOL				OnServiceStart			(YCommandLineInfo *cli);
	virtual BOOL				OnServicePause			();
	virtual BOOL				OnServiceContinue		();
	virtual BOOL				OnUserControl			(DWORD dwCtrlCode);
#if(_WIN32_WINNT >= 0x0500)
	virtual void				OnServiceParamChange	();
	virtual void				OnServiceNetBindChange	();
#endif
	virtual void				OnServiceError			(DWORD dwWin32Error, DWORD dwServiceError);
	virtual void				OnServiceEnd			(BOOL bSystemShudown, BOOL bRegularExit);

public:
	// advanced overridables
	virtual BOOL				OnServiceRename			(BOOL bFromServiceMain, LPCTSTR pszNewName);
	virtual void				OnReportStatus			(DWORD dwState, DWORD &dwControlsAccepted);

public:
	// very advanced overridables (the whole service logic)
	virtual void				ServiceMain				(UINT nIndex, YCommandLineInfo *cli, BOOL bRunAsService);
	virtual void				ServiceControl			(DWORD dwCtrlCode);
	virtual void				ServiceWait				(BOOL bRunAsService);

protected:
	// implementation
	void						InitServiceEnvironment	();
	// runtime
	BOOL						ReportStatusToSCM		(DWORD dwWin32Error, DWORD dwServiceError, DWORD dwWaitHint);
	void						ShowSimulationMenu		(LPTSTR lpszKeys);
	BOOL						ComputeActionPaths		(YComputerName &ysCompName, YPathString &ysBinPath);
	BOOL						SetNewState				(DWORD dwState, DWORD dwWin32Error = NOERROR, DWORD dwServiceError = 0, DWORD dwWaitHint = 3000);
	// management
	BOOL						PerformInstallation		(UINT nIndex, YServiceCmdLineParser &cliParser);
	BOOL						PerformDeinstallation	(UINT nIndex, YServiceCmdLineParser &cliParser);
	BOOL						PerformStart			(UINT nIndex, YServiceCmdLineParser &cliParser);
	BOOL						PerformStop				(UINT nIndex, YServiceCmdLineParser &cliParser);
	BOOL						PerformPause			(UINT nIndex, YServiceCmdLineParser &cliParser);
	BOOL						PerformResume			(UINT nIndex, YServiceCmdLineParser &cliParser);
	BOOL						PerformSimulation		(UINT nIndex, YServiceCmdLineParser &cliParser);

protected:
	// data members
	YEventLogSource				m_evLog;

protected:
	// implementation
	YSrvApp *					m_theSvc;
	SERVICE_STATUS_HANDLE		m_sshStatusHandle;
	DWORD						m_dwState;
	DWORD						m_dwCheckPoint;
	DWORD						m_dwServiceError;
	DWORD						m_dwControlsAccepted;
	YEvent						m_evTerm;
	BOOL						m_bShutDown;
	BOOL						m_bInteractive;

	friend class				YSrvApp;
};

/*============================================================================*
 * THE SYSTEM SERVICE CLASS
 *============================================================================*/
class YSrvApp : public YConApp
{
private:
	// kill these construction methods & operators
	YSrvApp						(const YSrvApp &);
	YSrvApp						&operator=				(const YSrvApp &);

public:
	// construction/destruction
	YSrvApp						(LPCTSTR pszAppName = NULL, LPCTSTR pszAppDesc = NULL, WORD wMajor = 0xffff, WORD wMinor = 0, WORD wStepping = 0, WORD wBuild = 0);
	YSrvApp						(UINT nAppNameID);
	YSrvApp						(YServiceLogic &sl, LPCTSTR pszAppName = NULL, LPCTSTR pszAppDesc = NULL, WORD wMajor = 0xffff, WORD wMinor = 0, WORD wStepping = 0, WORD wBuild = 0);
	YSrvApp						(YServiceLogic &sl, UINT nAppNameID);
	~YSrvApp					();

public:
	// attributes
	YServiceLogic *				GetService				(UINT nIndex) const;
	UINT						GetServiceCount			() const;
	BOOL						IsShareService			() const;
	BOOL						IsOwnService			() const;


public:
	// operations
	BOOL						AddService				(YServiceLogic *psl);
	UINT						FindService				(LPCTSTR pszName) const;
	BOOL						ProcessShellCommand		(YServiceCmdLineParser &cliParser);

public:
	// advanced overridables
#ifdef _DEBUG
	virtual BOOL				OnCrtDebugReport		(int reportType, LPCSTR pszMessage, int *iRetValue);
#endif

public:
	// very advanced overridables (the whole service logic)
	virtual void				Run						();

protected:
	// implementation
	void						CommonConstructor		();
	SERVICE_STATUS_HANDLE		RegisterControlHandler	(UINT nIndex);
	UINT						GetRequestedService		(YServiceCmdLineParser &cliParser, DWORDLONG dwCmd);

protected:
	// implementation
	UINT						m_nServices;
	YServiceLogic *				m_slServices[YLB_MAX_SERVICES];

	friend class				YServiceLogic;
};

#ifdef YLB_ENABLE_INLINE
#include <ySrvApp.inl>
#endif

#endif //__ySrvApp_h__
//
// EoF
////////
