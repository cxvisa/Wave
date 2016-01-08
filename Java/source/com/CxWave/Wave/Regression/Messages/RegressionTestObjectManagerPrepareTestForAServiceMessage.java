/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Regression.Messages;

import java.util.Vector;

import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.ManagementInterface.ClientInterface.ManagementInterfaceMessage;
import com.CxWave.Wave.Regression.RegressionMessageIds;
import com.CxWave.Wave.Regression.RegressionTestObjectManager;

public class RegressionTestObjectManagerPrepareTestForAServiceMessage extends ManagementInterfaceMessage
{
    private WaveServiceId  m_testServiceCode = new WaveServiceId (0);
    private Vector<String> m_inputStrings    = new Vector<String> ();

    public RegressionTestObjectManagerPrepareTestForAServiceMessage ()
    {
        super (RegressionTestObjectManager.getServiceName (), RegressionMessageIds.REGRESSION_PREPARE_TEST_FOR_A_SERVICE);
    }

    public RegressionTestObjectManagerPrepareTestForAServiceMessage (final WaveServiceId testServiceCode, final Vector<String> inputStrings)
    {
        super (RegressionTestObjectManager.getServiceName (), RegressionMessageIds.REGRESSION_PREPARE_TEST_FOR_A_SERVICE);

        m_testServiceCode = testServiceCode;
        m_inputStrings = inputStrings;
    }

    public WaveServiceId getTestServiceCode ()
    {
        return m_testServiceCode;
    }

    public void setTestServiceCode (final WaveServiceId testServiceCode)
    {
        m_testServiceCode = testServiceCode;
    }

    public Vector<String> getInputStrings ()
    {
        return m_inputStrings;
    }

    public void setInputStrings (final Vector<String> inputStrings)
    {
        m_inputStrings = inputStrings;
    }
}
