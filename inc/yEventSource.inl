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
 * FILENAME		:	yEventSource.inl
 * PURPOSE		:	Inline members of the Eventlog source class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:03:02  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yEventSource.h
 *============================================================================*/
YLB_INLINE YEventLogSource::YEventLogSource ()
{
	m_hEventSource	= NULL;
	m_pSID			= NULL;
	m_bSidAllocated	= FALSE;
	m_wCategory		= 0;
	m_dwNumInserts	= 0;
	m_lplpInserts	= NULL;
}

YLB_INLINE YEventLogSource::~YEventLogSource ()
{
	if ( m_pSID && m_bSidAllocated ) {
		free (m_pSID);
	}
	Deregister ();
}

YLB_INLINE void YEventLogSource::Attach (HANDLE hEventSource)
{
	if ( m_hEventSource != hEventSource ) {
		Deregister ();
	}

	m_hEventSource = hEventSource;
}

YLB_INLINE HANDLE YEventLogSource::Detach ()
{
	HANDLE	hReturn	= m_hEventSource;
	m_hEventSource	= NULL;
	return hReturn;
}

YLB_INLINE void YEventLogSource::SetOriginatorSID (PSID pSid)
{
	if ( m_pSID && m_bSidAllocated ) {
		free (m_pSID);
		m_bSidAllocated	= FALSE;
	}
	m_pSID = pSid;
}

YLB_INLINE PSID YEventLogSource::GetOriginatorSID () const
{
	return m_pSID;
}

YLB_INLINE void YEventLogSource::SetDefaultCategory (WORD wCategory)
{
	m_wCategory = wCategory;
}

YLB_INLINE WORD YEventLogSource::GetDefaultCategory () const
{
	return m_wCategory;
}

YLB_INLINE void YEventLogSource::SetInserts (DWORD dwNumInserts, LPCTSTR *lplpInserts)
{
	if ( !lplpInserts ) {
		dwNumInserts = 0;
	}
	m_dwNumInserts	= dwNumInserts;
	m_lplpInserts	= lplpInserts;
}


YLB_INLINE BOOL YEventLogSource::ReportEvent (WORD wType, WORD wCategory, DWORD dwEventID, PSID lpUserSid, WORD wNumStrings, LPCTSTR* lpStrings, DWORD dwDataSize, LPVOID lpRawData) const
{
	if ( !m_hEventSource ) {
		return FALSE;
	}
	return ::ReportEvent (m_hEventSource, wType, wCategory, dwEventID, lpUserSid, wNumStrings, dwDataSize, lpStrings, lpRawData);
}

YLB_INLINE BOOL YEventLogSource::ReportEvent (WORD wType, WORD wCategory, DWORD dwEventID, WORD wNumStrings, LPCTSTR* lpStrings, DWORD dwDataSize, LPVOID lpRawData) const
{
	if ( !m_hEventSource ) {
		return FALSE;
	}
	return ::ReportEvent (m_hEventSource, wType, wCategory, dwEventID, m_pSID, wNumStrings, dwDataSize, lpStrings, lpRawData);
}

YLB_INLINE BOOL YEventLogSource::ReportEx (WORD wType, WORD wCategory, DWORD dwEventID, ...) const
{
	va_list va;

	va_start (va, dwEventID);
	BOOL bRet = ReportVa (wType, wCategory, dwEventID, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YEventLogSource::Report (WORD wType, DWORD dwEventID, ...) const
{
	va_list va;

	va_start (va, dwEventID);
	BOOL bRet = ReportVa (wType, dwEventID, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YEventLogSource::ErrorVa (WORD wCategory, DWORD dwEventID, va_list va) const
{
	return ReportVa (EVENTLOG_ERROR_TYPE, wCategory, dwEventID, va);
}

YLB_INLINE BOOL YEventLogSource::ErrorEx (WORD wCategory, DWORD dwEventID, ...) const
{
	va_list va;

	va_start (va, dwEventID);
	BOOL bRet = ReportVa (EVENTLOG_ERROR_TYPE, wCategory, dwEventID, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YEventLogSource::ErrorVa (DWORD dwEventID, va_list va) const
{
	return ReportVa (EVENTLOG_ERROR_TYPE, m_wCategory, dwEventID, va);
}

YLB_INLINE BOOL YEventLogSource::Error (DWORD dwEventID, ...) const
{
	va_list va;

	va_start (va, dwEventID);
	BOOL bRet = ReportVa (EVENTLOG_ERROR_TYPE, m_wCategory, dwEventID, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YEventLogSource::WarningVa (WORD wCategory, DWORD dwEventID, va_list va) const
{
	return ReportVa (EVENTLOG_WARNING_TYPE, wCategory, dwEventID, va);
}

YLB_INLINE BOOL YEventLogSource::WarningEx (WORD wCategory, DWORD dwEventID, ...) const
{
	va_list va;

	va_start (va, dwEventID);
	BOOL bRet = ReportVa (EVENTLOG_WARNING_TYPE, wCategory, dwEventID, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YEventLogSource::WarningVa (DWORD dwEventID, va_list va) const
{
	return ReportVa (EVENTLOG_WARNING_TYPE, m_wCategory, dwEventID, va);
}

YLB_INLINE BOOL YEventLogSource::Warning (DWORD dwEventID, ...) const
{
	va_list va;

	va_start (va, dwEventID);
	BOOL bRet = ReportVa (EVENTLOG_WARNING_TYPE, m_wCategory, dwEventID, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YEventLogSource::InfoVa (WORD wCategory, DWORD dwEventID, va_list va) const
{
	return ReportVa (EVENTLOG_INFORMATION_TYPE, wCategory, dwEventID, va);
}

YLB_INLINE BOOL YEventLogSource::InfoEx (WORD wCategory, DWORD dwEventID, ...) const
{
	va_list va;

	va_start (va, dwEventID);
	BOOL bRet = ReportVa (EVENTLOG_INFORMATION_TYPE, wCategory, dwEventID, va);
	va_end (va);
	return bRet;
}

YLB_INLINE BOOL YEventLogSource::InfoVa (DWORD dwEventID, va_list va) const
{
	return ReportVa (EVENTLOG_INFORMATION_TYPE, m_wCategory, dwEventID, va);
}

YLB_INLINE BOOL YEventLogSource::Info (DWORD dwEventID, ...) const
{
	va_list va;

	va_start (va, dwEventID);
	BOOL bRet = ReportVa (EVENTLOG_INFORMATION_TYPE, m_wCategory, dwEventID, va);
	va_end (va);
	return bRet;
}

//
// EoF
////////