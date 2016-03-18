/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Test;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;

public class FrameworkTestabilityMessage1 extends WaveMessage
{
    private String m_message;

    public FrameworkTestabilityMessage1 ()
    {
        super (FrameworkTestability1ObjectManager.getWaveServiceId (), FrameworkTestabilityOpCodes.FRAMEWORK_TESTABILITY_MESSAGE1);
    }

    public String getMessage ()
    {
        return m_message;
    }

    public void setMessage (final String message)
    {
        m_message = message;
    }
}
