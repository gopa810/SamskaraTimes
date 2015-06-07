#include "stdafx.h"
#include "TResultEvent.h"

// PORTABLE

TResultEvents::TResultEvents()
{
	b_sorted = true;
	p_events = NULL;
	n_count = 0;
	n_size = 0;
	e_ptr = NULL;
	m_options = 0;
}

TResultEvents::~TResultEvents()
{
	if (p_events != NULL)
	{
		delete [] p_events;
		p_events = NULL;
	}
	if (e_ptr != NULL)
	{
		delete [] e_ptr;
		e_ptr = NULL;
	}
}
Boolean TResultEvents::AddEvent(VCTIME inTime, int inType, int inData, int inDst)
{
	if (p_events == NULL)
	{
		p_events = new TDayEvent[64];
		if (p_events == NULL)
			return false;
		n_size = 64;
	}
	if (n_count >= n_size)
	{
		TDayEvent * p = new TDayEvent[n_size + 64];
		if (p == NULL)
			return false;
		for(unsigned int i = 0; i < n_count; i++)
			p[i] = p_events[i];
		delete [] p_events;
		n_size += 64;
		p_events = p;
	}
	switch(inDst)
	{
	case 0:
		p_events[n_count].nDst = 0;
		break;
	case 1:
		if (inTime.shour >= 2/24.0)
		{
			inTime.shour += 1/24.0;
			inTime.NormalizeValues();
			p_events[n_count].nDst = 1;
		}
		else
		{
			p_events[n_count].nDst = 0;
		}
		break;
	case 2:
		inTime.shour += 1/24.0;
		inTime.NormalizeValues();
		p_events[n_count].nDst = 1;
		break;
	case 3:
		if (inTime.shour <= 2/24.0)
		{
			inTime.shour += 1/24.0;
			inTime.NormalizeValues();
			p_events[n_count].nDst = 1;
		}
		else
		{
			p_events[n_count].nDst = 0;
		}
		break;
	default:
		p_events[n_count].nDst = 0;
	}
	p_events[n_count].Time = inTime;
	p_events[n_count].nData = inData;
	p_events[n_count].nType = inType;
	n_count++;
	return true;
}

void TResultEvents::Sort(Boolean inSort)
{
	unsigned int i, j;
	TDayEvent * p;

	b_sorted = inSort;
	if (inSort == false)
		return;

	if (e_ptr != NULL)
	{
		delete [] e_ptr;
		e_ptr = NULL;
	}

	e_ptr = new TDayEventPtr[n_size];
	if (e_ptr == NULL)
	{
		b_sorted = false;
		return;
	}

	for(i = 0; i < n_count; i++)
		e_ptr[i] = &(p_events[i]);

	for(i = 0; i < n_count - 1; i++)
	{
		for(j = i+1; j < n_count; j++)
		{
			if ((e_ptr[i]->Time.GetDayInteger() + e_ptr[i]->Time.shour + e_ptr[i]->nDst/24.0) 
				> (e_ptr[j]->Time.GetDayInteger() + e_ptr[j]->Time.shour + e_ptr[j]->nDst/24.0))
			{
				p = e_ptr[i];
				e_ptr[i] = e_ptr[j];
				e_ptr[j] = p;
			}
		}
	}
}

void TResultEvents::clear()
{
	n_count = 0;
	if (e_ptr != NULL)
	{
		delete [] e_ptr;
		e_ptr = NULL;
	}
}
