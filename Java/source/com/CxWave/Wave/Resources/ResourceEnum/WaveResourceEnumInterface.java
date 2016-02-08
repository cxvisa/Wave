/***************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave.Resources.ResourceEnum;

import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;

public interface WaveResourceEnumInterface
{
    public int getEffectiveResourceId ();

    public String getName ();

    public String getValue ();

    public default ResourceId getResourceId ()
    {
        return (ResourceId.getResourceIdByEffectiveResourceId (getEffectiveResourceId ()));
    }
}
