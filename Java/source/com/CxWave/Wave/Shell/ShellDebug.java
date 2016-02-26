/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Shell;

import com.CxWave.Wave.Shell.Annotations.ShellSubordinate;

@ShellSubordinate (shell = ShellWave.class, token = "debug")
public class ShellDebug extends ShellBase
{
    public ShellDebug (final String name)
    {
        super (name);
    }
}
