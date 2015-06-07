// VCal5beta.h : main header file for the VCAL5BETA application
//

#if !defined(AFX_VCAL5BETA_H__4EB2C87E_15E1_473C_99CC_85E0D2F92D67__INCLUDED_)
#define AFX_VCAL5BETA_H__4EB2C87E_15E1_473C_99CC_85E0D2F92D67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

//#include "afxtempl.h"
#include "resource.h"		// main symbols
#include "platform.h"

/////////////////////////////////////////////////////////////////////////////
// GCalApp:
// See VCal5beta.cpp for the implementation of this class
//
class CCommandLineVCal;

class GCalApp : public CWinApp
{
public:
	BOOL m_bHelpAvailable;
	int ParseCommandArguments(CCommandLineVCal *);
	BOOL GetLangFileForAcr(const char * pszAcr, TString &strFile);
	BOOL InitLanguageOutputFromFile(const char * pszFile);
//	CList <CLangFileInfo *, CLangFileInfo *> m_langs;
//	TString m_strLangFile;
	BOOL m_bWindowless;
	DWORD GetDWordFromString(const char * psz);
	void InitInstanceData();
	GCalApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GCalApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(GCalApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ShowTipAtStartup(void);
private:
	void ShowTipOfTheDay(void);
};

void GCalShowHelp(LPCTSTR pszFile);

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCAL5BETA_H__4EB2C87E_15E1_473C_99CC_85E0D2F92D67__INCLUDED_)
