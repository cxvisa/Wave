/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Persistence;

import com.CxWave.Wave.Framework.ObjectModel.WaveObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NativeService;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.ObjectManagerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.PrePhaseService;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Resources.ResourceEnums.WaveObjectManagerPriority;

@PrePhaseService
@NativeService
@ObjectManagerPriority (WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_PERSISTENCE)
public class PersistenceObjectManager extends WaveObjectManager
{
    private static PersistenceObjectManager s_persistenceObjectManager = null;

    private PersistenceObjectManager ()
    {
        super (getServiceName ());
    }

    public static String getServiceName ()
    {
        return ("Persistence");
    }

    public static PersistenceObjectManager getInstance ()
    {
        if (null == s_persistenceObjectManager)
        {
            s_persistenceObjectManager = new PersistenceObjectManager ();
        }

        WaveAssertUtils.waveAssert (null != s_persistenceObjectManager);

        return (s_persistenceObjectManager);
    }

    public static WaveServiceId getWaveServiceId ()
    {
        return ((getInstance ()).getServiceId ());
    }
}
