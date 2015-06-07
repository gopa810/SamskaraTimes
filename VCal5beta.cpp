// VCal5beta.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "platform.h"
#include "VCal5beta.h"
#include "CommandLineVCal.h"
#include "FrameMain.h"
#include "FrameServer.h"
#include "locationref.h"
#include "strings.h"
#include "TFile.h"
#include "location.h"
#include "customevent.h"
#include "dlgasklimitation.h"
#include "TTimeZone.h"
#include "avc.h"
#include "langfileinfo.h"
#include "TFileRichList.h"
#include "TCountry.h"
#include "GCStrings.h"
#include "GCCalendar.h"
#include "GCDisplaySettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void AvcShowSetWriteFile(const char *);
void InitTips(FILE * hFile);

extern int g_ShowMode;
extern int g_NoteSize;
extern int g_TextSize;
extern int g_HeaderSize;
extern int g_Header2Size;

int WriteCalendarXml(TResultCalendar &, FILE * f);

/////////////////////////////////////////////////////////////////////////////
// GCalApp

BEGIN_MESSAGE_MAP(GCalApp, CWinApp)
	ON_COMMAND(CG_IDS_TIPOFTHEDAY, ShowTipOfTheDay)
	//{{AFX_MSG_MAP(GCalApp)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GCalApp construction

GCalApp::GCalApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_bWindowless = FALSE;
	m_bHelpAvailable = FALSE;
}

int GCalApp_InitFolders();
const char * GCalApp_GetFileName(int n);

/////////////////////////////////////////////////////////////////////////////
// The one and only GCalApp object

GCalApp theApp;
CFont gFontMenu;

extern int g_dstSelMethod;
extern CLocationRef gMyLocation;
extern CLocationRef gLastLocation;
extern VCTIME gToday;
extern VCTIME gTomorrow;
extern VCTIME gYesterday;
extern TLangFileList gLangList;

void GetBetaFileDate(SYSTEMTIME &stcr)
{
	FILETIME tm_create, tm_last, tm_write;
	HANDLE hFile;
	hFile = CreateFile("gcal.del", GENERIC_READ,0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		GetFileTime(hFile, &tm_create, &tm_last, &tm_write);
		FileTimeToSystemTime(&tm_create, &stcr);
		CloseHandle(hFile);
	}
	else
	{
		GetLocalTime(&stcr);
	}
}

//#include "TFileRichList.h"

