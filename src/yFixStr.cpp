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
 * FILENAME		:	yFixStr.cpp
 * PURPOSE		:	Implementation of the fixed string classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

#include "StdInc.hpp"

/*=============================================================================
 * @doc YLIB | yFixStr.h
 *============================================================================*/

/*=============================================================================
 * GENERIC OPERATORS
 *============================================================================*/
YBigString YLBAPI operator+ (const YStringData& string1, const YStringData& string2)
{
	YBigString	s;
	s.Assign (string1);
	s.Concat (string2);
	return s;
}

YBigString YLBAPI operator+ (const YStringData& string, LPCTSTR lpsz)
{
	ASSERTY(lpsz == NULL || YlbIsValidString(lpsz));
	YBigString	s;
	s.Assign (string);
	s.Concat (lpsz);
	return s;
}

YBigString YLBAPI operator+ (LPCTSTR lpsz, const YStringData& string)
{
	ASSERTY(lpsz == NULL || YlbIsValidString(lpsz));
	YBigString	s;
	s.Assign (lpsz);
	s.Concat (string);
	return s;
}

YBigString YLBAPI operator+ (const YStringData& string, TCHAR ch)
{
	YBigString	s;
	s.Assign (string);
	s.Concat (ch);
	return s;
}

YBigString YLBAPI operator+ (TCHAR ch, const YStringData& string)
{
	YBigString	s;
	s.Assign (ch);
	s.Concat (string);
	return s;
}

/*=============================================================================
 * FIXED STRING CLASS IMPLEMENTATION
 *============================================================================*/
void YFixedString::Assign (TCHAR ch)
{
	ASSERTY(m_pszString);
	*m_pszString = ch;
	if ( m_cbSize > 1 ) {
		m_pszString[1] = 0;
	}
}

void YFixedString::Assign (LPCTSTR lpsz)
{
	ASSERTY(m_pszString);
	if ( lpsz ) {
		ASSERTY(YlbIsValidString(lpsz));
		_tcsncpy (m_pszString, lpsz, m_cbSize - 1);
		m_pszString[m_cbSize - 1] = 0;
	}
	else {
		*m_pszString = 0;
	}
}

#ifdef _UNICODE

void YFixedString::Assign (LPCSTR lpsz)
{
	ASSERTY(m_pszString);
	if ( lpsz ) {
		_ymbstowcsz (m_pszString, lpsz, min(strlen (lpsz) + 1, m_cbSize));
	}
	else {
		*m_pszString = 0;
	}
}

void YFixedString::Assign (char ch)
{
	ASSERTY(m_pszString);
	*m_pszString = (TCHAR) ch;
	if ( m_cbSize > 1 ) {
		m_pszString[1] = 0;
	}
}

#else

void YFixedString::Assign (LPCWSTR lpsz)
{
	ASSERTY(m_pszString);
	if ( lpsz ) {
		_ywcstombsz (m_pszString, lpsz, min(wcslen (lpsz) + 1, m_cbSize) * sizeof (TCHAR));
	}
	else {
		*m_pszString = 0;
	}
}

#endif

void YFixedString::Assign (LPCTSTR lpsz, UINT nCount)
{
	ASSERTY(m_pszString);
	nCount = min(nCount,m_cbSize);
	if ( lpsz && nCount ) {
		--nCount;
		_tcsncpy (m_pszString, lpsz, nCount);
		m_pszString[nCount] = 0;
	}
	else {
		*m_pszString = 0;
	}
}

void YFixedString::Concat (const YStringData& stringSrc)
{
	ASSERTY(m_pszString);
	UINT nSrcLen = GetLength ();
	UINT nAddLen = min (m_cbSize - nSrcLen, _tcslen (stringSrc) + 1);
	if ( nAddLen ) {
		memcpy (m_pszString + nSrcLen, stringSrc.m_pszString, nAddLen - 1);
		m_pszString[nSrcLen + nAddLen - 1] = 0;
	}
}

