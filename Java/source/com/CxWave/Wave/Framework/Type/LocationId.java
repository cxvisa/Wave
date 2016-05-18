/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Type;

import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;

public class LocationId implements Comparable<LocationId>
{
    public static final LocationId NullLocationId   = new LocationId (new UI32 (0));

    public static final Object     HaPeerLocationId = new LocationId (new UI32 (1L));

    private UI32                   m_id;

    public LocationId (final UI32 id)
    {
        m_id = id;
    }

    public LocationId (final int id)
    {
        m_id = new UI32 (id);
    }

    public LocationId (final String locationIdAsString)
    {
        m_id = new UI32 (locationIdAsString);
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

    public static LocationId getThisLocationId ()
    {
        return (FrameworkToolKit.getThisLocationId ());
    }

    public static boolean isNull (final LocationId locationId)
    {
        if ((null == locationId) || (NullLocationId.equals (locationId)))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }

    public static boolean isNotNull (final LocationId locationId)
    {
        return (!(isNull (locationId)));
    }

    @Override
    public int compareTo (final LocationId rhs)
    {
        return (m_id.compareTo (rhs.m_id));
    }

    public void fromWaveString (final String inputString)
    {
        m_id = new UI32 (inputString);
    }
}
