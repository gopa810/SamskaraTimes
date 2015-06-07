#include "stdafx.h"

#include "LocationRef.h"
#include "XmlFile.h"
#include "level_6.h"
#include "strings.h"
#include "vedic_ui.h"
#include "level_5_days.h"
#include "TTimeZone.h"
#include "TResultApp.h"
#include "TResultEvent.h"
#include "TResultMasaList.h"
#include "enums.h"
#include "GCStrings.h"
#include "GCTithi.h"
#include "GCNaksatra.h"
#include "GCSankranti.h"

// PORTABLE

int WriteXML_FirstDay_Year(FILE * fout, CLocationRef & loc, VCTIME vcStart)
{
	TFileXml xml;

	xml.initWithFile(fout);

	vcStart = DAYDATA::GetFirstDayOfYear((EARTHDATA)loc, vcStart.year);
	vcStart.InitWeekDay();

	// write
	xml.write("<xml>\n");
	xml.write("\t<request name=\"FirstDay\" version=\"");
	xml.write(GCStrings::getString(130));
	xml.write("\">\n");
	xml.write("\t\t<arg name=\"longitude\" val=\"");
	xml.write(loc.m_fLongitude);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"latitude\" val=\"");
	xml.write(loc.m_fLatitude);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"year\" val=\"");
	xml.write(vcStart.year);
	xml.write("\" />\n");
	xml.write("\t</request>\n");
	xml.write("\t<result name=\"FirstDay_of_GaurabdaYear\">\n");
	xml.write("\t\t<firstday date=\"");
	xml.write(vcStart);
	xml.write("\" dayweekid = \"");
	xml.write(vcStart.dayOfWeek);
	xml.write("\" dayweek=\"");
	xml.write(GCStrings::getString(vcStart.dayOfWeek));
	xml.write("\" />\n");
	xml.write("\t</result>\n");
	xml.write("</xml>\n");

	return 0;
}

int WriteXML_Sankrantis(FILE * fout, CLocationRef & loc, VCTIME vcStart, VCTIME vcEnd)
{
	VCTIME d;
	DAYTIME dt;
	int zodiac;

	TFileXml xml;

	// open file
	xml.initWithFile(fout);

	d = vcStart;

	xml.write("<xml>\n");
	xml.write("\t<request name=\"Sankranti\" version=\"");
	xml.write(GCStrings::getString(130));
	xml.write("\">\n");
	xml.write("\t\t<arg name=\"longitude\" val=\"");
	xml.write(loc.m_fLongitude);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"latitude\" val=\"");
	xml.write(loc.m_fLatitude);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"timezone\" val=\"");
	xml.write(loc.m_fTimezone);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"location\" val=\"");
	xml.write(loc.m_strName);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"startdate\" val=\"");
				xml.write(vcStart);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"enddate\" val=\"");
				xml.write(vcEnd);
	xml.write("\" />\n");
	xml.write("\t</request>\n");
	xml.write("\t<result name=\"SankrantiList\">\n");

	while(d.IsBeforeThis(vcEnd))
	{
		d = GCSankranti::GetNextSankranti(d, zodiac);
		d.InitWeekDay();
		xml.write("\t\t<sank date=\"");
		xml.write(d);
		xml.write("\" ");
		xml.write("dayweekid=\"");
		xml.write(d.dayOfWeek);
		xml.write("\" dayweek=\"");
		xml.write(GCStrings::getString(d.dayOfWeek));
		xml.write("\" ");

		dt.SetDegTime( 360 * d.shour );

		xml.write(" time=\"");
		xml.write(dt);
		xml.write("\" >\n");
		xml.write("\t\t<zodiac sans=\"");
		xml.write(GCStrings::GetSankrantiName(zodiac));
		xml.write("\" eng=\"");
		xml.write(GCStrings::GetSankrantiNameEn(zodiac));
		xml.write("\" id=\"");
		xml.write(zodiac);
		xml.write("\" />\n");
		xml.write("\t\t</sank>\n\n");

		d.NextDay();
		d.NextDay();
	}

	xml.write("\t</result>\n");
	xml.write("</xml>");

	return 1;
}

