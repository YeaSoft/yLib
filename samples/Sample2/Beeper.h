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
 * FILENAME		:	Beeper.h
 * PURPOSE		:	The Beeper Thread
 * SCOPE		:	yLib SDK
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * THE BEEPER THREAD
 *============================================================================*/
class CBeeper : public YWorkerThread
{
public:
	// construction
	CBeeper						() : YWorkerThread (_T("Beeper")) { }

public:
	// attributes
	void						Pause					() { m_bSuspended = TRUE; }
	void						Continue				() { m_bSuspended = FALSE; }

protected:
	// overridables
	virtual BOOL				PreCreateThread			(BOOL &bSuspended, UINT &uStackSize, LPSECURITY_ATTRIBUTES &lpThreadAttributes);
	virtual UINT				OnRunThread				(void);
	virtual void				OnQueryThreadTermination(void);

private:
	YEvent						m_evStop;
	BOOL						m_bSuspended;
};

//
// EoF
////////