#include "stdafx.h"
#include "GCRasi.h"
#include "gmath.h"

GCRasi::GCRasi(void)
{
}


GCRasi::~GCRasi(void)
{
}

/*********************************************************************/
/*                                                                   */
/* Calculation of Rasi from sun-logitude and ayanamsa                */
/*                                                                   */
/*********************************************************************/

int GCRasi::GetRasi(double SunLongitude, double Ayanamsa)
{
	return (int)floor(put_in_360(SunLongitude - Ayanamsa)/30.0);
}
