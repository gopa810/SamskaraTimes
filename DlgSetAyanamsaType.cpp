// DlgSetAyanamsaType.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "DlgSetAyanamsaType.h"
#include "GCAyanamsha.h"
#include "GCSankranti.h"
#include "GCDisplaySettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgSetAyanamsaType dialog


DlgSetAyanamsaType::DlgSetAyanamsaType(CWnd* pParent /*=NULL*/)
	: CDialog(DlgSetAyanamsaType::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgSetAyanamsaType)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgSetAyanamsaType::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgSetAyanamsaType)
	DDX_Control(pDX, IDC_LIST2, m_san);
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DlgSetAyanamsaType, CDialog)
	//{{AFX_MSG_MAP(DlgSetAyanamsaType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgSetAyanamsaType message handlers

BOOL DlgSetAyanamsaType::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_list.AddString(GCAyanamsha::GetAyanamsaName(0));
	m_list.AddString(GCAyanamsha::GetAyanamsaName(1));
	m_list.AddString(GCAyanamsha::GetAyanamsaName(2));
	m_list.AddString(GCAyanamsha::GetAyanamsaName(3));

	m_list.SetCurSel(GCAyanamsha::GetAyanamsaType());

	m_san.AddString(GCSankranti::GetSankMethodName(0));
	m_san.AddString(GCSankranti::GetSankMethodName(1));
	m_san.AddString(GCSankranti::GetSankMethodName(2));
	m_san.AddString(GCSankranti::GetSankMethodName(3));

	m_san.SetCurSel(GCSankranti::GetSankrantiType());

	CheckDlgButton(IDC_CHECK1, GCDisplaySettings::getValue(44));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgSetAyanamsaType::OnOK() 
{
	GCAyanamsha::SetAyanamsaType(m_list.GetCurSel());
	GCSankranti::SetSankrantiType(m_san.GetCurSel());
	GCDisplaySettings::setValue(44, IsDlgButtonChecked(IDC_CHECK1));

	CDialog::OnOK();
}
