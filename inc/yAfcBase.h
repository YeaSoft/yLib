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
 * FILENAME		:	yAfcBase.hpp
 * PURPOSE		:	Base definitions for all yAfc features
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26  14:02:48  leo
 * Initial revision
 *
 *============================================================================*/

/*============================================================================*
 * @doc YLIB | yAfcBase.h
 *============================================================================*/
#ifndef __yAfcBase_h__
#define __yAfcBase_h__

/*============================================================================*
 * These defines are relevant when compiling yLib:
 *
 * YLB_MAX_OPTIONS:		Maximium number of parsed options in a YCmdLineParser
 * YLB_MAX_PARAMS:		Maximium number of parsed params in a YCmdLineParser
 * YLB_MAX_SERVICES:	Maximum number of services in a YSrvApp
 *
 *============================================================================*/
#define YLB_MAX_OPTIONS			128
#define YLB_MAX_PARAMS			128
#define YLB_MAX_SERVICES		8

/*============================================================================*
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yFlags_h__
#include <yFlags.h>
#endif

/*============================================================================*
 * LIBRARY INCLUSION STATEMENT
 *============================================================================*/
#if defined(_UNICODE)
	#if defined(_DEBUG)
		#if defined(_DLL)
			#pragma comment(lib, "uYFCdwd.lib")
		#else
			#pragma comment(lib, "uYFCswd.lib")
		#endif
	#else
		#if defined(_DLL)
			#pragma comment(lib, "uYFCdwr.lib")
		#else
			#pragma comment(lib, "uYFCswr.lib")
		#endif
	#endif
#else
	#if defined(_DEBUG)
		#if defined(_DLL)
			#pragma comment(lib, "nYFCdwd.lib")
		#else
			#pragma comment(lib, "nYFCswd.lib")
		#endif
	#else
		#if defined(_DLL)
			#pragma comment(lib, "nYFCdwr.lib")
		#else
			#pragma comment(lib, "nYFCswr.lib")
		#endif
	#endif
#endif

/*============================================================================*
 * FORWARD CLASS DECLARATIONS
 *============================================================================*/
class YBaseApp;
	class YConApp;
	class YSrvApp;

/*============================================================================*
 * HELPER FUNCTIONS
 *============================================================================*/
YConApp * YLBAPI				YlbGetApp				();
YSrvApp * YLBAPI				YlbGetSrv				();

/*============================================================================*
 * HELPER CLASSES
 *============================================================================*/
class YCmdLineParam : public YCommandLineInfo
{
public:
	// attributes
	void						ResetAdditionalArgs		();
	LPCTSTR						GetParam				() const;
	DWORDLONG					GetMeaning				() const;
	UINT						GetCliIndex				() const;
	void						SetMeaning				(DWORDLONG dwMeaning);
	void						SetParamCount			(UINT nCount);

public:
	DWORDLONG					m_dwMeaning;
	LPCTSTR						m_pszParam;
	UINT						m_nCliIndex;
};

class YCmdLineOption : public YCmdLineParam
{
public:
	// attributes
	TCHAR						GetOption				() const;

public:
	TCHAR						m_cOption;
};

class YCmdLineParser
{
public:
	// construction
	YCmdLineParser				(LPCTSTR pszOptionChars = _T("-"));

public:
	// overridables
	virtual BOOL				OnProcessOption			(BOOL &bTerminate, LPCTSTR &pszOptString, YCmdLineOption &cliOpt);
	virtual BOOL				OnProcessParam			(BOOL &bTerminate, YCmdLineParam &cliPar);
	virtual BOOL				OnFinalCheck			();

public:
	// attributes
	LPCTSTR						GetOptionChars			() const;
	void						SetOptionChars			(LPCTSTR pszOptionChars = _T("-"));

	UINT						GetOptionsCount			() const;
	UINT						GetParamsCount			() const;

	DWORDLONG					GetCommands				() const;
	DWORDLONG					GetOptions				() const;
	void						SetCommands				(DWORDLONG flags);
	void						SetOptions				(DWORDLONG flags);
	void						SetCommandFlags			(DWORDLONG flags);
	void						SetOptionFlags			(DWORDLONG flags);
	void						ClearCommandFlags		(DWORDLONG flags = ~(DWORDLONG) 0);
	void						ClearOptionFlags		(DWORDLONG flags = ~(DWORDLONG) 0);
	BOOL						TestCommandFlags		(DWORDLONG flags, FLG_TEST_MODE mode = FLG_AND) const;
	BOOL						TestOptionFlags			(DWORDLONG flags, FLG_TEST_MODE mode = FLG_AND) const;
	BOOL						GetParserResult			() const;

public:
	// operations
	YCmdLineOption *			FindOptionByMeaning		(DWORDLONG dwMeaning);
	YCmdLineParam *				FindParamByMeaning		(DWORDLONG dwMeaning);
	ITERATOR					GetOptionHeadPosition	() const;
	ITERATOR					GetOptionTailPosition	() const;
	YCmdLineOption *			GetNextOption			(ITERATOR &pos);
	YCmdLineOption *			GetPrevOption			(ITERATOR &pos);
	YCmdLineOption *			GetOptionAt				(ITERATOR pos);
	YCmdLineOption *			GetOption				(UINT nPos);
	ITERATOR					GetParamHeadPosition	() const;
	ITERATOR					GetParamTailPosition	() const;
	YCmdLineParam *				GetNextParam			(ITERATOR &pos);
	YCmdLineParam *				GetPrevParam			(ITERATOR &pos);
	YCmdLineParam *				GetParamAt				(ITERATOR pos);
	YCmdLineParam *				GetParam				(UINT nPos);

public:
	// implementation
	BOOL						Parse					();

protected:
	// implementation
	UINT						CountAdditionalArgs		(ITERATOR pos);

protected:
	// implementation
	TCHAR						m_szOptionChars[8];
	UINT						m_nNumOptions;
	UINT						m_nNumParams;
	BOOL						m_bParsingResult;
	YWideFlags					m_flgCommands;
	YWideFlags					m_flgOptions;
	YCmdLineOption				m_cliOptions[YLB_MAX_OPTIONS];
	YCmdLineParam				m_cliParams[YLB_MAX_PARAMS];
};

#ifdef YLB_ENABLE_INLINE
#include <yAfcBase.inl>
#endif

#endif //__yAfcBase_h__

//
// EoF
////////