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
 * FILENAME		:	yRegistry.cpp
 * PURPOSE		:	Implementation of the registry class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.4  2001/09/14 16:22:41  leopoldo
 * Made string default handling more typical
 *
 * Revision 1.3  2001/05/24 15:20:43  leopoldo
 * Added support for YStringData and YMultiString
 *
 * Revision 1.2  2000/09/04 12:07:43  leopoldo
 * Updated license to zlib/libpng
 *
 * Revision 1.1  2000/05/26 14:05:08  leo
 * Initial revision
 *
 *============================================================================*/

#include "StdInc.hpp"

/*=============================================================================
 * USEFUL MAKROS
 *============================================================================*/
#define CHECK_HELPER(psz,cb) \
	do { \
		if ( !(psz) || !(cb) ) { \
			(psz)	= m_szHelpBuffer; \
			(cb)	= _countof(m_szHelpBuffer); \
		} \
	} while (0)

#define SAFE_STRING(psz) \
	do { \
		if ( !(psz) ) { \
			(psz) = _T(""); \
		} \
	} while (0)

/*=============================================================================
 * @doc YLIB | yRegistry.h
 *============================================================================*/
// @topic Registry Iteration Example |
//		The following code demonstrates how to use some methods from
//		<c YRegistry> to iterate through a registry tree. The example
//		walks through the "Services" section and enumerates all installed
//		services of an NT machine and shows their readable name (if
//		present. Obviously it is stupid to read the "DisplayName" value
//		by iterating all values of the registry key, but in our case it's
//		very useful for demonstrating the iteration methods.
//
// @ex Iteration Example |
//
// YRegistry reg;
// if ( reg.Open ("SYSTEM\\CurrentControlSet\\Services") ) {
//     for ( ITERATOR pos = reg.GetFirstSectionPosition (); pos; /*TUNIX*/ ) {
//         LPCTSTR lpStr = reg.GetNextSection (pos);
//         if ( lpStr ) {
//             _tprintf ("Service: %s\n", lpStr);
//             YRegistry regSvc(reg.GetHandle ());
//             if ( regSvc.Open (lpStr) ) {
//                 // this strange mode to read the display name key is intended
//                 // only for demonstration purposes...
//                 for ( ITERATOR pos = regSvc.GetFirstValuePosition (); pos; /*TUNIX*/ ) {
//                     TCHAR   szVal[128];
//                     DWORD   dwVal = sizeof(szVal); // This is correct also for UNICODE!
//                     DWORD   dwType;
//                     LPCTSTR lpValName = regSvc.GetNextValue (
//                         pos,
//                         NULL,
//                         0,
//                         &dwType,
//                         (LPBYTE) szVal,
//                         &dwVal
//                     );
//                     if ( lpValName && (dwType == REG_SZ) && !_tcsicmp (lpValName, "DisplayName") ) {
//                         _tprintf ("     %s\n", szVal);
//                         break;
//                     }
//                 }
//                 if ( !pos ) {
//                     // "DisplayName" not found
//                     _tprintf ("     <no display name>\n");
//                 }
//             }
//         }
//     }
// }
//
// @xref <c YRegistry>

