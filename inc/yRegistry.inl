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
 * FILENAME		:	yRegistry.inl
 * PURPOSE		:	Inline members of the registry class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yRegistry.h
 *============================================================================*/
YLB_INLINE YRegistry::~YRegistry ()
{
	Close ();
}

YLB_INLINE void YRegistry::Close ()
{
	if ( m_regKey && m_bAutoClose ) {
		RegCloseKey (m_regKey);
		m_regKey = NULL;
	}
}

YLB_INLINE YRegistry::operator HKEY() const
{
	return INTKEY;
}

YLB_INLINE HKEY YRegistry::GetHandle () const
{
	return INTKEY;
}

YLB_INLINE HKEY YRegistry::GetAnchorHandle () const
{
	return m_regAnchor;
}

// @mfunc	Counts the number of values in the open key
// @rdesc	Number of values in the current key
// @comm	Counts the number of values in an already open registry key.
//
// @xref	<mf YRegistry::GetFirstSectionPosition>, <mf YRegistry::GetLastSectionPosition>,
//			<mf YRegistry::GetNextSection>, <mf YRegistry::GetPrevSection>,
//			<mf YRegistry::ValueExists>
// @key		Configuration Information Functions
YLB_INLINE DWORD YRegistry::ValueGetCount () const
{
	DWORD	dwRetVal;

	if ( !INTKEY ) {
		return 0;
	}
	if ( RegQueryInfoKey (INTKEY, NULL, NULL, NULL, NULL, NULL, NULL, &dwRetVal, NULL, NULL, NULL, NULL) != ERROR_SUCCESS ) {
		return 0;
	}
	return dwRetVal;
}

// @mfunc	Counts the number of subkeys in the open key
// @rdesc	Number of subkeys in the current key
// @comm	Counts the number of subkeys in the open registry key.
//
// @xref	<mf YRegistry::GetFirstValuePosition>, <mf YRegistry::GetLastValuePosition>,
//			<mf YRegistry::GetNextValue>, <mf YRegistry::GetPrevValue>,
//			<mf YRegistry::SectionExists>
// @key		Configuration Information Functions
YLB_INLINE DWORD YRegistry::SectionGetCount () const
{
	DWORD	dwRetVal;

	if ( !INTKEY ) {
		return 0;
	}
	if ( RegQueryInfoKey (INTKEY, NULL, NULL, NULL, &dwRetVal, NULL, NULL, NULL, NULL, NULL, NULL, NULL) != ERROR_SUCCESS ) {
		return 0;
	}
	return dwRetVal;
}

// @mfunc	Returns the position of the first value in the open key
// @rdesc	A <b>ITERATOR<n> value that can be used for iteration or
//			value data retrieval; <NULL> if there are no values in
//			the open registry key.
// @comm	Gets the position of the first value in the open key.
// @xref	<j Registry Iteration Example>,
//			<mf YRegistry::GetLastValuePosition>,
//			<mf YRegistry::GetNextValue>, <mf YRegistry::GetPrevValue>,
//			<mf YRegistry::ValueExists>, <mf YRegistry::ValueGetCount>
// @key		Configuration Information Functions
YLB_INLINE ITERATOR YRegistry::GetFirstValuePosition () const
{
	return (ValueGetCount ()) ? ((ITERATOR) 1) : ((ITERATOR) 0);
}

// @mfunc	Returns the position of the last value in the open key
// @rdesc	A <b>ITERATOR<n> value that can be used for iteration or
//			value data retrieval; <NULL> if there are no values in
//			the open registry key.
// @comm	Gets the position of the last value in the open key.
// @xref	<j Registry Iteration Example>,
//			<mf YRegistry::GetFirstValuePosition>,
//			<mf YRegistry::GetNextValue>, <mf YRegistry::GetPrevValue>,
//			<mf YRegistry::ValueExists>, <mf YRegistry::ValueGetCount>
// @key		Configuration Information Functions
YLB_INLINE ITERATOR YRegistry::GetLastValuePosition () const
{
	return (ITERATOR) ValueGetCount ();
}

// @mfunc	Returns the position of the first subkey in the open key
// @rdesc	A <b>ITERATOR<n> value that can be used for iteration or
//			subkey data retrieval; <NULL> if there are no subkeys in
//			the open registry key.
// @comm	Gets the position of the first subkey in the open key.
// @xref	<j Registry Iteration Example>,
//			<mf YRegistry::GetLastSectionPosition>,
//			<mf YRegistry::GetNextSection>, <mf YRegistry::GetPrevSection>,
//			<mf YRegistry::SectionExists>, <mf YRegistry::SectionGetCount>
// @key		Configuration Information Functions
YLB_INLINE ITERATOR YRegistry::GetFirstSectionPosition ()
{
	return (SectionGetCount ()) ? ((ITERATOR) 1) : ((ITERATOR) 0);
}

