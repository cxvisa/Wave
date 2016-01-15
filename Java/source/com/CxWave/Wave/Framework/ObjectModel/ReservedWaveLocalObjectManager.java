/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import com.CxWave.Wave.Framework.ObjectModel.Annotations.ObjectManagerPriority;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;
import com.CxWave.Wave.Resources.ResourceEnums.WaveObjectManagerPriority;

@ObjectManagerPriority (WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_RESERVED)
public class ReservedWaveLocalObjectManager extends WaveLocalObjectManager
{
    private static ReservedWaveLocalObjectManager s_reservedWaveLocalObjectManager      = null;
    private static WaveMutex                      s_reservedWaveLocalObjectManagerMutex = new WaveMutex ();

    private ReservedWaveLocalObjectManager ()
    {
        super (getClassName ());
    }

    public static String getClassName ()
    {
        return ("_Reserved For Wave Internal Purposes_");
    }

    public static ReservedWaveLocalObjectManager getInstance ()
    {
        s_reservedWaveLocalObjectManagerMutex.lock ();

        if (null == s_reservedWaveLocalObjectManager)
        {
            s_reservedWaveLocalObjectManager = new ReservedWaveLocalObjectManager ();
        }

        s_reservedWaveLocalObjectManagerMutex.unlock ();

        WaveAssertUtils.waveAssert (null != s_reservedWaveLocalObjectManager);

        return (s_reservedWaveLocalObjectManager);
    }

    public static WaveServiceId getWaveServiceId ()
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
