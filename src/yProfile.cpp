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
 * Revision 1.3  2002/08/04 15:25:49  leo
 * Updated from sourceforge
 *
 * Revision 1.4  2002/08/04 15:24:28  leopoldo
 * Fixed MultiString load behaviour
 *
 * Revision 1.3  2002/08/04 14:53:13  leopoldo
 * Added new functionality
 *
 * Revision 1.2  2001/09/15 12:41:11  leopoldo
 * Added YProfile::NumberSet and YProfile::NumberGet for 'double' Values
 *
 * Revision 1.1  2001/09/14 16:21:51  leopoldo
 * Initial revision
 *
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

bool YProfile::TestFile () const
{
	if ( m_ysIniFile.IsEmpty () ) {
		return false;
	}
	if ( m_ysIniFile.IsFile () ) {
		return true;
	}
	YPathString ysWinDir;
	::GetWindowsDirectory (ysWinDir.GetBuffer (), ysWinDir.GetBufferSize ());
	ysWinDir.AddFileName (m_ysIniFile);
	return ysWinDir.IsFile () != FALSE;
}

bool YProfile::SetFileName (LPCTSTR pszFile, ...)
{
	va_list va;
	va_start (va, pszFile);
	m_ysIniFile.FormatV (pszFile, va);
	va_end (va);
	return !m_ysIniFile.IsEmpty ();
}

