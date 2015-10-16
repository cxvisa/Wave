/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Type;

public class SI64
{
    private Long m_value;

    public SI64 (final Long value)
    {
        m_value = value;
    }

    public SI64 (final long value)
    {
        m_value = new Long (value);
    }

    public SI64 (final int value)
    {
        m_value = new Long (value);
    }

    @Override
    public boolean equals (final Object object)
    {
        if (!(object instanceof SI64))
        {
            return (false);
        }

        if (object == this)
        {
            return (true);
        }

        SI64 rhs = (SI64) object;

        if (m_value == (rhs.getValue ()))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }

    Long getValue ()
    {
        return (m_value);
    }
}
