/***************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave.Framework.Type;

public class WaveServiceId
{
    public static final WaveServiceId NullServiceId = new WaveServiceId (0);

    private long                      m_id;

    public WaveServiceId ()
    {
        m_id = 0;
    }

    public WaveServiceId (final long id)
    {
        m_id = id;
    }

    public WaveServiceId (final UI32 id)
    {
        m_id = id.getValue ();
    }

    public WaveServiceId (final WaveServiceId waveServiceId)
    {
        m_id = waveServiceId.m_id;
    }

    public long getId ()
    {
        return (m_id);
    }

    public void setId (final long id)
    {
        m_id = id;
    }

    public void increment ()
    {
        m_id++;
    }

    @Override
    public String toString ()
    {
        return ((new Long (m_id)).toString ());
    }

    @Override
    public int hashCode ()
    {
        return ((Long.valueOf (m_id)).hashCode ());
    }

    @Override
    public boolean equals (final Object object)
    {
        if (null == object)
        {
            return (false);
        }

        if (!(object instanceof WaveServiceId))
        {
            return (false);
        }

        if (object == this)
        {
            return (true);
        }

        final WaveServiceId rhs = (WaveServiceId) object;

        return (m_id == rhs.m_id);
    }
}
