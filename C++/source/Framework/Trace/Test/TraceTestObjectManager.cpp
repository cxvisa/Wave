/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Trace/Test/TraceTestObjectManager.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/FrameworkToolKit.h"

namespace WaveNs
{

TraceTestObjectManager::TraceTestObjectManager ()
    : WaveTestObjectManager ("Trace Test")
{
}

TraceTestObjectManager::~TraceTestObjectManager ()
{
}

TraceTestObjectManager *TraceTestObjectManager::getInstance ()
{
    static TraceTestObjectManager *pTraceTestObjectManager = NULL;

    if (NULL == pTraceTestObjectManager)
    {
        pTraceTestObjectManager = new TraceTestObjectManager ();
        WaveNs::waveAssert (NULL != pTraceTestObjectManager, __FILE__, __LINE__);
    }

    return (pTraceTestObjectManager);
}

WaveServiceId TraceTestObjectManager::getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

void TraceTestObjectManager::testRequestHandler (RegressionTestMessage *pRegressionTestMessage)
{
    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&TraceTestObjectManager::clearTraceClientsInformationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&TraceTestObjectManager::getTraceClientsInformationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&TraceTestObjectManager::displayTraceClientsInformationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&TraceTestObjectManager::getTraceClientTraceLevelStep),
        reinterpret_cast<WaveLinearSequencerStep> (&TraceTestObjectManager::setTraceClientTraceLevelStep),
        reinterpret_cast<WaveLinearSequencerStep> (&TraceTestObjectManager::clearTraceClientsInformationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&TraceTestObjectManager::getTraceClientsInformationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&TraceTestObjectManager::displayTraceClientsInformationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&TraceTestObjectManager::resetTraceClientTraceLevelStep),
        reinterpret_cast<WaveLinearSequencerStep> (&TraceTestObjectManager::clearTraceClientsInformationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&TraceTestObjectManager::getTraceClientsInformationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&TraceTestObjectManager::displayTraceClientsInformationStep),
        reinterpret_cast<WaveLinearSequencerStep> (&TraceTestObjectManager::waveLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&TraceTestObjectManager::waveLinearSequencerFailedStep),
    };

    TraceTestContext *pTraceTestContext = new TraceTestContext (pRegressionTestMessage, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    pTraceTestContext->holdAll ();
    pTraceTestContext->start ();
}

void TraceTestObjectManager::clearTraceClientsInformationStep (TraceTestContext *pTraceTestContext)
{
    pTraceTestContext->clearTraceClientsInformation ();

    pTraceTestContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void TraceTestObjectManager::getTraceClientsInformationStep (TraceTestContext *pTraceTestContext)
{
    TraceObjectManagerGetClientsInformationMessage message;

    WaveMessageStatus status = sendSynchronously (&message);

    if (WAVE_MESSAGE_SUCCESS == status)
    {
        ResourceId completionStatus = message.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != completionStatus)
        {
            trace (TRACE_LEVEL_ERROR, string ("TraceTestObjectManager::getTraceClientsInformationStep : Failed to get Trace Clients Information.  Completion Status = ") + completionStatus);
        }
        else
        {
            UI32          numberOfTraceClients = message.getNumberOfTraceClients ();
            UI32          i                    = 0;
            TraceClientId traceClientId;
            TraceLevel    traceLevel;

            for (i = 0; i < numberOfTraceClients; i++)
            {
                traceClientId = message.getTraceClientIdAt (i);
                traceLevel    = message.getTraceLevelAt (i);

                pTraceTestContext->addTraceClientInformation (traceClientId, traceLevel);
            }
        }

        pTraceTestContext->executeNextStep (completionStatus);
        return;
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, string ("TraceTestObjectManager::getTraceClientsInformationStep : Failed to get Trace Clients Information.  Status = ") + status);

        pTraceTestContext->executeNextStep (status);
        return;
    }
}

