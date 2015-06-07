#include "stdafx.h"
#include "GCStrings.h"
#include "TString.h"
#include "TFileRichList.h"
#include "enums.h"
#include "GCDisplaySettings.h"

extern TString gstr[];
extern int gstr_Modified;

GCStrings::GCStrings(void)
{
}


GCStrings::~GCStrings(void)
{
}

const char * GCStrings::GetMonthAbreviation(int month)
{
	return GCStrings::getString(64 + month).c_str();
}

const char * GCStrings::GetTithiName(int i)
{
	return GCStrings::getString(600 + i % 30);
}

const char * GCStrings::GetNaksatraName(int n)
{
	return GCStrings::getString(630 + n % 27);
}

const char * GCStrings::GetNaksatraChildSylable(int n, int pada)
{
	int i = (n * 4 + pada) % 108;

	static char * childsylable[108] = {
		"chu", "che", "cho", "la", //asvini
		"li", "lu", "le", "lo", // bharani
		"a", "i", "u", "e", //krtika
		"o", "va", "vi", "vo", // rohini
		"ve", "vo", "ka", "ke", // mrgasira
		"ku","gha","ng","chha", // ardra
		"ke","ko","ha","hi", // punarvasu
		"hu","he","ho","da", // pushya
		"di","du","de","do", //aslesa
		"ma","mi","mu","me", //magha
		"mo","ta","ti","tu", //purvaphalguni
		"te","to","pa","pi", //uttaraphalguni
		"pu","sha","na","tha",//hasta
		"pe","po","ra","ri",//chitra
		"ru","re","ra","ta",//svati
		"ti","tu","te","to",//visakha
		"na","ni","nu","ne",// anuradha
		"no","ya","yi","yu",//jyestha
		"ye","yo","ba","bi",// mula
		"bu","dha","bha","dha",//purvasada
		"be","bo","ja","ji",// uttarasada
		"ju","je","jo","gha",//sravana
		"ga","gi","gu","ge",// dhanistha
		"go","sa","si","su",//satabhisda
		"se","so","da","di",//purvabhadra
		"du","tha","jna","da",//uttarabhadra
		"de","do","cha","chi"// revati

	};

	return childsylable[i];
}

const char * GCStrings::GetRasiChildSylable(int n)
{
	static char * childsylable[12] = {
		"a.. e.. la..",
		"u.. ba.. va..",
		"ka.. gha..",
		"da.. ha..",
		"ma..",
		"pa..",
		"ra.. ta..",
		"na.. ya..",
		"dha.. bha... pha..",
		"kha.. ja..",
		"ga.. sa.. sha..",
		"da.. ca.. tha.. jha.."
	};
	/*Mesa :	 	 a   la
Vrsabha: 	   u   va,   i, e, o
Mithuna:  	 ka,  cha, gha
Kataka:	   ha
Simha:		  ma
Kanya:		 pa
Tula:		 ra , ta
Vrschika:	  na ,  ba

Dhanus:	   dha , bha,  pha
Makra:  	kha, ja
Kumbha:	   ga,, sa
Mina:		  da, ca , jha
*/		

	return childsylable[n % 12];
}

const char * GCStrings::GetYogaName(int n)
{
	return GCStrings::getString(660 + n % 27);
}

const char * GCStrings::GetSankrantiName(int i)
{
	return GCStrings::getString(688 + i % 12);
}

const char * GCStrings::GetSankrantiNameEn(int i)
{

	return GCStrings::getString(700 + i % 12);
}

char GCStrings::GetPaksaChar(int i)
{
	return (i ? 'G' : 'K');
}

const char * GCStrings::GetPaksaName(int i)
{
	return (i ? GCStrings::getString(712).c_str() : GCStrings::getString(713).c_str());
}

const char * GCStrings::GetMasaName(int i)
{
	switch(GCDisplaySettings::getValue(49))
	{
	case 0: // VAISNAVA
		return GCStrings::getString(720 + i % 13);
	case 1: // VAISNAVA (COMMON)
		return GCStrings::getString(897 + i % 13);
	case 2: // COMMON
		return GCStrings::getString(871 + i % 13);
	case 3: // COMMON (VAISNAVA)
		return GCStrings::getString(884 + i % 13);
	default:
		return GCStrings::getString(720 + i % 13);
	}
}

