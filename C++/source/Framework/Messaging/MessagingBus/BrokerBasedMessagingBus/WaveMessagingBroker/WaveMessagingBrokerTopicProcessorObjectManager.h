/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMESSAGINGBROKERTOPICPROCESSOROBJECTMANAGER_H
#define WAVEMESSAGINGBROKERTOPICPROCESSOROBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"
#include "Framework/Utils/WaveMutex.h"

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

        static WaveServiceId                                   getWaveServiceIdByTopicName                   (const string &topicName);

    // Now the data members

    private :
               string                                          m_topicName;

               WaveMessagingBrokerTopicProcessorPublishWorker *m_pWaveMessagingBrokerTopicProcessorPublishWorker;

        static map<string, WaveServiceId>                     m_topicNameToWaveServiceIdMap;
        static WaveMutex                                      m_topicNameToWaveServiceIdMapMutex;

    protected :
    public :

    friend class WaveMessagingBrokerTopic;
};

}

#endif // WAVEMESSAGINGBROKERTOPICPROCESSOROBJECTMANAGER_H
