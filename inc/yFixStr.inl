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
 * FILENAME		:	yFixStr.inl
 * PURPOSE		:	Inline members of the fixed string classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yFixStr.h
 *============================================================================*/

/*=============================================================================
 * GENERIC OPERATORS
 *============================================================================*/
#ifdef _UNICODE

YLB_INLINE YBigString YLBAPI operator+ (const YStringData& string, char ch)
{
	return string + (TCHAR) ch;
}

YLB_INLINE YBigString YLBAPI operator+ (char ch, const YStringData& string)
{
	return (TCHAR) ch + string;
}

#endif

/*=============================================================================
 * STRING DATA BASE CLASS IMPLEMENTATION
 *============================================================================*/
YLB_INLINE YStringData::YStringData (LPTSTR pszStorage, UINT cbSize)
{
	m_pszString	= pszStorage;
	m_cbSize	= cbSize;
}

YLB_INLINE UINT YStringData::GetSize () const
{
	return m_cbSize;
}

YLB_INLINE UINT YStringData::GetBufferSize () const
{
	return m_cbSize * sizeof (TCHAR);
}

YLB_INLINE LPTSTR YStringData::GetBuffer () const
{
	return m_pszString;
}

YLB_INLINE LPCTSTR YStringData::GetNullForEmptyString () const
{
	return (m_pszString && *m_pszString) ? (m_pszString) : (NULL);
}

YLB_INLINE YStringData::operator LPCTSTR () const
{
	return m_pszString;
}

/*=============================================================================
 * FIXED STRING CLASS IMPLEMENTATION
 *============================================================================*/
YLB_INLINE YFixedString::YFixedString (LPTSTR pszStorage, UINT cbSize, BOOL bEmpty) : YStringData (pszStorage, cbSize)
{
	if ( bEmpty ) {
		Empty ();
	}
}

YLB_INLINE UINT YFixedString::SafeStrLen (LPCTSTR lpsz)
{
	return (lpsz) ? (lstrlen (lpsz)) : (0);
}

YLB_INLINE UINT YFixedString::GetLength () const
{
	return (m_pszString) ? (_tcslen (m_pszString)) : (0);
}

YLB_INLINE BOOL YFixedString::IsEmpty () const
{
	return (m_pszString) ? (*m_pszString == 0) : (0);
}

YLB_INLINE void YFixedString::Empty ()
{
	ASSERTY(m_pszString);
	*m_pszString = 0;
}

YLB_INLINE TCHAR YFixedString::GetAt (UINT nIndex) const
{
	ASSERTY(m_pszString);
	return (nIndex < m_cbSize) ? (m_pszString[nIndex]) : (0);
}

YLB_INLINE TCHAR YFixedString::operator[] (UINT nIndex) const
{
	return GetAt (nIndex);
}

YLB_INLINE void YFixedString::SetAt (UINT nIndex, TCHAR ch)
{
	ASSERTY(m_pszString);
	if ( nIndex && (nIndex < m_cbSize) ) {
		m_pszString[nIndex] = ch;
	}
}

YLB_INLINE void YFixedString::Assign (const YStringData& stringSrc)
{
	ASSERTY(m_pszString);
	_tcsncpy (m_pszString, stringSrc, m_cbSize - 1);
	m_pszString[m_cbSize - 1] = 0;
}

YLB_INLINE void YFixedString::Assign (const unsigned char *psz)
{
	Assign ((LPCSTR) psz);
}

YLB_INLINE void YFixedString::Assign (INT iValue)
{
	_yxtot ((DWORD) iValue, m_pszString, m_cbSize, iValue < 0);
}

YLB_INLINE void YFixedString::Assign (UINT uValue)
{
	_yxtot ((DWORD) uValue, m_pszString, m_cbSize, FALSE);
}

YLB_INLINE void YFixedString::Assign (LONG lValue)
{
	_yxtot ((DWORD) lValue, m_pszString, m_cbSize, lValue < 0);
}

YLB_INLINE void YFixedString::Assign (DWORD dwValue)
{
	_yxtot ((DWORD) dwValue, m_pszString, m_cbSize, FALSE);
}

YLB_INLINE const YFixedString & YFixedString::operator= (const YStringData& stringSrc)
{
	Assign (stringSrc);
	return *this;
}

YLB_INLINE const YFixedString & YFixedString::operator= (TCHAR ch)
{
	Assign (ch);
	return *this;
}

YLB_INLINE const YFixedString & YFixedString::operator= (LPCTSTR lpsz)
{
	Assign (lpsz);
	return *this;
}

#ifdef _UNICODE

YLB_INLINE const YFixedString & YFixedString::operator= (LPCSTR lpsz)
{
	Assign (lpsz);
	return *this;
}

YLB_INLINE const YFixedString & YFixedString::operator= (char ch)
{
	Assign (ch);
	return *this;
}

#else

YLB_INLINE const YFixedString & YFixedString::operator= (LPCWSTR lpsz)
{
	Assign (lpsz);
	return *this;
}

#endif

YLB_INLINE void YFixedString::Concat (const unsigned char *psz)
{
	Concat ((LPCSTR) psz);
}

YLB_INLINE const YFixedString & YFixedString::operator+= (const YStringData& stringSrc)
{
	Concat (stringSrc);
	return *this;
}

