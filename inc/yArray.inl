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
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yArray.inl
 *============================================================================*/
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

YLB_INLINE LPVOID YPtrArray::operator[] (int nIndex) const
{
	return GetAt(nIndex);
}

YLB_INLINE LPVOID & YPtrArray::operator[] (int nIndex)
{
	return ElementAt(nIndex);
}

YLB_INLINE BOOL YPtrArray::InsertAt (int nIndex, YPtrArray * pNewArray)
{
	return InsertAt (nIndex, *pNewArray);
}

YLB_INLINE int YPtrArray::GetSize () const
{
	return m_nSize;
}

YLB_INLINE int YPtrArray::GetAllocatedSize () const
{
	return m_nAllocatedSize;
}

YLB_INLINE int YPtrArray::GetUpperBound () const
{
	return m_nSize - 1;
}

//
// EoF
////////
