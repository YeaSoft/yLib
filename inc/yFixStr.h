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
 * FILENAME		:	yFixStr.h
 * PURPOSE		:	Declaration of the fixed length string classes
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.10  2000/10/05 17:20:45  leopoldo
 * Added YFixedString::MakeCapital
 *
 * Revision 1.9  2000/08/28 13:04:43  leo
 * Added missing assignment operator on
 * predefined string types for self assignment
 *
 * Revision 1.8  2000/08/23 10:12:45  leo
 * Fixed some release build issue
 *
 * Revision 1.7  2000/08/22  16:18:59  leo
 * Added some of the directory operations to YPathString
 *
 * Revision 1.6  2000/08/22  16:01:50  leo
 * Added the transfer methods
 *
 * Revision 1.5  2000/08/22  15:41:11  leo
 * Added more oethods for path strings
 * Updated license
 *
 * Revision 1.4  2000/07/25  09:06:12  leo
 * Added pointer based find methods
 *
 * Revision 1.3  2000/07/05  13:46:46  leo
 * Added the YUserName class
 *
 * Revision 1.2  2000/07/05  13:26:39  leo
 * Added the "TerminateAfter" methods
 *
 * Revision 1.1  2000/05/26  14:03:08  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yFixStr.h
 *============================================================================*/
#ifndef __yFixStr_h__
#define __yFixStr_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yUNC_h__
#include <yUNC.h>
#endif
#ifndef __yFileTools_h__
#include <yFileTools.h>
#endif

/*=============================================================================
 * FORWARD CLASS DECLARATIONS
 *============================================================================*/
class YStringData;
	class YFixedString;
		// fixed length strings with different lengths
		class YString32;
		class YString64;
		class YString128;
		class YString256;
		class YString512;
		class YString1024;
		class YBigString;
		// dynamically allocated string with fixed length
		class YHeapString;
		// system related strings with related methods
		class YPathString;
		class YComputerName;
		class YUserName;
	class YMultiString;

/*=============================================================================
 * STRING DATA BASE CLASS DECLARATION
 *============================================================================*/
class YStringData
{
private:
	// kill these construction methods & operators
	YStringData					(const YStringData& stringSrc);

public:
	// construction
	YStringData					(LPTSTR pszStorage, UINT cbSize);

public:
	// attributes
	UINT						GetSize					() const;
	UINT						GetBufferSize			() const;
	LPTSTR						GetBuffer				() const;
	LPCTSTR						GetNullForEmptyString	() const;
	operator					LPCTSTR					() const;

private:
	// implementation
	LPTSTR						m_pszString;
	UINT						m_cbSize;

	friend class				YFixedString;
	friend class				YHeapString;
	friend class				YPathString;
	friend class				YMultiString;
};

/*=============================================================================
 * FIXED STRING BASE CLASS DECLARATION
 *============================================================================*/
class YFixedString : public YStringData
{
private:
	// kill these construction methods & operators
	YFixedString				(const YFixedString& stringSrc);

public:
	// construction
	YFixedString				(LPTSTR pszStorage, UINT cbSize, BOOL bEmpty = TRUE);

public:
	// attributes and operations
	UINT						GetLength				() const;
	BOOL						IsEmpty					() const;
	void						Empty					();
	TCHAR						GetAt					(UINT nIndex) const;
	TCHAR						operator[]				(UINT nIndex) const;
	void						SetAt					(UINT nIndex, TCHAR ch);

	// transfer
	void						Copy					(LPTSTR pszDest, UINT cbSize);
#ifdef _UNICODE
	void						Copy					(LPSTR pszDest, UINT cbSize);
#else
	void						Copy					(LPWSTR pszDest, UINT cbSize);
#endif

	// assignment
	void						Assign					(const YStringData& stringSrc);
	void						Assign					(TCHAR ch);
	void						Assign					(LPCSTR lpsz);
	void						Assign					(LPCWSTR lpsz);
	void						Assign					(const unsigned char* psz);
#ifdef _UNICODE
	void						Assign					(char ch);
#endif
	void						Assign					(INT iValue);
	void						Assign					(UINT uValue);
	void						Assign					(LONG lValue);
	void						Assign					(DWORD dwValue);

	// overloaded assignment
	const YFixedString &		operator=				(const YStringData& stringSrc);
	const YFixedString &		operator=				(TCHAR ch);
	const YFixedString &		operator=				(LPCSTR lpsz);
	const YFixedString &		operator=				(LPCWSTR lpsz);
	const YFixedString &		operator=				(const unsigned char* psz);
#ifdef _UNICODE
	const YFixedString &		operator=				(char ch);
#endif

	// concatenation
	void						Concat					(const YStringData& stringSrc);
	void						Concat					(TCHAR ch);
	void						Concat					(LPCSTR lpsz);
	void						Concat					(LPCWSTR lpsz);
	void						Concat					(const unsigned char* psz);
#ifdef _UNICODE
	void						Concat					(char ch);
#endif

