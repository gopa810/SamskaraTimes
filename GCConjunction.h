#pragma once

#include "GCGregorianTime.h"
#include "GCEarthData.h"

class GCConjunction
{
public:
	GCConjunction(void);
	~GCConjunction(void);
	static bool IsConjunction(double m1, double s1, double s2, double m2);
    static double GetPrevConjunction(VCTIME &, EARTHDATA);
    static double GetNextConjunction(VCTIME &, EARTHDATA);
    static double GetPrevConjunction(VCTIME, VCTIME &, bool, EARTHDATA);
    static double GetNextConjunction(VCTIME, VCTIME &, bool, EARTHDATA);

};

