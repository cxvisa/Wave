/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Boot/WaveBootAgent.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Core/WaveFrameworkMessages.h"
#include "Framework/ObjectRelationalMapping/OrmRepository.h"
#include "Framework/ObjectRelationalMapping/OrmTable.h"
#include "Framework/Database/DatabaseObjectManagerExecuteTransactionMessage.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/ObjectModel/WavePersistableObject.h"
#include "Framework/Database/DatabaseStandaloneTransaction.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Core/WaveFrameworkObjectManagerInitializeWorker.h"
#include "Framework/Core/WaveNodeBackendSyncUpAgent.h"

namespace WaveNs
{

WaveBootAgent::WaveBootAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator)
    : WaveWorker (pWaveObjectManager),
      m_currentFrameworkSequenceGenerator (currentFrameworkSequenceGenerator)
{
}

WaveBootAgent::~WaveBootAgent ()
{
}

ResourceId WaveBootAgent::execute (const WaveBootPhase &waveBootPhase)
{
    WaveNs::WaveSynchronousLinearSequencerStep sequencerSteps[] =
    {
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveBootAgent::initializeWaveServicesDuringPrePhaseStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveBootAgent::enableWaveServicesDuringPrePhaseStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveBootAgent::listenForEventsWaveServicesDuringPrePhaseStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveBootAgent::installWaveServicesDuringPrePhaseStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveBootAgent::bootWaveServicesDuringPrePhaseStep),

        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveBootAgent::initializeLocalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveBootAgent::enableLocalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveBootAgent::listenForEventsLocalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveBootAgent::installLocalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveBootAgent::bootLocalWaveServicesStep),

        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveBootAgent::initializeGlobalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveBootAgent::enableGlobalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveBootAgent::listenForEventsGlobalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveBootAgent::installGlobalWaveServicesStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveBootAgent::bootGlobalWaveServicesStep),

        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveBootAgent::waveSynchronousLinearSequencerSucceededStep),
        reinterpret_cast<WaveSynchronousLinearSequencerStep> (&WaveBootAgent::waveSynchronousLinearSequencerFailedStep)
    };

    WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext = new WaveSynchronousLinearSequencerContext (reinterpret_cast<WaveMessage *> (NULL), this, sequencerSteps, sizeof (sequencerSteps) / sizeof (sequencerSteps[0]));

    ResourceId status = pWaveSynchronousLinearSequencerContext->execute ();

    return (status);
}

ResourceId WaveBootAgent::initializeWaveServicesDuringPrePhaseStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToInitialize;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getInitializeSequenceDuringPrePhase (serviceIdsToInitialize);

    numberOfServices = serviceIdsToInitialize.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (true == isToBeExcludedFromInitializeDuringPrePhase (serviceIdsToInitialize[i]))
        {
            continue;
        }

        if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
        {
            if (true != (FrameworkToolKit::isALocalService (serviceIdsToInitialize[i])))
            {
                continue;
            }
        }

        WaveInitializeObjectManagerMessage waveInitializeObjectManagerMessage (serviceIdsToInitialize[i], getReason ());

        ResourceId status = sendSynchronously (&waveInitializeObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::initializeWaveServicesDuringPrePhaseStep : Could not send a message to Initialize a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInitialize[i]) + ", Status : " + FrameworkToolKit::localize (status));

            return (status);
        }

        status = waveInitializeObjectManagerMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::initializeWaveServicesDuringPrePhaseStep : Could not Initialize a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInitialize[i]) + ", Status : " + FrameworkToolKit::localize (status));

            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Initialized " + FrameworkToolKit::getServiceNameById (serviceIdsToInitialize[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveBootAgent::listenForEventsWaveServicesDuringPrePhaseStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToEnable;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getEnableSequenceDuringPrePhase (serviceIdsToEnable);
    numberOfServices = serviceIdsToEnable.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
        {
            if (true != (FrameworkToolKit::isALocalService (serviceIdsToEnable[i])))
            {
                continue;
            }
        }

        if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToEnable[i])))
        {
            continue;
        }

        WaveListenForEventsObjectManagerMessage waveListenForEventsObjectManagerMessage (serviceIdsToEnable[i]);

        ResourceId status = sendSynchronously (&waveListenForEventsObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::listenForEventsWaveServicesDuringPrePhaseStep : Could not send a message to Listen For Events from a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));

            return (status);
        }

        status = waveListenForEventsObjectManagerMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::listenForEventsWaveServicesDuringPrePhaseStep : Could not Listen For Events from a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));

            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Listen For Events " + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveBootAgent::enableWaveServicesDuringPrePhaseStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToEnable;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getEnableSequenceDuringPrePhase (serviceIdsToEnable);
    numberOfServices = serviceIdsToEnable.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
        {
            if (true != (FrameworkToolKit::isALocalService (serviceIdsToEnable[i])))
            {
                continue;
            }
        }

        if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToEnable[i])))
        {
            continue;
        }

        WaveEnableObjectManagerMessage waveEnableObjectManagerMessage (serviceIdsToEnable[i], getReason ());

        ResourceId status = sendSynchronously (&waveEnableObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::enableWaveServicesDuringPrePhaseStep : Could not send a message to Enable a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));

            return (status);
        }

        status = waveEnableObjectManagerMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::enableWaveServicesDuringPrePhaseStep : Could not Enable a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));

            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Enabled " + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveBootAgent::installWaveServicesDuringPrePhaseStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToInstall;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getInstallSequenceDuringPrePhase (serviceIdsToInstall);
    numberOfServices = serviceIdsToInstall.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
        {
            if (true != (FrameworkToolKit::isALocalService (serviceIdsToInstall[i])))
            {
                continue;
            }
        }

        if (true == (isToBeExcludedFromInstallDuringPrePhase (serviceIdsToInstall[i])))
        {
            continue;
        }

        WaveInstallObjectManagerMessage waveInstallObjectManagerMessage (serviceIdsToInstall[i], getReason ());

        ResourceId status = sendSynchronously (&waveInstallObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::installWaveServicesDuringPrePhaseStep : Could not send a message to Install a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInstall[i]) + ", Status : " + FrameworkToolKit::localize (status));

            return (status);
        }

        status = waveInstallObjectManagerMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::installWaveServicesDuringPrePhaseStep : Could not Install a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInstall[i]) + ", Status : " + FrameworkToolKit::localize (status));

            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Installed " + FrameworkToolKit::getServiceNameById (serviceIdsToInstall[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveBootAgent::bootWaveServicesDuringPrePhaseStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToBoot;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getBootSequenceDuringPrePhase (serviceIdsToBoot);
    numberOfServices = serviceIdsToBoot.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
        {
            if (true != (FrameworkToolKit::isALocalService (serviceIdsToBoot[i])))
            {
                continue;
            }
        }

        if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToBoot[i])))
        {
            continue;
        }

        WaveBootObjectManagerMessage waveBootObjectManagerMessage (serviceIdsToBoot[i], getReason (), getRollBackFlag ());

        ResourceId status = sendSynchronously (&waveBootObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::bootWaveServicesDuringPrePhaseStep : Could not send a message to Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));

            return (status);
        }

        status = waveBootObjectManagerMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::bootWaveServicesDuringPrePhaseStep : Could not Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));

            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Booted " + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveBootAgent::initializeGlobalWaveServicesDuringPrePhaseStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToInitialize;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getInitializeSequenceDuringPrePhase (serviceIdsToInitialize);
    numberOfServices = serviceIdsToInitialize.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (true == isToBeExcludedFromInitializeDuringPrePhase (serviceIdsToInitialize[i]))
        {
            continue;
        }

        if (false == (FrameworkToolKit::isALocalService (serviceIdsToInitialize[i])))
        {
            WaveInitializeObjectManagerMessage waveInitializeObjectManagerMessage (serviceIdsToInitialize[i], getReason ());

            ResourceId status = sendSynchronously (&waveInitializeObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::initializeGlobalWaveServicesDuringPrePhaseStep : Could not send a message to Initialize a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInitialize[i]) + ",  Status : " + FrameworkToolKit::localize (status));

                return (status);
            }

            status = waveInitializeObjectManagerMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::initializeGlobalWaveServicesDuringPrePhaseStep : Could not Initialize a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInitialize[i]) + ", Status : " + FrameworkToolKit::localize (status));

                return (status);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "Initialized " + FrameworkToolKit::getServiceNameById (serviceIdsToInitialize[i]));
            }
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveBootAgent::listenForEventsGlobalServicesDuringPrePhaseStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToEnable;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getEnableSequenceDuringPrePhase (serviceIdsToEnable);
    numberOfServices = serviceIdsToEnable.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToEnable[i])))
        {
            continue;
        }

        if (false == (FrameworkToolKit::isALocalService (serviceIdsToEnable[i])))
        {
            WaveListenForEventsObjectManagerMessage waveListenForEventsObjectManagerMessage (serviceIdsToEnable[i]);

            ResourceId status = sendSynchronously (&waveListenForEventsObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::listenForEventsGlobalServicesDuringPrePhaseStep : Could not send a message to Listen For Events from a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }

            status = waveListenForEventsObjectManagerMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::listenForEventsGlobalServicesDuringPrePhaseStep : Could not Listen For Events from a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "Listen For Events  " + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]));
            }
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveBootAgent::enableGlobalWaveServicesDuringPrePhaseStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToEnable;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getEnableSequenceDuringPrePhase (serviceIdsToEnable);
    numberOfServices = serviceIdsToEnable.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToEnable[i])))
        {
            continue;
        }

        if (false == (FrameworkToolKit::isALocalService (serviceIdsToEnable[i])))
        {
            WaveEnableObjectManagerMessage waveEnableObjectManagerMessage (serviceIdsToEnable[i], getReason ());

            ResourceId status = sendSynchronously (&waveEnableObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::enableGlobalWaveServicesDuringPrePhaseStep : Could not send a message to Enable a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }

            status = waveEnableObjectManagerMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::enableGlobalWaveServicesDuringPrePhaseStep : Could not Enable a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "Enabled " + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]));
            }
        }
    }

    return (WAVE_MESSAGE_SUCCESS);

}

