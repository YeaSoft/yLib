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
 * FILENAME		:	yAfc.cpp
 * PURPOSE		:	Implementation of base classes and global functions
 * SCOPE		:	yAfc
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26  14:04:50  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yAfcBase.h
 *============================================================================*/
#include "StdAfc.hpp"

#ifdef _DEBUG
#undef HERE
static char HERE[] = __FILE__;
#endif //_DEBUG

/*=============================================================================
 * HELPER FUNCTIONS
 *============================================================================*/
YConApp * YLBAPI YlbGetApp ()
{
	return _proc.m_pApp;
}

YSrvApp * YLBAPI YlbGetSrv ()
{
	return (_proc.m_flg.TestFlags (FLG_APP_YSERVICE)) ? ((YSrvApp *) _proc.m_pApp) : (NULL);
}

/*=============================================================================
 * COMMANDLINE PARSER IMPLEMENTATION
 *============================================================================*/
YCmdLineParser::YCmdLineParser (LPCTSTR pszSeparators)
{
	m_nNumOptions		= 0;
	m_nNumParams		= 0;
	m_flgCommands		= 0;
	m_flgOptions		= 0;
	m_bParsingResult	= FALSE;
	SetOptionChars ((pszSeparators) ? (pszSeparators) : (_T("-")));
}

YCmdLineOption *YCmdLineParser::FindOptionByMeaning (DWORDLONG dwMeaning)
{
	for ( UINT nCnt = 0; nCnt < m_nNumOptions; nCnt++ ) {
		if ( m_cliOptions[nCnt].m_dwMeaning == dwMeaning ) {
			return &(m_cliOptions[nCnt]);
		}
	}
	return NULL;
}

YCmdLineParam *YCmdLineParser::FindParamByMeaning (DWORDLONG dwMeaning)
{
	for ( UINT nCnt = 0; nCnt < m_nNumParams; nCnt++ ) {
		if ( m_cliParams[nCnt].m_dwMeaning == dwMeaning ) {
			return &(m_cliParams[nCnt]);
		}
	}
	return NULL;
}

BOOL YCmdLineParser::Parse ()
{
	if ( !_proc.m_cli.GetParamCount () ) {
		return FALSE;
	}

	m_nNumOptions		= 0;
	m_nNumParams		= 0;
	m_flgCommands		= 0;
	m_flgOptions		= 0;
	m_bParsingResult	= TRUE;

	BOOL		bTerminate = FALSE;
	ITERATOR	pos;
	UINT		nCliIndex = 2;
	for ( pos = _proc.m_cli.GetHeadPosition (), _proc.m_cli.GetNext (pos); pos; nCliIndex++ ) {
		LPCTSTR pszArg = _proc.m_cli.GetNext (pos);
		if ( pszArg ) {
			// check if it is an option
			if ( _tcschr (m_szOptionChars, *pszArg) ) {
				// it's an option
				if ( m_nNumOptions < YLB_MAX_OPTIONS ) {
					++pszArg;	// skip the option char
					UINT nAddArgs = CountAdditionalArgs (pos);
					while ( *pszArg ) {
						YCmdLineOption *cliOpt = &(m_cliOptions[m_nNumOptions]);
						cliOpt->m_cOption	= *pszArg;
						cliOpt->m_dwMeaning	= 0;
						cliOpt->m_pszParam	= pszArg + 1;
						cliOpt->m_nCliIndex	= nCliIndex;
						cliOpt->m_argc		= nAddArgs;
						cliOpt->m_argv		= (nAddArgs) ? ((LPTSTR *) pos) : (NULL);
						LPCTSTR pszArgStart	= pszArg;
						LPCTSTR pszArgEnd	= pszArg;
						while ( *pszArgEnd ) {
							++pszArgEnd;
						}
						if ( OnProcessOption (bTerminate, pszArg, *cliOpt) ) {
							// option accepted
							++m_nNumOptions;
							// plausibility checks
							if ( cliOpt->m_argc > nAddArgs ) {
								cliOpt->m_argc = nAddArgs;
							}
							if ( !nAddArgs ) {
								cliOpt->m_argv = NULL;
							}
							if ( cliOpt->m_argv && (cliOpt->m_argv != (LPTSTR *) pos) ) {
								cliOpt->m_argv = (LPTSTR *) pos;
							}
							// skip additional args requested by the option
							if ( cliOpt->m_argc ) {
								_proc.m_cli.Skip (pos, cliOpt->m_argc);
							}
						}
						// plausibility check
						if ( pszArg <= pszArgStart ) {
							// go on!
							pszArg = pszArgStart + 1;
						}
						if ( pszArg > pszArgEnd ) {
							pszArg = pszArgEnd;
						}
					}
				}
			}
			else {
				// it's a parameter
				if ( m_nNumParams < YLB_MAX_PARAMS ) {
					UINT nAddArgs = CountAdditionalArgs (pos);
					YCmdLineParam *cliPar = &(m_cliParams[m_nNumParams]);
					cliPar->m_dwMeaning	= 0;
					cliPar->m_pszParam	= pszArg;
					cliPar->m_nCliIndex	= nCliIndex;
					cliPar->m_argc		= nAddArgs;
					cliPar->m_argv		= (nAddArgs) ? ((LPTSTR *) pos) : (NULL);
					if ( OnProcessParam (bTerminate, *cliPar) ) {
						// parameter accepted
						++m_nNumParams;
						// plausibility checks
						if ( cliPar->m_argc > nAddArgs ) {
							cliPar->m_argc = nAddArgs;
						}
						if ( !nAddArgs ) {
							cliPar->m_argv = NULL;
						}
						if ( cliPar->m_argv && (cliPar->m_argv != (LPTSTR *) pos) ) {
							cliPar->m_argv = (LPTSTR *) pos;
						}
						// skip additional args requested by the parameter
						if ( cliPar->m_argc ) {
							_proc.m_cli.Skip (pos, cliPar->m_argc);
						}
					}
				}
			}
		}
	}

	return m_bParsingResult = OnFinalCheck ();
}

