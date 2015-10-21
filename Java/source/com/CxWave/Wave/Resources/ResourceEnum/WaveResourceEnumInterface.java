/***************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave.Resources.ResourceEnum;

import com.CxWave.Wave.Framework.Type.ResourceId;
import com.CxWave.Wave.Framework.Type.UI32;

public interface WaveResourceEnumInterface
{
    public int getEffectiveResourceId ();

    public String getName ();

    public String getValue ();

    public default ResourceId getResourceId ()
    {
        return (new ResourceId (new UI32 (getEffectiveResourceId ())));
    }
}
