// DlgSelectSamskara.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "DlgSelectSamskara.h"
#include "afxdialogex.h"


// DlgSelectSamskara dialog

IMPLEMENT_DYNAMIC(DlgSelectSamskara, CDialog)

DlgSelectSamskara::DlgSelectSamskara(CWnd* pParent /*=NULL*/)
	: CDialog(DlgSelectSamskara::IDD, pParent)
{

}

DlgSelectSamskara::~DlgSelectSamskara()
{
}

void DlgSelectSamskara::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_list);
}


BEGIN_MESSAGE_MAP(DlgSelectSamskara, CDialog)
END_MESSAGE_MAP()


// DlgSelectSamskara message handlers


BOOL DlgSelectSamskara::OnInitDialog()
{
	CDialog::OnInitDialog();
	int i;

	// TODO:  Add extra initialization here
	i = m_list.AddString("[Samskaras]");
	m_list.SetItemDataPtr(i, "");

    i = m_list.AddString("    Vivaha Samskara");
	m_list.SetItemDataPtr(i, "vivaha");

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
