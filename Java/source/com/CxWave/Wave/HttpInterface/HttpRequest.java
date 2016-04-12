/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.HttpInterface;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;
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
    WaveHttpInterfaceMethod     m_waveHttpInterfaceMethod;
    String                      m_uri;
    Vector<String>              m_uriTokens               = new Vector<String> ();
    String                      m_authorization;
    int                         m_contentLength;
    WaveHttpContentType         m_contentType;
    String                      m_contentBoundary;
    String                      m_content;
    boolean                     m_isContentReadIncomplete;
    Vector<String>              m_entityNames             = new Vector<String> ();
    Vector<String>              m_entityFileNames         = new Vector<String> ();
    Vector<String>              m_entityValues            = new Vector<String> ();
    Map<String, String>         m_entitiesMap             = new HashMap<String, String> ();
    String                      m_host;

    Map<String, String>         m_queryParamatersMap      = new HashMap<String, String> ();
    Map<String, String>         m_formParamatersMap       = new HashMap<String, String> ();
    Map<String, String>         m_pathParamatersMap       = new HashMap<String, String> ();

    Map<String, Vector<String>> m_queryParamatersMultiMap = new HashMap<String, Vector<String>> ();
    Map<String, Vector<String>> m_formParamatersMultiMap  = new HashMap<String, Vector<String>> ();
    Map<String, Vector<String>> m_pathParamatersMultiMap  = new HashMap<String, Vector<String>> ();

    String                      m_pathMapping;

    AcceptedStreamingSocket     m_serverStreamingSocket;

    static String               s_authorizationString     = "Authorization";
    static String               s_contentLengthString     = "Content-Length";
    static String               s_contentTypeString       = "Content-Type";
    static String               s_hostString              = "Host";

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

            if (-1 != status)
            {
                tempString = new String (tempStringBuffer, 0, status);
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

            nextEndOfLinePosition = httpRequest.indexOf ("\r\n", contentLengthPosition);

            if (-1 != nextEndOfLinePosition)
            {
                final String contentLengthValueString = httpRequest.substring (positionOfcontentLengthValue, nextEndOfLinePosition);

                m_contentLength = Integer.parseInt (contentLengthValueString, 10);
            }
            else
            {
                return;
            }

            nextEndOfLinePosition = httpRequest.indexOf ("\r\n\r\n", contentLengthPosition);

            if (-1 != nextEndOfLinePosition)
            {
                contentBeginPosition = nextEndOfLinePosition + 4;
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

        WaveTraceUtils.debugTracePrintf ("HttpRequest.HttpRequest : Content Begin                          : %d", contentBeginPosition);
        WaveTraceUtils.debugTracePrintf ("HttpRequest.HttpRequest : Content Length                         : %d", m_contentLength);
        WaveTraceUtils.debugTracePrintf ("HttpRequest.HttpRequest : Request Length                         : %d", requestLength);
        WaveTraceUtils.debugTracePrintf ("HttpRequest.HttpRequest : Length of Remaining Content to be Read : %d", lengthOfRemainingDataToBeRead);

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

        WaveTraceUtils.infoTracePrintf ("HttpRequest.HttpRequest : Request from wire:\r\n%s", httpRequest);

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

                // Get Authrization

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

                            m_queryParamatersMap.put (entityName, entityValue);

                            Vector<String> entityValues = m_queryParamatersMultiMap.get (entityName);

                            if (null == entityValues)
                            {
                                entityValues = new Vector<String> ();

                                m_queryParamatersMultiMap.put (entityName, entityValues);
                            }

                            entityValues.add (entityValue);
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

                            m_formParamatersMap.put (entityName, entityValue);

                            Vector<String> entityValues = m_formParamatersMultiMap.get (entityName);

                            if (null == entityValues)
                            {
                                entityValues = new Vector<String> ();

                                m_formParamatersMultiMap.put (entityName, entityValues);
                            }

                            entityValues.add (entityValue);

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

                        m_formParamatersMap.put (entityName, entityValue);

                        Vector<String> entityValues = m_formParamatersMultiMap.get (entityName);

                        if (null == entityValues)
                        {
                            entityValues = new Vector<String> ();

                            m_formParamatersMultiMap.put (entityName, entityValues);
                        }

                        entityValues.add (entityValue);
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

    public WaveHttpInterfaceMethod getWaveHttpInterfaceMethod ()
    {
        return m_waveHttpInterfaceMethod;
    }

    public void setWaveHttpInterfaceMethod (final WaveHttpInterfaceMethod waveHttpInterfaceMethod)
    {
        m_waveHttpInterfaceMethod = waveHttpInterfaceMethod;
    }

    public String getUri ()
    {
        return m_uri;
    }

    public void setUri (final String uri)
    {
        m_uri = uri;
    }

    public Vector<String> getUriTokens ()
    {
        return m_uriTokens;
    }

    public void setUriTokens (final Vector<String> uriTokens)
    {
        m_uriTokens = uriTokens;
    }

    public String getAuthorization ()
    {
        return m_authorization;
    }

    public void setAuthorization (final String authorization)
    {
        m_authorization = authorization;
    }

    public int getContentLength ()
    {
        return m_contentLength;
    }

    public void setContentLength (final int contentLength)
    {
        m_contentLength = contentLength;
    }

    public WaveHttpContentType getContentType ()
    {
        return m_contentType;
    }

    public void setContentType (final WaveHttpContentType contentType)
    {
        m_contentType = contentType;
    }

    public String getContentBoundary ()
    {
        return m_contentBoundary;
    }

    public void setContentBoundary (final String contentBoundary)
    {
        m_contentBoundary = contentBoundary;
    }

    public String getContent ()
    {
        return m_content;
    }

    public void setContent (final String content)
    {
        m_content = content;
    }

    public Vector<String> getEntityNames ()
    {
        return m_entityNames;
    }

    public void setEntityNames (final Vector<String> entityNames)
    {
        m_entityNames = entityNames;
    }

    public Vector<String> getEntityFileNames ()
    {
        return m_entityFileNames;
    }

    public void setEntityFileNames (final Vector<String> entityFileNames)
    {
        m_entityFileNames = entityFileNames;
    }

    public Vector<String> getEntityValues ()
    {
        return m_entityValues;
    }

    public void setEntityValues (final Vector<String> entityValues)
    {
        m_entityValues = entityValues;
    }

    public Map<String, String> getEntitiesMap ()
    {
        return m_entitiesMap;
    }

    public void setEntitiesMap (final Map<String, String> entitiesMap)
    {
        m_entitiesMap = entitiesMap;
    }

    public String getHost ()
    {
        return m_host;
    }

    public void setHost (final String host)
    {
        m_host = host;
    }

    public AcceptedStreamingSocket getAcceptedStreamingSocket ()
    {
        return m_serverStreamingSocket;
    }

    public void setServerStreamingSocket (final AcceptedStreamingSocket serverStreamingSocket)
    {
        m_serverStreamingSocket = serverStreamingSocket;
    }

    public static String getAuthorizationString ()
    {
        return s_authorizationString;
    }

    public static void setAuthorizationString (final String authorizationString)
    {
        s_authorizationString = authorizationString;
    }

    public static String getContentLengthString ()
    {
        return s_contentLengthString;
    }

    public static void setContentLengthString (final String contentLengthString)
    {
        s_contentLengthString = contentLengthString;
    }

    public static String getContentTypeString ()
    {
        return s_contentTypeString;
    }

    public static void setContentTypeString (final String contentTypeString)
    {
        s_contentTypeString = contentTypeString;
    }

    public static String getHostString ()
    {
        return s_hostString;
    }

    public static void setHostString (final String hostString)
    {
        s_hostString = hostString;
    }

    public int getNumberOfEntities ()
    {
        final int numberOfEntityNames = m_entityNames.size ();
        final int numberOfEntityFileNames = m_entityFileNames.size ();
        final int numberOfEntityValues = m_entityValues.size ();

        WaveAssertUtils.waveAssert (numberOfEntityNames == numberOfEntityValues);
        WaveAssertUtils.waveAssert (numberOfEntityNames == numberOfEntityFileNames);

        return (numberOfEntityNames);
    }

    public String getEntityNameAtIndex (final int index)
    {
        final int numberOfEntities = getNumberOfEntities ();

        if (index < numberOfEntities)
        {
            return (m_entityNames.get (index));
        }
        else
        {
            WaveAssertUtils.waveAssert ();
        }

        return ("");
    }

    public String getEntityFileNameAtIndex (final int index)
    {
        final int numberOfEntities = getNumberOfEntities ();

        if (index < numberOfEntities)
        {
            return (m_entityFileNames.get (index));
        }
        else
        {
            WaveAssertUtils.waveAssert ();
        }

        return ("");
    }

    public String getEntityValueAtIndex (final int index)
    {
        final int numberOfEntities = getNumberOfEntities ();

        if (index < numberOfEntities)
        {
            return (m_entityValues.get (index));
        }
        else
        {
            WaveAssertUtils.waveAssert ();
        }

        return ("");
    }

    public String getQueryParamterValue (final String queryParameter)
    {
        return (m_queryParamatersMap.get (queryParameter));
    }

    public Set<String> getQueryParamters ()
    {
        return (m_queryParamatersMap.keySet ());
    }

    public String getFormParamterValue (final String formParameter)
    {
        return (m_formParamatersMap.get (formParameter));
    }

    public Set<String> getFormParamters ()
    {
        return (m_formParamatersMap.keySet ());
    }

    public String getPathParamterValue (final String pathParameter)
    {
        return (m_pathParamatersMap.get (pathParameter));
    }

    public Set<String> getPathParamters ()
    {
        return (m_pathParamatersMap.keySet ());
    }

    public void applyUriToPathMapping (final String pathMapping)
    {
        m_pathMapping = pathMapping;

        final Vector<String> uriTokens = new Vector<String> ();
        final Vector<String> pathMappingTokens = new Vector<String> ();

        WaveStringUtils.tokenize (m_uri, uriTokens, '/');
        WaveStringUtils.tokenize (m_pathMapping, pathMappingTokens, '/');

        final int numberOfUriTokens = uriTokens.size ();
        final int numberOFPathMappingTokens = pathMappingTokens.size ();

        WaveAssertUtils.waveAssert (numberOFPathMappingTokens == numberOfUriTokens);

        for (int i = 0; i < numberOFPathMappingTokens; i++)
        {
            final String pathMappingToken = pathMappingTokens.get (i);

            if ((pathMappingToken.startsWith ("{")) && (pathMappingToken.endsWith ("}")))
            {
                final int pathMappingTokenSize = pathMappingToken.length ();
                int firstIndex = 0;
                int lastIndex = pathMappingTokenSize - 1;

                while (firstIndex < pathMappingTokenSize)
                {
                    if ((pathMappingToken.charAt (firstIndex)) != '{')
                    {
                        break;
                    }

                    firstIndex++;
                }

                while (lastIndex >= 0)
                {
                    if ((pathMappingToken.charAt (lastIndex)) != '}')
                    {
                        break;
                    }

                    lastIndex--;
                }

                if (lastIndex > firstIndex)
                {
                    final String pathParameter = pathMappingToken.substring (firstIndex, lastIndex + 1);
                    final String pathParameterValue = uriTokens.get (i);

                    m_pathParamatersMap.put (pathParameter, pathParameterValue);

                    Vector<String> entityValues = m_pathParamatersMultiMap.get (pathParameter);

                    if (null == entityValues)
                    {
                        entityValues = new Vector<String> ();

                        m_pathParamatersMultiMap.put (pathParameter, entityValues);
                    }

                    entityValues.add (pathParameterValue);
                }
            }
        }
    }

    public String getPathMapping ()
    {
        return (m_pathMapping);
    }

    public Vector<String> getPathParameterValues (final String pathParamter)
    {
        return (m_pathParamatersMultiMap.get (pathParamter));
    }

    public Vector<String> getQueryParameterValues (final String queryParameter)
    {
        return (m_queryParamatersMultiMap.get (queryParameter));
    }

    public Vector<String> getFormParameterValues (final String formParameter)
    {
        return (m_queryParamatersMultiMap.get (formParameter));
    }
}
