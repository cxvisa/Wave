/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Messages;

import com.CxWave.Wave.Framework.Messaging.LightHouse.LightPulse;
import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ObjectModel.FrameworkOpCodes;
import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.Message;
import com.CxWave.Wave.Framework.Type.WaveServiceId;

@Message (om = WaveObjectManager.class)
public class WaveDeliverLightPulseMessage extends WaveMessage
{
    LightPulse m_lightPulse = null;

    public WaveDeliverLightPulseMessage ()
    {
        super (WaveServiceId.NullServiceId, FrameworkOpCodes.WAVE_OBJECT_MANAGER_DELIVER_WAVE_LIGHT_PULSE_MESSAGE);
    }

    public WaveDeliverLightPulseMessage (final WaveServiceId id)
    {
        super (id, FrameworkOpCodes.WAVE_OBJECT_MANAGER_DELIVER_WAVE_LIGHT_PULSE_MESSAGE);
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
