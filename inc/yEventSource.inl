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
 * FILENAME		:	yEventSource.inl
 * PURPOSE		:	Inline members of the Eventlog source class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
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