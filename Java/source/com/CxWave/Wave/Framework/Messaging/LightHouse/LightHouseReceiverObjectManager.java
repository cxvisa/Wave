/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.LightHouse;

import java.util.Vector;

import com.CxWave.Wave.Framework.Boot.BootCompleteForThisLocationEvent;
import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManagerForUserSpecificTasks;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.ObjectManagerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Boot.WaveAsynchronousContextForBootPhases;
import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
import com.CxWave.Wave.Framework.Type.SI32;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Buffer.FixedSizeBuffer;
import com.CxWave.Wave.Framework.Utils.Socket.MulticastReceiverSocket;
import com.CxWave.Wave.Framework.Utils.Socket.MulticastSenderSocket;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;
import com.CxWave.Wave.Resources.ResourceEnums.WaveMessageStatus;
import com.CxWave.Wave.Resources.ResourceEnums.WaveObjectManagerPriority;
import com.CxWave.Wave.Shell.ShellDebug;
import com.CxWave.Wave.Shell.Annotations.ShellCommand;

@ObjectManagerPriority (WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_LIGHT_HOUSE_RECEIVER)
public class LightHouseReceiverObjectManager extends WaveLocalObjectManagerForUserSpecificTasks
{
    private static LightHouseReceiverObjectManager m_lightHouseReceiverObjectManager = null;

    private MulticastReceiverSocket                m_multicastReceiverSocket         = null;

    public LightHouseReceiverObjectManager ()
    {
        super (getServiceName ());

        setAllowAutomaticallyUnlistenForEvents (false);
    }

    public static String getServiceName ()
    {
        return ("Light House Receiver");
    }

    public static LightHouseReceiverObjectManager getInstance ()
    {
        if (null == m_lightHouseReceiverObjectManager)
        {
            m_lightHouseReceiverObjectManager = new LightHouseReceiverObjectManager ();
        }

        WaveAssertUtils.waveAssert (null != m_lightHouseReceiverObjectManager);

        return (m_lightHouseReceiverObjectManager);
    }

    public static WaveServiceId getWaveServiceId ()
    {
        return ((getInstance ()).getServiceId ());
    }

    @Override
    public void initialize (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        m_multicastReceiverSocket = new MulticastReceiverSocket (LightHouseToolKit.getLightHouseMulticastIpAddress (), LightHouseToolKit.getLightHouseMulticastPort ());

        waveAsynchronousContextForBootPhases.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        waveAsynchronousContextForBootPhases.callback ();
    }

    @Override
    public void boot (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        waveAsynchronousContextForBootPhases.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        waveAsynchronousContextForBootPhases.callback ();
    }

    @Override
    public void listenForEvents (final WaveAsynchronousContextForBootPhases waveAsynchronousContextForBootPhases)
    {
        waveAsynchronousContextForBootPhases.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        waveAsynchronousContextForBootPhases.callback ();
    }

    private void bootCompleteForThisLocationEventHandler (final BootCompleteForThisLocationEvent bootCompleteForThisLocationEvent)
    {
        unlistenEvents ();

        infoTracePrintf ("LightHouseReceiverObjectManager.bootCompleteForThisLocationEventHandler : Entering ...");

        reply (bootCompleteForThisLocationEvent);

        trace (TraceLevel.TRACE_LEVEL_INFO, "LightHouseReceiverObjectManager.bootCompleteForThisLocationEventHandler : Now accepting connections from Wave Clients.");

        for (;;)
        {
            final int maximumBufferSizeToRead = 4096;

            final FixedSizeBuffer fixedSizeBuffer = new FixedSizeBuffer (new UI32 (maximumBufferSizeToRead + 1));
            final StringBuffer from = new StringBuffer ();
            final SI32 port = new SI32 (0);

            final boolean status = m_multicastReceiverSocket.receive (fixedSizeBuffer, from, port);
            final String lightPulseString;

            lightPulseString = fixedSizeBuffer.toString ();

            if (true == status)
            {
                // trace (TRACE_LEVEL_INFO, string ("LightHouseReceiverObjectManager.bootCompleteForThisLocationEventHandler :
                // Received a Light Pulse : ") + lightPulseString + ", from : " + from + ", port : " + port);

                final LightPulseDispatchMessage lightPulseDispatchMessage = new LightPulseDispatchMessage ();

                waveAssert (null != lightPulseDispatchMessage);

                lightPulseDispatchMessage.setLightPulseSerializedString (lightPulseString);
                lightPulseDispatchMessage.setSenderIpAddress (from.toString ());
                lightPulseDispatchMessage.setSenderPort (port);

                final WaveMessageStatus sendStatus = sendOneWay (lightPulseDispatchMessage);

                if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != sendStatus)
                {
                    trace (TraceLevel.TRACE_LEVEL_ERROR, "LightHouseReceiverObjectManager.bootCompleteForThisLocationEventHandler : Error in sending message to dispatch a light pulse.  Status : " + FrameworkToolKit.localize (sendStatus));
                    trace (TraceLevel.TRACE_LEVEL_ERROR, "LightHouseReceiverObjectManager.bootCompleteForThisLocationEventHandler : Errored Light Pulse : \n" + lightPulseString);
                }
            }
        }
    }

    @ShellCommand (shell = ShellDebug.class, briefHelp = "Sends a muticast packet to the specified multicast group and port.")
    public static void sendMessageToMulticastGroup (final Vector<String> arguments)
    {
        if (3 <= (arguments.size ()))
        {
            final String groupAddress = arguments.get (0);
            final int port = Integer.valueOf (arguments.get (1));
            final String dataToSend = arguments.get (2);

            final MulticastSenderSocket muilticastSenderSocket = new MulticastSenderSocket (groupAddress, port);

            final boolean status = muilticastSenderSocket.send (dataToSend);

            if (true == status)
            {
                WaveTraceUtils.successTracePrintf ("LightHouseReceiverObjectManager.sendMessageToMulticastGroup : Successfully sent %s to %s : %d", dataToSend, groupAddress, port);
            }
            else
            {
                WaveTraceUtils.errorTracePrintf ("LightHouseReceiverObjectManager.sendMessageToMulticastGroup : Failed to send %s to %s : %d", dataToSend, groupAddress, port);
            }
        }
    }

    @ShellCommand (shell = ShellDebug.class, briefHelp = "Receives a muticast packet to the specified multicast group and port.")
    public static void receiveMessageToMulticastGroup (final Vector<String> arguments)
    {
        if (2 <= (arguments.size ()))
        {
            final String groupAddress = arguments.get (0);
            final int port = Integer.valueOf (arguments.get (1));
            final StringBuffer dataToReceive = new StringBuffer ();
            final StringBuffer fromIpAddress = new StringBuffer ();
            final SI32 fromPort = new SI32 (0);

            final MulticastReceiverSocket multicastReceiverSocket = new MulticastReceiverSocket (groupAddress, port);

            final boolean status = multicastReceiverSocket.receive (dataToReceive, fromIpAddress, fromPort);

            if (true == status)
            {
                WaveTraceUtils.successTracePrintf ("LightHouseReceiverObjectManager.receiveMessageToMulticastGroup : Successfully received %s from %s : %d", dataToReceive.toString (), fromIpAddress.toString (), fromPort.intValue ());
            }
            else
            {
                WaveTraceUtils.errorTracePrintf ("LightHouseReceiverObjectManager.receiveMessageToMulticastGroup : Failed to receive from %s : %d", groupAddress, port);
            }
        }
    }
}
