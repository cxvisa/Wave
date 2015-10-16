/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Database;

import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;

public class DatabaseObjectManager extends WaveLocalObjectManager
{
    private static DatabaseObjectManager s_databaseObjectManager = new DatabaseObjectManager ();
    private static boolean               s_isDatabaseEnabled     = true;
    private static int                   s_databasePort          = 3016;

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

    public static int getDatabasePort ()
    {
        return s_databasePort;
    }

    public static void setDatabasePort (final int databasePort)
    {
        s_databasePort = databasePort;
    }
}
