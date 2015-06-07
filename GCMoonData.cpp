#include "stdafx.h"
#include "GCMoonData.h"
#include "gmath.h"
#include "GCAyanamsha.h"

MOONDATA::MOONDATA(void)
{
}


MOONDATA::~MOONDATA(void)
{
}

void MOONDATA::Calculate(double jdate, EARTHDATA earth)
{
	const int arg_lr[60][4] = {
		 { 0, 0, 1, 0},
		 { 2, 0,-1, 0},
		 { 2, 0, 0, 0},
		 { 0, 0, 2, 0},
		 { 0, 1, 0, 0},
		 { 0, 0, 0, 2},
		 { 2, 0,-2, 0},
		 { 2,-1,-1, 0},
		 { 2, 0, 1, 0},
		 { 2,-1, 0, 0},
		 { 0, 1,-1, 0},
		 { 1, 0, 0, 0},
		 { 0, 1, 1, 0},
		 { 2, 0, 0,-2},
		 { 0, 0, 1, 2},
		 { 0, 0, 1,-2},
		 { 4, 0,-1, 0},
		 { 0, 0, 3, 0},
		 { 4, 0,-2, 0},
		 { 2, 1,-1, 0},
		 { 2, 1, 0, 0},
		 { 1, 0,-1, 0},
		 { 1, 1, 0, 0},
		 { 2,-1, 1, 0},
		 { 2, 0, 2, 0},
		 { 4, 0, 0, 0},
		 { 2, 0,-3, 0},
		 { 0, 1,-2, 0},
		 { 2, 0,-1, 2},
		 { 2,-1,-2, 0},
		 { 1, 0, 1, 0},
		 { 2,-2, 0, 0},
		 { 0, 1, 2, 0},
		 { 0, 2, 0, 0},
		 { 2,-2,-1, 0},
		 { 2, 0, 1,-2},
		 { 2, 0, 0, 2},
		 { 4,-1,-1, 0},
		 { 0, 0, 2, 2},
		 { 3, 0,-1, 0},
		 { 2, 1, 1, 0},
		 { 4,-1,-2, 0},
		 { 0, 2,-1, 0},
		 { 2, 2,-1, 0},
		 { 2, 1,-2, 0},
		 { 2,-1, 0,-2},
		 { 4, 0, 1, 0},
		 { 0, 0, 4, 0},
		 { 4,-1, 0, 0},
		 { 1, 0,-2, 0},
		 { 2, 1, 0,-2},
		 { 0, 0, 2,-2},
		 { 1, 1, 1, 0},
		 { 3, 0,-2, 0},
		 { 4, 0,-3, 0},
		 { 2,-1, 2, 0},
		 { 0, 2, 1, 0},
		 { 1, 1,-1, 0},
		 { 2, 0, 3, 0},
		 { 2, 0,-1,-2}
	   };

	  const int arg_b[60][4] = {
		 { 0, 0, 0, 1},
		 { 0, 0, 1, 1},
		 { 0, 0, 1,-1},
		 { 2, 0, 0,-1},
		 { 2, 0,-1, 1},
		 { 2, 0,-1,-1},
		 { 2, 0, 0, 1},
		 { 0, 0, 2, 1},
		 { 2, 0, 1,-1},
		 { 0, 0, 2,-1}, // {* !!! Error in German Meeus *}
		 { 2,-1, 0,-1},
		 { 2, 0,-2,-1},
		 { 2, 0, 1, 1},
		 { 2, 1, 0,-1},
		 { 2,-1,-1, 1},
		 { 2,-1, 0, 1},
		 { 2,-1,-1,-1},
		 { 0, 1,-1,-1},
		 { 4, 0,-1,-1},
		 { 0, 1, 0, 1},
		 { 0, 0, 0, 3},
		 { 0, 1,-1, 1},
		 { 1, 0, 0, 1},
		 { 0, 1, 1, 1},
		 { 0, 1, 1,-1},
		 { 0, 1, 0,-1},
		 { 1, 0, 0,-1},
		 { 0, 0, 3, 1},
		 { 4, 0, 0,-1},
		 { 4, 0,-1, 1},
		 { 0, 0, 1,-3},
		 { 4, 0,-2, 1},
		 { 2, 0, 0,-3},
		 { 2, 0, 2,-1},
		 { 2,-1, 1,-1},
		 { 2, 0,-2, 1},
		 { 0, 0, 3,-1},
		 { 2, 0, 2, 1},
		 { 2, 0,-3,-1},
		 { 2, 1,-1, 1},
		 { 2, 1, 0, 1},
		 { 4, 0, 0, 1},
		 { 2,-1, 1, 1},
		 { 2,-2, 0,-1},
		 { 0, 0, 1, 3},
		 { 2, 1, 1,-1},
		 { 1, 1, 0,-1},
		 { 1, 1, 0, 1},
		 { 0, 1,-2,-1},
		 { 2, 1,-1,-1},
		 { 1, 0, 1, 1},
		 { 2,-1,-2,-1},
		 { 0, 1, 2, 1},
		 { 4, 0,-2,-1},
		 { 4,-1,-1,-1},
		 { 1, 0, 1,-1},
		 { 4, 0, 1,-1},
		 { 1, 0,-1,-1},
		 { 4,-1, 0,-1},
		 { 2,-2, 0, 1}
		};
	  const int sigma_r[60] = {
	   -20905355,
		-3699111,
		-2955968,
		 -569925,
		   48888,
		   -3149,
		  246158,
		 -152138,
		 -170733,
		 -204586,
		 -129620,
		  108743,
		  104755,
		   10321,
			   0,
		   79661,
		  -34782,
		  -23210,
		  -21636,
		   24208,
		   30824,
		   -8379,
		  -16675,
		  -12831,
		  -10445,
		  -11650,
		   14403,
		   -7003,
			   0,
		   10056,
			6322,
		   -9884,
			5751,
			   0,
		   -4950,
			4130,
			   0,
		   -3958,
			   0,
			3258,
			2616,
		   -1897,
		   -2117,
			2354,
			   0,
			   0,
		   -1423,
		   -1117,
		   -1571,
		   -1739,
			   0,
		   -4421,
			   0,
			   0,
			   0,
			   0,
			1165,
			   0,
			   0,
			8752
				  };
	  const int sigma_l[60] = {
		6288774,
		1274027,
		 658314,
		 213618,
		-185116,
		-114332,
		  58793,
		  57066,
		  53322,
		  45758,
		 -40923,
		 -34720,
		 -30383,
		  15327,
		 -12528,
		  10980,
		  10675,
		  10034,
		   8548,
		  -7888,
		  -6766,
		  -5163,
		   4987,
		   4036,
		   3994,
		   3861,
		   3665,
		  -2689,
		  -2602,
		   2390,
		  -2348,
		   2236,
		  -2120,
		  -2069,
		   2048,
		  -1773,
		  -1595,
		   1215,
		  -1110,
		   -892,
		   -810,
			759,
		   -713,
		   -700,
			691,
			596,
			549,
			537,
			520,
		   -487,
		   -399,
		   -381,
			351,
		   -340,
			330,
			327,
		   -323,
			299,
			294,
			  0
		};
	  const int sigma_b[60] = {
		5128122,
		 280602,
		 277693,
		 173237,
		  55413,
		  46271,
		  32573,
		  17198,
		   9266,
		   8822,
		   8216,
		   4324,
		   4200,
		  -3359,
		   2463,
		   2211,
		   2065,
		  -1870,
		   1828,
		  -1794,
		  -1749,
		  -1565,
		  -1491,
		  -1475,
		  -1410,
		  -1344,
		  -1335,
		   1107,
		   1021,
			833,
			777,
			671,
			607,
			596,
			491,
		   -451,
			439,
			422,
			421,
		   -366,
		   -351,
			331,
			315,
			302,
		   -283,
		   -229,
			223,
			223,
		   -220,
		   -220,
		   -185,
			181,
		   -177,
			176,
			166,
		   -164,
			132,
		   -119,
			115,
			107
		};

	double t,d,m,ms,f,e,ls;// : extended;
	double sr,sl,sb,temp;// : extended;
	double a1,a2,a3; // : extended;
	double lambda,beta,delta; //: extended;
	int i; //: integer;


	t = (jdate - 2451545.0)/36525.0;

	//(* mean elongation of the moon  
	d = 297.8502042+(445267.1115168+(-0.0016300+(1.0/545868-1.0/113065000*t)*t)*t)*t;

	//(* mean anomaly of the sun  
	m =357.5291092+(35999.0502909+(-0.0001536+1.0/24490000*t)*t)*t;

	//(* mean anomaly of the moon  
	ms =134.9634114+(477198.8676313+(0.0089970+(1.0/69699-1.0/1471200*t)*t)*t)*t;

	//(* argument of the longitude of the moon  
	f =93.2720993+(483202.0175273+(-0.0034029+(-1.0/3526000+1.0/863310000*t)*t)*t)*t;

	//(* correction term due to excentricity of the earth orbit  
	e = 1.0+(-0.002516-0.0000074*t)*t;

	//(* mean longitude of the moon  
	ls =218.3164591+(481267.88134236+(-0.0013268+(1.0/538841-1.0/65194000*t)*t)*t)*t;

	//(* arguments of correction terms  
	a1 =119.75+131.849*t;
	a2 =53.09+479264.290*t;
	a3 =313.45+481266.484*t;

	sr =0;
	for(i = 0; i < 60; i++)
	{
		temp =sigma_r[i]*cos_d( arg_lr[i][0]*d
							   +arg_lr[i][1]*m
							   +arg_lr[i][2]*ms
							   +arg_lr[i][3]*f);
		if (abs(arg_lr[i][1])==1) temp =temp*e;
		if (abs(arg_lr[i][1])==2) temp =temp*e*e;
		sr =sr+temp;
	}

	sl =0;
	for(i =0; i < 60; i++)
	{
		temp =sigma_l[i]*sin_d( arg_lr[i][0]*d
							   +arg_lr[i][1]*m
							   +arg_lr[i][2]*ms
							   +arg_lr[i][3]*f);
		if (abs(arg_lr[i][1])==1) temp =temp*e;
		if (abs(arg_lr[i][1])==2) temp =temp*e*e;
		sl =sl+temp;
	}

	//(* correction terms  
	sl =sl +3958*sin_d(a1)
		+1962*sin_d(ls-f)
		+318*sin_d(a2);
	sb =0;
	for(i=0; i < 60; i++)
	{
		temp = sigma_b[i]*sin_d( arg_b[i][0]*d
							   +arg_b[i][1]*m
							   +arg_b[i][2]*ms
							   +arg_b[i][3]*f);
		if (abs(arg_b[i][1])==1) temp=temp*e;
		if (abs(arg_b[i][1])==2) temp=temp*e*e;
		sb=sb+temp;
	}

	//(* correction terms  
	sb =sb -2235*sin_d(ls)
		  +382*sin_d(a3)
		  +175*sin_d(a1-f)
		  +175*sin_d(a1+f)
		  +127*sin_d(ls-ms)
		  -115*sin_d(ls+ms);

	lambda=ls+sl/1000000;
	beta=sb/1000000;
	delta=385000.56+sr/1000;

	this->radius = delta;
	this->longitude_deg =lambda;
	this->latitude_deg = beta;

	EARTHDATA::calc_geocentric(this->longitude_deg, this->latitude_deg, this->rektaszension, this->declination, jdate);

}

