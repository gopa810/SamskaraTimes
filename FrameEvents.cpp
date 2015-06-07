// FrameEvents.cpp: implementation of the CFrameEvents class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "vcal5beta.h"
#include "FrameEvents.h"
#include "FrameServer.h"
#include "vedic_ui.h"
#include "CustomEvent.h"
#include "DlgEditCustomEvent.h"
#include "GCStrings.h"
#include "GCDisplaySettings.h"
#include "GCCalendar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern GCalApp theApp;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


BEGIN_MESSAGE_MAP(CFrameEvents, CFrameWnd)
	//{{AFX_MSG_MAP(CFrameEvents)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND(ID_EVENTS_CLOSE, OnEventsClose)
	ON_COMMAND(ID_EVENTS_DELETEEVENT, OnEventsDeleteevent)
	ON_COMMAND(ID_EVENTS_EDITEVENT, OnEventsEditevent)
	ON_COMMAND(ID_EVENTS_NEWEVENT, OnEventsNewevent)
	ON_UPDATE_COMMAND_UI(ID_EVENTS_EDITEVENT, OnUpdateEventsEditevent)
	ON_UPDATE_COMMAND_UI(ID_EVENTS_DELETEEVENT, OnUpdateEventsDeleteevent)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_HELP_HELP, OnHelpHelp)
	ON_UPDATE_COMMAND_UI(ID_HELP_HELP, OnUpdateHelpHelp)
	ON_COMMAND(ID_HELP_HELPTOPICTHISWINDOW, OnHelpHelptopicthiswindow)
	ON_UPDATE_COMMAND_UI(ID_HELP_HELPTOPICTHISWINDOW, OnUpdateHelpHelptopicthiswindow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CFrameEvents::CFrameEvents()
{
	int i;
	for(i=0;i<10;i++)
		b_class[i] = 1;
	for(i=0;i<12;i++)
		b_masa[i] = 1;
	dontUpdate = 0;
}

CFrameEvents::~CFrameEvents()
{
	m_fontMenu.DeleteObject();
}

BOOL CFrameEvents::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	int currSel;
	int i;

	switch(LOWORD(wParam))
	{
	case 200://class combobox
		if (HIWORD(wParam)==CBN_SELENDOK)
		{
			currSel = m_wndClass.GetCurSel();
			if (currSel == 0)
			{
				for(i=0;i<10;i++) b_class[i] = 1;
			}
			else
			{
				for(i=0;i<10;i++) b_class[i] = 0;
				if (currSel <= 10) b_class[currSel-1] = 1;
			}
			FillListView();
		}
		break;
	case 210://masa combobox
		if (HIWORD(wParam)==CBN_SELENDOK)
		{
			currSel = m_wndMasa.GetCurSel();
			if (currSel == 0)
			{
				for(i=0;i<12;i++) b_masa[i] = 1;
			}
			else
			{
				for(i=0;i<12;i++) b_masa[i] = 0;
				if (currSel <= 12) b_masa[GCCalendar::ComboMasaToMasa(currSel-1)] = 1;
			}
			FillListView();
		}
		break;
	}
	return CFrameBase::OnCommand(wParam, lParam);
}

BOOL CFrameEvents::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	int n = -1;
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
			}
			else
			{
			}
		}
		break;
	case LVN_ITEMCHANGED:
		if (dontUpdate == 0)
		{
			LPNMLISTVIEW lp = (LPNMLISTVIEW)lParam;
			CCustomEvent * p = (CCustomEvent *)m_wndList.GetItemData(lp->iItem);
			if (p && lp->uOldState!=0)
			{
//				TRACE1("another update of %s was done\n", p->strText.c_str());
				p->nVisible = m_wndList.GetCheck(lp->iItem);
			}
		}
		break;
	default:
		break;
	}

	return CFrameBase::OnNotify(wParam, lParam, pResult);
}

void CFrameEvents::OnDestroy() 
{
/*	TRACE2("List column %d ==> %d\n", 0, m_wndList.GetColumnWidth(0));
	TRACE2("List column %d ==> %d\n", 1, m_wndList.GetColumnWidth(1));
	TRACE2("List column %d ==> %d\n", 2, m_wndList.GetColumnWidth(2));
	TRACE2("List column %d ==> %d\n", 3, m_wndList.GetColumnWidth(3));
	TRACE2("List column %d ==> %d\n", 4, m_wndList.GetColumnWidth(4));
	TRACE2("List column %d ==> %d\n", 5, m_wndList.GetColumnWidth(5));*/
/*	if (p_webView != NULL)
	{
		delete p_webView;
		p_webView = NULL;
	}
*/
/*	m_wndList.DestroyWindow();
	m_wndClass.DestroyWindow();
	m_wndMasa.DestroyWindow();
*/
	CFrameBase::OnDestroy();
	
	// TODO: Add your message handler code here
	theFrameServer.RemoveFromEventFrames();
}

