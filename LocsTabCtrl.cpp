// LocsTabCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "LocsTabCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLocsTabCtrl

CLocsTabCtrl::CLocsTabCtrl()
{
}

CLocsTabCtrl::~CLocsTabCtrl()
{
}


BEGIN_MESSAGE_MAP(CLocsTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CLocsTabCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLocsTabCtrl message handlers

BOOL CLocsTabCtrl::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	GetParent()->SendMessage(WM_COMMAND, wParam, lParam);	
	return CTabCtrl::OnCommand(wParam, lParam);
}
