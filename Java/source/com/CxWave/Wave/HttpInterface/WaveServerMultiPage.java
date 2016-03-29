/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.HttpInterface;

import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

import com.CxWave.Wave.Framework.Utils.Socket.AcceptedStreamingSocket;

public class WaveServerMultiPage extends WaveServerPage
{
    Map<String, WaveServerMultiPageRequestHandler> m_multiPageRequestHandlersForGet     = new HashMap<String, WaveServerMultiPageRequestHandler> ();
    Vector<String>                                 m_multiPageOptionsForGet             = new Vector<String> ();
    Map<String, WaveServerMultiPageRequestHandler> m_multiPageRequestHandlersForHead    = new HashMap<String, WaveServerMultiPageRequestHandler> ();
    Map<String, WaveServerMultiPageRequestHandler> m_multiPageRequestHandlersForPut     = new HashMap<String, WaveServerMultiPageRequestHandler> ();
    Vector<String>                                 m_multiPageOptionsForPut             = new Vector<String> ();
    Map<String, WaveServerMultiPageRequestHandler> m_multiPageRequestHandlersForPost    = new HashMap<String, WaveServerMultiPageRequestHandler> ();
    Vector<String>                                 m_multiPageOptionsForPost            = new Vector<String> ();
    Map<String, WaveServerMultiPageRequestHandler> m_multiPageRequestHandlersForDelete  = new HashMap<String, WaveServerMultiPageRequestHandler> ();
    Vector<String>                                 m_multiPageOptionsForDelete          = new Vector<String> ();
    Map<String, WaveServerMultiPageRequestHandler> m_multiPageRequestHandlersForOptions = new HashMap<String, WaveServerMultiPageRequestHandler> ();
    Map<String, WaveServerMultiPageRequestHandler> m_multiPageRequestHandlersForConnect = new HashMap<String, WaveServerMultiPageRequestHandler> ();
    Map<String, WaveServerMultiPageRequestHandler> m_multiPageRequestHandlersForTrace   = new HashMap<String, WaveServerMultiPageRequestHandler> ();

    public WaveServerMultiPage (final HttpInterfaceReceiverObjectManager httpInterfaceReceiverObjectManager, final String path)
    {
        super (httpInterfaceReceiverObjectManager, path);
    }

    public boolean isAKnownWaveServerMultiPageRequestHandlerForGet (final String path)
    {
        return (m_multiPageRequestHandlersForGet.containsKey (path));
    }

    public boolean isAKnownWaveServerMultiPageRequestHandlerForPost (final String path)
    {
        return (m_multiPageRequestHandlersForPost.containsKey (path));
    }

    public boolean isAKnownWaveServerMultiPageRequestHandlerForPut (final String path)
    {
        return (m_multiPageRequestHandlersForPut.containsKey (path));
    }

    public boolean isAKnownWaveServerMultiPageRequestHandlerForDelete (final String path)
    {
        return (m_multiPageRequestHandlersForDelete.containsKey (path));
    }

    public void addWaveServerMultiPageRequestHandlerForGet (final String path, final WaveServerMultiPageRequestHandler waveServerMultiPageRequestHandler)
    {
        if (false == (isAKnownWaveServerMultiPageRequestHandlerForGet (path)))
        {
            m_multiPageRequestHandlersForGet.put (path, waveServerMultiPageRequestHandler);
            m_multiPageOptionsForGet.add (path);

            WaveServerPageDirectory.registerServerPage ((getPath ()) + "/" + path, this);
        }
        else
        {
            fatalTracePrintf ("WaveServerMultiPage.addWaveServerMultiPageRequestHandlerForGet : An option already exists with the path \"%s\"", path);
            waveAssert ();
        }
    }

    public void addWaveServerMultiPageRequestHandlerForPost (final String path, final WaveServerMultiPageRequestHandler waveServerMultiPageRequestHandler)
    {
        if (false == (isAKnownWaveServerMultiPageRequestHandlerForPost (path)))
        {
            m_multiPageRequestHandlersForPost.put (path, waveServerMultiPageRequestHandler);
            m_multiPageOptionsForPost.add (path);

            // WaveServerPageDirectory.registerServerPage ((getPath ()) + "/" + path, this);
        }
        else
        {
            fatalTracePrintf ("WaveServerMultiPage.addWaveServerMultiPageRequestHandlerForPost : An option already exists with the path \"%s\"", path);
            waveAssert ();
        }
    }

    public void addWaveServerMultiPageRequestHandlerForPut (final String path, final WaveServerMultiPageRequestHandler waveServerMultiPageRequestHandler)
    {
        if (false == (isAKnownWaveServerMultiPageRequestHandlerForPut (path)))
        {
            m_multiPageRequestHandlersForPut.put (path, waveServerMultiPageRequestHandler);
            m_multiPageOptionsForPut.add (path);

            // WaveServerPageDirectory.registerServerPage ((getPath ()) + "/" + path, this);
        }
        else
        {
            fatalTracePrintf ("WaveServerMultiPage.addWaveServerMultiPageRequestHandlerForPut : An option already exists with the path \"%s\"", path);
            waveAssert ();
        }
    }

