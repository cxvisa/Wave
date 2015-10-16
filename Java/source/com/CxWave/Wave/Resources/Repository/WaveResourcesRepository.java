/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Resources.Repository;

import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;

public class WaveResourcesRepository
{
    private static WaveResourcesRepository s_waveResourcesRepository = new WaveResourcesRepository ();

    private Map<Integer, String>          m_resourceIdToValueMap;
    private Map<Integer, Vector<Integer>> m_resourceEnumToResourceIdsMap;
    private Map<Integer, String>          m_resourceIdToNameMap;
    private Map<String, Integer>          m_nameToResourceIdMap;

    private WaveResourcesRepository ()
    {
        m_resourceIdToValueMap = new HashMap<Integer, String> ();
        m_resourceEnumToResourceIdsMap = new HashMap<Integer, Vector<Integer>> ();
        m_resourceIdToNameMap = new HashMap<Integer, String> ();
        m_nameToResourceIdMap = new HashMap<String, Integer> ();
    }

    public static WaveResourcesRepository getInstance ()
    {
        if (null != s_waveResourcesRepository)
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

    public void addResourceIdToResourceEnum (final int resourceId, final int resourceEnum)
    {
        if (!(m_resourceEnumToResourceIdsMap.containsKey (resourceEnum)))
        {
            m_resourceEnumToResourceIdsMap.put (resourceEnum, new Vector<Integer> ());
        }

        (m_resourceEnumToResourceIdsMap.get (resourceEnum)).add (resourceId);
    }
}
