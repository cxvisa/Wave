/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Boot;

import java.util.Set;
import java.util.Vector;

import com.CxWave.Wave.Framework.Core.FrameworkSequenceGenerator;
import com.CxWave.Wave.Framework.Core.Messages.WaveBootObjectManagerMessage;
import com.CxWave.Wave.Framework.Core.Messages.WaveEnableObjectManagerMessage;
import com.CxWave.Wave.Framework.Core.Messages.WaveInitializeObjectManagerMessage;
import com.CxWave.Wave.Framework.Core.Messages.WaveInstallObjectManagerMessage;
import com.CxWave.Wave.Framework.Core.Messages.WaveListenForEventsObjectManagerMessage;
import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Sequencer.WaveSynchronousLinearSequencerContext;
import com.CxWave.Wave.Framework.Utils.Source.WaveJavaSourceRepository;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.WaveBootReason;
import com.CxWave.Wave.Resources.ResourceEnums.WaveMessageStatus;

public class WaveBootAgent extends WaveWorker
{
    private Set<String>                      m_prePhaseServices;
    private Set<String>                      m_nonPrePhaseNativeServices;
    private Set<String>                      m_nonPrePhaseNonNativeServices;
    private final FrameworkSequenceGenerator m_currentFrameworkSequenceGenerator;

    public WaveBootAgent (final WaveObjectManager waveObjectManager, final FrameworkSequenceGenerator frameworkSequenceGenerator)
    {
        super (waveObjectManager);

        m_currentFrameworkSequenceGenerator = frameworkSequenceGenerator;
    }

    public ResourceId execute (final WaveBootPhase waveBootPhase)
    {
        infoTracePrintf ("WaveBootAgent.execute : Entering ...");

        final String[] synchronousSequencerSteps =
            {
                            "computeInstantiableServicesStep",
                            "initializeWaveServicesDuringPrePhaseStep",
                            "enableWaveServicesDuringPrePhaseStep",
                            "listenForEventsWaveServicesDuringPrePhaseStep",
                            "installWaveServicesDuringPrePhaseStep",
                            "bootWaveServicesDuringPrePhaseStep",

                            "initializeLocalWaveServicesStep",
                            "enableLocalWaveServicesStep",
                            "listenForEventsLocalWaveServicesStep",
                            "installLocalWaveServicesStep",
                            "bootLocalWaveServicesStep",

                            "initializeGlobalWaveServicesStep",
                            "enableGlobalWaveServicesStep",
                            "listenForEventsGlobalWaveServicesStep",
                            "installGlobalWaveServicesStep",
                            "bootGlobalWaveServicesStep",

                            "waveSynchronousLinearSequencerSucceededStep",
                            "waveSynchronousLinearSequencerFailedStep"
            };

        final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext = new WaveSynchronousLinearSequencerContext ((WaveMessage) null, this, synchronousSequencerSteps);

        final ResourceId status = waveSynchronousLinearSequencerContext.execute ();

        return (status);
    }

    private ResourceId computeInstantiableServicesStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.computeInstantiableServicesStep : Entering ...");

        final Set<String> prePhaseServices = WaveJavaSourceRepository.getAllAutoInstantiablePrePhaseObjectManagerClassNames ();

        infoTracePrintf ("WaveBootAgent.computeInstantiableServicesStep : Pre Phase Services :");

        for (final String prePhaseService : prePhaseServices)
        {
            infoTracePrintf ("WaveBootAgent.computeInstantiableServicesStep :     %s", prePhaseService);
        }

        final Set<String> nonPrePhaseNativeServices = WaveJavaSourceRepository.getAllAutoInstantiableNonPrePhaseNativeObjectManagerClassNames ();

        infoTracePrintf ("WaveBootAgent.computeInstantiableServicesStep : Non Pre Phase Native Services :");

        for (final String nonPrePhaseNativeService : nonPrePhaseNativeServices)
        {
            infoTracePrintf ("WaveBootAgent.computeInstantiableServicesStep :     %s", nonPrePhaseNativeService);
        }

        final Set<String> nonPrePhaseNonNativeServices = WaveJavaSourceRepository.getAllAutoInstantiableNonPrePhaseNonNativeObjectManagerClassNames ();

        infoTracePrintf ("WaveBootAgent.computeInstantiableServicesStep : Non Pre Phase Non Native Services :");