// @mfunc	Returns the position of the last subkey in the open key
// @rdesc	A <b>ITERATOR<n> value that can be used for iteration or
//			subkey data retrieval; <NULL> if there are no subkeys in
//			the open registry key.
// @comm	Gets the position of the last subkey in the open key.
// @xref	<j Registry Iteration Example>,
//			<mf YRegistry::GetFirstSectionPosition>,
//			<mf YRegistry::GetNextSection>, <mf YRegistry::GetPrevSection>,
//			<mf YRegistry::SectionExists>, <mf YRegistry::SectionGetCount>
// @key		Configuration Information Functions
YLB_INLINE ITERATOR YRegistry::GetLastSectionPosition ()
{
	return (ITERATOR) SectionGetCount ();
}

YLB_INLINE UINT YRegistry::MultiStringGet (LPCTSTR lpszValueName, LPTSTR pszBuffer /* = NULL */, UINT cbBuffer /* = 0 */) const
{
	UINT uRet = AnyGet (lpszValueName, REG_MULTI_SZ, pszBuffer, cbBuffer * sizeof (TCHAR)) / sizeof (TCHAR);
	if ( !uRet ) {
		uRet = 2;
		if ( pszBuffer ) {
			if ( cbBuffer > 0 ) pszBuffer[0] = 0;
			if ( cbBuffer > 1 ) pszBuffer[1] = 0;
			return min(uRet,cbBuffer);
		}
	}
	return uRet;
}

YLB_INLINE UINT YRegistry::BinaryGet (LPCTSTR lpszValueName, LPVOID pBuffer, UINT cbBuffer) const
{
	return AnyGet (lpszValueName, REG_BINARY, pBuffer, cbBuffer);
}

YLB_INLINE BOOL YRegistry::BooleanSet (LPCTSTR lpszValueName, BOOL bValue) const
{
	return NumberSet (lpszValueName, (DWORD) bValue);
}

YLB_INLINE BOOL YRegistry::NumberSet (LPCTSTR lpszValueName, DWORD dwValue) const
{
	if ( !INTKEY || !lpszValueName || !*lpszValueName ) {
		return FALSE;
	}
	return RegSetValueEx (INTKEY, lpszValueName, 0, REG_DWORD, (LPBYTE) &dwValue, sizeof (DWORD)) == ERROR_SUCCESS;
}

YLB_INLINE BOOL YRegistry::StringSet (LPCTSTR lpszValueName, LPCTSTR lpszValue) const
{
	if ( !INTKEY || !lpszValueName || !*lpszValueName || !lpszValue ) {
		return FALSE;
	}
	return RegSetValueEx (INTKEY, lpszValueName, 0, REG_SZ, (LPBYTE) lpszValue, _tcslen (lpszValue) + sizeof(TCHAR)) == ERROR_SUCCESS;
}

YLB_INLINE BOOL YRegistry::ExpandableStringSet (LPCTSTR lpszValueName, LPCTSTR lpszValue) const
{
	if ( !INTKEY || !lpszValueName || !*lpszValueName || !lpszValue ) {
		return FALSE;
	}
	return RegSetValueEx (INTKEY, lpszValueName, 0, REG_EXPAND_SZ, (LPBYTE) lpszValue, _tcslen (lpszValue) + sizeof(TCHAR)) == ERROR_SUCCESS;
}

YLB_INLINE BOOL YRegistry::AnySet (LPCTSTR lpszValueName, DWORD dwType, LPCVOID pszBuffer, UINT cbBuffer) const
{
	if ( !INTKEY || !lpszValueName || !*lpszValueName || !pszBuffer || !cbBuffer ) {
		return FALSE;
	}
	return RegSetValueEx (INTKEY, lpszValueName, 0, dwType, (LPBYTE) pszBuffer, cbBuffer) == ERROR_SUCCESS;
}

YLB_INLINE BOOL YRegistry::BinarySet (LPCTSTR lpszValueName, LPCVOID pszBuffer, UINT cbBuffer) const
{
	return AnySet (lpszValueName, REG_BINARY, pszBuffer, cbBuffer);
}

//
// EoF
////////