int WriteCalendarXml(TResultCalendar &daybuff, FILE * fout)
{
	int k;
	TString str, st;
	VCTIME date;
	TFileXml xml;
	VAISNAVADAY * pvd;
	int nPrevMasa = -1;
	int nPrevPaksa = -1;

	xml.initWithFile(fout);

	xml.write("<xml>\n");
	xml.write("\t<request name=\"Calendar\" version=\"");
	xml.write(GCStrings::getString(130));
	xml.write("\">\n");
	xml.write("\t\t<arg name=\"longitude\" val=\"");
	xml.write(daybuff.m_Location.m_fLongitude);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"latitude\" val=\"");
	xml.write(daybuff.m_Location.m_fLatitude);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"timezone\" val=\"");
	xml.write(daybuff.m_Location.m_fTimezone);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"startdate\" val=\"");
	xml.write(daybuff.m_vcStart);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"daycount\" val=\"");
	xml.write(daybuff.m_vcCount);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"dst\" val=\"");
	xml.write(daybuff.m_Location.m_nDST);
	xml.write("\" />\n");
	xml.write("\t</request>\n");
	xml.write("\t<result name=\"Calendar\">\n");
	if (daybuff.m_Location.m_nDST > 0)
		xml.write("\t<dstsystem name=\"");
	xml.write(TTimeZone::GetTimeZoneName(daybuff.m_Location.m_nDST));
	xml.write("\" />\n");

	for (k = 0; k < daybuff.m_vcCount; k++)
	{
		pvd = daybuff.GetDay(k);
		if (pvd)
		{
			if (nPrevMasa != pvd->astrodata.nMasa)
			{
				if (nPrevMasa != -1)
					xml.write("\t</masa>\n");
				xml.write("\t<masa name=\"");
				xml.write(GCStrings::GetMasaName(pvd->astrodata.nMasa));
				xml.write(" Masa");
				if (nPrevMasa == ADHIKA_MASA)
					xml.write(" ");
				xml.write(GCStrings::getString(109));
				xml.write("\"");
				xml.write(" gyear=\"Gaurabda ");
				xml.write(pvd->astrodata.nGaurabdaYear);
				xml.write("\"");
				xml.write(">\n");
			}

			nPrevMasa = pvd->astrodata.nMasa;

			// date data
			xml.write("\t<day date=\"");
			xml.write(pvd->date);
			xml.write("\" dayweekid=\"");
			xml.write(pvd->date.dayOfWeek);
			xml.write("\" dayweek=\"");
			GCStrings::getString(pvd->date.dayOfWeek).Left(2, st);
			xml.write(st.c_str());
			xml.write("\">\n");

			// sunrise data
			xml.write("\t\t<sunrise time=\"");
			xml.write(pvd->astrodata.sun.rise);
			xml.write("\">\n");

			xml.write("\t\t\t<tithi name=\"");
			xml.write(GCStrings::GetTithiName(pvd->astrodata.nTithi));
			if ((pvd->astrodata.nTithi == 10) || (pvd->astrodata.nTithi == 25) 
				|| (pvd->astrodata.nTithi == 11) || (pvd->astrodata.nTithi == 26))
			{
				if (pvd->ekadasi_parana == false)
				{
					if (pvd->nMhdType == EV_NULL)
					{
						xml.write(" ");
						xml.write(GCStrings::getString(58));
					}
					else
					{
						xml.write(" ");
						xml.write(GCStrings::getString(59));
					}
				}
			}
			str.Format("\" elapse=\"%.1f\" index=\"%d\"/>\n"
				,pvd->astrodata.nTithiElapse, pvd->astrodata.nTithi % 30 + 1 );
			xml.write(str);

			str.Format("\t\t\t<naksatra name=\"%s\" elapse=\"%.1f\" />\n"
				,GCStrings::GetNaksatraName(pvd->astrodata.nNaksatra), pvd->astrodata.nNaksatraElapse );
			xml.write(str);

			str.Format("\t\t\t<yoga name=\"%s\" />\n", GCStrings::GetYogaName(pvd->astrodata.nYoga) );
			xml.write(str);

			str.Format("\t\t\t<paksa id=\"%c\" name=\"%s\"/>\n", GCStrings::GetPaksaChar(pvd->astrodata.nPaksa), GCStrings::GetPaksaName(pvd->astrodata.nPaksa) );
			xml.write(str);

			xml.write("\t\t</sunrise>\n");

			xml.write("\t\t<dst offset=\"");
			xml.write(pvd->nDST);
			xml.write("\" />\n");
			// arunodaya data
			xml.write("\t\t<arunodaya time=\"");
			xml.write(pvd->astrodata.sun.arunodaya);
			xml.write("\">\n");
			xml.write("\t\t\t<tithi name=\"");
			xml.write(GCStrings::GetTithiName(pvd->astrodata.nTithiArunodaya));
			xml.write("\" />\n");
			xml.write("\t\t</arunodaya>\n");

			str.Empty();

			xml.write("\t\t<noon time=\"");
			xml.write(pvd->astrodata.sun.noon);
			xml.write("\" />\n");

			xml.write("\t\t<sunset time=\"");
			xml.write(pvd->astrodata.sun.set);
			xml.write("\" />\n");

			// moon data
			xml.write("\t\t<moon rise=\"");
			xml.write(pvd->moonrise);
			xml.write("\" set=\"");
			xml.write(pvd->moonset);
			xml.write("\" />\n");

			if (pvd->ekadasi_parana)
			{
				double h1, m1, h2, m2;
				m1 = modf(pvd->eparana_time1, &h1);
				if (pvd->eparana_time2 >= 0.0)
				{
					m2 = modf(pvd->eparana_time2, &h2);
					str.Format("\t\t<parana from=\"%02d:%02d\" to=\"%02d:%02d\" />\n", int(h1), int(m1*60), int(h2), int(m2*60));
				}
				else
				{
					str.Format("\t\t<parana after=\"%02d:%02d\" />\n", int(h1), int(m1*60) );
				}
				xml.write(str);
			}
			str.Empty();

			if (pvd->festivals.GetLength() > 0)
			{
				int i = pvd->GetHeadFestival();
				int nFestClass;
				TString str2;
				while(pvd->GetNextFestival(i, str2))
				{
					if (str2.GetLength() > 1)
					{
						nFestClass = pvd->GetFestivalClass(str2);
						str.Format("\t\t<festival name=\"%s\" class=\"%d\"/>\n", str2.c_str(), nFestClass);
						xml.write(str);
					}
				}
			}

			if (pvd->nFastType != FAST_NULL)
			{
				if (pvd->nFastType == FAST_EKADASI)
				{
					xml.write("\t\t<fast type=\"\" mark=\"*\" />\n");
				}
				else
				{
					xml.write("\t\t<fast type=\"\" mark=\"\" />\n");
				}
			}

			if (pvd->sankranti_zodiac >= 0)
			{
				//double h1, m1, s1;
				//m1 = modf(pvd->sankranti_day.shour*24, &h1);
//				s1 = modf(m1*60, &m1);
				str.Format("\t\t<sankranti rasi=\"%s\" time=\"%02d:%02d:%02d\" />\n"
					, GCStrings::GetSankrantiName(pvd->sankranti_zodiac), pvd->sankranti_day.GetHour()
					, pvd->sankranti_day.GetMinute(), pvd->sankranti_day.GetSecond());
				xml.write(str);
			}

			if (pvd->was_ksaya)
			{
				double h1, m1, h2, m2;
				m1 = modf(pvd->ksaya_time1*24, &h1);
				m2 = modf(pvd->ksaya_time2*24, &h2);
				str.Format("\t\t<ksaya from=\"%02d:%02d\" to=\"%02d:%02d\" />\n", int(h1), abs(int(m1*60)), int(h2), abs(int(m2*60)));
				xml.write(str);
			}

			if (pvd->is_vriddhi)
			{
				xml.write("\t\t<vriddhi sd=\"yes\" />\n");
			}
			else
			{
				xml.write("\t\t<vriddhi sd=\"no\" />\n");
			}

			if (pvd->nCaturmasya & CMASYA_PURN_MASK)
			{
				xml.write("\t\t<caturmasya day=\"" );
				xml.write((((pvd->nCaturmasya & CMASYA_PURN_MASK_DAY)) > 1 ? "last" : "first"));
				xml.write("\" month=\"");
				xml.write(int((pvd->nCaturmasya & CMASYA_PURN_MASK_MASA) >> 4));
				xml.write("\" system=\"PURNIMA\" />\n");
			}

			if (pvd->nCaturmasya & CMASYA_PRAT_MASK)
			{
				xml.write("\t\t<caturmasya day=\"" );
				xml.write((((pvd->nCaturmasya & CMASYA_PRAT_MASK_DAY) >> 8) > 1 ? "last" : "first"));
				xml.write("\" month=\"" );
				xml.write(int((pvd->nCaturmasya & CMASYA_PRAT_MASK_MASA) >> 12));
				xml.write("\" system=\"PRATIPAT\" />\n");
			}

			if (pvd->nCaturmasya & CMASYA_EKAD_MASK)
			{
				str.Format("\t<caturmasya day=\"%s\" month=\"%d\" system=\"EKADASI\" />\n"
					, ((pvd->nCaturmasya & CMASYA_EKAD_MASK_DAY) >> 16) > 1 ? "last" : "first"
					, int((pvd->nCaturmasya & CMASYA_EKAD_MASK_MASA) >> 20));
				xml.write(str);
			}

			xml.write("\t</day>\n\n");

		}
		date.shour = 0;
		date.NextDay();
	}
	xml.write("\t</masa>\n");

	
	xml.write("</result>\n");
	xml.write("</xml>\n");

	return 1;
}

