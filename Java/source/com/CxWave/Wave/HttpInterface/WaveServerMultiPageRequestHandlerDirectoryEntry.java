/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.HttpInterface;

import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.String.WaveStringUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;

public class WaveServerMultiPageRequestHandlerDirectoryEntry
{
    private String                                                             m_nodeName    = "";
    private WaveServerMultiPageRequestHandler                                  m_waveServerMultiPageRequestHandler;
    private final Map<String, WaveServerMultiPageRequestHandlerDirectoryEntry> m_siblingsMap = new HashMap<String, WaveServerMultiPageRequestHandlerDirectoryEntry> ();

    public WaveServerMultiPageRequestHandlerDirectoryEntry (final String nodeName, final WaveServerMultiPageRequestHandler waveServerMultiPageRequestHandler)
    {
        m_nodeName = nodeName;
        m_waveServerMultiPageRequestHandler = waveServerMultiPageRequestHandler;
    }

    public WaveServerMultiPageRequestHandler getWaveServerMultiPageRequestHandler ()
    {
        return (m_waveServerMultiPageRequestHandler);
    }

    public void setWaveServerMultiPageRequestHandler (final WaveServerMultiPageRequestHandler waveServerMultiPageRequestHandler)
    {
        m_waveServerMultiPageRequestHandler = waveServerMultiPageRequestHandler;
    }

    public boolean isAKnownImmediateSibling (final String immediateSiblingName)
    {
        return (m_siblingsMap.containsKey (immediateSiblingName));
    }

    public WaveServerMultiPageRequestHandlerDirectoryEntry getImmediateSibling (final String immediateSiblingName)
    {
        WaveServerMultiPageRequestHandlerDirectoryEntry WaveServerMultiPageRequestHandlerDirectoryEntry = null;

        if (isAKnownImmediateSibling (immediateSiblingName))
        {
            WaveServerMultiPageRequestHandlerDirectoryEntry = m_siblingsMap.get (immediateSiblingName);
        }

        if (null == WaveServerMultiPageRequestHandlerDirectoryEntry)
        {
            WaveServerMultiPageRequestHandlerDirectoryEntry = m_siblingsMap.get ("*");
        }

        return (WaveServerMultiPageRequestHandlerDirectoryEntry);
    }

    public boolean isAKnownSibling (final String siblingName)
    {
        final Vector<String> siblingNameTokens = new Vector<String> ();
        int numberOFTokensInSiblingName = 0;
        int i = 0;
        WaveServerMultiPageRequestHandlerDirectoryEntry tempWaveServerMultiPageRequestHandlerDirectoryEntry = this;

        WaveStringUtils.tokenize (siblingName, siblingNameTokens, '/');

        numberOFTokensInSiblingName = siblingNameTokens.size ();

        for (i = 0; i < numberOFTokensInSiblingName; i++)
        {
            final WaveServerMultiPageRequestHandlerDirectoryEntry temp = tempWaveServerMultiPageRequestHandlerDirectoryEntry.getImmediateSibling (siblingNameTokens.get (i));

            // If not found the exact match, check for wild card handler (*)

            if (null == temp)
            {
                tempWaveServerMultiPageRequestHandlerDirectoryEntry = tempWaveServerMultiPageRequestHandlerDirectoryEntry.getImmediateSibling ("*");
            }

            if (null == tempWaveServerMultiPageRequestHandlerDirectoryEntry)
            {
                return (false);
            }
        }

        return (true);
    }

    public WaveServerMultiPageRequestHandlerDirectoryEntry getSibling (final String siblingName)
    {
        final Vector<String> siblingNameTokens = new Vector<String> ();
        int numberOFTokensInSiblingName = 0;
        int i = 0;
        WaveServerMultiPageRequestHandlerDirectoryEntry tempWaveServerMultiPageRequestHandlerDirectoryEntry = this;

        WaveStringUtils.tokenize (siblingName, siblingNameTokens, '/');

        numberOFTokensInSiblingName = siblingNameTokens.size ();

        for (i = 0; i < numberOFTokensInSiblingName; i++)
        {
            tempWaveServerMultiPageRequestHandlerDirectoryEntry = tempWaveServerMultiPageRequestHandlerDirectoryEntry.getImmediateSibling (siblingNameTokens.get (i));

            if (null == tempWaveServerMultiPageRequestHandlerDirectoryEntry)
            {
                return (null);
            }
        }

        return (tempWaveServerMultiPageRequestHandlerDirectoryEntry);
    }

