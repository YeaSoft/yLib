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
 * FILENAME		:	yLib.cpp
 * PURPOSE		:	Implementation of base classes and global functions
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.4  2001/09/26 11:14:09  leopoldo
 * Fixed UNICODE issues
 *
 * Revision 1.3  2001/05/16 17:15:53  leopoldo
 * Added support for reattachment of RTL output handles
 *
 * Revision 1.2  2000/09/04 12:07:43  leopoldo
 * Updated license to zlib/libpng
 *
 * Revision 1.1  2000/05/26 14:05:02  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yLibBase.h
 *============================================================================*/
#include "StdInc.hpp"

#include <fcntl.h>
#include <io.h>

#ifdef _DEBUG
#undef HERE
static char HERE[] = __FILE__;
#endif //_DEBUG

/*=============================================================================
 * LIBRARY GLOBAL VARIABLES
 *============================================================================*/
YAUX_DATA						ylbData;

/*=============================================================================
 * Helpers
 *============================================================================*/
// @func BOOL | YlbIsValidString | Tests a string for validity
// @syntax <b>BOOL YLBAPI YlbIsValidString (LPCWSTR<n> lpsz<b>, int<n> nLength = <b>-1)<n>
// @syntax <b>BOOL YLBAPI YlbIsValidString (LPCSTR<n> lpsz<b>, int<n> nLength = <b>-1)<n>
// @parm LPCSTR | lpsz | The pointer to test
// @parm int | nLength | Specifies the length of the string to be tested,
//		in bytes. A value of -1 indicates that the string will be
//		null-terminated.
// @rdesc Nonzero if the specified pointer points to a string of the
//		specified size; otherwise 0.
// @comm Use this function to determine whether a pointer to a
//		string is valid.
// @xref <f YlbIsValidAddress>, <j Global Library Functions>
//
BOOL YLBAPI YlbIsValidString (LPCWSTR lpsz, int nLength)
{
	if ( lpsz == NULL ) {
		return FALSE;
	}
	return ylbData.bWin95 || (::IsBadStringPtrW (lpsz, nLength) == 0);
}

BOOL YLBAPI YlbIsValidString (LPCSTR lpsz, int nLength /* = -1 */)
{
	if ( lpsz == NULL ) {
		return FALSE;
	}
	return ::IsBadStringPtrA (lpsz, nLength) == 0;
}

// @func BOOL | YlbIsValidAddress | Tests a memory block for validity
// @parm const void* | lp | Points to the memory address to be tested.
// @parm UINT | nBytes | Contains the number of bytes of memory to
//		be tested.
// @parm BOOL | bReadWrite = TRUE | Specifies whether the memory is both for
//		reading and writing (<TRUE>) or just reading (<FALSE>).
// @rdesc Nonzero if the specified memory block is contained entirely
//		within the program’s memory space; otherwise 0.
// @comm Tests any memory address to ensure that it is contained
//		entirely within the program’s memory space. The address is
//		not restricted to blocks allocated by <b>new<n>.
// @xref <f YlbIsValidString>, <j Global Library Functions>
//
BOOL YLBAPI YlbIsValidAddress (const void* lp, UINT nBytes, BOOL bReadWrite)
{
	// simple version using Win-32 APIs for pointer validation.
	return (lp != NULL && !IsBadReadPtr (lp, nBytes) && (!bReadWrite || !IsBadWritePtr ((LPVOID) lp, nBytes)));
}

#ifdef _DEBUG

BOOL YLBAPI YlbAssertFailedLine (LPCSTR lpszFileName, int nLine)
{
	TCHAR	szMessage[_MAX_PATH*2];


	wsprintf (szMessage, _T("%s: File %hs, Line %d"), _T("<unknown>")/*lpszAppName*/, lpszFileName, nLine);

	// assume the debugger or auxiliary port
	TCHAR	szT[_MAX_PATH*2 + 20];
	wsprintf (szT, _T("Assertion Failed: %s\n"), szMessage);
	OutputDebugString (szT);

	// we remove WM_QUIT because if it is in the queue then the message box
	// won't display
	MSG		msg;
	BOOL	bQuit	= PeekMessage (&msg, NULL, WM_QUIT, WM_QUIT, PM_REMOVE);
	BOOL	bResult	= _CrtDbgReport (_CRT_ASSERT, lpszFileName, nLine, NULL, NULL);
	if ( bQuit ) {
		PostQuitMessage (msg.wParam);
	}

	return bResult;
}

