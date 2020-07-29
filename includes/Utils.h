#include "CustomTypeDefs.h"
#include <stringapiset.h>
#define CHAR_TO_UTF8(arr)																			\
	int reqBuff = MultiByteToWideChar(CP_UTF8, MB_COMPOSITE, arr.c_str(), arr.size(), NULL, 0);		\
	LPWSTR outPut  = new wchar_t[reqBuff+1];														\
	MultiByteToWideChar(CP_UTF8, MB_COMPOSITE, arr.c_str(), arr.size(),  outPut, reqBuff);			\
	outPut[reqBuff] ='\0'
	
class Utils
{
    public:
        static int Utils::BytesToInt(unsigned char* data, int len);
		static std::string ByteArrayToHexString(unsigned char* arrChData, size_t len);
		static bool HexStringToByteArray(unsigned char[], const size_t, std::string &);
		static int GetProcessOutput(std::string, std::string&);
		static void crTocrlf(std::string&);
		static std::string toHex(std::string);
		static void removeNonHex(std::string&);
		static int GetProcessOutput2(std::string, std::string&);
};