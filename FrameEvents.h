// FrameEvents.h: interface for the CFrameEvents class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FRAMEEVENTS_H__F72719C7_8CAC_41B2_B689_6C9679CC5CFB__INCLUDED_)
#define AFX_FRAMEEVENTS_H__F72719C7_8CAC_41B2_B689_6C9679CC5CFB__INCLUDED_

// #include "EventsHtmlView.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FrameBase.h"

class CFrameEvents : public CFrameBase  
{
public:
	void UpdateItemsFasting();
	int dontUpdate;
	void UpdateItemsCheckStatus();
	void FillListView();
	CFont m_fontMenu;
	NONCLIENTMETRICS _ncm;
	CComboBox m_wndMasa;
	CComboBox m_wndClass;
	CListCtrl m_wndList;
//	CEventsHtmlView * p_webView;
	CTabCtrl m_wndTab;
	CStatic m_wndClassTitle;
	CStatic m_wndMasaTitle;
	int b_class[11];
	int b_masa[13];
	CFrameEvents();
	virtual ~CFrameEvents();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrameEvents)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CFrameEvents)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEventsClose();
	afx_msg void OnEventsDeleteevent();
	afx_msg void OnEventsEditevent();
	afx_msg void OnEventsNewevent();
	afx_msg void OnUpdateEventsEditevent(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEventsDeleteevent(CCmdUI* pCmdUI);
	afx_msg void OnFileSave();
	afx_msg void OnHelpHelp();
	afx_msg void OnUpdateHelpHelp(CCmdUI* pCmdUI);
	afx_msg void OnHelpHelptopicthiswindow();
	afx_msg void OnUpdateHelpHelptopicthiswindow(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_FRAMEEVENTS_H__F72719C7_8CAC_41B2_B689_6C9679CC5CFB__INCLUDED_)
