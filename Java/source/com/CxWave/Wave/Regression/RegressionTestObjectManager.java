/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Regression;

import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.ObjectManagerPriority;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Resources.ResourceEnums.WaveObjectManagerPriority;

@ObjectManagerPriority (WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_REGRESSION)
public class RegressionTestObjectManager extends WaveLocalObjectManager
{
    private RegressionTestObjectManager s_regressionTestObjectManager = null;

    private RegressionTestObjectManager ()
    {
        super (getServiceName ());
    }

    public static String getServiceName ()
    {
        return ("Regression");
    }

    public RegressionTestObjectManager getInstance ()
    {
        if (null == s_regressionTestObjectManager)
        {
            s_regressionTestObjectManager = new RegressionTestObjectManager ();
        }

        WaveAssertUtils.waveAssert (null != s_regressionTestObjectManager);

        return (s_regressionTestObjectManager);
    }
}
