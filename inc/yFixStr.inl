/*=============================================================================
 * This is a part of the yLib Software Development Kit.
 * Copyright (C) 1998-2001 YEAsoft Int'l.
 * All rights reserved.
 *=============================================================================
 * Copyright (c) 1998-2001 YEAsoft Int'l (Leo Moll, Andrea Pennelli).
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
 * FILENAME		:	yFixStr.inl
 * PURPOSE		:	Inline members of the fixed string classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.11  2001/05/17 16:20:23  leopoldo
 * Fixed the misunderstanding between YStringData::GetSize and YStringData::GetBufferSize
 *
 * Revision 1.10  2001/05/08 17:10:30  leopoldo
 * Added the new methods IsRoot, Fill, BufferToHex, HexToBuffer
 *
 * Revision 1.9  2001/05/06 18:28:12  leopoldo
 * Improved YPathString::GetFileExtension
 *
 * Revision 1.8  2001/04/25 12:28:01  leopoldo
 * Added IsAbsolute, IsRelative and IsUNC to YPathString
 *
 * Revision 1.7  2001/03/23 12:17:55  leopoldo
 * Added missing compare helpers
 *
 * Revision 1.6  2000/08/23 10:12:34  leo
 * Fixed some release build issue
 *
 * Revision 1.5  2000/08/22  16:18:54  leo
 * Added some of the directory operations to YPathString
 *
 * Revision 1.4  2000/08/22  16:01:39  leo
 * Added the transfer methods
 *
 * Revision 1.3  2000/08/22  15:41:08  leo
 * Added more oethods for path strings
 * Updated license
 *
 * Revision 1.2  2000/07/25  09:05:38  leo
 * Added pointer based find methods
 *
 * Revision 1.1  2000/05/26  14:03:09  leo
 * Initial revision
 *
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

YLB_INLINE UINT YStringData::GetBufferSize () const
{
	return m_cbSize;
}

YLB_INLINE UINT YStringData::GetBufferSizeInBytes () const
{
	return m_cbSize * sizeof (TCHAR);
}

YLB_INLINE LPTSTR YStringData::GetBuffer () const
{
	return m_pszString;
}

YLB_INLINE LPCTSTR YStringData::GetString () const
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

YLB_INLINE void YFixedString::Cut (UINT cbLen)
{
	ASSERTY(m_pszString);
	if ( cbLen < m_cbSize ) {
		m_pszString[cbLen] = 0;
	}
}

YLB_INLINE int YFixedString::Find (TCHAR ch) const
{
	LPCTSTR lpPtr = FindPtr (ch);
	return (lpPtr) ? (int) (lpPtr - m_pszString) : (-1);
}

YLB_INLINE int YFixedString::ReverseFind (TCHAR ch) const
{
	LPCTSTR lpPtr = ReverseFindPtr (ch);
	return (lpPtr) ? (int) (lpPtr - m_pszString) : (-1);
}

YLB_INLINE int YFixedString::Find (TCHAR ch, int nStart) const
{
	LPCTSTR lpPtr = FindPtr (ch, nStart);
	return (lpPtr) ? (int) (lpPtr - m_pszString) : (-1);
}

YLB_INLINE int YFixedString::FindOneOf (LPCTSTR lpszCharSet) const
{
	LPCTSTR lpPtr = FindOneOfPtr (lpszCharSet);
	return (lpPtr) ? (int) (lpPtr - m_pszString) : (-1);
}

YLB_INLINE int YFixedString::Find (LPCTSTR lpszSub) const
{
	LPCTSTR lpPtr = FindPtr (lpszSub);
	return (lpPtr) ? (int) (lpPtr - m_pszString) : (-1);
}

YLB_INLINE int YFixedString::Find (LPCTSTR lpszSub, int nStart) const
{
	LPCTSTR lpPtr = FindPtr (lpszSub, nStart);
	return (lpPtr) ? (int) (lpPtr - m_pszString) : (-1);
}

YLB_INLINE LPCTSTR YFixedString::FindPtr (TCHAR ch) const
{
	ASSERTY(m_pszString);
	return _tcschr (m_pszString, (_TUCHAR) ch);
}

YLB_INLINE LPCTSTR YFixedString::ReverseFindPtr (TCHAR ch) const
{
	ASSERTY(m_pszString);
	return _tcsrchr (m_pszString, (_TUCHAR) ch);
}

YLB_INLINE LPCTSTR YFixedString::FindOneOfPtr (LPCTSTR lpszCharSet) const
{
	ASSERTY(m_pszString);
	ASSERTY(YlbIsValidString(lpszCharSet));
	return _tcspbrk (m_pszString, lpszCharSet);
}

YLB_INLINE LPCTSTR YFixedString::FindPtr (LPCTSTR lpszSub) const
{
	ASSERTY(m_pszString);
	ASSERTY(YlbIsValidString(lpszSub));
	return _tcsstr (m_pszString, lpszSub);
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
 * COMPARE HELPERS
 *============================================================================*/
YLB_INLINE bool YLBAPI operator== (const YFixedString& s1, const YFixedString& s2)
{
	return s1.Compare(s2) == 0;
}

YLB_INLINE bool YLBAPI operator== (const YFixedString& s1, LPCTSTR s2)
{
	return s1.Compare(s2) == 0;
}

YLB_INLINE bool YLBAPI operator== (LPCTSTR s1, const YFixedString& s2)
{
	return s2.Compare(s1) == 0;
}

