// DlgAskLimitation.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "DlgAskLimitation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgAskLimitation dialog


DlgAskLimitation::DlgAskLimitation(CWnd* pParent /*=NULL*/)
	: CDialog(DlgAskLimitation::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgAskLimitation)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgAskLimitation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgAskLimitation)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgAskLimitation, CDialog)
	//{{AFX_MSG_MAP(DlgAskLimitation)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgAskLimitation message handlers
