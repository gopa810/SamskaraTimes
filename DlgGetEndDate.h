#if !defined(AFX_DLGGETENDDATE_H__0439CFCA_9EA4_4A26_A0C1_6773200915B7__INCLUDED_)
#define AFX_DLGGETENDDATE_H__0439CFCA_9EA4_4A26_A0C1_6773200915B7__INCLUDED_

#include "level_0.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGetEndDate.h : header file
//

#include "staticheader1.h"

/////////////////////////////////////////////////////////////////////////////
// DlgGetEndDate dialog

class DlgGetEndDate : public CDialog
{
// Construction
public:
	int m_uncorrected_count;
	BOOL bFinal;
	void Recalc();
	int m_nNextStep;
	EARTHDATA m_earth;
	VATIME va_end;
	VCTIME vc_end;
	VATIME va_start;
	VCTIME vc_start;
	static int m_type;
	static int m_count;


	DlgGetEndDate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgGetEndDate)
	enum { IDD = IDD_END_DATE };
	CStaticHeader1	m_hdr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgGetEndDate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgGetEndDate)
	afx_msg void OnButtonBack();
	afx_msg void OnSet1();
	afx_msg void OnSet3();
	afx_msg void OnSet7();
	afx_msg void OnSet21();
	afx_msg void OnNumInc();
	afx_msg void OnNumDec();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	afx_msg void OnRadio7();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnChangeEdit1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGETENDDATE_H__0439CFCA_9EA4_4A26_A0C1_6773200915B7__INCLUDED_)
