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
 * FILENAME		:	yConsole.inl
 * PURPOSE		:	Inline members of the NT console class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.2  2000/09/04 11:59:53  leopoldo
 * Updated license to zlib/libpng
 *
 * Revision 1.1  2000/05/26 14:02:59  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yConsole.h
 *============================================================================*/
YLB_INLINE YConsole::YConsole ()
{
}

YLB_INLINE YConsole::~YConsole ()
{
}

YLB_INLINE BOOL YConsole::WriteVa (LPCTSTR pszFormat, va_list va) const
{
	return OutVa (FALSE, pszFormat, va);
}

YLB_INLINE BOOL YConsole::WriteLnVa (LPCTSTR pszFormat, va_list va) const
{
	return OutVa (TRUE, pszFormat, va);
}

YLB_INLINE BOOL YConsole::ErrorVa (LPCTSTR pszFormat, va_list va) const
{
	return ErrVa (FALSE, pszFormat, va);
}

YLB_INLINE BOOL YConsole::ErrorLnVa (LPCTSTR pszFormat, va_list va) const
{
	return ErrVa (TRUE, pszFormat, va);
}


YLB_INLINE BOOL YConsole::Write (LPCTSTR pszFormat, ...) const
{
	va_list va;
	va_start (va, pszFormat);
	BOOL bRet = OutVa (FALSE, pszFormat, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YConsole::WriteLn (LPCTSTR pszFormat, ...) const
{
	va_list va;
	va_start (va, pszFormat);
	BOOL bRet = OutVa (TRUE, pszFormat, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YConsole::Error (LPCTSTR pszFormat, ...) const
{
	va_list va;
	va_start (va, pszFormat);
	BOOL bRet = ErrVa (FALSE, pszFormat, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YConsole::ErrorLn (LPCTSTR pszFormat, ...) const
{
	va_list va;
	va_start (va, pszFormat);
	BOOL bRet = ErrVa (TRUE, pszFormat, va);
	va_end (va);
	return bRet;
}

YLB_INLINE YConsole& YConsole::operator<< (LPCTSTR lpsz)
{
	if ( lpsz ) {
		Out (FALSE, lpsz);
	}
	return *this;
}

YLB_INLINE YConsole& YConsole::operator<< (const void* lp)
{
	TCHAR szBuffer[16];
	int iLen = _sntprintf (szBuffer, _countof (szBuffer), _T("0x%08x"), lp);
	Out (FALSE, szBuffer, iLen);
	return *this;
}

YLB_INLINE YConsole& YConsole::operator<< (BYTE by)
{
	TCHAR szBuffer[32];
	_itot ((int) by, szBuffer, 10);
	Out (FALSE, szBuffer);
	return *this;
}

YLB_INLINE YConsole& YConsole::operator<< (WORD w)
{
	TCHAR szBuffer[32];
	_ultot ((unsigned long) w, szBuffer, 10);
	Out (FALSE, szBuffer);
	return *this;
}

YLB_INLINE YConsole& YConsole::operator<< (UINT u)
{
	TCHAR szBuffer[32];
	_ultot (u, szBuffer, 10);
	Out (FALSE, szBuffer);
	return *this;
}

YLB_INLINE YConsole& YConsole::operator<< (LONG l)
{
	TCHAR szBuffer[32];
	_ltot (l, szBuffer, 10);
	Out (FALSE, szBuffer);
	return *this;
}

YLB_INLINE YConsole& YConsole::operator<< (DWORD dw)
{
	TCHAR szBuffer[32];
	_ultot (dw, szBuffer, 10);
	Out (FALSE, szBuffer);
	return *this;
}

YLB_INLINE YConsole& YConsole::operator<< (float f)
{
	TCHAR szBuffer[256];
	int iLen = _sntprintf (szBuffer, _countof (szBuffer), _T("%f"), f);
	Out (FALSE, szBuffer, iLen);
	return *this;
}

YLB_INLINE YConsole& YConsole::operator<< (double d)
{
	TCHAR szBuffer[256];
	int iLen = _sntprintf (szBuffer, _countof (szBuffer), _T("%f"), d);
	Out (FALSE, szBuffer, iLen);
	return *this;
}

YLB_INLINE YConsole& YConsole::operator<< (int n)
{
	TCHAR szBuffer[32];
	_itot (n, szBuffer, 10);
	Out (FALSE, szBuffer);
	return *this;
}

YLB_INLINE BOOL YConsole::IsAllocated ()
{
	return YlbIsAttachedToConsole ();
}

YLB_INLINE BOOL YConsole::SetConsoleTitle (LPCTSTR lpConsoleTitle)
{
	return ::SetConsoleTitle (lpConsoleTitle);
}

YLB_INLINE DWORD YConsole::GetConsoleTitle (LPTSTR lpConsoleTitle, DWORD nSize)
{
	return ::GetConsoleTitle (lpConsoleTitle, nSize);
}

YLB_INLINE YString256 YConsole::GetConsoleTitle ()
{
	YString256 ysBuffer;
	::GetConsoleTitle (ysBuffer.GetBuffer (), ysBuffer.GetBufferSize ());
	return ysBuffer;
}


//
// EoF
////////
