/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.LightHouse;

public class LightHouseToolKit
{
    private static String m_lightHouseMulticastIpAddress = "239.255.23.16";
    private static int    m_lightHouseMulticastPort      = 5011;

    private LightHouseToolKit ()
    {
    }

    public static String getLightHouseMulticastIpAddress ()
    {
        return m_lightHouseMulticastIpAddress;
    }

    public static void setLightHouseMulticastIpAddress (final String lightHouseMulticastIpAddress)
    {
        m_lightHouseMulticastIpAddress = lightHouseMulticastIpAddress;
    }

    public static int getLightHouseMulticastPort ()
    {
        return m_lightHouseMulticastPort;
    }

    public static void setLightHouseMulticastPort (final int lightHouseMulticastPort)
    {
        m_lightHouseMulticastPort = lightHouseMulticastPort;
    }
}
