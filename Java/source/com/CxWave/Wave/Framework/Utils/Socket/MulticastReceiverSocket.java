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

import com.CxWave.Wave.Framework.Type.SI32;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Buffer.FixedSizeBuffer;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Shell.ShellDebug;
import com.CxWave.Wave.Shell.Annotations.ShellCommand;

public class MulticastReceiverSocket
{
    private MulticastSocket m_multicastSocket;
    private DatagramPacket  m_datagramPacket = new DatagramPacket (new byte[4096], 4096);

    public MulticastReceiverSocket (final String groupAddress, final int port)
    {
        try
        {
            m_multicastSocket = new MulticastSocket (port);
        }
        catch (IOException e)
        {
            WaveTraceUtils.fatalTracePrintf ("MulticastReceiverSocket.MulticastReceiverSocket : Could not create a multicast socket : %s", e.toString ());

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
            WaveTraceUtils.fatalTracePrintf ("MulticastReceiverSocket.MulticastReceiverSocket : Invalid group address : %s", e.toString ());

            WaveAssertUtils.waveAssert ();
        }

        try
        {
            m_multicastSocket.joinGroup (groupInetAddress);
        }
        catch (IOException e)
        {
            WaveTraceUtils.fatalTracePrintf ("MulticastReceiverSocket.MulticastReceiverSocket : could not join group %s : %s", groupAddress, e.toString ());

            WaveAssertUtils.waveAssert ();
        }
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

    public boolean receive (final StringBuffer dataString, final StringBuffer fromIpAddress, final SI32 fromPort)
    {
        if (! (isValid ()))
        {
            return (false);
        }

        try
        {
            m_multicastSocket.receive (m_datagramPacket);
        }
        catch (IOException e)
        {
            WaveTraceUtils.fatalTracePrintf ("MulticastReceiverSocket.receive :could not receive for string data.  Status : %s", e.toString ());

           return (false);
        }

        final byte data[] = m_datagramPacket.getData ();
        final int  length = m_datagramPacket.getLength ();
        final int  offset = m_datagramPacket.getOffset ();

        String receivedStringData = null;

        try
        {
            receivedStringData = new String (data, "UTF-8");
        }
        catch (UnsupportedEncodingException e)
        {
            WaveTraceUtils.fatalTracePrintf ("MulticastReceiverSocket.receive :could not receive for string data.  Status : %s", e.toString ());

            return (false);
        }

        WaveAssertUtils.waveAssert (null != receivedStringData);

        WaveAssertUtils.waveAssert (null != dataString);

        dataString.append (receivedStringData);

        InetAddress inetAddressForSource = m_datagramPacket.getAddress ();

        WaveAssertUtils.waveAssert (null != inetAddressForSource);

        WaveAssertUtils.waveAssert (null != fromIpAddress);

        fromIpAddress.append (inetAddressForSource.getHostAddress ());

        WaveAssertUtils.waveAssert (null != fromPort);

        fromPort.seValue (m_datagramPacket.getPort ());

        return (true);
    }

    public boolean receive (final FixedSizeBuffer fixedSizeBuffer, final StringBuffer fromIpAddress, final SI32 fromPort)
    {
        if (! (isValid ()))
        {
            return (false);
        }

        try
        {
            m_multicastSocket.receive (m_datagramPacket);
        }
        catch (IOException e)
        {
            WaveTraceUtils.fatalTracePrintf ("MulticastReceiverSocket.receive :could not receive for string data.  Status : %s", e.toString ());

           return (false);
        }

        final byte data[] = m_datagramPacket.getData ();
        final int  length = m_datagramPacket.getLength ();
        final int  offset = m_datagramPacket.getOffset ();

        WaveAssertUtils.waveAssert (null != fixedSizeBuffer);

        final byte destinationData[] = fixedSizeBuffer.getRawBuffer ();
        final int  destinationLength = ((fixedSizeBuffer.getMaximumSize ()).intValue ()) - ((fixedSizeBuffer.getCurrentSize ()).intValue ());
        final int  destinationOffset = (fixedSizeBuffer.getCurrentSize ()).intValue ();

        System.arraycopy (data, 0, destinationData, destinationOffset, destinationLength);

        InetAddress inetAddressForSource = m_datagramPacket.getAddress ();

        WaveAssertUtils.waveAssert (null != inetAddressForSource);

        WaveAssertUtils.waveAssert (null != fromIpAddress);

        fromIpAddress.append (inetAddressForSource.getHostAddress ());

        WaveAssertUtils.waveAssert (null != fromPort);

        fromPort.seValue (m_datagramPacket.getPort ());

        return (true);
    }


    @ShellCommand (shell = ShellDebug.class, briefHelp = "Sends a muticast packet to the specified multicast group and port.")
    public static void receiveMessageToMulticastGroup (final Vector<String> arguments)
    {
        if (2 <= (arguments.size ()))
        {
            String       groupAddress  = arguments.get (0);
            int          port          = Integer.valueOf (arguments.get (1));
            StringBuffer dataToReceive = new StringBuffer ();
            StringBuffer fromIpAddress = new StringBuffer ();
            SI32         fromPort      = new SI32 (0);

            MulticastReceiverSocket multicastReceiverSocket = new MulticastReceiverSocket (groupAddress, port);

            boolean status = multicastReceiverSocket.receive (dataToReceive, fromIpAddress, fromPort);

            if (true == status)
            {
                WaveTraceUtils.successTracePrintf ("MulticastReceiverSocket.receiveMessageToMulticastGroup : Successfully received %s from %s : %d", dataToReceive.toString (), fromIpAddress.toString (), fromPort.intValue ());
            }
            else
            {
                WaveTraceUtils.errorTracePrintf ("MulticastReceiverSocket.receiveMessageToMulticastGroup : Failed to receive from %s : %d", groupAddress, port);
            }
        }
    }
}
