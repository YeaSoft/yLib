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
 * FILENAME		:	yBaseApp.h
 * PURPOSE		:	Declaration of the application class
 * SCOPE		:	yAfc
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:02:54  leo
 * Initial revision
 *
 *============================================================================*/
/*=============================================================================
 * @doc YLIB | yBaseApp.h
 *============================================================================*/
#ifndef __yBaseApp_h__
#define __yBaseApp_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yFixString_h__
#include <yFixStr.h>
#endif
#ifndef __yAfcBase_h__
#include <yAfcBase.h>
#endif

/*=============================================================================
 * APPLICATION CLASSES
 *============================================================================*/
class YBaseApp
{
private:
	// kill these construction methods & operators
	YBaseApp					(const YBaseApp &);
	YBaseApp					&operator=				(const YBaseApp &);

public:
	// construction/destruction
	YBaseApp					(LPCTSTR pszAppName = NULL, LPCTSTR pszAppDesc = NULL);
	YBaseApp					(UINT nAppNameID);
	~YBaseApp					();

public:
	// attributes
	LPCTSTR						GetAppName				() const;
	void						SetAppName				(LPCTSTR pszAppName);
	LPCTSTR						GetAppDescription		() const;
	void						SetAppDescription		(LPCTSTR pszAppDescription);

	HINSTANCE					GetInstanceHandle		() const;
	HINSTANCE					GetResourceHandle		() const;
	YCommandLineInfo*			GetCommandLineInfo		() const;


public:
	// operations

public:
	// system operations
	YString256					GetSysErrorString		(DWORD dwError);

public:
	// overridables
	virtual BOOL				InitInstance			(YCommandLineInfo *cli);
	virtual void				ExitInstance			(BOOL bInstanceInited);

protected:
	// implementation
	void						CommonConstructor		();

protected:
	// implementation
	YCommandLineInfo*			m_pCLI;
	TCHAR						m_szAppName[16];
	TCHAR						m_szAppDesc[64];
};

#ifdef YLB_ENABLE_INLINE
#include <yBaseApp.inl>
#endif

#endif //__yBaseApp_h__
//
// EoF
////////

