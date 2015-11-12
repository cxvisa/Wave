/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Configuration;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.XmlWaveXPath;

public class WaveMainManagementInterface extends SerializableObject
{
    @XmlWaveXPath (path = "server")
    private WaveMainManagementInterfaceServer m_waveMainManagementInterfaceServer;

    @XmlWaveXPath (path = "client")
    private WaveMainManagementInterfaceClient m_waveMainManagementInterfaceClient;

    public WaveMainManagementInterfaceServer getWaveMainManagementInterfaceServer ()
    {
        return m_waveMainManagementInterfaceServer;
    }

    public void setWaveMainManagementInterfaceServer (final WaveMainManagementInterfaceServer waveMainManagementInterfaceServer)
    {
        m_waveMainManagementInterfaceServer = waveMainManagementInterfaceServer;
    }

    public WaveMainManagementInterfaceClient getWaveMainManagementInterfaceClient ()
    {
        return m_waveMainManagementInterfaceClient;
    }

    public void setWaveMainManagementInterfaceClient (final WaveMainManagementInterfaceClient waveMainManagementInterfaceClient)
    {
        m_waveMainManagementInterfaceClient = waveMainManagementInterfaceClient;
    }
}
