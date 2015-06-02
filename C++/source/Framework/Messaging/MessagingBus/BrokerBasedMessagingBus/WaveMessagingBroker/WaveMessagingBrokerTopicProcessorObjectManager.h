/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMESSAGINGBROKERTOPICPROCESSOROBJECTMANAGER_H
#define WAVEMESSAGINGBROKERTOPICPROCESSOROBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"
#include "Framework/Utils/PrismMutex.h"

namespace WaveNs
{

class WaveMessagingBrokerTopicProcessorPublishWorker;

class WaveMessagingBrokerTopicProcessorObjectManager : public WaveLocalObjectManager
{
    private :
        WaveMessagingBrokerTopicProcessorObjectManager (const string &topicName);

    protected :
    public :
        virtual                                                ~WaveMessagingBrokerTopicProcessorObjectManager ();

        static  WaveMessagingBrokerTopicProcessorObjectManager *createInstance                                 (const string &topicName);
        static  string                                          getServiceNamePrefix                           ();

                string                                          getTopicName                                   () const;

        static PrismServiceId                                   getPrismServiceIdByTopicName                   (const string &topicName);

    // Now the data members

    private :
               string                                          m_topicName;

               WaveMessagingBrokerTopicProcessorPublishWorker *m_pWaveMessagingBrokerTopicProcessorPublishWorker;

        static map<string, PrismServiceId>                     m_topicNameToPrismServiceIdMap;
        static PrismMutex                                      m_topicNameToPrismServiceIdMapMutex;

    protected :
    public :

    friend class WaveMessagingBrokerTopic;
};

}

#endif // WAVEMESSAGINGBROKERTOPICPROCESSOROBJECTMANAGER_H
