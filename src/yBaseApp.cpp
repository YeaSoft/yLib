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
 * FILENAME		:	yBaseApp.cpp
 * PURPOSE		:	Implementation of the application class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

#include "StdAfc.hpp"

/*=============================================================================
 * @doc YLIB | yBaseApp.h
 *============================================================================*/
#ifdef _DEBUG
#undef HERE
static char HERE[] = __FILE__;
#endif //_DEBUG

/*=============================================================================
 * IMPLEMENTATION
 *============================================================================*/
YBaseApp::YBaseApp (LPCTSTR pszAppName, LPCTSTR pszAppDesc)
{
	CommonConstructor ();

	YFixedString	ysAppName(m_szAppName, _countof (m_szAppName));
	YFixedString	ysAppDesc(m_szAppDesc, _countof (m_szAppDesc));

	ysAppName	= pszAppName;
	ysAppDesc	= pszAppDesc;
}

YBaseApp::YBaseApp (UINT nAppNameID)
{
	CommonConstructor ();

	YFixedString	ysAppName(m_szAppName, _countof (m_szAppName));
	YFixedString	ysAppDesc(m_szAppDesc, _countof (m_szAppDesc));
	YString256		ysAppString;

	ysAppString.LoadString (nAppNameID);

	YTokenizer		yt(ysAppString, _T(""), TRUE);

	ysAppName = yt.GetFirstToken (_T("\n"));
	ysAppDesc = yt.GetNextToken (_T("\n"));
}



//
// attributes
//
void YBaseApp::SetAppName (LPCTSTR pszAppName)
{
	if ( pszAppName && *pszAppName ) {
		_tcsncpy (m_szAppName, pszAppName, _countof (m_szAppName) - 1);
		m_szAppName[_countof (m_szAppName) - 1] = 0;
	}
}

void YBaseApp::SetAppDescription (LPCTSTR pszAppDescription)
{
	if ( pszAppDescription && *pszAppDescription ) {
		_tcsncpy (m_szAppDesc, pszAppDescription, _countof (m_szAppDesc) - 1);
		m_szAppDesc[_countof (m_szAppDesc) - 1] = 0;
	}
}



//
// system operations
//
YString256 YBaseApp::GetSysErrorString (DWORD dwError)
{
	YBigString	ysRet;
	YlbGetSysErrorString (dwError, ysRet.GetBuffer (), ysRet.GetBufferSize ());
	return ysRet;
}



//
// implementation
//
void YBaseApp::CommonConstructor ()
{
	m_pCLI			= NULL;
	*m_szAppName	= 0;
	*m_szAppDesc	= 0;
}

#ifndef YLB_ENABLE_INLINE
#include <yBaseApp.inl>
#endif

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////