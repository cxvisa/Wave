/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Socket;

import java.net.Socket;

public class AcceptedStreamingSocket extends ClientStreamingSocket
{
    public AcceptedStreamingSocket (final Socket socket)
    {
        super (socket);
    }
}