int WriteXML_Naksatra(FILE * fout, CLocationRef &loc, VCTIME vc, int nDaysCount)
{
	TString str;
	VCTIME date;

	TFileXml xml;
	xml.initWithFile(fout);

	xml.write("<xml>\n");
	xml.write("\t<request name=\"Naksatra\" version=\"");
	xml.write(GCStrings::getString(130));
	xml.write("\">\n");
	xml.write("\t\t<arg name=\"longitude\" val=\"");
	xml.write(loc.m_fLongitude);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"latitude\" val=\"");
	xml.write(loc.m_fLatitude);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"timezone\" val=\"");
	xml.write(loc.m_fTimezone);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"startdate\" val=\"");
	xml.write(vc);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"daycount\" val=\"");
	xml.write(nDaysCount);
	xml.write("\" />\n");
	xml.write("\t</request>\n");
	xml.write("\t<result name=\"Naksatra\">\n");

	VCTIME d = vc;
	d.tzone = loc.m_fTimezone;
	VCTIME dn;
	DAYTIME dt;
	SUNDATA sun;
	int nak;
	EARTHDATA earth = (EARTHDATA)loc;

	for(int i = 0; i < 30; i++)
	{
		nak = GCNaksatra::GetNextNaksatra(earth, d, dn);
		d = dn;
		xml.write("\t\t<day date=\"");
	xml.write(d);
	xml.write("\">\n");
		//str.Format("%d.%d.%d", d.day, d.month, d.year);
		//n = m_list.InsertItem(50, GetNaksatraName(nak));
		//m_list.SetItemText(n, 1, str);
		xml.write("\t\t\t<naksatra id=\"");
	xml.write(nak);
	xml.write("\" name=\"");
	xml.write(GCStrings::GetNaksatraName(nak));
	xml.write("\"\n");
		dt.SetDegTime( d.shour * 360);
		//time_print(str, dt);
		xml.write("\t\t\t\tstarttime=\"");
	xml.write(dt);
	xml.write("\" />\n");
		//m_list.SetItemText(n, 2, str);

		// sunrise time get
		sun.SunCalc(d, earth);
		//time_print(str, sun.rise);
		//m_list.SetItemText(n, 3, str);
		xml.write("\t\t\t<sunrise time=\"");
	xml.write(sun.rise);
	xml.write("\" />\n");

		xml.write("\t\t</day>\n");
		// increment for non-duplication of naksatra
		d = dn;
		d.shour += 1.0/8.0;
	}


	xml.write("\t</result>\n");
	xml.write("</xml>\n");


	return 1;
}

