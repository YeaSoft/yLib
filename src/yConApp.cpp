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
 * FILENAME		:	yConApp.cpp
 * PURPOSE		:	Implementation of the console application class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:04:53  leo
 * Initial revision
 *
 *============================================================================*/

#include "StdAfc.hpp"

/*=============================================================================
 * @doc YLIB | yConApp.h
 *============================================================================*/

#ifdef _DEBUG
#undef HERE
static char HERE[] = __FILE__;
#endif //_DEBUG


/*=============================================================================
 * IMPLEMENTATION
 *============================================================================*/

//
// construction/destruction
//

// @mfunc Constructor of <c YBaseApp>
// @parm LPCTSTR | pszAppName = NULL | A null-terminated string that contains
//			the short application name that the application uses. If this argument
//			is not supplied or is <NULL>, <c YBaseApp> tries to retrieve the <b>InternalName<n>
//			member of the version resource. If also this fails, <c YBaseApp> uses the filename
//			without path and extension of the executable image file.
// @parm LPCTSTR | pszAppDesc = NULL | A null-terminated string that contains
//			the descriptive name of the application. If this argument
//			is not supplied or is <NULL>, <c YBaseApp> tries to retrieve the <b>FileDescription<n>
//			member of the version resource. If also this fails, <c YBaseApp> initializes
//			the description to an empty string.
// @parm WORD | wMajor = 0xffff | The major version of the application. If this
//			argument is not supplied, <c YBaseApp> tries to retrieve the version
//			from the version resource. If also this fails, all version information
//			is inited to 0.
// @parm WORD | wMinor = 0| The minor version of the application. If this argument
//			is not supplied, <c YBaseApp> initializes this value to 0 or, in case
//			neither <p wMajor> is supplied, it tries to retieve the value from
//			the version resource.
// @parm WORD | wStepping = 0 | The stepping number of the application. If this argument
//			is not supplied, <c YBaseApp> initializes this value to 0 or, in case
//			neither <p wMajor> is supplied, it tries to retieve the value from
//			the version resource.
// @parm WORD | wBuild = 0 | The build number of the application. If this argument
//			is not supplied, <c YBaseApp> initializes this value to 0 or, in case
//			neither <p wMajor> is supplied, it tries to retieve the value from
//			the version resource.
// @comm Constructs a <c YBaseApp> object and passes <p lpszAppName> to be stored
//			as the application name. You should construct one global object
//			of your <c YBaseApp>-derived class. You can have only one <c YBaseApp>
//			object in your application. The constructor stores a pointer to
//			the <c YBaseApp> object so that <b>main<n> can call the object's
//			member functions to initialize and run the application.
YConApp::YConApp (LPCTSTR pszAppName, LPCTSTR pszAppDesc, WORD wMajor, WORD wMinor, WORD wStepping, WORD wBuild)
	: YBaseApp (pszAppName, pszAppDesc)
{
	YFixedString	ysAppName(m_szAppName, _countof (m_szAppName), FALSE);
	YFixedString	ysAppDesc(m_szAppDesc, _countof (m_szAppDesc), FALSE);
	YVersInfo		vi (_T("%s\\%s"), m_pszAppPath, m_pszAppName);

	// get short application name
	if ( ysAppName.IsEmpty () ) {
		if ( !(pszAppName = vi.QueryInternalName ()) ) {
			ysAppName = m_pszAppName;
			int i = ysAppName.ReverseFind (_T('.'));
			if ( i != -1 ) {
				ysAppName.SetAt (i, 0);
			}
		}
		ysAppName = pszAppName;
	}

	// get descriptive application name
	if ( ysAppDesc.IsEmpty () ) {
		ysAppDesc = vi.QueryFileDescription ();
		if ( ysAppDesc.IsEmpty () ) {
			ysAppDesc = ysAppName;
		}
	}

	// get version info
	if ( wMajor == 0xffff ) {
		m_wMajor	= vi.GetFileMajorVersion ();
		m_wMinor	= vi.GetFileMinorVersion ();
		m_wStepping	= vi.GetFileSteppingNumber ();
		m_wBuild	= vi.GetFileBuildNumber ();
	}
	else {
		m_wMajor	= wMajor;
		m_wMinor	= wMinor;
		m_wStepping	= wStepping;
		m_wBuild	= wBuild;
	}
}