	// overloaded concatenation
	const YFixedString &		operator+=				(const YStringData& stringSrc);
	const YFixedString &		operator+=				(TCHAR ch);
	const YFixedString &		operator+=				(LPCSTR lpsz);
	const YFixedString &		operator+=				(LPCWSTR lpsz);
	const YFixedString &		operator+=				(const unsigned char* psz);
#ifdef _UNICODE
	const YFixedString &		operator+=				(char ch);
#endif

	friend YBigString YLBAPI	operator+				(const YStringData& string1, const YStringData& string2);
	friend YBigString YLBAPI	operator+				(const YStringData& string, LPCTSTR lpsz);
	friend YBigString YLBAPI	operator+				(LPCTSTR lpsz, const YStringData& string);
	friend YBigString YLBAPI	operator+				(const YStringData& string, TCHAR ch);
	friend YBigString YLBAPI	operator+				(TCHAR ch, const YStringData& string);
#ifdef _UNICODE
	friend YBigString YLBAPI	operator+				(const YStringData& string, char ch);
	friend YBigString YLBAPI	operator+				(char ch, const YStringData& string);
#endif
	
	// string comparison
	int							Compare					(LPCTSTR lpsz) const;
	int							CompareNoCase			(LPCTSTR lpsz) const;
	int							Collate					(LPCTSTR lpsz) const;
	int							CollateNoCase			(LPCTSTR lpsz) const;

	// simple sub-string extraction
	YBigString					Mid						(int nFirst, int nCount) const;
	YBigString					Mid						(int nFirst) const;
	YBigString					Left					(int nCount) const;
	YBigString					Right					(int nCount) const;
	YBigString					SpanIncluding			(LPCTSTR lpszCharSet) const;
	YBigString					SpanExcluding			(LPCTSTR lpszCharSet) const;

	// upper/lower/reverse conversion
	void						MakeUpper				();
	void						MakeLower				();
	void						MakeCapital				();
	void						MakeCapital				(TCHAR chWhiteSpace);
	void						MakeCapital				(LPCTSTR lpszWhiteSpaces);
	void						MakeReverse				();

	// trimming whitespace (either side)
	void						Trim					();
	void						TrimRight				();
	void						TrimLeft				();

	// trimming anything (either side)
	void						Trim					(TCHAR chTarget);
	void						Trim					(LPCTSTR lpszTargets);
	void						TrimRight				(TCHAR chTarget);
	void						TrimRight				(LPCTSTR lpszTargets);
	void						TrimLeft				(TCHAR chTarget);
	void						TrimLeft				(LPCTSTR lpszTargets);

	// shortening
	void						Terminate				(TCHAR cTermChar);
	void						ReverseTerminate		(TCHAR cTermChar);
	void						Terminate				(LPCTSTR lpszTermCharSet);
	void						ReverseTerminate		(LPCTSTR lpszTermCharSet);
	void						TerminateAfter			(TCHAR cTermChar);
	void						ReverseTerminateAfter	(TCHAR cTermChar);
	void						TerminateAfter			(LPCTSTR lpszTermCharSet);
	void						ReverseTerminateAfter	(LPCTSTR lpszTermCharSet);

	// advanced manipulation
	int							Replace					(TCHAR chOld, TCHAR chNew);
	int							Replace					(LPCTSTR lpszOld, LPCTSTR lpszNew);
	int							Remove					(TCHAR chRemove);
	int							Insert					(int nIndex, TCHAR ch);
	int							Insert					(int nIndex, LPCTSTR pstr);
	int							Delete					(int nIndex, int nCount = 1);

	// searching
	int							Find					(TCHAR ch) const;
	int							ReverseFind				(TCHAR ch) const;
	int							Find					(TCHAR ch, int nStart) const;
	int							FindOneOf				(LPCTSTR lpszCharSet) const;
	int							Find					(LPCTSTR lpszSub) const;
	int							Find					(LPCTSTR lpszSub, int nStart) const;
	LPCTSTR						FindPtr					(TCHAR ch) const;
	LPCTSTR						ReverseFindPtr			(TCHAR ch) const;
	LPCTSTR						FindPtr					(TCHAR ch, int nStart) const;
	LPCTSTR						FindOneOfPtr			(LPCTSTR lpszCharSet) const;
	LPCTSTR						FindPtr					(LPCTSTR lpszSub) const;
	LPCTSTR						FindPtr					(LPCTSTR lpszSub, int nStart) const;

	// simple formatting
	void YLB_CDECL				Format					(LPCTSTR lpszFormat, ...);
	void YLB_CDECL				Format					(UINT nFormatID, ...);
	void						FormatV					(LPCTSTR lpszFormat, va_list argList);
	void YLB_CDECL				FormatMessage			(LPCTSTR lpszFormat, ...);
	void YLB_CDECL				FormatMessage			(UINT nFormatID, ...);

	BOOL						LoadString				(UINT nID);

	// ANSI <-> OEM support (convert string in place)
#ifndef _UNICODE
	void						AnsiToOem				();
	void						OemToAnsi				();
#endif

protected:
	// implementation
	void						Assign					(LPCTSTR lpsz, UINT nCount);

protected:
	// implementation
	static UINT					SafeStrLen				(LPCTSTR lpsz);
};

