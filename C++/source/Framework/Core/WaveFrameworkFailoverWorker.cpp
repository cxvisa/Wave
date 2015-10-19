/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/WaveFrameworkFailoverWorker.h"
#include "WaveFrameworkFailoverWorkerContext.h"
#include "Framework/Core/WaveFrameworkFailoverWorkerSequencerContext.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Failover/PrismFailoverAgent.h"
#include "Framework/Failover/PrismFailoverAgentContext.h"
#include "Framework/Failover/PrismPrimaryControlledFailoverAgent.h"
#include "Framework/Failover/PrismPrimaryUncontrolledFailoverAgent.h"
#include "Framework/Failover/PrismSecondaryControlledFailoverAgent.h"
#include "Framework/Failover/PrismSecondaryUncontrolledFailoverAgent.h"
#include "Framework/Core/ClusterFailoverCompleteEvent.h"

namespace WaveNs
{

WaveFrameworkFailoverWorker::WaveFrameworkFailoverWorker (WaveObjectManager *pPrismObjectMnager)
    : WaveWorker (pPrismObjectMnager)
{
}

WaveFrameworkFailoverWorker::~WaveFrameworkFailoverWorker ()
{
}

void WaveFrameworkFailoverWorker::executeFailover (WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkFailoverWorker::executeFailover : Entering ...");

    PrismLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<PrismLinearSequencerStep> (&WaveFrameworkFailoverWorker::executeFailoverSelectFailoverAgentStep),
        reinterpret_cast<PrismLinearSequencerStep> (&WaveFrameworkFailoverWorker::executeFailoverRunFailoverAgentStep),
        reinterpret_cast<PrismLinearSequencerStep> (&WaveFrameworkFailoverWorker::executeFailoverCompleteEventStep),
        reinterpret_cast<PrismLinearSequencerStep> (&WaveFrameworkFailoverWorker::executeFailoverDestroyFailoverAgentStep),
        reinterpret_cast<PrismLinearSequencerStep> (&WaveFrameworkFailoverWorker::prismLinearSequencerSucceededStep),
        reinterpret_cast<PrismLinearSequencerStep> (&WaveFrameworkFailoverWorker::prismLinearSequencerFailedStep),
    };

