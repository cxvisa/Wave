/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.LightHouse;

import java.util.Set;

import com.CxWave.Wave.Framework.Core.Messages.WaveDeliverLightPulseMessage;
import com.CxWave.Wave.Framework.Messaging.MessageFactory.WaveMessageFactory;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorkerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.Cardinality;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.OwnerOM;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.WorkerPriority;
import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;
import com.CxWave.Wave.Resources.ResourceEnums.WaveMessageStatus;

@OwnerOM (om = LightPulseDispatchObjectManager.class)
@Cardinality (1)
@WorkerPriority (WaveWorkerPriority.WAVE_WORKER_PRIORITY_0)
public class LightPulseDispatchWorker extends WaveWorker
{
    public LightPulseDispatchWorker (final LightPulseDispatchObjectManager lightPulseDispatchObjectManager)
    {
        super (lightPulseDispatchObjectManager);
    }

    private void dispatchReceivedLightPulseMessageHandler (final LightPulseDispatchMessage lightPulseDispatchMessage)
    {
        infoTracePrintf ("LightPulseDispatchWorker.dispatchReceivedLightPulseMessageHandler : Receied a light Pulse : %s", lightPulseDispatchMessage.getLightPulseSerializedString ());

        waveAssert (null != lightPulseDispatchMessage);

        final String seralizedLightPulseString = lightPulseDispatchMessage.getLightPulseSerializedString ();

        trace (TraceLevel.TRACE_LEVEL_DEVEL, "LightPulseDispatchWorker.dispatchReceivedLightPulseMessageHandler : Dispatching a Light Pulse ...\r\n" + seralizedLightPulseString);

        final String lightPulseName = LightPulse.getLightPulseName (seralizedLightPulseString);

        trace (TraceLevel.TRACE_LEVEL_DEVEL, "LightPulseDispatchWorker.dispatchReceivedLightPulseMessageHandler : Light Pulse Name : " + lightPulseName);

        final LightPulse lightPulse = WaveMessageFactory.getLightPulseInstance (lightPulseName);

        if (null == lightPulse)
        {
            trace (TraceLevel.TRACE_LEVEL_FATAL, "LightPulseDispatchWorker.dispatchReceivedLightPulseMessageHandler : Please have the corresponding Object Manager implement  createLightPulseInstance for : " + lightPulseName);
            waveAssert (false);
        }

        lightPulse.loadFromSerializedData2 (seralizedLightPulseString);

        final LightPulseRegistrationRepository lightPulseRegistrationRepository = LightPulseRegistrationRepository.getInstance ();

        waveAssert (null != lightPulseRegistrationRepository);

        final Set<WaveServiceId> servicesRegisteredForLightPulse = lightPulseRegistrationRepository.getLightPulseRecepientsForLightPulseName (lightPulseName);

        for (final WaveServiceId waveServiceId : servicesRegisteredForLightPulse)
        {
            final WaveDeliverLightPulseMessage waveDeliverLightPulseMessage = new WaveDeliverLightPulseMessage (waveServiceId);

            waveDeliverLightPulseMessage.setLightPulse (lightPulse);

            final WaveMessageStatus sendStatus = sendOneWay (waveDeliverLightPulseMessage);

            if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS != sendStatus)
            {
                tracePrintf (TraceLevel.TRACE_LEVEL_ERROR, true, false, "LightPulseDispatchWorker.dispatchReceivedLightPulseMessageHandler Could not deliver Light Pulse of type %s to service : %s, status : %s", lightPulseName, FrameworkToolKit.getServiceNameById (waveServiceId), FrameworkToolKit.localize (sendStatus));
            }
            else
            {
                tracePrintf (TraceLevel.TRACE_LEVEL_DEVEL, true, false, "LightPulseDispatchWorker.dispatchReceivedLightPulseMessageHandler : Trying to deliver Light Pulse of type %s to service : %s", lightPulseName, FrameworkToolKit.getServiceNameById (waveServiceId));
            }
        }

        lightPulseDispatchMessage.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        reply (lightPulseDispatchMessage);
    }
}