#endif

int YLBAPI YlbLoadString (UINT nID, LPTSTR lpszBuf, UINT nMaxBuf)
{
	ASSERTY(YlbIsValidAddress(lpszBuf, nMaxBuf * sizeof(TCHAR)));

	int nLen = ::LoadString (YlbGetResourceHandle (), nID, lpszBuf, nMaxBuf);
	if ( (nLen == 0) && nMaxBuf ) {
		lpszBuf[0] = '\0';
	}
	return nLen;
}

BOOL YLBAPI YlbGetSysErrorString (DWORD dwError, LPTSTR lpszBuf, UINT nMaxBuf)
{
	return FormatMessage (
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dwError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		lpszBuf,
		nMaxBuf,
		NULL 
	) != 0;
}

BOOL YLBAPI YlbIsAttachedToConsole ()
{
	if ( _proc.m_hStdOut != ::GetStdHandle (STD_OUTPUT_HANDLE) ) {
		_proc.m_hStdIn	= ::GetStdHandle (STD_INPUT_HANDLE);
		_proc.m_hStdOut	= ::GetStdHandle (STD_OUTPUT_HANDLE);
		_proc.m_hStdErr	= ::GetStdHandle (STD_ERROR_HANDLE);
	}
	return _proc.m_hStdOut != NULL;
}

BOOL YLBAPI YlbReattachRTL ()
{
	if ( !YlbIsAttachedToConsole () ) {
		return FALSE;
	}

	if ( _proc.m_fpStdOut ) {
		fclose (_proc.m_fpStdOut);
		_proc.m_fpStdOut = NULL;
	}
	if ( _proc.m_fpStdErr ) {
		fclose (_proc.m_fpStdErr);
		_proc.m_fpStdErr = NULL;
	}
	if ( _proc.m_iStdOut != -1 ) {
		_close (_proc.m_iStdOut);
		_proc.m_iStdOut = -1;
	}
	if ( _proc.m_iStdErr != -1 ) {
		_close (_proc.m_iStdErr);
		_proc.m_iStdErr = -1;
	}

	_proc.m_iStdOut = _open_osfhandle ((long) ::GetStdHandle (STD_OUTPUT_HANDLE), _O_TEXT);
	_proc.m_iStdErr = _open_osfhandle ((long) ::GetStdHandle (STD_ERROR_HANDLE), _O_TEXT);
	if ( _proc.m_iStdOut != -1 ) {
		_proc.m_fpStdOut = _tfdopen (_proc.m_iStdOut, _T("wt"));
	}
	if ( _proc.m_iStdErr != -1 ) {
		_proc.m_fpStdErr = _tfdopen (_proc.m_iStdOut, _T("wt"));
	}
	if ( _proc.m_fpStdOut ) {
		*stdout = *_proc.m_fpStdOut;
	}
	if ( _proc.m_fpStdErr ) {
		*stderr = *_proc.m_fpStdErr;
	}
	return _proc.m_fpStdOut && _proc.m_fpStdErr;
}

HINSTANCE YLBAPI YlbGetResourceHandle ()
{
	return _proc.m_hResHandle;
}

HINSTANCE YLBAPI YlbGetInstanceHandle ()
{
	return _proc.m_hInstance;
}

HANDLE YLBAPI YlbGetProcessHandle ()
{
	return _proc.m_hProcessHandle;
}

HANDLE YLBAPI YlbGetThreadHandle ()
{
	return _proc.m_hThreadHandle;
}


///////////////////////////////////////////////////////////////////////////////
// Conversion helpers (these use the current system locale)
int YLB_CDECL _ywcstombsz (char* mbstr, const wchar_t* wcstr, size_t count)
{
	if ( (count == 0) && (mbstr != NULL) ) {
		return 0;
	}

	int result = ::WideCharToMultiByte(CP_ACP, 0, wcstr, -1, mbstr, count, NULL, NULL);
	ASSERTY(mbstr == NULL || result <= (int)count);
	if ( result > 0 ) {
		mbstr[result-1] = 0;
	}
	else if ( ::GetLastError () == ERROR_INSUFFICIENT_BUFFER ) {
		mbstr[count - 1] = 0;
	}
	return result;
}

