// StaticHeader1.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "StaticHeader1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaticHeader1

CStaticHeader1::CStaticHeader1()
{
	m_bInitialized = FALSE;
}

CStaticHeader1::~CStaticHeader1()
{
}


BEGIN_MESSAGE_MAP(CStaticHeader1, CStatic)
	//{{AFX_MSG_MAP(CStaticHeader1)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticHeader1 message handlers

void CStaticHeader1::InitMyFont()
{
	if (m_bInitialized == FALSE)
	{
		m_myFont.CreateFont(32, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,"Tahoma");
		m_bInitialized = TRUE;
	}
	
	SetFont(&m_myFont);
}