void YFixedString::Concat (TCHAR ch)
{
	ASSERTY(m_pszString);
	UINT nSrcLen = GetLength ();
	if ( nSrcLen < (m_cbSize - 1) ) {
		m_pszString[nSrcLen] = ch;
		m_pszString[nSrcLen + 1] = 0;
	}
}

void YFixedString::Concat (LPCTSTR lpsz)
{
	ASSERTY(m_pszString);
	if ( lpsz ) {
		ASSERTY(YlbIsValidString(lpsz));
		UINT nSrcLen = GetLength ();
		UINT nAddLen = min (m_cbSize - nSrcLen, _tcslen (lpsz) + 1);
		if ( nAddLen ) {
			memcpy (m_pszString + nSrcLen, lpsz, nAddLen - 1);
			m_pszString[nSrcLen + nAddLen - 1] = 0;
		}
	}
}

#ifdef _UNICODE

void YFixedString::Concat (LPCSTR lpsz)
{
	ASSERTY(m_pszString);
	if ( lpsz ) {
		UINT nSrcLen = GetLength ();
		UINT nAddLen = min (m_cbSize - nSrcLen, strlen (lpsz) + 1);
		_ymbstowcsz (m_pszString + nSrcLen, lpsz, nAddLen);
	}
}

void YFixedString::Concat (char ch)
{
	ASSERTY(m_pszString);
	UINT nSrcLen = GetLength ();
	if ( nSrcLen < (m_cbSize - 1) ) {
		m_pszString[nSrcLen] = (TCHAR) ch;
		m_pszString[nSrcLen + 1] = 0;
	}
}

#else

void YFixedString::Concat (LPCWSTR lpsz)
{
	ASSERTY(m_pszString);
	if ( lpsz ) {
		UINT nSrcLen = GetLength ();
		UINT nAddLen = min (m_cbSize - nSrcLen, wcslen (lpsz) + 1);
		_ywcstombsz (m_pszString + nSrcLen, lpsz, nAddLen);
	}
}

#endif

YBigString YFixedString::Mid (int nFirst) const
{
	return Mid (nFirst, GetLength () - nFirst);
}

YBigString YFixedString::Mid (int nFirst, int nCount) const
{
	if ( nFirst < 0 ) {
		nFirst = 0;
	}
	if ( nCount < 0 ) {
		nCount = 0;
	}

	UINT nLength = GetLength ();

	if ( (UINT) (nFirst + nCount) > nLength ) {
		nCount = nLength - nFirst;
	}
	if ( (UINT) nFirst > nLength ) {
		nCount = 0;
	}

	ASSERTY(nFirst >= 0);
	ASSERTY((UINT) (nFirst + nCount) <= nLength);

	if ( (nFirst == 0) && ((UINT) (nFirst + nCount) == nLength) ) {
		// optimize case of returning entire string
		return *this;
	}

	YBigString	dest;
	dest.Assign (m_pszString + nFirst, nCount);
	return dest;
}

YBigString YFixedString::Left (int nCount) const
{
	if ( nCount < 0 ) {
		nCount = 0;
	}
	if ( (UINT) nCount >= GetLength () ) {
		return *this;
	}

	YBigString	dest;
	dest.Assign (m_pszString, nCount);
	return dest;
}

YBigString YFixedString::Right (int nCount) const
{
	if ( nCount < 0 ) {
		nCount = 0;
	}
	UINT nLength = GetLength ();
	if ( (UINT) nCount >= nLength ) {
		return *this;
	}

	YBigString	dest;
	dest.Assign (m_pszString + nCount, nLength - nCount);
	return dest;
}

YBigString YFixedString::SpanIncluding (LPCTSTR lpszCharSet) const
{
	ASSERTY(m_pszString);
	ASSERTY(YlbIsValidString(lpszCharSet));
	return Left (_tcsspn (m_pszString, lpszCharSet));
}

YBigString YFixedString::SpanExcluding (LPCTSTR lpszCharSet) const
{
	ASSERTY(m_pszString);
	ASSERTY(YlbIsValidString(lpszCharSet));
	return Left (_tcscspn (m_pszString, lpszCharSet));
}

