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
 * FILENAME		:	Sample1.h
 * PURPOSE		:	yLib application sample
 * SCOPE		:	yLib SDK
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26  14:07:28  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#include "SampleMsg1.h"
#include "SampleRes1.h"

/*=============================================================================
 * OUR COMMANDLINE PARSER
 *============================================================================*/
class CMyCliParser : public YCmdLineParser
{
public:
	static const DWORD			CMD_WANTSHELP;
	static const DWORD			CMD_UNKNOWN;
	static const DWORD			CMD_EVTINSTALL;
	static const DWORD			CMD_EVTREMOVE;
	static const DWORD			CMD_EVTTEST1;
	static const DWORD			CMD_EVTTEST2;
	static const DWORD			CMD_EVTTEST3;
	static const DWORD			CMD_ENUMSVC;
	static const DWORD			CMD_THREADTEST1;
	static const DWORD			CMD_THREADTEST2;
	static const DWORD			CMD_NPSERVER;
	static const DWORD			CMD_NPCLIENT;
	static const DWORD			CMD_MSSERVER;
	static const DWORD			CMD_MSCLIENT;
	static const DWORD			CMD_TEXTTO;

	static const DWORD			CMD_ACTIVITY_MASK;

public:
	CMyCliParser				() { Parse (); }

public:
	// overridables
	virtual BOOL				OnProcessOption			(BOOL &bTerminate, LPCTSTR &pszOptString, YCmdLineOption &cliOpt);
	virtual BOOL				OnProcessParam			(BOOL &bTerminate, YCmdLineParam &cliPar);
};

/*==================================================================================*
 * OUR SAMPLE APPLICATION
 *==================================================================================*/
class Sample1 : public YConApp
{
public:
	Sample1						() : YConApp (IDS_APP_TITLE) { }

public:
	virtual BOOL				InitInstance			(YCommandLineInfo *cli);
	virtual void				Run						();

protected:
	void						ShowHelp				(DWORD dwCmd);

	void						EvtInstall				();
	void						EvtRemove				();
	void						EvtTest1				(YCmdLineParam *cliPar);
	void						EvtTest2				(YCmdLineParam *cliPar);
	void						EvtTest3				(YCmdLineParam *cliPar);
	void						SvcEnumReg				();
	void						RunThread1				();
	void						RunThread2				();
	void						RunNPServer				(YCmdLineParam *cliPar);
	void						RunNPClient				(YCmdLineParam *cliPar);
	void						RunMSServer				(YCmdLineParam *cliPar);
	void						RunMSClient				(YCmdLineParam *cliPar);
	void						TextTo					(YCmdLineParam *cliPar);
};

