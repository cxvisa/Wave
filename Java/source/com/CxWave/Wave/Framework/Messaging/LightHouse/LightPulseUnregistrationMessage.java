/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.LightHouse;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;

public class LightPulseUnregistrationMessage extends WaveMessage
{
    private String m_lightPulseName;

    public LightPulseUnregistrationMessage ()
    {
        super (LightPulseDispatchObjectManager.getWaveServiceId (), LightHouseDispatchTypes.LIGHT_PULSE_DISPATCH_UNREGISTER_FOR_LIGHT_PULSE);
    }

    public LightPulseUnregistrationMessage (final String lightPulseName)
    {
        super (LightPulseDispatchObjectManager.getWaveServiceId (), LightHouseDispatchTypes.LIGHT_PULSE_DISPATCH_UNREGISTER_FOR_LIGHT_PULSE);

        m_lightPulseName = lightPulseName;
    }

    public String getLightPulseName ()
    {
        return m_lightPulseName;
    }

    public void setLightPulseName (final String lightPulseName)
    {
        m_lightPulseName = lightPulseName;
    }
}
