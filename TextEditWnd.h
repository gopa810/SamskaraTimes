#if !defined(AFX_TEXTEDITWND_H__F014D2AE_3DE6_4A3D_AFEC_62826D5E4D3A__INCLUDED_)
#define AFX_TEXTEDITWND_H__F014D2AE_3DE6_4A3D_AFEC_62826D5E4D3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextEditWnd.h : header file
//

class CFrameMain;

/////////////////////////////////////////////////////////////////////////////
// CTextEditWnd window

class CTextEditWnd : public CEdit
{
// Construction
public:
	CTextEditWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextEditWnd)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_bKeyShift;
	CFrameMain * GetMyParent(void);
	BOOL m_bKeyControl;
	virtual ~CTextEditWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTextEditWnd)
	afx_msg void OnEditClearselection();
	afx_msg void OnEditCopy();
	afx_msg void OnEditSelectall();
	afx_msg void OnCalculateAppearanceday();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTEDITWND_H__F014D2AE_3DE6_4A3D_AFEC_62826D5E4D3A__INCLUDED_)
