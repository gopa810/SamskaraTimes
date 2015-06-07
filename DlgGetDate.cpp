// DlgGetDate.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "DlgGetDate.h"
#include "level_6.h"
#include "TTimeZone.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgGetDate dialog

int DlgGetDate::s_init = 0;
VCTIME DlgGetDate::s_event;


DlgGetDate::DlgGetDate(CWnd* pParent /*=NULL*/)
	: CDialog(DlgGetDate::IDD, pParent)
{
	SYSTEMTIME st;

	if (s_init == 0)
	{
		GetLocalTime(&st);
		s_init = 1;
	}
	else
	{
		st.wDay = s_event.day;
		st.wMonth = s_event.month;
		st.wYear = s_event.year;
		st.wHour = s_event.GetHour();
		st.wMinute = s_event.GetMinuteRound();
	}

	m_nNextStep = 0;
	//{{AFX_DATA_INIT(DlgGetDate)
	m_nDay = st.wDay;
	m_nMonth = st.wMonth;
	m_nYear = st.wYear;
	m_nHour = st.wHour;
	m_nMin = st.wMinute;
	//}}AFX_DATA_INIT

}


void DlgGetDate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgGetDate)
	DDX_Text(pDX, IDC_EDIT1, m_nDay);
	DDV_MinMaxUInt(pDX, m_nDay, 1, 31);
	DDX_Text(pDX, IDC_EDIT2, m_nMonth);
	DDV_MinMaxUInt(pDX, m_nMonth, 1, 12);
	DDX_Text(pDX, IDC_EDIT3, m_nYear);
	DDV_MinMaxUInt(pDX, m_nYear, 1600, 3999);
	DDX_Text(pDX, IDC_EDIT4, m_nHour);
	DDV_MinMaxUInt(pDX, m_nHour, 0, 23);
	DDX_Text(pDX, IDC_EDIT5, m_nMin);
	DDV_MinMaxUInt(pDX, m_nMin, 0, 59);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgGetDate, CDialog)
	//{{AFX_MSG_MAP(DlgGetDate)
	ON_BN_CLICKED(ID_BUTTON_NEXT, OnButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_BACK, OnButtonBack)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgGetDate message handlers

void DlgGetDate::OnButtonNext()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_nNextStep = 1;
	s_event.day = m_nDay;
	s_event.month = m_nMonth;
	s_event.year  = m_nYear;
	s_event.shour = (double(m_nHour)*60.0 + double(m_nMin)) / 1440.0;

	CDialog::OnOK();

}

void DlgGetDate::OnButtonBack() 
{
	// TODO: Add your control notification handler code here
	m_nNextStep = -1;
	CDialog::OnCancel();
}

BOOL DlgGetDate::OnInitDialog() 
{
	m_nNextStep = 0;

	CDialog::OnInitDialog();
	
	SetDlgItemText(IDC_STATIC_TZ, TTimeZone::GetTimeZoneOffsetText(s_event.tzone));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
