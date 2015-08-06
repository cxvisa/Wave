/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMESSAGINGBROKERTOPICPROCESSORPUBLISHMESSAGE_H
#define WAVEMESSAGINGBROKERTOPICPROCESSORPUBLISHMESSAGE_H

#include "Framework/Messaging/Local/PrismMessage.h"

namespace WaveNs
{

class WaveBrokerBasedMessagePayload;

class WaveMessagingBrokerTopicProcessorPublishMessage : public PrismMessage
{
    private :
    protected :
    public :
                                               WaveMessagingBrokerTopicProcessorPublishMessage (const WaveServiceId &prismServiceId);
        virtual                               ~WaveMessagingBrokerTopicProcessorPublishMessage ();

                WaveBrokerBasedMessagePayload *getPWaveBrokerBasedMessagePayload               ();
                void                           setPWaveBrokerBasedMessagePayload               (WaveBrokerBasedMessagePayload *pWaveBrokerBasedMessagePayload);

                string                         &getUniqueStringForPublisher                    ();

    // Now the data members

    private :
        WaveBrokerBasedMessagePayload *m_pWaveBrokerBasedMessagePayload;
        string                         m_uniqueStringForPublisher;

    protected :
    public :
};

}

#endif // WAVEMESSAGINGBROKERTOPICPROCESSORPUBLISHMESSAGE_H
