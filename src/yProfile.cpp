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
 * FILENAME		:	yProfile.cpp
 * PURPOSE		:	Implementation of the INI File Class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/
#include "StdInc.hpp"

/*=============================================================================
 * @doc YLIB | yProfile.h
 *============================================================================*/

/*=============================================================================
 * USEFUL MAKROS
 *============================================================================*/
#define CHECK_HELPER(psz,cb) \
	do { \
		if ( !(psz) || !(cb) ) { \
			(psz)	= m_ysHelper.GetBuffer (); \
			(cb)	= m_ysHelper.GetBufferSize (); \
		} \
	} while (0)

#define SAFE_STRING(psz) \
	do { \
		if ( !(psz) ) { \
			(psz) = _T(""); \
		} \
	} while (0)

/*=============================================================================
 * CLASS IMPLEMENTATION
 *============================================================================*/
YProfile::YProfile ()
{
}

YProfile::YProfile (LPCTSTR pszFile, ...)
{
	va_list va;
	va_start (va, pszFile);
	m_ysIniFile.FormatV (pszFile, va);
	va_end (va);
}

YProfile::YProfile (const YProfile &iniSrc)
{
	m_ysIniFile	= iniSrc.m_ysIniFile;
	m_ysSection	= iniSrc.m_ysSection;
}

bool YProfile::Open (LPCTSTR lpszKey)
{
	TCHAR	szDummy[16];

	if ( m_ysIniFile.IsFile () && ::GetPrivateProfileSection (lpszKey, szDummy, _countof(szDummy), m_ysIniFile) ) {
		m_ysSection = lpszKey;
		return true;
	}
	return false;
}

bool YProfile::Create (LPCTSTR lpszKey)
{
	if ( Open (lpszKey) ) {
		return true;
	}
	if ( ::WritePrivateProfileString (lpszKey, _T("$yLibDummyKey$"), _T("$yLibDummyKey$"), m_ysIniFile) ) {
		::WritePrivateProfileString (lpszKey, _T("$yLibDummyKey$"), NULL, m_ysIniFile);
		return true;
	}
	return false;
}

bool YProfile::ValueDelete (LPCTSTR lpszValue) const
{
	if ( IsOpen () ) {
		return ::WritePrivateProfileString (m_ysSection, lpszValue, NULL, m_ysIniFile) != FALSE;
	}
	return false;
}

bool YProfile::SectionDelete (LPCTSTR lpszKey)
{
	if ( SectionExists (lpszKey) ) {
		if ( ::WritePrivateProfileString (lpszKey, NULL, NULL, m_ysIniFile) ) {
			if ( !m_ysSection.CompareNoCase (lpszKey) ) {
				m_ysSection.Empty ();
			}
			return true;
		}
	}
	return false;
}

bool YProfile::ValueExists (LPCTSTR lpszValue) const
{
	if ( IsOpen () ) {
		TCHAR	szDummy[32];
		::GetPrivateProfileString (m_ysSection, lpszValue, _T("$yLibTestValue$"), szDummy, _countof (szDummy), m_ysIniFile);
		return !_tcscmp (szDummy, _T("$yLibTestValue$"));
	}
	return false;
}

bool YProfile::SectionExists (LPCTSTR lpszKey) const
{
	TCHAR	szDummy[16];

	if ( m_ysIniFile.IsFile () && ::GetPrivateProfileSection (lpszKey, szDummy, _countof(szDummy), m_ysIniFile) ) {
		return true;
	}
	return false;
}

bool YProfile::BooleanGet (LPCTSTR lpszValueName, bool bDefault, BOOL bStrict /* = TRUE */) const
{
	if ( !IsOpen () ) {
		return bDefault;
	}
	YString32 ysBuffer;
	if ( !::GetPrivateProfileString (m_ysSection, lpszValueName, _T(""), ysBuffer.GetBuffer (), ysBuffer.GetBufferSize (), m_ysIniFile) ) {
		return bDefault;
	}
	if ( !ysBuffer.CompareNoCase (_T("true")) ) {
		return true;
	}
	else if ( !ysBuffer.CompareNoCase (_T("false")) ) {
		return false;
	}
	else if ( !ysBuffer.CompareNoCase (_T("1")) ) {
		return true;
	}
	else if ( !ysBuffer.CompareNoCase (_T("0")) ) {
		return false;
	}
	else if ( !ysBuffer.CompareNoCase (_T("yes")) ) {
		return true;
	}
	else if ( !ysBuffer.CompareNoCase (_T("no")) ) {
		return false;
	}
	else if ( !bStrict && (_tcsspn (ysBuffer, _T("0123456789")) == ysBuffer.GetLength ()) ) {
		return _ttoi (ysBuffer) != 0;
	}
	return bDefault;
}

