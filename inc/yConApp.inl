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
 * FILENAME		:	yConApp.inl
 * PURPOSE		:	Inline members of the console application class
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

/*=============================================================================
 * YConApp - The console application class
 *============================================================================*/

//
// construction/destruction
//
YLB_INLINE YConApp::~YConApp ()
{
}



//
// attributes
//
YLB_INLINE WORD YConApp::GetMajorVersion () const
{
	return m_wMajor;
}

YLB_INLINE WORD YConApp::GetMinorVersion () const
{
	return m_wMinor;
}

YLB_INLINE WORD YConApp::GetSteppingNumber () const
{
	return m_wStepping;
}

YLB_INLINE WORD YConApp::GetBuildNumber () const
{
	return m_wBuild;
}

YLB_INLINE LPCTSTR YConApp::GetImagePath () const
{
	return m_pszAppPath;
}

YLB_INLINE LPCTSTR YConApp::GetImageName () const
{
	return m_pszAppName;
}


// @mfunc	Get the return code that the application will return on exit.
// @rdesc	The current return code of the application
// @comm	Use this function to get the return code that your application
//		has previously set. Usually this code is 0 for an error
//		free execution. A nonzero value usually means that an error has occurred.
// @xref	<mf YConApp::SetReturnCode>, <c YConApp>
YLB_INLINE int YConApp::GetReturnCode () const
{
	return m_iReturn;
}

// @mfunc	Set the return code of the application.
// @parm	int | iReturn | The return code of your application
// @comm	Use this function to set the return code that your application
//		returns to the caller on exit. Usually this code is 0 for an error
//		free execution. A nonzero value usually means that an error has occurred.
// @xref	<mf YConApp::GetReturnCode>, <c YConApp>
YLB_INLINE void YConApp::SetReturnCode (int iReturn)
{
	m_iReturn = iReturn;
}



//
// overridables
//

// @mfunc	Override to perform that application's real work.
// @comm	Called by the framework after a successful call to <mf YConApp::InitInstance>.
//		<nl><nl>The default implementation of this function does nothing.
//		Override this function to perform the real work of your application.
YLB_INLINE void YConApp::Run ()
{
}



//
// advanced overridables
//
YLB_INLINE BOOL YConApp::OnCtrlC ()
{
	return FALSE;
}

YLB_INLINE BOOL YConApp::OnCtrlBreak ()
{
	return FALSE;
}

YLB_INLINE BOOL YConApp::OnClose ()
{
	return FALSE;
}

YLB_INLINE BOOL YConApp::OnLogoff ()
{
	return FALSE;
}

YLB_INLINE BOOL YConApp::OnShutdown ()
{
	return FALSE;
}

#ifdef _DEBUG

YLB_INLINE BOOL YConApp::OnCrtDebugReport (int reportType, LPCSTR pszMessage, int *iRetValue)
{
	return TRUE;
}

#endif

//
// EoF
////////