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
 * FILENAME		:	Sample5.cpp
 * PURPOSE		:	yLib file Splitter
 * SCOPE		:	yLib SDK
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.2  2000/05/30  11:17:36  leo
 * Fixed some smaller bug
 *
 * Revision 1.1  2000/05/30  10:59:15  leo
 * Initial revision
 *
 *============================================================================*/

#include "StdAfc.h"
#include "Sample5.h"

/*=============================================================================
 * MACROS & DEFINES
 *============================================================================*/
// convenient macros for manipulating 64-bit integers to 32-bit integers
#define LOWPART_DWORDLONG		((DWORDLONG) 0x00000000FFFFFFFF)
#define HIGHPART_DWORDLONG		((DWORDLONG) 0xFFFFFFFF00000000)

#define MAKEDWORDLONG(lo,hi)	( (DWORDLONG) ( ( (hi) << 32 ) | (lo) ) )
#define LOWDWORD(x)				( (DWORD) ( (x) & LOWPART_DWORDLONG ) )
#define HIDWORD(x)				( (DWORD) ( ( (x) & HIGHPART_DWORDLONG ) >> 32 ) )

#define LOWPART_LONGLONG		((LONGLONG) 0x00000000FFFFFFFF)
#define HIGHPART_LONGLONG		((LONGLONG) 0xFFFFFFFF00000000)

#define LOWLONG(x)				( (DWORD) ( (x) & LOWPART_LONGLONG ) )
#define HILONG(x)				( (LONG) ( ( (x) & HIGHPART_LONGLONG ) >> 32 ) )

#define FLOPPYSIZE				1457664

/*=============================================================================
 * INSTANTIATE
 *============================================================================*/
FileSplitter			theApp;

/*=============================================================================
 * OUR COMMANDLINE PARSER
 *============================================================================*/
void CMyParser::ShowIntro ()
{
	// show credits
	_tprintf (_T("\nThis is %s v%i.%i, the %s\n"), theApp.GetAppName (), theApp.GetMajorVersion (), theApp.GetMinorVersion (), theApp.GetAppDescription ());
	_tprintf (_T("(c) 2000 YEAsoft Int'l. All rights reserved.\n\n"));
}

void CMyParser::ShowUsage (DWORDLONG dwCmd)
{
	YConApp	*pApp	= YlbGetApp ();

	switch ( dwCmd ) {
	case CMD_SPLIT:
		_tprintf (_T("USAGE: %s split [-r] [-s <size>] [-p <number>] <sourcefile> [destpath]\n\n"), pApp->GetImageName ());
		_tprintf (_T("       This command splits the sourcefile in one or more parts\n"));
		_tprintf (_T("       If the destination path is not specified, the split parts are\n"));
		_tprintf (_T("       stored in the source file directory.\n"));
		_tprintf (_T("       The following options are available:\n\n"));
		_tprintf (_T("       -r  Raw mode. The split parts contain no additional info.\n"));
		_tprintf (_T("           By default the split parts contain additional info about the\n"));
		_tprintf (_T("           original file and role of the split part.\n"));
		_tprintf (_T("       -s  The size of the split parts specified in bytes. If the number\n"));
		_tprintf (_T("           is followed by a K, this means that the number is interpreted\n"));
		_tprintf (_T("           as kilobytes, if followed by an M, it is interpreted as megabytes.\n"));
		_tprintf (_T("           The special number 1.44 means the size of a 1,44 Megabyte diskette.\n"));
		_tprintf (_T("       -p  Part number. Creates only the part with the specified number.\n"));
		_tprintf (_T("           It is also possible to specify more than one number separated\n"));
		_tprintf (_T("           by commas. Also it is possible to specify a range (e.g. 4-7).\n"));
		break;
	case CMD_JOIN:
		_tprintf (_T("USAGE: %s join <sourcefile pattern> [<sourcefile pattern> ...] <destpath>\n\n"), pApp->GetImageName ());
		_tprintf (_T("USAGE: %s join -r <sourcefile> [<sourcefile> ...] <destfile>\n\n"), pApp->GetImageName ());
		_tprintf (_T("       The first version of the command recreates the original file by\n"));
		_tprintf (_T("       joining the specified parts. If parts are specified with wildcards, the\n"));
		_tprintf (_T("       filenames are automatically expanded. The joined file will be\n"));
		_tprintf (_T("       created in the specified destination directory. The file will also\n"));
		_tprintf (_T("       be created if some part is missing. The missing range is than filled\n"));
		_tprintf (_T("       with 0x00. If the destination is not complete, it's name will be\n"));
		_tprintf (_T("       suffixed with the extension .partial. If such a partial file is found,\n"));
		_tprintf (_T("       the specified parts are added to the file. If the file is complete,\n"));
		_tprintf (_T("       it will be renamed to it's original name.\n\n"));
		_tprintf (_T("       The second version simply concatenates the raw parts specified.\n"));
		break;
	case CMD_INFO:
		_tprintf (_T("USAGE: %s info <filename>\n\n"), pApp->GetImageName ());
		_tprintf (_T("       This command shows information about the specified file.\n"));
		_tprintf (_T("       The file can be either a split part, or a partial joined file.\n"));
		break;
	default:
		_tprintf (_T("USAGE: %s <cmd> [options] [params]\n\n"), pApp->GetImageName ());
		_tprintf (_T("       where <cmd> can be:\n"));
		_tprintf (_T("       split            Splits a file\n"));
		_tprintf (_T("       join             Joins part files to a file\n"));
		_tprintf (_T("       info             Shows information about a file\n"));
		break;
	}
}

