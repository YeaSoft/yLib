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
 * FILENAME		:	yUNC.hpp
 * PURPOSE		:	Declaration of the UNC Class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yUNC.h
 *============================================================================*/
#ifndef __yUNC_h__
#define __yUNC_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yLibBase_h__
#include <yLibBase.h>
#endif

/*=============================================================================
 * CLASS DEFINITIONS
 *============================================================================*/
class YUNC
{
public:
	// construction
	YUNC						();
	YUNC						(LPCTSTR lpszFileName, ...);
	YUNC						(const YUNC &uncSrc);

public:
	// attributes
	operator					LPCTSTR					() const;
	BOOL						IsUNC					() const;
	BOOL						IsLocal					() const;
	BOOL						IsLocalComputer			() const;
	BOOL						IsRemote				() const;
	BOOL						IsAdministrative		() const;
	BOOL						HasComputer				() const;

	LPCTSTR						GetComputerPart			(LPTSTR pszBuffer = NULL, UINT cbBuffer = 0);
	LPCTSTR						GetSharePart			(LPTSTR pszBuffer = NULL, UINT cbBuffer = 0);
	LPCTSTR						GetPathPart				(LPTSTR pszBuffer = NULL, UINT cbBuffer = 0);
	LPCTSTR						BuildLocalName			(LPTSTR pszBuffer = NULL, UINT cbBuffer = 0);

public:
	// operations
	void						SetName					(LPCTSTR lpszFileName, ...);

private:
	// implementation
	void						CommonConstructor			();
	void						Analyze						();

private:
	// implementation
	TCHAR						m_szFileName[MAX_PATH];
	TCHAR						m_szBuffer[MAX_PATH];
	LPCTSTR						m_pszComputerPart;
	UINT						m_nComputerLength;
	LPCTSTR						m_pszSharePart;
	UINT						m_nShareLength;
	LPCTSTR						m_pszPathPart;
	UINT						m_nPathLength;
};

#ifdef YLB_ENABLE_INLINE
#include <yUNC.inl>
#endif

#endif //__yUNC_h__

//
// EoF
////////