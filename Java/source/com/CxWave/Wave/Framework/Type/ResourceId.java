/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Type;

public class ResourceId
{
    private UI32 m_id;

    public ResourceId (final UI32 id)
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
}
