// TithiCalc.cpp : implementation file
//

#include "stdafx.h"
#include "VCal5beta.h"
#include "TithiCalc.h"
#include "vedic_ui.h"
#include "level_6.h"
#include "strings.h"
#include "GCStrings.h"
#include "GCCalendar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int WriteXML_GaurabdaTithi(const char * foutName, EARTHDATA earth, int, int, int, int, int);

/////////////////////////////////////////////////////////////////////////////
// DlgGetStartDate dialog

int DlgGetStartDate::s_init = 0;
VCTIME DlgGetStartDate::m_resultC;
VATIME DlgGetStartDate::m_resultA;
	

DlgGetStartDate::DlgGetStartDate(CWnd* pParent /*=NULL*/)
	: CDialog(DlgGetStartDate::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgGetStartDate)
	//}}AFX_DATA_INIT
	bFinal = FALSE;
	f_update = FALSE;
}


void DlgGetStartDate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgGetStartDate)
	DDX_Control(pDX, IDC_EDIT2, w_year);
	DDX_Control(pDX, IDC_COMBO2, w_tithi);
	DDX_Control(pDX, IDC_COMBO1, w_masa);
	DDX_Control(pDX, IDC_EDIT1, w_gyear);
	DDX_Control(pDX, IDC_COMBO4, w_month);
	DDX_Control(pDX, IDC_COMBO3, w_day);
	DDX_Control(pDX, IDC_STATIC1, m_hdr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgGetStartDate, CDialog)
	//{{AFX_MSG_MAP(DlgGetStartDate)
	ON_BN_CLICKED(IDC_BUTTON1, OnCalc)
	ON_BN_CLICKED(IDC_BUTTON3, OnButtonBack)
	ON_CBN_SELENDOK(IDC_COMBO3, OnSelendokCombo3)
	ON_CBN_SELENDOK(IDC_COMBO4, OnSelendokCombo4)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_CBN_SELENDOK(IDC_COMBO1, OnSelendokCombo1)
	ON_CBN_SELENDOK(IDC_COMBO2, OnSelendokCombo2)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgGetStartDate message handlers

void DlgGetStartDate::OnCalc() 
{
	CString str;

	m_resultA.tithi = w_tithi.GetCurSel();
	m_resultA.masa  = GCCalendar::ComboMasaToMasa(w_masa.GetCurSel());
	m_resultA.gyear = GetDlgItemInt(IDC_EDIT1, NULL, FALSE);

	if (m_resultA.gyear < 1 || m_resultA.gyear > 2500)
	{
		MessageBox("Gaurabda Year is invalid. It should be from the range 1 ... 2500",
			"Invalid Gaurabda Year", MB_OK | MB_ICONSTOP);
		GetDlgItem(IDC_EDIT1)->SetFocus();
		return;
	}

	m_resultC.day = w_day.GetCurSel() + 1;
	m_resultC.month = w_month.GetCurSel() + 1;
	m_resultC.year = GetDlgItemInt(IDC_EDIT2, NULL, FALSE);
	m_resultC.tzone = m_earth.tzone;

	if (m_resultC.year < 1500 || m_resultC.year > 3999)
	{
		MessageBox("Year is invalid. It should be from the range 1500 ... 3999",
			"Invalid Year", MB_OK | MB_ICONSTOP);
		GetDlgItem(IDC_EDIT2)->SetFocus();
		return;
	}
	m_resultC.shour = 0.5;

	m_nNextStep = 1;
	m_setMenu.DestroyMenu();
	CDialog::OnOK();
}

BOOL DlgGetStartDate::OnInitDialog() 
{
	int i;
	TString str;
	VCTIME vc;
	SYSTEMTIME st;
	if (bFinal)
		SetDlgItemText(IDC_BUTTON1, "Calculate");

	m_setMenu.CreatePopupMenu();
	m_setMenu.AppendMenu(MF_STRING, ID_SET_TODAY, "set today");
	m_setMenu.AppendMenu(MF_STRING, ID_SET_START_MONTH, "set start of the month");
	m_setMenu.AppendMenu(MF_STRING, ID_SET_START_YEAR, "set start of the year");
	m_setMenu.AppendMenu(MF_STRING, ID_SET_START_MASA, "set start of the masa");
	m_setMenu.AppendMenu(MF_STRING, ID_SET_START_GYEAR, "set start of the gaurabda year");

	// inicializacia prvkov okna
	CDialog::OnInitDialog();

	m_hdr.InitMyFont();
	m_hdr.SetWindowText("Get Start Date");

	for(i = 1; i <= 31; i++)
	{
		str.Format("%d", i);
		w_day.AddString(str.c_str());
	}

	for(i = 0; i < 12; i++)
	{
		w_month.AddString(GCStrings::getString(760 + i).c_str());
	}

	if (s_init == 0 || m_resultA.gyear < 0 || m_resultA.gyear > 2500)
	{
		GetLocalTime(&st);
		m_resultC.day = st.wDay;
		m_resultC.month = st.wMonth;
		m_resultC.year = st.wYear;
		m_resultC.shour = double(0.5);
		m_resultC.tzone = m_earth.tzone;

		GCCalendar::VCTIMEtoVATIME(m_resultC, m_resultA, m_earth);

		s_init = 1;

	}

	m_resultC.tzone = m_earth.tzone;

	f_update = FALSE;

	w_day.SetCurSel(m_resultC.day - 1);
	w_month.SetCurSel(m_resultC.month - 1);
	SetDlgItemInt(IDC_EDIT2, m_resultC.year, FALSE);

	w_tithi.SetCurSel(m_resultA.tithi);
	w_masa.SetCurSel(GCCalendar::MasaToComboMasa(m_resultA.masa));
	SetDlgItemInt(IDC_EDIT1, m_resultA.gyear, FALSE);

	f_update = TRUE;

	m_nNextStep = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgGetStartDate::OnButtonBack() 
{
	// TODO: Add your control notification handler code here
	m_nNextStep = -1;
	m_setMenu.DestroyMenu();
	CDialog::OnOK();
}

void DlgGetStartDate::OnSelendokCombo3() 
{
	if (f_update)
		SynchroGregorianToGaurabda();
}

void DlgGetStartDate::OnSelendokCombo4() 
{
	// TODO: Add your control notification handler code here
	if (f_update)
		SynchroGregorianToGaurabda();
	
}

void DlgGetStartDate::OnChangeEdit2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if (f_update)
		SynchroGregorianToGaurabda();	
}

