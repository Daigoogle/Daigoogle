#include "PutLog.h"

void Error(LPCSTR Mess)
{
	MessageBox(NULL, Mess, "Error",MB_OK);
}

void PutDebug(std::string DebugStr)
{
	OutputDebugString(DebugStr.c_str());
}