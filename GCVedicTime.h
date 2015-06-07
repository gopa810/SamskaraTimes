#pragma once


class VATIME
{
public:
	int tithi;
	int masa;
	int gyear;

	VATIME();
	VATIME(int t, int m, int y);
	void next();
	void prev();
};



