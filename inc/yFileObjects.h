/*=============================================================================
 * This is a part of the yLib Software Development Kit.
 * Copyright (C) 1998-2000 YEAsoft Inc.
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
 * FILENAME		:	yFileObjects.hpp
 * PURPOSE		:	File utility objects
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
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