void CMyParser::ShowExtro ()
{
	_tprintf (_T("\n"));
}

BOOL CMyParser::OnProcessParam (BOOL &bTerminate, YCmdLineParam &cliPar)
{
	typedef struct {
		LPCTSTR	pszCmd;
		DWORD	appCmd;
	} CMDMATRIX;

	static CMDMATRIX	cmCmds[] = {
		{ _T("help"),		CMD_WANTSHELP },
		{ _T("split"),		CMD_SPLIT },
		{ _T("join"),		CMD_JOIN },
		{ _T("info"),		CMD_INFO }
	};

	DWORD dwCmd = 0;
	for ( DWORD dw = 0; dw < _countof (cmCmds); dw++ ) {
		if ( !_tcsicmp (cmCmds[dw].pszCmd, cliPar.GetParam ()) ) {
			dwCmd = cmCmds[dw].appCmd;
			break;
		} 
	}
	if ( dwCmd ) {
		// command recognized. do not add to list.
		SetCommandFlags (dwCmd);
		return FALSE;
	}
	// must be a path/filename. add to list
	cliPar.ResetAdditionalArgs ();
	return TRUE;
}

BOOL CMyParser::OnProcessOption (BOOL &bTerminate, LPCTSTR &pszOptString, YCmdLineOption &cliOpt)
{
	switch ( cliOpt.GetOption () ) {
	case _T('r'):
		SetOptionFlags (OPT_RAWMODE);
		cliOpt.SetMeaning (OPT_RAWMODE);
		cliOpt.ResetAdditionalArgs ();
		++pszOptString;
		return TRUE;
	case _T('s'):
		SetOptionFlags (OPT_PARTSIZE);
		cliOpt.SetMeaning (OPT_PARTSIZE);
		cliOpt.SetParamCount (1);
		++pszOptString;
		return TRUE;
	case _T('p'):
		SetOptionFlags (OPT_PARTS);
		cliOpt.SetMeaning (OPT_PARTS);
		cliOpt.SetParamCount (1);
		++pszOptString;
		return TRUE;
	}
	SetOptionFlags (OPT_UNKNOWN);
	return FALSE;
}

