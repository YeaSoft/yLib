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
 * FILENAME		:	internal.h
 * PURPOSE		:	Internal common stuff
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.2  2000/08/23 10:01:41  leo
 * Added inlined format function
 * Updated license
 *
 * Revision 1.1  2000/05/26  14:04:48  leo
 * Initial revision
 *
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
	HANDLE						m_hStdIn;
	HANDLE						m_hStdOut;
	HANDLE						m_hStdErr;
	int							m_iStdOut;
	int							m_iStdErr;
	FILE *						m_fpStdOut;
	FILE *						m_fpStdErr;
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

/*=============================================================================
 * INLINED HELPERS
 *============================================================================*/
inline void						_ylb_formatv			(LPTSTR pszBuffer, UINT cbSize, LPCTSTR pszFormat, va_list argList)
{
	if ( _vsntprintf (pszBuffer, cbSize - 1, pszFormat, argList) < 0 ) {
		pszBuffer[cbSize - 1] = 0;
	}
}

#endif //_ylib_internal_
//
// EoF
////////