// @topic Understanding YRegistry handle inheritance  |
//		Since there is no exact way to duplicate a registry handle, it is
//		very problematic to implement the copy constructor in a manner that
//		creates a real persistent copy of the originating object.
//
//		If you create a <b>HREG<n> handle and assign it to another variable
//		of the same type, you will be able to call the registry functions
//		passing either the first or the second of this variables, but if you
//		close (with <b>RegCloseKey<n>) one of these handles, also the value
//		of the second handle is not valid any more.
//
//		<c YRegistry> objects work in a similar manner but behave a little
//		different. If you create a copy of a <c YRegistry> object by
//		assigning it, the copy will behave exactly like the original, but
//		if you call the <mf YRegistry::Close> method either by going out
//		of scope or by calling <mf YRegistry::Open> or <mf YRegistry::Create>,
//		the registry handle is NOT really closed.
//		
//		The <mf YRegistry::Close> method works only on <c YRegistry> objects
//		that have been explicitely initialized by a call to <mf YRegistry::Open>
//		or <mf YRegistry::Create>.
//
//		But remember: You can only use copies of an original <c YRegistry>
//		object as long as the original object is not closed either by a call
//		to <mf YRegistry::Close>, <mf YRegistry::Open>, <mf YRegistry::Create>
//		or it goes out of scope.
//
//		The principal difference between an <b>HKEY<n> and a <c YRegistry>
//		object is located in the fact that a <c YRegistry> is not only
//		a handle to a registry hive but stores also the parent handle
//		(called <i>Anchor<n>). This is a very useful concept, since there
//		is no registry handle that can be created from scratch. Every handle
//		is created upon other handles. The original "ever-existing" handles
//		are HKEY_LOCAL_MACHINE, HKEY_CURRENT_USER and some others.
//
//		Every <c YRegistry> object is always initialized with a anchor handle.
//		The default constructor initialized the anchor handle to HKEY_LOCAL_MACHINE
//		if not specified otherwise.
//
//		All <c YRegistry> methods work either on the anchor handle or on the
//		open subkey handle, if specified or explicitely opened.
//
//		The validity of the anchor handle is only needed if no call to
//		<mf YRegistry::Open> or <mf YRegistry::Create> is performed and
//		the object must work on the anchor handle or if a call to
//		<mf YRegistry::Open> or <mf YRegistry::Create> must be performed.
//		After calling this methods, the anchor handle can be invalidated.
//
//		These are the four assignment methods for <c YRegistry>:
//
//		<ul>The default constructor. This constructor initializes a 
//		<c YRegistry> object to an anchor handle of HKEY_LOCAL_MACHINE.
//		It's possible to specify an other anchor handle of type <b>HKEY<n>
//		simply by assigning it during the object declaration or by passing
//		it as a parameter to the object variable.
//
//		<ul>The copy constructor. This constructor creates a copy of the
//		original object but remembers that it is a copy. A call to
//		<mf YRegistry::Close> will NOT really destroy the handle. Only the
//		original object can close and destroy the handle.
//
//		<ul>The <b>HKEY<n> assignment operator. It works similar to the
//		default constructor but closes a possibly open subkey.
//
//		<ul>The <c YRegistry> assignment operator. It works similar to the
//		copy constructor but closes a possibly open subkey.
//
//		<plain><nl>See the following code examples to understand how handles are
//		treated:
//
// @ex Many constructions and assignments: | 
// YRegistry regBase; // This is initialized to HKEY_LOCAL_MACHINE as anchor
// if ( regBase.Open ("SOFTWARE") ) {
//     // regBase is now open on HKLM\SOFTWARE
//     YRegistry regSoftware = reg;
//     // regSoftware is a copy of regBase but will only be valid
//     // if regBase is not out of scope, closed or reopened....
//     YRegistry regCurrentControl = regBase.GetHandle ();
//     // regCurrentControl has now the anchor set to HKLM\SOFTWARE
//     // This is only valid if regBase is valid
//     if ( regCurrentControl.Open ("CurrentControlSet") ) {
//         // regCurrentControl is now open on HKLM\SOFTWARE\CurrentControlSet
//         regBase = HKEY_CURRENT_USER;
//         // regBase is closed and the anchor will be set to HKEY_CURRENT_USER
//         // This means that regSoftware is not valid any more and that
//         // the anchor of regCurrentControl is invalid. This doesn't matter
//         // until regCurrentControl is not closed and the opened on
//         // another key:
//         if ( regCurrentControl.Open ("Kikki") ) {
//             // will never be reached, since the anchor is not valid...
//         }
//         else {
//             regCurrentControl = HKEY_LOCAL_MACHINE;
//             if ( regCurrentControl.Create ("SOFTWARE\\Kikki") ) {
//                 // this will work....
//         ...
//
// @xref <c YRegistry>

// @mfunc	Constructs a <c YRegistry> object
// @parm	const HKEY | hAnchor = HKEY_LOCAL_MACHINE | Handle to a registry
//				key used as anchor for all subsequent operations
// @parm	const YRegistry & | regSrc | reference to another <c YRegistry>
//				object to use as original for the copy
// @syntax	<b>YRegistry::YRegistry (const HKEY<n> hAnchor<b> = HKEY_LOCAL_MACHINE)<n>
// @syntax	<b>YRegistry::YRegistry (const YRegistry &<n>regSrc<b>)<n>
// @comm	Constructs a <c YRegistry> object. The use of the copy constructor
//				constructs a object with a slightly different behaviour. Please
//				refer to the article "<j Understanding YRegistry handle inheritance>"
//				for further information about this topic.
// @xref	<j Understanding YRegistry handle inheritance>, <c YRegistry>
YRegistry::YRegistry (const HKEY hAnchor)
{
	m_regAnchor		= hAnchor;
	m_regKey		= NULL;
	m_bAutoClose	= FALSE;
}

YRegistry::YRegistry (const YRegistry &regSrc)
{
	m_regAnchor		= regSrc.m_regAnchor;
	m_regKey		= regSrc.m_regKey;
	m_bAutoClose	= FALSE;
}

YRegistry& YRegistry::operator= (const HKEY hAnchor)
{
	Close ();
	m_regAnchor		= hAnchor;
	m_regKey		= NULL;
	m_bAutoClose	= FALSE;
	return *this;
}

// @mfunc	Assignment operators
YRegistry& YRegistry::operator= (const YRegistry &regSrc)
{
	Close ();
	m_regAnchor		= regSrc.m_regAnchor;
	m_regKey		= regSrc.m_regKey;
	m_bAutoClose	= FALSE;
	return *this;
}

BOOL YRegistry::Open (LPCTSTR lpszKey, REGSAM samDesired /* = KEY_ALL_ACCESS */)
{
	if ( !lpszKey || !*lpszKey ) {
		return FALSE;
	}
	HKEY	hKeyMom;
	if ( RegOpenKeyEx (m_regAnchor, lpszKey, 0, samDesired, &hKeyMom) != ERROR_SUCCESS ) {
		return FALSE;
	}
	if ( m_regKey ) {
		Close ();
	}
	m_regKey		= hKeyMom;
	m_bAutoClose	= TRUE;
	return TRUE;
}