YLB_INLINE bool YLBAPI operator!= (const YFixedString& s1, const YFixedString& s2)
{
	return s1.Compare(s2) != 0;
}

YLB_INLINE bool YLBAPI operator!= (const YFixedString& s1, LPCTSTR s2)
{
	return s1.Compare(s2) != 0;
}

YLB_INLINE bool YLBAPI operator!= (LPCTSTR s1, const YFixedString& s2)
{
	return s2.Compare(s1) != 0;
}

YLB_INLINE bool YLBAPI operator< (const YFixedString& s1, const YFixedString& s2)
{
	return s1.Compare(s2) < 0;
}

YLB_INLINE bool YLBAPI operator< (const YFixedString& s1, LPCTSTR s2)
{
	return s1.Compare(s2) < 0;
}

YLB_INLINE bool YLBAPI operator< (LPCTSTR s1, const YFixedString& s2)
{
	return s2.Compare(s1) > 0;
}

YLB_INLINE bool YLBAPI operator> (const YFixedString& s1, const YFixedString& s2)
{
	return s1.Compare(s2) > 0;
}

YLB_INLINE bool YLBAPI operator> (const YFixedString& s1, LPCTSTR s2)
{
	return s1.Compare(s2) > 0;
}

YLB_INLINE bool YLBAPI operator> (LPCTSTR s1, const YFixedString& s2)
{
	return s2.Compare(s1) < 0;
}

YLB_INLINE bool YLBAPI operator<= (const YFixedString& s1, const YFixedString& s2)
{
	return s1.Compare(s2) <= 0;
}

YLB_INLINE bool YLBAPI operator<= (const YFixedString& s1, LPCTSTR s2)
{
	return s1.Compare(s2) <= 0;
}

YLB_INLINE bool YLBAPI operator<= (LPCTSTR s1, const YFixedString& s2)
{
	return s2.Compare(s1) >= 0;
}

YLB_INLINE bool YLBAPI operator>= (const YFixedString& s1, const YFixedString& s2)
{
	return s1.Compare(s2) >= 0;
}

YLB_INLINE bool YLBAPI operator>= (const YFixedString& s1, LPCTSTR s2)
{
	return s1.Compare(s2) >= 0;
}

YLB_INLINE bool YLBAPI operator>= (LPCTSTR s1, const YFixedString& s2)
{
	return s2.Compare(s1) <= 0;
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
 * SYSTEM STRING CLASSES IMPLEMENTATION
 *============================================================================*/
YLB_INLINE LPCTSTR YPathString::GetFileName () const
{
	LPCTSTR lpRet = _tcsrchr (m_pszString, _T('\\'));
	return (lpRet) ? (lpRet + 1) : (m_pszString);
}

YLB_INLINE LPCTSTR YPathString::GetFileExtension () const
{
	LPCTSTR lpSep = _tcsrchr (m_pszString, _T('\\'));
	LPCTSTR lpExt = _tcsrchr (m_pszString, _T('.'));
	return (lpExt > lpSep) ? (lpExt + 1) : (_T(""));
}

YLB_INLINE BOOL YPathString::IsFile () const
{
	return YFileManager::IsFile (m_pszString);
}

YLB_INLINE BOOL YPathString::IsDir () const
{
	return YFileManager::IsDir (m_pszString);
}

YLB_INLINE BOOL YPathString::IsDirWritable () const
{
	return YFileManager::IsDirWritable (m_pszString);
}

YLB_INLINE BOOL YPathString::IsDirCompressed () const
{
	return YFileManager::IsDirCompressed (m_pszString);
}

YLB_INLINE BOOL YPathString::IsDirEmpty () const
{
	return YFileManager::IsDirEmpty (m_pszString);
}

YLB_INLINE BOOL YPathString::CreateDirectoryTree () const
{
	return YFileManager::CreateDirectoryTree (m_pszString);
}

YLB_INLINE BOOL YPathString::DeleteFiles () const
{
	return YFileManager::DeleteFiles (m_pszString);
}

YLB_INLINE BOOL YPathString::RemoveDir () const
{
	return YFileManager::RemoveDir (m_pszString);
}

YLB_INLINE BOOL YPathString::KillDir () const
{
	return YFileManager::KillDir (m_pszString);
}

YLB_INLINE BOOL YPathString::CompressDir () const
{
	return YFileManager::CompressDir (m_pszString);
}

YLB_INLINE BOOL YPathString::UncompressDir () const
{
	return YFileManager::UncompressDir (m_pszString);
}

YLB_INLINE BOOL YPathString::CompressDirTree () const
{
	return YFileManager::CompressDirTree (m_pszString);
}

YLB_INLINE BOOL YPathString::UncompressDirTree () const
{
	return YFileManager::UncompressDirTree (m_pszString);
}

YLB_INLINE BOOL YPathString::IsAbsolute () const
{
	return _istalpha (m_szData[0]) &&  (m_szData[1] == _T(':')) && (m_szData[2] == _T('\\'));
}

YLB_INLINE BOOL YPathString::IsRelative () const
{
	return !IsAbsolute ();
}

YLB_INLINE BOOL YPathString::IsRoot () const
{
	return (m_szData[0] == _T('\\')) && (m_szData[1] != _T('\\'));
}

YLB_INLINE BOOL YPathString::IsUNC () const
{
	return (m_szData[0] == _T('\\')) && (m_szData[1] == _T('\\'));
}

//
// EoF
////////