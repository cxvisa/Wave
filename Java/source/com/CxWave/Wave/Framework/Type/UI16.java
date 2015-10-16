/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Type;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;

public class UI16
{
    private final short m_value;

    public UI16 (final short value)
    {
        m_value = value;
    }

    public UI16 (final long value)
    {
        WaveAssertUtils.waveAssert (isValid (value));

        m_value = (short) (value - (1 << 15));
    }

    @Override
    public boolean equals (final Object object)
    {
        if (!(object instanceof UI16))
        {
            return (false);
        }

        if (object == this)
        {
            return (true);
        }

        final UI16 rhs = (UI16) object;

        if (m_value == (rhs.getValue ()))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }

    short getValue ()
    {
        return (m_value);
    }

    public boolean isValid (final long value)
    {
        if ((0 <= value) && ((1 << 16) > value))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }
}