ResourceId WaveBootAgent::bootGlobalWaveServicesDuringPrePhaseStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToBoot;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getBootSequenceDuringPrePhase (serviceIdsToBoot);
    numberOfServices = serviceIdsToBoot.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToBoot[i])))
        {
            continue;
        }

        if (false == (FrameworkToolKit::isALocalService (serviceIdsToBoot[i])))
        {
            WaveBootObjectManagerMessage waveBootObjectManagerMessage (serviceIdsToBoot[i], getReason (), getRollBackFlag ());

            ResourceId status = sendSynchronously (&waveBootObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::bootGlobalWaveServicesDuringPrePhaseStep : Could not send a message to Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }

            status = waveBootObjectManagerMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::bootGlobalWaveServicesDuringPrePhaseStep : Could not Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "Booted " + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]));
            }
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveBootAgent::initializeLocalWaveServicesStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToInitialize;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getInitializeSequence (serviceIdsToInitialize);
    numberOfServices = serviceIdsToInitialize.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (true == (isToBeExcludedFromInitializePhase (serviceIdsToInitialize[i])))
        {
            continue;
        }

        if (true == (isToBeExcludedFromCurrentBootPhase (serviceIdsToInitialize[i])))
        {
            continue;
        }

        if (true == (FrameworkToolKit::isALocalService (serviceIdsToInitialize[i])))
        {
            WaveInitializeObjectManagerMessage waveInitializeObjectManagerMessage (serviceIdsToInitialize[i], getReason ());

            ResourceId status = sendSynchronously (&waveInitializeObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::initializeLocalWaveServicesStep : Could not send a message to Initialize a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInitialize[i]) + ",  Status : " + FrameworkToolKit::localize (status));
                return (status);
            }

            status = waveInitializeObjectManagerMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::initializeLocalWaveServicesStep : Could not Initialize a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInitialize[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "Initialized " + FrameworkToolKit::getServiceNameById (serviceIdsToInitialize[i]));
            }
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveBootAgent::initializeGlobalWaveServicesStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToInitialize;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getInitializeSequence (serviceIdsToInitialize);
    numberOfServices = serviceIdsToInitialize.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (true == (isToBeExcludedFromInitializePhase (serviceIdsToInitialize[i])))
        {
            continue;
        }

        if (false == (FrameworkToolKit::isALocalService (serviceIdsToInitialize[i])))
        {
            WaveInitializeObjectManagerMessage waveInitializeObjectManagerMessage (serviceIdsToInitialize[i], getReason ());

            ResourceId status = sendSynchronously (&waveInitializeObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::initializeGlobalWaveServicesStep : Could not send a message to Initialize a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInitialize[i]) + ",  Status : " + FrameworkToolKit::localize (status));
                return (status);
            }

            status = waveInitializeObjectManagerMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::initializeGlobalWaveServicesStep : Could not Initialize a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInitialize[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "Initialized " + FrameworkToolKit::getServiceNameById (serviceIdsToInitialize[i]));
            }
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveBootAgent::initializeWaveServicesStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToInitialize;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getInitializeSequence (serviceIdsToInitialize);
    numberOfServices = serviceIdsToInitialize.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (true == (isToBeExcludedFromInitializePhase (serviceIdsToInitialize[i])))
        {
            continue;
        }

        if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
        {
            if (true != (FrameworkToolKit::isALocalService (serviceIdsToInitialize[i])))
            {
                continue;
            }
        }

        WaveInitializeObjectManagerMessage waveInitializeObjectManagerMessage (serviceIdsToInitialize[i], getReason ());

        ResourceId status = sendSynchronously (&waveInitializeObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::initializeWaveServicesStep : Could not send a message to Initialize a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInitialize[i]) + ",  Status : " + FrameworkToolKit::localize (status));
            return (status);
        }

        status = waveInitializeObjectManagerMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::initializeWaveServicesStep : Could not Initialize a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInitialize[i]) + ", Status : " + FrameworkToolKit::localize (status));
            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Initialized " + FrameworkToolKit::getServiceNameById (serviceIdsToInitialize[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveBootAgent::listenForEventsLocalWaveServicesStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToEnable;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getEnableSequence (serviceIdsToEnable);
    numberOfServices = serviceIdsToEnable.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (true == (FrameworkToolKit::isALocalService (serviceIdsToEnable[i])))
        {
            if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
            {
                if (true != (FrameworkToolKit::isALocalService (serviceIdsToEnable[i])))
                {
                    continue;
                }
            }

            if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToEnable[i])))
            {
                continue;
            }

            WaveListenForEventsObjectManagerMessage waveListenForEventsObjectManagerMessage (serviceIdsToEnable[i]);

            ResourceId status = sendSynchronously (&waveListenForEventsObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::listenForEventsLocalWaveServicesStep : Could not send a message to Listen For Events from a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }

            status = waveListenForEventsObjectManagerMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::listenForEventsLocalWaveServicesStep : Could not Listen For Events from a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "Listen For Events " + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]));
            }
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}


