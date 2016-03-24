/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Socket;

import java.io.IOException;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;

import com.CxWave.Wave.Framework.LocationManagement.ServerStreamingSocketStatus;
import com.CxWave.Wave.Framework.Type.SI32;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class ServerStreamingSocket implements StreamingSocket
{
    private static UI32                 s_defaultNumberOfConnections = new UI32 (128);

    private String                      m_host                       = null;
    private SI32                        m_port                       = new SI32 (0);
    private UI32                        m_numberOfConnections        = s_defaultNumberOfConnections;

    private ServerStreamingSocketStatus m_status                     = ServerStreamingSocketStatus.SERVER_STREAMING_SOCKET_ERROR_COULD_NOT_BIND;

    private ServerSocket                m_serverSocket               = null;

    public ServerStreamingSocket (final SI32 port)
    {
        m_port = port;

        m_host = "0.0.0.0";

        try
        {
            m_serverSocket = new ServerSocket (port.intValue (), m_numberOfConnections.intValue (), InetAddress.getByName (m_host));

            m_status = ServerStreamingSocketStatus.SERVER_STREAMING_SOCKET_SUCCESS;

            setReuseAddress ();
            setSocketTimeOut (s_defaultSocketTimeoutInMilliSeconds.getValue ());
        }
        catch (final IOException e)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Could not create server socket using host %s, port %d, number of connections : %d", m_host, port.getValue (), m_numberOfConnections.getValue ());
        }
    }

    public ServerStreamingSocket (final String host, final SI32 port)
    {
        m_port = port;
        m_host = host;

        if (null == m_host)
        {
            m_host = "0.0.0.0";
        }

        try
        {
            m_serverSocket = new ServerSocket (port.intValue (), m_numberOfConnections.intValue (), InetAddress.getByName (m_host));

            m_status = ServerStreamingSocketStatus.SERVER_STREAMING_SOCKET_SUCCESS;

            setReuseAddress ();
            setSocketTimeOut (s_defaultSocketTimeoutInMilliSeconds.getValue ());
        }
        catch (final IOException e)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Could not create server socket using host %s, port %d, number of connections : %d", host, port.getValue (), m_numberOfConnections.getValue ());
        }
    }

    public ServerStreamingSocket (final String host, final SI32 port, final UI32 numberOfConnections)
    {
        m_port = port;
        m_host = host;
        m_numberOfConnections = numberOfConnections;

        if (null == m_host)
        {
            m_host = "0.0.0.0";
        }

        try
        {
            m_serverSocket = new ServerSocket (port.intValue (), m_numberOfConnections.intValue (), InetAddress.getByName (m_host));

            m_status = ServerStreamingSocketStatus.SERVER_STREAMING_SOCKET_SUCCESS;

            setReuseAddress ();
            setSocketTimeOut (s_defaultSocketTimeoutInMilliSeconds.getValue ());
        }
        catch (final IOException e)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Could not create server socket using host %s, port %d, number of connections : %d", host, port.getValue (), m_numberOfConnections.getValue ());
        }
    }

    public boolean isValid ()
    {
        if (null != m_serverSocket)
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }

    public boolean setReuseAddress ()
    {
        boolean succeeded = false;

        if (isValid ())
        {
            try
            {
                m_serverSocket.setReuseAddress (true);

                succeeded = true;
            }
            catch (final SocketException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Failed to set SO_REUSEADDR.  Host : %s and port : %d", (m_serverSocket.getInetAddress ()).toString (), m_serverSocket.getLocalPort ());
            }
        }

        return (succeeded);
    }

    public boolean clearReuseAddress ()
    {
        boolean succeeded = false;

        if (isValid ())
        {
            try
            {
                m_serverSocket.setReuseAddress (false);

                succeeded = true;
            }
            catch (final SocketException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Failed to clear SO_REUSEADDR.  Host : %s and port : %d", (m_serverSocket.getInetAddress ()).toString (), m_serverSocket.getLocalPort ());
            }
        }

        return (succeeded);
    }

    public boolean setSocketTimeOut (final int milliSeconds)
    {
        boolean succeeded = false;

        if (isValid ())
        {
            try
            {
                m_serverSocket.setSoTimeout (milliSeconds);

                succeeded = true;
            }
            catch (final SocketException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Failed to set SO_SOTIMEOUT.  Host : %s and port : %d. milliSeconds : %d", (m_serverSocket.getInetAddress ()).toString (), m_serverSocket.getLocalPort (), milliSeconds);
            }
        }

        return (succeeded);
    }

    public boolean clearSocketTimeOut ()
    {
        return (setSocketTimeOut (0));
    }

    public AcceptedStreamingSocket accept ()
    {
        Socket socket = null;

        while (null == socket)
        {
            try
            {
                socket = m_serverSocket.accept ();
            }
            catch (final IOException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_WARN, "Could not accept connection.  Host : %s and port : %d.", (m_serverSocket.getInetAddress ()).toString (), m_serverSocket.getLocalPort ());
                // WaveAssertUtils.waveAssert ();
            }
        }

        return (new AcceptedStreamingSocket (socket));
    }

    public ServerStreamingSocketStatus getStatus ()
    {
        return (m_status);
    }
}
