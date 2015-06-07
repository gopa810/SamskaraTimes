#if !defined(AFX_DPAGEFEST_H__7FCB3D07_B281_45DC_85A7_3E0804CFDC4B__INCLUDED_)
#define AFX_DPAGEFEST_H__7FCB3D07_B281_45DC_85A7_3E0804CFDC4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DPageFest.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DPageFest dialog

class DPageFest : public CPropertyPage
{
	DECLARE_DYNCREATE(DPageFest)

// Construction
public:
	DPageFest();
	~DPageFest();

// Dialog Data
	//{{AFX_DATA(DPageFest)
	enum { IDD = IDD_PAGE_FEST };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(DPageFest)
	public:
	virtual void OnOK();
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(DPageFest)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DPAGEFEST_H__7FCB3D07_B281_45DC_85A7_3E0804CFDC4B__INCLUDED_)
