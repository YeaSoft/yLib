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
 * FILENAME		:	Beeper.cpp
 * PURPOSE		:	The Beeper Thread
 * SCOPE		:	yLib SDK
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.2  2001/05/16 17:16:42  leopoldo
 * Added some printf message to demonstrate console reattachment
 *
 * Revision 1.1  2000/05/26 14:07:38  leo
 * Initial revision
 *
 *============================================================================*/

#include "StdAfc.h"
#include "Beeper.h"

BOOL CBeeper::PreCreateThread (BOOL &bSuspended, UINT &uStackSize, LPSECURITY_ATTRIBUTES &lpThreadAttributes)
{
	m_bSuspended = FALSE;

	// create the termination event
	return m_evStop.Create ();
}

UINT CBeeper::OnRunThread ()
{
	// you will see this because of sonsole to RTL
	// reattachment in YConsole::Attach
	printf ("Hello World!\n");

	while ( m_evStop.Wait (1000) != WAIT_OBJECT_0 ) {
		if ( !m_bSuspended ) {
			MessageBeep (0);
			printf ("Beep!\n");
		}
	}
	return 0;
}

void CBeeper::OnQueryThreadTermination ()
{
	m_evStop.SetEvent ();
}
