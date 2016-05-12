/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.LightHouse;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;

public class LightPulseDispatchMessage extends WaveMessage
{
    private String m_lightPulseSerializedString;

    public LightPulseDispatchMessage ()
    {
        super (LightPulseDispatchObjectManager.getWaveServiceId (), LightHouseDispatchTypes.LIGHT_PULSE_DISPATCH_RECEIVED_LIGHT_PULSE);
    }

    public LightPulseDispatchMessage (final String lightPulseSerializedString)
    {
        super (LightPulseDispatchObjectManager.getWaveServiceId (), LightHouseDispatchTypes.LIGHT_PULSE_DISPATCH_RECEIVED_LIGHT_PULSE);

        m_lightPulseSerializedString = lightPulseSerializedString;
    }

    public String getLightPulseSerializedString ()
    {
        return m_lightPulseSerializedString;
    }

    public void setLightPulseSerializedString (final String lightPulseSerializedString)
    {
        m_lightPulseSerializedString = lightPulseSerializedString;
    }
}
