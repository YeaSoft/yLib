/*=============================================================================
 * This is a part of the yLib Software Development Kit.
 * Copyright (C) 1998-2004 YEAsoft Int'l.
 * All rights reserved.
 *=============================================================================
 * Copyright (c) 1998-2004 YEAsoft Int'l (Leo Moll, Andrea Pennelli).
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
 * FILENAME		:	yArgParser.cpp
 * PURPOSE		:	Argument Parser Classes
 * SCOPE		:	yLib - The Y Application Framework Class Library
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.3  2004/08/02 10:04:03  leopoldo
 * Adjusted GetValueByNameOrPos
 *
 * Revision 1.2  2004/08/02 09:48:12  leopoldo
 * Added new methods
 *
 * Revision 1.1  2004/08/01 21:49:26  leopoldo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yArgParser.h
 *============================================================================*/
#include "StdInc.hpp"

/*=============================================================================
 * CONSTANTS
 *============================================================================*/
const TCHAR cNUL		= _T('\0');
const TCHAR cSPACE		= _T(' ');
const TCHAR cTAB		= _T('\t');
const TCHAR cQUOTE		= _T('\"');
const TCHAR cSLASH		= _T('\\');
const TCHAR	cEQUAL		= _T('=');

/*=============================================================================
 * IMPLEMENTATION
 *============================================================================*/
bool YArgPair::IsCommand (LPCTSTR pszTest, bool bCaseSensitive) const
{
	if ( IsCommand () ) {
		return (bCaseSensitive) ? (_tcscmp (m_pszName, pszTest) == 0) : (_tcsicmp (m_pszName, pszTest) == 0);
	}
	return false;
}

bool YArgPair::IsNamedValue (LPCTSTR pszTest, bool bCaseSensitive) const
{
	if ( IsNamedValue () ) {
		return (bCaseSensitive) ? (_tcscmp (m_pszName, pszTest) == 0) : (_tcsicmp (m_pszName, pszTest) == 0);
	}
	return false;
}

bool YArgPair::HasNamedValue (LPCTSTR pszTest, bool bCaseSensitive) const
{
	if ( IsNamedValue (pszTest, bCaseSensitive) ) {
		return *m_pszValue != 0;
	}
	return false;
}

/*=============================================================================
 * PARSER IMPLEMENTATION
 *============================================================================*/
bool YArgPairParser::Create (LPCTSTR pszCmdLine)
{
	int			iNumArgs;
	int			iNumCmds;
	int			iNumVals;
	int			iNumChars;
	YArgPair	*argp;
	YArgPair	*valp;
	LPTSTR		*cmdp;
	LPTSTR		args;
	
	// compute sizes
	ParseCmdLine (pszCmdLine, NULL, NULL, NULL, NULL, iNumArgs, iNumCmds, iNumVals, iNumChars);

	if ( NULL == (argp = (YArgPair *) malloc ((iNumArgs + iNumVals) * sizeof (YArgPair) + iNumCmds * sizeof (LPCTSTR) + iNumChars  * sizeof (TCHAR))) ) {
		return false;
	}
	valp = (YArgPair *)	&(argp[iNumArgs]);
	cmdp = (LPTSTR *)	&(valp[iNumVals]);
	args = (LPTSTR)		&(cmdp[iNumCmds]);

	ParseCmdLine (pszCmdLine, argp, cmdp, valp, args, iNumArgs, iNumCmds, iNumVals, iNumChars);
	
	if ( m_argv ) {
		free (m_argv);
	}

	m_argc = iNumArgs - 1;
	m_cmdc = iNumCmds - 1;
	m_valc = iNumVals - 1;
	m_argv = argp;
	m_cmdv = cmdp;
	m_valv = valp;

	return true;
}

bool YArgPairParser::Create (int argc, TCHAR **argv)
{
	int			iNumArgs;
	int			iNumCmds;
	int			iNumVals;
	int			iNumChars;
	YArgPair	*argp;
	YArgPair	*valp;
	LPTSTR		*cmdp;
	LPTSTR		args;
	
	ParseCmdLine (argc, argv, NULL, NULL, NULL, NULL, iNumArgs, iNumCmds, iNumVals, iNumChars);

	if ( NULL == (argp = (YArgPair *) malloc ((iNumArgs + iNumVals) * sizeof (YArgPair) + iNumCmds * sizeof (LPCTSTR) + iNumChars  * sizeof (TCHAR))) ) {
		return false;
	}
	valp = (YArgPair *)	&(argp[iNumArgs]);
	cmdp = (LPTSTR *)	&(valp[iNumVals]);
	args = (LPTSTR)		&(cmdp[iNumCmds]);

	ParseCmdLine (argc, argv, argp, cmdp, valp, args, iNumArgs, iNumCmds, iNumVals, iNumChars);

	if ( m_argv ) {
		free (m_argv);
	}

	m_argc = iNumArgs - 1;
	m_cmdc = iNumCmds - 1;
	m_valc = iNumVals - 1;
	m_argv = argp;
	m_cmdv = cmdp;
	m_valv = valp;

	return true;
}

