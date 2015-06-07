#if !defined(AFX_DLGASKLIMITATION_H__005BE17A_05D7_4E17_8B1F_4EC0BE898CAE__INCLUDED_)
#define AFX_DLGASKLIMITATION_H__005BE17A_05D7_4E17_8B1F_4EC0BE898CAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAskLimitation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgAskLimitation dialog

class DlgAskLimitation : public CDialog
{
// Construction
public:
	DlgAskLimitation(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgAskLimitation)
	enum { IDD = IDD_DIALOG4 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgAskLimitation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgAskLimitation)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGASKLIMITATION_H__005BE17A_05D7_4E17_8B1F_4EC0BE898CAE__INCLUDED_)
