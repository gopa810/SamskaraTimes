// DPageFest.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "DPageFest.h"
#include "showset.h"
#include "CustomEvent.h"
#include "GCDisplaySettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


int g_set_oldstylefast = 0;

extern int gCustomEventList_Modified;

/////////////////////////////////////////////////////////////////////////////
// DPageFest property page

IMPLEMENT_DYNCREATE(DPageFest, CPropertyPage)

DPageFest::DPageFest() : CPropertyPage(DPageFest::IDD)
{
	//{{AFX_DATA_INIT(DPageFest)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

DPageFest::~DPageFest()
{
}

void DPageFest::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DPageFest)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DPageFest, CPropertyPage)
	//{{AFX_MSG_MAP(DPageFest)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DPageFest message handlers

void DPageFest::OnOK() 
{
	CPropertyPage::OnOK();
}

BOOL DPageFest::OnSetActive() 
{
	int i;
	SendDlgItemMessage(IDC_COMBO1, CB_RESETCONTENT);
	SendDlgItemMessage(IDC_COMBO1, CB_ADDSTRING, 0, (LPARAM)(const char *)("Purnima System"));
	SendDlgItemMessage(IDC_COMBO1, CB_ADDSTRING, 0, (LPARAM)(const char *)("Pratipat System"));
	SendDlgItemMessage(IDC_COMBO1, CB_ADDSTRING, 0, (LPARAM)(const char *)("Ekadasi System"));
	if (GCDisplaySettings::getValue(13) == 1)
		i = 0;
	else if (GCDisplaySettings::getValue(14) == 1)
		i = 1;
	else
		i = 2;
	SendDlgItemMessage(IDC_COMBO1, CB_SETCURSEL, i);

	CheckDlgButton(IDC_CHECK2, GCDisplaySettings::getValue(16));
	CheckDlgButton(IDC_CHECK3, GCDisplaySettings::getValue(17));

	int chks[10][2];
	for(i=0;i<10;i++)
		chks[i][0] = chks[i][1] = 0;
	CCustomEvent * p = gCustomEventList.list;
	while(p)
	{
		chks[p->nClass][p->nVisible]++;
		p = p->next;
	}
	for(i=0;i<6;i++)
	{
		if (chks[i][1]>0 && chks[i][0]==0)
		{
			GCDisplaySettings::setValue(22+i, 1);
		}
		else if (chks[i][1]==0 && chks[i][0]>0)
		{
			GCDisplaySettings::setValue(22+i, 0);
		}
		else
		{
			GCDisplaySettings::setValue(22+i, 2);
		}
	}
	CheckDlgButton(IDC_CHECK4, GCDisplaySettings::getValue(22));
	CheckDlgButton(IDC_CHECK5, GCDisplaySettings::getValue(23));
	CheckDlgButton(IDC_CHECK6, GCDisplaySettings::getValue(24));
	CheckDlgButton(IDC_CHECK7, GCDisplaySettings::getValue(25));
	CheckDlgButton(IDC_CHECK8, GCDisplaySettings::getValue(26));
	CheckDlgButton(IDC_CHECK9, GCDisplaySettings::getValue(27));
	CheckDlgButton(IDC_CHECK10, GCDisplaySettings::getValue(28));
	CheckDlgButton(IDC_CHECK1,  GCDisplaySettings::getValue(36));
	CheckDlgButton(IDC_CHECK11, GCDisplaySettings::getValue(37));
	CheckDlgButton(IDC_CHECK12, GCDisplaySettings::getValue(38));
	CheckDlgButton(IDC_CHECK13, GCDisplaySettings::getValue(39));
	CheckDlgButton(IDC_CHECK14, GCDisplaySettings::getValue(42));
	CheckDlgButton(IDC_CHECK15, GCDisplaySettings::getValue(41));

	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnSetActive();
}

BOOL DPageFest::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	LPNMHDR lp = (LPNMHDR)lParam;

	if (lp->code == PSN_HELP)
	{
		MessageBox("This page allows to change the mode of display of the most common events in the calendar.", "Settings for Events", MB_OK);
		return TRUE;
	}
	
	return CPropertyPage::OnNotify(wParam, lParam, pResult);
}

BOOL DPageFest::OnKillActive() 
{
	int i = 0;
	// TODO: Add your specialized code here and/or call the base class
	i = SendDlgItemMessage(IDC_COMBO1, CB_GETCURSEL);
	GCDisplaySettings::setValue(16, IsDlgButtonChecked(IDC_CHECK2));
	GCDisplaySettings::setValue(17, IsDlgButtonChecked(IDC_CHECK3));
	
	GCDisplaySettings::setValue(22, IsDlgButtonChecked(IDC_CHECK4));
	GCDisplaySettings::setValue(23, IsDlgButtonChecked(IDC_CHECK5));
	GCDisplaySettings::setValue(24, IsDlgButtonChecked(IDC_CHECK6));
	GCDisplaySettings::setValue(25, IsDlgButtonChecked(IDC_CHECK7));
	GCDisplaySettings::setValue(26, IsDlgButtonChecked(IDC_CHECK8));
	GCDisplaySettings::setValue(27, IsDlgButtonChecked(IDC_CHECK9));
	GCDisplaySettings::setValue(28, IsDlgButtonChecked(IDC_CHECK10));
	GCDisplaySettings::setValue(36, IsDlgButtonChecked(IDC_CHECK1));
	GCDisplaySettings::setValue(37, IsDlgButtonChecked(IDC_CHECK11));
	GCDisplaySettings::setValue(38, IsDlgButtonChecked(IDC_CHECK12));
	GCDisplaySettings::setValue(39, IsDlgButtonChecked(IDC_CHECK13));
	GCDisplaySettings::setValue(41, IsDlgButtonChecked(IDC_CHECK15));
	GCDisplaySettings::setValue(42, IsDlgButtonChecked(IDC_CHECK14));

	if (i >= 0 && i < 3)
	{
		GCDisplaySettings::setValue(13 + i, 1);
		GCDisplaySettings::setValue(13 + (i + 1)%3, 0);
		GCDisplaySettings::setValue(13 + (i + 2)%3, 0);
	}
	
	CCustomEvent * p = gCustomEventList.list;
	while(p)
	{
		i = p->nClass;
		if (GCDisplaySettings::getValue(22+i) == 0)
		{
			p->nVisible = 0;
			gCustomEventList_Modified = 1;
		}
		else if (GCDisplaySettings::getValue(22+i) == 1)
		{
			p->nVisible = 1;
			gCustomEventList_Modified = 1;
		}
		p = p->next;
	}

	gCustomEventList_Modified = (gCustomEventList.setOldStyleFast(GCDisplaySettings::getValue(42)) ? 1 : gCustomEventList_Modified);

	return CPropertyPage::OnKillActive();
}

BOOL DPageFest::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	return CPropertyPage::OnCommand(wParam, lParam);
}
