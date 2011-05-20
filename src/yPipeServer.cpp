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
 * FILENAME		:	yPipeServer.cpp
 * PURPOSE		:	Implementation of the pipe server classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.3  2001/10/05 13:31:27  leopoldo
 * Fixed missing auto-instance-creation
 *
 * Revision 1.2  2000/09/04 12:07:43  leopoldo
 * Updated license to zlib/libpng
 *
 * Revision 1.1  2000/05/26 14:05:07  leo
 * Initial revision
 *
 *============================================================================*/

#include "StdInc.hpp"

/*=============================================================================
 * @doc YLIB | yPipeServer.h
 *============================================================================*/

/*=============================================================================
 * FILE IO COMPLETION ROUTINE
 *============================================================================*/

/*=============================================================================
 * HELPER CLASS
 *============================================================================*/
typedef enum {
	psNone,
	psConnecting,
	psReading,
	psWriting
} PIPESTATE;

class _YPIPINST
{
public:
	// construction/destruction
	_YPIPINST					();
	~_YPIPINST					();

public:
	// operations
	BOOL						Init					(YPipeServer *pPS);
	BOOL						Instantiate				(LPCTSTR lpName, UINT nCurInstance, UINT nMaxInstances, UINT nOutBufferSize, UINT nInBufferSize, UINT nTimeOut, LPSECURITY_ATTRIBUTES lpSA);
	void						Deinstantiate			();
	void						Deinit					();
	void						ConnectToNewClient		();
	void						DisconnectAndReconnect	(BOOL bSignalDisconnection);
	BOOL						Read					(BOOL &fSuccess, BOOL &fReady, DWORD &cbBytes);
	void						ReadAsync				(BOOL &fSuccess, BOOL &fReady, DWORD &cbBytes);
	void						Write					(BOOL &fSuccess, BOOL &fReady, DWORD &cbBytes);
	BOOL						Connect					(BOOL &fSuccess, BOOL &fReady);
	void						Error					(BOOL &fSuccess, BOOL &fReady);
	BOOL						WriteResponse			(LPCVOID lpData, UINT cbData);
	BOOL						Send					(LPCVOID lpData, UINT cbData);
	void						SyncLoop				();
	void						AsyncLoop				();
	static void WINAPI			PSO_Routine				(DWORD, DWORD, LPOVERLAPPED);

public:
	// attributes
	BOOL						IsIOPending				() const { return m_fPendingIO; }
	void						SetIOPending			(BOOL fIOPending = TRUE) { m_fPendingIO = fIOPending; }
	YEvent *					GetEvent				() { return &m_evEvent; }
	PIPESTATE					GetState				() const { return m_state; }
	void						SetState				(PIPESTATE state) { m_state = state; }
	DWORD						GetWriteSize			() const { return m_cbToWrite; }
	void						SetWriteSize			(DWORD cbToWrite) { m_cbToWrite = cbToWrite; }

public:
	// implementation
	OVERLAPPED					m_oOverlap;
	DWORD						m_cbToWrite;
	PIPESTATE					m_state;
	BOOL						m_fPendingIO;
	YEvent						m_evEvent;
	YServerNamedPipe			m_np;
	YPipeServer *				m_pPS;
	YPipeBaseInstance *			m_pPI;
	LPVOID						m_pInBuffer;
	LPVOID						m_pOutBuffer;
};

_YPIPINST::_YPIPINST ()
{
	memset (&m_oOverlap, 0, sizeof (m_oOverlap));
	m_cbToWrite		= 0;
	m_state			= psNone;
	m_fPendingIO	= FALSE;
	m_pPS			= NULL;
	m_pPI			= NULL;
	m_pInBuffer		= NULL;
	m_pOutBuffer	= NULL;
}

_YPIPINST::~_YPIPINST ()
{
	Deinit ();
}


