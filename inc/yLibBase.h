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
 * FILENAME		:	yLibBase.hpp
 * PURPOSE		:	Base definitions for all yLib features
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.3  2001/05/16 17:15:34  leopoldo
 * Added support for reattachment of RTL output handles
 *
 * Revision 1.2  2000/09/04 11:59:53  leopoldo
 * Updated license to zlib/libpng
 *
 * Revision 1.1  2000/05/26 14:03:14  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yLibBase.h
 *============================================================================*/
#ifndef __yLibBase_h__
#define __yLibBase_h__

/*=============================================================================
 * GENERAL DOCUMENTATION
 *
 * Please use the following defines to change the behaviour of yLib:
 *
 * YLB_NO_PLATFORM_SDK:		Prevent from including our subset of windows.h
 * YLB_NO_PLATFORM_SDKCFG:	Prevent from defining our subset of windows.h
 * YLB_NO_RUNTIME_LIBRARY:	Prevent from including the runtime library
 *============================================================================*/

/*=============================================================================
 * These defines are relevant when compiling yLib:
 *
 * YLB_ENABLE_PORTABLE:		Don't use machine specific extension
 * YLB_ENABLE_INLINE:		Activate inlining
 * YLB_ALWAYS_VTABLE:		Deactivates __declspec(novtable) for YObject classes
 * YLB_BIGSTRING_SIZE:		Size for the YBigString fixed string (defaults to 4096)
 * YLB_PACKING:				
 *============================================================================*/
#if defined(_M_MRX000) || defined(_M_ALPHA) || defined(_M_PPC)
#define YLB_PACKING		8
#else
#define YLB_PACKING		4
#endif
#ifndef _DEBUG
#define YLB_ENABLE_INLINE
#endif
#ifndef YLB_BIGSTRING_SIZE
#define YLB_BIGSTRING_SIZE		4096
#endif

/*=============================================================================
 * LIBRARY INCLUSION STATEMENT
 *============================================================================*/
#if defined(_UNICODE)
	#if defined(_DEBUG)
		#if defined(_DLL)
			#pragma comment(lib, "uYLBdwd.lib")
		#else
			#pragma comment(lib, "uYLBswd.lib")
		#endif
	#else
		#if defined(_DLL)
			#pragma comment(lib, "uYLBdwr.lib")
		#else
			#pragma comment(lib, "uYLBswr.lib")
		#endif
	#endif
#else
	#if defined(_DEBUG)
		#if defined(_DLL)
			#pragma comment(lib, "nYLBdwd.lib")
		#else
			#pragma comment(lib, "nYLBswd.lib")
		#endif
	#else
		#if defined(_DLL)
			#pragma comment(lib, "nYLBdwr.lib")
		#else
			#pragma comment(lib, "nYLBswr.lib")
		#endif
	#endif
#endif

/*=============================================================================
 * SYSTEM LIBRARY INCLUSION STATEMENTS
 *============================================================================*/
#pragma comment(lib, "version.lib")

/*=============================================================================
 * INCLUSION & COMPATIBILITY TEST
 *============================================================================*/
#ifndef _MT
#error yLib supports only the multithreaded runtime library!
#endif

#if defined(_WINDOWS_) || defined (__AFX_H__)
#define YLB_NO_PLATFORM_SDKCFG
#endif

/*=============================================================================
 * RUNTIME LIBRARY
 *============================================================================*/
#if !defined(YLB_NO_RUNTIME_LIBRARY)

#ifndef _INC_STRING
	#include <string.h>
#endif
#ifndef _INC_STDIO
	#include <stdio.h>
#endif
#ifndef _INC_STDLIB
	#include <stdlib.h>
#endif
#ifndef _INC_TIME
	#include <time.h>
#endif
#ifndef _INC_LIMITS
	#include <limits.h>
#endif
#ifndef _INC_STDDEF
	#include <stddef.h>
#endif
#ifndef _INC_STDARG
	#include <stdarg.h>
#endif
#ifndef _INC_PROCESS
	#include <process.h>
#endif
#ifndef _INC_CRTDBG
	#include <crtdbg.h>