BOOL YRegistry::Create (LPCTSTR lpszKey, LPTSTR lpszClass /* = TEXT("") */, REGSAM samDesired /* = KEY_ALL_ACCESS */, LPSECURITY_ATTRIBUTES lpSecurityAttributes /* = NULL */, DWORD dwOptions /* = REG_OPTION_NON_VOLATILE */)
{
	DWORD dwDispo;

	if ( !lpszKey || !*lpszKey ) {
		return FALSE;
	}
	HKEY	hKeyMom;
	if ( RegCreateKeyEx (m_regAnchor, lpszKey, 0, lpszClass, dwOptions, samDesired, lpSecurityAttributes, &hKeyMom, &dwDispo) != ERROR_SUCCESS ) {
		return FALSE;
	}
	if ( m_regKey ) {
		Close ();
	}
	m_regKey		= hKeyMom;
	m_bAutoClose	= TRUE;
	return TRUE;
}

BOOL YRegistry::Connect (LPCTSTR lpszComputer, const HKEY hAnchor /* = HKEY_LOCAL_MACHINE */)
{
	if ( !lpszComputer || !*lpszComputer ) {
		return FALSE;
	}
	HKEY	hKeyMom;

	if ( ::RegConnectRegistry (lpszComputer, hAnchor, &hKeyMom) != ERROR_SUCCESS ) {
		return FALSE;
	}

	if ( m_regKey ) {
		Close ();
	}
	m_regKey		= hKeyMom;
	m_bAutoClose	= TRUE;
	return TRUE;
}


// @mfunc	Deletes a value
// @rdesc	<TRUE> on success, <FALSE> on failure
// @comm	Deletes a value from an open subkey.
//
// @xref	<mf YRegistry::SectionDelete>
// @key		Configuration Delete Functions
BOOL YRegistry::ValueDelete (LPCTSTR lpszValue) const
{
	if ( !INTKEY || !lpszValue || !*lpszValue ) {
		return FALSE;
	}
	return RegDeleteValue (INTKEY, lpszValue) == ERROR_SUCCESS;
}

// @mfunc	Deletes an entire subkey of an open subkey
// @rdesc	<TRUE> on success, <FALSE> on failure
// @comm	Deletes a subkey of an open registry key, including all
//				of its values and subkeys.
// @xref	<mf YRegistry::ValueDelete>
// @key		Configuration Delete Functions
BOOL YRegistry::SectionDelete (LPCTSTR lpszKey) const
{
	TCHAR		szSubKey[MAX_PATH];
	DWORD		dwSize;
	FILETIME	ft;

	if ( !INTKEY || !lpszKey || !*lpszKey ) {
		return FALSE;
	}
	YRegistry reg(INTKEY);
	if ( !reg.Open (lpszKey) ) {
		return FALSE;
	}
	dwSize = _countof (szSubKey);
	while ( RegEnumKeyEx (reg, 0, szSubKey, &dwSize, NULL, NULL, NULL, &ft) == ERROR_SUCCESS ) {
		if ( !reg.SectionDelete (szSubKey) ) {
			reg.Close ();
			return FALSE;
		}
		dwSize = _countof (szSubKey);
	}
	reg.Close ();
	return RegDeleteKey (INTKEY, lpszKey) == ERROR_SUCCESS;
}

BOOL YRegistry::ValueExists (LPCTSTR lpszValue, DWORD dwType /* = REG_ANY */) const
{
	DWORD dwTypeFound;
	if ( !INTKEY || !lpszValue || !*lpszValue ) {
		return FALSE;
	}
	if ( RegQueryValueEx (INTKEY, lpszValue, NULL, &dwTypeFound, NULL, NULL) != ERROR_SUCCESS ) {
		// does not exists.
		return FALSE;
	}
	return (dwType == REG_ANY) ? (TRUE) : (dwType == dwTypeFound);
}

BOOL YRegistry::SectionExists (LPCTSTR lpszKey) const
{
	if ( !INTKEY || !lpszKey || !*lpszKey ) {
		return FALSE;
	}
	YRegistry reg(INTKEY);
	return reg.Open (lpszKey);	// will be closed by destructor
}

