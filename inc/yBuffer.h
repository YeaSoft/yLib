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
 * Revision 1.4  2001/05/06 18:30:49  leopoldo
 * Improved YBuffer
 * Added new class YDynamicBuffer
 *
 * Revision 1.3  2000/10/25 09:19:22  leopoldo
 * Added assignment operations
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
class YBuffer
{
private:
	// kill these construction methods & operators
	YBuffer						(const YBuffer &);

public:
	// construction/destruction
	YBuffer						();
	YBuffer						(LPVOID lpBuffer, UINT cbSize);
	~YBuffer					();

public:
	// operations
	void						Attach					(LPVOID lpBuffer, UINT cbSize);
	LPVOID						Detach					(LPUINT lpcbSize = NULL);
	BOOL						Alloc					(UINT cbSize, BOOL fZeroInit = FALSE);
	BOOL						Realloc					(UINT cbSize, BOOL fAllocCopyFree = FALSE, BOOL fNoCopy = FALSE);
	void						Free					();
	void						Clear					(int iFill = 0);
	BOOL						Copy					(const YBuffer &srcBuffer, BOOL bDontReallocIfFits = TRUE);

public:
	// operators
	YBuffer &					operator=				(const YBuffer &srcBuffer) { Copy (srcBuffer, FALSE); return *this; }

public:
	// attributes
	UINT						GetSize					() const;
	LPVOID						GetBuffer				();
	LPCVOID						GetBuffer				() const;
	LPBYTE						GetByteBufferPtr		(UINT nOffset = 0);
	const BYTE *				GetByteBufferPtr		(UINT nOffset = 0) const;
	operator					LPVOID					();
	operator					LPCVOID					() const;
	operator					LPBYTE					();
	operator					const BYTE *			() const;

protected:
	// implementation
	UINT						m_cbSize;
	LPBYTE						m_lpPtr;
};

class YDynamicBuffer : public YBuffer
{
private:
	// kill these construction methods & operators
	YDynamicBuffer				(const YBuffer &);

public:
	// construction/destruction
	YDynamicBuffer				(UINT nAllocationIncrease = 0);
	YDynamicBuffer				(LPVOID lpBuffer, UINT cbSize, UINT cbContentSize = 0);

public:
	// operations
	void						Attach					(LPVOID lpBuffer, UINT cbSize, UINT cbContentSize = 0);
	LPVOID						Detach					(LPUINT lpcbContentSize = NULL, LPUINT lpcbSize = NULL);
	BOOL						Alloc					(UINT cbSize, BOOL fZeroInit = FALSE);
	BOOL						Realloc					(UINT cbSize, BOOL fAllocCopyFree = FALSE, BOOL fNoCopy = FALSE);
	void						Free					();
	BOOL						FreeExtra				();
	void						Clear					(int iFill = 0);
	BOOL						Copy					(const YDynamicBuffer &srcBuffer, BOOL bDontReallocIfFits = TRUE);

	BOOL						PushData				(LPCVOID lpData, UINT cbSize);
	BOOL						InsertData				(UINT nOffset, LPCVOID lpData, UINT cbSize);
	BOOL						ExtractData				(UINT nOffset, LPVOID lpData, UINT cbSize, UINT *pNumberOfBytesRead = NULL);
	BOOL						PopData					(LPVOID lpData, UINT cbSize, UINT *pNumberOfBytesRead = NULL);

	BOOL						PushString				(LPCSTR pszData);
	BOOL						PushString				(LPCWSTR pszData);

	BOOL						PushTerminatedString	(LPCSTR pszData);
	BOOL						PushTerminatedString	(LPCWSTR pszData);

	BOOL						IncreaseSize			(UINT cbIncrease);

public:
	// operators
	YDynamicBuffer &			operator=				(const YDynamicBuffer &srcBuffer) { Copy (srcBuffer, FALSE); return *this; }

public:
	// attributes
	UINT						GetContentSize			() const;
	UINT						GetAllocationIncrease	() const;
	void						SetAllocationIncrease	(UINT nAllocationIncrease = 0);

protected:
	// implementation
	UINT						m_cbContentSize;
	UINT						m_nAllocationIncrease;
};

#ifdef YLB_ENABLE_INLINE
#include <yBuffer.inl>
#endif

#endif //__yBuffer_h__
//
// EoF
////////