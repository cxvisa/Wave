/***********************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.ToolKits.Framework;

public class FrameworkToolKit
{
    private static boolean s_isRunningAsADaemon = false;

    private FrameworkToolKit ()
    {
    }

    public boolean getIsRunningAsADaemon ()
    {
        return (s_isRunningAsADaemon);
    }

    public void setIsRunningAsADaemon (final boolean isRunningAsADaemon)
    {
        s_isRunningAsADaemon = isRunningAsADaemon;
    }
}