#endif
#ifndef _INC_TCHAR
	#include <tchar.h>
#endif
#ifndef _INC_CONIO
	#include <conio.h>
#endif

#endif //!defined(YLB_NO_RUNTIME_LIBRARY)

/*=============================================================================
 * BROWSER CONFIGURATION
 *============================================================================*/
#pragma component(browser, off, references, "ASSERTY")
#pragma component(browser, off, references, "YlbAssertFailedLine")
#pragma component(browser, off, references, "YlbDebugBreak")
#pragma component(browser, off, references, "BOOL")
#pragma component(browser, off, references, "BYTE")
#pragma component(browser, off, references, "DECLSPEC_IMPORT")
#pragma component(browser, off, references, "DWORD")
#pragma component(browser, off, references, "FALSE")
#pragma component(browser, off, references, "FAR")
#pragma component(browser, off, references, "LPSTR")
#pragma component(browser, off, references, "LPTSTR")
#pragma component(browser, off, references, "LPCSTR")
#pragma component(browser, off, references, "LPCTSTR")
#pragma component(browser, off, references, "NULL")
#pragma component(browser, off, references, "PASCAL")
#pragma component(browser, off, references, "THIS_FILE")
#pragma component(browser, off, references, "TRUE")
#pragma component(browser, off, references, "UINT")
#pragma component(browser, off, references, "WINAPI")
#pragma component(browser, off, references, "WORD")

/*=============================================================================
 * CONFIGURATION DEFINES
 *============================================================================*/
#ifndef STRICT
#define STRICT 1
#endif

#ifndef WIN32
#define WIN32
#endif

#ifdef _UNICODE
#ifndef UNICODE
#define UNICODE         // UNICODE is used by Windows headers
#endif
#endif

#ifdef UNICODE
#ifndef _UNICODE
#define _UNICODE        // _UNICODE is used by C-runtime/YLB headers
#endif
#endif

/*=============================================================================
 * PLATFORM SDK
 *============================================================================*/
#if !defined(YLB_NO_PLATFORM_SDK)

#if !defined(YLB_NO_PLATFORM_SDKCFG)

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#define NOGDICAPMASKS			// - CC_*, LC_*, PC_*, CP_*, TC_*, RC_
#define NOVIRTUALKEYCODES		// - VK_*
//#define NOWINMESSAGES			// - WM_*, EM_*, LB_*, CB_*
#define NOWINSTYLES				// - WS_*, CS_*, ES_*, LBS_*, SBS_*, CBS_*
#define NOSYSMETRICS			// - SM_*
#define NOMENUS					// - MF_*
#define NOICONS					// - IDI_*
#define NOKEYSTATES				// - MK_*
#define NOSYSCOMMANDS			// - SC_*
#define NORASTEROPS				// - Binary and Tertiary raster ops
#define NOSHOWWINDOW			// - SW_*
//#define OEMRESOURCE			// - OEM Resource values
//#define NOATOM				// - Atom Manager routines
#define NOCLIPBOARD				// - Clipboard routines
#define NOCOLOR					// - Screen colors
//#define NOCTLMGR				// - Control and Dialog routines
#define NODRAWTEXT				// - DrawText() and DT_*
//#define NOKERNEL				// - All GDI defines and routines
//#define NOUSER				// - All KERNEL defines and routines
//#define NOGDI					// - All USER defines and routines
//#define NONLS					// - All NLS defines and routines
//#define NOMB					// - MB_* and MessageBox()
//#define NOMEMMGR				// - GMEM_*, LMEM_*, GHND, LHND, associated routines
#define NOMETAFILE				// - typedef METAFILEPICT
//#define NOMINMAX				// - Macros min(a,b) and max(a,b)
//#define NOMSG					// - typedef MSG and associated routines
//#define NOOPENFILE			// - OpenFile(), OemToAnsi, AnsiToOem, and OF_*
#define NOSCROLL				// - SB_* and scrolling routines
//#define NOSERVICE				// - All Service Controller routines, SERVICE_ equates, etc.
#define NOSOUND					// - Sound driver routines
#define NOTEXTMETRIC			// - typedef TEXTMETRIC and associated routines
#define NOWH					// - SetWindowsHook and WH_*
#define NOWINOFFSETS			// - GWL_*, GCL_*, associated routines
//#define NOCOMM				// - COMM driver routines
#define NOKANJI					// - Kanji support stuff.
#define NOHELP					// - Help engine interface.
#define NOPROFILER				// - Profiler interface.
#define NODEFERWINDOWPOS		// - DeferWindowPos routines
#define NOMCX					// - Modem Configuration Extensions

