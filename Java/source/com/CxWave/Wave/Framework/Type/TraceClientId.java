/***************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave.Framework.Type;

public class TraceClientId
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
}
