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
 * FILENAME		:	yMulStr.inl
 * PURPOSE		:	Inline members of the multiple string class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.2  2001/05/24 15:20:11  leopoldo
 * First basic implementation
 *
 * Revision 1.1  2001/05/18 16:00:44  leopoldo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * MULTISTRING CLASS IMPLEMENTATION
 *============================================================================*/
YLB_INLINE YMultiString::YMultiString ()
{
}

YLB_INLINE YMultiString::~YMultiString ()
{
}

YLB_INLINE BOOL YMultiString::IsEmpty () const
{
	return !GetBuffer () || (GetBufferSize () < 2) || (!GetBuffer ()[0] && !GetBuffer ()[1]);
}

YLB_INLINE LPCTSTR YMultiString::GetString	() const
{
	return (IsEmpty ()) ? (_T("\0\0")) : (GetBuffer ());
}

YLB_INLINE LPCTSTR YMultiString::GetNullForEmptyString	() const
{
	return (IsEmpty ()) ? (NULL) : (GetBuffer ());
}

YLB_INLINE ITERATOR YMultiString::GetFirstStringPosition () const
{
	return (IsEmpty ()) ? (NULL) : ((ITERATOR) GetBuffer ());
}

YLB_INLINE void YMultiString::Empty (BOOL bFreeExtra /* = FALSE */)
{
	m_dbStorage.Empty (bFreeExtra);
}

YLB_INLINE BOOL YMultiString::Prepare (int cbSize)
{
	if ( Alloc (cbSize) ) {
		m_dbStorage.SetContentSize (cbSize);
		return TRUE;
	}
	return FALSE;
}

YLB_INLINE YMultiString::operator LPCTSTR () const
{
	return GetString ();
}



//
// EoF
////////