/*=============================================================================
 * This is a part of the yLib Software Development Kit.
 * Copyright (C) 1998-2001 YEAsoft Int'l.
 * All rights reserved.
 *=============================================================================
 * Copyright (c) 1998-2001 YEAsoft Int'l (Leo Moll, Andrea Pennelli).
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
 * FILENAME		:	yBuffer.h
 * PURPOSE		:	Declaration of the generic buffer class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.8  2001/09/06 11:57:19  leopoldo
 * Added new initialisation methods
 *
 * Revision 1.7  2001/05/24 15:16:55  leopoldo
 * Added some new method
 * Changed size variables to int
 *
 * Revision 1.6  2001/05/22 16:57:47  leopoldo
 * Added more methods to YDynamicBuffer
 *
 * Revision 1.5  2001/05/21 18:53:30  leopoldo
 * Added more methods to YDynamicBuffer
 *
 * Revision 1.4  2001/05/06 18:30:49  leopoldo
 * Improved YBuffer
 * Added new class YDynamicBuffer
 *
 * Revision 1.3  2000/10/25 09:19:22  leopoldo
 * Addd assignment operations
 *
 * Revision 1.2  2000/09/04 11:59:53  leopoldo
 * Updated license to zlib/libpng
 *
 * Revision 1.1  2000/05/26 14:02:55  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yBuffer.h
 *============================================================================*/
#ifndef __yBuffer_h__
#define __yBuffer_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yLibBase_h__
#include <yLibBase.h>
#endif

/*=============================================================================
 * FORWARD CLASS DECLARATIONS
 *============================================================================*/
class YBuffer;

/*=============================================================================
 * CLASS DECLARATIONS
 *============================================================================*/
class YMemBlock
{
public:
	// construction/destruction
	YMemBlock					() { m_lpPtr = NULL; }
	YMemBlock					(const YMemBlock &memSrc) { m_lpPtr = memSrc.m_lpPtr; }
	YMemBlock					(const void *pSrc) { m_lpPtr = static_cast<BYTE *>(const_cast<void *>(pSrc)); }
	~YMemBlock					() { }

public:
	// operations
	void						Attach					(void *lpPtr) { m_lpPtr = static_cast<BYTE *>(lpPtr); }
	void *						Detach					();
	void						Move					(void *lpDest, const void *lpSrc, int cbCount) { memmove (lpDest, lpSrc, cbCount); }
	void						Move					(int iDestOffset, int iSrcOffset, int cbCount) { memmove (m_lpPtr + iDestOffset, m_lpPtr + iSrcOffset, cbCount); }
	void						Copy					(const void *lpPtr, int cbCount) { memcpy (m_lpPtr, lpPtr, cbCount); }
	void *						CopyUpTo				(const void *lpPtr, int iChar, int cbCount);
	void						Fill					(int iValue, int cbCount) { memset (m_lpPtr, iValue, cbCount); }
	int							Compare					(const void *lpPtr, int cbCount) const { return memcmp (m_lpPtr, lpPtr, cbCount); }
	int							CompareNoCase			(const void *lpPtr, int cbCount) const { return _memicmp (m_lpPtr, lpPtr, cbCount); }

public:
	// attributes
	BOOL						IsNull					() const { return m_lpPtr == NULL; }
	BOOL						IsNil					() const { return m_lpPtr == NULL; }

public:
	// attributes
	operator					LPVOID					() { return m_lpPtr; }
	operator					LPCVOID					() const { return m_lpPtr; }
	operator					LPBYTE					() { return m_lpPtr; }
	operator					const BYTE *			() const { return m_lpPtr; }
	const BYTE					operator[]				(int iPos) const { return m_lpPtr[iPos]; }
	BYTE &						operator[]				(int iPos) { return m_lpPtr[iPos]; }

protected:
	// implementation
	LPBYTE						m_lpPtr;
};

class YSizedMemBlock : public YMemBlock
{
public:
	// construction/destruction
	YSizedMemBlock				() { m_lpPtr = NULL; m_cbSize = 0; }
	YSizedMemBlock				(const YSizedMemBlock &memSrc) { m_lpPtr = memSrc.m_lpPtr; m_cbSize = memSrc.m_cbSize; }
	YSizedMemBlock				(const void *pSrc, int cbSize);
	~YSizedMemBlock				() { }

public:
	// operations
	BOOL						Attach					(void *lpPtr, int cbSize);
	void *						Detach					(int *lpcbSize = NULL);

public:
	// attributes
	int							GetSize					() const;

protected:
	// implementation
	int						m_cbSize;
};

