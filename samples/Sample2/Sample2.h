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
 * FILENAME		:	Sample2.h
 * PURPOSE		:	yLib service sample
 * SCOPE		:	yLib SDK
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#include "SampleRes2.h"
#include "SampleMsg2.h"
#include "Beeper.h"

/*=============================================================================
 * OUR COMMANDLINE PARSER
 *============================================================================*/
class CBeeperParser : public YServiceCmdLineParser
{
public:
	// construction
	CBeeperParser				(BOOL bAutoParse = TRUE) : YServiceCmdLineParser (FALSE) { if ( bAutoParse ) Parse (); }

public:
	// overridables
	virtual void				ShowIntro				();
	virtual void				ShowExtro				();
};

/*=============================================================================
 * OUR SAMPLE SERVICE
 *============================================================================*/
class CBeeperService : public YServiceLogic
{
public:
	// construction/destruction
	CBeeperService				() : YServiceLogic (IDS_APP_TITLE) { }

public:
	// operations

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
	CBeeper						m_bpThread;
	YConsole					m_con;
};

/*=============================================================================
 * OUR SAMPLE SERVICE APPLICATION
 *============================================================================*/
class CBeeperApp : public YSrvApp
{
public:
	// construction/destruction
	CBeeperApp					();

public:
	// overridables
	virtual BOOL				InitInstance			(YCommandLineInfo *cli);

protected:
	// implementation
	CBeeperService				m_slBeeper;
};

