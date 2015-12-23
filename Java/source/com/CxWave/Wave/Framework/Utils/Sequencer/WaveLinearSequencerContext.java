/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Sequencer;

import java.lang.reflect.Method;
import java.util.Vector;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ObjectModel.WaveElement;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Context.WaveAsynchronousContext;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;

public class WaveLinearSequencerContext
{
    private WaveMessage             m_waveMessage                                = null;
    private WaveAsynchronousContext m_waveAsynchronousContext                    = null;
    private WaveElement             m_waveElement                                = null;
    private String[]                m_steps                                      = null;
    private int                     m_numberOfSteps                              = 0;
    private int                     m_currentStep                                = 0;
    private final int               m_numberOfCallbacksBeforeAdvancingToNextStep = 0;
    private final ResourceId        m_completionStatus                           = ResourceId.WAVE_MESSAGE_ERROR;
    private final boolean           m_isHoldAllRequested                         = false;
    private final boolean           m_isTransactionStartedByMe                   = false;

    private final Vector<Method>    m_methodsForSteps                            = new Vector<Method> ();

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

    public WaveLinearSequencerContext (final WaveAsynchronousContext waveAsynchronousContext, final WaveElement waveElement, final String[] steps)
    {
        m_waveAsynchronousContext = waveAsynchronousContext;
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

        final Class<?> waveElementClass = m_waveElement.getClass ();

        WaveAssertUtils.waveAssert (null != waveElementClass);

        for (final String methodNameForStep : m_steps)
        {
            try
            {
                final Method methodForStep = waveElementClass.getDeclaredMethod (methodNameForStep, getClass ());

                methodForStep.setAccessible (true);

                m_methodsForSteps.add (methodForStep);
            }
            catch (NoSuchMethodException | SecurityException e)
            {
                WaveTraceUtils.fatalTracePrintf ("WaveLinearSequencerContext.validateAndCompute : Could not obtain the Step method %s on class %s, Details : %s", methodNameForStep, waveElementClass.getName (), e.toString ());
                WaveAssertUtils.waveAssert ();

                return (false);
            }
        }

        return (true);
    }

    private void advanceCurrentStep ()
    {
        m_currentStep++;
    }

    public void executeCurrentStep ()
    {

    }

    public ResourceId getCompletionStatus ()
    {
        return (m_completionStatus);
    }
}
