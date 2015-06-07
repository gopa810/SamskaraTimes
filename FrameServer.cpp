// FrameServer.cpp: implementation of the CFrameServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "vcal5beta.h"
#include "FrameServer.h"
#include "GCStrings.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#include "strings.h"

extern GCalApp theApp;

CFrameServer theFrameServer;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFrameServer::CFrameServer()
{
	UnlockServer();
	m_mainIcon = NULL;
	m_pEvents = NULL;
	m_pFinder = NULL;
	m_pLocs = NULL;
	m_rectMain.SetRect(0,0,0,0);
	m_rectFind.SetRect(0,0,0,0);
}

CFrameServer::~CFrameServer()
{
/*
	pos = m_ArrFind.GetHeadPosition();
	while(pos)
	{
		prev = pos;
		f = m_ArrFind.GetNext(pos);
//		if (f->m_bClosed == FALSE)
//			f->CloseWindow();
		if (prev)
		{
			delete f;
			m_ArrFind.RemoveAt(prev);
		}
	}*/
}

CFrameMain * CFrameServer::CreateNewFrame()
{
	CFrameMain * pMainFrame = new CFrameMain;

	if (m_mainIcon == NULL)
		m_mainIcon = theApp.LoadIcon(IDR_MAINFRAME);

	if ((m_Arr.GetCount() == 0) && (m_rectMain.Width() > 80) && (m_rectMain.left >= 0) && (m_rectMain.top >= 0))
	{
		pMainFrame->Create(NULL, GCStrings::getString(131).c_str(), WS_OVERLAPPEDWINDOW, m_rectMain, 
			NULL, MAKEINTRESOURCE(IDR_MAINMENU), NULL, NULL);
	}
	else
	{
		pMainFrame->Create(NULL, GCStrings::getString(131).c_str(), WS_OVERLAPPEDWINDOW, CFrameWnd::rectDefault, 
			NULL, MAKEINTRESOURCE(IDR_MAINMENU), NULL, NULL);
	}
	

	pMainFrame->ShowWindow(SW_SHOW);

	if (m_bLocked == FALSE)
		m_Arr.AddTail( pMainFrame );

	return pMainFrame;
}

void CFrameServer::OnClose(CFrameMain *pFrame)
{
	CFrameMain * p;
	POSITION pos = m_Arr.GetHeadPosition();

	if (m_bLocked == TRUE)
		return;

	while(pos)
	{
		p = m_Arr.GetAt(pos);
		if (p == pFrame)
		{
			m_Arr.RemoveAt(pos);
			break;
		}
		else
		{
			m_Arr.GetNext(pos);
		}
	}

	if (m_Arr.GetCount() < 1)
	{
		CloseAllFinders();
		CloseAllLocs();
		CloseAllEventFrames();
//		theApp.ExitInstance();
		PostQuitMessage(0);
	}

}

void CFrameServer::LockServer()
{
	m_bLocked = TRUE;
}

void CFrameServer::UnlockServer()
{
	m_bLocked = FALSE;
}

void CFrameServer::CloseAllWindows()
{
	LockServer();

	POSITION pos;//, prev;
	CFrameMain * p;

	pos = m_Arr.GetHeadPosition();
	while(pos)
	{
		p = m_Arr.GetNext(pos);
		p->CloseWindow();
	}


}

void CFrameServer::ChangeMainWindow(CFrameMain *pFrame)
{
	CFrameMain * p;
	POSITION pos = m_Arr.GetHeadPosition();

	while(pos)
	{
		p = m_Arr.GetAt(pos);
		if (p != pFrame)
		{
			theApp.m_pMainWnd = p;
			return;
		}
		m_Arr.GetNext(pos);
	}
}

void CFrameServer::CreateNewFindFrame()
{
	TString strTitle;

	if (m_pFinder == NULL)
	{
		m_pFinder = new CFrameFind;

		strTitle.Format("%s - Event Finder", GCStrings::getString(131).c_str());
		m_pFinder->Create( AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW, ::LoadCursor(NULL, IDC_ARROW), (HBRUSH)(COLOR_BTNFACE + 1), NULL)
			, strTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, CFrameWnd::rectDefault, 
			NULL, MAKEINTRESOURCE(IDR_FINDMENU), NULL, NULL);
		m_pFinder->SetIcon(m_mainIcon, FALSE);
		m_pFinder->UpdateWindow();
		m_pFinder->ShowWindow(SW_SHOW);
	}
	else
	{
		m_pFinder->SetFocus();
	}
}