        for (final String nonPrePhaseNonNativeService : nonPrePhaseNonNativeServices)
        {
            infoTracePrintf ("WaveBootAgent.computeInstantiableServicesStep :     %s", nonPrePhaseNonNativeService);
        }

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId initializeWaveServicesDuringPrePhaseStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.initializeWaveServicesDuringPrePhaseStep : Entering ...");

        final Vector<WaveServiceId> serviceIdsToInitialize = new Vector<WaveServiceId> ();
        int i = 0;
        int numberOfServices = 0;

        m_currentFrameworkSequenceGenerator.getInitializeSequenceDuringPrePhase (serviceIdsToInitialize);

        numberOfServices = serviceIdsToInitialize.size ();

        for (i = 0; i < numberOfServices; i++)
        {
            if (true == isToBeExcludedFromInitializeDuringPrePhase (serviceIdsToInitialize.get (i)))
            {
                continue;
            }

            if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
            {
                if (true != (FrameworkToolKit.isALocalService (serviceIdsToInitialize.get (i))))
                {
                    continue;
                }
            }

            final WaveInitializeObjectManagerMessage waveInitializeObjectManagerMessage = new WaveInitializeObjectManagerMessage (serviceIdsToInitialize.get (i), getReason ());

            final WaveMessageStatus status = sendSynchronously (waveInitializeObjectManagerMessage, FrameworkToolKit.getThisLocationId ());

            if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
            {
                fatalTracePrintf ("WaveBootAgent.initializeWaveServicesDuringPrePhaseStep : Could not send a message to Initialize a service : %s, Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToInitialize.get (i)), FrameworkToolKit.localize (status));

                return (ResourceId.WAVE_MESSAGE_ERROR);
            }

            final ResourceId completionStatus = waveInitializeObjectManagerMessage.getCompletionStatus ();

            if (ResourceId.WAVE_MESSAGE_SUCCESS != completionStatus)
            {
                fatalTracePrintf ("WaveBootAgent.initializeWaveServicesDuringPrePhaseStep : Could not Initialize a service : %s, Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToInitialize.get (i)), FrameworkToolKit.localize (completionStatus));

                return (completionStatus);
            }
            else
            {
                infoTracePrintf ("Initialized %s", FrameworkToolKit.getServiceNameById (serviceIdsToInitialize.get (i)));
            }
        }

        return (ResourceId.WAVE_MESSAGE_SUCCESS);

    }

    private ResourceId enableWaveServicesDuringPrePhaseStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.enableWaveServicesDuringPrePhaseStep : Entering ...");

        final Vector<WaveServiceId> serviceIdsToEnable = new Vector<WaveServiceId> ();
        int i = 0;
        int numberOfServices = 0;

        m_currentFrameworkSequenceGenerator.getEnableSequenceDuringPrePhase (serviceIdsToEnable);
        numberOfServices = serviceIdsToEnable.size ();

        for (i = 0; i < numberOfServices; i++)
        {
            if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
            {
                if (true != (FrameworkToolKit.isALocalService (serviceIdsToEnable.get (i))))
                {
                    continue;
                }
            }

            if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToEnable.get (i))))
            {
                continue;
            }

            final WaveEnableObjectManagerMessage waveEnableObjectManagerMessage = new WaveEnableObjectManagerMessage (serviceIdsToEnable.get (i), getReason ());

            final WaveMessageStatus status = sendSynchronously (waveEnableObjectManagerMessage, FrameworkToolKit.getThisLocationId ());

            if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
            {
                fatalTracePrintf ("WaveBootAgent.initializeWaveServicesDuringPrePhaseStep : Could not send a message to Enable a service : %s, Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToEnable.get (i)), FrameworkToolKit.localize (status));

                return (ResourceId.WAVE_MESSAGE_ERROR);
            }

            final ResourceId completionStatus = waveEnableObjectManagerMessage.getCompletionStatus ();

            if (ResourceId.WAVE_MESSAGE_SUCCESS != completionStatus)
            {
                fatalTracePrintf ("WaveBootAgent.initializeWaveServicesDuringPrePhaseStep : Could not Enable a service : %s, Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToEnable.get (i)), FrameworkToolKit.localize (completionStatus));

                return (completionStatus);
            }
            else
            {
                infoTracePrintf ("Enabled " + (FrameworkToolKit.getServiceNameById (serviceIdsToEnable.get (i))));
            }
        }

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId listenForEventsWaveServicesDuringPrePhaseStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.listenForEventsWaveServicesDuringPrePhaseStep : Entering ...");

        final Vector<WaveServiceId> serviceIdsToEnable = new Vector<WaveServiceId> ();
        int i = 0;
        int numberOfServices = 0;

        m_currentFrameworkSequenceGenerator.getEnableSequenceDuringPrePhase (serviceIdsToEnable);
        numberOfServices = serviceIdsToEnable.size ();

        for (i = 0; i < numberOfServices; i++)
        {
            if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
            {
                if (true != (FrameworkToolKit.isALocalService (serviceIdsToEnable.get (i))))
                {
                    continue;
                }
            }

            if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToEnable.get (i))))
            {
                continue;
            }

            final WaveListenForEventsObjectManagerMessage waveListenForEventsObjectManagerMessage = new WaveListenForEventsObjectManagerMessage (serviceIdsToEnable.get (i), getReason ());

            final WaveMessageStatus status = sendSynchronously (waveListenForEventsObjectManagerMessage, FrameworkToolKit.getThisLocationId ());

            if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
            {
                fatalTracePrintf ("WaveBootAgent.listenForEventsWaveServicesDuringPrePhaseStep : Could not send a message to Listen for Events from a service : %s, Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToEnable.get (i)), FrameworkToolKit.localize (status));

                return (ResourceId.WAVE_MESSAGE_ERROR);
            }

            final ResourceId completionStatus = waveListenForEventsObjectManagerMessage.getCompletionStatus ();

            if (ResourceId.WAVE_MESSAGE_SUCCESS != completionStatus)
            {
                fatalTracePrintf ("WaveBootAgent.listenForEventsWaveServicesDuringPrePhaseStep : Could not Listen for Events from a service : %s, Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToEnable.get (i)), FrameworkToolKit.localize (completionStatus));

                return (completionStatus);
            }
            else
            {
                infoTracePrintf ("Listen for Events " + (FrameworkToolKit.getServiceNameById (serviceIdsToEnable.get (i))));
            }
        }

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId installWaveServicesDuringPrePhaseStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.installWaveServicesDuringPrePhaseStep : Entering ...");

        final Vector<WaveServiceId> serviceIdsToInstall = new Vector<WaveServiceId> ();
        int i = 0;
        int numberOfServices = 0;

        m_currentFrameworkSequenceGenerator.getInstallSequenceDuringPrePhase (serviceIdsToInstall);
        numberOfServices = serviceIdsToInstall.size ();

        for (i = 0; i < numberOfServices; i++)
        {
            if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
            {
                if (true != (FrameworkToolKit.isALocalService (serviceIdsToInstall.get (i))))
                {
                    continue;
                }
            }

            if (true == (isToBeExcludedFromInstallDuringPrePhase (serviceIdsToInstall.get (i))))
            {
                continue;
            }

            final WaveInstallObjectManagerMessage waveInstallObjectManagerMessage = new WaveInstallObjectManagerMessage (serviceIdsToInstall.get (i), getReason ());

            final WaveMessageStatus status = sendSynchronously (waveInstallObjectManagerMessage, FrameworkToolKit.getThisLocationId ());

            if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
            {
                fatalTracePrintf ("WaveBootAgent.installWaveServicesDuringPrePhaseStep : Could not send a message toInstall a service : %s, Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToInstall.get (i)), FrameworkToolKit.localize (status));

                return (ResourceId.WAVE_MESSAGE_ERROR);
            }

            final ResourceId completionStatus = waveInstallObjectManagerMessage.getCompletionStatus ();

            if (ResourceId.WAVE_MESSAGE_SUCCESS != completionStatus)
            {
                fatalTracePrintf ("WaveBootAgent.installWaveServicesDuringPrePhaseStep : Could not Install a service : %s, Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToInstall.get (i)), FrameworkToolKit.localize (completionStatus));

                return (completionStatus);
            }
            else
            {
                infoTracePrintf ("Installed " + (FrameworkToolKit.getServiceNameById (serviceIdsToInstall.get (i))));
            }
        }

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId bootWaveServicesDuringPrePhaseStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.bootWaveServicesDuringPrePhaseStep : Entering ...");

        final Vector<WaveServiceId> serviceIdsToBoot = new Vector<WaveServiceId> ();
        int i = 0;
        int numberOfServices = 0;

        m_currentFrameworkSequenceGenerator.getBootSequenceDuringPrePhase (serviceIdsToBoot);
        numberOfServices = serviceIdsToBoot.size ();

        for (i = 0; i < numberOfServices; i++)
        {
            if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
            {
                if (true != (FrameworkToolKit.isALocalService (serviceIdsToBoot.get (i))))
                {
                    continue;
                }
            }

            if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToBoot.get (i))))
            {
                continue;
            }

            final WaveBootObjectManagerMessage waveBootObjectManagerMessage = new WaveBootObjectManagerMessage (serviceIdsToBoot.get (i), getReason ());

            final WaveMessageStatus status = sendSynchronously (waveBootObjectManagerMessage, FrameworkToolKit.getThisLocationId ());

            if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
            {
                fatalTracePrintf ("WaveBootAgent.bootWaveServicesDuringPrePhaseStep : Could not send a message to Boot a service : %s, Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToBoot.get (i)), FrameworkToolKit.localize (status));

                return (ResourceId.WAVE_MESSAGE_ERROR);
            }

            final ResourceId completionStatus = waveBootObjectManagerMessage.getCompletionStatus ();

            if (ResourceId.WAVE_MESSAGE_SUCCESS != completionStatus)
            {
                fatalTracePrintf ("WaveBootAgent.bootWaveServicesDuringPrePhaseStep : Could not Boot a service : %s, Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToBoot.get (i)), FrameworkToolKit.localize (completionStatus));

                return (completionStatus);
            }
            else
            {
                infoTracePrintf ("Booted " + (FrameworkToolKit.getServiceNameById (serviceIdsToBoot.get (i))));
            }
        }
        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId initializeLocalWaveServicesStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.initializeLocalWaveServicesStep : Entering ...");

        final Vector<WaveServiceId> serviceIdsToInitialize = new Vector<WaveServiceId> ();
        int i = 0;
        int numberOfServices = 0;

        m_currentFrameworkSequenceGenerator.getInitializeSequence (serviceIdsToInitialize);

        numberOfServices = serviceIdsToInitialize.size ();

        for (i = 0; i < numberOfServices; i++)
        {
            if (true == (isToBeExcludedFromInitializePhase (serviceIdsToInitialize.get (i))))
            {
                continue;
            }

            if (true == (isToBeExcludedFromCurrentBootPhase (serviceIdsToInitialize.get (i))))
            {
                continue;
            }

            if (true == (FrameworkToolKit.isALocalService (serviceIdsToInitialize.get (i))))
            {
                final WaveInitializeObjectManagerMessage waveInitializeObjectManagerMessage = new WaveInitializeObjectManagerMessage (serviceIdsToInitialize.get (i), getReason ());

                final WaveMessageStatus status = sendSynchronously (waveInitializeObjectManagerMessage, FrameworkToolKit.getThisLocationId ());

                if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
                {
                    fatalTracePrintf ("WaveBootAgent.initializeLocalWaveServicesStep : Could not send a message to Initialize a service : %s,  Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToInitialize.get (i)), FrameworkToolKit.localize (status));

                    return (status.getResourceId ());
                }

                final ResourceId completionStatus = waveInitializeObjectManagerMessage.getCompletionStatus ();

                if (ResourceId.WAVE_MESSAGE_SUCCESS != completionStatus)
                {
                    fatalTracePrintf ("WaveBootAgent.initializeLocalWaveServicesStep : Could not Initialize a service : %s,  Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToInitialize.get (i)), FrameworkToolKit.localize (completionStatus));

                    return (completionStatus);
                }
                else
                {
                    infoTracePrintf ("Initialized %s", (FrameworkToolKit.getServiceNameById (serviceIdsToInitialize.get (i))));
                }
            }
        }

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId enableLocalWaveServicesStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.enableLocalWaveServicesStep : Entering ...");

        final Vector<WaveServiceId> serviceIdsToEnable = new Vector<WaveServiceId> ();
        int i = 0;
        int numberOfServices = 0;

        m_currentFrameworkSequenceGenerator.getEnableSequence (serviceIdsToEnable);

        numberOfServices = serviceIdsToEnable.size ();

        for (i = 0; i < numberOfServices; i++)
        {
            if (true == (FrameworkToolKit.isALocalService (serviceIdsToEnable.get (i))))
            {
                if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
                {
                    if (true != (FrameworkToolKit.isALocalService (serviceIdsToEnable.get (i))))
                    {
                        continue;
                    }
                }

                if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToEnable.get (i))))
                {
                    continue;
                }

                final WaveEnableObjectManagerMessage waveEnableObjectManagerMessage = new WaveEnableObjectManagerMessage (serviceIdsToEnable.get (i), getReason ());

                final WaveMessageStatus status = sendSynchronously (waveEnableObjectManagerMessage, FrameworkToolKit.getThisLocationId ());

                if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
                {
                    fatalTracePrintf ("WaveBootAgent.enableLocalWaveServicesStep : Could not send a message to Enable a service : %s,  Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToEnable.get (i)), FrameworkToolKit.localize (status));

                    return (status.getResourceId ());
                }

                final ResourceId completionStatus = waveEnableObjectManagerMessage.getCompletionStatus ();

                if (ResourceId.WAVE_MESSAGE_SUCCESS != completionStatus)
                {
                    fatalTracePrintf ("WaveBootAgent.enableLocalWaveServicesStep : Could not Enable a service : %s,  Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToEnable.get (i)), FrameworkToolKit.localize (completionStatus));

                    return (completionStatus);
                }
                else
                {
                    infoTracePrintf ("Enabled %s", (FrameworkToolKit.getServiceNameById (serviceIdsToEnable.get (i))));
                }
            }
        }

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId listenForEventsLocalWaveServicesStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.listenForEventsLocalWaveServicesStep : Entering ...");

        final Vector<WaveServiceId> serviceIdsToEnable = new Vector<WaveServiceId> ();
        int i = 0;
        int numberOfServices = 0;

        m_currentFrameworkSequenceGenerator.getEnableSequence (serviceIdsToEnable);
        numberOfServices = serviceIdsToEnable.size ();

        for (i = 0; i < numberOfServices; i++)
        {
            if (true == (FrameworkToolKit.isALocalService (serviceIdsToEnable.get (i))))
            {
                if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
                {
                    if (true != (FrameworkToolKit.isALocalService (serviceIdsToEnable.get (i))))
                    {
                        continue;
                    }
                }

                if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToEnable.get (i))))
                {
                    continue;
                }

                final WaveListenForEventsObjectManagerMessage waveListenForEventsObjectManagerMessage = new WaveListenForEventsObjectManagerMessage (serviceIdsToEnable.get (i), getReason ());

                final WaveMessageStatus status = sendSynchronously (waveListenForEventsObjectManagerMessage, FrameworkToolKit.getThisLocationId ());

                if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
                {
                    fatalTracePrintf ("WaveBootAgent.listenForEventsLocalWaveServicesStep : Could not send a message to Listen For Events from a service : %s,  Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToEnable.get (i)), FrameworkToolKit.localize (status));

                    return (status.getResourceId ());
                }

                final ResourceId completionStatus = waveListenForEventsObjectManagerMessage.getCompletionStatus ();

                if (ResourceId.WAVE_MESSAGE_SUCCESS != completionStatus)
                {
                    fatalTracePrintf ("WaveBootAgent.listenForEventsLocalWaveServicesStep : Could not Listen For Events from a service : %s,  Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToEnable.get (i)), FrameworkToolKit.localize (completionStatus));

                    return (completionStatus);
                }
                else
                {
                    infoTracePrintf ("Listen For Events %s", (FrameworkToolKit.getServiceNameById (serviceIdsToEnable.get (i))));
                }
            }
        }

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId installLocalWaveServicesStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.installLocalWaveServicesStep : Entering ...");

        final Vector<WaveServiceId> serviceIdsToInstall = new Vector<WaveServiceId> ();
        int i = 0;
        int numberOfServices = 0;

        m_currentFrameworkSequenceGenerator.getInstallSequence (serviceIdsToInstall);

        numberOfServices = serviceIdsToInstall.size ();

        for (i = 0; i < numberOfServices; i++)
        {
            if (true == (FrameworkToolKit.isALocalService (serviceIdsToInstall.get (i))))
            {
                if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
                {
                    if (true != (FrameworkToolKit.isALocalService (serviceIdsToInstall.get (i))))
                    {
                        continue;
                    }
                }

                if (true == (isToBeExcludedFromInstall (serviceIdsToInstall.get (i))))
                {
                    continue;
                }

                if (true == (isToBeExcludedFromCurrentBootPhase (serviceIdsToInstall.get (i))))
                {
                    continue;
                }

                final WaveInstallObjectManagerMessage waveInstallObjectManagerMessage = new WaveInstallObjectManagerMessage (serviceIdsToInstall.get (i), getReason ());

                final WaveMessageStatus status = sendSynchronously (waveInstallObjectManagerMessage, FrameworkToolKit.getThisLocationId ());

                if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
                {
                    fatalTracePrintf ("WaveBootAgent.installLocalWaveServicesStep : Could not send a message to Install a service : %s,  Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToInstall.get (i)), FrameworkToolKit.localize (status));

                    return (status.getResourceId ());
                }

                final ResourceId completionStatus = waveInstallObjectManagerMessage.getCompletionStatus ();

                if (ResourceId.WAVE_MESSAGE_SUCCESS != completionStatus)
                {
                    fatalTracePrintf ("WaveBootAgent.installLocalWaveServicesStep : Could not Install a service : %s,  Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToInstall.get (i)), FrameworkToolKit.localize (completionStatus));

                    return (completionStatus);
                }
                else
                {
                    infoTracePrintf ("Installed %s", (FrameworkToolKit.getServiceNameById (serviceIdsToInstall.get (i))));
                }
            }
        }

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId bootLocalWaveServicesStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.bootLocalWaveServicesStep : Entering ...");

        final Vector<WaveServiceId> serviceIdsToBoot = new Vector<WaveServiceId> ();
        int i = 0;
        int numberOfServices = 0;

        m_currentFrameworkSequenceGenerator.getBootSequence (serviceIdsToBoot);

        numberOfServices = serviceIdsToBoot.size ();

        for (i = 0; i < numberOfServices; i++)
        {
            if (true == (FrameworkToolKit.isALocalService (serviceIdsToBoot.get (i))))
            {
                if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
                {
                    if (true != (FrameworkToolKit.isALocalService (serviceIdsToBoot.get (i))))
                    {
                        continue;
                    }
                }

                if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToBoot.get (i))))
                {
                    continue;
                }

                final WaveBootObjectManagerMessage waveBootObjectManagerMessage = new WaveBootObjectManagerMessage (serviceIdsToBoot.get (i), getReason ());

                final WaveMessageStatus status = sendSynchronously (waveBootObjectManagerMessage, FrameworkToolKit.getThisLocationId ());

                if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
                {
                    fatalTracePrintf ("WaveBootAgent.bootLocalWaveServicesStep : Could not send a message to Boot a service : %s,  Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToBoot.get (i)), FrameworkToolKit.localize (status));

                    return (status.getResourceId ());
                }

                final ResourceId completionStatus = waveBootObjectManagerMessage.getCompletionStatus ();

                if (ResourceId.WAVE_MESSAGE_SUCCESS != completionStatus)
                {
                    fatalTracePrintf ("WaveBootAgent.bootLocalWaveServicesStep : Could not Boot a service : %s,  Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToBoot.get (i)), FrameworkToolKit.localize (completionStatus));

                    return (completionStatus);
                }
                else
                {
                    infoTracePrintf ("Booted %s", (FrameworkToolKit.getServiceNameById (serviceIdsToBoot.get (i))));
                }
            }
        }

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId initializeGlobalWaveServicesStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.initializeGlobalWaveServicesStep : Entering ...");

        final Vector<WaveServiceId> serviceIdsToInitialize = new Vector<WaveServiceId> ();
        int i = 0;
        int numberOfServices = 0;

        m_currentFrameworkSequenceGenerator.getInitializeSequence (serviceIdsToInitialize);

        numberOfServices = serviceIdsToInitialize.size ();

        for (i = 0; i < numberOfServices; i++)
        {
            if (true == (isToBeExcludedFromInitializePhase (serviceIdsToInitialize.get (i))))
            {
                continue;
            }

            if (false == (FrameworkToolKit.isALocalService (serviceIdsToInitialize.get (i))))
            {
                final WaveInitializeObjectManagerMessage waveInitializeObjectManagerMessage = new WaveInitializeObjectManagerMessage (serviceIdsToInitialize.get (i), getReason ());

                final WaveMessageStatus status = sendSynchronously (waveInitializeObjectManagerMessage, FrameworkToolKit.getThisLocationId ());

                if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
                {
                    fatalTracePrintf ("WaveBootAgent.bootLocalWaveServicesStep : Could not send a message to Initialize a service : %s,  Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToInitialize.get (i)), FrameworkToolKit.localize (status));

                    return (status.getResourceId ());
                }

                final ResourceId completionStatus = waveInitializeObjectManagerMessage.getCompletionStatus ();

                if (ResourceId.WAVE_MESSAGE_SUCCESS != completionStatus)
                {
                    fatalTracePrintf ("WaveBootAgent.bootLocalWaveServicesStep : Could not Initialize a service : %s,  Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToInitialize.get (i)), FrameworkToolKit.localize (completionStatus));

                    return (completionStatus);
                }
                else
                {
                    infoTracePrintf ("Initialized %s", (FrameworkToolKit.getServiceNameById (serviceIdsToInitialize.get (i))));
                }
            }
        }

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId enableGlobalWaveServicesStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.enableGlobalWaveServicesStep : Entering ...");

        final Vector<WaveServiceId> serviceIdsToEnable = new Vector<WaveServiceId> ();
        int i = 0;
        int numberOfServices = 0;

        m_currentFrameworkSequenceGenerator.getEnableSequence (serviceIdsToEnable);

        numberOfServices = serviceIdsToEnable.size ();

        for (i = 0; i < numberOfServices; i++)
        {
            if (false == (FrameworkToolKit.isALocalService (serviceIdsToEnable.get (i))))
            {
                if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
                {
                    if (true != (FrameworkToolKit.isALocalService (serviceIdsToEnable.get (i))))
                    {
                        continue;
                    }
                }

                if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToEnable.get (i))))
                {
                    continue;
                }

                final WaveEnableObjectManagerMessage waveEnableObjectManagerMessage = new WaveEnableObjectManagerMessage (serviceIdsToEnable.get (i), getReason ());

                final WaveMessageStatus status = sendSynchronously (waveEnableObjectManagerMessage, FrameworkToolKit.getThisLocationId ());

                if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
                {
                    fatalTracePrintf ("WaveBootAgent.enableGlobalWaveServicesStep : Could not send a message to Enable a service : %s,  Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToEnable.get (i)), FrameworkToolKit.localize (status));
                    return (status.getResourceId ());
                }

                final ResourceId completionStatus = waveEnableObjectManagerMessage.getCompletionStatus ();

                if (ResourceId.WAVE_MESSAGE_SUCCESS != completionStatus)
                {
                    fatalTracePrintf ("WaveBootAgent.enableGlobalWaveServicesStep : Could not Enable a service : %s,  Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToEnable.get (i)), FrameworkToolKit.localize (completionStatus));

                    return (completionStatus);
                }
                else
                {
                    infoTracePrintf ("Enabled %s", FrameworkToolKit.getServiceNameById (serviceIdsToEnable.get (i)));
                }
            }
        }

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId listenForEventsGlobalWaveServicesStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.listenForEventsGlobalWaveServicesStep : Entering ...");

        final Vector<WaveServiceId> serviceIdsToEnable = new Vector<WaveServiceId> ();
        int i = 0;
        int numberOfServices = 0;

        m_currentFrameworkSequenceGenerator.getEnableSequence (serviceIdsToEnable);

        numberOfServices = serviceIdsToEnable.size ();

        for (i = 0; i < numberOfServices; i++)
        {
            if (false == (FrameworkToolKit.isALocalService (serviceIdsToEnable.get (i))))
            {
                if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
                {
                    if (true != (FrameworkToolKit.isALocalService (serviceIdsToEnable.get (i))))
                    {
                        continue;
                    }
                }

                if (true == (isToBeExcludedForEnableAndBoot (serviceIdsToEnable.get (i))))
                {
                    continue;
                }

                final WaveListenForEventsObjectManagerMessage waveListenForEventsObjectManagerMessage = new WaveListenForEventsObjectManagerMessage (serviceIdsToEnable.get (i), getReason ());

                final WaveMessageStatus status = sendSynchronously (waveListenForEventsObjectManagerMessage, FrameworkToolKit.getThisLocationId ());

                if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
                {
                    fatalTracePrintf ("WaveBootAgent.listenForEventsGlobalWaveServicesStep : Could not send a message to Listen For Events From a service : %s,  Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToEnable.get (i)), FrameworkToolKit.localize (status));
                    return (status.getResourceId ());
                }

                final ResourceId completionStatus = waveListenForEventsObjectManagerMessage.getCompletionStatus ();

                if (ResourceId.WAVE_MESSAGE_SUCCESS != completionStatus)
                {
                    fatalTracePrintf ("WaveBootAgent.listenForEventsGlobalWaveServicesStep : Could not Listen For Events from a service : %s,  Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToEnable.get (i)), FrameworkToolKit.localize (completionStatus));

                    return (completionStatus);
                }
                else
                {
                    infoTracePrintf ("Listen For Events %s", FrameworkToolKit.getServiceNameById (serviceIdsToEnable.get (i)));
                }
            }
        }
        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId installGlobalWaveServicesStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.installGlobalWaveServicesStep : Entering ...");

        final Vector<WaveServiceId> serviceIdsToInstall = new Vector<WaveServiceId> ();
        int i = 0;
        int numberOfServices = 0;

        m_currentFrameworkSequenceGenerator.getInstallSequence (serviceIdsToInstall);

        numberOfServices = serviceIdsToInstall.size ();

        for (i = 0; i < numberOfServices; i++)
        {
            if (false == (FrameworkToolKit.isALocalService (serviceIdsToInstall.get (i))))
            {
                if ((true == (isAPersistentBoot ())) && (true != (willBeAPrimaryLocation ())))
                {
                    if (true != (FrameworkToolKit.isALocalService (serviceIdsToInstall.get (i))))
                    {
                        continue;
                    }
                }

                if (true == (isToBeExcludedFromInstall (serviceIdsToInstall.get (i))))
                {
                    continue;
                }

                final WaveInstallObjectManagerMessage waveInstallObjectManagerMessage = new WaveInstallObjectManagerMessage (serviceIdsToInstall.get (i), getReason ());

                final WaveMessageStatus status = sendSynchronously (waveInstallObjectManagerMessage, FrameworkToolKit.getThisLocationId ());

                if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
                {
                    fatalTracePrintf ("WaveBootAgent.installGlobalWaveServicesStep : Could not send a message to Install a service : %s,  Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToInstall.get (i)), FrameworkToolKit.localize (status));
                    return (status.getResourceId ());
                }

                final ResourceId completionStatus = waveInstallObjectManagerMessage.getCompletionStatus ();

                if (ResourceId.WAVE_MESSAGE_SUCCESS != completionStatus)
                {
                    fatalTracePrintf ("WaveBootAgent.installGlobalWaveServicesStep : Could not Install a service : %s,  Status : %s", FrameworkToolKit.getServiceNameById (serviceIdsToInstall.get (i)), FrameworkToolKit.localize (completionStatus));

                    return (completionStatus);
                }
                else
                {
                    infoTracePrintf ("Installed %s", FrameworkToolKit.getServiceNameById (serviceIdsToInstall.get (i)));
                }
            }
        }

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId bootGlobalWaveServicesStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveBootAgent.bootGlobalWaveServicesStep : Entering ...");

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private WaveBootReason getReason ()
    {
        return (WaveBootReason.WAVE_BOOT_FIRST_TIME_BOOT);
    }

    private boolean isToBeExcludedFromInitializeDuringPrePhase (final WaveServiceId waveServiceId)
    {
        return (false);
    }

    private boolean isAPersistentBoot ()
    {
        return false;
    }

    private boolean willBeAPrimaryLocation ()
    {
        return ((FrameworkToolKit.isStandAloneLocation ()) || (FrameworkToolKit.isPrimaryLocation ()));
    }

    private boolean isToBeExcludedForEnableAndBoot (final WaveServiceId waveServiceId)
    {
        return (false);
    }

    private boolean isToBeExcludedFromInstallDuringPrePhase (final WaveServiceId waveServiceId)
    {
        return false;
    }

    private boolean isToBeExcludedFromInitializePhase (final WaveServiceId waveServiceId)
    {
        return (false);

    }

    private boolean isToBeExcludedFromCurrentBootPhase (final WaveServiceId waveServiceId)
    {
        return (false);

    }

    private boolean isToBeExcludedFromInstall (final WaveServiceId waveServiceId)
    {
        return false;
    }
}