BOOL _YPIPINST::Init (YPipeServer *pPS)
{
	memset (&m_oOverlap, 0, sizeof (m_oOverlap));
	m_cbToWrite		= 0;
	m_state			= psNone;
	m_fPendingIO	= FALSE;
	m_pInBuffer		= NULL;
	m_pOutBuffer	= NULL;
	m_pPS			= pPS;
	m_pPI			= NULL;
	if ( !m_evEvent.Create (TRUE) ) {
		return FALSE;
	}
	m_oOverlap.hEvent = m_evEvent;
	return TRUE;
}

void _YPIPINST::Deinit ()
{
	Deinstantiate ();
	m_evEvent.Close ();
}

BOOL _YPIPINST::Instantiate (LPCTSTR lpName, UINT nCurInstance, UINT nMaxInstances, UINT nOutBufferSize, UINT nInBufferSize, UINT nTimeOut, LPSECURITY_ATTRIBUTES lpSA)
{
	TCHAR	szName[MAX_PATH];

	_tcscpy (szName, _T("\\\\.\\pipe\\"));
	_tcscat (szName, lpName);

	try {

		if (
			!m_np.Create (
				szName,
				PIPE_ACCESS_DUPLEX |
				FILE_FLAG_OVERLAPPED,
				PIPE_TYPE_MESSAGE |
				PIPE_READMODE_MESSAGE |
				PIPE_WAIT,
				nMaxInstances,
				nOutBufferSize,
				nInBufferSize,
				nTimeOut,
				lpSA
			)
		) {
			throw YException (::GetLastError ());
		}

		if ( !(m_pInBuffer = malloc (nInBufferSize + nOutBufferSize)) ) {
			throw YException (ERROR_NOT_ENOUGH_MEMORY);
		}
		m_pOutBuffer = &(((LPBYTE) m_pInBuffer)[nInBufferSize]);
		if ( !(m_pPI = (YPipeBaseInstance *) m_pPS->GetInstanceInfo ()->CreateObject ()) ) {
			throw YException (ERROR_NOT_ENOUGH_MEMORY);
		}

		ASSERTY_KINDOF(YPipeBaseInstance,m_pPI);

		m_pPI->m_pPipeServer = m_pPS;
		m_pPI->m_pInstDriver = this;
		if ( !m_pPI->InitInstance (nCurInstance) ) {
			throw YException (m_pPS->GetLastError ());
		}

	}
	catch ( YException e ) {
		m_pPS->SetLastError (e.GetLastError ());
		Deinstantiate ();
		return FALSE;
	}

	return TRUE;
}

void _YPIPINST::Deinstantiate ()
{
	if ( m_pPI ) {
		m_pPI->ExitInstance ();
		delete m_pPI;
		m_pPI = NULL;
	}
	if ( m_pInBuffer ) {
		free (m_pInBuffer);
	}
	m_pInBuffer		= NULL;
	m_pOutBuffer	= NULL;
	m_np.Close ();
}

void _YPIPINST::ConnectToNewClient ()
{
	SetIOPending (FALSE);
	SetState (psReading);

	// start an overlapped connection for this pipe instance
	BOOL fConnected = m_np.Connect (&m_oOverlap);
	switch ( ::GetLastError () ) {
	case ERROR_IO_PENDING:
		// overlapped connection in progress
		SetIOPending ();
		m_state = psConnecting;
		break;
	case ERROR_PIPE_CONNECTED:
		// client already connected, so signal an event
		m_evEvent.SetEvent ();
		m_pPI->OnConnect ();
		break;
	}
}

void _YPIPINST::DisconnectAndReconnect	(BOOL bSignalDisconnection)
{
	if ( bSignalDisconnection ) {
		m_pPI->OnDisconnect ();
	}
	m_np.Disconnect ();
	ConnectToNewClient ();
}

