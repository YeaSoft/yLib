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
 * FILENAME		:	yTokens.h
 * PURPOSE		:	Declaration of the token helper classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yTokens.h
 *============================================================================*/
#ifndef __yTokens_h__
#define __yTokens_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yLibBase_h__
#include <yLibBase.h>
#endif

/*=============================================================================
 * THE TOKENIZER
 *============================================================================*/
// @class This class permits the enumeration of tokens in a string
// @comm This class is intended for splitting a string in it's tokens. The
//		class permits to copy the tokens in a supplied buffer or to use
//		an internal buffer (limited to 256 characters). The supplied string
//		is not affected by this operation.
class YTokenizer
{
public:
	// @cmember Construction of a tokenizer object
	YTokenizer				(LPCTSTR lpszString, LPCTSTR lpszSeparators = NULL, BOOL bWordMode = FALSE);

public:
	// @access Attributes
	// @cmember Initializes the tokenizer with a new string to tokenize
	LPCTSTR					SetString			(LPCTSTR lpszString, LPCTSTR lpszSeparators = NULL, BOOL bWordMode = FALSE);

public:
	// @access Operations
	// @cmember Gets the first token of the supplied string using a supplied token separator
	LPCTSTR					GetFirstToken		(TCHAR cSeparator, LPTSTR pszBuffer, UINT cbSize);
	LPCTSTR					GetFirstToken		(TCHAR cSeparator);

	// @cmember Gets the next token of the supplied string using a supplied token separator
	LPCTSTR					GetNextToken		(TCHAR cSeparator, LPTSTR pszBuffer, UINT cbSize);
	LPCTSTR					GetNextToken		(TCHAR cSeparator);

	// @cmember Gets the first token of the supplied string using a supplied token separator array
	LPCTSTR					GetFirstToken		(LPCTSTR lpszSeparators, LPTSTR pszBuffer, UINT cbSize);
	LPCTSTR					GetFirstToken		(LPCTSTR lpszSeparators);

	// @cmember Gets the next token of the supplied string using a supplied token separator array
	LPCTSTR					GetNextToken		(LPCTSTR lpszSeparators, LPTSTR pszBuffer, UINT cbSize);
	LPCTSTR					GetNextToken		(LPCTSTR lpszSeparators);

	// @cmember Gets the first token of the supplied string
	LPCTSTR					GetFirstToken		(LPTSTR pszBuffer, UINT cbSize);
	LPCTSTR					GetFirstToken		();

	// @cmember Gets the next token of the supplied string
	LPCTSTR					GetNextToken		(LPTSTR pszBuffer, UINT cbSize);
	LPCTSTR					GetNextToken		();

private:
	LPCTSTR					m_pszSeparators;
	LPCTSTR					m_pszString;
	LPCTSTR					m_pszStart;
	TCHAR					m_szBuffer[256];
	BOOL					m_bWordMode;
};
//
// @ex Simple token enumeration | 
//
//	...
//	YTokenizer  tok("Blah,blubb;kak;piss", ";,");
//	LPCTSTR     lpPtr;
//
//	while ( lpPtr = tok.GetNextToken () ) {
//		printf ("%s\n", lpPtr);
//	}
//	...
//
// @ex generates the following output: | 
//
//	Blah
//	blubb
//	kak
//	piss
//
// @xref <j Needful Things>
//

#ifdef YLB_ENABLE_INLINE
#include <yTokens.inl>
#endif

#endif //__yTokens_h__
//
// EoF
////////