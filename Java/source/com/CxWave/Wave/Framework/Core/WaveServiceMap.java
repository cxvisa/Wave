/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core;

import java.util.Map;
import java.util.Vector;

import com.CxWave.Wave.Framework.MultiThreading.WaveThread;
import com.CxWave.Wave.Framework.ObjectModel.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;

public class WaveServiceMap
{
    private Map<WaveServiceId, WaveThread> m_servicesMap;
    private Map<WaveServiceId, String>     m_servicesNameMap;
    private Map<String, WaveServiceId>     m_servicesIdMap;
    private WaveMutex                      m_mutex;

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

        if (0 != (tempWaveServiceId.getId ()))
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
}
