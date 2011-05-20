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
 * FILENAME		:	yMulStr.cpp
 * PURPOSE		:	Implementation of the multiple string class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.3  2001/05/28 15:29:34  leopoldo
 * Added assignment methods
 *
 * Revision 1.2  2001/05/24 15:20:23  leopoldo
 * First basic implementation
 *
 * Revision 1.1  2001/05/18 16:01:06  leopoldo
 * Initial revision
 *
 *============================================================================*/

#include "StdInc.hpp"

/*=============================================================================
 * @doc YLIB | yMulStr.h
 *============================================================================*/

/*=============================================================================
 * MULTISTRING CLASS IMPLEMENTATION
 *============================================================================*/
int YMultiString::GetStringCount () const
{
	if ( IsEmpty () ) {
		return 0;
	}

	int iRet = 0;

	for ( LPCTSTR lpPtr = GetBuffer (); *lpPtr; lpPtr += _tcslen (lpPtr) + 1 ) {
		++iRet;
	}
	return iRet;
}

ITERATOR YMultiString::GetLastStringPosition () const
{
	LPCTSTR	lpPtr = NULL;

	if ( IsEmpty () ) {
		return NULL;
	}

	// find the beginning of the last string
	for ( lpPtr = GetBufferLast (); lpPtr && *lpPtr && (lpPtr > GetBuffer ()); lpPtr-- ) {
		/*TUNIX*/
	}

	if ( !lpPtr || (lpPtr == GetBuffer ()) ) {
		// empty or first string reached
		return (ITERATOR) lpPtr;
	}

	return  (ITERATOR) lpPtr - 1;
}

LPCTSTR YMultiString::GetNext (ITERATOR &pos) const
{
	LPCTSTR lpPtr = (LPCTSTR) pos;

	if ( IsEmpty () || (lpPtr < GetBuffer ()) || (lpPtr > (LPCTSTR) m_dbStorage.GetByteBufferPtr (m_dbStorage.GetContentSize() - sizeof (TCHAR))) ) {
		// junk pos
		pos = NULL;
		return NULL;
	}

	if ( !*lpPtr ) {
		// SNH: end of multistring
		pos = NULL;
	}
	else {
		// go one further
		pos = (ITERATOR) (lpPtr + _tcslen (lpPtr) + 1);
		if ( !*((LPCTSTR) pos) ) {
			// end of multistring
			pos = NULL;
		}
	}

	return lpPtr;
}

LPCTSTR YMultiString::GetPrev (ITERATOR &pos) const
{
	LPCTSTR lpPtr = (LPCTSTR) pos;
	LPCTSTR	lpTest;

	if ( IsEmpty () || (lpPtr < GetBuffer ()) || (lpPtr >= (LPCTSTR) m_dbStorage.GetByteBufferPtr (m_dbStorage.GetContentSize())) ) {
		// junk pos
		pos = NULL;
		return NULL;
	}

	if ( lpPtr == GetBuffer () ) {
		// this was the last string
		pos = NULL;
	}
	else {
		// lets go back
		for ( lpTest = lpPtr - 1; *lpTest && (lpTest > GetBuffer ()); lpTest-- ) {
			/*TUNIX*/
		}
		if ( lpTest == GetBuffer () ) {
			// reached first string
			pos = (ITERATOR) GetBuffer ();
		}
		else {
			pos = (ITERATOR) lpTest - 1;
		}
	}
	return lpPtr;
}

BOOL YMultiString::Alloc (int cbSize)
{
	if ( cbSize < 2 ) {
		return FALSE;
	}
	if ( !m_dbStorage.Alloc (cbSize * sizeof (TCHAR)) ) {
		return FALSE;
	}
	GetBuffer ()[0] = 0;
	GetBuffer ()[1] = 0;
	return TRUE;
}

BOOL YMultiString::Assign (const YMultiString &stringSrc)
{
	if ( stringSrc.IsEmpty () ) {
		Empty ();
		return TRUE;
	}
	return m_dbStorage.Copy (stringSrc.m_dbStorage);
}

BOOL YMultiString::Append (LPCTSTR pszString)
{
	if ( m_dbStorage.IsEmpty () ) {
		if ( !m_dbStorage.PushTerminatedString (pszString) ) {
			return FALSE;
		}
		if ( !m_dbStorage.PushData (_T("\0"), sizeof (TCHAR)) ) {
			m_dbStorage.Empty ();
			return FALSE;
		}
		return TRUE;
	}
	else {
		return m_dbStorage.InsertData (m_dbStorage.GetContentSize () - sizeof (TCHAR), pszString, (_tcslen (pszString) + 1) * sizeof (TCHAR));
	}
}

#ifndef YLB_ENABLE_INLINE
#include <yMulStr.inl>
#endif

/// IDENTITY STUFF ///
//LPCTSTR lpComment = _T("$Id$");

//
// EoF
////////