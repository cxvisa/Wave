/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Test;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;

public class FrameworkTestabilityMessage6 extends WaveMessage
{
    public FrameworkTestabilityMessage6 ()
    {
        super (FrameworkTestability1ObjectManager.getWaveServiceId (), FrameworkTestabilityOpCodes.FRAMEWORK_TESTABILITY_MESSAGE6);
    }
}
