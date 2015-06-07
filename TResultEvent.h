#ifndef _TRESULTEVENT________
#define _TRESULTEVENT________
#include "level_0.h"
#include "locationref.h"

class TDayEvent
{
public:
	int nType;
	int nData;
	VCTIME Time;
	int nDst;
};
// PORTABLE

typedef TDayEvent * TDayEventPtr;

class TResultEvents
{
public:
	VCTIME  m_vcStart;
	VCTIME  m_vcEnd;
	UInt32 m_options;
	CLocationRef m_location;
	void clear();
	TDayEventPtr * e_ptr;
	TDayEvent * p_events;
	UInt32      n_count;
	UInt32      n_size;
	Boolean     b_sorted;
	Boolean AddEvent(VCTIME inTime, int inType, int inData, int inDst);
	void Sort(Boolean inSort);
	TDayEvent &operator[](int i)
	{
		if (b_sorted) return *(e_ptr[i]);
		else return p_events[i];
	}
	TResultEvents();
	~TResultEvents();
};


#endif