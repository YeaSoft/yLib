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
 * FILENAME		:	yPipeServer.h
 * PURPOSE		:	Declaration of the pipe server classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:03:23  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yPipeServer.h
 *============================================================================*/
#ifndef __yPipeServer_h__
#define __yPipeServer_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yThread_h__
#include <yThread.h>
#endif
#ifndef __yPipes_h__
#include <yPipes.h>
#endif

/*=============================================================================
 * FORWARD CLASS DECLARATIONS
 *============================================================================*/
class YPipeServer;
class YPipeInstance;
class _YPIPINST;

/*=============================================================================
 * PIPE SERVER INSTANCE CLASSES
 *============================================================================*/
class YPipeBaseInstance : public YObject
{
	DECLARE_DYNAMIC_CREATABLE	(YPipeBaseInstance);

private:
	// kill these construction methods & operators
	YPipeBaseInstance			(const YPipeBaseInstance &);
	YPipeBaseInstance			&operator=				(const YPipeBaseInstance &);

public:
	// construction/destruction
	YPipeBaseInstance			();
	virtual ~YPipeBaseInstance	();

public:
	// attributes
	YPipeServer *				GetPipeServer			() const;

public:
	// overridables
	virtual BOOL				InitInstance			(UINT nInstanceNumber);
	virtual void				ExitInstance			();
	virtual void				OnConnect				();
	virtual void				OnTransact				(LPVOID lpData, UINT cbData);
	virtual void				OnError					();
	virtual void				OnDisconnect			();
	virtual void				OnTerminate				();

protected:
	YPipeServer *				m_pPipeServer;
	_YPIPINST *					m_pInstDriver;

	friend class				_YPIPINST;
};

class YPipeInstance : public YPipeBaseInstance
{
	DECLARE_DYNAMIC_CREATABLE	(YPipeInstance);

private:
	// kill these construction methods & operators
	YPipeInstance				(const YPipeInstance &);
	YPipeInstance				&operator=				(const YPipeInstance &);

public:
	// construction/destruction
	YPipeInstance				();
	virtual ~YPipeInstance		();

public:
	// operations
	BOOL						WriteResponse			(LPCVOID lpData, UINT cbData);
};

class YAsyncPipeInstance : public YPipeBaseInstance
{
	DECLARE_DYNAMIC_CREATABLE	(YAsyncPipeInstance);

private:
	// kill these construction methods & operators
	YAsyncPipeInstance			(const YAsyncPipeInstance &);
	YAsyncPipeInstance			&operator=				(const YAsyncPipeInstance &);

public:
	// construction/destruction
	YAsyncPipeInstance			();
	virtual ~YAsyncPipeInstance	();

public:
	// operations
	BOOL						Send					(LPCVOID lpData, UINT cbData);
};

/*=============================================================================
 * PIPE SERVER CLASS
 *============================================================================*/
class YPipeServer : public YWorkerThread
{
private:
	// kill these construction methods & operators
	YPipeServer					(const YPipeServer &);
	YPipeServer					&operator=				(const YPipeServer &);

public:
	// construction/destruction
	YPipeServer					(
		YRuntimeInfo *			pInstance = NULL,
		LPCTSTR					pszPipeName = NULL,
		UINT					nMaxInstances = 0,
		UINT					nMaxProxies = 0,
		UINT					nTimer = 0,
		UINT					nPipeTimeout = 10000,
		UINT					cbReadBuffer = 0x4000,
		UINT					cbWriteBuffer = 0x4000,
		LPSECURITY_ATTRIBUTES	lpSecurityAttributes = NULL,
		LPCTSTR					pszName = _T("<pipeserver>")
	);
	~YPipeServer				();

public:
	// operations
	BOOL						TriggerProxy			(UINT nProxyNumber) const;

public:
	// overridables
	virtual void				OnTimer					();
	virtual void				OnProxy					(UINT nProxyNumber);

public:
	// attributes
	LPCTSTR						GetPipeName				() const;
	BOOL						SetPipeName				(LPCTSTR pszPipeName);
	YRuntimeInfo *				GetInstanceInfo			() const;
	BOOL						SetInstanceInfo			(YRuntimeInfo *pInstance);
	UINT						GetMaxInstances			() const;
	BOOL						SetMaxInstances			(UINT nMaxInstances);
	UINT						GetMaxProxies			() const;
	BOOL						SetMaxProxies			(UINT nMaxProxies);
	UINT						GetTimer				() const;
	void						SetTimer				(UINT nTimer);
	UINT						GetPipeTimeout			() const;
	void						SetPipeTimeout			(UINT nPipeTimeout);
	UINT						GetReadBufferSize		() const;
	BOOL						SetReadBufferSize		(UINT cbReadBufferSize);
	UINT						GetWriteBufferSize		() const;
	BOOL						SetWriteBufferSize		(UINT cbWriteBufferSize);
	LPSECURITY_ATTRIBUTES		GetSecurityAttributes	() const;
	BOOL						SetSecurityAttributes	(LPSECURITY_ATTRIBUTES lpSecurityAttributes);

protected:
	// implemented overridables
	virtual BOOL				Unlock					();
	virtual BOOL				PreCreateThread			(BOOL &bSuspended, UINT &uStackSize, LPSECURITY_ATTRIBUTES &lpThreadAttributes);
	virtual UINT				OnRunThread				(void);
	virtual void				OnQueryThreadTermination(void);
	virtual void				OnExitThread			(BOOL bRegularExit);

protected:
	// implementation
	BOOL						Allocate				();
	void						Deallocate				();
	void						SignalTermination		();
	UINT						SyncLoop				(_YPIPINST *lpPipe);
	UINT						AsyncLoop				(_YPIPINST *lpPipe);

protected:
	// implementation
	YRuntimeInfo *				m_pInstanceInfo;
	TCHAR						m_szPipeName[MAX_PATH];
	UINT						m_nMaxInstances;
	UINT						m_nMaxProxies;
	UINT						m_nTimer;
	UINT						m_nPipeTimeout;
	UINT						m_cbReadBufferSize;
	UINT						m_cbWriteBufferSize;
	LPSECURITY_ATTRIBUTES		m_lpSecurityAttributes;
	YSecurityAttributes			m_sa;
	YSecurityDescriptor			m_sd;
	//--- runtime members
	BOOL						m_fAsyncMode;
	YEvent						m_evTerm;
	LPVOID						m_pReserved;
	YSemaphore *				m_pspProxy;
	YMultiGuard					m_mgWaiter;
	int							m_iCurInstances;
};

#ifdef YLB_ENABLE_INLINE
#include <yPipeServer.inl>
#endif

#endif //__yPipeServer_h__
//
// EoF
////////