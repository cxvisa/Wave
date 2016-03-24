/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.HttpInterface;

import java.io.UnsupportedEncodingException;
import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Buffer.FixedSizeBuffer;
import com.CxWave.Wave.Framework.Utils.Socket.AcceptedStreamingSocket;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.WaveHttpContentType;
import com.CxWave.Wave.Resources.ResourceEnums.WaveHttpInterfaceMethod;

public class HttpRequest
{
    WaveHttpInterfaceMethod m_waveHttpInterfaceMethod;
    String                  m_uri;
    Vector<String>          m_uriTokens           = new Vector<String> ();
    String                  m_authorization;
    int                     m_contentLength;
    WaveHttpContentType     m_contentType;
    String                  m_contentBoundary;
    String                  m_content;
    boolean                 m_isContentReadIncomplete;
    Vector<String>          m_entityNames         = new Vector<String> ();
    Vector<String>          m_entityFileNames     = new Vector<String> ();
    Vector<String>          m_entityValues        = new Vector<String> ();
    Map<String, String>     m_entitiesMap         = new HashMap<String, String> ();
    String                  m_host;

    AcceptedStreamingSocket m_serverStreamingSocket;

    static String           s_authorizationString = "Authorization";
    static String           s_contentLengthString = "Content-Length";
    static String           s_contentTypeString   = "Content-Type";
    static String           s_hostString          = "Host";