int YLB_CDECL _ymbstowcsz (wchar_t* wcstr, const char* mbstr, size_t count)
{
	if ( (count == 0) && (wcstr != NULL) ) {
		return 0;
	}

	int result = ::MultiByteToWideChar(CP_ACP, 0, mbstr, -1, wcstr, count);
	ASSERTY(wcstr == NULL || result <= (int)count);
	if ( result > 0 ) {
		wcstr[result-1] = 0;
	}
	else if ( ::GetLastError () == ERROR_INSUFFICIENT_BUFFER ) {
		wcstr[count - 1] = 0;
	}
	return result;
}

BOOL YLB_CDECL _yxtot (DWORD dwVal, LPTSTR pszBuffer, UINT cbBuffer, BOOL fIsNegative)
{
	LPTSTR	lpPtr	= pszBuffer;
	LPTSTR	lpFirst;
	TCHAR	cTemp;
	UINT	nDigVal;

	if ( !cbBuffer ) {
		return FALSE;
	}

	if ( fIsNegative ) {
		// negative: output '-' and negate value
		if ( !--cbBuffer ) {
			*lpPtr = 0;
			return FALSE;
		}
		*lpPtr++ = _T('-');
		dwVal = (DWORD) (- (LONG) dwVal);
	}

	if ( cbBuffer == 1 ) {
		*lpPtr = 0;
		return FALSE;
	}

	lpFirst = lpPtr;

	do {
		nDigVal	= (dwVal % 10);
		dwVal	/= 10;
		*lpPtr++ = (TCHAR) (nDigVal + _T('0'));
	} while ( dwVal && (--cbBuffer > 1) );

	// zero terminate
	*lpPtr-- = 0;

	// now reverse the string

	do {
		cTemp		= *lpPtr;
		*lpPtr		= *lpFirst;
		*lpFirst	= cTemp;
		--lpPtr;
		++lpFirst;
	} while ( lpFirst < lpPtr );
	return !dwVal && (cbBuffer > 1);
}

LPWSTR YLBAPI YlbA2WHelper (LPWSTR lpw, LPCSTR lpa, int nChars)
{
	if ( lpa == NULL ) {
		return NULL;
	}
	ASSERTY(lpw != NULL);
	// verify that no illegal character present
	// since lpw was allocated based on the size of lpa
	// don't worry about the number of chars
	lpw[0] = '\0';
	ASSERTY(MultiByteToWideChar (CP_ACP, 0, lpa, -1, lpw, nChars));
	return lpw;
}

LPSTR YLBAPI YlbW2AHelper (LPSTR lpa, LPCWSTR lpw, int nChars)
{
	if ( lpw == NULL ) {
		return NULL;
	}
	ASSERTY(lpa != NULL);
	// verify that no illegal character present
	// since lpa was allocated based on the size of lpw
	// don't worry about the number of chars
	lpa[0] = '\0';
	ASSERTY(WideCharToMultiByte (CP_ACP, 0, lpw, -1, lpa, nChars, NULL, NULL));
	return lpa;
}

/*=============================================================================
 * LIBRARY GLOBAL ENVIRONMENT DATA
 *============================================================================*/
// Initialization code
YAUX_DATA::YAUX_DATA()
{
	// Cache various target platform version information
	DWORD dwVersion		= ::GetVersion();
	nWinVer				= (LOBYTE(dwVersion) << 8) + HIBYTE(dwVersion);
	bWin95				= (dwVersion & 0x80000000) != 0;
	bWin4				= (BYTE) dwVersion >= 4;
	bNotWin4			= 1 - bWin4;   // for convenience
}

// Termination code
YAUX_DATA::~YAUX_DATA()
{
}

/*=============================================================================
 * COMMANDLINE INFO
 *============================================================================*/