/////////////////////////////////////////////////////////////////////////////
// GCalApp initialization
//double AvcGetTimeZone(int);
//char * AvcGetTimeZoneName(int);
BOOL GCalApp::InitInstance()
{
	//AddDocTemplate(pDocTemplate);
	theFrameServer.Initialize();

	//TTimeZone::ExportDB();
/*	TFileRichList tf;

	tf.Open("C:\\test.rl", "wt");
	if (tf.m_fHandle)
	{
		for(int i=1;i<100;i++)
		{
			tf.Clear();
			tf.AddTag(i);
			tf.AddText("InLine|| Text");
			tf.AddReal(1.078);
			tf.AddInt(567);
			tf.AddText("Second \\tag");
			tf.WriteLine();
		}
		fclose(tf.m_fHandle);
	}

	FILE * tt=fopen("C:\\test.txt", "wt");
	tf.Open("c:\\test.rl", "rt");
	while(tf.ReadLine())
	{
		fprintf(tt, "Tag=%s\n  f1=%s\n  f2=%s\n  f3=%s\n  f4=%s\n\n",
			tf.GetTag(), tf.GetField(0), tf.GetField(1), tf.GetField(2), tf.GetField(3));
	}
	fclose(tt);
	return FALSE;*/
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	InitGlobalStrings(0);

	//MessageBox(NULL, getenv("QUERY_STRING"), "a", MB_OK);
	//MessageBox(NULL, getenv("Path"), "a", MB_OK);
	m_bWindowless = TRUE;

	// initialization for AppDir
	GCalApp_InitFolders();

	/*FILE * f = fopen("C:\\op.txt", "w");
	if (f)	{	double a;
		for(int i = 0; i < 40; i++)	{
			a = AvcGetTimeZone(i);
			fprintf(f, "  { 0, 0x00000000, \"%s\", %+.2fF, -90.0F, +90.0F, %.2fF, %.2fF},\n",
				AvcGetTimeZoneName(i), a, put_in_180(a*15.0-22.5), put_in_180(a*15.0+7.5));	}
		fclose(f);}*/


	SetRegistryKey(_T("GCAL"));
	
	g_ShowMode = GetProfileInt("ui", "show_mode", 1);
	g_NoteSize = GetProfileInt("ui", "note_size", 16);
	g_TextSize = GetProfileInt("ui", "text_size", 24);
	g_HeaderSize = GetProfileInt("ui", "hdr_size", 36);
	g_Header2Size = GetProfileInt("ui", "hdr2_size", 32);

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CCommandLineVCal cmdInfo;
	//ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	/*if (!ProcessShellCommand(cmdInfo))
		return FALSE;*/

	m_bWindowless = ParseCommandArguments(&cmdInfo);

	//if (cmdInfo.GetCount())
	if (m_bWindowless)
	{
		// processing arguments
		// is done in last calling ParseParam
		//TRACE1("CmdLine = %s\n", m_lpCmdLine);
	}
	else
	{
		m_bWindowless = FALSE;
		NONCLIENTMETRICS ncm;
		ncm.cbSize = sizeof(NONCLIENTMETRICS);

		SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &ncm, 0);

		gFontMenu.CreateFontIndirect(&ncm.lfMenuFont);

		// shows dialog window
/*#ifdef GCAL_BETA
		SYSTEMTIME st;
		GetLocalTime(&st);
		if (GetJulianDay( st.wYear, st.wMonth, st.wDay) >= GetJulianDay(2009, 7, 15))
		{
			DlgAskLimitation dal;

			if (dal.DoModal() == IDOK)
			{
				ShellExecute(NULL, "open", "http://www.krishnadays.com", NULL, NULL, SW_SHOW);
				return FALSE;
			}

		}
#endif*/

		InitInstanceData();

		CFrameMain * pMainFrame = theFrameServer.CreateNewFrame();

		if (pMainFrame == NULL)
			return FALSE;

		m_pMainWnd = pMainFrame;

		ShowTipAtStartup();
		
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	// CG: This line inserted by 'Tip of the Day' component.

	return TRUE;
}

