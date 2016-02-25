/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectModel;

import java.util.HashMap;
import java.util.Map;

import com.CxWave.Wave.Framework.ObjectModel.Annotations.NonOM;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;

@NonOM
public class WaveLocalObjectManagerForUserSpecificTasks extends WaveLocalObjectManager
{
    private static final Map<WaveServiceId, WaveServiceId> s_userSpecificServicesMap      = new HashMap<WaveServiceId, WaveServiceId> ();
    private static final WaveMutex                         s_userSpecificServicesMapMutex = new WaveMutex ();

    public WaveLocalObjectManagerForUserSpecificTasks (final String waveLocalObjectManagerName)
    {
        super (waveLocalObjectManagerName);

        addToUserSpecificServicesMap (getServiceId ());
    }

    private static void addToUserSpecificServicesMap (final WaveServiceId waveServiceId)
    {
        s_userSpecificServicesMapMutex.lock ();

        s_userSpecificServicesMap.put (waveServiceId, waveServiceId);

        s_userSpecificServicesMapMutex.unlock ();
    }

    public static boolean isAUserSpecificService (final WaveServiceId waveServiceId)
    {
        s_userSpecificServicesMapMutex.lock ();

        final boolean isUserSpecificService = s_userSpecificServicesMap.containsKey (waveServiceId);

        s_userSpecificServicesMapMutex.unlock ();

        return (isUserSpecificService);
    }
}
