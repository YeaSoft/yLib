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
 * FILENAME		:	yTokens.inl
 * PURPOSE		:	Inline members of the token helper classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
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