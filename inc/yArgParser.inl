/*=============================================================================
 * This is a part of the yLib Software Development Kit.
 * Copyright (C) 1998-2004 YEAsoft Int'l.
 * All rights reserved.
 *=============================================================================
 * Copyright (c) 1998-2004 YEAsoft Int'l (Leo Moll, Andrea Pennelli).
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
 * FILENAME		:	yArgParser.inl
 * PURPOSE		:	Argument Parser Classes
 * SCOPE		:	yLib - The Y Application Framework Class Library
 * HISTORY		: =============================================================
 * 
 * $Log$
 *============================================================================*/
YLB_INLINE YArgPairParser::~YArgPairParser ()
{
	if ( m_argv ) {
		free (m_argv);
	}
}

YLB_INLINE bool YArgPairParser::Create (YCommandLineInfo &cli)
{
	return Create (cli.m_argc, cli.m_argv);
}

//
// EoF
////////