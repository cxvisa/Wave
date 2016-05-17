/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import com.CxWave.Wave.Framework.Messaging.LightHouse.LightPulse;
import com.CxWave.Wave.Framework.Messaging.Local.WaveEvent;
import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonEventHandler;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonLightPulseHandler;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonMessageHandler;
import com.CxWave.Wave.Framework.Type.LocationId;
import com.CxWave.Wave.Framework.Type.TimeValue;
import com.CxWave.Wave.Framework.Type.TimerHandle;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Utils.Context.WaveAsynchronousContext;
import com.CxWave.Wave.Framework.Utils.Sequencer.WaveLinearSequencerContext;
import com.CxWave.Wave.Framework.Utils.Sequencer.WaveSynchronousLinearSequencerContext;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;
import com.CxWave.Wave.Resources.ResourceEnums.WaveMessageStatus;

public abstract class WaveElement
{
    protected WaveObjectManager m_waveObjectManager;

    protected WaveElement ()
    {
    }

    protected WaveElement (final WaveObjectManager waveObjectManager)
    {
        m_waveObjectManager = waveObjectManager;
    }

    protected WaveElement (final WaveElement waveElement)
    {
        m_waveObjectManager = waveElement.m_waveObjectManager;
    }

    protected WaveObjectManager getWaveObjectManager ()
    {
        return (m_waveObjectManager);
    }

    protected void setWaveObjectManager (final WaveObjectManager waveObjectManager)
    {
        m_waveObjectManager = waveObjectManager;
    }

    protected abstract void trace (final TraceLevel requestedTraceLevel, final String stringToTrace, final boolean addNewLine, final boolean suppressPrefix);

    protected void unknownTrace (final String stringToTrace, final boolean addNewLine, final boolean suppressPrefix)
    {
        trace (TraceLevel.TRACE_LEVEL_UNKNOWN, stringToTrace, addNewLine, suppressPrefix);
    }

    protected void develTrace (final String stringToTrace, final boolean addNewLine, final boolean suppressPrefix)
    {
        trace (TraceLevel.TRACE_LEVEL_DEVEL, stringToTrace, addNewLine, suppressPrefix);
    }

    protected void debugTrace (final String stringToTrace, final boolean addNewLine, final boolean suppressPrefix)
    {
        trace (TraceLevel.TRACE_LEVEL_DEBUG, stringToTrace, addNewLine, suppressPrefix);
    }

    protected void infoTrace (final String stringToTrace, final boolean addNewLine, final boolean suppressPrefix)
    {
        trace (TraceLevel.TRACE_LEVEL_INFO, stringToTrace, addNewLine, suppressPrefix);
    }

    protected void successTrace (final String stringToTrace, final boolean addNewLine, final boolean suppressPrefix)
    {
        trace (TraceLevel.TRACE_LEVEL_SUCCESS, stringToTrace, addNewLine, suppressPrefix);
    }

    protected void warnTrace (final String stringToTrace, final boolean addNewLine, final boolean suppressPrefix)
    {
        trace (TraceLevel.TRACE_LEVEL_WARN, stringToTrace, addNewLine, suppressPrefix);
    }

    protected void errorTrace (final String stringToTrace, final boolean addNewLine, final boolean suppressPrefix)
    {
        trace (TraceLevel.TRACE_LEVEL_ERROR, stringToTrace, addNewLine, suppressPrefix);
    }

    protected void fatalTrace (final String stringToTrace, final boolean addNewLine, final boolean suppressPrefix)
    {
        trace (TraceLevel.TRACE_LEVEL_FATAL, stringToTrace, addNewLine, suppressPrefix);
    }

    protected abstract void trace (final TraceLevel requestedTraceLevel, final String stringToTrace);

    protected void unknownTrace (final String stringToTrace)
    {
        trace (TraceLevel.TRACE_LEVEL_UNKNOWN, stringToTrace);
    }

    protected void develTrace (final String stringToTrace)
    {
        trace (TraceLevel.TRACE_LEVEL_DEVEL, stringToTrace);
    }

    protected void debugTrace (final String stringToTrace)
    {
        trace (TraceLevel.TRACE_LEVEL_DEBUG, stringToTrace);
    }

    protected void infoTrace (final String stringToTrace)
    {
        trace (TraceLevel.TRACE_LEVEL_INFO, stringToTrace);
    }

