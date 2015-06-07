#if !defined(AFX_STATICHEADER3_H__92F450E8_3C62_4BD0_92E0_AB2E84C2D58E__INCLUDED_)
#define AFX_STATICHEADER3_H__92F450E8_3C62_4BD0_92E0_AB2E84C2D58E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaticHeader3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStaticHeader3 window

class CStaticHeader3 : public CStatic
{
// Construction
public:
	CStaticHeader3();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticHeader3)
	//}}AFX_VIRTUAL

// Implementation
public:
	void InitMyFont();
	BOOL m_bThisControlInit;
	static BOOL m_myFontInit;
	static CFont m_myFont;
	virtual ~CStaticHeader3();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStaticHeader3)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICHEADER3_H__92F450E8_3C62_4BD0_92E0_AB2E84C2D58E__INCLUDED_)
