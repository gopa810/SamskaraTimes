#if !defined(AFX_DLGEDITSTRING_H__62931476_1114_4927_8489_C9DF06AF2FA4__INCLUDED_)
#define AFX_DLGEDITSTRING_H__62931476_1114_4927_8489_C9DF06AF2FA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEditString.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgEditString dialog

class DlgEditString : public CDialog
{
// Construction
public:
	DlgEditString(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgEditString)
	enum { IDD = IDD_EDIT_STRING };
	CString	m_orig;
	CString	m_new;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgEditString)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgEditString)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEDITSTRING_H__62931476_1114_4927_8489_C9DF06AF2FA4__INCLUDED_)
