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
 * FILENAME		:	yConApp.h
 * PURPOSE		:	Declaration of the console application class
 * SCOPE		:	yAfc
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/
/*=============================================================================
 * @doc YLIB | yConApp.h
 *============================================================================*/
#ifndef __yConApp_h__
#define __yConApp_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yBaseApp_h__
#include <yBaseApp.h>
#endif

/*=============================================================================
 * CONSOLE APPLICATION CLASS
 *============================================================================*/
// @class	The base application class
// @comm	The <c YConApp> class is the base class from which you derive a Windows
//			console application object. An application object provides member
//			functions for initializing your application (and each instance of it)
//			and for running the application.
//			Each application that uses the yLib classes can only contain one
//			object derived from <c YConApp>. This object is constructed when other
//			C++ global objects are constructed and is already available when
//			Windows calls the <b>main<n> function, which is supplied by the
//			yLib Class Library. Declare your derived <c YConApp> object at the global
//			level.
//			When you derive an application class from <c YConApp>, override the
//			<mf YConApp::InitInstance> member function to create your application's main
//			object.
// @group MEMBER FUNCTIONS:
// @head2 Data Members | 
//		<md YConApp::m_pszAppName>: Specifies the name of the application.
//
//		<md YConApp::m_hInstance>: Identifies the current instance of the application.
//
// @head2 Construcion |
//		<mf YConApp::YConApp>: Constructs a <c YConApp> object.
//
// @head2 Operations |
//		none
//
// @head2 Overridables |
//		<mf YConApp::InitInstance>: Override to perform application
//		instance initialization, such as creating your internal objects
//
//		<mf YConApp::ExitInstance>: Override to clean up when your application
//		terminates.
//
//		<mf YConApp::Run>: Override to perform that application's real work.
//
// @head2 Attributes |
//		<mf YConApp::SetReturnCode>: Set the return code of the application.
//
//		<mf YConApp::GetReturnCode>: Get the return code that the application will return on exit.
//
class YConApp : public YBaseApp
{
private:
	// kill these construction methods & operators
	YConApp						(const YConApp &);
	YConApp						&operator=				(const YConApp &);

public:
	// construction/destruction
	YConApp						(LPCTSTR pszAppName = NULL, LPCTSTR pszAppDesc = NULL, WORD wMajor = 0xffff, WORD wMinor = 0, WORD wStepping = 0, WORD wBuild = 0);
	YConApp						(UINT nAppNameID);
	~YConApp					();

public:
	// operations
	BOOL						RegisterConsoleHandler	() const;
	BOOL						UnregisterConsoleHandler() const;

public:
	// attributes
	WORD						GetMajorVersion			() const;
	WORD						GetMinorVersion			() const;
	WORD						GetSteppingNumber		() const;
	WORD						GetBuildNumber			() const;
	LPCTSTR						GetImagePath			() const;
	LPCTSTR						GetImageName			() const;
	int							GetReturnCode			() const;
	void						SetReturnCode			(int iReturn);

public:
	// overridables
	virtual void				Run						();

public:
	// advanced overridables
	virtual BOOL				OnCtrlC					();
	virtual BOOL				OnCtrlBreak				();
	virtual BOOL				OnClose					();
	virtual BOOL				OnLogoff				();
	virtual BOOL				OnShutdown				();
#ifdef _DEBUG
	virtual BOOL				OnCrtDebugReport		(int reportType, LPCSTR pszMessage, int *iRetValue);
#endif

protected:
	// implementation
	void						CommonConstructor		();

protected:
	// implementation
	TCHAR						m_szAppPath[MAX_PATH];
	LPCTSTR						m_pszAppPath;
	LPCTSTR						m_pszAppName;
	WORD						m_wMajor;
	WORD						m_wMinor;
	WORD						m_wStepping;
	WORD						m_wBuild;
	int							m_iReturn;
};

#ifdef YLB_ENABLE_INLINE
#include <yConApp.inl>
#endif

#endif //__yConApp_h__
//
// EoF
////////

