/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.Local.Test;

import java.util.Vector;

import com.CxWave.Wave.Framework.Core.Test.FrameworkTestability1ObjectManager;
import com.CxWave.Wave.Framework.Core.Test.FrameworkTestabilityMessage1;
import com.CxWave.Wave.Framework.Core.Test.FrameworkTestabilityMessage5;
import com.CxWave.Wave.Framework.Core.Test.FrameworkTestabilityMessage6;
import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.MultiThreading.WaveThread;
import com.CxWave.Wave.Framework.ObjectModel.WaveMessageResponseHandler;
import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
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
        develTracePrintf ("FrameworkLocalMessagingTestObjectManager.handleTestRequest : Entering ...");

        final String[] sequencerSteps =
            {
                            "simpleAsynchronousMessageTestStep",
                            "simpleOneWayMessageTestStep",
                            "simpleSynchronousMessageTestStep",
                            "simpleRecallMessageTestStep",
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
                debugTracePrintf ("FrameworkLocalMessagingTestObjectManager.simpleAsynchronousMessageTestStep : Sending a message to [" + WaveThread.getWaveServiceNameForServiceId (frameworkTestabilityMessage1.getSenderServiceCode ()) + " service] failed.");
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

    private void simpleOneWayMessageTestStep (final FrameworkLocalMessagingTestContext frameworkLocalMessagingTestContext)
    {
        infoTracePrintf ("Starting One Way      Messaging              Test.");

        int numberOfMessagesToSend = 100000;
        int i = 0;
        WaveMessageStatus status = WaveMessageStatus.WAVE_MESSAGE_ERROR;

        if (0 != (m_regressionInput.size ()))
        {
            numberOfMessagesToSend = (new Integer (m_regressionInput.get (0))).intValue ();
        }

        infoTracePrintf ("    Sending %d messages.", numberOfMessagesToSend);

        frameworkLocalMessagingTestContext.setNumberOfFailures (0);

        frameworkLocalMessagingTestContext.incrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

        for (i = 0; i < numberOfMessagesToSend; i++)
        {
            final FrameworkTestabilityMessage1 FrameworkTestabilityMessage1 = new FrameworkTestabilityMessage1 ();

            FrameworkTestabilityMessage1.setMessage ("This is a test message");

            status = sendOneWay (FrameworkTestabilityMessage1);

            if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
            {
                frameworkLocalMessagingTestContext.incrementNumberOfFailures ();
                errorTracePrintf ("FrameworkLocalMessagingTestObjectManager.simpleAsynchronousMessageTestStep : Sending a message to [%s service] failed.", WaveThread.getWaveServiceNameForServiceId (FrameworkTestabilityMessage1.getServiceCode ()));
            }
        }

        frameworkLocalMessagingTestContext.decrementNumberOfCallbacksNeededBeforeAdvancingToNextStep ();

        frameworkLocalMessagingTestContext.executeNextStep (((frameworkLocalMessagingTestContext.getNumberOfFailures ()) > 0) ? ResourceId.WAVE_MESSAGE_ERROR : ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    void simpleSynchronousMessageTestStep (final FrameworkLocalMessagingTestContext frameworkLocalMessagingTestContext)
    {
        infoTrace ("Starting Simple Synchronous Messaging Test.");

        int numberOfMessagesToSend = 100000;
        int i = 0;
        WaveMessageStatus status = WaveMessageStatus.WAVE_MESSAGE_ERROR;

        if (0 != (m_regressionInput.size ()))
        {
            numberOfMessagesToSend = (new Integer (m_regressionInput.get (0))).intValue ();
        }

        infoTracePrintf ("    Sending %d messages.", numberOfMessagesToSend);

        for (i = 0; i < numberOfMessagesToSend; i++)
        {
            final FrameworkTestabilityMessage1 frameworkTestabilityMessage1 = new FrameworkTestabilityMessage1 ();
            // WaveNativeTest1ServiceMessage1 message;

            status = sendSynchronously (frameworkTestabilityMessage1);

            if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
            {
                debugTracePrintf ("FrameworkLocalMessagingTestObjectManager.simpleSynchronousMessageTestStep : Failed sending a message synchronously. status = %s.", FrameworkToolKit.localize (status));
                frameworkLocalMessagingTestContext.executeNextStep (ResourceId.WAVE_MESSAGE_ERROR);
            }
            else
            {
                final ResourceId completionStatus = frameworkTestabilityMessage1.getCompletionStatus ();

                if (ResourceId.WAVE_MESSAGE_SUCCESS != completionStatus)
                {
                    debugTracePrintf ("FrameworkLocalMessagingTestObjectManager.simpleSynchronousMessageTestStep : Failed sending a message synchronously. status = %s.", FrameworkToolKit.localize (completionStatus));
                    frameworkLocalMessagingTestContext.executeNextStep (ResourceId.WAVE_MESSAGE_ERROR);
                    return;
                }
            }
        }

        frameworkLocalMessagingTestContext.executeNextStep (ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    private void simpleRecallMessageTestStep (final FrameworkLocalMessagingTestContext frameworkLocalMessagingTestContext)
    {
        infoTracePrintf ("Starting Simple Recall       Messaging Test.");

        int numberOfMessagesToSend = 100000;
        int i = 0;
        WaveMessageStatus status = WaveMessageStatus.WAVE_MESSAGE_ERROR;
        final Vector<WaveMessage> messagesToCancel = new Vector<WaveMessage> ();
        int numberOfMessagesToCancel = 0;
        int numberOfFailuresToRecall = 0;

        if (0 != (m_regressionInput.size ()))
        {
            numberOfMessagesToSend = (new Integer (m_regressionInput.get (0))).intValue ();
        }

        infoTracePrintf ("    Sending %d messages.", numberOfMessagesToSend);

        final FrameworkTestabilityMessage5 fameworkTestabilityMessage5 = new FrameworkTestabilityMessage5 ();

        status = send (fameworkTestabilityMessage5, new WaveMessageResponseHandler ("frameworkTestabilityMessage5Callback"), frameworkLocalMessagingTestContext, 0, LocationId.NullLocationId, this);

        if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
        {

            frameworkLocalMessagingTestContext.executeNextStep (status.getResourceId ());
            return;
        }

        for (i = 0; i < numberOfMessagesToSend; i++)
        {
            final FrameworkTestabilityMessage6 frameworkTestabilityMessage6 = new FrameworkTestabilityMessage6 ();

            status = send (frameworkTestabilityMessage6, new WaveMessageResponseHandler ("frameworkTestabilityMessage6Callback"), frameworkLocalMessagingTestContext, 0, LocationId.NullLocationId, this);

            if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
            {
                frameworkLocalMessagingTestContext.incrementNumberOfFailures ();
                debugTracePrintf ("FrameworkLocalMessagingTestObjectManager.simpleRecallMessageTestStep : Failed sending a message synchronously. status = %s.", FrameworkToolKit.localize (status));
            }
            else
            {
                messagesToCancel.add (frameworkTestabilityMessage6);
            }
        }

        numberOfMessagesToCancel = messagesToCancel.size ();

        if (0 == numberOfMessagesToCancel)
        {
            fatalTracePrintf ("FrameworkLocalMessagingTestObjectManager.simpleRecallMessageTestStep : Cannot continue the test.  We could not send any messages.  So we cannot cancel any.");
            waveAssert ();
        }

        numberOfFailuresToRecall = 0;

        // Now before proceeding to cancellation, make sure that the receiver at least got a chance to see
        // if there were any messages in its incoming queues. Waiting here is important. Otherwise we may
        // cancel all the messages even before the reciever sees them in its incoming queues, causing the
        // receiver to wait forever expecting to see some number of messages (> 0) in its queues.

        // We read the value and reset it so that the setup will function properly for the next test iteration.

        while (false == (FrameworkTestability1ObjectManager.getAndResetAreMessage6sReceived ()))
        {
            try
            {
                Thread.sleep (1000);
            }
            catch (final InterruptedException e)
            {
                waveAssert ();
            }
        }

        infoTracePrintf ("FrameworkLocalMessagingTestObjectManager.simpleRecallFromFrontMessageTestStep : The receiver indicated that it saw messages in its incoming queues.  We can proceed to cancel them.");

        for (i = 0; i < numberOfMessagesToCancel; i++)
        {
            status = recall (messagesToCancel.get (i));

            if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != status)
            {
                frameworkLocalMessagingTestContext.incrementNumberOfFailures ();
                numberOfFailuresToRecall++;
            }
            else
            {
                // Nothing to do
            }
        }

        messagesToCancel.clear ();

        if (0 != numberOfFailuresToRecall)
        {
            errorTracePrintf ("FrameworkLocalMessagingTestObjectManager.simpleRecallMessageTestStep : Failed to recall %d out of %d.", numberOfFailuresToRecall, numberOfMessagesToCancel);
        }
    }

    private void frameworkTestabilityMessage5Callback (final FrameworkStatus frameworkStatus, final FrameworkTestabilityMessage5 frameworkTestabilityMessage5, final FrameworkLocalMessagingTestContext frameworkLocalMessagingTestContext)
    {
        if (FrameworkStatus.FRAMEWORK_SUCCESS == frameworkStatus)
        {
            waveAssert (null != frameworkTestabilityMessage5);

            if (ResourceId.WAVE_MESSAGE_SUCCESS != (frameworkTestabilityMessage5.getCompletionStatus ()))
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

    private void frameworkTestabilityMessage6Callback (final FrameworkStatus frameworkStatus, final FrameworkTestabilityMessage6 frameworkTestabilityMessage6, final FrameworkLocalMessagingTestContext frameworkLocalMessagingTestContext)
    {

        fatalTracePrintf ("FrameworkLocalMessagingTestObjectManager.frameworkTestabilityMessage6Callback : We should never reach this place.");
        waveAssert ();
    }
}
