// DlgGetEndDate.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "DlgGetEndDate.h"
#include "GCCalendar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


const char * FormatDate(VCTIME vc, VATIME va);


/////////////////////////////////////////////////////////////////////////////
// DlgGetEndDate dialog

int DlgGetEndDate::m_count = 1;
int DlgGetEndDate::m_type = 4;

DlgGetEndDate::DlgGetEndDate(CWnd* pParent /*=NULL*/)
	: CDialog(DlgGetEndDate::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgGetEndDate)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	bFinal = FALSE;
}


void DlgGetEndDate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgGetEndDate)
	DDX_Control(pDX, IDC_STATIC_1, m_hdr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgGetEndDate, CDialog)
	//{{AFX_MSG_MAP(DlgGetEndDate)
	ON_BN_CLICKED(IDC_BUTTON_BACK, OnButtonBack)
	ON_BN_CLICKED(IDC_BUTTON2, OnSet1)
	ON_BN_CLICKED(IDC_BUTTON3, OnSet3)
	ON_BN_CLICKED(IDC_BUTTON4, OnSet7)
	ON_BN_CLICKED(IDC_BUTTON5, OnSet21)
	ON_BN_CLICKED(IDC_BUTTON6, OnNumInc)
	ON_BN_CLICKED(IDC_BUTTON7, OnNumDec)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	ON_BN_CLICKED(IDC_RADIO7, OnRadio7)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgGetEndDate message handlers

void DlgGetEndDate::OnButtonBack() 
{
	// TODO: Add your control notification handler code here
	m_nNextStep = -1;
	CDialog::OnOK();
}

void DlgGetEndDate::OnSet1()
{
	SetDlgItemInt(IDC_EDIT1, 1, FALSE);
//	Recalc();
}

void DlgGetEndDate::OnSet3() 
{
	SetDlgItemInt(IDC_EDIT1, 3, FALSE);	
//	Recalc();
}

void DlgGetEndDate::OnSet7() 
{
	SetDlgItemInt(IDC_EDIT1, 7, FALSE);
//	Recalc();
}

void DlgGetEndDate::OnSet21() 
{
	SetDlgItemInt(IDC_EDIT1, 21, FALSE);	
//	Recalc();
}

void DlgGetEndDate::OnNumInc() 
{
	// TODO: Add your control notification handler code here
	unsigned int n = GetDlgItemInt(IDC_EDIT1, NULL, FALSE);
	n++;
	SetDlgItemInt(IDC_EDIT1, n, FALSE);	
//	Recalc();
}

void DlgGetEndDate::OnNumDec() 
{
	unsigned int n = GetDlgItemInt(IDC_EDIT1, NULL, FALSE);
	if (n > 0)
		n--;
	SetDlgItemInt(IDC_EDIT1, n, FALSE);
//	Recalc();
}

void DlgGetEndDate::OnRadio1() 
{
	m_type = 1;	
	CheckRadioButton(IDC_RADIO1, IDC_RADIO7, IDC_RADIO1);
	Recalc();
}

void DlgGetEndDate::OnRadio2() 
{
	m_type = 2;	
	CheckRadioButton(IDC_RADIO1, IDC_RADIO7, IDC_RADIO2);
	Recalc();
}

void DlgGetEndDate::OnRadio3() 
{
	m_type = 3;	
	CheckRadioButton(IDC_RADIO1, IDC_RADIO7, IDC_RADIO3);
	Recalc();
}

void DlgGetEndDate::OnRadio4() 
{
	m_type = 4;	
	CheckRadioButton(IDC_RADIO1, IDC_RADIO7, IDC_RADIO4);
	Recalc();
}

void DlgGetEndDate::OnRadio5() 
{
	m_type = 5;	
	CheckRadioButton(IDC_RADIO1, IDC_RADIO7, IDC_RADIO5);
	Recalc();
}

void DlgGetEndDate::OnRadio6() 
{
	m_type = 6;	
	CheckRadioButton(IDC_RADIO1, IDC_RADIO7, IDC_RADIO6);
	Recalc();
}

