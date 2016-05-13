
package com.CxWave.Wave.Framework.Messaging.LightHouse;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.Type.SI32;
import com.CxWave.Wave.Framework.Type.Uuid;

public class LightPulse extends SerializableObject
{
    private String m_name;
    private Uuid   m_senderLightHouseId                   = new Uuid ();
    private String m_senderLightHouseIpAddress            = "";
    private SI32   m_senderLightHousePort                 = new SI32 (0);
    private String m_senderIpAddressFromClientPerspective = "";

    public LightPulse (final String name)
    {
        m_name = name;
    }

    public String getName ()
    {
        return m_name;
    }

    public void setName (final String name)
    {
        m_name = name;
    }

    public Uuid getSenderLightHouseId ()
    {
        return m_senderLightHouseId;
    }

    public void setSenderLightHouseId (final Uuid senderLightHouseId)
    {
        m_senderLightHouseId = senderLightHouseId;
    }

    public String getSenderLightHouseIpAddress ()
    {
        return m_senderLightHouseIpAddress;
    }

    public void setSenderLightHouseIpAddress (final String senderLightHouseIpAddress)
    {
        m_senderLightHouseIpAddress = senderLightHouseIpAddress;
    }

    public SI32 getSenderLightHousePort ()
    {
        return m_senderLightHousePort;
    }

    public void setSenderLightHousePort (final SI32 senderLightHousePort)
    {
        m_senderLightHousePort = senderLightHousePort;
    }

    public String getSenderIpAddressFromClientPerspective ()
    {
        return m_senderIpAddressFromClientPerspective;
    }

    public void setSenderIpAddressFromClientPerspective (final String senderIpAddressFromClientPerspective)
    {
        m_senderIpAddressFromClientPerspective = senderIpAddressFromClientPerspective;
    }
}
