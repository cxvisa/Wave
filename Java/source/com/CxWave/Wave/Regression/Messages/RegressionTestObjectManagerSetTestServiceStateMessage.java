/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Regression.Messages;

import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.ManagementInterface.ClientInterface.ManagementInterfaceMessage;
import com.CxWave.Wave.Regression.RegressionMessageIds;
import com.CxWave.Wave.Regression.RegressionTestObjectManager;

public class RegressionTestObjectManagerSetTestServiceStateMessage extends ManagementInterfaceMessage
{
    private WaveServiceId m_testServiceId;
    private boolean       m_isTestEnabled;

    public RegressionTestObjectManagerSetTestServiceStateMessage ()
    {
        super (RegressionTestObjectManager.getServiceName (), RegressionMessageIds.REGRESSION_SET_TEST_SERVICE_STATE);
    }

    public RegressionTestObjectManagerSetTestServiceStateMessage (final WaveServiceId testServiceId, final boolean isTestEnabled)
    {
        super (RegressionTestObjectManager.getServiceName (), RegressionMessageIds.REGRESSION_SET_TEST_SERVICE_STATE);

        m_testServiceId = testServiceId;
        m_isTestEnabled = isTestEnabled;
    }

    public WaveServiceId getTestServiceId ()
    {
        return m_testServiceId;
    }

    public void setTestServiceId (final WaveServiceId testServiceId)
    {
        m_testServiceId = testServiceId;
    }

    public boolean getIsTestEnabled ()
    {
        return m_isTestEnabled;
    }

    public void setIsTestEnabled (final boolean isTestEnabled)
    {
        m_isTestEnabled = isTestEnabled;
    }
}
