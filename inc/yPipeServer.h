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
 * FILENAME		:	yPipeServer.h
 * PURPOSE		:	Declaration of the pipe server classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
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