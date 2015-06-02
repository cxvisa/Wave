/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEDELIVERBROKERPUBLISHMESSAGEWORKER_H
#define WAVEDELIVERBROKERPUBLISHMESSAGEWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class WaveObjectManager;
class WaveDeliverBrokerPublishMessage;

class WaveDeliverBrokerPublishMessageWorker : public WaveWorker
{
    private :
        void deliverBrokerPublishMessageHandler (WaveDeliverBrokerPublishMessage *pWaveDeliverBrokerPublishMessage);

    protected :
    public :
         WaveDeliverBrokerPublishMessageWorker (WaveObjectManager *pWaveObjectManager);
        ~WaveDeliverBrokerPublishMessageWorker ();

    // Now the data members.

    private :
    protected :
    public :
};

}

#endif // WAVEDELIVERBROKERPUBLISHMESSAGEWORKER_H
