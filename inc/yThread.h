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
 * FILENAME		:	yThread.h
 * PURPOSE		:	Declaration of the thread class
 * SCOPE		:	yLib
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.2  2000/09/04 11:59:53  leopoldo
 * Updated license to zlib/libpng
 *
 * Revision 1.1  2000/05/26 14:03:36  leo
 * Initial revision
 *
 *============================================================================*/

/*=============================================================================
 * @doc YLIB | yThread.h
 *============================================================================*/
#ifndef __yThread_h__
#define __yThread_h__

/*=============================================================================
 * RELATED INCLUDES
 *============================================================================*/
#ifndef __yLibBase_h__
#include <yLibBase.h>
#endif
#ifndef __ySync_h__
#include <ySync.h>
#endif

/*=============================================================================
 * MISSING PROTOTYPES FROM winbase.h
 *============================================================================*/
extern "C" {

	WINADVAPI HANDLE WINAPI OpenThread (
		DWORD	dwDesiredAccess,  // access right
		BOOL	bInheritHandle,    // handle inheritance option
		DWORD	dwThreadId        // thread identifier
	);

}

/*=============================================================================
 * FORWARD CLASS DECLARATIONS
 *============================================================================*/
class YBaseHandle;
	class YHandle;
		class YSyncHandle;
			class YThread;

/*=============================================================================
 * CONSTANTS
 *============================================================================*/
#define YLB_MAX_THREADNAME				16

/*=============================================================================
 * THE THREAD BASE CLASS
 *============================================================================*/
// @class	The system thread object class
// @base	public | YSyncHandle
// @comm	The <c YThread> class encapsulates all thread handle related functions.
//			Sinces it's derived from <c YSyncHandle>, all synchronisation operations
//			can directly been performed on this class.
// @group MEMBER FUNCTIONS:
// @head2 Construcion |
//		<mf YThread::YThread>: Constructs a <c YThread > object.
// @head2 Operations |
//		<mf YThread::Attach>: Attaches a thread handle to to the <c YThread> object.
//
//		<mf YThread::Open>: Open a running thread by specifying it's ID.
//
//		<mf YThread::Suspend>: Suspends a running thread.
//
//		<mf YThread::Resume>: Resumes a running thread.
//
//		<mf YThread::Terminate>: Terminates a running thread.
// @head2 Attributes |
//		<mf YThread::GetExitCode>: Returns the exit code of a thread.
//
//		<mf YThread::GetPriority>: Returns the priority of a thread.
//
//		<mf YThread::SetPriority>: Changes the priority of a thread.
//
//		<mf YThread::GetPriorityBoost>: Returns the priority boost control state of a thread.
//
//		<mf YThread::SetPriorityBoost>: Disables the ability of the system to temporarily boost the priority of a thread.
//
//		<mf YThread::GetTimes>: Obtains timing information about a thread.
//
//		<mf YThread::SetAffinityMask>: Sets a processor affinity mask for a thread.
//
//		<mf YThread::SetIdealProcessor>: Specifies a preferred processor for a thread. 
//
// @xref	<c YThread>, <c YSyncHandle>, <c YHandle>
class YThread : public YSyncHandle
{
private:
	// kill these construction methods & operators
	YThread						(const YThread &);
	YThread						&operator=				(const YThread &);

public:
	// construction
	YThread						();

public:
	// operations
	void						Attach					(HANDLE hThread);
#if(_WIN32_WINNT >= 0x0500)
	BOOL						Open					(DWORD dwThreadId, DWORD dwDesiredAccess = THREAD_ALL_ACCESS, BOOL bInheritHandle = FALSE);
#endif
	DWORD						Suspend					() const;
	DWORD						Resume					() const;
	BOOL						Terminate				(DWORD dwExitCode) const;

	virtual BOOL				Unlock					();
	virtual BOOL				Unlock					(LONG lCount, LPLONG lpPrevCount = NULL);

public:
	// attributes
	BOOL						GetExitCode				(LPDWORD lpdwExitCode) const;
	int							GetPriority				() const;
	BOOL						SetPriority				(int nPriority) const;
	BOOL						GetPriorityBoost		(LPBOOL pbDisablePriorityBoost) const;
	BOOL						SetPriorityBoost		(BOOL bDisablePriorityBoost) const;
	BOOL						GetTimes				(LPFILETIME lpCreationTime, LPFILETIME lpExitTime, LPFILETIME lpKernelTime, LPFILETIME lpUserTime) const;
	DWORD						SetAffinityMask			(DWORD dwThreadAffinityMask) const;
#if(_WIN32_WINNT >= 0x0400)
	DWORD						SetIdealProcessor		(DWORD dwIdealProcessor = MAXIMUM_PROCESSORS) const;
#endif
};

