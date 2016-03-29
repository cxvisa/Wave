/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.HttpInterface;

import java.util.Vector;

import com.CxWave.Wave.Framework.ObjectModel.WaveWorker;
import com.CxWave.Wave.Framework.Utils.Socket.AcceptedStreamingSocket;

public class WaveServerPage extends WaveWorker
{
    private String m_path        = "";
    private String m_pageHeading = "";

    public WaveServerPage (final String path)
    {
        super (HttpInterfaceReceiverObjectManager.getInstance ());

        m_path = path;

        WaveServerPageDirectory.registerServerPage (this);
    }

    public String getPath ()
    {
        return m_path;
    }

    public void setPath (final String path)
    {
        m_path = path;
    }

    public String getPageHeading ()
    {
        return m_pageHeading;
    }

    public void setPageHeading (final String pageHeading)
    {
        m_pageHeading = pageHeading;
    }

    public void get (final HttpRequest httpRequest)
    {
        final StringBuffer httpResponseString = new StringBuffer ();
        final AcceptedStreamingSocket acceptedStreamingSocket = httpRequest.getAcceptedStreamingSocket ();

        getWaveServerPagePrePortionForGet (httpResponseString);

        httpResponseString.append ("<H2 STYLE=\"COLOR:RGB(255, 0, 0);TEXT-ALIGN:CENTER;\">" + m_pageHeading + "</H2>\r\n");

        getWaveServerPagePostPortionForGet (httpResponseString);

        if (null != acceptedStreamingSocket)
        {
            acceptedStreamingSocket.send (httpResponseString);
        }
    }

    public void head (final HttpRequest httpRequest)
    {
    }

    public void post (final HttpRequest httpRequest)
    {
        final StringBuffer httpResponseString = new StringBuffer ();
        final AcceptedStreamingSocket acceptedStreamingSocket = httpRequest.getAcceptedStreamingSocket ();

        getWaveServerPagePrePortionForPost (httpResponseString);

        httpResponseString.append ("<H2 STYLE=\"COLOR:RGB(255, 0, 0);TEXT-ALIGN:CENTER;\">" + m_pageHeading + "</H2>\r\n");

        getWaveServerPagePostPortionForPost (httpResponseString);

        if (null != acceptedStreamingSocket)
        {
            acceptedStreamingSocket.send (httpResponseString);
        }
    }

    public void put (final HttpRequest httpRequest)
    {
        final StringBuffer httpResponseString = new StringBuffer ();
        final AcceptedStreamingSocket acceptedStreamingSocket = httpRequest.getAcceptedStreamingSocket ();

        getWaveServerPagePrePortionForPut (httpResponseString);

        httpResponseString.append ("<H2 STYLE=\"COLOR:RGB(255, 0, 0);TEXT-ALIGN:CENTER;\">" + m_pageHeading + "</H2>\r\n");

        getWaveServerPagePostPortionForPut (httpResponseString);

        if (null != acceptedStreamingSocket)
        {
            acceptedStreamingSocket.send (httpResponseString);
        }
    }

    public void deleteMethod (final HttpRequest httpRequest)
    {
        final StringBuffer httpResponseString = new StringBuffer ();
        final AcceptedStreamingSocket acceptedStreamingSocket = httpRequest.getAcceptedStreamingSocket ();

        getWaveServerPagePrePortionForDelete (httpResponseString);

        httpResponseString.append ("<H2 STYLE=\"COLOR:RGB(255, 0, 0);TEXT-ALIGN:CENTER;\">" + m_pageHeading + "</H2>\r\n");

        getWaveServerPagePostPortionForDelete (httpResponseString);

        if (null != acceptedStreamingSocket)
        {
            acceptedStreamingSocket.send (httpResponseString);
        }
    }

    public void options (final HttpRequest httpRequest)
    {
    }

    public void traceX (final HttpRequest httpRequest)
    {
    }

    public void connect (final HttpRequest httpRequest)
    {
    }