BOOL CMyParser::OnFinalCheck ()
{
	// no command or help wanted
	if ( !GetCommands () || TestCommandFlags (CMD_WANTSHELP) ) {
		SetCommandFlags (CMD_WANTSHELP);
		return TRUE;
	}
	// only one command permitted
	if ( TestCommandFlags (CMD_SPLIT|CMD_JOIN|CMD_INFO, FLG_OR) ) {
		if ( !TestCommandFlags (CMD_SPLIT|CMD_JOIN|CMD_INFO, FLG_XOR) ) {
			ShowIntro ();
			_tprintf (_T("ERROR: more than one command specified\n\n"));
			ShowUsage (GetCommands () & CMD_MASK);
			ShowExtro ();
			return FALSE;
		}
	}

	// unknown option specified
	if ( TestOptionFlags (OPT_UNKNOWN) ) {
		ShowIntro ();
		_tprintf (_T("ERROR: unknown option specified\n\n"));
		ShowUsage (0);
		ShowExtro ();
		return FALSE;
	}

	// part number and split size only with split
	if ( TestOptionFlags (OPT_PARTS|OPT_PARTSIZE, FLG_OR) && !TestCommandFlags (CMD_SPLIT) ) {
		ShowIntro ();
		_tprintf (_T("ERROR: option permitted only with 'split'\n\n"));
		ShowUsage (GetCommands () & CMD_MASK);
		ShowExtro ();
		return FALSE;
	}

	// check parts
	if ( TestOptionFlags (OPT_PARTS) ) {
		if ( !FindOptionByMeaning (OPT_PARTS)->GetParamCount () ) {
			ShowIntro ();
			_tprintf (_T("ERROR: no parts specified with -p\n\n"));
			ShowUsage (GetCommands () & CMD_MASK);
			ShowExtro ();
			return FALSE;
		}
	}

	// check part size
	if ( TestOptionFlags (OPT_PARTSIZE) ) {
		if ( !FindOptionByMeaning (OPT_PARTSIZE)->GetParamCount () ) {
			ShowIntro ();
			_tprintf (_T("ERROR: no size specified with -p\n\n"));
			ShowUsage (GetCommands () & CMD_MASK);
			ShowExtro ();
			return FALSE;
		}
	}

	// check files
	if ( !GetParamsCount () ) {
		ShowIntro ();
		_tprintf (_T("ERROR: no file specified\n\n"));
		ShowUsage (GetCommands () & CMD_MASK);
		ShowExtro ();
		return FALSE;
	}

	// check files
	if ( TestCommandFlags (CMD_JOIN, FLG_OR) ) {
		if ( GetParamsCount () < 2 ) {
			ShowIntro ();
			_tprintf (_T("ERROR: no destination specified\n\n"));
			ShowUsage (GetCommands () & CMD_MASK);
			ShowExtro ();
			return FALSE;
		}
	}

	return TRUE;
}


/*=============================================================================
 * OUR SAMPLE APPLICATION
 *============================================================================*/
FileSplitter::FileSplitter () : YConApp (IDS_APP_TITLE)
{
	memset (&m_pi, 0, sizeof (m_pi));

	m_pi.dwTag		= SPLOIN_HEADER;
	m_pi.dwSize		= sizeof (m_pi);
}

void FileSplitter::Run ()
{
	CMyParser	cliParser;

	if ( !cliParser.GetParserResult () ) {
		// we had an error and we had already shown it
		return;
	}

	cliParser.ShowIntro ();

	if ( cliParser.TestCommandFlags (CMD_WANTSHELP) ) {
		cliParser.ShowUsage (cliParser.GetCommands () & CMD_MASK);
		cliParser.ShowExtro ();
		return;
	}

	switch ( cliParser.GetCommands () ) {
	case CMD_SPLIT:
		SetReturnCode (Split (cliParser) ? (0) : (-1));
		break;
	case CMD_JOIN:
		SetReturnCode (Join (cliParser) ? (0) : (-1));
		break;
	case CMD_INFO:
		SetReturnCode (Info (cliParser) ? (0) : (-1));
		break;
	default:
		SetReturnCode (-1);
		break;
	}

	cliParser.ShowExtro ();
	return;
}

BOOL FileSplitter::Info (CMyParser &cliParser)
{
	return FALSE;
}

