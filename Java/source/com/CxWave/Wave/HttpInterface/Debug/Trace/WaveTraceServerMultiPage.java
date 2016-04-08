/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.HttpInterface.Debug.Trace;

import java.util.Vector;

import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
import com.CxWave.Wave.Framework.Trace.TraceObjectManager;
import com.CxWave.Wave.Framework.Type.TraceClientId;
import com.CxWave.Wave.Framework.Utils.Socket.AcceptedStreamingSocket;
import com.CxWave.Wave.HttpInterface.HttpInterfaceReceiverObjectManager;
import com.CxWave.Wave.HttpInterface.HttpRequest;
import com.CxWave.Wave.HttpInterface.WaveServerMultiPage;
import com.CxWave.Wave.HttpInterface.Annotations.GET;
import com.CxWave.Wave.HttpInterface.Annotations.Path;
import com.CxWave.Wave.HttpInterface.Annotations.PathMapping;
import com.CxWave.Wave.HttpInterface.Annotations.PathParam;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

@PathMapping (name = "/debug/{debugType}/trace")
public class WaveTraceServerMultiPage extends WaveServerMultiPage
{
    public WaveTraceServerMultiPage (final HttpInterfaceReceiverObjectManager httpInterfaceReceiverObjectManager, final String path)
    {
        super (httpInterfaceReceiverObjectManager, path);
    }

    @GET
    @Path (name = "List/*")
    @PathMapping (name = "List/{listType}")
    void getForList (final HttpRequest httpRequest, @PathParam (name = "debugType") final String debugType, @PathParam (name = "listType") final String listType)
    {
        final Vector<TraceClientId> traceClientIdsVector = new Vector<TraceClientId> ();
        final Vector<TraceLevel> traceLevelsVector = new Vector<TraceLevel> ();
        int nServices = 0;
        int index = 0;
        String serviceName;
        String traceLevelName;

        TraceObjectManager.getClientsInformationDirectly (traceClientIdsVector, traceLevelsVector);

        nServices = traceClientIdsVector.size ();

        final StringBuffer httpResponseString = new StringBuffer ();
        final AcceptedStreamingSocket acceptedStreamingSocket = httpRequest.getAcceptedStreamingSocket ();

        getWaveServerPagePrePortionForGet (httpResponseString);

        httpResponseString.append ("<H2 STYLE=\"COLOR:RGB(255, 0, 0);TEXT-ALIGN:CENTER;\">" + getPageHeading () + debugType + " - " + listType + "</H2>\r\n");
        httpResponseString.append ("<H3 STYLE=\"COLOR:RGB(0, 0, 255);TEXT-ALIGN:CENTER;\">List</H3>\r\n");

        if (0 < nServices)
        {
            httpResponseString.append ("<TABLE BORDER=0 \">\r\n");

            httpResponseString.append ("<TH>#</TH>\r\n");
            httpResponseString.append ("<TH>Service Name</TH>\r\n");
            httpResponseString.append ("<TH>Trace Level</TH>\r\n");

            for (index = 0; index < nServices; index++)
            {
                final TraceClientId traceClientId = traceClientIdsVector.get (index);
                final TraceLevel traceLevel = traceLevelsVector.get (index);

                serviceName = FrameworkToolKit.getTraceClientNameById (traceClientId);
                traceLevelName = FrameworkToolKit.localize (traceLevel);

                if (0 == (index % 2))
                {
                    httpResponseString.append ("<TR STYLE=\"BACKGROUND-COLOR:RGB(200, 200, 200);\">\r\n");
                }
                else
                {
                    httpResponseString.append ("<TR STYLE=\"BACKGROUND-COLOR:RGB(255, 255, 255);\">\r\n");
                }

                httpResponseString.append ("<TD>" + ((new Integer (index + 1)).toString ()) + "</TD>\r\n");
                httpResponseString.append ("<TD>" + serviceName + "</TD>\r\n");
                httpResponseString.append ("<TD>" + traceLevelName + "</TD>\r\n");

                httpResponseString.append ("</TR>\r\n");
            }

            httpResponseString.append ("</TABLE>\r\n");
        }

        getWaveServerPagePostPortionForGet (httpResponseString);

        if (null != acceptedStreamingSocket)
        {
            acceptedStreamingSocket.send (httpResponseString);
        }

    }
}