ResourceId WaveBootAgent::enableLocalWaveServicesStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToEnable;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getEnableSequence (serviceIdsToEnable);
    numberOfServices = serviceIdsToEnable.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (true == (FrameworkToolKit::isALocalService (serviceIdsToEnable[i])))
        {
            if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
            {
                if (true != (FrameworkToolKit::isALocalService (serviceIdsToEnable[i])))
                {
                    continue;
                }
            }

            if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToEnable[i])))
            {
                continue;
            }

            WaveEnableObjectManagerMessage waveEnableObjectManagerMessage (serviceIdsToEnable[i], getReason ());

            ResourceId status = sendSynchronously (&waveEnableObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::enableLocalWaveServicesStep : Could not send a message to Enable a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }

            status = waveEnableObjectManagerMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::enableLocalWaveServicesStep : Could not Enable a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "Enabled " + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]));
            }
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveBootAgent::listenForEventsGlobalWaveServicesStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToEnable;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getEnableSequence (serviceIdsToEnable);
    numberOfServices = serviceIdsToEnable.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (FrameworkToolKit::isALocalService (serviceIdsToEnable[i])))
        {
            if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
            {
                if (true != (FrameworkToolKit::isALocalService (serviceIdsToEnable[i])))
                {
                    continue;
                }
            }

            if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToEnable[i])))
            {
                continue;
            }

            WaveListenForEventsObjectManagerMessage waveListenForEventsObjectManagerMessage (serviceIdsToEnable[i]);

            ResourceId status = sendSynchronously (&waveListenForEventsObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::listenForEventsGlobalWaveServicesStep : Could not send a message to Listen For Events from a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }

            status = waveListenForEventsObjectManagerMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::listenForEventsGlobalWaveServicesStep : Could not Listen For Events from a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "Listen For Events " + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]));
            }
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveBootAgent::enableGlobalWaveServicesStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToEnable;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getEnableSequence (serviceIdsToEnable);
    numberOfServices = serviceIdsToEnable.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (FrameworkToolKit::isALocalService (serviceIdsToEnable[i])))
        {
            if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
            {
                if (true != (FrameworkToolKit::isALocalService (serviceIdsToEnable[i])))
                {
                    continue;
                }
            }

            if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToEnable[i])))
            {
                continue;
            }

            WaveEnableObjectManagerMessage waveEnableObjectManagerMessage (serviceIdsToEnable[i], getReason ());

            ResourceId status = sendSynchronously (&waveEnableObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::enableGlobalWaveServicesStep : Could not send a message to Enable a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }

            status = waveEnableObjectManagerMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::enableGlobalWaveServicesStep : Could not Enable a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "Enabled " + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]));
            }
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveBootAgent::listenForEventsWaveServicesStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToEnable;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getEnableSequence (serviceIdsToEnable);
    numberOfServices = serviceIdsToEnable.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
        {
            if (true != (FrameworkToolKit::isALocalService (serviceIdsToEnable[i])))
            {
                continue;
            }
        }

        if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToEnable[i])))
        {
            continue;
        }

        // Excluding the Applicaiton service in phase 2 and framework service in phase 3
        if (true == (isToBeExcludedFromCurrentBootPhase (serviceIdsToEnable[i])))
        {
            continue;
        }

        WaveListenForEventsObjectManagerMessage waveListenForEventsObjectManagerMessage (serviceIdsToEnable[i]);

        ResourceId status = sendSynchronously (&waveListenForEventsObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::listenForEventsWaveServicesStep : Could not send a message to Listen For Events from a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));
            return (status);
        }

        status = waveListenForEventsObjectManagerMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::listenForEventsWaveServicesStep : Could not Listen For Events from a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));
            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Listen For Events " + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveBootAgent::enableWaveServicesStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToEnable;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getEnableSequence (serviceIdsToEnable);
    numberOfServices = serviceIdsToEnable.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
        {
            if (true != (FrameworkToolKit::isALocalService (serviceIdsToEnable[i])))
            {
                continue;
            }
        }

        if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToEnable[i])))
        {
            continue;
        }

        if (true == (isToBeExcludedFromCurrentBootPhase (serviceIdsToEnable[i])))
        {
            continue;
        }

        WaveEnableObjectManagerMessage waveEnableObjectManagerMessage (serviceIdsToEnable[i], getReason ());

        ResourceId status = sendSynchronously (&waveEnableObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::enableWaveServicesStep : Could not send a message to Enable a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));
            return (status);
        }

        status = waveEnableObjectManagerMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::enableWaveServicesStep : Could not Enable a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));
            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Enabled " + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveBootAgent::installLocalWaveServicesStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToInstall;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getInstallSequence (serviceIdsToInstall);
    numberOfServices = serviceIdsToInstall.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (true == (FrameworkToolKit::isALocalService (serviceIdsToInstall[i])))
        {
            if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
            {
                if (true != (FrameworkToolKit::isALocalService (serviceIdsToInstall[i])))
                {
                    continue;
                }
            }

            if (true == (isToBeExcludedFromInstall (serviceIdsToInstall[i])))
            {
                continue;
            }

            if (true == (isToBeExcludedFromCurrentBootPhase (serviceIdsToInstall[i])))
            {
                continue;
            }

            WaveInstallObjectManagerMessage waveInstallObjectManagerMessage (serviceIdsToInstall[i], getReason ());

            ResourceId status = sendSynchronously (&waveInstallObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::installLocalWaveServicesStep : Could not send a message to Install a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInstall[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }

            status = waveInstallObjectManagerMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::installLocalWaveServicesStep : Could not Install a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInstall[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "Installed " + FrameworkToolKit::getServiceNameById (serviceIdsToInstall[i]));
            }
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveBootAgent::installGlobalWaveServicesStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToInstall;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getInstallSequence (serviceIdsToInstall);
    numberOfServices = serviceIdsToInstall.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (FrameworkToolKit::isALocalService (serviceIdsToInstall[i])))
        {
            if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
            {
                if (true != (FrameworkToolKit::isALocalService (serviceIdsToInstall[i])))
                {
                    continue;
                }
            }

           if (true == (isToBeExcludedFromInstall (serviceIdsToInstall[i])))
           {
               continue;
           }

            WaveInstallObjectManagerMessage waveInstallObjectManagerMessage (serviceIdsToInstall[i], getReason ());

            ResourceId status = sendSynchronously (&waveInstallObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::installGlobalWaveServicesStep : Could not send a message to Install a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInstall[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }

            status = waveInstallObjectManagerMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::installGlobalWaveServicesStep : Could not Install a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInstall[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "Installed " + FrameworkToolKit::getServiceNameById (serviceIdsToInstall[i]));
            }
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveBootAgent::installWaveServicesStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToInstall;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getInstallSequence (serviceIdsToInstall);
    numberOfServices = serviceIdsToInstall.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
        {
            if (true != (FrameworkToolKit::isALocalService (serviceIdsToInstall[i])))
            {
                continue;
            }
        }

        WaveInstallObjectManagerMessage waveInstallObjectManagerMessage (serviceIdsToInstall[i], getReason ());

        ResourceId status = sendSynchronously (&waveInstallObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::installWaveServicesStep : Could not send a message to Install a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInstall[i]) + ", Status : " + FrameworkToolKit::localize (status));
            return (status);
        }

        status = waveInstallObjectManagerMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::installWaveServicesStep : Could not Install a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToInstall[i]) + ", Status : " + FrameworkToolKit::localize (status));
            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Installed " + FrameworkToolKit::getServiceNameById (serviceIdsToInstall[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveBootAgent::bootLocalWaveServicesStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToBoot;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getBootSequence (serviceIdsToBoot);
    numberOfServices = serviceIdsToBoot.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (true == (FrameworkToolKit::isALocalService (serviceIdsToBoot[i])))
        {
            if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
            {
                if (true != (FrameworkToolKit::isALocalService (serviceIdsToBoot[i])))
                {
                    continue;
                }
            }

            if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToBoot[i])))
            {
                continue;
            }

            WaveBootObjectManagerMessage waveBootObjectManagerMessage (serviceIdsToBoot[i], getReason (), getRollBackFlag ());

            ResourceId status = sendSynchronously (&waveBootObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::bootLocalWaveServicesStep : Could not send a message to Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }

            status = waveBootObjectManagerMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::bootLocalWaveServicesStep : Could not Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "Booted " + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]));
            }
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveBootAgent::updateUserDefinedKeyCombinationConstraintsAndKeysStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    ResourceId dbConversionStatus = FrameworkToolKit::getDbConversionStatus ();

    if ((false == FrameworkToolKit::getDetectSchemaChange ()) && (DATABASE_SCHEMA_CONVERSION_SUCCEEDED != dbConversionStatus))
    {
        trace (TRACE_LEVEL_INFO, "WaveBootAgent::updateUserDefinedKeyCombinationConstraintsAndKeysStep : exiting as no need for ForeignKeyConstraints application.");
        return (WAVE_MESSAGE_SUCCESS);
    }

    OrmRepository *pOrmRepository = OrmRepository::getInstance ();
    waveAssert(NULL != pOrmRepository, __FILE__, __LINE__);

    ManagedObjectSchemaInfoRepository & moSchemaInfoRepository  = pOrmRepository->getMOSchemaInfoRepository ();

    if (false == moSchemaInfoRepository.getIfUserDefinedKeyCombinationChanged ())
    {
        trace (TRACE_LEVEL_INFO, "WaveBootAgent::updateUserDefinedKeyCombinationConstraintsAndKeysStep: no changes for UserDefinedKeyCombination. exiting..");
        return (WAVE_MESSAGE_SUCCESS);
    }

    string alterSqlForCurrentSchema;
    string alterSqlForStartupSchema;
    string alterSql;

    // 1. Sql to update userDefinedKeyCombinationValue, KeyString and OwnerKeyString.
    moSchemaInfoRepository.getSqlToUpdateUserDefinedKeyCombinationForUpgrade (alterSqlForCurrentSchema, alterSqlForStartupSchema);

    trace (TRACE_LEVEL_INFO, "WaveBootAgent::updateUserDefinedKeyCombinationConstraintsAndKeysStep: sql to update UDKC values for current schema- \n" + alterSqlForCurrentSchema);

    alterSql = alterSqlForCurrentSchema + alterSqlForStartupSchema;

    ResourceId      status  = WAVE_MESSAGE_SUCCESS;

    if (alterSql != "")
    {
        DatabaseObjectManagerExecuteTransactionMessage message (alterSql);
        status = sendSynchronously (&message);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "WaveBootAgent::updateUserDefinedKeyCombinationConstraintsAndKeysStep : Could not send message to update values for udkc. Status : " + FrameworkToolKit::localize (status));
            //waveAssert (false, __FILE__, __LINE__);
        }
        else
        {
            status = message.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_ERROR, "WaveBootAgent::updateUserDefinedKeyCombinationConstraintsAndKeysStep:: failed to update udkc values. Status : " + FrameworkToolKit::localize (status));
                //waveAssert (false, __FILE__, __LINE__);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "WaveBootAgent::updateDatabaseForeignKeyConstraintsStep: successfully updated the corresponding udkc values.");
            }
        }
    }

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        /* This indicates DB is not in proper state. remove cfg file and reboot and come back with First time boot */
        handleUpgradeFailure (getServiceId ());
    }

    // 2.Sql to apply the constraint.
    alterSql = alterSqlForCurrentSchema = alterSqlForStartupSchema = "";

    moSchemaInfoRepository.getSqlToAddUserDefinedKeyUniqueConstraint (alterSqlForCurrentSchema, alterSqlForStartupSchema);

    trace (TRACE_LEVEL_INFO, "WaveBootAgent::updateUserDefinedKeyCombinationConstraintsAndKeysStep: sql to add udkc constraints for current schema- \n" + alterSqlForCurrentSchema);

    alterSql = alterSqlForCurrentSchema + alterSqlForStartupSchema;

    status  = WAVE_MESSAGE_SUCCESS;

    if (alterSql != "")
    {
        DatabaseObjectManagerExecuteTransactionMessage message (alterSql);
        status = sendSynchronously (&message);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "WaveBootAgent::updateUserDefinedKeyCombinationConstraintsAndKeysStep : Could not send message to add constraint for udkc. Status : " + FrameworkToolKit::localize (status));
            //waveAssert (false, __FILE__, __LINE__);
        }
        else
        {
            status = message.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_ERROR, "WaveBootAgent::updateUserDefinedKeyCombinationConstraintsAndKeysStep:: failed to add udkc constraints. Status : " + FrameworkToolKit::localize (status));
                //waveAssert (false, __FILE__, __LINE__);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "WaveBootAgent::updateDatabaseForeignKeyConstraintsStep: successfully added udkc constraints.");
            }
        }
    }

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        /* This indicates DB is not in proper state. remove cfg file and reboot and come back with First time boot */
        handleUpgradeFailure (getServiceId ());
    }

    return (status);
}

