/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.LightHouse;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.Message;

@Message (om = LightPulseDispatchObjectManager.class)
public class LightPulseRegistrationMessage extends WaveMessage
{
    private String m_lightPulseName;

    public LightPulseRegistrationMessage ()
    {
        super (LightPulseDispatchObjectManager.getWaveServiceId (), LightHouseDispatchTypes.LIGHT_PULSE_DISPATCH_REGISTER_FOR_LIGHT_PULSE);
    }

    public LightPulseRegistrationMessage (final String lightPulseName)
    {
        super (LightPulseDispatchObjectManager.getWaveServiceId (), LightHouseDispatchTypes.LIGHT_PULSE_DISPATCH_REGISTER_FOR_LIGHT_PULSE);

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
