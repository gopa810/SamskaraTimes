// FrameMain.cpp : implementation file
//

#include "stdafx.h"
#include "vcal5beta.h"
#include "FrameMain.h"
#include "level_0.h"
#include "level_5_days.h"
#include "vedic_ui.h"
#include "strings.h"
#include "TFile.h"
#include "dlgselectlangoutput.h"
//#include <C:\Program Files (x86)\HTML Help Workshop\include\htmlhelp.h>
#include "DlgGetLocation.h"
#include "DlgGetLocationEx.h"
#include "DlgGetDate.h"
//#include "DlgGetTime.h"
//#include "DlgDateRange.h"
#include "DlgGetEndDate.h"
#include "DlgGetEventSpec.h"
#include "DlgStringManager.h"
#include "DlgSelectSamskara.h"
//#include "dlgobservedevents.h"
#include "TithiCalc.h"
//#include "SankrantiDlg.h"
#include "dlgmasalisting.h"
#include "location.h"
#include "frameserver.h"
#include "level_6.h"
#include "locationref.h"
#include "dlgcustomeventdialog.h"
#include "tipdlg.h"
#include "GCStrings.h"
#include "GCTithi.h"
#include "GCNaksatra.h"
#include "GCDisplaySettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int AvcGetNextLine(TString &, TString &, int &);
int AvcGetTextLineCount(VAISNAVADAY * pvd);
int WriteCalendarXml(TResultCalendar &daybuff, FILE * fout);
void WriteAppDayHTML(TResultApp &app, FILE *F);
int WriteCalendarHtmlTable(TResultCalendar &daybuff, FILE * fout);
int WriteCalendarHTML(TResultCalendar &daybuff, FILE * fout);
int WriteEventsHTML(TResultEvents &inEvents, FILE * f);
int WriteMasaListHTML(TResultMasaList &mlist, FILE * f);
int CalcCalendar(TResultCalendar &calendar, EARTHDATA earth, VCTIME date, int nDaysCount);
int FormatCalendarOld(TResultCalendar &, TString &);
int FormatCalendarICAL(TResultCalendar &calendar, TString &str);
int FormatCalendarVCAL(TResultCalendar &calendar, TString &str);
void FormatAppDayXML(TResultApp &, TString &);
int FormatMasaListText(TResultMasaList &mlist, TString &str);
int FormatMasaListRtf(TResultMasaList &mlist, TString &str);
void time_print(TString &, DAYTIME);
int AvcGetTextLineCount(VAISNAVADAY * pvd);
void AppendRtfHeader(TString &);
void AddNoteText(TString &str);

extern GCalApp theApp;
extern CLocationRef gMyLocation;
extern CLocationRef gLastLocation;
extern VCTIME gTodayAct;
extern VCTIME gToday;
extern VCTIME gTomorrow;
extern VCTIME gYesterday;
extern const char * gpszSeparator;
extern int g_ShowMode;
extern int g_NoteSize;
extern int g_TextSize;
extern int g_HeaderSize;
extern int g_Header2Size;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonLink();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_BUTTON_LINK, OnButtonLink)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




/////////////////////////////////////////////////////////////////////////////
// CFrameMain

//IMPLEMENT_DYNCREATE(CFrameMain, CFrameWnd)

CFrameMain::CFrameMain()
{
	m_bKeyControl = FALSE;
	m_rectPrintMargins.SetRect(15,15,15,15);
	m_bJumpToFinalStep = FALSE;
	naks.fOptions = 0xffff;
//	m_pHtmText = NULL;
}

CFrameMain::~CFrameMain()
{
}


BEGIN_MESSAGE_MAP(CFrameMain, CFrameWnd)
	//{{AFX_MSG_MAP(CFrameMain)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_CALCULATE_CALENDAR, OnCalculateCalendar)
	ON_COMMAND(ID_CALCULATE_VIVAHASAMSKARA, OnCalculateSamskara)
	ON_COMMAND(ID_CALCULATE_APPEARANCEDAY, OnCalculateAppearanceday)
	ON_COMMAND(ID_CALCULATE_MASALISTING, OnCalculateMasalisting)
	ON_COMMAND(ID_CALCULATE_EVENTS, OnCalculateEvents)
	ON_COMMAND(ID_EXPORT_EVENTS, OnExportEvents)
	ON_COMMAND(ID_EXPORT_LOCATIONSLIST, OnExportLocationslist)
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	ON_COMMAND(ID_FIND_MHD, OnToolsFindMhd)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEARSELECTION, OnEditClearselection)
	ON_COMMAND(ID_EDIT_SELECTALL, OnEditSelectall)
	ON_COMMAND(ID_TOOLS_NEWWINDOW, OnToolsNewwindow)
	ON_WM_CLOSE()
	ON_COMMAND(ID_WINDOW_CLOSE, OnWindowClose)
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	ON_COMMAND(ID_CALCULATE_TODAY, OnCalculateToday)
	ON_COMMAND(ID_CALCULATE_PREVIOUSDAY, OnCalculatePreviousday)
	ON_COMMAND(ID_CALCULATE_NEXTDAY, OnCalculateNextday)
	ON_COMMAND(ID_SETTINGS_MYLOCATION, OnSettingsMylocation)
	ON_COMMAND(ID_SETTINGS_CALENDARLIST, OnSettingsCalendarlist)
	ON_UPDATE_COMMAND_UI(ID_CALCULATE_PREVIOUSDAY, OnUpdateCalculatePreviousday)
	ON_UPDATE_COMMAND_UI(ID_CALCULATE_NEXTDAY, OnUpdateCalculateNextday)
	ON_COMMAND(ID_SETTINGS_LANGUAGE_OUTPUT, OnSettingsLanguageOutput)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_COMMAND(ID_SETTINGS_LOCATIONS, OnSettingsLocations)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_SETTINGS_AYANAMSAVALUE, OnSettingsAyanamsavalue)
	ON_COMMAND(ID_SETTINGS_MYEVENTS, OnSettingsMyevents)
	ON_COMMAND(ID_FILE_PRINT1, OnFilePrint1)
	ON_WM_SETFOCUS()
	ON_WM_SIZING()
	ON_WM_MOVE()
	ON_COMMAND(ID_FILE_STRINGMANAGER, OnFileStringmanager)
	ON_COMMAND(ID_SETTINGS_TEXTVIEW, OnSettingsTextview)
	ON_UPDATE_COMMAND_UI(ID_SETTINGS_TEXTVIEW, OnUpdateSettingsTextview)
	ON_COMMAND(ID_SETTINGS_RICHTEXTVIEW, OnSettingsRichtextview)
	ON_UPDATE_COMMAND_UI(ID_SETTINGS_RICHTEXTVIEW, OnUpdateSettingsRichtextview)
	ON_COMMAND(ID_SETTINGS_TEXTSIZE10, OnSettingsTextsize10)
	ON_UPDATE_COMMAND_UI(ID_SETTINGS_TEXTSIZE10, OnUpdateSettingsTextsize10)
	ON_COMMAND(ID_SETTINGS_TEXTSIZE11, OnSettingsTextsize11)
	ON_UPDATE_COMMAND_UI(ID_SETTINGS_TEXTSIZE11, OnUpdateSettingsTextsize11)
	ON_COMMAND(ID_SETTINGS_TEXTSIZE12, OnSettingsTextsize12)
	ON_UPDATE_COMMAND_UI(ID_SETTINGS_TEXTSIZE12, OnUpdateSettingsTextsize12)
	ON_COMMAND(ID_SETTINGS_TEXTSIZE13, OnSettingsTextsize13)
	ON_UPDATE_COMMAND_UI(ID_SETTINGS_TEXTSIZE13, OnUpdateSettingsTextsize13)
	ON_COMMAND(ID_SETTINGS_TEXTSIZE14, OnSettingsTextsize14)
	ON_UPDATE_COMMAND_UI(ID_SETTINGS_TEXTSIZE14, OnUpdateSettingsTextsize14)
	ON_COMMAND(ID_HELP_SHOWSTARTUPTIPS, OnHelpShowstartuptips)
	ON_COMMAND(ID_HELP_OFFLINEHELP, OnHelpOfflinehelp)
	ON_UPDATE_COMMAND_UI(ID_HELP_OFFLINEHELP, OnUpdateHelpOfflinehelp)
	ON_COMMAND(ID_HELP_HELPTOPICQUICKGUIDE, OnHelpHelptopicquickguide)
	ON_UPDATE_COMMAND_UI(ID_HELP_HELPTOPICQUICKGUIDE, OnUpdateHelpHelptopicquickguide)
	ON_COMMAND(ID_HELP_HELPTOPICTHISWINDOW, OnHelpHelptopicthiswindow)
	ON_UPDATE_COMMAND_UI(ID_HELP_HELPTOPICTHISWINDOW, OnUpdateHelpHelptopicthiswindow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


////////////////////////////////////////////////////////
void CalcAppDay(CLocationRef &location, VCTIME event, TResultApp &);
void FormatAppDayText(TResultApp & app, TString &strResult);
void FormatAppDayRtf(TResultApp & app, TString &strResult);

#define MW_MODE_CAL      1
#define MW_MODE_EVENTS   2
#define MW_MODE_MASALIST 3
#define MW_MODE_APPDAY   6
#define MW_MODE_TODAY    7


void GCalShowHelp(LPCTSTR pszFile)
{
	CString str;

	str.Format("gcal.chm::/%s", pszFile);

	HtmlHelp(NULL, str, HH_DISPLAY_TOPIC, 0);
}

/////////////////////////////////////////////////////////////////////////////
// CFrameMain message handlers

int CFrameMain::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameBase::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_textTXT.Create(WS_CHILD | (g_ShowMode==0?WS_VISIBLE:0) | ES_MULTILINE | WS_VSCROLL | ES_AUTOVSCROLL | WS_HSCROLL | ES_AUTOHSCROLL
		, CRect(0,0,0,0), this, 101);
	m_textRTF.Create(WS_CHILD | (g_ShowMode==1?WS_VISIBLE:0) | ES_MULTILINE | WS_VSCROLL | ES_AUTOVSCROLL | WS_HSCROLL | ES_AUTOHSCROLL
		, CRect(0,0,0,0), this, 101);

	m_Info.Create(GCStrings::getString(43).c_str(), WS_CHILD | WS_BORDER | (g_ShowMode==0?WS_VISIBLE:0), CRect(0,0,0,0), this, 102);

	m_hIcon = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	m_textTXT.SetFont( &m_fontList );
	m_textRTF.SetFont( &m_fontList );

	m_Info.SetFont( &m_fontInfo, TRUE);

	// ziskava info o dnesku
	OnCalculateToday();

	return 0;
}

