/*=============================================================================
 * This is a part of the yLib Software Development Kit.
 * Copyright (C) 1998-1999 YEAsoft Inc.
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
 * FILENAME		:	_tmainfn.cpp
 * PURPOSE		:	Application entry point
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

#include "StdAfc.hpp"

#ifdef _DEBUG
#undef HERE
static char HERE[] = __FILE__;
#endif //_DEBUG

/*=============================================================================
 * RUNTIME MAIN FUNCTION
 *============================================================================*/
extern "C" int _tmain			(int argc, _TCHAR **argv, _TCHAR **envp);

/*=============================================================================
 * SPECIFIC RUNTIME FUNCTIONS
 *============================================================================*/
static int						sfAppMain				();
static int						sfSvcMain				();

static int sfAppMain ()
{
#ifdef _DEBUG
	_CrtSetReportHook (_ylb_report_hook);
#endif

	_proc.m_pApp->RegisterConsoleHandler ();

	if ( _proc.m_pApp->InitInstance (&_proc.m_cli) ) {
		_proc.m_pApp->Run ();
		_proc.m_pApp->ExitInstance (TRUE);
	}
	else {
		_proc.m_pApp->ExitInstance (FALSE);
	}

	_proc.m_pApp->UnregisterConsoleHandler ();

	return _proc.m_pApp->GetReturnCode ();
}

static int sfSvcMain ()
{
	_proc.m_pApp->RegisterConsoleHandler ();

	if ( _proc.m_pApp->InitInstance (&_proc.m_cli) ) {
		_proc.m_pApp->Run ();
		_proc.m_pApp->ExitInstance (TRUE);
	}
	else {
		_proc.m_pApp->ExitInstance (FALSE);
	}

	_proc.m_pApp->UnregisterConsoleHandler ();

	return _proc.m_pApp->GetReturnCode ();
}

/*=============================================================================
 * APPLICATION MAIN FUNCTION
 *============================================================================*/
extern "C" int _tmain (int argc, _TCHAR **argv, _TCHAR **envp)
{
	if ( !_proc.m_pApp ) {
		ASSERTY (_proc.m_pApp);
		return -1;
	}
	_proc.m_cli = YCommandLineInfo (argc, argv);

	if ( _proc.m_flg.TestFlags (FLG_APP_YCONAPP) ) {
		return sfAppMain ();
	}
	else if ( _proc.m_flg.TestFlags (FLG_APP_YSERVICE) ) {
		return sfSvcMain ();
	}
	return -1;
}

/*=============================================================================
 * THE CRT REPORT HOOK
 *============================================================================*/
#ifdef _DEBUG

extern "C" int _ylb_report_hook (int reportType, char *userMessage, int *retVal)
{
	if ( !_proc.m_pApp ) {
		return TRUE;
	}
	return _proc.m_pApp->OnCrtDebugReport (reportType, userMessage, retVal);
}

#endif

/*=============================================================================
 * THE CONSOLE HANDLER
 *============================================================================*/
extern "C" BOOL WINAPI _ylb_console_handler (DWORD dwCtrlType)
{
	if ( !_proc.m_pApp ) {
		return FALSE;
	}
	switch ( dwCtrlType ) {
	case CTRL_C_EVENT:
		return _proc.m_pApp->OnCtrlC ();
	case CTRL_BREAK_EVENT:
		return _proc.m_pApp->OnCtrlBreak ();
	case CTRL_CLOSE_EVENT:
		return _proc.m_pApp->OnClose ();
	case CTRL_LOGOFF_EVENT:
		return _proc.m_pApp->OnLogoff ();
	case CTRL_SHUTDOWN_EVENT:
		return _proc.m_pApp->OnShutdown ();
	default:
		return FALSE;
	}
}

//
// EoF
////////