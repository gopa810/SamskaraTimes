#pragma once

#include "GCGregorianTime.h"

class GCSankranti
{
public:
	GCSankranti(void);
	~GCSankranti(void);

	static int GetSankrantiType(void);
	static int SetSankrantiType(int i);
	static const char * GetSankMethodName(int i);
	static VCTIME GetNextSankranti( VCTIME startDate, int &zodiac);
};

