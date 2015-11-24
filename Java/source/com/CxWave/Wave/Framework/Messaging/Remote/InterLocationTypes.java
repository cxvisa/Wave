/***********************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.Remote;

import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Type.WaveOperationCodeInterface;

public enum InterLocationTypes implements WaveOperationCodeInterface
{
    INTERLOCATION_MESSAGE_FOR_MULTICAST_SEND;

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
