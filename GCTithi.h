#pragma once

#include "GCEarthData.h"
#include "GCGregorianTime.h"

class GCTithi
{
public:
	GCTithi(void);
	~GCTithi(void);
	static int GetPrevTithiStart(EARTHDATA ed, VCTIME startDate, VCTIME &nextDate);
	static int GetNextTithiStart(EARTHDATA ed, VCTIME startDate, VCTIME &nextDate);
	static double GetTithiTimes(EARTHDATA, VCTIME vc, double &titBeg, double &titEnd, double sunRise);
	static VCTIME CalcTithiEnd(int nGYear, int nMasa, int nPaksa, int nTithi, EARTHDATA, VCTIME &);
    static VCTIME CalcTithiEndEx(VCTIME vcStart, int GYear, int nMasa, int nPaksa, int nTithi, EARTHDATA earth, VCTIME & endTithi);
    static VCTIME CalcTithiDate(int nGYear, int nMasa, int nPaksa, int nTithi, EARTHDATA earth);


	static int TITHI_EKADASI(int a) 
	{
		return (((a) == 10) || ((a) == 25)); 
	}
	
	static int TITHI_DVADASI(int a)
	{
		return (((a) == 11) || ((a) == 26));
	}
	
	static int TITHI_TRAYODASI(int a)
	{
		return (((a) == 12) || ((a) == 27));
	}

	static int TITHI_CATURDASI(int a) { return (((a) == 13) || ((a) == 28)); }

	static int TITHI_LESS_EKADASI(int a) { return (((a) == 9) || ((a) == 24) || ((a) == 8) || ((a) == 23)); }
	static int TITHI_LESS_DVADASI(int a) { return (((a) == 10) || ((a) == 25) || ((a) == 9) || ((a) == 24)); }
	static int TITHI_LESS_TRAYODASI(int a) { return (((a) == 11) || ((a) == 26) || ((a) == 10) || ((a) == 25)); }
	static int TITHI_FULLNEW_MOON(int a) { return (((a) == 14) || ((a) == 29)); }

	static int PREV_PREV_TITHI(int a) { return (((a) + 28) % 30); }
	static int PREV_TITHI(int a) { return (((a) + 29) % 30); }
	static int NEXT_TITHI(int a) { return (((a) + 1) % 30); }
	static int NEXT_NEXT_TITHI(int a) { return (((a) + 1) % 30); }

	static int TITHI_LESS_THAN(int a, int b) { return (((a) == PREV_TITHI(b)) || ((a) == PREV_PREV_TITHI(b))); }
	static int TITHI_GREAT_THAN(int a, int b) { return (((a) == NEXT_TITHI(b)) || ((a) == NEXT_NEXT_TITHI(b))); }

	// TRUE when transit from A to B is between T and U
	static int TITHI_TRANSIT(int t, int u, int a, int b) 
	{
		return ((t==a) && (u==b)) 
			|| ((t==a) && (u==NEXT_TITHI(b))) 
			|| ((t==PREV_TITHI(a)) && (u == b)); 
	}

};