void DlgGetEndDate::OnRadio7() 
{
	m_type = 7;	
	CheckRadioButton(IDC_RADIO1, IDC_RADIO7, IDC_RADIO7);
	Recalc();
}


BOOL DlgGetEndDate::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_hdr.InitMyFont();
	m_hdr.SetWindowText("Get End Date");
	if (bFinal == TRUE) SetDlgItemText(IDOK, "Calculate");

	SetDlgItemInt(IDC_EDIT1, m_count, FALSE);
	switch(m_type)
	{
	case 1:	CheckRadioButton(IDC_RADIO1, IDC_RADIO7, IDC_RADIO1); break;
	case 2:	CheckRadioButton(IDC_RADIO1, IDC_RADIO7, IDC_RADIO2); break;
	case 3:	CheckRadioButton(IDC_RADIO1, IDC_RADIO7, IDC_RADIO3); break;
	case 4:	CheckRadioButton(IDC_RADIO1, IDC_RADIO7, IDC_RADIO4); break;
	case 5:	CheckRadioButton(IDC_RADIO1, IDC_RADIO7, IDC_RADIO5); break;
	case 6:	CheckRadioButton(IDC_RADIO1, IDC_RADIO7, IDC_RADIO6); break;
	case 7:	CheckRadioButton(IDC_RADIO1, IDC_RADIO7, IDC_RADIO7); break;
	default: break;
	}

	SetDlgItemText(IDC_EDIT2, FormatDate(vc_start, va_start));
	Recalc();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgGetEndDate::Recalc()
{
	m_count = GetDlgItemInt(IDC_EDIT1, NULL, FALSE);
	m_uncorrected_count = m_count;
	switch(m_type)
	{
	case 1:
	case 5:
		if (m_count > 36500)
			m_count = 36500;
		if (m_count/365 + vc_start.year > 3999) m_count = (3999 - vc_start.year)*365;
		break;
	case 2:
		if (m_count > 5200)
			m_count = 5200;
		if (m_count/52 + vc_start.year > 3999) m_count = (3999 - vc_start.year)*52;
		break;
	case 3:
	case 6:
		if (m_count > 1200)
			m_count = 1200;
		if (m_count/12 + vc_start.year > 3999) m_count = (3999 - vc_start.year)*12;
		break;
	case 4:
	case 7:
		if (m_count > 100)
			m_count = 100;
		if (m_count + vc_start.year > 3999) m_count = 3999 - vc_start.year;
		break;
	default:
		break;
	}
	GCCalendar::CalcEndDate(m_earth, vc_start, va_start, vc_end, va_end, m_type, m_count);
	SetDlgItemText(IDC_EDIT3, FormatDate(vc_end, va_end));
}

void DlgGetEndDate::OnOK() 
{
	int i = 0;
	switch(m_type)
	{
	case 1:
	case 5:
		if (m_uncorrected_count/365 + vc_start.year > 3999) i = 1;
		break;
	case 2:
		if (m_uncorrected_count/52 + vc_start.year > 3999) i = 1;
		break;
	case 3:
	case 6:
		if (m_uncorrected_count/12 + vc_start.year > 3999) i = 1;
		break;
	case 4:
	case 7:
		if (m_uncorrected_count + vc_start.year > 3999) i = 1;
		break;
	default:
		break;
	}

	if (i == 1)
	{
		MessageBox("Given number has exceeded the valid range of dates (Years 1500 - 3999). \r\nTherefore end date was corrected and is below the year 3999.",
			"Corrected End Date", MB_OK | MB_ICONEXCLAMATION);
	}
	
	m_nNextStep = 1;
	
	CDialog::OnOK();
}

void DlgGetEndDate::OnCancel() 
{
	m_nNextStep = 0;
	
	CDialog::OnCancel();
}

void DlgGetEndDate::OnChangeEdit1() 
{
	Recalc();	
}
