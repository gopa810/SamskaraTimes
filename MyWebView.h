#if !defined(AFX_MYWEBVIEW_H__C634D0A1_B633_4C81_8E31_1753B5CF7A0B__INCLUDED_)
#define AFX_MYWEBVIEW_H__C634D0A1_B633_4C81_8E31_1753B5CF7A0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyWebView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyWebView html view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxhtml.h>

class CMyWebView : public CHtmlView
{
public:
	CMyWebView();           // protected constructor used by dynamic creation
protected:
	DECLARE_DYNCREATE(CMyWebView)

// html Data
public:
	//{{AFX_DATA(CMyWebView)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyWebView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnNavigateComplete2( LPCTSTR strURL );
	virtual void OnDownloadComplete( );
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyWebView();
protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMyWebView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYWEBVIEW_H__C634D0A1_B633_4C81_8E31_1753B5CF7A0B__INCLUDED_)
