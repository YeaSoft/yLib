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
 * FILENAME		:	yRegistry.h
 * PURPOSE		:	Declaration of the registry class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.4  2001/06/13 11:54:41  leopoldo
 * Added dependency
 *
 * Revision 1.3  2001/05/24 15:20:56  leopoldo
 * Added support for YStringData and YMultiString
 *
 * Revision 1.2  2000/09/04 11:59:53  leopoldo
 * Updated license to zlib/libpng
 *
 * Revision 1.1  2000/05/26 14:03:25  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yRegistry.h
 *============================================================================*/
#ifndef __yRegistry_h__
#define __yRegistry_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yLibBase_h__
#include <yLibBase.h>
#endif
#ifndef __yFixStr_h__
#include <yFixStr.h>
#endif

/*=============================================================================
 * FORWARD CLASS DECLARATIONS
 *============================================================================*/
class YStringData;
class YMultiString;

/*=============================================================================
 * USEFUL MACROS
 *============================================================================*/
#define REG_ANY					( 0 )

/*=============================================================================
 * CLASS DECLARATION
 *============================================================================*/
// @class	The Win32 Registry Class
// @comm	The <c YRegistry> class provides services to manage with the
//			Windows NT or Windows 95 Registry.
class YRegistry
{
public:
	// @cmember Construction of a <c YRegistry> object
	YRegistry					(const HKEY hAnchor = HKEY_LOCAL_MACHINE);
	// @cmember Construction of an inherited <c YRegistry> object
	YRegistry					(const YRegistry &regSrc);

	// @cmember Simple assignment operator
	YRegistry&					operator=				(const YRegistry &regSrc);
	// @cmember Assignment operator for <b>HKEY<n> handles
	YRegistry&					operator=				(const HKEY hAnchor);

public:
	~YRegistry					();

public:
	// @access Access Operations
	// @cmember Opens an existing key of the registry
	BOOL						Open					(LPCTSTR lpszKey, REGSAM samDesired = KEY_ALL_ACCESS);
	// @cmember Creates or opens an existing key of the registry
	BOOL						Create					(LPCTSTR lpszKey, LPTSTR lpszClass = TEXT(""), REGSAM samDesired = KEY_ALL_ACCESS, LPSECURITY_ATTRIBUTES lpSecurityAttributes = NULL, DWORD dwOptions = REG_OPTION_NON_VOLATILE);
	// @cmember Opens the registry of another computer
	BOOL						Connect					(LPCTSTR lpszComputer, const HKEY hAnchor = HKEY_LOCAL_MACHINE);
	// @cmember Closes an open key of the registry
	void						Close					();

	// @access Delete Operations
	// @cmember Deletes a value from the open key
	BOOL						ValueDelete				(LPCTSTR lpszValue) const;
	// @cmember Deletes an entire subkey of the open key
	BOOL						SectionDelete			(LPCTSTR lpszKey) const;

	// @access Information Query Methods
	// @cmember Checks a value of the open key for existance
	BOOL						ValueExists				(LPCTSTR lpszValue, DWORD dwType = REG_ANY) const;
	// @cmember Checks a subkey of the open key for existance
	BOOL						SectionExists			(LPCTSTR lpszKey) const;
	// @cmember Returns the number of values contained in the open key
	DWORD						ValueGetCount			() const;
	// @cmember Returns the number of sections contained in the open key
	DWORD						SectionGetCount			() const;

	// @cmember Returns the position of the first value in the open key
	ITERATOR					GetFirstValuePosition	() const;
	// @cmember Returns the position of the last value in the open key
	ITERATOR					GetLastValuePosition	() const;
	// @cmember Gets the next value name for iterating
	LPCTSTR						GetNextValue			(ITERATOR &rPosition, LPTSTR pszBuffer = NULL, UINT cbBuffer = 0, LPDWORD pdwType = NULL, LPBYTE pbData = NULL, LPDWORD pdwDataLen = 0);
	// @cmember Gets the previous value name for iterating
	LPCTSTR						GetPrevValue			(ITERATOR &rPosition, LPTSTR pszBuffer = NULL, UINT cbBuffer = 0, LPDWORD pdwType = NULL, LPBYTE pbData = NULL, LPDWORD pdwDataLen = 0);