BOOL _YPIPINST::Read (BOOL &fSuccess, BOOL &fReady, DWORD &cbBytes)
{
	if ( !IsIOPending () ) {
		fSuccess = m_np.Read (m_pInBuffer, m_pPS->GetReadBufferSize (), &cbBytes, &m_oOverlap);
	}

	if ( !fSuccess || !cbBytes ) {
		if ( !fSuccess && (::GetLastError () == ERROR_IO_PENDING) ) {
			SetIOPending ();
			fReady = TRUE;
			return FALSE;
		}
		// an error occurred: disconnect from the client
		DisconnectAndReconnect (TRUE);
		fReady = TRUE;
		return FALSE;
	}

	// the read operation was successfully completed
	SetIOPending (FALSE);
	SetState (psWriting);
	SetWriteSize (0);

	m_pPI->OnTransact (m_pInBuffer, cbBytes);

	if ( GetState () == psReading ) {
		// the request has already been answered completely
		return FALSE;
	}

	if ( IsIOPending () ) {
		// the request has already been answered, but transfer is not yet completed
		fReady = TRUE;
		return FALSE;
	}
	else {
		// fallthrough and answer with an empty packet (_should_ not happen)
		SetWriteSize (0);
	}

	return TRUE;
}

void _YPIPINST::ReadAsync (BOOL &fSuccess, BOOL &fReady, DWORD &cbBytes)
{
	if ( !IsIOPending () ) {
		fSuccess = m_np.Read (m_pInBuffer, m_pPS->GetReadBufferSize (), &cbBytes, &m_oOverlap);
	}

	if ( !fSuccess ) {
		if ( !fSuccess && (::GetLastError () == ERROR_IO_PENDING) ) {
			SetIOPending ();
			fReady = TRUE;
			return;
		}
		// an error occurred: disconnect from the client
		DisconnectAndReconnect (TRUE);
		fReady = TRUE;
		return;
	}

	// the read operation was successfully completed
	SetIOPending (FALSE);

	m_pPI->OnTransact (m_pInBuffer, cbBytes);
}

void _YPIPINST::Write (BOOL &fSuccess, BOOL &fReady, DWORD &cbBytes)
{
	if ( !IsIOPending () ) {
		fSuccess = m_np.Write (m_pOutBuffer, GetWriteSize (), &cbBytes, &m_oOverlap);
	}

	if ( fSuccess && (cbBytes == GetWriteSize ()) ) {
		// write operation completed succesfully
		SetWriteSize (0);
		SetIOPending (FALSE);
		SetState (psReading);
		return;
	}
	// the write operation is still pending
	if ( !fSuccess && (::GetLastError () == ERROR_IO_PENDING) ) {
		SetIOPending (TRUE);
		fReady = TRUE;
		return;
	}
	// an error occurred: disconnect from the client
	DisconnectAndReconnect (TRUE);
	fReady = TRUE;
}

BOOL _YPIPINST::Connect (BOOL &fSuccess, BOOL &fReady)
{
	if ( IsIOPending () ) {
		if ( !fSuccess ) {
			// connection aborted... reconnect please
			DisconnectAndReconnect (FALSE);
			fReady = TRUE;
			return TRUE;
		}
		m_pPI->OnConnect ();
		SetIOPending (FALSE);
		SetState (psReading);
		return TRUE;
	}
	fReady = TRUE;
	return FALSE;
}

void _YPIPINST::Error (BOOL &fSuccess, BOOL &fReady)
{
	m_pPI->OnError ();
	DisconnectAndReconnect (FALSE);
	fReady = TRUE;
}

