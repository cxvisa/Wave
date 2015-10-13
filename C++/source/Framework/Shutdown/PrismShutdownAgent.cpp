/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Shutdown/PrismShutdownAgent.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/PrismFrameworkMessages.h"
#include "Framework/Shutdown/PrismShutdownAgentContext.h"
#include "Framework/Core/PrismFrameworkObjectManager.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"

namespace WaveNs
{

PrismShutdownAgent::PrismShutdownAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : WaveWorker (pWaveObjectManager),
      m_currentFrameworkSequenceGenerator (currentFrameworkSequenceGenerator)
{
}

PrismShutdownAgent::~PrismShutdownAgent ()
{
}

ResourceId PrismShutdownAgent::execute ()
{
    WaveNs::PrismSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismShutdownAgent::getListOfEnabledServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismShutdownAgent::shutdownServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismShutdownAgent::uninstallServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismShutdownAgent::disableServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismShutdownAgent::uninitializeServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismShutdownAgent::shutdownPostPhaseServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismShutdownAgent::uninstallPostPhaseServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismShutdownAgent::disablePostPhaseServicesStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismShutdownAgent::uninitializePostPhaseServicesStep),

        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismShutdownAgent::prismSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<PrismSynchronousLinearSequencerStep> (&PrismShutdownAgent::prismSynchronousLinearSequencerFailedStep)
    };

    PrismShutdownAgentContext *pPrismShutdownAgentContext = new PrismShutdownAgentContext (reinterpret_cast<PrismAsynchronousContext *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    ResourceId status = pPrismShutdownAgentContext->execute ();

    return (status);
}

ResourceId PrismShutdownAgent::getListOfEnabledServicesStep (PrismShutdownAgentContext *pPrismShutdownAgentContext)
{
    vector<WaveServiceId> &enabledServices = pPrismShutdownAgentContext->getEnabledServices ();

    WaveObjectManager::getListOfEnabledServices (enabledServices);

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId PrismShutdownAgent::shutdownServicesStep (PrismShutdownAgentContext *pPrismShutdownAgentContext)
{
    vector<WaveServiceId> &serviceIdsToShutdown = pPrismShutdownAgentContext->getEnabledServices ();
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

        PrismShutdownObjectManagerMessage prismShutdownObjectManagerMessage (serviceIdsToShutdown[i]);

        ResourceId status = sendSynchronously (&prismShutdownObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "PrismBootAgent::shutdownServicesStep : Could not Shutdown a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToShutdown[i]));
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

ResourceId PrismShutdownAgent::uninstallServicesStep (PrismShutdownAgentContext *pPrismShutdownAgentContext)
{
    vector<WaveServiceId> &serviceIdsToUninstall = pPrismShutdownAgentContext->getEnabledServices ();
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

        PrismUninstallObjectManagerMessage prismUninstallObjectManagerMessage (serviceIdsToUninstall[i]);

        ResourceId status = sendSynchronously (&prismUninstallObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "PrismBootAgent::uninstallServicesStep : Could not Shutdown a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToUninstall[i]));
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

ResourceId PrismShutdownAgent::disableServicesStep (PrismShutdownAgentContext *pPrismShutdownAgentContext)
{
    vector<WaveServiceId> &serviceIdsToDisable = pPrismShutdownAgentContext->getEnabledServices ();
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

        PrismDisableObjectManagerMessage prismDisableObjectManagerMessage (serviceIdsToDisable[i]);

        ResourceId status = sendSynchronously (&prismDisableObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "PrismBootAgent::disableServicesStep : Could not disable a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToDisable[i]));

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

ResourceId PrismShutdownAgent::uninitializeServicesStep (PrismShutdownAgentContext *pPrismShutdownAgentContext)
{
    vector<WaveServiceId> &serviceIdsToUninitialize = pPrismShutdownAgentContext->getEnabledServices ();
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

        PrismUninitializeObjectManagerMessage prismUninitializeObjectManagerMessage (serviceIdsToUninitialize[i]);

        ResourceId status = sendSynchronously (&prismUninitializeObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "PrismBootAgent::uninitializeServicesStep : Could not Uninitialize a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToUninitialize[i]));
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

ResourceId PrismShutdownAgent::shutdownPostPhaseServicesStep (PrismShutdownAgentContext *pPrismShutdownAgentContext)
{
    vector<WaveServiceId> &serviceIdsToShutdown = pPrismShutdownAgentContext->getEnabledServices ();
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

        PrismShutdownObjectManagerMessage prismShutdownObjectManagerMessage (serviceIdsToShutdown[i]);

        ResourceId status = sendSynchronously (&prismShutdownObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "PrismBootAgent::shutdownPostPhaseServicesStep : Could not Shutdown a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToShutdown[i]));
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

ResourceId PrismShutdownAgent::uninstallPostPhaseServicesStep (PrismShutdownAgentContext *pPrismShutdownAgentContext)
{
    vector<WaveServiceId> &serviceIdsToUninstall = pPrismShutdownAgentContext->getEnabledServices ();
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

        PrismUninstallObjectManagerMessage prismUninstallObjectManagerMessage (serviceIdsToUninstall[i]);

        ResourceId status = sendSynchronously (&prismUninstallObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "PrismBootAgent::uninstallPostPhaseServicesStep : Could not Uninstall a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToUninstall[i]));
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

ResourceId PrismShutdownAgent::disablePostPhaseServicesStep (PrismShutdownAgentContext *pPrismShutdownAgentContext)
{
    vector<WaveServiceId> &serviceIdsToDisable = pPrismShutdownAgentContext->getEnabledServices ();
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

        PrismDisableObjectManagerMessage prismDisableObjectManagerMessage (serviceIdsToDisable[i]);

        ResourceId status = sendSynchronously (&prismDisableObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "PrismBootAgent::disablePostPhaseServicesStep : Could not disable a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToDisable[i]));
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

ResourceId PrismShutdownAgent::uninitializePostPhaseServicesStep (PrismShutdownAgentContext *pPrismShutdownAgentContext)
{
    vector<WaveServiceId> &serviceIdsToUninitialize = pPrismShutdownAgentContext->getEnabledServices ();
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

        PrismUninitializeObjectManagerMessage prismUninitializeObjectManagerMessage (serviceIdsToUninitialize[i]);

        ResourceId status = sendSynchronously (&prismUninitializeObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, "PrismBootAgent::uninitializePostPhaseServicesStep : Could not Uninitialize a service : " + FrameworkToolKit::getServiceNameById (serviceIdsToUninitialize[i]));
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

bool PrismShutdownAgent::requiresShutdown (const WaveServiceId &waveServiceId)
{
    if (((PrismFrameworkObjectManager::getWaveServiceId               ()) == waveServiceId) ||
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
