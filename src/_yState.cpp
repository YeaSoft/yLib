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
 * FILENAME		:	_yState.cpp
 * PURPOSE		:	Internal process state
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

#include "StdInc.hpp"

#ifdef _DEBUG
#undef HERE
static char HERE[] = __FILE__;
#endif //_DEBUG

/*=============================================================================
 * CONFIGURATION
 *============================================================================*/
#pragma warning(disable:4074)
#pragma init_seg(compiler)

/*=============================================================================
 * LIBRARY GLOBAL VARIABLES
 *============================================================================*/
PROC_ENV						_proc;

/*=============================================================================
 * IMPLEMENTATION
 *============================================================================*/
PROC_ENV::PROC_ENV()
{
	m_pApp				= NULL;
	m_hInstance			= (HINSTANCE) GetModuleHandle (NULL);
	m_hResHandle		= (HINSTANCE) GetModuleHandle (NULL);
	m_hProcessHandle	= NULL;
	m_hThreadHandle		= NULL;
	DuplicateHandle (
		::GetCurrentProcess (),
		::GetCurrentThread (),
		::GetCurrentProcess (),
		&m_hProcessHandle,
		0,
		TRUE,
		DUPLICATE_SAME_ACCESS
	);
	DuplicateHandle (
		::GetCurrentProcess (),
		::GetCurrentThread (),
		::GetCurrentProcess (),
		&m_hThreadHandle,
		0,
		TRUE,
		DUPLICATE_SAME_ACCESS
	);
}

PROC_ENV::~PROC_ENV()
{
	CloseHandle (m_hProcessHandle);
	CloseHandle (m_hThreadHandle);
}

//
// EoF
////////