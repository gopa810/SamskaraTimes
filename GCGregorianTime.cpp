#include "stdafx.h"
#include "GCGregorianTime.h"
#include "GCStrings.h"
#include "math.h"

VCTIME::VCTIME() { 
	year = 0;
	month = 0;
	dayOfWeek = 0;
	day = 0;
	shour = 0.0;
	tzone = 0.0;
}

VCTIME::~VCTIME(void)
{
}

bool VCTIME::operator<(VCTIME &date)
{
	int y1, y2, m1, m2, d1, d2;
	double h1, h2;
	d1 = this->day;
	d2 = date.day;
	m1 = this->month;
	m2 = date.month;
	y1 = this->year;
	y2 = date.year;
	h1 = shour + tzone/24.0;
	h2 = date.shour + date.tzone/24.0;

	NormalizeValues(y1, m1, d1, h1);
	NormalizeValues(y2, m2, d2, h2);

	if (y1 > y2)
		return false;
	else if (y1 < y2)
		return true;
	else
	{
		if (m1 > m2)
			return false;
		else if (m1 < m2)
			return true;
		else
		{
			if (d1 < d2)
				return true;
			else 
				return false;
		}
	}
}

bool VCTIME::operator<=(VCTIME &date)
{
	int y1, y2, m1, m2, d1, d2;
	double h1, h2;

	d1 = this->day;
	d2 = date.day;
	m1 = this->month;
	m2 = date.month;
	y1 = this->year;
	y2 = date.year;
	h1 = shour + tzone/24.0;
	h2 = date.shour + date.tzone/24.0;

	NormalizeValues(y1, m1, d1, h1);
	NormalizeValues(y2, m2, d2, h2);

	if (y1 > y2)
		return false;
	else if (y1 < y2)
		return true;
	else
	{
		if (m1 > m2)
			return false;
		else if (m1 < m2)
			return true;
		else
		{
			if (d1 <= d2)
				return true;
			else 
				return false;
		}
	}
}

bool VCTIME::operator==(VCTIME &date)
{
	int y1, y2, m1, m2, d1, d2;
	double h1, h2;

	d1 = this->day;
	d2 = date.day;
	m1 = this->month;
	m2 = date.month;
	y1 = this->year;
	y2 = date.year;
	h1 = shour + tzone/24.0;
	h2 = date.shour + date.tzone/24.0;

	NormalizeValues(y1, m1, d1, h1);
	NormalizeValues(y2, m2, d2, h2);

	return ((y1 == y2) && (m1 == m2) && (d1 == d2));

}

void VCTIME::NormalizeValues(int &y1, int &m1, int &d1, double &h1)
{

	if (h1 < 0.0)
	{
		d1--;
		h1 += 1.0;
	}
	else if (h1 >= 1.0)
	{
		h1 -= 1.0;
		d1++;
	}
	if (d1 < 1)
	{
		m1--;
		if (m1 < 1)
		{
			m1 = 12;
			y1--;
		}
		d1 = VCTIME::GetMonthMaxDays(y1, m1);
	}
	else if (d1 > VCTIME::GetMonthMaxDays(y1, m1))
	{
		m1++;
		if (m1 > 12)
		{
			m1 = 1;
			y1++;
		}
		d1 = 1;
	}

}

