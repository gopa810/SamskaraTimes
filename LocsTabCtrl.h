#if !defined(AFX_LOCSTABCTRL_H__541B17B9_1122_4EC2_9C69_5E78987BD9E8__INCLUDED_)
#define AFX_LOCSTABCTRL_H__541B17B9_1122_4EC2_9C69_5E78987BD9E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LocsTabCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLocsTabCtrl window

class CLocsTabCtrl : public CTabCtrl
{
// Construction
public:
	CLocsTabCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocsTabCtrl)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLocsTabCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLocsTabCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOCSTABCTRL_H__541B17B9_1122_4EC2_9C69_5E78987BD9E8__INCLUDED_)
