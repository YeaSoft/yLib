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
 * FILENAME		:	internal.h
 * PURPOSE		:	Internal common stuff
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

#ifndef _ylib_internal_
#define _ylib_internal_

/*=============================================================================
 * INTERNAL EXCEPTION CLASS
 *============================================================================*/
class YException : public YErrableObject
{
public:
	// construction
	YException					(DWORD dwError) : YErrableObject (dwError) { }
};

/*=============================================================================
 * FORWARD CLASS DECLARATIONS
 *============================================================================*/
class YConApp;

/*=============================================================================
 * PROCESS ENVIRONMENT
 *============================================================================*/
class PROC_ENV
{
public:
	PROC_ENV					();
	~PROC_ENV					();

public:
	YConApp						*m_pApp;
	YCommandLineInfo			m_cli;
	YFlags						m_flg;

	HANDLE						m_hProcessHandle;
	HANDLE						m_hThreadHandle;
	HINSTANCE					m_hInstance;
	HINSTANCE					m_hResHandle;
};

#define FLG_APP_YCONAPP			0x00000001
#define FLG_APP_YSERVICE		0x00000002
#define FLG_APP_USER			0x00010000

extern PROC_ENV					_proc;

/*=============================================================================
 * LIBRARY ENVIRONMENT DATA
 *============================================================================*/
class YAUX_DATA
{
public:
	// other system information
	UINT						nWinVer;        // Major.Minor version numbers
	BOOL						bWin95;         // TRUE if Windows 95 (not NT)
	BOOL						bWin4;          // TRUE if Windows 4.0
	BOOL						bNotWin4;       // TRUE if not Windows 4.0

public:
// Implementation
	YAUX_DATA					();
	~YAUX_DATA					();
};

/*=============================================================================
 * INSTANTIATION
 *============================================================================*/
extern YAUX_DATA				ylbData;

/*=============================================================================
 * CONVERSION HELPERS
 *============================================================================*/
int YLB_CDECL					_ywcstombsz				(char* mbstr, const wchar_t* wcstr, size_t count);
int YLB_CDECL					_ymbstowcsz				(wchar_t* wcstr, const char* mbstr, size_t count);

/*=============================================================================
 * DEBUGGING REPORT HOOK
 *============================================================================*/
#ifdef _DEBUG
extern "C" int					_ylb_report_hook		(int reportType, char *userMessage, int *retVal);
#endif

/*=============================================================================
 * CONSOLE HANDLER
 *============================================================================*/
extern "C" BOOL WINAPI			_ylb_console_handler	(DWORD dwCtrlType);

#endif //_ylib_internal_
//
// EoF
////////