ResourceId WaveBootAgent::updateDatabaseForeignKeyConstraintsStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    ResourceId dbConversionStatus = FrameworkToolKit::getDbConversionStatus ();

    //  FrameworkToolKit::getDetectSchemaChange () : helps in identifying the Persistent boot during FWDL case. This flag will be false during "standby Schema conversion".
    //  During standby schema conversion, dbConversionStatus is set to NOT_ATTEMPTED in first step "configureStandbyValidateVersionStep" and will be set to
    //  DATABASE_SCHEMA_CONVERSION_SUCCEEDED only after successful conversion of schema. Hence, (DATABASE_SCHEMA_CONVERSION_SUCCEEDED != dbConversionStatus) check to have
    //  ForeignKeyConstraint application on successful standby schema conversion.

    if ((false == FrameworkToolKit::getDetectSchemaChange ()) && (DATABASE_SCHEMA_CONVERSION_SUCCEEDED != dbConversionStatus))
    {
        trace (TRACE_LEVEL_INFO, "WaveBootAgent::updateDatabaseForeignKeyConstraintsStep : exiting as no need for ForeignKeyConstraints application.");
        return (WAVE_MESSAGE_SUCCESS);
    }

    string alterSqlForCurrentSchema;
    string alterSqlForStartupSchema;
    string alterSql;

    OrmRepository *pOrmRepository = OrmRepository::getInstance ();
    waveAssert(NULL != pOrmRepository, __FILE__, __LINE__);

    ManagedObjectSchemaInfoRepository & moSchemaInfoRepository  = pOrmRepository->getMOSchemaInfoRepository ();

    map<string, ModifiedManagedObjectSchemaDifference> modifiedTablesSchemaDifference = moSchemaInfoRepository.getModifiedTablesSchemaDifference ();
    map<string, ModifiedManagedObjectSchemaDifference>::iterator mIterator;

    trace (TRACE_LEVEL_DEBUG, "WaveBootAgent::updateDatabaseForeignKeyConstraintsStep : Number of Modified Managed Objects : " + modifiedTablesSchemaDifference.size ());

    for (mIterator = modifiedTablesSchemaDifference.begin(); mIterator != modifiedTablesSchemaDifference.end(); mIterator++)
    {
        //(mIterator->second).printContentsForDebugging ();

        string modifiedManagedObjectName = mIterator->first;

        //Iterate through the vector of all added relationships
        vector<RelationshipInfoFromSchemaDifference> addedRelationsVector = (mIterator->second).getAddedRelations ();
        vector<RelationshipInfoFromSchemaDifference>::const_iterator relationsIterator = addedRelationsVector.begin();

        //---generate Alter statements to add NOT NULL constraints for 1:1 relationships
        for(;relationsIterator != addedRelationsVector.end(); ++relationsIterator)
        {
            if(ORM_RELATION_TYPE_ONE_TO_ONE == relationsIterator->getRelationType ())
            {
                OrmTable* pOrmTable = OrmRepository::getTableByName (modifiedManagedObjectName);
                alterSqlForCurrentSchema += pOrmTable->getAlterSqlToAddNotNullForOneToOneRelationship (OrmRepository::getWaveCurrentSchema() ,relationsIterator->getRelationName());
                alterSqlForStartupSchema += pOrmTable->getAlterSqlToAddNotNullForOneToOneRelationship (OrmRepository::getWaveStartSchema(), relationsIterator->getRelationName());
            }
        }

        //Iterate through the vector of all changed relationships
        vector<RelationshipInfoFromSchemaDifference> changedRelationsVector = (mIterator->second).getChangedRelations ();
        vector<RelationshipInfoFromSchemaDifference>::const_iterator changedRelationsIterator = changedRelationsVector.begin();

        //---generate Alter statements to add NOT NULL constraints for 1:1 relationships
        for(;changedRelationsIterator != changedRelationsVector.end(); ++changedRelationsIterator)
        {
            if (changedRelationsIterator->isCanBeEmptyChanged ())
            {
                if (changedRelationsIterator->getCanBeEmpty ())
                {
                    /* If canBeEmpty is true, Dropping NOT NULL is done during DB conversion only*/
                }
                else
                {
                    OrmTable* pOrmTable = OrmRepository::getTableByName (modifiedManagedObjectName);
                    alterSqlForCurrentSchema += pOrmTable->getAlterSqlToAddNotNullForOneToOneRelationship (OrmRepository::getWaveCurrentSchema() ,changedRelationsIterator->getRelationName());
                    alterSqlForStartupSchema += pOrmTable->getAlterSqlToAddNotNullForOneToOneRelationship (OrmRepository::getWaveStartSchema(), changedRelationsIterator->getRelationName());
                }
            }

            if (changedRelationsIterator->isDisableValidationChanged ())
            {
                trace (TRACE_LEVEL_INFO, "disableValidationChanged : " + changedRelationsIterator->isDisableValidationChanged ());
                if (changedRelationsIterator->getDisableValidations ())
                {
                    /* If Validations are disabled, we remove Foriegn Key Constraints during DB conversion only*/
                }
                else
                {
                    trace (TRACE_LEVEL_INFO, "disableValidation : " + changedRelationsIterator->getDisableValidations ());
                    OrmTable* pOrmTable = OrmRepository::getTableByName (modifiedManagedObjectName);
                    alterSqlForCurrentSchema += pOrmTable->getAlterSqlToEnableValidationForOneToManyRelationship (OrmRepository::getWaveCurrentSchema() ,changedRelationsIterator->getRelationName());
                    alterSqlForStartupSchema += pOrmTable->getAlterSqlToEnableValidationForOneToManyRelationship (OrmRepository::getWaveStartSchema(), changedRelationsIterator->getRelationName());
                }
            }
        }
    }

    alterSql = alterSqlForCurrentSchema + alterSqlForStartupSchema;

    trace (TRACE_LEVEL_INFO, "WaveBootAgent::updateDatabaseForeignKeyConstraintsStep : Alter SQL to add NOT NULL constraint is : " + alterSqlForCurrentSchema);

    ResourceId                                     status  = WAVE_MESSAGE_SUCCESS;

    if (alterSql != "")
    {
        DatabaseObjectManagerExecuteTransactionMessage message (alterSql);
        status = sendSynchronously (&message);

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_ERROR, "WaveBootAgent::updateDatabaseForeignKeyConstraintsStep : Could not send message to alter 1:1 relationship constraints. Status : " + FrameworkToolKit::localize (status));
            //waveAssert (false, __FILE__, __LINE__);
        }
        else
        {
            status = message.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_ERROR, "WaveBootAgent::updateDatabaseForeignKeyConstraintsStep:: failed to update 1:1 relationship constraints. Status : " + FrameworkToolKit::localize (status));
                //waveAssert (false, __FILE__, __LINE__);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "WaveBootAgent::updateDatabaseForeignKeyConstraintsStep: updated 1:1 relationship constraints.");
            }
        }
        /*
        DatabaseStandaloneTransaction dbStandaloneTransaction;
        if (!dbStandaloneTransaction.execute (alterSql))
        {
            trace (TRACE_LEVEL_ERROR, "WaveBootAgent::updateDatabaseForeignKeyConstraintsStep : Error in applying SQL to database");
            status = WAVE_MESSAGE_ERROR;
        }
        */
    }

    if (WAVE_MESSAGE_SUCCESS != status)
    {
        /* This indicates DB is not in proper state. remove cfg file and reboot and come back with First time boot */
        handleUpgradeFailure (getServiceId ());
    }

    return (status);
}

