/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.HttpInterface;

import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

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
}
