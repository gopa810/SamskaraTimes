// DlgRenameCountry.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "DlgRenameCountry.h"
#include "TCountry.h"
#include "Location.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgRenameCountry dialog


DlgRenameCountry::DlgRenameCountry(CWnd* pParent /*=NULL*/)
	: CDialog(DlgRenameCountry::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgRenameCountry)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgRenameCountry::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgRenameCountry)
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
	DDX_Control(pDX, IDC_LIST1, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgRenameCountry, CDialog)
	//{{AFX_MSG_MAP(DlgRenameCountry)
	ON_BN_CLICKED(IDC_BUTTON1, OnSaveEdit)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgRenameCountry message handlers

void DlgRenameCountry::OnSaveEdit() 
{
	// TODO: Add your control notification handler code here
	CString str;
	CString strOld;
	CString str2;
	int idx;
	WORD w;

	m_Edit.GetWindowText(str);
	idx = m_List.GetItemData(nSelected);

	if (nSelected >= 0)
	{
		strOld = TCountry::GetCountryNameByIndex(idx);
		TCountry::SetCountryName(idx, (LPCTSTR)str);
		str2.Format("%s [%s]", str, TCountry::GetCountryAcronymByIndex(idx));
		w = TCountry::gcountries_var[idx].code;
		m_List.InsertString(nSelected, str2);
		m_List.DeleteString(nSelected + 1);
		m_List.SetItemData(nSelected, idx);
		m_List.SetCurSel(nSelected);
		theLocs.RenameCountry((LPCTSTR)strOld, str);
	}
}

void DlgRenameCountry::OnSelChange() 
{
	// TODO: Add your control notification handler code here
	int n = m_List.GetCurSel();

	int idx = m_List.GetItemData(n);

	nSelected = n;

	m_Edit.SetWindowText(TCountry::GetCountryNameByIndex(idx));

}

BOOL DlgRenameCountry::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString str;

	int n, cnt, b;

	cnt = TCountry::GetCountryCount();

	for(n = 0; n < cnt; n++)
	{
		str.Format("%s [%s]", TCountry::GetCountryNameByIndex(n),
			TCountry::GetCountryAcronymByIndex(n));
		b = m_List.AddString(str);
		m_List.SetItemData(b, n);
	}

	nSelected = -1;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
