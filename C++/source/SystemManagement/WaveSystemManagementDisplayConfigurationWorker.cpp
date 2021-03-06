/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "SystemManagement/WaveSystemManagementDisplayConfigurationWorker.h"
#include "SystemManagement/WaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage.h"
#include "SystemManagement/WaveSystemManagementTypes.h"
#include "SystemManagement/DisplayCurrentConfigurationContext.h"
#include "SystemManagement/WaveSystemManagementObjectManager.h"
#include "SystemManagement/WaveConfigurationSegmentMap.h"
#include "Modeling/YANG/ObjectModel/YangDisplayConfigurationContext.h"
#include "SystemManagement/WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContext.h"
#include "Framework/ObjectModel/WaveManagedObject.h"
#include "Framework/ObjectModel/WaveManagedObjectToolKit.h"
#include "Framework/ObjectModel/WaveManagedObjectQueryContext.h"
#include "Framework/Utils/FrameworkToolKit.h"

namespace WaveNs
{

WaveSystemManagementDisplayConfigurationWorker::WaveSystemManagementDisplayConfigurationWorker (WaveObjectManager *pWaveObjectManager)
    : WaveWorker (pWaveObjectManager)
{
    addOperationMap (WAVE_SYSTEM_MANAGEMENT_DISPLAY_CURRENT_CONFIGURATION_BY_QUALIFIED_YANG_PATH, reinterpret_cast<WaveMessageHandler> (&WaveSystemManagementDisplayConfigurationWorker::displayCurrentConfigurationByQualifiedYangPathHandler));
    addOperationMap (WAVE_SYSTEM_MANAGEMENT_DISPLAY_CURRENT_CONFIGURATION_BY_TARGET_NODE_NAME,    reinterpret_cast<WaveMessageHandler> (&WaveSystemManagementDisplayConfigurationWorker::displayCurrentConfigurationByTargetNodeNameHandler));
}

WaveSystemManagementDisplayConfigurationWorker::~WaveSystemManagementDisplayConfigurationWorker ()
{
}

WaveMessage *WaveSystemManagementDisplayConfigurationWorker::createMessageInstance (const UI32 &operationCode)
{
    WaveMessage *pWaveMessage = NULL;

    switch (operationCode)
    {
        case WAVE_SYSTEM_MANAGEMENT_DISPLAY_CURRENT_CONFIGURATION_BY_QUALIFIED_YANG_PATH:
            pWaveMessage = new WaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage ();
            break;

        case WAVE_SYSTEM_MANAGEMENT_DISPLAY_CURRENT_CONFIGURATION_BY_TARGET_NODE_NAME:
            pWaveMessage = new WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage ();
            break;

        default :
            trace (TRACE_LEVEL_FATAL, string ("WaveSystemManagementDisplayConfigurationWorker::createMessageInstance : Unknown operation code : ") + operationCode);
            waveAssert (false, __FILE__, __LINE__);
            break;
    }

    return (pWaveMessage);
}

void WaveSystemManagementDisplayConfigurationWorker::displayCurrentConfigurationByQualifiedYangPathHandler (WaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage *pWaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSystemManagementDisplayConfigurationWorker::displayCurrentConfigurationByQualifiedYangPathComputeYangDisplayConfigurationContextStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSystemManagementDisplayConfigurationWorker::displayCurrentConfigurationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSystemManagementDisplayConfigurationWorker::waveLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSystemManagementDisplayConfigurationWorker::waveLinearSequencerFailedStep),
    };

    DisplayCurrentConfigurationContext *pDisplayCurrentConfigurationContext = new DisplayCurrentConfigurationContext (pWaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pDisplayCurrentConfigurationContext->holdAll ();
    pDisplayCurrentConfigurationContext->start ();
}

