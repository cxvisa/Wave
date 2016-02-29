/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.Vector;

import com.CxWave.Wave.Framework.MultiThreading.WaveThread;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.WaveThreadStatus;

public class WaveServiceMap
{
    private final Map<WaveServiceId, WaveThread> m_servicesMap     = new HashMap<WaveServiceId, WaveThread> ();
    private final Map<WaveServiceId, String>     m_servicesNameMap = new HashMap<WaveServiceId, String> ();
    private final Map<String, WaveServiceId>     m_servicesIdMap   = new HashMap<String, WaveServiceId> ();
    private final WaveMutex                      m_mutex           = new WaveMutex ();

    public void addServiceMap (final WaveServiceId id, final WaveThread waveThread, final String serviceName)
    {
        m_mutex.lock ();

        final WaveThread tempWaveThread = m_servicesMap.get (id);
        final WaveServiceId tempWaveServiceId = m_servicesIdMap.get (serviceName);

        if (null != tempWaveThread)
        {
            WaveAssertUtils.waveAssert (false);
            System.err.println ("Cannot proceed.  Trying to add a duplicate service id.");
            System.exit (1);
        }

        if (null != tempWaveServiceId)
        {
            WaveAssertUtils.waveAssert (false);
            System.err.println ("Cannot proceed.  Trying to add a duplicate service name.");
            System.exit (2);
        }

        m_servicesMap.put (id, waveThread);
        m_servicesNameMap.put (id, serviceName);
        m_servicesIdMap.put (serviceName, id);

        m_mutex.unlock ();
    }

    public void removeServiceMap (final WaveServiceId waveServiceId)
    {
        m_mutex.lock ();

        if (m_servicesMap.containsKey (waveServiceId))
        {
            m_servicesMap.remove (waveServiceId);
        }
        else
        {
            WaveAssertUtils.waveAssert ();
        }

        String serviceName = null;

        if (m_servicesNameMap.containsKey (waveServiceId))
        {
            serviceName = m_servicesNameMap.remove (waveServiceId);
        }
        else
        {
            WaveAssertUtils.waveAssert ();
        }

        if (m_servicesIdMap.containsKey (serviceName))
        {
            m_servicesIdMap.remove (serviceName);
        }
        else
        {
            WaveAssertUtils.waveAssert ();
        }

        m_mutex.unlock ();
    }

    public void getListOfServiceIds (final Vector<WaveServiceId> serviceIds)
    {
        m_mutex.lock ();

        for (final WaveServiceId waveServiceId : m_servicesNameMap.keySet ())
        {
            serviceIds.add (waveServiceId);
        }

        m_mutex.unlock ();
    }

    public WaveThread getWaveThreadForServiceId (final WaveServiceId waveServiceId)
    {
        m_mutex.lock ();

        final WaveThread waveThread = m_servicesMap.get (waveServiceId);

        m_mutex.unlock ();

        return (waveThread);
    }

    public String getWaveServiceNameForServiceId (final WaveServiceId waveServiceId)
    {
        m_mutex.lock ();

        final String waveServiceName = m_servicesNameMap.get (waveServiceId);

        m_mutex.unlock ();

        return (waveServiceName);
    }

    public WaveServiceId getWaveServiceIdForServiceName (final String waveServiceName)
    {
        m_mutex.lock ();

        final WaveServiceId waveServiceId = m_servicesIdMap.get (waveServiceName);

        m_mutex.unlock ();

        return (waveServiceId);
    }

    public WaveThreadStatus joinAllThreads ()
    {
        m_mutex.lock ();

        final Set<Map.Entry<WaveServiceId, WaveThread>> servicesEntries = m_servicesMap.entrySet ();

        m_mutex.unlock ();

        final Iterator<Map.Entry<WaveServiceId, WaveThread>> iterator = servicesEntries.iterator ();

        while (iterator.hasNext ())
        {
            final Map.Entry<WaveServiceId, WaveThread> serviceEntry = iterator.next ();
            final WaveServiceId waveServiceId = serviceEntry.getKey ();
            final WaveThread waveThread = serviceEntry.getValue ();

            try
            {
                waveThread.join ();
            }
            catch (final InterruptedException e)
            {
                WaveTraceUtils.errorTracePrintf ("WaveServiceMap.joinAllThreads : Failed to wait for joning a thread %s (%s).  Details : %s", waveThread.toString (), WaveThread.getWaveServiceNameForServiceId (waveServiceId), e.toString ());

                try
                {
                    Thread.sleep (10000);
                }
                catch (final InterruptedException e1)
                {
                    WaveAssertUtils.waveAssert ();
                }
            }
        }

        return (WaveThreadStatus.WAVE_THREAD_SUCCESS);
    }
}