void CFrameMain::OnSize(UINT nType, int cx, int cy)
{
	CFrameBase::OnSize(nType, cx, cy);
	
	m_Info.MoveWindow(0, 0, cx, 38);
	m_textTXT.MoveWindow(0, 38, cx, cy - 38);
	m_textRTF.MoveWindow(0, 0, cx, cy);
}


void CFrameMain::OnCalculateCalendar() 
{
//	EARTHDATA earth;
//	TString location_info;
	TString text;
	TString rtf;
	
	DlgGetLocation d1(GCStrings::getString(44));
	DlgGetStartDate dstart;
	DlgGetEndDate   dend;

	if (m_bJumpToFinalStep == TRUE)
	{
		m_bJumpToFinalStep = FALSE;
		goto _step_final;
	}

_step_1:
	if (d1.DoModal() == IDCANCEL) return;
	if (d1.m_nNextStep < 0) return;
	earth = d1.m_location;

_step_2:
	dstart.m_earth = (EARTHDATA)earth;
	if (dstart.DoModal() == IDCANCEL) return;
	if (dstart.m_nNextStep < 0) goto _step_1;
	calendar.vc_start = dstart.m_resultC;
	calendar.va_start = dstart.m_resultA;

_step_final:
	dend.bFinal = TRUE;
	dend.m_earth  = (EARTHDATA)earth;
	dend.va_start = calendar.va_start;
	dend.vc_start = calendar.vc_start;

	if (dend.DoModal() == IDCANCEL) return;
	if (dend.m_nNextStep < 0) goto _step_2;

	calendar.vc_end = dend.vc_end;
	calendar.va_end   = dend.va_end;
	calendar.count = int(dend.vc_end.GetJulian() - dend.vc_start.GetJulian());

	CalcCalendar(m_calendar, earth, calendar.vc_start, calendar.count);

	if (g_ShowMode == 0)
	{
		FormatCalendarOld(m_calendar, text);
		AddNote1(text);
		m_textTXT.SetWindowText(text);
		m_strTxt = text;
	}
	else
	{
		FormatCalendarRtf(m_calendar, rtf);
		m_textRTF.LimitText(384000);
		m_textRTF.SetTextRtf(&rtf);
	}

	SetInfoText(GCStrings::getString(44), MW_MODE_CAL);
}

////////////////////////////////////////////////////////
void CFrameMain::OnCalculateAppearanceday() 
{
	DlgGetLocation d1(GCStrings::getString(45));
	DlgGetDate d2;
	TString str;
	VCTIME event;

	if (m_bJumpToFinalStep == TRUE)
	{
		m_bJumpToFinalStep = FALSE;
		goto _step_final;
	}

_step_1:
	d1.DoModal();
	if (d1.m_nNextStep < 1)
	{
		return;
	}
	earth = d1.m_location;

_step_final:
	d2.s_event.tzone = earth.m_fTimezone;
	d2.DoModal();
	if (d2.m_nNextStep == -1) goto _step_1;
	else if (d2.m_nNextStep == 0) return;

	event.day = d2.m_nDay;
	event.month = d2.m_nMonth;
	event.year = d2.m_nYear;
	event.shour = double(d2.m_nHour * 60 + d2.m_nMin) / 1440.0;
	event.tzone = earth.m_fTimezone;

	CalcAppDay(earth, event, m_appday);
	
	FormatAppDayXML(m_appday, m_strXml);

	if (g_ShowMode == 0)
	{
		FormatAppDayText(m_appday, str);
		AddNote1(str);
		m_textTXT.SetWindowText( str );
		m_strTxt = str;
	}
	else
	{
		FormatAppDayRtf(m_appday, str);
		m_textRTF.SetWindowText( str );
	}

	SetInfoText(GCStrings::getString(45).c_str(), MW_MODE_APPDAY);
	
}

