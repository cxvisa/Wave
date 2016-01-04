/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Type;

public class WaveResourceId
{
    private UI32 m_id;

    public WaveResourceId (final UI32 id)
    {
        m_id = id;
    }

    public UI32 getId ()
    {
        return m_id;
    }

    public void setId (final UI32 id)
    {
        m_id = id;
    }

    @Override
    public String toString ()
    {
        return (m_id.toString ());
    }

    @Override
    public int hashCode ()
    {
        return (m_id.hashCode ());
    }

    @Override
    public boolean equals (final Object object)
    {
        if (null == object)
        {
            return (false);
        }

        if (!(object instanceof WaveResourceId))
        {
            return (false);
        }

        if (object == this)
        {
            return (true);
        }

        final WaveResourceId rhs = (WaveResourceId) object;

        return (m_id.equals (rhs.m_id));
    }
}
