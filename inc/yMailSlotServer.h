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
 * FILENAME		:	yMailSlotServer.h
 * PURPOSE		:	Declaration of the mailslot server class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:03:19  leo
 * Initial revision
 *
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