long YProfile::NumberGet (LPCTSTR lpszValueName, long lDefault) const
{
	if ( !IsOpen () ) {
		return lDefault;
	}
	YString32 ysBuffer;
	if ( !::GetPrivateProfileString (m_ysSection, lpszValueName, _T(""), ysBuffer.GetBuffer (), ysBuffer.GetBufferSize (), m_ysIniFile) ) {
		return lDefault;
	}
	if ( !_tcsncmp (ysBuffer, _T("0x"), 2) ) {
		LPTSTR lpEnd;
		DWORD dwRet = _tcstoul (ysBuffer, &lpEnd, 16);
		if ( lpEnd && (lpEnd != ysBuffer.GetString () + ysBuffer.GetLength ()) ) {
			return lDefault;
		}
		return (long) dwRet;
	}
	long lMul = 1;
	if ( ysBuffer[0] == _T('-') ) {
		ysBuffer.TrimLeft (_T('-'));
		lMul = -1;
	}
	if ( _tcsspn (ysBuffer, _T("0123456789")) == ysBuffer.GetLength () ) {
		return lMul * _ttol (ysBuffer);
	}
	return lDefault;
}

DWORD YProfile::NumberGet (LPCTSTR lpszValueName, DWORD dwDefault) const
{
	if ( !IsOpen () ) {
		return dwDefault;
	}
	YString32 ysBuffer;
	if ( !::GetPrivateProfileString (m_ysSection, lpszValueName, _T(""), ysBuffer.GetBuffer (), ysBuffer.GetBufferSize (), m_ysIniFile) ) {
		return dwDefault;
	}
	if ( !_tcsncmp (ysBuffer, _T("0x"), 2) ) {
		LPTSTR lpEnd;
		DWORD dwRet = _tcstoul (ysBuffer, &lpEnd, 16);
		if ( lpEnd && (lpEnd != ysBuffer.GetString () + ysBuffer.GetLength ()) ) {
			return dwDefault;
		}
		return dwRet;
	}
	if ( _tcsspn (ysBuffer, _T("0123456789")) == ysBuffer.GetLength () ) {
		LPTSTR lpEnd;
		return _tcstoul (ysBuffer, &lpEnd, 10);
	}

	return dwDefault;
}

LPCTSTR YProfile::StringGet (LPCTSTR lpszValueName, LPTSTR pszBuffer, UINT cbBuffer, LPCTSTR lpszDefault)
{
	CHECK_HELPER(pszBuffer, cbBuffer);
	SAFE_STRING(lpszDefault);

	if ( !IsOpen () ) {
		_tcsncpy (pszBuffer, lpszDefault, cbBuffer);
		pszBuffer[cbBuffer - 1] = 0;
		return pszBuffer;
	}
	::GetPrivateProfileString (m_ysSection, lpszValueName, lpszDefault, pszBuffer, cbBuffer, m_ysIniFile);
	return pszBuffer;
}

LPCTSTR YProfile::StringGet (LPCTSTR lpszValueName, YStringData &ysValue, LPCTSTR lpszDefault)
{
	SAFE_STRING(lpszDefault);
	if ( !IsOpen () ) {
		_tcsncpy (ysValue.GetBuffer (), lpszDefault, ysValue.GetBufferSize ());
		ysValue.GetBuffer ()[ysValue.GetBufferSize () - 1] = 0;
		return ysValue;
	}
	::GetPrivateProfileString (m_ysSection, lpszValueName, lpszDefault, ysValue.GetBuffer (), ysValue.GetBufferSize (), m_ysIniFile);
	return ysValue;
}

bool YProfile::BooleanSet (LPCTSTR lpszValueName, bool bValue, YFormatFlags fFlags) const
{
	LPCTSTR lpPtr;

	switch ( fFlags & (boolTrueFalse|boolYesNo|boolNumeric) ) {
	default:
	case boolTrueFalse:
		lpPtr = (bValue) ? (_T("true")) : (_T("false"));
		break;
	case boolYesNo:
		lpPtr = (bValue) ? (_T("Yes")) : (_T("No"));
		break;
	case boolNumeric:
		lpPtr = (bValue) ? (_T("1")) : (_T("0"));
		break;
	}
	return StringSet (lpszValueName, lpPtr);
}

bool YProfile::NumberSet (LPCTSTR lpszValueName, long lValue, YFormatFlags fFlags) const
{
	YString32 ysBuffer;

	switch ( fFlags & (numberDecimal|numberHexadecimal) ) {
	default:
	case numberDecimal:
		ysBuffer.Format (_T("%d"), lValue);
		break;
	case numberHexadecimal:
		ysBuffer.Format (_T("0x%08x"), lValue);
		break;
	}
	return StringSet (lpszValueName, ysBuffer);
}

bool YProfile::NumberSet (LPCTSTR lpszValueName, DWORD dwValue, YFormatFlags fFlags) const
{
	YString32 ysBuffer;

	switch ( fFlags & (numberDecimal|numberHexadecimal) ) {
	default:
	case numberDecimal:
		ysBuffer.Format (_T("%u"), dwValue);
		break;
	case numberHexadecimal:
		ysBuffer.Format (_T("0x%08x"), dwValue);
		break;
	}
	return StringSet (lpszValueName, ysBuffer);
}

bool YProfile::StringSet (LPCTSTR lpszValueName, LPCTSTR lpszValue) const
{
	if ( IsOpen () ) {
		SAFE_STRING(lpszValue);
		return ::WritePrivateProfileString (m_ysSection, lpszValueName, lpszValue, m_ysIniFile) != FALSE;
	}
	return false;
}

#ifndef YLB_ENABLE_INLINE
#include <yProfile.inl>
#endif

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////