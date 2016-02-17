/***************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave.Framework.MultiThreading;

import static com.CxWave.Wave.Resources.ResourceEnums.WaveMessageStatus.WAVE_MESSAGE_ERROR_UNKNOWN_MESSAGE;
import static com.CxWave.Wave.Resources.ResourceEnums.WaveMessageStatus.WAVE_MESSAGE_SUCCESS;

import java.util.Deque;
import java.util.Iterator;
import java.util.LinkedList;

import com.CxWave.Wave.Framework.Core.Messages.WaveTimerExpiredObjectManagerMessage;
import com.CxWave.Wave.Framework.Type.TimerHandle;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;
import com.CxWave.Wave.Resources.ResourceEnums.WaveMessageStatus;

public class WaveMessageQueue<T>
{
    private final Deque<T> m_messageQueue;
    WaveMutex              m_waveMutex;

    WaveMessageQueue ()
    {
        m_messageQueue = new LinkedList<T> ();
        m_waveMutex = new WaveMutex ();
    }

    public void insertAtTheBack (final T element)
    {
        m_waveMutex.lock ();

        m_messageQueue.addLast (element);

        m_waveMutex.unlock ();
    }

    public void insertAtTheFront (final T element)
    {
        m_waveMutex.lock ();

        m_messageQueue.addFirst (element);

        m_waveMutex.unlock ();
    }

    public void removeFromFront ()
    {
        m_waveMutex.lock ();

        m_messageQueue.pollLast ();

        m_waveMutex.unlock ();
    }

    public WaveMessageStatus remove (final T element)
    {
        WaveMessageStatus status = WAVE_MESSAGE_ERROR_UNKNOWN_MESSAGE;

        m_waveMutex.lock ();

        final boolean elementPresent = m_messageQueue.removeFirstOccurrence (element);

        m_waveMutex.unlock ();

        if (elementPresent)
        {
            status = WAVE_MESSAGE_SUCCESS;
        }

        return (status);
    }

    public T getFromFront ()
    {
        m_waveMutex.lock ();

        final T element = m_messageQueue.peekFirst ();

        m_waveMutex.unlock ();

        return (element);
    }

    public T removeAndGetFromFront ()
    {
        m_waveMutex.lock ();

        final T element = m_messageQueue.pollFirst ();

        m_waveMutex.unlock ();

        return (element);
    }

    public long getSize ()
    {
        m_waveMutex.lock ();

        final long numberOfEntriesInTheMessageQueue = m_messageQueue.size ();

        m_waveMutex.unlock ();

        return (numberOfEntriesInTheMessageQueue);

    }

    public boolean isEmpty ()
    {
        boolean isMessageQueueEmpty = true;

        m_waveMutex.lock ();

        isMessageQueueEmpty = m_messageQueue.isEmpty ();

        m_waveMutex.unlock ();

        return (isMessageQueueEmpty);
    }

    public int removeTimerExpirationsForTimer (final TimerHandle timerHandle)
    {
        m_waveMutex.lock ();

        int numberOfExpirationsEncountered = 0;

        final Iterator<T> iterator = m_messageQueue.iterator ();

        while (iterator.hasNext ())
        {
            final T element = iterator.next ();

            WaveAssertUtils.waveAssert (null != element);

            final WaveTimerExpiredObjectManagerMessage waveTimerExpiredObjectManagerMessage = (WaveTimerExpiredObjectManagerMessage) element;

            WaveAssertUtils.waveAssert (null != waveTimerExpiredObjectManagerMessage);

            final TimerHandle timerId = waveTimerExpiredObjectManagerMessage.getTimerId ();

            WaveAssertUtils.waveAssert (null != timerId);

            if (timerHandle.equals (timerId))
            {
                iterator.remove ();

                numberOfExpirationsEncountered++;
            }
        }

        m_waveMutex.lock ();

        return numberOfExpirationsEncountered;
    }
}