//==================================================================================
//
//==================================================================================

void MOONDATA::CalcMoonTimes(EARTHDATA e, VCTIME vc, double nDaylightSavingShift, DAYTIME &rise, DAYTIME &set)
{
	double UT;
	int i;
	double prev_elev;
	int nType, nFound = 0;
	double a, ae, b, be, c, ce, elev;

	rise.SetValue(-1);
	set.SetValue(-1);

	// inicializacia prvej hodnoty ELEVATION
	vc.shour = (-nDaylightSavingShift - 1.0) / 24.0;
	prev_elev = MoonCalcElevation(e, vc);

	// prechod cez vsetky hodiny
	for(UT = (- 0.1 - nDaylightSavingShift); UT <= (24.1 - nDaylightSavingShift); UT+=1.0)
	{
		vc.shour = UT / 24.0;
		elev = MoonCalcElevation(e, vc);
		
		if (prev_elev * elev <= 0.0)
		{
			if (prev_elev <= 0.0)
			{
				nType = 0x1;
			}
			else
			{
				nType = 0x2;
			}
			
			a = UT - 1.0;
			ae = prev_elev;
			b = UT;
			be = elev;
			for(i = 0; i < 20; i++)
			{
				c = (a + b) / 2.0;
				vc.shour = c / 24.0;
				ce = MoonCalcElevation(e, vc);
				if (ae*ce <= 0.0)
				{
					be = ce;
					b = c;
				}
				else
				{
					ae = ce;
					a = c;
				}
			}

			if (nType == 1)
			{
				rise.SetDayTime((c + nDaylightSavingShift)/24.0);
			}
			else
			{
				set.SetDayTime((c + nDaylightSavingShift)/24.0);
			}

			nFound |= nType;

			if (nFound == 0x3)
				break;
		}

		prev_elev = elev;
	}

}