void YFixedString::Trim ()
{
	ASSERTY(m_pszString);

	LPTSTR	lpStart	= m_pszString;
	LPTSTR	lpStop	= NULL;
	LPTSTR	lpLast	= NULL;

	// skip initial whitespaces
	while ( _istspace (*lpStart) ) {
		lpStart = _tcsinc (lpStart);
	}

	// find last non-whitespace
	for ( LPTSTR lpPtr = lpStart; *lpPtr; lpPtr = _tcsinc (lpPtr) ) {
		if ( _istspace (*lpPtr) ) {
			if ( lpLast == NULL ) {
				lpLast = lpPtr;
			}
		}
		else {
			lpLast = NULL;
		}
	}

	if ( lpStart != m_pszString ) {
		if ( lpLast ) {
			// alltrim
			memmove (m_pszString, lpStart, lpLast - lpStart);
			m_pszString[lpLast - lpStart] = 0;
		}
		else {
			// lefttrim
			memmove (m_pszString, lpStart, lpPtr - lpStart);
			m_pszString[lpPtr - lpStart] = 0;
		}
	}
	else if ( lpLast ) {
		*lpLast = 0;
	}
}

void YFixedString::TrimLeft ()
{
	ASSERTY(m_pszString);

	LPCTSTR lpsz = m_pszString;

	while ( _istspace (*lpsz) ) {
		lpsz = _tcsinc (lpsz);
	}

	if ( lpsz != m_pszString ) {
		int nDataLength = GetLength () - (lpsz - m_pszString);
		memmove (m_pszString, lpsz, (nDataLength + 1) * sizeof (TCHAR));
	}
}

void YFixedString::TrimRight ()
{
	ASSERTY(m_pszString);

	LPTSTR lpsz		= m_pszString;
	LPTSTR lpszLast	= NULL;

	while ( *lpsz ) {
		if ( _istspace (*lpsz) ) {
			if ( lpszLast == NULL ) {
				lpszLast = lpsz;
			}
		}
		else {
			lpszLast = NULL;
		}
		lpsz = _tcsinc (lpsz);
	}

	if ( lpszLast != NULL ) {
		*lpszLast = '\0';
	}
}

void YFixedString::Trim (TCHAR chTarget)
{
	ASSERTY(m_pszString);

	LPTSTR	lpStart	= m_pszString;
	LPTSTR	lpStop	= NULL;
	LPTSTR	lpLast	= NULL;

	// skip initial targets
	while ( *lpStart == chTarget ) {
		lpStart = _tcsinc (lpStart);
	}

	// find last non-target
	for ( LPTSTR lpPtr = lpStart; *lpPtr; lpPtr = _tcsinc (lpPtr) ) {
		if ( *lpStart == chTarget ) {
			if ( lpLast == NULL ) {
				lpLast = lpPtr;
			}
		}
		else {
			lpLast = NULL;
		}
	}

	if ( lpStart != m_pszString ) {
		if ( lpLast ) {
			// alltrim
			memmove (m_pszString, lpStart, lpLast - lpStart);
			m_pszString[lpLast - lpStart] = 0;
		}
		else {
			// lefttrim
			memmove (m_pszString, lpStart, lpPtr - lpStart);
			m_pszString[lpPtr - lpStart] = 0;
		}
	}
	else if ( lpLast ) {
		*lpLast = 0;
	}
}

void YFixedString::Trim (LPCTSTR lpszTargets)
{
	ASSERTY(m_pszString);

	LPTSTR	lpStart	= m_pszString;
	LPTSTR	lpStop	= NULL;
	LPTSTR	lpLast	= NULL;

	// skip initial targets
	while ( _tcschr (lpszTargets, *lpStart) ) {
		lpStart = _tcsinc (lpStart);
	}

	// find last non-target
	for ( LPTSTR lpPtr = lpStart; *lpPtr; lpPtr = _tcsinc (lpPtr) ) {
		if ( _tcschr (lpszTargets, *lpStart) ) {
			if ( lpLast == NULL ) {
				lpLast = lpPtr;
			}
		}
		else {
			lpLast = NULL;
		}
	}

	if ( lpStart != m_pszString ) {
		if ( lpLast ) {
			// alltrim
			memmove (m_pszString, lpStart, lpLast - lpStart);
			m_pszString[lpLast - lpStart] = 0;
		}
		else {
			// lefttrim
			memmove (m_pszString, lpStart, lpPtr - lpStart);
			m_pszString[lpPtr - lpStart] = 0;
		}
	}
	else if ( lpLast ) {
		*lpLast = 0;
	}
}

