/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Socket;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;
import java.net.SocketException;
import java.util.Vector;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.Type.SI32;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Buffer.FixedSizeBuffer;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class ClientStreamingSocket implements StreamingSocket
{
    private Socket             m_socket           = null;
    private String             m_host             = null;
    private SI32               m_port             = new SI32 (0);
    private String             m_localHost        = null;
    private SI32               m_localPort        = new SI32 (0);

    protected DataOutputStream m_dataOutputStream = null;
    protected DataInputStream  m_dataInputStream  = null;

    private void computeAndSetDataOutputStream ()
    {
        if (null != m_dataOutputStream)
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
            m_dataOutputStream = new DataOutputStream (m_socket.getOutputStream ());
        }
        catch (final IOException e)
        {
            WaveAssertUtils.waveAssert ();
        }
    }

    private void resetDataOutputStream ()
    {
        if (null != m_dataOutputStream)
        {
            try
            {
                m_dataOutputStream.close ();
            }
            catch (final IOException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Could not reset underlying Data OutputStream.  Reason : %s", e.toString ());
            }

            m_dataOutputStream = null;
        }

        return;
    }

    private void computeAndSetDataInputStream ()
    {
        if (null != m_dataInputStream)
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
            m_dataInputStream = new DataInputStream (m_socket.getInputStream ());
        }
        catch (final IOException e)
        {
            WaveAssertUtils.waveAssert ();
        }
    }

    private void resetDataInputStream ()
    {
        if (null != m_dataInputStream)
        {
            try
            {
                m_dataInputStream.close ();
            }
            catch (final IOException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Could not reset underlying Data InputStream.  Reason : %s", e.toString ());
            }

            m_dataInputStream = null;
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
        computeAndSetDataInputStream ();
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
            computeAndSetDataInputStream ();
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
            computeAndSetDataInputStream ();
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

    public boolean send (final UI32 value)
    {
        return (send (value.getValue ()));
    }

    public boolean send (final int value)
    {
        if (!(isValid ()))
        {
            return (false);
        }

        int status = 0;

        try
        {
            m_dataOutputStream.writeInt (value);

            status = 4;
        }
        catch (final IOException e)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Failed to send integer : %s", e.toString ());

            status = -1;
        }

        return (status != -1 ? true : false);
    }

    public boolean send (final FixedSizeBuffer fixedSizeBuffer)
    {
        if (true != (isValid ()))
        {
            return (false);
        }

        final UI32 fixedSizeBufferSize = fixedSizeBuffer.getMaximumSize ();
        final byte[] buffer = fixedSizeBuffer.getRawBuffer ();
        boolean sendStatus = false;

        if (null != buffer)
        {
            sendStatus = send (fixedSizeBufferSize);

            if (false == sendStatus)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "ClientStreamingSocket.send (final FixedSizeBuffer fixedSizeBuffer) : Status : %d", sendStatus);
                return (sendStatus);
            }

            try
            {
                m_dataOutputStream.write (fixedSizeBuffer.getRawBuffer (), 0, (fixedSizeBuffer.getCurrentSize ()).getValue ());

                sendStatus = true;
            }
            catch (final IOException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Failed to send FixedSizeBuffer : %s", e.toString ());

                sendStatus = false;
            }

            return (sendStatus);
        }
        else
        {
            return (false);
        }
    }

    public boolean send (final byte[] buffer)
    {
        return (send (buffer, buffer.length));
    }

    public boolean send (final byte[] buffer, final int maximumBufferLength)
    {
        if (true != (isValid ()))
        {
            return (false);
        }

        boolean sendStatus = false;

        if (null != buffer)
        {
            sendStatus = send (maximumBufferLength);

            if (false == sendStatus)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "ClientStreamingSocket.send (final FixedSizeBuffer fixedSizeBuffer) : Status : %d", sendStatus);
                return (sendStatus);
            }

            try
            {
                m_dataOutputStream.write (buffer, 0, maximumBufferLength);

                sendStatus = true;
            }
            catch (final IOException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Failed to send buffer : %s", e.toString ());

                sendStatus = false;
            }

            return (sendStatus);
        }
        else
        {
            return (false);
        }
    }

    public boolean send (final byte[] buffer, final int offset, final int length)
    {
        if (true != (isValid ()))
        {
            return (false);
        }

        boolean sendStatus = false;

        if (null != buffer)
        {
            sendStatus = send (length);

            if (false == sendStatus)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "ClientStreamingSocket.send (final FixedSizeBuffer fixedSizeBuffer) : Status : %d", sendStatus);
                return (sendStatus);
            }

            try
            {
                m_dataOutputStream.write (buffer, offset, length);

                sendStatus = true;
            }
            catch (final IOException e)
            {
                WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Failed to send buffer : %s", e.toString ());

                sendStatus = false;
            }

            return (sendStatus);
        }
        else
        {
            return (false);
        }
    }

    public boolean send (final String value)
    {
        if (!(isValid ()))
        {
            return (false);
        }

        boolean status = false;

        try
        {
            m_dataOutputStream.writeBytes (value);

            status = true;
        }
        catch (final IOException e)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Failed to send String : %s", e.toString ());

            status = false;
        }

        return (status);
    }

    public boolean send (final WaveMessage waveMessage)
    {
        WaveAssertUtils.waveAssert (null != waveMessage);

        final StringBuffer bufferToPost = new StringBuffer ();

        waveMessage.serializeTo (bufferToPost);

        final UI32 bufferSize = new UI32 (bufferToPost.length ());
        final UI32 numberOfBuffers = waveMessage.getNumberOfBuffers ();

        boolean isSuccessful = false;

        isSuccessful = send (bufferSize);

        if (isSuccessful)
        {
            isSuccessful = send (bufferToPost.toString ());

            if (isSuccessful)
            {
                isSuccessful = send (numberOfBuffers);
            }
        }

        if (isSuccessful)
        {
            final Vector<UI32> bufferTags = new Vector<UI32> ();

            waveMessage.getBufferTags (bufferTags);

            for (final UI32 bufferTag : bufferTags)
            {
                isSuccessful = send (bufferTag);

                if (isSuccessful)
                {
                    final byte[] buffer = waveMessage.findBuffer (bufferTag);

                    WaveAssertUtils.waveAssert (null != buffer);

                    isSuccessful = send (buffer);

                    if (!isSuccessful)
                    {
                        break;
                    }
                }
            }
        }

        return (isSuccessful);
    }

    public int receive (final byte[] buffer)
    {
        if (!(isValid ()))
        {
            return (-1);
        }

        int status = 0;

        try
        {
            status = m_dataInputStream.read (buffer);
        }
        catch (final IOException e)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Failed to read Buffer : %s", e.toString ());

            status = -1;
        }

        return (status);
    }

    public int receive (final byte[] buffer, final int offset, final int length)
    {
        if (!(isValid ()))
        {
            return (-1);
        }

        int status = 0;

        try
        {
            status = m_dataInputStream.read (buffer, offset, length);
        }
        catch (final IOException e)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Failed to read Buffer : %s", e.toString ());

            status = -1;
        }

        return (status);
    }

    public int receiveAll (final byte[] buffer)
    {
        if (!(isValid ()))
        {
            return (-1);
        }

        int status = 0;

        try
        {
            m_dataInputStream.readFully (buffer);

            status = buffer.length;
        }
        catch (final IOException e)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, "Failed to read Buffer Fully : %s", e.toString ());

            status = -1;
        }

        return (status);
    }

    public int receiveAll (final FixedSizeBuffer fixedSizeBuffer)
    {
        final int status = receiveAll (fixedSizeBuffer.getRawBuffer ());

        return (status);
    }

    public int recieve (final FixedSizeBuffer fixedSizeBuffer)
    {
        final int status = receive (fixedSizeBuffer.getRawBuffer (), (fixedSizeBuffer.getCurrentSize ()).getValue (), (fixedSizeBuffer.getRemainingSize ()).getValue ());

        return (status);
    }
}
