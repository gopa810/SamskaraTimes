#pragma once


class DAYTIME
{
public:
	int hour;
	int min;
	int sec;
	int mili;

	double GetDayTime(void);
	bool operator<(DAYTIME &dt);
	bool operator>(DAYTIME &dt);
	bool operator>=(DAYTIME &dt);
	bool operator<=(DAYTIME &dt);
	void operator+=(int mn);
	void operator-=(int mn);
	void SetValue(int i);
	void SetDayTime(double d);
	void SetDegTime(double);
};



