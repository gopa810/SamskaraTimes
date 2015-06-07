#if !defined(AFX_FRAMEMAIN_H__D9D99ACD_46D1_4C68_A42B_89612F1088D3__INCLUDED_)
#define AFX_FRAMEMAIN_H__D9D99ACD_46D1_4C68_A42B_89612F1088D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FrameMain.h : header file
//
#include "level_0.h"
//#include "texteditwnd.h"
#include "level_5_days.h"	// Added by ClassView
#include "framebase.h"
#include "LocationRef.h"
#include "TResultEvent.h"
#include "TResultApp.h"
#include "TResultMasaList.h"	// Added by ClassView
#include "RichEditResults.h"
#include "TString.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CFrameMain frame

class CFrameMain : public CFrameBase
{
//	DECLARE_DYNCREATE(CFrameMain)
public:
	CFrameMain();           // protected constructor used by dynamic creation

	class f__1
	{
		EARTHDATA earth;
		VCTIME dateStart;
		int nDaysCount;
		int nCls[3];
		int nVal[3];
		TString strVal[3];
	}
	findata;

	class n__2
	{
	public:
		CLocationRef m_loc;
		VATIME va_start;
		VATIME va_end;
		VCTIME vc_start;
		VCTIME vc_end;
		UInt32 fOptions;
	}
	naks;

	VATIME tithi;

// Attributes
public:

// Operations
public:
	void OnSpecialCommand();
	void RetrieveCurrentScreenInRtf(TString &str);
	void RetrieveCurrentScreenInText(TString &str);
	TString m_strTxt;
//	void AddNoteRtf(TString &str);
	void RecalculateTodayScreen();
	TResultMasaList m_masalist;
	VCTIME m_eventDayE;
	VCTIME m_eventDayA;
	BOOL m_bJumpToFinalStep;
	TString m_strXml;
	int PrintNaksatras(CDC &dc, EARTHDATA earth, int m_masa, int  m_year, int m_stop_masa, CRect &rcPrint);
	TResultCalendar m_calendar;
	TResultEvents   m_events;
	TResultApp      m_appday;
	BOOL m_bKeyShift;
	void RecalculateCurrentScreen();
	void AddNote1(TString &str);
	BOOL m_bKeyControl;
	UINT m_nInfoType;
	void SetInfoText(const char * pszText, UINT nType);
	CStatic m_Info;
	HICON m_hIcon;
	CEdit m_textTXT;
	CRichEditResults m_textRTF;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrameMain)
	//}}AFX_VIRTUAL

// Implementation
	virtual ~CFrameMain();

	// Generated message map functions
	//{{AFX_MSG(CFrameMain)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCalculateCalendar();
	afx_msg void OnCalculateSamskara();
	afx_msg void OnCalculateAppearanceday();
	afx_msg void OnCalculateMasalisting();
	afx_msg void OnCalculateEvents();
	afx_msg void OnExportEvents();
	afx_msg void OnExportLocationslist();
	afx_msg void OnHelpAbout();
	afx_msg void OnToolsFindMhd();
	afx_msg void OnEditCopy();
	afx_msg void OnEditClearselection();
	afx_msg void OnEditSelectall();
	afx_msg void OnToolsNewwindow();
	afx_msg void OnClose();
	afx_msg void OnWindowClose();
	afx_msg void OnFileExit();
	afx_msg void OnCalculateToday();
	afx_msg void OnCalculatePreviousday();
	afx_msg void OnCalculateNextday();
	afx_msg void OnSettingsMylocation();
	afx_msg void OnSettingsCalendarlist();
	afx_msg void OnUpdateCalculatePreviousday(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCalculateNextday(CCmdUI* pCmdUI);
	afx_msg void OnSettingsLanguageOutput();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSettingsLocations();
	afx_msg void OnFileSave();
	afx_msg void OnSettingsAyanamsavalue();
	afx_msg void OnSettingsMyevents();
	afx_msg void OnFilePrint1();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnFileStringmanager();
	afx_msg void OnSettingsTextview();
	afx_msg void OnUpdateSettingsTextview(CCmdUI* pCmdUI);
	afx_msg void OnSettingsRichtextview();
	afx_msg void OnUpdateSettingsRichtextview(CCmdUI* pCmdUI);
	afx_msg void OnSettingsTextsize10();
	afx_msg void OnUpdateSettingsTextsize10(CCmdUI* pCmdUI);
	afx_msg void OnSettingsTextsize11();
	afx_msg void OnUpdateSettingsTextsize11(CCmdUI* pCmdUI);
	afx_msg void OnSettingsTextsize12();
	afx_msg void OnUpdateSettingsTextsize12(CCmdUI* pCmdUI);
	afx_msg void OnSettingsTextsize13();
	afx_msg void OnUpdateSettingsTextsize13(CCmdUI* pCmdUI);
	afx_msg void OnSettingsTextsize14();
	afx_msg void OnUpdateSettingsTextsize14(CCmdUI* pCmdUI);
	afx_msg void OnHelpShowstartuptips();
	afx_msg void OnHelpOfflinehelp();
	afx_msg void OnUpdateHelpOfflinehelp(CCmdUI* pCmdUI);
	afx_msg void OnHelpHelptopicquickguide();
	afx_msg void OnUpdateHelpHelptopicquickguide(CCmdUI* pCmdUI);
	afx_msg void OnHelpHelptopicthiswindow();
	afx_msg void OnUpdateHelpHelptopicthiswindow(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAMEMAIN_H__D9D99ACD_46D1_4C68_A42B_89612F1088D3__INCLUDED_)
