/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Persistence.Local;

import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.ObjectManagerPriority;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;
import com.CxWave.Wave.Resources.ResourceEnums.WaveObjectManagerPriority;

@ObjectManagerPriority (WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_PERSISTENCE_LOCAL)
public class PersistenceLocalObjectManager extends WaveLocalObjectManager
{
    private static PersistenceLocalObjectManager s_persistenceLocalObjectManager = null;
    private static boolean                       s_liveSyncEnabled               = false;
    private static WaveMutex                     s_liveSyncEnabledMutex          = new WaveMutex ();

    public PersistenceLocalObjectManager ()
    {
        super (getServiceName ());
    }

    public static String getServiceName ()
    {
        return ("Persistence Local Object Manager");
    }

    public static PersistenceLocalObjectManager getInstance ()
    {
        if (null == s_persistenceLocalObjectManager)
        {
            s_persistenceLocalObjectManager = new PersistenceLocalObjectManager ();
        }

        WaveAssertUtils.waveAssert (null != s_persistenceLocalObjectManager);

        return (s_persistenceLocalObjectManager);
    }

    public static WaveServiceId getWaveServiceId ()
    {
        return ((getInstance ()).getServiceId ());
    }

    public static boolean getLiveSyncEnabled ()
    {
        boolean liveSyncEnabled = false;

        s_liveSyncEnabledMutex.lock ();

        liveSyncEnabled = s_liveSyncEnabled;

        s_liveSyncEnabledMutex.unlock ();

        return (liveSyncEnabled);
    }

    public static void setLiveSyncEnabled (final boolean liveSyncEnabled)
    {
        s_liveSyncEnabledMutex.lock ();

        s_liveSyncEnabled = liveSyncEnabled;

        s_liveSyncEnabledMutex.unlock ();
    }
}