bool YCommandLineInfo::Shift ()
{
	if ( !m_argc || !m_argv ) {
		return false;
	}
	--m_argc;
	++m_argv;
	return true;
}

LPCTSTR YCommandLineInfo::GetAt (ITERATOR pos) const
{
	LPTSTR *lpPtr = (LPTSTR *) pos;
	if ( lpPtr < &(m_argv[0]) ) {
		// junk
		return NULL;
	}
	if ( lpPtr <= &(m_argv[m_argc - 1]) ) {
		// in list
		return *lpPtr;
	}
	// beyond
	return NULL;
}

LPCTSTR YCommandLineInfo::GetNext (ITERATOR &pos) const
{
	LPTSTR *lpPtr = (LPTSTR *) pos;
	if ( lpPtr < &(m_argv[0]) ) {
		// junk
		pos = NULL;
		return NULL;
	}
	if ( lpPtr < &(m_argv[m_argc - 1]) ) {
		// in list
		pos = (ITERATOR) &(lpPtr[1]);
		return *lpPtr;
	}
	if ( lpPtr == &(m_argv[m_argc - 1]) ) {
		// last element
		pos = NULL;
		return *lpPtr;
	}
	// beyond
	pos = NULL;
	return NULL;
}

LPCTSTR YCommandLineInfo::GetPrev (ITERATOR &pos) const
{
	LPTSTR *lpPtr = (LPTSTR *) pos;
	if ( lpPtr < &(m_argv[0]) ) {
		// junk
		pos = NULL;
		return NULL;
	}
	if ( lpPtr == &(m_argv[0]) ) {
		// first element
		pos = NULL;
		return *lpPtr;
	}
	if ( lpPtr < &(m_argv[m_argc - 1]) ) {
		// in list
		pos = (ITERATOR) &(lpPtr[-1]);
		return *lpPtr;
	}
	// beyond
	pos = NULL;
	return NULL;
}

LPCTSTR YCommandLineInfo::Skip (ITERATOR &pos, UINT nSkip) const
{
	LPTSTR *lpPtr = (LPTSTR *) pos;
	lpPtr += nSkip;
	if ( lpPtr < &(m_argv[0]) ) {
		// junk
		pos = NULL;
		return NULL;
	}
	if ( lpPtr <= &(m_argv[m_argc - 1]) ) {
		// in list
		pos = (ITERATOR) lpPtr;
		return *lpPtr;
	}
	// beyond
	pos = NULL;
	return NULL;
}

/*=============================================================================
 * DYNAMIC OBJECT MODEL
 *============================================================================*/
const struct YRuntimeInfo		YObject::infoYObject = { NULL, NULL, NULL };

YRuntimeInfo* YObject::GetRuntimeInfo () const
{
	return RUNTIME_INFO(YObject);
}

BOOL YObject::IsKindOf(const YRuntimeInfo* pClass) const
{
	ASSERTY(this != NULL);
	ASSERTY(YlbIsValidAddress(this, sizeof(YObject)));
	YRuntimeInfo* pClassThis = GetRuntimeInfo ();
	return pClassThis->IsDerivedFrom (pClass);
}

YObject* YRuntimeInfo::CreateObject ()
{
	if ( !m_pfnCreateObject ) {
		return NULL;
	}

	YObject* pObject = NULL;
	pObject = (*m_pfnCreateObject) ();
	return pObject;
}

BOOL YRuntimeInfo::IsDerivedFrom (const YRuntimeInfo* pBaseClass) const
{
	ASSERTY(this != NULL);
	ASSERTY(YlbIsValidAddress(this, sizeof(YRuntimeInfo), FALSE));
	ASSERTY(pBaseClass != NULL);
	ASSERTY(YlbIsValidAddress(pBaseClass, sizeof(YRuntimeInfo), FALSE));

	const YRuntimeInfo* pClassThis = this;
	while ( pClassThis ) {
		if ( pClassThis == pBaseClass ) {
			return TRUE;
		}
		pClassThis = pClassThis->m_pBaseClass;
	}
	return FALSE;
}


#ifndef YLB_ENABLE_INLINE
#include <yLibBase.inl>
#endif

/// IDENTITY STUFF ///
#pragma comment( exestr, "$Id$" )

//
// EoF
////////