void GCalApp::InitInstanceData()
{
	gMyLocation.m_fLongitude = 77.73;
	gMyLocation.m_fLatitude = 27.583;
	gMyLocation.m_fTimezone = 5.5;
	gMyLocation.m_strLatitude = "27N35";
	gMyLocation.m_strLongitude = "77E42";
	gMyLocation.m_strName = "Vrindavan, India";
	gMyLocation.m_strTimeZone = "+5:30";
	gMyLocation.m_nDST = 188;
	gLastLocation.m_fLongitude = 77.73;
	gLastLocation.m_fLatitude = 27.583;
	gLastLocation.m_fTimezone = 5.5;
	gLastLocation.m_strLatitude = "27N35";
	gLastLocation.m_strLongitude = "77E42";
	gLastLocation.m_strName = "Vrindavan, India";
	gLastLocation.m_strTimeZone = "+5:30";
	gLastLocation.m_nDST = 188;

	TString strFile;
	TFile f;
	TString str, strA, strB;
	TLangFileInfo * pl;

	/*GCAL 3.0*/
	if ( f.Open(GCalApp_GetFileName(GSTR_CONF_FILE), "r") != 0)
	{
		// nacitava
		while(f.ReadString2(strA, strB))
		{
			switch(atoi(strA.c_str()))
			{
			case 1: gMyLocation.m_fLongitude = atof(strB); break;
			case 2: gMyLocation.m_fLatitude = atof(strB); break;
			case 3: gMyLocation.m_fTimezone = atof(strB); break;
			case 4: gMyLocation.m_strLatitude = strB; break;
			case 5: gMyLocation.m_strLongitude = strB; break;
			case 6: gMyLocation.m_strName = strB; break;
			case 7: gMyLocation.m_strTimeZone = strB; break;
			case 8: gMyLocation.m_nDST = atoi(strB); 
				gMyLocation.m_strTimeZone = TTimeZone::GetTimeZoneName(gMyLocation.m_nDST);
				break;
			case 11: gLastLocation.m_fLongitude = atof(strB); break;
			case 12: gLastLocation.m_fLatitude = atof(strB); break;
			case 13: gLastLocation.m_fTimezone = atof(strB); break;
			case 14: gLastLocation.m_strLatitude = strB; break;
			case 15: gLastLocation.m_strLongitude = strB; break;
			case 16: gLastLocation.m_strName = strB; break;
			case 17: gLastLocation.m_strTimeZone = strB; break;
			case 18: gLastLocation.m_nDST = atoi(strB); 
				gLastLocation.m_strTimeZone = TTimeZone::GetTimeZoneName(gLastLocation.m_nDST);
				break;
			case 20: // meno subora s jazykom
				pl = gLangList.add();
				if (pl) pl->decode(strB.c_str());
				break;
			case 21: theFrameServer.m_rectMain.left = atoi(strB); break;
			case 22: theFrameServer.m_rectMain.top = atoi(strB); break;
			case 23: theFrameServer.m_rectMain.right = atoi(strB); break;
			case 24: theFrameServer.m_rectMain.bottom = atoi(strB); break;
			default: break;
			}
		}
		
		f.Close();
		DeleteFile(GCalApp_GetFileName(GSTR_CONF_FILE));
	}


	int tagn;
	TFileRichList rf;
	if ( rf.Open(GCalApp_GetFileName(GSTR_CONFX_FILE), "r") != 0)
	{
		// nacitava
		while(rf.ReadLine())
		{
			tagn = atoi(rf.GetTag());
			switch(tagn)
			{
			case 12701:
				gMyLocation.m_strName     = rf.GetField(0);
				gMyLocation.m_fLongitude  = atof(rf.GetField(1));
				gMyLocation.m_fLatitude   = atof(rf.GetField(2));
				gMyLocation.m_fTimezone   = atof(rf.GetField(3));
				gMyLocation.m_strLatitude = rf.GetField(2);
				gMyLocation.m_strLongitude = rf.GetField(1);
				gMyLocation.m_strTimeZone = rf.GetField(4);
				gMyLocation.m_nDST = TTimeZone::GetID(rf.GetField(4));
				break;
			case 12702:
				gLastLocation.m_strName     = rf.GetField(0);
				gLastLocation.m_fLongitude  = atof(rf.GetField(1));
				gLastLocation.m_fLatitude   = atof(rf.GetField(2));
				gLastLocation.m_fTimezone   = atof(rf.GetField(3));
				gLastLocation.m_strLatitude = rf.GetField(2);
				gLastLocation.m_strLongitude = rf.GetField(1);
				gLastLocation.m_strTimeZone = rf.GetField(4);
				gLastLocation.m_nDST = TTimeZone::GetID(rf.GetField(4));
				break;
			case 12710:
				theFrameServer.m_rectMain.left = atoi(rf.GetField(0));
				theFrameServer.m_rectMain.top = atoi(rf.GetField(1));
				theFrameServer.m_rectMain.right = atoi(rf.GetField(2));
				theFrameServer.m_rectMain.bottom = atoi(rf.GetField(3));
				break;
			case 12711:
				GCDisplaySettings::setValue(atoi(rf.GetField(0)), atoi(rf.GetField(1)));
				break;
			default:
				break;
			}
		}
		rf.Close();
	}

	////////////////////////////////////////////////////////
	//
	// strings
	//
	GCStrings::readFile(GCalApp_GetFileName(GSTR_TEXT_FILE));

	// inicializacia jazyka
//	InitLanguageOutputFromFile("d:\\work\\gcal-debug\\lang\\czech.lng");

	////////////////////////////////////////////////////////
	//
	// inicializacia countries
	//
	TCountry::InitWithFile(GCalApp_GetFileName(GSTR_COUNTRY_FILE));

	////////////////////////////////////////////////////////
	//
	// inicializacia miest a kontinentov
	//
	if (f.Open(GCalApp_GetFileName(GSTR_LOC_FILE), "r")==TRUE)
	{
		f.Close();
		theLocs.InitList(GCalApp_GetFileName(GSTR_LOC_FILE));
		::DeleteFile(GCalApp_GetFileName(GSTR_LOC_FILE));
	}
	else
	{
		theLocs.InitListX(GCalApp_GetFileName(GSTR_LOCX_FILE));
	}

	////////////////////////////////////////////////////////
	//
	// inicializacia tipov dna
	//
	if (f.Open(GCalApp_GetFileName(GSTR_TIPS_FILE), "r")==TRUE)
	{
		f.Close();
	}
	else
	{
		if (f.Open(GCalApp_GetFileName(GSTR_TIPS_FILE), "w")==TRUE)
		{
			InitTips(f.m_fHandle);
			f.Close();
		}
	}

	////////////////////////////////////////////////////////
	//
	// inicializacia zobrazovanych nastaveni
	//
	GCDisplaySettings::readFile(GCalApp_GetFileName(GSTR_SSET_FILE));


	////////////////////////////////////////////////////////
	//
	// inicializacia custom events
	//
	CustomEventListReadFile(GCalApp_GetFileName(GSTR_CE_FILE));
	CustomEventListReadFile_RL(GCalApp_GetFileName(GSTR_CEX_FILE));

	gCustomEventList.setOldStyleFast(GCDisplaySettings::getValue(42));

	if (f.Open(GCalApp_GetFileName(GSTR_HELP_FILE), "r")==TRUE)
	{
		f.Close();
		m_bHelpAvailable = TRUE;
	}
}

