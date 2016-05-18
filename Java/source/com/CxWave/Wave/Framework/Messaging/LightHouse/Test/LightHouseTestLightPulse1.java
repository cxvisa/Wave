/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.LightHouse.Test;

import com.CxWave.Wave.Framework.Messaging.LightHouse.LightPulse;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.OwnerOM;

@OwnerOM (om = LightHouseTestObjectManager2.class)
public class LightHouseTestLightPulse1 extends LightPulse
{
    private String m_lightMessage;

    public LightHouseTestLightPulse1 ()
    {
        super (getLightPulseName ());
    }

    public static String getLightPulseName ()
    {
        return ("LightHouseTestLightPulse1");
    }

    public String getLightMessage ()
    {
        return m_lightMessage;
    }

    public void setLightMessage (final String lightMessage)
    {
        m_lightMessage = lightMessage;
    }
}
