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

        if ("GET".equals (httpRequestMethodString))
        {
            waveHttpInterfaceMethod = WaveHttpInterfaceMethod.WAVE_HTTP_INTERFACE_METHOD_GET;
        }
        else if ("HEAD".equals (httpRequestMethodString))
        {
            waveHttpInterfaceMethod = WaveHttpInterfaceMethod.WAVE_HTTP_INTERFACE_METHOD_HEAD;
        }
        else if ("PUT".equals (httpRequestMethodString))
        {
            waveHttpInterfaceMethod = WaveHttpInterfaceMethod.WAVE_HTTP_INTERFACE_METHOD_PUT;
        }
        else if ("POST".equals (httpRequestMethodString))
        {
            waveHttpInterfaceMethod = WaveHttpInterfaceMethod.WAVE_HTTP_INTERFACE_METHOD_POST;
        }
        else if ("DELETE".equals (httpRequestMethodString))
        {
            waveHttpInterfaceMethod = WaveHttpInterfaceMethod.WAVE_HTTP_INTERFACE_METHOD_DELETE;
        }
        else if ("OPTIONS".equals (httpRequestMethodString))
        {
            waveHttpInterfaceMethod = WaveHttpInterfaceMethod.WAVE_HTTP_INTERFACE_METHOD_OPTIONS;
        }
        else if ("TRACE".equals (httpRequestMethodString))
        {
            waveHttpInterfaceMethod = WaveHttpInterfaceMethod.WAVE_HTTP_INTERFACE_METHOD_TRACE;
        }
        else if ("CONNECT".equals (httpRequestMethodString))
        {
            waveHttpInterfaceMethod = WaveHttpInterfaceMethod.WAVE_HTTP_INTERFACE_METHOD_CONNECT;
        }

        return (waveHttpInterfaceMethod);
    }

    public static WaveHttpContentType getHttpContentTypeFromString (final String contentTypeString)
    {
        WaveHttpContentType httpContentType = WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_UNKNOWN;

        if ("text/plain".equals (contentTypeString))
        {
            httpContentType = WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_TEXT_PLAIN;
        }
        else if ("text/html".equals (contentTypeString))
        {
            httpContentType = WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_TEXT_HTML;
        }
        else if ("text/xml".equals (contentTypeString))
        {
            httpContentType = WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_TEXT_XML;
        }
        else if ("application/octet-stream".equals (contentTypeString))
        {
            httpContentType = WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_APPLICATION_OCTET_STREAM;
        }
        else if ("application/atom+xml".equals (contentTypeString))
        {
            httpContentType = WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_APPLICATION_ATOM_XML;
        }
        else if ("application/x-www-form-urlencoded".equals (contentTypeString))
        {
            httpContentType = WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_APPLICATION_FORM_URLENCODED;
        }
        else if ("application/json".equals (contentTypeString))
        {
            httpContentType = WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_APPLICATION_JSON;
        }
        else if ("application/xhtml+xml".equals (contentTypeString))
        {
            httpContentType = WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_APPLICATION_XHTML_XML;
        }
        else if ("multipart/form-data".equals (contentTypeString))
        {
            httpContentType = WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_MULTIPART_FORM_DATA;
        }
        else if ("image/gif".equals (contentTypeString))
        {
            httpContentType = WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_IMAGE_GIF;
        }
        else if ("image/png".equals (contentTypeString))
        {
            httpContentType = WaveHttpContentType.WAVE_HTTP_CONTENT_TYPE_IMAGE_PNG;
        }
        else if ("image/jpeg".equals (contentTypeString))
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

    public static void getNotImplementedErrorString (final StringBuffer notImplementedErrorString)
    {
        notImplementedErrorString.append ("HTTP/1.1 501 Not Implemented\r\n");
        notImplementedErrorString.append ("Server: Wave World Wide Web Server (W4S) v0.0.1\r\n");
        notImplementedErrorString.append ("Content-Type: text/html\r\n");
        notImplementedErrorString.append ("\r\n");
        notImplementedErrorString.append ("<HTML>\r\n");
        notImplementedErrorString.append ("<TITLE>Wave World Wide Web Server (W4S) v0.0.1</TITLE>\r\n");
        notImplementedErrorString.append ("<H2>Method Not Implemented</H2>\r\n");
        notImplementedErrorString.append ("<BODY>\r\n");
        notImplementedErrorString.append ("<P STYLE=\"COLOR:RED\">Wave World Wide Web Server (W4S) Currently does not support the requested Method.</P>\r\n");
        addFooter (notImplementedErrorString);
        notImplementedErrorString.append ("</BODY>\r\n");
        notImplementedErrorString.append ("</HTML>\r\n");
    }

    public static void getMethodNotAllowedErrorString (final StringBuffer methodNotAllowedErrorString)
    {
        methodNotAllowedErrorString.append ("HTTP/1.1 405 Method Not Allowed\r\n");
        methodNotAllowedErrorString.append ("Server: Wave World Wide Web Server (W4S) v0.0.1\r\n");
        methodNotAllowedErrorString.append ("Allow: GET, HEAD, PUT, POST, TRACE, OPTIONS\r\n");
        methodNotAllowedErrorString.append ("Content-Type: text/html\r\n");
        methodNotAllowedErrorString.append ("\r\n");
        methodNotAllowedErrorString.append ("<HTML>\r\n");
        methodNotAllowedErrorString.append ("<TITLE>Wave World Wide Web Server (W4S) v0.0.1</TITLE>\r\n");
        methodNotAllowedErrorString.append ("<H2>Method Not Allowed</H2>\r\n");
        methodNotAllowedErrorString.append ("<BODY>\r\n");
        methodNotAllowedErrorString.append ("<P STYLE=\"COLOR:RED\">Wave World Wide Web Server (W4S) Currently does not allow the requested Method.</P>\r\n");
        addFooter (methodNotAllowedErrorString);
        methodNotAllowedErrorString.append ("</BODY>\r\n");
        methodNotAllowedErrorString.append ("</HTML>\r\n");
    }

    public static void getNotFoundErrorString (final StringBuffer notFoundErrorString)
    {
        notFoundErrorString.append ("HTTP/1.1 404 Not Found\r\n");
        notFoundErrorString.append ("Server: Wave World Wide Web Server (W4S) v0.0.1\r\n");
        notFoundErrorString.append ("Content-Type: text/html\r\n");
        notFoundErrorString.append ("\r\n");
        notFoundErrorString.append ("<HTML>\r\n");
        notFoundErrorString.append ("<TITLE>Wave World Wide Web Server (W4S) v0.0.1</TITLE>\r\n");
        notFoundErrorString.append ("<H2>Resource Not Found</H2>\r\n");
        notFoundErrorString.append ("<BODY>\r\n");
        notFoundErrorString.append ("<P STYLE=\"COLOR:RED\">Wave World Wide Web Server (W4S) could not find the requested resource.</P>\r\n");
        addFooter (notFoundErrorString);
        notFoundErrorString.append ("</BODY>\r\n");
        notFoundErrorString.append ("</HTML>\r\n");
    }

    public static void getUnauthorizedString (final StringBuffer unAuthorizedString)
    {
        unAuthorizedString.append ("HTTP/1.1 401 Unauthorized\r\n");
        unAuthorizedString.append ("WWW-Authenticate: Basic realm=\"Wave\"\r\n");
        unAuthorizedString.append ("Server: Wave World Wide Web Server (W4S) v0.0.1\r\n");
        unAuthorizedString.append ("Content-Type: text/html\r\n");
        unAuthorizedString.append ("\r\n");
        unAuthorizedString.append ("<HTML>\r\n");
        unAuthorizedString.append ("<TITLE>Wave World Wide Web Server (W4S) v0.0.1</TITLE>\r\n");
        unAuthorizedString.append ("<H2>Unauthorized</H2>\r\n");
        unAuthorizedString.append ("<BODY>\r\n");
        unAuthorizedString.append ("<P STYLE=\"COLOR:RED\">You are required to provide authorization credentials to access the requested resource.</P>\r\n");
        addFooter (unAuthorizedString);
        unAuthorizedString.append ("</BODY>\r\n");
        unAuthorizedString.append ("</HTML>\r\n");
    }

    public static void getBadRequestString (final StringBuffer badRequestString, final String reason)
    {
        badRequestString.append ("HTTP/1.1 400 Bad Request\r\n");
        badRequestString.append ("WWW-Authenticate: Basic realm=\"Wave\"\r\n");
        badRequestString.append ("Server: Wave World Wide Web Server (W4S) v0.0.1\r\n");
        badRequestString.append ("Content-Type: text/html\r\n");
        badRequestString.append ("\r\n");
        badRequestString.append ("<HTML>\r\n");
        badRequestString.append ("<TITLE>Wave World Wide Web Server (W4S) v0.0.1</TITLE>\r\n");
        badRequestString.append ("<H2>Bad Request</H2>\r\n");
        badRequestString.append ("<BODY>\r\n");
        badRequestString.append ("<P STYLE=\"COLOR:RED\">" + reason + "</P>\r\n");
        addFooter (badRequestString);
        badRequestString.append ("</BODY>\r\n");
        badRequestString.append ("</HTML>\r\n");
    }

    public static void getBadRequestString (final StringBuffer badRequestString)
    {
        getBadRequestString (badRequestString, "Bad Request");
    }

    public static void getCreatedString (final StringBuffer createdString, final StringBuffer createdUri)
    {
        createdString.append ("HTTP/1.1 201 Created\r\n");
        createdString.append ("WWW-Authenticate: Basic realm=\"Wave\"\r\n");
        createdString.append ("Server: Wave World Wide Web Server (W4S) v0.0.1\r\n");
        createdString.append ("Content-Type: text/html\r\n");
        createdString.append ("Location: " + createdUri + "\r\n");
        createdString.append ("\r\n");
        createdString.append ("<HTML>\r\n");
        createdString.append ("<TITLE>Wave World Wide Web Server (W4S) v0.0.1</TITLE>\r\n");
        createdString.append ("<H2>Resource Successfully Created</H2>\r\n");
        createdString.append ("<BODY>\r\n");
        createdString.append ("<P STYLE=\"COLOR:BLACK\">The resource has been successfully created.</P>\r\n");
        createdString.append ("<P STYLE=\"COLOR:BLACK\">Newly Created Resource Location : " + createdUri + "</P>\r\n");
        addFooter (createdString);
        createdString.append ("</BODY>\r\n");
        createdString.append ("</HTML>\r\n");
    }

    public static void getCreatedStringForRestXml (final StringBuffer createdString, final StringBuffer createdUri, final StringBuffer xmlBody)
    {
        createdString.append ("HTTP/1.1 201 Created\r\n");
        createdString.append ("WWW-Authenticate: Basic realm=\"Wave\"\r\n");
        createdString.append ("Server: Wave World Wide Web Server (W4S) v0.0.1\r\n");
        createdString.append ("Content-Type: text/xml\r\n");
        createdString.append ("Location: " + createdUri + "\r\n");
        createdString.append ("\r\n");
        createdString.append (xmlBody);
    }

    public static void getDeletedStringForRestXml (final StringBuffer deletedString, final StringBuffer xmlBody)
    {
        deletedString.append ("HTTP/1.1 204 Deleted\r\n");
        deletedString.append ("WWW-Authenticate: Basic realm=\"Wave\"\r\n");
        deletedString.append ("Server: Wave World Wide Web Server (W4S) v0.0.1\r\n");
        deletedString.append ("Content-Type: text/xml\r\n");
        deletedString.append ("\r\n");
        deletedString.append (xmlBody);
    }

    public static void getOkStringForGetForRestXml (final StringBuffer okString, final StringBuffer xmlBody)
    {
        okString.append ("HTTP/1.1 200 OK\r\n");
        okString.append ("Server: Wave World Wide Web Server (W4S) v0.0.1\r\n");
        okString.append ("Content-Type: text/xml\r\n");
        okString.append ("\r\n");
        okString.append (xmlBody);
    }

    public static void getNoContentStringForPutForRestXml (final StringBuffer noContentString)
    {
        noContentString.append ("HTTP/1.1 204 No Content\r\n");
        noContentString.append ("Server: Wave World Wide Web Server (W4S) v0.0.1\r\n");
        noContentString.append ("Content-Type: text/html\r\n");
        noContentString.append ("\r\n");
    }

    public static void getOkStringForGetForRestJson (final StringBuffer okString, final StringBuffer jsonBody)
    {
        okString.append ("HTTP/1.1 200 OK\r\n");
        okString.append ("Server: Wave World Wide Web Server (W4S) v0.0.1\r\n");
        okString.append ("Content-Type: text/json\r\n");
        okString.append ("\r\n");
        okString.append (jsonBody);
    }

    public static void addHeader (final StringBuffer httpResponseString)
    {
        httpResponseString.append ("<H1>\r\n");
        httpResponseString.append ("<P STYLE=\"COLOR:RGB(255, 0, 0); TEXT-ALIGN:CENTER\">Wave World Wide Web Server (W4S)</P>\r\n");
        httpResponseString.append ("</H1>\r\n");
        httpResponseString.append ("<P STYLE=\"COLOR:RGB(200, 200, 200); TEXT-ALIGN:CENTER\"><SUP>V 0.0.1 TB.PS 23.01</SUP></P>\r\n");
    }

    public static void addFooter (final StringBuffer httpResponseString)
    {
        httpResponseString.append ("<P STYLE=\"COLOR:RGB(200, 200, 200)\"><EM><SUB>Wave World Wide Web Server (W4S) TB.PS 23.01. (C) Vidyasagara R. Guntaka et al.</SUB></EM></P>\r\n");
    }
}
