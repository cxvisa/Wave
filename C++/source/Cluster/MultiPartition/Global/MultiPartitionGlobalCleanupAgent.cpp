/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayaraman Iyer                                               *
 ***************************************************************************/

#include "Cluster/MultiPartition/Global/MultiPartitionGlobalCleanupAgent.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/WaveFrameworkMessages.h"
#include "Cluster/MultiPartition/Global/MultiPartitionObjectManager.h"
#include "Cluster/MultiPartition/Global/MultiPartitionGlobalCleanupAgentContext.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"

namespace WaveNs
{

MultiPartitionGlobalCleanupAgent::MultiPartitionGlobalCleanupAgent (WaveObjectManager *pWaveObjectManager, string &partitionName, UI32 senderServiceId, ObjectId &ownerPartitionManagedObjectId) 
    : WaveWorker                        (pWaveObjectManager),
      m_partitionName                   (partitionName),
      m_senderServiceId                 (senderServiceId),
      m_ownerPartitionManagedObjectId   (ownerPartitionManagedObjectId),
      m_isPartialCleanup                (false),
      m_partialCleanupTag               (FRAMEWORK_ERROR)
{
}

MultiPartitionGlobalCleanupAgent::~MultiPartitionGlobalCleanupAgent ()
{
}

bool MultiPartitionGlobalCleanupAgent::getIsPartialCleanup () const
{
    return m_isPartialCleanup;
}

void MultiPartitionGlobalCleanupAgent::setPartialCleanupTag (const ResourceId &partialCleanupTag)
{
    m_isPartialCleanup  = true;

    m_partialCleanupTag = partialCleanupTag;
}

ResourceId MultiPartitionGlobalCleanupAgent::getPartialCleanupTag ()
{
    waveAssert (true == m_isPartialCleanup, __FILE__, __LINE__);

    return m_partialCleanupTag;
}

ResourceId MultiPartitionGlobalCleanupAgent::execute ()
{
    trace (TRACE_LEVEL_INFO, "WaveMultiPartitionGlobalCleanupAgent::execute: called.");

    WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&MultiPartitionGlobalCleanupAgent::getListOfEnabledServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&MultiPartitionGlobalCleanupAgent::sendMultiPartitionGlobalCleanupStep),

        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&MultiPartitionGlobalCleanupAgent::prismSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&MultiPartitionGlobalCleanupAgent::prismSynchronousLinearSequencerFailedStep)
    };

    MultiPartitionGlobalCleanupAgentContext *pMultiPartitionGlobalCleanupAgentContext = new MultiPartitionGlobalCleanupAgentContext (reinterpret_cast<WaveAsynchronousContext *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    ResourceId status = pMultiPartitionGlobalCleanupAgentContext->execute ();

    return (status);
}

ResourceId MultiPartitionGlobalCleanupAgent::getListOfEnabledServicesStep (MultiPartitionGlobalCleanupAgentContext *pMultiPartitionGlobalCleanupAgentContext)
{
    trace (TRACE_LEVEL_INFO, "WaveMultiPartitionGlobalCleanupAgent::getListOfEnabledServicesStep: called.");
    vector<WaveServiceId> &enabledServices = pMultiPartitionGlobalCleanupAgentContext->getEnabledServices ();

    WaveObjectManager::getListOfEnabledServices (enabledServices);

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId MultiPartitionGlobalCleanupAgent::sendMultiPartitionGlobalCleanupStep (MultiPartitionGlobalCleanupAgentContext *pMultiPartitionGlobalCleanupAgentContext)
{
    vector<WaveServiceId> &serviceIdsToSendMultiPartitionCleanup   = pMultiPartitionGlobalCleanupAgentContext->getEnabledServices ();
    UI32                   i                                        = 0;
    UI32                   numberOfServices                         = serviceIdsToSendMultiPartitionCleanup.size();

    trace (TRACE_LEVEL_INFO, string ("WaveMultiPartitionGlobalCleanupAgent::sendMultiPartitionGlobalCleanupStep: called. Total Services = [ ") + (serviceIdsToSendMultiPartitionCleanup.size())+ string("]"));

    for (i = 0; i < numberOfServices; i++)
    {
        trace (TRACE_LEVEL_SUCCESS, "WaveMultiPartitionGlobalCleanupAgent::sendMultiPartitionGlobalCleanupStep: send PartitionCleanup to service: " + FrameworkToolKit::getServiceNameById (serviceIdsToSendMultiPartitionCleanup[i]));

        if (false == (requiresMultiPartitionGlobalCleanupNotification(serviceIdsToSendMultiPartitionCleanup[i])))
        {
            continue;
        }

        if (m_senderServiceId == serviceIdsToSendMultiPartitionCleanup[i])
        {
            // Don't send the cleanup to the caller service. 
            continue;
        }

        ObjectId ownerPartitionManagedObjectId = getOwnerPartitionManagedObjectId ();

        WaveMultiPartitionCleanupObjectManagerMessage *prismMultiPartitionCleanupObjectManagerMessage = new WaveMultiPartitionCleanupObjectManagerMessage (serviceIdsToSendMultiPartitionCleanup[i], m_partitionName, ownerPartitionManagedObjectId );

        if (true == getIsPartialCleanup ())
        {
            ResourceId partialCleanupTag = getPartialCleanupTag ();
            prismMultiPartitionCleanupObjectManagerMessage->setPartialCleanupTag (partialCleanupTag);
        }

        ResourceId status = sendSynchronously (prismMultiPartitionCleanupObjectManagerMessage);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveMultiPartitionGlobalCleanupAgent::sendMultiPartitionGlobalCleanupStep: Could not send PartitionCleanup to service: " + FrameworkToolKit::getServiceNameById (serviceIdsToSendMultiPartitionCleanup[i]));

            delete prismMultiPartitionCleanupObjectManagerMessage;

            return (status);
        }
        else
        {
            status = prismMultiPartitionCleanupObjectManagerMessage->getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, "WaveMultiPartitionGlobalCleanupAgent::sendMultiPartitionGlobalCleanupStep: Not able to update Instance Id  Completion Status : " + FrameworkToolKit::localize (status));
                waveAssert (false, __FILE__, __LINE__);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "WaveMultiPartitionGlobalCleanupAgent::sendMultiPartitionGlobalCleanupStep : Successfully sent MultiPartitionCleanup to Service: " + FrameworkToolKit::getServiceNameById (serviceIdsToSendMultiPartitionCleanup[i]));
            }
        }

        delete prismMultiPartitionCleanupObjectManagerMessage;
    }

    return (WAVE_MESSAGE_SUCCESS);
}

bool MultiPartitionGlobalCleanupAgent::requiresMultiPartitionGlobalCleanupNotification (const WaveServiceId &waveServiceId)
{
    // 1. Exlude WaveFrameworkObjectManager (in general.)
    // 2. Exclude MultiTenencyLocalObjectManager (It is running this Agent)
    // 3. Exclude Local services
    // 4. Exclude User Specific Local services.

    if (((WaveFrameworkObjectManager::getWaveServiceId()) == waveServiceId) ||
        ((MultiPartitionObjectManager::getWaveServiceId ()) == waveServiceId) ||
        (true == (FrameworkToolKit::isALocalService (waveServiceId))) ||
        (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))))
    {
        return (false);
    }
    else
    {
        return (true);
    }
}

ObjectId  MultiPartitionGlobalCleanupAgent::getOwnerPartitionManagedObjectId () const
{
    return (m_ownerPartitionManagedObjectId);
}

}
