#include "stdafx.h"
#include "LocationRef.h"
#include "level_6.h"
#include "vedic_ui.h"
#include "strings.h"
#include "TTimeZone.h"
#include "TFile.h"
#include "TResultApp.h"
#include "TFileRichList.h"
#include "avc.h"
#include "GCStrings.h"
#include "GCCalendar.h"
#include "GCDisplaySettings.h"

const char * MSG_ERROR_1 = "Incorrect format for longitude. Correct examples: 35E05, 23W45";
const char * MSG_ERROR_2 = "Incorrect format for latitude. Correct examples: 45N05, 13S45";

extern VCTIME gToday;
extern VCTIME gTomorrow;
extern VCTIME gYesterday;


const char * AvcGetEarthPosFromString(const char * str, bool bNorth, double &Longitude)
{
	double l = 0.0;
	double sig = 1.0;
	double coma = 10.0;
	bool after_coma = false;
	bool is_deg = false;
	const char * pret = bNorth ? MSG_ERROR_1 : MSG_ERROR_2;
	bool was_comma = false;
	bool was_letter = false;
	bool was_digit = false;
	bool was_sign = false;
	int numsAfterComma = 0;

	const char * s = str;

	while(*s)
	{
		switch(*s)
		{
		case '0': case '1':
		case '2': case '3': case '4': case '5':
		case '6': case '7': case '8': case '9':
			was_digit = true;
			if (after_coma)
			{
				if (is_deg)
				{
					numsAfterComma++;
					if (numsAfterComma > 2)
					{
						return "Minutes are allowed only from range 0 - 59";
					}
					l += (*s - '0') * 5.0 / (coma * 3.0);
				}
				else
				{
					l += (*s - '0') / coma;
				}
				coma *= 10.0;
			}
			else
			{
				l = l*10.0 + (*s - '0');
				if (!bNorth)
				{
					if (l > 90.0)
						return "Latitude is allowed only in range 0 - 90";
				}
				else
				{
					if (l > 180.0)
						return "Longitude is allowed only in range 0 - 180";
				}
			}
			break;
		case 'n': case 'N':
			if (was_letter || was_sign || was_comma)
				return pret;

			was_letter = true;
			if (!bNorth)
			{
				after_coma = true;
				is_deg = true;
				sig = 1.0;
			}
			else
			{
				return pret;
			}
			break;
		case 's': case 'S':
			if (was_letter || was_sign || was_comma)
				return pret;
			was_letter = true;
			if (!bNorth)
			{
				after_coma = true;
				is_deg = true;
				sig = -1.0;
			}
			else
			{
				return pret;
			}
			break;
		case 'e': case 'E':
			if (was_letter || was_sign || was_comma)
				return pret;
			was_letter = true;
			if (bNorth)
			{
				after_coma = true;
				is_deg = true;
				sig = 1.0;
			}
			else
			{
				return pret;
			}
			break;
		case 'w': case 'W':
			if (was_letter || was_sign || was_comma)
				return pret;
			was_letter = true;
			if (bNorth)
			{
				after_coma = true;
				is_deg = true;
				sig = -1.0;
			}
			else
			{
				return pret;
			}
			break;
		case '-':
			if (was_letter || was_digit || was_comma)
				return pret;
			was_sign = true;
			sig = -1.0;
			break;
		case '+':
			if (was_letter || was_digit || was_comma)
				return pret;
			was_sign = true;
			sig = 1.0;
			break;
		case '.': case ',':
			if (was_letter || was_comma)
				return pret;
			was_comma = true;
			after_coma = true;
			is_deg = false;
			break;
		default:
			return pret;
		}
		s++;
	}

	Longitude = l * sig;

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// AppDay functions

void AddTextLine(TString &str, const char * pt)
{
	str += pt;
	str += "\r\n";
}

void AddTextLineRtf(TString &str, const char * pt)
{
	str += "\r\n\\par ";
	str += pt;
}

int AvcGetNextPartHash(TString &str, TString &strLine, int & i)
{
	int index = i, length;
	
	if (index >= str.GetLength())
		return 0;

	TCHAR tc;
	strLine.Empty();
	length = str.GetLength();

	while(1)
	{
		if (index >= length)
			break;

		tc = str.GetAt(index);
		if (tc == '#')
		{
			index++;
			break;
		}
		else
		{
			strLine += tc;
		}
		index++;
	}

	i = index;
	return 1;
}

int AvcGetFestivalClass(TString &str)
{
	int i, j, val;

	i = str.Find("[c");

	if (i >= 0)
	{
//		i += 2;
		if ((i + 2) < str.GetLength())
		{
			val = int(str.GetAt(i+2) - '0');
			j = str.Find("]", i);
			if (j >= str.GetLength() || j < 0)
				j = str.GetLength();
			if (j > i)
			{
				str.Delete(i, j - i + 1);
			}
			if (val < 0 || val > 6)
				return -1;
			return val;
		}
		else
			return -1;
	}
	else
	{
		return -1;
	}

}

int AvcClearStringFromTags(TString &str)
{
	int i, j, val = 0;

	i = str.Find("[");

	while (i >= 0)
	{
		if ((i + 2) < str.GetLength())
		{
			j = str.Find("]", i);
			if (j >= str.GetLength() || j < 0)
				j = str.GetLength();
			if (j > i)
			{
				str.Delete(i, j - i + 1);
				val ++;
			}
		}

		i = str.Find("[");
	}

	return val;
}

TString g_appstr[32];

int GCalApp_InitFolders()
{
	char pszBuffer[1024];
	int len, i;
	len = GetModuleFileName(AfxGetInstanceHandle(), pszBuffer, 1020);
	for(i = len-1; i > 0; i--)
	{
		if (pszBuffer[i] == '\\')
		{
			pszBuffer[i+1] = '\0';
			len = i+1;
			break;
		}
	}

	g_appstr[GSTR_APPFOLDER] = pszBuffer;

	g_appstr[GSTR_CONFOLDER] = g_appstr[GSTR_APPFOLDER];
	g_appstr[GSTR_CONFOLDER] += "config\\";
	CreateDirectory(g_appstr[GSTR_CONFOLDER], NULL);

	g_appstr[GSTR_LANFOLDER] = g_appstr[GSTR_APPFOLDER];
	g_appstr[GSTR_LANFOLDER] += "lang\\";
	CreateDirectory(g_appstr[GSTR_LANFOLDER], NULL);

	g_appstr[GSTR_TEMFOLDER] = g_appstr[GSTR_APPFOLDER];
	g_appstr[GSTR_TEMFOLDER] += "temp\\";
	CreateDirectory(g_appstr[GSTR_TEMFOLDER], NULL);

	g_appstr[GSTR_CE_FILE].Format("%scevents.cfg", g_appstr[GSTR_CONFOLDER].c_str());
	g_appstr[GSTR_CONF_FILE].Format("%scurrent.cfg", g_appstr[GSTR_CONFOLDER].c_str());
	g_appstr[GSTR_LOC_FILE].Format("%slocations.cfg", g_appstr[GSTR_CONFOLDER].c_str());
	g_appstr[GSTR_SSET_FILE].Format("%sshowset.cfg", g_appstr[GSTR_CONFOLDER].c_str());
	g_appstr[GSTR_LOCX_FILE].Format("%sloc.rl", g_appstr[GSTR_CONFOLDER].c_str());//GCAL 3.0
	g_appstr[GSTR_CEX_FILE].Format("%scev3.rl", g_appstr[GSTR_CONFOLDER].c_str());//GCAL 3.0
	g_appstr[GSTR_CONFX_FILE].Format("%sset.rl", g_appstr[GSTR_CONFOLDER].c_str());
	g_appstr[GSTR_TZ_FILE].Format("%stz.rl", g_appstr[GSTR_CONFOLDER].c_str());
	g_appstr[GSTR_COUNTRY_FILE].Format("%sctrs.rl", g_appstr[GSTR_CONFOLDER].c_str());
	g_appstr[GSTR_TEXT_FILE].Format("%sstrings.rl", g_appstr[GSTR_CONFOLDER].c_str());
	g_appstr[GSTR_TIPS_FILE].Format("%stips.txt", g_appstr[GSTR_CONFOLDER].c_str());
	g_appstr[GSTR_HELP_FILE].Format("%sgcal.chm", g_appstr[GSTR_APPFOLDER].c_str());
	return 1;
}

const char * GCalApp_GetFileName(int n)
{
	return g_appstr[n].c_str();
}



int AvcGetLocationAsText(TString &str, EARTHDATA earth)
{
	str.Format("%s: %s  %s: %s  %s: %s", 
		GCStrings::getString(10).c_str(), EARTHDATA::GetTextLatitude(earth.latitude_deg), 
		GCStrings::getString(11).c_str(), EARTHDATA::GetTextLongitude(earth.longitude_deg),
		GCStrings::getString(12).c_str(), TTimeZone::GetTimeZoneOffsetText(earth.tzone));

	return 1;
}

const char * AvcDoubleToString(double d)
{
	static TCHAR ts[128];

	sprintf(ts, "%f", d);

	return ts;
}

const char * AvcIntToString(int d)
{
	static TCHAR ts[32];

	sprintf(ts, "%d", d);

	return ts;
}

const char * AvcDateToString(VCTIME vc)
{
	static TCHAR ts[32];

	sprintf(ts, "%d %s %04d", vc.day, GCStrings::GetMonthAbreviation(vc.month), vc.year);

	return ts;
}

int AvcGetNextLine(TString &str, TString &strLine, int & i)
{
	int index = i, length;
	
	if (index >= str.GetLength())
		return 0;

	TCHAR tc;
	strLine.Empty();
	length = str.GetLength();

	while(1)
	{
		if (index >= length)
			break;

		tc = str.GetAt(index);
		if (tc == '\r');
		else if (tc == '\n')
		{
			index++;
			break;
		}
		else
		{
			strLine += tc;
		}
		index++;
	}

	i = index;
	return 1;
}

Boolean ConditionEvaluate(VAISNAVADAY * pd, int nClass, int nValue, TString &strText, Boolean defaultRet)
{
	static char * pcstr[] = {"", "", "", "", "", "", "", "", "", "", 
		"[c0]", "[c1]", "[c2]", "[c3]", "[c4]", "[c5]", "", ""};

	switch(nClass)
	{
	// mahadvadasis
	case 1:
		if (nValue == EV_NULL)
			return ((pd->nMhdType != EV_NULL) && (pd->nMhdType != EV_SUDDHA));
		else
			return (pd->nMhdType == nValue);
	// sankrantis
	case 2:
		if (nValue == 0xff)
			return (pd->sankranti_zodiac >= 0);
		else
			return (pd->sankranti_zodiac == nValue);
	// tithi + paksa
	case 3:
		return (pd->astrodata.nTithi == nValue);
	// naksatras
	case 4:
		return (pd->astrodata.nNaksatra == nValue);
	// yogas
	case 5:
		return (pd->astrodata.nYoga == nValue);
	// fast days
	case 6:
		if (nValue == 0)
			return (pd->nFastType != FAST_NULL);
		else
			return (pd->nFastType == (0x200 + nValue));
	
	// week day
	case 7:
		return (pd->date.dayOfWeek == nValue);
	// tithi
	case 8:
		return (pd->astrodata.nTithi % 15 == nValue);
	// paksa
	case 9:
		return (pd->astrodata.nPaksa == nValue);
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
		if (nValue == 0xffff)
		{
			return (pd->festivals.Find(pcstr[nClass]) >= 0);
		}
		else
		{
			if (pd->astrodata.nMasa == 12)
				return FALSE;
			if (abs(pd->astrodata.nTithi + pd->astrodata.nMasa*30 - nValue + 200) > 2)
				return FALSE;
			if (pd->festivals.Find(strText) >= 0)
				return TRUE;
		}
		return FALSE;
	case 15:
		if (nValue == 0xffff)
		{
			return (strText.Find(pcstr[15]) >= 0);
		}
		else
		{
			// difference against 10-14 is that we cannot test tithi-masa date
			// because some festivals in this category depends on sankranti
			if (pd->festivals.Find(strText) >= 0)
				return TRUE;
		}
		return FALSE;
	default:
		return defaultRet;
	}
}

int AvcGetTextLineCount(VAISNAVADAY * pvd)
{
	int i, nFestClass;
	int nCount = 0;
	TString str2;

	nCount++;

	if (GCDisplaySettings::getValue(17) == 1)
	{
		if (pvd->ekadasi_parana)
		{
			nCount++;
		}
	}

	if (GCDisplaySettings::getValue(6) == 1)
	{
		if (pvd->festivals)
		{
			i = pvd->GetHeadFestival();
			while(pvd->GetNextFestival(i, str2))
			{
				if (str2.GetLength() > 1)
				{
					nFestClass = pvd->GetFestivalClass(str2);
					if (nFestClass < 0 || GCDisplaySettings::getValue(22 + nFestClass) == 1)
					{
						nCount++;
					}
				}
			}
		}
	}

	if (GCDisplaySettings::getValue(16) == 1 && pvd->sankranti_zodiac >= 0)
	{
		nCount++;
	}

	if (GCDisplaySettings::getValue(7) == 1 && pvd->was_ksaya)//(m_dshow.m_info_ksaya) && (pvd->was_ksaya))
	{
		nCount++;
	}

	if (GCDisplaySettings::getValue(8) == 1)//(m_dshow.m_info_vriddhi) && (pvd->is_vriddhi))
	{
		if (pvd->is_vriddhi)
		{
			nCount++;
		}
	}

	if (pvd->nCaturmasya & CMASYA_CONT_MASK)
	{
		nCount++;
	}

	if ((GCDisplaySettings::getValue(13) == 1) && (pvd->nCaturmasya & CMASYA_PURN_MASK))
	{
		nCount++;
		if ((pvd->nCaturmasya & CMASYA_PURN_MASK_DAY) == 0x1)
		{
			nCount++;
		}
	}

	if ((GCDisplaySettings::getValue(14) == 1) && (pvd->nCaturmasya & CMASYA_PRAT_MASK))
	{
		nCount++;
		if ((pvd->nCaturmasya & CMASYA_PRAT_MASK_DAY) == 0x100)
		{
			nCount++;
		}
	}

	if ((GCDisplaySettings::getValue(15) == 1) && (pvd->nCaturmasya & CMASYA_EKAD_MASK))
	{
		nCount++;
		if ((pvd->nCaturmasya & CMASYA_EKAD_MASK_DAY) == 0x10000)
		{
			nCount++;
		}
	}

	// tithi at arunodaya
	if (GCDisplaySettings::getValue(0) == 1)//m_dshow.m_tithi_arun)
	{
		nCount++;
	}

	//"Arunodaya Time",//1
	if (GCDisplaySettings::getValue(1) == 1)//m_dshow.m_arunodaya)
	{
		nCount++;
	}
	//"Sunrise Time",//2
	//"Sunset Time",//3
	if (GCDisplaySettings::getValue(2) == 1)//m_dshow.m_sunrise)
	{
		nCount++;
	}
	if (GCDisplaySettings::getValue(3) == 1)//m_dshow.m_sunset)
	{
		nCount++;

	}
	//"Moonrise Time",//4
	if (GCDisplaySettings::getValue(4) == 1)
	{
		nCount++;
	}
	//"Moonset Time",//5
	if (GCDisplaySettings::getValue(5) == 1)
	{
		nCount++;
	}
	///"Sun Longitude",//9
	if (GCDisplaySettings::getValue(9) == 1)//m_dshow.m_sun_long)
	{
		nCount++;
	}
	//"Moon Longitude",//10
	if (GCDisplaySettings::getValue(10) == 1)//m_dshow.m_sun_long)
	{
		nCount++;
	}
	//"Ayanamsha value",//11
	if (GCDisplaySettings::getValue(11) == 1)//m_dshow.m_sun_long)
	{
		nCount++;
	}
	//"Julian Day",//12
	if (GCDisplaySettings::getValue(12) == 1)//m_dshow.m_sun_long)
	{
		nCount++;
	}

	return nCount;
}

const char * FormatDate(VCTIME vc, VATIME va)
{
	static char sz[128];

	sprintf(sz, "%d %s %d\r\n%s, %s Paksa, %s Masa, %d",
		vc.day, GCStrings::GetMonthAbreviation(vc.month), vc.year,
		GCStrings::GetTithiName(va.tithi%15), GCStrings::GetPaksaName(va.tithi/15), GCStrings::GetMasaName(va.masa), va.gyear);

	return sz;
}

