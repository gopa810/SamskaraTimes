// ConditionsView.cpp : implementation file
//

#include "stdafx.h"
#include "platform.h"
#include "vcal5beta.h"
#include "ConditionsView.h"
#include "level_6.h"
#include "strings.h"
#include "vedic_ui.h"
#include "locationref.h"
#include "dlggetlocation.h"

#include "GCStrings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConditionsView

CConditionsView::CConditionsView()
{
	memset(&ncm, 0, sizeof(NONCLIENTMETRICS));
	ncm.cbSize = sizeof(NONCLIENTMETRICS);

	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &ncm, 0);

	for(int i = 0; i < MAX_CONDS; i++)
	{
		m_evClass[i] = 0;
		m_evValue[i] = 0;
	}

	m_bMethodAnd = true;
}

CConditionsView::~CConditionsView()
{
}


BEGIN_MESSAGE_MAP(CConditionsView, CWnd)
	//{{AFX_MSG_MAP(CConditionsView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int AvcGetNextPartHash(TString &str, TString &strLine, int & i);
int AvcGetFestivalClass(TString &str);
int AvcClearStringFromTags(TString &str);

/////////////////////////////////////////////////////////////////////////////
// CConditionsView message handlers

int CConditionsView::GetProperHeight()
{
	return ncm.iScrollHeight*11;
}

CConditionsView::EventClass CConditionsView::m_eventClassList[] =
{
	{0, "<no condition>"},
	{1, "Mahadvadasi"},
	{2, "Sankranti"},
	{8, "Tithi"},
	{9, "Paksa"},
	{3, "Tithi + Paksa"},
	{4, "Naksatra"},
	{5, "Yoga"},
	{6, "Fasting Day"},
	{7, "Day of Week"},
	{10,"Appearance days of the Lord"},
	{11,"Events in the pastimes of the Lord"},
	{12,"App//Disapp of Recent Acaryas"},
	{13,"App//Disapp of Mahaprabhu's Associates and Other Acaryas"},
	{14,"ISKCON's Historical Events"},
	{15,"Bengal-specific Holidays"}
};

extern CLocationRef gLastLocation;

