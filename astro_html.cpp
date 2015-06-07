/******************************************************************************************/
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/******************************************************************************************/
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
#include "GCMoonData.h"
#include "GCAyanamsha.h"
#include "GCDisplaySettings.h"

#define DAYS_TO_ENDWEEK(i) (21-(i-g_firstday_in_week))%7
#define DAYS_FROM_BEGINWEEK(i) (i-g_firstday_in_week+14)%7
#define DAY_INDEX(i) (i+g_firstday_in_week)%7

void CalcAppDay(CLocationRef &, VCTIME, TResultApp &);
int CalcCalendar(TResultCalendar &, CLocationRef &, VCTIME, int);
int CalcMasaList(TResultMasaList &, CLocationRef &, int, int);
void CalcEvents(TResultEvents &, CLocationRef &, VCTIME, VCTIME);

/******************************************************************************************/
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/******************************************************************************************/

void WriteAppDayHTML(TResultApp &app, FILE *F)
{
	DAYDATA &d = app.details;
	TString str;
	VCTIME vc = app.event;
	EARTHDATA m_earth = (EARTHDATA)app.location;

	fprintf(F, "<html><head><title>Appearance day</title>");
	fprintf(F, "<style>\n<!--\nbody {\n  font-family:Verdana;\n  font-size:11pt;\n}\n\ntd.hed {\n  font-size:11pt;\n  font-weight:bold;\n");
	fprintf(F, "  background:#aaaaaa;\n  color:white;\n  text-align:center;\n  vertical-align:center;\n  padding-left:15pt;\n  padding-right:15pt;\n");
	fprintf(F, "  padding-top:5pt;\n  padding-bottom:5pt;\n}\n-->\n</style>\n");
	fprintf(F, "</head>\n\n<body>\n");
	fprintf(F, "<h2 align=center>Appearance day Calculation</h2>");
	fprintf(F, "<table align=center><tr><td valign=top>\n\n");
	fprintf(F, "<table align=center>");
	fprintf(F, "<tr><td colspan=3 class=hed>Details</td></tr>\n");
	fprintf(F, "<tr><td colspan=2>%s</td><td> %d %s %d</td></tr>\n", GCStrings::getString(7).c_str(), vc.day, GCStrings::GetMonthAbreviation(vc.month), vc.year);
	fprintf(F, "<tr><td colspan=2>%s</td><td> %d:%02d</td></tr>\n\n", GCStrings::getString(8).c_str(), vc.GetHour(), vc.GetMinuteRound());
	fprintf(F, "<tr><td colspan=2>%s</td><td> %s</td></tr>\n", GCStrings::getString(9).c_str(), app.location.m_strName.c_str());
	fprintf(F, "<tr><td colspan=2>%s</td><td> %s</td></tr>\n", GCStrings::getString(10).c_str(), EARTHDATA::GetTextLatitude(app.location.m_fLatitude));
	fprintf(F, "<tr><td colspan=2>%s</td><td> %s</td></tr>\n", GCStrings::getString(11).c_str(), EARTHDATA::GetTextLongitude(app.location.m_fLongitude));
	fprintf(F, "<tr><td colspan=2>%s</td><td> ", GCStrings::getString(12).c_str());
	fprintf(F, TTimeZone::GetTimeZoneOffsetText(app.location.m_fTimezone));
	fprintf(F, "</td></tr>\n");
	fprintf(F, "<tr><td colspan=2>DST</td><td>N/A</td></tr>\n");
	fprintf(F, "<tr><td colspan=2>%s</td><td> %s</td></tr>\n", GCStrings::getString(13).c_str(), GCStrings::GetTithiName(d.nTithi));
	fprintf(F, "<tr><td colspan=2>%s</td><td> %.2f %%</td></tr>\n", GCStrings::getString(14).c_str(), d.nTithiElapse);
	fprintf(F, "<tr><td colspan=2>%s</td><td> %s</td></tr>\n", GCStrings::getString(15).c_str(), GCStrings::GetNaksatraName(d.nNaksatra));
	fprintf(F, "<tr><td colspan=2>%s</td><td> %.2f %%</td></tr>\n", GCStrings::getString(16).c_str(), d.nNaksatraElapse);
	fprintf(F, "<tr><td colspan=2>%s</td><td> %s</td></tr>\n", GCStrings::getString(20).c_str(), GCStrings::GetPaksaName(d.nPaksa));
	if (app.b_adhika == true)
	{
		fprintf(F, "<tr><td colspan=2>%s</td><td> %s %s</td></tr>\n", GCStrings::getString(22).c_str(), GCStrings::GetMasaName(d.nMasa), GCStrings::getString(21).c_str());
	}
	else
		fprintf(F, "<tr><td colspan=2>%s</td><td> %s</td></tr>\n", GCStrings::getString(22).c_str(), GCStrings::GetMasaName(d.nMasa));
	fprintf(F, "<tr><td colspan=2>%s</td><td> %d</td></tr>\n\n", GCStrings::getString(23).c_str(), d.nGaurabdaYear);

	fprintf(F, "</table></td><td valign=top><table>");
	fprintf(F, "<tr><td colspan=3 class=hed>%s</td></tr>\n", GCStrings::getString(24).c_str());

	//fprintf(F, "<table align=center>");
	for(int o = 0; o < TRESULT_APP_CELEBS; o++)
	{
		fprintf(F, "<tr><td>Gaurabda %3d</td><td>&nbsp;&nbsp;:&nbsp;&nbsp;</td><td><b>%d %s %d</b></td></tr>", app.celeb_gy[o] , app.celeb_date[o].day,
			GCStrings::GetMonthAbreviation(app.celeb_date[o].month), 
			app.celeb_date[o].year);
	}
	fprintf(F, "</table>");
	fprintf(F, "</td></tr></table>\n\n");
	fprintf(F, "<hr align=center width=\"50%%\">\n<p style=\'text-align:center;font-size:8pt\'>Generated by %s</p>", GCStrings::getString(130).c_str());
	fprintf(F, "</body></html>");

}

/******************************************************************************************/
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/******************************************************************************************/

