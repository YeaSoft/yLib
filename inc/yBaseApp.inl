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
 * FILENAME		:	yBaseApp.inl
 * PURPOSE		:	Inline members of the application class
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