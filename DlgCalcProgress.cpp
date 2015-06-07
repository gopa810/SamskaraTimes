// DlgCalcProgress.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "DlgCalcProgress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgCalcProgress dialog


DlgCalcProgress::DlgCalcProgress(CWnd* pParent /*=NULL*/)
	: CDialog(DlgCalcProgress::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgCalcProgress)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgCalcProgress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgCalcProgress)
	DDX_Control(pDX, IDC_PROGRESS1, m_p1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgCalcProgress, CDialog)
	//{{AFX_MSG_MAP(DlgCalcProgress)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgCalcProgress message handlers