/////////////////////////////////////////////////////////////////////////////
// CFrameFind message handlers

int CFrameEvents::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	int i;

	if (CFrameBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rcClient, rcCond;
	GetClientRect(&rcClient);

/*	p_webView = new CEventsHtmlView;
	if (p_webView)
	{
		p_webView->Create(NULL, "web", WS_CHILD | WS_VISIBLE, rcClient, this, 140);
		p_webView->Navigate2("action:list");
	}
*/

/*	rcCond.SetRect(0, m_viewCond.GetProperHeight()+8, rcClient.right, rcClient.bottom);

	m_wndTab.Create(WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE, rcCond, this, 120);
	m_wndTab.InsertItem(0, "All Results");
	m_wndTab.InsertItem(1, "Calendar Context");
	m_wndTab.SetFont(&(m_viewCond.m_comboFont));

	m_wndTab.GetClientRect(&rcCond);
	*/
	_ncm.cbSize = sizeof(NONCLIENTMETRICS);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &_ncm, NULL);
	m_fontMenu.CreateFontIndirect(&(_ncm.lfMenuFont));
	rcCond.top = 8;
	rcCond.left = 16;
	rcCond.right = 220;
	rcCond.bottom = rcCond.top + _ncm.iCaptionHeight;
	m_wndClassTitle.Create("Filter Class", WS_CHILD | WS_VISIBLE, rcCond, this);
	m_wndClassTitle.SetFont(&m_fontMenu);
	rcCond.OffsetRect(230, 0);
	m_wndMasaTitle.Create("Filter Masa", WS_CHILD | WS_VISIBLE, rcCond, this);
	m_wndMasaTitle.SetFont(&m_fontMenu);
	rcCond.OffsetRect(-230, _ncm.iCaptionHeight);
	rcCond.bottom += 400;
	m_wndClass.Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, rcCond, this, 200);
	m_wndClass.SetFont(&m_fontMenu);
	rcCond.OffsetRect(230, 0);
	m_wndMasa.Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, rcCond, this, 210);
	m_wndMasa.SetFont(&m_fontMenu);

	rcCond = rcClient;
	rcCond.top += _ncm.iCaptionHeight*3;
	rcCond.left +=4;
	rcCond.right-=4;
	rcCond.bottom-=4;
	m_wndList.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_NOSORTHEADER | LVS_SORTASCENDING, rcCond, this, 130);
	//m_wndList.ModifyStyleEx(NULL, WS_EX_CLIENTEDGE);
	m_wndList.SetExtendedStyle(LVS_EX_CHECKBOXES | LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_wndList.InsertColumn(0, "Event Title", LVCFMT_LEFT, 274, 0);
	m_wndList.InsertColumn(1, "Tithi", LVCFMT_LEFT, 60, 1);
	m_wndList.InsertColumn(2, "Paksa", LVCFMT_LEFT, 60, 2);
	m_wndList.InsertColumn(3, "Masa", LVCFMT_LEFT, 60, 3);
	m_wndList.InsertColumn(4, "Fast Type", LVCFMT_LEFT, 108, 4);
	m_wndList.InsertColumn(5, "Fast Subject", LVCFMT_LEFT, 160, 5);
	m_wndList.InsertColumn(6, "Class", LVCFMT_LEFT, 250, 6);
	m_wndList.InsertColumn(7, "Start Year", LVCFMT_RIGHT, 50, 7);
//	m_wndList.SetFont( &m_fontList);

	m_wndClass.AddString("<all classes>");
	for(i = 0; i < 7; i++)
		m_wndClass.AddString(GCStrings::GetEventClassText(i));
/*	m_wndClass.AddString("Appearance Days of the Lord and His Incarnations");
	m_wndClass.AddString("Events in the Pastimes of the Lord and His Associates");
	m_wndClass.AddString("Appearance and Disappearance Days of Recent Acaryas");
	m_wndClass.AddString("Appearance and Disappearance Days of Mahaprabhu's Associates and Other Acaryas");
	m_wndClass.AddString("ISKCON's Historical Events");
	m_wndClass.AddString("Bengal-specific Holidays");
	m_wndClass.AddString("My Personal Events");
*/
	m_wndMasa.AddString("<all masa>");
	for(i = 0; i < 12; i++)
		m_wndMasa.AddString(GCStrings::GetMasaName(GCCalendar::ComboMasaToMasa(i)));

	m_wndClass.SetCurSel(0);
	m_wndMasa.SetCurSel(0);

	FillListView();

	return 0;
}