/*=============================================================================
 * COMPARE HELPERS
 *============================================================================*/
bool YLBAPI						operator==				(const YFixedString& s1, const YFixedString& s2);
bool YLBAPI						operator==				(const YFixedString& s1, LPCTSTR s2);
bool YLBAPI						operator==				(LPCTSTR s1, const YFixedString& s2);
bool YLBAPI						operator!=				(const YFixedString& s1, const YFixedString& s2);
bool YLBAPI						operator!=				(const YFixedString& s1, LPCTSTR s2);
bool YLBAPI						operator!=				(LPCTSTR s1, const YFixedString& s2);
bool YLBAPI						operator<				(const YFixedString& s1, const YFixedString& s2);
bool YLBAPI						operator<				(const YFixedString& s1, LPCTSTR s2);
bool YLBAPI						operator<				(LPCTSTR s1, const YFixedString& s2);
bool YLBAPI						operator>				(const YFixedString& s1, const YFixedString& s2);
bool YLBAPI						operator>				(const YFixedString& s1, LPCTSTR s2);
bool YLBAPI						operator>				(LPCTSTR s1, const YFixedString& s2);
bool YLBAPI						operator<=				(const YFixedString& s1, const YFixedString& s2);
bool YLBAPI						operator<=				(const YFixedString& s1, LPCTSTR s2);
bool YLBAPI						operator<=				(LPCTSTR s1, const YFixedString& s2);
bool YLBAPI						operator>=				(const YFixedString& s1, const YFixedString& s2);
bool YLBAPI						operator>=				(const YFixedString& s1, LPCTSTR s2);
bool YLBAPI						operator>=				(LPCTSTR s1, const YFixedString& s2);

/*=============================================================================
 * FIXED STRING TEMPLATE
 *============================================================================*/
template<unsigned int SIZE>
class YFixedStringClass : public YFixedString
{
public:
	// construction
	YFixedStringClass			(BOOL bEmpty = TRUE) : YFixedString (m_szData, SIZE, bEmpty) { }
	YFixedStringClass			(const YStringData& stringSrc) : YFixedString (m_szData, SIZE, FALSE) { Assign (stringSrc); }
	YFixedStringClass			(LPCTSTR lpsz) : YFixedString (m_szData, SIZE, FALSE) { Assign (lpsz); }
	
	// overloaded assignment
	const YFixedStringClass &	operator=				(const YFixedStringClass& stringSrc) { Assign (stringSrc); return *this; }
	const YFixedStringClass &	operator=				(const YStringData& stringSrc) { Assign (stringSrc); return *this; }
	const YFixedStringClass &	operator=				(TCHAR ch) { Assign (ch); return *this; }
	const YFixedStringClass &	operator=				(LPCSTR lpsz) { Assign (lpsz); return *this; }
	const YFixedStringClass &	operator=				(LPCWSTR lpsz) { Assign (lpsz); return *this; }
	const YFixedStringClass &	operator=				(const unsigned char* psz) { Assign (psz); return *this; }
#ifdef _UNICODE
	const YFixedStringClass &	operator=				(char ch) { Assign (ch); return *this; }
#endif

	// overloaded concatenation
	const YFixedStringClass &	operator+=				(const YStringData& stringSrc) { Concat (stringSrc); return *this; };
	const YFixedStringClass &	operator+=				(TCHAR ch) { Concat (ch); return *this; };
	const YFixedStringClass &	operator+=				(LPCSTR lpsz) { Concat (lpsz); return *this; };
	const YFixedStringClass &	operator+=				(LPCWSTR lpsz) { Concat (lpsz); return *this; };
	const YFixedStringClass &	operator+=				(const unsigned char* psz) { Concat (psz); return *this; };
#ifdef _UNICODE
	const YFixedStringClass &	operator+=				(char ch) { Concat (ch); return *this; };
#endif

private:
	// implementation
	TCHAR						m_szData[SIZE];
};

#ifdef WITH_TEMPLATES

/*=============================================================================
 * PREDEFINED FIXED STRINGS (DISABLED SINCE NOT TESTED
 *============================================================================*/
typedef YFixedStringClass<16>							YString16;
typedef YFixedStringClass<32>							YString32;
typedef YFixedStringClass<64>							YString64;
typedef YFixedStringClass<128>							YString128;
typedef YFixedStringClass<256>							YString256;
typedef YFixedStringClass<512>							YString512;
typedef YFixedStringClass<1024>							YString1024;
typedef YFixedStringClass<YLB_BIGSTRING_SIZE>			YBigString;

#else 

/*=============================================================================
 * PREDEFINED FIXED STRINGS
 *============================================================================*/
class YString16 : public YFixedString
{
public:
	// construction
	YString16					(BOOL bEmpty = TRUE) : YFixedString (m_szData, 16, bEmpty) { }
	YString16					(const YStringData& stringSrc) : YFixedString (m_szData, 16, FALSE) { Assign (stringSrc); }
	YString16					(LPCTSTR lpsz) : YFixedString (m_szData, 16, FALSE) { Assign (lpsz); }
	
