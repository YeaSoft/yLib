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
 * FILENAME		:	yBaseApp.h
 * PURPOSE		:	Declaration of the application class
 * SCOPE		:	yAfc
 * HISTORY		: =============================================================
 * 
 * $Log$
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

