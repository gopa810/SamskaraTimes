// FrameFind.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "FrameFind.h"
#include "DlgSetPrintStyle.h"

#include "DayFindBuffer.h"
#include "level_6.h"
#include "strings.h"
#include "FrameServer.h"
#include "TFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



extern GCalApp theApp;
int AvcGetOldCalendarDayText(VAISNAVADAY *, TString &);
int AvcGetNextLine(TString &, TString &, int &);
Boolean ConditionEvaluate(VAISNAVADAY *, int, int, TString &, Boolean);


/////////////////////////////////////////////////////////////////////////////
// CFrameFind

//IMPLEMENT_DYNCREATE(CFrameFind, CFrameWnd)

CFrameFind::CFrameFind()
{
	m_dwPrevDate = 0xffffffff;
	m_bKeyShift = FALSE;
	m_bKeyCtrl = FALSE;
}

CFrameFind::~CFrameFind()
{
}


BEGIN_MESSAGE_MAP(CFrameFind, CFrameWnd)
	ON_COMMAND_EX(CG_ID_VIEW_LOCATOR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_LOCATOR, OnUpdateControlBarMenu)
	ON_COMMAND_EX(CG_ID_VIEW_CALCULATIONCONTROLLER, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_CALCULATIONCONTROLLER, OnUpdateControlBarMenu)
	//{{AFX_MSG_MAP(CFrameFind)
	ON_WM_CREATE()
	ON_WM_SIZING()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_EVENT_FIND, OnEventFind)
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_COMMAND(ID_LOCATION_SETLOCATION, OnLocationSetlocation)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_WM_DESTROY()
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_HELP_HELP, OnHelpHelp)
	ON_UPDATE_COMMAND_UI(ID_HELP_HELP, OnUpdateHelpHelp)
	ON_COMMAND(ID_HELP_HELPTOPICTHISWINDOW, OnHelpHelptopicthiswindow)
	ON_UPDATE_COMMAND_UI(ID_HELP_HELPTOPICTHISWINDOW, OnUpdateHelpHelptopicthiswindow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrameFind message handlers

int CFrameFind::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	int halfSize;
	CRect rcClient, rcCond;
	GetClientRect(&rcClient);

	halfSize = rcClient.Width() / 2;

	rcCond.SetRect(4, 4, rcClient.Width() - 4, m_viewCond.GetProperHeight() + 4);

	m_viewCond.Create(AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW, ::LoadCursor(NULL, IDC_ARROW), (HBRUSH)(COLOR_BTNFACE + 1), NULL)
		, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, rcCond, this, 0, NULL);


	rcCond.SetRect(0, m_viewCond.GetProperHeight()+8, rcClient.right, rcClient.bottom);

	m_wndTab.Create(WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE, rcCond, this, 120);
	m_wndTab.InsertItem(0, "All Results");
	m_wndTab.InsertItem(1, "Calendar Context");
	m_wndTab.SetFont(&(m_viewCond.m_comboFont));

	m_wndTab.GetClientRect(&rcCond);
	rcCond.top += m_viewCond.ncm.iCaptionHeight*3/2;
	rcCond.left +=4;
	rcCond.right-=4;
	rcCond.bottom-=4;
	rcCond.SetRect(0,0,20,20);
	m_wndList.Create(WS_CHILD | WS_VSCROLL | WS_VISIBLE | LBS_NOINTEGRALHEIGHT, rcCond, &m_wndTab, 122);
	m_wndList.ModifyStyleEx(NULL, WS_EX_CLIENTEDGE);
	m_wndList.SetFont( &m_fontList);
	m_wndCalend.Create(WS_CHILD | WS_VSCROLL | ES_WANTRETURN | ES_MULTILINE, rcCond, &m_wndTab, 124);
	m_wndCalend.SetFont( &m_fontList);
	m_wndCalend.ModifyStyleEx(NULL, WS_EX_CLIENTEDGE);


	m_wndList.AddString("");
	m_wndList.AddString("");
	m_wndList.AddString("");
	m_wndList.AddString("---------------------- < no results > ------------------------");
	m_wndList.AddString("");
	m_wndList.AddString(" 1)  Please select at least one condition");
	m_wndList.AddString(" 2)  set proper location and time range");
	m_wndList.AddString(" 3)  click on \"Find\" button");
	m_wndList.AddString("");
	m_wndList.AddString("");
	m_wndList.AddString("");
	return 0;
}