void WaveSystemManagementDisplayConfigurationWorker::displayCurrentConfigurationByQualifiedYangPathComputeYangDisplayConfigurationContextStep (DisplayCurrentConfigurationContext *pDisplayCurrentConfigurationContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveSystemManagementDisplayConfigurationWorker::displayCurrentConfigurationByQualifiedYangPathComputeYangDisplayConfigurationContextStep : Entering ...");

    WaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage *pWaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage = dynamic_cast<WaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage *> (pDisplayCurrentConfigurationContext->getPWaveMessage ());

    waveAssert (NULL != pWaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage, __FILE__, __LINE__);

    string       qualifiedYangPath  = pWaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage->getQualifiedYangPath ();
    YangElement *pYangElement       = (WaveSystemManagementObjectManager::getYangModuleCollection ())->getYangElementByQualifiedYangPath (qualifiedYangPath);
    string       ttyName            = pWaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage->getTtyName ();
    ResourceId   status             = WAVE_MESSAGE_SUCCESS;

    if (NULL != pYangElement)
    {
        pYangElement->debugPrint ();

        YangDisplayConfigurationContext *pYangDisplayConfigurationContext = new YangDisplayConfigurationContext ();
        FILE                            *pFile                            = NULL;
        string                           managedObjectClassName           = WaveConfigurationSegmentMap::getManagedObjectClassNameByConfigurationSegmentName (pYangElement->getConfigurationSegmentName ());
        WaveManagedObjectQueryContext   *pWaveManagedObjectQueryContext   = new WaveManagedObjectQueryContext (managedObjectClassName, this, reinterpret_cast<WaveAsynchronousCallback> (&WaveSystemManagementDisplayConfigurationWorker::displayCurrentConfigurationCallback), pDisplayCurrentConfigurationContext);
        vector<YangElement *>            yangElements;

        yangElements.push_back (pYangElement);

        if ("" != ttyName)
        {
            pFile = fopen (ttyName.c_str (), "a");
        }

        pYangDisplayConfigurationContext->setPFile (pFile);

        pWaveManagedObjectQueryContext->setPageSizeForQueryResults (50);

        pDisplayCurrentConfigurationContext->setYangElements                     (yangElements);
        pDisplayCurrentConfigurationContext->setPYangDisplayConfigurationContext (pYangDisplayConfigurationContext);
        pDisplayCurrentConfigurationContext->setPWaveManagedObjectQueryContext   (pWaveManagedObjectQueryContext);
    }
    else
    {
        status = WAVE_MESSAGE_ERROR;
    }

    pDisplayCurrentConfigurationContext->executeNextStep (status);
    return;
}

void WaveSystemManagementDisplayConfigurationWorker::displayCurrentConfigurationStep (DisplayCurrentConfigurationContext *pDisplayCurrentConfigurationContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveSystemManagementDisplayConfigurationWorker::displayCurrentConfigurationStep : Entering ...");

    WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext = pDisplayCurrentConfigurationContext->getPWaveManagedObjectQueryContext ();

    waveAssert (NULL != pWaveManagedObjectQueryContext, __FILE__, __LINE__);

    query (pWaveManagedObjectQueryContext);

    return;
}

void WaveSystemManagementDisplayConfigurationWorker::displayCurrentConfigurationCallback (WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext)
{
    DisplayCurrentConfigurationContext *pDisplayCurrentConfigurationContext = reinterpret_cast<DisplayCurrentConfigurationContext *> (pWaveManagedObjectQueryContext->getPCallerContext ());
    ResourceId                          status                              = pWaveManagedObjectQueryContext->getCompletionStatus ();

    waveAssert (NULL != pDisplayCurrentConfigurationContext, __FILE__, __LINE__);

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        trace (TRACE_LEVEL_ERROR, "WaveSystemManagementDisplayConfigurationWorker::displayCurrentConfigurationCallback : Query failed. Status : " + FrameworkToolKit::localize (status));

        pDisplayCurrentConfigurationContext->executeNextStep (status);
        return;
    }
    else
    {
        vector<WaveManagedObject *> *pResults = pWaveManagedObjectQueryContext->getPResults ();

        waveAssert (NULL != pResults, __FILE__, __LINE__);

        pWaveManagedObjectQueryContext->setPResults (NULL);

        UI32                             numberOfResults = pResults->size ();
        YangDisplayConfigurationContext *pYangDisplayConfigurationContext = pDisplayCurrentConfigurationContext->getPYangDisplayConfigurationContext ();
        YangElement                     *pYangElement                     = pDisplayCurrentConfigurationContext->getPYangElement                     ();

        waveAssert (NULL != pYangDisplayConfigurationContext, __FILE__, __LINE__);
        waveAssert (NULL != pYangElement,                     __FILE__, __LINE__);

        // If more results are expected, them issue the asynchronous query first before processing the current set of results.

        if (50 == numberOfResults)
        {
            displayCurrentConfigurationStep (pDisplayCurrentConfigurationContext);
        }

        if (0 != numberOfResults)
        {
            pYangDisplayConfigurationContext->setPManagedObjectsToDisplay (pResults);

            pYangElement->displayConfiguration (pYangDisplayConfigurationContext);
        }

        WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector (pResults);

        if (50 > numberOfResults)
        {
            if (true == (pDisplayCurrentConfigurationContext->isAtTheLastYangElement ()))
            {
                pDisplayCurrentConfigurationContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
                return;
            }
            else
            {
                pDisplayCurrentConfigurationContext->advanceToNextYangElement ();

                pYangElement = pDisplayCurrentConfigurationContext->getPYangElement ();

                string managedObjectClassName         = WaveConfigurationSegmentMap::getManagedObjectClassNameByConfigurationSegmentName (pYangElement->getConfigurationSegmentName ());

                pWaveManagedObjectQueryContext = new WaveManagedObjectQueryContext (managedObjectClassName, this, reinterpret_cast<WaveAsynchronousCallback> (&WaveSystemManagementDisplayConfigurationWorker::displayCurrentConfigurationCallback), pDisplayCurrentConfigurationContext);

                waveAssert (NULL != pWaveManagedObjectQueryContext, __FILE__, __LINE__);

                pWaveManagedObjectQueryContext->setPageSizeForQueryResults (50);

                pDisplayCurrentConfigurationContext->setPWaveManagedObjectQueryContext (pWaveManagedObjectQueryContext);

                displayCurrentConfigurationStep (pDisplayCurrentConfigurationContext);
            }
        }
    }
}

