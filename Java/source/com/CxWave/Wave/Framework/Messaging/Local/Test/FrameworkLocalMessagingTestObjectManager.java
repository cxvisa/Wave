/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.Local.Test;

import com.CxWave.Wave.Framework.Core.Test.FrameworkTestabilityMessage1;
import com.CxWave.Wave.Framework.MultiThreading.WaveThread;
import com.CxWave.Wave.Framework.ObjectModel.WaveMessageResponseHandler;
import com.CxWave.Wave.Framework.Type.LocationId;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Regression.WaveTestObjectManager;
import com.CxWave.Wave.Regression.Contexts.RegressionTestAsynchronousContext;
import com.CxWave.Wave.Resources.ResourceEnums.FrameworkStatus;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.WaveMessageStatus;

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

        final String[] sequencerSteps =
            {
                            "simpleAsynchronousMessageTestStep",
                            "waveLinearSequencerSucceededStep",
                            "waveLinearSequencerFailedStep"
            };

        final FrameworkLocalMessagingTestContext frameworkLocalMessagingTestContext = new FrameworkLocalMessagingTestContext (regressionTestAsynchronousContext, this, sequencerSteps);

        frameworkLocalMessagingTestContext.holdAll ();
        frameworkLocalMessagingTestContext.start ();
    }

    private void simpleAsynchronousMessageTestStep (final FrameworkLocalMessagingTestContext frameworkLocalMessagingTestContext)
    {
        infoTrace ("Starting Simple Asynchronous Messaging Test.");

        int numberOfMessagesToSend = 100000;
        int i = 0;
        WaveMessageStatus status = WaveMessageStatus.WAVE_MESSAGE_ERROR;

        if (0 != (m_regressionInput.size ()))
        {
            numberOfMessagesToSend = (new Integer (m_regressionInput.get (0))).intValue ();
        }

        infoTracePrintf ("    Sending %d messages.", numberOfMessagesToSend);

        frameworkLocalMessagingTestContext.incrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

        for (i = 0; i < numberOfMessagesToSend; i++)
        {
            final FrameworkTestabilityMessage1 frameworkTestabilityMessage1 = new FrameworkTestabilityMessage1 ();

            status = send (frameworkTestabilityMessage1, new WaveMessageResponseHandler ("frameworkTestabilityMessage1Callback"), frameworkLocalMessagingTestContext, 0, LocationId.NullLocationId, this);

            if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
            {
                frameworkLocalMessagingTestContext.incrementNumberOfFailures ();
                debugTracePrintf ("FrameworkLocalMessagingTestObjectManager::simpleAsynchronousMessageTestStep : Sending a message to [" + WaveThread.getWaveServiceNameForServiceId (frameworkTestabilityMessage1.getSenderServiceCode ()) + " service] failed.");
            }
            else
            {
                frameworkLocalMessagingTestContext.incrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();
            }
        }

        frameworkLocalMessagingTestContext.decrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();
        frameworkLocalMessagingTestContext.executeNextStep (((frameworkLocalMessagingTestContext.getNumberOfFailures ()) > 0) ? ResourceId.WAVE_MESSAGE_ERROR : ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private void frameworkTestabilityMessage1Callback (final FrameworkStatus frameworkStatus, final FrameworkTestabilityMessage1 frameworkTestabilityMessage1, final FrameworkLocalMessagingTestContext frameworkLocalMessagingTestContext)
    {
        frameworkLocalMessagingTestContext.decrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

        if (FrameworkStatus.FRAMEWORK_SUCCESS == frameworkStatus)
        {
            waveAssert (null != frameworkTestabilityMessage1);

            if (ResourceId.WAVE_MESSAGE_SUCCESS != (frameworkTestabilityMessage1.getCompletionStatus ()))
            {
                frameworkLocalMessagingTestContext.incrementNumberOfFailures ();
            }

        }
        else
        {
            frameworkLocalMessagingTestContext.incrementNumberOfFailures ();
        }

        frameworkLocalMessagingTestContext.executeNextStep (((frameworkLocalMessagingTestContext.getNumberOfFailures ()) > 0) ? ResourceId.WAVE_MESSAGE_ERROR : ResourceId.WAVE_MESSAGE_SUCCESS);
    }
}
