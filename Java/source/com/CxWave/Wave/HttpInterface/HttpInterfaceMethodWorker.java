/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.HttpInterface;

import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Resources.ResourceEnums.WaveHttpInterfaceMethod;

public abstract class HttpInterfaceMethodWorker extends WaveWorker
{
    private WaveHttpInterfaceMethod m_waveHttpInterfaceMethod = WaveHttpInterfaceMethod.WAVE_HTTP_INTERFACE_METHOD_UNKNOWN;

    public HttpInterfaceMethodWorker (final HttpInterfaceReceiverObjectManager httpInterfaceReceiverObjectManager, final WaveHttpInterfaceMethod waveHttpInterfaceMethod)
    {
        super (httpInterfaceReceiverObjectManager);

        m_waveHttpInterfaceMethod = waveHttpInterfaceMethod;

        HttpInterfaceReceiverObjectManager.addHttpInterfaceMethodWorker (waveHttpInterfaceMethod, this);
    }

    public WaveHttpInterfaceMethod getWaveHttpInterfaceMethod ()
    {
        return (m_waveHttpInterfaceMethod);
    }

    public abstract void process (HttpRequest httpReuest);
}
