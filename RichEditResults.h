#if !defined(AFX_RICHEDITRESULTS_H__7C474566_FF42_496D_BC17_8A5BECE9208A__INCLUDED_)
#define AFX_RICHEDITRESULTS_H__7C474566_FF42_496D_BC17_8A5BECE9208A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RichEditResults.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRichEditResults window
class CFrameMain;

class CRichEditResults : public CRichEditCtrl
{
// Construction
public:
	CRichEditResults();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRichEditResults)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_bShift;
	BOOL m_bCtrl;
	TString * m_pReadString;
	CFrameMain * Getparent();
	int m_nCookie;
	int SetTextRtf(TString * str);
	virtual ~CRichEditResults();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRichEditResults)
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RICHEDITRESULTS_H__7C474566_FF42_496D_BC17_8A5BECE9208A__INCLUDED_)