void YFixedString::TrimLeft (TCHAR chTarget)
{
	ASSERTY(m_pszString);

	LPCTSTR lpsz = m_pszString;

	while ( *lpsz == chTarget ) {
		lpsz = _tcsinc (lpsz);
	}

	if ( lpsz != m_pszString ) {
		int nDataLength = GetLength () - (lpsz - m_pszString);
		memmove (m_pszString, lpsz, (nDataLength + 1) * sizeof (TCHAR));
	}
}

void YFixedString::TrimLeft (LPCTSTR lpszTargets)
{
	ASSERTY(m_pszString);

	LPCTSTR lpsz = m_pszString;

	while ( *lpsz ) {
		if ( !_tcschr (lpszTargets, *lpsz) ) {
			break;
		}
		lpsz = _tcsinc (lpsz);
	}

	if ( lpsz != m_pszString ) {
		int nDataLength = GetLength () - (lpsz - m_pszString);
		memmove (m_pszString, lpsz, (nDataLength + 1) * sizeof (TCHAR));
	}
}

void YFixedString::TrimRight (TCHAR chTarget)
{
	ASSERTY(m_pszString);

	LPTSTR lpsz		= m_pszString;
	LPTSTR lpszLast	= NULL;

	while ( *lpsz ) {
		if ( *lpsz == chTarget ) {
			if ( lpszLast == NULL ) {
				lpszLast = lpsz;
			}
		}
		else {
			lpszLast = NULL;
		}
		lpsz = _tcsinc (lpsz);
	}

	if ( lpszLast != NULL ) {
		*lpszLast = '\0';
	}
}

void YFixedString::TrimRight (LPCTSTR lpszTargets)
{
	ASSERTY(m_pszString);

	LPTSTR lpsz		= m_pszString;
	LPTSTR lpszLast	= NULL;

	while ( *lpsz ) {
		if ( _tcschr (lpszTargets, *lpsz) ) {
			if ( lpszLast == NULL ) {
				lpszLast = lpsz;
			}
		}
		else {
			lpszLast = NULL;
		}
		lpsz = _tcsinc (lpsz);
	}

	if ( lpszLast != NULL ) {
		*lpszLast = '\0';
	}
}

void YFixedString::Terminate (TCHAR cTermChar)
{
	ASSERTY(m_pszString);
	LPTSTR lpPtr = _tcschr (m_pszString, (_TUCHAR) cTermChar);
	if ( lpPtr ) {
		*lpPtr = 0;
	}
}

void YFixedString::ReverseTerminate (TCHAR cTermChar)
{
	ASSERTY(m_pszString);
	LPTSTR lpPtr = _tcsrchr (m_pszString, (_TUCHAR) cTermChar);
	if ( lpPtr ) {
		*lpPtr = 0;
	}
}


void YFixedString::Terminate (LPCTSTR lpszTermCharSet)
{
	ASSERTY(m_pszString);
	for ( LPTSTR lpPtr = m_pszString; *lpPtr; lpPtr++ ) {
		if ( _tcschr (lpszTermCharSet, *lpPtr) ) {
			*lpPtr = 0;
			break;
		}
	}
}

void YFixedString::ReverseTerminate (LPCTSTR lpszTermCharSet)
{
	ASSERTY(m_pszString);
	if ( IsEmpty () ) {
		return;
	}
	for ( LPTSTR lpPtr = m_pszString + GetLength () - 1; lpPtr >= m_pszString; lpPtr-- ) {
		if ( _tcschr (lpszTermCharSet, *lpPtr) ) {
			*lpPtr = 0;
			break;
		}
	}
}

