// FrameLocs.cpp: implementation of the CFrameLocs class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "vcal5beta.h"
#include "FrameLocs.h"
#include "FrameServer.h"
#include "TCountry.h"
#include "TTimeZone.h"
#include "DlgEditLocation.h"
#include "TFile.h"
#include "avc.h"
#include "DNewCountry.h"
#include "DlgRenameCountry.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CLocationRef gMyLocation;
extern CLocationRef gLastLocation;

extern GCalApp theApp;

BEGIN_MESSAGE_MAP(CFrameLocs, CFrameWnd)
	//{{AFX_MSG_MAP(CFrameLocs)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_LOCATION_CREATELOCATION, OnLocationCreatelocation)
	ON_UPDATE_COMMAND_UI(ID_LOCATION_CREATELOCATION, OnUpdateLocationCreatelocation)
	ON_COMMAND(ID_LOCATION_DELETELOCATION, OnLocationDeletelocation)
	ON_UPDATE_COMMAND_UI(ID_LOCATION_DELETELOCATION, OnUpdateLocationDeletelocation)
	ON_COMMAND(ID_LOCATION_EDITLOCATION, OnLocationEditlocation)
	ON_UPDATE_COMMAND_UI(ID_LOCATION_EDITLOCATION, OnUpdateLocationEditlocation)
	ON_COMMAND(ID_LIST_IMPORT, OnListImport)
	ON_UPDATE_COMMAND_UI(ID_LIST_IMPORT, OnUpdateListImport)
	ON_COMMAND(ID_LIST_RESET, OnListReset)
	ON_COMMAND(ID_GOOGLE_SHOWLOCATION, OnGoogleShowlocation)
	ON_COMMAND(ID_FILE_EXPORTLIST, OnFileExportlist)
	ON_COMMAND(ID_FILE_CLOSEWINDOW, OnFileClosewindow)
	ON_UPDATE_COMMAND_UI(ID_GOOGLE_SHOWLOCATION, OnUpdateGoogleShowlocation)
	ON_WM_SIZE()
	ON_COMMAND(ID_COUNTRY_ADDCOUNTRY, OnCountryAddcountry)
	ON_COMMAND(ID_COUNTRY_RENAMECOUNTRY, OnCountryRenamecountry)
	ON_COMMAND(ID_HELP_HELP, OnHelpHelp)
	ON_UPDATE_COMMAND_UI(ID_HELP_HELP, OnUpdateHelpHelp)
	ON_COMMAND(ID_HELP_HELPTOPICTHISWINDOW, OnHelpHelptopicthiswindow)
	ON_UPDATE_COMMAND_UI(ID_HELP_HELPTOPICTHISWINDOW, OnUpdateHelpHelptopicthiswindow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



extern int g_nCurrentCountry;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFrameLocs::CFrameLocs()
{
	NONCLIENTMETRICS ncm;
	ncm.cbSize = sizeof(NONCLIENTMETRICS);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &ncm, 0);
	m_fontMnu.CreateFontIndirect(&(ncm.lfMenuFont));
}

CFrameLocs::~CFrameLocs()
{
	m_fontMnu.DeleteObject();
}

BOOL CFrameLocs::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	switch(LOWORD(wParam))
	{
	case 121:
		if (HIWORD(wParam)==CBN_SELENDOK)
		{
			g_nCurrentCountry = GetCountrySelected();
			InitCityByCountry(g_nCurrentCountry);
		}
		break;
	case 120:
		break;
	default:
		break;
	}
	return CFrameBase::OnCommand(wParam, lParam);
}

int CFrameLocs::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	int tabs[] = {175, 290, 350, 410, 470};
	CRect rcClient, rcCond, rcCount, rcBtn;
	GetClientRect(&rcClient);

//	m_wndTab.Create(WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE, rcClient, this, 120);
//	m_wndTab.InsertItem(0, "Locations");
//	m_wndTab.InsertItem(1, "Countries");
//	m_wndTab.InsertItem(2, "Preview");
//	m_wndTab.SetFont(&m_fontMnu);

