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
 * FILENAME		:	yArray.inl
 * PURPOSE		:	Inline members of the generic array classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.2  2001/05/06 18:31:31  leopoldo
 * Improved arrays
 * Added cardinal array types
 *
 * Revision 1.1  2001/04/12 18:42:56  leopoldo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yArray.inl
 *============================================================================*/
YLB_INLINE int YBaseArray::GetSize () const
{
	return m_nSize;
}

YLB_INLINE int YBaseArray::GetAllocatedSize () const
{
	return m_nAllocatedSize;
}

YLB_INLINE int YBaseArray::GetUpperBound () const
{
	return m_nSize - 1;
}

//////////////////////////////////////

YLB_INLINE YIntArray::YIntArray (const YIntArray &src) : YBaseArray (src)
{
	Copy (src);
}

YLB_INLINE YIntArray::~YIntArray ()
{
	RemoveAll ();
}

YLB_INLINE BOOL YIntArray::FreeExtra ()
{
	return SetAllocatedSize (m_nSize);
}

YLB_INLINE int YIntArray::GetAt (int nIndex) const
{
	ASSERTY((nIndex >= 0) && (nIndex < m_nSize));
	return m_pData[nIndex];
}

YLB_INLINE int YIntArray::Add (int newElement)
{
	return (SetAtGrow (m_nSize, newElement)) ? (m_nSize - 1) : (-1);
}

YLB_INLINE int & YIntArray::ElementAt (int nIndex)
{
	ASSERTY((nIndex >= 0) && (nIndex < m_nSize));
	return m_pData[nIndex];
}

YLB_INLINE const int * YIntArray::GetData () const
{
	return (const int *) m_pData;
}

YLB_INLINE int * YIntArray::GetData ()
{
	return (int *) m_pData;
}

YLB_INLINE BOOL YIntArray::InsertAt (int nIndex, YIntArray * pNewArray)
{
	return InsertAt (nIndex, *pNewArray);
}

YLB_INLINE YIntArray & YIntArray::operator= (const YIntArray & src)
{
	Copy (src);
	return *this;
}

YLB_INLINE YIntArray::operator const int * () const
{
	return GetData ();
}

YLB_INLINE YIntArray::operator int * ()
{
	return GetData ();
}

YLB_INLINE int YIntArray::operator[] (int nIndex) const
{
	return GetAt(nIndex);
}

YLB_INLINE int & YIntArray::operator[] (int nIndex)
{
	return ElementAt(nIndex);
}


//////////////////////////////////////

YLB_INLINE YShortArray::YShortArray (const YShortArray &src) : YBaseArray (src)
{
	Copy (src);
}

YLB_INLINE YShortArray::~YShortArray ()
{
	RemoveAll ();
}

YLB_INLINE BOOL YShortArray::FreeExtra ()
{
	return SetAllocatedSize (m_nSize);
}

YLB_INLINE short YShortArray::GetAt (int nIndex) const
{
	ASSERTY((nIndex >= 0) && (nIndex < m_nSize));
	return m_pData[nIndex];
}

YLB_INLINE int YShortArray::Add (short newElement)
{
	return (SetAtGrow (m_nSize, newElement)) ? (m_nSize - 1) : (-1);
}

YLB_INLINE short & YShortArray::ElementAt (int nIndex)
{
	ASSERTY((nIndex >= 0) && (nIndex < m_nSize));
	return m_pData[nIndex];
}

YLB_INLINE const short * YShortArray::GetData () const
{
	return (const short *) m_pData;
}

YLB_INLINE short * YShortArray::GetData ()
{
	return (short *) m_pData;
}

YLB_INLINE BOOL YShortArray::InsertAt (int nIndex, YShortArray * pNewArray)
{
	return InsertAt (nIndex, *pNewArray);
}

YLB_INLINE YShortArray & YShortArray::operator= (const YShortArray & src)
{
	Copy (src);
	return *this;
}

YLB_INLINE YShortArray::operator const short * () const
{
	return GetData ();
}

YLB_INLINE YShortArray::operator short * ()
{
	return GetData ();
}