int WriteEventsHTML(TResultEvents &inEvents, FILE * f)
{

	unsigned int i;
	TString str, temp;

	fprintf(f, "<html>\n<head>\n<title>Core Events</title>\n\n");
	fprintf(f, "<style>\n<!--\nbody {\n  font-family:Verdana;\n  font-size:11pt;\n}\n\ntd.hed {\n  font-size:11pt;\n  font-weight:bold;\n");
	fprintf(f, "  background:#aaaaaa;\n  color:white;\n  text-align:center;\n  vertical-align:center;\n  padding-left:15pt;\n  padding-right:15pt;\n");
	fprintf(f, "  padding-top:5pt;\n  padding-bottom:5pt;\n}\n-->\n</style>\n");
	fprintf(f, "</head>\n");
	fprintf(f, "<body>\n\n");
	fprintf(f, "<h1 align=center>Events</h1>\n<p align=center>From %d %s %d to %d %s %d.</p>\n\n", 
		inEvents.m_vcStart.day,
		GCStrings::GetMonthAbreviation(inEvents.m_vcStart.month),
		inEvents.m_vcStart.year,
		inEvents.m_vcEnd.day,
		GCStrings::GetMonthAbreviation(inEvents.m_vcEnd.month),
		inEvents.m_vcEnd.year);

	fprintf(f, "<p align=center>%s</p>\n", inEvents.m_location.m_strFullName.c_str());

	VCTIME prevd;
	int prevt = -1;

	prevd.day = 0;
	prevd.month = 0;
	prevd.year = 0;

	fprintf(f, "<table align=center><tr>\n");
	for(i = 0; i < inEvents.n_count; i++)
	{
		TDayEvent & dnr = inEvents[i];

		if (inEvents.b_sorted)
		{
			if (prevd.day != dnr.Time.day || prevd.month != dnr.Time.month || prevd.year != dnr.Time.year)
			{
				fprintf(f, "<td class=\"hed\" colspan=2>%d %s %d </td></tr>\n<tr>", dnr.Time.day, GCStrings::GetMonthAbreviation(dnr.Time.month), dnr.Time.year);
			}
			prevd = dnr.Time;
		}
		else
		{
			if (prevt != dnr.nType)
			{
				switch(dnr.nType)
				{
				case 10:
				case 11:
				case 12:
				case 13:
					if (prevt < 10 || prevt >= 14)
					{
						fprintf(f, "<td class=\"hed\" colspan=3>SUNRISE, SUNSET</td></tr>\n<tr>\n");
					}
					break;
				case 20:
					fprintf(f, "<td class=\"hed\" colspan=3>TITHIS</td></tr>\n<tr>\n");
					break;
				case 21:
					fprintf(f, "<td class=\"hed\" colspan=3>NAKSATRAS</td></tr>\n<tr>\n");
					break;
				case 22:
					fprintf(f, "<td class=\"hed\" colspan=3>SANKRANTIS</td></tr>\n<tr>\n");
					break;
				case 23:
					fprintf(f, "<td class=\"hed\" colspan=3>SUN-MOON CONJUNCTIONS</td></tr>\n<tr>\n");
					break;
				}
			}
			prevt = dnr.nType;
		}

		if (!inEvents.b_sorted)
		{
			fprintf(f, "<td>%d %s %d </td>", dnr.Time.day, GCStrings::GetMonthAbreviation(dnr.Time.month), dnr.Time.year);
		}

		switch(dnr.nType)
		{
		case CCTYPE_S_ARUN:
			fprintf(f, "<td>Arunodaya</td><td>%02d:%02d:%02d</td></tr><tr>\n",
				dnr.Time.GetHour(), dnr.Time.GetMinute(), dnr.Time.GetSecond());
			break;
		case CCTYPE_S_RISE:
			fprintf(f, "<td>Sunrise</td><td>%02d:%02d:%02d</td></tr><tr>\n",
				dnr.Time.GetHour(), dnr.Time.GetMinute(), dnr.Time.GetSecond());
			break;
		case CCTYPE_S_NOON:
			fprintf(f, "<td>Noon</td><td>%02d:%02d:%02d</td></tr><tr>\n",
				dnr.Time.GetHour(), dnr.Time.GetMinute(), dnr.Time.GetSecond());
			break;
		case CCTYPE_S_SET:
			fprintf(f, "<td>Sunset</td><td>%02d:%02d:%02d</td></tr><tr>\n",
				dnr.Time.GetHour(), dnr.Time.GetMinute(), dnr.Time.GetSecond());
			break;
		case CCTYPE_TITHI:
			fprintf(f, "<td>%s Tithi</td><td>%02d:%02d:%02d</td></tr><tr>\n", 
				GCStrings::GetTithiName(dnr.nData),
				dnr.Time.GetHour(), dnr.Time.GetMinute(), dnr.Time.GetSecond());
			break;
		case CCTYPE_NAKS:
			fprintf(f, "<td>%s Naksatra</td><td>%02d:%02d:%02d</td></tr><tr>\n", 
				GCStrings::GetNaksatraName(dnr.nData),
				dnr.Time.GetHour(), dnr.Time.GetMinute(), dnr.Time.GetSecond());
			break;
		case CCTYPE_SANK:
			fprintf(f, "<td>%s Sankranti</td><td>%02d:%02d:%02d</td></tr><tr>\n", 
				GCStrings::GetSankrantiName(dnr.nData)
				, dnr.Time.GetHour(), dnr.Time.GetMinute(), dnr.Time.GetSecond());
			break;
		case CCTYPE_CONJ:
			fprintf(f, "<td>Conjunction in %s rasi</td><td>%02d:%02d:%02d</td></tr><tr>\n", 
				GCStrings::GetSankrantiName(dnr.nData)
				, dnr.Time.GetHour(), dnr.Time.GetMinute(), dnr.Time.GetSecond());
			break;
		case CCTYPE_KALA_START:
			fprintf(f, "<td>");
			fprintf(f, GCStrings::GetKalaName((KalaType)dnr.nData));
			fprintf(f, " starts</td>");
			fprintf(f, "<td>");
			fprintf(f, dnr.Time.c_str());
			fprintf(f, "</td></tr><tr>");
			break;
		case CCTYPE_KALA_END:
			fprintf(f, "<td>");
			fprintf(f, GCStrings::GetKalaName((KalaType)dnr.nData));
			fprintf(f, " ends</td>");
			fprintf(f, "<td>");
			fprintf(f, dnr.Time.c_str());
			fprintf(f, "</td></tr><tr>");
			break;
		default:
			break;
		}
	}

	fprintf(f, "</tr></table>\n");
	fprintf(f, "<hr align=center width=\"50%%\">\n<p align=center>Generated by %s</p>", GCStrings::getString(130).c_str());
	fprintf(f, "</body>\n</html>\n");

	return 1;
}

/******************************************************************************************/
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/******************************************************************************************/

int WriteMasaListHTML(TResultMasaList &mlist, FILE * f)
{
	TString stt;
	TString stt2;

	fprintf(f, "<html>\n<head>\n<title>Masa List</title>\n\n");
	fprintf(f, "<style>\n<!--\nbody {\n  font-family:Verdana;\n  font-size:11pt;\n}\n\ntd.hed {\n  font-size:11pt;\n  font-weight:bold;\n");
	fprintf(f, "  background:#aaaaaa;\n  color:white;\n  text-align:center;\n  vertical-align:center;\n  padding-left:15pt;\n  padding-right:15pt;\n");
	fprintf(f, "  padding-top:5pt;\n  padding-bottom:5pt;\n}\n-->\n</style>\n");
	fprintf(f, "</head>\n");
	fprintf(f, "<body>\n\n");

	fprintf(f, "<p style=\'text-align:center\'><span style=\'font-size:14pt\'>Masa List</span></br>%s: %s</p>\n", GCStrings::getString(40).c_str(), mlist.m_location.m_strFullName.c_str());
	fprintf(f, "<p align=center>%s %d %s %d %s %d %s %d</p>\n", GCStrings::getString(41).c_str(), mlist.vc_start.day, GCStrings::GetMonthAbreviation(mlist.vc_start.month), mlist.vc_start.year
		, GCStrings::getString(42).c_str(), mlist.vc_end.day, GCStrings::GetMonthAbreviation(mlist.vc_end.month), mlist.vc_end.year);
	fprintf(f, "<hr width=\"50%%\">");

	fprintf(f, "<table align=center>");
	fprintf(f, "<tr><td class=\"hed\" style=\'text-align:left\'>MASA NAME&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td><td class=\"hed\">START</td><td class=\"hed\">END</td></tr>");
	int i;
	for(i = 0; i < mlist.n_countMasa; i++)
	{
		fprintf(f, "<tr>");
		fprintf(f, "<td>%s %d&nbsp;&nbsp;&nbsp;&nbsp;</td>", GCStrings::GetMasaName(mlist.arr[i].masa), mlist.arr[i].year);
		fprintf(f, "<td>%d %s %d</td>", mlist.arr[i].vc_start.day, GCStrings::GetMonthAbreviation(mlist.arr[i].vc_start.month), mlist.arr[i].vc_start.year);
		fprintf(f, "<td>%d %s %d</td>", mlist.arr[i].vc_end.day, GCStrings::GetMonthAbreviation(mlist.arr[i].vc_end.month), mlist.arr[i].vc_end.year);
		fprintf(f, "</tr>");
	}
	fprintf(f, "</table>");
	fprintf(f, "<hr width=\"50%%\">\n<p align=center>Generated by %s</p>", GCStrings::getString(130).c_str());
	fprintf(f, "</body></html>");
	return 1;
}

/******************************************************************************************/
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/******************************************************************************************/

