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
import java.util.Vector;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Shell.ShellDebug;
import com.CxWave.Wave.Shell.Annotations.ShellCommand;

public class MuilticastSenderSocket
{
    private MulticastSocket m_multicastSocket;
    private DatagramPacket  m_datagramPacket = new DatagramPacket (new byte[1], 1);

    public MuilticastSenderSocket (final String groupAddress, final int port)
    {
        try
        {
            m_multicastSocket = new MulticastSocket ();
        }
        catch (IOException e)
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
        catch (UnknownHostException e)
        {
            WaveTraceUtils.fatalTracePrintf ("MuilticastSenderSocket.MuilticastSenderSocket : Invalid group address : %s", e.toString ());

            WaveAssertUtils.waveAssert ();
        }

        m_datagramPacket.setAddress (groupInetAddress);
        m_datagramPacket.setPort    (port);
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
        if (! (isValid ()))
        {
            return (false);
        }

        byte dataBytes[] = null;

        try
        {
            dataBytes = data.getBytes ("UTF-8");
        }
        catch (UnsupportedEncodingException e)
        {
            WaveTraceUtils.fatalTracePrintf ("MuilticastSenderSocket.send : could not encode into bytes : %s", e.toString ());

            return (false);
        }

        m_datagramPacket.setData (dataBytes);

        try
        {
            m_multicastSocket.send (m_datagramPacket);
        }
        catch (IOException e)
        {
            WaveTraceUtils.fatalTracePrintf ("MuilticastSenderSocket.send : could not send data string : %s", e.toString ());

            return (false);
        }

        return (true);
    }

    @ShellCommand (shell = ShellDebug.class, briefHelp = "Sends a muticast packet to the specified multicast group and port.")
    public static void sendMessageToMulticastGroup (final Vector<String> arguments)
    {
        if (3 <= (arguments.size ()))
        {
            String groupAddress = arguments.get (0);
            int    port         = Integer.valueOf (arguments.get (1));
            String dataToSend   = arguments.get (2);

            MuilticastSenderSocket muilticastSenderSocket = new MuilticastSenderSocket (groupAddress, port);

            boolean status = muilticastSenderSocket.send (dataToSend);

            if (true == status)
            {
                WaveTraceUtils.successTracePrintf ("MuilticastSenderSocket.sendMessageToMulticastGroup : Successfully sent %s to %s : %d", dataToSend, groupAddress, port);
            }
            else
            {
                WaveTraceUtils.errorTracePrintf ("MuilticastSenderSocket.sendMessageToMulticastGroup : Failed to send %s to %s : %d", dataToSend, groupAddress, port);
            }
        }
    }
}
