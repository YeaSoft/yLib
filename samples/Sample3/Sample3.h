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
 * FILENAME		:	Sample3.h
 * PURPOSE		:	yLib service sample
 * SCOPE		:	yLib SDK
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#include "SampleRes3.h"
#include "SampleMsg3.h"
#include "Threads.h"

/*=============================================================================
 * OUR COMMANDLINE PARSER
 *============================================================================*/
class CMultiParser : public YServiceCmdLineParser
{
public:
	// construction
	CMultiParser				(BOOL bAutoParse = TRUE) : YServiceCmdLineParser (FALSE) { if ( bAutoParse ) Parse (); }

public:
	// overridables
	virtual void				ShowIntro				();
	virtual void				ShowExtro				();
};

/*=============================================================================
 * OUR SAMPLE SERVICE
 *============================================================================*/
class CEarnerService : public YServiceLogic
{
public:
	// construction
	CEarnerService				(UINT nID, UINT nAccount) : YServiceLogic (nID) { m_nAccount = nAccount; }

public:
	// overridables
	virtual BOOL				InitInstance			(YCommandLineInfo *cli);

	virtual BOOL				PreInstallService		(LPCTSTR pszCompName, LPCTSTR pszImagePath, LPSVCCREATESTRUCT lpSCS);
	virtual void				OnInstallError			(DWORD dwError, LPCTSTR pszCompName, LPCTSTR pszImagePath);
	virtual void				OnInstall				();

	virtual void				AfterRemoveService		(LPCTSTR pszCompName, LPCTSTR pszImagePath, BOOL bBadInstalled);

	virtual BOOL				OnServiceStart			(YCommandLineInfo *cli);
	virtual BOOL				OnServicePause			();
	virtual BOOL				OnServiceContinue		();

	virtual void				OnServiceError			(DWORD dwWin32Error, DWORD dwServiceError);
	virtual void				OnServiceEnd			(BOOL bSystemShudown, BOOL bRegularExit);

protected:
	// implementation
	LPCTSTR						m_lpInserts[1];
	CEarner						m_eaThread;
	UINT						m_nAccount;
};

class CReporterService : public YServiceLogic
{
public:
	// construction
	CReporterService			() : YServiceLogic (IDS_SVC_REPORTER) { }

public:
	// overridables
	virtual BOOL				InitInstance			(YCommandLineInfo *cli);

	virtual BOOL				PreInstallService		(LPCTSTR pszCompName, LPCTSTR pszImagePath, LPSVCCREATESTRUCT lpSCS);
	virtual void				OnInstallError			(DWORD dwError, LPCTSTR pszCompName, LPCTSTR pszImagePath);
	virtual void				OnInstall				();

	virtual void				AfterRemoveService		(LPCTSTR pszCompName, LPCTSTR pszImagePath, BOOL bBadInstalled);

	virtual BOOL				OnServiceStart			(YCommandLineInfo *cli);
	virtual BOOL				OnServicePause			();
	virtual BOOL				OnServiceContinue		();

	virtual void				OnServiceError			(DWORD dwWin32Error, DWORD dwServiceError);
	virtual void				OnServiceEnd			(BOOL bSystemShudown, BOOL bRegularExit);

protected:
	// implementation
	LPCTSTR						m_lpInserts[1];
	CReporter					m_rpThread;
};

/*=============================================================================
 * OUR SAMPLE SERVICE APPLICATION
 *============================================================================*/
class CMultiService : public YSrvApp
{
public:
	// construction
	CMultiService				();

public:
	// operations
	void						Allocate				();
	
public:
	// overridables
	virtual BOOL				InitInstance			(YCommandLineInfo *cli);

protected:
	// implementation
	CEarnerService				m_slEarner1;
	CEarnerService				m_slEarner2;
	CReporterService			m_slReporter;

public:
	// implementation
	YConsole					m_con;
};

/*=============================================================================
 * THE INSTANTIATION
 *============================================================================*/
extern CMultiService			theSvc;

