/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Network;

import java.net.Inet4Address;
import java.net.Inet6Address;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;
import java.util.Vector;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class WaveNetworkUtils
{
    private WaveNetworkUtils ()
    {
    }

    public static Vector<String> getAllIpAddressesThatAreUpForThisMachine ()
    {
        final List<InetAddress> inetAddressList = new ArrayList<InetAddress> ();

        Enumeration<NetworkInterface> networkInterfaces = null;

        try
        {
            networkInterfaces = NetworkInterface.getNetworkInterfaces ();
        }
        catch (final SocketException e1)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "Could notget network interfaces : %s", e1.toString ());

            WaveAssertUtils.waveAssert ();
        }

        while (networkInterfaces.hasMoreElements ())
        {
            final NetworkInterface networkInterface = networkInterfaces.nextElement ();

            WaveAssertUtils.waveAssert (null != networkInterface);

            try
            {
                if (networkInterface.isUp ())
                {
                    final Enumeration<InetAddress> inetAddresses = networkInterface.getInetAddresses ();

                    while (inetAddresses.hasMoreElements ())
                    {
                        final InetAddress inetAddress = inetAddresses.nextElement ();

                        WaveAssertUtils.waveAssert (null != inetAddress);

                        if (!(inetAddress.isLinkLocalAddress ()))
                        {
                            inetAddressList.add (inetAddress);
                        }
                    }
                }
            }
            catch (final SocketException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "Could not check if network interface is up : %s", e.toString ());

                WaveAssertUtils.waveAssert ();
            }
        }

        final Vector<String> ipAddresses = new Vector<String> ();

        for (final InetAddress inetAddress1 : inetAddressList)
        {
            ipAddresses.add (inetAddress1.getHostAddress ());
        }

        return (ipAddresses);
    }

    public static final Vector<String> getAllIpAddressesForThisMachine ()
    {
        final List<InetAddress> inetAddressList = new ArrayList<InetAddress> ();

        Enumeration<NetworkInterface> networkInterfaces = null;

        try
        {
            networkInterfaces = NetworkInterface.getNetworkInterfaces ();
        }
        catch (final SocketException e1)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "Could not get network interfaces : %s", e1.toString ());

            WaveAssertUtils.waveAssert ();
        }

        while (networkInterfaces.hasMoreElements ())
        {
            final NetworkInterface networkInterface = networkInterfaces.nextElement ();

            WaveAssertUtils.waveAssert (null != networkInterface);

            final Enumeration<InetAddress> inetAddresses = networkInterface.getInetAddresses ();

            while (inetAddresses.hasMoreElements ())
            {
                final InetAddress inetAddress = inetAddresses.nextElement ();

                WaveAssertUtils.waveAssert (null != inetAddress);

                if (!(inetAddress.isLinkLocalAddress ()))
                {
                    inetAddressList.add (inetAddress);
                }
            }
        }

        final Vector<String> ipAddresses = new Vector<String> ();

        for (final InetAddress inetAddress1 : inetAddressList)

        {
            ipAddresses.add (inetAddress1.getHostAddress ());
        }

        return (ipAddresses);
    }

    public static Vector<String> getAllIpV4AddressesThatAreUpForThisMachine ()
    {
        final List<InetAddress> inetAddressList = new ArrayList<InetAddress> ();

        Enumeration<NetworkInterface> networkInterfaces = null;

        try
        {
            networkInterfaces = NetworkInterface.getNetworkInterfaces ();
        }
        catch (final SocketException e1)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "Could notget network interfaces : %s", e1.toString ());

            WaveAssertUtils.waveAssert ();
        }

        while (networkInterfaces.hasMoreElements ())
        {
            final NetworkInterface networkInterface = networkInterfaces.nextElement ();

            WaveAssertUtils.waveAssert (null != networkInterface);

            try
            {
                if (networkInterface.isUp ())
                {
                    final Enumeration<InetAddress> inetAddresses = networkInterface.getInetAddresses ();

                    while (inetAddresses.hasMoreElements ())
                    {
                        final InetAddress inetAddress = inetAddresses.nextElement ();

                        WaveAssertUtils.waveAssert (null != inetAddress);

                        if (!(inetAddress.isLinkLocalAddress ()))
                        {
                            if (inetAddress instanceof Inet4Address)
                            {
                                inetAddressList.add (inetAddress);
                            }
                        }
                    }
                }
            }
            catch (final SocketException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "Could not check if network interface is up : %s", e.toString ());

                WaveAssertUtils.waveAssert ();
            }
        }

        final Vector<String> ipAddresses = new Vector<String> ();

        for (final InetAddress inetAddress1 : inetAddressList)
        {
            ipAddresses.add (inetAddress1.getHostAddress ());
        }

        return (ipAddresses);
    }

    public static Vector<String> getAllIpV6AddressesThatAreUpForThisMachine ()
    {
        final List<InetAddress> inetAddressList = new ArrayList<InetAddress> ();

        Enumeration<NetworkInterface> networkInterfaces = null;

        try
        {
            networkInterfaces = NetworkInterface.getNetworkInterfaces ();
        }
        catch (final SocketException e1)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "Could notget network interfaces : %s", e1.toString ());

            WaveAssertUtils.waveAssert ();
        }

        while (networkInterfaces.hasMoreElements ())
        {
            final NetworkInterface networkInterface = networkInterfaces.nextElement ();

            WaveAssertUtils.waveAssert (null != networkInterface);

            try
            {
                if (networkInterface.isUp ())
                {
                    final Enumeration<InetAddress> inetAddresses = networkInterface.getInetAddresses ();

                    while (inetAddresses.hasMoreElements ())
                    {
                        final InetAddress inetAddress = inetAddresses.nextElement ();

                        WaveAssertUtils.waveAssert (null != inetAddress);

                        if (!(inetAddress.isLinkLocalAddress ()))
                        {
                            if (inetAddress instanceof Inet6Address)
                            {
                                inetAddressList.add (inetAddress);
                            }
                        }
                    }
                }
            }
            catch (final SocketException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "Could not check if network interface is up : %s", e.toString ());

                WaveAssertUtils.waveAssert ();
            }
        }

        final Vector<String> ipAddresses = new Vector<String> ();

        for (final InetAddress inetAddress1 : inetAddressList)
        {
            ipAddresses.add (inetAddress1.getHostAddress ());
        }

        return (ipAddresses);
    }

    public static Vector<String> getAllIpV4PublicAddressesThatAreUpForThisMachine ()
    {
        final List<InetAddress> inetAddressList = new ArrayList<InetAddress> ();

        Enumeration<NetworkInterface> networkInterfaces = null;

        try
        {
            networkInterfaces = NetworkInterface.getNetworkInterfaces ();
        }
        catch (final SocketException e1)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "Could notget network interfaces : %s", e1.toString ());

            WaveAssertUtils.waveAssert ();
        }

        while (networkInterfaces.hasMoreElements ())
        {
            final NetworkInterface networkInterface = networkInterfaces.nextElement ();

            WaveAssertUtils.waveAssert (null != networkInterface);

            try
            {
                if (networkInterface.isUp ())
                {
                    final Enumeration<InetAddress> inetAddresses = networkInterface.getInetAddresses ();

                    while (inetAddresses.hasMoreElements ())
                    {
                        final InetAddress inetAddress = inetAddresses.nextElement ();

                        WaveAssertUtils.waveAssert (null != inetAddress);

                        if (!(inetAddress.isLinkLocalAddress ()))
                        {
                            if (!(inetAddress.isLoopbackAddress ()))
                            {
                                if (inetAddress instanceof Inet4Address)
                                {
                                    inetAddressList.add (inetAddress);
                                }
                            }
                        }
                    }
                }
            }
            catch (final SocketException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "Could not check if network interface is up : %s", e.toString ());

                WaveAssertUtils.waveAssert ();
            }
        }

        final Vector<String> ipAddresses = new Vector<String> ();

        for (final InetAddress inetAddress1 : inetAddressList)
        {
            ipAddresses.add (inetAddress1.getHostAddress ());
        }

        return (ipAddresses);
    }

    public static Vector<String> getAllIpV6PublicAddressesThatAreUpForThisMachine ()
    {
        final List<InetAddress> inetAddressList = new ArrayList<InetAddress> ();

        Enumeration<NetworkInterface> networkInterfaces = null;

        try
        {
            networkInterfaces = NetworkInterface.getNetworkInterfaces ();
        }
        catch (final SocketException e1)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "Could notget network interfaces : %s", e1.toString ());

            WaveAssertUtils.waveAssert ();
        }

        while (networkInterfaces.hasMoreElements ())
        {
            final NetworkInterface networkInterface = networkInterfaces.nextElement ();

            WaveAssertUtils.waveAssert (null != networkInterface);

            try
            {
                if (networkInterface.isUp ())
                {
                    final Enumeration<InetAddress> inetAddresses = networkInterface.getInetAddresses ();

                    while (inetAddresses.hasMoreElements ())
                    {
                        final InetAddress inetAddress = inetAddresses.nextElement ();

                        WaveAssertUtils.waveAssert (null != inetAddress);

                        if (!(inetAddress.isLinkLocalAddress ()))
                        {
                            if (!(inetAddress.isLoopbackAddress ()))
                            {
                                if (inetAddress instanceof Inet6Address)
                                {
                                    inetAddressList.add (inetAddress);
                                }
                            }
                        }
                    }
                }
            }
            catch (final SocketException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "Could not check if network int(erface is up : %s", e.toString ());

                WaveAssertUtils.waveAssert ();
            }
        }

        final Vector<String> ipAddresses = new Vector<String> ();

        for (final InetAddress inetAddress1 : inetAddressList)
        {
            ipAddresses.add (inetAddress1.getHostAddress ());
        }

        return (ipAddresses);
    }

    public static String getAIpV4PublicAddressThatIsUpForThisMachine ()
    {
        final Vector<String> ipV4PublicAddressesThatAreUpForThisMachine = getAllIpV4PublicAddressesThatAreUpForThisMachine ();
        String aIpV4PublicIpAddressForThisMachine = null;

        if ((null != ipV4PublicAddressesThatAreUpForThisMachine) && (0 < (ipV4PublicAddressesThatAreUpForThisMachine.size ())))
        {
            aIpV4PublicIpAddressForThisMachine = ipV4PublicAddressesThatAreUpForThisMachine.get (0);
        }

        return (aIpV4PublicIpAddressForThisMachine);
    }

    public static String getAIpV6PublicAddressThatIsUpForThisMachine ()
    {
        final Vector<String> ipV6PublicAddressesThatAreUpForThisMachine = getAllIpV6PublicAddressesThatAreUpForThisMachine ();
        String aIpV6PublicIpAddressForThisMachine = null;

        if ((null != ipV6PublicAddressesThatAreUpForThisMachine) && (0 < (ipV6PublicAddressesThatAreUpForThisMachine.size ())))
        {
            aIpV6PublicIpAddressForThisMachine = ipV6PublicAddressesThatAreUpForThisMachine.get (0);
        }

        return (aIpV6PublicIpAddressForThisMachine);
    }
}
