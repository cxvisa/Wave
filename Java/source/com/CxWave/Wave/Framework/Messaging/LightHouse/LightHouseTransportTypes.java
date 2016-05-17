/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.LightHouse;

import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Type.WaveOperationCodeInterface;

public enum LightHouseTransportTypes implements WaveOperationCodeInterface
{
    LIGHT_HOUSE_TRANSPORT_BROADCAST_LIGHT_PULSE;

    private LightHouseTransportTypes ()
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
