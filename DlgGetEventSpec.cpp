// DlgGetEventSpec.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "DlgGetEventSpec.h"
#include "level_6.h"
#include "GCDisplaySettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgGetEventSpec dialog


DlgGetEventSpec::DlgGetEventSpec(CWnd* pParent /*=NULL*/)
	: CDialog(DlgGetEventSpec::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgGetEventSpec)
	m_sun = FALSE;
	m_tithi = FALSE;
	m_naks = FALSE;
	m_sank = FALSE;
	m_conj = FALSE;
	m_rahu_kalam = FALSE;
	m_yama_ghanti = FALSE;
	m_guli_kalam = FALSE;
	//}}AFX_DATA_INIT
	//  m_off = _T("");
	//  m_off = 0.0;
}


void DlgGetEventSpec::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgGetEventSpec)
	DDX_Check(pDX, IDC_CHECK1, m_sun);
	DDX_Check(pDX, IDC_CHECK2, m_tithi);
	DDX_Check(pDX, IDC_CHECK3, m_naks);
	DDX_Check(pDX, IDC_CHECK4, m_sank);
	DDX_Check(pDX, IDC_CHECK5, m_conj);
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_CHECK6, m_rahu_kalam);
	DDX_Check(pDX, IDC_CHECK7, m_yama_ghanti);
	DDX_Check(pDX, IDC_CHECK8, m_guli_kalam);
	DDX_Check(pDX, IDC_CHECK9, m_moon_rasi);
	DDX_Check(pDX, IDC_CHECK10, m_moon_times);
	DDX_Check(pDX, IDC_CHECK11, m_ascendent);
	//  DDX_Text(pDX, IDC_EDIT1, m_off);
	//  D//  DV_MaxChars(p//  DX, m_off, 3);
	//  DDX_Text(pDX, IDC_EDIT1, m_off);
	//  DDV_MinMaxDouble(pDX, m_off, -200, 200);
}


BEGIN_MESSAGE_MAP(DlgGetEventSpec, CDialog)
	//{{AFX_MSG_MAP(DlgGetEventSpec)
	ON_BN_CLICKED(IDC_BUTTON_BACK, OnButtonBack)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHECK6, &DlgGetEventSpec::OnBnClickedCheck6)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgGetEventSpec message handlers

void DlgGetEventSpec::OnButtonBack() 
{
	m_nNextStep = -1;
	CDialog::OnOK();
}

void DlgGetEventSpec::OnCancel() 
{
	m_nNextStep = 0;
	CDialog::OnCancel();
}


void DlgGetEventSpec::OnOK() 
{
	UpdateData();
	m_fOptions = 0;
	GCDisplaySettings::setValue(COREEVENTS_SUN, m_sun);
	GCDisplaySettings::setValue(COREEVENTS_NAKSATRA, m_naks);
	GCDisplaySettings::setValue(COREEVENTS_SANKRANTI, m_sank);
	GCDisplaySettings::setValue(COREEVENTS_TITHI, m_tithi);
	GCDisplaySettings::setValue(COREEVENTS_CONJUNCTION, m_conj);
	GCDisplaySettings::setValue(COREEVENTS_RAHUKALAM, m_rahu_kalam);
	GCDisplaySettings::setValue(COREEVENTS_YAMAGHANTI, m_yama_ghanti);
	GCDisplaySettings::setValue(COREEVENTS_GULIKALAM, m_guli_kalam);
	GCDisplaySettings::setValue(COREEVENTS_MOONRASI, m_moon_rasi);
	GCDisplaySettings::setValue(COREEVENTS_MOON, m_moon_times);
	GCDisplaySettings::setValue(COREEVENTS_ASCENDENT, m_ascendent);

	GCDisplaySettings::setValue(COREEVENTS_SORT, m_fSort);

	m_nNextStep = 1;
	CDialog::OnOK();
}

void DlgGetEventSpec::OnRadio1() 
{
	CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
	m_fSort = 1;
}

void DlgGetEventSpec::OnRadio2() 
{
	CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);
	m_fSort = 0;
}


BOOL DlgGetEventSpec::OnInitDialog() 
{
	m_conj = GCDisplaySettings::getValue(COREEVENTS_CONJUNCTION) ? TRUE : FALSE;
	m_naks = GCDisplaySettings::getValue(COREEVENTS_NAKSATRA) ? TRUE : FALSE;
	m_sank = GCDisplaySettings::getValue(COREEVENTS_SANKRANTI) ? TRUE : FALSE;
	m_sun  = GCDisplaySettings::getValue(COREEVENTS_SUN) ? TRUE : FALSE;
	m_tithi = GCDisplaySettings::getValue(COREEVENTS_TITHI) ? TRUE : FALSE;
	m_rahu_kalam = (GCDisplaySettings::getValue(COREEVENTS_RAHUKALAM)) ? TRUE : FALSE;
	m_yama_ghanti = GCDisplaySettings::getValue(COREEVENTS_YAMAGHANTI) ? TRUE : FALSE;
	m_guli_kalam = GCDisplaySettings::getValue(COREEVENTS_GULIKALAM) ? TRUE : FALSE;
	m_moon_rasi = GCDisplaySettings::getValue(COREEVENTS_MOONRASI) ? true : false;
	m_moon_times = GCDisplaySettings::getValue(COREEVENTS_MOON) ? true : false;
	m_ascendent = GCDisplaySettings::getValue(COREEVENTS_ASCENDENT) ? true : false;

	CDialog::OnInitDialog();

	m_fSort = GCDisplaySettings::getValue(COREEVENTS_SORT);

	CheckRadioButton(IDC_RADIO1, IDC_RADIO2, (m_fSort ? IDC_RADIO1 : IDC_RADIO2));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void DlgGetEventSpec::OnBnClickedCheck6()
{
	// TODO: Add your control notification handler code here
}