ResourceId WaveBootAgent::bootGlobalWaveServicesStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToBoot;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getBootSequence (serviceIdsToBoot);
    numberOfServices = serviceIdsToBoot.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (FrameworkToolKit::isALocalService (serviceIdsToBoot[i])))
        {
            if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
            {
                if (true != (FrameworkToolKit::isALocalService (serviceIdsToBoot[i])))
                {
                    continue;
                }
            }

            if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToBoot[i])))
            {
                continue;
            }

            WaveBootObjectManagerMessage waveBootObjectManagerMessage (serviceIdsToBoot[i], getReason (), getRollBackFlag ());

            ResourceId status = sendSynchronously (&waveBootObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::bootGlobalWaveServicesStep : Could not send a message to Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }

            status = waveBootObjectManagerMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::bootGlobalWaveServicesStep : Could not Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));
                return (status);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "Booted " + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]));
            }
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveBootAgent::bootWaveServicesStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    vector<WaveServiceId> serviceIdsToBoot;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getBootSequence (serviceIdsToBoot);
    numberOfServices = serviceIdsToBoot.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
        {
            if (true != (FrameworkToolKit::isALocalService (serviceIdsToBoot[i])))
            {
                continue;
            }
        }

        if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToBoot[i])))
        {
            continue;
        }

        if (true == (isToBeExcludedFromCurrentBootPhase (serviceIdsToBoot[i])))
        {
            continue;
        }

        WaveBootObjectManagerMessage waveBootObjectManagerMessage (serviceIdsToBoot[i], getReason (), getRollBackFlag ());

        ResourceId status = sendSynchronously (&waveBootObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::bootWaveServicesStep : Could not send a message to Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));
            return (status);
        }

        status = waveBootObjectManagerMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::bootWaveServicesStep : Could not Boot a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]) + ", Status : " + FrameworkToolKit::localize (status));
            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Booted " + FrameworkToolKit::getServiceNameById (serviceIdsToBoot[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId  WaveBootAgent::upgradeWaveServicesDuringPrePhaseStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    ResourceId dbConversionStatus = FrameworkToolKit::getDbConversionStatus ();

    if (DATABASE_SCHEMA_CONVERSION_SUCCEEDED != dbConversionStatus)
    {
        return (WAVE_MESSAGE_SUCCESS);
    }

    vector<WaveServiceId> serviceIdsToEnable;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getEnableSequenceDuringPrePhase (serviceIdsToEnable);
    numberOfServices = serviceIdsToEnable.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
        {
            if (true != (FrameworkToolKit::isALocalService (serviceIdsToEnable[i])))
            {
                continue;
            }
        }

        /* DO WE NEED THIS ?? SINCE UPGRADE IS CALLED ONLY FOR PERSISTENT SYSTEM BOOT UP CASE AND NOT THE CLUSTER BASED PHASES
        if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToEnable[i])))
        {
            continue;
        }*/

        WaveUpgradeObjectManagerMessage waveUpgradeObjectManagerMessage (serviceIdsToEnable[i], getReason ());

        ResourceId status = sendSynchronously (&waveUpgradeObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::upgradeWaveServicesDuringPrePhaseStep : Could not send a message to Upgrade a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));

            return (status);
        }

        status = waveUpgradeObjectManagerMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::upgradeWaveServicesDuringPrePhaseStep : Could not Upgrade a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));

            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "Upgraded " + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