    protected void successTrace (final String stringToTrace)
    {
        trace (TraceLevel.TRACE_LEVEL_SUCCESS, stringToTrace);
    }

    protected void warnTrace (final String stringToTrace)
    {
        trace (TraceLevel.TRACE_LEVEL_WARN, stringToTrace);
    }

    protected void errorTrace (final String stringToTrace)
    {
        trace (TraceLevel.TRACE_LEVEL_ERROR, stringToTrace);
    }

    protected void fatalTrace (final String stringToTrace)
    {
        trace (TraceLevel.TRACE_LEVEL_FATAL, stringToTrace);
    }

    protected abstract void tracePrintf (final TraceLevel requestedTraceLevel, final boolean addNewLine, final boolean suppressPrefix, final String formatString, Object... objects);

    protected void unknownTracePrintf (final boolean addNewLine, final boolean suppressPrefix, final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_UNKNOWN, addNewLine, suppressPrefix, formatString, objects);
    }

    protected void develTracePrintf (final boolean addNewLine, final boolean suppressPrefix, final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_DEVEL, addNewLine, suppressPrefix, formatString, objects);
    }

    protected void debugTracePrintf (final boolean addNewLine, final boolean suppressPrefix, final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_DEBUG, addNewLine, suppressPrefix, formatString, objects);
    }

    protected void infoTracePrintf (final boolean addNewLine, final boolean suppressPrefix, final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_INFO, addNewLine, suppressPrefix, formatString, objects);
    }

    protected void successTracePrintf (final boolean addNewLine, final boolean suppressPrefix, final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_SUCCESS, addNewLine, suppressPrefix, formatString, objects);
    }

    protected void warnTracePrintf (final boolean addNewLine, final boolean suppressPrefix, final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_WARN, addNewLine, suppressPrefix, formatString, objects);
    }

    protected void errorTracePrintf (final boolean addNewLine, final boolean suppressPrefix, final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, addNewLine, suppressPrefix, formatString, objects);
    }

    protected void fatalTracePrintf (final boolean addNewLine, final boolean suppressPrefix, final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, addNewLine, suppressPrefix, formatString, objects);
    }

    protected abstract void tracePrintf (final TraceLevel requestedTraceLevel, final String formatString, Object... objects);

    protected void unknownTracePrintf (final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_UNKNOWN, formatString, objects);
    }

    protected void develTracePrintf (final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_DEVEL, formatString, objects);
    }

    protected void debugTracePrintf (final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_DEBUG, formatString, objects);
    }

    protected void infoTracePrintf (final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_INFO, formatString, objects);
    }

    protected void successTracePrintf (final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_SUCCESS, formatString, objects);
    }

    protected void warnTracePrintf (final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_WARN, formatString, objects);
    }

    protected void errorTracePrintf (final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, formatString, objects);
    }

    protected void fatalTracePrintf (final String formatString, final Object... objects)
    {
        tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, formatString, objects);
    }

    protected abstract void holdMessages ();

    protected abstract void holdHighPriorityMessages ();

    protected abstract void holdEvents ();

    public abstract void holdAll ();

    protected abstract void unholdMessages ();

    protected abstract void unholdHighPriorityMessages ();

    protected abstract void unholdEvents ();

    public abstract void unholdAll ();

    public abstract void updateTimeConsumedInThisThread (final UI32 operationCode, final int currentStep, final long lastLapDuration);

    public abstract void updateRealTimeConsumedInThisThread (final UI32 operationCode, final int currentStep, final long lastLapDuration);

    /**
     * Note, if any transaction was started before calling this step, and not committed, the transaction will be committed to
     * preserve the semantics, even though if there is no db update by the step and then the reply will happen as usual.
     */

    protected void waveLinearSequencerSucceededStep (final WaveLinearSequencerContext waveLinearSequencerContext)
    {
        develTrace ("WaveElement.waveLinearSequencerSucceededStep : Entering ...");

        final WaveMessage waveMessage = waveLinearSequencerContext.getWaveMessage ();
        final WaveAsynchronousContext waveAsynchronousContext = waveLinearSequencerContext.getWaveAsynchronousContext ();
        ResourceId completionStatus = waveLinearSequencerContext.getCompletionStatus ();

        if (true == (waveLinearSequencerContext.getIsHoldAllRequested ()))
        {
            waveLinearSequencerContext.unholdAll ();
        }

        if (true == (waveLinearSequencerContext.getIsTransactionStartedByMe ()))
        {
            waveLinearSequencerContext.setIsTransactionStartedByMe (false);

            // commit the transaction to preserve the semantics of the executeSuccessStep and if the transaction
            // has no data to be committed, framework will immediately return without having to go to DB.

            completionStatus = commitTransaction ();

            if (ResourceId.FRAMEWORK_SUCCESS.equals (completionStatus))
            {
                completionStatus = ResourceId.WAVE_MESSAGE_SUCCESS;
            }
            else
            {
                completionStatus = ResourceId.WAVE_COMMIT_TRANSACTION_FAILED;
            }
        }

        if (null != waveMessage)
        {
            waveMessage.setCompletionStatus (completionStatus);
            reply (waveMessage);
        }
        else if (null != waveAsynchronousContext)
        {
            waveAsynchronousContext.setCompletionStatus (completionStatus);
            waveAsynchronousContext.callback ();
        }
    }

    protected void waveLinearSequencerFailedStep (final WaveLinearSequencerContext waveLinearSequencerContext)
    {
        develTrace ("WaveElement::waveLinearSequencerFailedStep : Entering ...");

        final WaveMessage waveMessage = waveLinearSequencerContext.getWaveMessage ();
        final WaveAsynchronousContext waveAsynchronousContext = waveLinearSequencerContext.getWaveAsynchronousContext ();

        if (true == (waveLinearSequencerContext.getIsHoldAllRequested ()))
        {
            waveLinearSequencerContext.unholdAll ();
        }

        if (true == (waveLinearSequencerContext.getIsTransactionStartedByMe ()))
        {
            waveLinearSequencerContext.setIsTransactionStartedByMe (false);
            rollbackTransaction ();
        }

        if (null != waveMessage)
        {
            waveMessage.setCompletionStatus (waveLinearSequencerContext.getCompletionStatus ());
            reply (waveMessage);
        }
        else if (null != waveAsynchronousContext)
        {
            waveAsynchronousContext.setCompletionStatus (waveLinearSequencerContext.getCompletionStatus ());
            waveAsynchronousContext.callback ();
        }
    }

    protected abstract void rollbackTransaction ();

    @NonMessageHandler
    protected abstract ResourceId reply (final WaveMessage waveMessage);

    protected abstract ResourceId commitTransaction ();

    public WaveMessage createMessageInstance (final UI32 operationCode)
    {
        if (null != m_waveObjectManager)
        {
            return (m_waveObjectManager.createMessageInstance (operationCode));
        }
        else
        {
            return (null);
        }
    }

    protected ResourceId waveSynchronousLinearSequencerSucceededStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveElement.waveSynchronousLinearSequencerSucceededStep : Entering ...");

        final WaveMessage waveMessage = waveSynchronousLinearSequencerContext.getWaveMessage ();
        final WaveAsynchronousContext waveAsynchronousContext = waveSynchronousLinearSequencerContext.getWaveAsynchronousContext ();
        ResourceId completionStatus = waveSynchronousLinearSequencerContext.getCompletionStatus ();

        if (true == (waveSynchronousLinearSequencerContext.getIsTransactionStartedByMe ()))
        {
            waveSynchronousLinearSequencerContext.setIsTransactionStartedByMe (false);

            // commit the transaction to preserve the semantics of the executeSuccessStep and if the transaction
            // has no data to be committed, framework will immediately return without having to go to DB.

            completionStatus = commitTransaction ();

            if (ResourceId.FRAMEWORK_SUCCESS.equals (completionStatus))
            {
                completionStatus = ResourceId.WAVE_MESSAGE_SUCCESS;
            }
            else
            {
                completionStatus = ResourceId.WAVE_COMMIT_TRANSACTION_FAILED;
            }
        }

        if (null != waveMessage)
        {
            waveMessage.setCompletionStatus (completionStatus);
            reply (waveMessage);
        }
        else if (null != waveAsynchronousContext)
        {
            waveAsynchronousContext.setCompletionStatus (completionStatus);
            waveAsynchronousContext.callback ();
        }

        return (completionStatus);
    }

    protected ResourceId waveSynchronousLinearSequencerFailedStep (final WaveSynchronousLinearSequencerContext waveSynchronousLinearSequencerContext)
    {
        infoTracePrintf ("WaveElement::waveLinearSequencerFailedStep : Entering ...");

        final WaveMessage waveMessage = waveSynchronousLinearSequencerContext.getWaveMessage ();
        final WaveAsynchronousContext waveAsynchronousContext = waveSynchronousLinearSequencerContext.getWaveAsynchronousContext ();
        final ResourceId completionStatus = waveSynchronousLinearSequencerContext.getCompletionStatus ();

        if (true == (waveSynchronousLinearSequencerContext.getIsTransactionStartedByMe ()))
        {
            waveSynchronousLinearSequencerContext.setIsTransactionStartedByMe (false);
            rollbackTransaction ();
        }

        if (null != waveMessage)
        {
            waveMessage.setCompletionStatus (completionStatus);
            reply (waveMessage);
        }
        else if (null != waveAsynchronousContext)
        {
            waveAsynchronousContext.setCompletionStatus (completionStatus);
            waveAsynchronousContext.callback ();
        }

        return (completionStatus);
    }

    @NonMessageHandler
    protected abstract WaveMessageStatus sendOneWay (final WaveMessage waveMessage);

    protected abstract WaveMessageStatus sendOneWay (final WaveMessage waveMessage, final LocationId locationId);

    @NonMessageHandler
    protected abstract WaveMessageStatus sendSynchronously (final WaveMessage waveMessage);

    protected abstract WaveMessageStatus sendSynchronously (final WaveMessage waveMessage, final LocationId locationId);

    protected abstract WaveMessageStatus send (final WaveMessage waveMessage, final WaveMessageResponseHandler waveMessageCallback, final Object waveMessageContext);

    protected abstract WaveMessageStatus send (final WaveMessage waveMessage, final WaveMessageResponseHandler waveMessageCallback, final Object waveMessageContext, final long timeOutInMilliSeconds, final LocationId locationId, final WaveElement waveMessageSender);

    @NonEventHandler
    protected abstract WaveMessageStatus broadcast (final WaveEvent waveEvent);

    protected abstract ResourceId startTimer (final TimerHandle timerHandle, final TimeValue startInterval, final TimeValue periodicInterval, final WaveTimerExpirationHandler waveTimerExpirationCallback, final Object waveTimerExpirationContext, final WaveElement waveTimerSender);

    protected abstract ResourceId startTimer (final TimerHandle timerHandle, final TimeValue startInterval, final TimeValue periodicInterval, final WaveTimerExpirationHandler waveTimerExpirationCallback, final Object waveTimerExpirationContexts);

    protected abstract ResourceId startTimer (final TimerHandle timerHandle, final TimeValue startInterval, final WaveTimerExpirationHandler waveTimerExpirationCallback, final Object waveTimerExpirationContext, final WaveElement waveTimerSender);

    protected abstract ResourceId startTimer (final TimerHandle timerHandle, final TimeValue startInterval, final WaveTimerExpirationHandler waveTimerExpirationCallback, final Object waveTimerExpirationContext);

    protected abstract ResourceId startTimer (final TimerHandle timerHandle, final long startIntervalMilliSeconds, final long periodicIntervalMilliSeconds, final WaveTimerExpirationHandler waveTimerExpirationCallback, final Object waveTimerExpirationContext, final WaveElement waveTimerSender);

    protected abstract ResourceId startTimer (final TimerHandle timerHandle, final long startIntervalMilliSeconds, final long periodicIntervalMilliSeconds, final WaveTimerExpirationHandler waveTimerExpirationCallback, final Object waveTimerExpirationContext);

    protected abstract ResourceId startTimer (final TimerHandle timerHandle, final long startIntervalMilliSeconds, final WaveTimerExpirationHandler waveTimerExpirationCallback, final Object waveTimerExpirationContext, final WaveElement waveTimerSender);

    protected abstract ResourceId startTimer (final TimerHandle timerHandle, final long startIntervalMilliSeconds, final WaveTimerExpirationHandler waveTimerExpirationCallback, final Object waveTimerExpirationContext);

    protected abstract ResourceId deleteTimer (final TimerHandle timerHandle);

    @NonLightPulseHandler
    protected abstract WaveMessageStatus broadcastLightPulse (final LightPulse lightPulse);
}
