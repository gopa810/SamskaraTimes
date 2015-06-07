#if !defined(AFX_DNEWCOUNTRY_H__C16133DB_F499_4497_BFE5_21E00A25C7DB__INCLUDED_)
#define AFX_DNEWCOUNTRY_H__C16133DB_F499_4497_BFE5_21E00A25C7DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DNewCountry.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DNewCountry dialog

class DNewCountry : public CDialog
{
// Construction
public:
	int nContinent;
	CString strName;
	CString strCode;
	DNewCountry(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DNewCountry)
	enum { IDD = IDD_NEW_COUNTRY };
	CComboBox	m_wCont;
	CEdit	m_wName;
	CEdit	m_wCode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DNewCountry)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DNewCountry)
	afx_msg void OnChangeEdit1();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DNEWCOUNTRY_H__C16133DB_F499_4497_BFE5_21E00A25C7DB__INCLUDED_)
