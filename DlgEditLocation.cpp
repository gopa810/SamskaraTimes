// DlgEditLocation.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "DlgEditLocation.h"
#include "level_0.h"
#include "vedic_ui.h"
#include "TTimeZone.h"
#include "TCountry.h"
#include "TLocation.h"
#include "strings.h"
#include "GCStrings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const char * AvcGetEarthPosFromString(const char * str, bool bNorth, double &Longitude);

/////////////////////////////////////////////////////////////////////////////
// DlgEditLocation dialog


DlgEditLocation::DlgEditLocation(CWnd* pParent /*=NULL*/)
	: CDialog(DlgEditLocation::IDD, pParent)
{
	m_bEdit = FALSE;
	errLong = FALSE;
	errLati = FALSE;
	lastLatiAnalyse = NULL;
	lastLongAnalyse = NULL;
	//{{AFX_DATA_INIT(DlgEditLocation)
	//}}AFX_DATA_INIT
}


void DlgEditLocation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgEditLocation)
	DDX_Control(pDX, IDC_EDIT5, cCity);
	DDX_Control(pDX, IDC_COMBO_COUNTRY, cCountry);
	DDX_Control(pDX, IDC_COMBO_DST, cDst);
	DDX_Control(pDX, IDC_EDIT6, cNote);
	DDX_Control(pDX, IDC_EDIT3, cLong);
	DDX_Control(pDX, IDC_EDIT1, cLat);
	DDX_Control(pDX, IDC_DST_INFO, cDstInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgEditLocation, CDialog)
	//{{AFX_MSG_MAP(DlgEditLocation)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeEdit5)
	ON_CBN_SELENDOK(IDC_COMBO_COUNTRY, OnSelendokComboCountry)
	ON_CBN_SELENDOK(IDC_COMBO_DST, OnSelendokComboDst)
	ON_CBN_EDITCHANGE(IDC_COMBO_COUNTRY, OnEditchangeComboCountry)
	ON_CBN_DROPDOWN(IDC_COMBO_DST, OnDropdownComboDst)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgEditLocation message handlers

BOOL DlgEditLocation::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_nLastDst = 0;

	if (m_bEdit)
	{
		SetWindowText("Edit Location");
		GetDlgItem(IDOK)->SetWindowText("OK");
	}
	// init of combo boxes
	int n, m = TTimeZone::GetTimeZoneCount(), c;
	TString str;

	for(n = 0; n < m; n++)
	{
		c = cDst.AddString(TTimeZone::gzone[n].name);
		cDst.SetItemData(c, TTimeZone::gzone[n].idx);
	}

	cLat.SetWindowText(EARTHDATA::GetTextLatitude(m_loc->m_fLatitude));
	cLong.SetWindowText(EARTHDATA::GetTextLongitude(m_loc->m_fLongitude));
	//cTimezone.SetCurSel(AvcGetNearestTimeZone(m_loc->m_fTimezone));
	cCity.SetWindowText(m_loc->m_strCity);

	m = TCountry::GetCountryCount();
	for(n = 0; n < m; n++)
	{
		c = cCountry.AddString(TCountry::GetCountryNameByIndex(n));
		cCountry.SetItemData(c, TCountry::gcountries_var[n].code);
	}

	if (m_loc->m_strCountry.IsEmpty() == FALSE)
	{
		cCountry.SetCurSel(cCountry.FindString(-1, m_loc->m_strCountry));
	}

	LocationToDialog();

	cNote.SetWindowText("EXAMPLES\r\n\r\nLongitude: 05E25 23W50\r\nLatitude: 45N00 17S20");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgEditLocation::OnOK() 
{
//	UpdateData(TRUE);
	CString str;
	cCity.GetWindowText(str);
	m_loc->m_strCity = str;
	cCountry.GetWindowText(str);
	m_loc->m_strCountry = str;

	m_loc->m_nDST = cDst.GetItemData(cDst.GetCurSel());
	m_loc->m_fTimezone = TTimeZone::GetTimeZoneOffset(m_loc->m_nDST);
	
	CDialog::OnOK();
}

void DlgEditLocation::OnChangeEdit5() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString s;
	int i = 0;
	if (GetDlgItemText(IDC_EDIT5, s) > 0)
	{
		CComboBox * c = (CComboBox *)GetDlgItem(IDC_COMBO_COUNTRY);
		if (c->GetCurSel() >= 0)
			i = 1;
	}

	GetDlgItem(IDOK)->EnableWindow(i);
	
}

void DlgEditLocation::OnSelendokComboCountry() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString s;
	int i = 0;
	CComboBox * p;
	CComboBox * c;
	// pridava
	p = (CComboBox *)GetDlgItem(IDC_COMBO_DST);
	c = (CComboBox *)GetDlgItem(IDC_COMBO_COUNTRY);

	if (GetDlgItemText(IDC_EDIT5, s) > 0)
	{
		if (c->GetCurSel() >= 0)
			i = 1;
	}

	GetDlgItem(IDOK)->EnableWindow(i);
	

	// v s je country
	// s -> country_id