	// @cmember Returns the position of the first subkey in the open key
	ITERATOR					GetFirstSectionPosition	();
	// @cmember Returns the position of the last subkey in the open key
	ITERATOR					GetLastSectionPosition	();
	// @cmember Gets the next section name for iterating
	LPCTSTR						GetNextSection			(ITERATOR &rPosition, LPTSTR pszBuffer = NULL, UINT cbBuffer = 0);
	// @cmember Gets the previous section name for iterating
	LPCTSTR						GetPrevSection			(ITERATOR &rPosition, LPTSTR pszBuffer = NULL, UINT cbBuffer = 0);
	
public:
	// @access Handle access
	// @cmember Casting operator
	operator					HKEY					() const;
	// @cmember Registry handle retrieval
	HKEY						GetHandle				() const;
	// @cmember Anchor registry handle retrieval
	HKEY						GetAnchorHandle			() const;

	// @access Simple registry data access
	// @cmember Returns a boolean value
	BOOL						BooleanGet				(LPCTSTR lpszValueName, BOOL bDefault, BOOL bStrict = TRUE) const;
	// @cmember Returns a numeric value
	DWORD						NumberGet				(LPCTSTR lpszValueName, DWORD dwDefault) const;
	// @cmember Returns a string value
	LPCTSTR						StringGet				(LPCTSTR lpszValueName, LPTSTR pszBuffer = NULL, UINT cbBuffer = 0, LPCTSTR lpszDefault = NULL);
	// @cmember Returns a string value
	LPCTSTR						StringGet				(LPCTSTR lpszValueName, YStringData &ysValue, LPCTSTR lpszDefault = NULL);
	// @cmember Returns an expandable string value
	LPCTSTR						ExpandableStringGet		(LPCTSTR lpszValueName, LPTSTR pszBuffer = NULL, UINT cbBuffer = 0, LPCTSTR lpszDefault = NULL);
	// @cmember Returns a multiple string value
	UINT						MultiStringGet			(LPCTSTR lpszValueName, LPTSTR pszBuffer = NULL, UINT cbBuffer = 0) const;
	// @cmember Returns a multiple string value
	UINT						MultiStringGet			(LPCTSTR lpszValueName, YMultiString &ysValue) const;
	// @cmember Returns a binary block of data
	UINT						BinaryGet				(LPCTSTR lpszValueName, LPVOID pBuffer = NULL, UINT cbBuffer = 0) const;
	// @cmember Returns a generic block of data
	UINT						AnyGet					(LPCTSTR lpszValueName, DWORD dwWantedType, LPVOID pBuffer = NULL, UINT cbBuffer = 0) const;

	// @cmember Writes a boolean value
	BOOL						BooleanSet				(LPCTSTR lpszValueName, BOOL bValue) const;
	// @cmember Writes a numeric value
	BOOL						NumberSet				(LPCTSTR lpszValueName, DWORD dwValue) const;
	// @cmember Writes a string value
	BOOL						StringSet				(LPCTSTR lpszValueName, LPCTSTR lpszValue) const;
	// @cmember Writes an expandable string value
	BOOL						ExpandableStringSet		(LPCTSTR lpszValueName, LPCTSTR lpszValue) const;
	// @cmember Writes a multiple string value
	BOOL						MultiStringSet			(LPCTSTR lpszValueName, LPCTSTR lpszValue) const;
	// @cmember Writes a binary block
	BOOL						BinarySet				(LPCTSTR lpszValueName, LPCVOID pszBuffer, UINT cbBuffer) const;
	// @cmember Writes a generic block of data
	BOOL						AnySet					(LPCTSTR lpszValueName, DWORD dwType, LPCVOID pszBuffer, UINT cbBuffer) const;

	// @access Complex registry data manipulation
	// @cmember Adds a string to a multistring value
	BOOL						MultiStringAdd			(LPCTSTR lpszValueName, LPCTSTR lpszValue, BOOL bCaseSensitive = FALSE) const;
	// @cmember Removes a string from a multistring value
	BOOL						MultiStringRemove		(LPCTSTR lpszValueName, LPCTSTR lpszValue, BOOL bCaseSensitive = FALSE) const;


private:
	HKEY						m_regAnchor;
	HKEY						m_regKey;
	BOOL						m_bAutoClose;
	TCHAR						m_szHelpBuffer[256];
};
// @xref	<j Registry Iteration Example>, <j Understanding YRegistry handle inheritance>,
//			<j System Services>

#define INTKEY				((m_regKey) ? (m_regKey) : (m_regAnchor))

#ifdef YLB_ENABLE_INLINE
#include <yRegistry.inl>
#endif

#endif //__yRegistry_h__
//
// EoF
////////