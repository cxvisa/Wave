/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core;

import com.CxWave.Wave.Framework.ObjectModel.WaveLocalObjectManager;
import com.CxWave.Wave.Framework.ObjectModel.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;

public class WaveFrameworkObjectManager extends WaveLocalObjectManager
{
    private static WaveFrameworkObjectManager s_waveFrameworkObjectManager = new WaveFrameworkObjectManager ();

    private static String s_frameworkConfigurationFile           = null;
    private static String s_frameworkConfigurationBackupFile     = null;
    private static String s_frameworkGlobalConfigurationFile     = null;
    private static String s_frameworkGlobalConfigurationTempFile = null;
    private static String s_lockFileForConfigurationFile         = null;

    private WaveFrameworkObjectManager ()
    {
        super (getServiceName ());
    }

    public static String getServiceName ()
    {
        return ("Wave Framework");
    }

    public WaveFrameworkObjectManager getInstance ()
    {
        if (null == s_waveFrameworkObjectManager)
        {
            s_waveFrameworkObjectManager = new WaveFrameworkObjectManager ();
        }

        WaveAssertUtils.waveAssert (null != s_waveFrameworkObjectManager);

        return (s_waveFrameworkObjectManager);
    }

    public WaveServiceId getWaveServiceId ()
    {
        return ((getInstance ()).getWaveServiceId ());
    }

    public static void setConfigurationFile (final String configurationFile)
    {
        s_frameworkConfigurationFile = configurationFile;
        s_frameworkConfigurationBackupFile = s_frameworkConfigurationFile + ".bk";
    }

    public static void setGlobalConfigurationFile (final String globalConfigurationFile)
    {
        s_frameworkGlobalConfigurationFile = globalConfigurationFile;
        s_frameworkGlobalConfigurationTempFile = s_frameworkGlobalConfigurationFile + ".tmp";
    }

    public static String getLockFileForConfigurationFile ()
    {
        return s_lockFileForConfigurationFile;
    }

    public static void setLockFileForConfigurationFile (final String lockFileForConfigurationFile)
    {
        s_lockFileForConfigurationFile = lockFileForConfigurationFile;
    }
}
