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
 * Revision 1.2  2001/04/19 17:30:20  leopoldo
 * Added new template YTypedAllocatedPtrArray
 *
 * Revision 1.1  2001/04/12 18:42:56  leopoldo
 * Initial revision
 *
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
 * BASE CLASS
 *============================================================================*/
#define SZHEU_CLEAR				0
#define SZHEU_DONOTHING			-1
#define SZHEU_SMALLER			-2
#define SZHEU_BIGGER			-3
#define SZHEU_NEGATIVE			-4
#define SZHEU_OVERFLOW			-5

class YBaseArray
{
public:
	// construction
	YBaseArray					(int nAllocationGranularity = -1);
	YBaseArray					(const YBaseArray &src);

public:
	// attributes
	int							GetSize					() const;
	int							GetAllocatedSize		() const;
	int							GetUpperBound			() const;

protected:
	// implementation
	int							SizeHeuristic			(int nNewSize, int nAllocationGranularity);

protected:
	// implementation
	int							m_nSize;
	int							m_nAllocatedSize;
	int							m_nAllocationGranularity;
};

/*=============================================================================
 * INTEGRAL ARRAYS
 *============================================================================*/
class YIntArray : public YBaseArray
{

public:
	// construction/destruction
	YIntArray					(int nAllocationGranularity = -1);
	YIntArray					(const YIntArray &src);				// may fail...
	~YIntArray					();

public:
	// operations
	BOOL						FreeExtra				();
	void						RemoveAll				();

	int							Find					(int theElement) const;
	int							GetAt					(int nIndex) const;
	BOOL						SetAt					(int nIndex, int newElement);
	BOOL						SetAtGrow				(int nIndex, int newElement);
	int							Add						(int newElement);

	int &						ElementAt				(int nIndex);
	const int *					GetData					() const;
	int *						GetData					();

	int							Append					(const YIntArray & src);
	BOOL						Copy					(const YIntArray & src);

	BOOL						InsertAt				(int nIndex, YIntArray * pNewArray);
	BOOL						InsertAt				(int nIndex, const YIntArray & src);
	BOOL						InsertAt				(int nIndex, int newElement, int nCount = 1);
	int							RemoveAt				(int nIndex, int nCount = 1);
	BOOL						Remove					(int theElement);

public:
	// operators
	YIntArray &					operator=				(const YIntArray & src);
	operator					const int *				() const;
	operator					int *					();
	int							operator[]				(int nIndex) const;
	int &						operator[]				(int nIndex);

public:
	// attributes
	BOOL						SetSize					(int nNewSize, int nAllocationGranularity = -1);
	BOOL						SetAllocatedSize		(int nNewSize);

protected:
	// implementation
	int *						m_pData;
};

class YShortArray : public YBaseArray
{

public:
	// construction/destruction
	YShortArray					(int nAllocationGranularity = -1);
	YShortArray					(const YShortArray &src);				// may fail...
	~YShortArray				();

public:
	// operations
	BOOL						FreeExtra				();
	void						RemoveAll				();

	int							Find					(short theElement) const;
	short						GetAt					(int nIndex) const;
	BOOL						SetAt					(int nIndex, short newElement);
	BOOL						SetAtGrow				(int nIndex, short newElement);
	int							Add						(short newElement);

	short &						ElementAt				(int nIndex);
	const short *				GetData					() const;
	short *						GetData					();

	int							Append					(const YShortArray & src);
	BOOL						Copy					(const YShortArray & src);

	BOOL						InsertAt				(int nIndex, YShortArray * pNewArray);
	BOOL						InsertAt				(int nIndex, const YShortArray & src);
	BOOL						InsertAt				(int nIndex, short newElement, int nCount = 1);
	int							RemoveAt				(int nIndex, int nCount = 1);
	BOOL						Remove					(short theElement);

public:
	// operators
	YShortArray &				operator=				(const YShortArray & src);
	operator					const short *			() const;
	operator					short *					();
	short						operator[]				(int nIndex) const;
	short &						operator[]				(int nIndex);

public:
	// attributes
	BOOL						SetSize					(int nNewSize, int nAllocationGranularity = -1);
	BOOL						SetAllocatedSize		(int nNewSize);

protected:
	// implementation
	short *						m_pData;
};

class YCharArray : public YBaseArray
{

public:
	// construction/destruction
	YCharArray					(int nAllocationGranularity = -1);
	YCharArray					(const YCharArray &src);				// may fail...
	~YCharArray					();

public:
	// operations
	BOOL						FreeExtra				();
	void						RemoveAll				();

	int							Find					(char theElement) const;
	char						GetAt					(int nIndex) const;
	BOOL						SetAt					(int nIndex, char newElement);
	BOOL						SetAtGrow				(int nIndex, char newElement);
	int							Add						(char newElement);

	char &						ElementAt				(int nIndex);
	const char *				GetData					() const;
	char *						GetData					();

	int							Append					(const YCharArray & src);
	BOOL						Copy					(const YCharArray & src);

	BOOL						InsertAt				(int nIndex, YCharArray * pNewArray);
	BOOL						InsertAt				(int nIndex, const YCharArray & src);
	BOOL						InsertAt				(int nIndex, char newElement, int nCount = 1);
	int							RemoveAt				(int nIndex, int nCount = 1);
	BOOL						Remove					(char theElement);

public:
	// operators
	YCharArray &				operator=				(const YCharArray & src);
	operator					const char *			() const;
	operator					char *					();
	char						operator[]				(int nIndex) const;
	char &						operator[]				(int nIndex);

public:
	// attributes
	BOOL						SetSize					(int nNewSize, int nAllocationGranularity = -1);
	BOOL						SetAllocatedSize		(int nNewSize);

protected:
	// implementation
	char *						m_pData;
};

