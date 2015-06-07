#if !defined(AFX_DLGCALCPROGRESS_H__4698EADD_D338_4547_AC9A_E26B36B548A7__INCLUDED_)
#define AFX_DLGCALCPROGRESS_H__4698EADD_D338_4547_AC9A_E26B36B548A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCalcProgress.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgCalcProgress dialog

class DlgCalcProgress : public CDialog
{
// Construction
public:
	DlgCalcProgress(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgCalcProgress)
	enum { IDD = IDD_CALC_PROGRESS };
	CProgressCtrl	m_p1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgCalcProgress)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgCalcProgress)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCALCPROGRESS_H__4698EADD_D338_4547_AC9A_E26B36B548A7__INCLUDED_)