const YArgPair * YArgPairParser::GetAt (ITERATOR pos) const
{
	YArgPair *pPtr = (YArgPair *) pos;
	if ( pPtr < m_argv ) {
		// junk
		return NULL;
	}
	if ( pPtr < (m_argv + m_argc) ) {
		// in list
		return pPtr;
	}
	// beyond
	return NULL;
}

const YArgPair * YArgPairParser::GetNext (ITERATOR &pos) const
{
	YArgPair *pPtr = (YArgPair *) pos;
	if ( pPtr < m_argv ) {
		// junk
		pos = NULL;
		return NULL;
	}
	if ( pPtr < (m_argv + m_argc - 1) ) {
		// in list
		pos = (ITERATOR) (pPtr + 1);
		return pPtr;
	}
	if ( pPtr == (m_argv + m_argc - 1) ) {
		// last element
		pos = NULL;
		return pPtr;
	}
	// beyond
	pos = NULL;
	return NULL;
}

const YArgPair * YArgPairParser::GetPrev (ITERATOR &pos) const
{
	YArgPair *pPtr = (YArgPair *) pos;
	if ( pPtr < m_argv ) {
		// junk
		pos = NULL;
		return NULL;
	}
	if ( pPtr == m_argv ) {
		// first element
		pos = NULL;
		return pPtr;
	}
	if ( pPtr < (m_argv + m_argc - 1) ) {
		// in list
		pos = (ITERATOR) (pPtr - 1);
		return pPtr;
	}
	// beyond
	pos = NULL;
	return NULL;
}

const YArgPair * YArgPairParser::Skip (ITERATOR &pos, int nSkip) const
{
	YArgPair *pPtr = (YArgPair *) pos;
	pPtr += nSkip;
	if ( pPtr < m_argv ) {
		// junk
		pos = NULL;
		return NULL;
	}
	if ( pPtr < (m_argv + m_argc) ) {
		// in list
		pos = (ITERATOR) pPtr;
		return pPtr;
	}
	// beyond
	pos = NULL;
	return NULL;
}

int YArgPairParser::FindCommand (LPCTSTR pszParam, bool bCaseSensitive) const
{
	for ( int i = 0; i < m_argc; i++ ) {
		if ( m_argv[i].IsCommand (pszParam, bCaseSensitive) ) {
			return i;
		}
	}
	return -1;
}

const YArgPair *YArgPairParser::FindCommandPtr (LPCTSTR pszParam, bool bCaseSensitive) const
{
	for ( int i = 0; i < m_argc; i++ ) {
		if ( m_argv[i].IsCommand (pszParam, bCaseSensitive) ) {
			return m_argv + i;
		}
	}
	return NULL;
}

int YArgPairParser::FindNamedValue (LPCTSTR pszParam, bool bCaseSensitive) const
{
	for ( int i = 0; i < m_argc; i++ ) {
		if ( m_argv[i].IsNamedValue (pszParam, bCaseSensitive) ) {
			return i;
		}
	}
	return -1;
}

const YArgPair *YArgPairParser::FindNamedValuePtr (LPCTSTR pszParam, bool bCaseSensitive) const
{
	for ( int i = 0; i < m_argc; i++ ) {
		if ( m_argv[i].IsNamedValue (pszParam, bCaseSensitive) ) {
			return m_argv + i;
		}
	}
	return NULL;
}

LPCTSTR YArgPairParser::GetValueByName (LPCTSTR pszParam, bool bCaseSensitive) const
{
	for ( int i = 0; i < m_argc; i++ ) {
		if ( m_argv[i].IsNamedValue (pszParam, bCaseSensitive) ) {
			return m_argv[i].GetValue ();
		}
	}
	return NULL;
}

