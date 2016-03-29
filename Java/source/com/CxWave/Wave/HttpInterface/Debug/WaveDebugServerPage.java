/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.HttpInterface.Debug;

import com.CxWave.Wave.HttpInterface.HttpInterfaceReceiverObjectManager;
import com.CxWave.Wave.HttpInterface.WaveServerPage;
import com.CxWave.Wave.HttpInterface.Debug.Trace.WaveTraceServerMultiPage;

public class WaveDebugServerPage extends WaveServerPage
{
    public WaveDebugServerPage (final HttpInterfaceReceiverObjectManager httpInterfaceReceiverObjectManager, final String path)
    {
        super (httpInterfaceReceiverObjectManager, path);

        final WaveTraceServerMultiPage waveTraceServerMultiPage = new WaveTraceServerMultiPage (httpInterfaceReceiverObjectManager, "/debug/*/trace");
    }

}
