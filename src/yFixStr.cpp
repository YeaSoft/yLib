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
 * FILENAME		:	yFixStr.cpp
 * PURPOSE		:	Implementation of the fixed string classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.10  2000/08/24 16:57:02  leo
 * Fixed error in Right
 * Corrected length adjustment in Assign(LPCTSTR, UINT)
 *
 * Revision 1.9  2000/08/23  14:38:24  leo
 * Fixed a typo
 *
 * Revision 1.8  2000/08/23  10:12:22  leo
 * Fixed some release build issue
 *
 * Revision 1.7  2000/08/22  16:18:51  leo
 * Added some of the directory operations to YPathString
 *
 * Revision 1.6  2000/08/22  16:01:43  leo
 * Added the transfer methods
 *
 * Revision 1.5  2000/08/22  15:41:01  leo
 * Added more oethods for path strings
 * Updated license
 *
 * Revision 1.4  2000/07/25  09:06:07  leo
 * Added pointer based find methods
 *
 * Revision 1.3  2000/07/05  13:46:34  leo
 * Added the YUserName class
 *
 * Revision 1.2  2000/07/05  13:30:38  leo
 * Added the "TerminateAfter" methods
 *
 * Revision 1.1  2000/05/26  14:04:59  leo
 * Initial revision
 *
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
void YFixedString::Copy (LPTSTR pszDest, UINT cbSize)
{
	ASSERTY(m_pszString && pszDest);
	if ( cbSize ) {
		_tcsncpy (pszDest, m_pszString, cbSize - 1);
		pszDest[cbSize - 1] = 0;
	}
}

#ifdef _UNICODE

void YFixedString::Copy (LPSTR pszDest, UINT cbSize)
{
	ASSERTY(pszDest);
	_ywcstombsz (pszDest, m_pszString, cbSize);
}

#else

void YFixedString::Copy (LPWSTR pszDest, UINT cbSize)
{
	ASSERTY(pszDest);
	_ymbstowcsz (pszDest, m_pszString, cbSize);
}

#endif

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
		if ( lpsz != m_pszString ) {
			// not self assigned
			ASSERTY(YlbIsValidString(lpsz));
			_tcsncpy (m_pszString, lpsz, m_cbSize - 1);
			m_pszString[m_cbSize - 1] = 0;
		}
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
	nCount = min(nCount+1,m_cbSize);
	if ( lpsz && nCount ) {
		--nCount;
		if ( lpsz != m_pszString ) {
			// not self assigned
			_tcsncpy (m_pszString, lpsz, nCount);
		}
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
	dest.Assign (m_pszString + nLength - nCount, nCount);
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

void YFixedString::TerminateAfter (TCHAR cTermChar)
{
	ASSERTY(m_pszString);
	LPTSTR lpPtr = _tcschr (m_pszString, (_TUCHAR) cTermChar);
	if ( lpPtr ) {
		lpPtr[1] = 0;
	}
}

void YFixedString::ReverseTerminateAfter (TCHAR cTermChar)
{
	ASSERTY(m_pszString);
	LPTSTR lpPtr = _tcsrchr (m_pszString, (_TUCHAR) cTermChar);
	if ( lpPtr ) {
		lpPtr[1] = 0;
	}
}


void YFixedString::TerminateAfter (LPCTSTR lpszTermCharSet)
{
	ASSERTY(m_pszString);
	for ( LPTSTR lpPtr = m_pszString; *lpPtr; lpPtr++ ) {
		if ( _tcschr (lpszTermCharSet, *lpPtr) ) {
			lpPtr[1] = 0;
			break;
		}
	}
}

void YFixedString::ReverseTerminateAfter (LPCTSTR lpszTermCharSet)
{
	ASSERTY(m_pszString);
	if ( IsEmpty () ) {
		return;
	}
	for ( LPTSTR lpPtr = m_pszString + GetLength () - 1; lpPtr >= m_pszString; lpPtr-- ) {
		if ( _tcschr (lpszTermCharSet, *lpPtr) ) {
			lpPtr[1] = 0;
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

LPCTSTR YFixedString::FindPtr (TCHAR ch, int nStart) const
{
	ASSERTY(m_pszString);

	if ( nStart < 0 ) {
		nStart = 0;
	}
	if ( (UINT) nStart >= GetLength () ) {
		return NULL;
	}

	return _tcschr (m_pszString + nStart, (_TUCHAR) ch);
}

LPCTSTR YFixedString::FindPtr (LPCTSTR lpszSub, int nStart) const
{
	ASSERTY(m_pszString);
	ASSERTY(YlbIsValidString(lpszSub));

	if ( nStart < 0 ) {
		nStart = 0;
	}
	if ( (UINT) nStart >= GetLength () ) {
		return NULL;
	}

	return _tcsstr (m_pszString + nStart, lpszSub);
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
void YPathString::AddFileName (LPCTSTR pszFileName)
{
	if ( pszFileName && *pszFileName ) {
		UINT nLength = GetLength ();
		if ( nLength && (m_pszString[nLength - 1] != _T('\\')) ) {
			Concat (_T('\\'));
		}
		Concat (pszFileName);
	}
}

void YPathString::AddFileExtension (LPCTSTR pszFileExtension)
{
	if ( pszFileExtension && *pszFileExtension ) {
		UINT nLength = GetLength ();
		if ( !nLength || (m_pszString[nLength - 1] != _T('.')) ) {
			Concat (_T('.'));
		}
		Concat (pszFileExtension);
	}
}

void YPathString::SubstFileName (LPCTSTR pszFileName)
{
	ASSERTY(pszFileName);
	ReverseTerminateAfter (_T('\\'));
	if ( pszFileName && *pszFileName ) {
		Concat (pszFileName);
	}
}

void YPathString::SubstFileExtension (LPCTSTR pszFileExtension)
{
	StripExtension ();
	if ( pszFileExtension && *pszFileExtension ) {
		Concat (_T('.'));
		Concat (pszFileExtension);
	}
}

void YPathString::StripFileName (BOOL bToValidPath /* = FALSE */)
{
	ReverseTerminateAfter (_T('\\'));
	if ( !*m_pszString && bToValidPath ) {
		Assign (_T(".\\"));
	}
}

void YPathString::AppendBackslash (BOOL bToValidPath /* = FALSE */)
{
	if ( !*m_pszString && bToValidPath ) {
		Assign (_T(".\\"));
		return;
	}
	UINT nLength = GetLength ();
	if ( nLength && (m_pszString[nLength - 1] != _T('\\')) ) {
		Concat (_T('\\'));
	}
}

void YPathString::RemoveBackslash ()
{
	UINT nLength = GetLength ();
	if ( nLength && (m_pszString[nLength - 1] == _T('\\')) ) {
		m_pszString[nLength - 1] = 0;
	}
}

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

BOOL YUserName::GetCurrent ()
{
	DWORD	dwLen = GetSize ();
	return ::GetUserName (m_szData, &dwLen);
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