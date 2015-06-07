#if !defined(AFX_DLGRENAMECOUNTRY_H__8F1734B0_1A9A_41E2_BDFC_84DA486094C7__INCLUDED_)
#define AFX_DLGRENAMECOUNTRY_H__8F1734B0_1A9A_41E2_BDFC_84DA486094C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRenameCountry.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgRenameCountry dialog

class DlgRenameCountry : public CDialog
{
// Construction
public:
	int nSelected;
	DlgRenameCountry(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgRenameCountry)
	enum { IDD = IDD_RENAME_COUNTRY };
	CEdit	m_Edit;
	CListBox	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgRenameCountry)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgRenameCountry)
	afx_msg void OnSaveEdit();
	afx_msg void OnSelChange();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRENAMECOUNTRY_H__8F1734B0_1A9A_41E2_BDFC_84DA486094C7__INCLUDED_)
