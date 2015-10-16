/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Type;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;

public class SI16
{
    private final short m_value;

    public SI16 (final short value)
    {
        m_value = value;
    }

    public SI16 (final long value)
    {
        WaveAssertUtils.waveAssert (isValid (value));

        m_value = (short) value;
    }

    @Override
    public boolean equals (final Object object)
    {
        if (!(object instanceof SI16))
        {
            return (false);
        }

        if (object == this)
        {
            return (true);
        }

        final SI16 rhs = (SI16) object;

        if (m_value == (rhs.getValue ()))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }

    public short getValue ()
    {
        return (m_value);
    }

    public boolean isValid (final long value)
    {
        if (((1 << 15) > value) && ((-(1 << 15)) <= value))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }
}
