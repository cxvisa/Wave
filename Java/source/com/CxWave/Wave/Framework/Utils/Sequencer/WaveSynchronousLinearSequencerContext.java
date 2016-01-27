/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Sequencer;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Vector;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ObjectModel.WaveElement;
import com.CxWave.Wave.Framework.ObjectModel.WaveManagedObject;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Context.WaveAsynchronousContext;
import com.CxWave.Wave.Framework.Utils.Source.WaveJavaSourceRepository;
import com.CxWave.Wave.Framework.Utils.Time.StopWatch;
import com.CxWave.Wave.Framework.Utils.Time.ThreadStopWatch;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;

public class WaveSynchronousLinearSequencerContext
{
    WaveMessage                             m_waveMessage                 = null;
    WaveAsynchronousContext                 m_waveAsynchronousContext     = null;
    private WaveElement                     m_waveElement                 = null;
    private String[]                        m_steps                       = null;
    private int                             m_numberOfSteps               = 0;
    private int                             m_currentStep                 = 0;
    private ResourceId                      m_completionStatus            = ResourceId.WAVE_MESSAGE_ERROR;
    private boolean                         m_isTransactionStartedByMe    = false;

    private final Vector<WaveManagedObject> m_queryResults                = new Vector<WaveManagedObject> ();

    boolean                                 m_isADelayedCommitTransaction = false;

    private final StopWatch                 m_wallClockTimeStopWatch      = new StopWatch ();
    private final ThreadStopWatch           m_threadTimeStopWatch         = new ThreadStopWatch ();

    private final UI32                      m_operationCode               = new UI32 (0);

    private final Vector<Method>            m_methodsForSteps             = new Vector<Method> ();

    public WaveSynchronousLinearSequencerContext (final WaveMessage waveMessage, final WaveElement waveElement, final String[] steps)
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

    public WaveSynchronousLinearSequencerContext (final WaveAsynchronousContext waveAsynchronousContext, final WaveElement waveElement, final String[] steps)
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

    private boolean validateAndCompute ()
    {
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
            WaveTraceUtils.fatalTracePrintf ("WaveSynchronousLinearSequencerContext.validateAndCompute :  There should be atleast three steps to run a Wave Linear Sequencer. %s Steps were specified.", m_numberOfSteps);

            return (false);
        }

        final Class<?> waveElementClass = m_waveElement.getClass ();

        WaveAssertUtils.waveAssert (null != waveElementClass);

        for (final String methodNameForStep : m_steps)
        {
            WaveTraceUtils.infoTracePrintf ("WaveSynchronousLinearSequencerContext.validateAndCompute : Searching for method name : %s", methodNameForStep);

            final Class<?> classToSearchForTheMethod = waveElementClass;
            Method methodForStep = null;

            methodForStep = WaveJavaSourceRepository.getMethodForWaveSynchronousLinearSequencerStepInWaveJavaClass (classToSearchForTheMethod.getTypeName (), methodNameForStep);

            if (null != methodForStep)
            {
                m_methodsForSteps.add (methodForStep);
            }
            else
            {
                WaveTraceUtils.fatalTracePrintf ("WaveSynchronousLinearSequencerContext.validateAndCompute : Could not obtain the Step method %s on class %s", methodNameForStep, waveElementClass.getName ());
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

    public ResourceId getCompletionStatus ()
    {
        return (m_completionStatus);
    }

    public ResourceId executeCurrentStep ()
    {
        if (m_currentStep < (m_numberOfSteps - 2))
        {
            if (null != m_waveMessage)
            {
                m_operationCode.setValue (m_waveMessage.getOperationCode ());
            }

            m_wallClockTimeStopWatch.start ();
            m_threadTimeStopWatch.start ();
        }

        final Method methodForCurrentStep = m_methodsForSteps.get (m_currentStep);

        WaveAssertUtils.waveAssert (null != methodForCurrentStep);

        WaveAssertUtils.waveAssert (null != m_waveElement);

        Object returnValueObject = null;

        try
        {
            returnValueObject = methodForCurrentStep.invoke (m_waveElement, this);
        }
        catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException e)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveSynchronousLinearSequencerContext.executeCurrentStep : Failed to invoke method : %s, Details : %s", methodForCurrentStep.getName (), e.toString ());
        }

        final ResourceId status = (ResourceId) returnValueObject;

        WaveAssertUtils.waveAssert (null != status);

        if (m_currentStep < (m_numberOfSteps - 2))
        {
            m_wallClockTimeStopWatch.stop ();
            m_threadTimeStopWatch.stop ();

            m_waveElement.updateTimeConsumedInThisThread (m_operationCode, m_currentStep, m_threadTimeStopWatch.getLastLapDuration ());
            m_waveElement.updateRealTimeConsumedInThisThread (m_operationCode, m_currentStep, m_wallClockTimeStopWatch.getLastLapDuration ());
        }

        return (status);
    }

    public ResourceId execute ()
    {
        int i;
        final int effectiveNumberOfSteps = m_numberOfSteps - 2;

        m_completionStatus = ResourceId.WAVE_MESSAGE_ERROR;

        for (i = 0; i < effectiveNumberOfSteps; i++)
        {
            m_completionStatus = executeCurrentStep ();

            if (!(ResourceId.WAVE_MESSAGE_SUCCESS.equals (m_completionStatus)))
            {
                if (ResourceId.WAVE_SEQUENCER_SKIP_TO_SUCCESS_STEP.equals (m_completionStatus))
                {
                    // Move step pointer to the success step
                    m_currentStep = effectiveNumberOfSteps;
                    m_completionStatus = ResourceId.WAVE_MESSAGE_SUCCESS;
                }

                break;
            }
            else
            {
                advanceCurrentStep ();
            }
        }

        if (!(ResourceId.WAVE_MESSAGE_SUCCESS.equals (m_completionStatus)))
        {
            m_currentStep = m_numberOfSteps - 1;
        }

        return (executeCurrentStep ());
    }

    public WaveMessage getWaveMessage ()
    {
        return m_waveMessage;
    }

    public void setWaveMessage (final WaveMessage waveMessage)
    {
        m_waveMessage = waveMessage;
    }

    public WaveAsynchronousContext getWaveAsynchronousContext ()
    {
        return m_waveAsynchronousContext;
    }

    public void setWaveAsynchronousContext (final WaveAsynchronousContext waveAsynchronousContext)
    {
        m_waveAsynchronousContext = waveAsynchronousContext;
    }

    public boolean getIsADelayedCommitTransaction ()
    {
        return m_isADelayedCommitTransaction;
    }

    public void setIsADelayedCommitTransaction (final boolean isADelayedCommitTransaction)
    {
        m_isADelayedCommitTransaction = isADelayedCommitTransaction;
    }

    public boolean getIsTransactionStartedByMe ()
    {
        return m_isTransactionStartedByMe;
    }

    public void setIsTransactionStartedByMe (final boolean isTransactionStartedByMe)
    {
        m_isTransactionStartedByMe = isTransactionStartedByMe;
    }
}
