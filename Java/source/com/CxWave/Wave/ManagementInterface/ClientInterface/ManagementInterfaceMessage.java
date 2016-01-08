/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.ManagementInterface.ClientInterface;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
import com.CxWave.Wave.Framework.Type.SI32;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Type.WaveOperationCodeInterface;

public class ManagementInterfaceMessage extends WaveMessage
{
    private String  m_serviceName;
    private String  m_clientIpAddress;
    private UI32    m_clientPort;
    private UI32    m_clientId;
    private String  m_clientName;
    private String  m_clientNameWithoutExtension;
    private UI32    m_serverId;
    private SI32    m_slotInstance;
    private boolean m_allWaveClients;
    private String  m_ttyName;

    public ManagementInterfaceMessage (final String serviceName, final WaveOperationCodeInterface operationCode)
    {
        super (FrameworkToolKit.getServiceIdByName (serviceName), operationCode);
    }

    public String getServiceName ()
    {
        return m_serviceName;
    }

    public void setServiceName (final String serviceName)
    {
        m_serviceName = serviceName;
    }

    public String getClientIpAddress ()
    {
        return m_clientIpAddress;
    }

    public void setClientIpAddress (final String clientIpAddress)
    {
        m_clientIpAddress = clientIpAddress;
    }

    public UI32 getClientPort ()
    {
        return m_clientPort;
    }

    public void setClientPort (final UI32 clientPort)
    {
        m_clientPort = clientPort;
    }

    public UI32 getClientId ()
    {
        return m_clientId;
    }

    public void setClientId (final UI32 clientId)
    {
        m_clientId = clientId;
    }

    public String getClientName ()
    {
        return m_clientName;
    }

    public void setClientName (final String clientName)
    {
        m_clientName = clientName;
    }

    public String getClientNameWithoutExtension ()
    {
        return m_clientNameWithoutExtension;
    }

    public void setClientNameWithoutExtension (final String clientNameWithoutExtension)
    {
        m_clientNameWithoutExtension = clientNameWithoutExtension;
    }

    public UI32 getServerId ()
    {
        return m_serverId;
    }

    public void setServerId (final UI32 serverId)
    {
        m_serverId = serverId;
    }

    public SI32 getSlotInstance ()
    {
        return m_slotInstance;
    }

    public void setSlotInstance (final SI32 slotInstance)
    {
        m_slotInstance = slotInstance;
    }

    public boolean getAllWaveClients ()
    {
        return m_allWaveClients;
    }

    public void setAllWaveClients (final boolean allWaveClients)
    {
        m_allWaveClients = allWaveClients;
    }

    public String getTtyName ()
    {
        return m_ttyName;
    }

    public void setTtyName (final String ttyName)
    {
        m_ttyName = ttyName;
    }
}
