/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Configuration;

import java.util.Vector;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.XmlWaveXPath;

public class WaveMainRasSysLogRemote extends SerializableObject
{
    @XmlWaveXPath (path = "enable")
    private boolean m_enable;

    @XmlWaveXPath (path = "ip-address-port")
    Vector<String>  m_ipAddressAndPortCombinations = new Vector<String> ();

    public boolean getEnable ()
    {
        return m_enable;
    }

    public void setEnable (final boolean enable)
    {
        m_enable = enable;
    }

    public Vector<String> getIpAddressAndPortCombinations ()
    {
        return m_ipAddressAndPortCombinations;
    }

    public void setIpAddressAndPortCombinations (final Vector<String> ipAddressAndPortCombinations)
    {
        m_ipAddressAndPortCombinations = ipAddressAndPortCombinations;
    }
}
