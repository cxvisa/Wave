/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Type;

import java.util.UUID;

public class Uuid implements Comparable<Uuid>
{
    private UUID m_uuid;

    public Uuid ()
    {
        m_uuid = UUID.randomUUID ();
    }

    public Uuid (final String uuidInStringFormat)
    {
        m_uuid.fromString (uuidInStringFormat);
    }

    public Uuid (final Uuid uuid)
    {
        fromString (uuid.toString ());
    }

    public void fromString (final String uuidInStringFormat)
    {
        m_uuid.fromString (uuidInStringFormat);
    }

    public UUID getValue ()
    {
        return (m_uuid);
    }

    @Override
    public String toString ()
    {
        return (m_uuid.toString ());
    }

    @Override
    public boolean equals (final Object object)
    {
        if (null == object)
        {
            return (false);
        }

        if (!(object instanceof Uuid))
        {
            return (false);
        }

        if (object == this)
        {
            return (true);
        }

        final Uuid rhs = (Uuid) object;

        if (m_uuid.equals ((rhs.getValue ())))
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }

    public boolean equals (final Uuid rhs)
    {
        return (m_uuid.equals (rhs.m_uuid));
    }

    @Override
    public int hashCode ()
    {
        return (m_uuid.hashCode ());
    }

    @Override
    public int compareTo (final Uuid rhs)
    {
        return (m_uuid.compareTo (rhs.m_uuid));
    }
}
