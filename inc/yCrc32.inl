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
 * FILENAME		:	yCrc32.inl
 * PURPOSE		:	Inline members of the CRC Calculation Class
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

// @mfunc Constructs a <c YCrc32> object
// @xref <c YCrc32>
YLB_INLINE YCrc32::YCrc32 ()
{
	m_dwCrc = 0;
}

YLB_INLINE DWORD YCrc32::GetBufferCrc (LPVOID lpBuffer, UINT cbSize)
{
	return UpdateCrc ((LPSTR) lpBuffer, cbSize, 0);
}

YLB_INLINE DWORD YCrc32::GetStringCrc (LPCTSTR pszString)
{
	return UpdateCrc ((LPSTR) pszString, _tcslen (pszString) * sizeof (TCHAR), 0);
}


// @mfunc Updates the CRC using the supplied memory buffer
// @parm LPVOID | lpBuffer | Pointer to the buffer containing the data
//		to be used for the CRC computation
// @parm DWORD | cbSize | Length in bytes of the supplied buffer
// @comm Call this member function to update the internal CRC value
//		with the contents of the supplied memory buffer
// @xref <mf YCrc32::GetCrc>, <mf YCrc32::ResetCrc>, <c YCrc32>
YLB_INLINE void YCrc32::UpdateCrc (LPVOID lpBuffer, UINT cbSize)
{
	m_dwCrc = UpdateCrc ((LPSTR) lpBuffer, cbSize, m_dwCrc);
}

// @mfunc Returns the computed CRC value
// @rdesc The computed CRC values after one or more calls to
//		<mf YCrc32::UpdateCrc>
// @comm Call this member function to get the computed CRC value
//		after one or more calls to the member function <mf YCrc32::UpdateCrc>.
//		If you wish to start a new CRC computation, you can reset the
//		internal CRC system by calling <mf YCrc32::ResetCrc>
// @xref <mf YCrc32::UpdateCrc>, <mf YCrc32::ResetCrc>, <c YCrc32>
YLB_INLINE DWORD YCrc32::GetCrc ()
{
	return m_dwCrc;
}

// @mfunc Resets the internal CRC value for a new computation
// @comm Use this function to reset the internal values of the CRC
//		computation system if you want to perform a new CRC
//		computation.
// @xref <mf YCrc32::UpdateCrc>, <mf YCrc32::GetCrc>, <c YCrc32>
YLB_INLINE void YCrc32::ResetCrc ()
{
	m_dwCrc = 0;
}

//
// EoF
////////