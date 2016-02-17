/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Timer;

import java.util.Iterator;

import com.CxWave.Wave.Framework.Core.Messages.WaveTimerExpiredObjectManagerMessage;
import com.CxWave.Wave.Framework.MultiThreading.WaveThread;
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

    private void addTimerMessageHandler (final TimerObjectManagerAddTimerMessage timerObjectManagerAddTimerMessage)
    {
        m_mutex.lock ();

        final WaveConditionStatus status = m_condition.signal ();

        if (WaveConditionStatus.WAVE_CONDITION_SUCCESS != status)
        {
            fatalTracePrintf ("TimerWorker.addTimerMessageHandler : Current Timer could not be cancelled.");

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

        timerInfo.setTimerId (new TimerHandle (m_currentTimerId));

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
        // fatalTracePrintf ("TimerWorker.addTimerMessageHandler : Timer queue could not be restarted.");
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

        timerObjectManagerAddTimerMessage.setCompletionStatus (ResourceId.TIMER_SUCCESS);
        reply (timerObjectManagerAddTimerMessage);

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
                else
                {
                    successTracePrintf ("TimerWorker.restartTimer : Successfully sent a notification to service %s about a timer expiration with timer handle %s", FrameworkToolKit.getServiceNameById (timerInfo.getServiceId ()), (timerInfo.getTimerId ()).toString ());
                }

                final TimeValue periodicInterval = timerInfo.getPeriodicInterval ();

                if (!(TimeValue.IMMEDIATE.equals (timerInfo.getPeriodicInterval ())))
                {
                    expirationTime.add (periodicInterval);

                    addTimerToList (timerInfo);

                    infoTracePrintf ("TimerWorker.restartTimer : Added a periodic Timer.");
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

    private void deleteTimerMessageHandler (final TimerObjectManagerDeleteTimerMessage timerObjectManagerDeleteTimerMessage)
    {
        m_mutex.lock ();

        final WaveConditionStatus status = m_condition.signal ();

        if (WaveConditionStatus.WAVE_CONDITION_SUCCESS != status)
        {
            fatalTracePrintf ("TimerWorker.deleteTimerMessageHandler : Current Timer could not be cancelled.");

            waveAssert ();

            timerObjectManagerDeleteTimerMessage.setCompletionStatus (ResourceId.TIMER_ERROR_CAN_NOT_CANCEL_SYS_TIMER);

            m_mutex.unlock ();

            reply (timerObjectManagerDeleteTimerMessage);

            return;
        }

        if (1 == removeTimer (timerObjectManagerDeleteTimerMessage, timerObjectManagerDeleteTimerMessage.getTimerId ()))
        {
            timerObjectManagerDeleteTimerMessage.setCompletionStatus (ResourceId.TIMER_SUCCESS);
        }
        else
        {
            warnTracePrintf ("TimerWorker::deleteTimerMessageHandler : Invalid Handle.");

            timerObjectManagerDeleteTimerMessage.setCompletionStatus (ResourceId.TIMER_ERROR_INVALID_HANDLE);
        }

        // final int result = restartTimer ();
        //
        // if (0 != result)
        // {
        // fatalTracePrintf ("TimerWorker.deleteTimerMessageHandler : Timer queue could not be restarted.");
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

        reply (timerObjectManagerDeleteTimerMessage);

        m_mutex.unlock ();
    }

    /*
     * removeTimer Remove a timer from the timer list.
     *
     * Inputs: timerId: Id of the timer to be removed.
     *
     * Outputs: 0 on success and 1 if the timer was not found.
     *
     * Description: Search for a timer using timer Id and remove it from the timer list.
     *
     */

    int removeTimer (final TimerObjectManagerDeleteTimerMessage timerObjectManagerDeleteTimerMessage, final TimerHandle timerId)
    {
        int found = 0;
        WaveThread waveThread = null;
        int nTimersRecalled;

        final Iterator<TimerData> iterator = m_timerList.iterator ();

        while (iterator.hasNext ())
        {
            final TimerData timerInfo = iterator.next ();

            waveAssert (null != timerInfo);

            final TimerHandle tempTimerId = timerInfo.getTimerId ();

            waveAssert (null != tempTimerId);

            if (timerId.equals (tempTimerId))
            {
                iterator.remove ();

                found = 1;
                break;
            }
        }

        waveThread = WaveThread.getWaveThreadForServiceId (timerObjectManagerDeleteTimerMessage.getSenderServiceCode ());

        if (null == waveThread)
        {
            fatalTracePrintf ("TimerWorker::removeTimer : Calling thread for delete timer is null");
            waveAssert (false);
            return 0;
        }

        nTimersRecalled = waveThread.recallTimerExpirationMessagesForTimer (timerId);

        if (0 != nTimersRecalled)
        {
            found = 1;
        }

        return (found);
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