    public void addWaveServerMultiPageRequestHandlerForDelete (final String path, final WaveServerMultiPageRequestHandler waveServerMultiPageRequestHandler)
    {
        if (false == (isAKnownWaveServerMultiPageRequestHandlerForDelete (path)))
        {
            m_multiPageRequestHandlersForDelete.put (path, waveServerMultiPageRequestHandler);
            m_multiPageOptionsForDelete.add (path);

            // WaveServerPageDirectory.registerServerPage ((getPath ()) + "/" + path, this);
        }
        else
        {
            fatalTracePrintf ("WaveServerMultiPage.addWaveServerMultiPageRequestHandlerForDelete : An option already exists with the path \"%s\"", path);
            waveAssert ();
        }
    }

    public WaveServerMultiPageRequestHandler getWaveServerMultiPageRequestHandlerForGet (final String path)
    {
        WaveServerMultiPageRequestHandler waveServerMultiPageRequestHandler = null;

        if (true == (isAKnownWaveServerMultiPageRequestHandlerForGet (path)))
        {
            waveServerMultiPageRequestHandler = m_multiPageRequestHandlersForGet.get (path);
        }

        return (waveServerMultiPageRequestHandler);
    }

    public WaveServerMultiPageRequestHandler getWaveServerMultiPageRequestHandlerForPost (final String path)
    {
        WaveServerMultiPageRequestHandler waveServerMultiPageRequestHandler = null;

        if (true == (isAKnownWaveServerMultiPageRequestHandlerForPost (path)))
        {
            waveServerMultiPageRequestHandler = m_multiPageRequestHandlersForPost.get (path);
        }

        return (waveServerMultiPageRequestHandler);
    }

    public WaveServerMultiPageRequestHandler getWaveServerMultiPageRequestHandlerForPut (final String path)
    {
        WaveServerMultiPageRequestHandler waveServerMultiPageRequestHandler = null;

        if (true == (isAKnownWaveServerMultiPageRequestHandlerForPut (path)))
        {
            waveServerMultiPageRequestHandler = m_multiPageRequestHandlersForPut.get (path);
        }

        return (waveServerMultiPageRequestHandler);
    }

    public WaveServerMultiPageRequestHandler getWaveServerMultiPageRequestHandlerForDelete (final String path)
    {
        WaveServerMultiPageRequestHandler waveServerMultiPageRequestHandler = null;

        if (true == (isAKnownWaveServerMultiPageRequestHandlerForDelete (path)))
        {
            waveServerMultiPageRequestHandler = m_multiPageRequestHandlersForDelete.get (path);
        }

        return (waveServerMultiPageRequestHandler);
    }

    @Override
    public void getListOfOptionsForGet (final Vector<String> optionsForGet)
    {
        optionsForGet.addAll (m_multiPageOptionsForGet);
    }

    @Override
    public void getListOfOptionsForPost (final Vector<String> optionsForPost)
    {
        optionsForPost.addAll (m_multiPageOptionsForPost);
    }

    @Override
    public void getListOfOptionsForPut (final Vector<String> optionsForPut)
    {
        optionsForPut.addAll (m_multiPageOptionsForPut);
    }

    @Override
    public void getListOfOptionsForDelete (final Vector<String> optionsForDelete)
    {
        optionsForDelete.addAll (m_multiPageOptionsForDelete);
    }

    @Override
    public void get (final HttpRequest httpRequest)
    {
        final String path = getPath ();
        final String uri = httpRequest.getUri ();
        final boolean isWildCardRequestHandlerRequiredAtTop = callWildCardRequestHandlerAtTop ();

        if (path.equals (uri))
        {
            if (true == isWildCardRequestHandlerRequiredAtTop)
            {
                wildCardRequestHandlerForGet (httpRequest);
            }
            else
            {
                super.get (httpRequest);
            }
        }
        else
        {
            final String adjustedPath = path + "/";
            String adjustedUri = uri;
            final int lengthOfAdjustedPath = adjustedPath.length ();
            final int position = uri.indexOf (adjustedPath, 0);

            if (-1 != position)
            {
                adjustedUri = adjustedUri.substring (lengthOfAdjustedPath);
            }

            debugTracePrintf ("WaveServerMultiPage.get : Adjusted URI : \"%s\"", adjustedUri);

            final WaveServerMultiPageRequestHandler waveServerMultiPageRequestHandler = getWaveServerMultiPageRequestHandlerForGet (adjustedUri);

            if (null != waveServerMultiPageRequestHandler)
            {
                waveServerMultiPageRequestHandler.execute (httpRequest);
            }
            else
            {
                wildCardRequestHandlerForGet (httpRequest);
            }
        }
    }

    public boolean callWildCardRequestHandlerAtTop ()
    {
        return false;
    }

    public void wildCardRequestHandlerForGet (final HttpRequest httpRequest)
    {
        final String uri = httpRequest.getUri ();
        final StringBuffer httpResponse = new StringBuffer ();
        final AcceptedStreamingSocket acceptedStreamingSocket = httpRequest.getAcceptedStreamingSocket ();

        debugTracePrintf ("WaveServerMultiPage.wildCardRequestHandlerForGet : There is no page implemented with the given path \"%s\"", uri);

        HttpToolKit.getNotFoundErrorString (httpResponse);

        if (null != acceptedStreamingSocket)
        {
            acceptedStreamingSocket.send (httpResponse);
        }
    }
}
