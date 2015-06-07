// DNewCountry.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "DNewCountry.h"
#include "TCountry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DNewCountry dialog


DNewCountry::DNewCountry(CWnd* pParent /*=NULL*/)
	: CDialog(DNewCountry::IDD, pParent)
{
	//{{AFX_DATA_INIT(DNewCountry)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DNewCountry::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DNewCountry)
	DDX_Control(pDX, IDC_COMBO1, m_wCont);
	DDX_Control(pDX, IDC_EDIT2, m_wName);
	DDX_Control(pDX, IDC_EDIT1, m_wCode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DNewCountry, CDialog)
	//{{AFX_MSG_MAP(DNewCountry)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DNewCountry message handlers

void DNewCountry::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString str;
	WORD w = 0xffff;
	int bAllow = 0;

	m_wCode.GetWindowText(str);

	if (str.GetLength() == 2)
	{
		w = (WORD)((BYTE)(str.GetAt(1) - 'A')) + (WORD)(((BYTE)(str.GetAt(1) - 'A'))<<8);
		bAllow = (strlen(TCountry::GetCountryName(w))==0);
	}

	GetDlgItem(IDOK)->EnableWindow(bAllow);
	m_wName.EnableWindow(bAllow);
}

void DNewCountry::OnOK() 
{
	// TODO: Add extra validation here
	m_wCode.GetWindowText(strCode);
	m_wName.GetWindowText(strName);
	nContinent = m_wCont.GetCurSel();
	
	CDialog::OnOK();
}

BOOL DNewCountry::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	for(int i = 0; i < 8; i++)
		m_wCont.AddString(TCountry::gcontinents[i]);
	m_wCont.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
