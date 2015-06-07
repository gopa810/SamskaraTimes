// CommandLineVCal.cpp: implementation of the CCommandLineVCal class.
// PORTABLE
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "platform.h"
#include "CommandLineVCal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommandLineVCal::CCommandLineVCal()
{
	gnLastError = 0;
}

CCommandLineVCal::~CCommandLineVCal()
{

}

//////////////////////////////////////////////////////////////////////
//

int CCommandLineVCal::GetArgLastError()
{
	return gnLastError;
}

//////////////////////////////////////////////////////////////////////
//

int CCommandLineVCal::SetArgLastError(int i)
{
	return (gnLastError = i);
}

//////////////////////////////////////////////////////////////////////
//

int CCommandLineVCal::GetArg_Year(const char * str, int &nYear)
{
	int n = _ttoi(str);

	if (n < 1600)
	{
		return SetArgLastError(10);
	}

	if (n > 3999)
		return SetArgLastError(11);

	nYear = n;

	return NULL;

}

//////////////////////////////////////////////////////////////////////
//

int CCommandLineVCal::GetArg_Int(const char * str, int &nInteger)
{
	nInteger = _ttoi(str);

	return NULL;
}

//////////////////////////////////////////////////////////////////////
//

int CCommandLineVCal::GetArg_Masa(const char * str)
{
	int nMasa = 0;

	char * masaname[14] = 
	{
		"visnu",
		"madhusudana",
		"trivikrama",
		"vamana",
		"sridhara",
		"hrsikesa",
		"padmanadbha",
		"damodara",
		"kesava",
		"narayana",
		"madhava",
		"govinda",
		"purusottama"
	};


	for(int i = 0; i < 13; i++)
	{
		if (stricmp(masaname[i], str) == 0)
		{
			return MasaIndexToInternal(i);
		}
	}

	nMasa = atoi(str);

	if (nMasa != 0)
	{
		return MasaIndexToInternal(nMasa - 1);
	}

	return 11;
}

int CCommandLineVCal::MasaIndexToInternal(int nMasa)
{
	int nMasaIndex[] = { 11, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12 };

	if (nMasa < 0)
		return 0;
	else if (nMasa > 12)
		return 0;
	else
		return nMasaIndex[ nMasa ];
}