// @mfunc	Gets the next value name for iterating
// @parm	ITERATOR & | rPosition | A reference to a <b>ITERATOR<n> value returned
//				by a previous <mf YRegistry::GetNextValue>, <mf YRegistry::GetPrevValue>,
//				<mf YRegistry::GetFirstValuePosition>, <mf YRegistry::GetLastValuePosition>
//				or other member function call.
// @parm	LPTSTR | pszBuffer = NULL | Points to the buffer that is to
//				receive the copied string of the value name. This value
//				can also be <NULL>.
// @parm	UINT | cbBuffer = 0 | Specifies the maximum number of characters
//				to be copied to the buffer. If the string is longer than the
//				number of characters specified in <p cbBuffer>, it is truncated.
// @parm	LPDWORD | pdwType = NULL | Pointer to a variable of type <i>DWORD<n>
//				that will receive the type of the value, if found. This
//				value can also be <NULL> if not needed. The following values
//				can be returned in <p pdwType>:
//				@flag REG_BINARY |		Binary data in any form
//				@flag REG_DWORD |		A 32-bit number
//				@flag REG_EXPAND_SZ |	A null-terminated string that contains
//										unexpanded references to environment
//										variables (for example, "%PATH%").
//				@flag REG_MULTI_SZ |	An array of null-terminated strings,
//										terminated by two null characters.
//				@flag REG_SZ |			A null-terminated string.
// @parm	LPBYTE | pbData = NULL | Pointer to a buffer that receives the
//				data for the value entry. This parameter can be <NULL> if
//				the data is not required.
// @parm	LPDWORD | pdwDataLen = 0 | Pointer to a variable that specifies
//				the size, in bytes, of the buffer pointed to by the <p pbData>
//				parameter. When the function returns, the variable pointed to
//				by the <p pdwDataLen> parameter contains the number of bytes
//				stored in the buffer. This parameter can be <NULL>, only if
//				<p pbData> is <NULL>.
// @rdesc	If the function was successful, the return value is a pointer to
//				the name of the retrieved value, otherwise it is <NULL>.
//				If either <p pszBuffer> or <p cbBuffer> were <NULL>, an
//				internal helper buffer of 256 characters will be used for
//				returning the value name. <b><red>WARNING:<n><n> althought useful
//				in most cases, using the internal help buffer is <b>NOT<n>
//				thread safe.
// @comm	Gets the value data identified by <p rPosition>, then sets
//				<p rPosition> to the <b>ITERATOR<n> value of the next
//				value in the open key. You can use <mf YRegistry::GetNextValue>
//				in a forward iteration loop if you establish the initial
//				position with a call to <mf YRegistry::GetFirstValuePosition>.
//
//				You must ensure that your <b>ITERATOR<n> value represents a
//				valid position in the list. If it is invalid, then the function
//				returns <NULL>.
//
//				If the retrieved value is the last in the open key, then the
//				new value of <p rPosition> is set to <NULL>.
// @xref	<j Registry Iteration Example>,
//			<mf YRegistry::GetFirstValuePosition>, <mf YRegistry::GetLastValuePosition>,
//			<mf YRegistry::GetPrevValue>,
//			<mf YRegistry::ValueExists>, <mf YRegistry::ValueGetCount>
// @key		Configuration Information Functions
LPCTSTR YRegistry::GetNextValue (ITERATOR &pos, LPTSTR pszBuffer, UINT cbBuffer, LPDWORD pdwType, LPBYTE pbData, LPDWORD pdwDataLen)
{
	if ( !INTKEY || !pos ) {
		return NULL;
	}
	CHECK_HELPER(pszBuffer,cbBuffer);
	DWORD dwcbBuffer = cbBuffer;
	if ( RegEnumValue (INTKEY, (DWORD) pos - 1, pszBuffer, &dwcbBuffer, NULL, pdwType, pbData, pdwDataLen) != ERROR_SUCCESS ) {
		pos = NULL;
		return NULL;
	}
	if ( ++pos > GetLastValuePosition () ) {
		pos = NULL;
	}
	return pszBuffer;
}

// @mfunc	Gets the previous value name for iterating
// @parm	ITERATOR & | rPosition | A reference to a <b>ITERATOR<n> value returned
//				by a previous <mf YRegistry::GetPrevValue>, <mf YRegistry::GetNextValue>,
//				<mf YRegistry::GetLastValuePosition>, <mf YRegistry::GetFirstValuePosition>
//				or other member function call.
// @parm	LPTSTR | pszBuffer = NULL | Points to the buffer that is to
//				receive the copied string of the value name. This value
//				can also be <NULL>.
// @parm	UINT | cbBuffer = 0 | Specifies the maximum number of characters
//				to be copied to the buffer. If the string is longer than the
//				number of characters specified in <p cbBuffer>, it is truncated.
// @parm	LPDWORD | pdwType = NULL | Pointer to a variable of type <i>DWORD<n>
//				that will receive the type of the value, if found. This
//				value can also be <NULL> if not needed. The following values
//				can be returned in <p pdwType>:
//				@flag REG_BINARY |		Binary data in any form
//				@flag REG_DWORD |		A 32-bit number
//				@flag REG_EXPAND_SZ |	A null-terminated string that contains
//										unexpanded references to environment
//										variables (for example, "%PATH%").
//				@flag REG_MULTI_SZ |	An array of null-terminated strings,
//										terminated by two null characters.
//				@flag REG_SZ |			A null-terminated string.
// @parm	LPBYTE | pbData = NULL | Pointer to a buffer that receives the
//				data for the value entry. This parameter can be <NULL> if
//				the data is not required.
// @parm	LPDWORD | pdwDataLen = 0 | Pointer to a variable that specifies
//				the size, in bytes, of the buffer pointed to by the <p pbData>
//				parameter. When the function returns, the variable pointed to
//				by the <p pdwDataLen> parameter contains the number of bytes
//				stored in the buffer. This parameter can be <NULL>, only if
//				<p pbData> is <NULL>.
// @rdesc	If the function was successful, the return value is a pointer to
//				the name of the retrieved value, otherwise it is <NULL>.
//				If either <p pszBuffer> or <p cbBuffer> were <NULL>, an
//				internal helper buffer of 256 characters will be used for
//				returning the value name. <b><red>WARNING:<n><n> althought useful
//				in most cases, using the internal help buffer is <b>NOT<n>
//				thread safe.
// @comm	Gets the value data identified by <p rPosition>, then sets
//				<p rPosition> to the <b>ITERATOR<n> value of the previous
//				value in the open key. You can use <mf YRegistry::GetPrevValue>
//				in a reverse iteration loop if you establish the initial
//				position with a call to <mf YRegistry::GetLastValuePosition>.
//
//				You must ensure that your <b>ITERATOR<n> value represents a
//				valid position in the list. If it is invalid, then the function
//				returns <NULL>.
//
//				If the retrieved value is the first in the open key, then the
//				new value of <p rPosition> is set to <NULL>.
// @xref	<j Registry Iteration Example>,
//			<mf YRegistry::GetFirstValuePosition>, <mf YRegistry::GetLastValuePosition>,
//			<mf YRegistry::GetNextValue>,
//			<mf YRegistry::ValueExists>, <mf YRegistry::ValueGetCount>
// @key		Configuration Information Functions
LPCTSTR YRegistry::GetPrevValue (ITERATOR &pos, LPTSTR pszBuffer, UINT cbBuffer, LPDWORD pdwType, LPBYTE pbData, LPDWORD pdwDataLen)
{
	if ( !INTKEY || !pos ) {
		return NULL;
	}
	CHECK_HELPER(pszBuffer,cbBuffer);
	DWORD dwcbBuffer = cbBuffer;
	if ( RegEnumValue (INTKEY, (DWORD) pos - 1, pszBuffer, &dwcbBuffer, NULL, pdwType, pbData, pdwDataLen) != ERROR_SUCCESS ) {
		pos = NULL;
		return NULL;
	}
	if ( --pos < GetFirstValuePosition () ) {
		pos = NULL;
	}
	return pszBuffer;
}

