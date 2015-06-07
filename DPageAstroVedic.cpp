// DPageToday.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "DPageAstroVedic.h"
#include "showset.h"
#include "GCDisplaySettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DPageToday property page

IMPLEMENT_DYNCREATE(DPageToday, CPropertyPage)

DPageToday::DPageToday() : CPropertyPage(DPageToday::IDD)
{
	//{{AFX_DATA_INIT(DPageToday)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

DPageToday::~DPageToday()
{
}

void DPageToday::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DPageToday)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DPageToday, CPropertyPage)
	//{{AFX_MSG_MAP(DPageToday)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DPageToday message handlers

void DPageToday::OnOK() 
{
	CPropertyPage::OnOK();
}

BOOL DPageToday::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	CheckDlgButton(IDC_CHECK1, GCDisplaySettings::getValue(29));
	CheckDlgButton(IDC_CHECK2, GCDisplaySettings::getValue(30));
	CheckDlgButton(IDC_CHECK3, GCDisplaySettings::getValue(31));
	CheckDlgButton(IDC_CHECK4, GCDisplaySettings::getValue(32));
	CheckDlgButton(IDC_CHECK5, GCDisplaySettings::getValue(33));
	CheckDlgButton(IDC_CHECK6, GCDisplaySettings::getValue(45));
	CheckDlgButton(IDC_CHECK7, GCDisplaySettings::getValue(46));
	CheckDlgButton(IDC_CHECK8, GCDisplaySettings::getValue(47));
	
	return CPropertyPage::OnSetActive();
}

BOOL DPageToday::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	GCDisplaySettings::setValue(29, IsDlgButtonChecked(IDC_CHECK1));
	GCDisplaySettings::setValue(30, IsDlgButtonChecked(IDC_CHECK2));
	GCDisplaySettings::setValue(31, IsDlgButtonChecked(IDC_CHECK3));
	GCDisplaySettings::setValue(32, IsDlgButtonChecked(IDC_CHECK4));
	GCDisplaySettings::setValue(33, IsDlgButtonChecked(IDC_CHECK5));
	GCDisplaySettings::setValue(45, IsDlgButtonChecked(IDC_CHECK6));
	GCDisplaySettings::setValue(46, IsDlgButtonChecked(IDC_CHECK7));
	GCDisplaySettings::setValue(47, IsDlgButtonChecked(IDC_CHECK8));
	
	return CPropertyPage::OnKillActive();
}
