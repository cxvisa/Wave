/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Type;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;

public class UI8
{
    private final byte m_value;

    public UI8 (final byte value)
    {
        m_value = value;
    }

    public UI8 (final long value)
    {
        WaveAssertUtils.waveAssert (isValid (value));

        m_value = (byte) (value - (1 << 7));
    }

    @Override
    public boolean equals (final Object object)
    {
        if (!(object instanceof UI8))
        {
            return (false);
        }

        if (object == this)
        {
            return (true);
        }

        final UI8 rhs = (UI8) object;

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
        if ((0 <= value) && ((1 << 8) > value))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }
}
