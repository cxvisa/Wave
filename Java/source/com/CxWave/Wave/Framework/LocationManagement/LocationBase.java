/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.LocationManagement;

import com.CxWave.Wave.Framework.Type.LocationId;
import com.CxWave.Wave.Framework.Type.SI32;
import com.CxWave.Wave.Framework.Utils.Socket.ServerStreamingSocket;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;
import com.CxWave.Wave.Resources.ResourceEnums.LocationRole;

public class LocationBase
{
    private WaveMutex             m_accessMutex;
    private WaveMutex             m_connectionEstablishmentMutex;
    private LocationRole          m_locationRole;
    private LocationId            m_locationId;
    private String                m_ipAddress;
    private String                m_ipAddressForHaInterface;
    private SI32                  m_port;
    private SI32                  m_portForHaPeer;

    private LocationId            m_clusterPrimaryLocationId;
    private SI32                  m_clusterPrimaryPort;

    private ServerStreamingSocket m_serverSocketForLocation;
    private ServerStreamingSocket m_serverSocketForHaPeer;
}
