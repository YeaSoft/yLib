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
 * FILENAME		:	yLogging.h
 * PURPOSE		:	Declaration of the logging classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yLogging.h
 *============================================================================*/
#ifndef __yLogging_h__
#define __yLogging_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yLibBase_h__
#include <yLibBase.h>
#endif
#ifndef __yFlags_h__
#include <yFlags.h>
#endif

/*=============================================================================
 * CONSTANTS
 *============================================================================*/
typedef DWORD					LOG_FLAG;	// @type	LOG_FLAG | Logging message flags.

/* logging flags */
#define LOG_F_FATAL				0x00000001	// @flag	LOG_F_FATAL | fatal error
#define LOG_F_ERROR				0x00000002	// @flag	LOG_F_ERROR | error
#define LOG_F_WARNING			0x00000004	// @flag	LOG_F_WARNING | warning
#define LOG_F_INFO				0x00000008	// @flag	LOG_F_INFO | informational message
#define LOG_F_DEBUG				0x00000010	// @flag	LOG_F_DEBUG | standard debug message
#define LOG_F_XDBG1				0x00000020	// @flag	LOG_F_XDBG1 | extended debug message level 1
#define LOG_F_XDBG2				0x00000040	// @flag	LOG_F_XDBG2 | extended debug message level 2
#define LOG_F_XDBG3				0x00000080	// @flag	LOG_F_XDBG3 | extended debug message level 3
#define LOG_F_XDBG4				0x00000100	// @flag	LOG_F_XDBG4 | extended debug message level 4
#define LOG_F_ASSERT			0x00000200	// @flag	LOG_F_ASSERT | debug assertion

/* compound logging flags */
#define XMR_F_CFATAL			0x00040001	// @flag	LOG_F_CFATAL | fatal error with detailed error information appended
#define XMR_F_CERROR			0x00040002	// @flag	LOG_F_CERROR | error with detailed error information appended
#define XMR_F_CWARNING			0x00040004	// @flag	LOG_F_CWARNING | warning with detailed error information appended

/* modifier flags */
#define LOG_F_ALWAYS			0x00010000	// @flag	LOG_F_ALWAYS | message is displayed always
#define LOG_F_ERRSTR			0x00040000	// @flag	LOG_F_ERRSTR | appends the last error message string
#define LOG_F_OEMSTR			0x00080000	// @flag	LOG_F_OEMSTR | converts an oem string to an ansi string

#define LOG_F_ONCE				0x80000000	// modification applies only once
#define LOG_M_FLAGS				0x0000ffff	// These are message flags
#define LOG_M_MODIFIERS			0xffff0000	// These are the flag modifiers

/*=============================================================================
 * THE LOGGING BASE CLASS
 *============================================================================*/
class YLogHandler
{
public:
	// construction
	// @cmember Constructs a logging handler
	YLogHandler					();

protected:
	// @access Overridable operations Operations
	// @cmember The logging output function
	virtual BOOL				OutVa				(LOG_FLAG logFlag, LPCTSTR lpszFormat, va_list va);

public:
	// @access Operations
	// @cmember Outputs a fatal error log message
	BOOL						Fatal				(LPCTSTR lpszFormat, ...);
	// @cmember Outputs a fatal error log message with detailed error information
	BOOL						FatalDetail			(LPCTSTR lpszFormat, ...);
	// @cmember Outputs an error log message
	BOOL						Error				(LPCTSTR lpszFormat, ...);
	// @cmember Outputs an error log message with detailed error information
	BOOL						ErrorDetail			(LPCTSTR lpszFormat, ...);
	// @cmember Outputs a warning log message
	BOOL						Warning				(LPCTSTR lpszFormat, ...);
	// @cmember Outputs a warning log message with detailed error information
	BOOL						WarningDetail		(LPCTSTR lpszFormat, ...);
	// @cmember Outputs an informational log message
	BOOL						Info				(LPCTSTR lpszFormat, ...);
	// @cmember Outputs a debug log message
	BOOL						Debug				(LPCTSTR lpszFormat, ...);
	// @cmember Outputs an extended debug level 1 log message
	BOOL						Dbg1				(LPCTSTR lpszFormat, ...);
	// @cmember Outputs an extended debug level 2 log message
	BOOL						Dbg2				(LPCTSTR lpszFormat, ...);
	// @cmember Outputs an extended debug level 3 log message
	BOOL						Dbg3				(LPCTSTR lpszFormat, ...);
	// @cmember Outputs an extended debug level 4 log message
	BOOL						Dbg4				(LPCTSTR lpszFormat, ...);
	// @cmember Outputs an assertion log message
	BOOL						Assert				(LPCTSTR lpszFormat, ...);

	// @cmember Outputs a log message
	BOOL						Write				(LOG_FLAG logFlag, LPCTSTR lpszFormat, ...);
	// @cmember Outputs a log message
	BOOL						WriteVa				(LOG_FLAG logFlag, LPCTSTR lpszFormat, va_list va);

	// @cmember modifies the logging flag once
	void						Once				(LOG_FLAG logFlag);
	// @cmember modifies the logging flag once
	void						Modify				(LOG_FLAG logFlag = 0);

protected:
	YFlags						m_lfModify;
};

/*=============================================================================
 * THE FILE LOGGING CLASS
 *============================================================================*/
class YLogFileHandler : public YLogHandler, public YFlags
{
public:
	// construction
	YLogFileHandler				() { m_hFile = INVALID_HANDLE_VALUE; SetVerbosityLevel (); m_bOpenOnDemand = FALSE; }
	~YLogFileHandler			() { Close (); }

public:
	// attributes
	DWORD						SetLogFilter		(LOG_FLAG lfFilter) { return Set (lfFilter); }
	void						SetVerbosityLevel	(int iLevel = 0);
	void						SetOpenMode			(BOOL bOpenOnDemand = FALSE);
	BOOL						IsOpen				() { return m_hFile != INVALID_HANDLE_VALUE; }

public:
	// operations
	BOOL						Open				(LPCTSTR pszName, BOOL bTruncate = TRUE);
	void						Close				() { if ( m_hFile != INVALID_HANDLE_VALUE ) CloseHandle (m_hFile); m_hFile = INVALID_HANDLE_VALUE; }

protected:
	virtual BOOL				OutVa				(LOG_FLAG logFlag, LPCTSTR lpszFormat, va_list va);

protected:
	// implementation
	BOOL						ReOpen				(BOOL bTrucate);

private:
	// implementation
	HANDLE						m_hFile;
	BOOL						m_bOpenOnDemand;
	TCHAR						m_szFileName[MAX_PATH];
};

#ifdef YLB_ENABLE_INLINE
#include <yLogging.inl>
#endif

#endif //__yLogging_h__
//
// EoF
////////