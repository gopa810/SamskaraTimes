// DlgSetPrintStyle.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "DlgSetPrintStyle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgSetPrintStyle dialog


DlgSetPrintStyle::DlgSetPrintStyle(CWnd* pParent /*=NULL*/)
	: CDialog(DlgSetPrintStyle::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgSetPrintStyle)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgSetPrintStyle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgSetPrintStyle)
	DDX_Control(pDX, IDC_EDIT5, m_wndBottom);
	DDX_Control(pDX, IDC_EDIT4, m_wndRight);
	DDX_Control(pDX, IDC_EDIT3, m_wndLeft);
	DDX_Control(pDX, IDC_EDIT2, m_wndTop);
	DDX_Control(pDX, IDC_EDIT1, m_wndFontName);
	DDX_Control(pDX, IDC_COMBO2, m_cbSizeHdr);
	DDX_Control(pDX, IDC_COMBO1, m_cbSizeText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgSetPrintStyle, CDialog)
	//{{AFX_MSG_MAP(DlgSetPrintStyle)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FONT, OnButtonSelectFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgSetPrintStyle message handlers

void DlgSetPrintStyle::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_STATIC1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);
	
}

void DlgSetPrintStyle::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_STATIC2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
	
}

//int sizes[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26};

BOOL DlgSetPrintStyle::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
	OnRadio1();

	m_nStyle = 0;

	m_nFontSize = 11;
	m_nHeaderSize = 18;
	m_strFont = "Tahoma";

	int i;
	TString str;

	for(i = 0; i < 20; i++)
	{
		str.Format("%d", i + 5);
		m_cbSizeText.AddString(str);
		m_cbSizeHdr.AddString(str);
	}

	m_cbSizeText.SetCurSel(m_nFontSize - 5);
	m_cbSizeHdr.SetCurSel(m_nHeaderSize - 5);

	m_wndFontName.SetWindowText(m_strFont);

	SetDlgItemInt(IDC_EDIT2, m_margins.top, FALSE);
	SetDlgItemInt(IDC_EDIT3, m_margins.left, FALSE);
	SetDlgItemInt(IDC_EDIT4, m_margins.right, FALSE);
	SetDlgItemInt(IDC_EDIT5, m_margins.bottom, FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgSetPrintStyle::OnButtonSelectFont() 
{
	// TODO: Add your control notification handler code here
	CFontDialog cfd;
	
	cfd.m_cf.Flags |= ( CF_NOSTYLESEL | CF_NOSIZESEL);

	if (cfd.DoModal() == IDOK)
	{
		m_strFont = cfd.GetFaceName();
		m_wndFontName.SetWindowText(m_strFont);
	}
}

void DlgSetPrintStyle::OnOK() 
{
	m_nHeaderSize = m_cbSizeHdr.GetCurSel() + 5;
	m_nFontSize = m_cbSizeText.GetCurSel() + 5;

	m_margins.top = GetDlgItemInt(IDC_EDIT2, NULL, FALSE);
	m_margins.left = GetDlgItemInt(IDC_EDIT3, NULL, FALSE);
	m_margins.right = GetDlgItemInt(IDC_EDIT4, NULL, FALSE);
	m_margins.bottom = GetDlgItemInt(IDC_EDIT5, NULL, FALSE);

	CDialog::OnOK();
}
