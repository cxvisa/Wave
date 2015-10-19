/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Shutdown/WaveShutdownAgent.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/WaveFrameworkMessages.h"
#include "Framework/Shutdown/WaveShutdownAgentContext.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"

namespace WaveNs
{

WaveShutdownAgent::WaveShutdownAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : WaveWorker (pWaveObjectManager),
      m_currentFrameworkSequenceGenerator (currentFrameworkSequenceGenerator)
{
}

WaveShutdownAgent::~WaveShutdownAgent ()
{
}

ResourceId WaveShutdownAgent::execute ()
{
    WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveShutdownAgent::getListOfEnabledServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveShutdownAgent::shutdownServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveShutdownAgent::uninstallServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveShutdownAgent::disableServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveShutdownAgent::uninitializeServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveShutdownAgent::shutdownPostPhaseServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveShutdownAgent::uninstallPostPhaseServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveShutdownAgent::disablePostPhaseServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveShutdownAgent::uninitializePostPhaseServicesStep),

        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveShutdownAgent::prismSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveShutdownAgent::prismSynchronousLinearSequencerFailedStep)
    };

    WaveShutdownAgentContext *pWaveShutdownAgentContext = new WaveShutdownAgentContext (reinterpret_cast<WaveAsynchronousContext *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    ResourceId status = pWaveShutdownAgentContext->execute ();

    return (status);
}