DWORD GCalApp::GetDWordFromString(const char * psz)
{
	return (DWORD)atoi(psz);
}

int GCalApp::ExitInstance() 
{
	TString str;
//	TLangFileInfo * p;

	WriteProfileInt("ui", "show_mode", g_ShowMode);
	WriteProfileInt("ui", "note_size", g_NoteSize);
	WriteProfileInt("ui", "text_size", g_TextSize);
	WriteProfileInt("ui", "hdr_size", g_HeaderSize);
	WriteProfileInt("ui", "hdr2_size", g_Header2Size);

	if (m_bWindowless == FALSE)
	{
		TString strFile;
		TFile f;
		
/*		if (f.Open(GCalApp_GetFileName(GSTR_CONF_FILE), "w") == FALSE)
			goto _next_file_to_save;

		f.WriteString2( 1, gMyLocation.m_fLongitude);
		f.WriteString2( 2, gMyLocation.m_fLatitude);
		f.WriteString2( 3, gMyLocation.m_fTimezone);
		f.WriteString2( 4, gMyLocation.m_strLatitude);
		f.WriteString2( 5, gMyLocation.m_strLongitude);
		f.WriteString2( 6, gMyLocation.m_strName);
		f.WriteString2( 7, gMyLocation.m_strTimeZone);
		f.WriteString2( 8, gMyLocation.m_nDST);
		f.WriteString2(11, gLastLocation.m_fLongitude);
		f.WriteString2(12, gLastLocation.m_fLatitude);
		f.WriteString2(13, gLastLocation.m_fTimezone);
		f.WriteString2(14, gLastLocation.m_strLatitude);
		f.WriteString2(15, gLastLocation.m_strLongitude);
		f.WriteString2(16, gLastLocation.m_strName);
		f.WriteString2(17, gLastLocation.m_strTimeZone);
		f.WriteString2(18, gLastLocation.m_nDST);
		for(p = gLangList.list; p != NULL; p = p->next)
		{
			p->encode(str);
			f.WriteString2(20, str);
		}
		f.WriteString2(21, theFrameServer.m_rectMain.left);
		f.WriteString2(22, theFrameServer.m_rectMain.top);
		f.WriteString2(23, theFrameServer.m_rectMain.right);
		f.WriteString2(24, theFrameServer.m_rectMain.bottom);
		f.Close();*/
		if (f.Open(GCalApp_GetFileName(GSTR_CONFX_FILE),"w")==TRUE)
		{
			str.Format("12701 %s|%f|%f|%f|%s\n", gMyLocation.m_strName.c_str(), gMyLocation.m_fLongitude, gMyLocation.m_fLatitude,
				gMyLocation.m_fTimezone, TTimeZone::GetTimeZoneName(gMyLocation.m_nDST));
			f.WriteString(str.c_str());
			str.Format("12702 %s|%f|%f|%f|%s\n", gLastLocation.m_strName.c_str(), gLastLocation.m_fLongitude, gLastLocation.m_fLatitude,
				gLastLocation.m_fTimezone, TTimeZone::GetTimeZoneName(gLastLocation.m_nDST));
			f.WriteString(str.c_str());
			str.Format("12710 %d|%d|%d|%d\n", theFrameServer.m_rectMain.left, theFrameServer.m_rectMain.top,
				theFrameServer.m_rectMain.right, theFrameServer.m_rectMain.bottom );
			f.WriteString(str.c_str());
			for(int y=0; y < GCDisplaySettings::getCount(); y++)
			{
				str.Format("12711 %d|%d\n", y, GCDisplaySettings::getValue(y));
				f.WriteString(str.c_str());
			}

			f.Close();
		}
	}

	if (theLocs.m_bModified)
	{
		theLocs.SaveAs(GCalApp_GetFileName(GSTR_LOCX_FILE),4);//GCAL 3.0
	}

	if (TCountry::_modified)
	{
		TCountry::SaveToFile(GCalApp_GetFileName(GSTR_COUNTRY_FILE));
	}

	if (gstr_Modified)
	{
		GCStrings::writeFile(GCalApp_GetFileName(GSTR_TEXT_FILE));
	}

	CustomEventListWriteFile_RL(GCalApp_GetFileName(GSTR_CEX_FILE));

	TFile f;

/*	if (f.Open("C:\\tz.cpp", "w")==TRUE)
	{
		for(int i = 0; i < TTimeZone::GetTimeZoneCount(); i++)
		{
			str.Format("{\"%s %s\", %.2fF, %2d, 0x%08x, %.2fF, %.2fF, %.2fF, %.2fF, %d}\n", 
				TTimeZone::GetTimeZoneOffsetText(TTimeZone::gzone[i].tzone),
				TTimeZone::gzone[i].name,
				TTimeZone::gzone[i].tzone,
				TTimeZone::gzone[i].bias,
				TTimeZone::gzone[i].val,
				TTimeZone::gzone[i].latA,
				TTimeZone::gzone[i].latB,
				TTimeZone::gzone[i].lonA,
				TTimeZone::gzone[i].lonB,
				i);
				//TTimeZone::gzone[i].name);
			f.WriteString(str.c_str());
		}
		f.Close();
	}*/
	/*if (f.Open(GCalApp_GetFileName(GSTR_TZ_FILE), "w")==TRUE)
	{
		for(int i = 0; i < TTimeZone::GetTimeZoneCount(); i++)
		{
			str.Format("11950 %d|%x|%s|%f|%f|%f|%f\n", TTimeZone::gzone[i].bias,
				TTimeZone::gzone[i].val, TTimeZone::gzone[i].name,
				TTimeZone::gzone[i].tzone, TTimeZone::gzone[i].latA, TTimeZone::gzone[i].latB,
				TTimeZone::gzone[i].lonA, TTimeZone::gzone[i].lonB);
			f.WriteString(str.c_str());
		}
		f.Close();
	}*/

/*	if (f.Open(GCalApp_GetFileName(GSTR_COUNTRY_FILE), "w")==TRUE)
	{
		for(int i = 0; i < TCountry::GetCountryCount(); i++)
		{
			str.Format("11960 %s|%d|%s|%d\n", TCountry::gcountries[i].pszAcr,
				TCountry::gcountries[i].code, TCountry::gcountries[i].pszName,
				TCountry::gcountries[i].continent);
			f.WriteString(str.c_str());
		}
		f.Close();
	}*/
	//AvcShowSetWriteFile(GCalApp_GetFileName(GSTR_SSET_FILE));

/*	CString tt;
	TString te;
	CString str2;
	int fn, fp;
	VAISNAVADAY vd;
	int oClass;
	int oo;

	CStdioFile ff;
	ff.Open("D:\\work\\gcal\\evx.rl", CFile::modeWrite|CFile::modeCreate);
	for(int i=200; i < 560; i++)
	{
		tt = GCStrings::getString(i).c_str();
		if (fp=0, fn = tt.Find('#', fp), fn>=0)
		{
			vd.festivals = tt;
			vd.GetHeadFestival();
			oo = 0;
			while(vd.GetNextFestival(oo, te))
			{
				oClass = vd.GetFestivalClass(te);
				str2.Format("16500 %d|%d|%d|%d|%s\n", (i-200)/30, (i-200)%30, oClass, 1, te.c_str());
				ff.WriteString(str2);
			}
		}
		else if (tt.GetLength()>0)
		{
			vd.festivals = tt;
			te = (LPCTSTR)tt;
			oClass = vd.GetFestivalClass(te);
			str2.Format("16500 %d|%d|%d|%d|%s\n", (i-200)/30, (i-200)%30, oClass, 1, te.c_str());
			ff.WriteString(str2);
		}
	}
	ff.Close();*/
	return CWinApp::ExitInstance();
}