int MOONDATA::GetNextMoonRasi(EARTHDATA ed, VCTIME startDate, VCTIME &nextDate)
{
	double phi = 30.0;
	double l1, l2;
	double jday = startDate.GetJulianComplete();
	MOONDATA moon;
	VCTIME d = startDate;
	double ayanamsa = GCAyanamsha::GetAyanamsa(jday);
	double scan_step = 0.5;
	int prev_naks = 0;
	int new_naks = -1;

	double xj;
	VCTIME xd;

	moon.Calculate(jday, ed);
	l1 = put_in_360(moon.longitude_deg - ayanamsa);
	prev_naks = int(floor(l1 / phi));

	int counter = 0;
	while(counter < 20)
	{
		xj = jday;
		xd = d;

		jday += scan_step;
		d.shour += scan_step;
		if (d.shour > 1.0)
		{
			d.shour -= 1.0;
			d.NextDay();
		}

		moon.Calculate(jday, ed);
		l2 = put_in_360(moon.longitude_deg - ayanamsa);
		new_naks = int(floor(l2/phi));
		if (prev_naks != new_naks)
		{
			jday = xj;
			d = xd;
			scan_step *= 0.5;
			counter++;
			continue;
		}
		else
		{
			l1 = l2;
		}
	}
	nextDate = d;
	return new_naks;
}