YConApp::YConApp (UINT nAppNameID) : YBaseApp (nAppNameID)
{
	CommonConstructor ();

	YString256		ysAppString;
	YFixedString	ysAppName(m_szAppName, _countof (m_szAppName), FALSE);
	YFixedString	ysAppDesc(m_szAppDesc, _countof (m_szAppDesc), FALSE);
	YVersInfo		vi (_T("%s\\%s"), m_pszAppPath, m_pszAppName);

	ysAppString.LoadString (nAppNameID);

	YTokenizer		yt(ysAppString, _T(""), TRUE);
	LPCTSTR			lpPtr;

	// skip other fields
	lpPtr = yt.GetFirstToken (_T("\n"));	// service name
	lpPtr = yt.GetNextToken (_T("\n"));		// descriptive service name

	// get short application name
	if ( ysAppName.IsEmpty () ) {
		if ( !(lpPtr = vi.QueryInternalName ()) ) {
			ysAppName = m_pszAppName;
			int i = ysAppName.ReverseFind (_T('.'));
			if ( i != -1 ) {
				ysAppName.SetAt (i, 0);
			}
		}
		else {
			ysAppName = lpPtr;
		}
	}

	// get descriptive application name
	if ( ysAppDesc.IsEmpty () ) {
		ysAppDesc = vi.QueryFileDescription ();
	}

	// get version info
	if ( !(lpPtr = yt.GetNextToken (_T("."))) ) {
		m_wMajor	= vi.GetFileMajorVersion ();
		m_wMinor	= vi.GetFileMinorVersion ();
		m_wStepping	= vi.GetFileSteppingNumber ();
		m_wBuild	= vi.GetFileBuildNumber ();
	}
	else {
		m_wMajor = (WORD) _ttoi (lpPtr);
		lpPtr = yt.GetNextToken (_T("."));
		m_wMinor	= (lpPtr) ? ((WORD) _ttoi (lpPtr)) : (0);
		lpPtr = yt.GetNextToken (_T("."));
		m_wStepping	= (lpPtr) ? ((WORD) _ttoi (lpPtr)) : (0);
		lpPtr = yt.GetNextToken (_T("."));
		m_wBuild	= (lpPtr) ? ((WORD) _ttoi (lpPtr)) : (0);
	}
}



//
// operations
//

BOOL YConApp::RegisterConsoleHandler () const
{
	return ::SetConsoleCtrlHandler (_ylb_console_handler, TRUE);
}

BOOL YConApp::UnregisterConsoleHandler () const
{
	return ::SetConsoleCtrlHandler (_ylb_console_handler, FALSE);
}



//
// implementation
//

void YConApp::CommonConstructor ()
{
	ASSERTY (!_proc.m_pApp);
	_proc.m_flg.SetFlags (FLG_APP_YCONAPP);
	_proc.m_pApp	= this;
	m_iReturn		= 0;
	m_pCLI			= &(_proc.m_cli);

	// initialize members.
	ASSERTY(::GetModuleFileName (NULL, m_szAppPath, _countof (m_szAppPath)));
	if ( (m_pszAppName = _tcsrchr (m_szAppPath, '\\')) != NULL ) {
		m_pszAppPath = m_szAppPath;
		*((LPTSTR) m_pszAppName) = 0;
		++m_pszAppName;
	}
	else {
		// should never happen
		m_pszAppPath = _T(".");
		m_pszAppName = m_szAppPath;
	}
}

#ifndef YLB_ENABLE_INLINE
#include <yConApp.inl>
#endif

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////