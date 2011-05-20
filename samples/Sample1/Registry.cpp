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
 * FILENAME		:	Registry.cpp
 * PURPOSE		:	yLib application sample (Registry Sample)
 * SCOPE		:	yLib SDK
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:07:25  leo
 * Initial revision
 *
 *============================================================================*/

#include "StdAfc.h"
#include "Sample1.h"

/*=============================================================================
 * IMPLEMENTATION
 *============================================================================*/
void Sample1::SvcEnumReg ()
{
	_tprintf (_T("This example shows the enumeration of services by\n"));
	_tprintf (_T("using registry functions:"));
	_tprintf (_T("\n"));

	YRegistry reg;
	if ( reg.Open (_T("SYSTEM\\CurrentControlSet\\Services")) ) {
		for ( ITERATOR pos = reg.GetFirstSectionPosition (); pos; /*TUNIX*/ ) {
			LPCTSTR lpStr = reg.GetNextSection (pos);
			if ( lpStr ) {
				_tprintf (_T("Service: %s\n"), lpStr);
				YRegistry regSvc(reg.GetHandle ());
				if ( regSvc.Open (lpStr) ) {
					// this strange mode to read the display name key is intended
					// only for demonstration purposes...
					ITERATOR pos;
					for ( pos = regSvc.GetFirstValuePosition (); pos; /*TUNIX*/ ) {
						TCHAR	szVal[128];
						DWORD	dwVal = sizeof(szVal); // This is correct also for UNICODE!
						DWORD	dwType;
						LPCTSTR lpValName = regSvc.GetNextValue (
							pos,
							NULL,
							0,
							&dwType,
							(LPBYTE) szVal,
							&dwVal
						);
						if ( lpValName && (dwType == REG_SZ) && !_tcsicmp (lpValName, _T("DisplayName")) ) {
							_tprintf (_T("     %s\n"), szVal);
							break;
						}
					}
					if ( !pos ) {
						// "DisplayName" not found
						_tprintf (_T("     <no display name>\n"));
					}
				}
			}
		}
	}
}

