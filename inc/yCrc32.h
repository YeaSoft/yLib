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
 * FILENAME		:	yCrc32.h
 * PURPOSE		:	Declaration of the CRC Calculation Class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yCrc32.h
 *============================================================================*/
#ifndef __yCrc32_h__
#define __yCrc32_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yLibBase_h__
#include <yLibBase.h>
#endif

/*=============================================================================
 * CLASS DEFINITIONS
 *============================================================================*/
// @class CRC computing class
// @comm This class implements the calculation of CRC values for files
//		or any memory objects. It provides static members for file CRC
//		calculation or a cumulative member for memory obect calculation.
class YCrc32
{
public:
	// construction/destruction
	// @cmember Constructs a YCrc32 object
	YCrc32					();
	~YCrc32					() {}

public:
	// attributes
	// @cmember Computes the CRC of a file based on it's filehandle
	static DWORD			GetFileCrc				(HANDLE hFile);
	// @cmember Computes the CRC of a file based on it's filename
	static DWORD			GetFileCrc				(LPCTSTR lpName);
	// @cmember Updates the CRC using the supplied memory buffer
	void					UpdateCrc				(LPVOID lpBuffer, DWORD cbSize);
	// @cmember Returns the computed CRC value
	DWORD					GetCrc					();
	// @cmember Resets the internal CRC value for a new computation
	void					ResetCrc				();


private:
	static DWORD			UpdateCrc				(LPSTR lpBuffer, DWORD cbSize, DWORD dwAccum);

private:
	DWORD					m_dwCrc;
	static DWORD			m_dwTable[256];
};
// @ex Calculation of the CRC of a file |
//
//	...
//	DWORD dwCrc = YCrc32::GetFileCrc ("e:\\mrs\\bin\\NameLoc.exe");
//	printf ("The CRC value of the Name Locator is 0x%08x", dwCrc);
//	...
//
// @ex Calculation of the CRC of a memory block |
//
//	...
//	/* in our example we calculate the CRC over all the filenames in a */
//	/* given directory to check if it's contents has changed.. */
//	HANDLE			hFind;
//	WIN32_FIND_DATA	wfd;
//	if ( !(hFind = FindFirstFile ("*.*", &wfd)) ) {
//		return FALSE;
//	}
//	YCrc32	crc;
//	do {
//		crc.UpdateCrc (wfd.cFileName, _tcslen (wfd.cFileName));
//	} while ( FindNextFile (hFind, &wfd) );
//	FindClose (hFind);
//	printf ("The CRC of this directory is: 0x%08x", crc.GetCrc ());
//
// @xref <j File Related Classes>, <j Needful Things>

#ifdef YLB_ENABLE_INLINE
#include <yCrc32.inl>
#endif

#endif //__yCrc32_h__

//
// EoF
////////