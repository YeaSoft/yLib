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
 * FILENAME		:	yArgParser.h
 * PURPOSE		:	Argument Parser Classes
 * SCOPE		:	yLib - The Y Application Framework Class Library
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.3  2004/08/02 10:03:49  leopoldo
 * Adjusted GetValueByNameOrPos
 *
 * Revision 1.2  2004/08/02 09:47:54  leopoldo
 * Added new methods
 *
 * Revision 1.1  2004/08/01 21:48:52  leopoldo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yArgParser.h
 *============================================================================*/
#ifndef __yArgParser_h__
#define __yArgParser_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yLibBase_h__
#include <yLibBase.h>
#endif

/*=============================================================================
 * FORWARD CLASS DECLARATIONS
 *============================================================================*/
class YArgPairParser;
	class YArgPair;
	

/*=============================================================================
 * CLASS DECLARATIONS
 *============================================================================*/
class YArgPair
{
public:
	YArgPair					(LPCTSTR pszName = NULL, LPCTSTR pszValue = NULL) : m_pszName(pszName), m_pszValue(pszValue) { }
	
public:
	LPCTSTR						GetName					() const { return m_pszName; }
	LPCTSTR						GetValue				() const { return m_pszValue; }
	bool						IsCommand				() const { return m_pszName && !m_pszValue; }
	bool						IsCommand				(LPCTSTR pszTest, bool bCaseSensitive = false) const;
	bool						IsNamedValue			() const { return m_pszName && m_pszValue; }
	bool						IsNamedValue			(LPCTSTR pszTest, bool bCaseSensitive = false) const;
	bool						HasNamedValue			() const { return m_pszName && m_pszValue && *m_pszName && *m_pszValue; }
	bool						HasNamedValue			(LPCTSTR pszTest, bool bCaseSensitive = false) const;

private:
	LPCTSTR						m_pszName;
	LPCTSTR						m_pszValue;
	
	friend						YArgPairParser;
};

class YArgPairParser
{
public:
	YArgPairParser				() { m_argc = 0; m_argv = NULL; }
	~YArgPairParser				();
	
public:
	bool						Create					(LPCTSTR pszCmdLine);
	bool						Create					(int argc, TCHAR **argv);
	bool						Create					(YCommandLineInfo &cli);

public:
	// attributes
	const YArgPair *			operator[]				(int nIndex) const { return GetAt (nIndex); }

public:
	// attributes
	const YArgPair *			GetAt					(int nIndex) const { return ((nIndex >= 0) && (nIndex < m_argc)) ? (&m_argv[nIndex]) : (NULL); }
	int							GetCount				() const { return m_argc; }

	LPCTSTR						GetCommandAt			(int nIndex) const { return ((nIndex >= 0) && (nIndex < m_cmdc)) ? (m_cmdv[nIndex]) : (NULL); }
	int							GetCommandCount			() const { return m_cmdc; }

	const YArgPair *			GetNamedValueAt			(int nIndex) const { return ((nIndex >= 0) && (nIndex < m_valc)) ? (&m_valv[nIndex]) : (NULL); }
	int							GetNamedValueCount		() const { return m_valc; }

	ITERATOR					GetHeadPosition			() const { return (m_argc) ? ((ITERATOR) &(m_argv[0])) : (NULL); }
	ITERATOR					GetTailPosition			() const { return (m_argc) ? ((ITERATOR) &(m_argv[m_argc - 1])) : (NULL); }
	const YArgPair *			GetNext					(ITERATOR &pos) const;
	const YArgPair *			GetPrev					(ITERATOR &pos) const;
	const YArgPair *			GetAt					(ITERATOR pos) const;
	const YArgPair *			Skip					(ITERATOR &pos, int nSkip = 1) const;
	
public:
	// operations
	int							FindCommand				(LPCTSTR pszParam, bool bCaseSensitive = false) const;
	const YArgPair *			FindCommandPtr			(LPCTSTR pszParam, bool bCaseSensitive = false) const;
	int							FindNamedValue			(LPCTSTR pszParam, bool bCaseSensitive = false) const;
	const YArgPair *			FindNamedValuePtr		(LPCTSTR pszParam, bool bCaseSensitive = false) const;
	LPCTSTR						GetValueByName			(LPCTSTR pszParam, bool bCaseSensitive = false) const;
	LPCTSTR						GetValueByNameOrPos		(LPCTSTR pszParam, int nIndex, bool bCaseSensitive = false) const;
	bool						RemoveAt				(int nIndex);
	bool						RemoveAt				(ITERATOR &pos);
	bool						Remove					(LPCTSTR pszParam, bool bCaseSensitive = false);

protected:
	static void					ParseCmdLine			(LPCTSTR pszCmdLine, YArgPair *argp, LPTSTR *cmdp, YArgPair *valp, LPTSTR pszArgs, int &iNumArgs, int &iNumCmds, int &iNumVals, int &iNumChars);
	static void					ParseCmdLine			(int argc, TCHAR **argv, YArgPair *argp, LPTSTR *cmdp, YArgPair *valp, LPTSTR pszArgs, int &iNumArgs, int &iNumCmds, int &iNumVals, int &iNumChars);

private:
	int							m_argc;
	int							m_cmdc;
	int							m_valc;
	YArgPair					*m_argv;
	LPTSTR						*m_cmdv;
	YArgPair					*m_valv;
};

#ifdef YLB_ENABLE_INLINE
#include <yArgParser.inl>
#endif

#endif //__yArgParser_h__
//
// EoF
////////