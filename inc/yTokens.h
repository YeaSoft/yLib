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
 * FILENAME		:	yTokens.h
 * PURPOSE		:	Declaration of the token helper classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:03:37  leo
 * Initial revision
 *
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