void CFrameFind::OnSizing(UINT fwSide, LPRECT pRect) 
{
	CFrameWnd::OnSizing(fwSide, pRect);
	
	// TODO: Add your message handler code here
	if (pRect->left + 256 > pRect->right)
	{
		if (fwSide == WMSZ_RIGHT || fwSide==WMSZ_TOPRIGHT || fwSide == WMSZ_BOTTOMRIGHT)
			pRect->right = pRect->left + 256;
		else
			pRect->left = pRect->right - 256;
	}

	if (pRect->top + 256 > pRect->bottom)
	{
		if (fwSide == WMSZ_BOTTOM || fwSide==WMSZ_BOTTOMRIGHT || fwSide==WMSZ_BOTTOMLEFT)
			pRect->bottom = pRect->top + 256;
		else
			pRect->top = pRect->bottom - 256;
	}
}

void CFrameFind::OnSetFocus(CWnd* pOldWnd) 
{
	CFrameWnd::OnSetFocus(pOldWnd);
	
	theApp.m_pActiveWnd = this;	
	m_bKeyCtrl = FALSE;
	m_bKeyShift = FALSE;
}

BOOL CFrameFind::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	return CFrameBase::OnCommand(wParam, lParam);
}

BOOL CFrameFind::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	int n = -1;
	DWORD dw;
	VCTIME vc;
	LPNMHDR ph = (LPNMHDR)lParam;
	TString location_info, text;
	CString str;

	switch(ph->code)
	{
	case TCN_SELCHANGE:
		if (ph->idFrom == 120)
		{
			if (m_wndTab.GetCurSel() == 0)
			{
				m_wndList.ShowWindow(SW_SHOW);
				m_wndList.SetFocus();
				m_wndCalend.ShowWindow(SW_HIDE);
			}
			else
			{
				m_wndList.ShowWindow(SW_HIDE);
				m_wndCalend.ShowWindow(SW_SHOW);
				m_wndCalend.SetFocus();

				n = m_wndList.GetCurSel();
				if (n < 0)
				{
					text = "Please do the following:\r\n\r\n - go back to \'All Results\'\r\n - select one of the calculated days\r\n - click again on \'Calendar Context\'\r\n\r\nIf you have no results in \'All Results\', you will again get this note in this screen.";
					m_wndCalend.SetWindowText(text);
					break;
				}
				dw = m_wndList.GetItemData(n);
				if (dw == m_dwPrevDate)
					break;
				m_dwPrevDate = dw;

				vc.day = LOBYTE(LOWORD(dw));
				vc.month = HIBYTE(LOWORD(dw));
				vc.year = HIWORD(dw);
				vc.tzone = m_viewCond.m_earth.m_fTimezone;
				vc.shour = 0.5;
				vc.PreviousDay();
				vc.PreviousDay();
				vc.PreviousDay();
				vc.PreviousDay();
				vc.PreviousDay();


				m_viewCond.m_edits[0].GetWindowText(str);
				m_viewCond.m_earth.m_strName = str;
				CalcCalendar(m_calendar, m_viewCond.m_earth, vc, 10);
				FormatCalendarOld(m_calendar, text);

				calendar.vc_start = vc;
				calendar.count = 10;

				m_wndCalend.SetWindowText(text);
			}
		}
		break;
	default:
		break;
	}

	return CFrameBase::OnNotify(wParam, lParam, pResult);
}

BOOL CFrameFind::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CFrameBase::OnChildNotify(message, wParam, lParam, pLResult);
}

//============================================================================
// looking for event conditions
//============================================================================

