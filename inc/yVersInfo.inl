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
 * FILENAME		:	yVersInfo.inl
 * PURPOSE		:	Inline members of the version information handler class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.3  2002/05/14 11:55:56  leopoldo
 * Added YVersInfo::GetName
 *
 * Revision 1.2  2000/09/04 11:59:53  leopoldo
 * Updated license to zlib/libpng
 *
 * Revision 1.1  2000/05/26 14:03:42  leo
 * Initial revision
 *
 *============================================================================*/

/*==================================================================================*
 * @doc YLIB | yVersInfo.h
 *==================================================================================*/

YLB_INLINE YVersInfo::YVersInfo ()
{
	CommonConstructor ();
}

YLB_INLINE LPCTSTR YVersInfo::GetName () const
{
	return m_szFileName;
}

YLB_INLINE const VS_FIXEDFILEINFO *	YVersInfo::GetFixedFileInfo ()
{
	LoadInfo ();
	return m_pvsFixedInfo;
}

YLB_INLINE WORD YVersInfo::GetFileMajorVersion ()
{
	LoadInfo ();
	return (m_pvsFixedInfo) ? (HIWORD(m_pvsFixedInfo->dwFileVersionMS)) : (0);
}

YLB_INLINE WORD YVersInfo::GetFileMinorVersion ()
{
	LoadInfo ();
	return (m_pvsFixedInfo) ? (LOWORD(m_pvsFixedInfo->dwFileVersionMS)) : (0);
}

YLB_INLINE WORD YVersInfo::GetFileSteppingNumber ()
{
	LoadInfo ();
	return (m_pvsFixedInfo) ? (HIWORD(m_pvsFixedInfo->dwFileVersionLS)) : (0);
}

YLB_INLINE WORD YVersInfo::GetFileBuildNumber ()
{
	LoadInfo ();
	return (m_pvsFixedInfo) ? (LOWORD(m_pvsFixedInfo->dwFileVersionLS)) : (0);
}

YLB_INLINE WORD YVersInfo::GetProductMajorVersion ()
{
	LoadInfo ();
	return (m_pvsFixedInfo) ? (HIWORD(m_pvsFixedInfo->dwProductVersionMS)) : (0);
}

YLB_INLINE WORD YVersInfo::GetProductMinorVersion ()
{
	LoadInfo ();
	return (m_pvsFixedInfo) ? (LOWORD(m_pvsFixedInfo->dwProductVersionMS)) : (0);
}

YLB_INLINE WORD YVersInfo::GetProductSteppingNumber ()
{
	LoadInfo ();
	return (m_pvsFixedInfo) ? (HIWORD(m_pvsFixedInfo->dwProductVersionLS)) : (0);
}

YLB_INLINE WORD YVersInfo::GetProductBuildNumber ()
{
	LoadInfo ();
	return (m_pvsFixedInfo) ? (LOWORD(m_pvsFixedInfo->dwProductVersionLS)) : (0);
}

YLB_INLINE DWORD YVersInfo::GetFileFlags ()
{
	LoadInfo ();
	return (m_pvsFixedInfo) ? (m_pvsFixedInfo->dwFileFlags & m_pvsFixedInfo->dwFileFlagsMask) : (0);
}

YLB_INLINE DWORD YVersInfo::GetFileOS ()
{
	LoadInfo ();
	return (m_pvsFixedInfo) ? (m_pvsFixedInfo->dwFileOS) : (0);
}

YLB_INLINE DWORD YVersInfo::GetFileType ()
{
	LoadInfo ();
	return (m_pvsFixedInfo) ? (m_pvsFixedInfo->dwFileType) : (0);
}

YLB_INLINE DWORD YVersInfo::GetFileSubType ()
{
	LoadInfo ();
	return (m_pvsFixedInfo) ? (m_pvsFixedInfo->dwFileSubtype) : (0);
}

YLB_INLINE LPCTSTR YVersInfo::QueryComments (WORD wLangCode, WORD wCodePage)
{
	return QueryValue (wLangCode, wCodePage, m_szComments);
}

