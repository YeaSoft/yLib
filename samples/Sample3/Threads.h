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
 * FILENAME		:	Threads.h
 * PURPOSE		:	The Service Threads
 * SCOPE		:	yLib SDK
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * THE CAPTURE THREAD
 *============================================================================*/
class CEarner : public YWorkerThread
{
public:
	// construction
	CEarner						() : YWorkerThread (_T("Earner")) { }

public:
	// attributes
	void						Pause					() { m_bSuspended = TRUE; }
	void						Continue				() { m_bSuspended = FALSE; }
	void						SetName					(LPCTSTR pszName) { m_pszName = pszName; }
	void						SetAccount				(UINT nAccount) { m_nAccount = nAccount; }

protected:
	// overridables
	virtual BOOL				PreCreateThread			(BOOL &bSuspended, UINT &uStackSize, LPSECURITY_ATTRIBUTES &lpThreadAttributes);
	virtual UINT				OnRunThread				(void);
	virtual void				OnQueryThreadTermination(void);

private:
	YEvent						m_evStop;
	BOOL						m_bSuspended;
	LPCTSTR						m_pszName;
	UINT						m_nAccount;
};

class CReporter : public YWorkerThread
{
public:
	// construction
	CReporter					() : YWorkerThread (_T("Reporter")) { }

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