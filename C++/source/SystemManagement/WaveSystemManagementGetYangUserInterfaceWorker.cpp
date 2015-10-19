/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "SystemManagement/WaveSystemManagementGetYangUserInterfaceWorker.h"
#include "SystemManagement/WaveSystemManagementGetYangUserInterfaceMessage.h"
#include "SystemManagement/WaveSystemManagementObjectManager.h"
#include "SystemManagement/WaveSystemManagementTypes.h"
#include "Framework/Utils/WaveLinearSequencerContext.h"

namespace WaveNs
{

WaveSystemManagementGetYangUserInterfaceWorker::WaveSystemManagementGetYangUserInterfaceWorker (WaveSystemManagementObjectManager *pWaveSystemManagementObjectManager)
    : WaveWorker                           (pWaveSystemManagementObjectManager),
      m_pWaveSystemManagementObjectManager (pWaveSystemManagementObjectManager)
{
    addOperationMap (WAVE_SYSTEM_MANAGEMENT_GET_YANG_USER_INTERFACE, reinterpret_cast<WaveMessageHandler> (&WaveSystemManagementGetYangUserInterfaceWorker::getYangUserInterfaceMessageHandler));
}

WaveSystemManagementGetYangUserInterfaceWorker::~WaveSystemManagementGetYangUserInterfaceWorker ()
{
}

void WaveSystemManagementGetYangUserInterfaceWorker::getYangUserInterfaceMessageHandler (WaveSystemManagementGetYangUserInterfaceMessage *pWaveSystemManagementGetYangUserInterfaceMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSystemManagementGetYangUserInterfaceWorker::getYangUserInterfaceCreateYangUserInterfaceStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSystemManagementGetYangUserInterfaceWorker::getYangUserInterfaceApplyAAAOnYangUserInterfaceStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSystemManagementGetYangUserInterfaceWorker::prismLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSystemManagementGetYangUserInterfaceWorker::prismLinearSequencerFailedStep),
    };

    WaveLinearSequencerContext *pWaveLinearSequencerContext = new WaveLinearSequencerContext (pWaveSystemManagementGetYangUserInterfaceMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pWaveLinearSequencerContext->holdAll ();
    pWaveLinearSequencerContext->start ();
}

void WaveSystemManagementGetYangUserInterfaceWorker::getYangUserInterfaceCreateYangUserInterfaceStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    WaveSystemManagementGetYangUserInterfaceMessage *pWaveSystemManagementGetYangUserInterfaceMessage = dynamic_cast<WaveSystemManagementGetYangUserInterfaceMessage *> (pWaveLinearSequencerContext->getPWaveMessage ());

    waveAssert (NULL != pWaveSystemManagementGetYangUserInterfaceMessage, __FILE__, __LINE__);

#if 0
    YangUserInterface *pClonedYangUserInterface = WaveSystemManagementObjectManager::getClonedYangUserInterface ();

    waveAssert (NULL != pClonedYangUserInterface, __FILE__, __LINE__);

    pClonedYangUserInterface->printYinToString (pWaveSystemManagementGetYangUserInterfaceMessage->getYangUserInterface ());
#else
    WaveSystemManagementObjectManager::getYinForYangUserInterface (pWaveSystemManagementGetYangUserInterfaceMessage->getYangUserInterface ());
#endif

    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveSystemManagementGetYangUserInterfaceWorker::getYangUserInterfaceApplyAAAOnYangUserInterfaceStep (WaveLinearSequencerContext *pWaveLinearSequencerContext)
{
    pWaveLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

}