int WriteCalendarHTML(TResultCalendar &daybuff, FILE * fout)
{
	int k;
	TString str, st;
	TString daystr;
	VCTIME date;
	TFileXml xml;
	VAISNAVADAY * pvd;
	int nPrevMasa = -1;
	int nPrevPaksa = -1;

	xml.initWithFile(fout);

	xml.write("<html><head><title>\n");
//	xml.write("\t<request name=\"Calendar\" version=\"");
	xml.write(GCStrings::getString(130));
	xml.write("\">\n");
//	xml.write("\t\t<arg name=\"longitude\" val=\"");
	xml.write(daybuff.m_Location.m_fLongitude);
	xml.write("\" />\n");
//	xml.write("\t\t<arg name=\"latitude\" val=\"");
	xml.write(daybuff.m_Location.m_fLatitude);
	xml.write("\" />\n");
//	xml.write("\t\t<arg name=\"timezone\" val=\"");
	xml.write(daybuff.m_Location.m_fTimezone);
	xml.write("\" />\n");
//	xml.write("\t\t<arg name=\"startdate\" val=\"");
	xml.write(daybuff.m_vcStart);
	xml.write("\" />\n");
//	xml.write("\t\t<arg name=\"daycount\" val=\"");
	xml.write(daybuff.m_vcCount);
	xml.write("\" />\n");
//	xml.write("\t\t<arg name=\"dst\" val=\"");
	xml.write(daybuff.m_Location.m_nDST);
	xml.write("\" />\n");
//	xml.write("\t</request>\n";
//	xml.write("\t<result name=\"Calendar\">\n";
//	if (daybuff.m_Location.m_nDST > 0)
//		xml.write("\t<dstsystem name=\"");
	xml.write(TTimeZone::GetTimeZoneName(daybuff.m_Location.m_nDST));
	xml.write("\" />\n");

	xml.write("Calendar ");
	xml.write(daybuff.m_vcStart.year);
	xml.write("</title>");
	xml.write("<style>\n");
	xml.write("<!--\nbody {\n");
	xml.write("  font-family:Verdana;\n");
	xml.write("  font-size:11pt;\n}\n\n");
	xml.write("td.hed {\n");
	xml.write("  font-family:Verdana;\n");
	xml.write("  font-size:9pt;\n");
	xml.write("  font-weight:bold;\n");
	xml.write("  background:#aaaaaa;\n");
	xml.write("  color:white;\n");
	xml.write("  text-align:center;\n");
	xml.write("  vertical-align:center;\n  padding-left:15pt;\n  padding-right:15pt;\n");
	xml.write("  padding-top:5pt;\n  padding-bottom:5pt;\n}\n-->\n</style>\n");
	xml.write("</head>\n<body>");

	for (k = 0; k < daybuff.m_vcCount; k++)
	{
		pvd = daybuff.GetDay(k);
		if (pvd)
		{
			if (nPrevMasa != pvd->astrodata.nMasa)
			{
				if (nPrevMasa != -1)
					xml.write("\t</table>\n");
				xml.write("<p style=\'text-align:center;font-weight:bold\'><span style =\'font-size:14pt\'>");
	xml.write(GCStrings::GetMasaName(pvd->astrodata.nMasa));
	xml.write(" Masa");
				if (nPrevMasa == ADHIKA_MASA)
					xml.write(" ");
	xml.write(GCStrings::getString(109));
				xml.write("</span>");
				xml.write("<br><span style=\'font-size:10pt;\'>Gaurabda ");
	xml.write(pvd->astrodata.nGaurabdaYear);
				xml.write("<br>");
	xml.write(daybuff.m_Location.m_strFullName);
	xml.write("</font>");
				xml.write("</span></p>\n<table align=center>");
				xml.write("<tr><td  class=\"hed\"colspan=2>");
				xml.write("DATE</td><td class=\"hed\">TITHI</td><td class=\"hed\">P</td><td class=\"hed\">NAKSATRA</td><td class=\"hed\">YOGA</td><td class=\"hed\">FAST</td></tr>");
			}

			nPrevMasa = pvd->astrodata.nMasa;

			if (((pvd->ekadasi_parana) || (pvd->festivals.GetLength() > 0) ||
				(pvd->sankranti_zodiac >= 0) || (GCDisplaySettings::getValue(7) == 1 && pvd->was_ksaya) ||
				(GCDisplaySettings::getValue(8) == 1 && pvd->is_vriddhi) ||
				((GCDisplaySettings::getValue(14) == 1) && (pvd->nCaturmasya & CMASYA_PRAT_MASK)) ||
				((GCDisplaySettings::getValue(13) == 1) && (pvd->nCaturmasya & CMASYA_PURN_MASK)) ||
				((GCDisplaySettings::getValue(15) == 1) && (pvd->nCaturmasya & CMASYA_EKAD_MASK))) == FALSE
				&& (GCDisplaySettings::getValue(20) != 0))
					 continue;

			// date data
			xml.write("<tr>");
			xml.write("<td>");
	xml.write(pvd->date);
	xml.write("</td><td>");
			GCStrings::getString(pvd->date.dayOfWeek).Left(2, st);
			xml.write(st.c_str());
	xml.write("</td>\n");

			// sunrise data
			//xml.write("\t\t<sunrise time=\"");
	xml.write(pvd->astrodata.sun.rise);
	xml.write("\">\n");

			//xml.write("\t\t\t<tithi name=\"");
			xml.write("<td>\n");
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
			xml.write("</td>\n");

			//str.Format("\" elapse=\"%.1f\" index=\"%d\"/>\n"
			//	,pvd->astrodata.nTithiElapse, pvd->astrodata.nTithi % 30 + 1 );
			//xml.write(str;

			str.Format("<td>%c</td>\n", GCStrings::GetPaksaChar(pvd->astrodata.nPaksa) );
			xml.write(str);

			str.Format("<td>%s</td>\n", GCStrings::GetNaksatraName(pvd->astrodata.nNaksatra));
			xml.write(str);

			str.Format("<td>%s</td>\n", GCStrings::GetYogaName(pvd->astrodata.nYoga) );
			xml.write(str);


			xml.write("<td>");
			xml.write(((pvd->nFastType!=FAST_NULL)?"FAST</td>":"</td>"));
			//xml.write("\t\t</sunrise>\n");

			//xml.write("\t\t<dst offset=\"");
			xml.write(pvd->nDST);
			xml.write("\" />\n");
			// arunodaya data
			//xml.write("\t\t<arunodaya time=\"");
			xml.write(pvd->astrodata.sun.arunodaya);
			xml.write("\">\n");
			//xml.write("\t\t\t<tithi name=\"");
			xml.write(GCStrings::GetTithiName(pvd->astrodata.nTithiArunodaya));
			xml.write("\" />\n");
			//xml.write("\t\t</arunodaya>\n");

			str.Empty();

			//xml.write("\t\t<noon time=\"");
			xml.write(pvd->astrodata.sun.noon);
			xml.write("\" />\n");

			//xml.write("\t\t<sunset time=\"");
			xml.write(pvd->astrodata.sun.set);
			xml.write("\" />\n");

			// moon data
			//xml.write("\t\t<moon rise=\"");
			xml.write(pvd->moonrise);
			xml.write("\" set=\"");
			xml.write(pvd->moonset);
			xml.write("\" />\n");

			xml.write("</tr>\n\n<tr>\n<td></td><td></td><td colspan=4>");
			if (pvd->ekadasi_parana)
			{
				double h1, m1, h2, m2;
				m1 = modf(pvd->eparana_time1, &h1);
				if (pvd->eparana_time2 >= 0.0)
				{
					m2 = modf(pvd->eparana_time2, &h2);
					str.Format("Break fast %02d:%02d - %02d:%02d %s<br>\n", int(h1), int(m1*60), int(h2), int(m2*60),
						pvd->nDST == 1 ? "(DST applied)" : "(Local Time)");
				}
				else
				{
					str.Format("Break fast after %02d:%02d<br>\n", int(h1), int(m1*60) );
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
						str.Format("%s<br>\n", str2.c_str());
						xml.write(str);
					}
				}
			}

			if (pvd->nFastType != FAST_NULL)
			{
				switch (pvd->nFastType)
				{
				case FAST_EKADASI:
					//xml.write("\t\t<fast type=\"Fasting for ");
					//xml.write(pvd->ekadasi_vrata_name;
					//xml.write("\" mark=\"*\"/>\n");
					//break;
				case FAST_NOON:
					//xml.write("\t\t<fast type=\"(Fast till noon)\"  mark=\"*\"/>\n");
					//xml.write("\t\t<fast type=\"\" mark=\"*\" />\n");
					//break;
				case FAST_SUNSET:
					//xml.write("\t\t<fast type=\"(Fast till sunset)\" mark=\"*\" />\n");
					//xml.write("\t\t<fast type=\"\" mark=\"*\" />\n");
					//break;
				case FAST_MOONRISE:
					//xml.write("\t\t<fast type=\"(Fast till moonrise)\" mark=\"*\" />\n");
					//xml.write("\t\t<fast type=\"\" mark=\"*\" />\n");
					//break;
				case FAST_DUSK:
					//xml.write("\t\t<fast type=\"(Fast till dusk)\" mark=\"*\" />\n");
					//xml.write("\t\t<fast type=\"\" mark=\"*\" />\n");
					//break;
				case FAST_MIDNIGHT:
					//xml.write("\t\t<fast type=\"(Fast till midnight)\" mark=\"*\" />\n");
					//xml.write("\t\t<fast type=\"\" mark=\"*\" />\n");
					break;
				default:
					//xml.write("\t\t<fast type=\"\" mark=\"\" />\n");
					break;
				}
			}

			if (pvd->sankranti_zodiac >= 0)
			{
				//double h1, m1, s1;
				//m1 = modf(pvd->sankranti_day.shour*24, &h1);
//				s1 = modf(m1*60, &m1);
				str.Format("<font color=\"blue\">%s Sankranti (<i>%d %s %d  %02d:%02d:%02d</i>)</font><br>\n"
					, GCStrings::GetSankrantiName(pvd->sankranti_zodiac), pvd->sankranti_day.day,
					GCStrings::GetMonthAbreviation(pvd->sankranti_day.month), pvd->sankranti_day.year,
					pvd->sankranti_day.GetHour()
					, pvd->sankranti_day.GetMinute(), pvd->sankranti_day.GetSecond());
				xml.write(str);
			}

			if (GCDisplaySettings::getValue(7) == 1 && pvd->was_ksaya)
			{
				double h1, m1, h2, m2;
				VCTIME ksayaDate;
				xml.write("Previous tithi is ksaya from ");
				m1 = modf(pvd->ksaya_time1*24, &h1);
				ksayaDate = pvd->date;
				if (pvd->ksaya_day1 < 0.0)
					ksayaDate.PreviousDay();
				str.Format("%d %s, %02d:%02d", ksayaDate.day, GCStrings::GetMonthAbreviation(ksayaDate.month), int(h1), int(m1*60));
				xml.write(str);

				m2 = modf(pvd->ksaya_time2*24, &h2);
				str.Format("to %d %s, %02d:%02d<br>\n", ksayaDate.day, GCStrings::GetMonthAbreviation(ksayaDate.month), int(h2), abs(int(m2*60)));
				xml.write(str);
			}

			if (GCDisplaySettings::getValue(8) == 1 && pvd->is_vriddhi)
			{
				xml.write("Second day of vriddhi tithi<br>\n");
			}

			if ((GCDisplaySettings::getValue(14) == 1) && (pvd->nCaturmasya & CMASYA_PRAT_MASK))
			{
				xml.write(GCStrings::getString(107 + ((pvd->nCaturmasya & CMASYA_PRAT_MASK_DAY) >> 8)
							   + ((pvd->nCaturmasya & CMASYA_PRAT_MASK_MASA) >> 10)).c_str());
				xml.write("[PRATIPAT SYSTEM]<br>\n");
				if ((pvd->nCaturmasya & CMASYA_PRAT_MASK_DAY) == 0x100)
				{
					xml.write(GCStrings::getString(110 + ((pvd->nCaturmasya & CMASYA_PRAT_MASK_MASA) >> 10)).c_str());
				}
			}

			if ((GCDisplaySettings::getValue(13) == 1) && (pvd->nCaturmasya & CMASYA_PURN_MASK))
			{
				xml.write(GCStrings::getString(107 + (pvd->nCaturmasya & CMASYA_PURN_MASK_DAY)
							   + ((pvd->nCaturmasya & CMASYA_PURN_MASK_MASA) >> 2)).c_str());
				xml.write("[PURNIMA SYSTEM]<br>");
				if ((pvd->nCaturmasya & CMASYA_PURN_MASK_DAY) == 0x1)
				{
					xml.write(GCStrings::getString(110 + ((pvd->nCaturmasya & CMASYA_PURN_MASK_MASA) >> 2)).c_str());
				}
			}

			if ((GCDisplaySettings::getValue(15) == 1) && (pvd->nCaturmasya & CMASYA_EKAD_MASK))
			{
				xml.write(GCStrings::getString(107 + ((pvd->nCaturmasya & CMASYA_EKAD_MASK_DAY) >> 16)
							   + ((pvd->nCaturmasya & CMASYA_EKAD_MASK_MASA) >> 18)).c_str());
				xml.write("[EKADASI SYSTEM]<br>");
				if ((pvd->nCaturmasya & CMASYA_EKAD_MASK_DAY) == 0x10000)
				{
					xml.write(GCStrings::getString(110 + ((pvd->nCaturmasya & CMASYA_EKAD_MASK_MASA) >> 18)).c_str());
				}
			}
			xml.write("\t</tr>\n\n");

		}
		date.shour = 0;
		date.NextDay();
	}
	xml.write("\t</table>\n\n");

	xml.write("<hr align=center width=\"65%%\">\n");
	xml.write("<p align=center>Generated by ");
	xml.write(GCStrings::getString(130));
	xml.write("</p>\n");
	
	xml.write("</body>\n</html>\n");

	return 1;
}

