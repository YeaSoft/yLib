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
 * FILENAME		:	yAfcBase.inl
 * PURPOSE		:	Inline implementation for base classes and global functions
 * SCOPE		:	yAfc
 * HISTORY		: =============================================================
 * 
 * $Log$
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

//
// EoF
////////
