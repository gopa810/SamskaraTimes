#if !defined(AFX_FRAMEFIND_H__AFF47B05_CDEE_4019_ABDF_82F1D892F251__INCLUDED_)
#define AFX_FRAMEFIND_H__AFF47B05_CDEE_4019_ABDF_82F1D892F251__INCLUDED_

#include "ConditionsView.h"	// Added by ClassView
#include "framebase.h"
#include "level_5_days.h"	// Added by ClassView
#include "editclipboarded.h"
#include "listboxclipboarded.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FrameFind.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFrameFind frame

class CFrameFind : public CFrameBase
{
//	DECLARE_DYNCREATE(CFrameFind)
protected:

// Attributes
public:

// Operations
public:
//	CFont m_fontPrintHdr;
//	CFont m_fontPrintText;
//	CRect m_rectPrintMargins;
	int CopyDataToString(TString &str);
	int CopyDataToClipboard();
	BOOL m_bKeyShift;
	BOOL m_bKeyCtrl;
	DWORD m_dwPrevDate;
	TResultCalendar m_calendar;
	CTabCtrl m_wndTab;
	CListBoxClipboarded m_wndList;
	CEditClipboarded    m_wndCalend;
	CConditionsView m_viewCond;
	CFrameFind();           // protected constructor used by dynamic creation
	virtual ~CFrameFind();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrameFind)
	public:
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CDialogBar m_wndLocator;
	CDialogBar m_wndControl;

	// Generated message map functions
	//{{AFX_MSG(CFrameFind)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnEventFind();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLocationSetlocation();
	afx_msg void OnEditCopy();
	afx_msg void OnFileExit();
	afx_msg void OnFilePrint();
	afx_msg void OnDestroy();
	afx_msg void OnFileSave();
	afx_msg void OnHelpHelp();
	afx_msg void OnUpdateHelpHelp(CCmdUI* pCmdUI);
	afx_msg void OnHelpHelptopicthiswindow();
	afx_msg void OnUpdateHelpHelptopicthiswindow(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAMEFIND_H__AFF47B05_CDEE_4019_ABDF_82F1D892F251__INCLUDED_)