LPCTSTR YArgPairParser::GetValueByNameOrPos (LPCTSTR pszParam, int nIndex, bool bCaseSensitive) const
{
	LPCTSTR pszValue = GetValueByName (pszParam, bCaseSensitive);
	if ( !pszValue ) {
		const YArgPair *pPair = GetAt (nIndex);
		if ( pPair && pPair->IsCommand () ) {
			pszValue =  pPair->GetName ();
		}
	}
	return pszValue;
}

bool YArgPairParser::RemoveAt (int nIndex)
{
	if ( nIndex < 0 || nIndex >= m_argc ) {
		// out of range
		return false;
	}
	// elems to move: argc - 1 - nIndex
	memmove (m_argv + nIndex, m_argv + nIndex + 1, (m_argc - 1 - nIndex) * sizeof (YArgPair));
	--m_argc;
	return true;	
}

bool YArgPairParser::RemoveAt (ITERATOR &pos)
{
	YArgPair *pPtr = (YArgPair *) pos;
	if ( (pPtr < m_argv) || (pPtr >= (m_argv + m_argc)) ) {
		// out of range
		pos = NULL;
		return false;
	}
	// elems to move: argc - 1 - nIndex
	int nIndex = pPtr - m_argv;
	memmove (pPtr, pPtr + 1, (m_argc - 1 - nIndex) * sizeof (YArgPair));
	if ( pPtr >= (m_argv + m_argc) ) {
		// out of range
		pos = NULL;
	}
	return true;
}

bool YArgPairParser::Remove (LPCTSTR pszParam, bool bCaseSensitive)
{
	for ( int i = 0; i < m_argc; i++ ) {
		if ( m_argv[i].IsCommand (pszParam, bCaseSensitive) || m_argv[i].IsNamedValue (pszParam, bCaseSensitive) ) {
			return RemoveAt (i);
		}
	}
	return false;
}

void YArgPairParser::ParseCmdLine (LPCTSTR pszCmdLine, YArgPair *argp, LPTSTR *cmdp, YArgPair *valp, LPTSTR pszArgs, int &iNumArgs, int &iNumCmds, int &iNumVals, int &iNumChars)
{
	LPCTSTR		pSrc;
	bool		bIsNamed;
	bool		bInQuote;
	bool		bCopyChar;
	int			iNumSlash;

	// initialize the parser...
	iNumArgs	= 0;
	iNumCmds	= 0;
	iNumVals	= 0;
	iNumChars	= 0;
	pSrc		= pszCmdLine;
	bIsNamed	= false;
	bInQuote	= false;

	// loop through arguments
	while ( true ) {
		// skip whitespaces
		while  ( *pSrc == cSPACE || *pSrc == cTAB )	{
			++pSrc;
		}
		if ( *pSrc == cNUL ) {
			// end of arguments
			break;
		}
		
		// scan an argument
		if ( argp ) {
			argp->m_pszName		= pszArgs;
			argp->m_pszValue	= NULL;
		}
		if ( valp ) {
			valp->m_pszName		= pszArgs;
		}
		if ( cmdp ) {
			*cmdp				= pszArgs;
		}

		bIsNamed = false;

		// loop through scanning one argument
		while ( true ) {
			/*=============================================
			 * Parser Rules:
			 *
			 * 2N backslashes + " ==> N backslashes and begin/end quote
			 * 2N+1 backslashes + " ==> N backslashes + literal "
			 * N backslashes ==> N backslashes
			 *============================================*/
			bCopyChar	= true;
			iNumSlash	= 0;
			// count number of backslashes
			while ( *pSrc == cSLASH ) {
				++pSrc;
				++iNumSlash;
			}
			if ( *pSrc == cQUOTE ) {
				// if 2N backslashes before, start/end quote, otherwise
				// copy literally
				if ( (iNumSlash % 2) == 0 ) {
					if ( bInQuote ) {
						if ( pSrc[1] == cQUOTE ) {
							// double quote inside quoted string
							// skip first quote char and copy sencond
							++pSrc;
						}
						else {
							bCopyChar = false;
						}
					}
					else {
						// do not copy quote
						bCopyChar = false;
					}
					bInQuote = !bInQuote;
				}
				// divide numslash by two
                iNumSlash /= 2;
			}
			
			// copy slashes
			while ( iNumSlash-- ) {
				if ( pszArgs ) {
					*pszArgs++ = cSLASH;
				}
				++iNumChars;
			}
            
			// if at end of arg, break loop
			if ( *pSrc == cNUL || (!bInQuote && (*pSrc == cSPACE || *pSrc == cTAB )) ) {
				break;
			}
			
			// check if we drift into the second part of the pair
			if ( bCopyChar && !bInQuote && *pSrc == cEQUAL ) {
				// zero terminate the left part
				// initialize the right part pointer
				// and continue the loop
				if ( pszArgs ) {
					*pszArgs++ = cNUL;
				}
				bIsNamed = true;
				if ( argp ) {
					argp->m_pszValue = pszArgs;
				}
				if ( valp ) {
					valp->m_pszValue = pszArgs;
				}
				++pSrc;
				++iNumChars;
				continue;
			}
			
			// copy character into argument
#ifdef _MBCS
			if ( bCopyChar ) {
				if ( pszArgs ) {
					if ( _ismbblead (*pSrc) ) {
						*pszArgs++ = *pSrc++;
						++iNumChars;
					}
					*pszArgs++ = *pSrc;
				} else {
					if ( _ismbblead (*pSrc) ) {
						++pSrc;
						++iNumChars;
					}
				}
				++iNumChars;
			}
			++pSrc;
#else //_MBCS
			if ( bCopyChar ) {
				if ( pszArgs ) {
					*pszArgs++ = *pSrc;
				}
				++iNumChars;
			}
			++pSrc;
#endif //_MBCS

		} // argument loop

		// null-terminate the argument
		if ( pszArgs ) {
			// terminate string
			*pszArgs++ = cNUL;
		}
		++iNumChars;

		// increment arguments
		if ( argp ) {
			++argp;
		}
		// adjust counters
		++iNumArgs;
		if ( bIsNamed ) {
			++iNumVals;
			if ( valp ) {
				++valp;
			}
		}
		else {
			++iNumCmds;
			if ( cmdp ) {
				++cmdp;
			}
		}
	} // commandline loop

	// We put one last argument in -- a null pair
	if ( argp ) {
		argp->m_pszName		= NULL;
		argp->m_pszValue	= NULL;
	}
	if ( valp ) {
		valp->m_pszName		= NULL;
		valp->m_pszValue	= NULL;
	}
	if ( cmdp ) {
		*cmdp				= NULL;
	}

	++iNumArgs;
	++iNumCmds;
	++iNumVals;
}