//	m_wndTab.GetClientRect(&rcCond);

	// buttons
	// - New City
	rcBtn.SetRect(8, 8, 112, 36);
	m_wndBtn[0].Create("New City", WS_CHILD | WS_VISIBLE, rcBtn, this, ID_LOCATION_CREATELOCATION);
	m_wndBtn[0].SetFont(&m_fontMnu);

	// - Edit City
	rcBtn.OffsetRect(0, 40);
	m_wndBtn[1].Create("Edit City", WS_CHILD | WS_VISIBLE, rcBtn, this, ID_LOCATION_EDITLOCATION);
	m_wndBtn[1].SetFont(&m_fontMnu);

	// - Remove City
	rcBtn.OffsetRect(0, 40);
	m_wndBtn[2].Create("Remove City", WS_CHILD | WS_VISIBLE, rcBtn, this, ID_LOCATION_DELETELOCATION);
	m_wndBtn[2].SetFont(&m_fontMnu);

	// - Add Country
	rcBtn.OffsetRect(0, 60);
	m_wndBtn[3].Create("Add Country", WS_CHILD | WS_VISIBLE, rcBtn, this, ID_COUNTRY_ADDCOUNTRY);
	m_wndBtn[3].SetFont(&m_fontMnu);

	// - Edit Country
	rcBtn.OffsetRect(0, 40);
	m_wndBtn[4].Create("Rename Country", WS_CHILD | WS_VISIBLE, rcBtn, this, ID_COUNTRY_RENAMECOUNTRY);
	m_wndBtn[4].SetFont(&m_fontMnu);

	// - Import List
	rcBtn.OffsetRect(0, 60);
	m_wndBtn[5].Create("Import", WS_CHILD | WS_VISIBLE, rcBtn, this, ID_LIST_IMPORT);
	m_wndBtn[5].SetFont(&m_fontMnu);

	// - Export List
	rcBtn.OffsetRect(0, 40);
	m_wndBtn[6].Create("Export", WS_CHILD | WS_VISIBLE, rcBtn, this, ID_FILE_EXPORTLIST);
	m_wndBtn[6].SetFont(&m_fontMnu);

	// - Show Google
	rcBtn.OffsetRect(0, 40);
	m_wndBtn[7].Create("Show Google", WS_CHILD | WS_VISIBLE, rcBtn, this, ID_GOOGLE_SHOWLOCATION);
	m_wndBtn[7].SetFont(&m_fontMnu);

	rcCond = rcClient;
	rcCount = rcCond;
	rcCond.top += 48;
	rcCond.right -= 4;
	rcCond.left += 128;
	rcCond.bottom -= 4;
	rcCount.top+=24;
	rcCount.right = 480;
	rcCount.left  += 128;

	m_wndCountry.Create(WS_CHILD | WS_VISIBLE | CBS_SORT | WS_VSCROLL | CBS_DROPDOWNLIST | LBS_NOTIFY, rcCount, this, 121);
	m_wndCountry.SetFont(&m_fontMnu);

//	m_wndList.Create(WS_CHILD | WS_VSCROLL | LBS_SORT | LBS_USETABSTOPS | LBS_NOINTEGRALHEIGHT, rcCond, &m_wndTab, 122);
//	m_wndList.ModifyStyleEx(NULL, WS_EX_CLIENTEDGE);
//	m_wndList.SetFont( &m_fontMnu);
//	m_wndList.SetTabStops(5, tabs);

	m_wndLocs.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SORTASCENDING | LVS_NOSORTHEADER | LVS_SHOWSELALWAYS, rcCond, this, 320);
	m_wndLocs.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_wndLocs.InsertColumn(0, "City", LVCFMT_LEFT, 132,0);
	m_wndLocs.InsertColumn(1, "Country", LVCFMT_LEFT, 150,1);
	m_wndLocs.InsertColumn(2, "Latitude", LVCFMT_LEFT, 66,2);
	m_wndLocs.InsertColumn(3, "Longitude", LVCFMT_LEFT, 66,3);
	m_wndLocs.InsertColumn(4, "TimeZone", LVCFMT_LEFT, 175,4);

