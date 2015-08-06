/***************************************************************************
 *   Copyright (C) 2011 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Mandar Datar                                                 *
 ***************************************************************************/

#ifndef MESSAGEHISTORY
#define MESSAGEHISTORY

#include "Framework/Types/Types.h"
#include <string>
#include <time.h>

using namespace std;

namespace WaveNs
{
class WaveMessage;
class MessageHistory {

    private :
    protected :
    public :
                MessageHistory              (WaveMessage *pWaveMessage, WaveMessageSendType sendType, WaveMessageHistoryLogType messageHistoryLogType);
                ~MessageHistory             ();
        void    getMessageHistoryString     (string &debugHistoryString);

       // Now the data members

    private :
        UI32                        m_originalMessageId;
        WaveMessageType             m_type;
        WaveMessageSendType         m_sendType;
        LocationId                  m_destinationLocationID;
        WaveServiceId              m_destinationServiceId;
        ResourceId                  m_opcode;
        ResourceId                  m_completionStatus;
        time_t                      m_timeInSeconds;
        UI32                        m_microSeconds;
        WaveMessageHistoryLogType   m_messageHistoryLogType;
    protected :
    public :

};

}

#endif //MESSAGEHISTORY

