/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Workers;

import com.CxWave.Wave.Framework.Boot.FirstTimeWaveBootAgent;
import com.CxWave.Wave.Framework.Boot.HaStandbyWaveBootAgent;
import com.CxWave.Wave.Framework.Boot.PersistentWaveBootAgent;
import com.CxWave.Wave.Framework.Boot.PersistentWithDefaultForHABootAgent;
import com.CxWave.Wave.Framework.Boot.PersistentWithDefaultWaveBootAgent;
import com.CxWave.Wave.Framework.Boot.RecoverWaveBootAgent;
import com.CxWave.Wave.Framework.Boot.SecondaryNodeConfigureWaveBootAgent;
import com.CxWave.Wave.Framework.Boot.SecondaryNodeRejoinWaveBootAgent;
import com.CxWave.Wave.Framework.Boot.SecondaryNodeUnconfigureWaveBootAgent;
import com.CxWave.Wave.Framework.Boot.WaveBootAgent;
import com.CxWave.Wave.Framework.Boot.WaveBootPhase;
import com.CxWave.Wave.Framework.Core.WaveBootMode;
import com.CxWave.Wave.Framework.Core.WaveFrameworkObjectManager;
import com.CxWave.Wave.Framework.Core.Contexts.WaveFrameworkInitializeWorkerStartServicesContext;
import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorkerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.Cardinality;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.OwnerOM;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.WorkerPriority;
import com.CxWave.Wave.Framework.Shutdown.WaveShutdownAgent;
import com.CxWave.Wave.Framework.Utils.Context.WaveAsynchronousContext;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;

@OwnerOM (om = WaveFrameworkObjectManager.class)
@Cardinality (1)
@WorkerPriority (WaveWorkerPriority.WAVE_WORKER_PRIORITY_0)
public class WaveFrameworkObjectManagerInitializeWorker extends WaveWorker
{
    private WaveBootAgent m_waveBootAgent = null;

    public WaveFrameworkObjectManagerInitializeWorker (final WaveObjectManager waveObjectManager)
    {
        super (waveObjectManager);
    }

    public void startWaveServices ()
    {
        startWaveServices (WaveBootMode.WAVE_BOOT_UNKNOWN, WaveBootPhase.WAVE_BOOT_PHASE_ALL_PHASES);
    }

    public void startWaveServices (final WaveBootMode waveBootMode, final WaveBootPhase waveBootPhase)
    {
        infoTracePrintf ("WaveFrameworkObjectManagerInitializeWorker.startWaveServices : Entering ...");

        final String[] sequencerSteps =
            {
                            "determineNodeBootModeStep",
                            "chooseABootAgentStep",
                            "runTheBootAgentStep",
                            "saveConfigurationStep",
                            "informServicesToInitializeBeforeBootComplete",
                            "declareBootCompleteStep",
                            "waveSynchronousLinearSequencerSucceededStep",
                            "waveSynchronousLinearSequencerFailedStep"
            };

        final WaveFrameworkInitializeWorkerStartServicesContext waveFrameworkInitializeWorkerStartServicesContext = new WaveFrameworkInitializeWorkerStartServicesContext ((WaveAsynchronousContext) null, this, sequencerSteps);

        waveFrameworkInitializeWorkerStartServicesContext.setWaveBootMode (waveBootMode);
        waveFrameworkInitializeWorkerStartServicesContext.setWaveBootPhase (waveBootPhase);

        waveFrameworkInitializeWorkerStartServicesContext.execute ();
    }

