/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Type;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;

public class SI8
{
    private final byte m_value;

    public SI8 (final byte value)
    {
        m_value = value;
    }

    public SI8 (final long value)
    {
        WaveAssertUtils.waveAssert (isValid (value));

        m_value = (byte) value;
    }

    @Override
    public boolean equals (final Object object)
    {
        if (!(object instanceof SI8))
        {
            return (false);
        }

        if (object == this)
        {
            return (true);
        }

        final SI8 rhs = (SI8) object;

        if (m_value == (rhs.getValue ()))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }

    public byte getValue ()
    {
        return (m_value);
    }

    public boolean isValid (final long value)
    {
        if ((128 > value) && (-128 <= value))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }
}
