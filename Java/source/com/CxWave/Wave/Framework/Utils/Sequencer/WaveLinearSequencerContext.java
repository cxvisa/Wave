/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Sequencer;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ObjectModel.WaveElement;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Context.WaveAsynchronousContext;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;

public class WaveLinearSequencerContext
{
    private WaveMessage                   m_waveMessage                                = null;
    private final WaveAsynchronousContext m_waveAsynchronousContext                    = null;
    private WaveElement                   m_waveElement                                = null;
    private String[]                      m_steps                                      = null;
    private int                           m_numberOfSteps                              = 0;
    private final int                     m_currentStep                                = 0;
    private final int                     m_numberOfCallbacksBeforeAdvancingToNextStep = 0;
    private final ResourceId              m_completionStatus                           = ResourceId.WAVE_MESSAGE_ERROR;
    private final boolean                 m_isHoldAllRequested                         = false;
    private final boolean                 m_isTransactionStartedByMe                   = false;

    public WaveLinearSequencerContext (final WaveMessage waveMessage, final WaveElement waveElement, final String[] steps)
    {
        m_waveMessage = waveMessage;
        m_waveElement = waveElement;
        m_steps = steps;
        m_numberOfSteps = steps.length;

        final boolean isValid = validateAndCompute ();

        if (!isValid)
        {
            WaveAssertUtils.waveAssert ();
        }
    }

    public WaveLinearSequencerContext (final WaveLinearSequencerContext waveLinearSequencerContext)
    {
        WaveTraceUtils.fatalTracePrintf ("WaveLinearSequencerContext.WaveLinearSequencerContext : Cannot copy construct a WaveLinearSequencerContext.");
        WaveAssertUtils.waveAssert ();
    }

    private boolean validateAndCompute ()
    {
        if ((null == m_waveMessage) && (null == m_waveAsynchronousContext))
        {
            return (false);
        }

        if (null == m_waveElement)
        {
            return (false);
        }

        if (null == m_steps)
        {
            return (false);
        }

        if (3 > m_numberOfSteps)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveLinearSequencerContext.validateAndCompute :  There should be atleast three steps to run a Wave Linear Sequencer. %s Steps were specified.", m_numberOfSteps);

            return (false);
        }

        return (true);
    }
}
