// DlgGetLocation.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "DlgGetLocation.h"
#include "DlgGetLocationEx.h"
#include "level_0.h"
#include "vedic_ui.h"
#include "TTimeZone.h"
#include "GCStrings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CLocationRef gLastLocation;
extern CLocationRef gMyLocation;
extern int g_dstSelMethod;

const char * AvcGetEarthPosFromString(const char * str, bool bNorth, double &Longitude);

/////////////////////////////////////////////////////////////////////////////
// DlgGetLocation dialog

DlgGetLocation::DlgGetLocation(LPCTSTR szTitle, CWnd* pParent /*=NULL*/)
	: CDialog(DlgGetLocation::IDD, pParent)
{
//	m_pfont = pFont;
	m_bMyLocation = FALSE;
	m_nNextStep = 0;
	//{{AFX_DATA_INIT(DlgGetLocation)
	//}}AFX_DATA_INIT
	m_strTitle = szTitle;
	m_bFinal = FALSE;
	m_latiSign = 1.0;
	m_longSign = 1.0;
	b_upd = true;
	m_nLastDst = 0;
	wrongCoordinates = FALSE;
	errorText = "";
}


void DlgGetLocation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgGetLocation)
	DDX_Control(pDX, IDC_BTN_LONG, cLongSw);
	DDX_Control(pDX, IDC_BTN_LATI, cLatiSw);
	DDX_Control(pDX, IDC_LONG_DEG, cLongDeg);
	DDX_Control(pDX, IDC_LONG_ARC, cLongArc);
	DDX_Control(pDX, IDC_LATI_DEG, cLatiDeg);
	DDX_Control(pDX, IDC_LATI_ARC, cLatiArc);
	DDX_Control(pDX, IDC_COMBO_DST, cDst);
	DDX_Control(pDX, IDC_EDIT5, cLocName);
	DDX_Control(pDX, IDC_DST_INFO, cDstInfo);
	DDX_Control(pDX, IDC_STATIC1, m_hdr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgGetLocation, CDialog)
	//{{AFX_MSG_MAP(DlgGetLocation)
	ON_BN_CLICKED(IDC_BUTTON1, OnSelectLocation)
	ON_BN_CLICKED(ID_BUTTON_BACK, OnButtonBack)
	ON_BN_CLICKED(ID_BUTTON_NEXT, OnButtonNext)
	ON_CBN_SELENDOK(IDC_COMBO_DST, OnSelendokComboDst)
	ON_CBN_DROPDOWN(IDC_COMBO_DST, OnDropdownComboDst)
	ON_BN_CLICKED(IDC_BTN_LONG, OnBtnLong)
	ON_BN_CLICKED(IDC_BTN_LATI, OnBtnLati)
	ON_EN_CHANGE(IDC_LATI_ARC, OnChangeLatiArc)
	ON_EN_CHANGE(IDC_LATI_DEG, OnChangeLatiDeg)
	ON_EN_CHANGE(IDC_LONG_ARC, OnChangeLongArc)
	ON_EN_CHANGE(IDC_LONG_DEG, OnChangeLongDeg)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeLocation)
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

int LocGetDeg(double d)
{
	return int(floor(fabs(d)));
}

int LocGetArc(double d)
{
	double a = fabs(d);
	return int((a - floor(a))* 60.0 + 0.5);
}

const char * LocGetTextLong(double d)
{
	if (d < 0.0)
		return "West";

	return "East";
}

const char * LocGetTextLati(double d)
{
	if (d < 0.0)
		return "South";

	return "North";
}

double sign(double b)
{
	return (b < 0.0) ? -1.0 : 1.0;
}

/////////////////////////////////////////////////////////////////////////////
// DlgGetLocation message handlers