int YFixedString::Replace (TCHAR chOld, TCHAR chNew)
{
	ASSERTY(m_pszString);

	int nCount = 0;

	if ( chOld != chNew ) {
		for ( LPTSTR lpPtr = m_pszString; *lpPtr; lpPtr = _tcsinc (lpPtr) ) {
			if ( *lpPtr == chOld ) {
				*lpPtr = chNew;
				++nCount;
			}
		}
	}
	return nCount;
}

int YFixedString::Replace (LPCTSTR lpszOld, LPCTSTR lpszNew)
{
	ASSERTY(m_pszString);

	UINT nSrcLen = SafeStrLen (lpszOld);
	if ( !nSrcLen ) {
		return 0;
	}
	UINT	nDiff;
	UINT	nLen	= GetLength ();
	UINT	nDstLen = SafeStrLen (lpszNew);
	int		nCount	= 0;
	LPTSTR	lpStart	= m_pszString;
	LPTSTR	lpEnd	= m_pszString + nLen;
	LPTSTR	lpTarget;

	if ( nSrcLen == nDstLen ) {
		// very simple case: the resulting string will equal to the original
		while ( (lpTarget = _tcsstr (lpStart, lpszOld)) != NULL ) {
			memcpy (lpTarget, lpszNew, nDstLen * sizeof (TCHAR));
			lpStart = lpTarget + nDstLen;
			++nCount;
		}
	}
	else if ( nSrcLen > nDstLen ) {
		// simple case: the resulting string will be shorter than the original
		nDiff = nSrcLen - nDstLen;
		while ( (lpTarget = _tcsstr (lpStart, lpszOld)) != NULL ) {
			memcpy (lpTarget, lpszNew, nDstLen * sizeof (TCHAR));
			lpStart = lpTarget + nDstLen;
			memmove (lpStart, lpTarget + nSrcLen, (lpEnd - (lpTarget + nSrcLen - 1)) * sizeof (TCHAR));
			lpEnd -= nDiff;
			++nCount;
		}
	}
	else {
		// complicated case: the resulting string will be longer than the original
		LPTSTR lpLast = m_pszString + m_cbSize - 1;
		nDiff = nDstLen - nSrcLen;
		while ( (lpTarget = _tcsstr (lpStart, lpszOld)) != NULL ) {
			if ( (lpTarget + nDstLen) >= lpLast ) {
				// end reached. Substitution string partially copied
				memcpy (lpTarget, lpszNew, ((m_pszString + m_cbSize - 1) - lpTarget) * sizeof (TCHAR));
				m_pszString[m_cbSize - 1] = 0;
				return ++nCount;
			}
			UINT nMove = (lpEnd - lpTarget) - nSrcLen;
			lpStart = lpTarget + nDstLen;
			if ( (lpTarget + nDstLen + nMove) >= lpLast ) {
				// end reached. Substitution string copied. Rest truncated
				nMove = lpLast - lpStart; //lpTarget - nDstLen;
				memmove (lpStart, lpTarget + nSrcLen, nMove * sizeof (TCHAR));
				memcpy (lpTarget, lpszNew, nDstLen * sizeof (TCHAR));
				m_pszString[m_cbSize - 1] = 0;
				lpEnd = lpLast;
				nLen = m_cbSize - 1;
			}
			else {
				// normal operation. shift and insert
				memmove (lpStart, lpTarget + nSrcLen, (nMove + 1) * sizeof (TCHAR));
				memcpy (lpTarget, lpszNew, nDstLen * sizeof (TCHAR));
				lpEnd += nDiff;
			}
			++nCount;
		}
	}
	return nCount;
}

int YFixedString::Remove (TCHAR chRemove)
{
	ASSERTY(m_pszString);

	LPTSTR lpSrc = m_pszString;
	LPTSTR lpDst = m_pszString;

	while ( *lpSrc ) {
		if ( *lpSrc != chRemove ) {
			*lpSrc = *lpDst;
			lpDst = _tcsinc (lpDst);
		}
		lpSrc = _tcsinc (lpSrc);
	}
	*lpDst = 0;

	return lpSrc - lpDst;
}

