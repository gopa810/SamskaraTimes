#if !defined(AFX_FRAMEBASE_H__34A0985F_C8B9_45B7_AFC7_60596383B293__INCLUDED_)
#define AFX_FRAMEBASE_H__34A0985F_C8B9_45B7_AFC7_60596383B293__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FrameBase.h : header file
#include "level_6.h"
//

/////////////////////////////////////////////////////////////////////////////
// CFrameBase frame

class CFrameBase : public CFrameWnd
{
//	DECLARE_DYNCREATE(CFrameBase)
protected:

// Attributes
public:
	class c__1
	{
	public:
		int    count;
		VCTIME vc_start;
		VATIME va_start;
		VCTIME vc_end;
		VATIME va_end;
	}
	calendar;

	CLocationRef earth;

	CFont m_fontInfo;
	CFont m_fontList;
	CFont m_fontPrintText;
	CFont m_fontPrintHdr;
	CRect m_rectPrintMargins;

// Operations
public:
	CRect m_rectWindow;
	BOOL m_bClosed;
	void InitBaseAttributes();
	int PrintBlockText(CDC &pdc, TString &strTitle, TString &strText, int &nPage, CRect & rcPrint);
	int AfxPrintCalendarText(CDC &dc, TResultCalendar &daybuff, CLocationRef & earth, VCTIME date, int nDaysCount, CRect & rcPrint);
	CFrameBase();           // protected constructor used by dynamic creation
	virtual ~CFrameBase();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrameBase)
	//}}AFX_VIRTUAL

// Implementation
protected:
	afx_msg void OnInitMenu(CMenu* pMenu);

	// Generated message map functions
	//{{AFX_MSG(CFrameBase)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAMEBASE_H__34A0985F_C8B9_45B7_AFC7_60596383B293__INCLUDED_)
