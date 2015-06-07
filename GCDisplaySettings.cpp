#include "stdafx.h"
#include "GCDisplaySettings.h"
#include "TString.h"
#include "TFile.h"

GCDisplaySettings::GCDisplaySettings(void)
{
}


GCDisplaySettings::~GCDisplaySettings(void)
{
}

int GCDisplaySettings::getCount()
{
	int i = 0;
	while(gss[i].text != NULL)
		i++;
	return i;
}

int GCDisplaySettings::getCountChanged()
{
	int i, count = 0;
	int size = GCDisplaySettings::getCount();

	for(i = 0; i < size; i++)
	{
		if (gss[i].val != gss[i].old_val)
			count++;
		gss[i].old_val = gss[i].val;
	}

	return count;
}

char * GCDisplaySettings::getSettingName(int i)
{
	return gss[i].text;
}

int GCDisplaySettings::getValue(int i)
{
	return gss[i].val;
}

void GCDisplaySettings::setValue(int i, int val)
{
	gss[i].val = val;
	gss[i].old_val = val;
}



void GCDisplaySettings::setValue(const char * pszSign, int val)
{
	int i, max = GCDisplaySettings::getCount();

	for(i = 0; i < max; i++)
	{
		if (_tcscmp(gss[i].sig, pszSign) == 0)
		{
			gss[i].val = val;
			gss[i].old_val = val;
			break;
		}
	}
}

void GCDisplaySettings::readFile(const char * psz)
{
	TString strA, strB;
	TFile file;

	if (file.Open(psz, "r") == TRUE)
	{
		while(file.ReadPropertyLine(strA, strB))
		{
			if (strA.GetLength() > 1 && strA.GetAt(0) == '#')
			{
			}
			else
			{
				GCDisplaySettings::setValue(strA, atoi(strB));
			}
		}

		file.Close();
		::DeleteFile(psz);
	}
}

CShowSetting GCDisplaySettings::gss[] =
{
	{0, 0, "ARTI", "Tithi at arunodaya"},//0
	{0, 0, "ARTM", "Arunodaya Time"},//1
	{0, 0, "SRTM", "Sunrise Time"},//2
	{0, 0, "SSTM", "Sunset Time"},//3
	{0, 0, "MRTM", "Moonrise Time"},//4
	{0, 0, "MSTM", "Moonset Time"},//5
	{1, 1, "FEST", "Festivals"},//6
	{0, 0, "KSAY", "Info about ksaya tithi"},//7
	{0, 0, "VRDH", "Info about vriddhi tithi"},//8
	{0, 0, "SLON", "Sun Longitude"},//9
	{0, 0, "MLON", "Moon Longitude"},//10
	{0, 0, "AYAN", "Ayanamsha value"},//11
	{0, 0, "JDAY", "Julian Day"},//12
	{1, 1, "CPUR", "Caturmasya Purnima System"}, //13
	{0, 0, "CPRA", "Caturmasya Pratipat System"}, //14
	{0, 0, "CEKA", "Caturmasya Ekadasi System"}, //15
	{1, 1, "SANI", "Sankranti Info"}, //16
	{1, 1, "EKAI", "Ekadasi Info"}, //17
	{1, 1, "VHDR", "Masa Header Info"}, //18
	{0, 0, "PHDR", "Month Header Info"}, //19
	{0, 0, "EDNS", "Do not show empty days"}, //20
	{0, 0, "SBEM", "Show begining of masa"}, //21
	{1, 1, "F000", "Appearance days of the Lord"},//22
	{1, 1, "F001", "Events in the pastimes of the Lord"},//23
	{1, 1, "F002", "App, Disapp of Recent Acaryas"},//24
	{1, 1, "F003", "App, Disapp of Mahaprabhu's Associates and Other Acaryas"},//25
	{1, 1, "F004", "ISKCON's Historical Events"},//26
	{1, 1, "F005", "Bengal-specific Holidays"},//27
	{1, 1, "F006", "My Personal Events"}, //28
	/* BEGIN GCAL 1.4.3 */
	{1, 1, "TSSR", "Todat Sunrise"},  //29 Today sunrise
	{1, 1, "TSSN", "Today Noon"},  //30 today noon
	{1, 1, "TSSS", "Today Sunset"},  //31 today sunset
	{0, 0, "TSAN", "Sandhya Times"},  //32 today + sandhya times
	{1, 1, "TSIN", "Sunrise Info"},  //33 today sunrise info
	{0, 0, "ASIN", "Noon Time"},  //34 astro - noon time
	{1, 1, "NDST", "Notice about DST"}, //35 notice about the change of the DST
	{1, 1, "DNAK", "Naksatra"}, // 36 naksatra info for each day
	{1, 1, "DYOG", "Yoga"}, //37 yoga info for each day
	{1, 1, "FFLG", "Fasting Flag"},//38
	{1, 1, "DPAK", "Paksa Info"},//39 paksa info
	{0, 0, "FDIW", "First Day in Week"},//40 first day in week
	{0, 0, "DRAS", "Rasi"}, //41 moon rasi for each calendar day
	{0, 0, "OSFA", "Old Style Fasting text"}, //42 old style fasting text
	{0, 0, "MLNT", "Name of month - type"}, //43 month type name 0-vaisnava,1-bengal,2-hindu,3-vedic
	/* END GCAL 1.4.3 */
	{0, 0, "EDBL", "Editable Default Events"}, //44 editable default events
	{0, 0, "TSBM", "Today Brahma Muhurta"},     //45 brahma muhurta in today screen
	{0, 0, "TROM", "Today Rasi of the Moon"}, // 46 rasi of the moon in today screen
	{0, 0, "TNPD", "Today Naksatra Pada details"}, // 47 naksatra pada details in today screen
	{0, 0, "ADCS", "Child Names Suggestions"}, // 48 child name suggestions in Appearance Day screen
	{0, 0, "MNFO", "Masa Name Format"}, // 49 format of masa name
	{0, 0, "EPDR", "Ekadasi Parana details"}, // 50 ekadasi parana details
	{0, 0, "ANIV", "Aniversary show format"}, // 51 format of aniversary info
	{1, 1, "CE01", "Sun events"}, // 52
	{1, 1, "CE02", "Tithi events"}, //53
	{1, 1, "CE03", "Naksatra Events"}, //54
	{1, 1, "CE04", "Sankranti Events"},//55
	{1, 1, "CE05", "Conjunction EVents"},//56
	{0, 0, "CE06", "Rahu kalam"}, //57
	{0, 0, "CE07", "Yama ghanti"}, //58
	{0, 0, "CE08", "Guli kalam"}, //59
	{0, 0, "CE09", "Moon events"}, //60
	{0, 0, "CE10", "Moon rasi"}, //61
	{0, 0, "CE11", "Ascendent"}, //62
	{0, 0, "CE12", "Sort results core events"},//63
	{0, 0, NULL, NULL}
};

