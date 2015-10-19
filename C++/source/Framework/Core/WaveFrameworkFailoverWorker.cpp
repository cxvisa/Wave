/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/WaveFrameworkFailoverWorker.h"
#include "WaveFrameworkFailoverWorkerContext.h"
#include "Framework/Core/WaveFrameworkFailoverWorkerSequencerContext.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Failover/WaveFailoverAgent.h"
#include "Framework/Failover/WaveFailoverAgentContext.h"
#include "Framework/Failover/WavePrimaryControlledFailoverAgent.h"
#include "Framework/Failover/WavePrimaryUncontrolledFailoverAgent.h"
#include "Framework/Failover/WaveSecondaryControlledFailoverAgent.h"
#include "Framework/Failover/WaveSecondaryUncontrolledFailoverAgent.h"
#include "Framework/Core/ClusterFailoverCompleteEvent.h"

namespace WaveNs
{

WaveFrameworkFailoverWorker::WaveFrameworkFailoverWorker (WaveObjectManager *pWaveObjectMnager)
    : WaveWorker (pWaveObjectMnager)
{
}

WaveFrameworkFailoverWorker::~WaveFrameworkFailoverWorker ()
{
}

void WaveFrameworkFailoverWorker::executeFailover (WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkFailoverWorker::executeFailover : Entering ...");

    WaveLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkFailoverWorker::executeFailoverSelectFailoverAgentStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkFailoverWorker::executeFailoverRunFailoverAgentStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkFailoverWorker::executeFailoverCompleteEventStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkFailoverWorker::executeFailoverDestroyFailoverAgentStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkFailoverWorker::waveLinearSequencerSucceededStep),
        reinterpret_cast<WaveLinearSequencerStep> (&WaveFrameworkFailoverWorker::waveLinearSequencerFailedStep),
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
    WaveFailoverAgent         *pWaveFailoverAgent        = NULL;

    if (LOCATION_PRIMARY == (pWaveFrameworkFailoverWorkerSequencerContext->getThisLocationRole ()))
    {
        if (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_CONTROLLED == (pWaveFrameworkFailoverWorkerSequencerContext->getFailoverReason ()))
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkFailoverWorker::executeFailoverSelectFailoverAgentStep : Selecting Primary Controlled Failover Agent.");

            pWaveFailoverAgent = new WavePrimaryControlledFailoverAgent (m_pWaveObjectManager, frameworkSequenceGenerator);

            status = WAVE_MESSAGE_SUCCESS;
        }
        else if (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED == (pWaveFrameworkFailoverWorkerSequencerContext->getFailoverReason ()))
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkFailoverWorker::executeFailoverSelectFailoverAgentStep : Selecting Primary Uncontrolled Failover Agent.");

            pWaveFailoverAgent = new WavePrimaryUncontrolledFailoverAgent (m_pWaveObjectManager, frameworkSequenceGenerator);

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

            pWaveFailoverAgent = new WaveSecondaryControlledFailoverAgent (m_pWaveObjectManager, frameworkSequenceGenerator);


            WaveFrameworkFailoverWorkerContext* pWaveFailoverWorkerContext =  static_cast<WaveFrameworkFailoverWorkerContext* > (pWaveFrameworkFailoverWorkerSequencerContext->getPWaveAsynchronousContext ()); 

            if(pWaveFailoverWorkerContext->isSecondaryControlledFailoverDueToPrimaryRemoval() )
            {
               WaveSecondaryControlledFailoverAgent* pWaveSecondaryControlledFailoverAgent = static_cast<WaveSecondaryControlledFailoverAgent* > (pWaveFailoverAgent);
               pWaveSecondaryControlledFailoverAgent->setFailoverDueToPrimaryRemoval (); 
            }
             
            status = WAVE_MESSAGE_SUCCESS;
        }
        else if (FRAMEWORK_OBJECT_MANAGER_FAILOVER_REASON_UNCONTROLLED == (pWaveFrameworkFailoverWorkerSequencerContext->getFailoverReason ()))
        {
            trace (TRACE_LEVEL_INFO, "WaveFrameworkFailoverWorker::executeFailoverSelectFailoverAgentStep : Selecting Secondary Uncontrolled Failover Agent.");

            pWaveFailoverAgent = new WaveSecondaryUncontrolledFailoverAgent (m_pWaveObjectManager, frameworkSequenceGenerator);

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
        pWaveFrameworkFailoverWorkerSequencerContext->setPWaveFailoverAgent (pWaveFailoverAgent);
    }

    pWaveFrameworkFailoverWorkerSequencerContext->executeNextStep (status);
}

