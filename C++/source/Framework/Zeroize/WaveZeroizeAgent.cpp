/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vadiraj C S
 ***************************************************************************/

#include "Framework/Zeroize/WaveZeroizeAgent.h"
#include "Framework/Shutdown/WaveShutdownAgent.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/WaveFrameworkMessages.h"
#include "Framework/Zeroize/WaveZeroizeAgentContext.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/Core/Wave.h"

namespace WaveNs
{

WaveZeroizeAgent::WaveZeroizeAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : WaveWorker (pWaveObjectManager),
      m_currentFrameworkSequenceGenerator (currentFrameworkSequenceGenerator),
      m_pWaveObjectManager(pWaveObjectManager),
      m_zeroizeAtBoot(false)
{
}

WaveZeroizeAgent::WaveZeroizeAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator,bool zeroizeAtBoot)
    : WaveWorker (pWaveObjectManager),
      m_currentFrameworkSequenceGenerator (currentFrameworkSequenceGenerator),
      m_pWaveObjectManager(pWaveObjectManager),
      m_zeroizeAtBoot(zeroizeAtBoot)
{
}

WaveZeroizeAgent::~WaveZeroizeAgent ()
{
}

ResourceId WaveZeroizeAgent::execute ()
{
    WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveZeroizeAgent::prepareFIPSZeroizeStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveZeroizeAgent::shutdownServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveZeroizeAgent::executeZeroizeStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveZeroizeAgent::completeFIPSZeroizeStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveZeroizeAgent::waveSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveZeroizeAgent::waveSynchronousLinearSequencerFailedStep)
    };

    WaveZeroizeAgentContext *pWaveZeroizeAgentContext = new WaveZeroizeAgentContext (reinterpret_cast<WaveAsynchronousContext *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    ResourceId status = pWaveZeroizeAgentContext->execute ();

    return (status);
}


ResourceId WaveZeroizeAgent::prepareFIPSZeroizeStep(WaveZeroizeAgentContext *pContext)
{
    vector<string> commandOutput;
    string          cmd = "/bin/touch " + WaveFrameworkObjectManager::getFIPSZeroizeFile();
    FrameworkToolKit::systemCommandOutput (cmd, commandOutput);
    trace (TRACE_LEVEL_INFO, "WaveZeroizeAgent::prepareFIPSZeroizeStep: Beginning System Call SYNC");
    sync ();
    trace (TRACE_LEVEL_INFO, "WaveZeroizeAgent::prepareFIPSZeroizeStep: Ending System Call SYNC");

    return (WAVE_MESSAGE_SUCCESS);
}


ResourceId WaveZeroizeAgent::shutdownServicesStep(WaveZeroizeAgentContext *pContext)
{

    ResourceId status = WAVE_MESSAGE_SUCCESS;

    /* At boot no services are started to shutdown. So we will skip this step.
     */
    if(isZeroizeAtBoot()) 
        return WAVE_MESSAGE_SUCCESS;

    trace(TRACE_LEVEL_INFO,"WaveZeroizeAgent::shutdownServicesStep: Shutting down all services\n");
    Wave::logOperationStatus (FIPS_OPERATION_SHUT_DOWN_SERVICES_FOR_ZEROIZE);

    FrameworkSequenceGenerator &frameworkSequenceGenerator = WaveFrameworkObjectManager::getCurrentFrameworkSequenceGenerator ();
  	WaveShutdownAgent *pShutdownAgent = new WaveShutdownAgent(m_pWaveObjectManager,frameworkSequenceGenerator);
    status = pShutdownAgent->execute();
    if(status != WAVE_MESSAGE_SUCCESS)
    {
        trace(TRACE_LEVEL_FATAL,"WaveZeroizeAgent::shutdownServicesStep: Shutting down all services failed\n");
        Wave::logOperationStatus (FIPS_OPERATION_FAILED_FOR_SERVICES_NOT_SHUT_DOWN);
    }
        
    delete pShutdownAgent;
    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveZeroizeAgent::executeZeroizeStep(WaveZeroizeAgentContext *pContext)
{
    vector<WaveServiceId> &serviceIds = pContext->getZeroizableServices();
    UI32            i                     = 0;
    UI32            numberOfServices      = 0;    
    ResourceId      status				  = WAVE_MESSAGE_SUCCESS;
    
    serviceIds.clear ();
    m_currentFrameworkSequenceGenerator.getZeroizeSequence (serviceIds);
    
    
    trace (TRACE_LEVEL_INFO, "WaveZeroizeAgent::executeZeroizeStep: Entering...");
    Wave::logOperationStatus (FIPS_OPERATION_RUN_ZEROIZE_FOR_SUPPORTED_SERVICES);

    numberOfServices = serviceIds.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        
        if ( false == needsZeroize( serviceIds[i]) )
        {
            continue;
        }

        WaveZeroizeObjectManagerMessage lMessage (serviceIds[i]);

        status = sendSynchronously (&lMessage);

        if (WAVE_MESSAGE_SUCCESS != status) 
        {
            trace (TRACE_LEVEL_DEBUG, "WaveZeroizeAgent::executeZeroizeStep: Could not zeroize: " + FrameworkToolKit::getServiceNameById (serviceIds[i]));
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "WaveZeroizeAgent::executeZeroizeStep: Zeroized" + FrameworkToolKit::getServiceNameById (serviceIds[i]));
        }
    }
    return (WAVE_MESSAGE_SUCCESS);
}


ResourceId WaveZeroizeAgent::completeFIPSZeroizeStep(WaveZeroizeAgentContext *pContext)
{

    if(unlink(WaveFrameworkObjectManager::getFIPSZeroizeFile().c_str()) < 0)
    {
        trace (TRACE_LEVEL_ERROR, "WaveZeroizeAgent::completeFIPSZeroizeStep: Failed to cleanup FIPSZeroize File");
    }
    sync();
    return (WAVE_MESSAGE_SUCCESS);
}


bool WaveZeroizeAgent::isZeroizeAtBoot()
{
    return(m_zeroizeAtBoot);
}

bool WaveZeroizeAgent::needsZeroize(const WaveServiceId &waveServiceId)
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
