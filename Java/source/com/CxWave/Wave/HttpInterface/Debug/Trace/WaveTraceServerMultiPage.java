/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.HttpInterface.Debug.Trace;

import com.CxWave.Wave.HttpInterface.HttpInterfaceReceiverObjectManager;
import com.CxWave.Wave.HttpInterface.WaveServerMultiPage;

public class WaveTraceServerMultiPage extends WaveServerMultiPage
{
    public WaveTraceServerMultiPage (final HttpInterfaceReceiverObjectManager httpInterfaceReceiverObjectManager, final String path)
    {
        super (httpInterfaceReceiverObjectManager, path);
    }
}
