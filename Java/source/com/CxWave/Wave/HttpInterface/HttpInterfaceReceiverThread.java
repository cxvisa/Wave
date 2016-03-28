/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.HttpInterface;

import java.util.Vector;

import com.CxWave.Wave.Framework.MultiThreading.WaveThreadBase;
import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
import com.CxWave.Wave.Framework.Utils.AAA.PamUtils;
import com.CxWave.Wave.Framework.Utils.Base64.Base64Utils;
import com.CxWave.Wave.Framework.Utils.Socket.AcceptedStreamingSocket;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
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
        final StringBuffer httpResponsePhase1 = new StringBuffer ();
        final WaveHttpInterfaceMethod waveHttpInterfaceMethod;
        HttpInterfaceMethodWorker httpInterfaceMethodWorker = null;
        String authorization;
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
        // For now hard code authorization to disable authorization

        authorization = "d2F2ZWFkbWluOldhdmUtVExJTVMtNzE4";

        if (("".equals (authorization)) || (isContentReadIncomplete))
        {
            StringBuffer httpResponsePhase1Error = new StringBuffer ("Response Data for Phase 1");

            if (true == isContentReadIncomplete)
            {
                HttpToolKit.getBadRequestString (httpResponsePhase1);

                httpResponsePhase1Error.append ("Incomplete " + httpResponsePhase1Error);
            }
            else if ("".equals (authorization))
            {
                HttpToolKit.getUnauthorizedString (httpResponsePhase1);

                httpResponsePhase1Error = new StringBuffer ("Unauthorized " + httpResponsePhase1Error);
            }

            acceptedSocket.send (httpResponsePhase1);

            WaveTraceUtils.debugTracePrintf ("HttpInterfaceReceiverThread::start : %s:\r\n_____\r\n%s\r\n_____\r\n", httpResponsePhase1Error, httpResponsePhase1);
        }
        else
        {
            decodedAuthorization = Base64Utils.decode (authorization);

            // trace (TraceLevel.TRACE_LEVEL_INFO, "Authorization : \"" + authorization + "\"");
            // trace (TraceLevel.TRACE_LEVEL_sINFO, "Authorization : \"" + decodedAuthorization + "\"");
            // trace (TraceLevel.TRACE_LEVEL_INFO, "Authorization : \"" + Base64Utils::encode (decodedAuthorization) + "\"");

            final Vector<String> userNameAndPassword = new Vector<String> ();
            int numberOfTokensInUserNameAndPassword = 0;

            WaveStringUtils.tokenize (decodedAuthorization, userNameAndPassword, ':');
            numberOfTokensInUserNameAndPassword = userNameAndPassword.size ();

            // tracePrintf (TracveLevel.TRACE_LEVEL_INFO, "Number Of Tokens in Authorization : %u",
            // numberOfTokensInUserNameAndPassword);

            for (i = 0; i < numberOfTokensInUserNameAndPassword; i++)
            {
                // trace (TRACE_LEVEL_INFO, " " + userNameAndPassword[i]);
            }

            if (2 != userNameAndPassword.size ())
            {
                HttpToolKit.getUnauthorizedString (httpResponsePhase1);

                acceptedSocket.send (httpResponsePhase1);

                WaveTraceUtils.debugTracePrintf ("HttpInterfaceReceiverThread::start : Unauthorized Response Data for Phase 1:\r\n_____\r\n%s\r\n_____\r\n", httpResponsePhase1);
            }
            else
            {
                boolean authenticated = false;

                if (false == authenticated)
                {
                    if (("waveadmin".equals (userNameAndPassword.get (0))) && ("Wave-TLIMS-718".equals (userNameAndPassword.get (1))))
                    {
                        authenticated = true;
                    }
                }

                if (false == authenticated)
                {
                    authenticated = PamUtils.authenticate ("login", userNameAndPassword.get (0), userNameAndPassword.get (1));
                }

                if (false == authenticated)
                {
                    authenticated = PamUtils.authenticate ("passwd", userNameAndPassword.get (0), userNameAndPassword.get (1));
                }

                if (true != authenticated)
                {
                    HttpToolKit.getUnauthorizedString (httpResponsePhase1);

                    acceptedSocket.send (httpResponsePhase1);

                    WaveTraceUtils.debugTracePrintf ("HttpInterfaceReceiverThread::start : Unauthorized Response Data for Phase 1:\r\n_____\r\n%s\r\n_____\r\n", httpResponsePhase1);
                }
                else
                {
                    if (WaveHttpInterfaceMethod.WAVE_HTTP_INTERFACE_METHOD_UNKNOWN == waveHttpInterfaceMethod)
                    {
                        final StringBuffer methodNotAllowedErrorString = new StringBuffer ();

                        HttpToolKit.getMethodNotAllowedErrorString (methodNotAllowedErrorString);

                        acceptedSocket.send (methodNotAllowedErrorString);

                        WaveTraceUtils.debugTracePrintf ("HttpInterfaceReceiverThread::start : Method Not Allowed Response Data for Phase 1:\r\n_____\r\n%s\r\n_____\r\n", methodNotAllowedErrorString);
                    }
                    else
                    {
                        httpInterfaceMethodWorker = HttpInterfaceReceiverObjectManager.getHttpInterfaceMethodWorker (waveHttpInterfaceMethod);

                        if (null == httpInterfaceMethodWorker)
                        {
                            final StringBuffer notImplemnetedErrorString = new StringBuffer ();

                            HttpToolKit.getNotImplementedErrorString (notImplemnetedErrorString);

                            acceptedSocket.send (notImplemnetedErrorString);

                            WaveTraceUtils.debugTracePrintf ("HttpInterfaceReceiverThread::start : Not Implemented Response Data for Phase 1:\r\n_____\r\n%s\r\n_____\r\n", notImplemnetedErrorString);
                        }
                        else
                        {
                            WaveTraceUtils.debugTracePrintf ("HttpInterfaceReceiverThread::start : Executing the supported method.");

                            httpInterfaceMethodWorker.process (httpRequest);
                        }
                    }
                }
            }
        }

        if (null != m_acceptedStreamingSocket)
        {
            m_acceptedStreamingSocket.close ();
        }
    }
}
