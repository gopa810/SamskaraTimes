// DlgGetLocationEx.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "DlgGetLocationEx.h"
#include "DlgEditLocation.h"
#include "Location.h"
#include "TFile.h"
#include "avc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define ID_MENU_CREATELOC 0x100
#define ID_MENU_EDITLOC   0x101
#define ID_MENU_DELETELOC 0x102
#define ID_MENU_IMPORTLIST 0x110
#define ID_MENU_RESETLIST  0x111
#define ID_MENU_SHOWGMAPS  0x112
#define ID_MENU_IMPORTGMAPS 0x113


const char * GCalApp_GetFileName(int i);

/////////////////////////////////////////////////////////////////////////////
// DlgGetLocationEx dialog


DlgGetLocationEx::DlgGetLocationEx(CWnd* pParent /*=NULL*/)
	: CDialog(DlgGetLocationEx::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgGetLocationEx)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgGetLocationEx::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgGetLocationEx)
	DDX_Control(pDX, IDC_LIST1, m_cities);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_COMBO1, m_countries);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgGetLocationEx, CDialog)
	//{{AFX_MSG_MAP(DlgGetLocationEx)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_CBN_SELENDOK(IDC_COMBO1, OnSelendokCombo1)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON4, OnSetCountryByCity)
	ON_BN_CLICKED(IDC_BUTTON5, OnAllCities)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_CBN_SELENDCANCEL(IDC_COMBO1, OnSelendcancelCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*
	ON_BN_CLICKED(IDC_BUTTON1, OnCreateLocation)
	ON_BN_CLICKED(IDC_BUTTON2, OnEditLocation)
	ON_BN_CLICKED(IDC_BUTTON3, OnDeleteLocation)
	ON_BN_CLICKED(IDC_BUTTON6, OnResetList)
*/

int g_nCurrentCountry = 0;

/////////////////////////////////////////////////////////////////////////////
// DlgGetLocationEx message handlers

BOOL DlgGetLocationEx::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int tabs[] = {185, 245, 305};
	int nCurrentCountry = g_nCurrentCountry;

	m_cities.SetTabStops(3, tabs);

	InitCountries();

	// setting the current country
	m_countries.SetCurSel(nCurrentCountry);

	InitCitiesForCountry(nCurrentCountry);

	m_menu.CreatePopupMenu();

	m_menu.AppendMenu(MF_STRING, ID_MENU_CREATELOC, "Create Location");
	m_menu.AppendMenu(MF_STRING, ID_MENU_EDITLOC,   "Edit Location");
	m_menu.AppendMenu(MF_STRING, ID_MENU_DELETELOC, "Delete Location");
	m_menu.AppendMenu(MF_STRING, ID_MENU_SHOWGMAPS, "Show Location in Google Maps");
	m_menu.AppendMenu(MF_SEPARATOR);
	m_menu.AppendMenu(MF_STRING, ID_MENU_IMPORTLIST, "Import List");
//	m_menu.AppendMenu(MF_STRING, ID_MENU_IMPORTGMAPS, "Import from Google Maps");
	m_menu.AppendMenu(MF_SEPARATOR);
	m_menu.AppendMenu(MF_STRING, ID_MENU_RESETLIST, "Reset List");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgGetLocationEx::OnCreateLocation() 
{
	// TODO: Add your control notification handler code here
	int n, m;
	DlgEditLocation dlg;
	
	dlg.m_loc = new CLocation;
	if (dlg.m_loc == NULL)
	{
		MessageBox("Unable to create location. Try again please.", "Error during creation.");
	}

	if (dlg.DoModal() == IDOK)
	{
		theLocs.AddTail( dlg.m_loc );
		m_countries.ResetContent();
		m_cities.ResetContent();
		n = InitCountries( dlg.m_loc->m_strCountry );
		m = InitCitiesForCountry( (n > 0 ? n : 0), dlg.m_loc->m_strCity);

		m_countries.SetCurSel(n);
		if (m >= 0)
			m_cities.SetCurSel(m);
		g_nCurrentCountry = n;
	}
	else
	{
		delete dlg.m_loc;
	}

//	dlg.SetDefID(IDOK);
}

void DlgGetLocationEx::OnEditLocation() 
{
	// TODO: Add your control notification handler code here
	int n, m;
	DlgEditLocation dlg;

	dlg.m_bEdit = TRUE;
	
	n = m_cities.GetCurSel();
	if (n == LB_ERR)
		return;

	dlg.m_loc = (CLocation *)(m_cities.GetItemData(n));
	if (dlg.m_loc == NULL)
		return;

	if (dlg.DoModal() == IDOK)
	{
		m_countries.ResetContent();
		m_cities.ResetContent();
		n = InitCountries( dlg.m_loc->m_strCountry );
		if (g_nCurrentCountry == 0)
			n = 0;
		m = InitCitiesForCountry( n, dlg.m_loc->m_strCity);

		m_countries.SetCurSel(n);
		if (m < 0)
		{
		}
		else
			m_cities.SetCurSel(m);
	}

//	dlg.SetDefID(IDOK);
	
}

void DlgGetLocationEx::OnDeleteLocation() 
{
	// TODO: Add your control notification handler code here
	int n, m;
	TString str;
	CLocation * loc;
	
	n = m_cities.GetCurSel();
	if (n == LB_ERR)
		return;

	loc = (CLocation *)(m_cities.GetItemData(n));
	if (loc == NULL)
		return;

	loc->SetTextB(str);
	str.Insert(0, "Do you want to remove location:\r\n\r\n");
	str += "\r\n\r\nfrom your list of locations?";

	if (AfxMessageBox(str, MB_YESNO) == IDYES)
	{
		theLocs.RemoveAt(loc);
		m_countries.ResetContent();
		m_cities.ResetContent();
		n = InitCountries( loc->m_strCountry );
		if ((g_nCurrentCountry == 0) || (n < 0))
			n = 0;
		m = InitCitiesForCountry( n );

		m_countries.SetCurSel(n);
		if (m < 0)
		{
		}
		else
			m_cities.SetCurSel(m);
		delete loc;
	}
}

void DlgGetLocationEx::OnChangeEdit1() 
{
	CString str;

	m_edit.GetWindowText(str);

	int n = m_cities.FindString(-1, str);

	if (n != LB_ERR)
	{
		m_cities.SetCurSel(n);
		m_lc = (CLocation *)(m_cities.GetItemData(n));
	}
}

void DlgGetLocationEx::OnSelendokCombo1() 
{
	g_nCurrentCountry = m_countries.GetCurSel();
	
	InitCitiesForCountry(g_nCurrentCountry);

}

void DlgGetLocationEx::OnSelchangeList1() 
{
	int n;
	TString str;
	
	n = m_cities.GetCurSel();
	m_lc = (CLocation *)(m_cities.GetItemData(n));

	m_lc->SetTextA(str);

	m_edit.SetWindowText(str);
}

int  DlgGetLocationEx::InitCitiesForCountry(int nCurrentCountry, const char * pszCurrentCity)
{
	int h, retVal = 0;
	TString city;
	CString country, str;
	CLocation * pos, * pos_old;

	m_cities.ResetContent();

	// getting current selection
	if (nCurrentCountry != 0)
	{
		m_countries.GetLBText(nCurrentCountry, country);
	}

	pos = theLocs.GetHeadPosition();
	while(pos)
	{
		pos_old = pos;
		CLocation &loc = *pos;
		loc.SetTextB( city );
		if (nCurrentCountry == 0)
		{
			h = m_cities.AddString( city );
			if (pszCurrentCity != NULL)
			{
				if (loc.m_strCity.CompareNoCase( pszCurrentCity) == 0)
				{
					retVal = h;
				}
			}
			m_cities.SetItemDataPtr(h, pos_old);
		}
		else if ((loc.m_strCountry.IsEmpty() == FALSE) && (country == loc.m_strCountry.c_str()))
		{
			h = m_cities.AddString( city );
			if (pszCurrentCity != NULL)
			{
				if (loc.m_strCity.CompareNoCase( pszCurrentCity) == 0)
				{
					retVal = h;
				}
			}
			m_cities.SetItemDataPtr(h, pos_old);
		}
		pos = pos->next;
	}

	m_edit.SetWindowText("");
	m_edit.SetFocus();

	return retVal;
}

int DlgGetLocationEx::InitCountries(const char * pszCurrentCountry)
{
	CMapStringToPtr map;
	LPVOID ptr, pbase = NULL;
	int n, retVal = -1;
	
	TString city, country;
	CLocation * pos, * pos_old;
	pos = theLocs.GetHeadPosition();
	//
	// initializes list of countries
	m_countries.AddString("< all cities >");
	while(pos)
	{
		pos_old = pos;
		CLocation & loc = *pos;
		if (loc.m_strCountry.IsEmpty() == FALSE)
		{
			if (map.Lookup(loc.m_strCountry, ptr) == FALSE)
			{
				n = m_countries.AddString(loc.m_strCountry);
				map.SetAt(loc.m_strCountry, pbase);
			}
		}
		pos = pos->next;
	}
	if (pszCurrentCountry != NULL)
	{
		retVal = m_countries.FindString(-1, pszCurrentCountry);
	}
	
	return retVal;
}

void DlgGetLocationEx::OnSetCountryByCity() 
{
	// TODO: Add your control notification handler code here
	int n;
	CLocation * pos;
	TString str;
	
	n = m_cities.GetCurSel();
	if (n == LB_ERR)
		return;

	pos = (CLocation *)(m_cities.GetItemData(n));
	if (pos == NULL)
		return;

	g_nCurrentCountry = n = m_countries.FindString(-1, pos->m_strCountry);
	m_countries.SetCurSel(n);
	OnSelendokCombo1();

	n = m_cities.FindString(-1, pos->m_strCity);
	if (n != LB_ERR)
	{
		m_cities.SetCurSel(n);
		OnSelchangeList1();
	}


}

void DlgGetLocationEx::OnAllCities() 
{
	// TODO: Add your control notification handler code here
	int n;
	TString str;
	CLocation * loc = NULL;
	
	n = m_cities.GetCurSel();
	if (n != LB_ERR)
	{
		loc = (CLocation *)(m_cities.GetItemData(n));
	}


	g_nCurrentCountry = 0;
	m_countries.SetCurSel(0);
	OnSelendokCombo1();

	if (loc)
	{
		n = m_cities.FindString(-1, loc->m_strCity);
		if (n != LB_ERR)
		{
			m_cities.SetCurSel(n);
			OnSelchangeList1();
		}
	}
	
}

void DlgGetLocationEx::OnResetList() 
{
	if (AfxMessageBox("Are you sure to revert list of locations to the internal build-in list of locations?", MB_YESNO) == IDYES)
	{
		theLocs.RemoveAll();
		theLocs.InitInternal();
		InitCountries();

		// setting the current country
		m_countries.SetCurSel(g_nCurrentCountry = 0);

		InitCitiesForCountry(g_nCurrentCountry);
//		GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
//		GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	}
}

void DlgGetLocationEx::OnButton7() 
{
	// TODO: Add your control notification handler code here
	int n = m_cities.GetCurSel();
	
	BOOL bEnable = ((n != LB_ERR) ? MF_ENABLED : MF_GRAYED);


	m_menu.EnableMenuItem(ID_MENU_EDITLOC, bEnable | MF_BYCOMMAND);
	m_menu.EnableMenuItem(ID_MENU_DELETELOC, bEnable | MF_BYCOMMAND);
	m_menu.EnableMenuItem(ID_MENU_SHOWGMAPS, bEnable | MF_BYCOMMAND);

	POINT point;
	GetCursorPos(&point);
	//ScreenToClient(&point);
	m_menu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
}

BOOL DlgGetLocationEx::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	switch (wParam)
	{
	case ID_MENU_EDITLOC:
		OnEditLocation();
		break;
	case ID_MENU_DELETELOC:
		OnDeleteLocation();
		break;
	case ID_MENU_RESETLIST:
		OnResetList();
		break;
	case ID_MENU_CREATELOC:
		OnCreateLocation();
		break;
	case ID_MENU_IMPORTLIST:
		OnImportList();
		break;
	case ID_MENU_SHOWGMAPS:
		ShowInGoogleMaps();
		break;
	case ID_MENU_IMPORTGMAPS:
		break;
	default:
		break;
	}

	return CDialog::OnCommand(wParam, lParam);
}

void DlgGetLocationEx::OnImportList()
{
	int nResult = MessageBox("Import List of Locations:\r\n"
		"1. First step is to find the file with the list of locations\r\n"
		"2. Second step is to choose from importing methods (Add or Replace)\r\n"
		"\r\nDo you want to continue with importing?", "Import List", MB_YESNO);

	if (nResult == IDNO)
		return;

	// zadava subor
	CFileDialog fd(TRUE, ".gloc", NULL, OFN_FILEMUSTEXIST);

	if (fd.DoModal() == IDCANCEL)
		return;

	// voli metodu vlozenia
	nResult = MessageBox("Do you want to ADD selected location file to the current database of locations?\r\n"
		"Press YES for Adding, press NO for replacement of current database with imported file.\r\n"
		"Press CANCEL for not importing.", "Importing method", MB_YESNOCANCEL);

	if (nResult == IDCANCEL)
		return;

	// vklada
	if (theLocs.ImportFile(fd.GetPathName(), (nResult == IDNO)) == FALSE)
	{
		MessageBox("Importing of file was not succesful.", "Importing progress");
		return;
	}

	// opatovna inicializacia dialog boxu
	m_cities.ResetContent();
	m_countries.ResetContent();
	InitCountries();

	// setting the current country
	m_countries.SetCurSel(g_nCurrentCountry = 0);

	InitCitiesForCountry(g_nCurrentCountry);

	// koniec
}

BOOL DlgGetLocationEx::ShowInGoogleMaps()
{
	TString str;

	int n;
	CLocation * loc = NULL;
	
	n = m_cities.GetCurSel();
	if (n != LB_ERR)
	{
		loc = (CLocation *)m_cities.GetItemDataPtr(n);
		if (loc != NULL)
		{
			str.Format("<html><head><meta http-equiv=\"REFRESH\" content=\"0;url=http://maps.google.com/?ie=UTF8&ll=%f,%f&spn=0.774196,1.235962&z=10"
						   "\"></head><body></body><html>", loc->m_fLatitude, loc->m_fLongitude);
			TFile file;
			TString fileName;
			fileName = GCalApp_GetFileName(GSTR_TEMFOLDER);
			fileName += "temp.html";
			if (file.Open(fileName, "w") == TRUE)
			{
				file.WriteString(str);
				file.Close();
				ShellExecute(this->m_hWnd, NULL, fileName, NULL, NULL, SW_SHOW);
			}
		}
	}

	return TRUE;
}

void DlgGetLocationEx::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	
}

void DlgGetLocationEx::OnSelendcancelCombo1() 
{
	// TODO: Add your control notification handler code here
	//g_nCurrentCountry = m_countries.GetCurSel();
	
	//InitCitiesForCountry(g_nCurrentCountry);
	
}
