#pragma once

#include "visa.h"
#include "visatype.h"

#pragma comment(lib, "visa64.lib")

namespace Visa{	
	#define READ_BUFFER_SIZE 4096

	static ViJobId job;
	static unsigned char data1[READ_BUFFER_SIZE];
	static ViAddr uhandle;
	static ViStatus status, StatusSession;
	static ViSession inst, Sessionparam;
	static ViEventType EventTypeparam;
	static ViAddr Addressparam;
	static ViUInt32 BytesToWrite;
	static ViSession defaultRM;
	static ViUInt32 rcount, RdCount;
	static volatile ViBoolean stopflag = VI_FALSE;
	static int letter;
	static char stringinput[256];

	static ViStatus _VI_FUNCH AsyncHandler(ViSession vi, ViEventType etype, ViEvent event, ViAddr userHandle){
		Sessionparam = vi;
		EventTypeparam = etype;
		Addressparam = userHandle;
		viGetAttribute(event, VI_ATTR_STATUS, &StatusSession);
		viGetAttribute(event, VI_ATTR_RET_COUNT, &RdCount);
		stopflag = VI_TRUE;
		return VI_SUCCESS;
	}

}



