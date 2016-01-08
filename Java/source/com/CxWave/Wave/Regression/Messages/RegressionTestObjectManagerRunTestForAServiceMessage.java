/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Regression.Messages;

import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.ManagementInterface.ClientInterface.ManagementInterfaceMessage;
import com.CxWave.Wave.Regression.RegressionMessageIds;
import com.CxWave.Wave.Regression.RegressionTestObjectManager;

public class RegressionTestObjectManagerRunTestForAServiceMessage extends ManagementInterfaceMessage
{
    private WaveServiceId m_testServiceCode               = new WaveServiceId (0);
    private UI32          m_numberOfTimesToRunServiceTest = new UI32 (0);

    public RegressionTestObjectManagerRunTestForAServiceMessage ()
    {
        super (RegressionTestObjectManager.getServiceName (), RegressionMessageIds.REGRESSION_RUN_TEST_FOR_A_SERVICE);
    }

    public RegressionTestObjectManagerRunTestForAServiceMessage (final WaveServiceId serviceCode, final UI32 numberOfTimesToRunServiceTest)
    {
        super (RegressionTestObjectManager.getServiceName (), RegressionMessageIds.REGRESSION_RUN_TEST_FOR_A_SERVICE);

        m_testServiceCode.setId (serviceCode.getId ());
        m_numberOfTimesToRunServiceTest.setValue (numberOfTimesToRunServiceTest);
    }

    public WaveServiceId getTestServiceCode ()
    {
        return m_testServiceCode;
    }

    public void setTestServiceCode (final WaveServiceId testServiceCode)
    {
        m_testServiceCode = testServiceCode;
    }

    public UI32 getNumberOfTimesToRunServiceTest ()
    {
        return m_numberOfTimesToRunServiceTest;
    }

    public void setNumberOfTimesToRunServiceTest (final UI32 numberOfTimesToRunServiceTest)
    {
        m_numberOfTimesToRunServiceTest = numberOfTimesToRunServiceTest;
    }
}
