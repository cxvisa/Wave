/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.HttpInterface;

import java.util.HashMap;
import java.util.Map;

import com.CxWave.Wave.Framework.Boot.BootCompleteForThisLocationEvent;
import com.CxWave.Wave.Framework.LocationManagement.ServerStreamingSocketStatus;
import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManagerForUserSpecificTasks;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.ObjectManagerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Boot.WaveAsynchronousContextForBootPhases;
import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Socket.AcceptedStreamingSocket;
import com.CxWave.Wave.Framework.Utils.Socket.ServerStreamingSocket;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.WaveHttpInterfaceMethod;
import com.CxWave.Wave.Resources.ResourceEnums.WaveObjectManagerPriority;

@ObjectManagerPriority (WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_HTTP_INTERFACE)
public class HttpInterfaceReceiverObjectManager extends WaveLocalObjectManagerForUserSpecificTasks
{
    private static HttpInterfaceReceiverObjectManager                      s_httpHttpInterfaceReceiverObjectManager = null;
    private static Map<WaveHttpInterfaceMethod, HttpInterfaceMethodWorker> m_httpInterfaceMethodWorkers             = new HashMap<WaveHttpInterfaceMethod, HttpInterfaceMethodWorker> ();
    private ServerStreamingSocket                                          m_serverSocketForHttpInterfaceClients    = null;
    private HttpInterfaceGetWorker                                         m_httpInterfaceGetWorker                 = null;

    public HttpInterfaceReceiverObjectManager ()
    {
        super (getServiceName ());

        setAllowAutomaticallyUnlistenForEvents (false);

        m_httpInterfaceGetWorker = new HttpInterfaceGetWorker (this);

        waveAssert (null != m_httpInterfaceGetWorker);
    }

    public static String getServiceName ()
    {
        return ("HTTP Interface");
    }

    public static HttpInterfaceReceiverObjectManager getInstance ()
    {
        if (null == s_httpHttpInterfaceReceiverObjectManager)
        {
            s_httpHttpInterfaceReceiverObjectManager = new HttpInterfaceReceiverObjectManager ();
        }

        WaveAssertUtils.waveAssert (null != s_httpHttpInterfaceReceiverObjectManager);

        return (s_httpHttpInterfaceReceiverObjectManager);
    }

    public static WaveServiceId getWaveServiceId ()
    {
        return ((getInstance ()).getServiceId ());
    }

    public static boolean isAKnownHttpInterfaceMethod (final WaveHttpInterfaceMethod waveHttpInterfaceMethod)
    {
        return (m_httpInterfaceMethodWorkers.containsKey (waveHttpInterfaceMethod));
    }

    public static HttpInterfaceMethodWorker getHttpInterfaceMethodWorker (final WaveHttpInterfaceMethod waveHttpInterfaceMethod)
    {
        return (m_httpInterfaceMethodWorkers.get (waveHttpInterfaceMethod));
    }

    public static void addHttpInterfaceMethodWorker (final WaveHttpInterfaceMethod waveHttpInterfaceMethod, final HttpInterfaceMethodWorker httpInterfaceMethodWorker)
    {
        if (false == (isAKnownHttpInterfaceMethod (waveHttpInterfaceMethod)))
        {
            m_httpInterfaceMethodWorkers.put (waveHttpInterfaceMethod, httpInterfaceMethodWorker);
        }
        else
        {
            WaveAssertUtils.waveAssert ();
        }
    }

    @Override
    public void initialize (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        ServerStreamingSocketStatus status = ServerStreamingSocketStatus.SERVER_STREAMING_SOCKET_SUCCESS;

        m_serverSocketForHttpInterfaceClients = new ServerStreamingSocket (FrameworkToolKit.getHttpInterfaceReceiverPort ());

        waveAssert (null != m_serverSocketForHttpInterfaceClients);

        status = m_serverSocketForHttpInterfaceClients.getStatus ();

        ResourceId initializeStatus = ResourceId.WAVE_MESSAGE_ERROR;

        if (ServerStreamingSocketStatus.SERVER_STREAMING_SOCKET_SUCCESS != status)
        {
            errorTracePrintf ("HttpInterfaceReceiverObjectManager::initialize : Could not bind to the HTTP Interface Receiver Port.  Please make sure that this port is not used by any other application.  Otherwise specify a different port for this purpose.");

            initializeStatus = ResourceId.WAVE_MESSAGE_ERROR;
        }
        else
        {
            infoTracePrintf ("HttpInterfaceReceiverObjectManager::initialize : Successfully bound to the HTTP Interface Receiver Port.");

            initializeStatus = ResourceId.WAVE_MESSAGE_SUCCESS;
        }

        waveAsynchronousContextForBootPhases.setCompletionStatus (initializeStatus);
        waveAsynchronousContextForBootPhases.callback ();
    }

    @Override
    public void boot (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        waveAsynchronousContextForBootPhases.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        waveAsynchronousContextForBootPhases.callback ();
    }

    void bootCompleteForThisLocationEventHandler (final BootCompleteForThisLocationEvent bootCompleteForThisLocationEvent)
    {
        // Since we told framework not to unlistenEvents, we must explicitly unlisten for events since we are going to go into
        // an infinite while loop.

        unlistenEvents ();

        infoTracePrintf ("HttpInterfaceReceiverObjectManager::bootCompleteForThisLocationEventHandler : Now accepting connections from Wave Clients.");

        for (;;)
        {
            final AcceptedStreamingSocket acceptedStreamingSocket = m_serverSocketForHttpInterfaceClients.accept ();

            waveAssert (null != acceptedStreamingSocket);

            if (!(acceptedStreamingSocket.isValid ()))
            {
                infoTracePrintf ("HttpInterfaceReceiverObjectManager::bootCompleteForThisLocationEventHandler : Could not accept connection from a new HTTP Interface Client.  This could be because of an unwanted Client arbitrarily trying to connect to us.");

                continue;
            }

            infoTracePrintf ("HttpInterfaceReceiverObjectManager::bootCompleteForThisLocationEventHandler : Accepted A NEW connection From : " + acceptedStreamingSocket.getPeerIpAddress ());

            acceptedStreamingSocket.close ();
        }
    }
}
