// PORTABLE
#ifndef _WRITE_S__________
#define _WRITE_S__________

int WriteXML_FirstDay_Year(FILE *, CLocationRef loc, VCTIME vc);
int WriteXML_Sankrantis(FILE *, CLocationRef loc, VCTIME, VCTIME);
int WriteXML_Naksatra(FILE *, CLocationRef loc, VCTIME, int);
int WriteXML_Tithi(FILE *, CLocationRef loc, VCTIME);
int WriteXML_GaurabdaTithi(FILE * fout, CLocationRef &loc, VATIME vaStart, VATIME vaEnd);
int WriteXML_GaurabdaNextTithi(FILE * fout, CLocationRef &loc, VCTIME vcStart, VATIME vaStart);


#endif