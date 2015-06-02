/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEBROKERPUBLISHMESSAGEFACTORY_H
#define WAVEBROKERPUBLISHMESSAGEFACTORY_H

#include "Framework/Types/Types.h"
#include "Framework/Utils/PrismMutex.h"

#include <map>

using namespace std;

namespace WaveNs
{

class WaveBrokerPublishMessage;

typedef WaveBrokerPublishMessage *(* WaveBrokerPublishMessageInstantiator) ();

class WaveBrokerPublishMessageFactory
{
    private :
    protected :
    public :
                                         WaveBrokerPublishMessageFactory              ();
                                        ~WaveBrokerPublishMessageFactory              ();

        static void                      registerWaveBrokerPublishMessageInstantiator (const string &topicName, WaveBrokerPublishMessageInstantiator waveBrokerPublishMessageInstantiator);
        static WaveBrokerPublishMessage *createWaveBrokerPublishMessageInstance       (const string &topicName);

    // Now the data members

    private :
        static map<string, WaveBrokerPublishMessageInstantiator> m_waveBrokerPublishMessageInstatiators;
        static PrismMutex                                        m_waveBrokerPublishMessageInstatiatorsMutex;

    protected :
    public :
};

}

#endif // WAVEBROKERPUBLISHMESSAGEFACTORY_H
