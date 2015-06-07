#pragma once

#include "GCGregorianTime.h"
#include "GCEarthData.h"
#include "GCVedicTime.h"

class GCCalendar
{
public:
	GCCalendar(void);
	~GCCalendar(void);

	static int	GetGaurabdaYear(VCTIME vc, EARTHDATA earth);
	static void VATIMEtoVCTIME(VATIME va, VCTIME &vc, EARTHDATA earth);
    static void VCTIMEtoVATIME(VCTIME vc, VATIME &va, EARTHDATA earth);
	static int CalcEndDate(EARTHDATA m_earth, VCTIME vcStart, VATIME vaStart, VCTIME &vcEnd, VATIME &vaEnd, int nType, int nCount);
	static int ComboMasaToMasa(int nComboMasa);
	static int MasaToComboMasa(int nComboMasa);
};

