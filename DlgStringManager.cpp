// DlgStringManager.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "DlgStringManager.h"
#include "strings.h"
#include "DlgEditString.h"
#include "avc.h"
#include "GCStrings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern GCalApp theApp;

/////////////////////////////////////////////////////////////////////////////
// DlgStringManager dialog


DlgStringManager::DlgStringManager(CWnd* pParent /*=NULL*/)
	: CDialog(DlgStringManager::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgStringManager)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgStringManager::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgStringManager)
	DDX_Control(pDX, IDC_LIST1, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgStringManager, CDialog)
	//{{AFX_MSG_MAP(DlgStringManager)
	ON_BN_CLICKED(IDC_BUTTON1, OnEdit)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON2, OnImport)
	ON_BN_CLICKED(IDC_BUTTON3, OnExport)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnHelp)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgStringManager message handlers

void DlgStringManager::OnEdit() 
{
	// TODO: Add your control notification handler code here
	POSITION pos;
	int i;
	int id;

	pos = m_List.GetFirstSelectedItemPosition();
	if (pos)
	{
		i = m_List.GetNextSelectedItem(pos);
		id = m_List.GetItemData(i);
		// edit char
		DlgEditString des;

		des.m_orig = GCStrings::getString(id).c_str();
		des.m_new = m_List.GetItemText(i, 1);
		if (des.DoModal()==IDOK)
		{
			m_List.SetItemText(i, 1, des.m_new);
			gstr_Modified = 1;
		}
	}
}

void DlgStringManager::OnOK() 
{
	// TODO: Add extra validation here
	SaveStringsToMemory();	
	CDialog::OnOK();
}

BOOL DlgStringManager::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString str1, str2;

	m_List.InsertColumn(0, "ID", LVCFMT_RIGHT, 50, 0);
	m_List.InsertColumn(1, "String", LVCFMT_LEFT, 250, 1);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	InitListWithStrings();

	GetDlgItem(IDC_BUTTON5)->EnableWindow(theApp.m_bHelpAvailable);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgStringManager::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	POSITION pos;

	pos = m_List.GetFirstSelectedItemPosition();

	if (pos != NULL)
	{
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	}
	
	*pResult = 0;
}

void DlgStringManager::OnImport() 
{
	int i;
	CString str;
	// TODO: Add your control notification handler code here
	CFileDialog cfd(TRUE, "srl", NULL, 0, "String Rich List File (*.srl)|*.srl||");

	if (cfd.DoModal() == IDOK)
	{
		i = GCStrings::readFile(cfd.GetPathName());
		if (i < 0)
			MessageBox("Cannot open file", "Import Strings", MB_OK | MB_ICONSTOP);
		else
		{
			InitListWithStrings();
			str.Format("Imported %d strings", i);
			MessageBox(str, "Import Strings", MB_OK | MB_ICONINFORMATION);
			gstr_Modified = 1;
		}
	}
}

void DlgStringManager::OnExport() 
{
	// TODO: Add your control notification handler code here
	int i;
	CString str;
	// TODO: Add your control notification handler code here
	CFileDialog cfd(FALSE, "srl", NULL, 0, "String Rich List File (*.srl)|*.srl||");

	if (cfd.DoModal() == IDOK)
	{
		SaveStringsToMemory();
		i = GCStrings::writeFile(cfd.GetPathName());
		if (i < 0)
			MessageBox("Cannot write file", "Export Strings", MB_OK | MB_ICONSTOP);
		else
		{
			str.Format("Exported %d strings", i);
			MessageBox(str, "Export Strings", MB_OK | MB_ICONINFORMATION);
		}
	}
		
}

void DlgStringManager::OnButton4() 
{
	InitGlobalStrings(1);
	InitListWithStrings();
}

void DlgStringManager::InitListWithStrings()
{
	TString str1;
	int i, j, nn;

	// a[x][0] je zaciatocny index
	// a[x][1] je konecny index skupiny (vratane)
	int a[3][2] =
	{
		{ 0, 128 },
		{ 135, 199 },
		{ 561, 899 }
	};

	m_List.DeleteAllItems();
	// save 0 - 128
	// save 135 - 199
	// save 561 - 899
	for(j = 0; j < 3; j++)
	{
		for(i = a[j][0]; i <= a[j][1]; i++)
		{
			if (GCStrings::getString(i).GetLength() > 0)
			{
				str1.Format("%6d", i);
				nn = m_List.InsertItem(1, str1);
				m_List.SetItemText(nn, 1, GCStrings::getString(i).c_str());
				m_List.SetItemData(nn, i);
			}
		}
	}

}

void DlgStringManager::OnHelp() 
{
	// TODO: Add your control notification handler code here
	GCalShowHelp("ref-strman.htm");
	
}

void DlgStringManager::SaveStringsToMemory()
{
	int i, m, ind;
	CString str;

	m = m_List.GetItemCount();

	for(i = 0; i < m; i++)
	{
		ind = m_List.GetItemData(i);
		str = m_List.GetItemText(i, 1);
		GCStrings::setString(ind, (LPCTSTR)(str));
	}
}

void DlgStringManager::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here

	CString strf;
	CString str;
	int i, m;
	int ev = -1;

	GetDlgItemText(IDC_EDIT1, strf);

	m = m_List.GetItemCount();
	for(i = 0; i < m; i++)
	{
		str = m_List.GetItemText(i, 1);
		if (str.Find(strf, 0) >= 0 && strf.GetLength()>0)
		{
			//m_List.SetSelectionMark(i);
			m_List.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
			//m_List.SetCheck(i, TRUE);
			if (ev < 0) {
				m_List.EnsureVisible(i, FALSE);
				ev = i;
			}
//			break;
		}
		else
		{
			m_List.SetItemState(i, 0, LVIS_SELECTED);
		}
	}
}
