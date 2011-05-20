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
 * FILENAME		:	yBaseApp.cpp
 * PURPOSE		:	Implementation of the application class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.2  2000/09/04 12:07:43  leopoldo
 * Updated license to zlib/libpng
 *
 * Revision 1.1  2000/05/26 14:04:52  leo
 * Initial revision
 *
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
// LPCTSTR lpComment = _T("$Id$");

//
// EoF
////////