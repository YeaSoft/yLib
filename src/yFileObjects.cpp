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
 * FILENAME		:	yFileObjects.cpp
 * PURPOSE		:	File utility objects
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yFileObjects.h
 *============================================================================*/
#include "StdInc.hpp"

/*=============================================================================
 * ATTRIBUTE HANDLING
 *============================================================================*/
DWORD		YFileAttributes::FAFLG_NAMEPRESENT		= 0x00000001;
DWORD		YFileAttributes::FAFLG_ATTRIBLOADED		= 0x00000002;
DWORD		YFileAttributes::FAFLG_CRCLOADED		= 0x00000004;
DWORD		YFileAttributes::FAFLG_VERSIONLOADED	= 0x00000008;
DWORD		YFileAttributes::FAFLG_CACHING			= 0x00000010;

YFileAttributes::YFileAttributes (BOOL bCaching /* = TRUE */)
{
	*m_szFileName		= 0;
	ChangeFlags (FAFLG_CACHING, bCaching);
}

YFileAttributes::YFileAttributes (LPCTSTR lpszFileName, ...)
{
	va_list			va;

	va_start (va, lpszFileName);
	_vstprintf (m_szFileName, lpszFileName, va);
	va_end (va);
	m_viVersion.SetName (m_szFileName);
	SetFlags (FAFLG_CACHING);
	ChangeFlags (FAFLG_NAMEPRESENT, *lpszFileName != 0);
}

void YFileAttributes::SetName (LPCTSTR lpszFileName, ...)
{
	va_list			va;

	va_start (va, lpszFileName);
	_vstprintf (m_szFileName, lpszFileName, va);
	va_end (va);
	m_viVersion.SetName (m_szFileName);
	ClearFlags (~(DWORD)FAFLG_CACHING);
	ChangeFlags (FAFLG_NAMEPRESENT, *lpszFileName != 0);
}

void YFileAttributes::SetCacheState (BOOL bCaching /* = TRUE */)
{
	ClearFlags (~(DWORD)FAFLG_NAMEPRESENT);
	ChangeFlags (FAFLG_CACHING, bCaching);
}


DWORD YFileAttributes::GetFileCrc ()
{
	if ( !TestFlags (FAFLG_NAMEPRESENT | FAFLG_CRCLOADED | FAFLG_CACHING) ) {
		LoadCrc ();
	}
	if ( !TestFlags (FAFLG_NAMEPRESENT | FAFLG_CRCLOADED ) ) {
		return 0;
	}
	return m_dwCrc;
}

DWORD YFileAttributes::GetFileSize (LPDWORD lpdwSizeHi /* = NULL */)
{
	if ( !TestFlags (FAFLG_NAMEPRESENT | FAFLG_ATTRIBLOADED | FAFLG_CACHING) ) {
		LoadAttribs ();
	}
	if ( !TestFlags (FAFLG_NAMEPRESENT | FAFLG_ATTRIBLOADED) ) {
		if ( lpdwSizeHi ) {
			*lpdwSizeHi = 0;
		}
		return 0;
	}
	if ( m_wfdAttr.nFileSizeHigh ) {
		if ( lpdwSizeHi ) {
			*lpdwSizeHi = m_wfdAttr.nFileSizeHigh;
		}
		else {
			return (DWORD) -1;
		}
	}
	return m_wfdAttr.nFileSizeLow;
}

const YVersInfo &YFileAttributes::GetFileVersion ()
{
	if ( !TestFlags (FAFLG_NAMEPRESENT | FAFLG_VERSIONLOADED | FAFLG_CACHING) ) {
		LoadVersion ();
	}
	return m_viVersion;
}

DWORD YFileAttributes::GetFileAttribs ()
{
	if ( !TestFlags (FAFLG_NAMEPRESENT | FAFLG_ATTRIBLOADED | FAFLG_CACHING) ) {
		LoadAttribs ();
	}
	if ( !TestFlags (FAFLG_NAMEPRESENT | FAFLG_ATTRIBLOADED) ) {
		return 0;
	}
	return m_wfdAttr.dwFileAttributes;
}

BOOL YFileAttributes::SetFileAttribs (DWORD dwAdd, DWORD dwRemove)
{
	DWORD dwAttr = GetFileAttributes (m_szFileName);
	if ( dwAttr == (DWORD) -1 )
		return FALSE;
	dwAttr |= dwAdd;
	dwAttr &= ~(DWORD) dwRemove;
	if ( SetFileAttributes (m_szFileName, dwAttr) ) {
		ClearFlags (FAFLG_ATTRIBLOADED);
		return TRUE;
	}
	return FALSE;
}

const YVersInfo& YFileAttributes::operator= (YFileAttributes &cfa)
{
	m_viVersion = cfa.GetFileVersion ();
	return m_viVersion;
}

BOOL YFileAttributes::LoadCrc ()
{
	HANDLE hFile = ::CreateFile (
		m_szFileName,
		GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
		NULL
	);
	if ( hFile == INVALID_HANDLE_VALUE ) {
		ClearFlags (FAFLG_CRCLOADED);
		return FALSE;
	}
	m_dwCrc = YCrc32::GetFileCrc (hFile);
	::CloseHandle (hFile);
	SetFlags (FAFLG_CRCLOADED);
	return TRUE;
}

BOOL YFileAttributes::LoadAttribs ()
{
	HANDLE	hFind = ::FindFirstFile (m_szFileName, &m_wfdAttr);
	if ( hFind == INVALID_HANDLE_VALUE ) {
		memset (&m_wfdAttr, 0, sizeof (m_wfdAttr));
		ClearFlags (FAFLG_ATTRIBLOADED);
		return FALSE;
	}
	while ( (m_wfdAttr.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
		if ( !::FindNextFile (hFind, &m_wfdAttr) ) {
			::FindClose (hFind);
			memset (&m_wfdAttr, 0, sizeof (m_wfdAttr));
			ClearFlags (FAFLG_ATTRIBLOADED);
			return FALSE;
		}
	}
	::FindClose (hFind);
	SetFlags (FAFLG_ATTRIBLOADED);
	return TRUE;
}

BOOL YFileAttributes::LoadVersion ()
{
	m_viVersion.UnloadInfo ();
	ChangeFlags (FAFLG_VERSIONLOADED, m_viVersion.LoadInfo ());
	return TestFlags (FAFLG_VERSIONLOADED);
}

#ifndef YLB_ENABLE_INLINE
#include <yFileObjects.inl>
#endif

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////