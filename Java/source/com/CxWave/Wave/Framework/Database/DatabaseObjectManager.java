/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Database;

import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.NativeService;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.ObjectManagerPriority;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.PrePhaseService;
import com.CxWave.Wave.Framework.Type.SI32;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Resources.ResourceEnums.WaveObjectManagerPriority;

@PrePhaseService
@NativeService
@ObjectManagerPriority (WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_DATABASE)
public class DatabaseObjectManager extends WaveLocalObjectManager
{
    private static DatabaseObjectManager s_databaseObjectManager = new DatabaseObjectManager ();
    private static boolean               s_isDatabaseEnabled     = true;
    private static SI32                  s_databasePort          = new SI32 (9013L);

    private DatabaseObjectManager ()
    {
        super (getClassName ());
    }

    public static DatabaseObjectManager getInstance ()
    {
        if (null == s_databaseObjectManager)
        {
            s_databaseObjectManager = new DatabaseObjectManager ();
        }

        WaveAssertUtils.waveAssert (null != s_databaseObjectManager);

        return (s_databaseObjectManager);
    }

    public static String getClassName ()
    {
        return ("Database");
    }

    public static WaveServiceId getWaveServiceId ()
    {
        return ((getInstance ()).getServiceId ());
    }

    public static boolean getIsDatabaseEnabled ()
    {
        return s_isDatabaseEnabled;
    }

    public static void setIsDatabaseEnabled (final boolean isDatabaseEnabled)
    {
        s_isDatabaseEnabled = isDatabaseEnabled;
    }

    public static SI32 getDatabasePort ()
    {
        return s_databasePort;
    }

    public static void setDatabasePort (final SI32 databasePort)
    {
        s_databasePort = databasePort;
    }
}
