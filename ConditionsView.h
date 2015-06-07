#if !defined(AFX_CONDITIONSVIEW_H__032E7957_2082_42B6_87A9_5809344B906A__INCLUDED_)
#define AFX_CONDITIONSVIEW_H__032E7957_2082_42B6_87A9_5809344B906A__INCLUDED_

#include "level_0.h"	// Added by ClassView
#include "LocationRef.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConditionsView.h : header file
//

#define MAX_CONDS 3

/////////////////////////////////////////////////////////////////////////////
// CConditionsView window

class CConditionsView : public CWnd
{
// Construction
public:
	CConditionsView();
	class EventClass
	{
	public:
		int nClass;
		const char * pszTitle;
	};
	static EventClass m_eventClassList[];

// Attributes
public:
	NONCLIENTMETRICS ncm;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConditionsView)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	Boolean m_bMethodAnd;
	int GetCountYear();
	int GetStartYear();
	int m_dst;
	CLocationRef m_earth;
	CFont m_infoFont;
	CEdit m_edits[3];
	CButton m_buttons[3];
	CStatic m_wnd_texts[5];
	int m_evClass[MAX_CONDS];
	int m_evValue[MAX_CONDS];
	TString m_evString[MAX_CONDS];

	CFont m_comboFont;
	int NaplnComboBox(CComboBox * pc, int nClass);
	CComboBox m_c[MAX_CONDS][2];
	int GetProperHeight();
	virtual ~CConditionsView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CConditionsView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONDITIONSVIEW_H__032E7957_2082_42B6_87A9_5809344B906A__INCLUDED_)
