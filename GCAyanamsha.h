#pragma once
class GCAyanamsha
{
public:
	GCAyanamsha(void);
	~GCAyanamsha(void);
	static double GetAyanamsa(double);
	static int GetAyanamsaType();
	static int SetAyanamsaType(int i);
	static const char * GetAyanamsaName(int nType);

};

