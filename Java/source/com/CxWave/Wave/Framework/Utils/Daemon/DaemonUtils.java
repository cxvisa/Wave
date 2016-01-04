/***************************************************************************
 *   Copyright (C) 2015-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.Wave.Framework.Utils.Daemon;

public class DaemonUtils
{
    public static void daemonize ()
    {
        System.out.close ();
        System.err.close ();
    }
}