BOOL FileSplitter::Split (CMyParser &cliParser)
{
	m_ysSrcName = cliParser.GetParam (0)->GetParam ();

	if ( !m_ysSrcName.IsFile () ) {
		ShowError (_T("File %s does not exist"), m_ysSrcName);
		return FALSE;
	}

	if ( cliParser.GetParam (1) && !IsDir (cliParser.GetParam (1)->GetParam ()) ) {
		ShowError (_T("Directory %s does not exist"), cliParser.GetParam (1)->GetParam ());
		return FALSE;
	}

	if ( cliParser.GetParam (1) ) {
		m_ysDestFormat = cliParser.GetParam (1)->GetParam ();
		m_ysDestFormat.AppendBackslash (TRUE);
	}
	else {
		m_ysDestFormat = m_ysSrcName;
		m_ysDestFormat.StripFileName (TRUE);
	}
	m_ysDestFormat += m_ysSrcName.GetFileName ();
	m_ysDestFormat.StripExtension ();
	m_ysDestFormat += _T("-(%04.4i).");
	m_ysDestFormat += (cliParser.TestOptionFlags (OPT_RAWMODE)) ? (_T(".spl")) : (m_ysSrcName.GetFileExtension ());

	_tcscpy (m_pi.szFileName, m_ysSrcName.GetFileName ());

	DWORD dwSizeHi, dwSizeLo;
	if ( !IsFile (&m_pi.ftFileTime, &m_pi.dwAttributes, &dwSizeHi, &dwSizeLo, NULL, m_ysSrcName) ) {
		ShowError (_T("Cannot get source file information"));
		return FALSE;
	}
	m_pi.dwlFileSize = MAKEDWORDLONG (dwSizeLo, dwSizeHi);

	YCmdLineOption *pPartSize = cliParser.FindOptionByMeaning (OPT_PARTSIZE);
	if ( pPartSize && pPartSize->GetParamCount () ) {
		LPCTSTR lpPtr = pPartSize->GetAt (ZERO);
		if ( !_tcscmp (lpPtr, _T("1.44")) ) {
			m_pi.dwPartSize = FLOPPYSIZE;
		}
		LPTSTR	lpEnd;
		m_dwPartFileSize = _tcstoul (lpPtr, &lpEnd, 10);
		if ( !m_dwPartFileSize ) {
			ShowError (_T("Invalid part size '%s' specified."), lpPtr);
			return FALSE;
		}
		switch ( *lpEnd ) {
		case _T('k'):
		case _T('K'):
			if ( m_dwPartFileSize >= 0x00400000 ) {
				ShowError (_T("Part size '%s' specified would exceed 4GB."), lpPtr);
				return FALSE;
			}
			m_dwPartFileSize *= 1024;
			break;
		case _T('m'):
		case _T('M'):
			if ( m_dwPartFileSize >= 0x00001000 ) {
				ShowError (_T("Part size '%s' specified would exceed 4GB."), lpPtr);
				return FALSE;
			}
			m_dwPartFileSize *= (1024*1024);
			break;
		case 0:
			break;
		default:
			ShowError (_T("Invalid part size '%s' specified."), lpPtr);
			return FALSE;
		}
		if ( m_dwPartFileSize < (64*1024) ) {
			ShowError (_T("Part size '%s' is less than 64KB."), lpPtr);
			return FALSE;
		}

	}
	else {
		m_dwPartFileSize = FLOPPYSIZE;
	}

	if ( cliParser.TestOptionFlags (OPT_RAWMODE) ) {
		return RawSplit (cliParser);
	}

	m_pi.dwPartSize	= m_dwPartFileSize - m_pi.dwSize;
	m_pi.dwParts	= (DWORD) ((m_pi.dwlFileSize / m_pi.dwPartSize) + 1);

	_tprintf (_T("Filename : %s\n"), m_pi.szFileName);
	_tprintf (_T("Size     : %I64u Bytes\n"), m_pi.dwlFileSize);
	_tprintf (_T("Part Size: %lu Bytes\n"), m_dwPartFileSize);
	_tprintf (_T("Parts    : %lu\n\n"), m_pi.dwParts);

	YFile	inFile;
	YBuffer	ybBuffer;

	if ( !ybBuffer.Alloc (128*1024) ) {
		ShowError (_T("Cannot allocate memory"));
		return FALSE;
	}

	if ( !inFile.Open (m_ysSrcName, YFile::modeRead|YFile::shareDenyWrite|YFile::cacheSequentialOptimized) ) {
		ShowError (_T("Cannot open source file '%s'"), m_ysSrcName);
		return FALSE;
	}

	YCmdLineOption *pParts = cliParser.FindOptionByMeaning (OPT_PARTS);
	if ( !pParts ) {
		// process all
		for ( DWORD dwCnt = 0; dwCnt < m_pi.dwParts; dwCnt++ ) {
			if ( !CreatePart (inFile, ybBuffer, dwCnt) ) {
				return FALSE;
			}
		}
	}
	else {
	}

	return TRUE;
}