ResourceId WaveShutdownAgent::getListOfEnabledServicesStep (WaveShutdownAgentContext *pWaveShutdownAgentContext)
{
    vector<WaveServiceId> &enabledServices = pWaveShutdownAgentContext->getEnabledServices ();

    WaveObjectManager::getListOfEnabledServices (enabledServices);

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveShutdownAgent::shutdownServicesStep (WaveShutdownAgentContext *pWaveShutdownAgentContext)
{
    vector<WaveServiceId> &serviceIdsToShutdown = pWaveShutdownAgentContext->getEnabledServices ();
    UI32                    i                    = 0;
    UI32                    numberOfServices     = 0;

    serviceIdsToShutdown.clear ();
    m_currentFrameworkSequenceGenerator.getShutdownSequence (serviceIdsToShutdown);

    numberOfServices = serviceIdsToShutdown.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (requiresShutdown (serviceIdsToShutdown[i])) || false == (WaveObjectManager::isServiceEnabled(serviceIdsToShutdown[i])))
        {
            continue;
        }

        WaveShutdownObjectManagerMessage prismShutdownObjectManagerMessage (serviceIdsToShutdown[i]);

        ResourceId status = sendSynchronously (&prismShutdownObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveBootAgent::shutdownServicesStep : Could not Shutdown a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToShutdown[i]));
            waveAssert (false, __FILE__, __LINE__);
            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Shutdown " + FrameworkToolKit::getServiceNameById (serviceIdsToShutdown[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveShutdownAgent::uninstallServicesStep (WaveShutdownAgentContext *pWaveShutdownAgentContext)
{
    vector<WaveServiceId> &serviceIdsToUninstall = pWaveShutdownAgentContext->getEnabledServices ();
    UI32                    i                     = 0;
    UI32                    numberOfServices      = 0;

    serviceIdsToUninstall.clear ();
    m_currentFrameworkSequenceGenerator.getUninstallSequence (serviceIdsToUninstall);

    numberOfServices = serviceIdsToUninstall.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (requiresShutdown (serviceIdsToUninstall[i])) || false == (WaveObjectManager::isServiceEnabled(serviceIdsToUninstall[i])))
        {
            continue;
        }

        WaveUninstallObjectManagerMessage prismUninstallObjectManagerMessage (serviceIdsToUninstall[i]);

        ResourceId status = sendSynchronously (&prismUninstallObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveBootAgent::uninstallServicesStep : Could not Shutdown a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToUninstall[i]));
            waveAssert (false, __FILE__, __LINE__);
            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Uninstall " + FrameworkToolKit::getServiceNameById (serviceIdsToUninstall[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveShutdownAgent::disableServicesStep (WaveShutdownAgentContext *pWaveShutdownAgentContext)
{
    vector<WaveServiceId> &serviceIdsToDisable = pWaveShutdownAgentContext->getEnabledServices ();
    UI32                    i                   = 0;
    UI32                    numberOfServices    = 0;

    serviceIdsToDisable.clear ();
    m_currentFrameworkSequenceGenerator.getDisableSequence (serviceIdsToDisable);

    numberOfServices = serviceIdsToDisable.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (requiresShutdown (serviceIdsToDisable[i])) || false == (WaveObjectManager::isServiceEnabled(serviceIdsToDisable[i])))
        {
            continue;
        }

        WaveDisableObjectManagerMessage prismDisableObjectManagerMessage (serviceIdsToDisable[i]);

        ResourceId status = sendSynchronously (&prismDisableObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveBootAgent::disableServicesStep : Could not disable a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToDisable[i]));

            waveAssert (false, __FILE__, __LINE__);
            return (status);

        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Disabled " + FrameworkToolKit::getServiceNameById (serviceIdsToDisable[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveShutdownAgent::uninitializeServicesStep (WaveShutdownAgentContext *pWaveShutdownAgentContext)
{
    vector<WaveServiceId> &serviceIdsToUninitialize = pWaveShutdownAgentContext->getEnabledServices ();
    UI32                    i                     = 0;
    UI32                    numberOfServices      = 0;

    serviceIdsToUninitialize.clear ();
    m_currentFrameworkSequenceGenerator.getUninitializeSequence (serviceIdsToUninitialize);

    numberOfServices = serviceIdsToUninitialize.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (requiresShutdown (serviceIdsToUninitialize[i])))
        {
            continue;
        }

        WaveUninitializeObjectManagerMessage prismUninitializeObjectManagerMessage (serviceIdsToUninitialize[i]);

        ResourceId status = sendSynchronously (&prismUninitializeObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveBootAgent::uninitializeServicesStep : Could not Uninitialize a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToUninitialize[i]));
            waveAssert (false, __FILE__, __LINE__);
            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Uninitialize " + FrameworkToolKit::getServiceNameById (serviceIdsToUninitialize[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveShutdownAgent::shutdownPostPhaseServicesStep (WaveShutdownAgentContext *pWaveShutdownAgentContext)
{
    vector<WaveServiceId> &serviceIdsToShutdown = pWaveShutdownAgentContext->getEnabledServices ();
    UI32                    i                    = 0;
    UI32                    numberOfServices     = 0;

    serviceIdsToShutdown.clear ();
    m_currentFrameworkSequenceGenerator.getShutdownSequenceDuringPostPhase (serviceIdsToShutdown);

    numberOfServices = serviceIdsToShutdown.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (requiresShutdown (serviceIdsToShutdown[i])) || false == (WaveObjectManager::isServiceEnabled(serviceIdsToShutdown[i])))
        {
            continue;
        }

        WaveShutdownObjectManagerMessage prismShutdownObjectManagerMessage (serviceIdsToShutdown[i]);

        ResourceId status = sendSynchronously (&prismShutdownObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveBootAgent::shutdownPostPhaseServicesStep : Could not Shutdown a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToShutdown[i]));
            waveAssert (false, __FILE__, __LINE__);
            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Shutdown " + FrameworkToolKit::getServiceNameById (serviceIdsToShutdown[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveShutdownAgent::uninstallPostPhaseServicesStep (WaveShutdownAgentContext *pWaveShutdownAgentContext)
{
    vector<WaveServiceId> &serviceIdsToUninstall = pWaveShutdownAgentContext->getEnabledServices ();
    UI32                    i                     = 0;
    UI32                    numberOfServices      = 0;

    serviceIdsToUninstall.clear ();
    m_currentFrameworkSequenceGenerator.getUninstallSequenceDuringPostPhase (serviceIdsToUninstall);

    numberOfServices = serviceIdsToUninstall.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (requiresShutdown (serviceIdsToUninstall[i]))  || false == (WaveObjectManager::isServiceEnabled(serviceIdsToUninstall[i])))
        {
            continue;
        }

        WaveUninstallObjectManagerMessage prismUninstallObjectManagerMessage (serviceIdsToUninstall[i]);

        ResourceId status = sendSynchronously (&prismUninstallObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveBootAgent::uninstallPostPhaseServicesStep : Could not Uninstall a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToUninstall[i]));
            waveAssert (false, __FILE__, __LINE__);
            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Uninstall " + FrameworkToolKit::getServiceNameById (serviceIdsToUninstall[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveShutdownAgent::disablePostPhaseServicesStep (WaveShutdownAgentContext *pWaveShutdownAgentContext)
{
    vector<WaveServiceId> &serviceIdsToDisable = pWaveShutdownAgentContext->getEnabledServices ();
    UI32                    i                   = 0;
    UI32                    numberOfServices    = 0;

    serviceIdsToDisable.clear ();
    m_currentFrameworkSequenceGenerator.getDisableSequenceDuringPostPhase (serviceIdsToDisable);

    numberOfServices = serviceIdsToDisable.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (requiresShutdown (serviceIdsToDisable[i])) || false == (WaveObjectManager::isServiceEnabled(serviceIdsToDisable[i])))
        {
            continue;
        }

        WaveDisableObjectManagerMessage prismDisableObjectManagerMessage (serviceIdsToDisable[i]);

        ResourceId status = sendSynchronously (&prismDisableObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveBootAgent::disablePostPhaseServicesStep : Could not disable a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToDisable[i]));
            waveAssert (false, __FILE__, __LINE__);
            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Disabled " + FrameworkToolKit::getServiceNameById (serviceIdsToDisable[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveShutdownAgent::uninitializePostPhaseServicesStep (WaveShutdownAgentContext *pWaveShutdownAgentContext)
{
    vector<WaveServiceId> &serviceIdsToUninitialize = pWaveShutdownAgentContext->getEnabledServices ();
    UI32                    i                     = 0;
    UI32                    numberOfServices      = 0;

    serviceIdsToUninitialize.clear ();
    m_currentFrameworkSequenceGenerator.getUninitializeSequenceDuringPostPhase (serviceIdsToUninitialize);

    numberOfServices = serviceIdsToUninitialize.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (requiresShutdown (serviceIdsToUninitialize[i])))
        {
            continue;
        }

        WaveUninitializeObjectManagerMessage prismUninitializeObjectManagerMessage (serviceIdsToUninitialize[i]);

        ResourceId status = sendSynchronously (&prismUninitializeObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "WaveBootAgent::uninitializePostPhaseServicesStep : Could not Uninitialize a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToUninitialize[i]));
            waveAssert (false, __FILE__, __LINE__);
            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Uninitialize " + FrameworkToolKit::getServiceNameById (serviceIdsToUninitialize[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

bool WaveShutdownAgent::requiresShutdown (const WaveServiceId &waveServiceId)
{
    if (((WaveFrameworkObjectManager::getWaveServiceId               ()) == waveServiceId) ||
        (true == (WaveLocalObjectManagerForUserSpecificTasks::isAUserSpecificService (waveServiceId))))
    {
        return (false);
    }
    else
    {
        return (true);
    }
}

}