/*	m_wndCtrs.Create(WS_CHILD | LVS_REPORT | LVS_SORTASCENDING, rcCond, &m_wndTab, 324);
	m_wndCtrs.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_wndCtrs.InsertColumn(0, "Country", LVCFMT_LEFT, 300,1);
	m_wndCtrs.InsertColumn(1, "Code", LVCFMT_LEFT, 64,0);
	m_wndCtrs.InsertColumn(2, "Continent", LVCFMT_LEFT, 200,2);
*/

	//p_wndWeb = new CMyWebView;
	//p_wndWeb->Create(NULL, "WebView", WS_CHILD, rcCond, &m_wndTab, 124);
	//p_wndWeb->Navigate2("http://maps.google.com");


	InitCountries();
	SetCountrySelected(g_nCurrentCountry);
	InitCityByCountry(g_nCurrentCountry);

	return 0;
}

void CFrameLocs::OnDestroy() 
{
/*	TRACE2("Locs column %d ==> %d\n", 0, m_wndLocs.GetColumnWidth(0));
	TRACE2("Locs column %d ==> %d\n", 1, m_wndLocs.GetColumnWidth(1));
	TRACE2("Locs column %d ==> %d\n", 2, m_wndLocs.GetColumnWidth(2));
	TRACE2("Locs column %d ==> %d\n", 3, m_wndLocs.GetColumnWidth(3));
	TRACE2("Locs column %d ==> %d\n", 4, m_wndLocs.GetColumnWidth(4));*/
//	if (p_wndWeb)
//		delete p_wndWeb;
//	p_wndWeb = NULL;

	CFrameBase::OnDestroy();
	
	// TODO: Add your message handler code here
	theFrameServer.RemoveFromLocs();
}


void CFrameLocs::InitCountries()
{
	int i, m, a;

//	m_wndCtrs.DeleteAllItems();
	m_wndCountry.ResetContent();
	m = TCountry::GetCountryCount();
	for(i = 0; i < m; i++)
	{
		a = m_wndCountry.AddString(TCountry::GetCountryNameByIndex(i));
		m_wndCountry.SetItemData(a, TCountry::gcountries_var[i].code);

/*		d = m_wndCtrs.InsertItem(0, TCountry::gcountries_var[i].pszName);
		m_wndCtrs.SetItemText(d, 1, TCountry::gcountries_var[i].pszAcr);
		m_wndCtrs.SetItemText(d, 2, TCountry::gcontinents[TCountry::gcountries_var[i].continent]);
		m_wndCtrs.SetItemData(d, TCountry::gcountries_var[i].code);
*/
	}
	m_wndCountry.InsertString(0, "<all countries>");
}

void CFrameLocs::SetCountrySelected(int nCode)
{
	int i, m = m_wndCountry.GetCount();
	for(i = 0; i < m; i++)
	{
		if ((unsigned)nCode == m_wndCountry.GetItemData(i))
		{
			m_wndCountry.SetCurSel(i);
			return;
		}
	}
	return;
}

void CFrameLocs::InitCityByCountry(int nCode)
{
	CLocation *L = theLocs.GetHeadPosition();
	TString sc;
	if (nCode != 0)
	{
		sc = TCountry::GetCountryName(nCode);
	}

	m_wndLocs.DeleteAllItems();

	while(L)
	{
		if (nCode == 0)
		{
			AddLocationStr(L);
		}
		else if (sc.CompareNoCase(L->m_strCountry)==0)
		{
			AddLocationStr(L);
		}
		L = L->next;
	}
}