const char * GCStrings::GetMahadvadasiName(int i)
{
	switch(i)
	{
	case EV_NULL:
	case EV_SUDDHA:
		return NULL;
	case EV_UNMILANI:
		return GCStrings::getString(733);
	case EV_TRISPRSA:
	case EV_UNMILANI_TRISPRSA:
		return GCStrings::getString(734);
	case EV_PAKSAVARDHINI:
		return GCStrings::getString(735);
	case EV_JAYA:
		return GCStrings::getString(736);
	case EV_VIJAYA:
		return GCStrings::getString(737);
	case EV_PAPA_NASINI:
		return GCStrings::getString(738);
	case EV_JAYANTI:
		return GCStrings::getString(739);
	case EV_VYANJULI:
		return GCStrings::getString(740);
	default:
		return NULL;
	}
}

const char * GCStrings::GetSpecFestivalName(int i)
{
	switch(i)
	{
	case SPEC_JANMASTAMI:
		return GCStrings::getString(741);
	case SPEC_GAURAPURNIMA:
		return GCStrings::getString(742);
	case SPEC_RETURNRATHA:
		return GCStrings::getString(743);
	case SPEC_HERAPANCAMI:
		return GCStrings::getString(744);
	case SPEC_GUNDICAMARJANA:
		return GCStrings::getString(745);
	case SPEC_GOVARDHANPUJA:
		return GCStrings::getString(746);
	case SPEC_RAMANAVAMI:
		return GCStrings::getString(747);
	case SPEC_RATHAYATRA:
		return GCStrings::getString(748);
	case SPEC_NANDAUTSAVA:
		return GCStrings::getString(749);
	case SPEC_PRABHAPP:
		return GCStrings::getString(759);
	case SPEC_MISRAFESTIVAL:
		return GCStrings::getString(750);
	default:
		return GCStrings::getString(64);
	}
}

void GCStrings::SetSpecFestivalName(int i, const char * szName)
{
	switch(i)
	{
	case SPEC_JANMASTAMI:
		GCStrings::setString(741, szName);
		gstr_Modified = 1;
		break;
	case SPEC_GAURAPURNIMA:
		GCStrings::setString(742, szName);
		gstr_Modified = 1;
		break;
	case SPEC_RETURNRATHA:
		GCStrings::setString(743, szName);
		gstr_Modified = 1;
		break;
	case SPEC_HERAPANCAMI:
		GCStrings::setString(744, szName);
		gstr_Modified = 1;
		break;
	case SPEC_GUNDICAMARJANA:
		GCStrings::setString(745, szName);
		gstr_Modified = 1;
		break;
	case SPEC_GOVARDHANPUJA:
		GCStrings::setString(746, szName);
		gstr_Modified = 1;
		break;
	case SPEC_RAMANAVAMI:
		GCStrings::setString(747, szName);
		gstr_Modified = 1;
		break;
	case SPEC_RATHAYATRA:
		GCStrings::setString(748, szName);
		gstr_Modified = 1;
		break;
	case SPEC_NANDAUTSAVA:
		GCStrings::setString(749, szName);
		gstr_Modified = 1;
		break;
	case SPEC_PRABHAPP:
		GCStrings::setString(759, szName);
		gstr_Modified = 1;
		break;
	case SPEC_MISRAFESTIVAL:
		GCStrings::setString(750, szName);
		gstr_Modified = 1;
		break;
	default:
		break;
	}

	return;
}


bool GCStrings::GetSpecFestivalNameEx(TString &str, int i)
{
	switch(i)
	{
	case SPEC_JANMASTAMI:
		str = GCStrings::getString(741);
		str += "[f:5:Sri Krsna]";
		break;
	case SPEC_GAURAPURNIMA:
		str = GCStrings::getString(742);
		str += "[f:3:Sri Caitanya Mahaprabhu]";
		break;
	case SPEC_RETURNRATHA:
		str = GCStrings::getString(743);
		break;
	case SPEC_HERAPANCAMI:
		str = GCStrings::getString(744);
		break;
	case SPEC_GUNDICAMARJANA:
		str = GCStrings::getString(745);
		break;
	case SPEC_GOVARDHANPUJA:
		str = GCStrings::getString(746);
		break;
	case SPEC_RAMANAVAMI:
		str = GCStrings::getString(747);
		str += "[f:2:Sri Ramacandra]";
		break;
	case SPEC_RATHAYATRA:
		str = GCStrings::getString(748);
		break;
	case SPEC_NANDAUTSAVA:
		str = GCStrings::getString(749);
		break;
	case SPEC_PRABHAPP:
		str = GCStrings::getString(759);
		str += "[f:1:Srila Prabhupada]";
		break;
	case SPEC_MISRAFESTIVAL:
		str = GCStrings::getString(750);
		break;
	default:
		str = GCStrings::getString(64);
		return FALSE;
	}

	return TRUE;
}