    public void getWaveServerPagePrePortionForGet (final StringBuffer waveServerPagePrePortionForGet)
    {
        final Vector<String> optionsForGet = new Vector<String> ();
        int numberOfOptionsForGet;
        int i = 0;

        getListOfOptionsForGet (optionsForGet);

        numberOfOptionsForGet = optionsForGet.size ();

        waveServerPagePrePortionForGet.append ("HTTP/1.1 200 OK\r\n");
        waveServerPagePrePortionForGet.append ("Server: Wave World Wide Web Server (W4S) v0.0.1\r\n");
        waveServerPagePrePortionForGet.append ("Content-Type: text/html\r\n");
        waveServerPagePrePortionForGet.append ("\r\n");
        waveServerPagePrePortionForGet.append ("<HTML>\r\n");

        waveServerPagePrePortionForGet.append ("<HEAD>\r\n");

        waveServerPagePrePortionForGet.append ("<STYLE>\r\n");

        waveServerPagePrePortionForGet.append ("A:VISITED\r\n");
        waveServerPagePrePortionForGet.append ("{\r\n");
        waveServerPagePrePortionForGet.append ("COLOR:RGB(255, 0 ,0);\r\n");
        waveServerPagePrePortionForGet.append ("TEXT-DECORATION:NONE;\r\n");
        waveServerPagePrePortionForGet.append ("}\r\n");

        waveServerPagePrePortionForGet.append ("TABLE\r\n");
        waveServerPagePrePortionForGet.append ("{\r\n");
        waveServerPagePrePortionForGet.append ("BORDER-COLLAPSE:COLLAPSE;\r\n");
        waveServerPagePrePortionForGet.append ("LEFT-MARGIN:AUTO;\r\n");
        waveServerPagePrePortionForGet.append ("RIGHT-MARGIN:AUTO;\r\n");
        waveServerPagePrePortionForGet.append ("}\r\n");
        waveServerPagePrePortionForGet.append ("TABLE, TD, TH\r\n");
        waveServerPagePrePortionForGet.append ("{\r\n");
        waveServerPagePrePortionForGet.append ("BORDER:1PX SOLID RED;\r\n");
        waveServerPagePrePortionForGet.append ("}\r\n");

        waveServerPagePrePortionForGet.append ("A:LINK\r\n");
        waveServerPagePrePortionForGet.append ("{\r\n");
        waveServerPagePrePortionForGet.append ("COLOR:RGB(0, 0 ,255);\r\n");
        waveServerPagePrePortionForGet.append ("TEXT-DECORATION:NONE;\r\n");
        waveServerPagePrePortionForGet.append ("}\r\n");

        waveServerPagePrePortionForGet.append ("A:HOVER\r\n");
        waveServerPagePrePortionForGet.append ("{\r\n");
        waveServerPagePrePortionForGet.append ("COLOR:RGB(0, 255 ,0)\r\n");
        waveServerPagePrePortionForGet.append ("}\r\n");

        waveServerPagePrePortionForGet.append ("A:ACTIVE\r\n");
        waveServerPagePrePortionForGet.append ("{\r\n");
        waveServerPagePrePortionForGet.append ("COLOR:RGB(255, 255 ,0)\r\n");
        waveServerPagePrePortionForGet.append ("}\r\n");

        waveServerPagePrePortionForGet.append ("</STYLE>\r\n");

        waveServerPagePrePortionForGet.append ("</HEAD>\r\n");

        waveServerPagePrePortionForGet.append ("<BODY LINK=\"COLOR:RGB(255,0,0)\" VLINK=\"COLOR:RGB(0, 255, 0)\" ALINK=\"COLOR:RGB(0, 0, 255)\">\r\n");
        waveServerPagePrePortionForGet.append ("<DIV id=\"EntirePage\" STYLE=\"BACKGROUND-COLOR:RGB(255, 255, 255)\">\r\n");

        waveServerPagePrePortionForGet.append ("<DIV id=\"Header\" STYLE=\"WIDTH:100%;HEIGHT:5%;BACKGROUND-COLOR:RGB(255, 255,255);COLOR:RGB(200, 200, 200);TEXT-ALIGN:CENTER;\">\r\n");
        waveServerPagePrePortionForGet.append ("<A>\r\n");
        waveServerPagePrePortionForGet.append ("<H1 STYLE=\"MARGIN-BOTTOM:0\">Wave World Wide Web Server (W4S)</H1>\r\n");
        waveServerPagePrePortionForGet.append ("</A>\r\n");
        waveServerPagePrePortionForGet.append ("</DIV>\r\n");

        waveServerPagePrePortionForGet.append ("<DIV id=\"HeaderOptions\" STYLE=\"WIDTH:100%;HEIGHT:3%;BACKGROUND-COLOR:RGB(0, 0,0);COLOR:RGB(255, 255, 255);TEXT-ALIGN:CENTER;FLOAT:LEFT\">\r\n");
        waveServerPagePrePortionForGet.append ("<A HREF=\"/\">Home</A>\r\n");
        waveServerPagePrePortionForGet.append (" | \r\n");
        waveServerPagePrePortionForGet.append ("<A HREF=\"/\">About</A>\r\n");
        waveServerPagePrePortionForGet.append (" | \r\n");
        waveServerPagePrePortionForGet.append ("<A HREF=\"/\">Contact Us</A>\r\n");
        waveServerPagePrePortionForGet.append ("</DIV>\r\n");

        waveServerPagePrePortionForGet.append ("<DIV id=\"MenuPane\" STYLE=\"WIDTH:20%;HEIGHT:92%;BACKGROUND-COLOR:RGB(202,200,200);COLOR:RGB(255,255,255);TEXT-ALIGN:LEFT;FLOAT:LEFT\">\r\n");

        waveServerPagePrePortionForGet.append ("<HR/>\r\n");

        if (0 < numberOfOptionsForGet)
        {
            waveServerPagePrePortionForGet.append ("<UL>\r\n");

            for (i = 0; i < numberOfOptionsForGet; i++)
            {
                waveServerPagePrePortionForGet.append ("<LI><A HREF=\"" + m_path + "/" + optionsForGet.get (i) + "\">" + optionsForGet.get (i) + "</A></BR></LI>\r\n");
            }

            waveServerPagePrePortionForGet.append ("</UL>\r\n");
        }

        waveServerPagePrePortionForGet.append ("<HR/>\r\n");

        waveServerPagePrePortionForGet.append ("</DIV>\r\n");

        waveServerPagePrePortionForGet.append ("<DIV id=\"ContentPane\" STYLE=\"WIDTH:80%;HEIGHT:92%;BACKGROUND-COLOR:RGB(255, 255, 255);COLOR:RGB(0, 0, 0);TEXT-ALIGN:LEFT;FLOAT:LEFT\">\r\n");
    }

