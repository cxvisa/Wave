/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Regression.Messages;

import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.ManagementInterface.ClientInterface.ManagementInterfaceMessage;
import com.CxWave.Wave.Regression.RegressionMessageIds;
import com.CxWave.Wave.Regression.RegressionTestObjectManager;

public class RegressionTestObjectManagerStartRegressionMessage extends ManagementInterfaceMessage
{
    private UI32 m_numberOfTimesToRunRegression = new UI32 (1);

    public RegressionTestObjectManagerStartRegressionMessage ()
    {
        super (RegressionTestObjectManager.getServiceName (), RegressionMessageIds.REGRESSION_START_REGRESSION);
    }

    public RegressionTestObjectManagerStartRegressionMessage (final UI32 numberOfTimesToRunRegression)
    {
        super (RegressionTestObjectManager.getServiceName (), RegressionMessageIds.REGRESSION_START_REGRESSION);

        m_numberOfTimesToRunRegression.setValue (numberOfTimesToRunRegression);
    }

    public UI32 getNumberOfTimesToRunRegression ()
    {
        return m_numberOfTimesToRunRegression;
    }

    public void setNumberOfTimesToRunRegression (final UI32 numberOfTimesToRunRegression)
    {
        m_numberOfTimesToRunRegression = numberOfTimesToRunRegression;
    }
}
