/***************************************************************************
 *   Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc             *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.Wave.Framework.Utils.Trace;

import com.CxWave.Wave.Framework.Trace.TraceObjectManager;
import com.CxWave.Wave.Framework.Type.TraceClientId;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class WaveTraceUtils
{
    private WaveTraceUtils ()
    {
    }

    public static void trace (final TraceClientId traceClientId, final TraceLevel requestedTraceLevel, final String stringToTrace, final boolean addNewLine, final boolean suppressPrefix)
    {
        TraceObjectManager.traceDirectly (traceClientId, requestedTraceLevel, stringToTrace, addNewLine, suppressPrefix);
    }
}
