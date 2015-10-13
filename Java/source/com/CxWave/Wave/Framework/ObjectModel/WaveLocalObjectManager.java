/***************************************************************************
 *   Copyright (C) 2015-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import java.util.HashMap;
import java.util.Map;

public class WaveLocalObjectManager extends WaveObjectManager
{
    static private Map<WaveServiceId, WaveServiceId> s_localWaveServices = new HashMap<WaveServiceId, WaveServiceId> ();

    public WaveLocalObjectManager (final String waveLocalObjectManagerName)
    {
        super (waveLocalObjectManagerName);

        s_localWaveServices.put (getServiceId (), getServiceId ());
    }

    protected boolean isALocalWaveService ()
    {
        return (true);
    }

    public static boolean isALocalService (final WaveServiceId waveServiceId)
    {
        return (s_localWaveServices.containsKey (waveServiceId));
    }
}
