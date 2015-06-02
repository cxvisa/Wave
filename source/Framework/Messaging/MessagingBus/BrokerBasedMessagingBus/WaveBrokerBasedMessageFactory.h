/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEBROKERBASEDMESSAGEFACTORY_H
#define WAVEBROKERBASEDMESSAGEFACTORY_H

#include "Framework/Types/Types.h"
#include "Framework/Utils/PrismMutex.h"

#include <map>

using namespace std;

namespace WaveNs
{

class WaveBrokerBasedMessage;

typedef WaveBrokerBasedMessage *(* WaveBrokerBasedMessageInstantiator) ();

class WaveBrokerBasedMessageFactory
{
    private :
    protected :
    public :
                                       WaveBrokerBasedMessageFactory              ();
                                      ~WaveBrokerBasedMessageFactory              ();

        static void                    registerWaveBrokerBasedMessageInstantiator (WaveBrokerBasedMessageType waveBrokerBasedMessageType, WaveBrokerBasedMessageInstantiator waveBrokerBasedMessageInstantiator);
        static WaveBrokerBasedMessage *createWaveBrokerBasedMessageInstance       (WaveBrokerBasedMessageType waveBrokerBasedMessageType, const string &topicName);

    // Now the data members

    private :
        static map<WaveBrokerBasedMessageType, WaveBrokerBasedMessageInstantiator> m_waveBrokerBasedMessageInstatiators;
        static PrismMutex                                                          m_waveBrokerBasedMessageInstatiatorsMutex;

    protected :
    public :
};

}

#endif // WAVEBROKERBASEDMESSAGEFACTORY_H