// @mfunc	Gets the next section name for iterating
// @parm	ITERATOR & | rPosition | A reference to a <b>ITERATOR<n> value returned
//				by a previous <mf YRegistry::GetNextSection>, <mf YRegistry::GetPrevSection>,
//				<mf YRegistry::GetFirstSectionPosition>, <mf YRegistry::GetLastSectionPosition>
//				or other member function call.
// @parm	LPTSTR | pszBuffer = NULL | Points to the buffer that is to
//				receive the copied string of the section name. This value
//				can also be <NULL>.
// @parm	UINT | cbBuffer = 0 | Specifies the maximum number of characters
//				to be copied to the buffer. If the string is longer than the
//				number of characters specified in <p cbBuffer>, it is truncated.
// @rdesc	If the function was successful, the return value is a pointer to
//				the name of the retrieved section, otherwise it is <NULL>.
//				If either <p pszBuffer> or <p cbBuffer> were <NULL>, an
//				internal helper buffer of 256 characters will be used for
//				returning the section name. <b><red>WARNING:<n><n> althought useful
//				in most cases, using the internal help buffer is <b>NOT<n>
//				thread safe.
// @comm	Gets the section name identified by <p rPosition>, then sets
//				<p rPosition> to the <b>ITERATOR<n> value of the next
//				section in the open key. You can use <mf YRegistry::GetNextSection>
//				in a forward iteration loop if you establish the initial
//				position with a call to <mf YRegistry::GetFirstSectionPosition>.
//
//				You must ensure that your <b>ITERATOR<n> value represents a
//				valid position in the list. If it is invalid, then the function
//				returns <NULL>.
//
//				If the retrieved section name is the last in the open key,
//				then the new value of <p rPosition> is set to <NULL>.
// @xref	<j Registry Iteration Example>,
//			<mf YRegistry::GetFirstSectionPosition>, <mf YRegistry::GetLastSectionPosition>,
//			<mf YRegistry::GetPrevSection>,
//			<mf YRegistry::SectionExists>, <mf YRegistry::SectionGetCount>
// @key		Configuration Information Functions
LPCTSTR YRegistry::GetNextSection (ITERATOR &pos, LPTSTR pszBuffer, UINT cbBuffer)
{
	if ( !INTKEY || !pos ) {
		return NULL;
	}
	CHECK_HELPER(pszBuffer,cbBuffer);
	if ( RegEnumKey (INTKEY, (DWORD) pos - 1, pszBuffer, cbBuffer) != ERROR_SUCCESS ) {
		pos = NULL;
		return NULL;
	}
	if ( ++pos > GetLastSectionPosition () ) {
		pos = NULL;
	}
	return pszBuffer;
}

