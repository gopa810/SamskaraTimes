// RichEditResults.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "RichEditResults.h"
#include "FrameMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRichEditResults

CRichEditResults::CRichEditResults()
{
	m_bShift = FALSE;
	m_bCtrl = FALSE;
}

CRichEditResults::~CRichEditResults()
{
}

int AvcOneStepBack(CFrameMain *);


BEGIN_MESSAGE_MAP(CRichEditResults, CRichEditCtrl)
	//{{AFX_MSG_MAP(CRichEditResults)
	ON_WM_KEYUP()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRichEditResults message handlers


BOOL CRichEditResults::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
/*	switch (LOWORD(wParam))
	{
	case ID_CALCULATE_APPEARANCEDAY:
	case ID_CALCULATE_CALENDAR:
	case ID_CALCULATE_MASALIST:
	case ID_CALCULATE_EVENTS:
	case ID_FIND_MHD:
	case ID_CALCULATE_PREVIOUSDAY:
	case ID_CALCULATE_TODAY:
		case ID_CALCULATE_*/
		//GetParent()->PostMessage(WM_COMMAND, wParam, lParam);
/*		break;
	default:
		break;
	}
*/	
	return CRichEditCtrl::OnCommand(wParam, lParam);
}

DWORD CALLBACK RichEditResults_Callback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	CRichEditResults * pWnd = (CRichEditResults *)dwCookie;
	if (pWnd == NULL)
		return 1;
	int nLen = pWnd->m_pReadString->GetLength();
	int nBottom = pWnd->m_nCookie;

	*pcb = nLen - nBottom;
	if (*pcb > cb) *pcb = cb;
	memcpy(pbBuff, pWnd->m_pReadString->c_str()+nBottom, *pcb);
	pWnd->m_nCookie += *pcb;
	return 0;
}

int CRichEditResults::SetTextRtf(TString * str)
{
	EDITSTREAM es;

	m_nCookie = 0;
	m_pReadString = str;

	es.dwCookie = (DWORD)this;
	es.dwError = 0;
	es.pfnCallback = RichEditResults_Callback;

	StreamIn(SF_RTF, es);

	m_nCookie = 0;

	return 1;
}

LRESULT CRichEditResults::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (message == WM_COMMAND)
	{
		GetParent()->PostMessage(message, wParam, lParam);
	}
	
	return CRichEditCtrl::WindowProc(message, wParam, lParam);
}

void CRichEditResults::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	// TODO: Add your message handler code here and/or call default
	switch(nChar)
	{
	case VK_CONTROL:
		m_bCtrl = FALSE;
		break;
	case VK_SHIFT:
		m_bShift = FALSE;
		break;
	default:
		break;
	}
	
	CRichEditCtrl::OnKeyUp(nChar, nRepCnt, nFlags);
}

CFrameMain * CRichEditResults::Getparent()
{
	return (CFrameMain *)(this->GetParent());
}

void CRichEditResults::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar)
	{
	case VK_CONTROL:
		m_bCtrl = TRUE;
		break;
	case VK_SHIFT:
		m_bShift = TRUE;
		break;
	case VK_F11:
		if (m_bShift && m_bCtrl)
		{
			Getparent()->OnSettingsAyanamsavalue();
		}
		break;
	case VK_F9:
		Getparent()->OnCalculateAppearanceday();
		break;
	case VK_BACK:
		if (m_bCtrl == TRUE)
		{
			AvcOneStepBack(Getparent());
		}
		break;
	case 'E':
		if (m_bCtrl == TRUE)
			Getparent()->OnCalculateEvents();
		break;
	case 'M':
		if (m_bCtrl == TRUE)
			Getparent()->OnCalculateMasalisting();
		break;
	case 'F':
		if (m_bCtrl == TRUE)
			Getparent()->OnToolsFindMhd();
		break;
	case VK_F5:
		// prev tithi
		Getparent()->OnCalculatePreviousday();
		break;
	case VK_F6:
		Getparent()->OnCalculateToday();
		break;
	case VK_F7:
		// calculate next day
		Getparent()->OnCalculateNextday();
		break;
	case VK_F8:
		if (m_bShift && m_bCtrl)
		{
			Getparent()->OnSpecialCommand();
		}
		else
		{
			Getparent()->OnCalculateCalendar();
		}
		break;
	case 'A':
		if (m_bCtrl == TRUE)
			Getparent()->OnEditSelectall();
		break;
	case 'C':
		if (m_bCtrl == TRUE)
			Getparent()->OnEditCopy();
		break;
	default:
		break;
	}
	
	CRichEditCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}