    public void getWaveServerPagePostPortionForGet (final StringBuffer waveServerPagePostPortionForGet)
    {
        waveServerPagePostPortionForGet.append ("</DIV>\r\n");

        waveServerPagePostPortionForGet.append ("</DIV>\r\n");
        waveServerPagePostPortionForGet.append ("</BODY>\r\n");
        waveServerPagePostPortionForGet.append ("</HTML>\r\n");
    }

    public void getWaveServerPagePrePortionForPost (final StringBuffer waveServerPagePrePortionForPost)
    {
        final Vector<String> optionsForPost = new Vector<String> ();
        int numberOfOptionsForPost;
        int i = 0;

        getListOfOptionsForPost (optionsForPost);

        numberOfOptionsForPost = optionsForPost.size ();

        waveServerPagePrePortionForPost.append ("HTTP/1.1 200 OK\r\n");
        waveServerPagePrePortionForPost.append ("Server: Wave World Wide Web Server (W4S) v0.0.1\r\n");
        waveServerPagePrePortionForPost.append ("Content-Type: text/html\r\n");
        waveServerPagePrePortionForPost.append ("\r\n");
        waveServerPagePrePortionForPost.append ("<HTML>\r\n");

        waveServerPagePrePortionForPost.append ("<HEAD>\r\n");

        waveServerPagePrePortionForPost.append ("<STYLE>\r\n");

        waveServerPagePrePortionForPost.append ("A:VISITED\r\n");
        waveServerPagePrePortionForPost.append ("{\r\n");
        waveServerPagePrePortionForPost.append ("COLOR:RGB(255, 0 ,0);\r\n");
        waveServerPagePrePortionForPost.append ("TEXT-DECORATION:NONE;\r\n");
        waveServerPagePrePortionForPost.append ("}\r\n");

        waveServerPagePrePortionForPost.append ("TABLE\r\n");
        waveServerPagePrePortionForPost.append ("{\r\n");
        waveServerPagePrePortionForPost.append ("BORDER-COLLAPSE:COLLAPSE;\r\n");
        waveServerPagePrePortionForPost.append ("LEFT-MARGIN:AUTO;\r\n");
        waveServerPagePrePortionForPost.append ("RIGHT-MARGIN:AUTO;\r\n");
        waveServerPagePrePortionForPost.append ("}\r\n");
        waveServerPagePrePortionForPost.append ("TABLE, TD, TH\r\n");
        waveServerPagePrePortionForPost.append ("{\r\n");
        waveServerPagePrePortionForPost.append ("BORDER:1PX SOLID RED;\r\n");
        waveServerPagePrePortionForPost.append ("}\r\n");

        waveServerPagePrePortionForPost.append ("A:LINK\r\n");
        waveServerPagePrePortionForPost.append ("{\r\n");
        waveServerPagePrePortionForPost.append ("COLOR:RGB(0, 0 ,255);\r\n");
        waveServerPagePrePortionForPost.append ("TEXT-DECORATION:NONE;\r\n");
        waveServerPagePrePortionForPost.append ("}\r\n");

        waveServerPagePrePortionForPost.append ("A:HOVER\r\n");
        waveServerPagePrePortionForPost.append ("{\r\n");
        waveServerPagePrePortionForPost.append ("COLOR:RGB(0, 255 ,0)\r\n");
        waveServerPagePrePortionForPost.append ("}\r\n");

        waveServerPagePrePortionForPost.append ("A:ACTIVE\r\n");
        waveServerPagePrePortionForPost.append ("{\r\n");
        waveServerPagePrePortionForPost.append ("COLOR:RGB(255, 255 ,0)\r\n");
        waveServerPagePrePortionForPost.append ("}\r\n");

        waveServerPagePrePortionForPost.append ("</STYLE>\r\n");

        waveServerPagePrePortionForPost.append ("</HEAD>\r\n");

        waveServerPagePrePortionForPost.append ("<BODY LINK=\"COLOR:RGB(255,0,0)\" VLINK=\"COLOR:RGB(0, 255, 0)\" ALINK=\"COLOR:RGB(0, 0, 255)\">\r\n");
        waveServerPagePrePortionForPost.append ("<DIV id=\"EntirePage\" STYLE=\"BACKGROUND-COLOR:RGB(255, 255, 255)\">\r\n");

        waveServerPagePrePortionForPost.append ("<DIV id=\"Header\" STYLE=\"WIDTH:100%;HEIGHT:5%;BACKGROUND-COLOR:RGB(255, 255,255);COLOR:RGB(200, 200, 200);TEXT-ALIGN:CENTER;\">\r\n");
        waveServerPagePrePortionForPost.append ("<A>\r\n");
        waveServerPagePrePortionForPost.append ("<H1 STYLE=\"MARGIN-BOTTOM:0\">Wave World Wide Web Server (W4S)</H1>\r\n");
        waveServerPagePrePortionForPost.append ("</A>\r\n");
        waveServerPagePrePortionForPost.append ("</DIV>\r\n");

        waveServerPagePrePortionForPost.append ("<DIV id=\"HeaderOptions\" STYLE=\"WIDTH:100%;HEIGHT:3%;BACKGROUND-COLOR:RGB(0, 0,0);COLOR:RGB(255, 255, 255);TEXT-ALIGN:CENTER;FLOAT:LEFT\">\r\n");
        waveServerPagePrePortionForPost.append ("<A HREF=\"/\">Home</A>\r\n");
        waveServerPagePrePortionForPost.append (" | \r\n");
        waveServerPagePrePortionForPost.append ("<A HREF=\"/\">About</A>\r\n");
        waveServerPagePrePortionForPost.append (" | \r\n");
        waveServerPagePrePortionForPost.append ("<A HREF=\"/\">Contact Us</A>\r\n");
        waveServerPagePrePortionForPost.append ("</DIV>\r\n");

        waveServerPagePrePortionForPost.append ("<DIV id=\"MenuPane\" STYLE=\"WIDTH:20%;HEIGHT:92%;BACKGROUND-COLOR:RGB(202,200,200);COLOR:RGB(255,255,255);TEXT-ALIGN:LEFT;FLOAT:LEFT\">\r\n");

        waveServerPagePrePortionForPost.append ("<HR/>\r\n");

        if (0 < numberOfOptionsForPost)
        {
            waveServerPagePrePortionForPost.append ("<UL>\r\n");

            for (i = 0; i < numberOfOptionsForPost; i++)
            {
                waveServerPagePrePortionForPost.append ("<LI><A HREF=\"" + m_path + "/" + optionsForPost.get (i) + "\">" + optionsForPost.get (i) + "</A></BR></LI>\r\n");
            }

            waveServerPagePrePortionForPost.append ("</UL>\r\n");
        }

        waveServerPagePrePortionForPost.append ("<HR/>\r\n");

        waveServerPagePrePortionForPost.append ("</DIV>\r\n");

        waveServerPagePrePortionForPost.append ("<DIV id=\"ContentPane\" STYLE=\"WIDTH:80%;HEIGHT:92%;BACKGROUND-COLOR:RGB(255, 255, 255);COLOR:RGB(0, 0, 0);TEXT-ALIGN:LEFT;FLOAT:LEFT\">\r\n");
    }

