#include "stdafx.h"
#include "GCVaisnavaDay.h"
#include "GCStrings.h"
#include "GCRasi.h"
#include "GCTithi.h"
#include "GCNaksatra.h"
#include "GCDisplaySettings.h"
#include "math.h"

VAISNAVADAY::~VAISNAVADAY()
{

}

VAISNAVADAY & VAISNAVADAY::operator=(VCTIME &vc)
{
	date = vc;
	fDateValid = true;
	return * this; 
}

VAISNAVADAY & VAISNAVADAY::operator=(DAYDATA &dd)
{
	astrodata = dd;
	fAstroValid = true;
	return * this;
}

VAISNAVADAY::VAISNAVADAY() 
{
	fDateValid = false;
	fAstroValid = false;
	fVaisValid = false;
	// init
	//festivals = "";
	nFastType = FAST_NULL;
	nMhdType = EV_NULL;
	ekadasi_parana = false;
	ekadasi_vrata_name.Empty();
	eparana_time1 = eparana_time2 = 0.0;
	eparana_type1 = eparana_type2 = EP_TYPE_NULL;
	sankranti_zodiac = -1;
	was_ksaya = false;
	ksaya_time1 = ksaya_time2 = 0.0;
	is_vriddhi = false;
	nDST = 0;
	nCaturmasya = 0;
	moonrise.SetValue(0);
	moonset.SetValue(0);
}

void VAISNAVADAY::Clear()
{
		fVaisValid = false;
		// init
		festivals.Empty();
		nFastType = FAST_NULL;
		nFeasting = FEAST_NULL;
		nMhdType = EV_NULL;
		ekadasi_parana = false;
		ekadasi_vrata_name.Empty();
		eparana_time1 = eparana_time2 = 0.0;
		sankranti_zodiac = -1;
		sankranti_day.day = 0;
		sankranti_day.shour = 0.0;
		sankranti_day.month = 0;
		sankranti_day.year = 0;
		was_ksaya = false;
//		nSpecFestival = 0;
		ksaya_time1 = ksaya_time2 = 0.0;
		is_vriddhi = false;
		nCaturmasya = 0;
		//moonset.SetValue(0);
		//moonrise.SetValue(0);
		//nDST = 0;
}

/* BEGIN GCAL 1.4.3 */
void VAISNAVADAY::GetTextA(TString &str, int bPaksa, int bNaks, int bYoga, int bFlag, int bRasi)
{
//	static char * dow[] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa" };

	TString s1, s2;

	s1 = GCStrings::GetTithiName(astrodata.nTithi);

	if ((astrodata.nTithi == 10) || (astrodata.nTithi == 25) || (astrodata.nTithi == 11) || (astrodata.nTithi == 26))
	{
		if (ekadasi_parana == false)
		{
			if (nMhdType == EV_NULL)
			{
				s1 += " ";
				s1 += GCStrings::getString(58);
			}
			else
			{
				s1 += " ";
				s1 += GCStrings::getString(59);
			}
		}
	}

	GCStrings::getString(this->date.dayOfWeek).Left(2, s2);
	str.Format("%2d %s %d %s  %-34s%c ", this->date.day, GCStrings::GetMonthAbreviation(date.month), this->date.year
		, s2.c_str() ,s1.c_str(), (bPaksa ? GCStrings::GetPaksaChar(this->astrodata.nPaksa) : ' '));

	if (bYoga)
	{
		s2.Format("%-10s", GCStrings::GetYogaName(this->astrodata.nYoga));
		str += s2;
	}

	if (bNaks)
	{
		s2.Format("%-15s", GCStrings::GetNaksatraName(this->astrodata.nNaksatra));
		str += s2;
	}
	
	if (this->nFastType != FAST_NULL && bFlag)
		str += " *";
	else
		str += "  ";

	if (bRasi)
	{
		if (bRasi == 1)
			s2.Format("   %-15s", GCStrings::GetSankrantiName(GCRasi::GetRasi(this->astrodata.moon.longitude_deg, this->astrodata.msAyanamsa)));
		else
			s2.Format("   %-15s", GCStrings::GetSankrantiNameEn(GCRasi::GetRasi(this->astrodata.moon.longitude_deg, this->astrodata.msAyanamsa)));
		str += s2;
	}
}

