/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.LightHouse;

import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Type.WaveOperationCodeInterface;

public enum LightHouseDispatchTypes implements WaveOperationCodeInterface
{
    LIGHT_PULSE_DISPATCH_RECEIVED_LIGHT_PULSE,
    LIGHT_PULSE_DISPATCH_REGISTER_FOR_LIGHT_PULSE,
    LIGHT_PULSE_DISPATCH_UNREGISTER_FOR_LIGHT_PULSE;

    private LightHouseDispatchTypes ()
    {
    }

    @Override
    public UI32 getOperationCode ()
    {
        return (new UI32 (ordinal ()));
    }

    @Override
    public int getOperationCodeIntValue ()
    {
        return (ordinal ());
    }
}