BOOL _YPIPINST::WriteResponse (LPCVOID lpData, UINT cbData)
{
	DWORD	cbBytes;

	if ( (GetState () != psWriting) || IsIOPending () ) {
		return FALSE;
	}
	if ( cbData > m_pPS->GetWriteBufferSize () ) {
		cbData = m_pPS->GetWriteBufferSize ();
	}
	if ( lpData ) {
		memcpy (m_pOutBuffer, lpData, cbData);
		SetWriteSize (cbData);
	}
	else {
		((LPBYTE) m_pOutBuffer)[0] = 0;
		SetWriteSize (0);
	}

	BOOL fSuccess = m_np.Write (
		m_pOutBuffer,
		GetWriteSize (),
		&cbBytes,
		&m_oOverlap
	);

	if ( fSuccess && (cbBytes == GetWriteSize ()) ) {
		// write operation completed succesfully
		SetWriteSize (0);
		SetIOPending (FALSE);
		SetState (psReading);
		return TRUE;
	}

	// the write operation is still pending
	if ( (!fSuccess) && (::GetLastError () == ERROR_IO_PENDING) ) {
		SetIOPending ();
		return TRUE;
	}

	// an error occurred: disconnect from the client
	DisconnectAndReconnect (TRUE);
	return FALSE;
}

BOOL _YPIPINST::Send (LPCVOID lpData, UINT cbData)
{
	if ( GetState () != psReading ) {
		return FALSE;
	}

	SetWriteSize ((lpData) ? (cbData) : (0));

	LPOVERLAPPED lpOv = (LPOVERLAPPED) calloc (sizeof (OVERLAPPED) + GetWriteSize (), 1);
	if ( !lpOv ) {
		return FALSE;
	}
	lpOv->hEvent = ((char *) lpOv) + sizeof (OVERLAPPED);
	memcpy (lpOv->hEvent, lpData, GetWriteSize ());

	BOOL fSuccess = m_np.WriteEx (
		(LPVOID) lpOv->hEvent,
		GetWriteSize (),
		lpOv,
		PSO_Routine
	);

	if ( fSuccess ) {
		// write operation completed succesfully
		SetWriteSize (0);
		return TRUE;
	}

	free (lpOv);
	return FALSE;
}

VOID _YPIPINST::PSO_Routine (DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped)
{
	if ( lpOverlapped ) {
		free (lpOverlapped);
	}
}


void _YPIPINST::SyncLoop ()
{
	DWORD	cbBytes;
	BOOL	fSuccess	= TRUE;
	BOOL	fReady		= FALSE;

	if ( IsIOPending () ) {
		// get the result if the operation was pending
		fSuccess = m_np.GetOverlappedResult (&m_oOverlap, &cbBytes, FALSE);
	}


	do {
		switch ( m_state ) {
		case psReading:
			//
			// READING_STATE:
			// The pipe instance is connected to the client
			// and ready to read a request from the client.
			//
			if ( !Read (fSuccess, fReady, cbBytes) ) {
				// no need to write
				break;
			}
			// intended fallthrough
		case psWriting:
			//
			// WRITING_STATE:
			// The request was successfully read from the client.
			// Get the reply data and write it to the client.
			//
			Write (fSuccess, fReady, cbBytes);
			break;
		case psConnecting:
			//
			// CONNECTING STATE
			// The pipe instance is trying to connect a client.
			//
			if ( Connect (fSuccess, fReady) ) {
				break;
			}
			// else fallthrough: CONNECTING_STATE is only allowed with PendingIO
		default:
			Error (fSuccess, fReady);
			break;
		}
	} while ( !fReady );
}

void _YPIPINST::AsyncLoop ()
{
	DWORD	cbBytes;
	BOOL	fSuccess	= TRUE;
	BOOL	fReady		= FALSE;

	if ( IsIOPending () ) {
		// get the result if the operation was pending
		fSuccess = m_np.GetOverlappedResult (&m_oOverlap, &cbBytes, FALSE);
	}


	do {
		switch ( m_state ) {
		case psReading:
			//
			// READING_STATE:
			// The pipe instance is connected to the client
			// and ready to read a request from the client.
			//
			ReadAsync (fSuccess, fReady, cbBytes);
			break;
		case psConnecting:
			//
			// CONNECTING STATE
			// The pipe instance is trying to connect a client.
			//
			if ( Connect (fSuccess, fReady) ) {
				break;
			}
			// else fallthrough: CONNECTING_STATE is only allowed with PendingIO
		default:
			Error (fSuccess, fReady);
			break;
		}
	} while ( !fReady );
}

