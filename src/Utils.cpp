#include <stdio.h>
#include <sstream>
#include <tchar.h>
#include <vector>
#include <sstream>

#include "Utils.h"


using namespace std;
/**
* @brief    This function is used to convert bytes to integer.
*
*
* @param[in]                           [unsigned char*]
* @param[in]                           [int]
* @return                              [int]
*
*/

int Utils::BytesToInt(unsigned char* data, int len)
{
    int i;
    int val=0;
    for(i=0; i<len; i++)
    {
        val=val<<8|data[i];
    }
    return val;
}

/**
* @brief    This function is used to convert character array to Hex Formate string.
*
*
* @param[in]                           [unsigned char*]
* @param[in]                           [ssize_t]
* @return                              [string]
*
*/
string Utils::ByteArrayToHexString(unsigned char* arrChData, size_t len)
{

    char buf[3];
    string resp="";

    for ( int i = 0; i < len; i++ )
    {
        sprintf(buf,"%02X",arrChData[i]);
        resp += buf;
    }
    return (resp);

}

bool Utils::HexStringToByteArray(unsigned char byteBuff[], const size_t buffLen, string &data)
{
	bool res = true;
	size_t dataLen = data.size();
	size_t byteBuffPointer = 0U ;
	char hexByte[3];
	unsigned char pos = 0U;
	memset(hexByte, 0, sizeof(hexByte));
	for (string::iterator it = data.begin(); it != data.end() && byteBuffPointer < buffLen ; it++)
	{
		if (!(((*it) >= '0' && (*it) <= '9') || ((*it) >= 'A' && (*it) <= 'F') || ((*it) >= 'a' && (*it) <= 'f')))
		{
			continue;
		}

		hexByte[pos++] = *it;
		if (pos > 1)
		{
			pos = 0;
			sscanf(hexByte, "%X", &byteBuff[byteBuffPointer]);
			byteBuffPointer++;
		}
	}

	if (pos != 0)
	{
		res = false;
	}

	return res;
}

int Utils::GetProcessOutput(string commandLine, string &output)
{
	int retCode = 0;
	char buffer[512];
	FILE* processHandle =  _popen(commandLine.c_str(), "r");
	
	if (processHandle == NULL)
	{
		throw std::exception("Unable to open process");
	}
	while (fgets(buffer, sizeof(buffer), processHandle))
	{
		output.append(buffer);
	}
	retCode = _pclose(processHandle);
	return retCode;
	
}

string Utils::toHex(string data)
{
	string out;
	char buff[30];
	for (string::iterator it = data.begin();
		it != data.end(); it++)
	{
		sprintf(buff, "%0X", int(*it));
		out += buff;
	}

	return out;
}


void Utils::crTocrlf(string &heyStack)
{
	size_t stringSize = heyStack.size();
	vector<size_t> pos;
	size_t lastPos = 0;
	do {
		lastPos = heyStack.find("\n", lastPos);
		if (lastPos != string::npos)
		{
			pos.push_back(lastPos);
			lastPos++;
		}
		else
		{
			break;
		}

	} while (lastPos < stringSize);
	
	wstringstream ss;
	int delta = 0;
	for each (int i in pos)
	{
		heyStack.insert(i+delta, 1, '\r');
		delta++;
	}
}

void Utils::removeNonHex(string& data)
{
	for (std::string::iterator it = data.begin(); it != data.end(); it++)
	{
		if ((isdigit((*it)) || ((*it) >= 'A' && (*it) <= 'F') || ((*it) >= 'a' && (*it) <= 'f')) == false)
		{
			data.erase(it);
			it--;
		}
	}
	
}

int Utils::GetProcessOutput2(std::string command, std::string& output)
{
	::MessageBox(NULL, L"running system", L"", MB_OK);
	string redirect = "\"" + string(getenv("TMP"));
	redirect += "\\npp_tlv_parser.txt\" ";
	command.append("  >" + redirect);
	return system(command.c_str());
}