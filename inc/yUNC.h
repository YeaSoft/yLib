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
 * FILENAME		:	yUNC.hpp
 * PURPOSE		:	Declaration of the UNC Class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:03:39  leo
 * Initial revision
 *
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