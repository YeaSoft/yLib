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
 * Revision 1.1  2000/05/30  10:59:15  leo
 * Initial revision
 *
 *============================================================================*/

#include "StdAfc.h"
#include "Sample5.h"

/*=============================================================================
 * INSTANTIATE
 *============================================================================*/
FileSplitter			theApp;

/*=============================================================================
 * OUR SAMPLE APPLICATION
 *============================================================================*/
BOOL FileSplitter::InitInstance (YCommandLineInfo *cli)
{
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
}

void FileSplitter::ShowError (LPCTSTR pszFormat, ...)
{
	va_list va;

	va_start (va, pszFormat);
	_tprintf (_T("\nERROR: "));
	_vtprintf (pszFormat, va);
	_tprintf (_T("\n"));
	va_end (va);
}

void FileSplitter::ShowUsage ()
{
	_tprintf (_T("\nUSAGE: Split <filename> [chunk size]\n\n"));
}


//
// EoF
////////