    WaveFrameworkFailoverWorkerSequencerContext *pWaveFrameworkFailoverWorkerSequencerContext = new WaveFrameworkFailoverWorkerSequencerContext (pWaveFrameworkFailoverWorkerContext, this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    // Setup the sequencer context with inputs from the context that we recieved.

    pWaveFrameworkFailoverWorkerSequencerContext->setThisLocationRole   (pWaveFrameworkFailoverWorkerContext->getThisLocationRole ());
    pWaveFrameworkFailoverWorkerSequencerContext->setFailoverReason     (pWaveFrameworkFailoverWorkerContext->getFailoverReason ());
    pWaveFrameworkFailoverWorkerSequencerContext->setServiceToBeIgnored (pWaveFrameworkFailoverWorkerContext->getServiceToBeIgnored ());

    UI32 numberOfFailedLocations = pWaveFrameworkFailoverWorkerContext->getNumberOfFailedLocations ();
    UI32 i                       = 0;

    for (i = 0; i < numberOfFailedLocations; i++)
    {
        pWaveFrameworkFailoverWorkerSequencerContext->addFailedLocationId (pWaveFrameworkFailoverWorkerContext->getFailedLocationAtIndex (i));
    }

    pWaveFrameworkFailoverWorkerSequencerContext->holdAll ();
    pWaveFrameworkFailoverWorkerSequencerContext->start ();
}

void WaveFrameworkFailoverWorker::executeFailoverSelectFailoverAgentStep (WaveFrameworkFailoverWorkerSequencerContext *pWaveFrameworkFailoverWorkerSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkFailoverWorker::executeFailoverSelectFailoverAgentStep : Entering ...");

    FrameworkSequenceGenerator &frameworkSequenceGenerator = WaveFrameworkObjectManager::getCurrentFrameworkSequenceGenerator ();
    ResourceId                  status                     = WAVE_MESSAGE_SUCCESS;
    PrismFailoverAgent         *pPrismFailoverAgent        = NULL;

    if (LOCATION_PRIMARY == (pWaveFrameworkFailoverWorkerSequencerContext->getThisLocationRole ()))
    {
        if (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_CONTROLLED == (pWaveFrameworkFailoverWorkerSequencerContext->getFailoverReason ()))
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkFailoverWorker::executeFailoverSelectFailoverAgentStep : Selecting Primary Controlled Failover Agent.");

            pPrismFailoverAgent = new PrismPrimaryControlledFailoverAgent (m_pWaveObjectManager, frameworkSequenceGenerator);

            status = WAVE_MESSAGE_SUCCESS;
        }
        else if (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED == (pWaveFrameworkFailoverWorkerSequencerContext->getFailoverReason ()))
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkFailoverWorker::executeFailoverSelectFailoverAgentStep : Selecting Primary Uncontrolled Failover Agent.");

            pPrismFailoverAgent = new PrismPrimaryUncontrolledFailoverAgent (m_pWaveObjectManager, frameworkSequenceGenerator);

            status = WAVE_MESSAGE_SUCCESS;
        }
        else
        {
            waveAssert (false, __FILE__, __LINE__);

            status = FRAMEWORK_INVALID_FAILOVER_REASON_ON_PRIMARY;
        }
    }
    else if (LOCATION_SECONDARY == (pWaveFrameworkFailoverWorkerSequencerContext->getThisLocationRole ()))
    {
        if (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_CONTROLLED == (pWaveFrameworkFailoverWorkerSequencerContext->getFailoverReason ()))
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkFailoverWorker::executeFailoverSelectFailoverAgentStep : Selecting Secondary Controlled Failover Agent.");

            pPrismFailoverAgent = new PrismSecondaryControlledFailoverAgent (m_pWaveObjectManager, frameworkSequenceGenerator);


            WaveFrameworkFailoverWorkerContext* pPrismFailoverWorkerContext =  static_cast<WaveFrameworkFailoverWorkerContext* > (pWaveFrameworkFailoverWorkerSequencerContext->getPPrismAsynchronousContext ()); 

            if(pPrismFailoverWorkerContext->isSecondaryControlledFailoverDueToPrimaryRemoval() )
            {
               PrismSecondaryControlledFailoverAgent* pPrismSecondaryControlledFailoverAgent = static_cast<PrismSecondaryControlledFailoverAgent* > (pPrismFailoverAgent);
               pPrismSecondaryControlledFailoverAgent->setFailoverDueToPrimaryRemoval (); 
            }
             
            status = WAVE_MESSAGE_SUCCESS;
        }
        else if (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED == (pWaveFrameworkFailoverWorkerSequencerContext->getFailoverReason ()))
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkFailoverWorker::executeFailoverSelectFailoverAgentStep : Selecting Secondary Uncontrolled Failover Agent.");

            pPrismFailoverAgent = new PrismSecondaryUncontrolledFailoverAgent (m_pWaveObjectManager, frameworkSequenceGenerator);

            status = WAVE_MESSAGE_SUCCESS;
        }
        else
        {
            waveAssert (false, __FILE__, __LINE__);

            status = FRAMEWORK_INVALID_FAILOVER_REASON_ON_SECONDARY;
        }
    }
    else
    {
        waveAssert (false, __FILE__, __LINE__);

        status = FRAMEWORK_INVALID_LOCATION_ROLE_FOR_FAILOVER;
    }

    if (WAVE_MESSAGE_SUCCESS == status)
    {
        pWaveFrameworkFailoverWorkerSequencerContext->setPPrismFailoverAgent (pPrismFailoverAgent);
    }

    pWaveFrameworkFailoverWorkerSequencerContext->executeNextStep (status);
}

void WaveFrameworkFailoverWorker::executeFailoverRunFailoverAgentStep (WaveFrameworkFailoverWorkerSequencerContext *pWaveFrameworkFailoverWorkerSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkFailoverWorker::executeFailoverRunFailoverAgentStep : Entering ...");

    WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext = reinterpret_cast<WaveFrameworkFailoverWorkerContext *> (pWaveFrameworkFailoverWorkerSequencerContext->getPPrismAsynchronousContext ());
    PrismFailoverAgent                  *pPrismFailoverAgent                  = pWaveFrameworkFailoverWorkerSequencerContext->getPPrismFailoverAgent ();
    vector<LocationId>                   failedLocationIds;
    WaveServiceId                       serviceToBeIgnored                   = 0;

    waveAssert (NULL != pWaveFrameworkFailoverWorkerContext, __FILE__, __LINE__);

    pWaveFrameworkFailoverWorkerContext->getFailedLocationIds (failedLocationIds);
    serviceToBeIgnored = pWaveFrameworkFailoverWorkerSequencerContext->getServiceToBeIgnored ();

    waveAssert (NULL != pPrismFailoverAgent, __FILE__, __LINE__);

    PrismFailoverAgentContext *pPrismFailoverAgentContext = new PrismFailoverAgentContext (this, reinterpret_cast<PrismAsynchronousCallback> (&WaveFrameworkFailoverWorker::executeFailoverRunFailoverAgentStepCallback), pWaveFrameworkFailoverWorkerSequencerContext);

    pPrismFailoverAgentContext->setFailedLocationIds(failedLocationIds);
    pPrismFailoverAgentContext->setServiceToBeIgnored(serviceToBeIgnored);
    pPrismFailoverAgentContext->setIsConfigurationChange (pWaveFrameworkFailoverWorkerContext->getIsConfigurationChange ());
    
    pPrismFailoverAgent->execute (pPrismFailoverAgentContext);
}