	// overloaded assignment
	const YString16 &			operator=				(const YString16& stringSrc) { Assign (stringSrc); return *this; }
	const YString16 &			operator=				(const YStringData& stringSrc) { Assign (stringSrc); return *this; }
	const YString16 &			operator=				(TCHAR ch) { Assign (ch); return *this; }
	const YString16 &			operator=				(LPCSTR lpsz) { Assign (lpsz); return *this; }
	const YString16 &			operator=				(LPCWSTR lpsz) { Assign (lpsz); return *this; }
	const YString16 &			operator=				(const unsigned char* psz) { Assign (psz); return *this; }
#ifdef _UNICODE
	const YString16 &			operator=				(char ch) { Assign (ch); return *this; }
#endif

	// overloaded concatenation
	const YString16 &			operator+=				(const YStringData& stringSrc) { Concat (stringSrc); return *this; };
	const YString16 &			operator+=				(TCHAR ch) { Concat (ch); return *this; };
	const YString16 &			operator+=				(LPCSTR lpsz) { Concat (lpsz); return *this; };
	const YString16 &			operator+=				(LPCWSTR lpsz) { Concat (lpsz); return *this; };
	const YString16 &			operator+=				(const unsigned char* psz) { Concat (psz); return *this; };
#ifdef _UNICODE
	const YString16 &			operator+=				(char ch) { Concat (ch); return *this; };
#endif

private:
	// implementation
	TCHAR						m_szData[16];
};

class YString32 : public YFixedString
{
public:
	// construction
	YString32					(BOOL bEmpty = TRUE) : YFixedString (m_szData, 32, bEmpty) { }
	YString32					(const YStringData& stringSrc) : YFixedString (m_szData, 32, FALSE) { Assign (stringSrc); }
	YString32					(LPCTSTR lpsz) : YFixedString (m_szData, 32, FALSE) { Assign (lpsz); }
	
	// overloaded assignment
	const YString32 &			operator=				(const YString32& stringSrc) { Assign (stringSrc); return *this; }
	const YString32 &			operator=				(const YStringData& stringSrc) { Assign (stringSrc); return *this; }
	const YString32 &			operator=				(TCHAR ch) { Assign (ch); return *this; }
	const YString32 &			operator=				(LPCSTR lpsz) { Assign (lpsz); return *this; }
	const YString32 &			operator=				(LPCWSTR lpsz) { Assign (lpsz); return *this; }
	const YString32 &			operator=				(const unsigned char* psz) { Assign (psz); return *this; }
#ifdef _UNICODE
	const YString32 &			operator=				(char ch) { Assign (ch); return *this; }
#endif

	// overloaded concatenation
	const YString32 &			operator+=				(const YStringData& stringSrc) { Concat (stringSrc); return *this; };
	const YString32 &			operator+=				(TCHAR ch) { Concat (ch); return *this; };
	const YString32 &			operator+=				(LPCSTR lpsz) { Concat (lpsz); return *this; };
	const YString32 &			operator+=				(LPCWSTR lpsz) { Concat (lpsz); return *this; };
	const YString32 &			operator+=				(const unsigned char* psz) { Concat (psz); return *this; };
#ifdef _UNICODE
	const YString32 &			operator+=				(char ch) { Concat (ch); return *this; };
#endif

private:
	// implementation
	TCHAR						m_szData[32];
};

class YString64 : public YFixedString
{
public:
	// construction
	YString64					(BOOL bEmpty = TRUE) : YFixedString (m_szData, 64, bEmpty) { }
	YString64					(const YStringData& stringSrc) : YFixedString (m_szData, 64, FALSE) { Assign (stringSrc); }
	YString64					(LPCTSTR lpsz) : YFixedString (m_szData, 64, FALSE) { Assign (lpsz); }

	// overloaded assignment
	const YString64 &			operator=				(const YString64& stringSrc) { Assign (stringSrc); return *this; }
	const YString64 &			operator=				(const YStringData& stringSrc) { Assign (stringSrc); return *this; }
	const YString64 &			operator=				(TCHAR ch) { Assign (ch); return *this; }
	const YString64 &			operator=				(LPCSTR lpsz) { Assign (lpsz); return *this; }
	const YString64 &			operator=				(LPCWSTR lpsz) { Assign (lpsz); return *this; }
	const YString64 &			operator=				(const unsigned char* psz) { Assign (psz); return *this; }
#ifdef _UNICODE
	const YString64 &			operator=				(char ch) { Assign (ch); return *this; }
#endif

	// overloaded concatenation
	const YString64 &			operator+=				(const YStringData& stringSrc) { Concat (stringSrc); return *this; };
	const YString64 &			operator+=				(TCHAR ch) { Concat (ch); return *this; };
	const YString64 &			operator+=				(LPCSTR lpsz) { Concat (lpsz); return *this; };
	const YString64 &			operator+=				(LPCWSTR lpsz) { Concat (lpsz); return *this; };
	const YString64 &			operator+=				(const unsigned char* psz) { Concat (psz); return *this; };
#ifdef _UNICODE
	const YString64 &			operator+=				(char ch) { Concat (ch); return *this; };
#endif

private:
	// implementation
	TCHAR						m_szData[64];
};