void WaveFrameworkFailoverWorker::executeFailoverRunFailoverAgentStep (WaveFrameworkFailoverWorkerSequencerContext *pWaveFrameworkFailoverWorkerSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkFailoverWorker::executeFailoverRunFailoverAgentStep : Entering ...");

    WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext = reinterpret_cast<WaveFrameworkFailoverWorkerContext *> (pWaveFrameworkFailoverWorkerSequencerContext->getPWaveAsynchronousContext ());
    WaveFailoverAgent                  *pWaveFailoverAgent                  = pWaveFrameworkFailoverWorkerSequencerContext->getPWaveFailoverAgent ();
    vector<LocationId>                   failedLocationIds;
    WaveServiceId                       serviceToBeIgnored                   = 0;

    waveAssert (NULL != pWaveFrameworkFailoverWorkerContext, __FILE__, __LINE__);

    pWaveFrameworkFailoverWorkerContext->getFailedLocationIds (failedLocationIds);
    serviceToBeIgnored = pWaveFrameworkFailoverWorkerSequencerContext->getServiceToBeIgnored ();

    waveAssert (NULL != pWaveFailoverAgent, __FILE__, __LINE__);

    WaveFailoverAgentContext *pWaveFailoverAgentContext = new WaveFailoverAgentContext (this, reinterpret_cast<WaveAsynchronousCallback> (&WaveFrameworkFailoverWorker::executeFailoverRunFailoverAgentStepCallback), pWaveFrameworkFailoverWorkerSequencerContext);

    pWaveFailoverAgentContext->setFailedLocationIds(failedLocationIds);
    pWaveFailoverAgentContext->setServiceToBeIgnored(serviceToBeIgnored);
    pWaveFailoverAgentContext->setIsConfigurationChange (pWaveFrameworkFailoverWorkerContext->getIsConfigurationChange ());
    
    pWaveFailoverAgent->execute (pWaveFailoverAgentContext);
}

void WaveFrameworkFailoverWorker::executeFailoverRunFailoverAgentStepCallback (WaveFailoverAgentContext *pWaveFailoverAgentContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkFailoverWorker::executeFailoverRunFailoverAgentStepCallback : Entering ...");

    waveAssert (NULL != pWaveFailoverAgentContext, __FILE__, __LINE__);

    WaveFrameworkFailoverWorkerSequencerContext *pWaveFrameworkFailoverWorkerSequencerContext = reinterpret_cast<WaveFrameworkFailoverWorkerSequencerContext *> (pWaveFailoverAgentContext->getPCallerContext ());

    waveAssert (NULL != pWaveFrameworkFailoverWorkerSequencerContext, __FILE__, __LINE__);

    ResourceId            status                = pWaveFrameworkFailoverWorkerSequencerContext->getCompletionStatus ();

    delete pWaveFailoverAgentContext;

    pWaveFrameworkFailoverWorkerSequencerContext->executeNextStep (status);
}

void WaveFrameworkFailoverWorker::executeFailoverDestroyFailoverAgentStep (WaveFrameworkFailoverWorkerSequencerContext *pWaveFrameworkFailoverWorkerSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkFailoverWorker::executeFailoverDestroyFailoverAgentStep : Entering ...");

    WaveFailoverAgent *pWaveFailoverAgent = pWaveFrameworkFailoverWorkerSequencerContext->getPWaveFailoverAgent ();

    waveAssert (NULL != pWaveFailoverAgent, __FILE__, __LINE__);

    delete (pWaveFailoverAgent);
    pWaveFrameworkFailoverWorkerSequencerContext->setPWaveFailoverAgent (NULL);

    pWaveFrameworkFailoverWorkerSequencerContext->executeNextStep (WAVE_MESSAGE_SUCCESS);
}

void WaveFrameworkFailoverWorker::executeFailoverCompleteEventStep (WaveFrameworkFailoverWorkerSequencerContext *pWaveFrameworkFailoverWorkerSequencerContext)
{
    trace (TRACE_LEVEL_DEVEL, "WaveFrameworkFailoverWorker::executeFailoverCompleteEventStep : Entering ...");

    WaveFrameworkFailoverWorkerContext *pWaveFrameworkFailoverWorkerContext = reinterpret_cast<WaveFrameworkFailoverWorkerContext *> (pWaveFrameworkFailoverWorkerSequencerContext->getPWaveAsynchronousContext ());    
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