int WriteXML_Tithi(FILE * fout, CLocationRef &loc, VCTIME vc)
{
	TString str;
	VCTIME date;

	TFileXml xml;
	xml.initWithFile(fout);

	xml.write("<xml>\n");
	xml.write("\t<request name=\"Tithi\" version=\"");
	xml.write(GCStrings::getString(130));
	xml.write("\">\n");
	xml.write("\t\t<arg name=\"longitude\" val=\"");
	xml.write(loc.m_fLongitude);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"latitude\" val=\"");
	xml.write(loc.m_fLatitude);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"timezone\" val=\"");
	xml.write(loc.m_fTimezone);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"startdate\" val=\"");
	xml.write(vc);
	xml.write("\" />\n");
	xml.write("\t</request>\n");
	xml.write("\t<result name=\"Tithi\">\n");

	VCTIME d = vc;
	VCTIME d1, d2;
	d.tzone = loc.m_fTimezone;
	VCTIME dn;
	DAYTIME dt;
	EARTHDATA earth = (EARTHDATA)loc;


	DAYDATA day;

	day.DayCalc(vc, earth);

	d.shour = day.sun.sunrise_deg/360.0 + loc.m_fTimezone/24.0;

	GCTithi::GetPrevTithiStart(earth, d, d1);
	GCTithi::GetNextTithiStart(earth, d, d2);

	{
		dt.SetDegTime( d1.shour * 360 );
		// start tithi at t[0]
		xml.write("\t\t<tithi\n\t\t\tid=\"");
	xml.write(day.nTithi);
	xml.write("\"\n");
		xml.write("\t\t\tname=\"");
	xml.write(GCStrings::GetTithiName(day.nTithi));
	xml.write("\"\n");
		xml.write("\t\t\tstartdate=\"");
	xml.write(d1);
	xml.write("\"\n");
		xml.write("\t\t\tstarttime=\"");
	xml.write(dt);
	xml.write("\"\n");
	
		dt.SetDegTime( d2.shour * 360 );
		xml.write("\t\t\tenddate=\"");
	xml.write(d2);
	xml.write("\"\n");
		xml.write("\t\t\tendtime=\"");
	xml.write(dt);
	xml.write("\"\n />");
	}

	xml.write("\t</result>\n");
	xml.write("</xml>\n");

	return 1;
}

