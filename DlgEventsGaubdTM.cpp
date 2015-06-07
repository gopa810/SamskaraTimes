// DlgEventsGaubdTM.cpp : implementation file
//

#include "stdafx.h"
#include "platform.h"
#include "vcal5beta.h"
#include "DlgEventsGaubdTM.h"
#include "vedic_ui.h"
#include "GCStrings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgEventsGaubdTM dialog


DlgEventsGaubdTM::DlgEventsGaubdTM(CWnd* pParent /*=NULL*/)
	: CDialog(DlgEventsGaubdTM::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgEventsGaubdTM)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nRetCancel = 0;
}


void DlgEventsGaubdTM::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgEventsGaubdTM)
	DDX_Control(pDX, IDC_STATIC2, m_s2);
	DDX_Control(pDX, IDC_STATIC1, m_s1);
	DDX_Control(pDX, IDC_LIST2, m_list2);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgEventsGaubdTM, CDialog)
	//{{AFX_MSG_MAP(DlgEventsGaubdTM)
	ON_BN_CLICKED(IDC_BUTTON1, OnBack)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgEventsGaubdTM message handlers

void DlgEventsGaubdTM::OnOK() 
{
	// TODO: Add extra validation here
	int i, n;

	i = m_list1.GetCurSel();
	if (i == LB_ERR)
	{
		CDialog::OnCancel();
		return;
	}
	n = m_list1.GetItemData(i);
	if (n == -1)
	{
		MessageBox("You should choose particular tithi, not only paksa in first listbox.", "Invalid selction in listbox 1", MB_OK);
		return;
	}

	m_nTithi = n;

	i = m_list2.GetCurSel();
	if (i == LB_ERR)
	{
		CDialog::OnCancel();
		return;
	}
	n = m_list2.GetItemData(i);
	if (n == -1)
	{
		CDialog::OnCancel();
		return;
	}

	m_nMasa = n;
	
	CDialog::OnOK();
}

BOOL DlgEventsGaubdTM::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int i = 0, n;
	TString str;

	str.Format("%s Paksa", GCStrings::GetPaksaName(0));
	i = m_list1.AddString(str);
	m_list1.SetItemData(i, -1);
	
	for(n = 0; n < 15; n++)
	{
		str.Format("     %s Tithi", GCStrings::GetTithiName(n));
		i = m_list1.AddString(str);
		m_list1.SetItemData(i, n);
	}

	str.Format("%s Paksa", GCStrings::GetPaksaName(1));
	i = m_list1.AddString(str);
	m_list1.SetItemData(i, -1);

	for(n = 15; n < 30; n++)
	{
		str.Format("     %s Tithi", GCStrings::GetTithiName(n));
		i = m_list1.AddString(str);
		m_list1.SetItemData(i, n);
	}

	for(n = 0; n < 12; n++)
	{
		str.Format(" %s Masa", GCStrings::GetMasaName((n + 11)%12));
		i = m_list2.AddString(str);
		m_list2.SetItemData(i, (n + 11)%12);
	}

	m_list1.SetCurSel(1);
	m_list2.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgEventsGaubdTM::OnBack() 
{
	// TODO: Add your control notification handler code here
	m_nRetCancel = 1;

	CDialog::OnCancel();	
}
