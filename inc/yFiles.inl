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
 * FILENAME		:	yFiles.inl
 * PURPOSE		:	Inline members of the generic file classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26  14:03:05  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yFiles.h
 *============================================================================*/
YLB_INLINE YBaseFile::YBaseFile ()
{
}

YLB_INLINE BOOL YBaseFile::Flush ()
{
	ASSERTY(IsValid());
	return ::FlushFileBuffers (m_hHandle);
}

YLB_INLINE DWORD YBaseFile::Seek (LONG lDistanceToMove, DWORD dwMoveMethod)
{
	ASSERTY(IsValid());
	return ::SetFilePointer (m_hHandle, lDistanceToMove, NULL, dwMoveMethod);
}

YLB_INLINE DWORD YBaseFile::Seek (LONG lDistanceToMove, LPLONG lpDistanceToMoveHigh, DWORD dwMoveMethod)
{
	ASSERTY(IsValid());
	return ::SetFilePointer (m_hHandle, lDistanceToMove, lpDistanceToMoveHigh, dwMoveMethod);
}

YLB_INLINE BOOL YBaseFile::SeekToBegin ()
{
	return Seek (0) != ((DWORD) -1);
}

YLB_INLINE BOOL YBaseFile::SeekToEnd ()
{
	return Seek (0, FILE_END) != ((DWORD) -1);
}

YLB_INLINE DWORD YBaseFile::GetLength (LPDWORD lpdwSizeHigh) const
{
	ASSERTY(IsValid());
	return ::GetFileSize (m_hHandle, lpdwSizeHigh);
}

/*=============================================================================
 * THE GENERIC FILE CLASS
 *============================================================================*/
YLB_INLINE YFile::YFile ()
{
	Set (FLG_DAT_FILE);
}

YLB_INLINE BOOL YStdioFile::Read (LPVOID lpBuffer, DWORD nNumberOfBytesToRead)
{
	return Read (lpBuffer, nNumberOfBytesToRead, &m_dwBytesRead);
}

YLB_INLINE BOOL YStdioFile::Write (LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite)
{
	return Write (lpBuffer, nNumberOfBytesToWrite, &m_dwBytesWritten);
}

YLB_INLINE BOOL YFile::LockRange (DWORD dwPos, DWORD dwCount)
{
	ASSERTY(IsValid());
	return ::LockFile (m_hHandle, dwPos, 0, dwCount, 0);
}

YLB_INLINE BOOL YFile::UnlockRange (DWORD dwPos, DWORD dwCount)
{
	ASSERTY(IsValid());
	return ::UnlockFile (m_hHandle, dwPos, 0, dwCount, 0);
}

YLB_INLINE BOOL YFile::Unlock ()
{
	return TRUE;
}

YLB_INLINE BOOL YFile::Unlock (LONG lCount, LPLONG lpPrevCount /* = NULL */)
{
	return TRUE;
}

YLB_INLINE BOOL YFile::GetStatus (LPBY_HANDLE_FILE_INFORMATION pbhFI) const
{
	ASSERTY(IsValid());
	ASSERTY(pbhFI);
	return ::GetFileInformationByHandle (m_hHandle, pbhFI);
}

/*=============================================================================
 * THE STREAM FILE CLASS
 *============================================================================*/
YLB_INLINE YStdioFile::YStdioFile ()
{
	Set (FLG_DAT_FILE);
	m_pStream = NULL;
}

YLB_INLINE HANDLE YStdioFile::Detach ()
{
	// should not be used with YStdioFile
	ASSERTY(FALSE);
	return NULL;
}

YLB_INLINE BOOL YStdioFile::Flush ()
{
	return (IsValid ()) ? (fflush (m_pStream) == 0) : (FALSE);
}

YLB_INLINE BOOL YStdioFile::IsValid () const
{
	return YBaseFile::IsValid () && m_pStream;
}

//
// EoF
////////