UINT YCmdLineParser::CountAdditionalArgs (ITERATOR pos)
{
	UINT	nCount = 0;

	for ( LPCTSTR pszArg = _proc.m_cli.GetNext (pos); pszArg; pszArg = _proc.m_cli.GetNext (pos) ) {
		// check if it is an option
		if ( _tcschr (m_szOptionChars, *pszArg) ) {
			return nCount;
		}
		++nCount;
	}
	return nCount;
}

YCmdLineOption * YCmdLineParser::GetNextOption (ITERATOR &pos)
{
	YCmdLineOption *lpPtr = (YCmdLineOption *) pos;
	if ( lpPtr < &(m_cliOptions[0]) ) {
		// junk
		pos = NULL;
		return NULL;
	}
	if ( lpPtr < &(m_cliOptions[m_nNumOptions - 1]) ) {
		// in list
		pos = (ITERATOR) &(lpPtr[1]);
		return lpPtr;
	}
	if ( lpPtr == &(m_cliOptions[m_nNumOptions - 1]) ) {
		// last element
		pos = NULL;
		return lpPtr;
	}
	// beyond
	pos = NULL;
	return NULL;
}

YCmdLineOption * YCmdLineParser::GetPrevOption (ITERATOR &pos)
{
	YCmdLineOption *lpPtr = (YCmdLineOption *) pos;
	if ( lpPtr < &(m_cliOptions[0]) ) {
		// junk
		pos = NULL;
		return NULL;
	}
	if ( lpPtr == &(m_cliOptions[0]) ) {
		// first element
		pos = NULL;
		return lpPtr;
	}
	if ( lpPtr < &(m_cliOptions[m_nNumOptions - 1]) ) {
		// in list
		pos = (ITERATOR) &(lpPtr[-1]);
		return lpPtr;
	}
	// beyond
	pos = NULL;
	return NULL;
}

YCmdLineOption * YCmdLineParser::GetOptionAt (ITERATOR pos)
{
	YCmdLineOption *lpPtr = (YCmdLineOption *) pos;
	if ( lpPtr < &(m_cliOptions[0]) ) {
		// junk
		return NULL;
	}
	if ( lpPtr <= &(m_cliOptions[m_nNumOptions - 1]) ) {
		// in list
		return lpPtr;
	}
	// beyond
	return NULL;
}

YCmdLineParam * YCmdLineParser::GetNextParam (ITERATOR &pos)
{
	YCmdLineParam *lpPtr = (YCmdLineParam *) pos;
	if ( lpPtr < &(m_cliParams[0]) ) {
		// junk
		pos = NULL;
		return NULL;
	}
	if ( lpPtr < &(m_cliParams[m_nNumParams - 1]) ) {
		// in list
		pos = (ITERATOR) &(lpPtr[1]);
		return lpPtr;
	}
	if ( lpPtr == &(m_cliParams[m_nNumParams - 1]) ) {
		// last element
		pos = NULL;
		return lpPtr;
	}
	// beyond
	pos = NULL;
	return NULL;
}

YCmdLineParam * YCmdLineParser::GetPrevParam (ITERATOR &pos)
{
	YCmdLineParam *lpPtr = (YCmdLineParam *) pos;
	if ( lpPtr < &(m_cliParams[0]) ) {
		// junk
		pos = NULL;
		return NULL;
	}
	if ( lpPtr == &(m_cliParams[0]) ) {
		// first element
		pos = NULL;
		return lpPtr;
	}
	if ( lpPtr < &(m_cliParams[m_nNumParams - 1]) ) {
		// in list
		pos = (ITERATOR) &(lpPtr[-1]);
		return lpPtr;
	}
	// beyond
	pos = NULL;
	return NULL;
}

YCmdLineParam * YCmdLineParser::GetParamAt (ITERATOR pos)
{
	YCmdLineParam *lpPtr = (YCmdLineParam *) pos;
	if ( lpPtr < &(m_cliParams[0]) ) {
		// junk
		return NULL;
	}
	if ( lpPtr <= &(m_cliParams[m_nNumParams - 1]) ) {
		// in list
		return lpPtr;
	}
	// beyond
	return NULL;
}


#ifndef YLB_ENABLE_INLINE
#include <yAfcBase.inl>
#endif

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////