// @mfunc	Gets the previous section name for iterating
// @parm	ITERATOR & | rPosition | A reference to a <b>ITERATOR<n> value returned
//				by a previous <mf YRegistry::GetPrevSection>, <mf YRegistry::GetNextSection>,
//				<mf YRegistry::GetFirstSectionPosition>, <mf YRegistry::GetLastSectionPosition>
//				or other member function call.
// @parm	LPTSTR | pszBuffer = NULL | Points to the buffer that is to
//				receive the copied string of the section name. This value
//				can also be <NULL>.
// @parm	UINT | cbBuffer = 0 | Specifies the maximum number of characters
//				to be copied to the buffer. If the string is longer than the
//				number of characters specified in <p cbBuffer>, it is truncated.
// @rdesc	If the function was successful, the return value is a pointer to
//				the name of the retrieved section, otherwise it is <NULL>.
//				If either <p pszBuffer> or <p cbBuffer> were <NULL>, an
//				internal helper buffer of 256 characters will be used for
//				returning the section name. <b><red>WARNING:<n><n> althought useful
//				in most cases, using the internal help buffer is <b>NOT<n>
//				thread safe.
// @comm	Gets the section name identified by <p rPosition>, then sets
//				<p rPosition> to the <b>ITERATOR<n> value of the previous
//				section in the open key. You can use <mf YRegistry::GetPrevSection>
//				in a reverse iteration loop if you establish the initial
//				position with a call to <mf YRegistry::GetLastSectionPosition>.
//
//				You must ensure that your <b>ITERATOR<n> value represents a
//				valid position in the list. If it is invalid, then the function
//				returns <NULL>.
//
//				If the retrieved section name is the first in the open key,
//				then the new value of <p rPosition> is set to <NULL>.
// @xref	<j Registry Iteration Example>,
//			<mf YRegistry::GetFirstSectionPosition>, <mf YRegistry::GetLastSectionPosition>,
//			<mf YRegistry::GetNextSection>,
//			<mf YRegistry::SectionExists>, <mf YRegistry::SectionGetCount>
// @key		Configuration Information Functions
LPCTSTR YRegistry::GetPrevSection (ITERATOR &pos, LPTSTR pszBuffer, UINT cbBuffer)
{
	if ( !INTKEY || !pos ) {
		return NULL;
	}
	CHECK_HELPER(pszBuffer,cbBuffer);
	if ( RegEnumKey (INTKEY, (DWORD) pos - 1, pszBuffer, cbBuffer) != ERROR_SUCCESS ) {
		pos = NULL;
		return NULL;
	}
	if ( --pos < GetFirstSectionPosition () ) {
		pos = NULL;
	}
	return pszBuffer;
}

BOOL YRegistry::BooleanGet (LPCTSTR lpszValueName, BOOL bDefault, BOOL bStrict) const
{
	DWORD dwRet = NumberGet (lpszValueName, bDefault);
	return (bStrict && (dwRet & 0xfffffffe)) ? (bDefault) : (dwRet != 0);
}

DWORD YRegistry::NumberGet (LPCTSTR lpszValueName, DWORD dwDefault) const
{
	if ( !INTKEY ) {
		return 0;
	}
	DWORD	dwType;
	DWORD	dwSize = sizeof (DWORD);
	DWORD	dwValue;
	if ( (RegQueryValueEx (INTKEY, lpszValueName, NULL, &dwType, (LPBYTE) &dwValue, &dwSize) != ERROR_SUCCESS) || (dwType != REG_DWORD) ) {
		return dwDefault;
	}
	return dwValue;
}

LPCTSTR YRegistry::StringGet (LPCTSTR lpszValueName, LPTSTR pszBuffer, UINT cbBuffer, LPCTSTR lpszDefault)
{
	SAFE_STRING(lpszDefault);
	if ( !INTKEY ) {
		return NULL;
	}
	CHECK_HELPER(pszBuffer,cbBuffer);

	DWORD	dwType;
	DWORD	dwSize = cbBuffer * sizeof (TCHAR);
	LONG	lRes = RegQueryValueEx (INTKEY, lpszValueName, NULL, &dwType, NULL, &dwSize);
	if ( ((lRes != ERROR_SUCCESS) && (lRes != ERROR_MORE_DATA)) || ((dwType != REG_SZ) && (dwType != REG_EXPAND_SZ))) {
		_tcsncpy (pszBuffer, lpszDefault, cbBuffer);
		pszBuffer[cbBuffer - 1] = 0;
		return pszBuffer;
	}

	if ( dwSize > (cbBuffer * sizeof (TCHAR)) ) {
		LPTSTR pszTmpVar = (LPTSTR) malloc (dwSize);
		if ( !pszTmpVar || (RegQueryValueEx (INTKEY, lpszValueName, NULL, &dwType, (LPBYTE) pszTmpVar, &dwSize) != ERROR_SUCCESS) ) {
			// the memory error should not happen but for security we return
			// the default value
			_tcsncpy (pszBuffer, lpszDefault, cbBuffer);
			pszBuffer[cbBuffer - 1] = 0;
			return pszBuffer;
		}
		_tcsncpy (pszBuffer, pszTmpVar, cbBuffer);
		free (pszTmpVar);
	}
	else {
		if ( RegQueryValueEx (INTKEY, lpszValueName, NULL, &dwType, (LPBYTE) pszBuffer, &dwSize) != ERROR_SUCCESS ) {
			// this should really not happen....
			_tcsncpy (pszBuffer, lpszDefault, cbBuffer);
			pszBuffer[cbBuffer - 1] = 0;
			return pszBuffer;
		}
	}
	pszBuffer[cbBuffer - 1] = 0;
	return pszBuffer;
}

