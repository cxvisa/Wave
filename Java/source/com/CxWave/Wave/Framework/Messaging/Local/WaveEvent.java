/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.Local;

import com.CxWave.Wave.Framework.MultiThreading.WaveThread;
import com.CxWave.Wave.Framework.Type.WaveOperationCodeInterface;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;

public class WaveEvent extends WaveMessage
{
    int             m_referenceCountForEventNotifications      = 0;
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
}