void WaveBootAgent::handleUpgradeFailure (const WaveServiceId &serviceId)
{
    trace (TRACE_LEVEL_WARN, "WaveBootAgent::handleUpgradeFailure: upgrade failed for service : [" + FrameworkToolKit::getServiceNameById (serviceId) + "]");

    // 1. Configuration file will be removed and 2. system will be rebooted.
    // This will bring system in first time boot and configuration will be regained by config replay.");

    // 1.
    vector<string>  output;
    SI32            cmdStatus                  = 0;
    const string    waveConfigurationfileName = (WaveFrameworkObjectManager::getInstance ())->getConfigurationFileName ();

    trace (TRACE_LEVEL_WARN, "DatabaseObjectManager::handleUpgradeFailure: deleting file " + waveConfigurationfileName);

    cmdStatus = FrameworkToolKit::systemCommandOutput ((string ("/bin/rm -rf ") + waveConfigurationfileName).c_str(), output);

    if (0 != cmdStatus)
    {
        if (0 < output.size())
        {
            trace (TRACE_LEVEL_ERROR, string("DatabaseObjectManager::handleUpgradeFailure: cmd to deleted file ")+ waveConfigurationfileName + string(" failed with error message : ") + output[0]);
        }
    }


    // 2.
    //Wave::logOperationStatus (REBOOT_FOR_SERVICE_UPGRADE_FAILURE_AUTO_RECOVERY);
    // As RAS OM will not be ready by now, cant use raslog here.
    FrameworkToolKit::initializeConsolePrintFunction ();
    FrameworkToolKit::consolePrint (string("System going down for auto recovery as upgrade has failed for [" + FrameworkToolKit::getServiceNameById (serviceId) + "]"));

    trace (TRACE_LEVEL_WARN, "DatabaseObjectManager::handleUpgradeFailure: System going down for auto recovery as upgrade has failed for [" + FrameworkToolKit::getServiceNameById (serviceId) + "]");

    output.clear();
    FrameworkToolKit::systemCommandOutput ("/fabos/sbin/reboot -s -r AutoRecoveryForUpgradeFailure", output);
    waveSleep(30);

    trace (TRACE_LEVEL_WARN, "DatabaseObjectManager::handleUpgradeFailure: Reboot is triggered but system has not yet rebooted.");
    waveAssert (false, __FILE__, __LINE__);
}

