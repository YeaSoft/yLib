/*=============================================================================
 * This is a part of the yLib Software Development Kit.
 * Copyright (C) 1998-1999 YEAsoft Inc.
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
 * FILENAME		:	yUNC.inl
 * PURPOSE		:	Declaration of the UNC Class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
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