#endif //!defined(YLB_NO_PLATFORM_SDKCFG)

#ifndef _WINDOWS_
#include <windows.h>
#endif
#ifndef __ACCESS_CONTROL__
#include <accctrl.h>
#endif
#ifndef __ACCESS_CONTROL_API__
#include <aclapi.h>
#endif
#ifndef NETCONS_INCLUDED
#include <lmcons.h>
#endif

#endif //!defined(YLB_NO_PLATFORM_SDK)

/*=============================================================================
 * INLINING
 *============================================================================*/
#ifdef YLB_ENABLE_INLINE
#define YLB_INLINE inline
#else
#define YLB_INLINE
#endif

/*=============================================================================
 * FORWARD CLASS DECLARATIONS
 *============================================================================*/
struct	YRuntimeInfo;
class	YCommandLineInfo;
class	YObject;

/*=============================================================================
 * DEBUG BREAK FUNCTION
 *============================================================================*/
#ifndef YlbDebugBreak
#if defined(_M_IX86) && !defined(YLB_ENABLE_PORTABLE)
#define YlbDebugBreak() _asm { int 3 }
#else
#define YlbDebugBreak() DebugBreak()
#endif
#else
#define YlbDebugBreak() _CrtDbgBreak()
#endif

#ifndef _DEBUG
#ifdef YlbDebugBreak
#undef YlbDebugBreak
#endif
#define YlbDebugBreak ()
#endif  // _DEBUG

/*=============================================================================
 * Standard preprocessor symbols if not already defined
 *============================================================================*/

// SIZE_T_MAX is used by the collection classes
#ifndef SIZE_T_MAX
	#define SIZE_T_MAX  UINT_MAX
#endif

// PASCAL is used for static member functions
#ifndef PASCAL
	#define PASCAL  __stdcall
#endif

// FASTCALL is used for static member functions with little or no params
#ifndef FASTCALL
	#define FASTCALL __fastcall
#endif

// CDECL and EXPORT are defined in case WINDOWS.H doesn't
#ifndef CDECL
	#define CDECL __cdecl
#endif

#ifndef EXPORT
	#define EXPORT
#endif

// UNALIGNED is used for unaligned data access (in CArchive mostly)
#ifndef UNALIGNED
	#define UNALIGNED
#endif

// YLBAPI is used on global public functions
#ifndef YLBAPI
	#define YLBAPI __stdcall
#endif

// YLB_CDECL is used for rare functions taking variable arguments
#ifndef YLB_CDECL
	#define YLB_CDECL __cdecl
#endif

// YLB_EXPORT is used for functions which need to be exported
#ifndef YLB_EXPORT
	#define YLB_EXPORT EXPORT
#endif

#ifndef YLB_STATIC
	#define YLB_STATIC extern
	#define YLB_STATIC_DATA extern __declspec(selectany)
#endif

// This macro is used to reduce size requirements of some classes
#ifndef YLB_ALWAYS_VTABLE
#ifndef YLB_NOVTABLE
#if _MSC_VER >= 1100 && !defined(_DEBUG)
#define YLB_NOVTABLE __declspec(novtable)
#else
#define YLB_NOVTABLE
#endif
#endif
#endif

/*=============================================================================
 * USEFUL MACROS
 *============================================================================*/
#define _countof(array)			(sizeof(array)/sizeof(array[0]))

/*=============================================================================
 * TRANSFORMER
 *============================================================================*/
BOOL YLB_CDECL					_yxtot					(DWORD dwVal, LPTSTR pszBuffer, UINT cbBuffer, BOOL fIsNegative);