BOOL FileSplitter::Join (CMyParser &cliParser)
{
	return FALSE;
}

BOOL FileSplitter::RawSplit (CMyParser &cliParser)
{
	return FALSE;
}

BOOL FileSplitter::RawJoin (CMyParser &cliParser)
{
	return FALSE;
}

BOOL FileSplitter::CreatePart (YFile &inFile, YBuffer &workBuffer, DWORD dwPart)
{
	YCrc32			crc;
	YFile			outFile;
	YPathString		outFileName;

	// position into the source file
	DWORDLONG		dwlStartPos = ((DWORDLONG) dwPart * (DWORDLONG) m_pi.dwPartSize);
	LONG			lStartPosHi = HILONG(dwlStartPos);
	if ( !inFile.Seek (LOWDWORD(dwlStartPos), &lStartPosHi) ) {
		ShowError (_T("Error positioning in source file (err: %d)"), ::GetLastError ());
		return FALSE;
	}

	outFileName.Format (m_ysDestFormat, dwPart);
	if ( !outFile.Open (outFileName, YFile::modeCreate|YFile::modeWrite|YFile::cacheSequentialOptimized) ) {
		ShowError (_T("Error creating destination file '%s'"), outFileName);
		return FALSE;
	}

	// reserve space for header
	if ( !outFile.Write (workBuffer, sizeof (m_pi)) ) {
		ShowError (_T("Error writing destination file '%s'"), outFileName);
		return FALSE;
	}

	// write out the stuff
	DWORD dwRest = m_pi.dwPartSize;

	while ( dwRest ) {
		if ( !inFile.Read (workBuffer, min (workBuffer.GetSize (), dwRest)) ) {
			ShowError (_T("Error reading from source file (err: %d)"), ::GetLastError ());
			return FALSE;
		}
		crc.UpdateCrc (workBuffer, workBuffer.GetSize ());
		dwRest = (inFile.GetBytesRead () > dwRest) ? (0) : (dwRest - inFile.GetBytesRead ());
		if ( !outFile.Write (workBuffer, inFile.GetBytesRead ()) ) {
			ShowError (_T("Error writing to destination file (err: %d)"), ::GetLastError ());
			return FALSE;
		}
	}

	// position at beginning to write out header
	if ( !outFile.Seek (0) ) {
		ShowError (_T("Error positioning in destination file (err: %d)"), ::GetLastError ());
		return FALSE;
	}

	m_pi.dwPart	= dwPart;
	m_pi.dwCRC	= crc.GetCrc ();

	if ( !outFile.Write (&m_pi, sizeof (m_pi)) ) {
		ShowError (_T("Error writing to destination file (err: %d)"), ::GetLastError ());
		return FALSE;
	}

	return TRUE;
}

void FileSplitter::ShowError (LPCTSTR pszFormat, ...)
{
	va_list va;

	va_start (va, pszFormat);
	_tprintf (_T("ERROR: "));
	_vtprintf (pszFormat, va);
	_tprintf (_T("\n"));
	va_end (va);
}


