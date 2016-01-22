/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.Local;

import com.CxWave.Wave.Framework.Type.WaveOperationCodeInterface;
import com.CxWave.Wave.Framework.Type.WaveServiceId;

public class WaveServiceIndependentMessage extends WaveMessage implements WaveServiceIndependentMessageBase
{

    protected WaveServiceIndependentMessage (final WaveServiceId serviceCode, final WaveOperationCodeInterface operationCode)
    {
        super (serviceCode, operationCode);
    }

}
