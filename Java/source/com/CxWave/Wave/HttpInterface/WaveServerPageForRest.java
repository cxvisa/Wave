/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.HttpInterface;

import com.CxWave.Wave.Framework.Utils.Socket.AcceptedStreamingSocket;

public class WaveServerPageForRest extends WaveServerPage
{

    public WaveServerPageForRest (final HttpInterfaceReceiverObjectManager httpInterfaceReceiverObjectManager, final String path)
    {
        super (httpInterfaceReceiverObjectManager, path);
    }

    @Override
    public void get (final HttpRequest httpRequest)
    {
        requestHandlerForGet (httpRequest);
    }

    @Override
    public void requestHandlerForGet (final HttpRequest httpRequest)
    {
        final StringBuffer httpResponse = new StringBuffer ();
        final AcceptedStreamingSocket acceptedStreamingSocket = httpRequest.getAcceptedStreamingSocket ();

        HttpToolKit.getOkStringForGetForRestXml (httpResponse, "");

        if (null != acceptedStreamingSocket)
        {
            acceptedStreamingSocket.send (httpResponse);
        }
    }
}