//==================================================================================
//
//==================================================================================

VCTIME MOONDATA::GetNextRise(EARTHDATA e, VCTIME vc, bool bRise)
{
	int nFound = 0;
	double a, b;

	double h[3];
	double hour = 1/24.0;
	double startHour = vc.shour;

	VCTIME track = vc;
	track.NormalizeValues();

	// inicializacia prvej hodnoty ELEVATION
	h[0] = MoonCalcElevation(e, track);
	track.shour += hour;
	h[1] = MoonCalcElevation(e, track);
	track.shour += hour;
	h[2] = MoonCalcElevation(e, track);

	for(int c = 0; c < 24; c++)
	{
		if ((bRise ? (h[1] < 0.0 && h[2] > 0.0) : (h[1] > 0.0 && h[2] < 0.0)))
		{
			a = (h[2] - h[1]) / hour;
			b = h[2] - a * track.shour;
			track.shour = - b / a;
			track.NormalizeValues();
			return track;
		}

		h[0] = h[1];
		h[1] = h[2];
		track.shour += hour;
		h[2] = MoonCalcElevation(e, track);
	}

	return track;
}


//==================================================================================
//
//==================================================================================

double MOONDATA::MoonCalcElevation(EARTHDATA e, VCTIME vc)
{
	MOONDATA moon;
	double d = vc.GetJulianComplete();
	moon.Calculate(d, e);
	moon.correct_position(d, e.latitude_deg, e.longitude_deg, 0);
	moon.calc_horizontal(d, e.longitude_deg, e.latitude_deg);

	return moon.elevation;
}

void MOONDATA::calc_horizontal(double date, double longitude, double latitude)
{
	double h;

	h = put_in_360(EARTHDATA::star_time(date) - this->rektaszension+longitude);
	
	this->azimuth = rad2deg( atan2(sin_d(h),
                           cos_d(h)*sin_d(latitude)-
                           tan_d(this->declination)*cos_d(latitude) ));
	
	this->elevation = rad2deg(asin(sin_d(latitude)*sin_d(this->declination) +
                            cos_d(latitude)*cos_d(this->declination)*cos_d(h)));
}

void MOONDATA::correct_position(double jdate, double latitude, double longitude, double height)
{
	double u,h,delta_alpha;
	double rho_sin, rho_cos;
	const double b_a=0.99664719;

	u =arctan_d(b_a*b_a*tan_d(latitude));
	rho_sin =b_a*sin_d(u)+height/6378140.0*sin_d(latitude);
	rho_cos =cos_d(u)+height/6378140.0*cos_d(latitude);

	this->parallax = arcsin_d(sin_d(8.794/3600)/(MOONDATA::MoonDistance(jdate) / AU));

	h = EARTHDATA::star_time(jdate) - longitude - this->rektaszension;
	delta_alpha = arctan_d(
                (-rho_cos*sin_d(this->parallax)*sin_d(h))/
                (cos_d(this->declination) -
                  rho_cos*sin_d(this->parallax)*cos_d(h)));
	this->rektaszension = this->rektaszension+delta_alpha;
	this->declination =arctan_d(
      (( sin_d(this->declination)
        -rho_sin*sin_d(this->parallax))*cos_d(delta_alpha))/
      ( cos_d(this->declination)
       -rho_cos*sin_d(this->parallax)*cos_d(h)));
}

