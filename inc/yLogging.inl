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
 * FILENAME		:	yLogging.inl
 * PURPOSE		:	Inline members of the logging classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2002/05/08 09:59:32  leo
 * Initial Sourceforge Revision
 *
 * Revision 1.2  2000/09/04 11:59:53  leopoldo
 * Updated license to zlib/libpng
 *
 * Revision 1.1  2000/05/26 14:03:16  leo
 * Initial revision
 *
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

YLB_INLINE BOOL YLogHandler::FatalDetail (LPCTSTR lpszFormat, ...)
{
	va_list	va;
	va_start (va, lpszFormat);
	BOOL bRet = WriteVa (LOG_F_CFATAL, lpszFormat, va);
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

YLB_INLINE BOOL YLogHandler::ErrorDetail (LPCTSTR lpszFormat, ...)
{
	va_list	va;
	va_start (va, lpszFormat);
	BOOL bRet = WriteVa (LOG_F_CERROR, lpszFormat, va);
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