ResourceId  WaveBootAgent::upgradeGlobalWaveServicesDuringPrePhaseStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    ResourceId dbConversionStatus = FrameworkToolKit::getDbConversionStatus ();

    if (DATABASE_SCHEMA_CONVERSION_SUCCEEDED != dbConversionStatus)
    {
        return (WAVE_MESSAGE_SUCCESS);
    }
    vector<WaveServiceId> serviceIdsToEnable;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getEnableSequenceDuringPrePhase (serviceIdsToEnable);
    numberOfServices = serviceIdsToEnable.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        /* DO WE NEED THIS ?? SINCE UPGRADE IS CALLED ONLY FOR PERSISTENT SYSTEM BOOT UP CASE AND NOT THE CLUSTER BASED PHASES
        if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToEnable[i])))
        {
            continue;
        }*/

        if (false == (FrameworkToolKit::isALocalService (serviceIdsToEnable[i])))
        {
            WaveUpgradeObjectManagerMessage waveUpgradeObjectManagerMessage (serviceIdsToEnable[i], getReason ());

            ResourceId status = sendSynchronously (&waveUpgradeObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::upgradeGlobalWaveServicesDuringPrePhaseStep : Could not send a message to Upgrade a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));

                return (status);
            }

            status = waveUpgradeObjectManagerMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::upgradeGlobalWaveServicesDuringPrePhaseStep : Could not Upgrade a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));

                if (false == FrameworkToolKit::isSchemaConversionDisabledByUser ())
                {
                    handleUpgradeFailure (serviceIdsToEnable[i]);
                }

                return (status);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "Upgraded " + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]));
            }
        }
    }

    return (WAVE_MESSAGE_SUCCESS);

}
ResourceId  WaveBootAgent::upgradeLocalWaveServicesStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    ResourceId dbConversionStatus = FrameworkToolKit::getDbConversionStatus ();

    if (DATABASE_SCHEMA_CONVERSION_SUCCEEDED != dbConversionStatus)
    {
        trace (TRACE_LEVEL_INFO, string("getDbConversionStatus") + FrameworkToolKit::localize (dbConversionStatus));
        return (WAVE_MESSAGE_SUCCESS);
    }

    vector<WaveServiceId> serviceIdsToEnable;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getEnableSequence (serviceIdsToEnable);
    numberOfServices = serviceIdsToEnable.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (true == (FrameworkToolKit::isALocalService (serviceIdsToEnable[i])))
        {
            if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
            {
                    continue;
            }

            if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToEnable[i])))
            {
                continue;
            }

            WaveUpgradeObjectManagerMessage waveUpgradeObjectManagerMessage (serviceIdsToEnable[i], getReason ());

            ResourceId status = sendSynchronously (&waveUpgradeObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::upgradeLocalWaveServicesStep : Could not send a message to Upgrade a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));

                return (status);
            }

            status = waveUpgradeObjectManagerMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::upgradeLocalWaveServicesStep : Could not Upgrade a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));

                if (false == FrameworkToolKit::isSchemaConversionDisabledByUser ())
                {
                    handleUpgradeFailure (serviceIdsToEnable[i]);
                }

                return (status);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "Upgraded " + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]));
            }
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId  WaveBootAgent::upgradeGlobalWaveServicesStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    ResourceId dbConversionStatus = FrameworkToolKit::getDbConversionStatus ();

    if (DATABASE_SCHEMA_CONVERSION_SUCCEEDED != dbConversionStatus)
    {
        trace (TRACE_LEVEL_INFO, string("getDbConversionStatus") + FrameworkToolKit::localize (dbConversionStatus));
        return (WAVE_MESSAGE_SUCCESS);
    }

    vector<WaveServiceId> serviceIdsToEnable;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getEnableSequence (serviceIdsToEnable);
    numberOfServices = serviceIdsToEnable.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if (false == (FrameworkToolKit::isALocalService (serviceIdsToEnable[i])))
        {
            if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
            {
                    continue;
            }

            if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToEnable[i])))
            {
                continue;
            }

            WaveUpgradeObjectManagerMessage waveUpgradeObjectManagerMessage (serviceIdsToEnable[i], getReason ());

            ResourceId status = sendSynchronously (&waveUpgradeObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::upgradeGlobalWaveServicesStep : Could not send a message to Upgrade a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));

                return (status);
            }

            status = waveUpgradeObjectManagerMessage.getCompletionStatus ();

            if (WAVE_MESSAGE_SUCCESS != status)
            {
                trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::upgradeGlobalWaveServicesStep : Could not Upgrade a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));


                if (false == FrameworkToolKit::isSchemaConversionDisabledByUser ())
                {
                    handleUpgradeFailure (serviceIdsToEnable[i]);
                }

                return (status);
            }
            else
            {
                trace (TRACE_LEVEL_INFO, "Upgraded " + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]));
            }
        }
    }

    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId  WaveBootAgent::upgradeWaveServicesStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    ResourceId dbConversionStatus = FrameworkToolKit::getDbConversionStatus ();

    if (DATABASE_SCHEMA_CONVERSION_SUCCEEDED != dbConversionStatus)
    {
        return (WAVE_MESSAGE_SUCCESS);
    }

    vector<WaveServiceId> serviceIdsToEnable;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    m_currentFrameworkSequenceGenerator.getEnableSequence (serviceIdsToEnable);
    numberOfServices = serviceIdsToEnable.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
        {
            if (true != (FrameworkToolKit::isALocalService (serviceIdsToEnable[i])))
            {
                continue;
            }
        }

        /* DO WE NEED THIS ?? SINCE UPGRADE IS CALLED ONLY FOR PERSISTENT SYSTEM BOOT UP CASE AND NOT THE CLUSTER BASED PHASES
        if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToEnable[i])))
        {
            continue;
        }*/

        WaveUpgradeObjectManagerMessage waveUpgradeObjectManagerMessage (serviceIdsToEnable[i], getReason ());

        ResourceId status = sendSynchronously (&waveUpgradeObjectManagerMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::upgradeWaveServicesStep: Could not send a message to Upgrade a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));

            return (status);
        }

        status = waveUpgradeObjectManagerMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::upgradeWaveServicesStep: Could not Upgrade a service : ") + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]) + ", Status : " + FrameworkToolKit::localize (status));

            if (false == FrameworkToolKit::isSchemaConversionDisabledByUser ())
            {
                handleUpgradeFailure (serviceIdsToEnable[i]);
            }

            return (status);
        }
        else
        {
            trace (TRACE_LEVEL_DEVEL, "Upgraded " + FrameworkToolKit::getServiceNameById (serviceIdsToEnable[i]));
        }
    }

    return (WAVE_MESSAGE_SUCCESS);

}

