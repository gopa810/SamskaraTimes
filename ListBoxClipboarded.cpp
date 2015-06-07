// ListBoxClipboarded.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "ListBoxClipboarded.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListBoxClipboarded

CListBoxClipboarded::CListBoxClipboarded()
{
	m_bKeyCtrl = FALSE;
	m_bKeyShift = FALSE;
}

CListBoxClipboarded::~CListBoxClipboarded()
{
}


BEGIN_MESSAGE_MAP(CListBoxClipboarded, CListBox)
	//{{AFX_MSG_MAP(CListBoxClipboarded)
	ON_WM_SETFOCUS()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListBoxClipboarded message handlers

void CListBoxClipboarded::OnSetFocus(CWnd* pOldWnd) 
{
	CListBox::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	m_bKeyCtrl = FALSE;
	m_bKeyShift = FALSE;

//	GetParent()->GetParent()->SetFocus();
	
}

void CListBoxClipboarded::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
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
	
	CListBox::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CListBoxClipboarded::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
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
	
	CListBox::OnKeyUp(nChar, nRepCnt, nFlags);
}
