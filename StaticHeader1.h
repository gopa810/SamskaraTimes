#if !defined(AFX_STATICHEADER1_H__9721AA69_370A_47AE_8856_C831F23893D9__INCLUDED_)
#define AFX_STATICHEADER1_H__9721AA69_370A_47AE_8856_C831F23893D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaticHeader1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStaticHeader1 window

class CStaticHeader1 : public CStatic
{
// Construction
public:
	CStaticHeader1();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticHeader1)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_bInitialized;
	CFont m_myFont;
	void InitMyFont();
	virtual ~CStaticHeader1();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStaticHeader1)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICHEADER1_H__9721AA69_370A_47AE_8856_C831F23893D9__INCLUDED_)
