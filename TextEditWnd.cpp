// TextEditWnd.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "TextEditWnd.h"
#include "FrameMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


int AvcOneStepBack(CFrameMain *);


/////////////////////////////////////////////////////////////////////////////
// CTextEditWnd

CTextEditWnd::CTextEditWnd()
{
	m_bKeyControl = FALSE;
}

CTextEditWnd::~CTextEditWnd()
{
}


BEGIN_MESSAGE_MAP(CTextEditWnd, CEdit)
	//{{AFX_MSG_MAP(CTextEditWnd)
	ON_COMMAND(ID_EDIT_CLEARSELECTION, OnEditClearselection)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_SELECTALL, OnEditSelectall)
	ON_COMMAND(ID_CALCULATE_APPEARANCEDAY, OnCalculateAppearanceday)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextEditWnd message handlers

BOOL CTextEditWnd::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	switch (LOWORD(wParam))
	{
	case ID_CALCULATE_APPEARANCEDAY:
		GetParent()->SendMessage(WM_COMMAND, wParam, lParam);
		break;
	default:
		break;
	}
	return CEdit::OnCommand(wParam, lParam);
}

void CTextEditWnd::OnEditClearselection() 
{
	// TODO: Add your command handler code here
	SetSel(-1, -1, TRUE);
}

void CTextEditWnd::OnEditCopy() 
{
	// TODO: Add your command handler code here
	Copy();	
}

void CTextEditWnd::OnEditSelectall() 
{
	// TODO: Add your command handler code here
	SetSel(0, -1, TRUE);
}

void CTextEditWnd::OnCalculateAppearanceday() 
{
	// TODO: Add your command handler code here
	GetParent()->SendMessage(WM_COMMAND, ID_CALCULATE_APPEARANCEDAY);
	
}

void CTextEditWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar)
	{
	case VK_CONTROL:
		m_bKeyControl = TRUE;
		break;
	case VK_SHIFT:
		m_bKeyShift = TRUE;
		break;
	case VK_BACK:
		if (m_bKeyControl == TRUE)
		{
			AvcOneStepBack((CFrameMain *)GetParent());
		}
		break;
	case VK_F11:
		if (m_bKeyShift && m_bKeyControl)
		{
			GetMyParent()->OnSettingsAyanamsavalue();
		}
		break;
	case 'A':
		if (m_bKeyControl == TRUE)
			OnEditSelectall();
		break;
	case 'C':
		if (m_bKeyControl == TRUE)
			OnEditCopy();
		break;
	case 'F':
		if (m_bKeyControl == TRUE)
			GetMyParent()->OnToolsFindMhd();
		break;
	case VK_F9:
		GetMyParent()->OnCalculateAppearanceday();
		break;
	case 'E':
		if (m_bKeyControl == TRUE)
			GetMyParent()->OnCalculateEvents();
		break;
	case 'M':
		if (m_bKeyControl == TRUE)
			GetMyParent()->OnCalculateMasalisting();
		break;
	case VK_F5:
		GetMyParent()->OnCalculatePreviousday();
		break;
	case VK_F6:
		GetMyParent()->OnCalculateToday();
		break;
	case VK_F7:
		GetMyParent()->OnCalculateNextday();
		break;
	case VK_F8:
		GetMyParent()->OnCalculateCalendar();
		break;

	default:
		break;
	}

	
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTextEditWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch(nChar)
	{
	case VK_CONTROL:
		m_bKeyControl = FALSE;
		break;
	case VK_SHIFT:
		m_bKeyShift = FALSE;
		break;
	default:
		break;
	}
	
	CEdit::OnKeyUp(nChar, nRepCnt, nFlags);
}

CFrameMain * CTextEditWnd::GetMyParent()
{
	return (CFrameMain *)GetParent();
}
