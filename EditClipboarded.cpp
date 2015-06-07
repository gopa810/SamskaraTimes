// EditClipboarded.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "EditClipboarded.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditClipboarded

CEditClipboarded::CEditClipboarded()
{
	m_bKeyCtrl = FALSE;
	m_bKeyShift = FALSE;
}

CEditClipboarded::~CEditClipboarded()
{
}


BEGIN_MESSAGE_MAP(CEditClipboarded, CEdit)
	//{{AFX_MSG_MAP(CEditClipboarded)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditClipboarded message handlers

void CEditClipboarded::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar)
	{
	case VK_CONTROL:
		m_bKeyCtrl = TRUE;
		break;
	case VK_SHIFT:
		m_bKeyShift = TRUE;
		break;
	case 'C':
	case 'X':
		if (m_bKeyCtrl == TRUE)
		{
			GetParent()->GetParent()->SendMessage(WM_COMMAND, ID_EDIT_COPY);
		}
		break;
	case 'P':
		if (m_bKeyCtrl == TRUE)
		{
			GetParent()->GetParent()->SendMessage(WM_COMMAND, ID_FILE_PRINT);
		}
		break;
	default:
		break;
	}
	
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CEditClipboarded::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar)
	{
	case VK_CONTROL:
		m_bKeyCtrl = FALSE;
		break;
	case VK_SHIFT:
		m_bKeyShift = FALSE;
		break;
	default:
		break;
	}
	
	CEdit::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CEditClipboarded::OnSetFocus(CWnd* pOldWnd) 
{
	CEdit::OnSetFocus(pOldWnd);
	
	m_bKeyCtrl = FALSE;
	m_bKeyShift = FALSE;

//	GetParent()->GetParent()->SetFocus();
}
