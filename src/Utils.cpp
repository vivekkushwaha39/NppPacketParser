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