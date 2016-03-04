/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.Local.Test;

import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Regression.WaveTestObjectManager;
import com.CxWave.Wave.Regression.Contexts.RegressionTestAsynchronousContext;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;

public class FrameworkLocalMessagingTestObjectManager extends WaveTestObjectManager
{
    private static FrameworkLocalMessagingTestObjectManager s_frameworkLocalMessagingTestObjectManager = null;

    public FrameworkLocalMessagingTestObjectManager ()
    {
        super (getServiceName ());
    }

    public static String getServiceName ()
    {
        return ("Framework Local Messaging Test");
    }

    public static FrameworkLocalMessagingTestObjectManager getInstance ()
    {
        if (null == s_frameworkLocalMessagingTestObjectManager)
        {
            s_frameworkLocalMessagingTestObjectManager = new FrameworkLocalMessagingTestObjectManager ();
        }

        WaveAssertUtils.waveAssert (null != s_frameworkLocalMessagingTestObjectManager);

        return (s_frameworkLocalMessagingTestObjectManager);
    }

    public static WaveServiceId getWaveServiceId ()
    {
        return ((getInstance ()).getServiceId ());
    }

    @Override
    public void handleTestRequest (final RegressionTestAsynchronousContext regressionTestAsynchronousContext)
    {
        infoTracePrintf ("FrameworkLocalMessagingTestObjectManager.handleTestRequest : Entering ...");

        regressionTestAsynchronousContext.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        regressionTestAsynchronousContext.callback ();
    }
}