ResourceId  WaveBootAgent::databaseSanityCheckStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    //This step will send a message(WAVE_OBJECT_MANAGER_DATABASE_SANITY_CHECK) to all Local and Global services.
    vector<WaveServiceId> serviceIds;
    UI32                   i                       = 0;
    UI32                   numberOfServices        = 0;

    /*
     * TBD - Do this Sanity Check only if the last reboot was an abrupt reboot(kernel panic/power cycle)
     */

    if (false == FrameworkToolKit::getIsAbruptReboot ())
    {
        return (WAVE_MESSAGE_SUCCESS);
    }

    m_currentFrameworkSequenceGenerator.getBootSequence (serviceIds);
    numberOfServices = serviceIds.size ();

    for (i = 0; i < numberOfServices; i++)
    {
        WaveObjectManagerDatabaseSanityCheckMessage waveObjectManagerDatabaseSanityCheckMessage (serviceIds[i], getReason ());

        ResourceId status = sendSynchronously (&waveObjectManagerDatabaseSanityCheckMessage, FrameworkToolKit::getThisLocationId ());

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::databaseSanityCheckStep: Could not send a message to check Database Sanity to service : ") + FrameworkToolKit::getServiceNameById (serviceIds[i]) + ", Status : " + FrameworkToolKit::localize (status));
            return (status);
        }

        status = waveObjectManagerDatabaseSanityCheckMessage.getCompletionStatus ();

        if (WAVE_MESSAGE_SUCCESS != status)
        {
            trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::databaseSanityCheckStep: Database Sanity Check failed for service : ") + FrameworkToolKit::getServiceNameById (serviceIds[i]) + ", Status : " + FrameworkToolKit::localize (status));
            return (WAVE_MESSAGE_ERROR_DATABASE_INCONSISTENT);
        }
        else
        {
            trace (TRACE_LEVEL_INFO, "DB Sanity Check Done : " + FrameworkToolKit::getServiceNameById (serviceIds[i]));
        }
    }
    return (WAVE_MESSAGE_SUCCESS);
}

ResourceId WaveBootAgent::backendSyncUpStep (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext)
{
    trace (TRACE_LEVEL_INFO, "WaveBootAgent::backendSyncUpStep: Send back end sync up to all plug-ins .... ");

    ResourceId status = WAVE_MESSAGE_SUCCESS;

    WaveNodeBackendSyncUpAgent *pWaveNodeBackendSyncUpAgent = new WaveNodeBackendSyncUpAgent (m_pWaveObjectManager);

    status = pWaveNodeBackendSyncUpAgent->execute ();

    delete pWaveNodeBackendSyncUpAgent;

    if (WAVE_MESSAGE_SUCCESS != status)
    {
       trace (TRACE_LEVEL_FATAL, string ("WaveBootAgent::backendSyncUpStep Failed : Status : ") + FrameworkToolKit::localize (status));
    }

    return (status);
}

bool WaveBootAgent::isAPersistentBoot ()
{
    return (false);
}

bool WaveBootAgent::isToBeExcludedForEnableAndBoot (const WaveServiceId &waveServiceId)
{
    return (false);
}

bool WaveBootAgent::willBeAPrimaryLocation ()
{
    return ((FrameworkToolKit::isStandAloneLocation ()) || (FrameworkToolKit::isPrimaryLocation ()));
}

bool WaveBootAgent::isToBeExcludedFromInstallDuringPrePhase (const WaveServiceId &waveServiceId)
{
    return (false);
}

bool WaveBootAgent::isToBeExcludedFromInstall (const WaveServiceId &waveServiceId)
{
    return (false);
}

bool WaveBootAgent::isToBeExcludedFromCurrentBootPhase (WaveServiceId waveServiceId)
{
    return (false);
}

bool WaveBootAgent::isToBeExcludedFromInitializeDuringPrePhase (const WaveServiceId &waveServiceId)
{
    return (false);
}

bool WaveBootAgent::isToBeExcludedFromInitializePhase (const WaveServiceId &waveServiceId)
{
    return (false);
}

WaveBootReason WaveBootAgent::getReason () const
{
    return (WAVE_BOOT_FIRST_TIME_BOOT);
}

bool WaveBootAgent::getRollBackFlag () const
{
    return (false);
}

}
