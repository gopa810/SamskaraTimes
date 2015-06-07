#if !defined(AFX_DLGSELECTLANGOUTPUT_H__EA42E4CA_6AAF_4F91_A007_B48B1521AAC4__INCLUDED_)
#define AFX_DLGSELECTLANGOUTPUT_H__EA42E4CA_6AAF_4F91_A007_B48B1521AAC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSelectLangOutput.h : header file
//
#include "LangFileInfo.h"

/////////////////////////////////////////////////////////////////////////////
// DlgSelectLangOutput dialog

class DlgSelectLangOutput : public CDialog
{
// Construction
public:
	TLangFileInfo * m_pfi;
	DlgSelectLangOutput(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgSelectLangOutput)
	enum { IDD = IDD_SELECT_LANG };
	CListBox	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgSelectLangOutput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgSelectLangOutput)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSELECTLANGOUTPUT_H__EA42E4CA_6AAF_4F91_A007_B48B1521AAC4__INCLUDED_)