LPCTSTR YRegistry::ExpandableStringGet (LPCTSTR lpszValueName, LPTSTR pszBuffer, UINT cbBuffer, LPCTSTR lpszDefault)
{
	SAFE_STRING(lpszDefault);
	if ( !INTKEY ) {
		return NULL;
	}
	CHECK_HELPER(pszBuffer,cbBuffer);
	if ( !StringGet (lpszValueName, pszBuffer, cbBuffer, lpszDefault) ) {
		_tcsncpy (pszBuffer, lpszDefault, cbBuffer);
		pszBuffer[cbBuffer - 1] = 0;
	}

	// we need a very big temp buffer, since the stupid function
	// ExpandEnvironmentStrings does absolutely not work as documented:
	// It returns shit, if the destination buffer is too small and the
	// return value absolutely senseless (something like the double
	// requested size) and unpredictable
	TCHAR	szDestBuffer[0x4000];	// we hope it's enougth (16K)
	*szDestBuffer = 0;

	if ( ExpandEnvironmentStrings (pszBuffer, szDestBuffer, _countof(szDestBuffer)) && _tcslen (szDestBuffer) ) {
		_tcsncpy (pszBuffer, szDestBuffer, cbBuffer);
		pszBuffer[cbBuffer - 1] = 0;
	}
	return pszBuffer;
}

UINT YRegistry::AnyGet (LPCTSTR lpszValueName, DWORD dwWantedType, LPVOID pBuffer, UINT cbBuffer) const
{
	if ( !INTKEY ) {
		return 0;
	}

	DWORD	dwType;
	DWORD	dwSize = cbBuffer;
	LONG	lRes = RegQueryValueEx (INTKEY, lpszValueName, NULL, &dwType, NULL, &dwSize);
	if ( ((lRes != ERROR_SUCCESS) && (lRes != ERROR_MORE_DATA)) || (dwType != dwWantedType) ) {
		// type incorrect or real error happened
		return 0;
	}
	if ( !dwSize ) {
		// data is empty
		return 0;
	}
	if ( !cbBuffer || !pBuffer ) {
		// only size requested
		return dwSize;
	}

	if ( dwSize > cbBuffer ) {
		// data is bigger than the supplied buffer
		LPVOID pTmpVar = (LPVOID) malloc (dwSize);
		if ( !pTmpVar || (RegQueryValueEx (INTKEY, lpszValueName, NULL, &dwType, (LPBYTE) pTmpVar, &dwSize) != ERROR_SUCCESS) ) {
			// the memory error should not happen
			if ( pTmpVar ) {
				free (pTmpVar);
			}
			return 0;
		}
		// transfer the requested part
		memcpy (pBuffer, pTmpVar, cbBuffer);
		free (pTmpVar);
	}
	else {
		// buffer is big enougth
		if ( RegQueryValueEx (INTKEY, lpszValueName, NULL, &dwType, (LPBYTE) pBuffer, &dwSize) != ERROR_SUCCESS ) {
			// this should really not happen....
			return 0;
		}
	}
	return min(dwSize,cbBuffer);
}

UINT YRegistry::MultiStringGet (LPCTSTR lpszValueName, YMultiString &ysValue) const
{
	DWORD dwValueSize = AnyGet (lpszValueName, REG_MULTI_SZ);
	if ( dwValueSize < 2 ) {
		ysValue.Empty ();
		return 0;
	}

	if ( !ysValue.Prepare (dwValueSize) ) {
		return 0;
	}

	return AnyGet (lpszValueName, REG_MULTI_SZ, ysValue.GetBuffer (), ysValue.GetBufferSizeInBytes ());
}

BOOL YRegistry::MultiStringSet (LPCTSTR lpszValueName, LPCTSTR lpszValue) const
{
	// determine size
	for ( LPCTSTR lpPtr = lpszValue; *lpPtr; lpPtr += (_tcslen (lpPtr) + 1) ) {
		/*TUNIX*/
	}
	if ( lpPtr == lpszValue ) {
		// empty
		TCHAR	szEmpty[2];
		szEmpty[0] = szEmpty[1] = 0;
		return AnySet (lpszValueName, REG_MULTI_SZ, szEmpty, 2 * sizeof (TCHAR));
	}
	return AnySet (lpszValueName, REG_MULTI_SZ, lpszValue, (lpPtr - lpszValue + 1) * sizeof (TCHAR));
}