/******************************************************************************************/
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/******************************************************************************************/

int WriteCalendarHtmlTable(TResultCalendar &daybuff, FILE * fout)
{
	int g_firstday_in_week = GCDisplaySettings::getValue(40);
	int k, y, lwd;
	TString str, st;
	VCTIME date;
	TFileXml xml;
	VAISNAVADAY * pvd;
	int nPrevMasa = -1;
	int prevMas = -1;
	int brw = 0;

	// first = 1
	//int i_end[7] = {0, 6, 5, 4, 3, 2, 1}; //(6-(i-first))%7
	//int i_beg[7] = {6, 0, 1, 2, 3, 4, 5}; //(i-first)%7
	xml.initWithFile(fout);

	xml.write("<html>\n<head>\n<title>Calendar ");
	xml.write(daybuff.m_vcStart);
	xml.write("</title>\n");

	xml.write("<style>\n<!--\np.MsoNormal, li.MsoNormal, div.MsoNormal\n	{mso-style-parent:\"\";");
	xml.write("margin:0in;margin-bottom:.0001pt;mso-pagination:widow-orphan;font-size:8.0pt;font-family:Arial;");
	xml.write("mso-fareast-font-family:Arial;}");
	xml.write("p.month\n{mso-style-name:month;\nmso-margin-top-alt:auto;\nmargin-right:0in;\nmso-margin-bottom-alt:auto;\nmargin-left:0in;\nmso-pagination:widow-orphan;\nfont-size:17.0pt;font-family:Arial;mso-fareast-font-family:Arial;}\n");
	xml.write(".text\n{mso-style-name:text;\nmso-margin-top-alt:auto;\nmargin-right:0in;\nmso-margin-bottom-alt:auto;\nmargin-left:0in;\n	mso-pagination:widow-orphan;\nfont-size:6.0pt;\nmso-bidi-font-size:6.0pt;\nfont-family:Arial;	mso-fareast-font-family:\"Arial\";mso-bidi-font-family:\"Arial\";}\n");
	xml.write(".tnote\n{mso-style-name:text;\nmso-margin-top-alt:auto;\nmargin-right:0in;\nmso-margin-bottom-alt:auto;\nmargin-left:0in;\n	mso-pagination:widow-orphan;\nfont-size:7.0pt;\nmso-bidi-font-size:7.0pt;\nfont-family:Arial;	mso-fareast-font-family:Arial;mso-bidi-font-family:Arial;}\n");
	xml.write(".tithiname\n{mso-style-name:text;\nmso-margin-top-alt:auto;\nmargin-right:0in;\nmso-margin-bottom-alt:auto;\nmargin-left:0in;\n	mso-pagination:widow-orphan;\nfont-size:8.0pt;\nmso-bidi-font-size:8.0pt;\nfont-family:Arial;	mso-fareast-font-family:\"Arial\";mso-bidi-font-family:\"Arial\";}\n");
	xml.write(".dayt\n	{mso-style-name:dayt;\nfont-size:12.0pt;\nmso-ansi-font-size:12.0pt;\nfont-family:Arial;\nmso-ascii-font-family:Arial;\nmso-hansi-font-family:Arial;\nfont-weight:bold;\nmso-bidi-font-weight:normal;}\n");
	xml.write("span.SpellE\n{mso-style-name:\"\";\nmso-spl-e:yes;}\n");
	xml.write("span.GramE\n{mso-style-name:\"\";\nmso-gram-e:yes;}\n");
	xml.write("-->\n</style>\n");

	xml.write("</head>\n\n<body>\n\n");
/*	xml.write("\t<request name=\"Calendar\" version=\"");
	xml.write(GCStrings::getString(130]);
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
	xml.write("\t</request>\n";
	xml.write("\t<result name=\"Calendar\">\n";
	if (daybuff.m_Location.m_nDST > 0)
		xml.write("\t<dstsystem name=\"");
	xml.write(TTimeZone::GetTimeZoneName(daybuff.m_Location.m_nDST));
	xml.write("\" />\n");
*/
	for (k = 0; k < daybuff.m_vcCount; k++)
	{
		pvd = daybuff.GetDay(k);
		if (pvd)
		{
			BOOL bSemicolon = false;
			BOOL bBr = false;
			lwd = pvd->date.dayOfWeek;
			if (nPrevMasa != pvd->date.month)
			{
				int y;
				if (nPrevMasa != -1)
				{
					for(y = 0; y < DAYS_TO_ENDWEEK(lwd); y++)
					{
						xml.write("<td style=\'border:solid windowtext 1.0pt;mso-border-alt:solid windowtext .5pt;padding:3.0pt 3.0pt 3.0pt 3.0pt\'>&nbsp;</td>");
					}
					xml.write("</tr></table>\n<p>&nbsp;</p>");
				}
				xml.write("\n<table width=\"100%\" border=0 frame=bottom cellspacing=0 cellpadding=0><tr><td width=\"60%\"><p class=month>");
				xml.write(GCStrings::getString(pvd->date.month + 759).c_str());
				xml.write(" ");
				xml.write(pvd->date.year);
				xml.write("</p></td><td><p class=tnote align=right>");
				xml.write(daybuff.m_Location.m_strName);
				xml.write("<br>Timezone: ");
				xml.write(TTimeZone::GetTimeZoneName(daybuff.m_Location.m_nDST));
				xml.write("</p>");
				xml.write("</td></tr></table><hr>");
				nPrevMasa = pvd->date.month;
				xml.write("\n<table width=\"100%\" bordercolor=black cellpadding=0 cellspacing=0>\n<tr>\n");
				for(y = 0; y < 7; y++)
				{
					xml.write("<td width=\"14%\" align=center style=\'font-size:10.0pt;border:none\'>");
					xml.write(GCStrings::getString(DAY_INDEX(y)).c_str());
					xml.write("</td>\n");
				}
				xml.write("<tr>\n");
				for(y=0; y < DAYS_FROM_BEGINWEEK(pvd->date.dayOfWeek); y++)
					xml.write("<td style=\'border:solid windowtext 1.0pt;mso-border-alt:solid windowtext .5pt;padding:3.0pt 3.0pt 3.0pt 3.0pt\'>&nbsp;</td>");
			}
			else
			{
				if (pvd->date.dayOfWeek == g_firstday_in_week)
					xml.write("<tr>\n");
			}

			// date data
			xml.write("\n<td valign=top style=\'border:solid windowtext 1.0pt;mso-border-alt:solid windowtext .5pt;padding:3.0pt 3.0pt 3.0pt 3.0pt\' bgcolor=\"");
			switch (pvd->nFastType)
			{
			case FAST_EKADASI:
				xml.write("#ffffbb");
				break;
			case FAST_NOON:
			case FAST_SUNSET:
			case FAST_MOONRISE:
			case FAST_DUSK:
			case FAST_MIDNIGHT:
			case FAST_DAY:
				xml.write("#bbffbb");
				break;
			default:
				xml.write("white");
				break;
			}
			xml.write("\"><table width=\"100%\" border=0><tr><td><p class=text><span class=dayt>");
			xml.write(pvd->date.day);
			xml.write("</span></td><td>");

			// sunrise data
//			xml.write("\t\t<sunrise time=\"");
			xml.write(pvd->astrodata.sun.rise);
			xml.write("\">\n");

//			xml.write("hi name=\"";
			xml.write("<span class=\"tithiname\">");
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
			xml.write("</span>");
			xml.write("</td></tr></table>\n");
			brw = 0;
			xml.write("<span class=\"text\">\n");
//			str.Format("\" elapse=\"%.1f\" index=\"%d\"/>\n"
//				,pvd->astrodata.nTithiElapse, pvd->astrodata.nTithi % 30 + 1 );
//			xml.write(str;

//			str.Format("\t\t\t<naksatra name=\"%s\" elapse=\"%.1f\" />\n"
//				,GetNaksatraName(pvd->astrodata.nNaksatra), pvd->astrodata.nNaksatraElapse );
//			xml.write(str;

//			str.Format("\t\t\t<yoga name=\"%s\" />\n", GetYogaName(pvd->astrodata.nYoga) );
//			xml.write(str;

//			str.Format("\t\t\t<paksa id=\"%c\" name=\"%s\"/>\n", GetPaksaChar(pvd->astrodata.nPaksa), GetPaksaName(pvd->astrodata.nPaksa) );
//			xml.write(str;

//			xml.write("\t\t</sunrise>\n";

//			xml.write("\t\t<dst offset=\"");
			xml.write(pvd->nDST);
			xml.write("\" />\n");
			// arunodaya data
//			xml.write("\t\t<arunodaya time=\"");
			xml.write(pvd->astrodata.sun.arunodaya);
			xml.write("\">\n");
//			xml.write("\t\t\t<tithi name=\"");
			xml.write(GCStrings::GetTithiName(pvd->astrodata.nTithiArunodaya));
			xml.write("\" />\n");
//			xml.write("\t\t</arunodaya>\n";

			str.Empty();

//			xml.write("\t\t<noon time=\"");
	xml.write(pvd->astrodata.sun.noon);
	xml.write("\" />\n");

//			xml.write("\t\t<sunset time=\"");
	xml.write(pvd->astrodata.sun.set);
	xml.write("\" />\n");

			// moon data
//			xml.write("\t\t<moon rise=\"");
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
					str.Format("Break fast %02d:%02d-%02d:%02d", int(h1), int(m1*60), int(h2), int(m2*60));
				}
				else
				{
					str.Format("Break fast after %02d:%02d", int(h1), int(m1*60) );
				}
				if (brw)
					xml.write("<br>\n");
				brw = 1;
				xml.write(str);
				bBr = true;
				bSemicolon = true;
			}
			str.Empty();

			if (pvd->festivals.GetLength() > 0)
			{
				int i = pvd->GetHeadFestival();
				int nFestClass;
				TString str2;
				if (brw)
					xml.write("<br>\n");
				brw = 1;
				while(pvd->GetNextFestival(i, str2))
				{
					if (str2.GetLength() > 1)
					{
						nFestClass = pvd->GetFestivalClass(str2);
//						str.Format("", str2.c_str(), nFestClass);
						if (bSemicolon)
							xml.write("; ");
						xml.write(str2.c_str());
						bSemicolon=true;
						bBr=false;
					}
				}
			}

			if (pvd->sankranti_zodiac >= 0)
			{
				str.Format("<i>%s Sankranti</i>\n", GCStrings::GetSankrantiName(pvd->sankranti_zodiac));
				if (brw)
					xml.write("<br>\n");
				brw = 1;
				xml.write(str);
				bBr = true;
			}

/*			if (pvd->was_ksaya)
			{
				double h1, m1, h2, m2;
				m1 = modf(pvd->ksaya_time1*24, &h1);
				m2 = modf(pvd->ksaya_time2*24, &h2);
				str.Format("\t\t<ksaya from=\"%02d:%02d\" to=\"%02d:%02d\" />\n", int(h1), abs(int(m1*60)), int(h2), abs(int(m2*60)));
				xml.write(str;
			}

			if (pvd->is_vriddhi)
			{
				xml.write("\t\t<vriddhi sd=\"yes\" />\n";
			}
			else
			{
				xml.write("\t\t<vriddhi sd=\"no\" />\n";
			}
*/
/*			if (pvd->nCaturmasya & CMASYA_PURN_MASK)
			{
				xml.write("\t\t<caturmasya day=\"" 
					<< (((pvd->nCaturmasya & CMASYA_PURN_MASK_DAY)) > 1 ? "last" : "first")
					<< " day of \" month=\"" 
					<< int((pvd->nCaturmasya & CMASYA_PURN_MASK_MASA) >> 4) 
					<< "\" system=\"PURNIMA\" />\n";
			}

			if (pvd->nCaturmasya & CMASYA_PRAT_MASK)
			{
				xml.write("\t\t<caturmasya day=\"" 
					<< (((pvd->nCaturmasya & CMASYA_PRAT_MASK_DAY) >> 8) > 1 ? "last" : "first")
					<< "\" month=\"" 
					<< int((pvd->nCaturmasya & CMASYA_PRAT_MASK_MASA) >> 12)
					<< "\" system=\"PRATIPAT\" />\n";
			}

			if (pvd->nCaturmasya & CMASYA_EKAD_MASK)
			{
				str.Format("\t<caturmasya day=\"%s\" month=\"%d\" system=\"EKADASI\" />\n"
					, ((pvd->nCaturmasya & CMASYA_EKAD_MASK_DAY) >> 16) > 1 ? "last" : "first"
					, int((pvd->nCaturmasya & CMASYA_EKAD_MASK_MASA) >> 20));
				xml.write(str;
			}
*/
			if (prevMas != pvd->astrodata.nMasa)
			{
				if (brw)
					xml.write("<br>\n");
				brw = 1;
				xml.write("<b>[");
				xml.write(GCStrings::GetMasaName(pvd->astrodata.nMasa));
				xml.write(" Masa]</b>");
				prevMas = pvd->astrodata.nMasa;
			}
			xml.write("</span>");
			xml.write("</td>\n\n");

		}
		date.shour = 0;
		date.NextDay();
	}
