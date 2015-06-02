/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMESSAGINGBROKERTOPICPROCESSORPUBLISHWORKER_H
#define WAVEMESSAGINGBROKERTOPICPROCESSORPUBLISHWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class WaveMessagingBrokerTopicProcessorObjectManager;
class WaveMessagingBrokerTopicProcessorPublishMessage;

class WaveMessagingBrokerTopicProcessorPublishWorker : public WaveWorker
{
    private :
        void publishMessageHandler (WaveMessagingBrokerTopicProcessorPublishMessage *pWaveMessagingBrokerTopicProcessorPublishMessage);

    protected :
    public :
                        WaveMessagingBrokerTopicProcessorPublishWorker (WaveMessagingBrokerTopicProcessorObjectManager *pWaveMessagingBrokerTopicProcessorObjectManager);
        virtual        ~WaveMessagingBrokerTopicProcessorPublishWorker ();

                string  getTopicName                                   () const;

    // Now the data members

    private:
        WaveMessagingBrokerTopicProcessorObjectManager *m_pWaveMessagingBrokerTopicProcessorObjectManager;

    protected :
    public :
};

}

#endif // WAVEMESSAGINGBROKERTOPICPROCESSORPUBLISHWORKER_H