/*=============================================================================
 * HELPER FUNCTIONS
 *============================================================================*/
HINSTANCE YLBAPI				YlbGetResourceHandle	();
HINSTANCE YLBAPI				YlbGetInstanceHandle	();
HANDLE YLBAPI					YlbGetProcessHandle		();
HANDLE YLBAPI					YlbGetThreadHandle		();
int YLBAPI						YlbLoadString			(UINT nID, LPTSTR lpszBuf, UINT nMaxBuf);
BOOL YLBAPI						YlbGetSysErrorString	(DWORD dwError, LPTSTR lpszBuf, UINT nMaxBuf);
BOOL YLBAPI						YlbIsAttachedToConsole	();
BOOL YLBAPI						YlbReattachRTL			();

/*=============================================================================
 * Diagnostic memory management routines
 *============================================================================*/
BOOL YLBAPI						YlbIsValidAddress		(const void* lp, UINT nBytes, BOOL bReadWrite = TRUE);
BOOL YLBAPI						YlbIsValidString		(LPCWSTR lpsz, int nLength = -1);
BOOL YLBAPI						YlbIsValidString		(LPCSTR lpsz, int nLength = -1);

/*=============================================================================
 * Diagnostic support
 *============================================================================*/
#ifdef _DEBUG

BOOL YLBAPI						YlbAssertFailedLine		(LPCSTR lpszFileName, int nLine);
void YLB_CDECL					YlbTrace				(LPCTSTR lpszFormat, ...);

#define YLB_TRACE				::YlbTrace
#define HERE					__FILE__
#define ASSERTY(f) \
	do { \
		if ( !(f) && YlbAssertFailedLine (HERE, __LINE__) ) \
			YlbDebugBreak(); \
	} while (0) \

#define VERIFYY(f)				ASSERTY(f)
#define DBG_ONLY(f)				(f)

#define YLB_TRACE0(sz)			::YlbTrace(_T("%s"), _T(sz))
#define YLB_TRACE1(sz,p1)		::YlbTrace(_T(sz), p1)
#define YLB_TRACE2(sz,p1,p2)	::YlbTrace(_T(sz), p1, p2)
#define YLB_TRACE3(sz,p1,p2,p3)	::YlbTrace(_T(sz), p1, p2, p3)

#else   // _DEBUG

inline void YLB_CDECL			YlbTrace				(LPCTSTR, ...) { }

#define ASSERTY(f)				((void)0)
#define VERIFYY(f)				((void)(f))
#define DBG_ONLY(f)				((void)0)
#define YLB_TRACE				1?(void)0: ::YlbTrace
#define YLB_TRACE0(sz)
#define YLB_TRACE1(sz,p1)
#define YLB_TRACE2(sz,p1,p2)
#define YLB_TRACE3(sz,p1,p2,p3)

#endif // !_DEBUG

#define ASSERTY_POINTER(p, type) \
	ASSERTY(((p) != NULL) && YlbIsValidAddress((p), sizeof(type), FALSE))

#define ASSERTY_NULL_OR_POINTER(p, type) \
	ASSERTY(((p) == NULL) || YlbIsValidAddress((p), sizeof(type), FALSE))

/*=============================================================================
 * BASIC TYPES
 *============================================================================*/
// abstract iteration position
struct __ITERATOR {
};

typedef __ITERATOR*				ITERATOR;

/*=============================================================================
 * LIKE NULL BUT NOT A POINTER
 *============================================================================*/
#define ZERO					((int) 0)

/*=============================================================================
 * MACROS & DEFINES
 *============================================================================*/
#define BEFORE_START_ITERATOR				((ITERATOR) - 1L)

#define RUNTIME_INFO(class_name)			((YRuntimeInfo *)(&class_name::info##class_name))
#define ASSERTY_KINDOF(class_name,object)	ASSERTY((object)->IsKindOf(RUNTIME_INFO(class_name)))

#define DECLARE_QUERABLE(class_name) \
public: \
	static const				YRuntimeInfo			info##class_name; \
	virtual YRuntimeInfo*		GetRuntimeInfo			() const; \

