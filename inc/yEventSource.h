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
 * FILENAME		:	yEventSource.h
 * PURPOSE		:	Declaration of the Eventlog source class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:03:01  leo
 * Initial revision
 *
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
