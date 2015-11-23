/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.ManagementInterface.ClientInterface;

import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManager;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class WaveUserInterfaceObjectManager extends WaveLocalObjectManager
{
    private static WaveUserInterfaceObjectManager s_waveUserInterfaceObjectManager = null;

    private WaveUserInterfaceObjectManager ()
    {
        super (getClassName ());
    }

    public static String getClassName ()
    {
        return ("Wave User Interface");
    }

    public static WaveUserInterfaceObjectManager getInstance ()
    {
        if (null == s_waveUserInterfaceObjectManager)
        {
            s_waveUserInterfaceObjectManager = new WaveUserInterfaceObjectManager ();
        }

        WaveAssertUtils.waveAssert (null != s_waveUserInterfaceObjectManager);

        return (s_waveUserInterfaceObjectManager);
    }

    public WaveServiceId getWaveServiceId ()
    {
        return ((getInstance ()).getServiceId ());
    }

    public void traceReservedForUtils (final WaveTraceUtils._Internal_ _internal_, final TraceLevel requestedTraceLevel, final String stringToTrace, final boolean addNewLine, final boolean suppressPrefix)
    {
        _internal_.getClass (); // protection from bypass using null.

        trace (requestedTraceLevel, stringToTrace, addNewLine, suppressPrefix);
    }

    public void tracePrintfReservedForUtils (final WaveTraceUtils._Internal_ _internal_, final TraceLevel requestedTraceLevel, final boolean addNewLine, final boolean suppressPrefix, final String formatString, final Object... objects)
    {
        _internal_.getClass (); // protection from bypass using null.

        tracePrintf (requestedTraceLevel, addNewLine, suppressPrefix, formatString, objects);
    }
}