/*=============================================================================
 * PIPE SERVER INSTANCE CLASS
 *============================================================================*/
IMPLEMENT_DYNAMIC_CREATABLE(YPipeBaseInstance,YObject);
IMPLEMENT_DYNAMIC_CREATABLE(YPipeInstance,YPipeBaseInstance);
IMPLEMENT_DYNAMIC_CREATABLE(YAsyncPipeInstance,YPipeBaseInstance);

BOOL YPipeInstance::WriteResponse (LPCVOID lpData, UINT cbData)
{
	return m_pInstDriver->WriteResponse (lpData, cbData);
}

BOOL YAsyncPipeInstance::Send (LPCVOID lpData, UINT cbData)
{
	return m_pInstDriver->Send (lpData, cbData);
}

/*=============================================================================
 * IMPLEMENTATION
 *============================================================================*/
YPipeServer::YPipeServer (
	YRuntimeInfo *			pInstance,
	LPCTSTR					pszPipeName,
	UINT					nMaxInstances,
	UINT					nMaxProxies,
	UINT					nTimer,
	UINT					nPipeTimeout,
	UINT					cbReadBuffer,
	UINT					cbWriteBuffer,
	LPSECURITY_ATTRIBUTES	lpSecurityAttributes,
	LPCTSTR					pszName
) : YWorkerThread (pszName)
{
	SetLastError (ERROR_SUCCESS);
	SetInstanceInfo (pInstance);
	SetPipeName (pszPipeName);
	SetMaxInstances (nMaxInstances);
	SetMaxProxies (nMaxProxies);
	SetTimer (nTimer);
	SetPipeTimeout (nPipeTimeout);
	SetReadBufferSize (cbReadBuffer);
	SetWriteBufferSize (cbWriteBuffer);
	SetSecurityAttributes (lpSecurityAttributes);

	m_pReserved		= NULL;
	m_pspProxy		= NULL;
	m_iCurInstances	= 0;
}

BOOL YPipeServer::TriggerProxy (UINT nProxyNumber) const
{
	if ( IsValid () && m_pspProxy && (nProxyNumber < GetMaxProxies ()) ) {
		m_pspProxy[nProxyNumber].Unlock (1);
		return TRUE;
	}
	return FALSE;
}

BOOL YPipeServer::Allocate ()
{
	try {
		if ( !m_sd.Create () ) {
			throw YException (ERROR_NOT_ENOUGH_MEMORY);
		}
		if ( !m_sd.SetDacl (TRUE, NULL, FALSE) ) {
			throw YException (::GetLastError ());
		}
		m_sa.SetSecurityDescriptor (m_sd);

		m_mgWaiter.CleanObjects ();

		// create the termination event
		if ( !m_evTerm.Create (TRUE) ) {
			throw YException (::GetLastError ());
		}

		// create the instances
		m_iCurInstances = 0;
		_YPIPINST *pInst;
		if ( !(pInst = new _YPIPINST[GetMaxInstances ()]) ) {
			throw YException (ERROR_NOT_ENOUGH_MEMORY);
		}
		m_pReserved = pInst;

		// initialize the instances
		for ( UINT nCnt = 0; nCnt < GetMaxInstances (); nCnt++ ) {
			if ( !pInst[nCnt].Init (this) ) {
				throw YException (::GetLastError ());
			}
			// preinstantiate at least 2
			if ( nCnt < 2 ) {
				if ( !pInst[nCnt].Instantiate (m_szPipeName, nCnt, m_nMaxInstances, m_cbWriteBufferSize, m_cbReadBufferSize, m_nPipeTimeout, (m_lpSecurityAttributes) ? (m_lpSecurityAttributes) : (m_sa)) ) {
					throw YException (GetLastError ());
				}
				++m_iCurInstances;
			}
			m_mgWaiter.AddObject (pInst[nCnt].GetEvent ());
		}

		if ( GetMaxProxies () ) {
			// create the proxies
			if ( !(m_pspProxy = new YSemaphore[GetMaxProxies ()]) ) {
				throw YException (ERROR_NOT_ENOUGH_MEMORY);
			}

			// prepare the proxies
			for ( UINT nCnt = 0; nCnt < GetMaxProxies (); nCnt++ ) {
				if ( !m_pspProxy[nCnt].Create (0, 0x7fffffff) ) {
					throw YException (GetLastError ());
				}
				m_mgWaiter.AddObject (m_pspProxy[nCnt]);
			}
		}

		m_mgWaiter.AddObject (m_evTerm);

	}
	catch ( YException e ) {
		SetLastError (e.GetLastError ());
		Deallocate ();
		return FALSE;
	}

	return TRUE;
}