/*	for(y = (pvd->date.dayOfWeek + 6)%7; y < 7; y++)
	{
		xml.write("<td></td>");
	}
*/
	for(y = 1; y < DAYS_TO_ENDWEEK(lwd); y++)
	{
		xml.write("<td style=\'border:solid windowtext 1.0pt;mso-border-alt:solid windowtext .5pt;padding:3.0pt 3.0pt 3.0pt 3.0pt\'>&nbsp;</td>");
	}
	xml.write("</tr>\n</table>\n");

	
	xml.write("</body>\n</html>\n");

	return 1;
}

const char * GetDayHumanTitle(VCTIME & vc)
{
	VCTIME tod;
	int n;

	tod.Today();
	n = int(tod.GetJulian() - vc.GetJulian());
	if (n == -1)
		return "[Tomorrow]";
	if (n == 1)
		return "[Yesterday]";
	if (n == 0)
		return "[Today]";
	return "";
}

const char * gcal_html_getDayBackground(VAISNAVADAY * p)
{
	if (p == NULL)
		return "white";
	if (p->nFastType == FAST_EKADASI)
		return "#FFFFBB";
	if (p->nFastType != 0)
		return "#BBFFBB";
	return "white";
}

/******************************************************************************************/
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/******************************************************************************************/


void WriteTodayInfoHTML(VCTIME vc, CLocationRef & loc, FILE * f)
{
	TString str2, str3, str4;

	int k = 0, nFestClass;

	TResultCalendar db;

	VCTIME vc2 = vc;
	vc2.tzone = loc.m_fTimezone;
	vc2.PreviousDay();
	vc2.PreviousDay();
	vc2.PreviousDay();
	vc2.PreviousDay();
	db.CalculateCalendar(loc, vc2, 9);

	int i = db.FindDate(vc);
	VAISNAVADAY * p = db.GetDay(i);

	if (p == NULL)
		return;

	fprintf(f, "<html>\n<head>\n<title></title>");
	fprintf(f, "<style>\n<!--\nbody {\n  font-family:Verdana;\n  font-size:9.5pt;\n}\n\ntd.hed {\n  font-size:9.5pt;\n  font-weight:bold;\n");
	fprintf(f, "  background:#aaaaaa;\n  color:white;\n  text-align:center;\n  vertical-align:center;\n  padding-left:15pt;\n  padding-right:15pt;\n");
	fprintf(f, "  padding-top:5pt;\n  padding-bottom:5pt;\n}\n-->\n</style>\n");
	fprintf(f, "</head>\n");
	fprintf(f, "<body>\n");
	fprintf(f, "<h2>%d %s %d  %s</h2>\n", vc.day, GCStrings::GetMonthAbreviation(vc.month), vc.year, GetDayHumanTitle(vc));
	fprintf(f, "<h4>%s</h4>\n", loc.m_strFullName.c_str());
	fprintf(f, "<p>  %s, %s %s<br>  %s %s, %d Gaurabda</p>",
		GCStrings::GetTithiName(p->astrodata.nTithi), GCStrings::GetPaksaName(p->astrodata.nPaksa), GCStrings::getString(20).c_str(), 
		GCStrings::GetMasaName(p->astrodata.nMasa), GCStrings::getString(22).c_str(), p->astrodata.nGaurabdaYear);

	int prevCountFest = 0;

	if (p->ekadasi_parana)
	{
		if (prevCountFest == 0)
			fprintf(f, "<table style=\'border-width:1pt;border-color:black;border-style:solid\'><tr><td style=\'font-size:9pt;background:%s;padding-left:25pt;padding-right:35pt;padding-top:15pt;padding-bottom:15pt;vertical-align:center\'>\n", gcal_html_getDayBackground(p));
		else
			fprintf(f, "<br>");
		p->GetTextEP(str2);
		fprintf(f, "<span style=\'color:red;font-weight:bold\'>%s</span>", str2.c_str());
		prevCountFest++;
	}

	// adding mahadvadasi
	// adding spec festivals

	if (p->festivals.GetLength() > 0)
	{
		if (prevCountFest == 0)
			fprintf(f, "<table style=\'border-width:1pt;border-color:black;border-style:solid\'><tr><td style=\'font-size:9pt;background:%s;padding-left:25pt;padding-right:35pt;padding-top:15pt;padding-bottom:15pt;vertical-align:center\'>\n", gcal_html_getDayBackground(p));
		int i = p->GetHeadFestival();
		while(p->GetNextFestival(i, str2))
		{
			if (str2.GetLength() > 1)
			{
				nFestClass = p->GetFestivalClass(str2);
				if (nFestClass < 0 || GCDisplaySettings::getValue(22 + nFestClass) == 1)
				{
					if (prevCountFest > 0)
						fprintf(f, "<br>");
					fprintf(f, "%s", str2.c_str());
					prevCountFest++;
				}
			}
		}
	}


	if (GCDisplaySettings::getValue(16) == 1 && p->sankranti_zodiac >= 0)
	{
		if (prevCountFest == 0)
			fprintf(f, "<table style=\'border-width:1pt;border-color:black;border-style:solid\'><tr><td style=\'font-size:9pt;background:%s;padding-left:25pt;padding-right:35pt;padding-top:15pt;padding-bottom:15pt;vertical-align:center\'>\n", gcal_html_getDayBackground(p));
		else
			fprintf(f, "<br>");
		//double h1, m1;
		//m1 = modf(p->sankranti_day.shour*24, &h1);
		fprintf(f, "<span style=\'color:#110033\'>%s %s (%s %s %s %d %s, %02d:%02d %s)</span>"
			, GCStrings::GetSankrantiName(p->sankranti_zodiac)
			, GCStrings::getString(56).c_str()
			, GCStrings::getString(111).c_str(), GCStrings::GetSankrantiNameEn(p->sankranti_zodiac)
			, GCStrings::getString(852).c_str()
			, p->sankranti_day.day, GCStrings::GetMonthAbreviation(p->sankranti_day.month)
			, p->sankranti_day.GetHour(), p->sankranti_day.GetMinuteRound()
			, GCStrings::GetDSTSignature(p->nDST));
		prevCountFest++;
	}

	if (GCDisplaySettings::getValue(7) == 1 && p->was_ksaya)//(m_dshow.m_info_ksaya) && (pvd->was_ksaya))
	{
		double h, m;
		VCTIME dd;
		if (prevCountFest == 0)
			fprintf(f, "<table style=\'border-width:1pt;border-color:black;border-style:solid\'><tr><td style=\'font-size:9pt;background:%s;padding-left:25pt;padding-right:35pt;padding-top:15pt;padding-bottom:15pt;vertical-align:center\'>\n", gcal_html_getDayBackground(p));
		else
			fprintf(f, "<br>");
		m = modf(p->ksaya_time1*24, &h);
		dd = p->date;
		if (p->ksaya_day1 < 0.0)
			dd.PreviousDay();
		fprintf(f, "%s %s ", GCStrings::getString(89).c_str(), GCStrings::getString(850).c_str());
		fprintf(f, "%d %s, %02d:%02d", dd.day, GCStrings::GetMonthAbreviation(dd.month), int(h), int(m*60));
		m = modf(p->ksaya_time2*24, &h);
		dd = p->date;
		if (p->ksaya_day2 < 0.0)
			dd.PreviousDay();
		fprintf(f, "%s %d %s, %02d:%02d", GCStrings::getString(851).c_str(),
			dd.day, GCStrings::GetMonthAbreviation(dd.month), int(h), int(m*60));
		fprintf(f, "(%s)", GCStrings::GetDSTSignature(p->nDST));
		prevCountFest++;
	}

	if (GCDisplaySettings::getValue(8) == 1)//(m_dshow.m_info_vriddhi) && (pvd->is_vriddhi))
	{
		if (p->is_vriddhi)
		{
			if (prevCountFest == 0)
				fprintf(f, "<table style=\'border-width:1pt;border-color:black;border-style:solid\'><tr><td style=\'font-size:9pt;background:%s;padding-left:25pt;padding-right:35pt;padding-top:15pt;padding-bottom:15pt;vertical-align:center\'>\n", gcal_html_getDayBackground(p));
			else
				fprintf(f, "<br>");
			fprintf(f, "%s", GCStrings::getString(90).c_str());
			prevCountFest++;
		}
	}


	if (p->nCaturmasya & CMASYA_PURN_MASK)
	{
		if (prevCountFest == 0)
			fprintf(f, "<table style=\'border-width:1pt;border-color:black;border-style:solid\'><tr><td style=\'font-size:9pt;background:%s;padding-left:25pt;padding-right:35pt;padding-top:15pt;padding-bottom:15pt;vertical-align:center\'>\n", gcal_html_getDayBackground(p));
		else
			fprintf(f, "<br><br>");
		fprintf(f, "%s [PURNIMA SYSTEM]"
			, GCStrings::getString(107 + (p->nCaturmasya & CMASYA_PURN_MASK_DAY)
					   + ((p->nCaturmasya & CMASYA_PURN_MASK_MASA) >> 2)).c_str()
			);
		if ((p->nCaturmasya & CMASYA_PURN_MASK_DAY) == 0x1)
		{
			fprintf(f, "<br>");
			fprintf(f, GCStrings::getString(110 + ((p->nCaturmasya & CMASYA_PURN_MASK_MASA) >> 2)).c_str());
		}
		fprintf(f, "<br>");
		prevCountFest++;
	}

	if (p->nCaturmasya & CMASYA_PRAT_MASK)
	{
		if (prevCountFest == 0)
			fprintf(f, "<table style=\'border-width:1pt;border-color:black;border-style:solid\'><tr><td style=\'font-size:9pt;background:%s;padding-left:25pt;padding-right:35pt;padding-top:15pt;padding-bottom:15pt;vertical-align:center\'>\n", gcal_html_getDayBackground(p));
		else
			fprintf(f, "<br><br>");
		fprintf(f, "%s [PRATIPAT SYSTEM]"
			, GCStrings::getString(107 + ((p->nCaturmasya & CMASYA_PRAT_MASK_DAY) >> 8)
					   + ((p->nCaturmasya & CMASYA_PRAT_MASK_MASA) >> 10)).c_str()
			);
		if ((p->nCaturmasya & CMASYA_PRAT_MASK_DAY) == 0x100)
		{
			fprintf(f, "<br>");
			fprintf(f, GCStrings::getString(110 + ((p->nCaturmasya & CMASYA_PRAT_MASK_MASA) >> 10)).c_str());
		}
		fprintf(f, "</br>");
		prevCountFest++;
	}

	if (p->nCaturmasya & CMASYA_EKAD_MASK)
	{
		if (prevCountFest == 0)
			fprintf(f, "<table style=\'border-width:1pt;border-color:black;border-style:solid\'><tr><td style=\'font-size:9pt;background:%s;padding-left:25pt;padding-right:35pt;padding-top:15pt;padding-bottom:15pt;vertical-align:center\'>\n", gcal_html_getDayBackground(p));
		else
			fprintf(f, "<br><br>");
		fprintf(f, "%s [EKADASI SYSTEM]"
			, GCStrings::getString(107 + ((p->nCaturmasya & CMASYA_EKAD_MASK_DAY) >> 16)
					   + ((p->nCaturmasya & CMASYA_EKAD_MASK_MASA) >> 18)).c_str()
			);
		if ((p->nCaturmasya & CMASYA_EKAD_MASK_DAY) == 0x10000)
		{
			fprintf(f, "<br>");
			fprintf(f, GCStrings::getString(110 + ((p->nCaturmasya & CMASYA_EKAD_MASK_MASA) >> 18)).c_str());
		}
		fprintf(f, "<br>");
		prevCountFest++;
	}

	if (prevCountFest > 0)
		fprintf(f, "</td></tr></table>\n");

	fprintf(f, "<p>");
	// tithi at arunodaya
	if (GCDisplaySettings::getValue(0) == 1)//m_dshow.m_tithi_arun)
	{
		fprintf(f, "<br>%s: %s", GCStrings::getString(98).c_str(), GCStrings::GetTithiName(p->astrodata.nTithiArunodaya));
	}

	//"Arunodaya Time",//1
	if (GCDisplaySettings::getValue(1) == 1)//m_dshow.m_arunodaya)
	{
		fprintf(f, "<br>%s %d:%02d (%s)\r\n", GCStrings::getString(99).c_str(), p->astrodata.sun.arunodaya.hour
			, p->astrodata.sun.arunodaya.min, GCStrings::GetDSTSignature(p->nDST));
	}

	//"Moonrise Time",//4
	if (GCDisplaySettings::getValue(4) == 1)
	{
		fprintf(f, "<br>");
		if (p->moonrise.hour < 0)
			fprintf(f, GCStrings::getString(136).c_str());
		else
		{
			fprintf(f, "%s %d:%02d (%s)", GCStrings::getString(53).c_str(), p->moonrise.hour
				, p->moonrise.min, GCStrings::GetDSTSignature(p->nDST));
		}
	}
	//"Moonset Time",//5
	if (GCDisplaySettings::getValue(5) == 1)
	{
		if (GCDisplaySettings::getValue(4) == 1)
			fprintf(f, "&nbsp;&nbsp;&nbsp;");
		else
			fprintf(f, "<br>");
		if (p->moonrise.hour < 0)
			fprintf(f, GCStrings::getString(137).c_str());
		else
		{
			fprintf(f, "%s %d:%02d (%s)", GCStrings::getString(54).c_str(), p->moonset.hour
				, p->moonset.min, GCStrings::GetDSTSignature(p->nDST));
		}
	}
	///"Sun Longitude",//9
	if (GCDisplaySettings::getValue(9) == 1)//m_dshow.m_sun_long)
	{
		fprintf(f, "<br>%s: %f (*)\r\n", GCStrings::getString(100).c_str(), p->astrodata.sun.longitude_deg);
	}
	//"Moon Longitude",//10
	if (GCDisplaySettings::getValue(10) == 1)//m_dshow.m_sun_long)
	{
		if (GCDisplaySettings::getValue(9)==1)
			fprintf(f, ", ");
		else
			fprintf(f, "<br>");
		fprintf(f, "%s: %f (*)\r\n", GCStrings::getString(101).c_str(), p->astrodata.moon.longitude_deg);
	}
	//"Ayanamsha value",//11
	if (GCDisplaySettings::getValue(11) == 1)//m_dshow.m_sun_long)
	{
		if (GCDisplaySettings::getValue(9)==1 || GCDisplaySettings::getValue(10)==1)
			fprintf(f, ", ");
		else
			fprintf(f, "<br>");
		fprintf(f, "<br>%s %f (%s) (*)\r\n", GCStrings::getString(102).c_str(), p->astrodata.msAyanamsa, GCAyanamsha::GetAyanamsaName(GCAyanamsha::GetAyanamsaType()));
	}
	//"Julian Day",//12
	if (GCDisplaySettings::getValue(12) == 1)//m_dshow.m_sun_long)
	{
		if (GCDisplaySettings::getValue(9)==1 || GCDisplaySettings::getValue(10)==1 || GCDisplaySettings::getValue(11)==1 )
			fprintf(f, ", ");
		else
			fprintf(f, "<br>");
		fprintf(f, "<br>%s %f (*)\r\n", GCStrings::getString(103).c_str(), p->astrodata.jdate);
	}

	/*BEGIN GCAL 1.4.3*/
	DAYTIME tdA, tdB;

	if (GCDisplaySettings::getValue(29))
	{
		fprintf(f, "<br>%s %2d:%02d ",
			GCStrings::getString(51).c_str(), p->astrodata.sun.rise.hour, p->astrodata.sun.rise.min );
		if (GCDisplaySettings::getValue(32))
		{
			tdA = p->astrodata.sun.rise;
			tdB = p->astrodata.sun.rise;
			tdA -= 24;
			tdB += 24;
			fprintf(f, " sandhya %2d:%02d - %2d:%02d ", tdA.hour, tdA.min, tdB.hour, tdB.min);
		}
		fprintf(f, " (%s)", GCStrings::GetDSTSignature(p->nDST));
	}
	if (GCDisplaySettings::getValue(30))
	{
		fprintf(f, "<br>%s    %2d:%02d ", GCStrings::getString(857).c_str(), p->astrodata.sun.noon.hour, p->astrodata.sun.noon.min);
		if (GCDisplaySettings::getValue(32))
		{
			tdA = p->astrodata.sun.noon;
			tdB = p->astrodata.sun.noon;
			tdA -= 24;
			tdB += 24;
			fprintf(f, " sandhya %2d:%02d - %2d:%02d ", tdA.hour, tdA.min, tdB.hour, tdB.min);
		}
		fprintf(f, " (%s)\r\n", GCStrings::GetDSTSignature(p->nDST));
	}
	if (GCDisplaySettings::getValue(31))
	{
		fprintf(f, "<br>%s  %2d:%02d ", GCStrings::getString(52).c_str(), p->astrodata.sun.set.hour, p->astrodata.sun.set.min);
		if (GCDisplaySettings::getValue(32))
		{
			tdA = p->astrodata.sun.set;
			tdB = p->astrodata.sun.set;
			tdA -= 24;
			tdB += 24;
			fprintf(f, " sandhya %2d:%02d - %2d:%02d ", tdA.hour, tdA.min, tdB.hour, tdB.min);
		}
		fprintf(f, " (%s)\r\n", GCStrings::GetDSTSignature(p->nDST));
	}
	if (GCDisplaySettings::getValue(33))
	{
		fprintf(f,"<br>%s info  Moon in %s %s",
			GCStrings::getString(51).c_str(), 
			GCStrings::GetNaksatraName(p->astrodata.nNaksatra), GCStrings::getString(15).c_str());
		if (GCDisplaySettings::getValue(47))
		{
			fprintf(f, ", %.1f%% passed (%s Pada)", p->astrodata.nNaksatraElapse, GCStrings::getString(811+int(p->astrodata.nNaksatraElapse/25)).c_str());
		}
		if (GCDisplaySettings::getValue(46))
		{
			fprintf(f, ", Moon in the %s %s", GCStrings::GetSankrantiName(p->astrodata.nMoonRasi), GCStrings::getString(105).c_str());
		}
		fprintf(f, ", %s %s<br>Sun in %s %s.",
			GCStrings::GetYogaName(p->astrodata.nYoga), GCStrings::getString(104).c_str(),
			GCStrings::GetSankrantiName(p->astrodata.nSunRasi), GCStrings::getString(105).c_str());
	}
	fprintf(f, "</p>");
	fprintf(f, "</body>");
	fprintf(f, "</html>");
	/* END GCAL 1.4.3 */

}

