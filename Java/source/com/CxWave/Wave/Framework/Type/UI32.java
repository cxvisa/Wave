/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Type;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;

public class UI32
{
    private final Integer m_value;

    public UI32 (final Integer value)
    {
        m_value = value;
    }

    public UI32 (final long value)
    {
        WaveAssertUtils.waveAssert (isValid (value));

        m_value = new Integer ((int) (value - (1 << 31)));
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
        if ((0 <= value) && ((1 << 31) > value))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }
}