void YArgPairParser::ParseCmdLine (int argc, TCHAR **argv, YArgPair *argp, LPTSTR *cmdp, YArgPair *valp, LPTSTR pszArgs, int &iNumArgs, int &iNumCmds, int &iNumVals, int &iNumChars)
{
	// initialize the parser...
	iNumChars	= 0;
	iNumCmds	= 0;
	iNumVals	= 0;

	for ( int i = 0; i < argc; i++ ) {
		// scan an argument
		if ( argp ) {
			argp->m_pszName = pszArgs;
		}
		if ( pszArgs ) {
			_tcscpy (pszArgs, argv[i]);
			pszArgs += (_tcslen (pszArgs) + 1);
		}
		iNumChars += (int) (_tcslen (argv[i]) + 1);
		
		LPTSTR pEqual = _tcschr (argv[i], cEQUAL);
		if ( pEqual ) {
			++iNumVals;
			if ( argp ) {
				argp->m_pszValue	= argp->m_pszName + (pEqual - argv[i]);
				*((LPTSTR) argp->m_pszValue) = 0;
				++argp->m_pszValue;
			}
			if ( valp ) {
				// set and increment
				valp->m_pszName		= pszArgs;
				valp->m_pszValue	= argp->m_pszName + (pEqual - argv[i]);
				*((LPTSTR) valp->m_pszValue) = 0;
				++valp->m_pszValue;
				++valp;
			}
		}
		else {
			// it's a command
			++iNumCmds;
			if ( cmdp ) {
				// set and increment
				*cmdp = pszArgs;
				++cmdp;
			}
		}

		// increment arguments
		if ( argp ) {
			++argp;
		}
	}

	// We put one last argument in -- a null pair
	if ( argp ) {
		argp->m_pszName		= NULL;
		argp->m_pszValue	= NULL;
	}
	if ( valp ) {
		valp->m_pszName		= NULL;
		valp->m_pszValue	= NULL;
	}
	if ( cmdp ) {
		*cmdp				= NULL;
	}

	iNumArgs = argc + 1;
	++iNumCmds;
	++iNumVals;
}

#ifndef YLB_ENABLE_INLINE
#include <yArgParser.inl>
#endif

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////