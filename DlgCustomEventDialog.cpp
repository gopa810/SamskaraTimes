// DlgCustomEventDialog.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "DlgCustomEventDialog.h"
#include "DlgEditCustomEvent.h"
#include "CustomEvent.h"
#include "vedic_ui.h"
#include "avc.h"
#include "GCStrings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*extern TString gCustomEventTexts[360];*/

/////////////////////////////////////////////////////////////////////////////
// DlgCustomEventDialog dialog


DlgCustomEventDialog::DlgCustomEventDialog(CWnd* pParent /*=NULL*/)
	: CDialog(DlgCustomEventDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgCustomEventDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgCustomEventDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgCustomEventDialog)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgCustomEventDialog, CDialog)
	//{{AFX_MSG_MAP(DlgCustomEventDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnAddEvent)
	ON_BN_CLICKED(IDC_BUTTON2, OnRemoveEvent)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, OnButtonEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgCustomEventDialog message handlers

BOOL DlgCustomEventDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	m_list.InsertColumn(0, "Tithi", LVCFMT_LEFT, 64, 0);
	m_list.InsertColumn(1, "Paksa", LVCFMT_LEFT, 64, 1);
	m_list.InsertColumn(2, "Masa", LVCFMT_LEFT, 64, 2);
	m_list.InsertColumn(3, "Text", LVCFMT_LEFT, 256, 3);

	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	CCustomEvent * pos;
	int n;


	pos = gCustomEventList.list;
	while(pos)
	{
		n = m_list.InsertItem(1000, GCStrings::GetTithiName(pos->nTithi));
		m_list.SetItemText(n, 1, GCStrings::GetPaksaName(pos->nTithi / 15));
		m_list.SetItemText(n, 2, GCStrings::GetMasaName(pos->nMasa));
		m_list.SetItemText(n, 3, pos->strText);
		m_list.SetItemData(n, pos->nTithi + pos->nMasa*30);
		pos = pos->next;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

#include "DlgEventsTypeOfEvent.h"
#include "DlgEventsGaubdTM.h"
#include "DlgGetDate.h"
//#include "DlgGetTime.h"
#include "DlgGetLocation.h"
#include "DlgEventsGetText.h"
#include "level_6.h"

void DlgCustomEventDialog::OnAddEvent() 
{
	DlgEventsTypeOfEvent dte;
	DlgEventsGaubdTM     dgtm;
	DlgGetDate           dgd;
	DlgGetLocation       dgl("Location of Event");
	EARTHDATA            earth;
	DlgEventsGetText     degt;
	CCustomEvent ce;

	int nTithi, nMasa, n;

AE_TypeAgain:
	if (dte.DoModal() == IDOK)
	{
		switch(dte.m_nType)
		{
		case 1:
			if (dgtm.DoModal() == IDOK)
			{
				nTithi = dgtm.m_nTithi;
				nMasa  = dgtm.m_nMasa;
			}
			else
			{
				if (dgtm.m_nRetCancel == 1)
					goto AE_TypeAgain;
			}
			// gaurabda date
			break;
		case 2:
		AE_LocAgain:
			if (dgl.DoModal() == IDOK)
			{
				dgd.s_event.tzone = dgl.m_location.m_fTimezone;
				if (dgd.DoModal() == IDOK)
				{
					VCTIME  vc;
					DAYDATA day;

					dgl.GetEarthData(earth);

					vc.year  = dgd.m_nYear;
					vc.month = dgd.m_nMonth;
					vc.day   = dgd.m_nDay;
					vc.shour = (dgd.m_nHour*60.0 + dgd.m_nMin) / 1440.0;
					day.DayCalc(vc, earth);
					nMasa = day.MasaCalc(vc, earth);
					nTithi = day.nTithi;
				}
				else if (dgd.m_nNextStep == -1)
				{
					goto AE_LocAgain;
				}
			}
			else if (dgl.m_nNextStep == -1)
			{
				goto AE_TypeAgain;
			}
			// gregorian date
			break;
		}

		// zadava text eventu
		if (degt.DoModal() == IDOK)
		{
			ce.nMasa = nMasa;
			ce.nTithi = nTithi;
			ce.strText = degt.m_strText;

			n = m_list.InsertItem(1000, GCStrings::GetTithiName(ce.nTithi));
			m_list.SetItemText(n, 1, GCStrings::GetPaksaName(ce.nTithi / 15));
			m_list.SetItemText(n, 2, GCStrings::GetMasaName(ce.nMasa));
			m_list.SetItemText(n, 3, ce.strText);
			m_list.SetItemData(n, ce.nTithi + ce.nMasa*30);

			// vklada do global custom events
/*			n = nMasa*30 + nTithi;
			if (gCustomEventTexts[n].IsEmpty() == TRUE)
			{
				gCustomEventTexts[n] = ce.strText;
			}
			else
			{
				gCustomEventTexts[n] += "#";
				gCustomEventTexts[n] += ce.strText;
			}*/

		}
		else
		{
		}

	}
}

void DlgCustomEventDialog::OnRemoveEvent() 
{
	int i;
	POSITION pos;
	
	pos = m_list.GetFirstSelectedItemPosition();

	while(pos)
	{
		i = m_list.GetNextSelectedItem(pos);
		m_list.DeleteItem(i);
	}
}

void DlgCustomEventDialog::OnOK() 
{
	int i, max, data;
	// TODO: Add extra validation here
	gCustomEventList.clear();
	
	CCustomEvent * pce;

	i = 0;
	max = m_list.GetItemCount();

/*	for(i = 0; i < 360; i++)
	{
		if (gCustomEventTexts[i].IsEmpty() == FALSE)
			gCustomEventTexts[i].Empty();
	}*/

	for(i = 0; i < max; i++)
	{
		pce = gCustomEventList.add();
		if (pce)
		{
			data = m_list.GetItemData(i);
			pce->strText = m_list.GetItemText(i, 3);
			pce->nTithi = data % 30;
			pce->nMasa = data / 30;
/*			if (gCustomEventTexts[data].IsEmpty() == TRUE)
			{
				gCustomEventTexts[data] = pce->strText;
			}
			else
			{
				gCustomEventTexts[data] += "#";
				gCustomEventTexts[data] += pce->strText;
			}*/
		}
	}

//	CustomEventListWriteFile(GCalApp_GetFileName(GSTR_CE_FILE));

	CDialog::OnOK();
}

void DlgCustomEventDialog::OnButtonEdit() 
{
	int i;
	POSITION pos;
	int data;
	TString strText;
	DlgEditCustomEvent dece;
	
	pos = m_list.GetFirstSelectedItemPosition();

	if(pos)
	{
		i = m_list.GetNextSelectedItem(pos);
		data = m_list.GetItemData(i);
		strText = m_list.GetItemText(i, 3);

		dece.m_nTithi = data % 30;
		dece.m_nMasa  = data / 30;
		dece.m_strText = strText;
		if (dece.DoModal() == IDOK)
		{
			data = dece.m_nTithi + dece.m_nMasa*30;
			m_list.SetItemData(i, data);
			m_list.SetItemText(i, 0, GCStrings::GetTithiName(dece.m_nTithi));
			m_list.SetItemText(i, 1, GCStrings::GetPaksaName(dece.m_nTithi/15));
			m_list.SetItemText(i, 2, GCStrings::GetMasaName(dece.m_nMasa));
			m_list.SetItemText(i, 3, dece.m_strText);
	
		}
	}
}
