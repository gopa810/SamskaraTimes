#if !defined(AFX_DPAGEGENERAL_H__B203AEF7_FAE8_4EC4_B3FD_E7571BA73BD2__INCLUDED_)
#define AFX_DPAGEGENERAL_H__B203AEF7_FAE8_4EC4_B3FD_E7571BA73BD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DPageGeneral.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DPageGeneral dialog

class DPageGeneral : public CPropertyPage
{
	DECLARE_DYNCREATE(DPageGeneral)

// Construction
public:
	DPageGeneral();
	~DPageGeneral();

// Dialog Data
	//{{AFX_DATA(DPageGeneral)
	enum { IDD = IDD_PAGE_GENERAL };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(DPageGeneral)
	public:
	virtual void OnOK();
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(DPageGeneral)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DPAGEGENERAL_H__B203AEF7_FAE8_4EC4_B3FD_E7571BA73BD2__INCLUDED_)
