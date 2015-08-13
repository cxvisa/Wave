/***************************************************************************
 *   Copyright (C) 2015-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.Wave.Framework.Core;

import java.util.Map;

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

    public void addServiceMap  (WaveServiceId id, WaveThread waveThread, final String serviceName)
    {
        m_mutex.lock ();

        WaveThread    tempWaveThread    = m_servicesMap.get(id);
        WaveServiceId tempWaveServiceId = m_servicesIdMap.get (serviceName);

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

        m_servicesMap.put     (id, waveThread);
        m_servicesNameMap.put (id, serviceName);
        m_servicesIdMap.put   (serviceName, id);

        m_mutex.unlock ();
    }
}
