/*=============================================================================
 * This is a part of the yLib Software Development Kit.
 * Copyright (C) 1998-2001 YEAsoft Int'l.
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
 * FILENAME		:	yArray.h
 * PURPOSE		:	Declaration of the generic array classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yArray.h
 *============================================================================*/
#ifndef __yArray_h__
#define __yArray_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yLibBase_h__
#include <yLibBase.h>
#endif

/*=============================================================================
 * POINTER ARRAYS
 *============================================================================*/
class YPtrArray
{
private:
	// kill these construction methods & operators
	YPtrArray					(const YPtrArray &);

public:
	// construction/destruction
	YPtrArray					(int nAllocationGranularity = -1);
	~YPtrArray					();

public:
	// operations
	BOOL						FreeExtra				();
	void						RemoveAll				();

	LPVOID						GetAt					(int nIndex) const;
	BOOL						SetAt					(int nIndex, LPVOID newElement);
	BOOL						SetAtGrow				(int nIndex, LPVOID newElement);
	int							Add						(LPVOID newElement);

	LPVOID &					ElementAt				(int nIndex);
	const LPVOID *				GetData					() const;
	LPVOID *					GetData					();

	int							Append					(const YPtrArray & src);
	BOOL						Copy					(const YPtrArray & src);

	LPVOID						operator[]				(int nIndex) const;
	LPVOID &					operator[]				(int nIndex);

	BOOL						InsertAt				(int nIndex, YPtrArray * pNewArray);
	BOOL						InsertAt				(int nIndex, const YPtrArray & src);
	BOOL						InsertAt				(int nIndex, LPVOID newElement, int nCount = 1);
	int							RemoveAt				(int nIndex, int nCount = 1);

public:
	// attributes
	int							GetSize					() const;
	BOOL						SetSize					(int nNewSize, int nAllocationGranularity = -1);
	int							GetAllocatedSize		() const;
	BOOL						SetAllocatedSize		(int nNewSize);
	int							GetUpperBound			() const;

protected:
	// implementation
	LPVOID *					m_pData;
	int							m_nSize;
	int							m_nAllocatedSize;
	int							m_nAllocationGranularity;
};

template<class TYPE>
class YTypedPtrArray : public YPtrArray
{
public:
	// construction/destruction
	YTypedPtrArray<TYPE>		(int nAllocationGranularity = -1) : YPtrArray (nAllocationGranularity) { }

public:
	// operations
	TYPE						GetAt					(int nIndex) const { return (TYPE) YPtrArray::GetAt (nIndex); }
	BOOL						SetAt					(int nIndex, TYPE newElement) { return YPtrArray::SetAt (nIndex, newElement); }
	BOOL						SetAtGrow				(int nIndex, TYPE newElement) { return YPtrArray::SetAtGrow (nIndex, newElement); }
	int							Add						(TYPE newElement) { return YPtrArray::Add (newElement); }

	TYPE &						ElementAt				(int nIndex) { return (TYPE &) YPtrArray::ElementAt (nIndex); }
	const TYPE *				GetData					() const { return (const TYPE) YPtrArray::GetData (); }
	TYPE *						GetData					() { return (TYPE) YPtrArray::GetData (); }

	TYPE						operator[]				(int nIndex) const { return (TYPE) YPtrArray::operator[] (nIndex); }
	TYPE &						operator[]				(int nIndex) { return (TYPE &) YPtrArray::operator[] (nIndex); }

	BOOL						InsertAt				(int nIndex, TYPE newElement, int nCount = 1) { return YPtrArray::InsertAt (nIndex, newElement, nCount); }
};


#ifdef YLB_ENABLE_INLINE
#include <yArray.inl>
#endif

#endif //__yArray_h__
//
// EoF
////////