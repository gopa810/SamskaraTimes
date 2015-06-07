// DlgSelectLangOutput.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "DlgSelectLangOutput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern GCalApp theApp;

/////////////////////////////////////////////////////////////////////////////
// DlgSelectLangOutput dialog


DlgSelectLangOutput::DlgSelectLangOutput(CWnd* pParent /*=NULL*/)
	: CDialog(DlgSelectLangOutput::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgSelectLangOutput)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgSelectLangOutput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgSelectLangOutput)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgSelectLangOutput, CDialog)
	//{{AFX_MSG_MAP(DlgSelectLangOutput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

extern TLangFileList gLangList;

/////////////////////////////////////////////////////////////////////////////
// DlgSelectLangOutput message handlers

BOOL DlgSelectLangOutput::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int i;
	TLangFileInfo * p = gLangList.list;
	i = m_list.AddString("<default>");
	m_list.SetItemDataPtr(i, NULL);
	while(p)
	{
		i = m_list.AddString(p->m_strLang);
		m_list.SetItemDataPtr(i, p);
		p = p->next;
	}

	m_pfi = NULL;

	m_list.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgSelectLangOutput::OnOK() 
{
	m_pfi = (TLangFileInfo *)m_list.GetItemDataPtr( m_list.GetCurSel() );
	CDialog::OnOK();
}
