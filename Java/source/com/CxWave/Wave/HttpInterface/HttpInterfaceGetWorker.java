/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.HttpInterface;

import com.CxWave.Wave.Framework.Utils.Socket.AcceptedStreamingSocket;
import com.CxWave.Wave.Resources.ResourceEnums.WaveHttpInterfaceMethod;

public class HttpInterfaceGetWorker extends HttpInterfaceMethodWorker
{

    public HttpInterfaceGetWorker (final HttpInterfaceReceiverObjectManager httpInterfaceReceiverObjectManager)
    {
        super (httpInterfaceReceiverObjectManager, WaveHttpInterfaceMethod.WAVE_HTTP_INTERFACE_METHOD_GET);
    }

    @Override
    public void process (final HttpRequest httpRequest)
    {
        final String uri = httpRequest.getUri ();
        final WaveServerPage waveServerPage = WaveServerPageDirectory.getWaveServerPage (uri);
        final AcceptedStreamingSocket acceptedStreamingSocket = httpRequest.getAcceptedStreamingSocket ();

        if (null == waveServerPage)
        {
            final StringBuffer httpResponse = new StringBuffer ();

            debugTracePrintf ("HttpInterfaceGetWorker.process : There is no page registered with the given path \"%s\"", uri);

            HttpToolKit.getNotFoundErrorString (httpResponse);

            if (null != acceptedStreamingSocket)
            {
                acceptedStreamingSocket.send (httpResponse);
            }
        }
        else
        {
            debugTracePrintf ("HttpInterfaceGetWorker.process : Serving get for \"%s\"", uri);

            waveServerPage.get (httpRequest);
        }
    }
}