YLB_INLINE short YShortArray::operator[] (int nIndex) const
{
	return GetAt(nIndex);
}

YLB_INLINE short & YShortArray::operator[] (int nIndex)
{
	return ElementAt(nIndex);
}

//////////////////////////////////////

YLB_INLINE YCharArray::YCharArray (const YCharArray &src) : YBaseArray (src)
{
	Copy (src);
}

YLB_INLINE YCharArray::~YCharArray ()
{
	RemoveAll ();
}

YLB_INLINE BOOL YCharArray::FreeExtra ()
{
	return SetAllocatedSize (m_nSize);
}

YLB_INLINE char YCharArray::GetAt (int nIndex) const
{
	ASSERTY((nIndex >= 0) && (nIndex < m_nSize));
	return m_pData[nIndex];
}

YLB_INLINE int YCharArray::Add (char newElement)
{
	return (SetAtGrow (m_nSize, newElement)) ? (m_nSize - 1) : (-1);
}

YLB_INLINE char & YCharArray::ElementAt (int nIndex)
{
	ASSERTY((nIndex >= 0) && (nIndex < m_nSize));
	return m_pData[nIndex];
}

YLB_INLINE const char * YCharArray::GetData () const
{
	return (const char *) m_pData;
}

YLB_INLINE char * YCharArray::GetData ()
{
	return (char *) m_pData;
}

YLB_INLINE BOOL YCharArray::InsertAt (int nIndex, YCharArray * pNewArray)
{
	return InsertAt (nIndex, *pNewArray);
}

YLB_INLINE YCharArray & YCharArray::operator= (const YCharArray & src)
{
	Copy (src);
	return *this;
}

YLB_INLINE YCharArray::operator const char * () const
{
	return GetData ();
}

YLB_INLINE YCharArray::operator char * ()
{
	return GetData ();
}

YLB_INLINE char YCharArray::operator[] (int nIndex) const
{
	return GetAt(nIndex);
}

YLB_INLINE char & YCharArray::operator[] (int nIndex)
{
	return ElementAt(nIndex);
}

//////////////////////////////////////

YLB_INLINE YPtrArray::YPtrArray (const YPtrArray &src) : YBaseArray (src)
{
	Copy (src);
}

YLB_INLINE YPtrArray::~YPtrArray ()
{
	RemoveAll ();
}

YLB_INLINE BOOL YPtrArray::FreeExtra ()
{
	return SetAllocatedSize (m_nSize);
}

YLB_INLINE LPVOID YPtrArray::GetAt (int nIndex) const
{
	ASSERTY((nIndex >= 0) && (nIndex < m_nSize));
	return m_pData[nIndex];
}

YLB_INLINE int YPtrArray::Add (LPVOID newElement)
{
	return (SetAtGrow (m_nSize, newElement)) ? (m_nSize - 1) : (-1);
}

YLB_INLINE LPVOID & YPtrArray::ElementAt (int nIndex)
{
	ASSERTY((nIndex >= 0) && (nIndex < m_nSize));
	return m_pData[nIndex];
}

YLB_INLINE const LPVOID * YPtrArray::GetData () const
{
	return (const LPVOID *) m_pData;
}

YLB_INLINE LPVOID * YPtrArray::GetData ()
{
	return (LPVOID *) m_pData;
}

YLB_INLINE BOOL YPtrArray::InsertAt (int nIndex, YPtrArray * pNewArray)
{
	return InsertAt (nIndex, *pNewArray);
}

YLB_INLINE YPtrArray & YPtrArray::operator= (const YPtrArray & src)
{
	Copy (src);
	return *this;
}

YLB_INLINE YPtrArray::operator const LPVOID * () const
{
	return GetData ();
}

YLB_INLINE YPtrArray::operator LPVOID * ()
{
	return GetData ();
}

YLB_INLINE LPVOID YPtrArray::operator[] (int nIndex) const
{
	return GetAt(nIndex);
}

YLB_INLINE LPVOID & YPtrArray::operator[] (int nIndex)
{
	return ElementAt(nIndex);
}

//
// EoF
////////
