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
 * FILENAME		:	yFileObjects.hpp
 * PURPOSE		:	File utility objects
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:03:03  leo
 * Initial revision
 *
 *============================================================================*/

/*============================================================================*
 * @doc YLIB | yFileObjects.h
 *============================================================================*/
#ifndef __yFileObjects_h__
#define __yFileObjects_h__

/*============================================================================*
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yLibBase_h__
#include <yLibBase.h>
#endif

/*============================================================================*
 * ATTRIBUTE HANDLING
 *============================================================================*/
class YFileAttributes : public YFlags
{
private:
	static DWORD			FAFLG_NAMEPRESENT;
	static DWORD			FAFLG_ATTRIBLOADED;
	static DWORD			FAFLG_CRCLOADED;
	static DWORD			FAFLG_VERSIONLOADED;
	static DWORD			FAFLG_CACHING;

public:
	// construction/destruction
	YFileAttributes			(BOOL bCaching = TRUE);
	YFileAttributes			(LPCTSTR lpszFileName, ...);

public:
	// operations
	void					SetName					(LPCTSTR lpszFileName, ...);
	BOOL					GetCacheState			() const;
	void					SetCacheState			(BOOL bCaching = TRUE);

	const YVersInfo&		operator=				(YFileAttributes &cfa);

public:
	// attributes
	DWORD					GetFileCrc				();
	DWORD					GetFileSize				(LPDWORD lpdwSizeHi = NULL);
	DWORD					GetFileAttribs			();
	const YVersInfo&		GetFileVersion			();

	BOOL					SetFileAttribs			(DWORD dwAdd, DWORD dwRemove);


protected:
	// implementation
	BOOL					LoadCrc					();
	BOOL					LoadAttribs				();
	BOOL					LoadVersion				();

private:
	// data
	TCHAR					m_szFileName[MAX_PATH];
	DWORD					m_dwCrc;
	WIN32_FIND_DATA			m_wfdAttr;
	YVersInfo				m_viVersion;
};


#ifdef YLB_ENABLE_INLINE
#include <yFileObjects.inl>
#endif

#endif //__yFileObjects_h__

//
// EoF
////////
