/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Messaging.MessageFactory;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.MultiThreading.WaveThread;
import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;

public class WaveMessageFactory
{
    private WaveMessageFactory ()
    {
    }

    public static WaveMessage getMessageInstance (final WaveServiceId serviceId, final UI32 opcode)
    {
        final WaveObjectManager waveObjectManager = getWaveObjectManagerForMessage (serviceId, opcode);
        WaveMessage waveMessage = null;

        if (null != waveObjectManager)
        {
            waveMessage = waveObjectManager.createMessageInstanceWrapper (opcode);
        }

        if (null == waveMessage)
        {
            WaveTraceUtils.fatalTracePrintf ("WaveMessageFactory::getMessageInstance : Could not create message instance for  Service : %s, Opcode = %d", FrameworkToolKit.getServiceNameById (serviceId), opcode.getValue ());
            WaveTraceUtils.fatalTracePrintf ("WaveMessageFactory::getMessageInstance : Have you implemented the createMessageInstance on the object manager yet???.");
            WaveTraceUtils.fatalTracePrintf ("WaveMessageFactory::getMessageInstance : Also, Please make sure that the opcode has been registered using addOperationMap on the corresponding Object Manager.");

            WaveAssertUtils.waveAssert (false);
        }

        return (waveMessage);
    }

    private static WaveObjectManager getWaveObjectManagerForMessage (final WaveServiceId serviceId, final UI32 opcode)
    {
        WaveThread waveThread = null;
        WaveObjectManager waveObjectManager = null;

        waveThread = WaveThread.getWaveThreadForServiceId (serviceId);

        if (null != waveThread)
        {
            waveObjectManager = waveThread.getWaveObjectManagerForOperationCode (opcode);
        }

        return (waveObjectManager);
    }

    public static WaveObjectManager getWaveObjectManagerForEvent (final WaveServiceId serviceId, final UI32 eventOpcode)
    {
        WaveThread waveThread = null;
        WaveObjectManager waveObjectManager = null;

        waveThread = WaveThread.getWaveThreadForServiceId (serviceId);

        if (null != waveThread)
        {
            waveObjectManager = waveThread.getWaveObjectManagerForEventOperationCode (eventOpcode);
        }

        return (waveObjectManager);
    }
}
