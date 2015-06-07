// DlgSpecCommand.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "DlgSpecCommand.h"

#include "level_0.h"
#include "Location.h"
#include "TTimeZone.h"
#include "CustomEvent.h"
#include "strings.h"
#include "GCStrings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgSpecCommand dialog


DlgSpecCommand::DlgSpecCommand(CWnd* pParent /*=NULL*/)
	: CDialog(DlgSpecCommand::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgSpecCommand)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgSpecCommand::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgSpecCommand)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgSpecCommand, CDialog)
	//{{AFX_MSG_MAP(DlgSpecCommand)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgSpecCommand message handlers

void DlgSpecCommand::OnOK() 
{
	CString str;

	GetDlgItemText(IDC_EDIT1, str);

	if (str=="commands")
	{
		MessageBox("export locs cocoa\r\nexport timezones cocoa\r\n"
			"export strings cocoa\r\nexport events cocoa\r\n", "", MB_OK);
	}
	else if (str == "export locs cocoa")
	{
		ExportLocsCocoa();
	}
	else if (str == "export timezones cocoa")
	{
		ExportTzCocoa();
	}
	else if (str == "export events cocoa")
	{
		ExportEventsCocoa();
	}
	else if (str == "export strings cocoa")
	{
		ExportStrings();
	}
	
	CDialog::OnOK();
}

void DlgSpecCommand::ExportLocsCocoa()
{
	CString str;
	CFileDialog cfd(FALSE);
	if (cfd.DoModal() == IDOK)
	{
		CStdioFile std;

		if (std.Open(cfd.GetPathName(), CFile::modeWrite|CFile::modeCreate))
		{
			CLocation * p = theLocs.GetHeadPosition();
			while(p)
			{
				str.Format("%s|%s|%s|%s|%s#",
					p->m_strCity.c_str(),
					p->m_strCountry.c_str(),
					EARTHDATA::GetTextLatitude(p->m_fLatitude),
					EARTHDATA::GetTextLongitude(p->m_fLongitude),
					TTimeZone::GetTimeZoneName(p->m_nDST));
				std.WriteString(str);
				p = p->next;
			}
			std.Close();
		}
	}
}

/*
void DlgSpecCommand::Export...()
{
	CFileDialog cfd(FALSE);
	if (cfd.DoModal() == IDOK)
	{
		CStdioFile std;

		if (std.Open(cfd.GetPathName(), CFile::modeWrite|CFile::modeCreate))
		{
			std.Close();
		}
	}
}
*/

void DlgSpecCommand::ExportTzCocoa()
{
	CString str;
	CFileDialog cfd(FALSE);
	if (cfd.DoModal() == IDOK)
	{
		CStdioFile std;

		if (std.Open(cfd.GetPathName(), CFile::modeWrite|CFile::modeCreate))
		{
			int i, m;
			DWORD dw;
			int a[10];
			m = TTimeZone::GetTimeZoneCount();
			for(i = 0; i < m; i++)
			{
				dw = TTimeZone::gzone[i].val;
				TTimeZone::ExpandVal(dw, a);
				if (dw != 0)
				{
					if (a[1] == 1)
					{
						a[2] = 1;
						a[3] = 0;
					}
					else
					{
						a[0]--;
						a[2]--;
					}
					if (a[5] == 1)
					{
						a[6] = 1;
						a[7] = 0;
					}
					else
					{
						a[4]--;
						a[6]--;
					}
				}
				str.Format("%s|%d|%d|%d|%d|%d|%d|%d|%d|%d~",
					TTimeZone::gzone[i].name,
					TTimeZone::gzone[i].offset,
					TTimeZone::gzone[i].bias,
					TTimeZone::gzone[i].val > 0 ? 1 : 0,
					a[0]-1,
					a[2]-1, a[3],
					a[4]-1,
					a[6]-1, a[7]
					);
				std.WriteString(str);
			}
			std.Close();
		}
	}
}

void DlgSpecCommand::ExportEventsCocoa()
{
	CString str;
	CFileDialog cfd(FALSE);
	if (cfd.DoModal() == IDOK)
	{
		CStdioFile std;

		if (std.Open(cfd.GetPathName(), CFile::modeWrite|CFile::modeCreate))
		{
			CCustomEvent * p = gCustomEventList.list;
			while(p)
			{
				str.Format("%s|%d|%d|%d|%d|%s|%d|%d|%d~",
					p->strText.c_str(),
					p->nTithi,
					p->nMasa,
					p->nClass,
					p->nFastType,
					p->strFastSubject.c_str(),
					p->nSpec,
					p->nVisible,
					p->nUsed);
				std.WriteString(str);
				p = p->next;
			}
			std.Close();
		}
	}

}

void DlgSpecCommand::ExportStrings()
{
	CString str;
	CFileDialog cfd(FALSE);
	if (cfd.DoModal() == IDOK)
	{
		CStdioFile std;

		if (std.Open(cfd.GetPathName(), CFile::modeWrite|CFile::modeCreate))
		{
			int i;
			for(i = 0; i < 900; i++)
			{
				if (GCStrings::getString(i).GetLength() > 0)
				{
					str.Format("%s|%d|%s\n",
						GCStrings::getString(i).c_str(),
						i,
						GCStrings::getString(i).c_str()
						);
					std.WriteString(str);
				}
			}
			std.Close();
		}
	}

}