int CConditionsView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	int i, j, n;
	CRect rcClient;
	TString str;

	GetClientRect(&rcClient);

	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_comboFont.CreateFontIndirect(&(ncm.lfMenuFont));
	m_infoFont.CreateFontIndirect(&(ncm.lfCaptionFont));
	
	m_wnd_texts[3].Create("Type of Event to Find", WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(4, 2, rcClient.Width()*2/5, ncm.iCaptionHeight), this);
	m_wnd_texts[4].Create("Specific Event", WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(rcClient.Width()*2/5+4, 2, rcClient.Width()*4/5, ncm.iCaptionHeight), this);
	m_wnd_texts[3].SetFont(&m_infoFont);
	m_wnd_texts[4].SetFont(&m_infoFont);

	// TODO: Add your specialized creation code here
	for(i = 0; i < MAX_CONDS; i++)
	{
		m_c[i][0].Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST
			, CRect(4, ncm.iScrollHeight*(i*2 + 1), rcClient.Width()*2/5, 500)
			, this, i*2+100);
		m_c[i][1].Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST
			, CRect(rcClient.Width()*2/5 + 4, ncm.iScrollHeight*(i*2+1), rcClient.Width()*4/5, 500)
			, this, i*2+101);
		m_c[i][0].SetFont(&m_comboFont);
		m_c[i][1].SetFont(&m_comboFont);
	}

	m_buttons[2].Create("AND", WS_CHILD | WS_VISIBLE | BS_FLAT, CRect(0,0,0,0), this, 140);
	m_buttons[2].SetFont(&m_comboFont);

	for(j = 0; j < 3; j++)
	{
		for(i = 0; i < 16; i++)
		{
			n = m_c[j][0].AddString(m_eventClassList[i].pszTitle);
			m_c[j][0].SetItemData(n, m_eventClassList[i].nClass);
		}
		m_c[j][0].SetCurSel(m_evClass[j]);
	}

	for(i = 0; i < MAX_CONDS; i++)
	{
		NaplnComboBox(&(m_c[i][1]), m_evClass[i]);
		m_c[i][1].SetCurSel(m_evValue[i]);
	}

	CRect cr;
	SetFont(&m_comboFont);
	const char * pszTitle;
	CSize cs;
	CDC * pdc = GetDC();

	// row 1
	// button for setting location
	cr.SetRect(4, ncm.iScrollHeight*7-2, 100, ncm.iScrollHeight*8+2);
	m_buttons[0].Create("Set Location", WS_VISIBLE | WS_CHILD | BS_FLAT, cr, this, 130);
	m_buttons[0].SetFont(&m_comboFont);
	// location
	cr.left = 120;
	cr.right = 800;
	m_edits[0].Create(WS_VISIBLE | WS_CHILD | ES_READONLY, cr, this, 132);
	m_edits[0].SetFont(&m_infoFont);
	str.Format("%s (%s, %s, %s: %s)"
		, gLastLocation.m_strName.c_str()
		, gLastLocation.m_strLatitude.c_str()
		, gLastLocation.m_strLongitude.c_str()
		, GCStrings::getString(12).c_str()
		, gLastLocation.m_strTimeZone.c_str());
	m_earth = (EARTHDATA)gLastLocation;
	m_dst = gLastLocation.m_nDST;

	m_edits[0].SetWindowText(str);

	// row 2
	// start year
	cr.SetRect(4, ncm.iScrollHeight*9-2, 4, ncm.iScrollHeight*10+2);
	pszTitle = "Start Year:";
	cs = pdc->GetTextExtent(pszTitle, _tcslen(pszTitle));
	cr.right += cs.cx + 4;
	m_wnd_texts[0].Create(pszTitle, WS_VISIBLE | WS_CHILD | SS_CENTER, cr, this);
	m_wnd_texts[0].SetFont(&m_comboFont);
	cr.left = cr.right;

	// EDIT START YEAR
	SYSTEMTIME st;
	GetLocalTime(&st);
	str.Format("%d", st.wYear);
	cr.right = cr.left + 58;
	m_edits[1].Create(WS_BORDER | WS_VISIBLE | WS_CHILD | ES_NUMBER | ES_RIGHT, cr, this, 133);
	m_edits[1].SetFont(&m_comboFont);
	m_edits[1].SetWindowText(str);
	cr.left = cr.right + 4;

	// title count....
	pszTitle = "Count of Years:";
	cs = pdc->GetTextExtent(pszTitle, _tcslen(pszTitle));
	cr.right += cs.cx + 4;
	m_wnd_texts[1].Create(pszTitle, WS_VISIBLE | WS_CHILD | SS_CENTER, cr, this);
	m_wnd_texts[1].SetFont(&m_comboFont);
	cr.left = cr.right;

	// EDIT COUNT YEARS
	cr.right = cr.left + 58;
	m_edits[2].Create(WS_BORDER | WS_VISIBLE | WS_CHILD | ES_NUMBER | ES_RIGHT, cr, this, 134);
	m_edits[2].SetFont(&m_comboFont);
	m_edits[2].SetWindowText("2");
	cr.left = cr.right + 4;

	// button FIND
	cr.right = cr.left + 64;
	m_buttons[1].Create("Find", WS_VISIBLE | WS_CHILD | BS_FLAT, cr, this, 131);
	m_buttons[1].SetFont(&m_comboFont);

	return 0;
}

int NaplnComboFestivalom(CComboBox * pc, int nClass)
{
	int i, j, n;
	TString s1;

	for(i = 200; i < 560; i++)
	{
		j = 0;
		while(AvcGetNextPartHash(GCStrings::getString(i), s1, j))
		{
			n = AvcGetFestivalClass(s1);
			if (n == (nClass - 10))
			{
				AvcClearStringFromTags(s1);
				n = pc->AddString(s1);
				pc->SetItemData(n, i);
			}
		}
	}
	n = pc->InsertString(0, "<all events>");
	pc->SetItemData(n, 0xffff);

	return 0;
}

