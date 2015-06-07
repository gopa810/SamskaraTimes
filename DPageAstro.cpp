// DPageAstro.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "DPageAstro.h"
#include "showset.h"
#include "GCDisplaySettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DPageAstro property page

IMPLEMENT_DYNCREATE(DPageAstro, CPropertyPage)

DPageAstro::DPageAstro() : CPropertyPage(DPageAstro::IDD)
{
	//{{AFX_DATA_INIT(DPageAstro)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

DPageAstro::~DPageAstro()
{
}

void DPageAstro::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DPageAstro)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DPageAstro, CPropertyPage)
	//{{AFX_MSG_MAP(DPageAstro)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DPageAstro message handlers

void DPageAstro::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	CPropertyPage::OnOK();
}

BOOL DPageAstro::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	CheckDlgButton(IDC_CHECK1, GCDisplaySettings::getValue(2));
	CheckDlgButton(IDC_CHECK2, GCDisplaySettings::getValue(3));
	CheckDlgButton(IDC_CHECK3, GCDisplaySettings::getValue(9));
	CheckDlgButton(IDC_CHECK4, GCDisplaySettings::getValue(4));
	CheckDlgButton(IDC_CHECK5, GCDisplaySettings::getValue(5));
	CheckDlgButton(IDC_CHECK6, GCDisplaySettings::getValue(10));
	CheckDlgButton(IDC_CHECK7, GCDisplaySettings::getValue(34));
	CheckDlgButton(IDC_CHECK8, GCDisplaySettings::getValue(48));
	
	return CPropertyPage::OnSetActive();
}

BOOL DPageAstro::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	LPNMHDR lp = (LPNMHDR)lParam;

	if (lp->code == PSN_HELP)
	{
		MessageBox("This page allows to change the mode of display of the astronomical events in the calendar.", "Settings for Astronomy Display", MB_OK);
		return TRUE;
	}
	
	return CPropertyPage::OnNotify(wParam, lParam, pResult);
}

BOOL DPageAstro::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	GCDisplaySettings::setValue(2, IsDlgButtonChecked(IDC_CHECK1));
	GCDisplaySettings::setValue(3, IsDlgButtonChecked(IDC_CHECK2));
	GCDisplaySettings::setValue(9, IsDlgButtonChecked(IDC_CHECK3));
	GCDisplaySettings::setValue(4, IsDlgButtonChecked(IDC_CHECK4));
	GCDisplaySettings::setValue(5, IsDlgButtonChecked(IDC_CHECK5));
	GCDisplaySettings::setValue(10, IsDlgButtonChecked(IDC_CHECK6));
	GCDisplaySettings::setValue(34, IsDlgButtonChecked(IDC_CHECK7));
	GCDisplaySettings::setValue(48, IsDlgButtonChecked(IDC_CHECK8));
	
	return CPropertyPage::OnKillActive();
}
