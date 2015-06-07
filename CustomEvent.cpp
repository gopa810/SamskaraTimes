// CustomEvent.cpp: implementation of the CCustomEvent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "vcal5beta.h"
#include "CustomEvent.h"
#include "TFile.h"
#include "TFileRichList.h"
#include "vedic_ui.h"
#include "strings.h"
#include "level_0.h"
#include "GCStrings.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//==============================================================
//
//==============================================================

/*TString gCustomEventTexts[360];*/

//==============================================================
//
//==============================================================

CCustomEventList gCustomEventList;
int              gCustomEventList_Modified = 0;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomEvent::CCustomEvent()
{
	nClass = 0;
	nTithi = 0;
	nMasa = 0;
	nFastType = 0;
	nVisible = 1;
	nUsed = 1;
	nDeleted = 0;
	nSpec = 0;
	next = NULL;
	next_masa = NULL;
	next_in_masa = NULL;
}

//==============================================================
//
//==============================================================

CCustomEvent::~CCustomEvent()
{

}

CCustomEvent * CCustomEventList::add(void)
{
	CCustomEvent * p;

	p = list;
	if (list == NULL)
	{
		list = new CCustomEvent;
		return list;
	}
	while(p->next != NULL)
		p = p->next;
	p->next = new CCustomEvent;
	return (p->next);
}

//==============================================================
//
//==============================================================

int CustomEventListReadFile(const char * pszFile)
{

	TFile csd;
	int tithi, masa;
	TString strA, strB, text;
	CCustomEvent * pce;
	int nRet = -1;

	if (csd.Open(pszFile, "r") == TRUE)
	{
		gCustomEventList.clear();
/*		for(tithi = 0; tithi < 360; tithi++)
		{
			gCustomEventTexts[tithi].Empty();
		}
*/
		nRet ++;
		while(csd.ReadPropertyLine(strA, strB))
		{
			if (strA.CompareNoCase("event") == 0)
			{
				nRet++;
				if (strB.GetLength() > 2)
				{
					strB.Mid(2, strB.GetLength(), text);
					pce = gCustomEventList.add();
					if (pce)
					{
						pce->nTithi  = tithi = strB.GetAt(0) - '@';
						pce->nMasa   = masa  = strB.GetAt(1) - '@';
						if (text.CompareNoCase("Sri Krsna Pusya abhiseka")==0)
							pce->strText = "Sri Krsna Pusya Abhiseka";
						else
							pce->strText = text;
					}

/*					if (tithi >= 0 && tithi < 30 && masa >= 0 && masa < 12)
					{
						if (gCustomEventTexts[tithi + masa*30].IsEmpty() == TRUE)
						{
							gCustomEventTexts[tithi + masa*30] = "[c6]";
							gCustomEventTexts[tithi + masa*30] += text;
						}
						else
						{
							gCustomEventTexts[tithi + masa*30] += "#[c6]";
							gCustomEventTexts[tithi + masa*30] += text;
						}
					}*/
				}
			}
		}

		csd.Close();
	}

	::DeleteFile(pszFile);

	return nRet;
}

