// Location.cpp: implementation of the CLocation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VCal5beta.h"
#include "Location.h"
#include "level_0.h"
#include "TFile.h"
#include "TTimeZone.h"
#include "TCountry.h"
#include "TLocation.h"
#include "TFileRichList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CLocationList theLocs;
// PORTABLE
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLocation::CLocation()
{
	m_fLatitude = 0.0;
	m_fLongitude = 0.0;
	m_fTimezone = 0.0;
	m_nDST = 0;
	next = NULL;
	prev = NULL;
}

CLocation::~CLocation()
{

}

CLocationList::CLocationList()
{
	m_bModified = TRUE;
	list = NULL;
}

CLocationList::~CLocationList()
{
	RemoveAll();
}

void CLocationList::InitInternal()
{
	CLocation * lc;
	TString city, country;

	int i, max;

	max = TLocation::GetLocationCount();

	for(i = 0; i < max; i++)
	{
		lc = new CLocation;
		if (lc)
		{
			lc->m_strCity = TLocation::gloc[i].name;
			lc->m_strCountry = TCountry::GetCountryName(TLocation::gloc[i].country_code);
			lc->m_fLatitude = TLocation::gloc[i].latitude;
			lc->m_fLongitude = TLocation::gloc[i].longitude;
			lc->m_fTimezone = TTimeZone::GetTimeZoneOffset(TLocation::gloc[i].timezone_id);
			lc->m_nDST = TLocation::gloc[i].timezone_id;
			AddTail(lc);
		}
	}
}

CLocation * CLocationList::GetHeadPosition()
{
	return list;
}

void CLocation::Empty()
{
	m_strCountry.Empty();
	m_strCity.Empty();
	m_fLatitude = 0.0;
	m_fLongitude = 0.0;
	m_fTimezone = 0.0;
	m_nDST = 0;
}

BOOL CLocationList::SaveAs(const char * lpszFileName, int nType)
{
	TString key, val, str, strTemp;
	TFile f;
	CLocation * lc;
	int i, ni;

	if (f.Open(lpszFileName, "w") == FALSE)
	{
		return FALSE;
	}

	switch(nType)
	{
	case 1:
		f.WriteString("<xml>\n");
		f.WriteString("\t<countries>\n");
		ni = TCountry::GetCountryCount();
		for(i = 0; i < ni; i++)
		{
			str.Format("\t<ccn country=\"%s\" continent=\"%s\" />\n", TCountry::GetCountryNameByIndex(i),
				TCountry::GetCountryContinentNameByIndex(i));
			f.WriteString(str);
		}
		f.WriteString("\t</countries>\n");
		f.WriteString("\t<dsts>\n");
		ni = TTimeZone::GetTimeZoneCount();
		for(i = 1; i < ni; i++)
		{
			TTimeZone::GetXMLString(str, i);
			f.WriteString(str);
		}
		f.WriteString("\t</dsts>\n");
		f.WriteString("\t<cities>\n");
		lc = list;
		while(lc)
		{
			str.Format("\t<loc city=\"%s\" lon=\"%f\" lat=\"%f\" tzone=\"%f\"\n\t\tcountry=\"%s\" />\n",
				lc->m_strCity.c_str(), lc->m_fLongitude, lc->m_fLatitude,
				lc->m_fTimezone, lc->m_strCountry.c_str());
			str.Replace("&", "&amp;");
			f.WriteString(str);
			lc = lc->next;
		}
		f.WriteString("\t</cities>\n");
		f.WriteString("</xml>");
		break;
	case 2:
		f.WriteString("Countries:\n");
		ni = TCountry::GetCountryCount();
		for(i = 0; i < ni; i++)
		{
			str.Format("%s, %s\n", TCountry::GetCountryNameByIndex(i),
				TCountry::GetCountryContinentNameByIndex(i));
			f.WriteString(str);
		}
		f.WriteString("Daylight Saving Time Systems:\n");
		ni = TTimeZone::GetTimeZoneCount();
		for(i = 1; i < ni; i++)
		{
			str.Format("\t%s\n", TTimeZone::GetTimeZoneName(i));
			f.WriteString(str);
		}
		f.WriteString("Cities:\n");
		lc = list;
		while(lc)
		{
			str.Format("\t%-23s%-17s %+03.6f %+03.6f %+02.6f\n",
				lc->m_strCity.c_str(),
				lc->m_strCountry.c_str(),
				lc->m_fLongitude,
				lc->m_fLatitude,
				lc->m_fTimezone);
			f.WriteString(str);
			lc = lc->next;
		}
		break;
	case 3:
		lc = list;
		while(lc)
		{
			// city
			f.WriteString("@city=");
			f.WriteString(lc->m_strCity);
			f.WriteString("\n");

			f.WriteString("@country=");
			f.WriteString(lc->m_strCountry);
			f.WriteString("\n");

			f.WriteString("@lat=");
			strTemp.Format("%f", lc->m_fLatitude);
			f.WriteString(strTemp);
			f.WriteString("\n");

			f.WriteString("@long=");
			strTemp.Format("%f", lc->m_fLongitude);
			f.WriteString(strTemp);
			f.WriteString("\n");

			f.WriteString("@timezone=");
			strTemp.Format("%f", lc->m_fTimezone);
			f.WriteString(strTemp);
			f.WriteString("\n");

			f.WriteString("@dst=");
			strTemp.Format("%d", lc->m_nDST);
			f.WriteString(strTemp);
			f.WriteString("\n@create\n\n");

			lc = lc->next;
		}
		break;
	case 4:
		lc = list;
		while(lc)
		{
			strTemp.Format("26700 %s|%s|%f|%f|%.2f|%d\n", lc->m_strCity.c_str(), lc->m_strCountry.c_str(), lc->m_fLongitude,
				lc->m_fLatitude, lc->m_fTimezone, lc->m_nDST);
			f.WriteString(strTemp);
			lc = lc->next;
		}
	default:
		break;
	}

	f.Close();

	return TRUE;
}

