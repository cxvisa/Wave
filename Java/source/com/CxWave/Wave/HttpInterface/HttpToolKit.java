/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.HttpInterface;

import java.util.Vector;

import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.WaveHttpContentType;
import com.CxWave.Wave.Resources.ResourceEnums.WaveHttpInterfaceMethod;
import com.CxWave.Wave.Shell.ShellDebug;
import com.CxWave.Wave.Shell.Annotations.ShellCommand;

public class HttpToolKit
{
    public static WaveHttpInterfaceMethod getHttpInterfaceMethod (final String httpRequest)
    {
        final Vector<String> httpRequestWords = new Vector<String> ();
        WaveHttpInterfaceMethod waveHttpInterfaceMethod = WaveHttpInterfaceMethod.WAVE_HTTP_INTERFACE_METHOD_UNKNOWN;

        WaveStringUtils.tokenize (httpRequest, httpRequestWords, ' ');

        if (0 < (httpRequestWords.size ()))
        {
            waveHttpInterfaceMethod = getHttpInterfaceMethodFromString (httpRequestWords.get (0));
        }

        return (waveHttpInterfaceMethod);
    }

    public static WaveHttpInterfaceMethod getHttpInterfaceMethodFromString (final String httpRequestMethodString)
    {
        WaveHttpInterfaceMethod waveHttpInterfaceMethod = WaveHttpInterfaceMethod.WAVE_HTTP_INTERFACE_METHOD_UNKNOWN;

        if ("GET" == httpRequestMethodString)
        {
            waveHttpInterfaceMethod = WaveHttpInterfaceMethod.WAVE_HTTP_INTERFACE_METHOD_GET;
        }
        else if ("HEAD" == httpRequestMethodString)
        {
            waveHttpInterfaceMethod = WaveHttpInterfaceMethod.WAVE_HTTP_INTERFACE_METHOD_HEAD;
        }
        else if ("PUT" == httpRequestMethodString)
        {
            waveHttpInterfaceMethod = WaveHttpInterfaceMethod.WAVE_HTTP_INTERFACE_METHOD_PUT;
        }
        else if ("POST" == httpRequestMethodString)
        {
            waveHttpInterfaceMethod = WaveHttpInterfaceMethod.WAVE_HTTP_INTERFACE_METHOD_POST;
        }
        else if ("DELETE" == httpRequestMethodString)
        {
            waveHttpInterfaceMethod = WaveHttpInterfaceMethod.WAVE_HTTP_INTERFACE_METHOD_DELETE;
        }
        else if ("OPTIONS" == httpRequestMethodString)
        {
            waveHttpInterfaceMethod = WaveHttpInterfaceMethod.WAVE_HTTP_INTERFACE_METHOD_OPTIONS;
        }
        else if ("TRACE" == httpRequestMethodString)
        {
            waveHttpInterfaceMethod = WaveHttpInterfaceMethod.WAVE_HTTP_INTERFACE_METHOD_TRACE;
        }
        else if ("CONNECT" == httpRequestMethodString)
        {
            waveHttpInterfaceMethod = WaveHttpInterfaceMethod.WAVE_HTTP_INTERFACE_METHOD_CONNECT;
        }

        return (waveHttpInterfaceMethod);
    }

    public static WaveHttpContentType getHttpContentTypeFromString (final String contentTypeString)
    {
        WaveHttpContentType httpContentType = WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_UNKNOWN;

        if ("text/plain" == contentTypeString)
        {
            httpContentType = WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_TEXT_PLAIN;
        }
        else if ("text/html" == contentTypeString)
        {
            httpContentType = WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_TEXT_HTML;
        }
        else if ("text/xml" == contentTypeString)
        {
            httpContentType = WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_TEXT_XML;
        }
        else if ("application/octet-stream" == contentTypeString)
        {
            httpContentType = WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_APPLICATION_OCTET_STREAM;
        }
        else if ("application/atom+xml" == contentTypeString)
        {
            httpContentType = WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_APPLICATION_ATOM_XML;
        }
        else if ("application/x-www-form-urlencoded" == contentTypeString)
        {
            httpContentType = WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_APPLICATION_FORM_URLENCODED;
        }
        else if ("application/json" == contentTypeString)
        {
            httpContentType = WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_APPLICATION_JSON;
        }
        else if ("application/xhtml+xml" == contentTypeString)
        {
            httpContentType = WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_APPLICATION_XHTML_XML;
        }
        else if ("multipart/form-data" == contentTypeString)
        {
            httpContentType = WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_MULTIPART_FORM_DATA;
        }
        else if ("image/gif" == contentTypeString)
        {
            httpContentType = WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_IMAGE_GIF;
        }
        else if ("image/png" == contentTypeString)
        {
            httpContentType = WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_IMAGE_PNG;
        }
        else if ("image/jpeg" == contentTypeString)
        {
            httpContentType = WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_IMAGE_JPEG;
        }

        return (httpContentType);
    }

    public static String decodeUrl (final String url)
    {
        int position = 0;
        final int length = url.length ();

        final StringBuffer urlBuffer = new StringBuffer (WaveStringUtils.replaceAllInstancesOfInputCharWith (url, '+', ' '));

        while (-1 != (position = (urlBuffer.indexOf ("%", position + 1))))
        {
            if (length > (position + 2))
            {
                char c = 0;

                c = (char) Integer.parseInt (urlBuffer.substring (position + 1, position + 3), 16);

                final String tempString = "" + c;

                urlBuffer.replace (position, position + 3, tempString);
            }
        }

        return (urlBuffer.toString ());
    }

    @ShellCommand (shell = ShellDebug.class, briefHelp = "Decodes a given URL.")
    public static void decodeUrl (final Vector<String> arguments)
    {
        for (final String argument : arguments)
        {
            WaveTraceUtils.infoTracePrintf ("Decoded URL : \"%s\"", decodeUrl (argument));
        }
    }
}