void CFrameMain::OnCalculateEvents() 
{
	DlgGetLocation  dloc(GCStrings::getString(46));
	DlgGetStartDate dstart;
	DlgGetEndDate   dend;
	DlgGetEventSpec dspec;

	TString str;

	if (m_bJumpToFinalStep == TRUE)
	{
		m_bJumpToFinalStep = FALSE;
		goto _step_final;
	}

_step_1:
	dloc.DoModal();
	if (dloc.m_nNextStep < 1) return;
	naks.m_loc = dloc.m_location;

_step_2:
	dstart.m_earth = (EARTHDATA)naks.m_loc;
	if (dstart.DoModal() == IDCANCEL) return;
	if (dstart.m_nNextStep < 0) goto _step_1;
	naks.va_start = dstart.m_resultA;
	naks.vc_start = dstart.m_resultC;

_step_3:
	dend.m_earth = (EARTHDATA)naks.m_loc;
	dend.va_start = naks.va_start;
	dend.vc_start = naks.vc_start;
	if (dend.DoModal() == IDCANCEL) return;
	if (dend.m_nNextStep < 0) goto _step_2;
	naks.va_end = dend.va_end;
	naks.vc_end = dend.vc_end;

_step_final:
	dspec.m_fOptions = naks.fOptions;
	if (dspec.DoModal() == IDCANCEL) return;
	if (dspec.m_nNextStep < 0) goto _step_3;
	naks.fOptions = dspec.m_fOptions;

	if (g_ShowMode == 0)
	{
		m_textTXT.SetWindowText("\r\n\r\n        Calculation in progress....");
		m_textTXT.UpdateWindow();
	}
	else
	{
		str = "";
		AppendRtfHeader(str);
		str += "\\par\\par\\qc\\fs30\\cf30\\b Calculation in progress....";
		m_textRTF.SetTextRtf(&str);
		m_textRTF.UpdateWindow();
	}

	CalcEvents(m_events, naks.m_loc, naks.vc_start, naks.vc_end);

	if (g_ShowMode == 0)
	{
		FormatEventsText(m_events, str);
		AddNote1(str);
		m_textTXT.SetWindowText( str );
		m_strTxt = str;
	}
	else
	{
		FormatEventsRtf(m_events, str);
		m_textRTF.LimitText(384000);
		m_textRTF.SetWindowText( str );
	}

	FormatEventsXML(m_events, m_strXml);

	SetInfoText(GCStrings::getString(46), MW_MODE_EVENTS);
}

void CFrameMain::OnCalculateSamskara() 
{
	DlgGetLocation  dloc(GCStrings::getString(46));
	DlgGetStartDate dstart;
	DlgGetEndDate   dend;
	DlgSelectSamskara dspec;

	TString str;

	if (m_bJumpToFinalStep == TRUE)
	{
		m_bJumpToFinalStep = FALSE;
		goto _step_final;
	}

_step_1:
	dloc.DoModal();
	if (dloc.m_nNextStep < 1) return;
	naks.m_loc = dloc.m_location;

_step_2:
	dstart.m_earth = (EARTHDATA)naks.m_loc;
	if (dstart.DoModal() == IDCANCEL) return;
	if (dstart.m_nNextStep < 0) goto _step_1;
	naks.va_start = dstart.m_resultA;
	naks.vc_start = dstart.m_resultC;

_step_3:
	dend.m_earth = (EARTHDATA)naks.m_loc;
	dend.va_start = naks.va_start;
	dend.vc_start = naks.vc_start;
	if (dend.DoModal() == IDCANCEL) return;
	if (dend.m_nNextStep < 0) goto _step_2;
	naks.va_end = dend.va_end;
	naks.vc_end = dend.vc_end;

_step_final:
	if (dspec.DoModal() == IDCANCEL) return;
	if (dspec.m_nNextStep < 0) goto _step_3;

	if (g_ShowMode == 0)
	{
		m_textTXT.SetWindowText("\r\n\r\n        Calculation in progress....");
		m_textTXT.UpdateWindow();
	}
	else
	{
		str = "";
		AppendRtfHeader(str);
		str += "\\par\\par\\qc\\fs30\\cf30\\b Calculation in progress....";
		m_textRTF.SetTextRtf(&str);
		m_textRTF.UpdateWindow();
	}

	CalcSamskaras(m_events, naks.m_loc, naks.vc_start, naks.vc_end);

	if (g_ShowMode == 0)
	{
		FormatEventsText(m_events, str);
		AddNote1(str);
		m_textTXT.SetWindowText( str );
		m_strTxt = str;
	}
	else
	{
		FormatEventsRtf(m_events, str);
		m_textRTF.LimitText(384000);
		m_textRTF.SetWindowText( str );
	}

	FormatEventsXML(m_events, m_strXml);

	SetInfoText(GCStrings::getString(46), MW_MODE_EVENTS);
}

/*void CFrameMain::OnCalculateSankrantis() 
{
	DlgGetLocation d1(GCStrings::getString(47], &m_fontInfo);
	DlgSankranti dlg;
	EARTHDATA earth;
	SYSTEMTIME st;
	GetLocalTime(&st);
	static int s_init = 0; 
	static int s_year = 0;


	if (m_bJumpToFinalStep == TRUE)
	{
		m_bJumpToFinalStep = FALSE;
		goto _step_final;
	}


_step_1:
	d1.DoModal();
	if (d1.m_nNextStep < 1)
	{
		return;
	}

	this->earth = d1.m_location;
	earth = (EARTHDATA)(this->earth);

_step_final:
	dlg.earth = this->earth;
	if (s_init == 0)
	{
		dlg.m_year = st.wYear;
		s_init = 1;
	}
	else
	{
		dlg.m_year = s_year;
	}

	dlg.bFinal = TRUE;
	dlg.DoModal();
	if (dlg.m_nNextStep == -1)
		goto _step_1;
	else if (dlg.m_nNextStep == 0)
		return;

	s_year = dlg.m_year;
	m_strXml = dlg.m_strXmlResult;

	AddNote1(dlg.m_strResult);
	m_text.SetWindowText( dlg.m_strResult );

	SetInfoText(GCStrings::getString(47], MW_MODE_SANK);
}
*/
void CFrameMain::OnCalculateMasalisting() 
{
	DlgMasaListing dlg;
	DlgGetLocation d1(GCStrings::getString(48));
	SYSTEMTIME st;
	GetLocalTime(&st);

	d1.m_location = gLastLocation;
	if (m_bJumpToFinalStep == TRUE)
	{
		m_bJumpToFinalStep = FALSE;
		goto _step_final;
	}

_step_1:
	d1.DoModal();
	if (d1.m_nNextStep < 1)
	{
		return;
	}
	earth = d1.m_location;

_step_final:
	dlg.m_loc = d1.m_location;
	dlg.bFinal = TRUE;
	dlg.m_pMasaList = &m_masalist;
	dlg.DoModal();
	if (dlg.m_nNextStep == -1) goto _step_1;
	else if (dlg.m_nNextStep == 0) return;

	if (g_ShowMode == 0)
	{
		AddNote1(dlg.m_strResult);
		m_textTXT.SetWindowText( dlg.m_strResult );
		m_strTxt = dlg.m_strResult;
	}
	else
	{
		m_textRTF.SetWindowText( dlg.m_strResult );
	}
	SetInfoText(GCStrings::getString(48), MW_MODE_MASALIST);
}

void CFrameMain::OnExportEvents() 
{
	theFrameServer.CreateNewEventsFrame();
}

void CFrameMain::OnExportLocationslist() 
{
	CFileDialog cfd(FALSE, "xml", NULL, OFN_OVERWRITEPROMPT, "XML file (*.xml)|*.xml|Text file (*.txt)|*.txt|Locations List (*.lox)|*.lox|");

	if (cfd.DoModal() != IDOK)
		return;

	// 0 = TXT, 1 = XML
	theLocs.SaveAs( cfd.GetPathName(), cfd.m_ofn.nFilterIndex);	
}

void CFrameMain::OnHelpAbout() 
{
	CAboutDlg aboutDlg;
	
	aboutDlg.DoModal();
	
}

void CFrameMain::OnToolsFindMhd() 
{
	theFrameServer.CreateNewFindFrame();
	return;
}

void CFrameMain::OnEditCopy() 
{
	if (g_ShowMode == 0)
	{
		m_textTXT.SetFocus();
		m_textTXT.Copy();
	}
	else
	{
		m_textRTF.SetFocus();
		m_textRTF.Copy();
	}
}

void CFrameMain::OnEditClearselection() 
{
	if (g_ShowMode == 0)
	{
		m_textTXT.SetFocus();
		m_textTXT.SetSel(-1, -1);
	}
	else
	{
		m_textRTF.SetFocus();
		m_textRTF.SetSel(-1, -1);	
	}
}

void CFrameMain::OnEditSelectall() 
{
	if (g_ShowMode == 0)
	{
		m_textTXT.SetFocus();
		m_textTXT.SetSel(0, -1);
	}
	else
	{
		m_textRTF.SetFocus();
		m_textRTF.SetSel(0, -1);
	}
}

