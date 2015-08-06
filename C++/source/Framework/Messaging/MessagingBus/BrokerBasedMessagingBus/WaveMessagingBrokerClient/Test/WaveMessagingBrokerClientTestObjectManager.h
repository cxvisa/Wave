/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMESSAGINGBROKERCLIENTTESTOBJECTMANAGER_H
#define WAVEMESSAGINGBROKERCLIENTTESTOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"
#include "Regression/PrismTestObjectManager.h"
#include "Regression/RegressionTestMessage.h"

namespace WaveNs
{

class PrismLinearSequencerContext;
class WaveBrokerPublishMessage;

class WaveMessagingBrokerClientTestObjectManager : public PrismTestObjectManager
{
    private :
        virtual void testRequestHandler                       (RegressionTestMessage *pRegressionTestMessage);

                void simpleWaveBrokerConnectTestStep          (PrismLinearSequencerContext *pPrismLinearSequencerContext);
                void simpleWaveBrokerSubscribeMessageTestStep (PrismLinearSequencerContext *pPrismLinearSequencerContext);
                void simpleWaveBrokerPublishMessageTestStep   (PrismLinearSequencerContext *pPrismLinearSequencerContext);

                void simpleSubscriptionCallback               (const WaveBrokerPublishMessage * const pWaveBrokerPublishMessage);

    protected :
    public :
                                                            WaveMessagingBrokerClientTestObjectManager ();
        virtual                                            ~WaveMessagingBrokerClientTestObjectManager ();

        static  string                                      getServiceName                             ();
        static  WaveServiceId                              getWaveServiceId                          ();
        static  WaveMessagingBrokerClientTestObjectManager *getInstance                                ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVEMESSAGINGBROKERCLIENTTESTOBJECTMANAGER_H
