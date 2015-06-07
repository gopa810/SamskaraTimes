#if !defined(AFX_DLGEVENTSGETTEXT_H__74DC8993_F071_4AB6_9BFB_03C25E284F7B__INCLUDED_)
#define AFX_DLGEVENTSGETTEXT_H__74DC8993_F071_4AB6_9BFB_03C25E284F7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEventsGetText.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgEventsGetText dialog

class DlgEventsGetText : public CDialog
{
// Construction
public:
	DlgEventsGetText(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgEventsGetText)
	enum { IDD = IDD_EVENTS_GET_TEXT };
	CString	m_strText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgEventsGetText)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgEventsGetText)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEVENTSGETTEXT_H__74DC8993_F071_4AB6_9BFB_03C25E284F7B__INCLUDED_)
