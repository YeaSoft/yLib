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
 * FILENAME		:	Sample1.cpp
 * PURPOSE		:	yLib application sample
 * SCOPE		:	yLib SDK
 * HISTORY		: =============================================================
 * 
 * $Log$
 * Revision 1.1  2000/05/26  14:07:26  leo
 * Initial revision
 *
 *============================================================================*/

#include "StdAfc.h"
#include "Sample1.h"

/*=============================================================================
 * INSTANTIATE
 *============================================================================*/
Sample1				theApp;

/*=============================================================================
 * OUR COMMANDLINE PARSER
 *============================================================================*/
const DWORD CMyCliParser::CMD_WANTSHELP		= 0x00000001;
const DWORD CMyCliParser::CMD_UNKNOWN		= 0x00000002;


const DWORD CMyCliParser::CMD_EVTINSTALL	= 0x00000004;
const DWORD CMyCliParser::CMD_EVTREMOVE		= 0x00000008;
const DWORD CMyCliParser::CMD_EVTTEST1		= 0x00000010;
const DWORD CMyCliParser::CMD_EVTTEST2		= 0x00000020;
const DWORD CMyCliParser::CMD_EVTTEST3		= 0x00000040;
const DWORD CMyCliParser::CMD_ENUMSVC		= 0x00000080;
const DWORD CMyCliParser::CMD_THREADTEST1	= 0x00000100;
const DWORD CMyCliParser::CMD_THREADTEST2	= 0x00000200;
const DWORD CMyCliParser::CMD_NPSERVER		= 0x00000400;
const DWORD CMyCliParser::CMD_NPCLIENT		= 0x00000800;
const DWORD CMyCliParser::CMD_MSSERVER		= 0x00001000;
const DWORD CMyCliParser::CMD_MSCLIENT		= 0x00002000;
const DWORD CMyCliParser::CMD_TEXTTO		= 0x00004000;

const DWORD CMyCliParser::CMD_ACTIVITY_MASK	= 0xfffffffc;

BOOL CMyCliParser::OnProcessOption (BOOL &bTerminate, LPCTSTR &pszOptString, YCmdLineOption &cliOpt)
{
	// we support no options
	return YCmdLineParser::OnProcessOption (bTerminate, pszOptString, cliOpt);
}

BOOL CMyCliParser::OnProcessParam (BOOL &bTerminate, YCmdLineParam &cliPar)
{
	if ( YCmdLineParser::OnProcessParam (bTerminate, cliPar) ) {
		return TRUE;
	}
	if ( !_tcsicmp (cliPar.m_pszParam, _T("help")) ) {
		SetCommandFlags (CMD_WANTSHELP);
	}
	else if ( !_tcsicmp (cliPar.m_pszParam, _T("EvtInstall")) ) {
		SetCommandFlags (CMD_EVTINSTALL);
	}
	else if ( !_tcsicmp (cliPar.m_pszParam, _T("EvtRemove")) ) {
		SetCommandFlags (CMD_EVTREMOVE);
	}
	else if ( !_tcsicmp (cliPar.m_pszParam, _T("EvtTest1")) ) {
		// remember since it gets parameters
		cliPar.m_dwMeaning	= CMD_EVTTEST1;
		SetCommandFlags (CMD_EVTTEST1);
		return TRUE;
	}
	else if ( !_tcsicmp (cliPar.m_pszParam, _T("EvtTest2")) ) {
		// remember since it gets parameters
		cliPar.m_dwMeaning	= CMD_EVTTEST2;
		SetCommandFlags (CMD_EVTTEST2);
		return TRUE;
	}
	else if ( !_tcsicmp (cliPar.m_pszParam, _T("EvtTest3")) ) {
		// remember since it gets parameters
		cliPar.m_dwMeaning	= CMD_EVTTEST3;
		SetCommandFlags (CMD_EVTTEST3);
		return TRUE;
	}
	else if ( !_tcsicmp (cliPar.m_pszParam, _T("SvcEnum")) ) {
		SetCommandFlags (CMD_ENUMSVC);
	}
	else if ( !_tcsicmp (cliPar.m_pszParam, _T("RunThread1")) ) {
		return TRUE;
	}
	else if ( !_tcsicmp (cliPar.m_pszParam, _T("RunThread2")) ) {
		SetCommandFlags (CMD_THREADTEST2);
	}
	else if ( !_tcsicmp (cliPar.m_pszParam, _T("RunNPServer")) ) {
		// remember since it gets parameters
		cliPar.m_dwMeaning	= (DWORD) CMD_NPSERVER;
		SetCommandFlags (CMD_NPSERVER);
		return TRUE;
	}
	else if ( !_tcsicmp (cliPar.m_pszParam, _T("RunNPClient")) ) {
		// remember since it gets parameters
		cliPar.m_dwMeaning	= (DWORD) CMD_NPCLIENT;
		SetCommandFlags (CMD_NPCLIENT);
		return TRUE;
	}
	else if ( !_tcsicmp (cliPar.m_pszParam, _T("RunMSServer")) ) {
		// remember since it gets parameters
		cliPar.m_dwMeaning	= (DWORD) CMD_MSSERVER;
		SetCommandFlags (CMD_MSSERVER);
		return TRUE;
	}
	else if ( !_tcsicmp (cliPar.m_pszParam, _T("RunMSClient")) ) {
		// remember since it gets parameters
		cliPar.m_dwMeaning	= (DWORD) CMD_MSCLIENT;
		SetCommandFlags (CMD_MSCLIENT);
		return TRUE;
	}
	else if ( !_tcsicmp (cliPar.m_pszParam, _T("TextTo")) ) {
		// remember since it gets parameters
		cliPar.SetParamCount (1);
		cliPar.m_dwMeaning	= (DWORD) CMD_TEXTTO;
		SetCommandFlags (CMD_TEXTTO);
		return TRUE;
	}
	else {
		// unknown!
		SetCommandFlags (CMD_UNKNOWN);
	}

	// discard
	return FALSE;
}