void AvcTransTodayInfoHTML(const char * szLocName, const char * szCountry, double Latitude, double Longitude, int timezoneID, int day, int month, int year, FILE * f)
{
	CLocationRef loc;
	VCTIME vc;
	
	loc.m_strName = szLocName;
//	loc.m_strCountry = szCountry;
	loc.m_fLatitude = Latitude;
	loc.m_fLongitude = Longitude;
	loc.m_nDST = timezoneID;
	loc.m_fTimezone = TTimeZone::GetTimeZoneOffset(timezoneID);
	
	vc.day = day;
	vc.month = month;
	vc.year = year;
	vc.shour = 0.5;
	vc.tzone = loc.m_fTimezone;
	
	WriteTodayInfoHTML(vc, loc, f);
}

void AvcTransAppDayInfoHTML(const char * szLocName, const char * szCountry, double Latitude, double Longitude, int timezoneID, int day, int month, int year, int hour, int minute, FILE * f)
{
	CLocationRef loc;
	VCTIME vc;
	
	loc.m_strName = szLocName;
	//loc.m_strCountry = szCountry;
	loc.m_fLatitude = Latitude;
	loc.m_fLongitude = Longitude;
	loc.m_nDST = timezoneID;
	loc.m_fTimezone = TTimeZone::GetTimeZoneOffset(timezoneID);
	
	vc.day = day;
	vc.month = month;
	vc.year = year;
	vc.shour = (hour*60 + minute)/1440.0;
	vc.tzone = loc.m_fTimezone;
	
	TResultApp app;
	
	CalcAppDay(loc, vc, app);
	
	WriteAppDayHTML(app, f);
}

