/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Contexts;

import com.CxWave.Wave.Framework.Boot.WaveBootAgent;
import com.CxWave.Wave.Framework.Boot.WaveBootPhase;
import com.CxWave.Wave.Framework.Core.WaveBootMode;
import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ObjectModel.WaveElement;
import com.CxWave.Wave.Framework.Utils.Context.WaveAsynchronousContext;
import com.CxWave.Wave.Framework.Utils.Sequencer.WaveSynchronousLinearSequencerContext;

public class WaveFrameworkInitializeWorkerStartServicesContext extends WaveSynchronousLinearSequencerContext
{
    private WaveBootMode  m_waveBootMode                 = WaveBootMode.WAVE_BOOT_FIRST_TIME;
    private WaveBootPhase m_waveBootPhase                = WaveBootPhase.WAVE_BOOT_PHASE_ALL_PHASES;
    private WaveBootAgent m_waveBootAgent                = null;
    private boolean       m_isSchemaChangedOnFwdl        = false;
    private boolean       m_isSchemaUpgradedSuccessfully = false;

    public WaveFrameworkInitializeWorkerStartServicesContext (final WaveMessage waveMessage, final WaveElement waveElement, final String[] steps)
    {
        super (waveMessage, waveElement, steps);
    }

    public WaveFrameworkInitializeWorkerStartServicesContext (final WaveAsynchronousContext waveAsynchronousContext, final WaveElement waveElement, final String[] steps)
    {
        super (waveAsynchronousContext, waveElement, steps);
    }

    public WaveBootMode getWaveBootMode ()
    {
        return m_waveBootMode;
    }

    public void setWaveBootMode (final WaveBootMode waveBootMode)
    {
        m_waveBootMode = waveBootMode;
    }

    public WaveBootPhase getWaveBootPhase ()
    {
        return m_waveBootPhase;
    }

    public void setWaveBootPhase (final WaveBootPhase waveBootPhase)
    {
        m_waveBootPhase = waveBootPhase;
    }

    public WaveBootAgent getWaveBootAgent ()
    {
        return m_waveBootAgent;
    }

    public void setWaveBootAgent (final WaveBootAgent waveBootAgent)
    {
        m_waveBootAgent = waveBootAgent;
    }

    public boolean getIsSchemaChangedOnFwdl ()
    {
        return m_isSchemaChangedOnFwdl;
    }

    public void setIsSchemaChangedOnFwdl (final boolean isSchemaChangedOnFwdl)
    {
        m_isSchemaChangedOnFwdl = isSchemaChangedOnFwdl;
    }

    public boolean getIsSchemaUpgradedSuccessfully ()
    {
        return m_isSchemaUpgradedSuccessfully;
    }

    public void setIsSchemaUpgradedSuccessfully (final boolean isSchemaUpgradedSuccessfully)
    {
        m_isSchemaUpgradedSuccessfully = isSchemaUpgradedSuccessfully;
    }

}
