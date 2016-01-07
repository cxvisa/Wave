/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Regression;

import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManager;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Regression.Contexts.RegressionPrepare2AsynchronousContext;
import com.CxWave.Wave.Regression.Contexts.RegressionPrepareAsynchronousContext;
import com.CxWave.Wave.Regression.Contexts.RegressionTestAsynchronousContext;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;

public class WaveTestObjectManager extends WaveLocalObjectManager
{
    private final Map<String, String> m_testParameters  = new HashMap<String, String> ();
    private final Vector<String>      m_regressionInput = new Vector<String> ();

    public WaveTestObjectManager (final String waveLocalObjectManagerName)
    {
        super (waveLocalObjectManagerName);
    }

    public WaveTestObjectManager (final String waveLocalObjectManagerName, final UI32 stackSize)
    {
        super (waveLocalObjectManagerName, stackSize);
    }

    public void handleTestRequest (final RegressionTestAsynchronousContext regressionTestAsynchronousContext)
    {
        develTracePrintf ("WaveTestObjectManager.handleTestRequest : Entering ...");

        regressionTestAsynchronousContext.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        regressionTestAsynchronousContext.callback ();
    }

    public void handlePrepareRequest (final RegressionPrepareAsynchronousContext regressionPrepareAsynchronousContext)
    {
        develTracePrintf ("WaveTestObjectManager.handlePrepareRequest : Entering ...");

        m_regressionInput.addAll (regressionPrepareAsynchronousContext.getInputStrings ());

        regressionPrepareAsynchronousContext.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        regressionPrepareAsynchronousContext.callback ();
    }

    public void handlePrepare2Request (final RegressionPrepare2AsynchronousContext regressionPrepare2AsynchronousContext)
    {
        develTracePrintf ("WaveTestObjectManager.handlePrepare2Request : Entering ...");

        final Vector<String> testInputStrings = regressionPrepare2AsynchronousContext.getInputStrings ();

        if (null == testInputStrings)
        {
            return;
        }

        final int numberOfTestParameters = testInputStrings.size ();
        int i = 0;

        for (i = 0; i < numberOfTestParameters; i++)
        {
            final String testParameterKey = testInputStrings.get (i);

            if (WaveStringUtils.isNotBlank (testParameterKey))
            {
                if ('-' == testParameterKey.charAt (i))
                {
                    if (numberOfTestParameters > (i + 1))
                    {
                        final String testParameterValue = testInputStrings.get (i + 1);

                        m_testParameters.put (testParameterKey, testParameterValue);
                    }
                }
                else
                {
                    continue;
                }
            }
            else
            {
                continue;
            }
        }

        regressionPrepare2AsynchronousContext.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        regressionPrepare2AsynchronousContext.callback ();
    }
}
