// FrameLocs.h: interface for the CFrameLocs class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FRAMELOCS_H__926915CD_B003_4FD1_9C23_090C817DA439__INCLUDED_)
#define AFX_FRAMELOCS_H__926915CD_B003_4FD1_9C23_090C817DA439__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FrameBase.h"
#include "Location.h"
#include "LocsTabCtrl.h"
#include <afxhtml.h>
#include "MyWebView.h"

class CFrameLocs : public CFrameBase  
{
public:
	void ShowControlsForTab(int nTab);
	unsigned short int GetCountrySelected();
	void AddLocationStr(CLocation *L);
	void InitCityByCountry(int nCode);
	void SetCountrySelected(int nCode);
	void InitCountries();
	CFont m_fontMnu;
	//CListBox m_wndList;
	CListCtrl m_wndLocs;
//	CListCtrl m_wndCtrs;
	//CLocsTabCtrl m_wndTab;
	CComboBox m_wndCountry;
	CButton m_wndBtn[16];
	CEdit m_wndSearch;
	//CMyWebView * p_wndWeb;
	CFrameLocs();
	virtual ~CFrameLocs();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrameLocs)
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

protected:
	// Generated message map functions
	//{{AFX_MSG(CFrameLocs)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnLocationCreatelocation();
	afx_msg void OnUpdateLocationCreatelocation(CCmdUI* pCmdUI);
	afx_msg void OnLocationDeletelocation();
	afx_msg void OnUpdateLocationDeletelocation(CCmdUI* pCmdUI);
	afx_msg void OnLocationEditlocation();
	afx_msg void OnUpdateLocationEditlocation(CCmdUI* pCmdUI);
	afx_msg void OnListImport();
	afx_msg void OnUpdateListImport(CCmdUI* pCmdUI);
	afx_msg void OnListReset();
	afx_msg void OnGoogleShowlocation();
	afx_msg void OnFileExportlist();
	afx_msg void OnFileClosewindow();
	afx_msg void OnUpdateGoogleShowlocation(CCmdUI* pCmdUI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCountryAddcountry();
	afx_msg void OnCountryRenamecountry();
	afx_msg void OnHelpHelp();
	afx_msg void OnUpdateHelpHelp(CCmdUI* pCmdUI);
	afx_msg void OnHelpHelptopicthiswindow();
	afx_msg void OnUpdateHelpHelptopicthiswindow(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#endif // !defined(AFX_FRAMELOCS_H__926915CD_B003_4FD1_9C23_090C817DA439__INCLUDED_)