void CFrameEvents::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	
	CRect rcCond;

	rcCond.top = _ncm.iCaptionHeight*3;
	rcCond.left =4;
	rcCond.right = cx - 4;
	rcCond.bottom = cy - 4;
	
	m_wndList.MoveWindow(&rcCond);
}

void CFrameEvents::FillListView()
{
	int i;
	CCustomEvent * p;

	p = gCustomEventList.list;

	m_wndList.DeleteAllItems();

	while(p)
	{
		if (p->nClass==0)
		{
			TRACE3("{/*tithi*/ %d, /*masa*/ %d, /*fast*/ %d, 9_7}\n", p->nTithi, p->nMasa, p->nFastType);
		}
		if (p->nMasa>=0 && p->nMasa<12 && p->nClass>=0 && p->nClass<10 && b_class[p->nClass] && b_masa[p->nMasa] && p->nDeleted==0)
		{
			i = m_wndList.InsertItem(0, p->strText.c_str());
			m_wndList.SetItemText(i, 1, GCStrings::GetTithiName(p->nTithi));
			m_wndList.SetItemText(i, 2, GCStrings::GetPaksaName(p->nTithi/15));
			m_wndList.SetItemText(i, 3, GCStrings::GetMasaName(p->nMasa));
			if (p->nFastType != 0)
			{
				m_wndList.SetItemText(i, 4, GCStrings::GetFastingName(p->nFastType + 0x200));
				m_wndList.SetItemText(i, 5, p->strFastSubject.c_str());
			}
			m_wndList.SetItemText(i, 6, GCStrings::GetEventClassText(p->nClass));
			if (p->nStartYear > -7000)
			{
				char str10[32];
				sprintf(str10, "%d", p->nStartYear);
				m_wndList.SetItemText(i, 7, str10);
			}
			m_wndList.SetItemData(i, DWORD(p));
			m_wndList.SetCheck(i, p->nVisible);
		}
		p = p->next;
	}
}

void CFrameEvents::OnEventsClose() 
{
	// TODO: Add your command handler code here
	DestroyWindow();	
}

void CFrameEvents::OnEventsDeleteevent() 
{
	// TODO: Add your command handler code here
	POSITION pos;
	int nSel;
	CCustomEvent * pe;

	pos  = m_wndList.GetFirstSelectedItemPosition();
	if (pos == NULL)
		return;
	nSel = m_wndList.GetNextSelectedItem(pos);
	pe = (CCustomEvent *)m_wndList.GetItemData(nSel);
	if (pe != NULL)
	{
		CString str;
		str.Format("Delete event \"%s\" from the list?", pe->strText.c_str());
		if (MessageBox(str, "Event Manager", MB_YESNO)==IDYES)
		{
			pe->nDeleted = 1;
			FillListView();
		}
	}
}

void CFrameEvents::OnEventsEditevent() 
{
	// TODO: Add your command handler code here
	POSITION pos;
	int nSel;
	CCustomEvent * pe;
	DlgEditCustomEvent d;

	pos  = m_wndList.GetFirstSelectedItemPosition();
	if (pos == NULL)
		return;
	nSel = m_wndList.GetNextSelectedItem(pos);
	pe = (CCustomEvent *)m_wndList.GetItemData(nSel);
	if (pe != NULL)
	{
		d.m_nClass = pe->nClass;
		d.m_nFastType = pe->nFastType;
		d.m_nMasa = pe->nMasa;
		d.m_nTithi = pe->nTithi;
		d.m_strText = pe->strText.c_str();
		d.m_strFastSubject = pe->strFastSubject.c_str();
		char str10[32];
		sprintf(str10, "%d", pe->nStartYear);
		if (pe->nStartYear > -7000)
			d.m_strStartYear = str10;

		if (d.DoModal() == IDOK)
		{
			if (pe)
			{
				pe->nClass = d.m_nClass;
				pe->nFastType = d.m_nFastType + 0x200;
				if (pe->nFastType==0x200)
					pe->nFastType = 0;
				pe->nMasa = d.m_nMasa;
				pe->nTithi = d.m_nTithi;
				pe->strFastSubject = (LPCTSTR)d.m_strFastSubject;
				pe->strText = (LPCTSTR)d.m_strText;
				const char * str11 = (LPCTSTR)d.m_strStartYear;
				if (strlen(str11) > 0)
					pe->nStartYear = _ttoi(str11);
				else
					pe->nStartYear = -10000;

				gCustomEventList_Modified = 1;
				GCStrings::SetSpecFestivalName(pe->nSpec, (LPCTSTR)d.m_strText);
				FillListView();
			}
		}
	}	
}

