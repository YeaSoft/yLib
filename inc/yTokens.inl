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
 * FILENAME		:	yTokens.inl
 * PURPOSE		:	Inline members of the token helper classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:03:38  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yTokens.h
 *============================================================================*/

YLB_INLINE YTokenizer::YTokenizer (LPCTSTR lpszString, LPCTSTR lpszSeparators /* = NULL */, BOOL bWordMode /* = FALSE */)
{
	m_pszSeparators	= (lpszSeparators ) ? (lpszSeparators ) : (TEXT(","));
	m_pszString		= lpszString;
	m_pszStart		= lpszString;
	m_bWordMode		= bWordMode;
}

YLB_INLINE LPCTSTR YTokenizer::SetString (LPCTSTR lpszString, LPCTSTR lpszSeparators  /* = NULL */, BOOL bWordMode /* = FALSE */)
{
	LPCTSTR lpOldString = m_pszString;

	m_pszSeparators = (lpszSeparators ) ? (lpszSeparators ) : (m_pszSeparators);
	m_pszString		= lpszString;
	m_pszStart		= lpszString;
	m_bWordMode		= bWordMode;
	return lpOldString;
}

YLB_INLINE LPCTSTR YTokenizer::GetFirstToken (TCHAR cSeparator, LPTSTR pszBuffer, UINT cbSize)
{
	m_pszStart = m_pszString;
	return GetNextToken (cSeparator, pszBuffer, cbSize);
}

YLB_INLINE LPCTSTR YTokenizer::GetFirstToken (TCHAR cSeparator)
{
	m_pszStart = m_pszString;
	return GetNextToken (cSeparator);
}

YLB_INLINE LPCTSTR YTokenizer::GetNextToken (TCHAR cSeparator)
{
	return GetNextToken (cSeparator, m_szBuffer, _countof (m_szBuffer));
}

YLB_INLINE LPCTSTR YTokenizer::GetFirstToken (LPCTSTR lpszSeparators, LPTSTR pszBuffer, UINT cbSize)
{
	m_pszStart = m_pszString;
	return GetNextToken (lpszSeparators, pszBuffer, cbSize);
}

YLB_INLINE LPCTSTR YTokenizer::GetFirstToken (LPCTSTR lpszSeparators)
{
	m_pszStart = m_pszString;
	return GetNextToken (lpszSeparators, m_szBuffer, _countof (m_szBuffer));
}

YLB_INLINE LPCTSTR YTokenizer::GetNextToken (LPCTSTR lpszSeparators)
{
	return GetNextToken (lpszSeparators, m_szBuffer, _countof (m_szBuffer));
}


YLB_INLINE LPCTSTR YTokenizer::GetFirstToken (LPTSTR pszBuffer, UINT cbSize)
{
	m_pszStart = m_pszString;
	return GetNextToken (m_pszSeparators, pszBuffer, cbSize);
}

YLB_INLINE LPCTSTR YTokenizer::GetFirstToken ()
{
	m_pszStart = m_pszString;
	return GetNextToken (m_pszSeparators, m_szBuffer, _countof (m_szBuffer));
}

YLB_INLINE LPCTSTR YTokenizer::GetNextToken (LPTSTR pszBuffer, UINT cbSize)
{
	return GetNextToken (m_pszSeparators, pszBuffer, cbSize);
}

YLB_INLINE LPCTSTR YTokenizer::GetNextToken ()
{
	return GetNextToken (m_pszSeparators, m_szBuffer, _countof (m_szBuffer));
}

//
// EoF
////////