    public void addImmediateSibling (final String immediateSiblingName, final WaveServerMultiPageRequestHandler waveServerMultiPageRequestHandler)
    {
        final boolean isImmeidateSiblingKnown = isAKnownImmediateSibling (immediateSiblingName);

        if (false == isImmeidateSiblingKnown)
        {
            final WaveServerMultiPageRequestHandlerDirectoryEntry newWaveServerMultiPageRequestHandlerDirectoryEntry = new WaveServerMultiPageRequestHandlerDirectoryEntry (immediateSiblingName, waveServerMultiPageRequestHandler);

            WaveAssertUtils.waveAssert (null != newWaveServerMultiPageRequestHandlerDirectoryEntry);

            m_siblingsMap.put (immediateSiblingName, newWaveServerMultiPageRequestHandlerDirectoryEntry);
        }
        else
        {
            if (null != waveServerMultiPageRequestHandler)
            {
                final WaveServerMultiPageRequestHandlerDirectoryEntry existingWaveServerMultiPageRequestHandlerDirectoryEntry = m_siblingsMap.get (immediateSiblingName);
                final WaveServerMultiPageRequestHandler existingWaveServerMultiPageRequestHandler = existingWaveServerMultiPageRequestHandlerDirectoryEntry.getWaveServerMultiPageRequestHandler ();

                if (null == existingWaveServerMultiPageRequestHandler)
                {
                    existingWaveServerMultiPageRequestHandlerDirectoryEntry.setWaveServerMultiPageRequestHandler (waveServerMultiPageRequestHandler);
                }
                else
                {
                    WaveTraceUtils.fatalTracePrintf ("WaveServerMultiPageRequestHandlerDirectoryEntry.addImmediateSibling : Adding a duplicate immediate Sibling : \'%s\'", immediateSiblingName);
                    WaveAssertUtils.waveAssert ();
                }
            }
        }
    }

    public void addSibling (final String siblingName, final WaveServerMultiPageRequestHandler waveServerMultiPageRequestHandler)
    {
        final Vector<String> siblingNameTokens = new Vector<String> ();
        int numberOFTokensInSiblingName = 0;
        int i = 0;
        WaveServerMultiPageRequestHandlerDirectoryEntry tempWaveServerMultiPageRequestHandlerDirectoryEntry = this;

        WaveStringUtils.tokenize (siblingName, siblingNameTokens, '/');

        numberOFTokensInSiblingName = siblingNameTokens.size ();

        for (i = 0; i < numberOFTokensInSiblingName; i++)
        {
            if ((numberOFTokensInSiblingName - 1) == i)
            {
                tempWaveServerMultiPageRequestHandlerDirectoryEntry.addImmediateSibling (siblingNameTokens.get (i), waveServerMultiPageRequestHandler);
            }
            else
            {
                tempWaveServerMultiPageRequestHandlerDirectoryEntry.addImmediateSibling (siblingNameTokens.get (i), null);
            }

            tempWaveServerMultiPageRequestHandlerDirectoryEntry = tempWaveServerMultiPageRequestHandlerDirectoryEntry.getImmediateSibling (siblingNameTokens.get (i));

            WaveAssertUtils.waveAssert (null != tempWaveServerMultiPageRequestHandlerDirectoryEntry);
        }
    }

    public void print (final String prefix)
    {
        WaveServerMultiPageRequestHandlerDirectoryEntry WaveServerMultiPageRequestHandlerDirectoryEntry = null;
        String postfix = "";

        if (null != m_waveServerMultiPageRequestHandler)
        {
            postfix = "(.)";
        }

        WaveTraceUtils.infoTracePrintf (prefix + m_nodeName + postfix);

        for (final Map.Entry<String, WaveServerMultiPageRequestHandlerDirectoryEntry> entry : m_siblingsMap.entrySet ())
        {
            WaveServerMultiPageRequestHandlerDirectoryEntry = entry.getValue ();

            WaveAssertUtils.waveAssert (null != WaveServerMultiPageRequestHandlerDirectoryEntry);

            WaveServerMultiPageRequestHandlerDirectoryEntry.print (prefix + "|-");
        }
    }

    public void print ()
    {
        print ("");
    }

    public WaveServerMultiPageRequestHandler getWaveServerMultiPageRequestHandlerForRelativePath (final String path)
    {
        final WaveServerMultiPageRequestHandlerDirectoryEntry WaveServerMultiPageRequestHandlerDirectoryEntry = getSibling (path);

        if (null != WaveServerMultiPageRequestHandlerDirectoryEntry)
        {
            return (WaveServerMultiPageRequestHandlerDirectoryEntry.getWaveServerMultiPageRequestHandler ());
        }
        else
        {
            return (null);
        }
    }
}
