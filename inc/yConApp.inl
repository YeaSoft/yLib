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
 * FILENAME		:	yConApp.inl
 * PURPOSE		:	Inline members of the console application class
 * SCOPE		:	yAfc
 * HISTORY		: =============================================================
 * 
 * $Log$
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