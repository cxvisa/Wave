/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Regression;

import com.CxWave.Wave.Framework.Type.WaveServiceId;

public class RegressionTestEntry
{
    private final WaveServiceId m_testServiceId;
    private final boolean       m_isTestEnabled;

    public RegressionTestEntry (final WaveServiceId testServiceId, final boolean isTestEnabled)
    {
        m_testServiceId = testServiceId;
        m_isTestEnabled = isTestEnabled;
    }

    public WaveServiceId getTestServiceId ()
    {
        return (m_testServiceId);
    }

    public boolean getIsTestEnabled ()
    {
        return (m_isTestEnabled);
    }
}
