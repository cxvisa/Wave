/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Regression.Contexts;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ObjectModel.WaveElement;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Context.WaveAsynchronousContext;
import com.CxWave.Wave.Framework.Utils.Sequencer.WaveLinearSequencerContext;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;

public class RegressionTestObjectManagerRunTestForAServiceLinearSequencerContext extends WaveLinearSequencerContext
{
    private final WaveServiceId m_testServiceId                  = null;
    ResourceId                  m_testServiceRunCompletionStatus = ResourceId.WAVE_MESSAGE_ERROR;

    public RegressionTestObjectManagerRunTestForAServiceLinearSequencerContext (final WaveMessage waveMessage, final WaveElement waveElement, final String[] steps)
    {
        super (waveMessage, waveElement, steps);
    }

    public RegressionTestObjectManagerRunTestForAServiceLinearSequencerContext (final WaveAsynchronousContext waveAsynchronousContext, final WaveElement waveElement, final String[] steps)
    {
        super (waveAsynchronousContext, waveElement, steps);
    }

    public ResourceId getTestServiceRunCompletionStatus ()
    {
        return m_testServiceRunCompletionStatus;
    }

    public void setTestServiceRunCompletionStatus (final ResourceId testServiceRunCompletionStatus)
    {
        m_testServiceRunCompletionStatus = testServiceRunCompletionStatus;
    }

    public WaveServiceId getTestServiceId ()
    {
        return m_testServiceId;
    }
}