// @mfunc	Adds a string to a multistring value
// @rdesc	<TRUE> if the function was successful, <FALSE> if not
// @parm	LPCTSTR | lpszValueName | Name of the value to be set
// @parm	LPCTSTR | lpszValue | String that has to be added
// @parm	BOOL | bCaseSensitive = FALSE | Comparison check on the string
// @comm	Adds a string to a multistring value. If the multistring value does not exist,
//				it will be created. If the value is already present, the
//				method returns <TRUE> and leaves the value intact.
//				This check is performed caseless by default. To check
//				the string with case sensivity, <p bCaseSensitive> must
//				be set to <TRUE>
// @xref	<mf YRegistry::MultiStringRemove>
// @key		Complex registry data manipulation
BOOL YRegistry::MultiStringAdd (LPCTSTR lpszValueName, LPCTSTR lpszValue, BOOL bCaseSensitive) const
{
	if ( !INTKEY ) {
		return FALSE;
	}

	DWORD	dwValueSize		= AnyGet (lpszValueName, REG_MULTI_SZ);
	DWORD	dwAddSize		= (_tcslen (lpszValue) + 1) * sizeof (TCHAR);
	DWORD	dwNeededSize	= (dwValueSize) ? (dwValueSize + dwAddSize) : (dwAddSize + 1);
	LPTSTR	lpBuffer		= (LPTSTR) malloc (dwNeededSize);
	LPTSTR	lpPtr;

	if ( !lpBuffer ) {
		// memory allocation error of corrupted heap
		return FALSE;
	}
	// get the value
	DWORD	dwRetSize		= AnyGet (lpszValueName, REG_MULTI_SZ, lpBuffer, dwNeededSize);
	if ( dwRetSize != dwValueSize ) {
		// something got wrong
		free (lpBuffer);
		return FALSE;
	}
	if ( !dwRetSize ) {
		lpPtr = lpBuffer;
	}
	else {
		// find the string
		if ( bCaseSensitive ) {
			for ( lpPtr = lpBuffer; *lpPtr; lpPtr += (_tcslen (lpPtr) + 1) ) {
				if ( !_tcscmp (lpPtr, lpszValue) ) {
					// value found. nothing to do
					free (lpBuffer);
					return TRUE;
				}
			}
		}
		else {
			for ( lpPtr = lpBuffer; *lpPtr; lpPtr += (_tcslen (lpPtr) + 1) ) {
				if ( !_tcsicmp (lpPtr, lpszValue) ) {
					// value found. nothing to do
					free (lpBuffer);
					return TRUE;
				}
			}
		}
	}
	// add the value
	_tcscpy (lpPtr, lpszValue);
	lpPtr += (_tcslen (lpszValue) + 1);
	*lpPtr = 0;
	// write the value
	BOOL bRet = AnySet (lpszValueName, REG_MULTI_SZ, lpBuffer, dwNeededSize);
	free (lpBuffer);
	return bRet;
}

// @mfunc	Removes a string from a multistring value
// @rdesc	<TRUE> if the function was successful, <FALSE> if not
// @parm	LPCTSTR | lpszValueName | Name of the value to be set
// @parm	LPCTSTR | lpszValue | String that has to be added
// @parm	BOOL | bCaseSensitive = FALSE | Comparison check on the string
// @comm	Removes a string from a multistring value. If the multistring value
//				does not exist, nothing happens and the method returns <TRUE>.
//				If the value is not present, the method returns <TRUE> and
//				leaves the value intact.
//				This check is performed caseless by default. To check
//				the string with case sensivity, <p bCaseSensitive> must
//				be set to <TRUE>
// @xref	<mf YRegistry::MultiStringAdd>
// @key		Complex registry data manipulation
BOOL YRegistry::MultiStringRemove (LPCTSTR lpszValueName, LPCTSTR lpszValue, BOOL bCaseSensitive) const
{
	if ( !INTKEY ) {
		return FALSE;
	}

	DWORD	dwValueSize		= AnyGet (lpszValueName, REG_MULTI_SZ);
	DWORD	dwRemSize		= (_tcslen (lpszValue) + 1) * sizeof (TCHAR);
	if ( !dwValueSize ) {
		// empty....
		return TRUE;
	}
	LPTSTR	lpBuffer		= (LPTSTR) malloc (dwValueSize);
	LPTSTR	lpPtr;
	BOOL	bRet			= TRUE;

	if ( !lpBuffer ) {
		// memory allocation error of corrupted heap
		return FALSE;
	}
	// get the value
	DWORD	dwRetSize		= AnyGet (lpszValueName, REG_MULTI_SZ, lpBuffer, dwValueSize);
	if ( dwRetSize != dwValueSize ) {
		// something got wrong
		free (lpBuffer);
		return FALSE;
	}
	// find the string
	if ( bCaseSensitive ) {
		for ( lpPtr = lpBuffer; *lpPtr; lpPtr += (_tcslen (lpPtr) + 1) ) {
			if ( !_tcscmp (lpPtr, lpszValue) ) {
				// value found. exit
				break;
			}
		}
	}
	else {
		for ( lpPtr = lpBuffer; *lpPtr; lpPtr += (_tcslen (lpPtr) + 1) ) {
			if ( !_tcsicmp (lpPtr, lpszValue) ) {
				// value found. exit
				break;
			}
		}
	}

	if ( *lpPtr ) {
		// value was found
		LPCTSTR	lpNext	= lpPtr + _tcslen (lpPtr) + 1;
		DWORD	dwCount	= dwRetSize - ((lpNext - lpBuffer) * sizeof (TCHAR));
		memmove (lpPtr, lpPtr + _tcslen (lpPtr) + 1, dwCount);
		bRet = AnySet (lpszValueName, REG_MULTI_SZ, lpBuffer, dwRetSize - dwRemSize);
	}

	free (lpBuffer);
	return bRet;
}

#ifndef YLB_ENABLE_INLINE
#include <yRegistry.inl>
#endif

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////