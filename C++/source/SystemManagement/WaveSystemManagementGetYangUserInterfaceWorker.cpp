/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "SystemManagement/WaveSystemManagementGetYangUserInterfaceWorker.h"
#include "SystemManagement/WaveSystemManagementGetYangUserInterfaceMessage.h"
#include "SystemManagement/WaveSystemManagementObjectManager.h"
#include "SystemManagement/WaveSystemManagementTypes.h"
#include "Framework/Utils/PrismLinearSequencerContext.h"

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
    PrismLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<PrismLinearSequencerStep> (&WaveSystemManagementGetYangUserInterfaceWorker::getYangUserInterfaceCreateYangUserInterfaceStep),
        reinterpret_cast<PrismLinearSequencerStep> (&WaveSystemManagementGetYangUserInterfaceWorker::getYangUserInterfaceApplyAAAOnYangUserInterfaceStep),
        reinterpret_cast<PrismLinearSequencerStep> (&WaveSystemManagementGetYangUserInterfaceWorker::prismLinearSequencerSucceededStep),
        reinterpret_cast<PrismLinearSequencerStep> (&WaveSystemManagementGetYangUserInterfaceWorker::prismLinearSequencerFailedStep),
    };

    PrismLinearSequencerContext *pPrismLinearSequencerContext = new PrismLinearSequencerContext (pWaveSystemManagementGetYangUserInterfaceMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pPrismLinearSequencerContext->holdAll ();
    pPrismLinearSequencerContext->start ();
}

void WaveSystemManagementGetYangUserInterfaceWorker::getYangUserInterfaceCreateYangUserInterfaceStep (PrismLinearSequencerContext *pPrismLinearSequencerContext)
{
    WaveSystemManagementGetYangUserInterfaceMessage *pWaveSystemManagementGetYangUserInterfaceMessage = dynamic_cast<WaveSystemManagementGetYangUserInterfaceMessage *> (pPrismLinearSequencerContext->getPWaveMessage ());

    prismAssert (NULL != pWaveSystemManagementGetYangUserInterfaceMessage, __FILE__, __LINE__);

#if 0
    YangUserInterface *pClonedYangUserInterface = WaveSystemManagementObjectManager::getClonedYangUserInterface ();

    prismAssert (NULL != pClonedYangUserInterface, __FILE__, __LINE__);

    pClonedYangUserInterface->printYinToString (pWaveSystemManagementGetYangUserInterfaceMessage->getYangUserInterface ());
#else
    WaveSystemManagementObjectManager::getYinForYangUserInterface (pWaveSystemManagementGetYangUserInterfaceMessage->getYangUserInterface ());
#endif

    pPrismLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveSystemManagementGetYangUserInterfaceWorker::getYangUserInterfaceApplyAAAOnYangUserInterfaceStep (PrismLinearSequencerContext *pPrismLinearSequencerContext)
{
    pPrismLinearSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

}