UINT YPipeServer::SyncLoop (_YPIPINST *lpPipe)
{

	while ( TRUE ) {
		DWORD dwWait = m_mgWaiter.Wait (GetTimer ());
		if ( dwWait == WAIT_TIMEOUT ) {
			OnTimer ();
			continue;
		}
		else if ( dwWait == WAIT_FAILED ) {
			// shit! All is broken... Exit pipeserver
			return 0;
		}

		int iCurInstance = dwWait - WAIT_OBJECT_0;

		if ( (iCurInstance < 0) || (iCurInstance >= (int) (GetMaxInstances () + GetMaxProxies () + 1)) ||
			 (iCurInstance >= m_iCurInstances && iCurInstance < (int) GetMaxInstances ()) ) {
			// should never happen (index out of range)
			continue;
		}

		if ( iCurInstance == (int) (GetMaxInstances () + GetMaxProxies ()) ) {
			// termination requested from outside - return and exit thread
			SignalTermination ();
			return 0;
		}

		if ( iCurInstance >= (int) GetMaxInstances () ) {
			// proxy triggered
			OnProxy (iCurInstance - GetMaxInstances ());
			continue;
		}
			
		// increment instances in case
		if ( (iCurInstance >= (m_iCurInstances - 2)) && (m_iCurInstances < (int) GetMaxInstances ()) ) {
			// not at least 2 instances left?
			// maximum not reached?
			if ( lpPipe[m_iCurInstances].Instantiate (m_szPipeName, m_iCurInstances, m_nMaxInstances, m_cbWriteBufferSize, m_cbReadBufferSize, m_nPipeTimeout, (m_lpSecurityAttributes) ? (m_lpSecurityAttributes) : (m_sa)) ) {
				lpPipe[m_iCurInstances].ConnectToNewClient ();
				++m_iCurInstances;
			}
		}

		lpPipe[iCurInstance].SyncLoop ();
	}
	return 0;
}

UINT YPipeServer::AsyncLoop (_YPIPINST *lpPipe)
{
	while ( TRUE ) {
		DWORD dwWait = m_mgWaiter.WaitEx (GetTimer ());
		if ( dwWait == WAIT_TIMEOUT ) {
			OnTimer ();
			continue;
		}
		else if ( dwWait == WAIT_FAILED ) {
			// shit! All is broken... Exit pipeserver
			return 0;
		}
		else if ( dwWait == WAIT_IO_COMPLETION ) {
			// fine - our routine will be called to free memory
			continue;
		}

		int iCurInstance = dwWait - WAIT_OBJECT_0;

		if ( (iCurInstance < 0) || (iCurInstance >= (int) (GetMaxInstances () + GetMaxProxies () + 1)) ||
			 (iCurInstance >= m_iCurInstances && iCurInstance < (int) GetMaxInstances ()) ) {
			// should never happen (index out of range)
			continue;
		}

		if ( iCurInstance == (int) (GetMaxInstances () + GetMaxProxies ()) ) {
			// termination requested from outside - return and exit thread
			SignalTermination ();
			return 0;
		}

		if ( iCurInstance >= (int) GetMaxInstances () ) {
			// proxy triggered
			OnProxy (iCurInstance - GetMaxInstances ());
			continue;
		}
			
		// increment instances in case
		if ( (iCurInstance >= (m_iCurInstances - 2)) && (m_iCurInstances < (int) GetMaxInstances ()) ) {
			// not at least 2 instances left?
			// maximum not reached?
			if ( lpPipe[iCurInstance].Instantiate (m_szPipeName, iCurInstance, m_nMaxInstances, m_cbWriteBufferSize, m_cbReadBufferSize, m_nPipeTimeout, (m_lpSecurityAttributes) ? (m_lpSecurityAttributes) : (m_sa)) ) {
				lpPipe[m_iCurInstances].ConnectToNewClient ();
				++iCurInstance;
			}
		}

		lpPipe[iCurInstance].AsyncLoop ();
	}
	return 0;
}