int VCTIME::GetMonthMaxDays(int year, int month)
{
	int m_months_ovr[13] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; 
	int m_months[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; 

	if (VCTIME::IsLeapYear(year))
		return m_months_ovr[month];
	else
		return m_months[month];
}

bool VCTIME::IsLeapYear(int year)
{
	if ((year % 4) == 0)
	{
		if ((year % 100 == 0) && (year % 400 != 0))
			return false;
		else
			return true;
	}

	return false;
}

void VCTIME::ChangeTimeZone(double tZone)
{
	shour += (tZone - tzone)/24;
	NormalizeValues(year, month, day, shour);
	tzone = tZone;
}

int VCTIME::GetJulianInteger()
{
	int yy = year - int((12 - month) / 10);
	int mm = month + 9;

	if (mm >= 12)
		mm -= 12;

	int k1, k2, k3;
	int j;

	k1 = int (floor(365.25 * (yy + 4712)));
	k2 = int (floor(30.6 * mm + 0.5));
	k3 = int (floor(floor((double)(yy/100)+49)*.75))-38;
	j = k1 + k2 + day + 59;
	if (j > 2299160)
		j -= k3;

	return j;
}

double VCTIME::GetJulian()
{
	return (double)GetJulianInteger();
}

void VCTIME::NormalizeValues()
{
	NormalizeValues(year, month, day, shour);
}

void VCTIME::PreviousDay()
{
	day--;
	if (day < 1)
	{
		month--;
		if (month < 1)
		{
			month = 12;
			year--;
		}
		day = VCTIME::GetMonthMaxDays(year, month);
	}
	dayOfWeek = (dayOfWeek + 6) % 7;
}

void VCTIME::NextDay()
{
	day++;
	if (day > VCTIME::GetMonthMaxDays(year, month))
	{
		month++;
		if (month > 12)
		{
			month = 1;
			year++;
		}
		day = 1;
	}
	dayOfWeek = (dayOfWeek + 1) % 7;
}

void VCTIME::operator+=(int n)
{
	for(int i = 0; i < n; i++)
		NextDay();
}

void VCTIME::operator-=(int n)
{
	for(int i = 0; i < n; i++)
		PreviousDay();
}

double VCTIME::GetJulianDetailed()
{
	return GetJulian() - 0.5 + shour;
}

double VCTIME::GetJulianComplete()
{
	return GetJulian() - 0.5 + shour - tzone/24.0;
}

void VCTIME::InitWeekDay()
{
	dayOfWeek = (int(GetJulian()) + 1) % 7;
}

//***********************************************************************/
//* Name:    calcDateFromJD								*/
//* Type:    Function									*/
//* Purpose: Calendar date from Julian Day					*/
//* Arguments:										*/
//*   jd   : Julian Day									*/
//* Return value:										*/
//*   String date in the form DD-MONTHNAME-YYYY					*/
//* Note:											*/
//***********************************************************************/

void VCTIME::SetFromJulian(double jd)
{
	double z = floor(jd + 0.5);

	double f = (jd + 0.5) - z;

	double A, B, C, D, E, alpha;

	if (z < 2299161.0)
	{
		A = z;
	} 
	else 
	{
		alpha = floor((z - 1867216.25)/36524.25);
		A = z + 1.0 + alpha - floor(alpha/4.0);
	}

	B = A + 1524;
	C = floor((B - 122.1)/365.25);
	D = floor(365.25 * C);
	E = floor((B - D)/30.6001);
	day = (int) floor(B - D - floor(30.6001 * E) + f);
	month = int ((E < 14) ? E - 1 : E - 13);
	year = int((month > 2) ? C - 4716 : C - 4715);
	tzone = 0.0;
	shour = modf(jd + 0.5, &z);
}


int VCTIME::operator=(int i)
{
	year = i;
	month = i;
	day = i;
	shour = 0.0;
	tzone = 0.0;

	return i;
}

bool VCTIME::IsBeforeThis(VCTIME &date)
{
	int y1, y2, m1, m2, d1, d2;
	d1 = this->day;
	d2 = date.day;
	m1 = this->month;
	m2 = date.month;
	y1 = this->year;
	y2 = date.year;

	if (y1 > y2)
		return false;
	else if (y1 < y2)
		return true;
	else if (m1 > m2)
		return false;
	else if (m1 < m2)
		return true;
	else if (d1 < d2)
		return true;
	else 
		return false;
}

void VCTIME::Today()
{
	SYSTEMTIME st;
	TIME_ZONE_INFORMATION tzi;
	DWORD dw;


	GetLocalTime(&st);

	day = st.wDay;
	month = st.wMonth;
	year = st.wYear;
	shour = 0.5;
	tzone = 0;

	dw = GetTimeZoneInformation(&tzi);
	switch(dw)
	{
	case TIME_ZONE_ID_DAYLIGHT:
		shour = -tzi.DaylightBias / 1440.0;
		tzone = -tzi.Bias / 60.0;
		break;
	case TIME_ZONE_ID_STANDARD:
		shour = 0.0;
		tzone = -tzi.Bias / 60.0;
		break;
	}
}

// vracia -1, ak zadany den je den nasledujuci po THIS
// vracia 1 ak THIS je nasledujuci den po zadanom dni

int VCTIME::CompareYMD(VCTIME v)
{
	if (v.year < year)
		return (year - v.year) * 365;
	else if (v.year > year)
		return (year - v.year) * 365;

	if (v.month < month)
		return (month - v.month)*31;
	else if (v.month > month)
		return (month - v.month)*31;

	return (day - v.day);
}

int VCTIME::GetHour()
{
	return int(floor(shour*24));
}

int VCTIME::GetMinute()
{
	return int(floor((shour*24 - int(shour*24)) * 60));
}

int VCTIME::GetMinuteRound()
{
	return int(floor((shour*24 - int(shour*24)) * 60 + 0.5));
}

int VCTIME::GetDayInteger()
{
	return year * 384 + month * 32 + day;
}

int VCTIME::GetSecond()
{
	return int(floor((shour*1440 - int(floor(shour*1440))) * 60));
}

const char * VCTIME::c_str()
{
	static char sz[36];

	sprintf(sz, "%2d %s %d  %02d:%02d:%02d", day, GCStrings::GetMonthAbreviation(month), year, GetHour(), GetMinute(), GetSecond());

	return sz;
}

void VCTIME::GetDateTextWithTodayExt(TString &str, VCTIME vc)
{
	if ((vc.day > 0) && (vc.day < 32) && (vc.month > 0) && (vc.month < 13) && (vc.year >= 1500) && (vc.year < 4000))
	{
		VCTIME * today = new VCTIME();
		int diff = today->GetJulianInteger() - vc.GetJulianInteger();
		if (diff == 0)
		{
			str.Format("%d %s %d (%s)", vc.day, GCStrings::GetMonthAbreviation(vc.month), vc.year, GCStrings::getString(43).c_str());
		}
		else if (diff == -1)
		{
			str.Format("%d %s %d (%s)", vc.day, GCStrings::GetMonthAbreviation(vc.month), vc.year, GCStrings::getString(854).c_str());
		}
		else if (diff == 1)
		{
			str.Format("%d %s %d (%s)", vc.day, GCStrings::GetMonthAbreviation(vc.month), vc.year, GCStrings::getString(853).c_str());
		}
		else
		{
			str.Format("%d %s %d", vc.day, GCStrings::GetMonthAbreviation(vc.month), vc.year);
		}
	}
}

double VCTIME::CalculateJulianDay(int year, int month, int day)
{
	int yy = year - int((12 - month) / 10);
	int mm = month + 9;

	if (mm >= 12)
		mm -= 12;

	int k1, k2, k3;
	int j;

	k1 = int (floor(365.25 * (yy + 4712)));
	k2 = int (floor(30.6 * mm + 0.5));
	k3 = int (floor(floor((double)(yy/100)+49)*.75))-38;
	j = k1 + k2 + day + 59;
	if (j > 2299160)
		j -= k3;

	return double(j);
}

