/*=============================================================================
 * This is a part of the yLib Software Development Kit.
 * Copyright (C) 1998-1999 YEAsoft Inc.
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
 * FILENAME		:	yLogging.inl
 * PURPOSE		:	Inline members of the logging classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yLogging.h
 *============================================================================*/
YLB_INLINE YLogHandler::YLogHandler ()
{
	m_lfModify	= 0;
}

YLB_INLINE BOOL YLogHandler::OutVa (LOG_FLAG logFlag, LPCTSTR lpszFormat, va_list va)
{
	return FALSE;
}

YLB_INLINE BOOL YLogHandler::WriteVa (LOG_FLAG logFlag, LPCTSTR lpszFormat, va_list va)
{
	if ( m_lfModify.TestClearFlags (LOG_F_ONCE) ) {
		BOOL bRet = OutVa (logFlag | m_lfModify, lpszFormat, va);
		m_lfModify = 0;
		return bRet;
	}
	return OutVa (logFlag | m_lfModify, lpszFormat, va);
}

YLB_INLINE BOOL YLogHandler::Write (LOG_FLAG logFlag, LPCTSTR lpszFormat, ...)
{
	va_list	va;
	va_start (va, lpszFormat);
	BOOL bRet = WriteVa (logFlag, lpszFormat, va);
	va_end (va);
	return bRet;
}

YLB_INLINE void YLogHandler::Once (LOG_FLAG logFlag)
{
	m_lfModify	= logFlag | LOG_F_ONCE;
}

YLB_INLINE void YLogHandler::Modify (LOG_FLAG logFlag /* = 0 */)
{
	m_lfModify	= logFlag;
}

YLB_INLINE BOOL YLogHandler::Fatal (LPCTSTR lpszFormat, ...)
{
	va_list	va;
	va_start (va, lpszFormat);
	BOOL bRet = WriteVa (LOG_F_FATAL, lpszFormat, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YLogHandler::Error (LPCTSTR lpszFormat, ...)
{
	va_list	va;
	va_start (va, lpszFormat);
	BOOL bRet = WriteVa (LOG_F_ERROR, lpszFormat, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YLogHandler::Warning (LPCTSTR lpszFormat, ...)
{
	va_list	va;
	va_start (va, lpszFormat);
	BOOL bRet = WriteVa (LOG_F_WARNING, lpszFormat, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YLogHandler::Info (LPCTSTR lpszFormat, ...)
{
	va_list	va;
	va_start (va, lpszFormat);
	BOOL bRet = WriteVa (LOG_F_INFO, lpszFormat, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YLogHandler::Debug (LPCTSTR lpszFormat, ...)
{
	va_list	va;
	va_start (va, lpszFormat);
	BOOL bRet = WriteVa (LOG_F_DEBUG, lpszFormat, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YLogHandler::Dbg1 (LPCTSTR lpszFormat, ...)
{
	va_list	va;
	va_start (va, lpszFormat);
	BOOL bRet = WriteVa (LOG_F_XDBG1, lpszFormat, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YLogHandler::Dbg2 (LPCTSTR lpszFormat, ...)
{
	va_list	va;
	va_start (va, lpszFormat);
	BOOL bRet = WriteVa (LOG_F_XDBG2, lpszFormat, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YLogHandler::Dbg3 (LPCTSTR lpszFormat, ...)
{
	va_list	va;
	va_start (va, lpszFormat);
	BOOL bRet = WriteVa (LOG_F_XDBG3, lpszFormat, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YLogHandler::Dbg4 (LPCTSTR lpszFormat, ...)
{
	va_list	va;
	va_start (va, lpszFormat);
	BOOL bRet = WriteVa (LOG_F_XDBG4, lpszFormat, va);
	va_end (va);
	return bRet;
}

//
// EoF
////////