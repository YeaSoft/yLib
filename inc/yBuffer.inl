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
 * FILENAME		:	yBuffer.inl
 * PURPOSE		:	Inline members of the generic buffer class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.2  2000/09/04 11:59:53  leopoldo
 * Updated license to zlib/libpng
 *
 * Revision 1.1  2000/05/26 14:02:56  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yBuffer.h
 *============================================================================*/
YLB_INLINE YBuffer::YBuffer ()
{
	m_cbSize	= 0;
	m_lpPtr		= NULL;
}

YLB_INLINE YBuffer::YBuffer (LPVOID lpBuffer, UINT cbSize)
{
	ASSERTY((!lpBuffer && !cbSize) || (lpBuffer && cbSize));
	m_lpPtr		= lpBuffer;
	m_cbSize	= cbSize;
}

YLB_INLINE YBuffer::~YBuffer ()
{
	Free ();
}

YLB_INLINE UINT YBuffer::GetSize () const
{
	return m_cbSize;
}

YLB_INLINE LPVOID YBuffer::GetBuffer ()
{
	return m_lpPtr;
}

YLB_INLINE LPCVOID YBuffer::GetBuffer () const
{
	return m_lpPtr;
}

YLB_INLINE LPBYTE YBuffer::GetByteBufferPtr (int iOffset /* = 0 */)
{
	return ((LPBYTE) m_lpPtr) + iOffset;
}

YLB_INLINE YBuffer::operator LPVOID ()
{
	return m_lpPtr;
}

YLB_INLINE YBuffer::operator LPCVOID () const
{
	return m_lpPtr;
}

YLB_INLINE YBuffer::operator LPBYTE ()
{
	return (LPBYTE) m_lpPtr;
}

YLB_INLINE void YBuffer::Clear (int iFill)
{
	if ( m_lpPtr ) {
		memset (m_lpPtr, iFill, m_cbSize);
	}
}

/////////////////////////////

YLB_INLINE YDynamicBuffer::YDynamicBuffer (UINT nAllocationIncrease /* = 0 */)
{
	m_cbContentSize			= 0;
	m_nAllocationIncrease	= 0;
}

YLB_INLINE YDynamicBuffer::YDynamicBuffer (LPVOID lpBuffer, UINT cbSize, UINT cbContentSize /* = 0 */) : YBuffer (lpBuffer, cbSize)
{
	m_cbContentSize			= (cbContentSize < cbSize) ? (cbContentSize) : (cbSize);
	m_nAllocationIncrease	= 0;
}

YLB_INLINE void YDynamicBuffer::Attach (LPVOID lpBuffer, UINT cbSize, UINT cbContentSize /* = 0 */)
{
	YBuffer::Attach (lpBuffer, cbSize);
	m_cbContentSize = (cbContentSize < cbSize) ? (cbContentSize) : (cbSize);
}

YLB_INLINE void YDynamicBuffer::Free ()
{
	YBuffer::Free ();
	m_cbContentSize	= 0;
}

YLB_INLINE BOOL YDynamicBuffer::FreeExtra ()
{
	return Realloc (m_cbContentSize, FALSE, FALSE);
}

YLB_INLINE BOOL YDynamicBuffer::PushString (LPCSTR pszData)
{
	return PushData (pszData, strlen (pszData));
}

YLB_INLINE BOOL YDynamicBuffer::PushString (LPCWSTR pszData)
{
	return PushData (pszData, wcslen (pszData) * sizeof (WCHAR));
}

YLB_INLINE BOOL YDynamicBuffer::PushTerminatedString (LPCSTR pszData)
{
	return PushData (pszData, strlen (pszData) + 1);
}

YLB_INLINE BOOL YDynamicBuffer::PushTerminatedString (LPCWSTR pszData)
{
	return PushData (pszData, (wcslen (pszData) + 1) * sizeof (WCHAR));
}

YLB_INLINE UINT YDynamicBuffer::GetContentSize () const
{
	return m_cbContentSize;
}

YLB_INLINE UINT YDynamicBuffer::GetAllocationIncrease () const
{
	return m_nAllocationIncrease;
}

YLB_INLINE void YDynamicBuffer::SetAllocationIncrease (UINT nAllocationIncrease /* = 0 */)
{
	m_nAllocationIncrease = nAllocationIncrease;
}

//
// EoF
////////