void CFrameLocs::AddLocationStr(CLocation *L)
{
//	static char st_str[256];
	int i;

/*	sprintf(st_str, "%s\t%s\t%s\t%s\t%s", L->m_strCity.c_str(), L->m_strCountry.c_str(),
		EARTHDATA::GetTextLatitude(L->m_fLatitude), EARTHDATA::GetTextLongitude(L->m_fLongitude),
		TTimeZone::GetTimeZoneName(L->m_nDST));
	i = m_wndList.AddString(st_str);*/
	i = m_wndLocs.InsertItem(0, L->m_strCity.c_str());
	if (i >= 0)
	{
		m_wndLocs.SetItemText(i, 1, L->m_strCountry.c_str());
		m_wndLocs.SetItemText(i, 2, EARTHDATA::GetTextLatitude(L->m_fLatitude));
		m_wndLocs.SetItemText(i, 3, EARTHDATA::GetTextLongitude(L->m_fLongitude));
		m_wndLocs.SetItemText(i, 4, TTimeZone::GetTimeZoneName(L->m_nDST));
		m_wndLocs.SetItemData(i, (DWORD)L);
//		m_wndList.SetItemDataPtr(i, L);
	}
}


unsigned short int CFrameLocs::GetCountrySelected()
{
	int i = m_wndCountry.GetCurSel();
	if (i != CB_ERR)
		return (unsigned short int)m_wndCountry.GetItemData(i);
	else
		return 0;
}

void CFrameLocs::OnLocationCreatelocation() 
{
	// TODO: Add your command handler code here
//	int n, m;
	DlgEditLocation dlg;
	
	dlg.m_loc = new CLocation;
	if (dlg.m_loc == NULL)
	{
		MessageBox("Unable to create location. Try again please.", "Error during creation.");
	}

	if (dlg.DoModal() == IDOK)
	{
		theLocs.AddTail( dlg.m_loc );
//		m_wndList.ResetContent();
		InitCityByCountry( g_nCurrentCountry);
	}
	else
	{
		delete dlg.m_loc;
	}
	
}

void CFrameLocs::OnUpdateLocationCreatelocation(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CFrameLocs::OnLocationDeletelocation() 
{
	// TODO: Add your control notification handler code here
	int n;
	TString str;
	CLocation * loc;
	POSITION pos = m_wndLocs.GetFirstSelectedItemPosition();
	
	if (pos == NULL)
		return;
	
	n = m_wndLocs.GetNextSelectedItem(pos);
	if (n < 0)
		return;

	loc = (CLocation *)(m_wndLocs.GetItemData(n));
	if (loc == NULL)
		return;

	loc->SetTextB(str);
	str.Insert(0, "Do you want to remove location:\r\n\r\n");
	str += "\r\n\r\nfrom your list of locations?";

	if (AfxMessageBox(str, MB_YESNO) == IDYES)
	{
		theLocs.RemoveAt(loc);
		InitCityByCountry(g_nCurrentCountry);
		delete loc;
	}	
}

void CFrameLocs::OnUpdateLocationDeletelocation(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_wndLocs.GetFirstSelectedItemPosition() != NULL);
}