int YFixedString::Insert (int nIndex, TCHAR ch)
{
	ASSERTY(m_pszString);

	if ( nIndex < 0 ) {
		nIndex = 0;
	}
	UINT nLen = GetLength ();
	if ( nLen < (m_cbSize - 1) ) {
		// append
		if ( (UINT) nIndex >= nLen ) {
			m_pszString[nLen] = ch;
			m_pszString[++nLen] = 0;
			return nLen;
		}
		// shift and insert
		memcpy (m_pszString + nIndex + 1, m_pszString + nIndex, (nLen + 1 - nIndex) * sizeof (TCHAR));
		m_pszString[nIndex] = ch;
		++nLen;
	}
	// doesn't fit;
	return nLen;
}

int YFixedString::Insert (int nIndex, LPCTSTR pstr)
{
	ASSERTY(m_pszString);

	if ( nIndex < 0 ) {
		nIndex = 0;
	}

	UINT	nLen	= GetLength ();
	UINT	nAddLen	= SafeStrLen (pstr);

	if ( (UINT) nIndex > nLen ) {
		nIndex = nLen;
	}

	if ( (nIndex + nAddLen + 1) >= m_cbSize ) {
		// insertion string will reach the end and probably will be truncated
		memcpy (m_pszString + nIndex, pstr, (m_cbSize - nIndex - 1) * sizeof (TCHAR));
		m_pszString[m_cbSize - 1] = 0;
		return m_cbSize - 1;
	}
	if ( (nLen + nAddLen + 1) >= m_cbSize ) {
		// insertion string will fit but the rest will be truncated
		memmove (m_pszString + nIndex + nAddLen, m_pszString + nIndex, (m_cbSize - (nIndex + nAddLen + 1)) * sizeof (TCHAR));
		memcpy (m_pszString + nIndex, pstr, nAddLen * sizeof (TCHAR));
		m_pszString[m_cbSize - 1] = 0;
		return m_cbSize - 1;
	}
	// new string will fit
	memmove (m_pszString + nIndex + nAddLen, m_pszString + nIndex, ((nLen - nIndex) + 1) * sizeof (TCHAR));
	memcpy (m_pszString + nIndex, pstr, nAddLen * sizeof (TCHAR));
	return nLen + 1;
}

int YFixedString::Delete (int nIndex, int nCount /* = 1 */)
{
	ASSERTY(m_pszString);

	if ( nIndex < 0 ) {
		nIndex = 0;
	}

	UINT nLength = GetLength ();
	if ( (nCount > 0) && ((UINT) nIndex < nLength) ) {
		if ( (UINT) (nIndex + nCount) >= nLength ) {
			m_pszString[nIndex] = 0;
			return nIndex;
		}
		memcpy (m_pszString + nIndex, m_pszString + nIndex + nCount, (nLength - nIndex - nCount + 1) * sizeof(TCHAR));
		return nLength - nCount;
	}
	return nLength;
}

int YFixedString::Find(TCHAR ch, int nStart) const
{
	ASSERTY(m_pszString);

	if ( nStart < 0 ) {
		nStart = 0;
	}
	if ( (UINT) nStart >= GetLength () ) {
		return -1;
	}

	LPTSTR lpPtr = _tcschr (m_pszString + nStart, (_TUCHAR) ch);
	return (lpPtr) ? (int) (lpPtr - m_pszString) : (-1);
}

int YFixedString::Find (LPCTSTR lpszSub, int nStart) const
{
	ASSERTY(m_pszString);
	ASSERTY(YlbIsValidString(lpszSub));

	if ( nStart < 0 ) {
		nStart = 0;
	}
	if ( (UINT) nStart >= GetLength () ) {
		return -1;
	}

	LPTSTR lpPtr = _tcsstr (m_pszString + nStart, lpszSub);
	return (lpPtr) ? (int) (lpPtr - m_pszString) : (-1);
}

