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
 * FILENAME		:	docFile.h
 * PURPOSE		:	Pseudo include for inline documentation
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26 14:04:42  leo
 * Initial revision
 *
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