class YString128 : public YFixedString
{
public:
	// construction
	YString128					(BOOL bEmpty = TRUE) : YFixedString (m_szData, 128, bEmpty) { }
	YString128					(const YStringData& stringSrc) : YFixedString (m_szData, 128, FALSE) { Assign (stringSrc); }
	YString128					(LPCTSTR lpsz) : YFixedString (m_szData, 128, FALSE) { Assign (lpsz); }
	
	// overloaded assignment
	const YString128 &			operator=				(const YString128& stringSrc) { Assign (stringSrc); return *this; }
	const YString128 &			operator=				(const YStringData& stringSrc) { Assign (stringSrc); return *this; }
	const YString128 &			operator=				(TCHAR ch) { Assign (ch); return *this; }
	const YString128 &			operator=				(LPCSTR lpsz) { Assign (lpsz); return *this; }
	const YString128 &			operator=				(LPCWSTR lpsz) { Assign (lpsz); return *this; }
	const YString128 &			operator=				(const unsigned char* psz) { Assign (psz); return *this; }
#ifdef _UNICODE
	const YString128 &			operator=				(char ch) { Assign (ch); return *this; }
#endif

	// overloaded concatenation
	const YString128 &			operator+=				(const YStringData& stringSrc) { Concat (stringSrc); return *this; };
	const YString128 &			operator+=				(TCHAR ch) { Concat (ch); return *this; };
	const YString128 &			operator+=				(LPCSTR lpsz) { Concat (lpsz); return *this; };
	const YString128 &			operator+=				(LPCWSTR lpsz) { Concat (lpsz); return *this; };
	const YString128 &			operator+=				(const unsigned char* psz) { Concat (psz); return *this; };
#ifdef _UNICODE
	const YString128 &			operator+=				(char ch) { Concat (ch); return *this; };
#endif

private:
	// implementation
	TCHAR						m_szData[128];
};

class YString256 : public YFixedString
{
public:
	// construction
	YString256					(BOOL bEmpty = TRUE) : YFixedString (m_szData, 256, bEmpty) { }
	YString256					(const YStringData& stringSrc) : YFixedString (m_szData, 256, FALSE) { Assign (stringSrc); }
	YString256					(LPCTSTR lpsz) : YFixedString (m_szData, 256, FALSE) { Assign (lpsz); }
	
	// overloaded assignment
	const YString256 &			operator=				(const YString256& stringSrc) { Assign (stringSrc); return *this; }
	const YString256 &			operator=				(const YStringData& stringSrc) { Assign (stringSrc); return *this; }
	const YString256 &			operator=				(TCHAR ch) { Assign (ch); return *this; }
	const YString256 &			operator=				(LPCSTR lpsz) { Assign (lpsz); return *this; }
	const YString256 &			operator=				(LPCWSTR lpsz) { Assign (lpsz); return *this; }
	const YString256 &			operator=				(const unsigned char* psz) { Assign (psz); return *this; }
#ifdef _UNICODE
	const YString256 &			operator=				(char ch) { Assign (ch); return *this; }
#endif

	// overloaded concatenation
	const YString256 &			operator+=				(const YStringData& stringSrc) { Concat (stringSrc); return *this; };
	const YString256 &			operator+=				(TCHAR ch) { Concat (ch); return *this; };
	const YString256 &			operator+=				(LPCSTR lpsz) { Concat (lpsz); return *this; };
	const YString256 &			operator+=				(LPCWSTR lpsz) { Concat (lpsz); return *this; };
	const YString256 &			operator+=				(const unsigned char* psz) { Concat (psz); return *this; };
#ifdef _UNICODE
	const YString256 &			operator+=				(char ch) { Concat (ch); return *this; };
#endif

private:
	// implementation
	TCHAR						m_szData[256];
};

class YString512 : public YFixedString
{
public:
	// construction
	YString512					(BOOL bEmpty = TRUE) : YFixedString (m_szData, 512, bEmpty) { }
	YString512					(const YStringData& stringSrc) : YFixedString (m_szData, 512, FALSE) { Assign (stringSrc); }
	YString512					(LPCTSTR lpsz) : YFixedString (m_szData, 512, FALSE) { Assign (lpsz); }
	
	// overloaded assignment
	const YString512 &			operator=				(const YString512& stringSrc) { Assign (stringSrc); return *this; }
	const YString512 &			operator=				(const YStringData& stringSrc) { Assign (stringSrc); return *this; }
	const YString512 &			operator=				(TCHAR ch) { Assign (ch); return *this; }
	const YString512 &			operator=				(LPCSTR lpsz) { Assign (lpsz); return *this; }
	const YString512 &			operator=				(LPCWSTR lpsz) { Assign (lpsz); return *this; }
	const YString512 &			operator=				(const unsigned char* psz) { Assign (psz); return *this; }
#ifdef _UNICODE
	const YString512 &			operator=				(char ch) { Assign (ch); return *this; }
#endif

