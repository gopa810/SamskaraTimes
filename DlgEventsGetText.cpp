// DlgEventsGetText.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "DlgEventsGetText.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgEventsGetText dialog


DlgEventsGetText::DlgEventsGetText(CWnd* pParent /*=NULL*/)
	: CDialog(DlgEventsGetText::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgEventsGetText)
	m_strText = _T("");
	//}}AFX_DATA_INIT
}


void DlgEventsGetText::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgEventsGetText)
	DDX_Text(pDX, IDC_EDIT1, m_strText);
	DDV_MaxChars(pDX, m_strText, 39);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgEventsGetText, CDialog)
	//{{AFX_MSG_MAP(DlgEventsGetText)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgEventsGetText message handlers