int CConditionsView::NaplnComboBox(CComboBox *pc, int nClass)
{
	int i, j, n;
	TString s1, s2;

	switch(nClass)
	{
	case 0:
		pc->ResetContent();
		pc->AddString("<no condition>");
		break;
	case 1:
		pc->ResetContent();
		n = pc->AddString(GCStrings::getString(38));
		pc->SetItemData(n, EV_NULL);
		n = pc->AddString(GCStrings::GetMahadvadasiName(EV_UNMILANI));
		pc->SetItemData(n, EV_UNMILANI);
		n = pc->AddString(GCStrings::GetMahadvadasiName(EV_TRISPRSA));
		pc->SetItemData(n, EV_TRISPRSA);
		n = pc->AddString("Unmilani Trisprsa Mahadvadasi");
		pc->SetItemData(n, EV_UNMILANI_TRISPRSA);
		n = pc->AddString(GCStrings::GetMahadvadasiName(EV_PAKSAVARDHINI));
		pc->SetItemData(n, EV_PAKSAVARDHINI);
		n = pc->AddString(GCStrings::GetMahadvadasiName(EV_JAYA));
		pc->SetItemData(n, EV_JAYA);
		n = pc->AddString(GCStrings::GetMahadvadasiName(EV_VIJAYA));
		pc->SetItemData(n, EV_VIJAYA);
		n = pc->AddString(GCStrings::GetMahadvadasiName(EV_PAPA_NASINI));
		pc->SetItemData(n, EV_PAPA_NASINI);
		n = pc->AddString(GCStrings::GetMahadvadasiName(EV_JAYANTI));
		pc->SetItemData(n, EV_JAYANTI);
		n = pc->AddString(GCStrings::GetMahadvadasiName(EV_VYANJULI));
		pc->SetItemData(n, EV_VYANJULI);
		break;
	case 2:
		pc->ResetContent();
		pc->AddString(GCStrings::getString(132));
		pc->SetItemData(0, 0xff);
		for(i = 0; i < 12; i++)
		{
			s1.Format("%s (%s)", GCStrings::GetSankrantiName(i), GCStrings::GetSankrantiNameEn(i));
			j = pc->AddString(s1);
			pc->SetItemData(j, i);
		}
		break;
	case 3:
		pc->ResetContent();
		for(i = 0; i < 30; i++)
		{
			s1.Format("%s (%s Paksa)", GCStrings::GetTithiName(i), GCStrings::GetPaksaName(i/15));
			j = pc->AddString(s1);
			pc->SetItemData(j, i);
		}
		break;
	case 4:
		pc->ResetContent();
		for(i = 0; i < 27; i++)
		{
			s1.Format("%s Naksatra", GCStrings::GetNaksatraName(i));
			j = pc->AddString(s1);
			pc->SetItemData(j, i);
		}
		break;
	case 5:
		pc->ResetContent();
		for(i = 0; i < 27; i++)
		{
			s1.Format("%s Yoga", GCStrings::GetYogaName(i));
			j = pc->AddString(s1);
			pc->SetItemData(j, i);
		}
		break;
	case 6:
		pc->ResetContent();
		j = pc->AddString(GCStrings::getString(134).c_str());
		pc->SetItemData(j, 0);
		j = pc->AddString(GCStrings::getString(751).c_str());
		pc->SetItemData(j, 1);
		j = pc->AddString(GCStrings::getString(752).c_str());
		pc->SetItemData(j, 2);
		j = pc->AddString(GCStrings::getString(753).c_str());
		pc->SetItemData(j, 3);
		j = pc->AddString(GCStrings::getString(754).c_str());
		pc->SetItemData(j, 4);
		j = pc->AddString(GCStrings::getString(755).c_str());
		pc->SetItemData(j, 5);
		j = pc->AddString(GCStrings::getString(135).c_str());
		pc->SetItemData(j, 6);
		break;
	case 7:
		pc->ResetContent();
		for(i = 0; i < 7; i++)
		{
			pc->SetItemData(pc->AddString(GCStrings::getString(i).c_str()), i);
		}
		break;
	case 8:
		pc->ResetContent();
		for(i = 0; i < 14; i++)
		{
			pc->SetItemData(pc->AddString(GCStrings::getString(600 + i).c_str()), i);
		}
		s1.Format("%s//%s", GCStrings::getString(614).c_str(), GCStrings::getString(629).c_str());
		pc->SetItemData(pc->AddString(s1), 14);
		break;
	case 9:
		pc->ResetContent();
		pc->SetItemData(pc->AddString(GCStrings::getString(712).c_str()), 1);
		pc->SetItemData(pc->AddString(GCStrings::getString(713).c_str()), 0);
		break;
	case 10:
		pc->ResetContent();
		n = pc->AddString(GCStrings::GetSpecFestivalName(SPEC_JANMASTAMI));
		pc->SetItemData(n, 328);
		n = pc->AddString(GCStrings::GetSpecFestivalName(SPEC_GAURAPURNIMA));
		pc->SetItemData(n, 529);
		n = pc->AddString(GCStrings::GetSpecFestivalName(SPEC_RAMANAVAMI));
		pc->SetItemData(n, 554);
		NaplnComboFestivalom(pc, nClass);
		break;
	case 11:
		pc->ResetContent();
		n = pc->AddString(GCStrings::GetSpecFestivalName(SPEC_GOVARDHANPUJA));
		pc->SetItemData(n, 395);
		n = pc->AddString(GCStrings::GetSpecFestivalName(SPEC_RATHAYATRA));
		pc->SetItemData(n, 277);
		n = pc->AddString(GCStrings::GetSpecFestivalName(SPEC_NANDAUTSAVA));
		pc->SetItemData(n, 329);
//					f.WriteString("\" depends=\"Sri Krsna Janmastami\" rel=\"+1\"/>\n");
		n = pc->AddString(GCStrings::GetSpecFestivalName(SPEC_MISRAFESTIVAL));
		pc->SetItemData(n, 530);
//					f.WriteString("\" depends=\"Gaura Purnima\" rel=\"+1\"/>\n");
		n = pc->AddString(GCStrings::GetSpecFestivalName(SPEC_HERAPANCAMI));
		pc->SetItemData(n, 281);
//					f.WriteString("\" depends=\"Ratha Yatra\" rel=\"+4\"/>\n");
		n = pc->AddString(GCStrings::GetSpecFestivalName(SPEC_RETURNRATHA));
		pc->SetItemData(n, 285);
//					f.WriteString("\" depends=\"Ratha Yatra\" rel=\"+8\"/>\n");
		n = pc->AddString(GCStrings::GetSpecFestivalName(SPEC_GUNDICAMARJANA));
		pc->SetItemData(n, 276);
//					f.WriteString("\" depends=\"Ratha Yatra\" rel=\"-1\"/>\n");
		NaplnComboFestivalom(pc, nClass);
		break;
	case 12:
		pc->ResetContent();
		n = pc->AddString(GCStrings::GetSpecFestivalName(SPEC_PRABHAPP));
		pc->SetItemData(n, 329);
		NaplnComboFestivalom(pc, nClass);
		break;
	case 13:
		pc->ResetContent();
		NaplnComboFestivalom(pc, nClass);
		break;
	case 14:
		pc->ResetContent();
		NaplnComboFestivalom(pc, nClass);
		break;
	case 15:
		pc->ResetContent();
		n = pc->AddString(GCStrings::getString(78));
		pc->SetItemData(n, 1);
		n = pc->AddString(GCStrings::getString(79));
		pc->SetItemData(n, 1);
		n = pc->AddString(GCStrings::getString(80));
		pc->SetItemData(n, 1);
		NaplnComboFestivalom(pc, nClass);
		break;
	default:
		break;
	}

	return 0;
}