void WaveSystemManagementDisplayConfigurationWorker::displayCurrentConfigurationByTargetNodeNameHandler (WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage *pWaveSystemManagementDisplayConfigurationByTargetNodeNameMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSystemManagementDisplayConfigurationWorker::displayCurrentConfigurationByTargetNodeNameComputeYangDisplayConfigurationContextStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSystemManagementDisplayConfigurationWorker::displayCurrentConfigurationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSystemManagementDisplayConfigurationWorker::waveLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveSystemManagementDisplayConfigurationWorker::waveLinearSequencerFailedStep),
    };

    DisplayCurrentConfigurationContext *pDisplayCurrentConfigurationContext = new DisplayCurrentConfigurationContext (pWaveSystemManagementDisplayConfigurationByTargetNodeNameMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pDisplayCurrentConfigurationContext->holdAll ();
    pDisplayCurrentConfigurationContext->start ();
}

void WaveSystemManagementDisplayConfigurationWorker::displayCurrentConfigurationByTargetNodeNameComputeYangDisplayConfigurationContextStep (DisplayCurrentConfigurationContext *pDisplayCurrentConfigurationContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveSystemManagementDisplayConfigurationWorker::displayCurrentConfigurationByTargetNodeNameComputeYangDisplayConfigurationContextStep : Entering ...");

    WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage *pWaveSystemManagementDisplayConfigurationByTargetNodeNameMessage = dynamic_cast<WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage *> (pDisplayCurrentConfigurationContext->getPWaveMessage ());

    waveAssert (NULL != pWaveSystemManagementDisplayConfigurationByTargetNodeNameMessage, __FILE__, __LINE__);

    string       targetNodeName        = pWaveSystemManagementDisplayConfigurationByTargetNodeNameMessage->getTargetNodeName ();
    vector<YangElement *> yangElements = (WaveSystemManagementObjectManager::getYangUserInterface ())->getYangElementsByTargetNodeName (targetNodeName);
    string       ttyName               = pWaveSystemManagementDisplayConfigurationByTargetNodeNameMessage->getTtyName ();
    ResourceId   status                = WAVE_MESSAGE_SUCCESS;

    if (0 != (yangElements.size ()))
    {
        pDisplayCurrentConfigurationContext->setYangElements (yangElements);

        YangElement                     *pYangElement                     = pDisplayCurrentConfigurationContext->getPYangElement ();
        YangDisplayConfigurationContext *pYangDisplayConfigurationContext = new YangDisplayConfigurationContext ();
        FILE                            *pFile                            = NULL;
        string                           managedObjectClassName           = WaveConfigurationSegmentMap::getManagedObjectClassNameByConfigurationSegmentName (pYangElement->getConfigurationSegmentName ());
        WaveManagedObjectQueryContext   *pWaveManagedObjectQueryContext   = new WaveManagedObjectQueryContext (managedObjectClassName, this, reinterpret_cast<WaveAsynchronousCallback> (&WaveSystemManagementDisplayConfigurationWorker::displayCurrentConfigurationCallback), pDisplayCurrentConfigurationContext);

        pYangElement->debugPrint ();

        if ("" != ttyName)
        {
            pFile = fopen (ttyName.c_str (), "a");
        }

        pYangDisplayConfigurationContext->setPFile (pFile);

        pWaveManagedObjectQueryContext->setPageSizeForQueryResults (50);

        pDisplayCurrentConfigurationContext->setPYangElement                     (pYangElement);
        pDisplayCurrentConfigurationContext->setPYangDisplayConfigurationContext (pYangDisplayConfigurationContext);
        pDisplayCurrentConfigurationContext->setPWaveManagedObjectQueryContext   (pWaveManagedObjectQueryContext);
    }
    else
    {
        status = WAVE_MESSAGE_ERROR;
    }

    pDisplayCurrentConfigurationContext->executeNextStep (status);
    return;
}

}

