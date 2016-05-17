/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.LightHouse;

import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorkerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.Cardinality;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.OwnerOM;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.WorkerPriority;
import com.CxWave.Wave.Framework.Utils.Socket.MulticastSenderSocket;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

@OwnerOM (om = LightHouseTransportObjectManager.class)
@Cardinality (1)
@WorkerPriority (WaveWorkerPriority.WAVE_WORKER_PRIORITY_0)
public class LightHouseTransportBroadcastLightPulseWorker extends WaveWorker
{
    private final MulticastSenderSocket m_multicastSenderSocket;

    public LightHouseTransportBroadcastLightPulseWorker (final LightHouseTransportObjectManager lightHouseTransportObjectManager)
    {
        super (lightHouseTransportObjectManager);

        m_multicastSenderSocket = new MulticastSenderSocket (LightHouseToolKit.getLightHouseMulticastIpAddress (), LightHouseToolKit.getLightHouseMulticastPort ());

        waveAssert (null != m_multicastSenderSocket);
        waveAssert (m_multicastSenderSocket.isValid ());
    }

    private void broadcastLightPulseMessageHandler (final LightHouseTransportBroadcastLightPulseMessage lightHouseTransportBroadcastLightPulseMessage)
    {
        trace (TraceLevel.TRACE_LEVEL_DEVEL, "LightHouseTransportBroadcastLightPulseWorker.broadcastLightPulseMessageHandler : Entering ...");

        waveAssert (null != lightHouseTransportBroadcastLightPulseMessage);

        final LightPulse lightPulse = lightHouseTransportBroadcastLightPulseMessage.getLightPulse ();

        waveAssert (null != lightPulse);

        final StringBuffer serializedLightPulseStringBuffer = new StringBuffer ();

        lightPulse.serializeTo (serializedLightPulseStringBuffer);

        m_multicastSenderSocket.send (serializedLightPulseStringBuffer);

        lightHouseTransportBroadcastLightPulseMessage.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        reply (lightHouseTransportBroadcastLightPulseMessage);
    }
}
