#if !defined(AFX_DLGSETPRINTSTYLE_H__E788F005_AB15_41C8_B567_A99780F576DC__INCLUDED_)
#define AFX_DLGSETPRINTSTYLE_H__E788F005_AB15_41C8_B567_A99780F576DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSetPrintStyle.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgSetPrintStyle dialog

class DlgSetPrintStyle : public CDialog
{
// Construction
public:
	CRect m_margins;
	int m_nHeaderSize;
	int m_nFontSize;
	TString m_strFont;
	int m_nStyle;
	DlgSetPrintStyle(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgSetPrintStyle)
	enum { IDD = IDD_PRINT_STYLE };
	CEdit	m_wndBottom;
	CEdit	m_wndRight;
	CEdit	m_wndLeft;
	CEdit	m_wndTop;
	CEdit	m_wndFontName;
	CComboBox	m_cbSizeHdr;
	CComboBox	m_cbSizeText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgSetPrintStyle)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgSetPrintStyle)
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSelectFont();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETPRINTSTYLE_H__E788F005_AB15_41C8_B567_A99780F576DC__INCLUDED_)
