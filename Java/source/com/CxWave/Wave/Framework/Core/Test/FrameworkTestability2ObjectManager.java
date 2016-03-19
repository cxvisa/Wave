
package com.CxWave.Wave.Framework.Core.Test;

import com.CxWave.Wave.Framework.Messaging.Local.Test.FrameworkTestabilityEvent1;
import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManager;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;

public class FrameworkTestability2ObjectManager extends WaveLocalObjectManager
{
    private static FrameworkTestability2ObjectManager s_frameworkTestability2ObjectManager = null;
    private int                                       s_numberOfEventsRceivedSoFar         = 0;

    protected FrameworkTestability2ObjectManager ()
    {
        super (getServiceName ());
    }

    public static String getServiceName ()
    {
        return ("Framework Testability2");
    }

    public static FrameworkTestability2ObjectManager getInstance ()
    {
        if (null == s_frameworkTestability2ObjectManager)
        {
            s_frameworkTestability2ObjectManager = new FrameworkTestability2ObjectManager ();
        }

        WaveAssertUtils.waveAssert (null != s_frameworkTestability2ObjectManager);

        return (s_frameworkTestability2ObjectManager);
    }

    public static WaveServiceId getWaveServiceId ()
    {
        return ((getInstance ()).getServiceId ());
    }

    private void frameworkTestabilityEvent1EventHandler (final FrameworkTestabilityEvent1 frameworkTestabilityEvent1)
    {
        s_numberOfEventsRceivedSoFar++;

        if (0 == (s_numberOfEventsRceivedSoFar % 10000))
        {
            infoTracePrintf ("FrameworkTestability2ObjectManager::frameworkTestabilityEvent1EventHandler : Received Events ... %d", s_numberOfEventsRceivedSoFar);
            debugTracePrintf ("m_eventUI32   = %d", frameworkTestabilityEvent1.getEventUI32 ());
            debugTracePrintf ("m_eventString = %s", frameworkTestabilityEvent1.getEventString ());
        }

        reply (frameworkTestabilityEvent1);
    }
}
