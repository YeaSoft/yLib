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
 *============================================================================*/
/*=============================================================================
 * @doc YLIB | yProfile.h
 *============================================================================*/
YLB_INLINE bool YProfile::IsOpen () const
{
	return !m_ysIniFile.IsEmpty () && m_ysIniFile.IsFile () && !m_ysSection.IsEmpty ();
}

YLB_INLINE void YProfile::Close ()
{
	m_ysSection.Empty ();
}

YLB_INLINE bool YProfile::ExpandableStringSet (LPCTSTR lpszValueName, LPCTSTR lpszValue) const
{
	return StringSet (lpszValueName, lpszValue);
}


//
// EoF
////////
