/*=============================================================================
 * This is a part of the yLib Software Development Kit.
 * Copyright (C) 1998-2000 YEAsoft Inc.
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
 * FILENAME		:	yVersInfo.hpp
 * PURPOSE		:	Declaration of the version information handler class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yVersInfo.h
 *============================================================================*/
#ifndef __yVersInfo_h__
#define __yVersInfo_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yLibBase_h__
#include <yLibBase.h>
#endif

/*=============================================================================
 * CLASS DECLARATION
 *============================================================================*/
// @class Version information handler class
// @comm This class permits the retrieval of version information
//		contained in an executable file.
class YVersInfo : public YErrableObject
{
public:
	// construction/destruction
	// @cmember Copy constructor
	YVersInfo					(const YVersInfo &cvi);
	// @cmember Constructor with filename
	YVersInfo					(LPCTSTR lpszFileName, ...);
	// @cmember Default constructor
	YVersInfo					();

	~YVersInfo					() { UnloadInfo (); }

public:
	// @access Operations
	// @cmember Sets the filename for all subsequent requests
	void						SetName						(LPCTSTR lpszFileName, ...);

public:
	// @access Attributes
	// @cmember Gets the file major version number
	WORD						GetFileMajorVersion			();
	// @cmember Gets the file minor version number
	WORD						GetFileMinorVersion			();
	// @cmember Gets the file stepping number
	WORD						GetFileSteppingNumber		();
	// @cmember Gets the file build number
	WORD						GetFileBuildNumber			();
	// @cmember Gets the file major product version number
	WORD						GetProductMajorVersion		();
	// @cmember Gets the file minor product version number
	WORD						GetProductMinorVersion		();
	// @cmember Gets the file product stepping number
	WORD						GetProductSteppingNumber	();
	// @cmember Gets the file product build number
	WORD						GetProductBuildNumber		();
	// @cmember Gets the file build flags
	DWORD						GetFileFlags				();
	// @cmember Gets the file OS flags
	DWORD						GetFileOS					();
	// @cmember Gets the file type flags
	DWORD						GetFileType					();
	// @cmember Gets the file subtype flags
	DWORD						GetFileSubType				();

	// @cmember Retrieves the first language/codepage configuration
	BOOL						GetFirstLanguage			(LPWORD pwLangCode = NULL, LPWORD pwCodePage = NULL);
	// @cmember Retrieves the next language/codepage configuration
	BOOL						GetNextLanguage				(LPWORD pwLangCode = NULL, LPWORD pwCodePage = NULL);
	// @cmember Retrieves a specified string value for the specified language/codepage configuration
	LPCTSTR						QueryValue					(WORD wLangCode, WORD wCodePage, LPCTSTR pszName);
	// @cmember Retrieves a specified string value
	LPCTSTR						QueryValue					(LPCTSTR pszName);

	LPCTSTR						QueryComments				(WORD wLangCode, WORD wCodePage);
	LPCTSTR						QueryInternalName			(WORD wLangCode, WORD wCodePage);
	LPCTSTR						QueryProductName			(WORD wLangCode, WORD wCodePage);
	LPCTSTR						QueryCompanyName			(WORD wLangCode, WORD wCodePage);
	LPCTSTR						QueryLegalCopyright			(WORD wLangCode, WORD wCodePage);
	LPCTSTR						QueryProductVersion 		(WORD wLangCode, WORD wCodePage);
	LPCTSTR						QueryFileDescription		(WORD wLangCode, WORD wCodePage);
	LPCTSTR						QueryLegalTrademarks		(WORD wLangCode, WORD wCodePage);
	LPCTSTR						QueryPrivateBuild			(WORD wLangCode, WORD wCodePage);
	LPCTSTR						QueryFileVersion			(WORD wLangCode, WORD wCodePage);
	LPCTSTR						QueryOriginalFilename		(WORD wLangCode, WORD wCodePage);
	LPCTSTR						QuerySpecialBuild			(WORD wLangCode, WORD wCodePage);

	LPCTSTR						QueryComments				();
	LPCTSTR						QueryInternalName			();
	LPCTSTR						QueryProductName			();
	LPCTSTR						QueryCompanyName			();
	LPCTSTR						QueryLegalCopyright			();
	LPCTSTR						QueryProductVersion 		();
	LPCTSTR						QueryFileDescription		();
	LPCTSTR						QueryLegalTrademarks		();
	LPCTSTR						QueryPrivateBuild			();
	LPCTSTR						QueryFileVersion			();
	LPCTSTR						QueryOriginalFilename		();
	LPCTSTR						QuerySpecialBuild			();

private:
	// implementation
	void						CommonConstructor			(DWORD dwErr = NOERROR);
	BOOL						LoadInfo					();
	void						UnloadInfo					();

private:
	// implementation
	typedef struct _tagLANGANDCODEPAGE {
		WORD		wLanguage;
		WORD		wCodePage;
	} LANGANDCODEPAGE, *LPLANGANDCODEPAGE;

	static TCHAR				m_szComments[];
	static TCHAR				m_szInternalName[];
	static TCHAR				m_szProductName[];
	static TCHAR				m_szCompanyName[];
	static TCHAR				m_szLegalCopyright[];
	static TCHAR				m_szProductVersion[];
	static TCHAR				m_szFileDescription[];
	static TCHAR				m_szLegalTrademarks[];
	static TCHAR				m_szPrivateBuild[];
	static TCHAR				m_szFileVersion[];
	static TCHAR				m_szOriginalFilename[];
	static TCHAR				m_szSpecialBuild[];


	TCHAR						m_szFileName[MAX_PATH];
	LPVOID						m_pVerInfo;
	DWORD						m_dwVerInfoSize;
	VS_FIXEDFILEINFO			*m_pvsFixedInfo;
	LPLANGANDCODEPAGE			m_lpTranslate;
	DWORD						m_dwNumLang;
	
	friend class YFileAttributes;
};
//
// @xref <j File Related Classes>

#ifdef YLB_ENABLE_INLINE
#include <yVersInfo.inl>
#endif

#endif //__yVersInfo_hpp__