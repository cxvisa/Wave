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

public class WaveServerPageDirectoryEntry
{
    private String                                          m_nodeName    = "";
    private WaveServerPage                                  m_waveServerPage;
    private final Map<String, WaveServerPageDirectoryEntry> m_siblingsMap = new HashMap<String, WaveServerPageDirectoryEntry> ();

    public WaveServerPageDirectoryEntry (final String nodeName, final WaveServerPage waveServerPage)
    {
        m_nodeName = nodeName;
        m_waveServerPage = waveServerPage;
    }

    public WaveServerPage getWaveServerPage ()
    {
        return (m_waveServerPage);
    }

    public void setWaveServerPage (final WaveServerPage waveServerPage)
    {
        m_waveServerPage = waveServerPage;
    }

    public boolean isAKnownImmediateSibling (final String immediateSiblingName)
    {
        return (m_siblingsMap.containsKey (immediateSiblingName));
    }

    public WaveServerPageDirectoryEntry getImmediateSibling (final String immediateSiblingName)
    {
        WaveServerPageDirectoryEntry waveServerPageDirectoryEntry = null;

        if (isAKnownImmediateSibling (immediateSiblingName))
        {
            waveServerPageDirectoryEntry = m_siblingsMap.get (immediateSiblingName);
        }

        if (null == waveServerPageDirectoryEntry)
        {
            waveServerPageDirectoryEntry = m_siblingsMap.get ("*");
        }

        return (waveServerPageDirectoryEntry);
    }

    public boolean isAKnownSibling (final String siblingName)
    {
        final Vector<String> siblingNameTokens = new Vector<String> ();
        int numberOFTokensInSiblingName = 0;
        int i = 0;
        WaveServerPageDirectoryEntry tempWaveServerPageDirectoryEntry = this;

        WaveStringUtils.tokenize (siblingName, siblingNameTokens, '/');

        numberOFTokensInSiblingName = siblingNameTokens.size ();

        for (i = 0; i < numberOFTokensInSiblingName; i++)
        {
            final WaveServerPageDirectoryEntry temp = tempWaveServerPageDirectoryEntry.getImmediateSibling (siblingNameTokens.get (i));

            // If not found the exact match, check for wild card handler (*)

            if (null == temp)
            {
                tempWaveServerPageDirectoryEntry = tempWaveServerPageDirectoryEntry.getImmediateSibling ("*");
            }

            if (null == tempWaveServerPageDirectoryEntry)
            {
                return (false);
            }
        }

        return (true);
    }

    public WaveServerPageDirectoryEntry getSibling (final String siblingName)
    {
        final Vector<String> siblingNameTokens = new Vector<String> ();
        int numberOFTokensInSiblingName = 0;
        int i = 0;
        WaveServerPageDirectoryEntry tempWaveServerPageDirectoryEntry = this;

        WaveStringUtils.tokenize (siblingName, siblingNameTokens, '/');

        numberOFTokensInSiblingName = siblingNameTokens.size ();

        for (i = 0; i < numberOFTokensInSiblingName; i++)
        {
            tempWaveServerPageDirectoryEntry = tempWaveServerPageDirectoryEntry.getImmediateSibling (siblingNameTokens.get (i));

            if (null == tempWaveServerPageDirectoryEntry)
            {
                return (null);
            }
        }

        return (tempWaveServerPageDirectoryEntry);
    }

    public void addImmediateSibling (final String immediateSiblingName, final WaveServerPage waveServerPage)
    {
        final boolean isImmeidateSiblingKnown = isAKnownImmediateSibling (immediateSiblingName);

        if (false == isImmeidateSiblingKnown)
        {
            final WaveServerPageDirectoryEntry newWaveServerPageDirectoryEntry = new WaveServerPageDirectoryEntry (immediateSiblingName, waveServerPage);

            WaveAssertUtils.waveAssert (null != newWaveServerPageDirectoryEntry);

            m_siblingsMap.put (immediateSiblingName, newWaveServerPageDirectoryEntry);
        }
        else
        {
            if (null != waveServerPage)
            {
                final WaveServerPageDirectoryEntry existingWaveServerPageDirectoryEntry = m_siblingsMap.get (immediateSiblingName);
                final WaveServerPage existingWaveServerPage = existingWaveServerPageDirectoryEntry.getWaveServerPage ();

                if (null == existingWaveServerPage)
                {
                    existingWaveServerPageDirectoryEntry.setWaveServerPage (waveServerPage);
                }
                else
                {
                    WaveTraceUtils.fatalTracePrintf ("WaveServerPageDirectoryEntry.addImmediateSibling : Adding a duplicate immediate Sibling : \'%s\'", immediateSiblingName);
                    WaveAssertUtils.waveAssert ();
                }
            }
        }
    }

    public void addSibling (final String siblingName, final WaveServerPage waveServerPage)
    {
        final Vector<String> siblingNameTokens = new Vector<String> ();
        int numberOFTokensInSiblingName = 0;
        int i = 0;
        WaveServerPageDirectoryEntry tempWaveServerPageDirectoryEntry = this;

        WaveStringUtils.tokenize (siblingName, siblingNameTokens, '/');

        numberOFTokensInSiblingName = siblingNameTokens.size ();

        for (i = 0; i < numberOFTokensInSiblingName; i++)
        {
            if ((numberOFTokensInSiblingName - 1) == i)
            {
                tempWaveServerPageDirectoryEntry.addImmediateSibling (siblingNameTokens.get (i), waveServerPage);
            }
            else
            {
                tempWaveServerPageDirectoryEntry.addImmediateSibling (siblingNameTokens.get (i), null);
            }

            tempWaveServerPageDirectoryEntry = tempWaveServerPageDirectoryEntry.getImmediateSibling (siblingNameTokens.get (i));

            WaveAssertUtils.waveAssert (null != tempWaveServerPageDirectoryEntry);
        }
    }

    public void print (final String prefix)
    {
        WaveServerPageDirectoryEntry waveServerPageDirectoryEntry = null;
        String postfix = "";

        if (null != m_waveServerPage)
        {
            postfix = "(.)";
        }

        WaveTraceUtils.infoTracePrintf (prefix + m_nodeName + postfix);

        for (final Map.Entry<String, WaveServerPageDirectoryEntry> entry : m_siblingsMap.entrySet ())
        {
            waveServerPageDirectoryEntry = entry.getValue ();

            WaveAssertUtils.waveAssert (null != waveServerPageDirectoryEntry);

            waveServerPageDirectoryEntry.print (prefix + "|-");
        }
    }

    public WaveServerPage getWaveServerPageForRelativePath (final String path)
    {
        final WaveServerPageDirectoryEntry waveServerPageDirectoryEntry = getSibling (path);

        if (null != waveServerPageDirectoryEntry)
        {
            return (waveServerPageDirectoryEntry.getWaveServerPage ());
        }
        else
        {
            return (null);
        }
    }
}