	// overloaded concatenation
	const YString512 &			operator+=				(const YStringData& stringSrc) { Concat (stringSrc); return *this; };
	const YString512 &			operator+=				(TCHAR ch) { Concat (ch); return *this; };
	const YString512 &			operator+=				(LPCSTR lpsz) { Concat (lpsz); return *this; };
	const YString512 &			operator+=				(LPCWSTR lpsz) { Concat (lpsz); return *this; };
	const YString512 &			operator+=				(const unsigned char* psz) { Concat (psz); return *this; };
#ifdef _UNICODE
	const YString512 &			operator+=				(char ch) { Concat (ch); return *this; };
#endif

private:
	// implementation
	TCHAR						m_szData[512];
};

class YString1024 : public YFixedString
{
public:
	// construction
	YString1024					(BOOL bEmpty = TRUE) : YFixedString (m_szData, 1024, bEmpty) { }
	YString1024					(const YStringData& stringSrc) : YFixedString (m_szData, 1024, FALSE) { Assign (stringSrc); }
	YString1024					(LPCTSTR lpsz) : YFixedString (m_szData, 1024, FALSE) { Assign (lpsz); }
	
	// overloaded assignment
	const YString1024 &			operator=				(const YString1024& stringSrc) { Assign (stringSrc); return *this; }
	const YString1024 &			operator=				(const YStringData& stringSrc) { Assign (stringSrc); return *this; }
	const YString1024 &			operator=				(TCHAR ch) { Assign (ch); return *this; }
	const YString1024 &			operator=				(LPCSTR lpsz) { Assign (lpsz); return *this; }
	const YString1024 &			operator=				(LPCWSTR lpsz) { Assign (lpsz); return *this; }
	const YString1024 &			operator=				(const unsigned char* psz) { Assign (psz); return *this; }
#ifdef _UNICODE
	const YString1024 &			operator=				(char ch) { Assign (ch); return *this; }
#endif

	// overloaded concatenation
	const YString1024 &			operator+=				(const YStringData& stringSrc) { Concat (stringSrc); return *this; };
	const YString1024 &			operator+=				(TCHAR ch) { Concat (ch); return *this; };
	const YString1024 &			operator+=				(LPCSTR lpsz) { Concat (lpsz); return *this; };
	const YString1024 &			operator+=				(LPCWSTR lpsz) { Concat (lpsz); return *this; };
	const YString1024 &			operator+=				(const unsigned char* psz) { Concat (psz); return *this; };
#ifdef _UNICODE
	const YString1024 &			operator+=				(char ch) { Concat (ch); return *this; };
#endif

private:
	// implementation
	TCHAR						m_szData[1024];
};

class YBigString : public YFixedString
{
public:
	// construction
	YBigString					(BOOL bEmpty = TRUE) : YFixedString (m_szData, YLB_BIGSTRING_SIZE, bEmpty) { }
	YBigString					(const YStringData& stringSrc) : YFixedString (m_szData, YLB_BIGSTRING_SIZE, FALSE) { Assign (stringSrc); }
	YBigString					(LPCTSTR lpsz) : YFixedString (m_szData, YLB_BIGSTRING_SIZE, FALSE) { Assign (lpsz); }
	
	// overloaded assignment
	const YBigString &			operator=				(const YBigString& stringSrc) { Assign (stringSrc); return *this; }
	const YBigString &			operator=				(const YStringData& stringSrc) { Assign (stringSrc); return *this; }
	const YBigString &			operator=				(TCHAR ch) { Assign (ch); return *this; }
	const YBigString &			operator=				(LPCSTR lpsz) { Assign (lpsz); return *this; }
	const YBigString &			operator=				(LPCWSTR lpsz) { Assign (lpsz); return *this; }
	const YBigString &			operator=				(const unsigned char* psz) { Assign (psz); return *this; }
#ifdef _UNICODE
	const YBigString &			operator=				(char ch) { Assign (ch); return *this; }
#endif

	// overloaded concatenation
	const YBigString &			operator+=				(const YStringData& stringSrc) { Concat (stringSrc); return *this; };
	const YBigString &			operator+=				(TCHAR ch) { Concat (ch); return *this; };
	const YBigString &			operator+=				(LPCSTR lpsz) { Concat (lpsz); return *this; };
	const YBigString &			operator+=				(LPCWSTR lpsz) { Concat (lpsz); return *this; };
	const YBigString &			operator+=				(const unsigned char* psz) { Concat (psz); return *this; };
#ifdef _UNICODE
	const YBigString &			operator+=				(char ch) { Concat (ch); return *this; };
#endif

private:
	// implementation
	TCHAR						m_szData[YLB_BIGSTRING_SIZE];
};

#endif //WITH_TEMPLATES

/*=============================================================================
 * DYNAMICALLY ALLOCATED FIXED SYSTEM STRING CLASS
 *============================================================================*/
