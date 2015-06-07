// DlgEditString.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "DlgEditString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgEditString dialog


DlgEditString::DlgEditString(CWnd* pParent /*=NULL*/)
	: CDialog(DlgEditString::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgEditString)
	m_orig = _T("");
	m_new = _T("");
	//}}AFX_DATA_INIT
}


void DlgEditString::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgEditString)
	DDX_Text(pDX, IDC_EDIT1, m_orig);
	DDX_Text(pDX, IDC_EDIT2, m_new);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgEditString, CDialog)
	//{{AFX_MSG_MAP(DlgEditString)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgEditString message handlers
