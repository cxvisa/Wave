/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Shell;

public class ShellWave extends ShellBase
{
    public ShellWave (final String name)
    {
        super (name);
    }

    @Override
    public boolean isRootShell ()
    {
        return (true);
    }
}
