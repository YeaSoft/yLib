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
 * PURPOSE		:	The Service Threads
 * SCOPE		:	yLib SDK
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

#include "StdAfc.h"
#include "Sample3.h"

/*=============================================================================
 * THE PROTECTION
 *============================================================================*/
YCriticalSection	csAccounts[2];
DWORD				dwAccount[2];

/*=============================================================================
 * THE EARNER THREAD
 *============================================================================*/
BOOL CEarner::PreCreateThread (BOOL &bSuspended, UINT &uStackSize, LPSECURITY_ATTRIBUTES &lpThreadAttributes)
{
	m_bSuspended = FALSE;

	srand (GetTickCount ());

	// create the termination event
	return m_evStop.Create ();
}

UINT CEarner::OnRunThread ()
{
	while ( m_evStop.Wait ((rand () * 3000) / RAND_MAX) != WAIT_OBJECT_0 ) {
		if ( !m_bSuspended ) {
			DWORD dwEarn = (rand () * 100) / RAND_MAX;
			theSvc.m_con.Write (_T("%s: Hurray! I've earned $ %d!\n"), m_pszName, dwEarn);
			csAccounts[m_nAccount].Enter ();
			dwAccount[m_nAccount] += dwEarn;
			csAccounts[m_nAccount].Leave ();
		}
	}
	return 0;
}

void CEarner::OnQueryThreadTermination ()
{
	m_evStop.SetEvent ();
}

/*=============================================================================
 * THE REPORTER THREAD
 *============================================================================*/
BOOL CReporter::PreCreateThread (BOOL &bSuspended, UINT &uStackSize, LPSECURITY_ATTRIBUTES &lpThreadAttributes)
{
	m_bSuspended = FALSE;

	srand (GetTickCount ());

	// create the termination event
	return m_evStop.Create ();
}

UINT CReporter::OnRunThread ()
{
	while ( m_evStop.Wait ((rand () * 10000) / RAND_MAX) != WAIT_OBJECT_0 ) {
		if ( !m_bSuspended ) {
			csAccounts[0].Enter ();
			theSvc.m_con.Write (_T("Reporter: The first account has the follwing balance: $ %d\n"), dwAccount[0]);
			csAccounts[0].Leave ();
			csAccounts[1].Enter ();
			theSvc.m_con.Write (_T("Reporter: The second account has the follwing balance: $ %d\n"), dwAccount[1]);
			csAccounts[1].Leave ();
		}
	}
	return 0;
}

void CReporter::OnQueryThreadTermination ()
{
	m_evStop.SetEvent ();
}