BOOL GCalApp::InitLanguageOutputFromFile(const char * pszFile)
{
	TFile f;
	TString strA, strB;

	if (f.Open(pszFile, "r") == TRUE)
	{
		int n;

		while(f.ReadString2(strA, strB))
		{
			n = atoi(strA);
			if ((n >= 0) && (n < 800))
			{
				GCStrings::setString(n, strB);
			}
		}

		f.Close();

		return TRUE;
	}

	return FALSE;
}

BOOL GCalApp::GetLangFileForAcr(const char * pszAcr, TString &strFile)
{
	TLangFileInfo * p = gLangList.list;

	while(p)
	{
		if (p->m_strAcr.CompareNoCase(pszAcr) == 0)
		{
			strFile = p->m_strFile;
			return TRUE;
		}
		p = p->next;
	}
	return FALSE;
}

#define ISARGSEP(c) (((c) == 0) || ((c)==' '))


int WriteXML_FirstDay_Year(FILE *, CLocationRef &loc, VCTIME vc);
int WriteXML_Sankrantis(FILE *, CLocationRef &loc, VCTIME, VCTIME);
int WriteXML_Naksatra(FILE *, CLocationRef &loc, VCTIME, int);
int WriteXML_Tithi(FILE *, CLocationRef &loc, VCTIME);
int WriteXML_GaurabdaTithi(FILE * fout, CLocationRef &loc, VATIME vaStart, VATIME vaEnd);
int WriteXML_GaurabdaNextTithi(FILE * fout, CLocationRef &loc, VCTIME vcStart, VATIME vaStart);
void FormatAppDayXML(TResultApp &, TString &strResult);
void CalcAppDay(CLocationRef &, VCTIME, TResultApp &);


