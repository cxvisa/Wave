/***********************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Type;

public class LocationId
{
    private UI32 m_id;

    public LocationId (final UI32 id)
    {
        m_id = id;
    }

    public LocationId (final int id)
    {
        m_id = new UI32 (id);
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

        if (!(object instanceof LocationId))
        {
            return (false);
        }

        if (object == this)
        {
            return (true);
        }

        final LocationId rhs = (LocationId) object;

        return (m_id.equals (rhs.m_id));
    }

    public Long getSubLocationMask ()
    {
        return (new Long (0x000000FF));
    }

    public boolean isASubLocation ()
    {
        return (0 == ((m_id.getValue ()) & (getSubLocationMask ())));
    }
}
