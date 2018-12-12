#ifndef VIPAPARSER_H_
#define VIPAPARSER_H_

#include<stdio.h>
#include <stdlib.h>
#include<cstdlib>
#include<sstream>
#include<map>
#include <string.h>
#include <iomanip>
#include <vector>
#include <list>
#include <set>
#include "Utils.h"

#define MAX_SIZE 4096

using std::map;
using namespace std;

class VipaParser
{
    /*    Data members of Class VIPAResponse */

private:
    unsigned char NAD; // Node Address
    unsigned char PCB; // Protocol Control Byte
    unsigned char LEN; // length byte of Rx
    unsigned char SW1;  // Status Byte 1
    unsigned char SW2;  // Status Byte2
    unsigned char LRC;  // Longitudinal Redundancy Check  of Rx
    bool m_bTemplate;
    unsigned char m_cTemplate;
    unsigned int m_iTemplateLen;
    unsigned int m_TemplateLenCurrent;
    vector <pair<string, string>> m_TVPairs;
    vector <pair<string, string>> m_TVEMVParaPairs;
    unsigned char  bufferVIPARespBytes[ MAX_SIZE ];
	size_t buffRespDataSize;
    unsigned char m_MSRFlag;
    unsigned char m_ATRFlag;
    map<int, map<string,string>> m_MultipleAIDDetails;
    map<string, string> m_AIDDetails;
    vector <pair<string, string>> m_SAIDDetails;
    static set<string> m_VIPARedundantTags;
    static bool m_VIPARedundantTagInitialized;
    /* Member Function of Class VIPAResponse */

public:
	void ParseVIPAResponse();
	~VipaParser();
	VipaParser(string);
};

#endif /*VIPAPARSER_H_*/