void CFrameLocs::OnLocationEditlocation() 
{
	// TODO: Add your command handler code here
	// TODO: Add your control notification handler code here
	int n;
	bool bUpdLastLoc = false;
	bool bUpdMyLoc = false;

	DlgEditLocation dlg;
	POSITION pos = m_wndLocs.GetFirstSelectedItemPosition();

	dlg.m_bEdit = TRUE;
	
	if (pos ==NULL || (n = m_wndLocs.GetNextSelectedItem(pos), n <0))
		return;

	dlg.m_loc = (CLocation *)(m_wndLocs.GetItemData(n));
	if (dlg.m_loc == NULL)
		return;

	if ((fabs(dlg.m_loc->m_fLatitude - gMyLocation.m_fLatitude)<0.001)
		&& (fabs(dlg.m_loc->m_fLongitude - gMyLocation.m_fLongitude)<0.001))
		bUpdMyLoc = true;

	if ((fabs(dlg.m_loc->m_fLatitude - gLastLocation.m_fLatitude)<0.001)
		&& (fabs(dlg.m_loc->m_fLongitude - gLastLocation.m_fLongitude)<0.001))
		bUpdLastLoc = true;

	if (dlg.DoModal() == IDOK)
	{
		m_wndLocs.SetItemText(n, 0, dlg.m_loc->m_strCity.c_str());
		m_wndLocs.SetItemText(n, 1, dlg.m_loc->m_strCountry.c_str());
		m_wndLocs.SetItemText(n, 2, EARTHDATA::GetTextLatitude(dlg.m_loc->m_fLatitude));
		m_wndLocs.SetItemText(n, 3, EARTHDATA::GetTextLongitude(dlg.m_loc->m_fLongitude));
		m_wndLocs.SetItemText(n, 4, TTimeZone::GetTimeZoneName(dlg.m_loc->m_nDST));
		// check is this location is gMyLocation or gLastLocation
		// if yes then change coordinates and names also in these variables
		if (bUpdLastLoc)
		{
			gLastLocation.m_fLatitude = dlg.m_loc->m_fLatitude;
			gLastLocation.m_fLongitude = dlg.m_loc->m_fLongitude;
			gLastLocation.m_fTimezone = dlg.m_loc->m_fTimezone;
			gLastLocation.m_nDST = dlg.m_loc->m_nDST;
			gLastLocation.m_strName.Format("%s [%s]", dlg.m_loc->m_strCity.c_str(),
				dlg.m_loc->m_strCountry.c_str());
			gLastLocation.m_strLatitude = EARTHDATA::GetTextLatitude(dlg.m_loc->m_fLatitude);
			gLastLocation.m_strLongitude = EARTHDATA::GetTextLongitude(dlg.m_loc->m_fLongitude);
			gLastLocation.m_strTimeZone = TTimeZone::GetTimeZoneOffsetText(dlg.m_loc->m_fTimezone);
		}

		if (bUpdMyLoc)
		{
			gMyLocation.m_fLatitude = dlg.m_loc->m_fLatitude;
			gMyLocation.m_fLongitude = dlg.m_loc->m_fLongitude;
			gMyLocation.m_fTimezone = dlg.m_loc->m_fTimezone;
			gMyLocation.m_nDST = dlg.m_loc->m_nDST;
			gMyLocation.m_strName.Format("%s [%s]", dlg.m_loc->m_strCity.c_str(),
				dlg.m_loc->m_strCountry.c_str());
			gMyLocation.m_strLatitude = EARTHDATA::GetTextLatitude(dlg.m_loc->m_fLatitude);
			gMyLocation.m_strLongitude = EARTHDATA::GetTextLongitude(dlg.m_loc->m_fLongitude);
			gMyLocation.m_strTimeZone = TTimeZone::GetTimeZoneOffsetText(dlg.m_loc->m_fTimezone);
			theFrameServer.RecalculateAllTodayScreens();
		}
		//InitCityByCountry( g_nCurrentCountry );
		//m_wndLocs.SetCurSel(n);
	}	
}

void CFrameLocs::OnUpdateLocationEditlocation(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_wndLocs.GetFirstSelectedItemPosition() != NULL);	
}

void CFrameLocs::OnListImport() 
{
	// TODO: Add your command handler code here
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
	m_wndLocs.DeleteAllItems(); // m_wndList.ResetContent();
	m_wndCountry.ResetContent();

	// setting the current country
	InitCountries();
	m_wndCountry.SetCurSel(g_nCurrentCountry = 0);

	InitCityByCountry(g_nCurrentCountry);

}

void CFrameLocs::OnUpdateListImport(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);	
}

void CFrameLocs::OnListReset() 
{
	// TODO: Add your command handler code here
	if (AfxMessageBox("Are you sure to revert list of locations to the internal build-in list of locations?", MB_YESNO) == IDYES)
	{
		theLocs.RemoveAll();
		theLocs.InitInternal();
//		InitCountries();
		// setting the current country
//		m_countries.SetCurSel(g_nCurrentCountry = 0);

		InitCityByCountry(g_nCurrentCountry);
	}	
}

void CFrameLocs::OnGoogleShowlocation() 
{
	// TODO: Add your command handler code here
	TString str;

	int n;
	CLocation * loc = NULL;
	POSITION pos;
	
	pos = m_wndLocs.GetFirstSelectedItemPosition();
	if (pos != NULL && (n = m_wndLocs.GetNextSelectedItem(pos),n>=0))
	{
		loc = (CLocation *)m_wndLocs.GetItemData(n);
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
/*			str.Format("http://maps.google.com/?ie=UTF8&ll=%f,%f&spn=0.774196,1.235962&z=10", loc->m_fLatitude, loc->m_fLongitude);
			if (p_wndWeb != NULL)
			{
				p_wndWeb->Navigate(str.c_str());
				m_wndTab.SetCurSel(1);
				ShowControlsForTab(1);
			}*/
		}
	}

	return;	
}