void CFrameMain::OnToolsNewwindow() 
{
	CFrameMain * newFrame = theFrameServer.CreateNewFrame();
	
	if (newFrame == NULL)
	{
		AfxMessageBox(GCStrings::getString(50), MB_OK | MB_ICONSTOP);
	}
}

void CFrameMain::OnClose() 
{
	GetWindowRect(theFrameServer.m_rectMain);

	theFrameServer.ChangeMainWindow(this);

	CFrameWnd::OnClose();

	theFrameServer.OnClose(this);
}

void CFrameMain::OnWindowClose() 
{
	CloseWindow();	
}

void CFrameMain::OnFileExit() 
{
	//theFrameServer.LockServer();
	
	//theFrameServer.CloseAllWindows();

	//PostQuitMessage(0);
	OnClose();
}

void CFrameMain::SetInfoText(LPCTSTR pszText, UINT nType)
{
	TString str;

	str = pszText;

	str.Replace("&", "&&");
	m_Info.SetWindowText( str);

	m_nInfoType = nType;
}

void CFrameMain::OnCalculateToday() 
{
	TString str, info;

	SYSTEMTIME st;
	GetLocalTime(&st);
	gTodayAct.day = st.wDay;
	gTodayAct.month = st.wMonth;
	gTodayAct.year = st.wYear;
	gTodayAct.shour = 0.5;
	gTodayAct.tzone = gMyLocation.m_fTimezone;
	gToday = gTodayAct;
	gTomorrow = gToday;
	gTomorrow.NextDay();
	gYesterday = gToday;
	gYesterday.PreviousDay();

	if (g_ShowMode == 1)
	{
		FormatTodayInfoRtf(gTodayAct, gMyLocation, str);
		m_nInfoType = MW_MODE_TODAY;
		m_textRTF.SetWindowText(str);
	}
	else
	{
		AvcGetTodayInfo(gTodayAct, gMyLocation, str);
		VCTIME::GetDateTextWithTodayExt(info, gTodayAct);
		SetInfoText(info, MW_MODE_TODAY);
		m_textTXT.SetWindowText(str);
		m_strTxt = str;
	}

	
}

void CFrameMain::OnCalculatePreviousday() 
{
	TString str;
	if (m_nInfoType == MW_MODE_TODAY)
	{
		TString info;
		gTodayAct.PreviousDay();
		gTodayAct.tzone = gMyLocation.m_fTimezone;

		if (g_ShowMode == 1)
		{
			FormatTodayInfoRtf(gTodayAct, gMyLocation, str);
			m_nInfoType = MW_MODE_TODAY;
			m_textRTF.SetWindowText(str);
		}
		else
		{
			AvcGetTodayInfo(gTodayAct, gMyLocation, str);
			VCTIME::GetDateTextWithTodayExt(info, gTodayAct);
			info.Insert(0, " ");
			SetInfoText(info, MW_MODE_TODAY);
			m_textTXT.SetWindowText(str);
			m_strTxt = str;
		}
	}


	
}

void CFrameMain::OnCalculateNextday() 
{
	TString str, info;
	if (m_nInfoType == MW_MODE_TODAY)
	{
		gTodayAct.NextDay();
		gTodayAct.tzone = gMyLocation.m_fTimezone;

		if (g_ShowMode == 1)
		{
			FormatTodayInfoRtf(gTodayAct, gMyLocation, str);
			m_nInfoType = MW_MODE_TODAY;
			m_textRTF.SetWindowText(str);
		}
		else
		{
			AvcGetTodayInfo(gTodayAct, gMyLocation, str);
			VCTIME::GetDateTextWithTodayExt(info, gTodayAct);
			info.Insert(0, " ");
			SetInfoText(info, MW_MODE_TODAY);
			m_textTXT.SetWindowText(str);
			m_strTxt = str;
		}
	}
}

void CFrameMain::OnSettingsMylocation() 
{
	DlgGetLocation d1("Set My Location");
	d1.m_bMyLocation = TRUE;
	d1.m_bFinal = TRUE;
	d1.DoModal();

	if (d1.m_nNextStep == 1)
	{
		gMyLocation = d1.m_location;
		if (m_nInfoType == 7)
			OnCalculateToday();
	}

}

#include "DPageGeneral.h"
#include "DPageFest.h"
#include "DPageAstroVedic.h"
#include "DPageAstro.h"

#include "DlgCalcProgress.h"
#include "GCDisplaySettings.h"

void CFrameMain::OnSettingsCalendarlist() 
{
	CPropertySheet sheet("Calendar Display Settings", this);

	DPageGeneral page_gen;
	DPageFest page_fest;
	DPageToday page_av;
	DPageAstro page_a;

	sheet.AddPage(&page_fest);
	sheet.AddPage(&page_a);
	sheet.AddPage(&page_gen);
	sheet.AddPage(&page_av);

	sheet.DoModal();

	TString text;

	if (GCDisplaySettings::getCountChanged() > 0)
	{
		RecalculateCurrentScreen();
	}
	theFrameServer.UpdateAllEventFrames();
}

void CFrameMain::OnUpdateCalculatePreviousday(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_nInfoType == 7 || m_nInfoType == 2);	
}

void CFrameMain::OnUpdateCalculateNextday(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( m_nInfoType == 7 || m_nInfoType == 2);	
	
}

void CFrameMain::OnSettingsLanguageOutput() 
{
	TString strFile;
	TFile sdf;
	DlgSelectLangOutput d;

	if (d.DoModal() == IDOK)
	{
		if (d.m_pfi == NULL)
		{
			InitGlobalStrings(0);
//			theApp.m_strLangFile.Empty();
			AfxMessageBox("Language for Output set succesfully to default (English).", MB_OK);
			RecalculateCurrentScreen();
		}
		else
		{
			if (theApp.InitLanguageOutputFromFile( d.m_pfi->m_strFile ) == FALSE)
			{
				AfxMessageBox("Error opening file with Language for Output.", MB_OK | MB_ICONSTOP);
			}
			else
			{
//				AfxMessageBox("Language for Output set succesfully.", MB_OK);
				RecalculateCurrentScreen();
			}
		}
	}
}

int AvcOneStepBack(CFrameMain * pFrame)
{
	pFrame->m_bJumpToFinalStep = TRUE;
	switch(pFrame->m_nInfoType)
	{
	case 1:
		pFrame->OnCalculateCalendar();
		break;
	case 2:
		pFrame->OnCalculateEvents();
		break;
	case 3:
		pFrame->OnCalculateMasalisting();
		break;
	case 6:
		pFrame->OnCalculateAppearanceday();
		break;
	default:
		break;
	}

	return pFrame->m_nInfoType;
}

void CFrameMain::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar)
	{
	case VK_CONTROL:
		m_bKeyControl = TRUE;
		break;
	case VK_SHIFT:
		m_bKeyShift = TRUE;
		break;
	case VK_F11:
		if (m_bKeyShift && m_bKeyControl)
		{
			OnSettingsAyanamsavalue();
		}
		break;
	case VK_F9:
		OnCalculateAppearanceday();
		break;
	case VK_BACK:
		if (m_bKeyControl == TRUE)
		{
			AvcOneStepBack(this);
		}
		break;
	case 'E':
		if (m_bKeyControl == TRUE)
			OnCalculateEvents();
		break;
	case 'M':
		if (m_bKeyControl == TRUE)
			OnCalculateMasalisting();
		break;
	case 'F':
		if (m_bKeyControl == TRUE)
			OnToolsFindMhd();
		break;
	case VK_F5:
		// prev tithi
		OnCalculatePreviousday();
		break;
	case VK_F6:
		OnCalculateToday();
		break;
	case VK_F7:
		// calculate next day
		OnCalculateNextday();
		break;
	case VK_F8:
		if (m_bKeyShift && m_bKeyControl)
		{
			OnSpecialCommand();
		}
		else
		{
			OnCalculateCalendar();
		}
		break;
	case 'A':
		if (m_bKeyControl == TRUE)
			OnEditSelectall();
		break;
	case 'C':
		if (m_bKeyControl == TRUE)
			OnEditCopy();
		break;
	default:
		break;
	}

	CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CFrameMain::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar)
	{
	case VK_CONTROL:
		m_bKeyControl = FALSE;
		break;
	case VK_SHIFT:
		m_bKeyShift = FALSE;
		break;
	default:
		break;
	}
	
	CFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CFrameMain::OnSettingsLocations() 
{
	theFrameServer.CreateNewLocationFrame();

	//DlgGetLocationEx dex;
	//dex.DoModal();
}


