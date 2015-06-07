#include <stdafx.h>


class AVC_MEM_PAGE
{
public:
	AVC_MEM_PAGE * pNext;
	int used;
	char szMem[4096];
	AVC_MEM_PAGE * getLast() {
		AVC_MEM_PAGE * cand = this;
		while(cand->pNext != NULL)
			cand = cand->pNext;
		return cand;
	}
	char * giveBytes(int nBytes) {
		char * p;
		if (nBytes > 4096)
			return NULL;
		if (used + nBytes <= 4096)
		{
			p = szMem + used;
			used += nBytes;
		}
		else if (pNext != NULL)
		{
			AVC_MEM_PAGE * last = getLast();
			if (last == NULL)
				return NULL;
			return last->giveBytes(nBytes);
		}
		else
		{
			pNext = new AVC_MEM_PAGE;
			if (pNext == NULL)
				return NULL;
			return pNext->giveBytes(nBytes);
		}
		return p;
	}
	AVC_MEM_PAGE() { pNext = NULL; used = 0; }
	~AVC_MEM_PAGE() { }
};

AVC_MEM_PAGE * gp_memory = NULL;

char * AvcAllocMemory(int nLen)
{
	if (nLen > 4096)
		return NULL;

	if (gp_memory == NULL)
	{
		gp_memory = new AVC_MEM_PAGE;
		if (gp_memory == NULL)
			return NULL;
	}
	
	return gp_memory->giveBytes(nLen);
}

const char *AvcAllocString(const char *str)
{
	int i = strlen(str);
	char * pMem = AvcAllocMemory(i+2);
	if (pMem != NULL)
	{
		strcpy(pMem, str);
	}
	return pMem;
}

