/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Test;

import com.CxWave.Wave.Framework.ObjectModel.Annotations.ObjectManagerPriority;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Regression.WaveTestObjectManager;
import com.CxWave.Wave.Regression.Contexts.RegressionTestAsynchronousContext;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.WaveObjectManagerPriority;

@ObjectManagerPriority (WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_FRAMEWORK_CORE_TEST)
public class FrameworkCoreTestObjectManager extends WaveTestObjectManager
{
    private static FrameworkCoreTestObjectManager s_frameworkCoreTestObjectManager = null;

    public FrameworkCoreTestObjectManager ()
    {
        super (getServiceName ());
    }

    public static String getServiceName ()
    {
        return ("Framework Core Test");
    }

    public static FrameworkCoreTestObjectManager getInstance ()
    {
        if (null == s_frameworkCoreTestObjectManager)
        {
            s_frameworkCoreTestObjectManager = new FrameworkCoreTestObjectManager ();
        }

        WaveAssertUtils.waveAssert (null != s_frameworkCoreTestObjectManager);

        return (s_frameworkCoreTestObjectManager);
    }

    @Override
    public void handleTestRequest (final RegressionTestAsynchronousContext regressionTestAsynchronousContext)
    {
        develTracePrintf ("FrameworkCoreTestObjectManager.handleTestRequest : Entering ...");

        regressionTestAsynchronousContext.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        regressionTestAsynchronousContext.callback ();
    }
}