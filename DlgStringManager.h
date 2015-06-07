#if !defined(AFX_DLGSTRINGMANAGER_H__D2055F77_679F_4ECE_8C24_ED422A6770C5__INCLUDED_)
#define AFX_DLGSTRINGMANAGER_H__D2055F77_679F_4ECE_8C24_ED422A6770C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgStringManager.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgStringManager dialog

class DlgStringManager : public CDialog
{
// Construction
public:
	void SaveStringsToMemory();
	void InitListWithStrings();
	DlgStringManager(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgStringManager)
	enum { IDD = IDD_STRING_MANAGER };
	CListCtrl	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgStringManager)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgStringManager)
	afx_msg void OnEdit();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnImport();
	afx_msg void OnExport();
	afx_msg void OnButton4();
	afx_msg void OnHelp();
	afx_msg void OnChangeEdit1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSTRINGMANAGER_H__D2055F77_679F_4ECE_8C24_ED422A6770C5__INCLUDED_)
