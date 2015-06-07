#if !defined(AFX_DLGGETLOCATIONEX_H__142F4D8F_EB41_40D5_B2C8_EDD388BAAECB__INCLUDED_)
#define AFX_DLGGETLOCATIONEX_H__142F4D8F_EB41_40D5_B2C8_EDD388BAAECB__INCLUDED_

#include "Location.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGetLocationEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgGetLocationEx dialog

class DlgGetLocationEx : public CDialog
{
// Construction
public:
	BOOL ShowInGoogleMaps();
	void OnImportList();
	CMenu m_menu;
	int InitCountries(const char * pszCurrentCountry = NULL);
	int InitCitiesForCountry(int nCurrentCountry, const char * pszCurrentCity = NULL);
	CLocation * m_lc;
	DlgGetLocationEx(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgGetLocationEx)
	enum { IDD = IDD_GET_LOCATION_EX };
	CListBox	m_cities;
	CEdit	m_edit;
	CComboBox	m_countries;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgGetLocationEx)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgGetLocationEx)
	virtual BOOL OnInitDialog();
	afx_msg void OnCreateLocation();
	afx_msg void OnEditLocation();
	afx_msg void OnDeleteLocation();
	afx_msg void OnChangeEdit1();
	afx_msg void OnSelendokCombo1();
	afx_msg void OnSelchangeList1();
	afx_msg void OnSetCountryByCity();
	afx_msg void OnAllCities();
	afx_msg void OnResetList();
	afx_msg void OnButton7();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnSelendcancelCombo1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGETLOCATIONEX_H__142F4D8F_EB41_40D5_B2C8_EDD388BAAECB__INCLUDED_)