void CFrameMain::OnFileSave() 
{
	static char BASED_CODE * szFilter;
	char * szFileName;

	switch (m_nInfoType)
	{
	case 1:
		szFilter = "Text Files (*.txt)|*.txt|Rich Text Files (*.rtf)|*.rtf|XML Files (*.xml)|*.xml|iCalendar Files (*.ics)|*.ics|vCalendar Files (*.vcs)|*.vcs|Comma Separated Values (*.csv)|*.csv|HTML File (in Table format) (*.htm)|*.htm|HTML File (in List format) (*.htm)|*.htm||";
		szFileName = "Calendar";
		break;
	case 2:
		szFilter = "Text Files (*.txt)|*.txt|Rich Text Files (*.rtf)|*.rtf|XML Files (*.xml)|*.xml|HTML Files (*.html)|*.html||";
		szFileName = "Day_Details";
		break;
	case 3:
		szFilter = "Text Files (*.txt)|*.txt|Rich Text Files (*.rtf)|*.rtf|HTML Files (*.html)|*.html||";
		szFileName = "Masa_List";
		break;
	case 4:
		szFilter = "Text Files (*.txt)|*.txt|Rich Text Files (*.rtf)|*.rtf|XML Files (*.xml)|*.xml||";
		szFileName = "Sankranti_List";
		break;
	case 5:
		szFilter = "Text Files (*.txt)|*.txt|Rich Text Files (*.rtf)|*.rtf|XML Files (*.xml)|*.xml||";
		szFileName = "Tithi_Naksatra_List";
		break;
	case 6:
		szFilter = "Text Files (*.txt)|*.txt|Rich Text Files (*.rtf)|*.rtf|XML Files (*.xml)|*.xml|HTML Files (*.html)|*.html||";
		szFileName = "AppDay_Info";
		break;
	default:
		szFilter = "Text Files (*.txt)|*.txt|Rich Text Files (*.rtf)|*.rtf||";
		szFileName = "GCal_Result";
		break;
	}

	CFileDialog fd(FALSE, "txt", szFileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);

	if (fd.DoModal() == IDOK)
	{
		TFile std;
		CString strA;
		TString str;

		switch(fd.m_ofn.nFilterIndex)
		{
		case 1:
			if (std.Open(fd.GetPathName(), "wb") == TRUE)
			{
				//m_text.GetWindowText(strA);
				//str = m_strTxt;
				RetrieveCurrentScreenInText(str);
				//str.Replace("\r\n", "\n");
				//const char * pp = str.c_str();
/*				while(*pp)
				{
					if (*pp != '\r')
					{
						fputc(*pp, std.m_fHandle);
					}
					pp++;
				}*/
				std.WriteString(str.c_str());
				std.Close();
			}
			break;
		case 2:
			if (std.Open(fd.GetPathName(), "wb") == TRUE)
			{
				RetrieveCurrentScreenInRtf(str);
				std.WriteString(str.c_str());
				std.Close();
			}
			break;
		case 3:
			{
				switch (m_nInfoType)
				{
				case 1:
					{
						FILE * fout = fopen(fd.GetPathName(), "wt");
						if (fout != NULL)
						{
							WriteCalendarXml(m_calendar, fout);
							fclose(fout);
						}
					}
					break;
				case 3:
					if (std.Open(fd.GetPathName(), "w") == TRUE)
					{
						WriteMasaListHTML(m_masalist, std.m_fHandle);
						std.Close();
					}
					break;
				case 2:
				case 4:
				case 5:
				case 6:
					if (std.Open(fd.GetPathName(), "w") == TRUE)
					{
						std.WriteString(m_strXml);
						std.Close();
					}
					break;
				}
			}
			break;

		case 4:
			{
				switch(m_nInfoType)
				{
				case 1:
					if (std.Open(fd.GetPathName(), "w") == TRUE)
					{
						FormatCalendarICAL(m_calendar, str);
						std.WriteString(str);
						std.Close();
					}
					break;
				case 2:
					if (std.Open(fd.GetPathName(), "w") == TRUE)
					{
						WriteEventsHTML(m_events, std.m_fHandle);
						std.Close();
					}
					break;
				case 6:
					if (std.Open(fd.GetPathName(), "w") == TRUE)
					{
						WriteAppDayHTML(m_appday, std.m_fHandle);
						std.Close();
					}
					break;
				default:
					break;
				}
			}
			break;
		case 5:
			if (std.Open(fd.GetPathName(), "w") == TRUE)
			{
				FormatCalendarVCAL(m_calendar, str);
				std.WriteString(str);
				std.Close();
			}
			break;
		case 6:
			if (std.Open(fd.GetPathName(), "w") == TRUE)
			{
				FormatCalendarCSV(m_calendar, str);
				std.WriteString(str);
				std.Close();
			}
			break;
		case 7:
			if (std.Open(fd.GetPathName(), "w") == TRUE)
			{
				WriteCalendarHtmlTable(m_calendar, std.m_fHandle);
				std.Close();
			}
			break;
		case 8:
			if (std.Open(fd.GetPathName(), "w") == TRUE)
			{
				WriteCalendarHTML(m_calendar, std.m_fHandle);
				std.Close();
			}
			break;
		default:
			break;
		}
	}
}

#include "dlgsetayanamsatype.h"

void CFrameMain::OnSettingsAyanamsavalue() 
{
	// TODO: Add your command handler code here
	DlgSetAyanamsaType d;
	
	d.DoModal();
	if (MessageBox("Would you like to recalculate current screen?", "After change of settings...", MB_YESNO) == IDYES)
	{
		RecalculateCurrentScreen();
	}

}

void CFrameMain::OnSettingsMyevents() 
{

	DlgCustomEventDialog dce;

	if (dce.DoModal() == IDOK)
	{
		if (m_nInfoType == 1 || m_nInfoType == 9)
		{
			if (MessageBox("Would you like to recalculate current screen?", "After change of settings...", MB_YESNO) == IDYES)
			{
				RecalculateCurrentScreen();
			}
		}
	}

}

void CFrameMain::AddNote1(TString &str)
{
	str += "\r\n\r\n";
	str += gpszSeparator;
	str += "\r\nNotes:\r\n\r\n";
	str += "DST - Time is in \'Daylight Saving Time\'\r\nLT  - Time is in \'Local Time\'\r\n";

	if (GCDisplaySettings::getValue(9) > 0 || GCDisplaySettings::getValue(10) > 0 || GCDisplaySettings::getValue(11) > 0 || GCDisplaySettings::getValue(12) > 0)
	{
		str += "(*) - value at the moment of sunrise\r\n";
	}

	// last line
	str += "\r\nGenerated by ";
	str += GCStrings::getString(131);
}

