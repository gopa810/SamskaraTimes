// DlgEditCustomEvent.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "DlgEditCustomEvent.h"
#include "vedic_ui.h"
#include "GCStrings.h"
#include "GCDisplaySettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgEditCustomEvent dialog


DlgEditCustomEvent::DlgEditCustomEvent(CWnd* pParent /*=NULL*/)
	: CDialog(DlgEditCustomEvent::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgEditCustomEvent)
	m_nTithi = -1;
	m_nMasa = -1;
	m_strText = _T("");
	m_nClass = -1;
	m_nFastType = -1;
	m_strFastSubject = _T("");
	//}}AFX_DATA_INIT
}


void DlgEditCustomEvent::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgEditCustomEvent)
	DDX_CBIndex(pDX, IDC_COMBO1, m_nTithi);
	DDX_CBIndex(pDX, IDC_COMBO2, m_nMasa);
	DDX_Text(pDX, IDC_EDIT1, m_strText);
	DDV_MaxChars(pDX, m_strText, 80);
	DDX_CBIndex(pDX, IDC_COMBO3, m_nClass);
	DDX_CBIndex(pDX, IDC_COMBO4, m_nFastType);
	DDX_Text(pDX, IDC_EDIT2, m_strFastSubject);
	DDX_Text(pDX, IDC_EDIT3, m_strStartYear);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgEditCustomEvent, CDialog)
	//{{AFX_MSG_MAP(DlgEditCustomEvent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgEditCustomEvent message handlers

BOOL DlgEditCustomEvent::OnInitDialog() 
{
	CDialog::OnInitDialog();
	TString str;
	
// TODO: Add extra initialization here
	CComboBox * p;
	int i;

	p = (CComboBox *)GetDlgItem(IDC_COMBO1);
	for(i =0; i < 30; i++)
	{
		str.Format("%s Tithi (%s Paksa)", GCStrings::GetTithiName(i), GCStrings::GetPaksaName(i/15));
		p->AddString(str);
	}
	p->SetCurSel(this->m_nTithi);
	if (m_nClass != 6)
		p->EnableWindow(FALSE);

	p = (CComboBox *)GetDlgItem(IDC_COMBO2);
	for(i = 0; i < 12; i++)
	{
		p->AddString(GCStrings::GetMasaName(i));
	}
	p->SetCurSel(this->m_nMasa);
	if (m_nClass != 6)
		p->EnableWindow(FALSE);

	p = (CComboBox *)GetDlgItem(IDC_COMBO3);
	for(i = 0; i <= 6; i++)
	{
		p->AddString(GCStrings::GetEventClassText(i));
	}
	p->SetCurSel(this->m_nClass);
	if (m_nClass != 6)
		p->EnableWindow(FALSE);
	else
		p->EnableWindow(GCDisplaySettings::getValue(44)==1);
	
	p = (CComboBox *)GetDlgItem(IDC_COMBO4);
	p->AddString("no fast");
	p->AddString(GCStrings::GetFastingName(0x201));
	p->AddString(GCStrings::GetFastingName(0x202));
	p->AddString(GCStrings::GetFastingName(0x203));
	p->AddString(GCStrings::GetFastingName(0x204));
	p->AddString(GCStrings::GetFastingName(0x205));
	p->SetCurSel(this->m_nFastType);
	if (m_nClass != 6)
		p->EnableWindow(FALSE);

	if (m_nClass != 6)
		GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
