#if !defined(AFX_DLGGETEVENTSPEC_H__836A9F40_38D3_45D7_A91A_CA852AD2ECD0__INCLUDED_)
#define AFX_DLGGETEVENTSPEC_H__836A9F40_38D3_45D7_A91A_CA852AD2ECD0__INCLUDED_

#include "platform.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGetEventSpec.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgGetEventSpec dialog

class DlgGetEventSpec : public CDialog
{
// Construction
public:
	UInt32 m_fSort;
	UInt32 m_fOptions;
	int m_nNextStep;
	DlgGetEventSpec(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgGetEventSpec)
	enum { IDD = IDD_CALCEVENTS_TYPES };
	BOOL	m_sun;
	BOOL	m_tithi;
	BOOL	m_naks;
	BOOL	m_sank;
	BOOL	m_conj;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgGetEventSpec)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgGetEventSpec)
	afx_msg void OnButtonBack();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheck6();
	BOOL m_rahu_kalam;
	BOOL m_yama_ghanti;
	BOOL m_guli_kalam;
	BOOL m_moon_rasi;
	BOOL m_moon_times;
	BOOL m_ascendent;
//	CString m_off;
//	double m_off;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGETEVENTSPEC_H__836A9F40_38D3_45D7_A91A_CA852AD2ECD0__INCLUDED_)