int CCommandLineVCal::GetArg_EarthPos(const char * str, double &Latitude, double &Longitude)
{
	double l = 0.0;
	double sig = 1.0;
	double coma = 10.0;
	bool after_coma = false;
	bool is_deg = false;
	bool bNorth = false;
	bool bLat = false;
	bool bLon = false;

	const char * s = str;

	while(*s)
	{
		switch(*s)
		{
		case '0': case '1':
		case '2': case '3': case '4': case '5':
		case '6': case '7': case '8': case '9':
			if (after_coma)
			{
				if (is_deg)
				{
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
			}
			break;
		case 'n': case 'N':
			after_coma = true;
			is_deg = true;
			sig = 1.0;
			bNorth = true;
			break;
		case 's': case 'S':
			bNorth = true;
			after_coma = true;
			is_deg = true;
			sig = -1.0;
			break;
		case 'e': case 'E':
			bNorth = false;
			after_coma = true;
			is_deg = true;
			sig = 1.0;
			break;
		case 'w': case 'W':
			bNorth = false;
			after_coma = true;
			is_deg = true;
			sig = -1.0;
			break;
		case '.':
			after_coma = true;
			is_deg = false;
			break;
		case '-':
			sig = -1.0;
			break;
		case '+':
			sig = 1.0;
			break;
		case ';':
			if (bNorth == true)
			{
				bLat = true;
				Latitude = l * sig;
				bNorth = false;
			}
			else
			{
				bLon = true;
				Longitude = l * sig;
				bNorth = true;
			}
			l = 0.0;
			sig = 1.0;
			after_coma = false;
			is_deg = false;
			coma = 10.0;
			break;
		default:
			break;
		}
		s++;
	}

	if (bNorth == true)
	{
		bLat = true;
		Latitude = l * sig;
	}
	else
	{
		bLon = true;
		Longitude = l * sig;
	}

	return NULL;
}

int CCommandLineVCal::GetArg_TimeZone(const char * str, double &TimeZone)
{
	double l = 0.0;
	double sig = 1.0;
	double coma = 10.0;
	bool after_coma = false;
	bool is_deg = false;

	const char * s = str;

	while(*s)
	{
		switch(*s)
		{
		case '0': case '1':
		case '2': case '3': case '4': case '5':
		case '6': case '7': case '8': case '9':
			if (after_coma)
			{
				if (is_deg)
				{
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
			}
			break;
		case 'W':
			after_coma = true;
			sig = -1.0;
			is_deg = true;
			break;
		case 'E':
			after_coma = true;
			sig = 1.0;
			is_deg = true;
			break;
		case '-':
			//after_coma = true;
			sig = -1.0;
			break;
		case '+':
			//after_coma = true;
			sig = 1.0;
			break;
		case '.':
			after_coma = true;
			is_deg = false;
			break;
		case ':':
			after_coma = true;
			is_deg = true;
			break;
		default:
			return SetArgLastError(14);
		}
		s++;
	}

	TimeZone = l * sig;

	return NULL;
}

int CCommandLineVCal::GetArg_Tithi(const char * str)
{
	char * tithi[] = {
		"Pratipat",
		"Dvitiya",
		"Tritiya",
		"Caturthi",
		"Pancami",
		"Sasti",
		"Saptami",
		"Astami",
		"Navami",
		"Dasami",
		"Ekadasi",
		"Dvadasi",
		"Trayodasi",
		"Caturdasi",
		"Amavasya",
		"Pratipat",
		"Dvitiya",
		"Tritiya",
		"Caturthi",
		"Pancami",
		"Sasti",
		"Saptami",
		"Astami",
		"Navami",
		"Dasami",
		"Ekadasi",
		"Dvadasi",
		"Trayodasi",
		"Caturdasi",
		"Purnima"
	};

	int i;

	for(i = 0; i < 30; i++)
	{
		if (stricmp(tithi[i], str) == 0)
		{
			return i % 15;
		}
	}

	i = _ttoi(str);
	if (i > 0)
	{
		return i - 1;
	}

	return 0;
}

int CCommandLineVCal::GetArg_Paksa(const char * str)
{
	if ((str[0] == TCHAR('g')) || (str[0] == TCHAR('G')) || (str[0] == TCHAR('1')))
	{
		return 1;
	}

	return 0;
}

int CCommandLineVCal::GetArg_Date(const char * str, VCTIME &vc)
{
	char szt[32];
	TString s[4];
	int n, p, len;
	int c = 0;

	p = strlen(str);
	for(n = p - 1; n >= 0; n--)
	{
		if (str[n] == '-' || str[n]=='/' || n == 0)
		{
			if (n == 0)
				n--;
			len = p - n - 1;
			if (len > 30)
				len = 30;
			strncpy(szt, str + n + 1, len);
			szt[len] = 0;
			//TRACE2("###arg %d = %s\n", c, szt);
			s[c] = szt;
			c++;
			p = n;
		}
	}

	vc.day = atoi(s[2].c_str());
	if (vc.day == 0)
		vc.day = 1;
	vc.month = atoi(s[1].c_str());
	if (vc.month == 0)
		vc.month = 1;
	vc.year = atoi(s[0].c_str());

	return NULL;
}

int CCommandLineVCal::GetArg_VaisnDate(const char * str, VATIME &va)
{
	char szt[32];
	TString s[4];
	int n, p, len;
	int c = 0;

	p = strlen(str);
	for(n = p - 1; n >= 0; n--)
	{
		if (str[n] == '-' || str[n] == '/' || n == 0)
		{
			if (n == 0)
				n--;
			len = p - n - 1;
			if (len > 30)
				len = 30;
			strncpy(szt, str + n + 1, len);
			szt[len] = 0;
			//TRACE2("###arg %d = %s\n", c, szt);
			s[c] = szt;
			c++;
			p = n;
		}
	}

	va.tithi = GetArg_Tithi(s[3].c_str()) + GetArg_Paksa(s[2].c_str())*15;
	va.masa = GetArg_Masa(s[1].c_str());
	va.gyear = atoi(s[0].c_str());

	return NULL;
}


int CCommandLineVCal::GetArg_Interval(const char * pszText, int &A, int &B)
{
	int * p = &A;

	A = 0;
	B = 0;

	const TCHAR * t = pszText;

	while(t && *t)
	{
		if ((*t == TCHAR('-')) || (*t == TCHAR(':')))
		{
			p = &B;
		}
		else if (isdigit(TCHAR(*t)))
		{
			*p = (*p) * 10 + (*t - TCHAR('0'));
		}
		else
			return 1;
		t++;
	}

	if (A == 0)
		A = B;
	else if (B == 0)
		B = A;
	
	return 0;
}


int CCommandLineVCal::GetArg_Time(const char * str, VCTIME &vc)
{
	double l = 0.0;
	double sig = 1.0;
	double coma = 10.0;
	bool after_coma = false;
	bool is_deg = false;

	const char * s = str;

	while(*s)
	{
		switch(*s)
		{
		case '0': case '1':
		case '2': case '3': case '4': case '5':
		case '6': case '7': case '8': case '9':
			if (after_coma)
			{
				if (is_deg)
				{
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
			}
			break;
		case ':':
			after_coma = true;
			is_deg = true;
			break;
		default:
			return SetArgLastError(14);
		}
		s++;
	}

	vc.shour = l / 24.0;

	return NULL;
}