void YLB_CDECL YFixedString::Format(LPCTSTR lpszFormat, ...)
{
	va_list argList;
	va_start (argList, lpszFormat);
	FormatV (lpszFormat, argList);
	va_end (argList);
}

void YLB_CDECL YFixedString::Format(UINT nFormatID, ...)
{
	YBigString	strFormat;
	VERIFYY(strFormat.LoadString (nFormatID));

	va_list argList;
	va_start (argList, nFormatID);
	FormatV (strFormat, argList);
	va_end (argList);
}

/*=============================================================================
 * DYNAMICALLY ALLOCATED FIXED SYSTEM STRING CLASS IMPLEMENTATION
 *============================================================================*/
BOOL YHeapString::Alloc (UINT cbSize, BOOL bEmpty)
{
	if ( !cbSize ) {
		Free ();
		return TRUE;
	}

	LPTSTR	lpPtr, lpOld = m_pszString;

	if ( !(lpPtr = (LPTSTR) malloc (sizeof (TCHAR) * cbSize)) ) {
		return FALSE;
	}
	m_cbSize	= cbSize;
	m_pszString	= lpPtr;

	if ( lpOld ) {
		_tcsncpy (m_pszString, lpOld, m_cbSize - 1);
		m_pszString[m_cbSize - 1] = 0;
		free (lpOld);
	}
	else if ( bEmpty ) {
		*m_pszString = 0;
	}
	return TRUE;
}

void YHeapString::Free ()
{
	if ( m_pszString ) {
		free (m_pszString);
	}
	m_pszString	= NULL;
	m_cbSize	= 0;
}


/*=============================================================================
 * SYSTEM STRING CLASSES IMPLEMENTATION
 *============================================================================*/
BOOL YComputerName::GetCurrent ()
{
	DWORD	dwLen = GetSize ();
	return ::GetComputerName (m_szData, &dwLen);
}

BOOL YComputerName::FromUNC (LPCTSTR lpszUNC)
{
	ASSERTY(lpszUNC);
	if ( (lpszUNC[0] != _T('\\')) || (lpszUNC[1] != _T('\\')) ) {
		Empty ();
		return FALSE;
	}

	lpszUNC += 2;

	LPCTSTR lpPtr = _tcschr (lpszUNC, _T('\\'));
	if ( lpPtr ) {
		_tcsncpy (m_szData, lpszUNC, min(lpPtr - lpszUNC,(int)GetSize () - 1));
		m_szData[min(lpPtr - lpszUNC,(int)GetSize () - 1)] = 0;
	}
	else {
		_tcsncpy (m_szData, lpszUNC, GetSize () - 1);
		m_szData[GetSize () - 1] = 0;
	}
	return *m_szData != 0;
}

/*=============================================================================
 * MULTISTRING CLASS IMPLEMENTATION
 *============================================================================*/
BOOL YMultiString::Alloc (UINT cbSize, BOOL bEmpty)
{
	if ( cbSize < 2) {
		Free ();
		return TRUE;
	}

	LPTSTR	lpPtr, lpOld	= m_pszString;
	UINT	cbOld			= m_cbSize;

	if ( !(lpPtr = (LPTSTR) malloc (sizeof (TCHAR) * cbSize)) ) {
		return FALSE;
	}
	m_cbSize	= cbSize;
	m_pszString	= lpPtr;

	if ( lpOld ) {
		memcpy (m_pszString, lpOld, min(m_cbSize - 2,cbOld - 2) * sizeof (TCHAR));
		m_pszString[m_cbSize - 2] = 0;
		m_pszString[m_cbSize - 1] = 0;
		free (lpOld);
	}
	else if ( bEmpty ) {
		m_pszString[0] = m_pszString[1] = 0;
	}
	return TRUE;
}

void YMultiString::Free ()
{
	if ( m_pszString ) {
		free (m_pszString);
	}
	m_pszString	= NULL;
	m_cbSize	= 0;
}

#ifndef YLB_ENABLE_INLINE
#include <yFixStr.inl>
#endif

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////