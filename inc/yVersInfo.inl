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
 * FILENAME		:	yVersInfo.inl
 * PURPOSE		:	Inline members of the version information handler class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*==================================================================================*
 * @doc YLIB | yVersInfo.h
 *==================================================================================*/

YLB_INLINE YVersInfo::YVersInfo ()
{
	CommonConstructor ();
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

