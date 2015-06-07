#if !defined(AFX_TITHICALC_H__876B52A6_8955_4730_B7CC_0132E1C64DC7__INCLUDED_)
#define AFX_TITHICALC_H__876B52A6_8955_4730_B7CC_0132E1C64DC7__INCLUDED_

#include "level_0.h"	// Added by ClassView
#include "staticheader1.h"
#include "locationref.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TithiCalc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgGetStartDate dialog

class DlgGetStartDate : public CDialog
{
// Construction
public:
	CMenu m_setMenu;
	BOOL f_update;
	EARTHDATA m_earth;
	static VCTIME m_resultC;
	static VATIME m_resultA;
	static int s_init;

	void SynchroGaurabdaToGregorian();
	void SynchroGregorianToGaurabda();
	BOOL bFinal;
	int m_nNextStep;
	DlgGetStartDate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgGetStartDate)
	enum { IDD = IDD_DIALOG1 };
	CEdit	w_year;
	CComboBox	w_tithi;
	CComboBox	w_masa;
	CEdit	w_gyear;
	CComboBox	w_month;
	CComboBox	w_day;
	CStaticHeader1	m_hdr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgGetStartDate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgGetStartDate)
	afx_msg void OnCalc();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonBack();
	afx_msg void OnSelendokCombo3();
	afx_msg void OnSelendokCombo4();
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEdit1();
	afx_msg void OnSelendokCombo1();
	afx_msg void OnSelendokCombo2();
	afx_msg void OnButtonSet();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TITHICALC_H__876B52A6_8955_4730_B7CC_0132E1C64DC7__INCLUDED_)
