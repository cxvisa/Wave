/***************************************************************************
 *   Copyright (C) 2015-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

public class WaveServiceId
{
    private long m_id;

    public WaveServiceId ()
    {
        m_id = 0;
    }

    public WaveServiceId (final long id)
    {
        m_id = id;
    }

    public long getId ()
    {
        return (m_id);
    }

    public void setId (final long id)
    {
        m_id = id;
    }
}
