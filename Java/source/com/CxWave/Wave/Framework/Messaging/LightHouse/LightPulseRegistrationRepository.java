/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.LightHouse;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;

public class LightPulseRegistrationRepository
{
    private static LightPulseRegistrationRepository s_lightPulseRegistrationRepository     = null;

    private final Map<String, Set<WaveServiceId>>   m_lightPulseRecepientsByLightPulseName = new HashMap<String, Set<WaveServiceId>> ();

    private LightPulseRegistrationRepository ()
    {
    }

    public static LightPulseRegistrationRepository getInstance ()
    {
        if (null == s_lightPulseRegistrationRepository)
        {
            s_lightPulseRegistrationRepository = new LightPulseRegistrationRepository ();
        }

        WaveAssertUtils.waveAssert (null != s_lightPulseRegistrationRepository);

        return (s_lightPulseRegistrationRepository);
    }

    public void addLightPulseRecepientForLightPulseName (final String lightPulseName, final WaveServiceId recepientWaveServiceId)
    {
        Set<WaveServiceId> waveServiceIdsForLightPulseName = null;

        if (!(m_lightPulseRecepientsByLightPulseName.containsKey (lightPulseName)))
        {
            waveServiceIdsForLightPulseName = m_lightPulseRecepientsByLightPulseName.get (lightPulseName);
        }
        else
        {
            waveServiceIdsForLightPulseName = new HashSet<WaveServiceId> ();

            m_lightPulseRecepientsByLightPulseName.put (lightPulseName, waveServiceIdsForLightPulseName);
        }

        WaveAssertUtils.waveAssert (null != waveServiceIdsForLightPulseName);

        waveServiceIdsForLightPulseName.add (recepientWaveServiceId);
    }

    public void removeLightPulseRecepientForLightPulseName (final String lightPulseName, final WaveServiceId recepientWaveServiceId)
    {
        if (m_lightPulseRecepientsByLightPulseName.containsKey (lightPulseName))
        {
            (m_lightPulseRecepientsByLightPulseName.get (lightPulseName)).remove (recepientWaveServiceId);
        }
    }

    public Set<WaveServiceId> getLightPulseRecepientsForLightPulseName (final String lightPulseName)
    {
        return (m_lightPulseRecepientsByLightPulseName.getOrDefault (lightPulseName, new HashSet<WaveServiceId> ()));
    }
}
