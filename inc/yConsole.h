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
 * FILENAME		:	yConsole.h
 * PURPOSE		:	Declaration of the NT console class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
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
	BOOL						Allocate				();
	BOOL						Free					();
	BOOL						LoadHandles				();
	void						ClearHandles			();

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
	BOOL						IsAllocated				() const;
	BOOL						AreHandlesValid			() const;

	BOOL						SetConsoleTitle			(LPCTSTR lpConsoleTitle) const;
	DWORD						GetConsoleTitle			(LPTSTR lpConsoleTitle, DWORD nSize) const;
	YString256					GetConsoleTitle			() const;


protected:
	// implementation
	BOOL						Out						(HANDLE hHandle, BOOL fAppendLF, LPCTSTR pszString, int cbLength = -1) const;
	BOOL						OutVa					(HANDLE hHandle, BOOL fAppendLF, LPCTSTR pszFormat, va_list va) const;

protected:
	// implementation
	HANDLE						m_hStdIn;
	HANDLE						m_hStdOut;
	HANDLE						m_hStdErr;
};

#ifdef YLB_ENABLE_INLINE
#include <yConsole.inl>
#endif

#endif //__yConsole_h__
//
// EoF
////////