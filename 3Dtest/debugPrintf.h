/*=====================================================
DebugPrintf
using like printf
=======================================================*/

#pragma once
#ifndef DEBUG_PRINTF_H
#define DEBUG_PRINTF_H

#define TIME_STRING_LENGTH 64
#define LOG_MESSAGE_LENGTH 256


void GetTimeString(char* const timeString, int len);
void DebugPrintf(const char* pFormat, ...);

#endif