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
 * FILENAME		:	yConsole.h
 * PURPOSE		:	Declaration of the NT console class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.2  2000/09/04 11:59:53  leopoldo
 * Updated license to zlib/libpng
 *
 * Revision 1.1  2000/05/26 14:02:58  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yConsole.h
 *============================================================================*/
#ifndef __yConsole_h__
#define __yConsole_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yFixStr_h__
#include <yFixStr.h>
#endif

/*=============================================================================
 * FORWARD CLASS DECLARATIONS
 *============================================================================*/
class YConsole;

/*=============================================================================
 * CLASS DECLARATIONS
 *============================================================================*/
class YConsole
{
private:
	// kill these construction methods & operators
	YConsole					(const YConsole &);
	YConsole					&operator=				(const YConsole &);

public:
	// construction/destruction
	YConsole					();
	~YConsole					();

public:
	// operations
	static BOOL					Allocate				(BOOL bReattachRTL = TRUE);
	static BOOL					Free					();

	BOOL						WriteVa					(LPCTSTR pszFormat, va_list va) const;
	BOOL						WriteLnVa				(LPCTSTR pszFormat, va_list va) const;
	BOOL						ErrorVa					(LPCTSTR pszFormat, va_list va) const;
	BOOL						ErrorLnVa				(LPCTSTR pszFormat, va_list va) const;

	BOOL						Write					(LPCTSTR pszFormat, ...) const;
	BOOL						WriteLn					(LPCTSTR pszFormat, ...) const;
	BOOL						Error					(LPCTSTR pszFormat, ...) const;
	BOOL						ErrorLn					(LPCTSTR pszFormat, ...) const;

	YConsole &					operator<<				(LPCTSTR lpsz);
#ifdef _UNICODE
	YConsole &					operator<<				(LPCSTR lpsz);
#else
	YConsole &					operator<<				(LPCWSTR lpsz);
#endif
	YConsole &					operator<<				(const void* lp);
	YConsole &					operator<<				(BYTE by);
	YConsole &					operator<<				(WORD w);
	YConsole &					operator<<				(UINT u);
	YConsole &					operator<<				(LONG l);
	YConsole &					operator<<				(DWORD dw);
	YConsole &					operator<<				(float f);
	YConsole &					operator<<				(double d);
	YConsole &					operator<<				(int n);

public:
	// attributes
	static BOOL					IsAllocated				();

	static BOOL					SetConsoleTitle			(LPCTSTR lpConsoleTitle);
	static DWORD				GetConsoleTitle			(LPTSTR lpConsoleTitle, DWORD nSize);
	static YString256			GetConsoleTitle			();


protected:
	// implementation
	BOOL						Err						(BOOL fAppendLF, LPCTSTR pszString, int cbLength = -1) const;
	BOOL						ErrVa					(BOOL fAppendLF, LPCTSTR pszFormat, va_list va) const;
	BOOL						Out						(BOOL fAppendLF, LPCTSTR pszString, int cbLength = -1) const;
	BOOL						OutVa					(BOOL fAppendLF, LPCTSTR pszFormat, va_list va) const;
	BOOL						Out						(HANDLE hHandle, BOOL fAppendLF, LPCTSTR pszString, int cbLength = -1) const;
	BOOL						OutVa					(HANDLE hHandle, BOOL fAppendLF, LPCTSTR pszFormat, va_list va) const;

protected:
	// implementation
};

#ifdef YLB_ENABLE_INLINE
#include <yConsole.inl>
#endif

#endif //__yConsole_h__
//
// EoF
////////