void DlgGetLocation::OnSelectLocation() 
{
	// TODO: Add your control notification handler code here
	//CDlgSelectLocation d;
	DlgGetLocationEx d;

	if (d.DoModal() == IDOK)
	{
		// this is part: DIALOG.RESULT TO LOCATION
		m_location.m_fLongitude = d.m_lc->m_fLongitude;
		m_location.m_fLatitude = d.m_lc->m_fLatitude;
		m_location.m_fTimezone = d.m_lc->m_fTimezone;
		m_location.m_strName = d.m_lc->m_strCity;
		m_location.m_strName += " [";
		m_location.m_strName += d.m_lc->m_strCountry;
		m_location.m_strName += "]";
		m_location.m_nDST = d.m_lc->m_nDST;

		// this is part: LOCATION TO DIALOG
		cLocName.SetWindowText(m_location.m_strName);
		b_upd = false;
		SetDlgItemInt(IDC_LATI_DEG, LocGetDeg(d.m_lc->m_fLatitude));
		SetDlgItemInt(IDC_LATI_ARC, LocGetArc(d.m_lc->m_fLatitude));
		SetDlgItemInt(IDC_LONG_DEG, LocGetDeg(d.m_lc->m_fLongitude));
		SetDlgItemInt(IDC_LONG_ARC, LocGetArc(d.m_lc->m_fLongitude));
		cLatiSw.SetWindowText(LocGetTextLati(d.m_lc->m_fLatitude));
		cLongSw.SetWindowText(LocGetTextLong(d.m_lc->m_fLongitude));
		m_latiSign = sign(d.m_lc->m_fLatitude);
		m_longSign = sign(d.m_lc->m_fLongitude);
		b_upd = true;
		//UpdateDstByTimezone(m_location.m_fTimezone);

		//cLat.SetWindowText(EARTHDATA::GetTextLatitude());
		//cLong.SetWindowText(EARTHDATA::GetTextLongitude());
		//cTimezone.SetCurSel(AvcGetNearestTimeZone(d.m_lc->m_fTimezone));
		SetCurSelDST(d.m_lc->m_nDST);
	}

}

//============================================================================
// 
//============================================================================

void DlgGetLocation::OnButtonBack() 
{
	// TODO: Add your control notification handler code here
	m_nNextStep = -1;
	CDialog::OnCancel();
}

//============================================================================
// 
//============================================================================

void DlgGetLocation::OnButtonNext() 
{
	CString str;

	m_location.m_nDST = cDst.GetItemData(cDst.GetCurSel());
	cLocName.GetWindowText(str);
	m_location.m_strName = str;
	m_location.m_fTimezone = TTimeZone::GetTimeZoneOffset(m_location.m_nDST);
	m_location.m_strLatitude = EARTHDATA::GetTextLatitude(m_location.m_fLatitude);
	m_location.m_strLongitude = EARTHDATA::GetTextLongitude(m_location.m_fLongitude);
	m_location.m_strTimeZone = TTimeZone::GetTimeZoneOffsetText(m_location.m_fTimezone);
	m_location.m_strFullName.Format("%s (%s %s, %s)",
		m_location.m_strName.c_str(),
		m_location.m_strLatitude.c_str(),
		m_location.m_strLongitude.c_str(),
		m_location.m_strTimeZone.c_str());

	// TODO: Add your control notification handler code here
	if (m_bMyLocation)
	{
		gMyLocation = m_location;
	}

	gLastLocation = m_location;

	m_nNextStep = 1;
	CDialog::OnOK();
}

//============================================================================
// 
//============================================================================