template<class BASE, class TYPE>
class YIntegralArray : public BASE
{
public:
	// construction/destruction
	YIntegralArray<BASE,TYPE>							(int nAllocationGranularity = -1) : BASE (nAllocationGranularity) { }
	YIntegralArray<BASE,TYPE>							(const YIntegralArray<BASE,TYPE> &src) : BASE (src) { }

public:
	// operations
	int							Find					(TYPE theElement) const { return BASE::Find ((int) theElement); }
	TYPE						GetAt					(int nIndex) const { return (TYPE) BASE::GetAt (nIndex); }
	BOOL						SetAt					(int nIndex, TYPE newElement) { return BASE::SetAt (nIndex, (int) newElement); }
	BOOL						SetAtGrow				(int nIndex, TYPE newElement) { return BASE::SetAtGrow (nIndex, (int) newElement); }
	int							Add						(TYPE newElement) { return BASE::Add ((int) newElement); }

	TYPE &						ElementAt				(int nIndex) { return (TYPE &) BASE::ElementAt (nIndex); }
	const TYPE *				GetData					() const { return (const TYPE) BASE::GetData (); }
	TYPE *						GetData					() { return (TYPE) BASE::GetData (); }

	int							Append					(const YIntegralArray<BASE,TYPE> & src) { return BASE::Append (src); }
	BOOL						Copy					(const YIntegralArray<BASE,TYPE> & src) { return BASE::Copy (src); }

	BOOL						InsertAt				(int nIndex, YIntegralArray<BASE,TYPE> * pNewArray) { return BASE::InsertAt (nIndex, pNewArray); }
	BOOL						InsertAt				(int nIndex, const YIntegralArray<BASE,TYPE> & src) { return BASE::InsertAt (nIndex, src); }
	BOOL						InsertAt				(int nIndex, TYPE newElement, int nCount = 1) { return BASE::InsertAt (nIndex, (int) newElement, nCount); }
	BOOL						Remove					(TYPE theElement) { return BASE::Remove ((int) theElement); }

public:
	// operators
	YIntegralArray<BASE,TYPE> &	operator=				(const YIntegralArray<BASE,TYPE> & src) { Copy (src); return *this; }
	operator					const TYPE *			() const { return (const TYPE *) BASE::operator const int * (); }
	operator					TYPE *					() { return (TYPE *) BASE::operator int * (); }
	TYPE						operator[]				(int nIndex) const { return (TYPE) BASE::operator[] (nIndex); }
	TYPE &						operator[]				(int nIndex) { return (TYPE &) BASE::operator[] (nIndex); }

};

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

	int							Find					(LPVOID pElement) const;
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
	BOOL						Remove					(LPVOID pElement);

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
	int							Find					(TYPE pElement) const { return YPtrArray::Find (pElement); }
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
	BOOL						Remove					(TYPE pElement) { return YPtrArray::Remove (pElement); }
};

template<class TYPE, class CREATIONTYPE>
class YTypedAllocatedPtrArray : public YPtrArray
{
public:
	// construction/destruction
	YTypedAllocatedPtrArray<TYPE, CREATIONTYPE>			(int nAllocationGranularity = -1) : YPtrArray (nAllocationGranularity) { }
	~YTypedAllocatedPtrArray<TYPE, CREATIONTYPE>		() { RemoveAll (); }

public:
	// operations
	void						RemoveAll				(BOOL bFreeAllocated = TRUE);

	int							Find					(TYPE pElement) const { return YPtrArray::Find (pElement); }
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
	int							RemoveAt				(int nIndex, int nCount = 1, BOOL bFreeAllocated = TRUE);
	BOOL						Remove					(TYPE pElement, BOOL bFreeAllocated = TRUE);
};

template<class TYPE, class CREATIONTYPE>
void YTypedAllocatedPtrArray<TYPE, CREATIONTYPE>::RemoveAll (BOOL bFreeAllocated)
{
	if ( bFreeAllocated ) {
		for ( int i = 0; i < m_nSize; i++ ) {
			delete GetAt (i);
		}
	}

	YPtrArray::RemoveAll ();
}

template<class TYPE, class CREATIONTYPE>
BOOL YTypedAllocatedPtrArray<TYPE, CREATIONTYPE>::Remove (TYPE pElement, BOOL bFreeAllocated)
{
	if ( bFreeAllocated ) {
		if ( YPtrArray::Remove (pElement) ) {
			delete pElement;
			return TRUE;
		}
		return FALSE;
	}
	return YPtrArray::Remove (pElement);
}

template<class TYPE, class CREATIONTYPE>
int YTypedAllocatedPtrArray<TYPE, CREATIONTYPE>::RemoveAt (int nIndex, int nCount, BOOL bFreeAllocated)
{
	if ( bFreeAllocated ) {
		int nTop = min(nIndex + nCount,m_nSize);
		for ( int i = nIndex; (i >= 0) && (i < nTop); i++ ) {
			delete GetAt (i);
		}
	}
	return YPtrArray::RemoveAt (nIndex, nCount);
}

#ifdef YLB_ENABLE_INLINE
#include <yArray.inl>
#endif

#endif //__yArray_h__
//
// EoF
////////