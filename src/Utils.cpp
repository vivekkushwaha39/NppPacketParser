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