int GCalApp::ParseCommandArguments(CCommandLineVCal * cmd)
{
	// if no arguments, then application should open window
	if (_tcslen(m_lpCmdLine) < 1)
		return FALSE;
	
	char * arg = new char[_tcslen(m_lpCmdLine) + 1];
	if (arg == NULL)
		return FALSE;

	const char * parse = m_lpCmdLine;
	int argp = 0;
	int argc = 0;
	char * args[64];
	char stopc;
	char * pw = arg;

	while(*parse)
	{
		while(*parse != 0 && *parse==' ')
			parse++;
		if (*parse)
		{
			args[argc] = pw;
			argc++;
		}
		stopc = (*parse == '\"') ? '\"' : ' ';
		if (stopc == '\"')
			parse++;
		while(*parse != 0 && *parse != stopc)
		{
			*pw = *parse;
			pw++;
			parse++;
		}
		if (*parse)
			parse++;
		*pw = 0;
		pw++;
	}

	CLocationRef loc;
	VCTIME vcStart, vcEnd;
	VATIME vaStart, vaEnd;
	int nCount;
	int nReq;
	TString str;
	TString strFileOut;
	FILE * fout = stdout;

	loc.m_fLatitude = 0.0;
	loc.m_fLongitude = 0.0;
	loc.m_fTimezone = 0.0;
	loc.m_nDST = 0;
	loc.m_strName = "";
	vcStart.day = 0;
	vcStart.month = 0;
	vcStart.year = 0;
	vcEnd = vcStart;
	vaStart.tithi = vaStart.masa = vaStart.gyear = 0;
	vaEnd = vaStart;
	nCount = -1;

	for(int i = 0; i < argc; i++)
	{
		//TRACE2("arg %d = %s\n", i, args[i]);
		if (strcmp(args[i],"-L") == 0)
		{
			if (argc >= i+2)
			{
				loc.m_strLongitude = args[i+1];
				cmd->GetArg_EarthPos(args[i+1], loc.m_fLatitude, loc.m_fLongitude);
				//TRACE2("-L latitude=%f longitude=%f\n", loc.m_fLatitude, loc.m_fLongitude);
			}
			i++;
		}
		else if (strcmp(args[i],"-N") == 0)
		{
			if (argc >= i+2)
			{
				loc.m_strName = args[i+1];
				//TRACE1("-N name=%s\n", loc.m_strName);
			}
			i++;
		}
		else if (strcmp(args[i],"-SV") == 0)
		{
			if (argc >= i+2)
			{
				cmd->GetArg_VaisnDate(args[i+1], vaStart);
			}
			i++;
		}
		else if (strcmp(args[i],"-SG") == 0)
		{
			if (argc >= i+2)
			{
				cmd->GetArg_Date(args[i+1], vcStart);
			}
			i++;
		}
		else if (strcmp(args[i],"-ST") == 0)
		{
			if (argc >= i+2)
			{
				cmd->GetArg_Time(args[i+1], vcStart);
			}
			i++;
		}
		else if (strcmp(args[i],"-EG") == 0)
		{
			if (argc >= i+2)
			{
				cmd->GetArg_Date(args[i+1], vcEnd);
				//AfxTrace("-EG day=%d month=%d year=%d\n", vcEnd.day, vcEnd.month, vcEnd.year);
			}
			i++;
		}
		else if (strcmp(args[i],"-EV") == 0)
		{
			if (argc >= i+2)
			{
				cmd->GetArg_VaisnDate(args[i+1], vaEnd);
				//AfxTrace("-EV tithi=%d masa=%d gyear=%d\n", vaEnd.tithi, vaEnd.masa, vaEnd.gyear);
			}
			i++;
		}
		else if (strcmp(args[i],"-EC") == 0)
		{
			if (argc >= i+2)
			{
				nCount = atoi(args[i+1]);
				//AfxTrace("couint = %d\n", nCount);
			}
			i++;
		}
		else if (strcmp(args[i],"-TZ") == 0)
		{
			if (argc >= i+2)
			{
				cmd->GetArg_TimeZone(args[i+1], loc.m_fTimezone);
				//TRACE1("-TZ  timezone=%f\n", loc.m_fTimezone);
			}
			i++;
		}
		else if (strcmp(args[i],"-LNG") == 0)
		{
			if (argc >= i+2)
			{
				TString strLang;
				strLang = args[i+1];
				TString strFile;
				if (GetLangFileForAcr(strLang, strFile) == TRUE)
				{
					InitLanguageOutputFromFile(strFile);
				}
			}
			i++;
		}
		else if (strcmp(args[i],"-DST") == 0)
		{
			if (argc >= i+2)
			{
				loc.m_nDST = TTimeZone::GetID(args[i+1]);
			}
			i++;
		}
		else if (strcmp(args[i],"-O") == 0)
		{
			if (argc >= i+2)
			{
				if (fout != stdout && fout != stderr)
					fclose(fout);
				fout = fopen(args[i+1], "wt");
				//strFileOut = args[i+1];
				if (fout == NULL)
					fout = stderr;
			}
			i++;
		}
		else if (stricmp(args[i],"-R") == 0)
		{
			if (argc >= i+2)
			{
				if (stricmp(args[i + 1], "calendar") == 0)
				{
					nReq = 10;
				} else if (stricmp(args[i + 1], "appday") == 0)
				{
					nReq = 11;
				} else if (stricmp(args[i + 1], "tithi") == 0)
				{
					nReq = 12;
				} else if (stricmp(args[i + 1], "sankranti") == 0)
				{
					nReq = 13;
				} else if (stricmp(args[i + 1], "naksatra") == 0)
				{
					nReq = 14;
				} else if (stricmp(args[i + 1], "firstday") == 0)
				{
					nReq = 15;
				} else if (stricmp(args[i + 1], "gcalendar") == 0)
				{
					nReq = 16;
				} else if (stricmp(args[i + 1], "gtithi") == 0)
				{
					nReq = 17;
				} else if (stricmp(args[i + 1], "next") == 0)
				{
					nReq = 18;
				} else if (stricmp(args[i + 1], "xlan") == 0)
				{
					nReq = 50;
				}
				else if (stricmp(args[i + 1], "help") == 0)
				{
					nReq = 60;
				}
				/*else if (stricmp(args[i + 1], "") == 0)
				{
				} else if (stricmp(args[i + 1], "") == 0)
				{
				} else if (stricmp(args[i + 1], "") == 0)
				{
				} else if (stricmp(args[i + 1], "") == 0)
				{
				}*/
			}
			i++;
		}
	}

	loc.m_strFullName.Format("%s (%s %s, %s)", loc.m_strName.c_str(), loc.m_strLatitude.c_str(), 
		loc.m_strLongitude.c_str(), loc.m_strTimeZone.c_str());
	vcStart.tzone = loc.m_fTimezone;
	vcEnd.tzone = loc.m_fTimezone;
	//AfxTrace("vcStart = %d,%d,%d,...,%f\n", vcStart.day, vcStart.month, vcStart.year, vcStart.shour);

	switch(nReq)
	{
	case 10:
	case 13:
	case 14:
		if (vcStart.year == 0 && vaStart.gyear != 0)
			GCCalendar::VATIMEtoVCTIME(vaStart, vcStart, (EARTHDATA)loc);
		if (vcEnd.year == 0 && vaEnd.gyear != 0)
			GCCalendar::VATIMEtoVCTIME(vaEnd, vcEnd, (EARTHDATA)loc);		
		break;
	default:
		break;
	}

	if (vcStart.year != 0 && vcEnd.year != 0 && nCount < 0)
		nCount = int(vcEnd.GetJulian() - vcStart.GetJulian());

	if (nCount < 0)
		nCount = 30;

	TResultApp appday;
	TResultCalendar calendar;
	//AfxTrace("Count === %d\n", nCount);

	switch(nReq)
	{
	case 10:
		// -R -O -LAT -LON -SG -C [-DST -NAME]
		vcStart.NextDay();
		vcStart.PreviousDay();
		CalcCalendar(calendar, loc, vcStart, nCount);
		WriteCalendarXml(calendar, fout);
		break;
	case 11:
		// -R -O -LAT -LON -SG -ST [-NAME]
		CalcAppDay(loc, vcStart, appday);
		FormatAppDayXML(appday, str);
		fputs(str, fout);
		break;
	case 12:
		WriteXML_Tithi( fout, loc, vcStart);
		break;
	case 13:
		if (vcEnd.year == 0)
		{
			vcEnd = vcStart;
			vcEnd += nCount;
		}
		WriteXML_Sankrantis(fout, loc, vcStart, vcEnd);
		break;
	case 14:
		WriteXML_Naksatra(fout, loc, vcStart, nCount);
		break;
	case 15:
		WriteXML_FirstDay_Year(fout, loc, vcStart);
		break;
	case 16:
		vcStart = DAYDATA::GetFirstDayOfYear((EARTHDATA)loc, vcStart.year);
		vcEnd = DAYDATA::GetFirstDayOfYear((EARTHDATA)loc, vcStart.year + 1);
		nCount = int(vcEnd.GetJulian() - vcStart.GetJulian());
		CalcCalendar(calendar, loc, vcStart, nCount);
		WriteCalendarXml(calendar, fout);
		break;
	case 17:
		WriteXML_GaurabdaTithi( fout, loc, vaStart, vaEnd);
		break;
	case 18:
		WriteXML_GaurabdaNextTithi( fout, loc, vcStart, vaStart);
		break;
	case 50:
		{
			int i = 0;
			TString str;
			fputs("10000\nEnglish\n10001\nen\n", fout);
			// export obsahu do subora
			for(i = 0; i < 900; i ++)
			{
				if (!GCStrings::getString(i).IsEmpty())
				{
					str.Format("%d\n%s\n", i, GCStrings::getString(i).c_str());
					fputs(str, fout);
				}
			}
		}
		break;
	}
	// application should be windowless
	// since some parameters are present
	delete [] arg;

	return TRUE;
}

void GCalApp::ShowTipAtStartup(void)
{
	// CG: This function added by 'Tip of the Day' component.

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	if (cmdInfo.m_bShowSplash)
	{
		CTipDlg dlg;
		if (dlg.m_bStartup)
			dlg.DoModal();
	}

}

void GCalApp::ShowTipOfTheDay(void)
{
	// CG: This function added by 'Tip of the Day' component.

	CTipDlg dlg;
	dlg.DoModal();

}
