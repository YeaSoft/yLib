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
 * Revision 1.5  2001/05/10 10:26:15  leopoldo
 * Fixed array bugs and harmonized YPtrArray
 *
 * Revision 1.4  2001/05/09 23:12:02  leopoldo
 * Added some inactive stuff
 *
 * Revision 1.3  2001/05/06 18:31:31  leopoldo
 * Improved arrays
 * Added cardinal array types
 *
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
class YPtrArray : public YBaseArray
{
public:
	// construction/destruction
	YPtrArray					(int nAllocationGranularity = -1);
	YPtrArray					(const YPtrArray &src);				// may fail...
	~YPtrArray					();

public:
	// operations
	BOOL						FreeExtra				();
	void						RemoveAll				();

	int							Find					(LPVOID theElement) const;
	LPVOID						GetAt					(int nIndex) const;
	BOOL						SetAt					(int nIndex, LPVOID newElement);
	BOOL						SetAtGrow				(int nIndex, LPVOID newElement);
	int							Add						(LPVOID newElement);

	LPVOID &					ElementAt				(int nIndex);
	const LPVOID *				GetData					() const;
	LPVOID *					GetData					();

	int							Append					(const YPtrArray & src);
	BOOL						Copy					(const YPtrArray & src);

	BOOL						InsertAt				(int nIndex, YPtrArray * pNewArray);
	BOOL						InsertAt				(int nIndex, const YPtrArray & src);
	BOOL						InsertAt				(int nIndex, LPVOID newElement, int nCount = 1);
	int							RemoveAt				(int nIndex, int nCount = 1);
	BOOL						Remove					(LPVOID theElement);

public:
	// operators
	YPtrArray &					operator=				(const YPtrArray & src);
	operator					const LPVOID *			() const;
	operator					LPVOID *				();
	LPVOID						operator[]				(int nIndex) const;
	LPVOID &					operator[]				(int nIndex);

public:
	// attributes
	BOOL						SetSize					(int nNewSize, int nAllocationGranularity = -1);
	BOOL						SetAllocatedSize		(int nNewSize);

protected:
	// implementation
	LPVOID *					m_pData;
};

template<class TYPE>
class YTypedPtrArray : public YPtrArray
{
public:
	// construction/destruction
	YTypedPtrArray<TYPE>								(int nAllocationGranularity = -1) : YPtrArray (nAllocationGranularity) { }
	YTypedPtrArray<TYPE>								(const YTypedPtrArray<TYPE> &src) : YPtrArray (src) { }

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


	BOOL						InsertAt				(int nIndex, YTypedPtrArray<TYPE> * pNewArray) { return YPtrArray::InsertAt (nIndex, pNewArray); }
	BOOL						InsertAt				(int nIndex, const YTypedPtrArray<TYPE> & src) { return YPtrArray::InsertAt (nIndex, src); }
	BOOL						InsertAt				(int nIndex, TYPE newElement, int nCount = 1) { return YPtrArray::InsertAt (nIndex, newElement, nCount); }
	BOOL						Remove					(TYPE theElement) { return YPtrArray::Remove (theElement); }

public:
	// operators
	YTypedPtrArray<TYPE> &		operator=				(const YTypedPtrArray<TYPE> & src) { Copy (src); return *this; }
	operator					const TYPE *			() const { return (const TYPE *) YPtrArray::operator const LPVOID * (); }
	operator					TYPE *					() { return (TYPE *) YPtrArray::operator LPVOID * (); }
	TYPE						operator[]				(int nIndex) const { return (TYPE) YPtrArray::operator[] (nIndex); }
	TYPE &						operator[]				(int nIndex) { return (TYPE &) YPtrArray::operator[] (nIndex); }
};

