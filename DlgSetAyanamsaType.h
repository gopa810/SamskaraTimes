#if !defined(AFX_DLGSETAYANAMSATYPE_H__3E42904C_29B7_4C61_8183_4B1063953321__INCLUDED_)
#define AFX_DLGSETAYANAMSATYPE_H__3E42904C_29B7_4C61_8183_4B1063953321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSetAyanamsaType.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgSetAyanamsaType dialog

class DlgSetAyanamsaType : public CDialog
{
// Construction
public:
	DlgSetAyanamsaType(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgSetAyanamsaType)
	enum { IDD = IDD_SET_AYANAMSA };
	CListBox	m_san;
	CListBox	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgSetAyanamsaType)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgSetAyanamsaType)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETAYANAMSATYPE_H__3E42904C_29B7_4C61_8183_4B1063953321__INCLUDED_)
