// DPageGeneral.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "DPageGeneral.h"
#include "showset.h"
#include "strings.h"
#include "GCStrings.h"
#include "GCDisplaySettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DPageGeneral property page

IMPLEMENT_DYNCREATE(DPageGeneral, CPropertyPage)

DPageGeneral::DPageGeneral() : CPropertyPage(DPageGeneral::IDD)
{
	//{{AFX_DATA_INIT(DPageGeneral)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

DPageGeneral::~DPageGeneral()
{
}

void DPageGeneral::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DPageGeneral)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DPageGeneral, CPropertyPage)
	//{{AFX_MSG_MAP(DPageGeneral)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DPageGeneral message handlers

void DPageGeneral::OnOK() 
{
	CPropertyPage::OnOK();
}

BOOL DPageGeneral::OnSetActive() 
{
	int i;
	SendDlgItemMessage(IDC_COMBO1, CB_RESETCONTENT);
	SendDlgItemMessage(IDC_COMBO1, CB_ADDSTRING, 0, (LPARAM)LPCTSTR("Before New Masa"));
	SendDlgItemMessage(IDC_COMBO1, CB_ADDSTRING, 0, (LPARAM)LPCTSTR("Before New Month"));
	if (GCDisplaySettings::getValue(18) == 1)
		i = 0;
	else
		i = 1;
	SendDlgItemMessage(IDC_COMBO1, CB_SETCURSEL, i);

	SendDlgItemMessage(IDC_COMBO2, CB_RESETCONTENT);
	for(i=0; i<7; i++)
		SendDlgItemMessage(IDC_COMBO2, CB_ADDSTRING, 0, (LPARAM)LPCTSTR(GCStrings::getString(i).c_str()));
	SendDlgItemMessage(IDC_COMBO2, CB_SETCURSEL, GCDisplaySettings::getValue(40));
	SendDlgItemMessage(IDC_COMBO3, CB_SETCURSEL, GCDisplaySettings::getValue(49));

	CheckDlgButton(IDC_CHECK1, GCDisplaySettings::getValue(20));
	CheckDlgButton(IDC_CHECK2, GCDisplaySettings::getValue(21));

	CheckDlgButton(IDC_CHECK18, GCDisplaySettings::getValue(11));
	CheckDlgButton(IDC_CHECK19, GCDisplaySettings::getValue(0));
	CheckDlgButton(IDC_CHECK3, GCDisplaySettings::getValue(1));
	CheckDlgButton(IDC_CHECK4, GCDisplaySettings::getValue(7));
	CheckDlgButton(IDC_CHECK7, GCDisplaySettings::getValue(12));
	CheckDlgButton(IDC_CHECK5, GCDisplaySettings::getValue(8));
	CheckDlgButton(IDC_CHECK6, GCDisplaySettings::getValue(35));
	CheckDlgButton(IDC_CHECK8, GCDisplaySettings::getValue(50));
	SendDlgItemMessage(IDC_COMBO4, CB_SETCURSEL, GCDisplaySettings::getValue(51));

	return CPropertyPage::OnSetActive();
}

BOOL DPageGeneral::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	LPNMHDR lp = (LPNMHDR)lParam;

	if (lp->code == PSN_HELP)
	{
		MessageBox("This page allows to change the mode of display of the general information in the calendar.", "General Settings of Display", MB_OK);
		return TRUE;
	}
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnNotify(wParam, lParam, pResult);
}

BOOL DPageGeneral::OnKillActive() 
{
	int i = 0;
	i = SendDlgItemMessage(IDC_COMBO1, CB_GETCURSEL);
	GCDisplaySettings::setValue(20, IsDlgButtonChecked(IDC_CHECK1));
	GCDisplaySettings::setValue(21, IsDlgButtonChecked(IDC_CHECK2));
	if (i >= 0 && i < 2)
	{
		GCDisplaySettings::setValue(18 + i, 1);
		GCDisplaySettings::setValue(19 - i, 0);
	}
	GCDisplaySettings::setValue(11, IsDlgButtonChecked(IDC_CHECK18));
	GCDisplaySettings::setValue(0, IsDlgButtonChecked(IDC_CHECK19));
	GCDisplaySettings::setValue(1, IsDlgButtonChecked(IDC_CHECK3));
	GCDisplaySettings::setValue(7, IsDlgButtonChecked(IDC_CHECK4));
	GCDisplaySettings::setValue(8, IsDlgButtonChecked(IDC_CHECK5));
	GCDisplaySettings::setValue(12, IsDlgButtonChecked(IDC_CHECK7));
	GCDisplaySettings::setValue(35, IsDlgButtonChecked(IDC_CHECK6));
	GCDisplaySettings::setValue(40, SendDlgItemMessage(IDC_COMBO2, CB_GETCURSEL));
	GCDisplaySettings::setValue(49, SendDlgItemMessage(IDC_COMBO3, CB_GETCURSEL));
	GCDisplaySettings::setValue(50, IsDlgButtonChecked(IDC_CHECK8));
	GCDisplaySettings::setValue(51, SendDlgItemMessage(IDC_COMBO4, CB_GETCURSEL));
	return CPropertyPage::OnKillActive();
}
