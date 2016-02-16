/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Timer;

import com.CxWave.Wave.Framework.Core.Messages.WaveTimerExpiredObjectManagerMessage;
import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.OwnerOM;
import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
import com.CxWave.Wave.Framework.Type.TimeValue;
import com.CxWave.Wave.Framework.Type.TimerHandle;
import com.CxWave.Wave.Framework.Type.AbstractDataType.WavePriorityQueue;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveCondition;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveConditionStatus;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.WaveMessageStatus;

@OwnerOM (om = TimerObjectManager.class)
public class TimerWorker extends WaveWorker
{
    private final WavePriorityQueue<TimerData> m_timerList      = new WavePriorityQueue<TimerData> ();
    private final WaveMutex                    m_mutex          = new WaveMutex ();
    private final TimerHandle                  m_currentTimerId = new TimerHandle (1);
    private final TimeValue                    m_maxDelay       = new TimeValue ();
    private final WaveCondition                m_condition      = new WaveCondition (m_mutex);

    public TimerWorker (final WaveObjectManager waveObjectManager)
    {
        super (waveObjectManager);
    }

    private void addTimer (final TimerObjectManagerAddTimerMessage timerObjectManagerAddTimerMessage)
    {
        m_mutex.lock ();

        final WaveConditionStatus status = m_condition.signal ();

        if (WaveConditionStatus.WAVE_CONDITION_SUCCESS != status)
        {
            fatalTracePrintf ("TimerWorker.addTimer : Current Timer could not be cancelled.");

            waveAssert ();

            timerObjectManagerAddTimerMessage.setTimerId (new TimerHandle (0));
            timerObjectManagerAddTimerMessage.setCompletionStatus (ResourceId.TIMER_ERROR_CAN_NOT_CANCEL_SYS_TIMER);

            m_mutex.unlock ();

            reply (timerObjectManagerAddTimerMessage);

            return;
        }

        final TimerData timerInfo = new TimerData ();

        final TimeValue periodicInterval = new TimeValue (timerObjectManagerAddTimerMessage.getPeriodicInterval ());

        timerInfo.setPeriodicInterval (periodicInterval);

        final TimeValue expirationTime = new TimeValue (timerObjectManagerAddTimerMessage.getStartTime ());

        expirationTime.add (timerObjectManagerAddTimerMessage.getStartInterval ());

        timerInfo.setExpirationTime (expirationTime);

        if (TimerHandle.NullTimerHandle.equals (m_currentTimerId))
        {
            m_currentTimerId.increment ();
        }

        timerInfo.setTimerId (m_currentTimerId);

        timerObjectManagerAddTimerMessage.setTimerId (timerInfo.getTimerId ());

        m_currentTimerId.increment ();

        timerInfo.setWaveTimerExpirationCallback (timerObjectManagerAddTimerMessage.getWaveTimerExpirationCallback ());
        timerInfo.setWaveTimerExpirationContext (timerObjectManagerAddTimerMessage.getWaveTimerExpirationContext ());
        timerInfo.setWaveTimerSender (timerObjectManagerAddTimerMessage.getWaveTimerSender ());
        timerInfo.setServiceId (timerObjectManagerAddTimerMessage.getSenderServiceCode ());

        addTimerToList (timerInfo);

        // final int result = restartTimer ();
        //
        // if (0 != result)
        // {
        // fatalTracePrintf ("TimerWorker.addTimer : Timer queue could not be restarted.");
        //
        // waveAssert ();
        //
        // timerObjectManagerAddTimerMessage.setTimerId (new TimerHandle (0));
        // timerObjectManagerAddTimerMessage.setCompletionStatus (ResourceId.TIMER_ERROR_CAN_NOT_RESTART_SYS_TIMER);
        //
        // m_mutex.unlock ();
        //
        // reply (timerObjectManagerAddTimerMessage);
        //
        // return;
        // }

        m_mutex.unlock ();
    }

    private void addTimerToList (final TimerData timerData)
    {
        m_timerList.addElement (timerData);
    }

    private int restartTimer ()
    {
        final int numberOfTimers = m_timerList.size ();

        if (0 == numberOfTimers)
        {
            final WaveConditionStatus waveConditionStatus = m_condition.awaitUninterruptibly ();

            if (WaveConditionStatus.WAVE_CONDITION_SUCCESS != waveConditionStatus)
            {
                fatalTracePrintf ("TimerWorker.restartTimer : Could not start a condition wait uninterruptibly.");

                waveAssert ();

                return (-1);
            }
        }

        final TimeValue currentTimeValue = new TimeValue ();

        while (0 < (m_timerList.size ()))
        {
            final TimerData timerInfo = m_timerList.peekFirst ();

            final TimeValue expirationTime = timerInfo.getExpirationTime ();

            currentTimeValue.resetToCurrent ();

            final int comparisonResult = expirationTime.compareTo (currentTimeValue);

            if (0 >= comparisonResult)
            {
                m_timerList.removeAndGetFirstElement ();

                final WaveTimerExpiredObjectManagerMessage waveTimerExpiredObjectManagerMessage = new WaveTimerExpiredObjectManagerMessage (timerInfo.getServiceId (), timerInfo.getTimerId (), timerInfo.getWaveTimerExpirationCallback (), timerInfo.getWaveTimerExpirationContext (), timerInfo.getWaveTimerSender ());

                final WaveMessageStatus sendStatus = sendOneWay (waveTimerExpiredObjectManagerMessage);

                if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != sendStatus)
                {
                    errorTracePrintf ("TimerWorker.restartTimer : Could not send a notification to service %s about a timer expiration with timer handle %s", FrameworkToolKit.getServiceNameById (timerInfo.getServiceId ()), (timerInfo.getTimerId ()).toString ());
                }

                final TimeValue periodicInterval = timerInfo.getPeriodicInterval ();

                if (!(TimerHandle.NullTimerHandle.equals (timerInfo.getPeriodicInterval ())))
                {
                    expirationTime.add (periodicInterval);

                    addTimerToList (timerInfo);
                }
            }
            else
            {
                currentTimeValue.resetToCurrent ();

                final long nextWaitInterval = (expirationTime.getValueInNanos ()) - (currentTimeValue.getValueInNanos ());

                final WaveConditionStatus waveConditionStatus = m_condition.awaitNanos (nextWaitInterval);

                if (WaveConditionStatus.WAVE_CONDITION_SUCCESS != waveConditionStatus)
                {
                    fatalTracePrintf ("TimerWorker.restartTimer : Could not start a condition wait for the next timer.  Wait interval in nanos : %l", nextWaitInterval);

                    waveAssert ();

                    return (-1);
                }
            }
        }

        return (0);
    }

    private void processTimeoutInternal ()
    {
        m_mutex.lock ();

        final int result = restartTimer ();

        if (0 != result)
        {
            fatalTracePrintf ("TimerWorker.processTimeoutInternal : Timer queue could not be restarted.");
        }

        m_mutex.unlock ();
    }

    public static void processTimeout ()
    {
        final TimerObjectManager timerObjectManager = TimerObjectManager.getInstance ();

        WaveAssertUtils.waveAssert (null != timerObjectManager);

        final WaveWorker waveWorker = timerObjectManager.getAWaveWorkerByWorkerClass (TimerWorker.class);

        WaveAssertUtils.waveAssert (null != waveWorker);

        final TimerWorker timerWorker = (TimerWorker) waveWorker;

        WaveAssertUtils.waveAssert (null != timerWorker);

        timerWorker.processTimeoutInternal ();
    }
}
