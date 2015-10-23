/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Type;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class UI32
{
    private final Integer m_value;

    public UI32 (final Integer value)
    {
        m_value = value;
    }

    public UI32 (final long value)
    {
        if (!(isValid (value)))
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_FATAL, "Invalid Value : " + value, true, false);

            WaveAssertUtils.waveAssert ();
        }

        m_value = new Integer ((int) (value - (1L << 31)));
    }

    @Override
    public boolean equals (final Object object)
    {
        if (!(object instanceof UI32))
        {
            return (false);
        }

        if (object == this)
        {
            return (true);
        }

        final UI32 rhs = (UI32) object;

        if (m_value == (rhs.getValue ()))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }

    public Integer getValue ()
    {
        return (m_value);
    }

    public boolean isValid (final long value)
    {
        if ((0 <= value) && ((1L << 31) > value))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }
}
