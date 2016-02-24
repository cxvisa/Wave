/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.Local;

import com.CxWave.Wave.Framework.MultiThreading.WaveThread;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Type.WaveOperationCodeInterface;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;

public class WaveEvent extends WaveMessage
{
    int             m_referenceCountForEventNotifications      = 1;
    final WaveMutex m_referenceCountForEventNotificationsMutex = new WaveMutex ();

    protected WaveEvent (final WaveServiceId serviceCode, final WaveOperationCodeInterface operationCode)
    {
        super (serviceCode, operationCode);
    }

    protected WaveEvent (final WaveOperationCodeInterface operationCode)
    {
        super (WaveThread.getWaveServiceIdForCurrentThread (), operationCode);
    }

    public int incrementReferenceCountForEventNotifications ()
    {
        m_referenceCountForEventNotificationsMutex.lock ();

        m_referenceCountForEventNotifications++;

        final int referenceCountForEventNotifications = m_referenceCountForEventNotifications;

        m_referenceCountForEventNotificationsMutex.unlock ();

        return (referenceCountForEventNotifications);
    }

    public int decrementReferenceCountForEventNotifications ()
    {
        m_referenceCountForEventNotificationsMutex.lock ();

        m_referenceCountForEventNotifications--;

        final int referenceCountForEventNotifications = m_referenceCountForEventNotifications;

        m_referenceCountForEventNotificationsMutex.unlock ();

        return (referenceCountForEventNotifications);
    }

    public void setReferenceCountForEventNotifications (final int referenceCountForEventNotifications)
    {
        m_referenceCountForEventNotificationsMutex.lock ();

        m_referenceCountForEventNotifications = referenceCountForEventNotifications;

        m_referenceCountForEventNotificationsMutex.unlock ();
    }

    public static UI32 getOperationCodeForEventClass (final Class<?> eventClass)
    {
        WaveAssertUtils.waveAssert (null != eventClass);

        Object object = null;

        try
        {
            object = eventClass.newInstance ();
        }
        catch (final Exception exception)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveEvent.getOperationCodeForEventClass : %s message class could not be instantiated.  Details : %s", eventClass.getName (), exception.toString ());

            WaveAssertUtils.waveAssert ();
        }

        final WaveEvent waveEvent = (WaveEvent) object;

        WaveAssertUtils.waveAssert (null != waveEvent);

        final UI32 operationCode = waveEvent.getOperationCode ();

        WaveAssertUtils.waveAssert (null != operationCode);

        return (operationCode);
    }

    public static WaveServiceId getServiceCodeForEventClass (final Class<?> eventClass)
    {
        WaveAssertUtils.waveAssert (null != eventClass);

        Object object = null;

        try
        {
            object = eventClass.newInstance ();
        }
        catch (final Exception exception)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveEvent.getServiceCodeForEventClass : %s message class could not be instantiated.  Details : %s", eventClass.getName (), exception.toString ());

            WaveAssertUtils.waveAssert ();
        }

        final WaveEvent waveEvent = (WaveEvent) object;

        WaveAssertUtils.waveAssert (null != waveEvent);

        final WaveServiceId serviceCode = waveEvent.getServiceCode ();

        WaveAssertUtils.waveAssert (null != serviceCode);

        return (serviceCode);
    }
}