void AvcTransCalendarHTML(const char * szLocName, const char * szCountry, double Latitude, double Longitude, int timezoneID, int day, int month, int year, int count, FILE * f)
{
	CLocationRef loc;
	VCTIME vc;
	
	loc.m_strName = szLocName;
	//loc.m_strCountry = szCountry;
	loc.m_fLatitude = Latitude;
	loc.m_fLongitude = Longitude;
	loc.m_nDST = timezoneID;
	loc.m_fTimezone = TTimeZone::GetTimeZoneOffset(timezoneID);
	
	vc.day = day;
	vc.month = month;
	vc.year = year;
	vc.shour = 0.5;
	vc.tzone = loc.m_fTimezone;
	
	TResultCalendar cal;
	
	CalcCalendar(cal, loc, vc, count);
	WriteCalendarHTML(cal, f);
}


void AvcTransMasaListHTML(const char * szLocName, const char * szCountry, double Latitude, double Longitude, int timezoneID, int year, int count, FILE * f)
{
	CLocationRef loc;
	VCTIME vc;
	
	loc.m_strName = szLocName;
	//loc.m_strCountry = szCountry;
	loc.m_fLatitude = Latitude;
	loc.m_fLongitude = Longitude;
	loc.m_nDST = timezoneID;
	loc.m_fTimezone = TTimeZone::GetTimeZoneOffset(timezoneID);
	
	TResultMasaList mlist;
	
	CalcMasaList(mlist, loc, year, count);
	WriteMasaListHTML(mlist, f);
}

void AvcTransEventsHTML(const char * szLocName, const char * szCountry, double Latitude, double Longitude, int timezoneID, int day, int month, int year, int count, int options, FILE * f)
{
	CLocationRef loc;
	VCTIME vc;
	VCTIME vcEnd;
	
	loc.m_strName = szLocName;
	//loc.m_strCountry = szCountry;
	loc.m_fLatitude = Latitude;
	loc.m_fLongitude = Longitude;
	loc.m_nDST = timezoneID;
	loc.m_fTimezone = TTimeZone::GetTimeZoneOffset(timezoneID);
	
	vc.day = day;
	vc.month = month;
	vc.year = year;
	vc.shour = 0.5;
	vc.tzone = loc.m_fTimezone;
	
	vcEnd = vc;
	vcEnd += count;
	
	TResultEvents cal;
	
	CalcEvents(cal, loc, vc, vcEnd);
	WriteEventsHTML(cal, f);
}
