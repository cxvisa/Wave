/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Test;

import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NativeService;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.ObjectManagerPriority;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.WaveObjectManagerPriority;

@NativeService
@ObjectManagerPriority (WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_FRAMEWORK_TESTABILITY3)
public class FrameworkTestability1ObjectManager extends WaveLocalObjectManager
{
    private static FrameworkTestability1ObjectManager s_frameworkTestability1ObjectManager = null;

    private FrameworkTestability1ObjectManager ()
    {
        super (getServiceName ());
    }

    public static String getServiceName ()
    {
        return ("Framework Testability1");
    }

    public static FrameworkTestability1ObjectManager getInstance ()
    {
        if (null == s_frameworkTestability1ObjectManager)
        {
            s_frameworkTestability1ObjectManager = new FrameworkTestability1ObjectManager ();
        }

        WaveAssertUtils.waveAssert (null != s_frameworkTestability1ObjectManager);

        return (s_frameworkTestability1ObjectManager);
    }

    public static WaveServiceId getWaveServiceId ()
    {
        return ((getInstance ()).getServiceId ());
    }

    private void frameworkTestabilityMessage1RequestHandler (final FrameworkTestabilityMessage1 frameworkTestabilityMessage1)
    {
        develTracePrintf ("FrameworkTestability1ObjectManager.frameworkTestabilityMessage1RequestHandler : Entering ...");

        frameworkTestabilityMessage1.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        reply (frameworkTestabilityMessage1);
    }
}
