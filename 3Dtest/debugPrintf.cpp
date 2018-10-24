#include "debugPrintf.h"
#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <time.h>
using namespace std;

void GetTimeString(char* const timeString, int len)
{
	time_t timep;
	tm tmp;
	time(&timep);
	localtime_s(&tmp, &timep);
	sprintf_s(timeString, len, "%d-%d-%d %d:%d:%d", tmp.tm_year, tmp.tm_mon, tmp.tm_mday,
		tmp.tm_hour, tmp.tm_min, tmp.tm_sec);
}

void DebugPrintf(const char* pFormat, ...)
{
#if defined(_DEBUG) || defined(DEBUG)
	va_list argp;
	char buf[256];
	va_start(argp, pFormat);
	vsprintf_s(buf, 256, pFormat, argp);
	va_end(argp);
	OutputDebugStringA(buf);
#endif // _DEBUG || 
}

//void FaultLog(char* message)
//{
//	char timeString[TIME_STRING_LENGTH];
//	GetTimeString(timeString, TIME_STRING_LENGTH);
//	DebugPrintf("%s: %s %s\n", "FAULT", timeString, message);
//}