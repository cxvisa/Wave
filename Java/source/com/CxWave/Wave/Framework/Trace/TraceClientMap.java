/***************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave.Framework.Trace;

import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

import com.CxWave.Wave.Framework.Type.TraceClientId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Debug.DebugUtils;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class TraceClientMap
{
    private final Map<TraceClientId, TraceLevel> m_traceClientsAndLevels;
    private final Map<TraceClientId, String>     m_traceClientsAndNames;
    private final TraceClientId                  m_nextAvailableTraceClientId;

    private final WaveMutex                      m_traceClientMapMutex;

    private static final TraceClientMap          s_traceClientMap = new TraceClientMap ();

    private TraceClientMap ()
    {
        m_traceClientsAndLevels = new HashMap<TraceClientId, TraceLevel> ();
        m_traceClientsAndNames = new HashMap<TraceClientId, String> ();

        m_nextAvailableTraceClientId = new TraceClientId (1);

        m_traceClientMapMutex = new WaveMutex ();
    }

    public boolean isAKnownClient (final TraceClientId traceClientId)
    {
        m_traceClientMapMutex.lock ();

        final boolean isKnown = m_traceClientsAndLevels.containsKey (traceClientId);

        m_traceClientMapMutex.unlock ();

        return (isKnown);
    }

    public boolean isAKnownClient (final String traceClientName)
    {
        m_traceClientMapMutex.lock ();

        final boolean isKnown = m_traceClientsAndNames.containsValue (traceClientName);

        m_traceClientMapMutex.unlock ();

        return (isKnown);
    }

    public TraceClientId addClient (final TraceLevel traceLevel, final String traceClientName)
    {
        m_traceClientMapMutex.lock ();

        TraceClientId newTraceClientId = null;

        if (m_traceClientsAndNames.containsValue (traceClientName))
        {
            DebugUtils.prettyPrint (m_traceClientsAndNames.keySet ());

            m_traceClientMapMutex.unlock ();

            WaveAssertUtils.waveAssert ();
        }
        else
        {
            newTraceClientId = new TraceClientId (m_nextAvailableTraceClientId);
            m_nextAvailableTraceClientId.increment ();

            m_traceClientsAndLevels.put (newTraceClientId, traceLevel);
            m_traceClientsAndNames.put (newTraceClientId, traceClientName);

            m_traceClientMapMutex.unlock ();
        }

        return (newTraceClientId);
    }

    public void removeTraceClient (final TraceClientId traceClientId)
    {
        m_traceClientMapMutex.lock ();

        if (m_traceClientsAndLevels.containsKey (traceClientId))
        {
            m_traceClientsAndLevels.remove (traceClientId);

            if (m_traceClientsAndNames.containsKey (traceClientId))
            {
                m_traceClientsAndNames.remove (traceClientId);

                m_traceClientMapMutex.unlock ();
            }
            else
            {
                m_traceClientMapMutex.unlock ();

                WaveAssertUtils.waveAssert ();
            }
        }
        else
        {
            m_traceClientMapMutex.unlock ();

            WaveAssertUtils.waveAssert ();
        }
    }

    public void setTraceClientLevel (final TraceClientId traceClientId, final TraceLevel traceLevel)
    {
        m_traceClientMapMutex.lock ();

        if (m_traceClientsAndLevels.containsKey (traceClientId))
        {
            m_traceClientsAndLevels.replace (traceClientId, traceLevel);
        }
        else
        {
            System.err.println ("TraceClientMap.setTraceClientLevel : TraceClientId not known.  Ignoring.");
        }

        m_traceClientMapMutex.unlock ();
    }

    public TraceLevel getTraceClientLevel (final TraceClientId traceClientId)
    {
        m_traceClientMapMutex.lock ();

        TraceLevel traceLevel = null;

        if (m_traceClientsAndLevels.containsKey (traceClientId))
        {
            traceLevel = m_traceClientsAndLevels.get (traceClientId);
        }
        else
        {
            System.err.println ("TraceClientMap.getTraceClientLevel : TraceClientId not known.");

            WaveAssertUtils.waveAssert ();
        }

        m_traceClientMapMutex.unlock ();

        return (traceLevel);
    }

    public void getTraceClientsAndLevels (final Vector<TraceClientId> traceClients, final Vector<TraceLevel> traceLevels)
    {
        m_traceClientMapMutex.lock ();

        for (final Map.Entry<TraceClientId, TraceLevel> entry : m_traceClientsAndLevels.entrySet ())
        {
            traceClients.add (entry.getKey ());
            traceLevels.add (entry.getValue ());
        }

        m_traceClientMapMutex.unlock ();
    }

    public void getTraceClientsAndLevels (final Map<TraceClientId, TraceLevel> traceClientsAndLevels)
    {
        m_traceClientMapMutex.lock ();

        for (final Map.Entry<TraceClientId, TraceLevel> entry : m_traceClientsAndLevels.entrySet ())
        {
            traceClientsAndLevels.put (entry.getKey (), entry.getValue ());
        }

        m_traceClientMapMutex.unlock ();
    }

    public String getTraceClientName (final TraceClientId traceClientId)
    {
        String traceClientName = null;

        m_traceClientMapMutex.lock ();

        traceClientName = m_traceClientsAndNames.get (traceClientId);

        m_traceClientMapMutex.unlock ();

        return (traceClientName);
    }

    public static TraceClientMap getInstance ()
    {
        return (s_traceClientMap);
    }

    public void getClientsAndLevels (final Vector<TraceClientId> traceClientIdsVector, final Vector<TraceLevel> traceLevelsVector)
    {
        m_traceClientMapMutex.lock ();

        for (final Map.Entry<TraceClientId, TraceLevel> entry : m_traceClientsAndLevels.entrySet ())
        {
            final TraceClientId traceClientId = entry.getKey ();
            final TraceLevel traceLevel = entry.getValue ();

            traceClientIdsVector.add (traceClientId);
            traceLevelsVector.add (traceLevel);
        }

        m_traceClientMapMutex.unlock ();
    }
}