int WriteXML_GaurabdaTithi(FILE * fout, CLocationRef &loc, VATIME vaStart, VATIME vaEnd)
{
	int gyearA = vaStart.gyear;
	int gyearB = vaEnd.gyear;
	int gmasa = vaStart.masa;
	int gpaksa = vaStart.tithi / 15;
	int gtithi = vaStart.tithi % 15;
	
	if (gyearB < gyearA)
		gyearB = gyearA;

	TFileXml xml;

	xml.initWithFile(fout);

	xml.write("<xml>\n");
	xml.write("\t<request name=\"Tithi\" version=\"");
	xml.write(GCStrings::getString(130));
	xml.write("\">\n");
	xml.write("\t\t<arg name=\"longitude\" val=\"");
	xml.write(loc.m_fLongitude);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"latitude\" val=\"");
	xml.write(loc.m_fLatitude);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"timezone\" val=\"");
	xml.write(loc.m_fTimezone);
	xml.write("\" />\n");
	if (gyearA > 1500)
	{
		xml.write("\t\t<arg name=\"year-start\" val=\"");
	xml.write(gyearA);
	xml.write("\" />\n");
		xml.write("\t\t<arg name=\"year-end\" val=\"");
	xml.write(gyearB);
	xml.write("\" />\n");
	}
	else
	{
		xml.write("\t\t<arg name=\"gaurabdayear-start\" val=\"");
	xml.write(gyearA);
	xml.write("\" />\n");
		xml.write("\t\t<arg name=\"gaurabdayear-end\" val=\"");
	xml.write(gyearB);
	xml.write("\" />\n");
	}
	xml.write("\t\t<arg name=\"masa\" val=\"");
	xml.write(gmasa);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"paksa\" val=\"");
	xml.write(gpaksa);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"tithi\" val=\"");
	xml.write(gtithi);
	xml.write("\" />\n");
	xml.write("\t</request>\n");
	xml.write("\t<result name=\"Tithi\">\n");


	EARTHDATA earth = (EARTHDATA)loc;
	VCTIME vcs, vce, today;
	SUNDATA sun;
	int A, B;
	double sunrise;
	DAYDATA day;
	int oTithi, oPaksa, oMasa, oYear;

	if (gyearA > 1500)
	{
		A = gyearA - 1487;
		B = gyearB - 1485;
	}
	else
	{
		A = gyearA;
		B = gyearB;
	}

	for(; A <= B; A++)
	{
		vcs = GCTithi::CalcTithiEnd(A, gmasa, gpaksa, gtithi, earth, vce);
		if (gyearA > 1500)
		{
			if ((vcs.year < gyearA) || (vcs.year > gyearB))
				continue;
		}
		oTithi = gpaksa*15 + gtithi;
		oMasa = gmasa;
		oPaksa = gpaksa;
		oYear = 0;
		xml.write("\t<celebration\n");
//		xml.write("\t\t<tithi\n";
		xml.write("\t\trtithi=\"");
	xml.write(GCStrings::GetTithiName(oTithi));
	xml.write("\"\n");
		xml.write("\t\trmasa=\"");
	xml.write(GCStrings::GetMasaName(oMasa));
	xml.write("\"\n");
		xml.write("\t\trpaksa=\"");
	xml.write((oPaksa ? _T("Gaura") : _T("Krsna")));
	xml.write("\"\n");
		// test ci je ksaya
		today = vcs;
		today.shour = 0.5;
		sun.SunCalc(today, earth);
		sunrise = (sun.sunrise_deg + loc.m_fTimezone*15.0)/360;
		if (sunrise < vcs.shour)
		{
			today = vce;
			sun.SunCalc(today, earth);
			sunrise = (sun.sunrise_deg + loc.m_fTimezone*15.0)/360;
			if (sunrise < vce.shour)
			{
				// normal type
				vcs.NextDay();
				xml.write("\t\ttype=\"normal\"\n");
			}
			else
			{
				// ksaya
				vcs.NextDay();
				day.DayCalc(vcs, earth);
				oTithi = day.nTithi;
				oPaksa = day.nPaksa;
				oMasa = day.MasaCalc(vcs, earth);
				oYear = day.nGaurabdaYear;
				xml.write("\t\ttype=\"ksaya\"\n");
			}
		}
		else
		{
			// normal, alebo prvy den vriddhi
			today = vce;
			sun.SunCalc(today, earth);
			if ((sun.sunrise_deg + loc.m_fTimezone*15.0)/360 < vce.shour)
			{
				// first day of vriddhi type
				xml.write("\t\ttype=\"vriddhi\"\n");
			}
			else
			{
				// normal
				xml.write("\t\ttype=\"normal\"\n");
			}
		}
		xml.write("\t\tdate=\"");
	xml.write(vcs);
	xml.write("\"\n");
		xml.write("\t\totithi=\"");
	xml.write(GCStrings::GetTithiName(oTithi));
	xml.write("\"\n");
		xml.write("\t\tomasa=\"");
	xml.write(GCStrings::GetMasaName(oMasa));
	xml.write("\"\n");
		xml.write("\t\topaksa=\"");
	xml.write((oPaksa ? _T("Gaura") : _T("Krsna")));
	xml.write("\"\n");
		xml.write("\t/>\n");
//		xml.write("\t\t</celebration>\n";

	}