#if (0)
	_tprintf (_T("\nThis is %s, the %s\n"), GetAppName (), GetAppDescription ());
	_tprintf (_T("(c) 2000 YEAsoft Int'l. All rights reserved.\n\n"));

	if ( (cli->GetParamCount () != 2) && (cli->GetParamCount () != 3) ) {
		ShowError (_T("Invalid Parameters"));
		ShowUsage ();
		return FALSE;
	}

	if ( !YFileManager::IsFile (cli->GetAt (1)) ) {
		ShowError (_T("File %s does not exists"), cli->GetAt (1));
		ShowUsage ();
		return FALSE;
	}

	DWORD dwChunkSize = 5 * 1024 * 1024;

	if ( cli->GetParamCount () == 3 ) {
		dwChunkSize = _ttol (cli->GetAt (2));
	}
	if ( (dwChunkSize < 1024*1024) || (dwChunkSize > 512 * 1024 * 1024) ) {
		ShowError (_T("Invalid chunk size %lu (must be between 1M and 512M"), dwChunkSize);
		ShowUsage ();
		return FALSE;
	}
	dwChunkSize = ((dwChunkSize / 1024) * 1024);

	YPathString		ysPath, ysName, ysDest;
	YString16		ysExt;

	YFileNameHandler::SplitPath (cli->GetAt (1), ysPath.GetBuffer (), ysName.GetBuffer (), ysExt.GetBuffer ());

	if ( ysPath.GetLength () ) {
		ysPath += _T("\\");
	}

	YFile	yfSrc;
	YFile	yfDst;
	YBuffer	ybBuffer;

	if ( !ybBuffer.Alloc (128*1024) ) {
		ShowError (_T("Cannot allocate memory"));
		return FALSE;
	}

	if ( !yfSrc.Create (cli->GetAt (1), GENERIC_READ) ) {
		ShowError (_T("Cannot open file (err: %d) %s"), ::GetLastError (), cli->GetAt (1));
		return FALSE;
	}

	DWORD dwParts = (yfSrc.GetLength () / dwChunkSize);
	_tprintf (_T("File %s will be split in %d parts a %lu bytes\n"), cli->GetAt (1), dwParts + 1, dwChunkSize);


	for ( DWORD dwPart = 0; dwPart < dwParts; dwPart++ ) {
		_tprintf (_T("Creating part %d..."), dwPart + 1);
		ysDest.Format (_T("%s%s (%d).%s"), (LPCTSTR) ysPath, (LPCTSTR) ysName, dwPart + 1, (LPCTSTR) ysExt);
		if ( !yfDst.Create (ysDest) ) {
			_tprintf (_T("\n"));
			ShowError (_T("Cannot create output file %s (err: %d)"), ysDest, ::GetLastError ());
			return FALSE;
		}
		DWORD dwRest = dwChunkSize;

		while ( dwRest ) {
			if ( !yfSrc.Read (ybBuffer, min (ybBuffer.GetSize (), dwRest)) ) {
				_tprintf (_T("\n"));
				ShowError (_T("Error reading from source file (err: %d)"), ::GetLastError ());
				return FALSE;
			}
			dwRest = (yfSrc.GetBytesRead () > dwRest) ? (0) : (dwRest - yfSrc.GetBytesRead ());
			if ( !yfDst.Write (ybBuffer, yfSrc.GetBytesRead ()) ) {
				_tprintf (_T("\n"));
				ShowError (_T("Error writing to destination file (err: %d)"), ::GetLastError ());
				return FALSE;
			}
		}
		yfDst.Close ();
		_tprintf (_T("\n"));
	}

	DWORD dwRest = yfSrc.GetLength () - (dwParts * dwChunkSize);

	if ( dwRest ) {
		_tprintf (_T("Creating part %d..."), dwParts + 1);
		ysDest.Format (_T("%s\\%s (%d).%s"), (LPCTSTR) ysPath, (LPCTSTR) ysName, dwParts + 1, (LPCTSTR) ysExt);
		if ( !yfDst.Create (ysDest) ) {
			_tprintf (_T("\n"));
			ShowError (_T("Cannot create output file %s (err: %d)"), ysDest, ::GetLastError ());
			return FALSE;
		}

		while ( dwRest ) {
			if ( !yfSrc.Read (ybBuffer, ybBuffer.GetSize ()) ) {
				_tprintf (_T("\n"));
				ShowError (_T("Error reading from source file (err: %d)"), ::GetLastError ());
				return FALSE;
			}
			dwRest = (yfSrc.GetBytesRead () > dwRest) ? (0) : (dwRest - yfSrc.GetBytesRead ());
			if ( !yfDst.Write (ybBuffer, yfSrc.GetBytesRead ()) ) {
				_tprintf (_T("\n"));
				ShowError (_T("Error writing to destination file (err: %d)"), ::GetLastError ());
				return FALSE;
			}
		}
		yfDst.Close ();
		_tprintf (_T("\n"));
	}
	_tprintf (_T("Done.\n"));

	return TRUE;
#endif

//
// EoF
////////