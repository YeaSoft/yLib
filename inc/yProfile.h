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
 * FILENAME		:	yProfile.h
 * PURPOSE		:	Declaration of the INI File Class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2001/09/14 16:19:48  leopoldo
 * Initial revision
 *
 *============================================================================*/
/*=============================================================================
 * @doc YLIB | yProfile.h
 *============================================================================*/
#ifndef __yProfile_h__
#define __yProfile_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yFixStr_h__
#include <yFixStr.h>
#endif

/*=============================================================================
 * FORWARD CLASS DECLARATIONS
 *============================================================================*/

/*=============================================================================
 * CLASS DECLARATION
 *============================================================================*/
class YProfile
{
public:
	enum YFormatFlags {
		boolTrueFalse					= 0x00000001,
		boolYesNo						= 0x00000002,
		boolNumeric						= 0x00000004,
		numberDecimal					= 0x00000008,
		numberHexadecimal				= 0x00000010
	};

public:
	// construction
	YProfile					();
	YProfile					(LPCTSTR pszFile, ...);
	YProfile					(const YProfile &iniSrc);

public:
	// @access Access Operations
	// @cmember Opens an existing key of the ini file
	bool						Open					(LPCTSTR lpszKey);
	// @cmember Creates or opens an existing key of the ini file
	bool						Create					(LPCTSTR lpszKey);
	// @cmember Closes an open key of the ini file
	void						Close					();
	// @cmember Test if a section is open
	bool						IsOpen					() const;

	// @access Delete Operations
	// @cmember Deletes a value from the open key
	bool						ValueDelete				(LPCTSTR lpszValue) const;
	// @cmember Deletes an entire key
	bool						SectionDelete			(LPCTSTR lpszKey);

	// @access Information Query Methods
	// @cmember Checks a value of the open key for existance
	bool						ValueExists				(LPCTSTR lpszValue) const;
	// @cmember Checks a key for existance
	bool						SectionExists			(LPCTSTR lpszKey) const;
	// @cmember Returns the number of values contained in the open key
	DWORD						ValueGetCount			() const;
	// @cmember Returns the number of sections contained in the ini file
	DWORD						SectionGetCount			() const;

	// @cmember Returns the position of the first value in the open key
	ITERATOR					GetFirstValuePosition	() const;
	// @cmember Returns the position of the last value in the open key
	ITERATOR					GetLastValuePosition	() const;
	// @cmember Gets the next value name for iterating
	LPCTSTR						GetNextValue			(ITERATOR &rPosition, LPTSTR pszBuffer = NULL, UINT cbBuffer = 0, LPDWORD pdwType = NULL, LPBYTE pbData = NULL, LPDWORD pdwDataLen = 0);
	// @cmember Gets the previous value name for iterating
	LPCTSTR						GetPrevValue			(ITERATOR &rPosition, LPTSTR pszBuffer = NULL, UINT cbBuffer = 0, LPDWORD pdwType = NULL, LPBYTE pbData = NULL, LPDWORD pdwDataLen = 0);

	// @cmember Returns the position of the first key in the ini file
	ITERATOR					GetFirstSectionPosition	();
	// @cmember Returns the position of the last key in the ini file
	ITERATOR					GetLastSectionPosition	();
	// @cmember Gets the next section name for iterating
	LPCTSTR						GetNextSection			(ITERATOR &rPosition, LPTSTR pszBuffer = NULL, UINT cbBuffer = 0);
	// @cmember Gets the previous section name for iterating
	LPCTSTR						GetPrevSection			(ITERATOR &rPosition, LPTSTR pszBuffer = NULL, UINT cbBuffer = 0);
	
public:
	// @access Simple ini file data access
	// @cmember Returns a boolean value
	bool						BooleanGet				(LPCTSTR lpszValueName, bool bDefault, BOOL bStrict = TRUE) const;
	// @cmember Returns a numeric value
	long						NumberGet				(LPCTSTR lpszValueName, long lDefault) const;
	// @cmember Returns a numeric value
	DWORD						NumberGet				(LPCTSTR lpszValueName, DWORD dwDefault) const;
	// @cmember Returns a numeric value
	double						NumberGet				(LPCTSTR lpszValueName, double dDefault) const;
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
	bool						BooleanSet				(LPCTSTR lpszValueName, bool bValue, YFormatFlags fFlags = boolTrueFalse) const;
	// @cmember Writes a numeric value
	bool						NumberSet				(LPCTSTR lpszValueName, long lValue, YFormatFlags fFlags = numberDecimal) const;
	// @cmember Writes a numeric value
	bool						NumberSet				(LPCTSTR lpszValueName, DWORD dwValue, YFormatFlags fFlags = numberDecimal) const;
	// @cmember Writes a numeric value
	bool						NumberSet				(LPCTSTR lpszValueName, double dValue) const;
	// @cmember Writes a string value
	bool						StringSet				(LPCTSTR lpszValueName, LPCTSTR lpszValue) const;
	// @cmember Writes an expandable string value
	bool						ExpandableStringSet		(LPCTSTR lpszValueName, LPCTSTR lpszValue) const;
	// @cmember Writes a multiple string value
	bool						MultiStringSet			(LPCTSTR lpszValueName, LPCTSTR lpszValue) const;
	// @cmember Writes a binary block
	bool						BinarySet				(LPCTSTR lpszValueName, LPCVOID pszBuffer, UINT cbBuffer) const;
	// @cmember Writes a generic block of data
	bool						AnySet					(LPCTSTR lpszValueName, DWORD dwType, LPCVOID pszBuffer, UINT cbBuffer) const;

	// @access Complex registry data manipulation
	// @cmember Adds a string to a multistring value
	bool						MultiStringAdd			(LPCTSTR lpszValueName, LPCTSTR lpszValue, bool bCaseSensitive = FALSE) const;
	// @cmember Removes a string from a multistring value
	bool						MultiStringRemove		(LPCTSTR lpszValueName, LPCTSTR lpszValue, bool bCaseSensitive = FALSE) const;


private:
	YPathString					m_ysIniFile;
	YString64					m_ysSection;
	YString256					m_ysHelper;
};

#ifdef YLB_ENABLE_INLINE
#include <yProfile.inl>
#endif

#endif //__yProfile_h__
//
// EoF
////////
