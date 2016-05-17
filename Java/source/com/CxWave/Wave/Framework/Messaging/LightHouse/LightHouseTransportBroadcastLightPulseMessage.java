/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.LightHouse;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonSerializable;

@NonSerializable
public class LightHouseTransportBroadcastLightPulseMessage extends WaveMessage
{
    private LightPulse m_lightPulse;

    public LightHouseTransportBroadcastLightPulseMessage ()
    {
        super (LightHouseTransportObjectManager.getWaveServiceId (), LightHouseTransportTypes.LIGHT_HOUSE_TRANSPORT_BROADCAST_LIGHT_PULSE);
    }

    public LightHouseTransportBroadcastLightPulseMessage (final LightPulse lightPulse)
    {
        super (LightHouseTransportObjectManager.getWaveServiceId (), LightHouseTransportTypes.LIGHT_HOUSE_TRANSPORT_BROADCAST_LIGHT_PULSE);

        m_lightPulse = lightPulse;
    }

    public LightPulse getLightPulse ()
    {
        return m_lightPulse;
    }

    public void setLightPulse (final LightPulse lightPulse)
    {
        m_lightPulse = lightPulse;
    }
}
