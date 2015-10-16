/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Type;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;

public class SI32
{
    private final Integer m_value;

    public SI32 (final Integer value)
    {
        m_value = value;
    }

    public SI32 (final long value)
    {
        WaveAssertUtils.waveAssert (isValid (value));

        m_value = new Integer ((int) value);
    }

    @Override
    public boolean equals (final Object object)
    {
        if (!(object instanceof SI32))
        {
            return (false);
        }

        if (object == this)
        {
            return (true);
        }

        final SI32 rhs = (SI32) object;

        if (m_value == (rhs.getValue ()))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }

    Integer getValue ()
    {
        return (m_value);
    }

    public boolean isValid (final long value)
    {
        if (((1 << 31) > value) && ((-(1 << 31)) <= value))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }
}
