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
 * FILENAME		:	yAfc.cpp
 * PURPOSE		:	Implementation of base classes and global functions
 * SCOPE		:	yAfc
 * HISTORY		: =============================================================
 * 
 * $Log$
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


#ifndef YLB_ENABLE_INLINE
#include <yAfcBase.inl>
#endif

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////