void DlgGetStartDate::SynchroGregorianToGaurabda()
{
	BOOL upd_old = f_update;
	f_update = FALSE;
	m_resultC.day = w_day.GetCurSel() + 1;
	m_resultC.month = w_month.GetCurSel() + 1;
	m_resultC.year = GetDlgItemInt(IDC_EDIT2, NULL, FALSE);
	m_resultC.tzone = m_earth.tzone;

	if (m_resultC.year < 1500 || m_resultC.year > 3999)
	{
		f_update = upd_old;
		return;
	}

	m_resultC.NextDay();
	m_resultC.PreviousDay();

	GCCalendar::VCTIMEtoVATIME(m_resultC, m_resultA, m_earth);

	w_tithi.SetCurSel(m_resultA.tithi);
	w_masa.SetCurSel(GCCalendar::MasaToComboMasa(m_resultA.masa));
	SetDlgItemInt(IDC_EDIT1, m_resultA.gyear, FALSE);
	f_update = upd_old;
}

void DlgGetStartDate::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if (f_update)
		SynchroGaurabdaToGregorian();
}

void DlgGetStartDate::OnSelendokCombo1() 
{
	// TODO: Add your control notification handler code here
	if (f_update)
		SynchroGaurabdaToGregorian();
}

void DlgGetStartDate::OnSelendokCombo2() 
{
	// TODO: Add your control notification handler code here
	if (f_update)
		SynchroGaurabdaToGregorian();	
}

void DlgGetStartDate::SynchroGaurabdaToGregorian()
{
	BOOL upd_old = f_update;
	f_update = FALSE;

	m_resultA.tithi = w_tithi.GetCurSel();
	m_resultA.masa  = GCCalendar::ComboMasaToMasa(w_masa.GetCurSel());
	m_resultA.gyear = GetDlgItemInt(IDC_EDIT1, NULL, FALSE);

	if (m_resultA.gyear < 0 || m_resultA.gyear > 2500)
	{
		f_update = upd_old;
		return;
	}

	GCCalendar::VATIMEtoVCTIME(m_resultA, m_resultC, m_earth);

	if (m_resultC.year < 0)
	{
		MessageBox("Corresponding date for given tithi and masa was not found.", "Date Not Found", MB_OK);
		//SynchroGregorianToGaurabda();
	}
	else
	{
		w_day.SetCurSel(m_resultC.day - 1);
		w_month.SetCurSel(m_resultC.month - 1);
		SetDlgItemInt(IDC_EDIT2, m_resultC.year, FALSE);
	}
	f_update = upd_old;
}

void DlgGetStartDate::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
	CPoint point;
	GetCursorPos(&point);
	m_setMenu.TrackPopupMenu(TPM_CENTERALIGN, point.x, point.y, this);
}

BOOL DlgGetStartDate::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	switch(LOWORD(wParam))
	{
	case ID_SET_TODAY:
		f_update = FALSE;
		m_resultC.Today();
		m_resultC.shour = 0.5;
		m_resultC.tzone = m_earth.tzone;
		w_day.SetCurSel(m_resultC.day - 1);
		w_month.SetCurSel(m_resultC.month - 1);
		SetDlgItemInt(IDC_EDIT2, m_resultC.year, FALSE);
		GCCalendar::VCTIMEtoVATIME(m_resultC, m_resultA, m_earth);
		w_tithi.SetCurSel(m_resultA.tithi);
		w_masa.SetCurSel(GCCalendar::MasaToComboMasa(m_resultA.masa));
		SetDlgItemInt(IDC_EDIT1, m_resultA.gyear, FALSE);
		f_update = TRUE;
		break;
	case ID_SET_START_MONTH:
		f_update = FALSE;
		w_day.SetCurSel(0);
		m_resultC.day = 1;
		SynchroGregorianToGaurabda();
		f_update = TRUE;
		break;
	case ID_SET_START_MASA:
		f_update = FALSE;
		w_tithi.SetCurSel(0);
		m_resultA.tithi = 0;
		SynchroGaurabdaToGregorian();
		f_update = TRUE;
		break;
	case ID_SET_START_YEAR:
		f_update = FALSE;
		w_day.SetCurSel(0);
		w_month.SetCurSel(0);
		m_resultC.day = 1;
		m_resultC.month = 1;
		SynchroGregorianToGaurabda();
		f_update = TRUE;
		break;
	case ID_SET_START_GYEAR:
		f_update = FALSE;
		w_tithi.SetCurSel(0);
		w_masa.SetCurSel(0);
		m_resultA.tithi = 0;
		m_resultA.masa = GCCalendar::ComboMasaToMasa(0);
		SynchroGaurabdaToGregorian();
		f_update = TRUE;
		break;
	}
	return CDialog::OnCommand(wParam, lParam);
}

void DlgGetStartDate::OnCancel() 
{
	m_setMenu.DestroyMenu();
	CDialog::OnCancel();
}
