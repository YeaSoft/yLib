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
 * FILENAME		:	Threads.cpp
 * PURPOSE		:	yLib application sample (Worker Thread Parts)
 * SCOPE		:	yLib SDK
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

#include "StdAfc.h"
#include "Sample1.h"

/*=============================================================================
 * THREAD SAMPLE 1
 *============================================================================*/
// Thirst of all we declare our thread....
class CTestThread : public YWorkerThread
{
public:
	CTestThread					() { }

public:
	virtual BOOL				OnInitThread			(void);
	virtual UINT				OnRunThread				(void);
	virtual void				OnExitThread			(BOOL bRegularExit);
	virtual void				OnQueryThreadTermination(void);

public:
	YCriticalSection			m_csOutput;	// protects the console
	YEvent						m_evStop;	// signals the termination wish
};

BOOL CTestThread::OnInitThread ()
{
	YSingleGuard sg(&m_csOutput);

	_tprintf (_T(" CTestThread::OnInitThread: Initializing...\n"));
	if ( !m_evStop.Create () ) {
		_tprintf (_T(" CTestThread::OnInitThread: Failed to create stop event. Terminating..."));
		return FALSE;
	}
	return TRUE;
}

UINT CTestThread::OnRunThread ()
{
	DWORD	dwCount = 0;
	while ( m_evStop.Wait (1000) == WAIT_TIMEOUT ) {
		YSingleGuard sg(&m_csOutput);
		_tprintf (_T("  CTestThread::OnRunThread: Beep %02.02i from worker thread\n"), dwCount++);
		MessageBeep (0);
	}
	// when the event is signalled, Wait() returns with WAIT_OBJECT_0
	return 0;
}

void CTestThread::OnQueryThreadTermination ()
{
	YSingleGuard sg(&m_csOutput);
	_tprintf (_T("CTestThread::OnQueryThreadTermination: main thread requests termination\n"));
	// we signal the event
	m_evStop.SetEvent ();
}

void CTestThread::OnExitThread (BOOL bRegularExit)
{
	YSingleGuard sg(&m_csOutput);

	if ( bRegularExit ) {
		_tprintf (_T(" CTestThread::OnExitThread: Graceful termination\n"));
	}
	else {
		_tprintf (_T("CTestThread::OnExitThread: Hard termination\n"));
	}
	m_evStop.Close ();
}

void Sample1::RunThread1 ()
{
	_tprintf (_T("This example shows a thread with graceful termination strategy:\n"));
	_tprintf (_T("\n"));

	CTestThread tt;

	_tprintf (_T("Creating suspended test thread...\n"));
	if ( !tt.Create (TRUE) ) {
		_tprintf (_T("Failed creating thread\n"));
		return;
	}
	_tprintf (_T("After resuming the thread we will wait 10 seconds...\n"));
	tt.Resume ();

	Sleep (10000);

	tt.Terminate (2000, 0);

	_tprintf (_T("Thread terminated.\n"));
}

/*=============================================================================
 * THREAD SAMPLE 2
 *============================================================================*/
class CCounterThread : public YWorkerThread
{
public:
	CCounterThread				() { m_bSync = FALSE; }

public:
	virtual BOOL				OnInitThread			(void) { return TRUE; }
	virtual UINT				OnRunThread				(void);

public:
	static BOOL					m_bSync;
	static int					m_iCounter;	// one for all
	static YCriticalSection		m_cs;		// one for all
};

BOOL				CCounterThread::m_bSync;
int					CCounterThread::m_iCounter;
YCriticalSection	CCounterThread::m_cs;

UINT CCounterThread::OnRunThread ()
{
	for ( int i = 0; i < 10; i++ ) {
		if ( m_bSync ) {
			// Synchronized
			m_cs.Enter ();
			int iMyVar = m_iCounter;
			++iMyVar;
			Sleep ((10 * rand ()) / RAND_MAX);
			m_iCounter = iMyVar;
			m_cs.Leave ();
			Sleep ((30 * rand ()) / RAND_MAX);
		}
		else {
			int iMyVar = m_iCounter;
			++iMyVar;
			Sleep ((10 * rand ()) / RAND_MAX);
			m_iCounter = iMyVar;
			Sleep ((30 * rand ()) / RAND_MAX);
		}
	}
	return 0;
}


void Sample1::RunThread2 ()
{
	_tprintf (_T("This example shows how simple synchronisation works across different threads:\n"));
	_tprintf (_T("\n"));

	CCounterThread	tr[3];
	YSyncHandle *	sh[] = { &(tr[0]), &(tr[1]), &(tr[2]) };

	_tprintf (_T("Unsynchronized example:\n"));
	CCounterThread::m_iCounter	= 0;
	CCounterThread::m_bSync		= FALSE;
	tr[0].Create ();
	tr[1].Create ();
	tr[2].Create ();
	YMultiGuard		mg1(sh, 3);
	mg1.Wait (INFINITE);
	_tprintf (_T("The result is %i\n"), CCounterThread::m_iCounter);

	_tprintf (_T("Synchronized example:\n"));
	CCounterThread::m_iCounter	= 0;
	CCounterThread::m_bSync		= TRUE;
	tr[0].Create ();
	tr[1].Create ();
	tr[2].Create ();
	YMultiGuard		mg2(sh, 3);
	mg2.Wait (INFINITE);
	_tprintf (_T("The result is %i\n"), CCounterThread::m_iCounter);
}

