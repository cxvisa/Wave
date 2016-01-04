/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Resources.Repository;

import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Resources.ResourceEnum.WaveResourceEnumInterface;

public class WaveResourcesRepository
{
    private static WaveResourcesRepository               s_waveResourcesRepository = new WaveResourcesRepository ();

    private final Map<Integer, String>                   m_resourceIdToValueMap;
    private final Map<Integer, Vector<Integer>>          m_resourceEnumToResourceIdsMap;
    private final Map<Integer, Integer>                  m_resourceIdToResourceEnumMap;
    private final Map<Integer, String>                   m_resourceIdToNameMap;
    private final Map<String, Integer>                   m_nameToResourceIdMap;
    private final Map<Integer, String>                   m_resourceEnumIdToNameMap;
    private final Map<String, Integer>                   m_resourceEnumNameToIdMap;
    private final Map<String, WaveResourceEnumInterface> m_resourceIdNameToWaveResourceEnumInterfaceMap;

    private WaveResourcesRepository ()
    {
        m_resourceIdToValueMap = new HashMap<Integer, String> ();
        m_resourceEnumToResourceIdsMap = new HashMap<Integer, Vector<Integer>> ();
        m_resourceIdToResourceEnumMap = new HashMap<Integer, Integer> ();
        m_resourceIdToNameMap = new HashMap<Integer, String> ();
        m_nameToResourceIdMap = new HashMap<String, Integer> ();
        m_resourceEnumIdToNameMap = new HashMap<Integer, String> ();
        m_resourceEnumNameToIdMap = new HashMap<String, Integer> ();
        m_resourceIdNameToWaveResourceEnumInterfaceMap = new HashMap<String, WaveResourceEnumInterface> ();
    }

    public static WaveResourcesRepository getInstance ()
    {
        if (null == s_waveResourcesRepository)
        {
            s_waveResourcesRepository = new WaveResourcesRepository ();
        }

        WaveAssertUtils.waveAssert (null != s_waveResourcesRepository);

        return (s_waveResourcesRepository);
    }

    public void addResourceId (final String resourceName, final int resourceId, final String resourceValue)
    {
        m_resourceIdToValueMap.put (resourceId, resourceValue);
        m_resourceIdToNameMap.put (resourceId, resourceName);
        m_nameToResourceIdMap.put (resourceName, resourceId);
    }

    public void addResourceEnum (final String resourceEnumName, final int resourceEnumId)
    {
        m_resourceEnumIdToNameMap.put (new Integer (resourceEnumId), resourceEnumName);
        m_resourceEnumNameToIdMap.put (resourceEnumName, new Integer (resourceEnumId));
    }

    public void addResourceIdToResourceEnum (final int resourceId, final int resourceEnum)
    {
        if (!(m_resourceEnumToResourceIdsMap.containsKey (resourceEnum)))
        {
            m_resourceEnumToResourceIdsMap.put (resourceEnum, new Vector<Integer> ());
        }

        (m_resourceEnumToResourceIdsMap.get (resourceEnum)).add (resourceId);

        m_resourceIdToResourceEnumMap.put (new Integer (resourceId), new Integer (resourceEnum));
    }

    public void setResourceIdNameToWaveResourceEnumInterface (final String resourceIdName, final WaveResourceEnumInterface waveResourceEnumInterface)
    {
        m_resourceIdNameToWaveResourceEnumInterfaceMap.put (resourceIdName, waveResourceEnumInterface);
    }

    public WaveResourceEnumInterface getWaveResourceEnumInterfaceByResourceIdName (final String resourceIdName)
    {
        return (m_resourceIdNameToWaveResourceEnumInterfaceMap.get (resourceIdName));
    }
}