void CFrameMain::RecalculateCurrentScreen()
{
	TString text;
	switch(m_nInfoType)
	{
	case MW_MODE_CAL:
		{
			DlgCalcProgress dcp;

			dcp.Create(IDD_CALC_PROGRESS, AfxGetMainWnd());
			dcp.CenterWindow();
			dcp.ShowWindow(SW_SHOW);
			dcp.UpdateWindow();

			m_calendar.m_pProgress = &(dcp.m_p1);
			
			if (g_ShowMode == 0)
			{
				FormatCalendarOld(m_calendar, text);
				AddNoteText(text);
				m_textTXT.SetWindowText( text );
				m_strTxt = text;
			}
			else if (g_ShowMode == 1)
			{
				FormatCalendarRtf(m_calendar, text);
				m_textRTF.SetWindowText( text );
			}
			//m_text.SetTextRtf(&text);

			m_calendar.m_pProgress = NULL;

			dcp.DestroyWindow();
		}
		//AfxCalculateCalendar(m_calendar, earth.earth, calendar.date, calendar.count, earth.dst, calendar.locinfo, text);
		//AddNote1(text);
		//m_text.SetWindowText( text );
		break;
	case MW_MODE_EVENTS:
			if (g_ShowMode == 0)
			{
				FormatEventsText(m_events, text);
				AddNoteText(text);
				m_textTXT.SetWindowText( text );
				m_strTxt = text;
			}
			else if (g_ShowMode == 1)
			{
				FormatEventsRtf(m_events, text);
				m_textRTF.SetWindowText( text );
			}
		break;
	case MW_MODE_MASALIST:
			if (g_ShowMode == 0)
			{
				FormatMasaListText(m_masalist, text);
				AddNoteText(text);
				m_textTXT.SetWindowText( text );
				m_strTxt = text;
			}
			else if (g_ShowMode == 1)
			{
				FormatMasaListRtf(m_masalist, text);
				m_textRTF.SetWindowText( text );
			}
		break;
	case MW_MODE_APPDAY:
			if (g_ShowMode == 0)
			{
				FormatAppDayText(m_appday, text);
				AddNoteText(text);
				m_textTXT.SetWindowText( text );
				m_strTxt = text;
			}
			else if (g_ShowMode == 1)
			{
				FormatAppDayRtf(m_appday, text);
				m_textRTF.SetWindowText( text );
			}
		break;
	case MW_MODE_TODAY:
		gTodayAct.NextDay();
		OnCalculatePreviousday();
		break;
	case 9://find-day
		break;
	default:
		break;
	}
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetDlgItemText(IDC_STATIC_VER, GCStrings::getString(131));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAboutDlg::OnButtonLink() 
{
	ShellExecute(NULL, "open", "http://www.krishnadays.com", NULL, NULL, SW_SHOW);
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if (pWnd->GetDlgCtrlID() == IDC_BUTTON_LINK)
	{
		if (nCtlColor == CTLCOLOR_BTN)
		{
			pDC->SetTextColor(RGB(0,0,255));
			//pDC->SetBkMode(TRANSPARENT);
		}
	}
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

#include "DlgSetPrintStyle.h"

void CFrameMain::OnFilePrint1() 
{
	int nCopies = 0;
	int nPage = 1;
	CPrintDialog pd(FALSE);
	DlgSetPrintStyle spd;
	TString str;
	CDC dc;
	CRect rcPrint;
	double resX, resY;
	
	if (pd.DoModal() != IDOK)
	{
		return;
	}


	// copies of document
	nCopies = pd.GetCopies();

	// need to obtain style of printing
	// if calendar - then two styles (text, wall calendar)
	// otherwise - one style (text)

	spd.m_margins = m_rectPrintMargins;
	if (spd.DoModal() == IDCANCEL)
		return;

	m_rectPrintMargins = spd.m_margins;
    
	DOCINFO di;
	memset( &di, 0, sizeof(DOCINFO) );
    di.cbSize = sizeof(DOCINFO);
	switch(m_nInfoType)
	{
	case 1:
	    di.lpszDocName = "GCal Calendar"; 
		break;
	case 2:
	    di.lpszDocName = "GCal Tithi Info"; 
		break;
	case 3:
	    di.lpszDocName = "GCal Masa List"; 
		break;
	case 4:
	    di.lpszDocName = "GCal Sankranti List"; 
		break;
	case 5:
	    di.lpszDocName = "GCal Naksatra List"; 
		break;
	case 6:
	    di.lpszDocName = "GCal Appearance Day"; 
		break;
	case 7:
	    di.lpszDocName = "GCal Today Info"; 
		break;
	case 9:
		di.lpszDocName = "GCal Find Results";
		break;
	default:
	    di.lpszDocName = "GCal PrintOut"; 
		break;
	}
    di.lpszOutput = (LPTSTR)NULL; 
    //di.lpszDataType = (LPTSTR)NULL; 
    di.fwType = 0; 

	dc.Attach(pd.m_pd.hDC);

	// user wants to print
	LPDEVMODE lpDevMode = pd.GetDevMode();

	resX = dc.GetDeviceCaps(LOGPIXELSX) / 25.4;
	resY = dc.GetDeviceCaps(LOGPIXELSY) / 25.4;

	int offX, offY;

	offX = int(lpDevMode->dmPaperWidth - dc.GetDeviceCaps(HORZSIZE)*10.0) / 2;
	offY  = int(lpDevMode->dmPaperLength  - dc.GetDeviceCaps(VERTSIZE)*10.0) / 2;

	rcPrint.left = int((m_rectPrintMargins.left - offX/10.0) * resX);
	rcPrint.right = int((lpDevMode->dmPaperWidth/10.0 - m_rectPrintMargins.right - m_rectPrintMargins.left)*resX + rcPrint.left);
	rcPrint.top = int((m_rectPrintMargins.top - offY/10.0) * resY);
	rcPrint.bottom = int((lpDevMode->dmPaperLength/10.0 - m_rectPrintMargins.bottom - m_rectPrintMargins.top)*resY + rcPrint.top);

	m_fontPrintText.CreateFont(dc.GetDeviceCaps(LOGPIXELSX) / 72 * spd.m_nFontSize, 
		0,0,0,0,0,0, 0,0,0,0,0,0, spd.m_strFont);
	m_fontPrintHdr.CreateFont(dc.GetDeviceCaps(LOGPIXELSY) / 72 * spd.m_nHeaderSize, 
		0,0,0,0,0,0, 0,0,0,0,0,0, spd.m_strFont);

	TString strTitle;
	TString strText;

	switch (m_nInfoType)
	{
	case 1:
		{
			//     kontext: pd.m_pd.hDC
			// tlacit text: special generovanie;
			//    s nazvom: nazov masy;
			//    lokacia:  location.location
			//     strana:  nPage

			dc.StartDoc(&di);
			AfxPrintCalendarText(dc, m_calendar, earth, calendar.vc_start, calendar.count, rcPrint);
			dc.EndDoc();

		}
		break;
/*	case 5:
		{
			dc.StartDoc(&di);
			PrintNaksatras(dc, naks.m_loc, naks.dateA.masa, naks.dateA.gyear, naks.stop_masa, rcPrint);
			dc.EndDoc();
		}
		break;*/
	default:
		{
			//
			//     kontext: pd.m_pd.hDC
			// tlacit text: m_text.GetWindowText();
			//    s nazvom: m_Info.GetWindowText();
			//    lokacia:  location.location
			//     strana:  nPage
			//
			CString str;
			m_Info.GetWindowText(str);
			strTitle = str;
			//m_text.GetWindowText(str);
			RetrieveCurrentScreenInText(strText);
			//strText = m_strTxt;

			dc.StartDoc(&di);
			PrintBlockText(dc, strTitle, strText, nPage, rcPrint);
			dc.EndDoc();

		}
		break;
	}

	dc.Detach();

	m_fontPrintHdr.DeleteObject();
	m_fontPrintText.DeleteObject();
}

int CFrameMain::PrintNaksatras(CDC &dc, EARTHDATA earth, int m_masa, int m_year, int m_stop_masa, CRect &rcPrint)
{
	VCTIME d, dn, dstop, dtit;
	int mas, nak, gy, count, tith, i;
	TString str[6], strPage;
	CString S;
	DAYDATA day;
	SUNDATA sun;
	bool bStart = true;
	bool bStarted = false;
	bool bFirst = true;
	int nPage = 1;
	int nColumn[5];
	int xSpace;
	CSize sz;
	int yCurr = rcPrint.top;
	int yLine = 0, yCurrTithi, yCurrNaks;
	int maxNaks = 0, maxTithi = 0, maxDate = 0;
	CPen penGray;

	int res = dc.GetDeviceCaps(LOGPIXELSX);

	nColumn[0] = int(res * 1.5);
	nColumn[1] = int(res * 1.75);
	nColumn[2] = int(res * 2.5);
	nColumn[3] = int(res * 3.8);
	nColumn[4] = int(res * 5.45);

	mas = (m_masa == 12) ? 12 : ((m_masa + 11) % 12);
	
	CPoint midPoint;

	penGray.CreatePen(PS_SOLID, 0, RGB(180,180,180));

	for(i = 0 ; i < 30; i++)
	{
		str[0] = GCStrings::GetTithiName(i);
		S = str[0].c_str();
		sz = dc.GetTextExtent(S);
		if (sz.cx > maxTithi)
			maxTithi = sz.cx;
	}

	for(i = 0 ; i < 27; i++)
	{
		str[0] = GCStrings::GetNaksatraName(i);
		S = str[0].c_str();
		sz = dc.GetTextExtent(S);
		if (sz.cx > maxNaks)
			maxNaks = sz.cx;
	}

	sz = dc.GetTextExtent(" ", 1);
	xSpace = sz.cx;
	maxNaks = int(0.9 * res);
	maxTithi = int(0.78 * res);

	sz = dc.GetTextExtent("88 Mmm 2008 ", 12);
	maxDate = sz.cx;

/*	nColumn[0] = rcPrint.left + maxDate - xSpace;

	sz = dc.GetTextExtent("MM  ", 3);
	nColumn[1] = nColumn[0] + sz.cx;
	sz = dc.GetTextExtent("88:88:88 ", 9);
	nColumn[2] = nColumn[1] + sz.cx;
	sz = dc.GetTextExtent("Purusottama-adhika ", 19);
	nColumn[3] = nColumn[2] + sz.cx;
	sz = dc.GetTextExtent("88:88:88 ", 9);
	nColumn[4] = nColumn[3] + sz.cx + maxTithi + xSpace;
*/
	midPoint = rcPrint.CenterPoint();
	d = DAYDATA::GetFirstDayOfMasa(earth, m_year, mas);
	d.InitWeekDay();
	d.PreviousDay();
	if (m_stop_masa == 0)
		dstop = DAYDATA::GetFirstDayOfMasa(earth, m_year + 1, mas);
	else
		dstop = DAYDATA::GetFirstDayOfMasa(earth, m_year, (mas + 1) % 12);
	count = int (dstop.GetJulian() - d.GetJulian());

	TString strTitle;

	strTitle = GCStrings::getString(46);

	dn = d;
	dn.PreviousDay();
	nak = 0;

	dtit = d;
	dtit.PreviousDay();
	tith = 0;
	
	for(i = 0; i < count; i++)
	{

		if (bStart == true)
		{
			if (bStarted == true)
				dc.EndPage();

			bStarted = true;
			dc.StartPage();

			yCurr = rcPrint.top;
			dc.SelectObject(&m_fontPrintHdr);

			// titul
			S = strTitle;
			sz = dc.GetTextExtent(S);
			dc.TextOut( midPoint.x - sz.cx / 2, yCurr, S);
			yCurr += sz.cy;

			dc.SelectObject(&m_fontPrintText);

			// pozn o programe verzii
			S = GCStrings::getString(130);
			sz = dc.GetTextExtent(S);
			dc.TextOut(rcPrint.right - sz.cx, yCurr - sz.cy - 5, S);

			// cislo strany
			strPage.Format("%s %d", GCStrings::getString(162).c_str(), nPage);
			nPage++;
			S = strPage;
			sz = dc.GetTextExtent(S);
			dc.TextOut(rcPrint.right - sz.cx, yCurr + 10, S);

			// ciara
			dc.MoveTo( rcPrint.left, yCurr);
			dc.LineTo( rcPrint.right, yCurr);
			yCurr += 10;

			// lokacia
			S = this->earth.m_strName;
			sz = dc.GetTextExtent(S);
			dc.TextOut( midPoint.x - sz.cx / 2, yCurr, S);
			yCurr += 3 * sz.cy;

			S = GCStrings::getString(157);
			dc.TextOut(nColumn[0] - 4*xSpace, yCurr, S);
			S = GCStrings::getString(158);
			dc.TextOut(nColumn[1], yCurr, S);
			S = GCStrings::getString(159);
			dc.TextOut(nColumn[2], yCurr, S);
			S = GCStrings::getString(160);
			dc.TextOut(nColumn[3], yCurr, S);
			S = GCStrings::getString(161);
			dc.TextOut(nColumn[4], yCurr, S);

			yLine = sz.cy * 6 / 5;
			yCurr += yLine;
			dc.MoveTo( rcPrint.left, yCurr);
			dc.LineTo( rcPrint.right, yCurr);
			yCurr += yLine / 2;

	
			bStart = false;
			bFirst = true;
		}

		// sunrise time get
		sun.SunCalc(d, earth);
		//sun.rise.hour += dst;
		time_print(str[4], sun.rise);
		S = str[4];
		dc.TextOut(nColumn[1], yCurr, S);

		day.DayCalc(d, earth);
		d.InitWeekDay();
		str[5] = GCStrings::GetMasaName(day.MasaCalc(d, earth));
		gy = day.nGaurabdaYear;
		S = str[5];
		dc.TextOut(nColumn[2], yCurr, S);

		str[2].Format("%d %s %d", d.day, GCStrings::GetMonthAbreviation(d.month), d.year);
		S = str[2];
		sz = dc.GetTextExtent(S);
		dc.TextOut(nColumn[0] - sz.cx - 2*xSpace, yCurr, S);

		S = GCStrings::getString(d.dayOfWeek + 150);
		dc.TextOut(nColumn[0] - xSpace, yCurr, S); // day of week

		yCurrNaks = yCurr;

		while(dn.GetDayInteger() <= d.GetDayInteger())
		{
			if (dn.GetDayInteger() == d.GetDayInteger())
			{
				str[3].Format("%s", GCStrings::GetNaksatraName(nak) );
				S = str[3];
				dc.TextOut(nColumn[4], yCurrNaks, S);

				str[1].Format("%02d:%02d:%02d", dn.GetHour(), dn.GetMinute(), dn.GetSecond());
				S = str[1];
				dc.TextOut(nColumn[4] + maxNaks, yCurrNaks, S);

				yCurrNaks += yLine;
			}
			dn.shour += 1.0/8.0;
			if (dn.shour >= 1.0)
			{
				dn.shour -= 1.0;
				dn.NextDay();
			}

			nak = GCNaksatra::GetNextNaksatra(earth, dn, dn);
		}

		yCurrTithi = yCurr;

		while(dtit.GetDayInteger() <= d.GetDayInteger())
		{
			if (dtit.GetDayInteger() == d.GetDayInteger())
			{
				str[3].Format("%s", GCStrings::GetTithiName(tith));
				S = str[3];
				dc.TextOut(nColumn[3], yCurrTithi, S);
				str[1].Format("%02d:%02d:%02d", dtit.GetHour(), dtit.GetMinute(), dtit.GetSecond());
				S = str[1];
				dc.TextOut(nColumn[3] + maxTithi, yCurrTithi, S);
				yCurrTithi += yLine;
			}
			dtit.shour += 1.0/8.0;
			if (dtit.shour >= 1.0)
			{
				dtit.shour -= 1.0;
				dtit.NextDay();
			}
			tith = GCTithi::GetNextTithiStart(earth, dtit, dtit);
		}

		if (bFirst == false)
		{
			CPen * pen = dc.SelectObject(&penGray);
			dc.MoveTo( rcPrint.left, yCurr);
			dc.LineTo( rcPrint.right, yCurr);
			dc.SelectObject(pen);
		}
		bFirst = false;

		yCurr += yLine;

		if (yCurr < yCurrTithi)
			yCurr = yCurrTithi;
		if (yCurr < yCurrNaks)
			yCurr = yCurrNaks;

		if (yCurr > (rcPrint.bottom - 4*yLine))
			bStart = true;
		d.NextDay();
	}

	dc.EndPage();

	return 0;
}

void CFrameMain::OnSetFocus(CWnd* pOldWnd) 
{
	CFrameWnd::OnSetFocus(pOldWnd);
	

	theApp.m_pMainWnd = this;
}

void CFrameMain::OnSizing(UINT fwSide, LPRECT pRect) 
{
	CFrameWnd::OnSizing(fwSide, pRect);
	
	// TODO: Add your message handler code here
	if (pRect->left + 256 > pRect->right)
	{
		if (fwSide == WMSZ_RIGHT || fwSide==WMSZ_TOPRIGHT || fwSide == WMSZ_BOTTOMRIGHT)
			pRect->right = pRect->left + 256;
		else
			pRect->left = pRect->right - 256;
	}

	if (pRect->top + 256 > pRect->bottom)
	{
		if (fwSide == WMSZ_BOTTOM || fwSide==WMSZ_BOTTOMRIGHT || fwSide==WMSZ_BOTTOMLEFT)
			pRect->bottom = pRect->top + 256;
		else
			pRect->top = pRect->bottom - 256;
	}
}

void CFrameMain::OnMove(int x, int y) 
{
	CFrameBase::OnMove(x, y);

}

void CFrameMain::RecalculateTodayScreen()
{
	if (m_nInfoType == MW_MODE_TODAY)
	{
		gTodayAct.NextDay();
		OnCalculatePreviousday();
	}
}

void CFrameMain::OnFileStringmanager() 
{
	DlgStringManager d;
	
	d.DoModal();
}


void CFrameMain::OnSettingsTextview() 
{
	// TODO: Add your command handler code here
	g_ShowMode = 0;
	m_Info.ShowWindow(TRUE);
	m_textTXT.ShowWindow(TRUE);
	m_textRTF.ShowWindow(FALSE);
	RecalculateCurrentScreen();	
}

void CFrameMain::OnUpdateSettingsTextview(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(g_ShowMode == 0);	
}

void CFrameMain::OnSettingsRichtextview() 
{
	// TODO: Add your command handler code here
	g_ShowMode = 1;
	m_Info.ShowWindow(FALSE);
	m_textTXT.ShowWindow(FALSE);
	m_textRTF.ShowWindow(TRUE);
	RecalculateCurrentScreen();	
}

void CFrameMain::OnUpdateSettingsRichtextview(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(g_ShowMode == 1);
}

void CFrameMain::OnSettingsTextsize10() 
{
	// TODO: Add your command handler code here
	g_NoteSize = 14;
	g_TextSize=20;
	g_HeaderSize = 30;
	g_Header2Size = 25;
	RecalculateCurrentScreen();
}

void CFrameMain::OnUpdateSettingsTextsize10(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(g_ShowMode == 1);
	pCmdUI->SetRadio(g_TextSize==20);
}

void CFrameMain::OnSettingsTextsize11() 
{
	// TODO: Add your command handler code here
	g_NoteSize = 15;
	g_TextSize=22;
	g_HeaderSize = 33;
	g_Header2Size = 28;
	RecalculateCurrentScreen();
	
}

void CFrameMain::OnUpdateSettingsTextsize11(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(g_ShowMode == 1);
	pCmdUI->SetRadio(g_TextSize==22);
	
}

void CFrameMain::OnSettingsTextsize12() 
{
	// TODO: Add your command handler code here
	g_NoteSize = 16;
	g_TextSize=24;
	g_HeaderSize = 36;
	g_Header2Size = 32;
	RecalculateCurrentScreen();
	
}

void CFrameMain::OnUpdateSettingsTextsize12(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(g_ShowMode == 1);
	pCmdUI->SetRadio(g_TextSize==24);
	
}

void CFrameMain::OnSettingsTextsize13() 
{
	// TODO: Add your command handler code here
	g_NoteSize = 17;
	g_TextSize=26;
	g_HeaderSize = 39;
	g_Header2Size = 35;
	RecalculateCurrentScreen();
	
}

void CFrameMain::OnUpdateSettingsTextsize13(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(g_ShowMode == 1);
	pCmdUI->SetRadio(g_TextSize==26);
	
}

void CFrameMain::OnSettingsTextsize14() 
{
	// TODO: Add your command handler code here
	g_NoteSize = 18;
	g_TextSize=28;
	g_HeaderSize = 42;
	g_Header2Size = 37;
	RecalculateCurrentScreen();
	
}

void CFrameMain::OnUpdateSettingsTextsize14(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(g_ShowMode == 1);
	pCmdUI->SetRadio(g_TextSize==28);
	
}

void CFrameMain::RetrieveCurrentScreenInText(TString &text)
{
	if (g_ShowMode == 0)
	{
		text = m_strTxt;
		return;
	}

	switch(m_nInfoType)
	{
	case MW_MODE_CAL:
		FormatCalendarOld(m_calendar, text);
		AddNoteText(text);
		m_strTxt = text;
		break;
	case MW_MODE_EVENTS:
		FormatEventsText(m_events, text);
		AddNoteText(text);
		m_strTxt = text;
		break;
	case MW_MODE_MASALIST:
		FormatMasaListText(m_masalist, text);
		AddNoteText(text);
		m_strTxt = text;
		break;
	case MW_MODE_APPDAY:
		FormatAppDayText(m_appday, text);
		AddNoteText(text);
		m_strTxt = text;
		break;
	case MW_MODE_TODAY:
		AvcGetTodayInfo(gTodayAct, gMyLocation, text);
		AddNoteText(text);
		m_strTxt = text;
		break;
	default:
		break;
	}
}

void CFrameMain::RetrieveCurrentScreenInRtf(TString &text)
{
	switch(m_nInfoType)
	{
	case MW_MODE_CAL:
		FormatCalendarRtf(m_calendar, text);
		break;
	case MW_MODE_EVENTS:
		FormatEventsRtf(m_events, text);
		break;
	case MW_MODE_MASALIST:
		FormatMasaListRtf(m_masalist, text);
		break;
	case MW_MODE_APPDAY:
		FormatAppDayRtf(m_appday, text);
		break;
	case MW_MODE_TODAY:
		FormatTodayInfoRtf(gTodayAct, gMyLocation, text);
		break;
	default:
		break;
	}

}

void CFrameMain::OnHelpShowstartuptips() 
{
	// TODO: Add your command handler code here
	CTipDlg dlg;
	dlg.DoModal();
}



void CFrameMain::OnHelpOfflinehelp() 
{
	// TODO: Add your command handler code here
	GCalShowHelp("index.htm");
}

void CFrameMain::OnUpdateHelpOfflinehelp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(theApp.m_bHelpAvailable);	
}

void CFrameMain::OnHelpHelptopicquickguide() 
{
	// TODO: Add your command handler code here
	GCalShowHelp("quick-main.htm");	
}

void CFrameMain::OnUpdateHelpHelptopicquickguide(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(theApp.m_bHelpAvailable);	
	
}

void CFrameMain::OnHelpHelptopicthiswindow() 
{
	// TODO: Add your command handler code here
	GCalShowHelp("ref-main.htm");
	
}

void CFrameMain::OnUpdateHelpHelptopicthiswindow(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(theApp.m_bHelpAvailable);	
	
}

#include "DlgSpecCommand.h"

void CFrameMain::OnSpecialCommand()
{
	DlgSpecCommand dlg;

	dlg.DoModal();
}
