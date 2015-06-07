// MyWebView.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "MyWebView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyWebView

IMPLEMENT_DYNCREATE(CMyWebView, CHtmlView)

CMyWebView::CMyWebView()
{
	//{{AFX_DATA_INIT(CMyWebView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMyWebView::~CMyWebView()
{
}

void CMyWebView::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyWebView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CMyWebView::OnNavigateComplete2( LPCTSTR strURL )
{
//	InvalidateRect(NULL);
}

void CMyWebView::OnDownloadComplete()
{
//	InvalidateRect(NULL);
}

BEGIN_MESSAGE_MAP(CMyWebView, CHtmlView)
	//{{AFX_MSG_MAP(CMyWebView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyWebView diagnostics

#ifdef _DEBUG
void CMyWebView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CMyWebView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyWebView message handlers