class YHeapString : public YFixedString
{
private:
	// kill these construction methods & operators
	YHeapString					(const YStringData& stringSrc);

public:
	// construction
	YHeapString					();
	~YHeapString				();

public:
	// allocation
	BOOL						Alloc					(UINT cbSize, BOOL bEmpty = TRUE);
	void						Free					();

public:
	// overloaded assignment
	const YHeapString &			operator=				(const YHeapString& stringSrc) { Assign (stringSrc); return *this; }
	const YHeapString &			operator=				(const YStringData& stringSrc) { Assign (stringSrc); return *this; }
	const YHeapString &			operator=				(TCHAR ch) { Assign (ch); return *this; }
	const YHeapString &			operator=				(LPCSTR lpsz) { Assign (lpsz); return *this; }
	const YHeapString &			operator=				(LPCWSTR lpsz) { Assign (lpsz); return *this; }
	const YHeapString &			operator=				(const unsigned char* psz) { Assign (psz); return *this; }
#ifdef _UNICODE
	const YHeapString &			operator=				(char ch) { Assign (ch); return *this; }
#endif

	// overloaded concatenation
	const YHeapString &			operator+=				(const YStringData& stringSrc) { Concat (stringSrc); return *this; };
	const YHeapString &			operator+=				(TCHAR ch) { Concat (ch); return *this; };
	const YHeapString &			operator+=				(LPCSTR lpsz) { Concat (lpsz); return *this; };
	const YHeapString &			operator+=				(LPCWSTR lpsz) { Concat (lpsz); return *this; };
	const YHeapString &			operator+=				(const unsigned char* psz) { Concat (psz); return *this; };
#ifdef _UNICODE
	const YHeapString &			operator+=				(char ch) { Concat (ch); return *this; };
#endif
};

/*=============================================================================
 * SYSTEM STRING CLASSES
 *============================================================================*/
class YPathString : public YFixedString
{
public:
	// construction
	YPathString					(BOOL bEmpty = TRUE) : YFixedString (m_szData, MAX_PATH, bEmpty) { }
	YPathString					(const YStringData& stringSrc) : YFixedString (m_szData, MAX_PATH, FALSE) { Assign (stringSrc); }
	YPathString					(LPCTSTR lpsz) : YFixedString (m_szData, MAX_PATH, FALSE) { Assign (lpsz); }
	
	// overloaded assignment
	const YPathString &			operator=				(const YPathString& stringSrc) { Assign (stringSrc); return *this; }
	const YPathString &			operator=				(const YStringData& stringSrc) { Assign (stringSrc); return *this; }
	const YPathString &			operator=				(TCHAR ch) { Assign (ch); return *this; }
	const YPathString &			operator=				(LPCSTR lpsz) { Assign (lpsz); return *this; }
	const YPathString &			operator=				(LPCWSTR lpsz) { Assign (lpsz); return *this; }
	const YPathString &			operator=				(const unsigned char* psz) { Assign (psz); return *this; }
#ifdef _UNICODE
	const YPathString &			operator=				(char ch) { Assign (ch); return *this; }
#endif

	// overloaded concatenation
	const YPathString &			operator+=				(const YStringData& stringSrc) { Concat (stringSrc); return *this; };
	const YPathString &			operator+=				(TCHAR ch) { Concat (ch); return *this; };
	const YPathString &			operator+=				(LPCSTR lpsz) { Concat (lpsz); return *this; };
	const YPathString &			operator+=				(LPCWSTR lpsz) { Concat (lpsz); return *this; };
	const YPathString &			operator+=				(const unsigned char* psz) { Concat (psz); return *this; };
#ifdef _UNICODE
	const YPathString &			operator+=				(char ch) { Concat (ch); return *this; };
#endif

public:
	// special operations and attributes
	LPCTSTR						GetFileName				() const;
	LPCTSTR						GetFileExtension		() const;
	void						AddFileName				(LPCTSTR pszFileName);
	void						AddFileExtension		(LPCTSTR pszFileExtension);
	void						SubstFileName			(LPCTSTR pszFileName);
	void						SubstFileExtension		(LPCTSTR pszFileExtension);
	void						StripFileName			(BOOL bToValidPath = FALSE);
	void						StripExtension			();
	void						AppendBackslash			(BOOL bToValidPath = FALSE);
	void						RemoveBackslash			();
	BOOL						IsFile					() const;
	BOOL						IsDir					() const;
	BOOL						IsDirWritable			() const;
	BOOL						IsDirCompressed			() const;
	BOOL						IsDirEmpty				() const;
	BOOL						CreateDirectoryTree		() const;
	BOOL						DeleteFiles				() const;
	BOOL						RemoveDir				() const;
	BOOL						KillDir					() const;
	BOOL						CompressDir				() const;
	BOOL						UncompressDir			() const;
	BOOL						CompressDirTree			() const;
	BOOL						UncompressDirTree		() const;

private:
	// implementation
	TCHAR						m_szData[MAX_PATH];
};

