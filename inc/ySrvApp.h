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
 * FILENAME		:	ySrvApp.h
 * PURPOSE		:	Declaration of the system service classes
 * SCOPE		:	yAfc
 * HISTORY		: =============================================================
 * 
 * $Log$
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
	YServiceCmdLineParser		(BOOL bAutoParse = TRUE);

public:
	// overridables
	virtual void				ShowIntro				();
	virtual void				ShowUsage				(DWORDLONG dwCmd);
	virtual void				ShowExtro				();
	virtual void				ShowServices			();

public:
	// implemented overridables
	virtual BOOL				OnProcessOption			(BOOL &bTerminate, LPCTSTR &pszOptString, YCmdLineOption &cliOpt);
	virtual BOOL				OnProcessParam			(BOOL &bTerminate, YCmdLineParam &cliPar);
	virtual BOOL				OnFinalCheck			();
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
