/*=============================================================================
 * This is a part of the yLib Software Development Kit.
 * Copyright (C) 1998-1999 YEAsoft Inc.
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
 * FILENAME		:	docFile.h
 * PURPOSE		:	Pseudo include for inline documentation
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yLib.h
 *============================================================================*/

// @topic Global Library Functions |
//
//	This is the list of the global functions provided by yLib:
//
//	<f YlbIsValidString>: Tests a string for validity
//
//	<f YlbIsValidAddress>: Tests a memory block for validity
//
//	<f YlbAssertFailedLine>: Internal assertion function
//
//	<f YlbLoadString>: Loads a resource string from the current process module
//
//	<f YlbGetResourceHandle>: Returns the current process resource handle



// @topic Tools Pseudoclasses |
//
//	The tools pseudoclasses are not real C++ classes but are simple
//	collections of useful utility functions. They are organized as static
//	functions in classes to permit other classes to inherit their
//	functionality.
//	<nl>Simply derive your class also from one or more tools pseudoclasses
//	to inherit their functionality.
//	<nl>The following pseudoclasses are available:
//
//	<c YFileNameHandler>: Tools for filename handling
//
//	<c YFileManager>: Tools for filesystem related file handling
//
//

// @topic File Related Classes |
//
// The following classes are intended for better and confortable
// file and directory handling:
//
// <c YCrc32>: The CRC Calculation Class
//
// <c YVersInfo>: The version information handler class


// @topic Needful Things |
//
// The following classes provide a set of needful code for various
// jobs:
//
// <c YCrc32>: The CRC Calculation Class
//
// <c YFlags>: Flag storage class
//
// <c YTokenizer>: Token splitter class

// @topic System Services |
//
// The following classes provide access to several WIN32 system APIs:
//
// <c YRegistry>: Registry access class