void WaveFrameworkFailoverWorker::executeFailoverRunFailoverAgentStepCallback (PrismFailoverAgentContext *pPrismFailoverAgentContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkFailoverWorker::executeFailoverRunFailoverAgentStepCallback : Entering ...");

    waveAssert (NULL != pPrismFailoverAgentContext, __FILE__, __LINE__);

    WaveFrameworkFailoverWorkerSequencerContext *pWaveFrameworkFailoverWorkerSequencerContext = reinterpret_cast<WaveFrameworkFailoverWorkerSequencerContext *> (pPrismFailoverAgentContext->getPCallerContext ());

    waveAssert (NULL != pWaveFrameworkFailoverWorkerSequencerContext, __FILE__, __LINE__);

    ResourceId            status                = pWaveFrameworkFailoverWorkerSequencerContext->getCompletionStatus ();

    delete pPrismFailoverAgentContext;

    pWaveFrameworkFailoverWorkerSequencerContext->executeNextStep (status);
}

void WaveFrameworkFailoverWorker::executeFailoverDestroyFailoverAgentStep (WaveFrameworkFailoverWorkerSequencerContext *pWaveFrameworkFailoverWorkerSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkFailoverWorker::executeFailoverDestroyFailoverAgentStep : Entering ...");

    PrismFailoverAgent *pPrismFailoverAgent = pWaveFrameworkFailoverWorkerSequencerContext->getPPrismFailoverAgent ();

    waveAssert (NULL != pPrismFailoverAgent, __FILE__, __LINE__);

    delete (pPrismFailoverAgent);
    pWaveFrameworkFailoverWorkerSequencerContext->setPPrismFailoverAgent (NULL);

    pWaveFrameworkFailoverWorkerSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkFailoverWorker::executeFailoverCompleteEventStep (WaveFrameworkFailoverWorkerSequencerContext *pWaveFrameworkFailoverWorkerSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkFailoverWorker::executeFailoverCompleteEventStep : Entering ...");

    WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext = reinterpret_cast<WaveFrameworkFailoverWorkerContext *> (pWaveFrameworkFailoverWorkerSequencerContext->getPPrismAsynchronousContext ());    
    vector<LocationId>                   failedLocationIds;
    FrameworkObjectManagerFailoverReason failoverReason = pWaveFrameworkFailoverWorkerSequencerContext->getFailoverReason ();
    bool                                 isPrincipalChangedWithThisFailover = false;

    pWaveFrameworkFailoverWorkerContext->getFailedLocationIds (failedLocationIds);

    //Check if primary has gone down and accordingly set the principal changed flag
    if (LOCATION_SECONDARY == (pWaveFrameworkFailoverWorkerSequencerContext->getThisLocationRole ()))
    {
        isPrincipalChangedWithThisFailover = true;
    }

    ClusterFailoverCompleteEvent *pClusterFailoverCompleteEvent = new ClusterFailoverCompleteEvent (failoverReason, failedLocationIds, isPrincipalChangedWithThisFailover);
    
    //Broadcast the event
    ResourceId status = broadcast (pClusterFailoverCompleteEvent);

    if(status != WAVE_MESSAGE_SUCCESS)
    {
       trace(TRACE_LEVEL_ERROR, "WaveFrameworkFailoverWorker::executeFailoverCompleteEventStep: Failure during broadcast..");
       pWaveFrameworkFailoverWorkerSequencerContext->executeNextStep (status);
       return;
    }
    
    pWaveFrameworkFailoverWorkerSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

}
