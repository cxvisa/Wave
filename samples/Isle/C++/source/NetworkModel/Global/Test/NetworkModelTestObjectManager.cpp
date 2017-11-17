/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "NetworkModel/Global/Test/NetworkModelTestObjectManager.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "NetworkModel/Global/Test/NetworkModelTestContext.h"
#include "Framework/Utils/FrameworkToolKit.h"

namespace IsleNs
{

NetworkModelTestObjectManager::NetworkModelTestObjectManager ()
    : WaveTestObjectManager (getServiceName ())
{
}

NetworkModelTestObjectManager::~NetworkModelTestObjectManager ()
{
}

string NetworkModelTestObjectManager::getServiceName ()
{
    return ("Network Model Global Test");
}

NetworkModelTestObjectManager *NetworkModelTestObjectManager::getInstance ()
{
    static NetworkModelTestObjectManager *pNetworkModelTestObjectManager = new NetworkModelTestObjectManager ();

    WaveNs::waveAssert (NULL != pNetworkModelTestObjectManager, __FILE__, __LINE__);

    return (pNetworkModelTestObjectManager);
}

void NetworkModelTestObjectManager::testRequestHandler (RegressionTestMessage *pRegressionTestMessage)
{
    trace (TRACE_LEVEL_DEBUG, "NetworkModelTestObjectManager::testRequestHandler : Entering ...");

     WaveLinearSequencerStep sequencerSteps[] =
     {
         reinterpret_cast<WaveLinearSequencerStep> (&NetworkModelTestObjectManager::sampleStep),

         reinterpret_cast<WaveLinearSequencerStep> (&NetworkModelTestObjectManager::waveLinearSequencerSucceededStep),
         reinterpret_cast<WaveLinearSequencerStep> (&NetworkModelTestObjectManager::waveLinearSequencerFailedStep)
     };

     NetworkModelTestContext *pNetworkModelTestContext = new NetworkModelTestContext (pRegressionTestMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

     pNetworkModelTestContext->holdAll ();
     pNetworkModelTestContext->start   ();
}

void NetworkModelTestObjectManager::sampleStep (NetworkModelTestContext *pNetworkModelTestContext)
{
    trace (TRACE_LEVEL_DEVEL, "NetworkModelTestObjectManager::sampleStep : Entering ...");

    pNetworkModelTestContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
    return;
}

}
