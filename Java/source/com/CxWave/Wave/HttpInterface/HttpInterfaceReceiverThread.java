/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.HttpInterface;

import com.CxWave.Wave.Framework.MultiThreading.WaveThreadBase;
import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
import com.CxWave.Wave.Framework.Utils.Socket.AcceptedStreamingSocket;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.WaveHttpContentType;
import com.CxWave.Wave.Resources.ResourceEnums.WaveHttpInterfaceMethod;

public class HttpInterfaceReceiverThread extends WaveThreadBase
{
    private AcceptedStreamingSocket m_acceptedStreamingSocket = null;

    public HttpInterfaceReceiverThread (final AcceptedStreamingSocket acceptedStreamingSocket)
    {
        super ("HttpInterfaceReceiverThread - " + acceptedStreamingSocket.getPeerIpAddress ());

        m_acceptedStreamingSocket = acceptedStreamingSocket;
    }

    @Override
    public void run ()
    {
        WaveTraceUtils.infoTracePrintf ("HttpInterfaceReceiverThread::start : Starting ...");

        final AcceptedStreamingSocket acceptedSocket = m_acceptedStreamingSocket;
        StringBuffer httpRequestPhase1 = null;
        int numberOfBytesRead = 0;
        final StringBuffer httpResponsePhase1;
        final WaveHttpInterfaceMethod waveHttpInterfaceMethod;
        final HttpInterfaceMethodWorker httpInterfaceMethodWorker = null;
        final String authorization;
        final String decodedAuthorization;
        int contentLength = 0;
        final WaveHttpContentType contentType;
        final String contentBoundary;
        final String content;
        boolean isContentReadIncomplete = false;
        int i = 0;
        int numberOfEntities = 0;
        String entityName;
        String entityValue;
        String entityFileName;
        String uri;

        final byte[] inputBuffer = new byte[512];

        numberOfBytesRead = acceptedSocket.receive (inputBuffer);

        httpRequestPhase1 = new StringBuffer ();

        if (-1 != numberOfBytesRead)
        {
            final String tempString = new String (inputBuffer, 0, numberOfBytesRead);

            WaveTraceUtils.infoTracePrintf ("HttpInterfaceReceiverThread::start : Received Data for Phase 1:\r\n_____\r\n%s\r\n_____\r\n", tempString);

            httpRequestPhase1.append (tempString);
        }
        else
        {
            WaveTraceUtils.errorTracePrintf ("HttpInterfaceReceiverThread::start : Could not receive data for Phase 1.");
        }

        final HttpRequest httpRequest = new HttpRequest (httpRequestPhase1, m_acceptedStreamingSocket);

        waveHttpInterfaceMethod = httpRequest.getWaveHttpInterfaceMethod ();
        uri = httpRequest.getUri ();
        authorization = httpRequest.getAuthorization ();
        contentLength = httpRequest.getContentLength ();
        contentType = httpRequest.getContentType ();
        contentBoundary = httpRequest.getContentBoundary ();
        content = httpRequest.getContent ();
        isContentReadIncomplete = httpRequest.getIsContentReadIncomplete ();
        numberOfEntities = httpRequest.getNumberOfEntities ();

        WaveTraceUtils.infoTracePrintf ("HttpInterfaceReceiverThread::start : URI                = " + uri);

        if (0 != contentLength)
        {
            WaveTraceUtils.infoTracePrintf ("HttpInterfaceReceiverThread::start : Content Length     = " + contentLength);
            WaveTraceUtils.infoTracePrintf ("HttpInterfaceReceiverThread::start : Content Type       = " + (FrameworkToolKit.localize (contentType)));
            WaveTraceUtils.infoTracePrintf ("HttpInterfaceReceiverThread::start : Content Boundary   = " + contentBoundary);

            WaveTraceUtils.infoTracePrintf ("HttpInterfaceReceiverThread::start : Content:\r\n_____\r\n" + content + "\r\n_____\r\n");
        }

        WaveTraceUtils.infoTracePrintf ("HttpInterfaceReceiverThread::start : Number of Entities = %d", numberOfEntities);

        for (i = 0; i < numberOfEntities; i++)
        {
            entityName = "";
            entityValue = "";
            entityFileName = "";

            entityName = httpRequest.getEntityNameAtIndex (i);
            entityValue = httpRequest.getEntityValueAtIndex (i);
            entityFileName = httpRequest.getEntityFileNameAtIndex (i);

            WaveTraceUtils.infoTracePrintf ("HttpInterfaceReceiverThread::start : \"" + entityName + "(" + entityFileName + ")\" = ***\"" + entityValue + "\"***");
        }

        if (null != m_acceptedStreamingSocket)
        {
            m_acceptedStreamingSocket.close ();
        }
    }
}