bool YProfile::Open (LPCTSTR lpszKey)
{
	TCHAR	szDummy[16];

	if ( TestFile () && ::GetPrivateProfileSection (lpszKey, szDummy, _countof(szDummy), m_ysIniFile) ) {
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

	if ( TestFile () && ::GetPrivateProfileSection (lpszKey, szDummy, _countof(szDummy), m_ysIniFile) ) {
		return true;
	}
	return false;
}

bool YProfile::GetSectionBuffer ()
{
	DWORD dwSize;

	if ( !m_ysSecEnum.GetBuffer () && !m_ysSecEnum.Alloc (16384) ) {
		return false;
	}
	while ( true ) {
		if ( !(dwSize = ::GetPrivateProfileSectionNames (m_ysSecEnum.GetBuffer (), m_ysSecEnum.GetBufferSize (), m_ysIniFile)) ) {
			m_ysSecEnum.Empty (TRUE);
			return false;
		}
		if ( dwSize < (m_ysSecEnum.GetBufferSize () - 2) ) {
			break;
		}
		if ( !m_ysSecEnum.Alloc (m_ysSecEnum.GetBufferSize () * 2) ) {
			m_ysSecEnum.Empty (TRUE);
			return false;
		}
	};
	m_ysSecEnum.SetContentSize (dwSize + 1);
	return true;
}

LPCTSTR YProfile::GetNextSection (ITERATOR &rPosition, LPTSTR pszBuffer, UINT cbBuffer)
{
	CHECK_HELPER(pszBuffer, cbBuffer);

	LPCTSTR lpPtr = m_ysSecEnum.GetNext (rPosition);
	if ( !lpPtr ) {
		return NULL;
	}
	_tcsncpy (pszBuffer, lpPtr, cbBuffer);
	pszBuffer[cbBuffer - 1] = 0;
	return pszBuffer;
}

LPCTSTR YProfile::GetPrevSection (ITERATOR &rPosition, LPTSTR pszBuffer, UINT cbBuffer)
{
	CHECK_HELPER(pszBuffer, cbBuffer);

	LPCTSTR lpPtr = m_ysSecEnum.GetPrev (rPosition);
	if ( !lpPtr ) {
		return NULL;
	}
	_tcsncpy (pszBuffer, lpPtr, cbBuffer);
	pszBuffer[cbBuffer - 1] = 0;
	return pszBuffer;
}

bool YProfile::GetValueBuffer ()
{
	if ( !IsOpen () ) {
		return false;
	}

	DWORD dwSize;

	if ( !m_ysValEnum.GetBuffer () && !m_ysValEnum.Alloc (16384) ) {
		return false;
	}
	while ( true ) {
		if ( !(dwSize = ::GetPrivateProfileSection (m_ysSection, m_ysValEnum.GetBuffer (), m_ysValEnum.GetBufferSize (), m_ysIniFile)) ) {
			m_ysValEnum.Empty (TRUE);
			return false;
		}
		if ( dwSize < (m_ysValEnum.GetBufferSize () - 2) ) {
			break;
		}
		if ( !m_ysValEnum.Alloc (m_ysValEnum.GetBufferSize () * 2) ) {
			m_ysValEnum.Empty (TRUE);
			return false;
		}
	};
	m_ysValEnum.SetContentSize (dwSize + 1);
	return true;
}

LPCTSTR YProfile::GetValue (LPCTSTR lpszValuePair, LPTSTR pszBuffer, UINT cbBuffer, LPDWORD pdwType, LPBYTE pbData, LPDWORD pdwDataLen) const
{
	CHECK_HELPER(pszBuffer, cbBuffer);

	if ( !lpszValuePair ) {
		return NULL;
	}

	_tcsncpy (pszBuffer, lpszValuePair, cbBuffer);
	pszBuffer[cbBuffer - 1] = 0;

	LPTSTR lpPtr = _tcschr (pszBuffer, _T('='));
	if ( lpPtr ) {
		*lpPtr = 0;
	}

	if ( !(lpPtr = _tcschr (lpszValuePair, _T('='))) ) {
		// snh
		if ( pdwType ) {
			*pdwType = REG_NONE;
		}
		return pszBuffer;
	}

	DWORD	dwType	= REG_NONE;
	DWORD	dwValue	= 0;

	if ( pdwType || (pbData && pdwDataLen) ) {
		++lpPtr;

		LPTSTR lpEnd;

		if ( (lpPtr[0] == _T('0')) && (lpPtr[1] == _T('x')) ) {
			// hex number ?
			dwValue = _tcstoul (lpPtr + 2, &lpEnd, 16);
			if ( (errno == 0) && (!lpEnd || !*lpEnd) ) {
				dwType = REG_DWORD;
			}
		}
		if ( (dwType == REG_NONE) && *lpPtr ) {
			// decimal number?
			dwValue = _tcstoul (lpPtr, &lpEnd, 10);
			if ( (errno == 0) && (!lpEnd || !*lpEnd) ) {
				dwType = REG_DWORD;
			}
		}
		if ( dwType == REG_NONE ) {
			// string!
			dwType = REG_SZ;
		}
	}

	if ( pdwType ) {
		*pdwType = dwType;
	}
	if ( pbData && pdwDataLen ) {
		if ( dwType == REG_SZ ) {
			_tcsncpy ((LPTSTR) pbData, lpPtr, *pdwDataLen / sizeof (TCHAR));
			((LPTSTR)pbData)[(*pdwDataLen/sizeof (TCHAR)) - 1] = 0;
		}
		else {
			*((LPDWORD)pbData) = dwValue;
		}
	}

	return pszBuffer;
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

double YProfile::NumberGet (LPCTSTR lpszValueName, double dDefault) const
{
	if ( !IsOpen () ) {
		return dDefault;
	}
	YString32 ysBuffer;
	if ( !::GetPrivateProfileString (m_ysSection, lpszValueName, _T(""), ysBuffer.GetBuffer (), ysBuffer.GetBufferSize (), m_ysIniFile) ) {
		return dDefault;
	}
	LPTSTR lpEnd;
	double dRet = _tcstod (ysBuffer, &lpEnd);
	if ( lpEnd && (lpEnd != ysBuffer.GetString () + ysBuffer.GetLength ()) ) {
		return dDefault;
	}
	return dRet;
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

bool YProfile::NumberSet (LPCTSTR lpszValueName, double dValue) const
{
	YString32 ysBuffer;
	ysBuffer.Format (_T("%f"), dValue);
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