void TraceTestObjectManager::displayTraceClientsInformationStep (TraceTestContext *pTraceTestContext)
{
    UI32          numberOfTraceClients = pTraceTestContext->getNumberOfTraceClients ();
    UI32          i                    = 0;
    TraceClientId traceClientId;
    TraceLevel    traceLevel;
    char          buffer[1024];

    for (i = 0; i < numberOfTraceClients; i++)
    {
        traceClientId = pTraceTestContext->getTraceClientIdAt (i);
        traceLevel    = pTraceTestContext->getTraceLevelAt (i);

        sprintf (buffer, "%3u : %-50s : %3u", i + 1, (FrameworkToolKit::getTraceClientNameById (traceClientId)).c_str (), traceLevel);
        trace (TRACE_LEVEL_INFO, string (buffer));
    }

    pTraceTestContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void TraceTestObjectManager::getTraceClientTraceLevelStep (TraceTestContext *pTraceTestContext)
{
    TraceClientId                                traceClientId = getTraceClientId ();
    TraceObjectManagerGetClientTraceLevelMessage message       (traceClientId);

    trace (TRACE_LEVEL_INFO, string ("TraceTestObjectManager::getTraceClientTraceLevelStep : Trying to get Trace Level for \"") + FrameworkToolKit::getTraceClientNameById (traceClientId) + "\".");

    WaveMessageStatus status = sendSynchronously (&message);

    if (WAVE_MESSAGE_SUCCESS == status)
    {
        ResourceId completionStatus = message.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != completionStatus)
        {
            trace (TRACE_LEVEL_ERROR, string ("TraceTestObjectManager::getTraceClientTraceLevelStep : Error in getting Trace Client Level.  Completion Status = ") + completionStatus);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, string ("TraceTestObjectManager::getTraceClientTraceLevelStep : Got Trace Level for \"") + FrameworkToolKit::getTraceClientNameById (traceClientId) + "\" as : " + message.getTraceLevel ());
            pTraceTestContext->setTraceLevelForAClient (message.getTraceLevel ());
        }

        pTraceTestContext->executeNextStep (completionStatus);
        return;
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, string ("TraceTestObjectManager::getTraceClientTraceLevelStep : Error in sending message.  Status = ") + status);

        pTraceTestContext->executeNextStep (status);
        return;
    }
}

void TraceTestObjectManager::setTraceClientTraceLevelStep (TraceTestContext *pTraceTestContext)
{
    TraceClientId                                traceClientId = getTraceClientId ();
    TraceLevel                                   traceLevel    = TRACE_LEVEL_DEVEL;
    TraceObjectManagerSetClientTraceLevelMessage message       (traceClientId, traceLevel);

    trace (TRACE_LEVEL_INFO, string ("TraceTestObjectManager::setTraceClientTraceLevelStep : Trying to set Trace Level for \"") + FrameworkToolKit::getTraceClientNameById (traceClientId) + "\" to " + traceLevel);

    WaveMessageStatus status = sendSynchronously (&message);

    if (WAVE_MESSAGE_SUCCESS == status)
    {
        ResourceId completionStatus = message.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != completionStatus)
        {
            trace (TRACE_LEVEL_ERROR, string ("TraceTestObjectManager::setTraceClientTraceLevelStep : Error in setting Trace Client Level.  Completion Status = ") + completionStatus);
        }

        pTraceTestContext->executeNextStep (completionStatus);
        return;
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, string ("TraceTestObjectManager::setTraceClientTraceLevelStep : Error in sending message.  Status = ") + status);

        pTraceTestContext->executeNextStep (status);
        return;
    }
}

void TraceTestObjectManager::resetTraceClientTraceLevelStep (TraceTestContext *pTraceTestContext)
{
    TraceClientId                                traceClientId = getTraceClientId ();
    TraceLevel                                   traceLevel    = pTraceTestContext->getTraceLevelForAClient ();
    TraceObjectManagerSetClientTraceLevelMessage message       (traceClientId, traceLevel);

    trace (TRACE_LEVEL_INFO, string ("TraceTestObjectManager::resetTraceClientTraceLevelStep : Trying to Reset Trace Level for \"") + FrameworkToolKit::getTraceClientNameById (traceClientId) + "\" to " + traceLevel);

    WaveMessageStatus status = sendSynchronously (&message);

    if (WAVE_MESSAGE_SUCCESS == status)
    {
        ResourceId completionStatus = message.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != completionStatus)
        {
            trace (TRACE_LEVEL_ERROR, string ("TraceTestObjectManager::resetTraceClientTraceLevelStep : Error in setting Trace Client Level.  Completion Status = ") + completionStatus);
        }

        pTraceTestContext->executeNextStep (completionStatus);
        return;
    }
    else
    {
        trace (TRACE_LEVEL_ERROR, "TraceTestObjectManager::resetTraceClientTraceLevelStep : Error in sending message.  Status = " + status);

        pTraceTestContext->executeNextStep (status);
        return;
    }
}

}
