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
 * FILENAME		:	yMailSlotServer.h
 * PURPOSE		:	Declaration of the mailslot server class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yMailSlotServer.h
 *============================================================================*/
#ifndef __yMailSlotServer_h__
#define __yMailSlotServer_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yThread_h__
#include <yThread.h>
#endif
#ifndef __yMailSlots_h__
#include <yMailSlots.h>
#endif

/*=============================================================================
 * MAILSLOT SERVER CLASS
 *============================================================================*/
class YMailslotServer : public YWorkerThread
{
private:
	// kill these construction methods & operators
	YMailslotServer				(const YMailslotServer &);
	YMailslotServer				&operator=				(const YMailslotServer &);

public:
	// construction/destruction
	YMailslotServer				(
		LPCTSTR					pszMailslotName = NULL,
		UINT					nTimer = 0,
		DWORD					dwMaxMessageSize = 0,
		UINT					cbReadBuffer = 0x0200,
		DWORD					dwReadTimeout = MAILSLOT_WAIT_FOREVER,
		LPSECURITY_ATTRIBUTES	lpSecurityAttributes = NULL,
		LPCTSTR					pszName = _T("<mailslotserver>")
	);
	~YMailslotServer			();

public:
	// operations

public:
	// overridables
	virtual void				OnTimer					();
	virtual void				OnReceive				(LPVOID lpData, UINT cbData);
	virtual void				OnFatalError			(DWORD dwError);
	// advanced overridables
	virtual BOOL				OnIncreaseBuffer		();

protected:
	// implemented overridables
	virtual BOOL				Unlock					();
	virtual BOOL				PreCreateThread			(BOOL &bSuspended, UINT &uStackSize, LPSECURITY_ATTRIBUTES &lpThreadAttributes);
	virtual UINT				OnRunThread				(void);
	virtual void				OnQueryThreadTermination(void);
	virtual void				OnExitThread			(BOOL bRegularExit);

public:
	// attributes
	LPCTSTR						GetMailslotName			() const;
	BOOL						SetMailslotName			(LPCTSTR pszMailslotName);
	UINT						GetTimer				() const;
	void						SetTimer				(UINT nTimer);
	DWORD						GetMaxMessageSize		() const;
	BOOL						SetMaxMessageSize		(DWORD dwMaxMessageSize);
	DWORD						GetReadTimeout			() const;
	BOOL						SetReadTimeout			(DWORD dwReadTimeout);
	UINT						GetReadBufferSize		() const;
	BOOL						SetReadBufferSize		(UINT cbReadBufferSize);
	LPSECURITY_ATTRIBUTES		GetSecurityAttributes	() const;
	BOOL						SetSecurityAttributes	(LPSECURITY_ATTRIBUTES lpSecurityAttributes);

protected:
	// implementation
	BOOL						Allocate				();
	void						Deallocate				();

protected:
	// implementation
	TCHAR						m_szMailslotName[MAX_PATH];
	UINT						m_nTimer;
	DWORD						m_dwMaxMessageSize;
	DWORD						m_dwReadTimeout;
	UINT						m_cbReadBufferSize;
	LPSECURITY_ATTRIBUTES		m_lpSecurityAttributes;
	YSecurityAttributes			m_sa;
	YSecurityDescriptor			m_sd;
	//--- runtime members
	YEvent						m_evTerm;
	YEvent						m_evRead;
	YServerMailslot				m_ms;
	YBuffer						m_lpReadBuffer;
};


#ifdef YLB_ENABLE_INLINE
#include <yMailSlotServer.inl>
#endif

#endif //__yMailSlotServer_h__
//
// EoF
////////