int CustomEventList_InitDefault()
{
	gCustomEventList.addEvent(3,0,6,1,"","Sri Abhirama Thakura -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,0,9,1,"","Srila Vrndavana Dasa Thakura -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,0,14,1,"","Sri Gadadhara Pandita -- Appearance",0,1,-10000);
	gCustomEventList.addEvent(1,0,17,1,"","Aksaya Trtiya. Candana Yatra starts. (Continues for 21 days)",0,1,-10000);
	gCustomEventList.addEvent(5,0,21,1,"","Jahnu Saptami",0,1,-10000);
	gCustomEventList.addEvent(1,0,23,1,"","Srimati Sita Devi (consort of Lord Sri Rama) -- Appearance",0,1,-10000);
	gCustomEventList.addEvent(3,0,23,1,"","Sri Madhu Pandita -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,0,23,1,"","Srimati Jahnava Devi -- Appearance",0,1,-10000);
	gCustomEventList.addEvent(1,0,26,1,"","Rukmini Dvadasi",0,1,-10000);
	gCustomEventList.addEvent(4,0,27,1,"","Sri Jayananda Prabhu -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(0,0,28,1,"Lord Nrsimhadeva","Nrsimha Caturdasi: Appearance of Lord Nrsimhadeva",4,1,-10000);
	gCustomEventList.addEvent(1,0,29,1,"","Krsna Phula Dola, Salila Vihara",0,1,-10000);
	gCustomEventList.addEvent(3,0,29,1,"","Sri Paramesvari Dasa Thakura -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(1,0,29,1,"","Sri Sri Radha-Ramana Devaji -- Appearance",0,1,-10000);
	gCustomEventList.addEvent(3,0,29,1,"","Sri Madhavendra Puri -- Appearance",0,1,-10000);
	gCustomEventList.addEvent(3,0,29,1,"","Sri Srinivasa Acarya -- Appearance",0,1,-10000);
	gCustomEventList.addEvent(3,1,4,1,"","Sri Ramananda Raya -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,1,11,1,"","Srila Vrndavana Dasa Thakura -- Appearance",0,1,-10000);
	gCustomEventList.addEvent(3,1,24,1,"","Sri Baladeva Vidyabhusana -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(1,1,24,1,"","Ganga Puja",0,1,-10000);
	gCustomEventList.addEvent(3,1,24,1,"","Srimati Gangamata Gosvamini -- Appearance",0,1,-10000);
	gCustomEventList.addEvent(1,1,27,1,"","Panihati Cida Dahi Utsava",0,1,-10000);
	gCustomEventList.addEvent(1,1,29,1,"","Snana Yatra",0,1,-10000);
	gCustomEventList.addEvent(3,1,29,1,"","Sri Mukunda Datta -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,1,29,1,"","Sri Sridhara Pandita -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,2,0,1,"","Sri Syamananda Prabhu -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,2,4,1,"","Sri Vakresvara Pandita -- Appearance",0,1,-10000);
	gCustomEventList.addEvent(3,2,9,1,"","Sri Srivasa Pandita -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,2,14,1,"","Sri Gadadhara Pandita -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(2,2,14,1,"Bhaktivinoda Thakura","Srila Bhaktivinoda Thakura -- Disappearance",1,1,-10000);
	gCustomEventList.addEvent(3,2,16,1,"","Sri Svarupa Damodara Gosvami -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,2,16,1,"","Sri Sivananda Sena -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,2,20,1,"","Sri Vakresvara Pandita -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(1,2,29,1,"","Guru (Vyasa) Purnima",0,1,-10000);
	gCustomEventList.addEvent(3,2,29,1,"","Srila Sanatana Gosvami -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,3,4,1,"","Srila Gopala Bhatta Gosvami -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,3,7,1,"","Srila Lokanatha Gosvami -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(4,3,8,1,"","The incorporation of ISKCON in New York",0,1,-10000);
	gCustomEventList.addEvent(3,3,18,1,"","Sri Raghunandana Thakura -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(2,3,18,1,"","Sri Vamsidasa Babaji -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(1,3,25,1,"","Radha Govinda Jhulana Yatra begins",0,1,-10000);
	gCustomEventList.addEvent(3,3,26,1,"","Srila Rupa Gosvami -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,3,26,1,"","Sri Gauridasa Pandita -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(1,3,29,1,"","Jhulana Yatra ends",0,1,-10000);
	gCustomEventList.addEvent(0,3,29,1,"Lord Balarama","Lord Balarama -- Appearance",1,1,-10000);
	gCustomEventList.addEvent(4,4,0,1,"","Srila Prabhupada's departure for the USA",0,1,-10000);
	gCustomEventList.addEvent(3,4,19,1,"","Srimati Sita Thakurani (Sri Advaita's consort) -- Appearance",0,1,-10000);
	gCustomEventList.addEvent(1,4,20,1,"","Lalita sasti",0,1,-10000);
	gCustomEventList.addEvent(0,4,22,1,"Srimati Radharani","Radhastami: Appearance of Srimati Radharani",1,1,-10000);
	gCustomEventList.addEvent(0,4,26,1,"Vamanadeva","Sri Vamana Dvadasi: Appearance of Lord Vamanadeva",1,1,-10000);
	gCustomEventList.addEvent(3,4,26,1,"","Srila Jiva Gosvami -- Appearance",0,1,-10000);
	gCustomEventList.addEvent(2,4,27,1,"Bhaktivinoda Thakura","Srila Bhaktivinoda Thakura -- Appearance",1,1,-10000);
	gCustomEventList.addEvent(1,4,28,1,"","Ananta Caturdasi Vrata",0,1,-10000);
	gCustomEventList.addEvent(3,4,28,1,"","Srila Haridasa Thakura -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(1,4,29,1,"","Sri Visvarupa Mahotsava",0,1,-10000);
	gCustomEventList.addEvent(4,4,29,1,"","Acceptance of sannyasa by Srila Prabhupada",0,1,-10000);
	gCustomEventList.addEvent(4,5,6,1,"","Srila Prabhupada's arrival in the USA",0,1,-10000);
	gCustomEventList.addEvent(5,5,21,1,"","Durga Puja",0,1,-10000);
	gCustomEventList.addEvent(1,5,24,1,"","Ramacandra Vijayotsava",0,1,-10000);
	gCustomEventList.addEvent(2,5,24,1,"","Sri Madhvacarya -- Appearance",0,1,-10000);
	gCustomEventList.addEvent(3,5,26,1,"","Srila Raghunatha Dasa Gosvami -- Disappearance",0,1, 1571);
	gCustomEventList.addEvent(3,5,26,1,"","Srila Raghunatha Bhatta Gosvami -- Disappearance",0,1,1505);
	gCustomEventList.addEvent(3,5,26,1,"","Srila Krsnadasa Kaviraja Gosvami -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(1,5,29,1,"","Sri Krsna Saradiya Rasayatra",0,1,-10000);
	gCustomEventList.addEvent(3,5,29,1,"","Sri Murari Gupta -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(5,5,29,1,"","Laksmi Puja",0,1,-10000);
	gCustomEventList.addEvent(3,6,4,1,"","Srila Narottama Dasa Thakura -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(1,6,7,1,"","Appearance of Radha Kunda, snana dana",0,1,-10000);
	gCustomEventList.addEvent(1,6,7,1,"","Bahulastami",0,1,-10000);
	gCustomEventList.addEvent(3,6,8,1,"","Sri Virabhadra -- Appearance",0,1,-10000);
	gCustomEventList.addEvent(1,6,14,1,"","Dipa dana, Dipavali, (Kali Puja)",0,1,-10000);
	gCustomEventList.addEvent(1,6,15,1,"","Bali Daityaraja Puja",0,1,-10000);
	gCustomEventList.addEvent(3,6,15,1,"","Sri Rasikananda -- Appearance",0,1,-10000);
	gCustomEventList.addEvent(3,6,16,1,"","Sri Vasudeva Ghosh -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(2,6,18,1,"Srila Prabhupada","Srila Prabhupada -- Disappearance",1,1,-10000);
	gCustomEventList.addEvent(1,6,22,1,"","Gopastami, Gosthastami",0,1,-10000);
	gCustomEventList.addEvent(3,6,22,1,"","Sri Gadadhara Dasa Gosvami -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,6,22,1,"","Sri Dhananjaya Pandita -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,6,22,1,"","Sri Srinivasa Acarya -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(5,6,23,1,"","Jagaddhatri Puja",0,1,-10000);
	gCustomEventList.addEvent(2,6,25,1,"Gaura Kisora Dasa Babaji","Srila Gaura Kisora Dasa Babaji -- Disappearance",1,1,-10000);
	gCustomEventList.addEvent(3,6,28,1,"","Sri Bhugarbha Gosvami -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,6,28,1,"","Sri Kasisvara Pandita -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(1,6,29,1,"","Sri Krsna Rasayatra",0,1,-10000);
	gCustomEventList.addEvent(1,6,29,1,"","Tulasi-Saligrama Vivaha (marriage)",0,1,-10000);
	gCustomEventList.addEvent(3,6,29,1,"","Sri Nimbarkacarya -- Appearance",0,1,-10000);
	gCustomEventList.addEvent(1,7,0,1,"","Katyayani vrata begins",0,1,-10000);
	gCustomEventList.addEvent(3,7,10,1,"","Sri Narahari Sarakara Thakura -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,7,11,1,"","Sri Kaliya Krsnadasa -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,7,12,1,"","Sri Saranga Thakura -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(1,7,20,1,"","Odana sasthi",0,1,-10000);
	gCustomEventList.addEvent(1,7,25,1,"","Advent of Srimad Bhagavad-gita",0,1,-10000);
	gCustomEventList.addEvent(1,7,29,1,"","Katyayani vrata ends",0,1,-10000);
	gCustomEventList.addEvent(2,8,3,1,"Bhaktisiddhanta Sarasvati","Srila Bhaktisiddhanta Sarasvati Thakura -- Disappearance",1,1,-10000);
	gCustomEventList.addEvent(3,8,10,1,"","Sri Devananda Pandita -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,8,12,1,"","Sri Mahesa Pandita -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,8,12,1,"","Sri Uddharana Datta Thakura -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,8,15,1,"","Sri Locana Dasa Thakura -- Appearance",0,1,-10000);
	gCustomEventList.addEvent(3,8,17,1,"","Srila Jiva Gosvami -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,8,17,1,"","Sri Jagadisa Pandita -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,8,26,1,"","Sri Jagadisa Pandita -- Appearance",0,1,-10000);
	gCustomEventList.addEvent(1,8,29,1,"","Sri Krsna Pusya Abhiseka",0,1,-10000);
	gCustomEventList.addEvent(3,9,4,1,"","Sri Ramacandra Kaviraja -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,9,4,1,"","Srila Gopala Bhatta Gosvami -- Appearance",0,1,-10000);
	gCustomEventList.addEvent(3,9,5,1,"","Sri Jayadeva Gosvami -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,9,6,1,"","Sri Locana Dasa Thakura -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(1,9,19,1,"","Vasanta Pancami",0,1,-10000);
	gCustomEventList.addEvent(3,9,19,1,"","Srimati Visnupriya Devi -- Appearance",0,1,-10000);
	gCustomEventList.addEvent(5,9,19,1,"","Sarasvati Puja",0,1,-10000);
	gCustomEventList.addEvent(3,9,19,1,"","Srila Visvanatha Cakravarti Thakura -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,9,19,1,"","Sri Pundarika Vidyanidhi -- Appearance",0,1,-10000);
	gCustomEventList.addEvent(3,9,19,1,"","Sri Raghunandana Thakura -- Appearance",0,1,-10000);
	gCustomEventList.addEvent(3,9,19,1,"","Srila Raghunatha Dasa Gosvami -- Appearance",0,1,-10000);
	gCustomEventList.addEvent(0,9,21,1,"Advaita Acarya","Sri Advaita Acarya -- Appearance",1,1,-10000);
	gCustomEventList.addEvent(1,9,22,1,"","Bhismastami",0,1,-10000);
	gCustomEventList.addEvent(3,9,23,1,"","Sri Madhvacarya -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,9,24,1,"","Sri Ramanujacarya -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(0,9,26,1,"Varahadeva","Varaha Dvadasi: Appearance of Lord Varahadeva",1,1,-10000);
	gCustomEventList.addEvent(0,9,27,1,"Sri Nityananda","Nityananda Trayodasi: Appearance of Sri Nityananda Prabhu",1,1,-10000);
	gCustomEventList.addEvent(1,9,29,1,"","Sri Krsna Madhura Utsava",0,1,-10000);
	gCustomEventList.addEvent(3,9,29,1,"","Srila Narottama Dasa Thakura -- Appearance",0,1,-10000);
	gCustomEventList.addEvent(3,10,4,1,"","Sri Purusottama Das Thakura -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(2,10,4,1,"Bhaktisiddhanta Sarasvati","Srila Bhaktisiddhanta Sarasvati Thakura -- Appearance",1,1,-10000);
	gCustomEventList.addEvent(3,10,11,1,"","Sri Isvara Puri -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(1,10,13,1,"","Siva Ratri",0,1,-10000);
	gCustomEventList.addEvent(2,10,15,1,"","Srila Jagannatha Dasa Babaji -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,10,15,1,"","Sri Rasikananda -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,10,18,1,"","Sri Purusottama Dasa Thakura -- Appearance",0,1,-10000);
	gCustomEventList.addEvent(3,10,26,1,"","Sri Madhavendra Puri -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,11,7,1,"","Sri Srivasa Pandita -- Appearance",0,1,-10000);
	gCustomEventList.addEvent(3,11,11,1,"","Sri Govinda Ghosh -- Disappearance",0,1,-10000);
	gCustomEventList.addEvent(3,11,19,1,"","Sri Ramanujacarya -- Appearance",0,1,-10000);
	gCustomEventList.addEvent(1,11,26,1,"","Damanakaropana Dvadasi",0,1,-10000);
	gCustomEventList.addEvent(1,11,29,1,"","Sri Balarama Rasayatra",0,1,-10000);
	gCustomEventList.addEvent(1,11,29,1,"","Sri Krsna Vasanta Rasa",0,1,-10000);
	gCustomEventList.addEvent(3,11,29,1,"","Sri Vamsivadana Thakura -- Appearance",0,1,-10000);
	gCustomEventList.addEvent(3,11,29,1,"","Sri Syamananda Prabhu -- Appearance",0,1,-10000);

	return 1;
}

//==============================================================
//
//==============================================================

int CustomEventListReadFile_RL(const char * pszFile)
{
	TFileRichList F;
	int tithi, masa;
	TString strA, strB, text;
	CCustomEvent * pce;
	int nRet = -1;

	if (F.Open(pszFile, "rt") == TRUE)
	{
		gCustomEventList.clear();
/*		for(tithi = 0; tithi < 360; tithi++)
		{
			gCustomEventTexts[tithi].Empty();
		}*/

		nRet ++;
		while(F.ReadLine())
		{
			if (atoi(F.GetTag()) == 13)
			{
				nRet++;
				pce = gCustomEventList.add();
				if (pce)
				{
					if (strcmp(F.GetField(0), "Sri Krsna Pusya abhiseka")==0)
						pce->strText = "Sri Krsna Pusya Abhiseka";
					else
						pce->strText = F.GetField(0);
					//pce->strText = F.GetField(0);
					pce->nMasa   = masa  = atoi(F.GetField(1));
					pce->nTithi  = tithi = atoi(F.GetField(2));
					pce->nClass  = atoi(F.GetField(3));
					pce->nVisible = atoi(F.GetField(4));
					pce->nFastType = atoi(F.GetField(5));
					pce->strFastSubject = F.GetField(6);
					pce->nUsed = atoi(F.GetField(7));
					pce->nSpec = atoi(F.GetField(8));
					const char * str10 = F.GetField(9);
					if (strlen(str10) == 0)
						pce->nStartYear = -10000;
					else
						pce->nStartYear = atoi(str10);

				}

/*				if (gCustomEventTexts[_id].IsEmpty() == TRUE)
					gCustomEventTexts[_id] = "[c6]";
				else
					gCustomEventTexts[_id] += "#[c6]";
				gCustomEventTexts[_id] += text;*/
			}
		}

		F.Close();
	}
	else
	{
		VAISNAVADAY vd;
		//int cls;
		//int i;
		TString strFest, strFastSubj;
		
		// list is modified write it at exit from application
		gCustomEventList_Modified = 1;

		/*for(i = 200; i < 560; i++)
		{
			vd.festivals = GCStrings::getString(i).c_str();
			ind = vd.GetHeadFestival();
			while(vd.GetNextFestival(ind, strFest))
			{
				cls = vd.GetFestivalClass(strFest);
				vd.GetFastingSubject(strFest, nFast, strFastSubj);
				pce = gCustomEventList.add();
				if (pce)
				{
					pce->nClass = cls;
					pce->nMasa = (i - 200)/30;
					pce->nTithi = (i - 200) % 30;
					pce->nVisible = 1;
					pce->strFastSubject = strFastSubj.c_str();
					pce->strText = strFest;
					pce->nFastType = nFast;
					pce->nUsed = 1;
					AfxTrace("gCustomEventList.add(%d,%d,%d,%d,\"%s\",\"%s\",%d,%d);\n",
						pce->nClass, pce->nMasa, pce->nTithi, pce->nVisible,
						pce->strFastSubject.c_str(),
						pce->strText.c_str(), pce->nFastType, 1);
				}
			}
		}*/

		CustomEventList_InitDefault();

		pce = gCustomEventList.add();
		if (pce)
		{
			pce->nUsed = 0;
			pce->nClass = 0;
			pce->nMasa = 4;
			pce->nTithi = 7;
			pce->nSpec = SPEC_JANMASTAMI;
			pce->strText = GCStrings::getString(741).c_str();
			pce->nFastType = 5;
			pce->strFastSubject = "Sri Krsna";
		}
		pce = gCustomEventList.add();
		if (pce)
		{
			pce->nUsed = 0;
			pce->nClass = 0;
			pce->nMasa = 10;
			pce->nTithi = 29;
			pce->nSpec = SPEC_GAURAPURNIMA;
			pce->strText = GCStrings::getString(742).c_str();
			pce->nFastType = 3;
			pce->strFastSubject = "Sri Krsna Caitanya Mahaprabhu";
		}
		pce = gCustomEventList.add();
		if (pce)
		{
			pce->nUsed = 0;
			pce->nClass = 1;
			pce->nMasa = 2;
			pce->nTithi = 8;
			pce->nSpec = SPEC_RETURNRATHA;
			pce->strText = GCStrings::getString(743).c_str();
			pce->nFastType = 0;
			pce->strFastSubject = "";
		}
		pce = gCustomEventList.add();
		if (pce)
		{
			pce->nUsed = 0;
			pce->nClass = 1;
			pce->nMasa = 2;
			pce->nTithi = 4;
			pce->nSpec = SPEC_HERAPANCAMI;
			pce->strText = GCStrings::getString(744).c_str();
			pce->nFastType = 0;
			pce->strFastSubject = "";
		}
		pce = gCustomEventList.add();
		if (pce)
		{
			pce->nUsed = 0;
			pce->nClass = 1;
			pce->nMasa = 2;
			pce->nTithi = 0;
			pce->nSpec = SPEC_GUNDICAMARJANA;
			pce->strText = GCStrings::getString(745).c_str();
			pce->nFastType = 0;
			pce->strFastSubject = "";
		}
		pce = gCustomEventList.add();
		if (pce)
		{
			pce->nUsed = 0;
			pce->nClass = 1;
			pce->nMasa = 6;
			pce->nTithi = 0;
			pce->nSpec = SPEC_GOVARDHANPUJA;
			pce->strText = GCStrings::getString(746).c_str();
			pce->nFastType = 0;
			pce->strFastSubject = "";
		}
		pce = gCustomEventList.add();
		if (pce)
		{
			pce->nUsed = 0;
			pce->nClass = 0;
			pce->nMasa = 11;
			pce->nTithi = 23;
			pce->nSpec = SPEC_RAMANAVAMI;
			pce->strText = GCStrings::getString(747).c_str();
			pce->nFastType = 2;
			pce->strFastSubject = "Sri Ramacandra";
		}
		pce = gCustomEventList.add();
		if (pce)
		{
			pce->nUsed = 0;
			pce->nClass = 1;
			pce->nMasa = 2;
			pce->nTithi = 1;
			pce->nSpec = SPEC_RATHAYATRA;
			pce->strText = GCStrings::getString(748).c_str();
			pce->nFastType = 0;
			pce->strFastSubject = "";
		}
		pce = gCustomEventList.add();
		if (pce)
		{
			pce->nUsed = 0;
			pce->nClass = 1;
			pce->nMasa = 4;
			pce->nTithi = 23;
			pce->nSpec = SPEC_NANDAUTSAVA;
			pce->strText = GCStrings::getString(749).c_str();
			pce->nFastType = 0;
			pce->strFastSubject = "";
		}
		pce = gCustomEventList.add();
		if (pce)
		{
			pce->nUsed = 0;
			pce->nClass = 2;
			pce->nMasa = 4;
			pce->nTithi = 8;
			pce->nSpec = SPEC_PRABHAPP;
			pce->strText = GCStrings::getString(759).c_str();
			pce->nFastType = 1;
			pce->strFastSubject = "Srila Prabhupada";
		}
		pce = gCustomEventList.add();
		if (pce)
		{
			pce->nUsed = 0;
			pce->nClass = 1;
			pce->nMasa = 11;
			pce->nTithi = 15;
			pce->nSpec = SPEC_MISRAFESTIVAL;
			pce->strText = GCStrings::getString(750).c_str();
			pce->nFastType = 0;
			pce->strFastSubject = "";
		}

		CustomEventListRefreshLinks();
	}

	return nRet;
}

//==============================================================
//
//==============================================================

int CustomEventListWriteFile(const char * pszFile)
{
	TFile csd;
	TString str;
	CCustomEvent * pce;
	int nRet = -1;

	if (csd.Open(pszFile, "w") == TRUE)
	{
		nRet ++;
		pce = gCustomEventList.list;

		while(pce)
		{
			nRet ++;
			// write to file
			str.Format("event=%c%c%s\n", '@' + pce->nTithi, '@' + pce->nMasa, pce->strText.c_str());
			csd.WriteString(str);

			pce = pce->next;
		}
		// close file
		csd.Close();
	}

	return nRet;
}

//==============================================================
//
//==============================================================

int CustomEventListWriteFile_RL(const char * pszFile)
{
	if (gCustomEventList_Modified == 0)
		return 0;

	TFile csd;
	TString str;
	CCustomEvent * pce;
	int nRet = -1;

	if (csd.Open(pszFile, "w") == TRUE)
	{
		nRet ++;
		pce = gCustomEventList.list;

		while(pce)
		{
			if (pce->nDeleted==0)
			{
				nRet ++;
				// write to file
				str.Format("13 %s|%d|%d|%d|%d|%d|%s|%d|%d\n", pce->strText.c_str(), 
					pce->nMasa, pce->nTithi, pce->nClass, pce->nVisible,
					pce->nFastType, pce->strFastSubject.c_str(), pce->nUsed, pce->nSpec);
				csd.WriteString(str);
			}
			pce = pce->next;
		}
		// close file
		csd.Close();
	}

	return nRet;
}
//==============================================================
//
//==============================================================

void CustomEventList_Export() 
{
	CFileDialog d(FALSE, "txt", "events", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST, "Text file (*.txt)|*.txt|XML File (*.xml)|*.xml||");
	CString strc;
	CCustomEvent * pce = NULL;

	if (d.DoModal() == IDOK)
	{
		TString str, str2, str3;
		TFile f;

		if (f.Open(d.GetPathName(), "w") == TRUE)
		{
//			int i, m;

			switch(d.m_ofn.nFilterIndex)
			{
			case 1:
				pce = gCustomEventList.list;
				while(pce)
				{
					strc.Format("%s\n\t%s Tithi,%s Paksa,%s Masa\n", pce->strText.c_str(),
						GCStrings::GetTithiName(pce->nTithi), GCStrings::GetPaksaName(pce->nTithi/15), GCStrings::GetMasaName(pce->nMasa));
					f.WriteString(strc);
					if (pce->nFastType)
					{
						strc.Format("\t%s\n", GCStrings::GetFastingName(0x200 + pce->nFastType));
						f.WriteString(strc);
					}
					pce = pce->next;
				}
				f.WriteString(GCStrings::getString(78));
				f.WriteString("\n\t\tMakara Sankranti\n");
				f.WriteString(GCStrings::getString(79));
				f.WriteString("\n\t\tMesha Sankranti\n");
				f.WriteString(GCStrings::getString(80));
				f.WriteString("\n\t\tA day before Vrsabha Sankranti\n");
				break;
			case 2:
				{
//					int n;
					f.WriteString("<xml>\n");
					pce = gCustomEventList.list;
					while(pce)
					{
						f.WriteString("\t<event>\n");
						strc.Format("\t\t<name>%s</name>\n", pce->strText.c_str());
						f.WriteString(strc);
						strc.Format("\t\t<tithi>%s</tithi>\n", GCStrings::GetTithiName(pce->nTithi));
						f.WriteString(strc);
						strc.Format("\t\t<paksa>%s</paksa>\n", GCStrings::GetPaksaName(pce->nTithi/15));
						f.WriteString(strc);
						strc.Format("\t\t<masa>%s</masa>\n", GCStrings::GetMasaName(pce->nMasa));
						f.WriteString(strc);
						f.WriteString("\t</event>\n");
					}
					f.WriteString("\t<event>\n\t\t<name>");
					f.WriteString(GCStrings::getString(78));
					f.WriteString("</name>\n\t\t<sankranti>Makara</sankranti>\n\t\t<rel>0</rel>\n\t</event>\n");
					f.WriteString("\t<event>\n\t\t<name>");
					f.WriteString(GCStrings::getString(79));
					f.WriteString("</name>\n\t\t<sankranti>Mesha</sankranti>\n\t\t<rel>0</rel>\n\t</event>\n");
					f.WriteString("\t<event>\n\t\t<name>");
					f.WriteString(GCStrings::getString(80));
					f.WriteString("</name>\n\t\t<sankranti>Vrsabha</sankranti>\n\t\t<rel>-1</rel>\n\t</event>\n");
					f.WriteString("</xml>\n");
				}
				break;
			default:
				break;
			}
			f.Close();
		}
	}
}

//==============================================================
//
//==============================================================

//==============================================================
//
//==============================================================


void CCustomEventList::clear()
{
	CCustomEvent * p, * r;

	p = list;
	while(p)
	{
		r = p->next;
		delete p;
		p = r;
	}
	list = NULL;
}

//==============================================================
//
//==============================================================

void CustomEventListRefreshLinks()
{
	CCustomEvent * p = gCustomEventList.list;

	while(p)
	{
		p->next_in_masa = p->findNextInMasa();
		p->next_masa = p->findNextMasa();
		p = p->next;
	}
}

CCustomEvent * CCustomEvent::findNextInMasa()
{
	CCustomEvent * p = next;

	while(p)
	{
		if (nMasa == p->nMasa)
			return p;
		p = p->next;
	}
	return NULL;
}

CCustomEvent * CCustomEvent::findNextMasa()
{
	CCustomEvent * p = next;

	while(p)
	{
		if (nMasa != p->nMasa)
			return p;
		p = p->next;
	}
	return NULL;
}

CCustomEvent * CCustomEvent::findMasa(int inMasa)
{
	CCustomEvent * p = this;

	while(p && p->nMasa!=inMasa)
		p = p->next_masa;

	if (p == NULL)
		return NULL;

	if (nMasa == p->nMasa)
		return p;
	
	return NULL;
}

int GetSpecFestivalVisibility(int i)
{
	CCustomEvent  * p = gCustomEventList.list;
	while(p)
	{
		if(p->nSpec == i)
		{
			return p->nVisible;
		}
		p = p->next;
	}

	return 1;
}

int CCustomEventList::setOldStyleFast(int bOldStyle)
{
	CCustomEvent * pce = NULL;

	const int locMatrix[][5] =
	{
		// visnu tattva and sakti tattva
		{/*tithi*/ 28, /*masa*/  0, /*fast*/ 4, /*new fast*/ 7, /*class*/ 0},
		{/*tithi*/ 29, /*masa*/  3, /*fast*/ 1, 7, 0},
		{/*tithi*/ 22, /*masa*/  4, /*fast*/ 1, 0, 0},
		{/*tithi*/ 26, /*masa*/  4, /*fast*/ 1, 7, 0},
		{/*tithi*/ 21, /*masa*/  9, /*fast*/ 1, 7, 0},
		{/*tithi*/ 26, /*masa*/  9, /*fast*/ 1, 7, 0},
		{/*tithi*/ 27, /*masa*/  9, /*fast*/ 1, 7, 0},
		{/*tithi*/  7, /*masa*/  4, /*fast*/ 5, 7, 0},
		{/*tithi*/ 29, /*masa*/ 10, /*fast*/ 3, 7, 0},
		{/*tithi*/ 23, /*masa*/ 11, /*fast*/ 2, 7, 0},
		// acaryas
		{/*tithi*/  8, /*masa*/  4, /*fast*/ 1, 0, 2},
		{/*tithi*/ 27, /*masa*/  4, /*fast*/ 1, 0, 2},
		{/*tithi*/ 14, /*masa*/  2, /*fast*/ 1, 0, 2},
		{/*tithi*/ 25, /*masa*/  6, /*fast*/ 1, 0, 2},
		{/*tithi*/ 18, /*masa*/  6, /*fast*/ 1, 0, 2},
		{/*tithi*/  3, /*masa*/  8, /*fast*/ 1, 0, 2},
		{/*tithi*/  4, /*masa*/ 10, /*fast*/ 1, 0, 2},
		{-1,-1,-1,-1, -1}
	};

	int i, idx;
	int ret = 0;
	if (bOldStyle) idx = 2;
	else idx = 3;

	for(i = 0; locMatrix[i][0] >= 0; i++)
	{
		pce = list;
		while(pce)
		{
			if (pce->nMasa==locMatrix[i][1] &&
				pce->nTithi==locMatrix[i][0] &&
				pce->nClass==locMatrix[i][4])
			{
				if (pce->nFastType != locMatrix[i][idx])
				{
					ret ++;
					pce->nFastType = locMatrix[i][idx];
				}
				break;
			}
			pce = pce->next;
		}
	}

	return ret;
}

void CCustomEventList::addEvent(int inClass, int inMasa, int inTithi, int inVisible, const char *pszFastSubject, const char *pszText, int inFastType, int inUsed, int inStartYear)
{
	CCustomEvent * pce = NULL;

	pce = gCustomEventList.add();
	if (pce)
	{
		pce->nClass = inClass;
		pce->nMasa = inMasa;
		pce->nTithi = inTithi;
		pce->nVisible = inVisible;
		pce->strFastSubject = pszFastSubject;
		pce->strText = pszText;
		pce->nFastType = inFastType;
		pce->nUsed = inUsed;
		pce->nStartYear = inStartYear;
	}
}
