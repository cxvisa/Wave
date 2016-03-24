/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.HttpInterface;

import com.CxWave.Wave.Resources.ResourceEnums.WaveHttpInterfaceMethod;

public class HttpInterfaceGetWorker extends HttpInterfaceMethodWorker
{

    public HttpInterfaceGetWorker (final HttpInterfaceReceiverObjectManager httpInterfaceReceiverObjectManager)
    {
        super (httpInterfaceReceiverObjectManager, WaveHttpInterfaceMethod.WAVE_HTTP_INTERFACE_METHOD_GET);
    }

    @Override
    public void process (final HttpRequest httpReuest)
    {
    }
}
