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
 * FILENAME		:	yCrc32.h
 * PURPOSE		:	Declaration of the CRC Calculation Class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.2  2000/09/04 11:59:53  leopoldo
 * Updated license to zlib/libpng
 *
 * Revision 1.1  2000/05/26 14:03:00  leo
 * Initial revision
 *
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
	void					UpdateCrc				(LPVOID lpBuffer, UINT cbSize);
	// @cmember Returns the computed CRC value
	DWORD					GetCrc					();
	// @cmember Resets the internal CRC value for a new computation
	void					ResetCrc				();
	// @cmember Returns the CRC of a buffer
	static DWORD			GetBufferCrc			(LPVOID lpBuffer, UINT cbSize);
	// @cmember Returns the CRC of a string
	static DWORD			GetStringCrc			(LPCTSTR pszString);


private:
	static DWORD			UpdateCrc				(LPSTR lpBuffer, UINT cbSize, DWORD dwAccum);

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