template<class TYPE, class CREATIONTYPE>
class YTypedAllocatedPtrArray : public YPtrArray
{
public:
	// construction/destruction
	YTypedAllocatedPtrArray<TYPE,CREATIONTYPE>			(int nAllocationGranularity = -1) : YPtrArray (nAllocationGranularity) { }
//	YTypedAllocatedPtrArray<TYPE,CREATIONTYPE>			(const YTypedAllocatedPtrArray<TYPE,CREATIONTYPE> &src);
	~YTypedAllocatedPtrArray<TYPE,CREATIONTYPE>			() { RemoveAll (); }


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


//	BOOL						InsertAt				(int nIndex, YTypedAllocatedPtrArray<TYPE,CREATIONTYPE> * pNewArray);
//	BOOL						InsertAt				(int nIndex, const YTypedAllocatedPtrArray<TYPE,CREATIONTYPE> & src);
	BOOL						InsertAt				(int nIndex, TYPE newElement, int nCount = 1) { return YPtrArray::InsertAt (nIndex, newElement, nCount); }
	int							RemoveAt				(int nIndex, int nCount = 1, BOOL bFreeAllocated = TRUE);
	BOOL						Remove					(TYPE pElement, BOOL bFreeAllocated = TRUE);

public:
	// operators
//	YTypedAllocatedPtrArray<TYPE,CREATIONTYPE> &	operator=	(const YTypedAllocatedPtrArray<TYPE,CREATIONTYPE> & src) { Copy (src); return *this; }
	operator					const TYPE *			() const { return (const TYPE *) YPtrArray::operator const LPVOID * (); }
	operator					TYPE *					() { return (TYPE *) YPtrArray::operator LPVOID * (); }
	TYPE						operator[]				(int nIndex) const { return (TYPE) YPtrArray::operator[] (nIndex); }
	TYPE &						operator[]				(int nIndex) { return (TYPE &) YPtrArray::operator[] (nIndex); }
};