BOOL DlgGetLocation::OnInitDialog() 
{
	int n, m, c;
	if (m_bFinal == TRUE)
	{
		GetDlgItem(ID_BUTTON_NEXT)->SetWindowText("Set");
	}

	if (m_bMyLocation)
	{
		m_location = gMyLocation;
	}
	else
	{
		m_location = gLastLocation;
	}

	CDialog::OnInitDialog();
	
	m_hdr.InitMyFont();
	m_hdr.SetWindowText(m_strTitle);

	m = TTimeZone::GetTimeZoneCount();

	cDst.ResetContent();
	for(n = 0; n < m; n++)
	{
		c = cDst.AddString(TTimeZone::gzone[n].name);
		cDst.SetItemData(c, TTimeZone::gzone[n].idx);
	}

	cLocName.SetWindowText(m_location.m_strName);

	LocationToDialog();

	m_nNextStep = 0;
	CheckDlgButton(IDC_CHECK1, 0);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//============================================================================
// 
//============================================================================

void DlgGetLocation::LocationToDialog()
{
	b_upd = false;
	SetDlgItemInt(IDC_LATI_DEG, LocGetDeg(m_location.m_fLatitude));
	SetDlgItemInt(IDC_LATI_ARC, LocGetArc(m_location.m_fLatitude));
	SetDlgItemInt(IDC_LONG_DEG, LocGetDeg(m_location.m_fLongitude));
	SetDlgItemInt(IDC_LONG_ARC, LocGetArc(m_location.m_fLongitude));
	cLatiSw.SetWindowText(LocGetTextLati(m_location.m_fLatitude));
	cLongSw.SetWindowText(LocGetTextLong(m_location.m_fLongitude));
	b_upd = true;

	SetCurSelDST(m_location.m_nDST);
}

//============================================================================
// 
//============================================================================

void DlgGetLocation::GetEarthData(EARTHDATA &earth)
{
	earth.latitude_deg = m_location.m_fLatitude;
	earth.longitude_deg = m_location.m_fLongitude;
	earth.tzone = m_location.m_fTimezone;
	earth.dst   = m_location.m_nDST;
}

//============================================================================
// 
//============================================================================

void DlgGetLocation::OnSelendokComboDst() 
{
	UpdateDSTInfo();
	CheckDlgButton(IDC_CHECK1, 0);
}

//============================================================================
// 
//============================================================================

void DlgGetLocation::UpdateDSTInfo()
{
	TString str, ret;

	if (wrongCoordinates)
	{
		cDstInfo.SetWindowTextA(errorText);
		return;
	}

	int i = cDst.GetItemData( cDst.GetCurSel() );

	if (i < 0 || i >= TTimeZone::GetTimeZoneCount())
		return;

	DWORD dw = TTimeZone::gzone[TTimeZone::ID2INDEX(i)].val;

//	cTimezone.SetCurSel( AvcGetNearestTimeZone( TTimeZone::gzone[i].tzone));

	int a[8];

	if (dw == 0)
	{
		ret = GCStrings::getString(807);
	}
	else
	{
		TTimeZone::ExpandVal(dw, a);

		ret = GCStrings::getString(808);
		// pre datumovy den
		if (a[1] == 1)
		{

			str.Format("since %s %s ", GCStrings::getString(a[2] + 810).c_str(), GCStrings::getString(a[0] + 794).c_str());
			//SetDlgItemText(IDC_STATIC_DST_INFO1, str);
		}
		else
		{
			// pre tyzdenny den
			str.Format("since %s %s %s ", GCStrings::getString(a[2] + 781).c_str(), GCStrings::getString(a[3] + 787).c_str(), GCStrings::getString(a[0] + 794).c_str());
			//SetDlgItemText(IDC_STATIC_DST_INFO1, str);
		}
		ret += str;

		if (a[5] == 1)
		{
			str.Format("to %s %s", GCStrings::getString(810 + a[6]).c_str(), GCStrings::getString(a[4] + 794).c_str());
			//SetDlgItemText(IDC_STATIC_DST_INFO2, str);
		}
		else
		{
			// pre tyzdenny den
			str.Format("to %s %s %s", GCStrings::getString(a[6] + 781).c_str(), GCStrings::getString(a[7] + 787).c_str(), GCStrings::getString(a[4] + 794).c_str());
			//SetDlgItemText(IDC_STATIC_DST_INFO2, str);
		}
		ret += str;
	}

	cDstInfo.SetWindowText(ret);
}

//============================================================================
// 
//============================================================================

int DlgGetLocation::UpdateDstByTimezone(double tzone)
{
	int n, m = TTimeZone::GetTimeZoneCount();
	int found = 0;

	if (IsDlgButtonChecked(IDC_CHECK1)==0)
		return 0;

//	return 1;

	double lon = (fabs(m_location.m_fLongitude)+7.5)/15.0;
	if (m_location.m_fLongitude<0.0)
		lon = -lon;

	for(n = 0; n < m; n++)
	{
		if (TTimeZone::gzone[n].offset >= int(lon)*60)
		{
			cDst.SetCurSel(n);
			break;
		}
	}

	UpdateDSTInfo();

	return 1;
}

//============================================================================
// 
//============================================================================

void DlgGetLocation::OnDropdownComboDst() 
{
	//m_location.m_fTimezone = AvcGetTimeZone(cTimezone.GetCurSel());
	//UpdateDstByTimezone(m_location.m_fTimezone);
}

void DlgGetLocation::OnBtnLong() 
{
	m_longSign = -m_longSign;
	if (g_dstSelMethod == 2 && b_upd == true)
	{
		m_location.m_fLongitude = m_longSign * (double(GetDlgItemInt(IDC_LONG_DEG)) + double(GetDlgItemInt(IDC_LONG_ARC))/60.0);	
		UpdateDstByTimezone(m_location.m_fTimezone);
	}
	SetDlgItemText(IDC_BTN_LONG, LocGetTextLong(m_longSign));
}

void DlgGetLocation::OnBtnLati() 
{
	m_latiSign = -m_latiSign;
	if (g_dstSelMethod == 2 && b_upd == true)
	{
		m_location.m_fLatitude = m_latiSign * (double(GetDlgItemInt(IDC_LATI_DEG)) + double(GetDlgItemInt(IDC_LATI_ARC))/60.0);	
		UpdateDstByTimezone(m_location.m_fTimezone);
	}
	SetDlgItemText(IDC_BTN_LATI, LocGetTextLati(m_latiSign));
}

void DlgGetLocation::OnChangeLatiArc() 
{
	if (g_dstSelMethod == 2 && b_upd == true)
	{
		m_location.m_fLatitude = m_latiSign * (double(GetDlgItemInt(IDC_LATI_DEG)) + double(GetDlgItemInt(IDC_LATI_ARC))/60.0);	
		UpdateDstByTimezone(m_location.m_fTimezone);
	}
}

void DlgGetLocation::OnChangeLatiDeg() 
{
	if (g_dstSelMethod == 2 && b_upd == true)
	{
		m_location.m_fLatitude = m_latiSign * (double(GetDlgItemInt(IDC_LATI_DEG)) + double(GetDlgItemInt(IDC_LATI_ARC))/60.0);	
		UpdateDstByTimezone(m_location.m_fTimezone);
	}
}

void DlgGetLocation::OnChangeLongArc() 
{
	if (g_dstSelMethod == 2 && b_upd == true)
	{
		m_location.m_fLongitude = m_longSign * (double(GetDlgItemInt(IDC_LONG_DEG)) + double(GetDlgItemInt(IDC_LONG_ARC))/60.0);	
		UpdateDstByTimezone(m_location.m_fTimezone);
	}
}

void DlgGetLocation::OnChangeLongDeg() 
{
	if (g_dstSelMethod == 2 && b_upd == true)
	{
		m_location.m_fLongitude = m_longSign * (double(GetDlgItemInt(IDC_LONG_DEG)) + double(GetDlgItemInt(IDC_LONG_ARC))/60.0);	
		UpdateDstByTimezone(m_location.m_fTimezone);
	}
}

int DlgGetLocation::SetCurSelDST(int nID)
{
	int i, m = cDst.GetCount();

	m_nLastDst = nID;
	for(i = 0; i< m; i++)
	{
		if (cDst.GetItemData(i) == nID)
		{
			cDst.SetCurSel(i);
			UpdateDSTInfo();
			return 1;
		}
	}

	m_nLastDst = 0;
	cDst.SetCurSel(0);

	UpdateDSTInfo();
	return 0;
}

void DlgGetLocation::OnChangeLocation() 
{
	CheckDlgButton(IDC_CHECK1, 1);	
}

HBRUSH DlgGetLocation::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF redColor = RGB(255,0,0);
	COLORREF blackColor = RGB(0,0,0);

	// TODO:  Change any attributes of the DC here
	if (nCtlColor == CTLCOLOR_EDIT)
	{

		BOOL wrongLongDeg = GetDlgItemInt(IDC_LONG_DEG) > 180;
		BOOL wrongLongArc = GetDlgItemInt(IDC_LONG_ARC) > 59;
		BOOL wrongLatiDeg = GetDlgItemInt(IDC_LATI_DEG) > 90;
		BOOL wrongLatiArc = GetDlgItemInt(IDC_LATI_ARC) > 59;

		wrongCoordinates = wrongLatiArc | wrongLatiDeg | wrongLongArc | wrongLongDeg;

		if (pWnd->GetDlgCtrlID() == IDC_LONG_ARC) {
			pDC->SetTextColor(wrongLongArc ? redColor : blackColor);
			if (wrongLongArc) cDstInfo.SetWindowTextA("Longitude Minutes must be from range 0 - 59");
		} else if (pWnd->GetDlgCtrlID() == IDC_LONG_DEG) {
			pDC->SetTextColor(wrongLongDeg ? redColor : blackColor);
			if (wrongLongDeg) cDstInfo.SetWindowTextA("Longitude Degrees must be from range 0 - 180");
		} else if (pWnd->GetDlgCtrlID() == IDC_LATI_ARC) {
			pDC->SetTextColor(wrongLatiArc ? redColor : blackColor);
			if (wrongLatiArc) cDstInfo.SetWindowTextA("Latitude Minutes must be from range 0 - 59");
		} else if (pWnd->GetDlgCtrlID() == IDC_LATI_DEG) {
			pDC->SetTextColor(wrongLatiDeg ? redColor : blackColor);
			if (wrongLatiDeg) cDstInfo.SetWindowTextA("Latitude Degrees must be from range 0 - 90");
		}

		if (!wrongCoordinates) UpdateDSTInfo();
	}

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		if (pWnd->GetDlgCtrlID() == IDC_DST_INFO){
			pDC->SetTextColor(wrongCoordinates ? redColor : blackColor);
		}
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