BOOL CConditionsView::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	UINT nRow, nCol, n;
	CString str;

	if (HIWORD(wParam) == CBN_SELENDOK)
	{
		// zmena combo
		nRow = (LOWORD(wParam) - 100) / 2;
		nCol = LOWORD(wParam) % 2;

		if (nRow < 3 && nCol < 2)
		{
			if (nCol == 0)
			{
				// je to trieda
				n = m_c[nRow][0].GetCurSel();
				m_evClass[nRow] = m_c[nRow][0].GetItemData(n);
				NaplnComboBox(  &(m_c[nRow][1]), m_evClass[nRow]);
				m_c[nRow][1].SetCurSel(0);
				m_evValue[nRow] = m_c[nRow][1].GetItemData(0);
			}
			else
			{
				// je to hodnota
				n = m_c[nRow][1].GetCurSel();
				m_evValue[nRow] = m_c[nRow][1].GetItemData(n);
				m_c[nRow][1].GetLBText(n, str);
				m_evString[nRow] = str;
			}
		}
	}
	else if (HIWORD(wParam) == BN_CLICKED)
	{
		// stlacil tlacidlo
		if (LOWORD(wParam) == 130)
		{
			// set location
			DlgGetLocation dlg(GCStrings::getString(110));
			dlg.m_bFinal = TRUE;
			TString str;

			if (dlg.DoModal() == IDOK)
			{
				str.Format("%s (%s, %s, %s: %s)"
					, gLastLocation.m_strName.c_str()
					, gLastLocation.m_strLatitude.c_str()
					, gLastLocation.m_strLongitude.c_str()
					, GCStrings::getString(12).c_str()
					, gLastLocation.m_strTimeZone.c_str());
				m_earth = (EARTHDATA)gLastLocation;
				m_dst = gLastLocation.m_nDST;
				m_edits[0].SetWindowText(str);
			}
		}
		else if (LOWORD(wParam) == 131)
		{
			// find
			GetParent()->PostMessage(WM_COMMAND, ID_EVENT_FIND);
		}
		else if (LOWORD(wParam) == 140)
		{
			m_bMethodAnd = !m_bMethodAnd;
			if (m_bMethodAnd)
				m_buttons[2].SetWindowText("AND");
			else
				m_buttons[2].SetWindowText("OR");
		}
	}
	
	return CWnd::OnCommand(wParam, lParam);
}

int CConditionsView::GetStartYear()
{
	CString str;

	m_edits[1].GetWindowText(str);
	return _ttoi(str);
}

int CConditionsView::GetCountYear()
{
	CString str;

	m_edits[2].GetWindowText(str);
	return _ttoi(str);
}

void CConditionsView::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);

	int i;
	CRect rcClient;

	GetClientRect(&rcClient);

	// TODO: Add your specialized creation code here
	for(i = 0; i < MAX_CONDS; i++)
	{
		m_c[i][0].MoveWindow(4, ncm.iScrollHeight*(i*2+1), rcClient.Width()*2/5, 500);
		m_c[i][1].MoveWindow(rcClient.Width()*2/5 + 6, ncm.iScrollHeight*(i*2+1), rcClient.Width()*3/5-8, 500);
	}
	m_wnd_texts[3].MoveWindow(4, 2, rcClient.Width()*2/5, ncm.iCaptionHeight);
	m_wnd_texts[4].MoveWindow(rcClient.Width()*2/5+4, 2, rcClient.Width()*3/5, ncm.iCaptionHeight);	

	m_buttons[2].MoveWindow(rcClient.Width() - 40, ncm.iScrollHeight*7, 32, ncm.iScrollHeight);
}