void CFrameEvents::OnEventsNewevent() 
{
	DlgEditCustomEvent d;

	d.m_nClass = 6;
	d.m_nFastType = 0;
	d.m_nMasa = 0;
	d.m_nTithi = 0;
	d.m_strText = "Custom Event";

	if (d.DoModal() == IDOK)
	{
		CCustomEvent * p = gCustomEventList.add();
		if (p)
		{
			p->nClass = d.m_nClass;
			p->nFastType = d.m_nFastType+0x200;
			if (p->nFastType==0x200)
				p->nFastType = 0;
			p->nMasa = d.m_nMasa;
			p->nTithi = d.m_nTithi;
			p->strFastSubject = (LPCTSTR)d.m_strFastSubject;
			p->strText = (LPCTSTR)d.m_strText;
			gCustomEventList_Modified = 1;
			GCStrings::SetSpecFestivalName(p->nSpec, (LPCTSTR)d.m_strText);
			FillListView();
		}
	}
}

void CFrameEvents::OnUpdateEventsEditevent(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//if (GCDisplaySettings::getValue(44))
		pCmdUI->Enable(m_wndList.GetFirstSelectedItemPosition() != NULL);
	//else
	//	pCmdUI->Enable(FALSE);

}

void CFrameEvents::OnUpdateEventsDeleteevent(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	POSITION pos = m_wndList.GetFirstSelectedItemPosition();
	int ind;
	int nAllowed = 0;
	if (pos != NULL)
	{
		ind = m_wndList.GetNextSelectedItem(pos);
		CCustomEvent * pce = (CCustomEvent *)m_wndList.GetItemData(ind);
		if (pce && pce->nClass == 6)
			nAllowed = 1;

	}
	else ind = -1;

	if (GCDisplaySettings::getValue(44) || nAllowed)
		pCmdUI->Enable(ind >= 0);	
	else
		pCmdUI->Enable(FALSE);
}

void CFrameEvents::UpdateItemsCheckStatus()
{
	int i = 0, m;
	CCustomEvent * p;
	dontUpdate = 1;
	m = m_wndList.GetItemCount();
	while(i<m)
	{
		p = (CCustomEvent *)m_wndList.GetItemData(i);
		m_wndList.SetCheck(i, p->nVisible);
		i++;
	}
	dontUpdate = 0;
}

void CFrameEvents::UpdateItemsFasting()
{
	int i = 0, m;
	CCustomEvent * p;
	dontUpdate = 1;
	m = m_wndList.GetItemCount();
	while(i<m)
	{
		p = (CCustomEvent *)m_wndList.GetItemData(i);
		if (p->nFastType != 0)
		{
			m_wndList.SetItemText(i, 4, GCStrings::GetFastingName(p->nFastType + 0x200));
			m_wndList.SetItemText(i, 5, p->strFastSubject.c_str());
		}
		else
		{
			m_wndList.SetItemText(i, 4, "");
			m_wndList.SetItemText(i, 5, "");
		}
		i++;
	}
	dontUpdate = 0;
}

void CFrameEvents::OnFileSave() 
{
	CustomEventList_Export();	
}

void CFrameEvents::OnHelpHelp() 
{
	// TODO: Add your command handler code here
	GCalShowHelp("index.htm");
	
}

void CFrameEvents::OnUpdateHelpHelp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(theApp.m_bHelpAvailable);	
	
}

void CFrameEvents::OnHelpHelptopicthiswindow() 
{
	// TODO: Add your command handler code here
	GCalShowHelp("ref-evman.htm");
	
}

void CFrameEvents::OnUpdateHelpHelptopicthiswindow(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(theApp.m_bHelpAvailable);	
	
}
