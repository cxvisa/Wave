/***************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave.Framework.Type;

public class TraceClientId implements Comparable<TraceClientId>
{
    private long m_id;

    public TraceClientId (final long id)
    {
        m_id = id;
    }

    public TraceClientId (final TraceClientId traceClientId)
    {
        m_id = traceClientId.getId ();
    }

    public TraceClientId ()
    {
        m_id = 0;
    }

    public long getId ()
    {
        return (m_id);
    }

    public void setId (final long id)
    {
        m_id = id;
    }

    public long increment ()
    {
        m_id++;

        return (m_id);
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

        if (!(object instanceof TraceClientId))
        {
            return (false);
        }

        if (object == this)
        {
            return (true);
        }

        final TraceClientId rhs = (TraceClientId) object;

        return (m_id == rhs.m_id);
    }

    @Override
    public int compareTo (final TraceClientId rhs)
    {
        return ((new Long (m_id)).compareTo (rhs.m_id));
    }
}
