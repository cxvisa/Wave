/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vadiraj C S
 ***************************************************************************/

#include "Framework/Zeroize/PrismZeroizeAgent.h"
#include "Framework/Shutdown/PrismShutdownAgent.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/WaveFrameworkMessages.h"
#include "Framework/Zeroize/PrismZeroizeAgentContext.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/Core/Wave.h"

namespace WaveNs
{

PrismZeroizeAgent::PrismZeroizeAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : WaveWorker (pWaveObjectManager),
      m_currentFrameworkSequenceGenerator (currentFrameworkSequenceGenerator),
      m_pWaveObjectManager(pWaveObjectManager),
      m_zeroizeAtBoot(false)
{
}

PrismZeroizeAgent::PrismZeroizeAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator,bool zeroizeAtBoot)
    : WaveWorker (pWaveObjectManager),
      m_currentFrameworkSequenceGenerator (currentFrameworkSequenceGenerator),
      m_pWaveObjectManager(pWaveObjectManager),
      m_zeroizeAtBoot(zeroizeAtBoot)
{
}

PrismZeroizeAgent::~PrismZeroizeAgent ()
{
}

ResourceId PrismZeroizeAgent::execute ()
{
    WaveNs::PrismSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismZeroizeAgent::prepareFIPSZeroizeStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismZeroizeAgent::shutdownServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismZeroizeAgent::executeZeroizeStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismZeroizeAgent::completeFIPSZeroizeStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismZeroizeAgent::prismSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismZeroizeAgent::prismSynchronousLinearSequencerFailedStep)
    };

    PrismZeroizeAgentContext *pPrismZeroizeAgentContext = new PrismZeroizeAgentContext (reinterpret_cast<PrismAsynchronousContext *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    ResourceId status = pPrismZeroizeAgentContext->execute ();

    return (status);
}


ResourceId PrismZeroizeAgent::prepareFIPSZeroizeStep(PrismZeroizeAgentContext *pContext)
{
    vector<string> commandOutput;
    string          cmd = "/bin/touch " + WaveFrameworkObjectManager::getFIPSZeroizeFile();
    FrameworkToolKit::systemCommandOutput (cmd, commandOutput);
    trace (TRACE_LEVEL_INFO, "PrismZeroizeAgent::prepareFIPSZeroizeStep: Beginning System Call SYNC");
    sync ();
    trace (TRACE_LEVEL_INFO, "PrismZeroizeAgent::prepareFIPSZeroizeStep: Ending System Call SYNC");

    return (WAVE_MESSAGE_SUCCESS);
}


ResourceId PrismZeroizeAgent::shutdownServicesStep(PrismZeroizeAgentContext *pContext)
{

    ResourceId status = WAVE_MESSAGE_SUCCESS;

    /* At boot no services are started to shutdown. So we will skip this step.
     */
    if(isZeroizeAtBoot()) 
        return WAVE_MESSAGE_SUCCESS;

    trace(TRACE_LEVEL_INFO,"PrismZeroizeAgent::shutdownServicesStep: Shutting down all services\n");
    Wave::logOperationStatus (FIPS_OPERATION_SHUT_DOWN_SERVICES_FOR_ZEROIZE);

    FrameworkSequenceGenerator &frameworkSequenceGenerator = WaveFrameworkObjectManager::getCurrentFrameworkSequenceGenerator ();
  	PrismShutdownAgent *pShutdownAgent = new PrismShutdownAgent(m_pWaveObjectManager,frameworkSequenceGenerator);
    status = pShutdownAgent->execute();
    if(status != WAVE_MESSAGE_SUCCESS)
    {
        trace(TRACE_LEVEL_FATAL,"PrismZeroizeAgent::shutdownServicesStep: Shutting down all services failed\n");
        Wave::logOperationStatus (FIPS_OPERATION_FAILED_FOR_SERVICES_NOT_SHUT_DOWN);
    }
        
    delete pShutdownAgent;
    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId PrismZeroizeAgent::executeZeroizeStep(PrismZeroizeAgentContext *pContext)
{
    vector<WaveServiceId> &serviceIds = pContext->getZeroizableServices();
    UI32            i                     = 0;
    UI32            numberOfServices      = 0;    
    ResourceId      status				  = WAVE_MESSAGE_SUCCESS;
    
    serviceIds.clear ();
    m_currentFrameworkSequenceGenerator.getZeroizeSequence (serviceIds);
    
    
    trace (TRACE_LEVEL_INFO, "PrismZeroizeAgent::executeZeroizeStep: Entering...");
    Wave::logOperationStatus (FIPS_OPERATION_RUN_ZEROIZE_FOR_SUPPORTED_SERVICES);

    numberOfServices = serviceIds.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        
        if ( false == needsZeroize( serviceIds[i]) )
        {
            continue;
        }

        PrismZeroizeObjectManagerMessage lMessage (serviceIds[i]);

        status = sendSynchronously (&lMessage);

        if (WAVE_MESSAGE_SUCCESS != status) 
        {
            trace (TRACE_LEVEL_DEBUG, "PrismZeroizeAgent::executeZeroizeStep: Could not zeroize: " + FrameworkToolKit::getServiceNameById (serviceIds[i]));
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "PrismZeroizeAgent::executeZeroizeStep: Zeroized" + FrameworkToolKit::getServiceNameById (serviceIds[i]));
        }
    }
    return (WAVE_MESSAGE_SUCCESS);
}


ResourceId PrismZeroizeAgent::completeFIPSZeroizeStep(PrismZeroizeAgentContext *pContext)
{

    if(unlink(WaveFrameworkObjectManager::getFIPSZeroizeFile().c_str()) < 0)
    {
        trace (TRACE_LEVEL_ERROR, "PrismZeroizeAgent::completeFIPSZeroizeStep: Failed to cleanup FIPSZeroize File");
    }
    sync();
    return (WAVE_MESSAGE_SUCCESS);
}


bool PrismZeroizeAgent::isZeroizeAtBoot()
{
    return(m_zeroizeAtBoot);
}

bool PrismZeroizeAgent::needsZeroize(const WaveServiceId &waveServiceId)
{

    bool returnFlag = true;
    if (((WaveFrameworkObjectManager::getWaveServiceId ()) == waveServiceId))
    {
        returnFlag = false;
    }
    else if( (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))))
    {
        if ( TraceObjectManager::getWaveServiceId () == waveServiceId)
        {
            returnFlag = true;
        }
        else 
        {
            returnFlag = false;
        }
    }
    else
        returnFlag = true;

    return (returnFlag);
}



}