void CLocationList::RemoveAll()
{
	CLocation * p = list;
	CLocation * pn;

	while(p)
	{
		pn = p->next;
		delete p;
		p = pn;
	}

	list = NULL;

	m_bModified = TRUE;
}

void CLocationList::RemoveAt(CLocation * rem)
{
	CLocation * bef;
	CLocation * aft;

	if (rem == NULL)
		return;

	bef = rem->prev;
	aft = rem->next;

	if (rem == list)
	{
		list = list->next;
		list->prev = NULL;
	}
	else
	{
		if (bef) bef->next = aft;
		if (aft) aft->prev = bef;
	}
	rem->next = NULL;
	rem->prev = NULL;


}

void CLocationList::AddTail(CLocation *lc)
{
	if (lc == NULL)
		return;

	lc->next = list;
	if (list)
		list->prev = lc;
	lc->prev = NULL;
	list = lc;
	m_bModified = TRUE;
}

void CLocation::SetTextA(TString &str)
{
	TString temp;

	str = m_strCity;
	str += " [";
	str += m_strCountry;
	str += "]    ";

	str += EARTHDATA::GetTextLatitude(m_fLatitude);
	str += " ";
	str += EARTHDATA::GetTextLongitude(m_fLongitude);
	str += " ";
	str += TTimeZone::GetTimeZoneOffsetText(m_fTimezone);
}

void CLocation::SetTextB(TString &str)
{
	TString temp;

	str = m_strCity;
	str += " [";
	str += m_strCountry;
	str += "]\t";

	str += EARTHDATA::GetTextLatitude(m_fLatitude);
	str += "\t";
	str += EARTHDATA::GetTextLongitude(m_fLongitude);
	str += "\t";
	str += TTimeZone::GetTimeZoneOffsetText(m_fTimezone);

}

BOOL CLocationList::InitList(const char * pszFileList)
{
	TString strA, strB;
	TFile file;
	CLocation * loc = NULL;

	// try to open
	if (file.Open(pszFileList, "r") == FALSE)
	{
		InitInternal();
		m_bModified = TRUE;
		return FALSE;
	}

	// read file
	while(file.ReadPropertyLine(strA, strB))
	{
		if (loc == NULL)
		{
			loc = new CLocation;
			if (loc == NULL)
				break;
		}

		if (strA == "@create")
		{
			AddTail(loc);
			loc = NULL;
		}
		else if (strA == "@city")
		{
			loc->m_strCity = strB.c_str();
		}
		else if (strA == "@country")
		{
			loc->m_strCountry = strB.c_str();
		}
		else if (strA == "@lat")
		{
			loc->m_fLatitude = atof(strB);
		}
		else if (strA == "@long")
		{
			loc->m_fLongitude = atof(strB.c_str());
		}
		else if (strA == "@timezone")
		{
			loc->m_fTimezone = atof(strB.c_str());
		}
		else if (strA == "@dst")
		{
			loc->m_nDST = atoi(strB.c_str());
		}

	}

	// zatvara subor
	file.Close();

	return TRUE;
}

BOOL CLocationList::InitListX(const char * pszFileList)
{
	TString strA, strB;
	TFileRichList file;
	CLocation * loc = NULL;
	int notNullCountry = 0;

	// try to open
	if (file.Open(pszFileList, "r") == FALSE)
	{
		InitInternal();
		m_bModified = TRUE;
		return FALSE;
	}

	// read file
	while(file.ReadLine())
	{
		loc = new CLocation;
		if (loc != NULL)
		{
			loc->m_strCity = file.GetField(0);
			loc->m_strCountry = file.GetField(1);
			if (loc->m_strCountry.GetLength() > 0)
				notNullCountry ++;
			loc->m_fLongitude = atof(file.GetField(2));
			loc->m_fLatitude = atof(file.GetField(3));
			loc->m_fTimezone = atof(file.GetField(4));
			loc->m_nDST = atoi(file.GetField(5));
			AddTail(loc);
			loc = NULL;
		}
	}

	// zatvara subor
	file.Close();

	if (list == NULL || notNullCountry == 0)
	{
		RemoveAll();
		InitInternal();
		m_bModified = TRUE;
	}


	return TRUE;
}

BOOL CLocationList::ImportFile(const char * pszFile, BOOL bDeleteCurrent)
{
	if (bDeleteCurrent)
	{
		RemoveAll();
	}

	m_bModified = TRUE;

	return InitList(pszFile);
}


int CLocationList::RenameCountry(const char *pszOld, const char *pszNew)
{
	CLocation * L = list;

	while(L)
	{
		if (strcmp(L->m_strCountry.c_str(), pszOld)==0)
			L->m_strCountry = pszNew;
		L = L->next;
	}
	return 1;
}