void CFrameLocs::OnFileExportlist() 
{
	// TODO: Add your command handler code here
	CFileDialog cfd(FALSE, "xml", NULL, OFN_OVERWRITEPROMPT, "XML file (*.xml)|*.xml|Text file (*.txt)|*.txt|Locations List (*.lox)|*.lox|Rich List Format (*.rl)|*.rl||");

	if (cfd.DoModal() != IDOK)
		return;

	// 0 = TXT, 1 = XML
	theLocs.SaveAs( cfd.GetPathName(), cfd.m_ofn.nFilterIndex);	
	
}

void CFrameLocs::OnFileClosewindow() 
{
	// TODO: Add your command handler code here
	DestroyWindow();
//	theFrameServer.m_pLocs = NULL;	
}

void CFrameLocs::OnUpdateGoogleShowlocation(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((m_wndLocs.GetFirstSelectedItemPosition() != NULL)/*&& (p_wndWeb != NULL)*/);	
}


BOOL CFrameLocs::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
/*	int nTabSel = 0;
	LPNMHDR ph = (LPNMHDR)lParam;

	switch(ph->code)
	{
	case TCN_SELCHANGE:
		if (ph->idFrom == 120)
		{
			nTabSel = m_wndTab.GetCurSel();
			ShowControlsForTab(nTabSel);
			switch(nTabSel)
			{
			case 0:
				break;
			case 1:
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
*/
	return CFrameBase::OnNotify(wParam, lParam, pResult);
}

#define ShowWndIfTab(a) (nTabSel==a ? SW_SHOW : SW_HIDE)

void CFrameLocs::ShowControlsForTab(int nTabSel)
{
	m_wndCountry.ShowWindow(ShowWndIfTab(0));
	m_wndLocs.ShowWindow(ShowWndIfTab(0));
//	m_wndCtrs.ShowWindow(ShowWndIfTab(1));
//	p_wndWeb->ShowWindow(ShowWndIfTab(2));
}

void CFrameLocs::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);

	CRect rcTab;
	CRect rcCond;

	GetClientRect(&rcCond);
//	m_wndTab.MoveWindow(&rcCond);

	//m_wndTab.GetClientRect(&rcCond);

	
	rcCond.top += 48;
	rcCond.right -= 4;
	rcCond.left += 128;
	rcCond.bottom -= 4;
	
	m_wndLocs.MoveWindow(&rcCond);
//	if (p_wndWeb)
//		p_wndWeb->MoveWindow(&rcCond);
}

void CFrameLocs::OnCountryAddcountry() 
{
	// TODO: Add your command handler code here
	DNewCountry dnc;

	if (dnc.DoModal() == IDOK)
	{
		TCountry::AddCountry(dnc.strCode, dnc.strName, dnc.nContinent);
	}
}

void CFrameLocs::OnCountryRenamecountry() 
{
	// TODO: Add your command handler code here
	DlgRenameCountry drc;
	
	if (drc.DoModal() == IDOK)
	{
		InitCountries();
		SetCountrySelected(g_nCurrentCountry);
		InitCityByCountry(g_nCurrentCountry);
	}
}

void CFrameLocs::OnHelpHelp() 
{
	// TODO: Add your command handler code here
	GCalShowHelp("index.htm");
	
}

void CFrameLocs::OnUpdateHelpHelp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(theApp.m_bHelpAvailable);	
	
}

void CFrameLocs::OnHelpHelptopicthiswindow() 
{
	// TODO: Add your command handler code here
	GCalShowHelp("ref-locman.htm");
	
}

void CFrameLocs::OnUpdateHelpHelptopicthiswindow(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(theApp.m_bHelpAvailable);	
	
}
