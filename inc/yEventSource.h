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
 * FILENAME		:	yEventSource.h
 * PURPOSE		:	Declaration of the Eventlog source class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*============================================================================*
 * @doc YLIB | yEventSource.h
 *============================================================================*/
#ifndef __yEventSource_h__
#define __yEventSource_h__

/*============================================================================*
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yLibBase_h__
#include <yLibBase.h>
#endif

/*============================================================================*
 * MAKROS & DEFINES
 *============================================================================*/
#define EVENTLOG_ALL_STD				(EVENTLOG_ERROR_TYPE | EVENTLOG_WARNING_TYPE | EVENTLOG_INFORMATION_TYPE)

/*============================================================================*
 * CLASS DEFINITIONS
 *============================================================================*/
class YEventLogSource
{
public:
	// construction/destruction
	YEventLogSource				();
	~YEventLogSource			();

public:
	// operations
	void						Attach					(HANDLE hEventSource);
	HANDLE						Detach					();

	static BOOL					Install					(LPCTSTR lpSourceName, LPCTSTR lpEventMessageFile, UINT cbCategoryCount = 0, LPCTSTR lpCategoryMessageFile = NULL, DWORD dwTypesSupported = EVENTLOG_ALL_STD);
	static BOOL					Install					(LPCTSTR lpComputerName, LPCTSTR lpSourceName, LPCTSTR lpEventMessageFile, UINT cbCategoryCount = 0, LPCTSTR lpCategoryMessageFile = NULL, DWORD dwTypesSupported = EVENTLOG_ALL_STD);
	static BOOL					Uninstall				(LPCTSTR lpSourceName, LPCTSTR lpComputerName = NULL);

	BOOL						Register				(LPCTSTR lpSourceName, LPCTSTR lpUNCServerName = NULL);
	BOOL						Deregister				();

	BOOL						ReportEvent				(WORD wType, WORD wCategory, DWORD dwEventID, PSID lpUserSid, WORD wNumStrings = 0, LPCTSTR* lpStrings = NULL, DWORD dwDataSize = 0, LPVOID lpRawData = NULL) const;
	BOOL						ReportEvent				(WORD wType, WORD wCategory, DWORD dwEventID, WORD wNumStrings = 0, LPCTSTR* lpStrings = NULL, DWORD dwDataSize = 0, LPVOID lpRawData = NULL) const;
	BOOL						ReportVa				(WORD wType, WORD wCategory, DWORD dwEventID, va_list va) const;
	BOOL						ReportEx				(WORD wType, WORD wCategory, DWORD dwEventID, ...) const;
	BOOL						ReportVa				(WORD wType, DWORD dwEventID, va_list va) const;
	BOOL						Report					(WORD wType, DWORD dwEventID, ...) const;
	BOOL						ErrorVa					(WORD wCategory, DWORD dwEventID, va_list va) const;
	BOOL						ErrorEx					(WORD wCategory, DWORD dwEventID, ...) const;
	BOOL						ErrorVa					(DWORD dwEventID, va_list va) const;
	BOOL						Error					(DWORD dwEventID, ...) const;
	BOOL						WarningVa				(WORD wCategory, DWORD dwEventID, va_list va) const;
	BOOL						WarningEx				(WORD wCategory, DWORD dwEventID, ...) const;
	BOOL						WarningVa				(DWORD dwEventID, va_list va) const;
	BOOL						Warning					(DWORD dwEventID, ...) const;
	BOOL						InfoVa					(WORD wCategory, DWORD dwEventID, va_list va) const;
	BOOL						InfoEx					(WORD wCategory, DWORD dwEventID, ...) const;
	BOOL						InfoVa					(DWORD dwEventID, va_list va) const;
	BOOL						Info					(DWORD dwEventID, ...) const;

public:
	// attributes
	void						SetOriginatorSID		(PSID pSid);
	BOOL						SetOriginatorSID		(LPCTSTR lpszUserName = NULL);
	PSID						GetOriginatorSID		() const;
	void						SetDefaultCategory		(WORD wCategory);
	WORD						GetDefaultCategory		() const;
	void						SetInserts				(DWORD dwNumInserts, LPCTSTR *lplpInserts);

private:
	// implementation
	HANDLE						m_hEventSource;
	PSID						m_pSID;
	BOOL						m_bSidAllocated;
	WORD						m_wCategory;
	DWORD						m_dwNumInserts;
	LPCTSTR *					m_lplpInserts;
};


#ifdef YLB_ENABLE_INLINE
#include <yEventSource.inl>
#endif

#endif //__yEventSource_h__

//
// EoF
////////