#define DECLARE_DYNAMIC_CREATABLE(class_name) \
	DECLARE_QUERABLE(class_name) \
	static YObject* PASCAL		CreateObject			(); \


#define IMPLEMENT_RUNTIMEINFO(class_name, base_class_name, pfnNew) \
	const YRuntimeInfo			class_name::info##class_name = { \
		pfnNew, RUNTIME_INFO(base_class_name), NULL \
	}; \
	YRuntimeInfo* class_name::GetRuntimeInfo () const \
		{ return RUNTIME_INFO(class_name); } \

#define IMPLEMENT_QUERABLE(class_name, base_class_name) \
	IMPLEMENT_RUNTIMEINFO(class_name, base_class_name, NULL)

#define IMPLEMENT_DYNAMIC_CREATABLE(class_name, base_class_name) \
	YObject* PASCAL class_name::CreateObject () \
		{ return new class_name; } \
	IMPLEMENT_RUNTIMEINFO(class_name, base_class_name, class_name::CreateObject) \

/*=============================================================================
 * HELPER CLASSES
 *============================================================================*/
struct YRuntimeInfo
{
	YObject*					(PASCAL* m_pfnCreateObject)();
	YRuntimeInfo*				m_pBaseClass;
	YRuntimeInfo*				m_pNextClass;

	YObject*					CreateObject			();
	BOOL						IsDerivedFrom			(const YRuntimeInfo* pBaseClass) const;
};

class YCommandLineInfo
{
public:
	YCommandLineInfo			() { m_argc = 0; m_argv = NULL; }
	YCommandLineInfo			(int argc, TCHAR **argv) { m_argc = (UINT) argc; m_argv = argv; }

public:
	// attributes
	LPCTSTR						operator[]				(UINT nIndex) const { return GetAt (nIndex); }

public:
	// attributes
	LPCTSTR						GetAt					(UINT nIndex) const { return ((nIndex >= 0) && (nIndex < m_argc)) ? (m_argv[nIndex]) : (NULL); }
	UINT						GetParamCount			() const { return m_argc; }
	ITERATOR					GetHeadPosition			() const { return (m_argc) ? ((ITERATOR) &(m_argv[0])) : (NULL); }
	ITERATOR					GetTailPosition			() const { return (m_argc) ? ((ITERATOR) &(m_argv[m_argc - 1])) : (NULL); }
	LPCTSTR						GetNext					(ITERATOR &pos) const;
	LPCTSTR						GetPrev					(ITERATOR &pos) const;
	LPCTSTR						GetAt					(ITERATOR pos) const;
	LPCTSTR						Skip					(ITERATOR &pos, UINT nSkip = 1) const;

public:
	UINT						m_argc;
	TCHAR						**m_argv;
};

class YLB_NOVTABLE YObject
{
protected:
	// construction
	YObject						();

private:
	// kill these construction methods & operators
	YObject						(const YObject& objectSrc);
	void						operator=				(const YObject& objectSrc);

public:
	// runtime information support
	virtual ~YObject			();
	virtual YRuntimeInfo*		GetRuntimeInfo			() const;

public:
	// attributes
	BOOL						IsKindOf				(const YRuntimeInfo* pInfo) const;

public:
	// implementation
	static const				YRuntimeInfo			infoYObject;
};

class YErrableObject
{
public:
	// construction
	YErrableObject				(DWORD dwError = NOERROR) { m_dwLastError = dwError; }

public:
	// attributes
	DWORD						GetLastError			() const { return m_dwLastError; }
	BOOL						SetLastError			(DWORD dwLastError) { m_dwLastError = dwLastError; return  m_dwLastError != NOERROR; }
	void						SetLastSysError			() { m_dwLastError = ::GetLastError (); }
	BOOL						HasFailed				() const { return m_dwLastError != NOERROR; }

protected:
	// implementation
	DWORD						m_dwLastError;
};

#ifdef YLB_ENABLE_INLINE
#include <yLibBase.inl>
#endif

#endif //__yLibBase_h__

//
// EoF
////////