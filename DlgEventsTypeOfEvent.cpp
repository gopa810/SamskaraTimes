// DlgEventsTypeOfEvent.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "DlgEventsTypeOfEvent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgEventsTypeOfEvent dialog


DlgEventsTypeOfEvent::DlgEventsTypeOfEvent(CWnd* pParent /*=NULL*/)
	: CDialog(DlgEventsTypeOfEvent::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgEventsTypeOfEvent)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nType = 0;
}


void DlgEventsTypeOfEvent::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgEventsTypeOfEvent)
	DDX_Control(pDX, IDC_STATIC2, m_s2);
	DDX_Control(pDX, IDC_STATIC1, m_s1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgEventsTypeOfEvent, CDialog)
	//{{AFX_MSG_MAP(DlgEventsTypeOfEvent)
	ON_BN_CLICKED(IDC_BUTTON1, OnGaurabdaDate)
	ON_BN_CLICKED(IDC_BUTTON2, OnGregorianDate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgEventsTypeOfEvent message handlers

void DlgEventsTypeOfEvent::OnGaurabdaDate() 
{
	// TODO: Add your control notification handler code here
	m_nType = 1;
	CDialog::OnOK();
}

void DlgEventsTypeOfEvent::OnGregorianDate() 
{
	// TODO: Add your control notification handler code here
	m_nType = 2;
	CDialog::OnOK();	
}
