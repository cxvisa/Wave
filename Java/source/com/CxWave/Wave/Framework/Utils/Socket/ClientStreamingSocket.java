/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Socket;

import java.io.DataOutputStream;
import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;
import java.net.SocketException;

import com.CxWave.Wave.Framework.Type.SI32;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class ClientStreamingSocket implements StreamingSocket
{
    private Socket             m_socket           = null;
    private String             m_host             = null;
    private SI32               m_port             = new SI32 (0);
    private String             m_localHost        = null;
    private SI32               m_localPort        = new SI32 (0);

    protected DataOutputStream m_dataOutputString = null;

    private void computeAndSetDataOutputStream ()
    {
        if (null != m_dataOutputString)
        {
            return;
        }

        if (!(isValid ()))
        {
            return;
        }

        if (!(getIsConnected ()))
        {
            return;
        }

        try
        {
            m_dataOutputString = new DataOutputStream (m_socket.getOutputStream ());
        }
        catch (final IOException e)
        {
            WaveAssertUtils.waveAssert ();
        }
    }

    private void resetDataOutputStream ()
    {
        if (null != m_dataOutputString)
        {
            try
            {
                m_dataOutputString.close ();
            }
            catch (final IOException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Could not reset underlying Data OutputStream.  Reason : %s", e.toString ());
            }

            m_dataOutputString = null;
        }

        return;
    }

    public ClientStreamingSocket ()
    {
    }

    public ClientStreamingSocket (final Socket socket)
    {
        if (null == socket)
        {
            WaveAssertUtils.waveAssert ();
        }

        m_socket = socket;

        m_host = (m_socket.getInetAddress ()).getHostAddress ();
        m_port = new SI32 (m_socket.getPort ());
        m_localHost = m_socket.getLocalAddress ().getHostAddress ();
        m_localPort = new SI32 (m_socket.getLocalPort ());

        computeAndSetDataOutputStream ();
    }

    public ClientStreamingSocket (final String host, final SI32 port)
    {
        m_host = host;
        m_port = port;

        try
        {
            m_socket = new Socket (host, port.getValue ());

            setReuseAddress ();
            setSocketTimeOut (s_defaultSocketTimeoutInMilliSeconds.getValue ());
            setTcpNoDelay ();
            setKeepAlive ();

            computeAndSetDataOutputStream ();
        }
        catch (final IOException e)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Could not connect to host %s, port %d", host, port.getValue ());
        }
    }

    public ClientStreamingSocket (final String host, final SI32 port, final String localHost, final SI32 localPort)
    {
        m_host = host;
        m_port = port;
        m_localHost = localHost;
        m_localPort = localPort;

        try
        {
            m_socket = new Socket (host, port.getValue (), InetAddress.getByName (localHost), localPort.getValue ());

            setReuseAddress ();
            setSocketTimeOut (s_defaultSocketTimeoutInMilliSeconds.getValue ());
            setTcpNoDelay ();
            setKeepAlive ();

            computeAndSetDataOutputStream ();
        }
        catch (final IOException e)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Could not connect to host %s, port %d using local address : %s and local port : %d", host, port.getValue (), localHost, localPort.getValue ());
        }
    }

    public boolean isValid ()
    {
        if (null != m_socket)
        {
            return (true);
        }
        else
        {
            return (true);
        }
    }

    public boolean setTcpNoDelay ()
    {
        boolean succeeded = false;

        if (isValid ())
        {
            try
            {
                m_socket.setTcpNoDelay (true);

                succeeded = true;
            }
            catch (final SocketException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Failed to set TCP_NO_DELAY.  Remote Host : %s and port : %d", (m_socket.getInetAddress ()).toString (), m_socket.getPort ());
            }
        }

        return (succeeded);
    }

    public boolean clearTcpNoDelay ()
    {
        boolean succeeded = false;

        if (isValid ())
        {
            try
            {
                m_socket.setTcpNoDelay (true);

                succeeded = true;
            }
            catch (final SocketException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Failed to unset TCP_NO_DELAY.  Remote Host : %s and port : %d", (m_socket.getInetAddress ()).toString (), m_socket.getPort ());
            }
        }

        return (succeeded);
    }

    public boolean setReuseAddress ()
    {
        boolean succeeded = false;

        if (isValid ())
        {
            try
            {
                m_socket.setReuseAddress (true);

                succeeded = true;
            }
            catch (final SocketException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Failed to set SO_REUSEADDR.  Remote Host : %s and port : %d", (m_socket.getInetAddress ()).toString (), m_socket.getPort ());
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
                m_socket.setReuseAddress (false);

                succeeded = true;
            }
            catch (final SocketException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Failed to clear SO_REUSEADDR.  Remote Host : %s and port : %d", (m_socket.getInetAddress ()).toString (), m_socket.getPort ());
            }
        }

        return (succeeded);
    }

    public boolean setKeepAlive ()
    {
        boolean succeeded = false;

        if (isValid ())
        {
            try
            {
                m_socket.setKeepAlive (true);

                succeeded = true;
            }
            catch (final SocketException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Failed to set SO_KEEPALIVE.  Remote Host : %s and port : %d", (m_socket.getInetAddress ()).toString (), m_socket.getPort ());
            }
        }

        return (succeeded);
    }

    public boolean clearKeepAlive ()
    {
        boolean succeeded = false;

        if (isValid ())
        {
            try
            {
                m_socket.setKeepAlive (false);

                succeeded = true;
            }
            catch (final SocketException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Failed to clear SO_KEEPALIVE.  Remote Host : %s and port : %d", (m_socket.getInetAddress ()).toString (), m_socket.getPort ());
            }
        }

        return (succeeded);
    }

    public boolean setSocketLinger (final int seconds)
    {
        boolean succeeded = false;

        if (isValid ())
        {
            try
            {
                m_socket.setSoLinger (true, seconds);

                succeeded = true;
            }
            catch (final SocketException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Failed to set SO_LINGER.  Remote Host : %s and port : %d, seconds : %d", (m_socket.getInetAddress ()).toString (), m_socket.getPort (), seconds);
            }
        }

        return (succeeded);
    }

    public boolean clearSocketLinger ()
    {
        boolean succeeded = false;

        if (isValid ())
        {
            try
            {
                m_socket.setSoLinger (false, 0);

                succeeded = true;
            }
            catch (final SocketException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Failed to clear SO_LINGER.  Remote Host : %s and port : %d", (m_socket.getInetAddress ()).toString (), m_socket.getPort ());
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
                m_socket.setSoTimeout (milliSeconds);

                succeeded = true;
            }
            catch (final SocketException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Failed to set SO_SOTIMEOUT.  Remote Host : %s and port : %d. milliSeconds : %d", (m_socket.getInetAddress ()).toString (), m_socket.getPort (), milliSeconds);
            }
        }

        return (succeeded);
    }

    public boolean clearSocketTimeOut ()
    {
        return (setSocketTimeOut (0));
    }

    public boolean getIsConnected ()
    {
        if (isValid ())
        {
            return (m_socket.isConnected ());
        }
        else
        {
            return (false);
        }
    }

    public String getHost ()
    {
        return (m_host);
    }

    public SI32 getPort ()
    {
        return (m_port);
    }

    public boolean tryToConnect ()
    {
        if (getIsConnected ())
        {
            return (true);
        }
        else
        {
            try
            {
                m_socket = new Socket (m_host, m_port.getValue (), InetAddress.getByName (m_localHost), m_localPort.getValue ());

                setReuseAddress ();
                setSocketTimeOut (s_defaultSocketTimeoutInMilliSeconds.getValue ());
                setTcpNoDelay ();
                setKeepAlive ();

                computeAndSetDataOutputStream ();
            }
            catch (final IOException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Could not connect to host %s, port %d using local address : %s and local port : %d", m_host, m_port.getValue (), m_localHost, m_localPort.getValue ());
            }

            return (getIsConnected ());
        }
    }

    public String getSourceIpAddress ()
    {
        if (isValid ())
        {
            return (m_socket.getLocalAddress ().toString ());
        }
        else
        {
            return ("");
        }
    }

    public String getPeerIpAddress ()
    {
        if (getIsConnected ())
        {
            return (m_socket.getInetAddress ().getHostAddress ());
        }
        else
        {
            return ("");
        }
    }

    public SI32 getPeerPort ()
    {
        if (getIsConnected ())
        {
            return (new SI32 (m_socket.getPort ()));
        }
        else
        {
            return (new SI32 (0));
        }
    }

    public void close ()
    {
        if (isValid ())
        {
            try
            {
                m_socket.close ();

                resetDataOutputStream ();
            }
            catch (final IOException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Failed to close socket, host : %s, port : %d, localhsot : %s, localport : %d", m_host, m_port, m_localHost, m_localPort);
            }
        }
    }

    public boolean getIsClosed ()
    {
        if (isValid ())
        {
            return (m_socket.isClosed ());
        }
        else
        {
            return (true);
        }
    }

    public String getLocalHost ()
    {
        return (m_localHost);
    }

    public SI32 getLocalPort ()
    {
        return (m_localPort);
    }

    public int send (final UI32 value)
    {
        return (send (value.getValue ()));
    }

    public int send (final int value)
    {
        if (!(isValid ()))
        {
            return (-1);
        }

        int status = 0;

        try
        {
            m_dataOutputString.writeInt (value);
        }
        catch (final IOException e)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Failed to send integer : %s", e.toString ());

            status = -1;
        }

        return (status);
    }
}
