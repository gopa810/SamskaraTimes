#if !defined(AFX_DLGEVENTSTYPEOFEVENT_H__83EFFF8F_342D_4C7F_816E_03890C7F74E5__INCLUDED_)
#define AFX_DLGEVENTSTYPEOFEVENT_H__83EFFF8F_342D_4C7F_816E_03890C7F74E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "staticheader3.h"
// DlgEventsTypeOfEvent.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgEventsTypeOfEvent dialog

class DlgEventsTypeOfEvent : public CDialog
{
// Construction
public:
	int m_nType;
	DlgEventsTypeOfEvent(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgEventsTypeOfEvent)
	enum { IDD = IDD_EVENTS_1 };
	CStaticHeader3	m_s2;
	CStaticHeader3	m_s1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgEventsTypeOfEvent)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgEventsTypeOfEvent)
	afx_msg void OnGaurabdaDate();
	afx_msg void OnGregorianDate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEVENTSTYPEOFEVENT_H__83EFFF8F_342D_4C7F_816E_03890C7F74E5__INCLUDED_)
