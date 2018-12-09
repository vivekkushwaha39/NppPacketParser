#pragma once
#include<string>
#include<sstream>
#include<map>
#include<iomanip>
using namespace std;
class XPIPacketParser
{
private:
	map<string, char> splChrMap;
public:
	XPIPacketParser(void);
	~XPIPacketParser(void);
	string parsePacket(string );
	string getAsciiAsStr(char );
	string getSpacialChrAsStr(string );
	void initSplChrMap();
};