/*	xml.write("\t\t<tithi\n\t\t\tid=\"");
	xml.write(int(gpaksa*15 + gtithi));
	xml.write("\"\n");
	xml.write("\t\t\tname=\"");
	xml.write(GetTithiName(gpaksa*15 + gtithi));
	xml.write("\"\n");
	xml.write("\t\t\tstartdate=\"");
	xml.write(vcs);
	xml.write("\"\n");
	dt.SetDegTime(360.0 * vcs.shour);
	xml.write("\t\t\tstarttime=\"");
	xml.write(dt);
	xml.write("\"\n");
	xml.write("\t\t\tenddate=\"");
	xml.write(vce);
	xml.write("\"\n");
	dt.SetDegTime(360.0 * vce.shour);
	xml.write("\t\t\tendtime=\"");
	xml.write(dt);
	xml.write("\"\n");
	xml.write("\t\t\tmasa=\"");
	xml.write(GetMasaName(gmasa));
	xml.write("\"\n");
	xml.write("\t\t\tpaksa=\"");
	xml.write((gpaksa ? _T("Gaura") : _T("Krsna")));
	xml.write("\"\n");
	xml.write("\t\t/>\n";
*/
	xml.write("\t</result>\n");
	xml.write("</xml>\n");

	return 1;
}

