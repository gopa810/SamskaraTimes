#include "stdafx.h"
#include "LocationRef.h"
#include "langfileinfo.h"

// PORTABLE 
//==================================================================
//
//==================================================================

int g_dstSelMethod = 2;
const char * gpszSeparator = "----------------------------------------------------------------------------------";
CLocationRef gMyLocation;
CLocationRef gLastLocation;
VCTIME gTodayAct;
VCTIME gToday;
VCTIME gTomorrow;
VCTIME gYesterday;
TLangFileList gLangList;