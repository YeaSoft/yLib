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
 * FILENAME		:	yConApp.h
 * PURPOSE		:	Declaration of the console application class
 * SCOPE		:	yAfc
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:02:57  leo
 * Initial revision
 *
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

