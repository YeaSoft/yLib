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
 * FILENAME		:	yMulStr.h
 * PURPOSE		:	Declaration of the multiple string class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.3  2001/05/28 15:29:00  leopoldo
 * Added assignment methods
 *
 * Revision 1.2  2001/05/24 15:20:11  leopoldo
 * First basic implementation
 *
 * Revision 1.1  2001/05/18 16:00:44  leopoldo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yMulStr.h
 *============================================================================*/
#ifndef __yMulStr_h__
#define __yMulStr_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yBuffer_h__
#include <yBuffer.h>
#endif
#ifndef __yFixStr_h__
#include <yFixStr.h>
#endif

/*=============================================================================
 * FORWARD CLASS DECLARATIONS
 *============================================================================*/

/*=============================================================================
 * MULTISTRING CLASS DECLARATION
 *============================================================================*/
class YMultiString
{
private:
	// kill these construction methods & operators
	YMultiString				(const YStringData& stringSrc);

public:
	// construction
	YMultiString				();
	~YMultiString				();

public:
	// attributes
	BOOL						IsEmpty					() const;
	LPCTSTR						GetString				() const;
	LPCTSTR						GetNullForEmptyString	() const;
	int							GetStringCount			() const;

	ITERATOR					GetFirstStringPosition	() const;
	ITERATOR					GetLastStringPosition	() const;
	LPCTSTR						GetNext					(ITERATOR &pos) const;
	LPCTSTR						GetPrev					(ITERATOR &pos) const;

	LPTSTR						GetBuffer				() { return (LPTSTR) m_dbStorage.GetBuffer (); }
	LPCTSTR						GetBuffer				() const { return (LPCTSTR) m_dbStorage.GetBuffer (); }
	UINT						GetBufferSize			() const { return m_dbStorage.GetSize () / sizeof (TCHAR); }
	UINT						GetBufferSizeInBytes	() const { return m_dbStorage.GetSize (); }
	UINT						GetContentSize			() const { return m_dbStorage.GetContentSize () / sizeof (TCHAR); }
	UINT						GetContentSizeInBytes	() const { return m_dbStorage.GetContentSize (); }
	void						SetContentSize			(int iContentSize) { m_dbStorage.SetContentSize (iContentSize * sizeof(TCHAR)); }

public:
	// operations
	void						Empty					(BOOL bFreeExtra = FALSE);
	BOOL						Alloc					(int cbSize);
	BOOL						Prepare					(int cbSize);
	BOOL						Assign					(const YMultiString &stringSrc);
	BOOL						Append					(LPCTSTR pszString);

public:
	// operators
	operator					LPCTSTR					() const;
	YMultiString &				operator=				(const YMultiString &stringSrc) { Assign (stringSrc); return *this; }
	YMultiString &				operator+=				(LPCTSTR pszString) { Append (pszString); return *this; }

protected:
	// implementation
	BOOL						IsBufferEmpty			() const { return m_dbStorage.IsEmpty (); }
	LPTSTR						GetBufferNext			() { return (LPTSTR) m_dbStorage.GetByteBufferPtr (m_dbStorage.GetContentSize() - sizeof (TCHAR)); }
	LPCTSTR						GetBufferNext			() const { return (LPCTSTR) m_dbStorage.GetByteBufferPtr (m_dbStorage.GetContentSize() - sizeof (TCHAR)); }
	LPTSTR						GetBufferLast			() { return (LPTSTR) m_dbStorage.GetByteBufferPtr (m_dbStorage.GetContentSize() - 2 * sizeof (TCHAR)); }
	LPCTSTR						GetBufferLast			() const { return (LPCTSTR) m_dbStorage.GetByteBufferPtr (m_dbStorage.GetContentSize() - 2 * sizeof (TCHAR)); }
	
protected:
	// implementation
	YDynamicBuffer				m_dbStorage;
};

#ifdef YLB_ENABLE_INLINE
#include <yMulStr.inl>
#endif

#endif //__yMulStr_h__
//
// EoF
////////
