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
 * FILENAME		:	yBuffer.h
 * PURPOSE		:	Declaration of the generic buffer class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
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
	YBuffer						&operator=				(const YBuffer &);

public:
	// construction/destruction
	YBuffer						();
	~YBuffer					();

public:
	// operations
	void						Attach					(LPVOID lpBuffer, UINT cbSize);
	LPVOID						Detach					(LPUINT lpcbSize = NULL);
	BOOL						Alloc					(UINT cbSize, BOOL fZeroInit = FALSE);
	BOOL						Realloc					(UINT cbSize, BOOL fAllocCopyFree = FALSE, BOOL fNoCopy = FALSE);
	void						Free					();
	void						Clear					(int iFill = 0);

public:
	// attributes
	UINT						GetSize					() const;
	LPVOID						GetBuffer				() const;
	operator					LPVOID					() const;

protected:
	// implementation
	UINT						m_cbSize;
	LPVOID						m_lpPtr;
};

#ifdef YLB_ENABLE_INLINE
#include <yBuffer.inl>
#endif

#endif //__yBuffer_h__
//
// EoF
////////