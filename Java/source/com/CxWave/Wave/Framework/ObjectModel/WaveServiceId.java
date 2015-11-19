/***************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import com.CxWave.Wave.Framework.Type.UI32;

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
}
