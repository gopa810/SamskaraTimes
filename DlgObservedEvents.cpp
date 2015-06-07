// DlgObservedEvents.cpp : implementation file
//

#include "stdafx.h"
#include "VCal5beta.h"
#include "DlgObservedEvents.h"
#include "vedic_ui.h"
#include "strings.h"
#include "level_0.h"
#include "TFile.h"
#include "GCStrings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgObservedEvents dialog


DlgObservedEvents::DlgObservedEvents(CWnd* pParent /*=NULL*/)
	: CDialog(DlgObservedEvents::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgObservedEvents)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgObservedEvents::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgObservedEvents)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgObservedEvents, CDialog)
	//{{AFX_MSG_MAP(DlgObservedEvents)
	ON_BN_CLICKED(IDC_BUTTON1, OnExport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//char * gp_Fest[];

/////////////////////////////////////////////////////////////////////////////
// DlgObservedEvents message handlers

void DlgObservedEvents::OnExport() 
{
	CFileDialog d(FALSE, "txt", "events", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST, "Text file (*.txt)|*.txt|XML File (*.xml)|*.xml||");
	CString strc;

	if (d.DoModal() == IDOK)
	{
		TString str, str2, str3;
		TFile f;

		if (f.Open(d.GetPathName(), "w") == TRUE)
		{
			int i, m;

			switch(d.m_ofn.nFilterIndex)
			{
			case 1:
				m = m_list.GetCount();
				for(i = 0; i < m; i++)
				{
					m_list.GetText(i, strc);
					f.WriteString(strc);
					f.WriteString("\n");
				}
				break;
			case 2:
				{
					int n;
					f.WriteString("<xml>\n");
					for(i = 0; i < 360; i++)
					{
						n = 0;
						if (GCStrings::getString(200+i).IsEmpty() == FALSE)
						{
							str2 = GCStrings::getString(200 + i);
							n = str2.Find("#");
							while(n >= 0)
							{
								str2.Left(n, str3);
								str.Format("\t<event name=\"%s\" tithi=\"%s\" paksa=\"%s\" masa=\"%s\" />\n", str3.c_str(), GCStrings::GetTithiName(i % 30), 
									GCStrings::GetPaksaName((i/15)%2), GCStrings::GetMasaName(i/30));
								str2.Delete(0, n+1);
								f.WriteString(str);
								n = str2.Find("#");
							}
							if (str2.IsEmpty() == FALSE)
							{
								str.Format("\t<event name=\"%s\" tithi=\"%s\" paksa=\"%s\" masa=\"%s\" />\n", str2.c_str(), 
									GCStrings::GetTithiName(i % 30), GCStrings::GetPaksaName((i/15)%2), GCStrings::GetMasaName(i/30));
								f.WriteString(str);
							}
						}
					}
					f.WriteString("\t<event name=\"");
					f.WriteString(GCStrings::GetSpecFestivalName(SPEC_JANMASTAMI));
					f.WriteString("\" tithi=\"Astami\" paksa=\"Krsna\" masa=\"Hrsikesa\" />\n");
					f.WriteString("\t<event name=\"");
					f.WriteString(GCStrings::GetSpecFestivalName(SPEC_GOVARDHANPUJA));
					f.WriteString("\" tithi=\"Pratipat\" paksa=\"Gaura\" masa=\"Damodara\" />\n");
					f.WriteString("\t<event name=\"");
					f.WriteString(GCStrings::GetSpecFestivalName(SPEC_RATHAYATRA));
					f.WriteString("\" tithi=\"Dvitiya\" paksa=\"Gaura\" masa=\"Vamana\" />\n");
					f.WriteString("\t<event name=\"");
					f.WriteString(GCStrings::GetSpecFestivalName(SPEC_GAURAPURNIMA));
					f.WriteString("\" tithi=\"Purnima\" paksa=\"Gaura\" masa=\"Govinda\" />\n");
					f.WriteString("\t<event name=\"");
					f.WriteString(GCStrings::GetSpecFestivalName(SPEC_NANDAUTSAVA));
					f.WriteString("\" depends=\"Sri Krsna Janmastami\" rel=\"+1\"/>\n");
					f.WriteString("\t<event name=\"");
					f.WriteString(GCStrings::GetSpecFestivalName(SPEC_PRABHAPP));
					f.WriteString("\" depends=\"Sri Krsna Janmastami\" rel=\"+1\"/>\n");
					f.WriteString("\t<event name=\"");
					f.WriteString(GCStrings::GetSpecFestivalName(SPEC_MISRAFESTIVAL));
					f.WriteString("\" depends=\"Gaura Purnima\" rel=\"+1\"/>\n");
					f.WriteString("\t<event name=\"");
					f.WriteString(GCStrings::GetSpecFestivalName(SPEC_HERAPANCAMI));
					f.WriteString("\" depends=\"Ratha Yatra\" rel=\"+4\"/>\n");
					f.WriteString("\t<event name=\"");
					f.WriteString(GCStrings::GetSpecFestivalName(SPEC_RETURNRATHA));
					f.WriteString("\" depends=\"Ratha Yatra\" rel=\"+8\"/>\n");
					f.WriteString("\t<event name=\"");
					f.WriteString(GCStrings::GetSpecFestivalName(SPEC_GUNDICAMARJANA));
					f.WriteString("\" depends=\"Ratha Yatra\" rel=\"-1\"/>\n");
					f.WriteString("\t<event name=\"");
					f.WriteString(GCStrings::getString(78));
					f.WriteString("\" sankranti=\"Makara\" rel=\"0\"/>\n");
					f.WriteString("\t<event name=\"");
					f.WriteString(GCStrings::getString(79));
					f.WriteString("\" sankranti=\"Mesha\" rel=\"0\"/>\n");
					f.WriteString("\t<event name=\"");
					f.WriteString(GCStrings::getString(80));
					f.WriteString("\" sankranti=\"Vrsabha\" rel=\"-1\"/>\n");
					f.WriteString("\t<event name=\"");
					f.WriteString(GCStrings::GetSpecFestivalName(SPEC_RAMANAVAMI));
					f.WriteString("\" tithi=\"Navami\" paksa=\"Gaura\" masa=\"Visnu\" />\n");
					f.WriteString("</xml>\n");
				}
				break;
			default:
				break;
			}
			f.Close();
		}
	}
}


BOOL DlgObservedEvents::OnInitDialog() 
{
	int n;
	int pTabs[] = {230,300,370,450};
	TString str, str2, str3;
	CDialog::OnInitDialog();
	char szTemp[256];
	int nTemp = 0;
	int ct = 0;
	const char * pSrc;
	int nBrLevel = 0;

	m_list.SetTabStops(3, pTabs);

	for(int i = 0; i < 360; i++)
	{
		n = 0;
		if (GCStrings::getString(200+i).IsEmpty() == FALSE)
		{
			pSrc = GCStrings::getString(200 + i);

			for(ct = 0; pSrc[ct]; ct++)
			{
				// beginning of note
				if (pSrc[ct] == '[')
				{
					nBrLevel++;
				}

				if (pSrc[ct] == '#')
				{
					if (nTemp >= 256)
						szTemp[255] = 0;
					else
						szTemp[nTemp] = 0;
					str.Format("%s\t%s, %s Paksa, %s Masa", szTemp, GCStrings::GetTithiName(i % 30), GCStrings::GetPaksaName((i/15)%2), GCStrings::GetMasaName(i/30));
					m_list.AddString(str);
					nTemp = 0;
				}
				else if (nBrLevel < 1)
				{
					if (nTemp < 256)
					{
						szTemp[nTemp] = pSrc[ct];
						nTemp++;
					}
				}

				// end of note
				if (pSrc[ct] == ']')
				{
					nBrLevel--;
				}
			}

			if (nTemp > 0)
			{
				if (nTemp >= 256)
					szTemp[255] = 0;
				else
					szTemp[nTemp] = 0;
				str.Format("%s\t%s, %s Paksa, %s Masa", szTemp, GCStrings::GetTithiName(i % 30), GCStrings::GetPaksaName((i/15)%2), GCStrings::GetMasaName(i/30));
				m_list.AddString(str);
				nTemp = 0;
			}

		}
	}

	m_list.AddString("Sri Krsna Janmastami\tAstami, Krsna Paksa, Hrsikesa Masa");
	m_list.AddString("Govardhana Puja, Go Puja, Go Krda.\tPratipat, Gaura Paksa, Damodara Masa");
	m_list.AddString("Nandotsava.\t(a day after Sri Krsna Janmastami)");
	m_list.AddString("Srila Prabhupada -- Appearance\t(a day after Sri Krsna Janmastami)");
	m_list.AddString("Ratha Yatra\tDvitiya, Gaura Paksa, Vamana Masa");
	m_list.AddString("Gaura Purnima\tPurnima, Gaura Paksa, Govinda Masa");
	m_list.AddString("Jagannatha Misra festival\t(a day after Gaura Purnima)");
	m_list.AddString("Hera Pancami\t(4 days after Ratha yatra)");
	m_list.AddString("Return Ratha yatra\t(8 days after Ratha yatra festival)");
	m_list.AddString("Gundica Marjana\t(a day before Ratha Yatra festival");
	m_list.AddString("Ganga Sagara Mela\t(Makara Sankranti)");
	m_list.AddString("Tulasi Jala Dan begins\t(Mesha Sankranti)");
	m_list.AddString("Tulasi Jala Dan ends\t(a day before Vrsabha Sankranti)");
	m_list.AddString("Rama Navami\tNavami, Gaura Paksa, Visnu Masa");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