    private ResourceId determineNodeBootModeStep (final WaveFrameworkInitializeWorkerStartServicesContext waveFrameworkInitializeWorkerStartServicesContext)
    {
        infoTracePrintf ("WaveFrameworkObjectManagerInitializeWorker.determineNodeBootModeStep : Entering ...");

        WaveBootMode waveBootMode = waveFrameworkInitializeWorkerStartServicesContext.getWaveBootMode ();

        if (WaveBootMode.WAVE_BOOT_UNKNOWN != waveBootMode)
        {
            return (ResourceId.WAVE_MESSAGE_SUCCESS);
        }

        waveBootMode = WaveBootMode.WAVE_BOOT_FIRST_TIME;

        waveFrameworkInitializeWorkerStartServicesContext.setWaveBootMode (waveBootMode);

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId chooseABootAgentStep (final WaveFrameworkInitializeWorkerStartServicesContext waveFrameworkInitializeWorkerStartServicesContext)
    {
        infoTracePrintf ("WaveFrameworkObjectManagerInitializeWorker.chooseABootAgentStep : Entering ...");

        final WaveBootMode waveBootMode = waveFrameworkInitializeWorkerStartServicesContext.getWaveBootMode ();

        infoTracePrintf ("Boot Mode is %s", waveBootMode.toString ());

        if (WaveBootMode.WAVE_BOOT_FIRST_TIME == waveBootMode)
        {
            m_waveBootAgent = new FirstTimeWaveBootAgent (m_waveObjectManager);
        }
        else if (WaveBootMode.WAVE_BOOT_PERSISTENT == waveBootMode)
        {
            m_waveBootAgent = new PersistentWaveBootAgent (m_waveObjectManager);
        }
        else if (WaveBootMode.WAVE_BOOT_PERSISTENT_WITH_DEFAULT == waveBootMode)
        {
            m_waveBootAgent = new PersistentWithDefaultWaveBootAgent (m_waveObjectManager);
        }
        else if (WaveBootMode.WAVE_BOOT_SECONDARY_CONFIGURE == waveBootMode)
        {
            m_waveBootAgent = new SecondaryNodeConfigureWaveBootAgent (m_waveObjectManager);
        }
        else if (WaveBootMode.WAVE_BOOT_SECONDARY_UNCONFIGURE == waveBootMode)
        {
            m_waveBootAgent = new SecondaryNodeUnconfigureWaveBootAgent (m_waveObjectManager);
        }
        else if (WaveBootMode.WAVE_BOOT_SECONDARY_REJOIN == waveBootMode)
        {
            m_waveBootAgent = new SecondaryNodeRejoinWaveBootAgent (m_waveObjectManager);
        }
        else if (WaveBootMode.WAVE_BOOT_HASTANDBY == waveBootMode)
        {
            m_waveBootAgent = new HaStandbyWaveBootAgent (m_waveObjectManager);
        }
        else if (WaveBootMode.WAVE_BOOT_PREPARE_FOR_HA_BOOT == waveBootMode)
        {
            m_waveBootAgent = new PersistentWithDefaultForHABootAgent (m_waveObjectManager);
        }
        else
        {
            fatalTracePrintf ("WaveFrameworkObjectManagerInitializeWorker::chooseABootAgentStep : Unknown Wave Boot Mode : %d", waveBootMode.ordinal ());
            waveAssert ();
        }

        waveAssert (null != m_waveBootAgent);

        if (null == m_waveBootAgent)
        {
            return (ResourceId.WAVE_MESSAGE_ERROR);
        }

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId runTheBootAgentStep (final WaveFrameworkInitializeWorkerStartServicesContext waveFrameworkInitializeWorkerStartServicesContext)
    {
        infoTracePrintf ("WaveFrameworkObjectManagerInitializeWorker.runTheBootAgentStep : Entering ...");

        ResourceId status = m_waveBootAgent.execute (waveFrameworkInitializeWorkerStartServicesContext.getWaveBootPhase ());

        if (ResourceId.WAVE_MESSAGE_ERROR_DATABASE_INCONSISTENT == status)
        {
            final WaveShutdownAgent shutdownAgent = new WaveShutdownAgent (m_waveObjectManager);

            status = shutdownAgent.execute ();

            if (status != ResourceId.WAVE_MESSAGE_SUCCESS)
            {
                fatalTracePrintf ("WaveFrameworkObjectManagerInitializeWorker::runTheBootAgentStep: Shutting down all services failed.\n");

                return status;
            }
            else
            {
                infoTracePrintf ("WaveFrameworkObjectManagerInitializeWorker::runTheBootAgentStep : Recovering now with Boot Mode %s", WaveBootMode.WAVE_BOOT_FIRST_TIME.toString ());

                m_waveBootAgent = new RecoverWaveBootAgent (m_waveObjectManager);

                status = m_waveBootAgent.execute (WaveBootPhase.WAVE_BOOT_PHASE_PRE_PHASE);

                if (status != ResourceId.WAVE_MESSAGE_SUCCESS)
                {
                    fatalTracePrintf ("WaveFrameworkObjectManagerInitializeWorker::runTheBootAgentStep: Shutting down all services failed.\n");

                    return status;
                }
                else
                {
                    m_waveBootAgent = new RecoverWaveBootAgent (m_waveObjectManager);

                    return (m_waveBootAgent.execute (WaveBootPhase.WAVE_BOOT_PHASE_POST_PHASE));
                }
            }
        }
        else
        {
            return status;
        }
    }

    private ResourceId saveConfigurationStep (final WaveFrameworkInitializeWorkerStartServicesContext waveFrameworkInitializeWorkerStartServicesContext)
    {
        infoTracePrintf ("WaveFrameworkObjectManagerInitializeWorker.saveConfigurationStep : Entering ...");

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId informServicesToInitializeBeforeBootComplete (final WaveFrameworkInitializeWorkerStartServicesContext waveFrameworkInitializeWorkerStartServicesContext)
    {
        infoTracePrintf ("WaveFrameworkObjectManagerInitializeWorker.informServicesToInitializeBeforeBootComplete : Entering ...");

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private ResourceId declareBootCompleteStep (final WaveFrameworkInitializeWorkerStartServicesContext waveFrameworkInitializeWorkerStartServicesContext)
    {
        infoTracePrintf ("WaveFrameworkObjectManagerInitializeWorker.declareBootCompleteStep : Entering ...");

        return (ResourceId.WAVE_MESSAGE_SUCCESS);
    }
}
