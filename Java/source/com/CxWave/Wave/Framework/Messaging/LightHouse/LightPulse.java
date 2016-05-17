/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.LightHouse;

import com.CxWave.Wave.Framework.ObjectModel.SerializableObject;
import com.CxWave.Wave.Framework.Type.SI32;
import com.CxWave.Wave.Framework.Type.Uuid;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;

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

    public static String getLightPulseNameForLightPulseClass (final Class<?> lightPulseClass)
    {
        WaveAssertUtils.waveAssert (null != lightPulseClass);

        Object object = null;

        try
        {
            object = lightPulseClass.newInstance ();
        }
        catch (final Exception exception)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveEvent.getLightPulseNameForLightPulseClass : %s message class could not be instantiated.  Details : %s", lightPulseClass.getName (), exception.toString ());

            WaveAssertUtils.waveAssert ();
        }

        final LightPulse lightPulse = (LightPulse) object;

        WaveAssertUtils.waveAssert (null != lightPulse);

        final String lightPulseName = lightPulse.getName ();

        WaveAssertUtils.waveAssert (WaveStringUtils.isNotBlank (lightPulseName));

        return (lightPulseName);
    }
}
