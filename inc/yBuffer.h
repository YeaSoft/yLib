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
 * FILENAME		:	yBuffer.h
 * PURPOSE		:	Declaration of the generic buffer class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
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