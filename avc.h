#ifndef _AVC_H_GCAL_____
#define _AVC_H_GCAL_____
// PORTABLE


#define GSTR_APPFOLDER 1
#define GSTR_CONFOLDER 2
#define GSTR_LANFOLDER 3
#define GSTR_TEMFOLDER 4

#define GSTR_CE_FILE   5
#define GSTR_CONF_FILE 6
#define GSTR_LOC_FILE  7
#define GSTR_SSET_FILE 8
#define GSTR_LOCX_FILE  9 /*GCAL 3.0*/
#define GSTR_CEX_FILE   10 /*GCAL 3.0*/
#define GSTR_CONFX_FILE 11 /*GCAL 3.0*/ 
#define GSTR_TZ_FILE    12 /*GCAL 3.0*/ 
#define GSTR_COUNTRY_FILE 13 /*GCAL 3.0*/ 
#define GSTR_TEXT_FILE 14 /*GCAL 4.1*/
#define GSTR_TIPS_FILE 15 /*GCAL 4.3*/
#define GSTR_HELP_FILE 16 /*GCAL 5.0*/

const char * GCalApp_GetFileName(int);

#endif