    public HttpRequest (final StringBuffer httpRequest, final AcceptedStreamingSocket serverStreamingSocket)
    {
        m_waveHttpInterfaceMethod = WaveHttpInterfaceMethod.WAVE_HTTP_INTERFACE_METHOD_UNKNOWN;
        m_contentLength = 0;
        m_contentType = WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_UNKNOWN;
        m_isContentReadIncomplete = false;
        m_serverStreamingSocket = serverStreamingSocket;

        // First check if we have an empty line in the request - which is a delimiter indicating the end of header.
        // Otherwise keep reading from the socket till we receive such line.

        int emptyLinePosition = -1;
        int consecutiveZeroSizeReturns = 0;

        while (-1 == (emptyLinePosition = (httpRequest.indexOf ("\r\n\r\n"))))
        {
            String tempString = null;
            // final boolean isSuccesful = false;
            int status = -1;
            final byte[] tempStringBuffer = new byte[512];

            status = serverStreamingSocket.receive (tempStringBuffer);
            try
            {
                tempString = new String (tempStringBuffer, "UTF-8");
            }
            catch (final UnsupportedEncodingException e)
            {
                WaveAssertUtils.waveAssert ();
            }

            if (0 == (tempString.length ()))
            {
                consecutiveZeroSizeReturns++;
            }
            else
            {
                consecutiveZeroSizeReturns = 0;
            }

            if (100 < consecutiveZeroSizeReturns)
            {
                return;
            }

            if (-1 != status)
            {
                httpRequest.append (tempString);
            }
        }

        // First check if we have the entire request.
        // Otherwise read the remaining from wire.

        final int requestLength = httpRequest.length ();
        final int contentLengthPosition = httpRequest.indexOf (s_contentLengthString);
        int nextEndOfLinePosition = 0;
        int contentBeginPosition = 0;
        int lengthOfRemainingDataToBeRead = 0;

        if (-1 != contentLengthPosition)
        {
            final int positionOfcontentLengthValue = contentLengthPosition + s_contentLengthString.length () + 2;

            nextEndOfLinePosition = httpRequest.indexOf ("\r\n\r\n", contentLengthPosition);

            if (-1 != nextEndOfLinePosition)
            {
                contentBeginPosition = nextEndOfLinePosition + 4;

                final String contentLengthValueString = httpRequest.substring (positionOfcontentLengthValue, nextEndOfLinePosition);

                m_contentLength = Integer.parseInt (contentLengthValueString, 10);
            }
            else
            {
                return;
            }
        }

        if (0 != contentBeginPosition)
        {
            if (((UI32.MAXIMUM.getValue ()) - m_contentLength) >= contentBeginPosition)
            {
                if ((contentBeginPosition + m_contentLength) > requestLength)
                {
                    lengthOfRemainingDataToBeRead = (contentBeginPosition + m_contentLength) - requestLength;
                }
            }
        }

        WaveTraceUtils.develTracePrintf ("HttpRequest.HttpRequest : Content Begin                          : %d", contentBeginPosition);
        WaveTraceUtils.develTracePrintf ("HttpRequest.HttpRequest : Content Length                         : %d", m_contentLength);
        WaveTraceUtils.develTracePrintf ("HttpRequest.HttpRequest : Request Length                         : %d", requestLength);
        WaveTraceUtils.develTracePrintf ("HttpRequest.HttpRequest : Length of Remaining Content to be Read : %d", lengthOfRemainingDataToBeRead);

        if (0 < lengthOfRemainingDataToBeRead)
        {
            if (null != serverStreamingSocket)
            {
                final FixedSizeBuffer fixedSizeBuffer = new FixedSizeBuffer (new UI32 (lengthOfRemainingDataToBeRead));
                final boolean isSuccesful = false;
                int status = -1;

                status = serverStreamingSocket.receiveAll (fixedSizeBuffer);

                if (-1 != status)
                {
                    String tempString = null;

                    tempString = fixedSizeBuffer.toString ();

                    httpRequest.append (tempString);

                    setIsContentReadIncomplete (false);
                }
                else
                {
                    setIsContentReadIncomplete (true);
                }
            }
            else
            {
                WaveAssertUtils.waveAssert ();
            }
        }

        // Now proceed to process the request in its entirety.

        final String httpRequestFromWire = (httpRequest.toString ()).replaceAll ("\r", "");
        int position = 0;
        int headerEndLineIndex = 0;
        final int lineLength = 0;

        final Vector<String> httpRequestLines = new Vector<String> ();

        WaveStringUtils.tokenize (httpRequestFromWire, httpRequestLines, '\n');

        final int numberOfHttpRequestLines = httpRequestLines.size ();
        int i = 0;
        int j = 0;

        if (0 < numberOfHttpRequestLines)
        {
            // Get the Method.

            final String requestLine = httpRequestLines.get (0);

            final Vector<String> requestLineTokens = new Vector<String> ();

            WaveStringUtils.tokenize (requestLine, requestLineTokens, ' ');

            final int numberOfRequetLineTokens = requestLineTokens.size ();

            if (0 < numberOfRequetLineTokens)
            {
                m_waveHttpInterfaceMethod = HttpToolKit.getHttpInterfaceMethodFromString (requestLineTokens.get (0));
            }

            if (1 < numberOfRequetLineTokens)
            {
                m_uri = requestLineTokens.get (1);

                WaveStringUtils.tokenize (m_uri, m_uriTokens, '/');
            }

            // Eliminate the \r characters at the end of each line if exists.

            // Not needed since we replaced all of the "\r" above when we obtained the httpRequestFromWire variable.

            for (i = 0; i < numberOfHttpRequestLines; i++)
            {
                // WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_DEVEL, httpRequestLines[i] + "\r");

                // First empty line signals the end of the message header.

                if ("".equals (httpRequestLines.get (i)))
                {
                    headerEndLineIndex = i;

                    break;
                }

                // Get Host

                if ((httpRequestLines.get (i)).startsWith (s_hostString))
                {
                    final Vector<String> hostTokens = new Vector<String> ();

                    WaveStringUtils.tokenize (httpRequestLines.get (i), hostTokens, ' ');

                    if (2 <= (hostTokens.size ()))
                    {
                        m_host = hostTokens.get (1);
                    }
                }

                // Get Authrozation

                if ((httpRequestLines.get (i)).startsWith (s_authorizationString))
                {
                    final Vector<String> authorizationTokens = new Vector<String> ();

                    WaveStringUtils.tokenize (httpRequestLines.get (i), authorizationTokens, ' ');

                    if (3 <= (authorizationTokens.size ()))
                    {
                        m_authorization = authorizationTokens.get (2);
                    }
                }

                // Get Content Length

                if ((httpRequestLines.get (i)).startsWith (s_contentLengthString))
                {
                    final Vector<String> contentLengthTokens = new Vector<String> ();

                    WaveStringUtils.tokenize (httpRequestLines.get (i), contentLengthTokens, ' ');

                    if (2 <= (contentLengthTokens.size ()))
                    {
                        m_contentLength = Integer.parseInt (contentLengthTokens.get (1), 10);
                    }
                }

                // Get Content Type

                if ((httpRequestLines.get (i)).startsWith (s_contentTypeString))
                {
                    final Vector<String> contentTypeTokens = new Vector<String> ();
                    String contentTypeString;

                    WaveStringUtils.tokenize (httpRequestLines.get (i), contentTypeTokens, ' ');

                    if (3 <= (contentTypeTokens.size ()))
                    {
                        contentTypeString = contentTypeTokens.get (1);
                        // contentTypeString.erase (contentTypeString.begin () + (contentTypeString.length () - 1));

                        m_contentType = HttpToolKit.getHttpContentTypeFromString (contentTypeString);

                        if (WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_MULTIPART_FORM_DATA == m_contentType)
                        {
                            m_contentBoundary = contentTypeTokens.get (2);

                            final StringBuffer contentBoundaryBuffer = new StringBuffer (m_contentBoundary);

                            contentBoundaryBuffer.replace (0, m_contentBoundary.indexOf ('=') + 1, "");

                            m_contentBoundary = contentBoundaryBuffer.toString ();
                        }
                    }
                    else if (2 <= (contentTypeTokens.size ()))
                    {
                        m_contentType = HttpToolKit.getHttpContentTypeFromString (contentTypeTokens.get (1));
                    }
                }
            }
        }

        // Fix the URI. Then URL Decode it.

        position = m_uri.indexOf ('?');

        if (-1 != position)
        {
            final Vector<String> uriTokens = new Vector<String> ();
            int numberOfUriTokens = 0;

            WaveStringUtils.tokenize (m_uri, uriTokens, '?');

            numberOfUriTokens = uriTokens.size ();

            if (1 <= numberOfUriTokens)
            {
                m_uri = uriTokens.get (0);

                m_uri = HttpToolKit.decodeUrl (m_uri);

                for (i = 1; i < numberOfUriTokens; i++)
                {
                    final Vector<String> uriEntityTokens = new Vector<String> ();
                    int numberOfUriEntityTokens = 0;

                    WaveStringUtils.tokenize (uriTokens.get (i), uriEntityTokens, '&');

                    numberOfUriEntityTokens = uriEntityTokens.size ();

                    for (j = 0; j < numberOfUriEntityTokens; j++)
                    {
                        final Vector<String> uriEntityNameValueTokens = new Vector<String> ();
                        int numberOfUriEntityNameValueTokens = 0;

                        WaveStringUtils.tokenize (uriEntityTokens.get (j), uriEntityNameValueTokens, '=');

                        numberOfUriEntityNameValueTokens = uriEntityNameValueTokens.size ();

                        if (2 <= numberOfUriEntityNameValueTokens)
                        {
                            String entityName = uriEntityNameValueTokens.get (0);
                            String fileName = "";
                            String entityValue = uriEntityNameValueTokens.get (1);

                            entityName = HttpToolKit.decodeUrl (entityName);
                            fileName = HttpToolKit.decodeUrl (fileName);
                            entityValue = HttpToolKit.decodeUrl (entityValue);

                            m_entityNames.add (entityName);
                            m_entityFileNames.add (fileName);
                            m_entityValues.add (entityValue);

                            m_entitiesMap.put (entityName, entityValue);
                        }
                    }
                }
            }
        }
        else
        {
            m_uri = HttpToolKit.decodeUrl (m_uri);
        }

        // Get Content

        if (0 != m_contentLength)
        {
            final int totalHttpRequestLength = httpRequest.length ();

            if ((totalHttpRequestLength > m_contentLength) && (0 != contentBeginPosition))
            {
                // m_content.assign (httpRequest, totalHttpRequestLength - m_contentLength, m_contentLength);
                m_content = httpRequest.substring (contentBeginPosition);
            }

            if (WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_MULTIPART_FORM_DATA == m_contentType)
            {
                WaveAssertUtils.waveAssert (0 != (m_contentBoundary.length ()));

                String entityName = "";
                String fileName = "";
                String entityValue = "";
                final String effectiveContentBoundaryString = "--" + m_contentBoundary;
                final String finalEffectiveContentBoundaryString = effectiveContentBoundaryString + "--";
                boolean startAddingToEntityValue = false;

                for (i = headerEndLineIndex + 1; i < numberOfHttpRequestLines; i++)
                {
                    if (0 == ((httpRequestLines.get (i)).indexOf (effectiveContentBoundaryString)))
                    {
                        if (!(entityName.isEmpty ()))
                        {
                            m_entityNames.add (entityName);
                            m_entityFileNames.add (fileName);
                            m_entityValues.add (entityValue);

                            m_entitiesMap.put (entityName, entityValue);

                            entityName = "";
                            fileName = "";
                            entityValue = "";
                            startAddingToEntityValue = false;
                        }
                    }
                    else
                    {
                        if ((httpRequestLines.get (i)).isEmpty ())
                        {
                            if (false == startAddingToEntityValue)
                            {
                                startAddingToEntityValue = true;
                            }
                            else
                            {
                                if (entityValue.isEmpty ())
                                {
                                    entityValue += httpRequestLines.get (i);
                                }
                                else
                                {
                                    entityValue += "\n" + httpRequestLines.get (i);
                                }
                            }
                        }
                        else
                        {
                            if (true == startAddingToEntityValue)
                            {
                                if (entityValue.isEmpty ())
                                {
                                    entityValue += httpRequestLines.get (i);
                                }
                                else
                                {
                                    entityValue += "\n" + httpRequestLines.get (i);
                                }
                            }
                            else
                            {
                                if (entityName.isEmpty ())
                                {
                                    final Vector<String> entityNameLineTokens = new Vector<String> ();
                                    int numberOfEntityLineTokens = 0;

                                    WaveStringUtils.tokenize (httpRequestLines.get (i), entityNameLineTokens, ';');

                                    numberOfEntityLineTokens = entityNameLineTokens.size ();

                                    if (2 <= numberOfEntityLineTokens)
                                    {
                                        final Vector<String> entityNameTokens = new Vector<String> ();
                                        int numberOfEntityNameTokens = 0;

                                        WaveStringUtils.tokenize (entityNameLineTokens.get (1), entityNameTokens, '=');
                                        numberOfEntityNameTokens = entityNameTokens.size ();

                                        if (2 <= numberOfEntityNameTokens)
                                        {
                                            entityName = entityNameTokens.get (1);

                                            entityName = WaveStringUtils.removeAllInstancesOfInputChar (entityName, '"');
                                        }
                                    }

                                    if (3 <= numberOfEntityLineTokens)
                                    {
                                        final Vector<String> fileNameTokens = new Vector<String> ();
                                        int numberOfFileNameTokens = 0;

                                        WaveStringUtils.tokenize (entityNameLineTokens.get (2), fileNameTokens, '=');
                                        numberOfFileNameTokens = fileNameTokens.size ();

                                        if (2 <= numberOfFileNameTokens)
                                        {
                                            fileName = fileNameTokens.get (1);

                                            fileName = WaveStringUtils.removeAllInstancesOfInputChar (fileName, '"');
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if (WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_APPLICATION_FORM_URLENCODED == m_contentType)
            {
                final Vector<String> contentTokens = new Vector<String> ();
                int numberOfContentTokens = 0;

                WaveStringUtils.tokenize (m_content, contentTokens, '&');

                numberOfContentTokens = contentTokens.size ();

                for (i = 0; i < numberOfContentTokens; i++)
                {
                    final Vector<String> contentNameValueTokens = new Vector<String> ();
                    int numberOfContentNameValueTokens = 0;

                    WaveStringUtils.tokenize (contentTokens.get (i), contentNameValueTokens, '=');

                    numberOfContentNameValueTokens = contentNameValueTokens.size ();

                    if (2 <= numberOfContentNameValueTokens)
                    {
                        String entityName = contentNameValueTokens.get (0);
                        String fileName = "";
                        String entityValue = contentNameValueTokens.get (1);

                        entityName = HttpToolKit.decodeUrl (entityName);
                        fileName = HttpToolKit.decodeUrl (fileName);
                        entityValue = HttpToolKit.decodeUrl (entityValue);

                        m_entityNames.add (entityName);
                        m_entityFileNames.add (fileName);
                        m_entityValues.add (entityValue);

                        m_entitiesMap.put (entityName, entityValue);
                    }
                }
            }
        }
    }

    public boolean getIsContentReadIncomplete ()
    {
        return (m_isContentReadIncomplete);
    }

    public void setIsContentReadIncomplete (final boolean isContentReadIncomplete)
    {
        m_isContentReadIncomplete = isContentReadIncomplete;
    }
}