double MOONDATA::MoonDistance(double jdate)
{
	const int arg_lr[60][4] = {
		 { 0, 0, 1, 0},		 { 2, 0,-1, 0},		 { 2, 0, 0, 0},		 { 0, 0, 2, 0},		 { 0, 1, 0, 0},
		 { 0, 0, 0, 2},		 { 2, 0,-2, 0},		 { 2,-1,-1, 0},		 { 2, 0, 1, 0},		 { 2,-1, 0, 0},
		 { 0, 1,-1, 0},		 { 1, 0, 0, 0},		 { 0, 1, 1, 0},		 { 2, 0, 0,-2},		 { 0, 0, 1, 2},
		 { 0, 0, 1,-2},		 { 4, 0,-1, 0},		 { 0, 0, 3, 0},		 { 4, 0,-2, 0},		 { 2, 1,-1, 0},
		 { 2, 1, 0, 0},		 { 1, 0,-1, 0},		 { 1, 1, 0, 0},		 { 2,-1, 1, 0},		 { 2, 0, 2, 0},
		 { 4, 0, 0, 0},		 { 2, 0,-3, 0},		 { 0, 1,-2, 0},		 { 2, 0,-1, 2},		 { 2,-1,-2, 0},
		 { 1, 0, 1, 0},		 { 2,-2, 0, 0},		 { 0, 1, 2, 0},		 { 0, 2, 0, 0},		 { 2,-2,-1, 0},
		 { 2, 0, 1,-2},		 { 2, 0, 0, 2},		 { 4,-1,-1, 0},		 { 0, 0, 2, 2},		 { 3, 0,-1, 0},
		 { 2, 1, 1, 0},		 { 4,-1,-2, 0},		 { 0, 2,-1, 0},		 { 2, 2,-1, 0},		 { 2, 1,-2, 0},
		 { 2,-1, 0,-2},		 { 4, 0, 1, 0},		 { 0, 0, 4, 0},		 { 4,-1, 0, 0},		 { 1, 0,-2, 0},
		 { 2, 1, 0,-2},		 { 0, 0, 2,-2},		 { 1, 1, 1, 0},		 { 3, 0,-2, 0},		 { 4, 0,-3, 0},
		 { 2,-1, 2, 0},		 { 0, 2, 1, 0},		 { 1, 1,-1, 0},		 { 2, 0, 3, 0},		 { 2, 0,-1,-2}
	   };

	  const int sigma_r[60] = {
	   -20905355,		-3699111,		-2955968,		 -569925,		   48888,		   -3149,		  246158,
		 -152138,		 -170733,		 -204586,		 -129620,		  108743,		  104755,		   10321,
			   0,		   79661,		  -34782,		  -23210,		  -21636,		   24208,		   30824,
		   -8379,		  -16675,		  -12831,		  -10445,		  -11650,		   14403,		   -7003,
			   0,		   10056,			6322,		   -9884,			5751,			   0,		   -4950,
			4130,			   0,		   -3958,			   0,			3258,			2616,		   -1897,
		   -2117,			2354,			   0,			   0,		   -1423,		   -1117,		   -1571,
		   -1739,			   0,		   -4421,			   0,			   0,			   0,			   0,
			1165,			   0,			   0,			8752
				  };

	double temp, t,d,m,ms,f,e,ls,sr;// : extended;

	t = (jdate - 2451545.0)/36525.0;

	//(* mean elongation of the moon  
	d = 297.8502042+(445267.1115168+(-0.0016300+(1.0/545868-1.0/113065000*t)*t)*t)*t;

	//(* mean anomaly of the sun  
	m =357.5291092+(35999.0502909+(-0.0001536+1.0/24490000*t)*t)*t;

	//(* mean anomaly of the moon  
	ms =134.9634114+(477198.8676313+(0.0089970+(1.0/69699-1.0/1471200*t)*t)*t)*t;

	//(* argument of the longitude of the moon  
	f =93.2720993+(483202.0175273+(-0.0034029+(-1.0/3526000+1.0/863310000*t)*t)*t)*t;

	//(* correction term due to excentricity of the earth orbit  
	e = 1.0+(-0.002516-0.0000074*t)*t;

	//(* mean longitude of the moon  
	ls =218.3164591+(481267.88134236+(-0.0013268+(1.0/538841-1.0/65194000*t)*t)*t)*t;
	
	sr =0;

	int i;
	for(i = 0; i < 60; i++)
	{
		temp =sigma_r[i]*cos_d( arg_lr[i][0]*d
							   +arg_lr[i][1]*m
							   +arg_lr[i][2]*ms
							   +arg_lr[i][3]*f);
		if (abs(arg_lr[i][1])==1) temp =temp*e;
		if (abs(arg_lr[i][1])==2) temp =temp*e*e;
		sr =sr+temp;
	}
	
	
	return 385000.56+sr/1000;

}

