#pragma once
#include <Windows.h>
#include <string>
#include <sstream>
typedef std::basic_string<TCHAR> tstring;
typedef std::basic_stringstream<TCHAR> tstringstream;


// MACROS
#define WS_TO_S(x) std::string((x).begin(), (x).end())
#define S_TO_WS(x) std::wstring((x).begin(), (x).end())