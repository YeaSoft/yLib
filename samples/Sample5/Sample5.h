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
 * FILENAME		:	Sample5.h
 * PURPOSE		:	yLib file splitter
 * SCOPE		:	yLib SDK
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/30  10:59:37  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#include "SampleRes5.h"

/*==================================================================================*
 * DATA STRUCTURES
 *==================================================================================*/
#pragma pack (1)

typedef struct _tagPARTINFO {
	DWORD			dwTag;
	DWORD			dwSize;
	TCHAR			szFileName[MAX_PATH];
	DWORD			dwAttributes;
	FILETIME		ftFileTime;
	DWORDLONG		dwlFileSize;
	DWORD			dwPartSize;
	DWORD			dwParts;
	DWORD			dwPart;
	DWORD			dwCRC;
} PARTINFO;

typedef struct _tagFOOTINFO {
	DWORD			dwTag;
	DWORD			dwSize;
} FOOTINFO;

#pragma pack ()

#define SPLOIN_HEADER			'SLOI'
#define SPLOIN_PARTFOOTER		'PART'

/*=============================================================================
 * OUR COMMANDLINE PARSER
 *============================================================================*/
// supported commands
#define CMD_WANTSHELP			0x00000001

#define CMD_SPLIT				0x00000002
#define CMD_JOIN				0x00000004
#define CMD_INFO				0x00000008

#define CMD_MASK				0xfffffffe
#define CMD_MASK_KNOWN			0x0000000e

#define OPT_RAWMODE				0x00000001
#define OPT_PARTSIZE			0x00000002
#define OPT_PARTS				0x00000004
#define OPT_UNKNOWN				0x80000000

class CMyParser : public YCmdLineParser
{
public:
	CMyParser					() { Parse (); }

public:
	// overridables
	virtual void				ShowIntro				();
	virtual void				ShowUsage				(DWORDLONG dwCmd);
	virtual void				ShowExtro				();

	virtual BOOL				OnProcessOption			(BOOL &bTerminate, LPCTSTR &pszOptString, YCmdLineOption &cliOpt);
	virtual BOOL				OnProcessParam			(BOOL &bTerminate, YCmdLineParam &cliPar);
	virtual BOOL				OnFinalCheck			();
};

/*==================================================================================*
 * OUR SAMPLE APPLICATION
 *==================================================================================*/
class FileSplitter : public YConApp, public YFileManager
{
public:
	FileSplitter				();

public:
	virtual void				Run						();

protected:
	BOOL						Info					(CMyParser &cliParser);
	BOOL						Split					(CMyParser &cliParser);
	BOOL						Join					(CMyParser &cliParser);
	BOOL						RawSplit				(CMyParser &cliParser);
	BOOL						RawJoin					(CMyParser &cliParser);
	BOOL						CreatePart				(YFile &inFile, YBuffer &workBuffer, DWORD dwPart);
	void						ShowError				(LPCTSTR pszFormat, ...);

	PARTINFO					m_pi;

	DWORD						m_dwPartFileSize;
	YPathString					m_ysSrcName;
	YPathString					m_ysDestFormat;
};