/*=============================================================================
 * OUR SAMPLE APPLICATION
 *============================================================================*/
BOOL Sample1::InitInstance (YCommandLineInfo *cli)
{
	_tprintf (_T("\nThis is %s, the %s\n"), GetAppName (), GetAppDescription ());
	_tprintf (_T("(c) 2000 YEAsoft Int'l. All rights reserved.\n\n"));

	return TRUE;
}

void Sample1::Run ()
{
	CMyCliParser myParser;

	if ( myParser.GetCommands () & CMyCliParser::CMD_UNKNOWN ) {
		_tprintf (_T("ERROR: unknown command specified\n\n"));
		myParser.SetCommandFlags (CMyCliParser::CMD_WANTSHELP);
	}

	if ( myParser.TestCommandFlags (CMyCliParser::CMD_WANTSHELP) ) {
		ShowHelp ((DWORD) (myParser.GetCommands () & CMyCliParser::CMD_ACTIVITY_MASK));
		return;
	}

	switch ( myParser.GetCommands () & CMyCliParser::CMD_ACTIVITY_MASK ) {
	case CMyCliParser::CMD_EVTINSTALL:
		EvtInstall ();
		break;
	case CMyCliParser::CMD_EVTREMOVE:
		EvtRemove ();
		break;
	case CMyCliParser::CMD_EVTTEST1:
		EvtTest1 (myParser.FindParamByMeaning (CMyCliParser::CMD_EVTTEST1));
		break;
	case CMyCliParser::CMD_EVTTEST2:
		EvtTest2 (myParser.FindParamByMeaning (CMyCliParser::CMD_EVTTEST2));
		break;
	case CMyCliParser::CMD_EVTTEST3:
		EvtTest3 (myParser.FindParamByMeaning (CMyCliParser::CMD_EVTTEST3));
		break;
	case CMyCliParser::CMD_ENUMSVC:
		SvcEnumReg ();
		break;
	case CMyCliParser::CMD_THREADTEST1:
		RunThread1 ();
		break;
	case CMyCliParser::CMD_THREADTEST2:
		RunThread2 ();
		break;
	case CMyCliParser::CMD_NPSERVER:
		RunNPServer (myParser.FindParamByMeaning (CMyCliParser::CMD_NPSERVER));
		break;
	case CMyCliParser::CMD_NPCLIENT:
		RunNPClient (myParser.FindParamByMeaning (CMyCliParser::CMD_NPCLIENT));
		break;
	case CMyCliParser::CMD_MSSERVER:
		RunMSServer (myParser.FindParamByMeaning (CMyCliParser::CMD_MSSERVER));
		break;
	case CMyCliParser::CMD_MSCLIENT:
		RunMSClient (myParser.FindParamByMeaning (CMyCliParser::CMD_MSCLIENT));
		break;
	case CMyCliParser::CMD_TEXTTO:
		TextTo (myParser.FindParamByMeaning (CMyCliParser::CMD_TEXTTO));
		break;
	default:
		// more than one command specified
		_tprintf (_T("ERROR: illegal combination of commands specified\n\n"));
		// intended...
	case 0:
		// no command specified
		ShowHelp ((DWORD) (myParser.GetCommands () & CMyCliParser::CMD_ACTIVITY_MASK));
		break;
	}
}

