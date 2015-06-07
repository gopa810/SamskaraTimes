// StaticHeader3.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "StaticHeader3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaticHeader3

CStaticHeader3::CStaticHeader3()
{
	m_bThisControlInit = FALSE;
}

CStaticHeader3::~CStaticHeader3()
{
}


BEGIN_MESSAGE_MAP(CStaticHeader3, CStatic)
	//{{AFX_MSG_MAP(CStaticHeader3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CFont CStaticHeader3::m_myFont;
BOOL  CStaticHeader3::m_myFontInit = FALSE;

/////////////////////////////////////////////////////////////////////////////
// CStaticHeader3 message handlers


void CStaticHeader3::InitMyFont()
{
	if (m_myFontInit == FALSE)
	{
		NONCLIENTMETRICS ncm;

		ncm.cbSize = sizeof(NONCLIENTMETRICS);

		SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &ncm, 0);

		m_myFont.CreateFontIndirect(&ncm.lfCaptionFont);

		m_myFontInit = TRUE;
	}

	if (m_bThisControlInit == FALSE)
	{
		m_bThisControlInit = TRUE;
		SetFont(&m_myFont);
	}
}
