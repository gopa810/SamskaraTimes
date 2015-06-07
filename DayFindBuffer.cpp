// DayFindBuffer.cpp: implementation of the CDayFindBuffer class.
// PORTABLE
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "vcal5beta.h"
#include "DayFindBuffer.h"
#include "strings.h"
#include "GCStrings.h"
#include "GCSankranti.h"
#include "TTimeZone.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


extern int gp_Fasting[];

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TFinderBuffer::TFinderBuffer()
{

}

TFinderBuffer::~TFinderBuffer()
{

}

int TFinderBuffer::CalculateFindCalendar(int start_year, int start_month, EARTHDATA earth, int nDST)
{
	int i, m, weekday;
	int iCount = 50 - 2*BEFORE_DAYS;
	int nTotalCount = 50;
	VCTIME date, begDate;
	int nYear;

/*	bool bCalcMasa[] = 
		{ true, true, false, false, false, false, false, false, false, false, false, false, false, false, true, 
		true, true, false, false, false, false, false, false, false, false, false, false, false, false, true };
*/
	m_nCount = 0;
	date.day = 1;
	date.month = start_month;
	date.year = start_year;
	date.shour = 0.0;
	date.tzone = earth.tzone;
	begDate = date;

	// alokacia pola
	m_pData = m_rData;

	// inicializacia poctovych premennych
	m_nCount = nTotalCount;
	m_PureCount = iCount;

	for(i = BEFORE_DAYS, date = begDate; i > 0; i--)
	{
		date.PreviousDay();
	}

	weekday = (int(date.GetJulian()) + 1) % 7;

	// 1
	// initialization of days
	for(i = 0; i < nTotalCount; i++)
	{
		m_pData[i].date = date;
		m_pData[i].date.dayOfWeek = weekday;
		m_pData[i].fDateValid = true;
		m_pData[i].fVaisValid = false;
		date.NextDay();
		weekday = (weekday + 1) % 7;
		m_pData[i].moonrise.SetValue(-1);
		m_pData[i].moonset.SetValue(-1);
	}

	// 2
	// calculating moon times

	// 3
	for(i = 0; i < nTotalCount; i++)
	{
		m_pData[i].nDST = TTimeZone::determineDaylightStatus(m_pData[i].date, nDST);
	}

	// 4
	// init of astro data
	for(i = 0; i < nTotalCount; i++)
	{
		m_pData[i].astrodata.DayCalc(m_pData[i].date, earth);
	}

	// 5
	// init of masa
	for(i = 0; i < nTotalCount; i++)
	{
		if ((i == 0) || (m_pData[i-1].astrodata.nPaksa != m_pData[i].astrodata.nPaksa))
		{
			m = m_pData[i].astrodata.MasaCalc(m_pData[i].date, earth);
			nYear = m_pData[i].astrodata.nGaurabdaYear;
		}
		m_pData[i].astrodata.nMasa = m;
		m_pData[i].astrodata.nGaurabdaYear = nYear;
		m_pData[i].fAstroValid = true;
	}

	// 6
	// init of mahadvadasis
	for(i = 2; i < m_PureCount + BEFORE_DAYS + 3; i++)
	{
		m_pData[i].Clear();
		MahadvadasiCalc(i, earth);
	}

	for(i = 3; i < m_PureCount + BEFORE_DAYS + 3; i++)
	{
		EkadasiCalc(i, earth);
	}

	// 7
	// init of festivals
	for(i = BEFORE_DAYS; i < m_PureCount + BEFORE_DAYS + 3; i++)
	{
		CompleteCalc(i, earth);
	}

	// 8
	// init of festivals
	for(i = BEFORE_DAYS; i < m_PureCount + BEFORE_DAYS; i++)
	{
		ExtendedCalc(i, earth);
	}

	// resolve festivals fasting
	for(i = BEFORE_DAYS; i < m_PureCount + BEFORE_DAYS; i++)
	{
		ResolveFestivalsFasting(i);
	}

	// init for sankranti
	date = m_pData[0].date;
	i = 0;
	bool bFoundSan;
	int zodiac;
	int i_target;
	do
	{
		date = GCSankranti::GetNextSankranti(date, zodiac);
		date.shour += TTimeZone::determineDaylightStatus(date, nDST);
		date.NormalizeValues();

		bFoundSan = false;
		for(i=0;i < m_nCount-1;i++)
		{
			i_target = -1;

			switch(GCSankranti::GetSankrantiType())
			{
			case 0:
				if (date.CompareYMD(m_pData[i].date) == 0)
				{
					i_target = i;
				}
				break;
			case 1:
				if (date.CompareYMD(m_pData[i].date) == 0)
				{
					if (date.shour < m_pData[i].astrodata.sun.rise.GetDayTime())
					{
						i_target = i - 1;
					}
					else
					{
						i_target = i;
					}
				}
				break;
			case 2:
				if (date.CompareYMD(m_pData[i].date) == 0)
				{
					if (date.shour > m_pData[i].astrodata.sun.noon.GetDayTime())
					{
						i_target = i+1;
					}
					else
					{
						i_target = i;
					}
				}
				break;
			case 3:
				if (date.CompareYMD(m_pData[i].date) == 0)
				{
					if (date.shour > m_pData[i].astrodata.sun.set.GetDayTime())
					{
						i_target = i+1;
					}
					else
					{
						i_target = i;
					}
				}
				break;
			}

			if (i_target >= 0)
			{
				m_pData[i_target].sankranti_zodiac = zodiac;
				m_pData[i_target].sankranti_day = date;
				bFoundSan = true;
				break;
			}
		}
		date.NextDay();
		date.NextDay();
	}
	while(bFoundSan == true);

	// 9
	// init for festivals dependent on sankranti
	for(i = BEFORE_DAYS; i < m_PureCount + BEFORE_DAYS; i++)
	{
		if (m_pData[i].sankranti_zodiac == MAKARA_SANKRANTI)
		{
			if (m_pData[i].festivals.IsEmpty() == FALSE)
				m_pData[i].festivals += "#";
			m_pData[i].festivals += GCStrings::getString(78);
		}
		else if (m_pData[i].sankranti_zodiac == MESHA_SANKRANTI)
		{
			if (m_pData[i].festivals.IsEmpty() == FALSE)
				m_pData[i].festivals += "#";
			m_pData[i].festivals += GCStrings::getString(79);
		}
		else if (m_pData[i+1].sankranti_zodiac == VRSABHA_SANKRANTI)
		{
			if (m_pData[i].festivals.IsEmpty() == FALSE)
				m_pData[i].festivals += "#";
			m_pData[i].festivals += GCStrings::getString(80);
		}
	}

	m_pData = NULL;

	return 1;


}

int TFinderBuffer::GetStartIndex()
{
	return BEFORE_DAYS;
}

int TFinderBuffer::GetUpperBound()
{
	return BEFORE_DAYS + 31;
}
