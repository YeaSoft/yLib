/*=============================================================================
 * This is a part of the yLib Software Development Kit.
 * Copyright (C) 1998-1999 YEAsoft Inc.
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
 * FILENAME		:	yBaseApp.inl
 * PURPOSE		:	Inline members of the application class
 * SCOPE		:	yAfc
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yBaseApp.h
 *============================================================================*/

//
// construction/destruction
//
YLB_INLINE YBaseApp::~YBaseApp ()
{
}



//
// attributes
//
YLB_INLINE LPCTSTR YBaseApp::GetAppName () const
{
	return m_szAppName;
}

YLB_INLINE LPCTSTR YBaseApp::GetAppDescription () const
{
	return m_szAppDesc;
}

YLB_INLINE HINSTANCE YBaseApp::GetInstanceHandle () const
{
	return YlbGetInstanceHandle ();
}

YLB_INLINE HINSTANCE YBaseApp::GetResourceHandle () const
{
	return YlbGetResourceHandle ();
}

// @mfunc	Get a pointer to the command line info object
// @rdesc	Pointer to a command line information object of type <c YCommandLineInfo>
// @comm	Use this function to retrieve the command line information packaged
//				in a <c YCommandLineInfo> object.
YLB_INLINE YCommandLineInfo* YBaseApp::GetCommandLineInfo () const
{
	return m_pCLI;
}



//
// overridables
//

// @mfunc	Override to perform application instance initialization,
//		such as creating your internal objects.
// @parm	YCommandLineInfo * | cli | Pointer to a <c YCommandLineInfo> object.
// @rdesc	Nonzero if initialization is successful; otherwise 0.
// @comm	Windows allows several copies of the same program to run at the same
//		time. Application initialization is conceptually divided into two
//		sections: one-time application initialization that is done the first
//		time the program runs, and instance initialization that runs each
//		time a copy of the program runs, including the first time.
//		The framework's implementation of <b>main<n> calls this function.
//		<nl><nl>Override <mf YBaseApp::InitInstance> to initialize each new instance of
//		your application running under Windows. Typically, you override
//		<mf YBaseApp::InitInstance> to initialize you application objects.
YLB_INLINE BOOL YBaseApp::InitInstance (YCommandLineInfo *cli)
{
	return TRUE;
}

// @mfunc	Override to clean up when your application terminates.
// @parm	BOOL | bInstanceInited | <TRUE> if <mf YBaseApp::InitInstance> was succesful
//		and the program has run, <FALSE> if not.
// @comm	Called by the framework after the <mf YBaseApp::Run> member function
//		or the <mf YBaseApp::InitInstance> member function to exit this instance
//		of the application.
//		<nl><nl>The default implementation of this function does nothing.
//		Override this function to clean up when your application terminates.
YLB_INLINE void YBaseApp::ExitInstance (BOOL bInstanceInited)
{
}

//
// EoF
////////