void CFrameFind::OnEventFind() 
{
	int i, j, k, n, c, indexLine;
	int year1, ycount;
	TFinderBuffer buf;
	TString str, s1;
	VAISNAVADAY * pd;
	VCTIME vcFrom, vcTo;
	Boolean next_day = false;
	Boolean succ = false;
	DWORD dwDateNote;

	// update data

	if (m_viewCond.m_evClass[0] == m_viewCond.m_evClass[1] 
		&& m_viewCond.m_evClass[1] == m_viewCond.m_evClass[2] 
		&& m_viewCond.m_evClass[2] == 0)
	{
		MessageBox("Please specify at least one condition for day.", "Uncomplete Specification", MB_OK | MB_ICONSTOP);
		return;
	}

	m_wndList.ResetContent();

	year1 = m_viewCond.GetStartYear();
	ycount = m_viewCond.GetCountYear();

	AvcProgressWindowCreate();
	AvcProgressWindowSetRange(0, (ycount + 1)*12);
	c = 0;

	// 
	for(i = year1; i < year1 + ycount; i++)
	{
		for(j = 1; j < 13; j++)
		{

			// vypocet dni pre datum
			buf.CalculateFindCalendar(i, j, m_viewCond.m_earth, m_viewCond.m_dst);
			AvcProgressWindowSetPos(c++);
			//m_progress.UpdateWindow();

			// prechadzanie cez datumy
			for(k = buf.GetStartIndex(); k <= buf.GetUpperBound(); k++)
			{
				pd = &(buf.m_rData[k]);

				if (pd->date.month != j)
					continue;

				succ = false;
				if (m_viewCond.m_bMethodAnd)
				{
					succ = (ConditionEvaluate(pd, m_viewCond.m_evClass[0], m_viewCond.m_evValue[0], m_viewCond.m_evString[0], m_viewCond.m_bMethodAnd)
						&& ConditionEvaluate(pd, m_viewCond.m_evClass[1], m_viewCond.m_evValue[1], m_viewCond.m_evString[1], m_viewCond.m_bMethodAnd)
						&& ConditionEvaluate(pd, m_viewCond.m_evClass[2], m_viewCond.m_evValue[2], m_viewCond.m_evString[2], m_viewCond.m_bMethodAnd));
				}
				else
				{
					succ = (ConditionEvaluate(pd, m_viewCond.m_evClass[0], m_viewCond.m_evValue[0], m_viewCond.m_evString[0], m_viewCond.m_bMethodAnd)
						|| ConditionEvaluate(pd, m_viewCond.m_evClass[1], m_viewCond.m_evValue[1], m_viewCond.m_evString[1], m_viewCond.m_bMethodAnd)
						|| ConditionEvaluate(pd, m_viewCond.m_evClass[2], m_viewCond.m_evValue[2], m_viewCond.m_evString[2], m_viewCond.m_bMethodAnd));
				}

				if (succ)
				{
					AvcGetOldCalendarDayText(pd, str);
					dwDateNote = MAKELONG(MAKEWORD(pd->date.day, pd->date.month), pd->date.year);
					indexLine = 0;
					while(AvcGetNextLine(str, s1, indexLine))
					{
						n = m_wndList.AddString(s1);
						m_wndList.SetItemData(n, dwDateNote);
					}
					n = m_wndList.AddString("");
					m_wndList.SetItemData(n, dwDateNote);
				}

			}
		}
		m_wndList.UpdateWindow();
	}

	if (m_wndList.GetCount() < 1)
	{
		m_wndList.AddString("");
		m_wndList.AddString("");
		m_wndList.AddString("");
		m_wndList.AddString("-------------------------- < no results > -------------------------");
		m_wndList.AddString("");
		m_wndList.AddString("");
		m_wndList.AddString("          Condition were not satisfied in given time range.");
	}

	// ak dokoncil vypocet a ma platny smernik na textove okno
	// tak umozni spustit funkciu "Kopiruj zoznam do okna"
//	GetDlgItem(IDC_BUTTON_LISTTOCAL)->EnableWindow(m_pViewText != NULL);


	AvcProgressWindowClose();
}

void CFrameFind::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	
	CRect rcClient, rcCond;
	GetClientRect(&rcClient);

	rcCond.SetRect(4, 4, rcClient.Width() - 4, m_viewCond.GetProperHeight() + 4);

	m_viewCond.MoveWindow(&rcCond);

	rcCond.SetRect(0, m_viewCond.GetProperHeight()+8, rcClient.right, rcClient.bottom);

	m_wndTab.MoveWindow(&rcCond);

	m_wndTab.GetClientRect(&rcCond);

	rcCond.top += m_viewCond.ncm.iCaptionHeight*3/2;
	rcCond.left +=4;
	rcCond.right-=4;
	rcCond.bottom-=4;

	m_wndList.MoveWindow(&rcCond);
	m_wndCalend.MoveWindow(&rcCond);
	
}

