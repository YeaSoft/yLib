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
 * FILENAME		:	yFiles.inl
 * PURPOSE		:	Inline members of the generic file classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
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