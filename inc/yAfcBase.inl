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
 * FILENAME		:	yAfcBase.inl
 * PURPOSE		:	Inline implementation for base classes and global functions
 * SCOPE		:	yAfc
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26  14:02:53  leo
 * Initial revision
 *
 *============================================================================*/
/*=============================================================================
 * @doc YLIB | yCmdParse.h
 *============================================================================*/
/*=============================================================================
 * COMMANDLINE PARSER IMPLEMENTATION
 *============================================================================*/
YLB_INLINE void YCmdLineParam::ResetAdditionalArgs ()
{
	m_argc	= 0;
	m_argv	= NULL;
}

YLB_INLINE LPCTSTR YCmdLineParam::GetParam () const
{
	return m_pszParam;
}

YLB_INLINE DWORDLONG YCmdLineParam::GetMeaning () const
{
	return m_dwMeaning;
}

YLB_INLINE UINT YCmdLineParam::GetCliIndex () const
{
	return m_nCliIndex;
}

YLB_INLINE void YCmdLineParam::SetMeaning (DWORDLONG dwMeaning)
{
	m_dwMeaning = dwMeaning;
}

YLB_INLINE void YCmdLineParam::SetParamCount (UINT nCount)
{
	m_argc = nCount;
}

YLB_INLINE TCHAR YCmdLineOption::GetOption () const
{
	return m_cOption;
}

YLB_INLINE LPCTSTR YCmdLineParser::GetOptionChars () const
{
	return m_szOptionChars;
}

YLB_INLINE void YCmdLineParser::SetOptionChars (LPCTSTR pszOptionChars)
{
	ASSERTY(pszOptionChars);
	_tcsncpy (m_szOptionChars, pszOptionChars, _countof (m_szOptionChars) - 1);
	m_szOptionChars[_countof (m_szOptionChars) - 1] = 0;
}

YLB_INLINE UINT YCmdLineParser::GetOptionsCount () const
{
	return m_nNumOptions;
}

YLB_INLINE UINT YCmdLineParser::GetParamsCount () const
{
	return m_nNumParams;
}

YLB_INLINE DWORDLONG YCmdLineParser::GetCommands () const
{
	return m_flgCommands.Get ();
}

YLB_INLINE DWORDLONG YCmdLineParser::GetOptions () const
{
	return m_flgOptions.Get ();
}

YLB_INLINE void YCmdLineParser::SetCommands (DWORDLONG flags)
{
	m_flgCommands.Set (flags);
}

YLB_INLINE void YCmdLineParser::SetOptions (DWORDLONG flags)
{
	m_flgOptions.Set (flags);
}

YLB_INLINE void YCmdLineParser::SetCommandFlags (DWORDLONG flags)
{
	m_flgCommands.SetFlags (flags);
}

YLB_INLINE void YCmdLineParser::SetOptionFlags (DWORDLONG flags)
{
	m_flgOptions.SetFlags (flags);
}

YLB_INLINE void YCmdLineParser::ClearCommandFlags (DWORDLONG flags)
{
	m_flgCommands.ClearFlags (flags);
}

YLB_INLINE void YCmdLineParser::ClearOptionFlags (DWORDLONG flags)
{
	m_flgOptions.ClearFlags (flags);
}

YLB_INLINE BOOL YCmdLineParser::TestCommandFlags (DWORDLONG flags, FLG_TEST_MODE mode) const
{
	return m_flgCommands.TestFlags (flags, mode);
}

YLB_INLINE BOOL YCmdLineParser::TestOptionFlags (DWORDLONG flags, FLG_TEST_MODE mode) const
{
	return m_flgOptions.TestFlags (flags, mode);
}

YLB_INLINE BOOL YCmdLineParser::GetParserResult () const
{
	return m_bParsingResult;
}

YLB_INLINE BOOL YCmdLineParser::OnProcessOption (BOOL &bTerminate, LPCTSTR &pszOptString, YCmdLineOption &cliOpt)
{
	// by default we do not accept any options
	return FALSE;
}

YLB_INLINE BOOL YCmdLineParser::OnProcessParam (BOOL &bTerminate, YCmdLineParam &cliPar)
{
	// by default we do not accept any parameters
	return FALSE;
}

YLB_INLINE BOOL YCmdLineParser::OnFinalCheck ()
{
	// by default we have no idea...
	return FALSE;
}

YLB_INLINE ITERATOR YCmdLineParser::GetOptionHeadPosition () const
{
	return (m_nNumOptions) ? ((ITERATOR) &(m_cliOptions[0])) : (NULL);
}

YLB_INLINE ITERATOR YCmdLineParser::GetOptionTailPosition () const
{
	return (m_nNumOptions) ? ((ITERATOR) &(m_cliOptions[m_nNumOptions - 1])) : (NULL);
}

YLB_INLINE YCmdLineOption * YCmdLineParser::GetOption (UINT nPos)
{
	return (m_nNumOptions && (nPos < m_nNumOptions)) ? (&(m_cliOptions[nPos])) : (NULL);
}

YLB_INLINE ITERATOR YCmdLineParser::GetParamHeadPosition () const
{
	return (m_nNumParams) ? ((ITERATOR) &(m_cliParams[0])) : (NULL);
}

YLB_INLINE ITERATOR YCmdLineParser::GetParamTailPosition () const
{
	return (m_nNumParams) ? ((ITERATOR) &(m_cliParams[m_nNumParams - 1])) : (NULL);
}

YLB_INLINE YCmdLineParam * YCmdLineParser::GetParam (UINT nPos)
{
	return (GetParamsCount () && (nPos < GetParamsCount ())) ? (&(m_cliParams[nPos])) : (NULL);
}

//
// EoF
////////