void VAISNAVADAY::GetTextRtf(TString &str, int bPaksa, int bNaks, int bYoga, int bFlag, int bRasi)
{
	TString s1, s2;

	s1 = GCStrings::GetTithiName(astrodata.nTithi);

	if ((astrodata.nTithi == 10) || (astrodata.nTithi == 25) || (astrodata.nTithi == 11) || (astrodata.nTithi == 26))
	{
		if (ekadasi_parana == false)
		{
			if (nMhdType == EV_NULL)
			{
				s1 += " ";
				s1 += GCStrings::getString(58);
			}
			else
			{
				s1 += " ";
				s1 += GCStrings::getString(59);
			}
		}
	}

	GCStrings::getString(this->date.dayOfWeek).Left(2, s2);
	str.Format("\\par %2d %s %d %s\\tab %s\\tab %c ", this->date.day, GCStrings::GetMonthAbreviation(date.month), this->date.year
		, s2.c_str() ,s1.c_str(), (bPaksa ? GCStrings::GetPaksaChar(this->astrodata.nPaksa) : ' '));

	if (bYoga)
	{
		s2.Format("\\tab %s", GCStrings::GetYogaName(this->astrodata.nYoga));
		str += s2;
	}

	if (bNaks)
	{
		s2.Format("\\tab %s", GCStrings::GetNaksatraName(this->astrodata.nNaksatra));
		str += s2;
	}
	
	if (this->nFastType != FAST_NULL && bFlag)
		str += "\\tab *";
	else if (bFlag)
		str += "\\tab ";

	if (bRasi)
	{
		if (bRasi == 1)
			s2.Format("\\tab %s", GCStrings::GetSankrantiName(GCRasi::GetRasi(this->astrodata.moon.longitude_deg, this->astrodata.msAyanamsa)));
		else
			s2.Format("\\tab %s", GCStrings::GetSankrantiNameEn(GCRasi::GetRasi(this->astrodata.moon.longitude_deg, this->astrodata.msAyanamsa)));
		str += s2;
	}

	str += "\r\n";
}

/* END GCAL 1.4.3 */

void VAISNAVADAY::GetTextEP(TString &str)
{
	double h1, m1, h2, m2;
	m1 = modf(eparana_time1, &h1);
	if (eparana_time2 >= 0.0)
	{
		m2 = modf(eparana_time2, &h2);
		if (GCDisplaySettings::getValue(50))
			str.Format("                 %s %02d:%02d (%s) - %02d:%02d (%s) %s", GCStrings::getString(60).c_str(),
				int(h1), int(m1*60), GCStrings::GetParanaReasonText(eparana_type1), 
				int(h2), int(m2*60), GCStrings::GetParanaReasonText(eparana_type2),
				GCStrings::GetDSTSignature(nDST));
		else
			str.Format("                 %s %02d:%02d - %02d:%02d (%s)", GCStrings::getString(60).c_str(),
				int(h1), int(m1*60), int(h2), int(m2*60), GCStrings::GetDSTSignature(nDST));
	}
	else if (eparana_time1 >= 0.0)
	{
		if (GCDisplaySettings::getValue(50))
			str.Format("                 %s %02d:%02d (%s) %s", GCStrings::getString(61).c_str(),
				int(h1), int(m1*60), GCStrings::GetParanaReasonText(eparana_type1), GCStrings::GetDSTSignature(nDST) );
		else
			str.Format("                 %s %02d:%02d (%s)", GCStrings::getString(61).c_str(),
				int(h1), int(m1*60), GCStrings::GetDSTSignature(nDST) );
	}
	else
	{
		str = "                 ";
		str += GCStrings::getString(62);
	}
}


int VAISNAVADAY::GetHeadFestival()
{
	if (festivals.IsEmpty())
		return -1;

	return 0;
}

bool VAISNAVADAY::GetNextFestival(int &i, TString &str)
{
	str.Empty();

	if (i < 0)
		return FALSE;

	while(i < festivals.GetLength() && festivals.GetAt(i) != '#')
	{
		str += festivals.GetAt(i);
		i++;
	}

	if (i < festivals.GetLength())
	{
		i++;
	}
	else
	{
		i = -1;
	}

	return TRUE;
}


bool VAISNAVADAY::GetNaksatraTimeRange(EARTHDATA earth, VCTIME &from, VCTIME &to)
{
	VCTIME start;

	start = date;
	start.shour = this->astrodata.sun.sunrise_deg / 360 + earth.tzone/24.0;

	GCNaksatra::GetNextNaksatra(earth, start, to);
	GCNaksatra::GetPrevNaksatra(earth, start, from);

	return TRUE;
}


bool VAISNAVADAY::GetTithiTimeRange(EARTHDATA earth, VCTIME &from, VCTIME &to)
{
	VCTIME start;

	start = date;
	start.shour = this->astrodata.sun.sunrise_deg / 360 + earth.tzone/24.0;

	GCTithi::GetNextTithiStart(earth, start, to);
	GCTithi::GetPrevTithiStart(earth, start, from);

	return TRUE;

}


int VAISNAVADAY::GetFestivalClass(TString &str)
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
			if (j >= str.GetLength())
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

void VAISNAVADAY::GetFastingSubject(TString &strFest, int &nFast, TString &strFastSubj)
{
	int nf, nf2;

	// default values
	nFast = 0;
	strFastSubj.Empty();

	// finding fast subject
	nf = strFest.Find("[f:");
	if (nf >= 0 && nf < strFest.GetLength())
	{
		// ziskava typ postu
		nFast = strFest.GetAt(nf+3) - '0';
		nf2 = strFest.Find("]", nf);
		if (nf2 >= 0)
		{
			strFest.Mid(nf + 5, nf2 - nf - 5, strFastSubj);
		}
		strFest.Delete(nf, strFest.GetLength() - nf);
	}
}


