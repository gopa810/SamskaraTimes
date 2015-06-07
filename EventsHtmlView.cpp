// EventsHtmlView.cpp: implementation of the CResultHtmlView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "vcal5beta.h"
#include "EventsHtmlView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CResultHtmlView::CResultHtmlView()
{

}

CResultHtmlView::~CResultHtmlView()
{

}

void CResultHtmlView::OnBeforeNavigate2( LPCTSTR lpszURL, DWORD nFlags,
			LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, 
			LPCTSTR lpszHeaders, BOOL* pbCancel )
{
	int a;

	a = 0;

	if (strcmp(lpszURL,"action:list")==0)
	{
		*pbCancel = TRUE;
	}
}
