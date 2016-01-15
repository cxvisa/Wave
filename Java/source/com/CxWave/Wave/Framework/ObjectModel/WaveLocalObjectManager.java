/***************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import java.util.HashMap;
import java.util.Map;

import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonOM;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Type.WaveServiceId;

@NonOM
public class WaveLocalObjectManager extends WaveObjectManager
{
    static private Map<WaveServiceId, WaveServiceId> s_localWaveServices = new HashMap<WaveServiceId, WaveServiceId> ();

    public WaveLocalObjectManager (final String waveLocalObjectManagerName, final UI32 stackSize)
    {
        super (waveLocalObjectManagerName, stackSize);

        s_localWaveServices.put (getServiceId (), getServiceId ());
    }

    public WaveLocalObjectManager (final String waveLocalObjectManagerName)
    {
        super (waveLocalObjectManagerName);

        s_localWaveServices.put (getServiceId (), getServiceId ());
    }

    @Override
    protected boolean isALocalWaveService ()
    {
        return (true);
    }

    public static boolean isALocalService (final WaveServiceId waveServiceId)
    {
        return (s_localWaveServices.containsKey (waveServiceId));
    }
}