void Sample1::TextTo (YCmdLineParam *cliPar)
{
	SetReturnCode (-1);
	if ( !cliPar ) {
		_tprintf (_T("ERROR: No parameters\n"));
		return;
	}
	if ( cliPar->GetParamCount () != 1 ) {
		_tprintf (_T("ERROR: wrong param count\n"));
		return;
	}
	YPathString ysName = cliPar->GetAt (ZERO);
	if ( !ysName.IsFile () ) {
		_tprintf (_T("ERROR: source file not found\n"));
		return;
	}
	YPathString ysDest = ysName;
	ysDest.ReverseTerminateAfter (_T('.'));
	YString32 ysExt = ysName.GetFileExtension ();
	if ( ysExt.Right (2).Compare (_T("~v")) ) {
		_tprintf (_T("ERROR: bad extension '%s'\n"), (LPCTSTR) ysExt.Right (2));
		return;
	}
	ysExt.Replace (_T('~'), _T(','));
	ysDest += ysExt;

	YStdioFile	ysSrc, ysDst;
	YHeapString	ysBuffer;

	if ( !ysBuffer.Alloc (64*1024) ) {
		_tprintf (_T("ERROR: memory error\n"));
		return;
	}

	if ( !ysSrc.Open (ysName, YFile::modeRead|YFile::shareDenyWrite|YFile::typeText) ) {
		_tprintf (_T("ERROR: cant open source\n"));
		return;
	}
	if ( !ysDst.Open (ysDest, YFile::modeCreate|YFile::modeWrite|YFile::typeBinary) ) {
		_tprintf (_T("ERROR: cant create dest\n"));
		return;
	}
	while ( ysSrc.ReadString (ysBuffer) ) {
		ysDst.WriteString (ysBuffer);
	}
	SetReturnCode (0);
}