const char * GCStrings::GetFastingName(int i)
{
	switch (i)
	{
	case FAST_NOON:
		return( GCStrings::getString(751));
		break;
	case FAST_SUNSET:
		return( GCStrings::getString(752));
		break;
	case FAST_MOONRISE:
		return( GCStrings::getString(753));
		break;
	case FAST_DUSK:
		return( GCStrings::getString(754));
		break;
	case FAST_MIDNIGHT:
		return( GCStrings::getString(755));
		break;
	case FAST_DAY:
		return( GCStrings::getString(756));
	default:
		return NULL;
	}
}

TString & GCStrings::getString(int i)
{
	return gstr[i];
}

const char * GCStrings::GetEkadasiName(int nMasa, int nPaksa)
{
	return GCStrings::getString(560 + nMasa*2 + nPaksa);
}

const char * GCStrings::GetDSTSignature(int nDST)
{
	return nDST ? "DST" : "LT";
}

const char * GCStrings::GetParanaReasonText(int eparana_type)
{
	switch(eparana_type)
	{
	case EP_TYPE_3DAY:
		return GCStrings::getString(165).c_str();
	case EP_TYPE_4TITHI:
		return GCStrings::getString(166).c_str();
	case EP_TYPE_SUNRISE:
		return GCStrings::getString(169).c_str();
	case EP_TYPE_TEND:
		return GCStrings::getString(167).c_str();
	case EP_TYPE_NAKEND:
		return GCStrings::getString(168).c_str();
	default:
		break;
	}

	return "";
}

const char * GCStrings::GetVersionText(void)
{
	return GCStrings::getString(130);
}

void GCStrings::setString(int i, const char * str)
{
	gstr[i] = str;
}

const char * GCStrings::GetEventClassText(int i)
{
	switch(i)
	{
		case 0: return "Appearance Days of the Lord and His Incarnations"; break;
		case 1: return "Events in the Pastimes of the Lord and His Associates"; break;
		case 2: return "Appearance and Disappearance Days of Recent Acaryas"; break;
		case 3: return "Appearance and Disappearance Days of Mahaprabhu's Associates and Other Acaryas"; break;
		case 4: return "ISKCON's Historical Events"; break;
		case 5: return "Bengal-specific Holidays"; break;
		case 6: return "My Personal Events"; break;
		default: break;
	}
	return "";
}

const char * GCStrings::GetDayOfWeek(int i)
{
	return gstr[i].c_str();
}

int GCStrings::readFile(const char * pszFile)
{
	int v = 0;
	TFileRichList rf;

	if (rf.Open(pszFile, "rt") != 0)
	{
		int index = 0;
		while(rf.ReadLine())
		{
			if (atoi(rf.GetTag())==78)
			{
				index = atoi(rf.GetField(0));
				if (index >= 0 && index < 900)
				{
					gstr[index] = rf.GetField(1);
					v++;
				}
			}
		}
		rf.Close();
	}
	else
	{
		return -1;
	}

	return v;
}

int GCStrings::writeFile(const char * pszFile)
{
	int i, j, v = 0;
	// a[x][0] je zaciatocny index
	// a[x][1] je konecny index skupiny (vratane)
	int a[3][2] =
	{
		{ 0, 128 },
		{ 135, 199 },
		{ 561, 899 }
	};
	TFileRichList trf;

	if (trf.Open(pszFile, "wt"))
	{
		// save 0 - 128
		// save 135 - 199
		// save 561 - 899
		for(j = 0; j < 3; j++)
		{
			for(i = a[j][0]; i <= a[j][1]; i++)
			{
				if (GCStrings::getString(i).GetLength() > 0)
				{
					trf.Clear();
					trf.AddTag(78);
					trf.AddInt(i);
					trf.AddText(GCStrings::getString(i).c_str());
					trf.WriteLine();
					v++;
				}
			}
		}
		trf.Close();
	}
	else
	{
		return -1;
	}

	return v;
}

const char * GCStrings::GetKalaName(KalaType i)
{
	switch(i)
	{
	case KT_RAHU_KALAM:
		return "Rahu kalam";
	case KT_YAMA_GHANTI:
		return "Yama ghanti";
	case KT_GULI_KALAM:
		return "Guli kalam";
	}
}
