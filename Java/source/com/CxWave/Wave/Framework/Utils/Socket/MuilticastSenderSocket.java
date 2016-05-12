/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Socket;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.net.UnknownHostException;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;

public class MuilticastSenderSocket
{
    private MulticastSocket      m_multicastSocket;
    private final DatagramPacket m_datagramPacket = new DatagramPacket (new byte[1], 1);

    public MuilticastSenderSocket (final String groupAddress, final int port)
    {
        try
        {
            m_multicastSocket = new MulticastSocket ();
        }
        catch (final IOException e)
        {
            WaveTraceUtils.fatalTracePrintf ("MuilticastSenderSocket.MuilticastSenderSocket : Could not create a multicast socket : %s", e.toString ());

            WaveAssertUtils.waveAssert ();
        }

        WaveAssertUtils.waveAssert (WaveStringUtils.isNotBlank (groupAddress));

        InetAddress groupInetAddress = null;

        try
        {
            groupInetAddress = InetAddress.getByName (groupAddress);
        }
        catch (final UnknownHostException e)
        {
            WaveTraceUtils.fatalTracePrintf ("MuilticastSenderSocket.MuilticastSenderSocket : Invalid group address : %s", e.toString ());

            WaveAssertUtils.waveAssert ();
        }

        m_datagramPacket.setAddress (groupInetAddress);
        m_datagramPacket.setPort (port);
    }

    public boolean isValid ()
    {
        if (null == m_multicastSocket)
        {
            return (false);
        }

        if (null == m_datagramPacket)
        {
            return (false);
        }

        return (true);
    }

    public boolean send (final String data)
    {
        if (!(isValid ()))
        {
            return (false);
        }

        byte dataBytes[] = null;

        try
        {
            dataBytes = data.getBytes ("UTF-8");
        }
        catch (final UnsupportedEncodingException e)
        {
            WaveTraceUtils.fatalTracePrintf ("MuilticastSenderSocket.send : could not encode into bytes : %s", e.toString ());

            return (false);
        }

        m_datagramPacket.setData (dataBytes);

        try
        {
            m_multicastSocket.send (m_datagramPacket);
        }
        catch (final IOException e)
        {
            WaveTraceUtils.fatalTracePrintf ("MuilticastSenderSocket.send : could not send data string : %s", e.toString ());

            return (false);
        }

        return (true);
    }
}