void Sample1::ShowHelp (DWORD dwCmd)
{
	switch ( dwCmd ) {
	case CMyCliParser::CMD_EVTINSTALL:
		_tprintf (_T("USAGE: sample1 evtInstall\n\n"));
		_tprintf (_T("       This command installs the sample application as\n"));
		_tprintf (_T("       an Event Source\n\n"));
		break;
	case CMyCliParser::CMD_EVTREMOVE:
		_tprintf (_T("USAGE: sample1 evtRemove\n\n"));
		_tprintf (_T("       This command uninstalls the sample application example as\n"));
		_tprintf (_T("       an Event Source\n\n"));
		break;
	case CMyCliParser::CMD_EVTTEST1:
		_tprintf (_T("USAGE: sample1 evtTest1 [UserName]\n\n"));
		_tprintf (_T("       This command post a simple message into the event log.\n"));
		_tprintf (_T("       If a valid NT username is specified, this user will\n"));
		_tprintf (_T("       be the originator of the event\n\n"));
		break;
	case CMyCliParser::CMD_EVTTEST2:
		_tprintf (_T("USAGE: sample1 evtTest2 [UserName]\n\n"));
		_tprintf (_T("       This command post a message with 1 parameter into the event log.\n"));
		_tprintf (_T("       If a valid NT username is specified, this user will\n"));
		_tprintf (_T("       be the originator of the event\n\n"));
		break;
	case CMyCliParser::CMD_EVTTEST3:
		_tprintf (_T("USAGE: sample1 evtTest3 [UserName]\n\n"));
		_tprintf (_T("       This command post a message with 3 parameters into the event log.\n"));
		_tprintf (_T("       The first two parameters are not specified in the posting routine, but are\n"));
		_tprintf (_T("       predefined for the entire eventlog object.\n"));
		_tprintf (_T("       If a valid NT username is specified, this user will\n"));
		_tprintf (_T("       be the originator of the event\n\n"));
		break;
	case CMyCliParser::CMD_ENUMSVC:
		_tprintf (_T("USAGE: sample1 svcEnum\n\n"));
		_tprintf (_T("       This command enumerates all services by walking through\n"));
		_tprintf (_T("       the registry\n\n"));
		break;
	case CMyCliParser::CMD_THREADTEST1:
		_tprintf (_T("USAGE: sample1 RunThread1\n\n"));
		_tprintf (_T("       This command starts a thread that will be gracefully terminated\n"));
		_tprintf (_T("       from outside after 10 seconds. It illustrates also the use\n"));
		_tprintf (_T("       of yLibs synchronisation objects\n\n"));
		break;
	case CMyCliParser::CMD_THREADTEST2:
		_tprintf (_T("USAGE: sample1 RunThread2\n\n"));
		_tprintf (_T("       This command start three threads and shows how simple\n"));
		_tprintf (_T("       synchronisation works across different threads.\n"));
		_tprintf (_T("       \n\n"));
		break;
	case CMyCliParser::CMD_NPSERVER:
		_tprintf (_T("USAGE: sample1 RunNPServer [LifeTime]\n\n"));
		_tprintf (_T("       This command starts a named pipe server that stays alive for the\n"));
		_tprintf (_T("       specified time (in seconds) or 30 seconds if nothing is specified.\n"));
		_tprintf (_T("       The named pipe server will echo on the console the data sent by\n"));
		_tprintf (_T("       client transactions.\n"));
		_tprintf (_T("       \n\n"));
		break;
	case CMyCliParser::CMD_NPCLIENT:
		_tprintf (_T("USAGE: sample1 RunNPClient [[ComputerName] param ...]\n\n"));
		_tprintf (_T("       This command sends each param to the computer specified via a named pipe\n"));
		_tprintf (_T("       transaction. If no ComputerName is specified, a test string will be sent\n"));
		_tprintf (_T("       to a pipe server on the local machine. If a ComputerName is specified\n"));
		_tprintf (_T("       but no params, a test string will be sent.\n"));
		_tprintf (_T("       \n\n"));
		break;
	case CMyCliParser::CMD_MSSERVER:
		_tprintf (_T("USAGE: sample1 RunMSServer [LifeTime]\n\n"));
		_tprintf (_T("       This command starts a mailslot server that stays alive for the\n"));
		_tprintf (_T("       specified time (in seconds) or 30 seconds if nothing is specified.\n"));
		_tprintf (_T("       The mailslot server will echo on the console the data sent by\n"));
		_tprintf (_T("       client applications.\n"));
		_tprintf (_T("       \n\n"));
		break;
	case CMyCliParser::CMD_MSCLIENT:
		_tprintf (_T("USAGE: sample1 RunMSClient [[<ComputerName>|<*>] param ...]\n\n"));
		_tprintf (_T("       This command sends each param to the computer specified via a mailslot\n"));
		_tprintf (_T("       message. If no ComputerName is specified, a test string will be sent\n"));
		_tprintf (_T("       to a mailslot server on the local machine. If a ComputerName is specified\n"));
		_tprintf (_T("       but no params, a test string will be sent. '*' sends to all computers in\n"));
		_tprintf (_T("       the domain\n"));
		_tprintf (_T("       \n\n"));
		break;

	default:
		_tprintf (_T("USAGE: sample1 <cmd>\n\n"));
		_tprintf (_T("       where <cmd> can be:\n"));
		_tprintf (_T("       evtInstall       Registers the app within the event log service\n"));
		_tprintf (_T("       evtRemove        Unregisters the app from the event log service\n"));
		_tprintf (_T("       evtTest1         writes a test message into the event log\n"));
		_tprintf (_T("       evtTest2         writes a test message into the event log\n"));
		_tprintf (_T("       evtTest3         writes a test message into the event log\n"));
		_tprintf (_T("       svcEnum          enumerates all services from the registry\n"));
		_tprintf (_T("       runThread1       runs the simple thread example\n"));
		_tprintf (_T("       runThread2       runs the synchronisation thread example\n"));
		_tprintf (_T("       runNPServer      runs a named pipe server that shows the received msgs\n"));
		_tprintf (_T("       runNPClient      runs a named pipe client that sends all parameters\n"));
		_tprintf (_T("       runMSServer      runs a mailslot server that shows the received msgs\n"));
		_tprintf (_T("       runMSClient      runs a mailslot client that sends all parameters\n"));
		_tprintf (_T("\n"));
		break;
	}
}

//
// EoF
////////