int WriteXML_GaurabdaNextTithi(FILE * fout, CLocationRef &loc, VCTIME vcStart, VATIME vaStart)
{
	int gmasa, gpaksa, gtithi;
	TFileXml xml;

	gmasa = vaStart.masa;
	gpaksa = vaStart.tithi / 15;
	gtithi = vaStart.tithi % 15;

	xml.initWithFile(fout);

	xml.write("<xml>\n");
	xml.write("\t<request name=\"Tithi\" version=\"");
	xml.write(GCStrings::getString(130).c_str());
	xml.write("\">\n");
	xml.write("\t\t<arg name=\"longitude\" val=\"");
	xml.write(loc.m_fLongitude);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"latitude\" val=\"");
	xml.write(loc.m_fLatitude);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"timezone\" val=\"");
	xml.write(loc.m_fTimezone);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"start date\" val=\"");
	xml.write(vcStart);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"masa\" val=\"");
	xml.write(gmasa);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"paksa\" val=\"");
	xml.write(gpaksa);
	xml.write("\" />\n");
	xml.write("\t\t<arg name=\"tithi\" val=\"");
	xml.write(gtithi);
	xml.write("\" />\n");
	xml.write("\t</request>\n");
	xml.write("\t<result name=\"Tithi\">\n");

	EARTHDATA earth = (EARTHDATA)loc;
	VCTIME vcs, vce, today;
	SUNDATA sun;
	int A;
	double sunrise;
	DAYDATA day;
	int oTithi, oPaksa, oMasa, oYear;

	today = vcStart;
	today.PreviousDay();
	vcStart -= 15;
	for(A = 0; A <= 3; A++)
	{
		vcs = GCTithi::CalcTithiEndEx(vcStart, 0, gmasa, gpaksa, gtithi, earth, vce);
		if (!vcs.IsBeforeThis(today))
		{
			oTithi = gpaksa*15 + gtithi;
			oMasa = gmasa;
			oPaksa = gpaksa;
			oYear = 0;
			xml.write("\t<celebration\n");
	//		xml.write("\t\t<tithi\n";
			xml.write("\t\trtithi=\"");
	xml.write(GCStrings::GetTithiName(oTithi));
	xml.write("\"\n");
			xml.write("\t\trmasa=\"");
	xml.write(GCStrings::GetMasaName(oMasa));
	xml.write("\"\n");
			xml.write("\t\trpaksa=\"");
	xml.write((oPaksa ? _T("Gaura") : _T("Krsna")));
	xml.write("\"\n");
			// test ci je ksaya
			today = vcs;
			today.shour = 0.5;
			sun.SunCalc(today, earth);
			sunrise = (sun.sunrise_deg + loc.m_fTimezone*15.0)/360;
			if (sunrise < vcs.shour)
			{
				today = vce;
				sun.SunCalc(today, earth);
				sunrise = (sun.sunrise_deg + loc.m_fTimezone*15.0)/360;
				if (sunrise < vce.shour)
				{
					// normal type
					vcs.NextDay();
					xml.write("\t\ttype=\"normal\"\n");
				}
				else
				{
					// ksaya
					vcs.NextDay();
					day.DayCalc(vcs, earth);
					oTithi = day.nTithi;
					oPaksa = day.nPaksa;
					oMasa = day.MasaCalc(vcs, earth);
					oYear = day.nGaurabdaYear;
					xml.write("\t\ttype=\"ksaya\"\n");
				}
			}
			else
			{
				// normal, alebo prvy den vriddhi
				today = vce;
				sun.SunCalc(today, earth);
				if ((sun.sunrise_deg + loc.m_fTimezone*15.0)/360 < vce.shour)
				{
					// first day of vriddhi type
					xml.write("\t\ttype=\"vriddhi\"\n");
				}
				else
				{
					// normal
					xml.write("\t\ttype=\"normal\"\n");
				}
			}
			xml.write("\t\tdate=\"");
	xml.write(vcs);
	xml.write("\"\n");
			xml.write("\t\totithi=\"");
	xml.write(GCStrings::GetTithiName(oTithi));
	xml.write("\"\n");
			xml.write("\t\tomasa=\"");
	xml.write(GCStrings::GetMasaName(oMasa));
	xml.write("\"\n");
			xml.write("\t\topaksa=\"");
	xml.write((oPaksa ? _T("Gaura") : _T("Krsna")));
	xml.write("\"\n");
			xml.write("\t/>\n");
			break;
		}
		else
		{
			vcStart = vcs;
			vcs.NextDay();
		}
	}

	xml.write("\t</result>\n");
	xml.write("</xml>\n");


	return 1;
}