YLB_INLINE const YFixedString & YFixedString::operator+= (TCHAR ch)
{
	Concat (ch);
	return *this;
}

YLB_INLINE const YFixedString & YFixedString::operator+= (LPCTSTR lpsz)
{
	Concat (lpsz);
	return *this;
}

#ifdef _UNICODE

YLB_INLINE const YFixedString & YFixedString::operator+= (LPCSTR lpsz)
{
	Concat (lpsz);
	return *this;
}

YLB_INLINE const YFixedString & YFixedString::operator+= (char ch)
{
	Concat (ch);
	return *this;
}

#else

YLB_INLINE const YFixedString & YFixedString::operator+= (LPCWSTR lpsz)
{
	Concat (lpsz);
	return *this;
}

#endif

YLB_INLINE int YFixedString::Compare (LPCTSTR lpsz) const
{
	ASSERTY(m_pszString);
	ASSERTY(YlbIsValidString (lpsz));
	return _tcscmp (m_pszString, lpsz);
}

YLB_INLINE int YFixedString::CompareNoCase (LPCTSTR lpsz) const
{
	ASSERTY(m_pszString);
	ASSERTY(YlbIsValidString (lpsz));
	return _tcsicmp (m_pszString, lpsz);
}

YLB_INLINE int YFixedString::Collate (LPCTSTR lpsz) const
{
	ASSERTY(m_pszString);
	ASSERTY(YlbIsValidString (lpsz));
	return _tcscoll (m_pszString, lpsz);
}

YLB_INLINE int YFixedString::CollateNoCase (LPCTSTR lpsz) const
{
	ASSERTY(m_pszString);
	ASSERTY(YlbIsValidString (lpsz));
	return _tcsicoll (m_pszString, lpsz);
}

YLB_INLINE void YFixedString::MakeUpper ()
{
	ASSERTY(m_pszString);
	_tcsupr (m_pszString);
}

YLB_INLINE void YFixedString::MakeLower ()
{
	ASSERTY(m_pszString);
	_tcslwr (m_pszString);
}

YLB_INLINE void YFixedString::MakeReverse ()
{
	ASSERTY(m_pszString);
	_tcsrev (m_pszString);
}

YLB_INLINE int YFixedString::Find (TCHAR ch) const
{
	ASSERTY(m_pszString);
	LPCTSTR lpPtr = _tcschr (m_pszString, (_TUCHAR) ch);
	return (lpPtr) ? (int) (lpPtr - m_pszString) : (-1);
}

YLB_INLINE int YFixedString::ReverseFind (TCHAR ch) const
{
	ASSERTY(m_pszString);
	LPCTSTR lpPtr = _tcsrchr (m_pszString, (_TUCHAR) ch);
	return (lpPtr) ? (int) (lpPtr - m_pszString) : (-1);
}

YLB_INLINE int YFixedString::FindOneOf (LPCTSTR lpszCharSet) const
{
	ASSERTY(m_pszString);
	ASSERTY(YlbIsValidString(lpszCharSet));
	LPTSTR lpPtr = _tcspbrk (m_pszString, lpszCharSet);
	return (lpPtr) ? (int) (lpPtr - m_pszString) : (-1);
}

YLB_INLINE int YFixedString::Find (LPCTSTR lpszSub) const
{
	ASSERTY(m_pszString);
	ASSERTY(YlbIsValidString(lpszSub));
	LPTSTR lpPtr = _tcsstr (m_pszString, lpszSub);
	return (lpPtr) ? (int) (lpPtr - m_pszString) : (-1);
}

YLB_INLINE void YFixedString::FormatV (LPCTSTR lpszFormat, va_list argList)
{
	ASSERTY(m_pszString);
	ASSERTY(YlbIsValidString(lpszFormat));

	if ( _vsntprintf (m_pszString, m_cbSize - 1, lpszFormat, argList) < 0 ) {
		m_pszString[m_cbSize - 1] = 0;
	}
}

#ifndef _UNICODE

YLB_INLINE void YFixedString::AnsiToOem ()
{
	ASSERTY(m_pszString);
	::CharToOem (m_pszString, m_pszString);
}

YLB_INLINE void YFixedString::OemToAnsi ()
{
	ASSERTY(m_pszString);
	::OemToChar (m_pszString, m_pszString);
}

#endif

YLB_INLINE BOOL YFixedString::LoadString (UINT nID)
{
	ASSERTY(m_pszString);
	YlbLoadString (nID, m_pszString, m_cbSize);
	return ::GetLastError () == NOERROR;
}

/*=============================================================================
 * DYNAMICALLY ALLOCATED FIXED SYSTEM STRING CLASS IMPLEMENTATION
 *============================================================================*/
YLB_INLINE YHeapString::YHeapString () : YFixedString (NULL, 0, FALSE)
{
}

YLB_INLINE YHeapString::~YHeapString ()
{
	Free ();
}

/*=============================================================================
 * MULTISTRING CLASS IMPLEMENTATION
 *============================================================================*/
YLB_INLINE YMultiString::YMultiString () : YStringData (NULL, 0)
{
}

YLB_INLINE YMultiString::~YMultiString ()
{
	Free ();
}

//
// EoF
////////