void CFrameServer::CloseAllFinders()
{
	if (m_pFinder != NULL)
	{
		m_pFinder->DestroyWindow();
	}

	m_pFinder = NULL;
}

void CFrameServer::RemoveFromFinders()
{
	m_pFinder = NULL;

	CFrameMain * p;
	POSITION pos = m_Arr.GetHeadPosition();
	if (pos != NULL)
	{
		p = m_Arr.GetAt(pos);
		p->SetFocus();
		theApp.m_pMainWnd = p;
	}
}

void CFrameServer::CreateNewLocationFrame()
{
	TString strTitle;

	if (m_pLocs == NULL)
	{
		m_pLocs = new CFrameLocs;

		strTitle.Format("%s - Locations", GCStrings::getString(131).c_str());
		m_pLocs->Create( AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW, ::LoadCursor(NULL, IDC_ARROW), (HBRUSH)(COLOR_BTNFACE + 1), NULL)
			, strTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, CFrameWnd::rectDefault, 
			NULL, MAKEINTRESOURCE(IDR_LOCSMENU), NULL, NULL);
		m_pLocs->SetIcon(m_mainIcon, FALSE);
		m_pLocs->UpdateWindow();
		m_pLocs->ShowWindow(SW_SHOW);
	}
	else
	{
		m_pLocs->SetFocus();
	}

}

void CFrameServer::CloseAllLocs()
{
	if (m_pLocs != NULL)
	{
		m_pLocs->DestroyWindow();
	}
	m_pLocs = NULL;
}

void CFrameServer::RemoveFromLocs()
{
	m_pLocs = NULL;

	CFrameMain * p;
	POSITION pos = m_Arr.GetHeadPosition();
	if (pos != NULL)
	{
		p = m_Arr.GetAt(pos);
		p->SetFocus();
		theApp.m_pMainWnd = p;
	}
}

void CFrameServer::Initialize()
{

}

void CFrameServer::CreateNewEventsFrame()
{
	CString strTitle;

	if (m_pEvents != NULL)
	{
		m_pEvents->SetFocus();
		return;
	}

	m_pEvents = new CFrameEvents;
	strTitle.Format("%s - Events", GCStrings::getString(131).c_str());
	m_pEvents->Create( AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW, ::LoadCursor(NULL, IDC_ARROW), (HBRUSH)(COLOR_BTNFACE + 1), NULL)
		, strTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, CFrameWnd::rectDefault, 
		NULL, MAKEINTRESOURCE(IDR_EVENTSMENU), NULL, NULL);
	m_pEvents->SetIcon(m_mainIcon, FALSE);
	m_pEvents->UpdateWindow();
	m_pEvents->ShowWindow(SW_SHOW);
}

void CFrameServer::CloseAllEventFrames()
{
	if (m_pEvents != NULL)
	{
		m_pEvents->DestroyWindow();
	}
	m_pEvents = NULL;

}

void CFrameServer::RemoveFromEventFrames()
{
	m_pEvents = NULL;

	CFrameMain * p;
	POSITION pos = m_Arr.GetHeadPosition();
	if (pos != NULL)
	{
		p = m_Arr.GetAt(pos);
		p->SetFocus();
		theApp.m_pMainWnd = p;
	}
}

void CFrameServer::RecalculateAllTodayScreens()
{
	CFrameMain * p;
	POSITION pos = m_Arr.GetHeadPosition();

	while(pos)
	{
		p = m_Arr.GetNext(pos);
		p->RecalculateTodayScreen();
	}
}

void CFrameServer::UpdateAllEventFrames()
{
	if (m_pEvents != NULL)
	{
		m_pEvents->UpdateItemsCheckStatus();
		m_pEvents->UpdateItemsFasting();
	}
}