    public void getWaveServerPagePostPortionForPost (final StringBuffer waveServerPagePostPortionForPost)
    {
        waveServerPagePostPortionForPost.append ("</DIV>\r\n");

        waveServerPagePostPortionForPost.append ("</DIV>\r\n");
        waveServerPagePostPortionForPost.append ("</BODY>\r\n");
        waveServerPagePostPortionForPost.append ("</HTML>\r\n");
    }

    public void getListOfOptionsForGet (final Vector<String> optionsForGet)
    {
    }

    public void getListOfOptionsForPost (final Vector<String> optionsForPost)
    {
    }

    public void getListOfOptionsForPut (final Vector<String> optionsForPost)
    {
    }

    public void getListOfOptionsForDelete (final Vector<String> optionsForDelete)
    {
    }

    public void getWaveServerPagePrePortionForPut (final StringBuffer waveServerPagePrePortionForPut)
    {
        final Vector<String> optionsForPut = new Vector<String> ();
        int numberOfOptionsForPut;
        int i = 0;

        getListOfOptionsForPut (optionsForPut);

        numberOfOptionsForPut = optionsForPut.size ();

        waveServerPagePrePortionForPut.append ("HTTP/1.1 200 OK\r\n");
        waveServerPagePrePortionForPut.append ("Server: Wave World Wide Web Server (W4S) v0.0.1\r\n");
        waveServerPagePrePortionForPut.append ("Content-Type: text/html\r\n");
        waveServerPagePrePortionForPut.append ("\r\n");
        waveServerPagePrePortionForPut.append ("<HTML>\r\n");

        waveServerPagePrePortionForPut.append ("<HEAD>\r\n");

        waveServerPagePrePortionForPut.append ("<STYLE>\r\n");

        waveServerPagePrePortionForPut.append ("A:VISITED\r\n");
        waveServerPagePrePortionForPut.append ("{\r\n");
        waveServerPagePrePortionForPut.append ("COLOR:RGB(255, 0 ,0);\r\n");
        waveServerPagePrePortionForPut.append ("TEXT-DECORATION:NONE;\r\n");
        waveServerPagePrePortionForPut.append ("}\r\n");

        waveServerPagePrePortionForPut.append ("TABLE\r\n");
        waveServerPagePrePortionForPut.append ("{\r\n");
        waveServerPagePrePortionForPut.append ("BORDER-COLLAPSE:COLLAPSE;\r\n");
        waveServerPagePrePortionForPut.append ("LEFT-MARGIN:AUTO;\r\n");
        waveServerPagePrePortionForPut.append ("RIGHT-MARGIN:AUTO;\r\n");
        waveServerPagePrePortionForPut.append ("}\r\n");
        waveServerPagePrePortionForPut.append ("TABLE, TD, TH\r\n");
        waveServerPagePrePortionForPut.append ("{\r\n");
        waveServerPagePrePortionForPut.append ("BORDER:1PX SOLID RED;\r\n");
        waveServerPagePrePortionForPut.append ("}\r\n");

        waveServerPagePrePortionForPut.append ("A:LINK\r\n");
        waveServerPagePrePortionForPut.append ("{\r\n");
        waveServerPagePrePortionForPut.append ("COLOR:RGB(0, 0 ,255);\r\n");
        waveServerPagePrePortionForPut.append ("TEXT-DECORATION:NONE;\r\n");
        waveServerPagePrePortionForPut.append ("}\r\n");

        waveServerPagePrePortionForPut.append ("A:HOVER\r\n");
        waveServerPagePrePortionForPut.append ("{\r\n");
        waveServerPagePrePortionForPut.append ("COLOR:RGB(0, 255 ,0)\r\n");
        waveServerPagePrePortionForPut.append ("}\r\n");

        waveServerPagePrePortionForPut.append ("A:ACTIVE\r\n");
        waveServerPagePrePortionForPut.append ("{\r\n");
        waveServerPagePrePortionForPut.append ("COLOR:RGB(255, 255 ,0)\r\n");
        waveServerPagePrePortionForPut.append ("}\r\n");

        waveServerPagePrePortionForPut.append ("</STYLE>\r\n");

        waveServerPagePrePortionForPut.append ("</HEAD>\r\n");

        waveServerPagePrePortionForPut.append ("<BODY LINK=\"COLOR:RGB(255,0,0)\" VLINK=\"COLOR:RGB(0, 255, 0)\" ALINK=\"COLOR:RGB(0, 0, 255)\">\r\n");
        waveServerPagePrePortionForPut.append ("<DIV id=\"EntirePage\" STYLE=\"BACKGROUND-COLOR:RGB(255, 255, 255)\">\r\n");

        waveServerPagePrePortionForPut.append ("<DIV id=\"Header\" STYLE=\"WIDTH:100%;HEIGHT:5%;BACKGROUND-COLOR:RGB(255, 255,255);COLOR:RGB(200, 200, 200);TEXT-ALIGN:CENTER;\">\r\n");
        waveServerPagePrePortionForPut.append ("<A>\r\n");
        waveServerPagePrePortionForPut.append ("<H1 STYLE=\"MARGIN-BOTTOM:0\">Wave World Wide Web Server (W4S)</H1>\r\n");
        waveServerPagePrePortionForPut.append ("</A>\r\n");
        waveServerPagePrePortionForPut.append ("</DIV>\r\n");

        waveServerPagePrePortionForPut.append ("<DIV id=\"HeaderOptions\" STYLE=\"WIDTH:100%;HEIGHT:3%;BACKGROUND-COLOR:RGB(0, 0,0);COLOR:RGB(255, 255, 255);TEXT-ALIGN:CENTER;FLOAT:LEFT\">\r\n");
        waveServerPagePrePortionForPut.append ("<A HREF=\"/\">Home</A>\r\n");
        waveServerPagePrePortionForPut.append (" | \r\n");
        waveServerPagePrePortionForPut.append ("<A HREF=\"/\">About</A>\r\n");
        waveServerPagePrePortionForPut.append (" | \r\n");
        waveServerPagePrePortionForPut.append ("<A HREF=\"/\">Contact Us</A>\r\n");
        waveServerPagePrePortionForPut.append ("</DIV>\r\n");

        waveServerPagePrePortionForPut.append ("<DIV id=\"MenuPane\" STYLE=\"WIDTH:20%;HEIGHT:92%;BACKGROUND-COLOR:RGB(202,200,200);COLOR:RGB(255,255,255);TEXT-ALIGN:LEFT;FLOAT:LEFT\">\r\n");

        waveServerPagePrePortionForPut.append ("<HR/>\r\n");

        if (0 < numberOfOptionsForPut)
        {
            waveServerPagePrePortionForPut.append ("<UL>\r\n");

            for (i = 0; i < numberOfOptionsForPut; i++)
            {
                waveServerPagePrePortionForPut.append ("<LI><A HREF=\"" + m_path + "/" + optionsForPut.get (i) + "\">" + optionsForPut.get (i) + "</A></BR></LI>\r\n");
            }

            waveServerPagePrePortionForPut.append ("</UL>\r\n");
        }

        waveServerPagePrePortionForPut.append ("<HR/>\r\n");

        waveServerPagePrePortionForPut.append ("</DIV>\r\n");

        waveServerPagePrePortionForPut.append ("<DIV id=\"ContentPane\" STYLE=\"WIDTH:80%;HEIGHT:92%;BACKGROUND-COLOR:RGB(255, 255, 255);COLOR:RGB(0, 0, 0);TEXT-ALIGN:LEFT;FLOAT:LEFT\">\r\n");
    }

