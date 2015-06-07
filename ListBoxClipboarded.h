#if !defined(AFX_LISTBOXCLIPBOARDED_H__048071B6_79C8_4445_929B_18802F299DB8__INCLUDED_)
#define AFX_LISTBOXCLIPBOARDED_H__048071B6_79C8_4445_929B_18802F299DB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListBoxClipboarded.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListBoxClipboarded window

class CListBoxClipboarded : public CListBox
{
// Construction
public:
	CListBoxClipboarded();

// Attributes
public:
	BOOL m_bKeyCtrl;
	BOOL m_bKeyShift;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListBoxClipboarded)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListBoxClipboarded();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListBoxClipboarded)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTBOXCLIPBOARDED_H__048071B6_79C8_4445_929B_18802F299DB8__INCLUDED_)