void YPipeServer::Deallocate ()
{
	m_mgWaiter.CleanObjects ();

	if ( m_pspProxy ) {
		delete[] m_pspProxy;
	}
	if ( m_pReserved ) {
		delete[] ((_YPIPINST *) m_pReserved);
	}
	m_iCurInstances	= 0;
	m_pspProxy		= NULL;
	m_pReserved		= NULL;
}

void YPipeServer::SignalTermination ()
{
	_YPIPINST *lpPipe = (_YPIPINST *) m_pReserved;
	ASSERTY(lpPipe);

	for ( int i = 0; i < m_iCurInstances; i++ ) {
		if ( lpPipe[i].GetState () != psConnecting ) {
			lpPipe[i].m_pPI->OnTerminate ();
		}
	}
}

BOOL YPipeServer::PreCreateThread (BOOL &bSuspended, UINT &uStackSize, LPSECURITY_ATTRIBUTES &lpThreadAttributes)
{
	// plausibility checks
	if ( !*m_szPipeName ) {
		SetLastError (ERROR_INVALID_PARAMETER);
		return FALSE;
	}
	if ( !m_pInstanceInfo ) {
		SetLastError (ERROR_INVALID_PARAMETER);
		return FALSE;
	}

	if ( m_pInstanceInfo->IsDerivedFrom (RUNTIME_INFO(YPipeInstance)) ) {
		m_fAsyncMode = FALSE;
	}
	else if ( m_pInstanceInfo->IsDerivedFrom (RUNTIME_INFO(YAsyncPipeInstance)) ) {
		m_fAsyncMode = TRUE;
	}
	else {
		SetLastError (ERROR_INVALID_PARAMETER);
		return FALSE;
	}

	if ( (m_nMaxInstances + m_nMaxProxies + 1) > MAXIMUM_WAIT_OBJECTS ) {
		SetLastError (ERROR_INVALID_PARAMETER);
		return FALSE;
	}
	if ( m_cbReadBufferSize < 16 ) {
		SetLastError (ERROR_INVALID_PARAMETER);
		return FALSE;
	}
	if ( m_cbWriteBufferSize < 16 ) {
		SetLastError (ERROR_INVALID_PARAMETER);
		return FALSE;
	}

	Deallocate ();

	// prepare internal data
	return Allocate ();
}

UINT YPipeServer::OnRunThread ()
{
	ASSERTY(m_pReserved);

	_YPIPINST *lpPipe = (_YPIPINST *) m_pReserved;

	// initialize first instances
	for ( int i = 0; i < m_iCurInstances; i++ ) {
		lpPipe[i].ConnectToNewClient ();
	}

	// main operational loop
	if ( m_fAsyncMode ) {
		return AsyncLoop (lpPipe);
	}
	else {
		return SyncLoop (lpPipe);
	}
}

#ifndef YLB_ENABLE_INLINE
#include <yPipeServer.inl>
#endif

/// RCS STUFF ///
//LPCTSTR lpComment = _T("$Id$");

//
// EoF
////////