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
 * FILENAME		:	Sample5.h
 * PURPOSE		:	yLib file splitter
 * SCOPE		:	yLib SDK
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#include "SampleRes5.h"

/*==================================================================================*
 * OUR SAMPLE APPLICATION
 *==================================================================================*/
class FileSplitter : public YConApp
{
public:
	FileSplitter				() : YConApp (IDS_APP_TITLE) { }

public:
	virtual BOOL				InitInstance			(YCommandLineInfo *cli);

protected:
	void						ShowError				(LPCTSTR pszFormat, ...);
	void						ShowUsage				();
};