class YBuffer
{
private:
	// kill these construction methods & operators
	YBuffer						(const YBuffer &);

public:
	// construction/destruction
	YBuffer						();
	YBuffer						(LPVOID lpBuffer, int cbSize);
	~YBuffer					();

public:
	// operations
	BOOL						Attach					(LPVOID lpBuffer, int cbSize);
	LPVOID						Detach					(LPINT lpcbSize = NULL);
	BOOL						Alloc					(const void *pData, int cbSize);
	BOOL						Alloc					(int cbSize, BOOL fZeroInit = FALSE);
	BOOL						Realloc					(int cbSize, BOOL fAllocCopyFree = FALSE, BOOL fNoCopy = FALSE);
	void						Free					();
	void						Clear					(int iFill = 0);
	BOOL						Copy					(const YBuffer &srcBuffer, BOOL bDontReallocIfFits = TRUE);
	BOOL						Copy					(const void *pData, int cbSize, BOOL bDontReallocIfFits = TRUE);

public:
	// operators
	YBuffer &					operator=				(const YBuffer &srcBuffer) { Copy (srcBuffer, FALSE); return *this; }

public:
	// attributes
	int							GetSize					() const;
	LPVOID						GetBuffer				();
	LPCVOID						GetBuffer				() const;
	LPBYTE						GetByteBufferPtr		(int nOffset = 0);
	const BYTE *				GetByteBufferPtr		(int nOffset = 0) const;
	operator					LPVOID					();
	operator					LPCVOID					() const;
	operator					LPBYTE					();
	operator					const BYTE *			() const;

protected:
	// implementation
	int							m_cbSize;
	LPBYTE						m_lpPtr;
};

class YDynamicBuffer : public YBuffer
{
private:
	// kill these construction methods & operators
	YDynamicBuffer				(const YBuffer &);

public:
	// construction/destruction
	YDynamicBuffer				(int nAllocationIncrease = 0);
	YDynamicBuffer				(LPVOID lpBuffer, int cbSize, int cbContentSize = 0);

public:
	// operations
	BOOL						Attach					(LPVOID lpBuffer, int cbSize, int cbContentSize = 0);
	LPVOID						Detach					(LPINT lpcbContentSize = NULL, LPINT lpcbSize = NULL);
	BOOL						Alloc					(int cbSize, BOOL fZeroInit = FALSE);
	BOOL						Realloc					(int cbSize, BOOL fAllocCopyFree = FALSE, BOOL fNoCopy = FALSE);
	void						Free					();
	BOOL						FreeExtra				();
	void						Clear					(int iFill = 0);
	BOOL						Copy					(const YDynamicBuffer &srcBuffer, BOOL bDontReallocIfFits = TRUE);
	void						Empty					(BOOL bFreeExtra = FALSE);

	BOOL						PushData				(LPCVOID lpData, int cbSize);
	BOOL						InsertData				(int nOffset, LPCVOID lpData, int cbSize);
	BOOL						ExtractData				(int nOffset, LPVOID lpData, int cbSize, LPINT pNumberOfBytesRead = NULL);
	BOOL						PopData					(LPVOID lpData, int cbSize, LPINT pNumberOfBytesRead = NULL);

	BOOL						PushString				(LPCSTR pszData);
	BOOL						PushString				(LPCWSTR pszData);
	BOOL						ExtractString			(int nOffset, LPSTR pszData, int cbSize);
	BOOL						ExtractString			(int nOffset, LPWSTR pszData, int cbSize);
	BOOL						PopString				(LPSTR pszData, int cbSize);
	BOOL						PopString				(LPWSTR pszData, int cbSize);

	BOOL						PushTerminatedString	(LPCSTR pszData);
	BOOL						PushTerminatedString	(LPCWSTR pszData);

	BOOL						IncreaseSize			(int cbIncrease);

public:
	// operators
	YDynamicBuffer &			operator=				(const YDynamicBuffer &srcBuffer) { Copy (srcBuffer, FALSE); return *this; }

public:
	// attributes
	BOOL						IsEmpty					() const;
	int							GetContentSize			() const;
	BOOL						SetContentSize			(int cbContentSize);
	int							GetAllocationIncrease	() const;
	void						SetAllocationIncrease	(int nAllocationIncrease = 0);

protected:
	// implementation
	int 						m_cbContentSize;
	int							m_nAllocationIncrease;
};

#ifdef YLB_ENABLE_INLINE
#include <yBuffer.inl>
#endif

#endif //__yBuffer_h__
//
// EoF
////////