class YComputerName : public YFixedString
{
public:
	// construction
	YComputerName				(BOOL bEmpty = TRUE) : YFixedString (m_szData, MAX_COMPUTERNAME_LENGTH + 1, bEmpty) { }
	YComputerName				(const YStringData& stringSrc) : YFixedString (m_szData, MAX_COMPUTERNAME_LENGTH + 1, FALSE) { Assign (stringSrc); }
	YComputerName				(LPCTSTR lpsz) : YFixedString (m_szData, MAX_COMPUTERNAME_LENGTH + 1, FALSE) { Assign (lpsz); }
	YComputerName				(const YUNC& uncSrc) : YFixedString (m_szData, MAX_COMPUTERNAME_LENGTH + 1, FALSE) { FromUNC (uncSrc); }

public:
	// special operations
	BOOL						GetCurrent				();
	BOOL						FromUNC					(LPCTSTR lpszUNC);
	const YComputerName &		operator=				(const YUNC& unc) { FromUNC (unc); return *this; }

public:
	// overloaded assignment
	const YComputerName &		operator=				(const YComputerName& stringSrc) { Assign (stringSrc); return *this; }
	const YComputerName &		operator=				(const YStringData& stringSrc) { Assign (stringSrc); return *this; }
	const YComputerName &		operator=				(TCHAR ch) { Assign (ch); return *this; }
	const YComputerName &		operator=				(LPCSTR lpsz) { Assign (lpsz); return *this; }
	const YComputerName &		operator=				(LPCWSTR lpsz) { Assign (lpsz); return *this; }
	const YComputerName &		operator=				(const unsigned char* psz) { Assign (psz); return *this; }
#ifdef _UNICODE
	const YComputerName &		operator=				(char ch) { Assign (ch); return *this; }
#endif

	// overloaded concatenation
	const YComputerName &		operator+=				(const YStringData& stringSrc) { Concat (stringSrc); return *this; };
	const YComputerName &		operator+=				(TCHAR ch) { Concat (ch); return *this; };
	const YComputerName &		operator+=				(LPCSTR lpsz) { Concat (lpsz); return *this; };
	const YComputerName &		operator+=				(LPCWSTR lpsz) { Concat (lpsz); return *this; };
	const YComputerName &		operator+=				(const unsigned char* psz) { Concat (psz); return *this; };
#ifdef _UNICODE
	const YComputerName &		operator+=				(char ch) { Concat (ch); return *this; };
#endif

private:
	// implementation
	TCHAR						m_szData[MAX_COMPUTERNAME_LENGTH + 1];
};

class YUserName : public YFixedString
{
public:
	// construction
	YUserName					(BOOL bEmpty = TRUE) : YFixedString (m_szData, UNLEN + 1, bEmpty) { }
	YUserName					(const YStringData& stringSrc) : YFixedString (m_szData, UNLEN + 1, FALSE) { Assign (stringSrc); }
	YUserName					(LPCTSTR lpsz) : YFixedString (m_szData, UNLEN + 1, FALSE) { Assign (lpsz); }

public:
	// special operations
	BOOL						GetCurrent				();

public:
	// overloaded assignment
	const YUserName &			operator=				(const YUserName& stringSrc) { Assign (stringSrc); return *this; }
	const YUserName &			operator=				(const YStringData& stringSrc) { Assign (stringSrc); return *this; }
	const YUserName &			operator=				(TCHAR ch) { Assign (ch); return *this; }
	const YUserName &			operator=				(LPCSTR lpsz) { Assign (lpsz); return *this; }
	const YUserName &			operator=				(LPCWSTR lpsz) { Assign (lpsz); return *this; }
	const YUserName &			operator=				(const unsigned char* psz) { Assign (psz); return *this; }
#ifdef _UNICODE
	const YUserName &			operator=				(char ch) { Assign (ch); return *this; }
#endif

	// overloaded concatenation
	const YUserName &			operator+=				(const YStringData& stringSrc) { Concat (stringSrc); return *this; };
	const YUserName &			operator+=				(TCHAR ch) { Concat (ch); return *this; };
	const YUserName &			operator+=				(LPCSTR lpsz) { Concat (lpsz); return *this; };
	const YUserName &			operator+=				(LPCWSTR lpsz) { Concat (lpsz); return *this; };
	const YUserName &			operator+=				(const unsigned char* psz) { Concat (psz); return *this; };
#ifdef _UNICODE
	const YUserName &			operator+=				(char ch) { Concat (ch); return *this; };
#endif

private:
	// implementation
	TCHAR						m_szData[UNLEN + 1];
};

/*=============================================================================
 * MULTISTRING CLASS DECLARATION
 *============================================================================*/
class YMultiString : public YStringData
{
private:
	// kill these construction methods & operators
	YMultiString				(const YStringData& stringSrc);

public:
	// construction
	YMultiString				();
	~YMultiString				();

public:
	// allocation
	BOOL						Alloc					(UINT cbSize, BOOL bEmpty = TRUE);
	void						Free					();

};

#ifdef YLB_ENABLE_INLINE
#include <yFixStr.inl>
#endif

#endif //__yFixStr_h__
//
// EoF
////////
