/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Test;

import com.CxWave.Wave.Framework.Messaging.Local.Test.FrameworkTestabilityEvent1;
import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NativeService;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.ObjectManagerPriority;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.WaveObjectManagerPriority;

@NativeService
@ObjectManagerPriority (WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_FRAMEWORK_TESTABILITY3)
public class FrameworkTestability1ObjectManager extends WaveLocalObjectManager
{
    private static FrameworkTestability1ObjectManager s_frameworkTestability1ObjectManager = null;
    private static boolean                            s_areMessage6sReceived               = false;
    private static WaveMutex                          s_areMessage6sReceivedMutex          = new WaveMutex ();

    static int                                        s_numberOfEventsRceivedSoFar         = 0;

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

    public static void setAreMessage6sReceived (final boolean areMessage6sReceived)
    {
        s_areMessage6sReceivedMutex.lock ();
        s_areMessage6sReceived = areMessage6sReceived;
        s_areMessage6sReceivedMutex.unlock ();
    }

    public static boolean getAndResetAreMessage6sReceived ()
    {
        boolean areMessage6sReceived = false;

        s_areMessage6sReceivedMutex.lock ();
        areMessage6sReceived = s_areMessage6sReceived;
        s_areMessage6sReceived = false;
        s_areMessage6sReceivedMutex.unlock ();

        return (areMessage6sReceived);
    }

    private void frameworkTestabilityMessage5RequestHandler (final FrameworkTestabilityMessage5 frameworkTestabilityMessage5)
    {
        develTracePrintf ("FrameworkTestability1ObjectManager.frameworkTestabilityMessage5RequestHandler : Serving up a FrameworkTestabilityMessage5.");

        long numberOfPendingMessages = 0;

        while (0 == (numberOfPendingMessages = getNumberOfPendingNormalMessages ()))
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

        infoTracePrintf ("FrameworkTestability1ObjectManager.frameworkTestabilityMessage5RequestHandler : Received more messages in the incoming queues.");

        setAreMessage6sReceived (true);

        while (0 != (numberOfPendingMessages = getNumberOfPendingNormalMessages ()))
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

        infoTracePrintf ("FrameworkTestability1ObjectManager.frameworkTestabilityMessage5RequestHandler : All messages from the incoming queues are gone.");

        frameworkTestabilityMessage5.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        reply (frameworkTestabilityMessage5);
    }

    private void frameworkTestabilityMessage6RequestHandler (final FrameworkTestabilityMessage6 frameworkTestabilityMessage6)
    {
        develTracePrintf ("FrameworkTestability1ObjectManager.frameworkTestabilityMessage6RequestHandler : Serving up a FrameworkTestabilityMessage6.");

        fatalTracePrintf ("FrameworkTestability1ObjectManager.frameworkTestabilityMessage6RequestHandler : We must never reach this place.  FrameworkTestabilityMessage6 is used message cancellation test mechanisms.");
        waveAssert ();

        frameworkTestabilityMessage6.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        reply (frameworkTestabilityMessage6);
    }

    private void frameworkTestabilityEvent1EventHandler (final FrameworkTestabilityEvent1 frameworkTestabilityEvent1)
    {

        s_numberOfEventsRceivedSoFar++;

        if (0 == (s_numberOfEventsRceivedSoFar % 10000))
        {
            infoTracePrintf ("FrameworkTestability1ObjectManager::frameworkTestabilityEvent1EventHandler : Received Events ... %d", s_numberOfEventsRceivedSoFar);
            debugTracePrintf ("m_eventUI32   = %d", frameworkTestabilityEvent1.getEventUI32 ());
            debugTracePrintf ("m_eventString = %s", frameworkTestabilityEvent1.getEventString ());
        }

        reply (frameworkTestabilityEvent1);
    }
}