void CFrameFind::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{

	// TODO: Add your message handler code here and/or call default
	switch(nChar)
	{
	case VK_CONTROL:
		m_bKeyCtrl = TRUE;
		break;
	case VK_SHIFT:
		m_bKeyShift = TRUE;
		break;
	case 'C':
	case 'X':
		if (m_bKeyCtrl == TRUE)
		{
			CopyDataToClipboard();
		}
		break;
	default:
		break;
	}
	
	CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CFrameFind::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar)
	{
	case VK_CONTROL:
		m_bKeyCtrl = FALSE;
		break;
	case VK_SHIFT:
		m_bKeyShift = FALSE;
		break;
	default:
		break;
	}
	
	CFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

int CFrameFind::CopyDataToClipboard()
{
	TString str;

	// copy active contents into clipboard
	CopyDataToString(str);

	// otvara clipboard
	if (!OpenClipboard())
	{
		return 0;
	}

	// vyprazdnuje clipboard
	EmptyClipboard();

	HANDLE handle = GlobalAlloc(GHND, sizeof(TCHAR)*str.GetLength() + 2);

	if (handle == NULL)
	{
		return 0;
	}

	LPSTR pText = (LPSTR)GlobalLock(handle);
	if (pText == NULL)
	{
		return 0;
	}

	_tcscpy(pText, str);
	GlobalUnlock(handle);


	SetClipboardData(CF_TEXT, handle);

	// zatvara clipboard
	CloseClipboard();

	GlobalFree(handle);

	return 1;

}

void CFrameFind::OnLocationSetlocation() 
{
	// TODO: Add your command handler code here
	m_viewCond.PostMessage(WM_COMMAND, MAKELONG(130, BN_CLICKED));	
}

void CFrameFind::OnEditCopy() 
{
	CopyDataToClipboard();	
}

void CFrameFind::OnFileExit() 
{
	// TODO: Add your command handler code here
	CloseWindow();	
}

int CFrameFind::CopyDataToString(TString &str)
{
	int i, max;
	CString line;

	if (m_wndTab.GetCurSel() == 0)
	{
		str.Empty();
		max = m_wndList.GetCount();
		for(i = 0; i < max; i++)
		{
			m_wndList.GetText(i, line);
			str += line;
			str += "\r\n";
		}
	}
	else
	{
		m_wndCalend.GetWindowText(line);
		str = line;
	}

	return 1;
}

void CFrameFind::OnFilePrint() 
{
	// TODO: Add your command handler code here
	int nCopies = 0;
	int nPage = 1;
	CPrintDialog pd(FALSE);
	DlgSetPrintStyle spd;
	TString str;
	CString strA;
	CDC dc;
	CRect rcPrint;
	double resX, resY;
	
	if (pd.DoModal() != IDOK)
	{
		return;
	}


	// copies of document
	nCopies = pd.GetCopies();

	// need to obtain style of printing
	// if calendar - then two styles (text, wall calendar)
	// otherwise - one style (text)

	spd.m_margins = m_rectPrintMargins;
	if (spd.DoModal() == IDCANCEL)
		return;

	m_rectPrintMargins = spd.m_margins;
    
	DOCINFO di;
	memset( &di, 0, sizeof(DOCINFO) );
    di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = "GCal Find Results";
    di.lpszOutput = (LPTSTR)NULL; 
    //di.lpszDataType = (LPTSTR)NULL; 
    di.fwType = 0; 

	dc.Attach(pd.m_pd.hDC);

	// user wants to print
	LPDEVMODE lpDevMode = pd.GetDevMode();

	resX = dc.GetDeviceCaps(LOGPIXELSX) / 25.4;
	resY = dc.GetDeviceCaps(LOGPIXELSY) / 25.4;

	int offX, offY;

	offX = int(lpDevMode->dmPaperWidth - dc.GetDeviceCaps(HORZSIZE)*10.0) / 2;
	offY  = int(lpDevMode->dmPaperLength  - dc.GetDeviceCaps(VERTSIZE)*10.0) / 2;

	rcPrint.left = int((m_rectPrintMargins.left - offX/10.0) * resX);
	rcPrint.right = int((lpDevMode->dmPaperWidth/10.0 - m_rectPrintMargins.right - m_rectPrintMargins.left)*resX + rcPrint.left);
	rcPrint.top = int((m_rectPrintMargins.top - offY/10.0) * resY);
	rcPrint.bottom = int((lpDevMode->dmPaperLength/10.0 - m_rectPrintMargins.bottom - m_rectPrintMargins.top)*resY + rcPrint.top);

	m_fontPrintText.CreateFont(dc.GetDeviceCaps(LOGPIXELSX) / 72 * spd.m_nFontSize, 
		0,0,0,0,0,0, 0,0,0,0,0,0, spd.m_strFont);
	m_fontPrintHdr.CreateFont(dc.GetDeviceCaps(LOGPIXELSY) / 72 * spd.m_nHeaderSize, 
		0,0,0,0,0,0, 0,0,0,0,0,0, spd.m_strFont);

	TString strTitle;
	TString strText;

	strTitle = "Find Results";
	m_viewCond.m_edits[0].GetWindowText(strA);
	this->earth.m_strName = strA;

	switch(m_wndTab.GetCurSel())
	{
	case 0:
		//
		//     kontext: pd.m_pd.hDC
		// tlacit text: m_text.GetWindowText();
		//    s nazvom: m_Info.GetWindowText();
		//    lokacia:  location.location
		//     strana:  nPage
		//
		CopyDataToString(strText);
		dc.StartDoc(&di);
		PrintBlockText(dc, strTitle, strText, nPage, rcPrint);
		dc.EndDoc();
		break;
	case 1:
		{
			//     kontext: pd.m_pd.hDC
			// tlacit text: special generovanie;
			//    s nazvom: nazov masy;
			//    lokacia:  location.location
			//     strana:  nPage

			dc.StartDoc(&di);
			AfxPrintCalendarText(dc, m_calendar, m_viewCond.m_earth, calendar.vc_start, calendar.count, rcPrint);
			dc.EndDoc();

		}
		break;
	default:
		break;
	}

	dc.Detach();

	m_fontPrintHdr.DeleteObject();
	m_fontPrintText.DeleteObject();
	
}


