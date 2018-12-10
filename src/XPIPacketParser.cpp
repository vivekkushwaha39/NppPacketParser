#include "XPIPacketParser.h"


XPIPacketParser::XPIPacketParser(void)
{
	// Initialize spacial map for 
	// Invisible ascii values
	initSplChrMap();
}


XPIPacketParser::~XPIPacketParser(void)
{
}

string XPIPacketParser::parsePacket(string data)
{
	bool spacialChrFlag = false;
	string finalStr = "";
	string spacialCharStack = ""; 
	for( unsigned int i=0 ; i < data.size() ; i++ )
	{
		if( data[i] == '<' )
		{
			if( spacialChrFlag == true )
			{
				finalStr += getAsciiAsStr('<');
			}
			else
			{
				spacialChrFlag = true;
			}

		}
		else if ( data[i] == '>' && spacialChrFlag == true )
		{
			finalStr += getSpacialChrAsStr( spacialCharStack );
			spacialCharStack.clear();
			spacialChrFlag = false;
		}
		else 
		{
			if ( spacialChrFlag == true )
			{
				spacialCharStack.push_back( data[i] );
			}
			else
			{
				finalStr += getAsciiAsStr( data[i] );
			}
		}
	}

	return finalStr;
}

string XPIPacketParser::getAsciiAsStr(char c)
{
	int ascii = (int) c;
	char chr[4];
	memset(chr, 0, sizeof(chr));
	sprintf(chr, "%02X", ascii);
	return string(chr);
}


void XPIPacketParser::initSplChrMap()
{
	splChrMap.insert(make_pair("NUL", 0));
	splChrMap.insert(make_pair("SOH", 1));
	splChrMap.insert(make_pair("STX", 2));
	splChrMap.insert(make_pair("ETX", 3));
	splChrMap.insert(make_pair("EOT", 4));
	splChrMap.insert(make_pair("ENQ", 5));
	splChrMap.insert(make_pair("ACK", 6));
	splChrMap.insert(make_pair("BEL", 7));
	splChrMap.insert(make_pair("BS", 8));
	splChrMap.insert(make_pair("TAB", 9));
	splChrMap.insert(make_pair("LF", 10));
	splChrMap.insert(make_pair("VT", 11));
	splChrMap.insert(make_pair("FF", 12));
	splChrMap.insert(make_pair("CR", 13));
	splChrMap.insert(make_pair("SO", 14));
	splChrMap.insert(make_pair("SI", 15));
	splChrMap.insert(make_pair("DLE", 16));
	splChrMap.insert(make_pair("DC1", 17));
	splChrMap.insert(make_pair("DC2", 18));
	splChrMap.insert(make_pair("DC3", 19));
	splChrMap.insert(make_pair("DC4", 20));
	splChrMap.insert(make_pair("NAK", 21));
	splChrMap.insert(make_pair("SYN", 22));
	splChrMap.insert(make_pair("ETB", 23));
	splChrMap.insert(make_pair("CAN", 24));
	splChrMap.insert(make_pair("EM", 25));
	splChrMap.insert(make_pair("SUB", 26));
	splChrMap.insert(make_pair("ESC", 27));
	splChrMap.insert(make_pair("FS", 28));
	splChrMap.insert(make_pair("GS", 29));
	splChrMap.insert(make_pair("RS", 30));
	splChrMap.insert(make_pair("US", 31));
}

string XPIPacketParser::getSpacialChrAsStr(string chr)
{
	string finalStr = "";
	if ( splChrMap.count(chr) > 0 )
	{
		char asc = splChrMap[chr];
		finalStr = getAsciiAsStr(asc);
	}
	else 
	{
		finalStr = chr;
	}

	return finalStr;
}