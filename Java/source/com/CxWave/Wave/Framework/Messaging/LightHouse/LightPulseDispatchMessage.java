/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.LightHouse;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.Type.SI32;

public class LightPulseDispatchMessage extends WaveMessage
{
    private String m_lightPulseSerializedString;
    private String m_senderIpAddress;
    private SI32   m_senderPort = new SI32 (0);

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

    public String getSenderIpAddress ()
    {
        return m_senderIpAddress;
    }

    public void setSenderIpAddress (final String senderIpAddress)
    {
        m_senderIpAddress = senderIpAddress;
    }

    public SI32 getSenderPort ()
    {
        return m_senderPort;
    }

    public void setSenderPort (final SI32 senderPort)
    {
        m_senderPort = senderPort;
    }
}
