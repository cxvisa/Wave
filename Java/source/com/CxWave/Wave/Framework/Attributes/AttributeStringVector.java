/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Attributes;

import java.util.HashSet;
import java.util.Set;
import java.util.Vector;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class AttributeStringVector extends Attribute
{
    private static final Vector<String> s_temp = null;

    @Override
    public Set<String> getSupportedDataTypes ()
    {
        final Set<String> supportedDataTypes = new HashSet<String> ();

        try
        {
            supportedDataTypes.add ((((getClass ()).getDeclaredField ("s_temp")).getGenericType ()).getTypeName ());
        }
        catch (NoSuchFieldException | SecurityException e)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "AttributeStringVector.getSupportedDataTypes : Could not return supported data type.  Exception : " + e.toString ());
            WaveAssertUtils.waveAssert ();
        }

        return (supportedDataTypes);
    }

}