void CFrameFind::OnDestroy() 
{
	CFrameBase::OnDestroy();
	
	// TODO: Add your message handler code here
	theFrameServer.RemoveFromFinders();
}

void CFrameFind::OnFileSave() 
{
	// TODO: Add your command handler code here
	CFileDialog fd(FALSE, "*.txt", "gcal find result", OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, 
		"Text Files (*.txt)|*.txt||");
	int i, m;
	TString str, str1, str2;
	CString strA;

	if (fd.DoModal() != IDOK)
		return;

	TFile file;

	if (file.Open(fd.GetPathName(), "w") == FALSE)
		return;

	file.WriteString("--------------------------------- Event Finder ---------------------------------\n\n");
	for(i = 0; i < 3; i++)
	{
		if (m_viewCond.m_c[i][0].GetCurSel() != 0)
		{
			m_viewCond.m_c[i][0].GetWindowText(strA);
			str1 = strA;
			m_viewCond.m_c[i][1].GetWindowText(strA);
			str2 = strA;
			str.Format(" Condition %c : %s / %s\n", 'A' + i, str1.c_str(), str2.c_str());
			file.WriteString(str);
		}
	}
	file.WriteString("\n Location : ");
	m_viewCond.m_edits[0].GetWindowText(strA);
	str = strA;
	file.WriteString(str);
	file.WriteString("\n\n--------------------------------------------------------------------------------\n\n");


	switch(m_wndTab.GetCurSel())
	{
	case 0:
		m = m_wndList.GetCount();
		for(i = 0; i < m; i++)
		{
			m_wndList.GetText(i, strA);
			str = strA;
			file.WriteString(str);
			file.WriteString("\n");
		}
		break;
	case 1:
		m_wndCalend.GetWindowText(strA);
		str = strA;
		file.WriteString(str);
		file.WriteString("\n");
		break;
	default:
		break;
	}

	file.Close();

}


void CFrameFind::OnHelpHelp() 
{
	// TODO: Add your command handler code here
	GCalShowHelp("index.htm");
	
}

void CFrameFind::OnUpdateHelpHelp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(theApp.m_bHelpAvailable);	
	
}

void CFrameFind::OnHelpHelptopicthiswindow() 
{
	// TODO: Add your command handler code here
	GCalShowHelp("ref-evfin.htm");
	
}

void CFrameFind::OnUpdateHelpHelptopicthiswindow(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(theApp.m_bHelpAvailable);	
	
}