//	int n, nc;
	WORD country_id = 0;

	country_id = (WORD)c->GetItemData( c->GetCurSel());

	int n_id = -1;//, index;

	if (p)
	{
		//p->ResetContent();
		// country_id -> list of timezones
//		nc = TLocation::GetLocationCount();
//		for(n = 0; n < nc; n++)
//		{
//			if (TLocation::gloc[n].country_code == country_id)
//			{
//				n_id = TLocation::gloc[n].timezone_id;
//				if (p->FindString(-1, TTimeZone::GetTimeZoneName(n_id)) == CB_ERR)
//				{
//					index = p->AddString(TTimeZone::GetTimeZoneName(n_id));
//					p->SetItemData(index, n_id);
//				}
//			}
//		}

//		if (p->GetCount() < 1)
//		{
//			p->AddString("Undefined");
//		}

//		p->SetCurSel(0);
	}

	if (n_id >= 0)
	{
		UpdateDstByTimezone(TTimeZone::GetTimeZoneOffset(n_id));
	}
	
}

void DlgEditLocation::OnSelendokComboDst() 
{
	UpdateDSTInfo();
}

void DlgEditLocation::OnEditchangeComboCountry() 
{

}

extern int g_dstSelMethod;

int DlgEditLocation::UpdateDstByTimezone(double tzone)
{
	return 1;
}

void DlgEditLocation::UpdateDSTInfo()
{
	TString str, ret;

	int i = cDst.GetItemData( cDst.GetCurSel() );

	if (i < 0 || i >= TTimeZone::GetTimeZoneCount())
		return;

	DWORD dw = TTimeZone::gzone[TTimeZone::ID2INDEX(i)].val;

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

void DlgEditLocation::OnDropdownComboDst() 
{
	// TODO: Add your control notification handler code here
	//UpdateDstByTimezone(AvcGetTimeZone(m_nTimezone));
	
}

void DlgEditLocation::LocationToDialog()
{
	//int n, c, m, sel, null;

	cLat.SetWindowText( EARTHDATA::GetTextLatitude(m_loc->m_fLatitude) );
	cLong.SetWindowText( EARTHDATA::GetTextLongitude(m_loc->m_fLongitude) );

	/*m = cDst.GetCount();
	sel = -1;
	for(n =0; n < m; n++)
	{
		c = cDst.GetItemData(n);
		if (c == m_loc->m_nDST)
		{
			sel = n;
			break;
		}
		else if (c == 0)
		{
			null = n;
			break;
		}
	}

	cDst.SetCurSel(sel < 0 ? null : sel);*/
	cDst.SetCurSel(TTimeZone::ID2INDEX(m_loc->m_nDST));
	UpdateDSTInfo();
}

void DlgEditLocation::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	double d;
	CString str;
	cLat.GetWindowText(str);
	lastLatiAnalyse = AvcGetEarthPosFromString(str, false, d);
	if (lastLatiAnalyse == NULL)
	{
		m_loc->m_fLatitude = d;
		UpdateDstByTimezone(m_loc->m_fTimezone);
	}

	if (lastLatiAnalyse == NULL) {
		if (lastLongAnalyse == NULL)
			cNote.SetWindowTextA("Coordinates are acceptable.");
		else
			cNote.SetWindowText(lastLongAnalyse);
	} else {
		CString str = lastLatiAnalyse;
		if (lastLongAnalyse != NULL)
		{
			str += "\n";
			str += lastLongAnalyse;
		}
		cNote.SetWindowTextA(str);
	}

	errLati = (lastLatiAnalyse != NULL);
	cLat.Invalidate();
	cNote.Invalidate();
}

void DlgEditLocation::OnChangeEdit3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	double d;
	CString str;
	cLong.GetWindowText(str);
	lastLongAnalyse = AvcGetEarthPosFromString(str, true, d);
	if (lastLongAnalyse == NULL)
	{
		m_loc->m_fLongitude = d;
		UpdateDstByTimezone(m_loc->m_fTimezone);
	}

	if (lastLatiAnalyse == NULL) {
		if (lastLongAnalyse == NULL)
			cNote.SetWindowTextA("Coordinates are acceptable.");
		else
			cNote.SetWindowText(lastLongAnalyse);
	} else {
		CString str = lastLatiAnalyse;
		if (lastLongAnalyse != NULL)
		{
			str += "\n";
			str += lastLongAnalyse;
		}
		cNote.SetWindowTextA(str);
	}

	errLong = (lastLongAnalyse != NULL);
	cLong.Invalidate();
	cNote.Invalidate();
}

HBRUSH DlgEditLocation::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	COLORREF redColor = RGB(255,0,0);
	COLORREF blackColor = RGB(0,0,0);

	// TODO:  Change any attributes of the DC here
	if (nCtlColor == CTLCOLOR_EDIT)
	{
		if (pWnd->GetDlgCtrlID() == IDC_EDIT1) {
			pDC->SetTextColor(errLati ? redColor : blackColor);
		} else if (pWnd->GetDlgCtrlID() == IDC_EDIT3) {
			pDC->SetTextColor(errLong ? redColor : blackColor);
		}
		if (pWnd->GetDlgCtrlID() == IDC_EDIT6){
			pDC->SetTextColor((errLong || errLati) ? redColor : blackColor);
		}

	}

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		if (pWnd->GetDlgCtrlID() == IDC_EDIT6){
			pDC->SetTextColor((errLong || errLati) ? redColor : blackColor);
		}
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
