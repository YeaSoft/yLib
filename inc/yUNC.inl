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
 * FILENAME		:	yUNC.inl
 * PURPOSE		:	Declaration of the UNC Class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:03:40  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yUNC.h
 *============================================================================*/

YLB_INLINE YUNC::YUNC ()
{
	CommonConstructor ();
}

YLB_INLINE YUNC::operator LPCTSTR () const
{
	return m_szFileName;
}

YLB_INLINE BOOL YUNC::IsUNC () const
{
	return m_pszComputerPart != NULL;
}

YLB_INLINE BOOL YUNC::IsLocalComputer () const
{
	return m_pszComputerPart && (m_nComputerLength == 1) && (*m_pszComputerPart == _T('.'));
}

YLB_INLINE BOOL YUNC::IsLocal () const
{
	return (IsUNC ()) ? (IsLocalComputer ()) : (TRUE);
}

YLB_INLINE BOOL YUNC::IsRemote () const
{
	return !IsLocal ();
}

YLB_INLINE BOOL YUNC::IsAdministrative () const
{
	return (HasComputer ()) ? ((m_nShareLength == 2) && (m_pszSharePart[1] == _T('$'))) : (FALSE);
}

YLB_INLINE BOOL YUNC::HasComputer () const
{
	return m_pszComputerPart && *m_pszComputerPart && (*m_pszComputerPart != _T('\\'));
}


//
// EoF
////////