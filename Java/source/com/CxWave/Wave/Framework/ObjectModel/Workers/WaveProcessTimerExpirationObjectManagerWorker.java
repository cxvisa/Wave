/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel.Workers;

import com.CxWave.Wave.Framework.Core.Messages.WaveTimerExpiredObjectManagerMessage;
import com.CxWave.Wave.Framework.ObjectModel.WaveElement;
import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveTimerExpirationHandler;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Framework.ObjectModel.WaveWorkerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.Cardinality;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.OwnerOM;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.WorkerPriority;
import com.CxWave.Wave.Framework.Type.TimerHandle;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;

@OwnerOM (om = WaveObjectManager.class)
@Cardinality (1)
@WorkerPriority (WaveWorkerPriority.WAVE_WORKER_PRIORITY_0)
public class WaveProcessTimerExpirationObjectManagerWorker extends WaveWorker
{

    public WaveProcessTimerExpirationObjectManagerWorker (final WaveObjectManager waveObjectManager)
    {
        super (waveObjectManager);
    }

    private void timerExpiredRequestHandler (final WaveTimerExpiredObjectManagerMessage waveTimerExpiredObjectManagerMessage)
    {
        infoTracePrintf ("WaveProcessTimerExpirationObjectManagerWorker.timerExpiredRequestHandler : Entering for OM %s", (getWaveObjectManager ()).getName ());

        waveAssert (null != waveTimerExpiredObjectManagerMessage);

        final TimerHandle timerId = waveTimerExpiredObjectManagerMessage.getTimerId ();
        final WaveElement timerSender = waveTimerExpiredObjectManagerMessage.getWaveTimerSender ();
        final WaveTimerExpirationHandler timerExpirationHandler = waveTimerExpiredObjectManagerMessage.getWaveTimerExpirationCallback ();
        final Object timerExpirationContext = waveTimerExpiredObjectManagerMessage.getWaveTimerExpirationContext ();

        waveAssert (null != timerId);
        waveAssert (null != timerSender);
        waveAssert (null != timerExpirationHandler);

        waveTimerExpiredObjectManagerMessage.setCompletionStatus (ResourceId.WAVE_MESSAGE_SUCCESS);
        reply (waveTimerExpiredObjectManagerMessage);

        timerExpirationHandler.validateAndCompute (timerSender);

        timerExpirationHandler.execute (timerId, timerExpirationContext);
    }
}