template<class TYPE, class CREATIONTYPE>
void YTypedAllocatedPtrArray<TYPE, CREATIONTYPE>::RemoveAll (BOOL bFreeAllocated)
{
	if ( bFreeAllocated ) {
		for ( int i = 0; i < m_nSize; i++ ) {
			TYPE lpPtr = GetAt (i);
			if ( lpPtr ) {
				delete lpPtr;
			}
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
		int nTop = MIN(nIndex + nCount,m_nSize);
		for ( int i = nIndex; (i >= 0) && (i < nTop); i++ ) {
			TYPE lpPtr = GetAt (i);
			if ( lpPtr ) {
				delete lpPtr;
			}
		}
	}
	return YPtrArray::RemoveAt (nIndex, nCount);
}

/*=============================================================================
 * GENERIC DATA ARRAY
 *============================================================================*/
template<class TYPE>
class YDataArray : public YBaseArray
{

public:
	// construction/destruction
	YDataArray<TYPE>			(int nAllocationGranularity = -1) : YBaseArray (nAllocationGranularity) { m_pData = NULL; }
	YDataArray<TYPE>			(const YDataArray<TYPE> &src) { m_pData = NULL; Copy (src); }	// may fail...
	~YDataArray<TYPE>			() { RemoveAll (); }

public:
	// operations
	BOOL						FreeExtra				() { return SetAllocatedSize (m_nSize); }
	void						RemoveAll				();

	int							Find					(TYPE theElement) const;
	TYPE						GetAt					(int nIndex) const;
	BOOL						SetAt					(int nIndex, TYPE newElement);
	BOOL						SetAtGrow				(int nIndex, TYPE newElement);
	int							Add						(TYPE newElement) { return (SetAtGrow (m_nSize, newElement)) ? (m_nSize - 1) : (-1); }

	TYPE &						ElementAt				(int nIndex);
	const TYPE *				GetData					() const { return (const TYPE *) m_pData; }
	TYPE *						GetData					() { return (TYPE *) m_pData; }

	int							Append					(const YDataArray<TYPE> & src);
	BOOL						Copy					(const YDataArray<TYPE> & src);

	BOOL						InsertAt				(int nIndex, YDataArray<TYPE> * pNewArray) { return InsertAt (nIndex, *pNewArray); }
	BOOL						InsertAt				(int nIndex, const YDataArray<TYPE> & src);
	BOOL						InsertAt				(int nIndex, TYPE newElement, int nCount = 1);
	int							RemoveAt				(int nIndex, int nCount = 1);
	BOOL						Remove					(TYPE theElement);

public:
	// operators
	YDataArray<TYPE> &			operator=				(const YDataArray<TYPE> & src) { Copy (src); return *this; }
	operator					const TYPE *			() const { return GetData (); }
	operator					TYPE *					() { return GetData (); }
	TYPE						operator[]				(int nIndex) const { return GetAt (nIndex); }
	TYPE &						operator[]				(int nIndex) { return ElementAt (nIndex); }

public:
	// attributes
	BOOL						SetSize					(int nNewSize, int nAllocationGranularity = -1);
	BOOL						SetAllocatedSize		(int nNewSize);

protected:
	// implementation
	TYPE *						m_pData;
};

template<class TYPE>
void YDataArray<TYPE>::RemoveAll ()
{
	if ( m_pData ) {
		free (m_pData);
	}
	m_pData				= NULL;
	m_nSize				= 0;
	m_nAllocatedSize	= 0;
}

template<class TYPE>
int YDataArray<TYPE>::Find (TYPE theElement) const
{
	for ( int i = 0; i < m_nSize; i++ ) {
		if ( !memcmp (&(m_pData[i]), &theElement, sizeof(TYPE)) ) {
			return i;
		}
	}
	return -1;
}

template<class TYPE>
TYPE YDataArray<TYPE>::GetAt (int nIndex) const
{
	ASSERTY((nIndex >= 0) && (nIndex < m_nSize));
	return m_pData[nIndex];
}

template<class TYPE>
BOOL YDataArray<TYPE>::SetAt (int nIndex, TYPE newElement)
{
	if ( (nIndex >= 0) && (nIndex < m_nSize) ) {
		m_pData[nIndex] = newElement;
		return TRUE;
	}
	return FALSE;
}

template<class TYPE>
BOOL YDataArray<TYPE>::SetAtGrow (int nIndex, TYPE newElement)
{
	if ( (nIndex < 0) || ((nIndex >= m_nSize) && !SetSize (nIndex + 1)) ) {
		return FALSE;
	}
	m_pData[nIndex] = newElement;
	return TRUE;
}

template<class TYPE>
TYPE & YDataArray<TYPE>::ElementAt (int nIndex)
{
	ASSERTY((nIndex >= 0) && (nIndex < m_nSize));
	return m_pData[nIndex];
}

template<class TYPE>
int YDataArray<TYPE>::Append (const YDataArray<TYPE> & src)
{
	int nOldSize = m_nSize;
	if ( ((m_nSize + src.m_nSize) > m_nAllocatedSize) && !SetAllocatedSize (m_nSize + src.m_nSize) ) {
		return -1;
	}
	memcpy (m_pData + m_nSize, src.m_pData, src.m_nSize * sizeof (TYPE));
	m_nSize += src.m_nSize;
	return nOldSize;
}

template<class TYPE>
BOOL YDataArray<TYPE>::Copy (const YDataArray<TYPE> & src)
{
	if ( (src.m_nSize > m_nAllocatedSize) && !SetAllocatedSize (src.m_nSize) ) {
		return FALSE;
	}
	memcpy (m_pData, src.m_pData, src.m_nSize * sizeof (TYPE));
	m_nSize = src.m_nSize;
	return TRUE;
}

template<class TYPE>
BOOL YDataArray<TYPE>::InsertAt (int nIndex, const YDataArray<TYPE> & src)
{
	// compute new size
	int nNewSize = (nIndex < m_nSize) ? (m_nSize + src.m_nSize) : (nIndex + src.m_nSize);
	// in case resize....
	if ( (nNewSize > m_nAllocatedSize) && !SetAllocatedSize (nNewSize) ) {
		return FALSE;
	}
	if ( nIndex < m_nSize ) {
		// shift up the remaining stuff
		memmove (m_pData + nIndex + src.m_nSize, m_pData + nIndex, (m_nSize - nIndex) * sizeof (TYPE));
	}
	else if ( nIndex > m_nSize ) {
		// initialize newly created but unused elements
		memset (m_pData + m_nSize, 0, (nIndex - m_nSize) * sizeof (TYPE));
	}
	// copy the stuff
	memcpy (m_pData + nIndex, src.m_pData, src.m_nSize * sizeof (TYPE));
	m_nSize = nNewSize;
	return TRUE;
}

template<class TYPE>
BOOL YDataArray<TYPE>::InsertAt (int nIndex, TYPE newElement, int nCount /* = 1 */)
{
	// compute new size
	int nNewSize = (nIndex < m_nSize) ? (m_nSize + nCount) : (nIndex + nCount);
	// in case resize....
	if ( (nNewSize > m_nAllocatedSize) && !SetAllocatedSize (nNewSize) ) {
		return FALSE;
	}
	if ( nIndex < m_nSize ) {
		// shift up the remaining stuff
		memmove (m_pData + nIndex + nCount, m_pData + nIndex, (m_nSize - nIndex) * sizeof (TYPE));
	}
	else if ( nIndex > m_nSize ) {
		// initialize newly created but unused elements
		memset (m_pData + m_nSize, 0, (nIndex - m_nSize) * sizeof (TYPE));
	}
	// set values
	for ( int * lpPtr = m_pData + nIndex; nCount; lpPtr++, nCount-- ) {
		*lpPtr = newElement;
	}
	m_nSize = nNewSize;
	return TRUE;
}

template<class TYPE>
int YDataArray<TYPE>::RemoveAt (int nIndex, int nCount /* = 1 */)
{
	if ( (nIndex < 0) || (nIndex >= m_nSize) ) {
		// bad param
		return -1;
	}
	else if ( nCount == 0 ) {
		// nothing to do
		return m_nSize;
	}
	// compute the real remove count
	if ( (nIndex + nCount) > m_nSize ) {
		nCount = m_nSize - nIndex;
	}
	else if ( (nIndex + nCount) < m_nSize ) {
		// we must shift
		memmove (m_pData + nIndex, m_pData + nIndex + nCount, (m_nSize - (nIndex + nCount)) * sizeof (TYPE));
	}
	m_nSize -= nCount;
	return m_nSize;
}

template<class TYPE>
BOOL YDataArray<TYPE>::Remove (TYPE theElement)
{
	int nIndex = Find (theElement);
	if ( nIndex != -1 ) {
		return RemoveAt (nIndex) != -1;
	}
	return FALSE;
}

template<class TYPE>
BOOL YDataArray<TYPE>::SetSize (int nNewSize, int nAllocationGranularity /* = -1 */)
{
	int nNewAllocated = SizeHeuristic (nNewSize, nAllocationGranularity);

	switch ( nNewAllocated ) {
	case SZHEU_CLEAR:
		RemoveAll ();
		// intended fallthrough
	case SZHEU_DONOTHING:
		return TRUE;

	case SZHEU_NEGATIVE:
	case SZHEU_OVERFLOW:
		return FALSE;

	default:
		if ( !SetAllocatedSize (nNewAllocated) ) {
			return FALSE;
		}
		// intended fallthrough
	case SZHEU_BIGGER:
		// initialize the added elements
		memset (m_pData + m_nSize, 0, (nNewSize - m_nSize) * sizeof (TYPE));
		// intended fallthrough
	case SZHEU_SMALLER:
		m_nSize = nNewSize;
		return TRUE;
	}
}

template<class TYPE>
BOOL YDataArray<TYPE>::SetAllocatedSize (int nNewSize)
{
	if ( nNewSize <= 0 ) {
		RemoveAll ();
	}
	else if ( m_nAllocatedSize != nNewSize ) {
		if ( nNewSize > (SIZE_T_MAX/sizeof (TYPE)) ) {
			// allocation too big (would exceed memory boundaries)
			return FALSE;
		}
		TYPE *pData = NULL;
		int nByteSize = nNewSize * sizeof (TYPE);
		if ( (pData = (TYPE *) malloc (nByteSize)) == NULL ) {
			return FALSE;
		}
		memcpy (pData, m_pData, MIN (m_nSize, nNewSize) * sizeof (TYPE));
		free (m_pData);
		m_pData				= pData;
		m_nSize				= MIN (m_nSize, nNewSize);
		m_nAllocatedSize	= nNewSize;
	}
	return TRUE;
}

#if (0)
/*=============================================================================
 * GENERIC OBJECT ARRAY
 *============================================================================*/
template<class TYPE>
YLB_INLINE void YLBAPI ConstructElements (TYPE *pElements, int nCount)
{
	ASSERT(!nCount || YlbIsValidAddress(pElements, nCount * sizeof (TYPE)));

	memset ((LPVOID) pElements, 0, nCount * sizeof (TYPE));

	for ( /*TUNIX*/; nCount--; pElements++ ) {
		::new ((LPVOID) pElements) TYPE;
	}
}

template<class TYPE>
YLB_INLINE void YLBAPI DestructElements (TYPE *pElements, int nCount)
{
	ASSERT(!nCount || YlbIsValidAddress(pElements, nCount * sizeof (TYPE)));

	for ( /*TUNIX*/; nCount--; pElements++ ) {
		pElements->~TYPE ();
	}
}

template<class TYPE>
YLB_INLINE void YLBAPI CopyElements (TYPE *pDest, const TYPE *pSrc, int nCount)
{
	ASSERT(!nCount || YlbIsValidAddress (pDest, nCount * sizeof (TYPE)));
	ASSERT(!nCount || YlbIsValidAddress (pSrc,  nCount * sizeof (TYPE)));

	while ( nCount-- ) {
		*pDest++ = *pSrc++;
	}
}

template<class TYPE,ARG_TYPE>
class YObjectArray : public YBaseArray
{

public:
	// construction/destruction
	YObjectArray<TYPE,ARG_TYPE>	(int nAllocationGranularity = -1) : YBaseArray (nAllocationGranularity) { m_pData = NULL; }
	YObjectArray<TYPE,ARG_TYPE>	(const YObjectArray<TYPE,ARG_TYPE> &src) { m_pData = NULL; Copy (src); }	// may fail...
	~YObjectArray<TYPE,ARG_TYPE>() { RemoveAll (); }

public:
	// operations
	BOOL						FreeExtra				() { return SetAllocatedSize (m_nSize); }
	void						RemoveAll				();

	int							Find					(ARG_TYPE theElement) const;
	TYPE						GetAt					(int nIndex) const;
	BOOL						SetAt					(int nIndex, ARG_TYPE newElement);
	BOOL						SetAtGrow				(int nIndex, ARG_TYPE newElement);
	int							Add						(ARG_TYPE newElement) { return (SetAtGrow (m_nSize, newElement)) ? (m_nSize - 1) : (-1); }

	TYPE &						ElementAt				(int nIndex);
	const TYPE *				GetData					() const { return (const TYPE *) m_pData; }
	TYPE *						GetData					() { return (TYPE *) m_pData; }

	int							Append					(const YObjectArray<TYPE,ARG_TYPE> & src);
	BOOL						Copy					(const YObjectArray<TYPE,ARG_TYPE> & src);

	BOOL						InsertAt				(int nIndex, YObjectArray<TYPE,ARG_TYPE> * pNewArray) { return InsertAt (nIndex, *pNewArray); }
	BOOL						InsertAt				(int nIndex, const YObjectArray<TYPE,ARG_TYPE> & src);
	BOOL						InsertAt				(int nIndex, ARG_TYPE newElement, int nCount = 1);
	int							RemoveAt				(int nIndex, int nCount = 1);
	BOOL						Remove					(ARG_TYPE theElement);

public:
	// operators
	YObjectArray<TYPE,ARG_TYPE> &operator=				(const YObjectArray<TYPE,ARG_TYPE> & src) { Copy (src); return *this; }
	operator					const TYPE *			() const { return GetData (); }
	operator					TYPE *					() { return GetData (); }
	TYPE						operator[]				(int nIndex) const { return GetAt (nIndex); }
	TYPE &						operator[]				(int nIndex) { return ElementAt (nIndex); }

public:
	// attributes
	BOOL						SetSize					(int nNewSize, int nAllocationGranularity = -1);
	BOOL						SetAllocatedSize		(int nNewSize);

protected:
	// implementation
	TYPE *						m_pData;
};

template<class TYPE,ARG_TYPE>
void YObjectArray<TYPE,ARG_TYPE>::RemoveAll ()
{
	if ( m_pData ) {
		delete m_pData;
	}
	m_pData				= NULL;
	m_nSize				= 0;
	m_nAllocatedSize	= 0;
}

template<class TYPE,ARG_TYPE>
int YObjectArray<TYPE,ARG_TYPE>::Find (ARG_TYPE theElement) const
{
	for ( int i = 0; i < m_nSize; i++ ) {
		if ( m_pData[i] != theElement ) {
			return i;
		}
	}
	return -1;
}

template<class TYPE,ARG_TYPE>
TYPE YObjectArray<TYPE,ARG_TYPE>::GetAt (int nIndex) const
{
	ASSERTY((nIndex >= 0) && (nIndex < m_nSize));
	return m_pData[nIndex];
}

template<class TYPE,ARG_TYPE>
BOOL YObjectArray<TYPE,ARG_TYPE>::SetAt (int nIndex, ARG_TYPE newElement)
{
	if ( (nIndex >= 0) && (nIndex < m_nSize) ) {
		m_pData[nIndex] = newElement;
		return TRUE;
	}
	return FALSE;
}

template<class TYPE,ARG_TYPE>
BOOL YObjectArray<TYPE,ARG_TYPE>::SetAtGrow (int nIndex, ARG_TYPE newElement)
{
	if ( (nIndex < 0) || ((nIndex >= m_nSize) && !SetSize (nIndex + 1)) ) {
		return FALSE;
	}
	m_pData[nIndex] = newElement;
	return TRUE;
}

template<class TYPE,ARG_TYPE>
TYPE & YObjectArray<TYPE,ARG_TYPE>::ElementAt (int nIndex)
{
	ASSERTY((nIndex >= 0) && (nIndex < m_nSize));
	return m_pData[nIndex];
}

template<class TYPE,ARG_TYPE>
int YObjectArray<TYPE,ARG_TYPE>::Append (const YObjectArray<TYPE,ARG_TYPE> & src)
{
	int nOldSize = m_nSize;
	if ( ((m_nSize + src.m_nSize) > m_nAllocatedSize) && !SetAllocatedSize (m_nSize + src.m_nSize) ) {
		return -1;
	}
	memcpy (m_pData + m_nSize, src.m_pData, src.m_nSize * sizeof (TYPE));
	m_nSize += src.m_nSize;
	return nOldSize;
}

template<class TYPE,ARG_TYPE>
BOOL YObjectArray<TYPE,ARG_TYPE>::Copy (const YObjectArray<TYPE,ARG_TYPE> & src)
{
	if ( (src.m_nSize > m_nAllocatedSize) && !SetAllocatedSize (src.m_nSize) ) {
		return FALSE;
	}
	memcpy (m_pData, src.m_pData, src.m_nSize * sizeof (TYPE));
	m_nSize = src.m_nSize;
	return TRUE;
}

template<class TYPE,ARG_TYPE>
BOOL YObjectArray<TYPE,ARG_TYPE>::InsertAt (int nIndex, const YObjectArray<TYPE,ARG_TYPE> & src)
{
	// compute new size
	int nNewSize = (nIndex < m_nSize) ? (m_nSize + src.m_nSize) : (nIndex + src.m_nSize);
	// in case resize....
	if ( (nNewSize > m_nAllocatedSize) && !SetAllocatedSize (nNewSize) ) {
		return FALSE;
	}
	if ( nIndex < m_nSize ) {
		// shift up the remaining stuff
		memmove (m_pData + nIndex + src.m_nSize, m_pData + nIndex, (m_nSize - nIndex) * sizeof (TYPE));
	}
	else if ( nIndex > m_nSize ) {
		// initialize newly created but unused elements
		memset (m_pData + m_nSize, 0, (nIndex - m_nSize) * sizeof (TYPE));
	}
	// copy the stuff
	memcpy (m_pData + nIndex, src.m_pData, src.m_nSize * sizeof (TYPE));
	m_nSize = nNewSize;
	return TRUE;
}

template<class TYPE,ARG_TYPE>
BOOL YObjectArray<TYPE,ARG_TYPE>::InsertAt (int nIndex, TYPE newElement, int nCount /* = 1 */)
{
	// compute new size
	int nNewSize = (nIndex < m_nSize) ? (m_nSize + nCount) : (nIndex + nCount);
	// in case resize....
	if ( (nNewSize > m_nAllocatedSize) && !SetAllocatedSize (nNewSize) ) {
		return FALSE;
	}
	if ( nIndex < m_nSize ) {
		// shift up the remaining stuff
		memmove (m_pData + nIndex + nCount, m_pData + nIndex, (m_nSize - nIndex) * sizeof (TYPE));
	}
	else if ( nIndex > m_nSize ) {
		// initialize newly created but unused elements
		memset (m_pData + m_nSize, 0, (nIndex - m_nSize) * sizeof (TYPE));
	}
	// set values
	for ( int * lpPtr = m_pData + nIndex; nCount; lpPtr++, nCount-- ) {
		*lpPtr = newElement;
	}
	m_nSize = nNewSize;
	return TRUE;
}

template<class TYPE,ARG_TYPE>
int YObjectArray<TYPE,ARG_TYPE>::RemoveAt (int nIndex, int nCount /* = 1 */)
{
	if ( (nIndex < 0) || (nIndex >= m_nSize) ) {
		// bad param
		return -1;
	}
	else if ( nCount == 0 ) {
		// nothing to do
		return m_nSize;
	}
	// compute the real remove count
	if ( (nIndex + nCount) > m_nSize ) {
		nCount = m_nSize - nIndex;
	}
	else if ( (nIndex + nCount) < m_nSize ) {
		// we must shift
		memmove (m_pData + nIndex, m_pData + nIndex + nCount, (m_nSize - (nIndex + nCount)) * sizeof (TYPE));
	}
	m_nSize -= nCount;
	return m_nSize;
}

template<class TYPE,ARG_TYPE>
BOOL YObjectArray<TYPE,ARG_TYPE>::Remove (TYPE theElement)
{
	int nIndex = Find (theElement);
	if ( nIndex != -1 ) {
		return RemoveAt (nIndex);
	}
	return FALSE;
}

template<class TYPE,ARG_TYPE>
BOOL YObjectArray<TYPE,ARG_TYPE>::SetSize (int nNewSize, int nAllocationGranularity /* = -1 */)
{
	int nNewAllocated = SizeHeuristic (nNewSize, nAllocationGranularity);

	switch ( nNewAllocated ) {
	case SZHEU_CLEAR:
		RemoveAll ();
		// intended fallthrough
	case SZHEU_DONOTHING:
		return TRUE;

	case SZHEU_NEGATIVE:
	case SZHEU_OVERFLOW:
		return FALSE;

	default:
		if ( !SetAllocatedSize (nNewAllocated) ) {
			return FALSE;
		}
		// intended fallthrough
	case SZHEU_BIGGER:
		// initialize the added elements
		memset (m_pData + m_nSize, 0, (nNewSize - m_nSize) * sizeof (TYPE));
		// intended fallthrough
	case SZHEU_SMALLER:
		m_nSize = nNewSize;
		return TRUE;
	}
}

template<class TYPE,ARG_TYPE>
BOOL YObjectArray<TYPE,ARG_TYPE>::SetAllocatedSize (int nNewSize)
{
	if ( nNewSize <= 0 ) {
		RemoveAll ();
	}
	else if ( m_nAllocatedSize != nNewSize ) {
		if ( nNewSize > (SIZE_T_MAX/sizeof (TYPE)) ) {
			// allocation too big (would exceed memory boundaries)
			return FALSE;
		}
		TYPE *pData = NULL;
		int nByteSize = nNewSize * sizeof (TYPE);
		if ( (pData = (TYPE *) malloc (nByteSize)) == NULL ) {
			return FALSE;
		}
		memcpy (pData, m_pData, MIN (m_nSize, nNewSize) * sizeof (TYPE));
		free (m_pData);
		m_pData				= pData;
		m_nSize				= MIN (m_nSize, nNewSize);
		m_nAllocatedSize	= nNewSize;
	}
	return TRUE;
}
#endif


#ifdef YLB_ENABLE_INLINE
#include <yArray.inl>
#endif

#endif //__yArray_h__
//
// EoF
////////