/*=============================================================================
 * THE WORKER THREAD CLASS
 *============================================================================*/
// @class	The worker thread class
// @base	public | YThread
// @comm	The <c YWorkerThread> class is a base class from which you can
//			derive your own worker thread classes.
// @group MEMBER FUNCTIONS:
// @head2 Construcion |
//		<mf YWorkerThread::YWorkerThread>: Constructs a <c YWorkerThread > object.
// @head2 Operations |
//		<mf YWorkerThread::Create>: Creates the thread.
//
//		<mf YWorkerThread::Suspend>: Suspends a running thread.
//
//		<mf YWorkerThread::Resume>: Resumes a suspended thread.
//
//		<mf YWorkerThread::Terminate>: Terminates a thread.
//
// @head2 Overridables |
//		<mf YWorkerThread::OnInitThread>: Override to perform thread
//		instance initialization, such as creating your internal objects
//
//		<mf YWorkerThread::OnRunThread>: Override to perform that thread's real work.
//
//		<mf YWorkerThread::OnExitThread>: Override to clean up when your thread
//		terminates.
//
//		<mf YWorkerThread::OnQuerYWorkerThreadTermination>: Override to respond to a
//		termination request.
//
//		<mf YWorkerThread::OnHardThreadTermination>: Override to handle cleanup
//		when you thread was terminated ingracefully.
//
// @head2 Attributes |
//		<mf YWorkerThread::GetLastError>: Returns the last error code for
//		the thread object.
//
//		<mf YWorkerThread::GetSuspendCount>: Returns the count of suspend
//		requests.
//
//		<mf YWorkerThread::SetName>: Sets the name of the thread.
//
//		<mf YWorkerThread::GetName>: Returns the name of the thread.
//
//		<mf YWorkerThread::IsRunning>: Return status information about the thread.
//
//		<mf YWorkerThread::IsThis>: Returns <TRUE> if called from the worker thread.
//
// @xref	<c YThread>, <c YSyncHandle>, <c YHandle>
class YWorkerThread : public YErrableObject, public YThread
{
private:
	// kill these construction methods & operators
	YWorkerThread				(const YWorkerThread &);
	YWorkerThread				&operator=				(const YWorkerThread &);

public:
	// construction/destruction
	YWorkerThread				(LPCTSTR pszName = _T("<noname>"));
	~YWorkerThread				();

public:
	// operations
	BOOL						Open					(DWORD dwThreadId, DWORD dwDesiredAccess = THREAD_ALL_ACCESS, BOOL bInheritHandle = FALSE);
	BOOL						Create					(BOOL bSuspended = FALSE, UINT uStackSize = 0, LPSECURITY_ATTRIBUTES lpThreadAttributes = NULL);
	BOOL						Suspend					(void);
	BOOL						Resume					(void);
	BOOL						Terminate				(DWORD dwExitCode) const;
	BOOL						Terminate				(DWORD dwTimeout, DWORD dwExitCode); 

public:
	// attributes
	DWORD						GetSuspendCount			(void);
	LPCTSTR						GetName					(void);
	void						SetName					(LPCTSTR pszName);
	BOOL						IsRunning				(void);
	BOOL						IsThis					(void);

protected:
	// overridables
	virtual BOOL				PreCreateThread			(BOOL &bSuspended, UINT &uStackSize, LPSECURITY_ATTRIBUTES &lpThreadAttributes);
	virtual BOOL				OnInitThread			(void);
	virtual UINT				OnRunThread				(void);
	virtual void				OnExitThread			(BOOL bRegularExit);
	virtual void				OnQueryThreadTermination(void);
	virtual BOOL				OnHardThreadTermination	(void);

private:
	// internals
	void						CommonConstructor		(void);
	static unsigned __stdcall	WorkerThread			(void *pParam);
	unsigned					WorkerThread			();

private:
	// implementation
	UINT						m_uThreadID;
	TCHAR						m_szThreadName[YLB_MAX_THREADNAME];
	DWORD						m_dwSuspendCount;
	DWORD						m_dwExitCode;
	YCriticalSection			m_csControl;
	YFlags						m_flags;
};

#ifdef YLB_ENABLE_INLINE
#include "yThread.inl"
#endif

#endif //__yThread_h__

//
// EoF
////////