    void getWaveServerPagePostPortionForPut (final StringBuffer waveServerPagePostPortionForPut)
    {
        waveServerPagePostPortionForPut.append ("</DIV>\r\n");

        waveServerPagePostPortionForPut.append ("</DIV>\r\n");
        waveServerPagePostPortionForPut.append ("</BODY>\r\n");
        waveServerPagePostPortionForPut.append ("</HTML>\r\n");
    }

    public void getWaveServerPagePrePortionForDelete (final StringBuffer waveServerPagePrePortionForDelete)
    {
        final Vector<String> optionsForDelete = new Vector<String> ();
        int numberOfOptionsForDelete;
        int i = 0;

        getListOfOptionsForDelete (optionsForDelete);

        numberOfOptionsForDelete = optionsForDelete.size ();

        waveServerPagePrePortionForDelete.append ("HTTP/1.1 200 OK\r\n");
        waveServerPagePrePortionForDelete.append ("Server: Wave World Wide Web Server (W4S) v0.0.1\r\n");
        waveServerPagePrePortionForDelete.append ("Content-Type: text/html\r\n");
        waveServerPagePrePortionForDelete.append ("\r\n");
        waveServerPagePrePortionForDelete.append ("<HTML>\r\n");

        waveServerPagePrePortionForDelete.append ("<HEAD>\r\n");

        waveServerPagePrePortionForDelete.append ("<STYLE>\r\n");

        waveServerPagePrePortionForDelete.append ("A:VISITED\r\n");
        waveServerPagePrePortionForDelete.append ("{\r\n");
        waveServerPagePrePortionForDelete.append ("COLOR:RGB(255, 0 ,0);\r\n");
        waveServerPagePrePortionForDelete.append ("TEXT-DECORATION:NONE;\r\n");
        waveServerPagePrePortionForDelete.append ("}\r\n");

        waveServerPagePrePortionForDelete.append ("TABLE\r\n");
        waveServerPagePrePortionForDelete.append ("{\r\n");
        waveServerPagePrePortionForDelete.append ("BORDER-COLLAPSE:COLLAPSE;\r\n");
        waveServerPagePrePortionForDelete.append ("LEFT-MARGIN:AUTO;\r\n");
        waveServerPagePrePortionForDelete.append ("RIGHT-MARGIN:AUTO;\r\n");
        waveServerPagePrePortionForDelete.append ("}\r\n");
        waveServerPagePrePortionForDelete.append ("TABLE, TD, TH\r\n");
        waveServerPagePrePortionForDelete.append ("{\r\n");
        waveServerPagePrePortionForDelete.append ("BORDER:1PX SOLID RED;\r\n");
        waveServerPagePrePortionForDelete.append ("}\r\n");

        waveServerPagePrePortionForDelete.append ("A:LINK\r\n");
        waveServerPagePrePortionForDelete.append ("{\r\n");
        waveServerPagePrePortionForDelete.append ("COLOR:RGB(0, 0 ,255);\r\n");
        waveServerPagePrePortionForDelete.append ("TEXT-DECORATION:NONE;\r\n");
        waveServerPagePrePortionForDelete.append ("}\r\n");

        waveServerPagePrePortionForDelete.append ("A:HOVER\r\n");
        waveServerPagePrePortionForDelete.append ("{\r\n");
        waveServerPagePrePortionForDelete.append ("COLOR:RGB(0, 255 ,0)\r\n");
        waveServerPagePrePortionForDelete.append ("}\r\n");

        waveServerPagePrePortionForDelete.append ("A:ACTIVE\r\n");
        waveServerPagePrePortionForDelete.append ("{\r\n");
        waveServerPagePrePortionForDelete.append ("COLOR:RGB(255, 255 ,0)\r\n");
        waveServerPagePrePortionForDelete.append ("}\r\n");

        waveServerPagePrePortionForDelete.append ("</STYLE>\r\n");

        waveServerPagePrePortionForDelete.append ("</HEAD>\r\n");

        waveServerPagePrePortionForDelete.append ("<BODY LINK=\"COLOR:RGB(255,0,0)\" VLINK=\"COLOR:RGB(0, 255, 0)\" ALINK=\"COLOR:RGB(0, 0, 255)\">\r\n");
        waveServerPagePrePortionForDelete.append ("<DIV id=\"EntirePage\" STYLE=\"BACKGROUND-COLOR:RGB(255, 255, 255)\">\r\n");

        waveServerPagePrePortionForDelete.append ("<DIV id=\"Header\" STYLE=\"WIDTH:100%;HEIGHT:5%;BACKGROUND-COLOR:RGB(255, 255,255);COLOR:RGB(200, 200, 200);TEXT-ALIGN:CENTER;\">\r\n");
        waveServerPagePrePortionForDelete.append ("<A>\r\n");
        waveServerPagePrePortionForDelete.append ("<H1 STYLE=\"MARGIN-BOTTOM:0\">Wave World Wide Web Server (W4S)</H1>\r\n");
        waveServerPagePrePortionForDelete.append ("</A>\r\n");
        waveServerPagePrePortionForDelete.append ("</DIV>\r\n");

        waveServerPagePrePortionForDelete.append ("<DIV id=\"HeaderOptions\" STYLE=\"WIDTH:100%;HEIGHT:3%;BACKGROUND-COLOR:RGB(0, 0,0);COLOR:RGB(255, 255, 255);TEXT-ALIGN:CENTER;FLOAT:LEFT\">\r\n");
        waveServerPagePrePortionForDelete.append ("<A HREF=\"/\">Home</A>\r\n");
        waveServerPagePrePortionForDelete.append (" | \r\n");
        waveServerPagePrePortionForDelete.append ("<A HREF=\"/\">About</A>\r\n");
        waveServerPagePrePortionForDelete.append (" | \r\n");
        waveServerPagePrePortionForDelete.append ("<A HREF=\"/\">Contact Us</A>\r\n");
        waveServerPagePrePortionForDelete.append ("</DIV>\r\n");

        waveServerPagePrePortionForDelete.append ("<DIV id=\"MenuPane\" STYLE=\"WIDTH:20%;HEIGHT:92%;BACKGROUND-COLOR:RGB(202,200,200);COLOR:RGB(255,255,255);TEXT-ALIGN:LEFT;FLOAT:LEFT\">\r\n");

        waveServerPagePrePortionForDelete.append ("<HR/>\r\n");

        if (0 < numberOfOptionsForDelete)
        {
            waveServerPagePrePortionForDelete.append ("<UL>\r\n");

            for (i = 0; i < numberOfOptionsForDelete; i++)
            {
                waveServerPagePrePortionForDelete.append ("<LI><A HREF=\"" + m_path + "/" + optionsForDelete.get (i) + "\">" + optionsForDelete.get (i) + "</A></BR></LI>\r\n");
            }

            waveServerPagePrePortionForDelete.append ("</UL>\r\n");
        }

        waveServerPagePrePortionForDelete.append ("<HR/>\r\n");

        waveServerPagePrePortionForDelete.append ("</DIV>\r\n");

        waveServerPagePrePortionForDelete.append ("<DIV id=\"ContentPane\" STYLE=\"WIDTH:80%;HEIGHT:92%;BACKGROUND-COLOR:RGB(255, 255, 255);COLOR:RGB(0, 0, 0);TEXT-ALIGN:LEFT;FLOAT:LEFT\">\r\n");
    }

    public void getWaveServerPagePostPortionForDelete (final StringBuffer waveServerPagePostPortionForDelete)
    {
        waveServerPagePostPortionForDelete.append ("</DIV>\r\n");

        waveServerPagePostPortionForDelete.append ("</DIV>\r\n");
        waveServerPagePostPortionForDelete.append ("</BODY>\r\n");
        waveServerPagePostPortionForDelete.append ("</HTML>\r\n");
    }

    public void requestHandlerForGet (final HttpRequest httpRequest)
    {
    }
}