YLB_INLINE LPCTSTR YVersInfo::QueryInternalName (WORD wLangCode, WORD wCodePage)
{
	return QueryValue (wLangCode, wCodePage, m_szInternalName);
}

YLB_INLINE LPCTSTR YVersInfo::QueryProductName (WORD wLangCode, WORD wCodePage)
{
	return QueryValue (wLangCode, wCodePage, m_szProductName);
}

YLB_INLINE LPCTSTR YVersInfo::QueryCompanyName (WORD wLangCode, WORD wCodePage)
{
	return QueryValue (wLangCode, wCodePage, m_szCompanyName);
}

YLB_INLINE LPCTSTR YVersInfo::QueryLegalCopyright (WORD wLangCode, WORD wCodePage)
{
	return QueryValue (wLangCode, wCodePage, m_szLegalCopyright);
}

YLB_INLINE LPCTSTR YVersInfo::QueryProductVersion (WORD wLangCode, WORD wCodePage)
{
	return QueryValue (wLangCode, wCodePage, m_szProductVersion);
}

YLB_INLINE LPCTSTR YVersInfo::QueryFileDescription (WORD wLangCode, WORD wCodePage)
{
	return QueryValue (wLangCode, wCodePage, m_szFileDescription);
}

YLB_INLINE LPCTSTR YVersInfo::QueryLegalTrademarks (WORD wLangCode, WORD wCodePage)
{
	return QueryValue (wLangCode, wCodePage, m_szLegalTrademarks);
}

YLB_INLINE LPCTSTR YVersInfo::QueryPrivateBuild (WORD wLangCode, WORD wCodePage)
{
	return QueryValue (wLangCode, wCodePage, m_szPrivateBuild);
}

YLB_INLINE LPCTSTR YVersInfo::QueryFileVersion (WORD wLangCode, WORD wCodePage)
{
	return QueryValue (wLangCode, wCodePage, m_szFileVersion);
}

YLB_INLINE LPCTSTR YVersInfo::QueryOriginalFilename (WORD wLangCode, WORD wCodePage)
{
	return QueryValue (wLangCode, wCodePage, m_szOriginalFilename);
}

YLB_INLINE LPCTSTR YVersInfo::QuerySpecialBuild (WORD wLangCode, WORD wCodePage)
{
	return QueryValue (wLangCode, wCodePage, m_szSpecialBuild);
}

YLB_INLINE LPCTSTR YVersInfo::QueryComments ()
{
	return QueryValue (m_szComments);
}

YLB_INLINE LPCTSTR YVersInfo::QueryInternalName ()
{
	return QueryValue (m_szInternalName);
}

YLB_INLINE LPCTSTR YVersInfo::QueryProductName ()
{
	return QueryValue (m_szProductName);
}

YLB_INLINE LPCTSTR YVersInfo::QueryCompanyName ()
{
	return QueryValue (m_szCompanyName);
}

YLB_INLINE LPCTSTR YVersInfo::QueryLegalCopyright ()
{
	return QueryValue (m_szLegalCopyright);
}

YLB_INLINE LPCTSTR YVersInfo::QueryProductVersion ()
{
	return QueryValue (m_szProductVersion);
}

YLB_INLINE LPCTSTR YVersInfo::QueryFileDescription ()
{
	return QueryValue (m_szFileDescription);
}

YLB_INLINE LPCTSTR YVersInfo::QueryLegalTrademarks ()
{
	return QueryValue (m_szLegalTrademarks);
}

YLB_INLINE LPCTSTR YVersInfo::QueryPrivateBuild ()
{
	return QueryValue (m_szPrivateBuild);
}

YLB_INLINE LPCTSTR YVersInfo::QueryFileVersion ()
{
	return QueryValue (m_szFileVersion);
}

YLB_INLINE LPCTSTR YVersInfo::QueryOriginalFilename ()
{
	return QueryValue (m_szOriginalFilename);
}

YLB_INLINE LPCTSTR YVersInfo::QuerySpecialBuild ()
{
	return QueryValue (m_szSpecialBuild);
}

