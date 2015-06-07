#if !defined(AFX_EDITCLIPBOARDED_H__2937601E_F26B_4FF0_AFA4_3866C78B837B__INCLUDED_)
#define AFX_EDITCLIPBOARDED_H__2937601E_F26B_4FF0_AFA4_3866C78B837B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditClipboarded.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditClipboarded window

class CEditClipboarded : public CEdit
{
// Construction
public:
	CEditClipboarded();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditClipboarded)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_bKeyCtrl;
	BOOL m_bKeyShift;
	virtual ~CEditClipboarded();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditClipboarded)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCLIPBOARDED_H__2937601E_F26B_4FF0_AFA4_3866C78B837B__INCLUDED_)
