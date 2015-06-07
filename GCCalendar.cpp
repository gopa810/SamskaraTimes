#include "stdafx.h"
#include "GCCalendar.h"
#include "GCDayData.h"
#include "GCTithi.h"

GCCalendar::GCCalendar(void)
{
}


GCCalendar::~GCCalendar(void)
{
}

int	GCCalendar::GetGaurabdaYear(VCTIME vc, EARTHDATA earth)
{
	DAYDATA day;

	day.DayCalc(vc, earth);
	day.MasaCalc(vc, earth);

	return day.nGaurabdaYear;
}

//===========================================================================
//
//===========================================================================

void GCCalendar::VATIMEtoVCTIME(VATIME va, VCTIME &vc, EARTHDATA earth)
{
	vc = GCTithi::CalcTithiDate(va.gyear, va.masa, va.tithi / 15, va.tithi % 15, earth);
}

//===========================================================================
//
//===========================================================================

void GCCalendar::VCTIMEtoVATIME(VCTIME vc, VATIME &va, EARTHDATA earth)
{
	DAYDATA day;

	day.DayCalc(vc, earth);
	va.masa = day.MasaCalc(vc, earth);
	va.tithi = day.nTithi;
	va.gyear = day.nGaurabdaYear;
}

int GCCalendar::CalcEndDate(EARTHDATA m_earth, VCTIME vcStart, VATIME vaStart, VCTIME &vcEnd, VATIME &vaEnd, int nType, int nCount)
{
	switch(nType)
	{
	case 1:
		vcEnd = vcStart;
		if (nCount > 30240) nCount = 30240;
		vcEnd += nCount;
		GCCalendar::VCTIMEtoVATIME(vcEnd, vaEnd, m_earth);
		break;
	case 2:
		vcEnd = vcStart;
		if (nCount > 4320) nCount = 4320;
		vcEnd += nCount*7;
		GCCalendar::VCTIMEtoVATIME(vcEnd, vaEnd, m_earth);
		break;
	case 3:
		vcEnd = vcStart;
		if (nCount > 1080) nCount = 1080;
		vcEnd.month += nCount;
		while(vcEnd.month > 12)
		{
			vcEnd.year++;
			vcEnd.month -= 12;
		}
		GCCalendar::VCTIMEtoVATIME(vcEnd, vaEnd, m_earth);
		break;
	case 4:
		vcEnd = vcStart;
		if (nCount > 90) nCount = 90;
		vcEnd.year += nCount;
		GCCalendar::VCTIMEtoVATIME(vcEnd, vaEnd, m_earth);
		break;
	case 5:
		vaEnd = vaStart;
		if (nCount > 30240) nCount = 30240;
		vaEnd.tithi += nCount;
		while(vaEnd.tithi >= 30)
		{
			vaEnd.tithi-=30;
			vaEnd.masa++;
		}
		while(vaEnd.masa >= 12)
		{
			vaEnd.masa -= 12;
			vaEnd.gyear++;
		}
		GCCalendar::VATIMEtoVCTIME(vaEnd, vcEnd, m_earth);
		break;
	case 6:
		vaEnd = vaStart;
		if (nCount > 1080) nCount = 1080;
		vaEnd.masa = GCCalendar::MasaToComboMasa(vaEnd.masa);
		if (vaEnd.masa == ADHIKA_MASA)
		{
			vcEnd = vcStart;
			vcEnd.month += nCount;
			while(vcEnd.month > 12)
			{
				vcEnd.year++;
				vcEnd.month -= 12;
			}
			GCCalendar::VCTIMEtoVATIME(vcEnd, vaEnd, m_earth);
			vaEnd.tithi = vaStart.tithi;
			GCCalendar::VATIMEtoVCTIME(vaEnd, vcEnd, m_earth);
		}
		else
		{
			vaEnd.masa += nCount;
			while(vaEnd.masa >= 12)
			{
				vaEnd.masa -= 12;
				vaEnd.gyear++;
			}
			vaEnd.masa = GCCalendar::ComboMasaToMasa(vaEnd.masa);
			GCCalendar::VATIMEtoVCTIME(vaEnd, vcEnd, m_earth);
		}
		break;
	case 7:
		vaEnd = vaStart;
		if (nCount > 90) nCount = 90;
		vaEnd.gyear += nCount;
		GCCalendar::VATIMEtoVCTIME(vaEnd, vcEnd, m_earth);
		break;
	}

	return 1;
}

int GCCalendar::ComboMasaToMasa(int nComboMasa)
{
	return (nComboMasa == 12) ? 12 : ((nComboMasa + 11) % 12);
}

int GCCalendar::MasaToComboMasa(int nMasa)
{
	return (nMasa == 12) ? 12 : ((nMasa + 1) % 12);
}
