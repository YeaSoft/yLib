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
 * FILENAME		:	yProfile.inl
 * PURPOSE		:	Inline members of the INI File Class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.2  2002/08/04 14:50:00  leopoldo
 * Added new functionality
 *
 * Revision 1.1  2001/09/14 16:19:48  leopoldo
 * Initial revision
 *
 *============================================================================*/
/*=============================================================================
 * @doc YLIB | yProfile.h
 *============================================================================*/
YLB_INLINE bool YProfile::IsOpen () const
{
	return !m_ysIniFile.IsEmpty () && TestFile () && !m_ysSection.IsEmpty ();
}

YLB_INLINE LPCTSTR YProfile::GetFileName () const
{
	return m_ysIniFile;
}

YLB_INLINE void YProfile::Close ()
{
	m_ysSection.Empty ();
}

YLB_INLINE bool YProfile::ExpandableStringSet (LPCTSTR lpszValueName, LPCTSTR lpszValue) const
{
	return StringSet (lpszValueName, lpszValue);
}

YLB_INLINE ITERATOR YProfile::GetFirstSectionPosition ()
{
	return GetSectionBuffer () ? m_ysSecEnum.GetFirstStringPosition () : NULL;
}

YLB_INLINE ITERATOR YProfile::GetLastSectionPosition ()
{
	return GetSectionBuffer () ? m_ysSecEnum.GetLastStringPosition () : NULL;
}

YLB_INLINE ITERATOR YProfile::GetFirstValuePosition ()
{
	return GetValueBuffer () ? m_ysValEnum.GetFirstStringPosition () : NULL;
}

YLB_INLINE ITERATOR YProfile::GetLastValuePosition ()
{
	return GetValueBuffer () ? m_ysValEnum.GetLastStringPosition () : NULL;
}

YLB_INLINE LPCTSTR YProfile::GetNextValue (ITERATOR &rPosition, LPTSTR pszBuffer, UINT cbBuffer, LPDWORD pdwType, LPBYTE pbData, LPDWORD pdwDataLen)
{
	return GetValue (m_ysValEnum.GetNext (rPosition), pszBuffer, cbBuffer, pdwType, pbData, pdwDataLen);
}

YLB_INLINE LPCTSTR YProfile::GetPrevValue (ITERATOR &rPosition, LPTSTR pszBuffer, UINT cbBuffer, LPDWORD pdwType, LPBYTE pbData, LPDWORD pdwDataLen)
{
	return GetValue (m_ysValEnum.GetPrev (rPosition), pszBuffer, cbBuffer, pdwType, pbData, pdwDataLen);
}

//
// EoF
////////
