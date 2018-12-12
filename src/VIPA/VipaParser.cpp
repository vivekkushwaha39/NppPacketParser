#include "VIPA/VipaParser.h"
#include<iostream>
#include<cstring>
#include<sstream>
#include <algorithm>
#include <string.h>
#define BufferSize 300  // TagBuffer size
//VIPAResponse* VipaParser::m_VIPAResponse = nullptr;
#define TEMPLATE_NONE 0x00
#define TEMPLATE_E0 0xE0
#define TEMPLATE_E1 0xE1
#define TEMPLATE_E2 0xE2
#define TEMPLATE_E3 0xE3
#define TEMPLATE_E4 0xE4
#define TEMPLATE_E5 0xE5
#define TEMPLATE_E6 0xE6
#define TEMPLATE_E7 0xE7
#define TEMPLATE_E8 0xE8
#define TEMPLATE_E9 0xE9
#define HAS_MORE_LENGTH_BYTE 0x80
#define LENGTH_BITS 0x7F
#define HAS_MORE_TAG_BYTE1 0x1F
#define HAS_MORE_TAG_BYTE2 0x80
#define CARD_INSLOT  0
#define CARD_NOT_INSLOT  1
#define NOT_A_CARD_STATUS_RESPONSE  2
#define CARD_SWIPED 2
#define CARD_NOT_SWIPED 3
#define ATR_BITS_COUNT  4
#define ATR_SYNC  32
#define ATR_ASYNC  64
#define ATR_CHIP  128
#define INVALID_ATR_TYPE -1
#define ZERO 0
#define CARD_INSERTION_MASK 0x01

#define CANCEL_BUTTON   1
#define CLEAR_BUTTON    2
#define ENTER_BUTTON    3
#define INVALID_BUTTON  -1

#define ENTRY_MODE_MSD "91"
#define ENTRY_MODE_EMV "07"
#define INCORRECTCERTIFICATE "02"

#define TAG_SCRIPT  "ScriptResult"
#define PIN_CANCEL "14"
#define AID_CARD  "4F"    /* Application AID for CARD */
using std::map;
using namespace std;

set<string> VipaParser::m_VIPARedundantTags;

bool VipaParser::m_VIPARedundantTagInitialized( false );
/**
* @brief     This function is the constructor of the class VIPAResponse.
*
*
* @param[in]                           [void]
* @return                              [void]
*
*/

VipaParser::VipaParser(string hexString)
    :NAD( 0x00 ),
     PCB( 0x00 ),
     LEN( 0x00 ),
     SW1( 0x00 ),
     SW2( 0x00 ),
     LRC( 0x00 ),
     m_bTemplate( false ),
     m_cTemplate( 0x00 ),
     m_TemplateLenCurrent(0),
     buffRespDataSize(0),
     m_MSRFlag(0x00),
     m_ATRFlag(0x00)
{
    m_cTemplate=TEMPLATE_NONE;
    m_iTemplateLen=ZERO;
}

/**
* @brief     This function is the Destructor of the class VIPAResponse.
*
*
* @param[in]                           [void]
* @return                              [void]
*
*/

VipaParser::~VipaParser()
{
    m_SAIDDetails.clear();
}


/**
* @brief     This function is used to parse VIPA response based on the type of template
*            received.  
*
* @param[in]                           [void]
* @return                              [void]
*
*/

void VipaParser::ParseVIPAResponse()
{
    int j =0 ;
    /* Print the data of Response */
    /* VPAY-1874 : Reducing the debug log : Jemas Kumar*/
    /*while(j<buffRespDataSize)
        syslog(LOG_DEBUG,"%x ", bufferVIPARespBytes[j++]);*/


    int nLenBytes = 1;
    int iPosition = 0;

    if( buffRespDataSize <= 0 )
    {
        return;
    }

    /* Parsing start from here */
    if( TEMPLATE_E0 <= bufferVIPARespBytes[ iPosition ]
            && TEMPLATE_E9 >= bufferVIPARespBytes[ iPosition ] )
    {
        /* For Template Response  */
        m_cTemplate = bufferVIPARespBytes[ iPosition++ ];

        if( bufferVIPARespBytes[ iPosition ] & HAS_MORE_LENGTH_BYTE )
        {
            nLenBytes = bufferVIPARespBytes[ iPosition++ ] & LENGTH_BITS;
            m_iTemplateLen = Utils::BytesToInt( &bufferVIPARespBytes[ iPosition ], nLenBytes );
        }
        else
        {
            m_iTemplateLen = bufferVIPARespBytes[ iPosition ];
        }
        iPosition += nLenBytes;
    }
    else
    {
        /* Full Non-Templated Data includes sw1 sw2 */
        m_iTemplateLen = buffRespDataSize;
    }
    //syslog(LOG_DEBUG, "Template=%x, template length=%d", m_cTemplate, m_iTemplateLen );

    /* Now the pointer is pointing to the TLV */
    unsigned int iTemplateStart = iPosition;

    while( ( iPosition - iTemplateStart ) < m_iTemplateLen )
    {
        string value="", tag = "";
        int len = 0;
        /*Reading TAG*/
        tag.append( Utils::ByteArrayToHexString( &bufferVIPARespBytes[ iPosition ], 1 ) );
        if( ( bufferVIPARespBytes[ iPosition++ ] & HAS_MORE_TAG_BYTE1 )== HAS_MORE_TAG_BYTE1 )
        {
            do
            {
                tag.append( Utils::ByteArrayToHexString( &bufferVIPARespBytes[ iPosition ], 1 ) );
            }
            while( bufferVIPARespBytes[ iPosition++ ] & HAS_MORE_TAG_BYTE2 );

        }
        /*Reading LEN*/
        nLenBytes = 1;
        if( bufferVIPARespBytes[ iPosition ] & HAS_MORE_LENGTH_BYTE )
        {
            nLenBytes = bufferVIPARespBytes[ iPosition++ ] & LENGTH_BITS;
            len = Utils::BytesToInt( &bufferVIPARespBytes[ iPosition ], nLenBytes );
        }
        else
        {
            len = bufferVIPARespBytes[ iPosition ];
        }
        iPosition += nLenBytes;

        /*Reading Value*/
        value.append( Utils::ByteArrayToHexString( &bufferVIPARespBytes[ iPosition ], len ) );
        iPosition+=len;

        /* Pushing the Tag value pair inside the m_TVPairs vector except incomplete last Bytes */
        m_TVPairs.push_back( make_pair( tag, value) );
    }
}
