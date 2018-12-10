/******************************************************************
   Copyright (C) 2017-2018 by VeriFone Inc. All rights reserved.

 No part of this software may be used, stored, compiled, reproduced,
 modified, transcribed, translated, transmitted, or transferred, in
 any form or by any means  whether electronic, mechanical,  magnetic,
 optical, or otherwise, without the express prior written permission
                          of VeriFone, Inc.
*******************************************************************/
/*
 *
 * FILE NAME:   VIPAResponse.hpp
 *
 * COMPONENT OF: EVPAY
 *
 * AUTHOR(S):   Joju_J1
 *              Prantick
 *
 * MODULE DESCRIPTION:
 *
 *  This file contains code needed for performing following tasks :
 *
 *      1.VIPA Interface exposes APIs to agent for processing the Device Request.
 *      2.VIPAInterface APIs to send commands to the VIPA application without 
 *      knowing the complexity of VIPA protocol as well as the VIPA connection.
 *
 * MODIFICATION HISTORY:
 *
 *  DATE        DESCRIPTION                                 INITIALS
 *  --------    -----------                                 --------
 *  14/12/2017  Creation                                    Joju & Prantick
 *
 *******************************************************************************/

#ifndef VIPARESPONSE_H_
#define VIPARESPONSE_H_

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
	VipaParser();
};

#endif /*VIPARESPONSE_H_*/
