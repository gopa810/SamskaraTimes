#if !defined(AFX_DLGEDITLOCATION_H__1634F6F2_A2E4_4E22_A99E_15DC6120C7E2__INCLUDED_)
#define AFX_DLGEDITLOCATION_H__1634F6F2_A2E4_4E22_A99E_15DC6120C7E2__INCLUDED_

#include "Location.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEditLocation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgEditLocation dialog

class DlgEditLocation : public CDialog
{
// Construction
public:
	int m_nLastDst;
	void LocationToDialog();
	void UpdateDSTInfo();
	BOOL m_bEdit;
	CLocation * m_loc;
	BOOL errLong;
	BOOL errLati;
	const char * lastLatiAnalyse;
	const char * lastLongAnalyse;
	DlgEditLocation(CWnd* pParent = NULL);   // standard constructor
	int UpdateDstByTimezone(double tzone);

// Dialog Data
	//{{AFX_DATA(DlgEditLocation)
	enum { IDD = IDD_CREATE_LOCATION };
	CEdit	cCity;
	CComboBox	cCountry;
	CComboBox	cDst;
	CEdit	cNote;
	CEdit	cLong;
	CEdit	cLat;
	CEdit	cDstInfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgEditLocation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgEditLocation)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnChangeEdit5();
	afx_msg void OnSelendokComboCountry();
	afx_msg void OnSelendokComboDst();
	afx_msg void OnEditchangeComboCountry();
	afx_msg void OnSelendokCombo7();
	afx_msg void OnDropdownComboDst();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEDITLOCATION_H__1634F6F2_A2E4_4E22_A99E_15DC6120C7E2__INCLUDED_)
