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
import com.CxWave.Wave.Framework.Utils.Time.StopWatch;
import com.CxWave.Wave.Framework.Utils.Time.ThreadStopWatch;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;

public class WaveLinearSequencerContext
{
    private WaveMessage               m_waveMessage                                = null;
    private WaveAsynchronousContext   m_waveAsynchronousContext                    = null;
    private WaveElement               m_waveElement                                = null;
    private String[]                  m_steps                                      = null;
    private int                       m_numberOfSteps                              = 0;
    private int                       m_currentStep                                = 0;
    private int                       m_numberOfCallbacksBeforeAdvancingToNextStep = 0;
    private ResourceId                m_completionStatus                           = ResourceId.WAVE_MESSAGE_ERROR;
    private boolean                   m_isHoldAllRequested                         = false;
    private boolean                   m_isTransactionStartedByMe                   = false;

    private int                       m_numberOfFailures                           = 0;

    private Vector<WaveManagedObject> m_queryResults                               = new Vector<WaveManagedObject> ();

    private boolean                   m_isADelayedCommitTransaction                = false;

    private final StopWatch           m_wallClockTimeStopWatch                     = new StopWatch ();
    private final ThreadStopWatch     m_threadTimeStopWatch                        = new ThreadStopWatch ();

    private final UI32                m_operationCode                              = new UI32 (0);

    private final Vector<Method>      m_methodsForSteps                            = new Vector<Method> ();

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
            WaveTraceUtils.infoTracePrintf ("WaveLinearSequencerContext.validateAndCompute : Searching for method name : %s", methodNameForStep);

            Class<?> classToSearchForTheMethod = waveElementClass;
            Method methodForStep = null;

            while (null != classToSearchForTheMethod)
            {
                WaveTraceUtils.infoTracePrintf ("WaveLinearSequencerContext.validateAndCompute :     Searching in class : %s", classToSearchForTheMethod.getName ());

                try
                {
                    methodForStep = classToSearchForTheMethod.getDeclaredMethod (methodNameForStep, WaveLinearSequencerContext.class);

                    methodForStep.setAccessible (true);

                    break;
                }
                catch (NoSuchMethodException | SecurityException e)
                {
                    classToSearchForTheMethod = classToSearchForTheMethod.getSuperclass ();
                }
            }

            if (null != methodForStep)
            {
                m_methodsForSteps.add (methodForStep);
            }
            else
            {
                WaveTraceUtils.fatalTracePrintf ("WaveLinearSequencerContext.validateAndCompute : Could not obtain the Step method %s on class %s", methodNameForStep, waveElementClass.getName ());
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

    public WaveMessage getWaveMessage ()
    {
        return (m_waveMessage);
    }

    public void setWaveMessage (final WaveMessage waveMessage)
    {
        m_waveMessage = waveMessage;
    }

    public WaveAsynchronousContext getWaveAsynchronousContext ()
    {
        return (m_waveAsynchronousContext);
    }

    public void incrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ()
    {
        m_numberOfCallbacksBeforeAdvancingToNextStep++;
    }

    public void decrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ()
    {
        m_numberOfCallbacksBeforeAdvancingToNextStep--;
    }

    public Vector<WaveManagedObject> getQueryResults ()
    {
        return (m_queryResults);
    }

    public void setQueryResults (final Vector<WaveManagedObject> queryResults)
    {
        m_queryResults = queryResults;
    }

    public int getNumberOfCallbacksBeforeAdvancingToNextStep ()
    {
        return (m_numberOfCallbacksBeforeAdvancingToNextStep);
    }

    public void holdAll ()
    {
        WaveAssertUtils.waveAssert (null != m_waveElement);

        m_waveElement.holdAll ();

        m_isHoldAllRequested = true;
    }

    public void unholdAll ()
    {
        WaveAssertUtils.waveAssert (null != m_waveElement);

        m_waveElement.unholdAll ();

        m_isHoldAllRequested = false;
    }

    public void incrementNumberOfFailures ()
    {
        m_numberOfFailures++;
    }

    public void setNumberOfFailures (final int numberOfFailures)
    {
        m_numberOfFailures = numberOfFailures;
    }

    public int getNumberOfFailures ()
    {
        return (m_numberOfFailures);
    }

    public boolean getIsHoldAllRequested ()
    {
        return (m_isHoldAllRequested);
    }

    public boolean getIsTransactionStartedByMe ()
    {
        return (m_isTransactionStartedByMe);
    }

    public void setIsTransactionStartedByMe (final boolean isTransactionStartedByMe)
    {
        m_isTransactionStartedByMe = isTransactionStartedByMe;
    }

    public boolean getIsADelayedCommitTransaction ()
    {
        return (m_isADelayedCommitTransaction);
    }

    public void setIsADelayedCommitTransaction (final boolean isADelayedCommitTransaction)
    {
        m_isADelayedCommitTransaction = isADelayedCommitTransaction;
    }

    public void executeCurrentStep ()
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

        try
        {
            methodForCurrentStep.invoke (m_waveElement, this);
        }
        catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException e)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveLinearSequencerContext.executeCurrentStep : Failed to invoke method : %s, Details : %s", methodForCurrentStep.getName (), e.toString ());
        }
    }

    public void start ()
    {
        executeCurrentStep ();
    }

    /*
     * Note, make sure that a call to this function is followed by a return. There should be absolutely no call to
     * "executeNextStep" after calling this function.
     */

    public void executeSuccessStep ()
    {
        if (m_currentStep >= (m_numberOfSteps - 2))
        {
            WaveTraceUtils.warnTracePrintf ("WaveLinearSequencerContext.executeSuccessStep : Invalid state for this operation. Step (%d / %d)", m_currentStep, m_numberOfSteps);
            executeNextStep (ResourceId.WAVE_MESSAGE_SUCCESS);
            return;
        }

        // Move step pointer to success step, set status to SUCCSSS, and then just execute the step.

        m_currentStep = m_numberOfSteps - 2;
        m_completionStatus = ResourceId.WAVE_MESSAGE_SUCCESS;

        executeCurrentStep ();
        return;
    }

    public void executeNextStep (final ResourceId currentStepStatus)
    {
        if (0 != m_numberOfCallbacksBeforeAdvancingToNextStep)
        {
            return;
        }

        if (m_currentStep < (m_numberOfSteps - 2))
        {
            m_wallClockTimeStopWatch.stop ();
            m_threadTimeStopWatch.stop ();

            m_waveElement.updateTimeConsumedInThisThread (m_operationCode, m_currentStep, m_threadTimeStopWatch.getLastLapDuration ());
            m_waveElement.updateRealTimeConsumedInThisThread (m_operationCode, m_currentStep, m_wallClockTimeStopWatch.getLastLapDuration ());
        }

        m_completionStatus = currentStepStatus;

        advanceCurrentStep ();

        if ((m_numberOfSteps - 2) < m_currentStep)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveLinearSequencerContext.executeNextStep : Trying to execute beyond the end of the sequencer. Step (%d / %d)", m_currentStep, m_numberOfSteps);
            WaveAssertUtils.waveAssert ();
            return;
        }

        if (ResourceId.WAVE_MESSAGE_SUCCESS == m_completionStatus)
        {
            executeCurrentStep ();
            return;
        }
        else
        {
            m_currentStep = m_numberOfSteps - 1;
            executeCurrentStep ();
            return;
        }
    }
}
